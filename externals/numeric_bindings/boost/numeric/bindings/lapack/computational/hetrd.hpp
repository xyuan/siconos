//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HETRD_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_HETRD_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_complex.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/is_real.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/traits/detail/utils.hpp>
#include <boost/numeric/bindings/uplo_tag.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for hetrd is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hetrd( const UpLo, const fortran_int_t n, float* a,
        const fortran_int_t lda, float* d, float* e, float* tau, float* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_SSYTRD( &lapack_option< UpLo >::value, &n, a, &lda, d, e, tau,
            work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hetrd( const UpLo, const fortran_int_t n, double* a,
        const fortran_int_t lda, double* d, double* e, double* tau,
        double* work, const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_DSYTRD( &lapack_option< UpLo >::value, &n, a, &lda, d, e, tau,
            work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hetrd( const UpLo, const fortran_int_t n,
        std::complex<float>* a, const fortran_int_t lda, float* d, float* e,
        std::complex<float>* tau, std::complex<float>* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_CHETRD( &lapack_option< UpLo >::value, &n, a, &lda, d, e, tau,
            work, &lwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
template< typename UpLo >
inline std::ptrdiff_t hetrd( const UpLo, const fortran_int_t n,
        std::complex<double>* a, const fortran_int_t lda, double* d,
        double* e, std::complex<double>* tau, std::complex<double>* work,
        const fortran_int_t lwork ) {
    fortran_int_t info(0);
    LAPACK_ZHETRD( &lapack_option< UpLo >::value, &n, a, &lda, d, e, tau,
            work, &lwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to hetrd.
//
template< typename Value, typename Enable = void >
struct hetrd_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct hetrd_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU, typename WORK >
    static std::ptrdiff_t invoke( MatrixA& a, VectorD& d, VectorE& e,
            VectorTAU& tau, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorD >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorTAU >::value) );
        BOOST_ASSERT( bindings::size(d) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(tau) >= bindings::size_column(a)-1 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work());
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::hetrd( uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(tau),
                bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU >
    static std::ptrdiff_t invoke( MatrixA& a, VectorD& d, VectorE& e,
            VectorTAU& tau, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        bindings::detail::array< real_type > tmp_work( min_size_work() );
        return invoke( a, d, e, tau, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU >
    static std::ptrdiff_t invoke( MatrixA& a, VectorD& d, VectorE& e,
            VectorTAU& tau, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        real_type opt_size_work;
        detail::hetrd( uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(tau), &opt_size_work, -1 );
        bindings::detail::array< real_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( a, d, e, tau, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work() {
        return 1;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct hetrd_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU, typename WORK >
    static std::ptrdiff_t invoke( MatrixA& a, VectorD& d, VectorE& e,
            VectorTAU& tau, detail::workspace1< WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorD >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorE >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorD >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorE >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorTAU >::value) );
        BOOST_ASSERT( bindings::size(d) >= bindings::size_column(a) );
        BOOST_ASSERT( bindings::size(tau) >= bindings::size_column(a)-1 );
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work());
        BOOST_ASSERT( bindings::size_column(a) >= 0 );
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(a)) );
        return detail::hetrd( uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(tau),
                bindings::begin_value(work.select(value_type())),
                bindings::size(work.select(value_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU >
    static std::ptrdiff_t invoke( MatrixA& a, VectorD& d, VectorE& e,
            VectorTAU& tau, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        bindings::detail::array< value_type > tmp_work( min_size_work() );
        return invoke( a, d, e, tau, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorD, typename VectorE,
            typename VectorTAU >
    static std::ptrdiff_t invoke( MatrixA& a, VectorD& d, VectorE& e,
            VectorTAU& tau, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        typedef typename result_of::uplo_tag< MatrixA >::type uplo;
        value_type opt_size_work;
        detail::hetrd( uplo(), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(d), bindings::begin_value(e),
                bindings::begin_value(tau), &opt_size_work, -1 );
        bindings::detail::array< value_type > tmp_work(
                traits::detail::to_int( opt_size_work ) );
        return invoke( a, d, e, tau, workspace( tmp_work ) );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work() {
        return 1;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the hetrd_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for hetrd. Its overload differs for
// * User-defined workspace
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
hetrd( MatrixA& a, VectorD& d, VectorE& e, VectorTAU& tau,
        Workspace work ) {
    return hetrd_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, d, e, tau, work );
}

//
// Overloaded function for hetrd. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorD, typename VectorE,
        typename VectorTAU >
inline typename boost::disable_if< detail::is_workspace< VectorTAU >,
        std::ptrdiff_t >::type
hetrd( MatrixA& a, VectorD& d, VectorE& e, VectorTAU& tau ) {
    return hetrd_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( a, d, e, tau, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif
