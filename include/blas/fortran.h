// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#ifndef BLAS_FORTRAN_H
#define BLAS_FORTRAN_H

#include "blas/defines.h"
#include "blas/mangling.h"

// Accelerate uses std::complex
#define BLAS_COMPLEX_CPP
#include "blas/config.h"

#ifdef ACCELERATE_NEW_LAPACK
    // New macOS Accelerate (>= macOS 13.3) requires their prototypes
    // with extra mangling, and does not include strlen.
    #if defined( BLAS_ILP64 ) && ! defined( ACCELERATE_ILP64 )
        #define ACCELERATE_ILP64
    #endif
    #include <Accelerate/Accelerate.h>
#else
    // It seems all current Fortran compilers put strlen at end.
    // Some historical compilers put strlen after the str argument
    // or make the str argument into a struct.
    #ifndef BLAS_FORTRAN_STRLEN_END
    #define BLAS_FORTRAN_STRLEN_END
    #endif

    // Set flag to define prototypes below (i.e., not Accelerate's prototypes).
    #define BLAS_PROTO
#endif

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// Level 1 BLAS - Fortran prototypes

//------------------------------------------------------------------------------
#define BLAS_saxpy BLAS_FORTRAN_NAME( saxpy, SAXPY )
#define BLAS_daxpy BLAS_FORTRAN_NAME( daxpy, DAXPY )
#define BLAS_caxpy BLAS_FORTRAN_NAME( caxpy, CAXPY )
#define BLAS_zaxpy BLAS_FORTRAN_NAME( zaxpy, ZAXPY )

#ifdef BLAS_PROTO
void BLAS_saxpy(
    blas_int const *n,
    float const *alpha,
    float const *x, blas_int const *incx,
    float       *y, blas_int const *incy );

void BLAS_daxpy(
    blas_int const *n,
    double const *alpha,
    double const *x, blas_int const *incx,
    double       *y, blas_int const *incy );

void BLAS_caxpy(
    blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float       *y, blas_int const *incy );

void BLAS_zaxpy(
    blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double       *y, blas_int const *incy );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_sscal BLAS_FORTRAN_NAME( sscal, SSCAL )
#define BLAS_dscal BLAS_FORTRAN_NAME( dscal, DSCAL )
#define BLAS_cscal BLAS_FORTRAN_NAME( cscal, CSCAL )
#define BLAS_zscal BLAS_FORTRAN_NAME( zscal, ZSCAL )

#ifdef BLAS_PROTO
void BLAS_sscal(
    blas_int const *n,
    float const *alpha,
    float       *x, blas_int const *incx );

void BLAS_dscal(
    blas_int const *n,
    double const *alpha,
    double       *x, blas_int const *incx );

void BLAS_cscal(
    blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float       *x, blas_int const *incx );

void BLAS_zscal(
    blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double       *x, blas_int const *incx );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_scopy BLAS_FORTRAN_NAME( scopy, SCOPY )
#define BLAS_dcopy BLAS_FORTRAN_NAME( dcopy, DCOPY )
#define BLAS_ccopy BLAS_FORTRAN_NAME( ccopy, CCOPY )
#define BLAS_zcopy BLAS_FORTRAN_NAME( zcopy, ZCOPY )

#ifdef BLAS_PROTO
void BLAS_scopy(
    blas_int const *n,
    float const *x, blas_int const *incx,
    float       *y, blas_int const *incy );

void BLAS_dcopy(
    blas_int const *n,
    double const *x, blas_int const *incx,
    double       *y, blas_int const *incy );

void BLAS_ccopy(
    blas_int const *n,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float       *y, blas_int const *incy );

void BLAS_zcopy(
    blas_int const *n,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double       *y, blas_int const *incy );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_sswap BLAS_FORTRAN_NAME( sswap, SSWAP )
#define BLAS_dswap BLAS_FORTRAN_NAME( dswap, DSWAP )
#define BLAS_cswap BLAS_FORTRAN_NAME( cswap, CSWAP )
#define BLAS_zswap BLAS_FORTRAN_NAME( zswap, ZSWAP )

#ifdef BLAS_PROTO
void BLAS_sswap(
    blas_int const *n,
    float *x, blas_int const *incx,
    float *y, blas_int const *incy );

void BLAS_dswap(
    blas_int const *n,
    double *x, blas_int const *incx,
    double *y, blas_int const *incy );

void BLAS_cswap(
    blas_int const *n,
    blas_complex_float *x, blas_int const *incx,
    blas_complex_float *y, blas_int const *incy );

void BLAS_zswap(
    blas_int const *n,
    blas_complex_double *x, blas_int const *incx,
    blas_complex_double *y, blas_int const *incy );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_sdot BLAS_FORTRAN_NAME( sdot, SDOT )
#define BLAS_ddot BLAS_FORTRAN_NAME( ddot, DDOT )

#ifdef BLAS_PROTO
blas_float_return BLAS_sdot(
    blas_int const *n,
    float const *x, blas_int const *incx,
    float const *y, blas_int const *incy );

double BLAS_ddot(
    blas_int const *n,
    double const *x, blas_int const *incx,
    double const *y, blas_int const *incy );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_cdotc BLAS_FORTRAN_NAME( cdotc, CDOTC )
