// [[Rcpp::plugins(openmp)]]
#ifdef _OPENMP
#include <omp.h>
#endif
#include <Rcpp.h>
#include <RcppEigen.h>
#include <Eigen/Core>
#include <random>
#include "distributions.h"
#include "concurrentqueue.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace RcppEigen;
using namespace Eigen;
inline void initialize_file( std::ofstream& outFile,int M,int N){
  bool queueFull;
  queueFull=0;


  outFile<< "iteration,"<<"mu,";
  for(unsigned int i = 0; i < M; ++i){
    outFile << "beta[" << (i+1) << "],";

  }
  outFile<<"sigmaE,"<<"sigmaG,";
  for(unsigned int i = 0; i < M; ++i){
    outFile << "comp[" << (i+1) << "],";
  }
  unsigned int i;
  for(i = 0; i < (N-1);i++){
    outFile << "epsilon[" << (i+1) << "],";
  }

  outFile << "epsilon[" << (i+1) << "]";
  outFile<<"\n";
}

//' BayesR sampler
//'
//' @param outputFile The file in which the samples aftare burnin will be stored
//' @param seed random seed
//' @param max_iterations total of number of samples taken
//' @param burn_in integer leq than max_iterations, number of samples used for burn in, after which, al samples will  be stored in the outputFile
//' @param thinning thinning regime, not implemented
//' @param X matrix of snp markers, or covariates of interest
//' @param Y vector of response variates, must have the same number of rows as X
//' @param sigma0 variance of the zero-centered normal prior over the intercept
//' @param v0E degrees of  freedom of the prior inverse scaled chi-squared distribution over residues variance
//' @param s02E  scale parameter of the prior inverse scaled chi-squared distribution over residues variance
//' @param v0G degrees of freedom of the prior inverse scaled chi-squared distribution over genetic effects variance
//' @param s02G  scale parameter of the prior inverse scaled chi-squared distribution over residues variance
//' @param cva Vector of mixture components variances.
//'
//' @return (max_iteration - burn_in) modulo thinning samples saved in outputFile.
//' @export
//'
//' @examples
// [[Rcpp::export]]
void BayesRSamplerV2(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y,double sigma0, double v0E, double s02E, double v0G, double s02G,Eigen::VectorXd cva) {
  int flag;
  moodycamel::ConcurrentQueue<Eigen::VectorXd> q;
  flag=0;
  int N(Y.size());
  int M(X.cols());
  VectorXd components(M);
  std::ofstream outFile;

  outFile.open(outputFile);
  initialize_file(outFile,M,N);
  VectorXd sampleq(2*M+4+N);
  IOFormat CommaInitFmt(StreamPrecision, DontAlignCols, ", ", ", ", "", "", "", "");
  int K(cva.size()+1);
  ////////////validate inputs

  if(max_iterations < burn_in || max_iterations<1 || burn_in<1) //validations related to mcmc burnin and iterations
  {
    Rcpp::Rcerr<<"error: burn_in has to be a positive integer and smaller than the maximum number of iterations ";
    return;
  }
  if(sigma0 < 0 || v0E < 0 || s02E < 0 || v0G < 0||  s02G < 0 )//validations related to hyperparameters
  {
    Rcpp::Rcerr<<"error: hyper parameters have to be positive";
    //return;
  }
  if((cva.array()==0).any() )//validations related to hyperparameters
  {
    Rcpp::Rcerr<<"error: the zero component is already included in the model by default";
    //return;
  }
  if((cva.array()<0).any() )//validations related to hyperparameters
  {
    Rcpp::Rcerr<<"error: the variance of the components should be positive";
    //return;
  }
  /////end of declarations//////


//  Eigen::initParallel();
 // Eigen::setNbThreads(10);

#ifdef _OPENMP
 omp_set_num_threads(2);
#endif
#pragma omp parallel num_threads(2) shared(flag,q,M,N)
{
#pragma omp sections
{
  //begin producer
  {

    //mean and residual variables
    double mu; // mean or intercept
    double sigmaG; //genetic variance
    double sigmaE; // residuals variance

    //component variables
    VectorXd priorPi(K); // prior probabilities for each component
    VectorXd pi(K); // mixture probabilities
    VectorXd cVa(K); //component-specific variance
    VectorXd logL(K); // log likelihood of component
    VectorXd muk(K); // mean of k-th component marker effect size
    VectorXd denom(K-1); // temporal variable for computing the inflation of the effect variance for a given non-zero componnet
    double num;//storing dot product
    int m0; // total num ber of markes in model
    VectorXd v(K); //variable storing the component assignment
    VectorXd cVaI(K);// inverse of the component variances

    //linear model variables
    MatrixXd beta(M,1); // effect sizes
    VectorXd y_tilde(N); // variable containing the adjusted residuals to exclude the effects of a given marker
    VectorXd epsilon(N); // variable containing the residuals
    VectorXd xsquared(M); //variable containing the squared norm of the X columns

    //sampler variables
    VectorXd sample(2*M+4+N); // varible containg a sambple of all variables in the model, M marker effects, M component assigned to markers, sigmaE, sigmaG, mu, iteration number and Explained variance
    std::vector<int> markerI;
    for (int i=0; i<M; ++i) {
      markerI.push_back(i);
    }


    int marker;
    double acum;

    priorPi[0]=0.5;



    priorPi.segment(1,(K-1))=priorPi[0]*cVa.segment(1,(K-1)).segment(1,(K-1)).array()/cVa.segment(1,(K-1)).segment(1,(K-1)).sum();
    y_tilde.setZero();
    cVa[0] = 0;
    cVa.segment(1,(K-1))=cva;

    cVaI[0] = 0;
    cVaI.segment(1,(K-1))=cVa.segment(1,(K-1)).cwiseInverse();

    beta.setZero();

    mu=0;

    sigmaG=beta_rng(1,1);

    pi=priorPi;

    components.setZero();
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    epsilon= Y.array() - mu - (X*beta).array();
    sigmaE=epsilon.squaredNorm()/N*0.5;
    xsquared=X.colwise().squaredNorm();
    for(int iteration=0; iteration < max_iterations; iteration++){

      if(iteration>0)
        if( iteration % (int)std::ceil(max_iterations/10) ==0)
          Rcpp::Rcout << "iteration: "<<iteration <<"\n";

      epsilon= epsilon.array()+mu;//  we substract previous value
      mu = norm_rng(epsilon.sum()/(double)N, sigmaE/(double)N); //update mu
      epsilon= epsilon.array()-mu;// we substract again now epsilon =Y-mu-X*beta


      std::random_shuffle(markerI.begin(), markerI.end());

      m0=0;
      v.setZero();
      for(int j=0; j < M; j++){

        marker= markerI[j];


        y_tilde= epsilon.array()+(X.col(marker)*beta(marker,0)).array();//now y_tilde= Y-mu-X*beta+ X.col(marker)*beta(marker)_old



        muk[0]=0.0;//muk for the zeroth component=0

       // std::cout<< muk;
        //we compute the denominator in the variance expression to save computations
        denom=xsquared(marker)+(sigmaE/sigmaG)*cVaI.segment(1,(K-1)).array();
        //we compute the dot product to save computations
        num=(X.col(marker).cwiseProduct(y_tilde)).sum();
        //muk for the other components is computed according to equaitons
        muk.segment(1,(K-1))= num/denom.array();



        logL= pi.array().log();//first component probabilities remain unchanged


        //update the log likelihood for each component
        logL.segment(1,(K-1))=logL.segment(1,(K-1)).array() - 0.5*((((sigmaG/sigmaE)*(xsquared(marker)))*cVa.segment(1,(K-1)).array() + 1).array().log()) + 0.5*( muk.segment(1,(K-1)).array()*num)/sigmaE;

        double p(beta_rng(1,1));//I use beta(1,1) because I cant be bothered in using the std::random or create my own uniform distribution, I will change it later


        if(((logL.segment(1,(K-1)).array()-logL[0]).abs().array() >700 ).any() ){
         acum=0;
        }else{
          acum=1.0/((logL.array()-logL[0]).exp().sum());
        }

        for(int k=0;k<K;k++){
          if(p<=acum){
            //if zeroth component
            if(k==0){
              beta(marker,0)=0;
            }else{
              beta(marker,0)=norm_rng(muk[k],sigmaE/denom[k-1]);
            }
            v[k]+=1.0;
            components[marker]=k;
            break;
          }else{
            //if too big or too small
            if(((logL.segment(1,(K-1)).array()-logL[k+1]).abs().array() >700 ).any() ){
              acum+=0;
            }
            else{
              acum+=1.0/((logL.array()-logL[k+1]).exp().sum());
            }
          }
        }
       epsilon=y_tilde-X.col(marker)*beta(marker,0);//now epsilon contains Y-mu - X*beta+ X.col(marker)*beta(marker)_old- X.col(marker)*beta(marker)_new

      }

      m0=M-v[0];
      sigmaG=inv_scaled_chisq_rng(v0G+m0,(beta.squaredNorm()*m0+v0G*s02G)/(v0G+m0));


      sigmaE=inv_scaled_chisq_rng(v0E+N,((epsilon).squaredNorm()+v0E*s02E)/(v0E+N));



      pi=dirichilet_rng(v.array() + 1.0);

      if(iteration >= burn_in)
      {
        if(iteration % thinning == 0){
          sample<< iteration,mu,beta,sigmaE,sigmaG,components,epsilon;
          q.enqueue(sample);
#ifdef _OPENMP

#else
          if(q.try_dequeue(sampleq))
            outFile<< sampleq.transpose().format(CommaInitFmt) << "\n";
#endif
           //here we have the consumer

        }

      }

    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    Rcpp::Rcout << "duration: "<<duration << "s\n";
    flag=1;
  }//end producer
#ifdef _OPENMP
#pragma omp section
      {

        while(!flag ){
          if(q.try_dequeue(sampleq))
            outFile<< sampleq.transpose().format(CommaInitFmt) << "\n";
        }
      }//end consumer
#endif
}
}

}


/*** R
M=200 #non zero marker effects
N=2000 #observations
MT=2000 #number of markers
B=matrix(rnorm(MT,sd=sqrt(0.5)),ncol=1) #marker effects, M marquers explain approx 50% of the variance
B[sample(1:MT,MT-M),1]=0 #we set MT-M marker effects to zero
#B=-abs(B)
X <- matrix(rnorm(MT*N), N, MT); var(X[,1])
G <- X%*%B; var(G)
Y=X%*%B+rnorm(N,sd=sqrt(0.4)); var(Y)
Y=Y
X=scale(X)
P=0.5 #prior probability of a marker being excluded from the model
sigma0=0.01# prior  variance of a zero mean gaussian prior over the mean mu NOT IMPLEMENTED
v0E=0.01 # degrees of freedom over the inv scaled chi square prior over residuals variance
s02E=0.01 #scale of the inv scaled chi square prior over residuals variance
v0G=0.01 #degrees of freedom of the inv bla bla prior over snp effects
s02G=0.01 # scale for the same
BayesRSamplerV2("./test2.csv",2, 5000, 2000,10,X, Y,sigma0,v0E,s02E,v0G,s02G,P)
library(readr)
tmp <- read_csv("./test2.csv")
#names(tmp)
#plot(tmp$sigmaG); mean(tmp$sigmaG)
plot(B,colMeans(tmp[,grep("beta",names(tmp))]))
lines(B,B)
abline(h=0)
var(G)
mean(tmp$EV)
1-var(G)
mean(tmp$sigmaE)
plot(tmp$mu)
plot(tmp$sigmaE)
plot(tmp$sigmaG)
hist(as.matrix(tmp[,grep("comp",names(tmp))])) #histogram of components, component 0= variance 0, component 1= variance 0.0001 and so long so forth
*/

