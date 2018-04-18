// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// BayesRSamplerV2
void BayesRSamplerV2(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double sigma0, double v0E, double s02E, double v0G, double s02G, Eigen::VectorXd cva);
RcppExport SEXP _BayesRRcpp_BayesRSamplerV2(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP sigma0SEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP v0GSEXP, SEXP s02GSEXP, SEXP cvaSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type sigma0(sigma0SEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type v0G(v0GSEXP);
    Rcpp::traits::input_parameter< double >::type s02G(s02GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type cva(cvaSEXP);
    BayesRSamplerV2(outputFile, seed, max_iterations, burn_in, thinning, X, Y, sigma0, v0E, s02E, v0G, s02G, cva);
    return R_NilValue;
END_RCPP
}
// BayesRSamplerV2Groups
void BayesRSamplerV2Groups(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double sigma0, double v0E, double s02E, double v0G, double s02G, Eigen::MatrixXd cva, int groups, Eigen::VectorXi gAssign);
RcppExport SEXP _BayesRRcpp_BayesRSamplerV2Groups(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP sigma0SEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP v0GSEXP, SEXP s02GSEXP, SEXP cvaSEXP, SEXP groupsSEXP, SEXP gAssignSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type sigma0(sigma0SEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type v0G(v0GSEXP);
    Rcpp::traits::input_parameter< double >::type s02G(s02GSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type cva(cvaSEXP);
    Rcpp::traits::input_parameter< int >::type groups(groupsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXi >::type gAssign(gAssignSEXP);
    BayesRSamplerV2Groups(outputFile, seed, max_iterations, burn_in, thinning, X, Y, sigma0, v0E, s02E, v0G, s02G, cva, groups, gAssign);
    return R_NilValue;
END_RCPP
}
// QRdecompose
Eigen::MatrixXd QRdecompose(std::string outputFile, Eigen::MatrixXd X);
RcppExport SEXP _BayesRRcpp_QRdecompose(SEXP outputFileSEXP, SEXP XSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    rcpp_result_gen = Rcpp::wrap(QRdecompose(outputFile, X));
    return rcpp_result_gen;
END_RCPP
}
// BayesRSamplerV2QR
void BayesRSamplerV2QR(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double sigma0, double v0E, double s02E, double v0G, double s02G, Eigen::VectorXd cva);
RcppExport SEXP _BayesRRcpp_BayesRSamplerV2QR(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP sigma0SEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP v0GSEXP, SEXP s02GSEXP, SEXP cvaSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type sigma0(sigma0SEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type v0G(v0GSEXP);
    Rcpp::traits::input_parameter< double >::type s02G(s02GSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type cva(cvaSEXP);
    BayesRSamplerV2QR(outputFile, seed, max_iterations, burn_in, thinning, X, Y, sigma0, v0E, s02E, v0G, s02G, cva);
    return R_NilValue;
END_RCPP
}
// BRV2Grstart
void BRV2Grstart(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, double mu, Eigen::MatrixXd beta, double sigmaE, Eigen::VectorXd sigmaGG, Eigen::MatrixXd X, Eigen::VectorXd epsilon, Eigen::VectorXd components, double sigma0, double v0E, double s02E, double v0G, double s02G, Eigen::MatrixXd cva, int groups, Eigen::VectorXi gAssign);
RcppExport SEXP _BayesRRcpp_BRV2Grstart(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP muSEXP, SEXP betaSEXP, SEXP sigmaESEXP, SEXP sigmaGGSEXP, SEXP XSEXP, SEXP epsilonSEXP, SEXP componentsSEXP, SEXP sigma0SEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP v0GSEXP, SEXP s02GSEXP, SEXP cvaSEXP, SEXP groupsSEXP, SEXP gAssignSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< double >::type mu(muSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< double >::type sigmaE(sigmaESEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type sigmaGG(sigmaGGSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type components(componentsSEXP);
    Rcpp::traits::input_parameter< double >::type sigma0(sigma0SEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type v0G(v0GSEXP);
    Rcpp::traits::input_parameter< double >::type s02G(s02GSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type cva(cvaSEXP);
    Rcpp::traits::input_parameter< int >::type groups(groupsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXi >::type gAssign(gAssignSEXP);
    BRV2Grstart(outputFile, seed, max_iterations, burn_in, thinning, mu, beta, sigmaE, sigmaGG, X, epsilon, components, sigma0, v0E, s02E, v0G, s02G, cva, groups, gAssign);
    return R_NilValue;
END_RCPP
}
// BRV2PPGroups
void BRV2PPGroups(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::VectorXd mu, Eigen::MatrixXd beta, Eigen::VectorXd sigmaE, Eigen::MatrixXd X, Eigen::VectorXd y);
RcppExport SEXP _BayesRRcpp_BRV2PPGroups(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP muSEXP, SEXP betaSEXP, SEXP sigmaESEXP, SEXP XSEXP, SEXP ySEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type mu(muSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type beta(betaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type sigmaE(sigmaESEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type y(ySEXP);
    BRV2PPGroups(outputFile, seed, max_iterations, burn_in, thinning, mu, beta, sigmaE, X, y);
    return R_NilValue;
END_RCPP
}
// dirichilet_rng
Eigen::VectorXd dirichilet_rng(Eigen::VectorXd alpha);
RcppExport SEXP _BayesRRcpp_dirichilet_rng(SEXP alphaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type alpha(alphaSEXP);
    rcpp_result_gen = Rcpp::wrap(dirichilet_rng(alpha));
    return rcpp_result_gen;
END_RCPP
}
// inv_gamma_rng
double inv_gamma_rng(double shape, double scale);
RcppExport SEXP _BayesRRcpp_inv_gamma_rng(SEXP shapeSEXP, SEXP scaleSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    rcpp_result_gen = Rcpp::wrap(inv_gamma_rng(shape, scale));
    return rcpp_result_gen;
END_RCPP
}
// gamma_rng
double gamma_rng(double shape, double scale);
RcppExport SEXP _BayesRRcpp_gamma_rng(SEXP shapeSEXP, SEXP scaleSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    rcpp_result_gen = Rcpp::wrap(gamma_rng(shape, scale));
    return rcpp_result_gen;
END_RCPP
}
// inv_gamma_rate_rng
double inv_gamma_rate_rng(double shape, double rate);
RcppExport SEXP _BayesRRcpp_inv_gamma_rate_rng(SEXP shapeSEXP, SEXP rateSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type rate(rateSEXP);
    rcpp_result_gen = Rcpp::wrap(inv_gamma_rate_rng(shape, rate));
    return rcpp_result_gen;
END_RCPP
}
// gamma_rate_rng
double gamma_rate_rng(double shape, double rate);
RcppExport SEXP _BayesRRcpp_gamma_rate_rng(SEXP shapeSEXP, SEXP rateSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type rate(rateSEXP);
    rcpp_result_gen = Rcpp::wrap(gamma_rate_rng(shape, rate));
    return rcpp_result_gen;
END_RCPP
}
// inv_scaled_chisq_rng
double inv_scaled_chisq_rng(double dof, double scale);
RcppExport SEXP _BayesRRcpp_inv_scaled_chisq_rng(SEXP dofSEXP, SEXP scaleSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type dof(dofSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    rcpp_result_gen = Rcpp::wrap(inv_scaled_chisq_rng(dof, scale));
    return rcpp_result_gen;
END_RCPP
}
// norm_rng
double norm_rng(double mean, double sigma2);
RcppExport SEXP _BayesRRcpp_norm_rng(SEXP meanSEXP, SEXP sigma2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type mean(meanSEXP);
    Rcpp::traits::input_parameter< double >::type sigma2(sigma2SEXP);
    rcpp_result_gen = Rcpp::wrap(norm_rng(mean, sigma2));
    return rcpp_result_gen;
END_RCPP
}
// component_probs
double component_probs(double b2, Eigen::VectorXd pi);
RcppExport SEXP _BayesRRcpp_component_probs(SEXP b2SEXP, SEXP piSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type b2(b2SEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type pi(piSEXP);
    rcpp_result_gen = Rcpp::wrap(component_probs(b2, pi));
    return rcpp_result_gen;
END_RCPP
}
// HorseshoeP
void HorseshoeP(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double A, double v0E, double s02E, double vL, double vT, int B);
RcppExport SEXP _BayesRRcpp_HorseshoeP(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP ASEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP vLSEXP, SEXP vTSEXP, SEXP BSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type A(ASEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type vL(vLSEXP);
    Rcpp::traits::input_parameter< double >::type vT(vTSEXP);
    Rcpp::traits::input_parameter< int >::type B(BSEXP);
    HorseshoeP(outputFile, seed, max_iterations, burn_in, thinning, X, Y, A, v0E, s02E, vL, vT, B);
    return R_NilValue;
END_RCPP
}
// HorseshoePlus
void HorseshoePlus(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double A, double v0E, double s02E, double vL, double vT, int B, double c2);
RcppExport SEXP _BayesRRcpp_HorseshoePlus(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP ASEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP vLSEXP, SEXP vTSEXP, SEXP BSEXP, SEXP c2SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type A(ASEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type vL(vLSEXP);
    Rcpp::traits::input_parameter< double >::type vT(vTSEXP);
    Rcpp::traits::input_parameter< int >::type B(BSEXP);
    Rcpp::traits::input_parameter< double >::type c2(c2SEXP);
    HorseshoePlus(outputFile, seed, max_iterations, burn_in, thinning, X, Y, A, v0E, s02E, vL, vT, B, c2);
    return R_NilValue;
END_RCPP
}
// HorseshoePlusv2
void HorseshoePlusv2(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double A, double v0E, double s02E, double vL, double vT, int B, double c2);
RcppExport SEXP _BayesRRcpp_HorseshoePlusv2(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP ASEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP vLSEXP, SEXP vTSEXP, SEXP BSEXP, SEXP c2SEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type A(ASEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type vL(vLSEXP);
    Rcpp::traits::input_parameter< double >::type vT(vTSEXP);
    Rcpp::traits::input_parameter< int >::type B(BSEXP);
    Rcpp::traits::input_parameter< double >::type c2(c2SEXP);
    HorseshoePlusv2(outputFile, seed, max_iterations, burn_in, thinning, X, Y, A, v0E, s02E, vL, vT, B, c2);
    return R_NilValue;
END_RCPP
}
// sumDiagonal
Eigen::MatrixXd sumDiagonal(Eigen::MatrixXd Ma, Eigen::VectorXd va);
RcppExport SEXP _BayesRRcpp_sumDiagonal(SEXP MaSEXP, SEXP vaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type Ma(MaSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type va(vaSEXP);
    rcpp_result_gen = Rcpp::wrap(sumDiagonal(Ma, va));
    return rcpp_result_gen;
END_RCPP
}
// mvn_rng
Eigen::MatrixXd mvn_rng(int nn, const Eigen::MatrixXd mean, const Eigen::MatrixXd covar);
RcppExport SEXP _BayesRRcpp_mvn_rng(SEXP nnSEXP, SEXP meanSEXP, SEXP covarSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type nn(nnSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd >::type mean(meanSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd >::type covar(covarSEXP);
    rcpp_result_gen = Rcpp::wrap(mvn_rng(nn, mean, covar));
    return rcpp_result_gen;
END_RCPP
}
// mvnCoef_rng
Eigen::MatrixXd mvnCoef_rng(int nn, const Eigen::MatrixXd xty, const Eigen::MatrixXd xtx, const Eigen::VectorXd d, double sigma);
RcppExport SEXP _BayesRRcpp_mvnCoef_rng(SEXP nnSEXP, SEXP xtySEXP, SEXP xtxSEXP, SEXP dSEXP, SEXP sigmaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type nn(nnSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd >::type xty(xtySEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd >::type xtx(xtxSEXP);
    Rcpp::traits::input_parameter< const Eigen::VectorXd >::type d(dSEXP);
    Rcpp::traits::input_parameter< double >::type sigma(sigmaSEXP);
    rcpp_result_gen = Rcpp::wrap(mvnCoef_rng(nn, xty, xtx, d, sigma));
    return rcpp_result_gen;
END_RCPP
}
// RHorseshoeP
void RHorseshoeP(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, double A, double v0E, double s02E, double vL, double vT, int B, double vC, double sC);
RcppExport SEXP _BayesRRcpp_RHorseshoeP(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP ASEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP vLSEXP, SEXP vTSEXP, SEXP BSEXP, SEXP vCSEXP, SEXP sCSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< double >::type A(ASEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type vL(vLSEXP);
    Rcpp::traits::input_parameter< double >::type vT(vTSEXP);
    Rcpp::traits::input_parameter< int >::type B(BSEXP);
    Rcpp::traits::input_parameter< double >::type vC(vCSEXP);
    Rcpp::traits::input_parameter< double >::type sC(sCSEXP);
    RHorseshoeP(outputFile, seed, max_iterations, burn_in, thinning, X, Y, A, v0E, s02E, vL, vT, B, vC, sC);
    return R_NilValue;
END_RCPP
}
// spikeSlab
void spikeSlab(std::string outputFile, int seed, int max_iterations, int burn_in, int thinning, Eigen::MatrixXd X, Eigen::VectorXd Y, Eigen::VectorXd cats, double v0E, double s02E, double v0L, double s02L, int B, double a, double b);
RcppExport SEXP _BayesRRcpp_spikeSlab(SEXP outputFileSEXP, SEXP seedSEXP, SEXP max_iterationsSEXP, SEXP burn_inSEXP, SEXP thinningSEXP, SEXP XSEXP, SEXP YSEXP, SEXP catsSEXP, SEXP v0ESEXP, SEXP s02ESEXP, SEXP v0LSEXP, SEXP s02LSEXP, SEXP BSEXP, SEXP aSEXP, SEXP bSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type outputFile(outputFileSEXP);
    Rcpp::traits::input_parameter< int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type max_iterations(max_iterationsSEXP);
    Rcpp::traits::input_parameter< int >::type burn_in(burn_inSEXP);
    Rcpp::traits::input_parameter< int >::type thinning(thinningSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type X(XSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type Y(YSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type cats(catsSEXP);
    Rcpp::traits::input_parameter< double >::type v0E(v0ESEXP);
    Rcpp::traits::input_parameter< double >::type s02E(s02ESEXP);
    Rcpp::traits::input_parameter< double >::type v0L(v0LSEXP);
    Rcpp::traits::input_parameter< double >::type s02L(s02LSEXP);
    Rcpp::traits::input_parameter< int >::type B(BSEXP);
    Rcpp::traits::input_parameter< double >::type a(aSEXP);
    Rcpp::traits::input_parameter< double >::type b(bSEXP);
    spikeSlab(outputFile, seed, max_iterations, burn_in, thinning, X, Y, cats, v0E, s02E, v0L, s02L, B, a, b);
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_BayesRRcpp_BayesRSamplerV2", (DL_FUNC) &_BayesRRcpp_BayesRSamplerV2, 13},
    {"_BayesRRcpp_BayesRSamplerV2Groups", (DL_FUNC) &_BayesRRcpp_BayesRSamplerV2Groups, 15},
    {"_BayesRRcpp_QRdecompose", (DL_FUNC) &_BayesRRcpp_QRdecompose, 2},
    {"_BayesRRcpp_BayesRSamplerV2QR", (DL_FUNC) &_BayesRRcpp_BayesRSamplerV2QR, 13},
    {"_BayesRRcpp_BRV2Grstart", (DL_FUNC) &_BayesRRcpp_BRV2Grstart, 20},
    {"_BayesRRcpp_BRV2PPGroups", (DL_FUNC) &_BayesRRcpp_BRV2PPGroups, 10},
    {"_BayesRRcpp_dirichilet_rng", (DL_FUNC) &_BayesRRcpp_dirichilet_rng, 1},
    {"_BayesRRcpp_inv_gamma_rng", (DL_FUNC) &_BayesRRcpp_inv_gamma_rng, 2},
    {"_BayesRRcpp_gamma_rng", (DL_FUNC) &_BayesRRcpp_gamma_rng, 2},
    {"_BayesRRcpp_inv_gamma_rate_rng", (DL_FUNC) &_BayesRRcpp_inv_gamma_rate_rng, 2},
    {"_BayesRRcpp_gamma_rate_rng", (DL_FUNC) &_BayesRRcpp_gamma_rate_rng, 2},
    {"_BayesRRcpp_inv_scaled_chisq_rng", (DL_FUNC) &_BayesRRcpp_inv_scaled_chisq_rng, 2},
    {"_BayesRRcpp_norm_rng", (DL_FUNC) &_BayesRRcpp_norm_rng, 2},
    {"_BayesRRcpp_component_probs", (DL_FUNC) &_BayesRRcpp_component_probs, 2},
    {"_BayesRRcpp_HorseshoeP", (DL_FUNC) &_BayesRRcpp_HorseshoeP, 13},
    {"_BayesRRcpp_HorseshoePlus", (DL_FUNC) &_BayesRRcpp_HorseshoePlus, 14},
    {"_BayesRRcpp_HorseshoePlusv2", (DL_FUNC) &_BayesRRcpp_HorseshoePlusv2, 14},
    {"_BayesRRcpp_sumDiagonal", (DL_FUNC) &_BayesRRcpp_sumDiagonal, 2},
    {"_BayesRRcpp_mvn_rng", (DL_FUNC) &_BayesRRcpp_mvn_rng, 3},
    {"_BayesRRcpp_mvnCoef_rng", (DL_FUNC) &_BayesRRcpp_mvnCoef_rng, 5},
    {"_BayesRRcpp_RHorseshoeP", (DL_FUNC) &_BayesRRcpp_RHorseshoeP, 15},
    {"_BayesRRcpp_spikeSlab", (DL_FUNC) &_BayesRRcpp_spikeSlab, 15},
    {NULL, NULL, 0}
};

RcppExport void R_init_BayesRRcpp(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