#define BLAS_zdotc BLAS_FORTRAN_NAME( zdotc, ZDOTC )
#define BLAS_cdotu BLAS_FORTRAN_NAME( cdotu, CDOTU )
#define BLAS_zdotu BLAS_FORTRAN_NAME( zdotu, ZDOTU )

#ifdef BLAS_PROTO
// For Fortran functions returning complex values,
// define BLAS_COMPLEX_RETURN_ARGUMENT if result is a hidden first argument (Intel icc),
// else the default is to return complex values (GNU gcc).
#ifdef BLAS_COMPLEX_RETURN_ARGUMENT

    void BLAS_cdotc(
        blas_complex_float *result,
        blas_int const *n,
        blas_complex_float const *x, blas_int const *incx,
        blas_complex_float const *y, blas_int const *incy );

    void BLAS_zdotc(
        blas_complex_double *result,
        blas_int const *n,
        blas_complex_double const *x, blas_int const *incx,
        blas_complex_double const *y, blas_int const *incy );

    void BLAS_cdotu(
        blas_complex_float *result,
        blas_int const *n,
        blas_complex_float const *x, blas_int const *incx,
        blas_complex_float const *y, blas_int const *incy );

    void BLAS_zdotu(
        blas_complex_double *result,
        blas_int const *n,
        blas_complex_double const *x, blas_int const *incx,
        blas_complex_double const *y, blas_int const *incy );

#else // ! defined(BLAS_COMPLEX_RETURN_ARGUMENT)

    blas_complex_float BLAS_cdotc(
        blas_int const *n,
        blas_complex_float const *x, blas_int const *incx,
        blas_complex_float const *y, blas_int const *incy );

    blas_complex_double BLAS_zdotc(
        blas_int const *n,
        blas_complex_double const *x, blas_int const *incx,
        blas_complex_double const *y, blas_int const *incy );

    blas_complex_float BLAS_cdotu(
        blas_int const *n,
        blas_complex_float const *x, blas_int const *incx,
        blas_complex_float const *y, blas_int const *incy );

    blas_complex_double BLAS_zdotu(
        blas_int const *n,
        blas_complex_double const *x, blas_int const *incx,
        blas_complex_double const *y, blas_int const *incy );

#endif // ! defined(BLAS_COMPLEX_RETURN)
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_snrm2 BLAS_FORTRAN_NAME( snrm2, SNRM2 )
#define BLAS_dnrm2 BLAS_FORTRAN_NAME( dnrm2, DNRM2 )
#define BLAS_scnrm2 BLAS_FORTRAN_NAME( scnrm2, SCNRM2 )
#define BLAS_dznrm2 BLAS_FORTRAN_NAME( dznrm2, DZNRM2 )

#ifdef BLAS_PROTO
blas_float_return BLAS_snrm2(
    blas_int const *n,
    float const *x, blas_int const *incx );

double BLAS_dnrm2(
    blas_int const *n,
    double const *x, blas_int const *incx );

blas_float_return BLAS_scnrm2(
    blas_int const *n,
    blas_complex_float const *x, blas_int const *incx );

double BLAS_dznrm2(
    blas_int const *n,
    blas_complex_double const *x, blas_int const *incx );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_sasum BLAS_FORTRAN_NAME( sasum, SASUM )
#define BLAS_dasum BLAS_FORTRAN_NAME( dasum, DASUM )
#define BLAS_scasum BLAS_FORTRAN_NAME( scasum, SCASUM )
#define BLAS_dzasum BLAS_FORTRAN_NAME( dzasum, DZASUM )

#ifdef BLAS_PROTO
blas_float_return BLAS_sasum(
    blas_int const *n,
    float const *x, blas_int const *incx );

double BLAS_dasum(
    blas_int const *n,
    double const *x, blas_int const *incx );

blas_float_return BLAS_scasum(
    blas_int const *n,
    blas_complex_float const *x, blas_int const *incx );

double BLAS_dzasum(
    blas_int const *n,
    blas_complex_double const *x, blas_int const *incx );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_isamax BLAS_FORTRAN_NAME( isamax, ISAMAX )
#define BLAS_idamax BLAS_FORTRAN_NAME( idamax, IDAMAX )
#define BLAS_icamax BLAS_FORTRAN_NAME( icamax, ICAMAX )
#define BLAS_izamax BLAS_FORTRAN_NAME( izamax, IZAMAX )

#ifdef BLAS_PROTO
blas_int BLAS_isamax(
    blas_int const *n,
    float const *x, blas_int const *incx );

blas_int BLAS_idamax(
    blas_int const *n,
    double const *x, blas_int const *incx );

blas_int BLAS_icamax(
    blas_int const *n,
    blas_complex_float const *x, blas_int const *incx );

blas_int BLAS_izamax(
    blas_int const *n,
    blas_complex_double const *x, blas_int const *incx );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
// c is real
// oddly, b is const for crotg, zrotg
#define BLAS_srotg BLAS_FORTRAN_NAME( srotg, SROTG )
#define BLAS_drotg BLAS_FORTRAN_NAME( drotg, DROTG )
#define BLAS_crotg BLAS_FORTRAN_NAME( crotg, CROTG )
#define BLAS_zrotg BLAS_FORTRAN_NAME( zrotg, ZROTG )

#ifdef BLAS_PROTO
void BLAS_srotg(
    float *a,
    float *b,
    float *c,
    float *s );

