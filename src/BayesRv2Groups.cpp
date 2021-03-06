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
using Eigen::Matrix;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::SparseVector;
using Eigen::LLT;
using Eigen::Lower;
using Eigen::Map;
using Eigen::Upper;
typedef Map<MatrixXd> MapMatd;

inline void initialize_file( std::ofstream& outFile,int M,int N,int groups, int F){
  bool queueFull;
  queueFull=0;


  outFile<< "iteration,"<<"mu,";
  for(unsigned int i = 0; i < M; ++i){
    outFile << "beta[" << (i+1) << "],";

  }
  outFile<<"sigmaE,";
  for(unsigned int i = 0; i < M; ++i){
    outFile << "comp[" << (i+1) << "],";
  }
  for(unsigned int i = 0; i < groups; ++i){
    outFile << "sigmaG[" << (i+1) << "],";
  }
  unsigned int i;
  for(i = 0; i < (N-1);i++){
    outFile << "epsilon[" << (i+1) << "],";
  }

  outFile << "epsilon[" << (i+1) << "],";

  for(i = 0; i < F; i ++){
    outFile << "alpha[" << (i+1) << "],";
  }
  outFile << "sigmaF";
  outFile<<"\n";
}


//' BayesRR sampler
//' @param outputFile The file in which the samples aftare burnin will be stored
//' @param seed random seed
//' @param max_iterations total of number of samples taken.
//' @param burn_in integer leq than max_iterations, number of samples used for burn in, after which, al samples will  be stored in the outputFile
//' @param thinning thinning regime, not implemented
//' @param X matrix of snp markers, or covariates of interest
//' @param Y vector of response variates, must have the same number of rows as X
//' @param sigma0 variance of the zero-centered normal prior over the intercept
//' @param v0E degrees of  freedom of the prior inverse scaled chi-squared distribution over residues variance
//' @param s02E scale parameter of the prior inverse scaled chi-squared distribution over residues variance
//' @param v0G degrees of freedom of the prior inverse scaled chi-squared distribution over genetic effects variance
//' @param s02G scale parameter of the prior inverse scaled chi-squared distribution over genetic effects variance
//' @param cva Matrix of mixture variances for groups, rows must be the same as number of groups, columns the same as number of mixtures.
//' @param groups number of groups
//' @param gAssign Vector of the same size as the number of columns of X, containing group assignments for each column(starting with group 0).
//' @param fixed Matrxi with same rows as X and Y , contains the fixed effects, those whose prior is always different than zero
// [[Rcpp::export]]
void BayesRSamplerV2Groups(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y,double sigma0, double v0E, double s02E, double v0G, double s02G,Eigen::MatrixXd cva,int groups, Eigen::VectorXi gAssign, Eigen::MatrixXd fixed) {
  int flag;
  moodycamel::ConcurrentQueue<Eigen::VectorXd> q;
  flag=0;
  int N(Y.size());
  int M(X.cols());
  int F(fixed.cols());
  VectorXd components(M);
  std::ofstream outFile;

  outFile.open(outputFile);
  int K(cva.cols()+1);
  VectorXd sampleq(2*M+3+groups+ N + F+ 1);
  IOFormat CommaInitFmt(StreamPrecision, DontAlignCols, ", ", ", ", "", "", "", "");
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

  initialize_file(outFile,M,N,groups,F);
 // Eigen::initParallel();
//  Eigen::setNbThreads(10);
  //double sum_beta_sqr;
#ifdef _OPENMP
  omp_set_num_threads(2);
#endif
#pragma omp parallel num_threads(2) shared(flag,q,M,N,F)
{
#pragma omp sections
{
  //producer
  {

    //mean and residual variables
    double mu; // mean or intercept
    double sigmaG; //genetic variance
    double sigmaE; // residuals variance
    VectorXd sigmaGG(groups);
    double sigmaF; // fixed effects variance

    //component variables
    MatrixXd priorPi(groups,K); // prior probabilities for each component
    MatrixXd pi(groups,K); // mixture probabilities
    VectorXd cVa(K); //component-specific variance
    VectorXd logL(K); // log likelihood of component
    VectorXd muk(K); // mean of k-th component marker effect size
    VectorXd denom(K-1); // temporal variable for computing the inflation of the effect variance for a given non-zero componnet
    int m0; // total num ber of markes in model
    MatrixXd v(groups,K); //variable storing the component assignment
    VectorXd cVaI(K);// inverse of the component variances

    //linear model variables
    MatrixXd beta(M,1); // effect sizes
    VectorXd alpha(F); // fixed effects
    VectorXd y_tilde(N); // variable containing the adjusted residuals to exclude the effects of a given marker
    VectorXd epsilon(N); // variable containing the residuals

    //sampler variables
    VectorXd sample(2*M+3+groups+ N + F+ 1); // varible containg a sambple of all variables in the model, M marker effects, M component assigned to markers, sigmaE, sigmaG, mu, iteration number and Explained variance
    std::vector<int> markerI;
    for (int i=0; i<M; ++i) {
      markerI.push_back(i);
    }
    std::vector<int> fixedI;
    for(int j=0; j<F; ++j){
      fixedI.push_back(j);
    }
    VectorXd xsquared(M);
    double num;

    int marker;
    double acum;
    VectorXd betaAcum(groups);



        for(int i=0; i < groups; i++){
        	priorPi.row(i)(0)=0.5;
        	for(int k=1;k<K;k++){
        	priorPi.row(i)(k)=0.5/K;
        	}
        }
    y_tilde.setZero();
    //cVa[0] = 0;
    //cVa.segment(1,(K-1))=cva;

    //cVaI[0] = 0;
    //cVaI.segment(1,(K-1))=cVa.segment(1,(K-1)).cwiseInverse();
    //beta=beta.setRandom();

    //beta=(beta.array().abs() > 1e-6  ).select(beta, MatrixXd::Zero(M,1));
    beta.setZero();
    alpha.setZero();

    //mu=norm_rng(0,1);
    mu=0;


    betaAcum.setZero();
    // sigmaG=(1*cVa).sum()/M;
    for(int i=0; i<groups;i++)
      sigmaGG[i]=beta_rng(1,1);

    sigmaF= (double)R::runif(0,1);

    pi=priorPi;

    components.setZero();
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    epsilon= Y.array() - mu;
    sigmaE=epsilon.squaredNorm()/N*0.5;
    xsquared=X.colwise().squaredNorm();
    for(int iteration=0; iteration < max_iterations; iteration++){

      if(iteration>0)
        if( iteration % (int)std::ceil(max_iterations/10) ==0)
          Rcpp::Rcout << "iteration: "<<iteration <<"\n";

        epsilon= epsilon.array()+mu;//  we substract previous value
        mu = norm_rng(epsilon.sum()/(double)N, sigmaE/(double)N); //update mu
        epsilon= epsilon.array()-mu;// we substract again now epsilon =Y-mu-X*beta

        std::random_shuffle(fixedI.begin(), fixedI.end());
        for(int cur_fix=0; cur_fix < F; cur_fix++){
          int cur = fixedI[cur_fix];
          auto cur_alpha = alpha[cur];
          y_tilde= epsilon.array()+(fixed.col(cur)*cur_alpha).array();
          auto denom_f = (N-1) + (sigmaE/sigmaF);
          auto num_f = (fixed.col(cur).cwiseProduct(y_tilde)).sum();
          alpha[cur] = norm_rng(num_f/denom_f,sigmaE/denom_f);
          epsilon = y_tilde - fixed.col(cur)*alpha[cur];
        }

        std::random_shuffle(markerI.begin(), markerI.end());

        m0=0;
        v.setZero();
        betaAcum.setZero();
        for(int j=0; j < M; j++){

          marker= markerI[j];
          sigmaG=sigmaGG[gAssign(marker)];

          cVa[0]=0;
          cVaI[0]=0;
          cVa.segment(1,(K-1))=cva.row(gAssign(marker));
          cVaI.segment(1,(K-1))=(cVa.segment(1,(K-1))).cwiseInverse();


          y_tilde= epsilon.array()+(X.col(marker)*beta(marker,0)).array();//now y_tilde= Y-mu-X*beta+ X.col(marker)*beta(marker)_old




          muk[0]=0.0;//muk for the zeroth component=0

          // Rcpp::Rcout<< muk;
          //we compute the denominator in the variance expression to save computations
          denom=xsquared(marker)+(sigmaE/sigmaG)*cVaI.segment(1,(K-1)).array();
          //muk for the other components is computed according to equaitons
          num=(X.col(marker).cwiseProduct(y_tilde)).sum();
          muk.segment(1,(K-1))= num/denom.array();



          logL= pi.row(gAssign(marker)).array().log();//first component probabilities remain unchanged


          // Here we reproduce the fortran code
          logL.segment(1,(K-1))=logL.segment(1,(K-1)).array() - 0.5*((((sigmaG/sigmaE)*(xsquared(marker))*cVa.segment(1,(K-1)).array() + 1).array().log()))+
            0.5*( muk.segment(1,(K-1)).array()*num)/sigmaE;

          double p((double)R::runif( 0.0, 1.0 ));//

          if(((logL.segment(1,(K-1)).array()-logL[0]).abs().array() >700 ).any() ){
            acum=0;
          }else{
            acum=1.0/((logL.array()-logL[0]).exp().sum());
          }

          for(int k=0;k<K;k++){
            if(p<=acum){
              if(k==0){
                beta(marker,0)=0;
              }else{
                beta(marker,0)=norm_rng(muk[k],sigmaE/denom[k-1]);
                betaAcum(gAssign(marker))+= pow(beta(marker,0),2);
                // beta(marker,0)=norm_rng(rhs/denom[k-1],sigmaE/denom[k-1]);
              }
              v.row(gAssign(marker))(k)+=1.0;
              components[marker]=k;
              break;
            }else{
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


        sigmaF = inv_scaled_chisq_rng(v0E+F,(alpha.squaredNorm()+v0E*s02E)/(v0E+F));
        // Rcpp::Rcout << sigmaF;

        sigmaE=inv_scaled_chisq_rng(v0E+N,((epsilon).squaredNorm()+v0E*s02E)/(v0E+N));


        for(int i=0; i<groups; i++){
          m0=v.row(i).sum()-v.row(i)(0);
          sigmaGG[i]=inv_scaled_chisq_rng(v0G+m0,(betaAcum(i)*m0+v0G*s02G)/(v0G+m0));
          pi.row(i)=dirichilet_rng(v.row(i).array() + 1.0);

        }

        if(iteration >= burn_in)
        {
          if(iteration % thinning == 0){
            sample<< iteration,mu,beta,sigmaE,components,sigmaGG,epsilon,alpha,sigmaF;

            q.enqueue(sample);
            //here we have the consumer
#ifdef _OPENMP

#else
            if(q.try_dequeue(sampleq)){

              outFile<< sampleq.transpose().format(CommaInitFmt) << "\n";
            }
#endif
          }

        }

    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    Rcpp::Rcout << "duration: "<<duration << "s\n";
    flag=1;
  }//end producer
  //consumer
    #ifdef _OPENMP
    #pragma omp section
    {


      while(!flag ){
        if(q.try_dequeue(sampleq)){
          outFile<< sampleq.transpose().format(CommaInitFmt) << "\n";
        }
      }//while



    }// endconsumer
    #endif
}

}

}

