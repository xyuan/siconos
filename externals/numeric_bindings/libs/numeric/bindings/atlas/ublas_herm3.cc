
// BLAS level 3
// hermitian matrix (kind of ;o)

#include <stddef.h>
#include <iostream>
#include <complex>
#include <boost/numeric/bindings/blas.hpp>
#include <boost/numeric/bindings/ublas/matrix.hpp>
#include <boost/numeric/bindings/ublas/hermitian.hpp>
#include "utils.h"

namespace ublas = boost::numeric::ublas;
namespace blas = boost::numeric::bindings::blas;
namespace bindings = boost::numeric::bindings;
namespace tag = boost::numeric::bindings::tag;

using std::cout;
using std::cin;
using std::endl; 

typedef double real_t; 
typedef std::complex<real_t> cmplx_t;

typedef ublas::matrix<cmplx_t, ublas::column_major> cm_t; 
typedef ublas::matrix<cmplx_t, ublas::row_major> rm_t; 

typedef ublas::hermitian_adaptor<cm_t, ublas::upper> uchemm_t; 
typedef ublas::hermitian_adaptor<cm_t, ublas::lower> lchemm_t; 
typedef ublas::hermitian_adaptor<rm_t, ublas::upper> urhemm_t; 
typedef ublas::hermitian_adaptor<rm_t, ublas::lower> lrhemm_t; 

int main (int argc, char **argv) {
  size_t n = 0;
  if (argc > 1) {
    n = atoi(argv [1]);
  }
  
  cout << endl; 

  if (n <= 0) {
    cout << "n -> ";
    cin >> n;
  }
  cout << endl; 

  cm_t uc (n, n);
  uchemm_t ucs (uc); 
  cm_t lc (n, n); 
  lchemm_t lcs (lc); 
  rm_t ur (n, n); 
  urhemm_t urs (ur); 
  rm_t lr (n, n); 
  lrhemm_t lrs (lr); 

  init_symm (ucs, 'u'); 
  init_symm (lcs, 'l'); 
  init_symm (urs, 'u'); 
  init_symm (lrs, 'l'); 

  print_m (ucs, "a == ucs");
  cout << endl; 
  print_m_data (ucs, "ucs");
  cout << endl; 

  print_m (lcs, "a == lcs");
  cout << endl; 
  print_m_data (lcs, "lcs");
  cout << endl; 

  print_m (urs, "a == urs");
  cout << endl; 
  print_m_data (urs, "urs");
  cout << endl; 

  print_m (lrs, "a == lrs");
  cout << endl; 
  print_m_data (lrs, "lrs");
  cout << endl; 

  cm_t cbl (n, n+1); 
  rm_t rbl (n, n+1); 
  cm_t ccl (n, n+1); 
  rm_t rcl (n, n+1); 

  init_m (cbl, rws1());
  init_m (rbl, rws1());

  print_m (cbl, "b == cb");
  cout << endl; 
  print_m (rbl, "b == rb");
  cout << endl; 

  blas::hemm ( tag::left(), 1.0, ucs, cbl, 0.0, ccl); 
  print_m (ccl, "c = a b");
  cout << endl; 

  blas::hemm ( tag::left(), 1.0, lcs, cbl, 0.0, ccl);  
  print_m (ccl, "c = a b");
  cout << endl; 

  blas::hemm ( tag::left(), 1.0, urs, rbl, 0.0, rcl); 
  print_m (rcl, "c = a b");
  cout << endl; 

  blas::hemm ( tag::left(), 1.0, lrs, rbl, 0.0, rcl); 
  print_m (rcl, "c = a b");
  cout << endl; 
  
  cm_t cbr (n+1, n); 
  rm_t rbr (n+1, n); 
  cm_t ccr (n+1, n); 
  rm_t rcr (n+1, n); 

  init_m (cbr, cls1());
  init_m (rbr, cls1());
  
  print_m (cbr, "b == cb");
  cout << endl; 
  print_m (rbr, "b == rb");
  cout << endl; 

  blas::hemm ( tag::right(), 1.0, ucs, cbr, 0.0, ccr); 
  print_m (ccr, "c = b a");
  cout << endl; 

  blas::hemm ( tag::right(), 1.0, lcs, cbr, 0.0, ccr);  
  print_m (ccr, "c = b a");
  cout << endl; 

  blas::hemm ( tag::right(), 1.0, urs, rbr, 0.0, rcr); 
  print_m (rcr, "c = b a");
  cout << endl; 

  blas::hemm ( tag::right(), 1.0, lrs, rbr, 0.0, rcr); 
  print_m (rcr, "c = b a");
  cout << endl; 

  cout << endl; 

}