void BLAS_drotg(
    double *a,
    double *b,
    double *c,
    double *s );

void BLAS_crotg(
    blas_complex_float *a,
    blas_complex_float const *b,
    float *c,
    blas_complex_float *s );

void BLAS_zrotg(
    blas_complex_double *a,
    blas_complex_double const *b,
    double *c,
    blas_complex_double *s );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
// c is real
#define BLAS_srot BLAS_FORTRAN_NAME( srot, SROT )
#define BLAS_drot BLAS_FORTRAN_NAME( drot, DROT )
#define BLAS_csrot BLAS_FORTRAN_NAME( csrot, CSROT )
#define BLAS_zdrot BLAS_FORTRAN_NAME( zdrot, ZDROT )
#define BLAS_crot BLAS_FORTRAN_NAME( crot, CROT )
#define BLAS_zrot BLAS_FORTRAN_NAME( zrot, ZROT )

#ifdef BLAS_PROTO
void BLAS_srot(
    blas_int const *n,
    float *x, blas_int const *incx,
    float *y, blas_int const *incy,
    float const *c,
    float const *s );

void BLAS_drot(
    blas_int const *n,
    double *x, blas_int const *incx,
    double *y, blas_int const *incy,
    double const *c,
    double const *s );

void BLAS_csrot(
    blas_int const *n,
    blas_complex_float *x, blas_int const *incx,
    blas_complex_float *y, blas_int const *incy,
    float const *c,
    float const *s );

void BLAS_zdrot(
    blas_int const *n,
    blas_complex_double *x, blas_int const *incx,
    blas_complex_double *y, blas_int const *incy,
    double const *c,
    double const *s );

void BLAS_crot(
    blas_int const *n,
    blas_complex_float *x, blas_int const *incx,
    blas_complex_float *y, blas_int const *incy,
    float const *c,
    blas_complex_float const *s );

void BLAS_zrot(
    blas_int const *n,
    blas_complex_double *x, blas_int const *incx,
    blas_complex_double *y, blas_int const *incy,
    double const *c,
    blas_complex_double const *s );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_srotmg BLAS_FORTRAN_NAME( srotmg, SROTMG )
#define BLAS_drotmg BLAS_FORTRAN_NAME( drotmg, DROTMG )

#ifdef BLAS_PROTO
void BLAS_srotmg(
    float *d1,
    float *d2,
    float *x1,
    float const *y1,
    float *param );

void BLAS_drotmg(
    double *d1,
    double *d2,
    double *x1,
    double const *y1,
    double *param );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_srotm BLAS_FORTRAN_NAME( srotm, SROTM )
#define BLAS_drotm BLAS_FORTRAN_NAME( drotm, DROTM )

#ifdef BLAS_PROTO
void BLAS_srotm(
    blas_int const *n,
    float *x, blas_int const *incx,
    float *y, blas_int const *incy,
    float const *param );

void BLAS_drotm(
    blas_int const *n,
    double *x, blas_int const *incx,
    double *y, blas_int const *incy,
    double const *param );
#endif // BLAS_PROTO

// =============================================================================
// Level 2 BLAS - Fortran prototypes

//------------------------------------------------------------------------------
#define BLAS_sgemv_base BLAS_FORTRAN_NAME( sgemv, SGEMV )
#define BLAS_dgemv_base BLAS_FORTRAN_NAME( dgemv, DGEMV )
#define BLAS_cgemv_base BLAS_FORTRAN_NAME( cgemv, CGEMV )
#define BLAS_zgemv_base BLAS_FORTRAN_NAME( zgemv, ZGEMV )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_sgemv( ... ) BLAS_sgemv_base( __VA_ARGS__, 1 )
    #define BLAS_dgemv( ... ) BLAS_dgemv_base( __VA_ARGS__, 1 )
    #define BLAS_cgemv( ... ) BLAS_cgemv_base( __VA_ARGS__, 1 )
    #define BLAS_zgemv( ... ) BLAS_zgemv_base( __VA_ARGS__, 1 )
#else
    #define BLAS_sgemv( ... ) BLAS_sgemv_base( __VA_ARGS__ )
    #define BLAS_dgemv( ... ) BLAS_dgemv_base( __VA_ARGS__ )
    #define BLAS_cgemv( ... ) BLAS_cgemv_base( __VA_ARGS__ )
    #define BLAS_zgemv( ... ) BLAS_zgemv_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_sgemv_base(
    char const *trans,
    blas_int const *m, blas_int const *n,
    float const *alpha,
    float const *A, blas_int const *lda,
    float const *x, blas_int const *incx,
    float const *beta,
    float       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t trans_len
    #endif
    );

void BLAS_dgemv_base(
    char const *trans,
    blas_int const *m, blas_int const *n,
    double const *alpha,
    double const *A, blas_int const *lda,
    double const *x, blas_int const *incx,
    double const *beta,
    double       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t trans_len
    #endif
    );

void BLAS_cgemv_base(
    char const *trans,
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float const *beta,
    blas_complex_float       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t trans_len
    #endif
    );

