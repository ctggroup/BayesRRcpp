#include <omp.h>
// [[Rcpp::plugins(openmp)]]
#include <Rcpp.h>
#include <RcppEigen.h>
#include <Eigen/Core>
#include <random>
#include "distributions.h"
#include "MultVar.h"


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

inline MatrixXd AtA(const MapMatd& A) {
  int n(A.cols());
  return MatrixXd(n,n).setZero().selfadjointView<Lower>()
                      .rankUpdate(A.adjoint());
}


// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//
template<typename Scalar>
struct categorical_functor
{
  categorical_functor(const Eigen::VectorXd& pi,const Scalar& sigmaG) : m_b(sigmaG),m_c(pi){}

  const Scalar operator()(const Scalar& x) const{ return component_probs(x,m_c,m_b); }
  Scalar  m_b;
  Eigen::VectorXd m_c;
};
template<typename Scalar>
struct categorical_init
{
  categorical_init(const Eigen::VectorXd& pi) : m_c(pi){}

  const Scalar operator()(const Scalar& x) const{ return categorical(m_c); }
  Eigen::VectorXd m_c;
};
// [[Rcpp::export]]
void BayesRSampler(int seed, int max_iterations, int burn_in,int thinning,Eigen::MatrixXd X, Eigen::VectorXd Y,double v0,double s02, int B) {
 int flag;
  std::stringstream buffer;
  flag=0;
  #pragma omp parallel num_threads(2) shared(flag,buffer)
{
    #pragma omp sections
    {

{
  int N(Y.size());
  int M(X.cols());
  double mu;
  double sigmaG;
  double sigmaE;
  int m0;
  std::random_device rd;
  std::mt19937 gen(rd());
  int b(M/B);
  // values near the mean are the most likely
  // standard deviation affects the dispersion of generated values from the mean
  std::normal_distribution<> norm(0,1);
  VectorXd priorPi(4);
  VectorXd pi(4);
  VectorXd cVa(4);
  VectorXd invsqrtcVa(4);
  VectorXd residues;
  VectorXd components(M);
  MatrixXd beta(M,1);
  MatrixXd xtX(M,M);
  MatrixXd xtY(M,1);
  MatrixXd xS(M,1);
  MatrixXd sum_beta_sqr(1,max_iterations);
  Map<MatrixXd> xM(X.data(),N,M);
  VectorXd v(4);
  MatrixXd mu_b(N,1);
  VectorXd ones(N);
  VectorXd mu_f(N);

  int beginSegment;
  int endSegment;
  //std::ofstream file("test.txt");

  //Eigen::setNbThreads(100);

  /////end of declarations//////

  ones.setOnes();
  M=X.cols();
  N=Y.rows();
  std::cout<<" computing XtX\n";
  xtX=AtA(xM);
  priorPi.setOnes();
  priorPi*=0.25;
  cVa[0] = 0;
  cVa[1] = 0.0001;
  cVa[2] = 0.001;
  cVa[3] = 0.01;
  invsqrtcVa[0]=0;
  invsqrtcVa.segment(1,3)=-1*(cVa.segment(1,3)).array().square().cwiseInverse();

  beta.setRandom();
  mu=norm(gen);
  sigmaE=std::abs(norm_rng(0,1));
  sigmaG=std::abs(norm_rng(0,1));
  pi=dirichilet_rng(priorPi);
  components.unaryExpr(categorical_init<double>(priorPi));
  // residues=Y-mu*ones;


  std::cout<<"block size " << b <<"\n";
  Eigen::initParallel();
  Eigen::setNbThreads(10);
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

  residues= X*beta;

  for(int iteration=0; iteration < max_iterations; iteration++){
    std::cout << "iteration: "<<iteration <<"\n";
    mu = norm_rng((1/(double)N)*residues.sum(), sigmaE/(double)N);
    components= beta.unaryExpr(categorical_functor<double>(pi,sigmaG));
    mu_f.setZero();
    for(int block=0; block < M;block+=b){
      beginSegment=block;
      endSegment=(block+b-1)>=(M-1)?(M-1):(block+b-1);
      if(beginSegment==0){
        mu_b=residues-((X.block(0,0,N,b)*beta.block(0,0,b,1)));

      }
      else{

        mu_b+=(-X.block(0,beginSegment,N,b)*beta.block(beginSegment,0,b,1));
      }


      beta.block(beginSegment,0,b,1)= mvnCoef_rng(1,
                 X.block(0,beginSegment,N,b).transpose()*(Y-mu*ones-mu_b-mu_f),
                 xtX.block(beginSegment,beginSegment,b,b),
                 sigmaG*components.segment(beginSegment,b));
      beta.block(beginSegment,0,b,1) = (components.block(beginSegment,0,b,1).array() > 1e-10 ).select(beta.block(beginSegment,0,b,1), MatrixXd::Zero(b,1));
      mu_f+=X.block(0,beginSegment,N,b)*beta.block(beginSegment,0,b,1);
    }

    residues=mu_f;
    m0=(components.array()>0).count();
    sigmaG=inv_scaled_chisq_rng(v0+m0,((beta.array()).pow(2).sum()+v0*s02)/(v0+m0));
    sigmaE=inv_scaled_chisq_rng(v0+N,((((Y-residues).array()-mu).array().pow(2)).sum()+v0*s02)/(v0+N));
    v(0)=priorPi[0]+(components.array()==cVa[0]).count();
    v(1)=priorPi[1]+(components.array()==cVa[1]).count();
    v(2)=priorPi[2]+(components.array()==cVa[2]).count();
    v(3)=priorPi[3]+(components.array()==cVa[3]).count();
    pi=dirichilet_rng(v);

    sum_beta_sqr(iteration)= ((beta.sparseView().cwiseProduct(beta).cwiseProduct(components.cwiseInverse())).sum()+v0*s02)/(m0+v0);
    if(iteration >= burn_in)
      buffer << iteration <<"\t"<< mu <<"\t"<< beta.col(1).transpose()<<"\t"<< sigmaG <<"\t"<<sigmaE <<"\t"<< components.transpose()<<  "\n";
    //buff<<"sigma\n" ;

  }

  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
  std::cout << "duration: "<<duration << "s\n";
  flag=1;
}
#pragma omp section
{
  std::ofstream outFile;
  outFile.open("test.txt");
  while(!flag){
    #pragma omp critical
    outFile<< buffer.str();
  }
  outFile.close();
  buffer.str(std::string());
}

    }
}

}
// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation.
//

/*** R
M=10000
N=20000
B=matrix(rnorm(M,sd=sqrt(0.5/M)),ncol=1)
  X <- matrix(rnorm(M*N), N, M); var(X[,1])
    G <- X%*%B; var(G)
      Y=X%*%B+rnorm(N,sd=sqrt(1-var(G))); var(Y)
       BayesRSampler(1, 200, 100,1,X, Y,0.01,0.01,1000)
#        names(tmp)
 #       plot(tmp$sigmaG); mean(tmp$sigmaG)
#        plot(B,colMeans(tmp$beta[900:1000,]))
 #       lines(B,B)
#        abline(h=0)
 #        var(G)
 #       mean(tmp$sum_beta_sqr[900:1000])
  #       1-var(G)
   #      mean(tmp$sigmaE[900:1000])

  */

