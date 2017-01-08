// [[Rcpp::depends(RcppArmadillo, bigmemory, BH)]]
#include <RcppArmadillo.h>
#include <bigmemory/MatrixAccessor.hpp>

using namespace Rcpp;


/******************************************************************************/

// [[Rcpp::export]]
double crossprodCpp(const NumericMatrix& mat, int j,
                    const NumericVector& r) {
  int j2 = j - 1;
  double sum = 0;
  for (int i = 0; i < r.size(); i++) {
    sum += mat(i, j2) * r[i];
  }
  return sum;
}

// [[Rcpp::export]]
NumericVector& updateR(NumericVector& r,
                       const NumericMatrix& mat, int j,
                       double diff) {
  int j2 = j - 1;
  for (int i = 0; i < r.size(); i++) {
    r[i] -= mat(i, j2) * diff;
  }
  return r;
}

/******************************************************************************/

// template <typename T>
//
// ListOf<NumericVector> univRegLin2(XPtr<BigMatrix> xpMat,
//                                   MatrixAccessor<T> macc,
//                                   arma::mat& covar,
//                                   arma::vec y,
//                                   const IntegerVector& rowInd) {
//   int n = rowInd.size();
//   int m = xpMat->ncol();
//   int K = covar.n_cols;
//   arma::mat tmp;
//   arma::vec betas, eps;
//   double* colX;
//   int i, j, k;
//
//   arma::mat XtX = covar.t() * covar;
//   arma::vec Xty = covar.t() * y;
//
//   // indices begin at 1 in R and 0 in C++
//   IntegerVector trains = rowInd - 1;
//
//   NumericVector res(m);
//   NumericVector var(m);
//
//   for (j = 0; j < m; j++) {
//     colX = covar.colptr(0);
//     for (i = 0; i < n; i++) {
//       colX[i] = macc[j][trains[i]];
//     }
//     for (k = 0; k < K; k++) {
//       XtX(0, k) = XtX(k, 0) = crossprod(colX, covar.colptr(k), n);
//     }
//     Xty(0) = crossprod(colX, y.memptr(), n);
//
//     tmp = inv(XtX);
//     betas = tmp * Xty;
//     eps = y - covar * betas;
//     res[j] = betas(0);
//     var[j] = tmp(0, 0) * sum(eps % eps) / (n - K);
//   }
//
//   return(List::create(_["estim"] = res,
//                       _["std.err"] = sqrt(var)));
// }

/******************************************************************************/

// // Dispatch function for univRegLin2
// // [[Rcpp::export]]
// ListOf<NumericVector> univRegLin2(SEXP pBigMat,
//                                   arma::mat& covar,
//                                   arma::vec y,
//                                   const IntegerVector& rowInd) {
//   XPtr<BigMatrix> xpMat(pBigMat);
//
//   switch(xpMat->matrix_type()) {
//   case 1:
//     return univRegLin2(xpMat, MatrixAccessor<char>(*xpMat),   covar, y, rowInd);
//   case 2:
//     return univRegLin2(xpMat, MatrixAccessor<short>(*xpMat),  covar, y, rowInd);
//   case 4:
//     return univRegLin2(xpMat, MatrixAccessor<int>(*xpMat),    covar, y, rowInd);
//   case 6:
//     return univRegLin2(xpMat, MatrixAccessor<float>(*xpMat),  covar, y, rowInd);
//   case 8:
//     return univRegLin2(xpMat, MatrixAccessor<double>(*xpMat), covar, y, rowInd);
//   default:
//     throw Rcpp::exception("unknown type detected for big.matrix object!");
//   }
// }

/******************************************************************************/