void BLAS_zgemv_base(
    char const *trans,
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double const *beta,
    blas_complex_double       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t trans_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_sger BLAS_FORTRAN_NAME( sger, SGER )
#define BLAS_dger BLAS_FORTRAN_NAME( dger, DGER )

#ifdef BLAS_PROTO
void BLAS_sger(
    blas_int const *m, blas_int const *n,
    float const *alpha,
    float const *x, blas_int const *incx,
    float const *y, blas_int const *incy,
    float       *A, blas_int const *lda );

void BLAS_dger(
    blas_int const *m, blas_int const *n,
    double const *alpha,
    double const *x, blas_int const *incx,
    double const *y, blas_int const *incy,
    double       *A, blas_int const *lda );
#endif // BLAS_PROTO

//----------------------------------------
#define BLAS_cgerc BLAS_FORTRAN_NAME( cgerc, CGERC )
#define BLAS_zgerc BLAS_FORTRAN_NAME( zgerc, ZGERC )

#ifdef BLAS_PROTO
void BLAS_cgerc(
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float const *y, blas_int const *incy,
    blas_complex_float       *A, blas_int const *lda );

void BLAS_zgerc(
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double const *y, blas_int const *incy,
    blas_complex_double       *A, blas_int const *lda );
#endif // BLAS_PROTO

//----------------------------------------
#define BLAS_cgeru BLAS_FORTRAN_NAME( cgeru, CGERU )
#define BLAS_zgeru BLAS_FORTRAN_NAME( zgeru, ZGERU )

#ifdef BLAS_PROTO
void BLAS_cgeru(
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float const *y, blas_int const *incy,
    blas_complex_float       *A, blas_int const *lda );

void BLAS_zgeru(
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double const *y, blas_int const *incy,
    blas_complex_double       *A, blas_int const *lda );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_ssymv_base BLAS_FORTRAN_NAME( ssymv, SSYMV )
#define BLAS_dsymv_base BLAS_FORTRAN_NAME( dsymv, DSYMV )
// #define BLAS_csymv_base BLAS_FORTRAN_NAME( csymv, CSYMV )
// #define BLAS_zsymv_base BLAS_FORTRAN_NAME( zsymv, ZSYMV )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_ssymv( ... ) BLAS_ssymv_base( __VA_ARGS__, 1 )
    #define BLAS_dsymv( ... ) BLAS_dsymv_base( __VA_ARGS__, 1 )
    //#define BLAS_csymv( ... ) BLAS_csymv_base( __VA_ARGS__, 1 )
    //#define BLAS_zsymv( ... ) BLAS_zsymv_base( __VA_ARGS__, 1 )
#else
    #define BLAS_ssymv( ... ) BLAS_ssymv_base( __VA_ARGS__ )
    #define BLAS_dsymv( ... ) BLAS_dsymv_base( __VA_ARGS__ )
    //#define BLAS_csymv( ... ) BLAS_csymv_base( __VA_ARGS__ )
    //#define BLAS_zsymv( ... ) BLAS_zsymv_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_ssymv_base(
    char const *uplo,
    blas_int const *n,
    float const *alpha,
    float const *A, blas_int const *lda,
    float const *x, blas_int const *incx,
    float const *beta,
    float       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

void BLAS_dsymv_base(
    char const *uplo,
    blas_int const *n,
    double const *alpha,
    double const *A, blas_int const *lda,
    double const *x, blas_int const *incx,
    double const *beta,
    double       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

// [cz]symv moved to LAPACK++ since they are provided by LAPACK.
// void BLAS_csymv_base(
//     char const *uplo,
//     blas_int const *n,
//     blas_complex_float const *alpha,
//     blas_complex_float const *A, blas_int const *lda,
//     blas_complex_float const *x, blas_int const *incx,
//     blas_complex_float const *beta,
//     blas_complex_float       *y, blas_int const *incy
//     #ifdef BLAS_FORTRAN_STRLEN_END
//     , size_t uplo_len
//     #endif
//     );
//
// void BLAS_zsymv_base(
//     char const *uplo,
//     blas_int const *n,
//     blas_complex_double const *alpha,
//     blas_complex_double const *A, blas_int const *lda,
//     blas_complex_double const *x, blas_int const *incx,
//     blas_complex_double const *beta,
//     blas_complex_double       *y, blas_int const *incy
//     #ifdef BLAS_FORTRAN_STRLEN_END
//     , size_t uplo_len
//     #endif
//     );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_chemv_base BLAS_FORTRAN_NAME( chemv, CHEMV )
#define BLAS_zhemv_base BLAS_FORTRAN_NAME( zhemv, ZHEMV )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_chemv( ... ) BLAS_chemv_base( __VA_ARGS__, 1 )
    #define BLAS_zhemv( ... ) BLAS_zhemv_base( __VA_ARGS__, 1 )
#else
    #define BLAS_chemv( ... ) BLAS_chemv_base( __VA_ARGS__ )
    #define BLAS_zhemv( ... ) BLAS_zhemv_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_chemv_base(
    char const *uplo,
    blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float const *beta,
    blas_complex_float       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

void BLAS_zhemv_base(
    char const *uplo,
    blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double const *beta,
    blas_complex_double       *y, blas_int const *incy
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_ssyr_base BLAS_FORTRAN_NAME( ssyr, SSYR )
#define BLAS_dsyr_base BLAS_FORTRAN_NAME( dsyr, DSYR )
//#define BLAS_zsyr_base BLAS_FORTRAN_NAME( zsyr, ZSYR )
//#define BLAS_csyr_base BLAS_FORTRAN_NAME( csyr, CSYR )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_ssyr( ... ) BLAS_ssyr_base( __VA_ARGS__, 1 )
    #define BLAS_dsyr( ... ) BLAS_dsyr_base( __VA_ARGS__, 1 )
    //#define BLAS_csyr( ... ) BLAS_csyr_base( __VA_ARGS__, 1 )
    //#define BLAS_zsyr( ... ) BLAS_zsyr_base( __VA_ARGS__, 1 )
#else
    #define BLAS_ssyr( ... ) BLAS_ssyr_base( __VA_ARGS__ )
    #define BLAS_dsyr( ... ) BLAS_dsyr_base( __VA_ARGS__ )
    //#define BLAS_csyr( ... ) BLAS_csyr_base( __VA_ARGS__ )
    //#define BLAS_zsyr( ... ) BLAS_zsyr_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_ssyr_base(
    char const *uplo,
    blas_int const *n,
    float const *alpha,
    float const *x, blas_int const *incx,
    float       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

void BLAS_dsyr_base(
    char const *uplo,
    blas_int const *n,
    double const *alpha,
    double const *x, blas_int const *incx,
    double       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

// conflicts with current prototype in lapacke.h
//void BLAS_FORTRAN_NAME( csyr, CSYR )(
//    char const *uplo,
//    blas_int const *n,
//    blas_complex_float const *alpha,
//    blas_complex_float const *x, blas_int const *incx,
//    blas_complex_float       *A, blas_int const *lda
//     #ifdef BLAS_FORTRAN_STRLEN_END
//     , size_t uplo_len
//     #endif
//     );
//
//void BLAS_zsyr_base(
//    char const *uplo,
//    blas_int const *n,
//    blas_complex_double const *alpha,
//    blas_complex_double const *x, blas_int const *incx,
//    blas_complex_double       *A, blas_int const *lda
//     #ifdef BLAS_FORTRAN_STRLEN_END
//     , size_t uplo_len
//     #endif
//     );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_cher_base BLAS_FORTRAN_NAME( cher, CHER )
#define BLAS_zher_base BLAS_FORTRAN_NAME( zher, ZHER )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_cher( ... ) BLAS_cher_base( __VA_ARGS__, 1 )
    #define BLAS_zher( ... ) BLAS_zher_base( __VA_ARGS__, 1 )
#else
    #define BLAS_cher( ... ) BLAS_cher_base( __VA_ARGS__ )
    #define BLAS_zher( ... ) BLAS_zher_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
// alpha is real
void BLAS_cher_base(
    char const *uplo,
    blas_int const *n,
    float const *alpha,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

void BLAS_zher_base(
    char const *uplo,
    blas_int const *n,
    double const *alpha,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_ssyr2_base BLAS_FORTRAN_NAME( ssyr2, SSYR2 )
#define BLAS_dsyr2_base BLAS_FORTRAN_NAME( dsyr2, DSYR2 )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_ssyr2( ... ) BLAS_ssyr2_base( __VA_ARGS__, 1 )
    #define BLAS_dsyr2( ... ) BLAS_dsyr2_base( __VA_ARGS__, 1 )
#else
    #define BLAS_ssyr2( ... ) BLAS_ssyr2_base( __VA_ARGS__ )
    #define BLAS_dsyr2( ... ) BLAS_dsyr2_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
// [cz]syr2 not available in standard BLAS or LAPACK; use [cz]syr2k with k=1.
void BLAS_ssyr2_base(
    char const *uplo,
    blas_int const *n,
    float const *alpha,
    float const *x, blas_int const *incx,
    float const *y, blas_int const *incy,
    float       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

void BLAS_dsyr2_base(
    char const *uplo,
    blas_int const *n,
    double const *alpha,
    double const *x, blas_int const *incx,
    double const *y, blas_int const *incy,
    double       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_cher2_base BLAS_FORTRAN_NAME( cher2, CHER2 )
#define BLAS_zher2_base BLAS_FORTRAN_NAME( zher2, ZHER2 )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_cher2( ... ) BLAS_cher2_base( __VA_ARGS__, 1 )
    #define BLAS_zher2( ... ) BLAS_zher2_base( __VA_ARGS__, 1 )
#else
    #define BLAS_cher2( ... ) BLAS_cher2_base( __VA_ARGS__ )
    #define BLAS_zher2( ... ) BLAS_zher2_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_cher2_base(
    char const *uplo,
    blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *x, blas_int const *incx,
    blas_complex_float const *y, blas_int const *incy,
    blas_complex_float       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );

void BLAS_zher2_base(
    char const *uplo,
    blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *x, blas_int const *incx,
    blas_complex_double const *y, blas_int const *incy,
    blas_complex_double       *A, blas_int const *lda
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_strmv_base BLAS_FORTRAN_NAME( strmv, STRMV )
#define BLAS_dtrmv_base BLAS_FORTRAN_NAME( dtrmv, DTRMV )
#define BLAS_ctrmv_base BLAS_FORTRAN_NAME( ctrmv, CTRMV )
#define BLAS_ztrmv_base BLAS_FORTRAN_NAME( ztrmv, ZTRMV )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_strmv( ... ) BLAS_strmv_base( __VA_ARGS__, 1, 1, 1 )
    #define BLAS_dtrmv( ... ) BLAS_dtrmv_base( __VA_ARGS__, 1, 1, 1 )
    #define BLAS_ctrmv( ... ) BLAS_ctrmv_base( __VA_ARGS__, 1, 1, 1 )
    #define BLAS_ztrmv( ... ) BLAS_ztrmv_base( __VA_ARGS__, 1, 1, 1 )
#else
    #define BLAS_strmv( ... ) BLAS_strmv_base( __VA_ARGS__ )
    #define BLAS_dtrmv( ... ) BLAS_dtrmv_base( __VA_ARGS__ )
    #define BLAS_ctrmv( ... ) BLAS_ctrmv_base( __VA_ARGS__ )
    #define BLAS_ztrmv( ... ) BLAS_ztrmv_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_strmv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    float const *A, blas_int const *lda,
    float       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_dtrmv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    double const *A, blas_int const *lda,
    double       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ctrmv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ztrmv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_strsv_base BLAS_FORTRAN_NAME( strsv, STRSV )
#define BLAS_dtrsv_base BLAS_FORTRAN_NAME( dtrsv, DTRSV )
#define BLAS_ctrsv_base BLAS_FORTRAN_NAME( ctrsv, CTRSV )
#define BLAS_ztrsv_base BLAS_FORTRAN_NAME( ztrsv, ZTRSV )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_strsv( ... ) BLAS_strsv_base( __VA_ARGS__, 1, 1, 1 )
    #define BLAS_dtrsv( ... ) BLAS_dtrsv_base( __VA_ARGS__, 1, 1, 1 )
    #define BLAS_ctrsv( ... ) BLAS_ctrsv_base( __VA_ARGS__, 1, 1, 1 )
    #define BLAS_ztrsv( ... ) BLAS_ztrsv_base( __VA_ARGS__, 1, 1, 1 )
#else
    #define BLAS_strsv( ... ) BLAS_strsv_base( __VA_ARGS__ )
    #define BLAS_dtrsv( ... ) BLAS_dtrsv_base( __VA_ARGS__ )
    #define BLAS_ctrsv( ... ) BLAS_ctrsv_base( __VA_ARGS__ )
    #define BLAS_ztrsv( ... ) BLAS_ztrsv_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_strsv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    float const *A, blas_int const *lda,
    float       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_dtrsv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    double const *A, blas_int const *lda,
    double       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ctrsv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ztrsv_base(
    char const *uplo, char const *trans, char const *diag,
    blas_int const *n,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double       *x, blas_int const *incx
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );
#endif // BLAS_PROTO

// =============================================================================
// Level 3 BLAS - Fortran prototypes

//------------------------------------------------------------------------------
#define BLAS_sgemm_base BLAS_FORTRAN_NAME( sgemm, SGEMM )
#define BLAS_dgemm_base BLAS_FORTRAN_NAME( dgemm, DGEMM )
#define BLAS_cgemm_base BLAS_FORTRAN_NAME( cgemm, CGEMM )
#define BLAS_zgemm_base BLAS_FORTRAN_NAME( zgemm, ZGEMM )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_sgemm( ... ) BLAS_sgemm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_dgemm( ... ) BLAS_dgemm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_cgemm( ... ) BLAS_cgemm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zgemm( ... ) BLAS_zgemm_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_sgemm( ... ) BLAS_sgemm_base( __VA_ARGS__ )
    #define BLAS_dgemm( ... ) BLAS_dgemm_base( __VA_ARGS__ )
    #define BLAS_cgemm( ... ) BLAS_cgemm_base( __VA_ARGS__ )
    #define BLAS_zgemm( ... ) BLAS_zgemm_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_sgemm_base(
    char const *transA, char const *transB,
    blas_int const *m, blas_int const *n, blas_int const *k,
    float const *alpha,
    float const *A, blas_int const *lda,
    float const *B, blas_int const *ldb,
    float const *beta,
    float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t transA_len, size_t transB_len
    #endif
    );

void BLAS_dgemm_base(
    char const *transA, char const *transB,
    blas_int const *m, blas_int const *n, blas_int const *k,
    double const *alpha,
    double const *A, blas_int const *lda,
    double const *B, blas_int const *ldb,
    double const *beta,
    double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t transA_len, size_t transB_len
    #endif
    );

void BLAS_cgemm_base(
    char const *transA, char const *transB,
    blas_int const *m, blas_int const *n, blas_int const *k,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *B, blas_int const *ldb,
    blas_complex_float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t transA_len, size_t transB_len
    #endif
    );

void BLAS_zgemm_base(
    char const *transA, char const *transB,
    blas_int const *m, blas_int const *n, blas_int const *k,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *B, blas_int const *ldb,
    blas_complex_double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t transA_len, size_t transB_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_ssymm_base BLAS_FORTRAN_NAME( ssymm, SSYMM )
#define BLAS_dsymm_base BLAS_FORTRAN_NAME( dsymm, DSYMM )
#define BLAS_csymm_base BLAS_FORTRAN_NAME( csymm, CSYMM )
#define BLAS_zsymm_base BLAS_FORTRAN_NAME( zsymm, ZSYMM )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_ssymm( ... ) BLAS_ssymm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_dsymm( ... ) BLAS_dsymm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_csymm( ... ) BLAS_csymm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zsymm( ... ) BLAS_zsymm_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_ssymm( ... ) BLAS_ssymm_base( __VA_ARGS__ )
    #define BLAS_dsymm( ... ) BLAS_dsymm_base( __VA_ARGS__ )
    #define BLAS_csymm( ... ) BLAS_csymm_base( __VA_ARGS__ )
    #define BLAS_zsymm( ... ) BLAS_zsymm_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_ssymm_base(
    char const *side, char const *uplo,
    blas_int const *m, blas_int const *n,
    float const *alpha,
    float const *A, blas_int const *lda,
    float const *B, blas_int const *ldb,
    float const *beta,
    float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len
    #endif
    );

void BLAS_dsymm_base(
    char const *side, char const *uplo,
    blas_int const *m, blas_int const *n,
    double const *alpha,
    double const *A, blas_int const *lda,
    double const *B, blas_int const *ldb,
    double const *beta,
    double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len
    #endif
    );

void BLAS_csymm_base(
    char const *side, char const *uplo,
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *B, blas_int const *ldb,
    blas_complex_float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len
    #endif
    );

void BLAS_zsymm_base(
    char const *side, char const *uplo,
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *B, blas_int const *ldb,
    blas_complex_double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_chemm_base BLAS_FORTRAN_NAME( chemm, CHEMM )
#define BLAS_zhemm_base BLAS_FORTRAN_NAME( zhemm, ZHEMM )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_chemm( ... ) BLAS_chemm_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zhemm( ... ) BLAS_zhemm_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_chemm( ... ) BLAS_chemm_base( __VA_ARGS__ )
    #define BLAS_zhemm( ... ) BLAS_zhemm_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_chemm_base(
    char const *side, char const *uplo,
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *B, blas_int const *ldb,
    blas_complex_float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len
    #endif
    );

void BLAS_zhemm_base(
    char const *side, char const *uplo,
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *B, blas_int const *ldb,
    blas_complex_double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_ssyrk_base BLAS_FORTRAN_NAME( ssyrk, SSYRK )
#define BLAS_dsyrk_base BLAS_FORTRAN_NAME( dsyrk, DSYRK )
#define BLAS_csyrk_base BLAS_FORTRAN_NAME( csyrk, CSYRK )
#define BLAS_zsyrk_base BLAS_FORTRAN_NAME( zsyrk, ZSYRK )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_ssyrk( ... ) BLAS_ssyrk_base( __VA_ARGS__, 1, 1 )
    #define BLAS_dsyrk( ... ) BLAS_dsyrk_base( __VA_ARGS__, 1, 1 )
    #define BLAS_csyrk( ... ) BLAS_csyrk_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zsyrk( ... ) BLAS_zsyrk_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_ssyrk( ... ) BLAS_ssyrk_base( __VA_ARGS__ )
    #define BLAS_dsyrk( ... ) BLAS_dsyrk_base( __VA_ARGS__ )
    #define BLAS_csyrk( ... ) BLAS_csyrk_base( __VA_ARGS__ )
    #define BLAS_zsyrk( ... ) BLAS_zsyrk_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_ssyrk_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    float const *alpha,
    float const *A, blas_int const *lda,
    float const *beta,
    float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_dsyrk_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    double const *alpha,
    double const *A, blas_int const *lda,
    double const *beta,
    double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_csyrk_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_zsyrk_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_cherk_base BLAS_FORTRAN_NAME( cherk, CHERK )
#define BLAS_zherk_base BLAS_FORTRAN_NAME( zherk, ZHERK )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_cherk( ... ) BLAS_cherk_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zherk( ... ) BLAS_zherk_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_cherk( ... ) BLAS_cherk_base( __VA_ARGS__ )
    #define BLAS_zherk( ... ) BLAS_zherk_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
// alpha and beta are real
void BLAS_cherk_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_zherk_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_ssyr2k_base BLAS_FORTRAN_NAME( ssyr2k, SSYR2K )
#define BLAS_dsyr2k_base BLAS_FORTRAN_NAME( dsyr2k, DSYR2K )
#define BLAS_csyr2k_base BLAS_FORTRAN_NAME( csyr2k, CSYR2K )
#define BLAS_zsyr2k_base BLAS_FORTRAN_NAME( zsyr2k, ZSYR2K )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_ssyr2k( ... ) BLAS_ssyr2k_base( __VA_ARGS__, 1, 1 )
    #define BLAS_dsyr2k( ... ) BLAS_dsyr2k_base( __VA_ARGS__, 1, 1 )
    #define BLAS_csyr2k( ... ) BLAS_csyr2k_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zsyr2k( ... ) BLAS_zsyr2k_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_ssyr2k( ... ) BLAS_ssyr2k_base( __VA_ARGS__ )
    #define BLAS_dsyr2k( ... ) BLAS_dsyr2k_base( __VA_ARGS__ )
    #define BLAS_csyr2k( ... ) BLAS_csyr2k_base( __VA_ARGS__ )
    #define BLAS_zsyr2k( ... ) BLAS_zsyr2k_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_ssyr2k_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    float const *alpha,
    float const *A, blas_int const *lda,
    float const *B, blas_int const *ldb,
    float const *beta,
    float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_dsyr2k_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    double const *alpha,
    double const *A, blas_int const *lda,
    double const *B, blas_int const *ldb,
    double const *beta,
    double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_csyr2k_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *B, blas_int const *ldb,
    blas_complex_float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_zsyr2k_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *B, blas_int const *ldb,
    blas_complex_double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_cher2k_base BLAS_FORTRAN_NAME( cher2k, CHER2K )
#define BLAS_zher2k_base BLAS_FORTRAN_NAME( zher2k, ZHER2K )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_cher2k( ... ) BLAS_cher2k_base( __VA_ARGS__, 1, 1 )
    #define BLAS_zher2k( ... ) BLAS_zher2k_base( __VA_ARGS__, 1, 1 )
#else
    #define BLAS_cher2k( ... ) BLAS_cher2k_base( __VA_ARGS__ )
    #define BLAS_zher2k( ... ) BLAS_zher2k_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
// beta is real
void BLAS_cher2k_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float const *B, blas_int const *ldb,
    float const *beta,
    blas_complex_float       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );

void BLAS_zher2k_base(
    char const *uplo, char const *transA,
    blas_int const *n, blas_int const *k,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double const *B, blas_int const *ldb,
    double const *beta,
    blas_complex_double       *C, blas_int const *ldc
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t uplo_len, size_t transA_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_strmm_base BLAS_FORTRAN_NAME( strmm, STRMM )
#define BLAS_dtrmm_base BLAS_FORTRAN_NAME( dtrmm, DTRMM )
#define BLAS_ctrmm_base BLAS_FORTRAN_NAME( ctrmm, CTRMM )
#define BLAS_ztrmm_base BLAS_FORTRAN_NAME( ztrmm, ZTRMM )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_strmm( ... ) BLAS_strmm_base( __VA_ARGS__, 1, 1, 1, 1 )
    #define BLAS_dtrmm( ... ) BLAS_dtrmm_base( __VA_ARGS__, 1, 1, 1, 1 )
    #define BLAS_ctrmm( ... ) BLAS_ctrmm_base( __VA_ARGS__, 1, 1, 1, 1 )
    #define BLAS_ztrmm( ... ) BLAS_ztrmm_base( __VA_ARGS__, 1, 1, 1, 1 )
#else
    #define BLAS_strmm( ... ) BLAS_strmm_base( __VA_ARGS__ )
    #define BLAS_dtrmm( ... ) BLAS_dtrmm_base( __VA_ARGS__ )
    #define BLAS_ctrmm( ... ) BLAS_ctrmm_base( __VA_ARGS__ )
    #define BLAS_ztrmm( ... ) BLAS_ztrmm_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_strmm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    float const *alpha,
    float const *A, blas_int const *lda,
    float       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_dtrmm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    double const *alpha,
    double const *A, blas_int const *lda,
    double       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ctrmm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ztrmm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );
#endif // BLAS_PROTO

//------------------------------------------------------------------------------
#define BLAS_strsm_base BLAS_FORTRAN_NAME( strsm, STRSM )
#define BLAS_dtrsm_base BLAS_FORTRAN_NAME( dtrsm, DTRSM )
#define BLAS_ctrsm_base BLAS_FORTRAN_NAME( ctrsm, CTRSM )
#define BLAS_ztrsm_base BLAS_FORTRAN_NAME( ztrsm, ZTRSM )

#ifdef BLAS_FORTRAN_STRLEN_END
    // Pass 1 for string lengths.
    #define BLAS_strsm( ... ) BLAS_strsm_base( __VA_ARGS__, 1, 1, 1, 1 )
    #define BLAS_dtrsm( ... ) BLAS_dtrsm_base( __VA_ARGS__, 1, 1, 1, 1 )
    #define BLAS_ctrsm( ... ) BLAS_ctrsm_base( __VA_ARGS__, 1, 1, 1, 1 )
    #define BLAS_ztrsm( ... ) BLAS_ztrsm_base( __VA_ARGS__, 1, 1, 1, 1 )
#else
    #define BLAS_strsm( ... ) BLAS_strsm_base( __VA_ARGS__ )
    #define BLAS_dtrsm( ... ) BLAS_dtrsm_base( __VA_ARGS__ )
    #define BLAS_ctrsm( ... ) BLAS_ctrsm_base( __VA_ARGS__ )
    #define BLAS_ztrsm( ... ) BLAS_ztrsm_base( __VA_ARGS__ )
#endif

#ifdef BLAS_PROTO
void BLAS_strsm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    float const *alpha,
    float const *A, blas_int const *lda,
    float       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_dtrsm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    double const *alpha,
    double const *A, blas_int const *lda,
    double       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ctrsm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    blas_complex_float const *alpha,
    blas_complex_float const *A, blas_int const *lda,
    blas_complex_float       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );

void BLAS_ztrsm_base(
    char const *side, char const *uplo, char const *trans, char const *diag,
    blas_int const *m, blas_int const *n,
    blas_complex_double const *alpha,
    blas_complex_double const *A, blas_int const *lda,
    blas_complex_double       *B, blas_int const *ldb
    #ifdef BLAS_FORTRAN_STRLEN_END
    , size_t side_len, size_t uplo_len, size_t trans_len, size_t diag_len
    #endif
    );
#endif // BLAS_PROTO

#ifdef __cplusplus
}  // #endif
#endif

#endif        //  #ifndef BLAS_FORTRAN_H
