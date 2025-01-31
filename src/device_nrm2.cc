// Copyright (c) 2017-2022, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "blas/device_blas.hh"

#include "device_internal.hh"

#include <limits>

// =============================================================================
// Overloaded wrappers for s, d, c, z precisions.

// -----------------------------------------------------------------------------
/// @ingroup nrm2
void blas::nrm2(
    int64_t n,
    float *dx, int64_t incdx,
    float *result,
    blas::Queue& queue)
{
    // check arguments
    blas_error_if( n < 0 );       // standard BLAS returns, doesn't fail
    blas_error_if( incdx <= 0 );  // standard BLAS returns, doesn't fail

    // check for overflow in native BLAS integer type, if smaller than int64_t
    if (sizeof(int64_t) > sizeof(device_blas_int)) {
        blas_error_if( n     > std::numeric_limits<device_blas_int>::max() );
        blas_error_if( incdx > std::numeric_limits<device_blas_int>::max() );
    }

    device_blas_int n_     = (device_blas_int) n;
    device_blas_int incdx_ = (device_blas_int) incdx;

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    device::snrm2( queue, n_, dx, incdx_, result );
}

// -----------------------------------------------------------------------------
/// @ingroup nrm2
void blas::nrm2(
    int64_t n,
    double *dx, int64_t incdx,
    double *result,
    blas::Queue& queue)
{
    // check arguments
    blas_error_if( n < 0 );       // standard BLAS returns, doesn't fail
    blas_error_if( incdx <= 0 );  // standard BLAS returns, doesn't fail

    // check for overflow in native BLAS integer type, if smaller than int64_t
    if (sizeof(int64_t) > sizeof(device_blas_int)) {
        blas_error_if( n     > std::numeric_limits<device_blas_int>::max() );
        blas_error_if( incdx > std::numeric_limits<device_blas_int>::max() );
    }

    device_blas_int n_     = (device_blas_int) n;
    device_blas_int incdx_ = (device_blas_int) incdx;

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    device::dnrm2( queue, n_, dx, incdx_, result );
}

// -----------------------------------------------------------------------------
/// @ingroup nrm2
void blas::nrm2(
    int64_t n,
    std::complex<float> *dx, int64_t incdx,
    float *result,
    blas::Queue& queue)
{
    // check arguments
    blas_error_if( n < 0 );       // standard BLAS returns, doesn't fail
    blas_error_if( incdx <= 0 );  // standard BLAS returns, doesn't fail

    // check for overflow in native BLAS integer type, if smaller than int64_t
    if (sizeof(int64_t) > sizeof(device_blas_int)) {
        blas_error_if( n     > std::numeric_limits<device_blas_int>::max() );
        blas_error_if( incdx > std::numeric_limits<device_blas_int>::max() );
    }

    device_blas_int n_     = (device_blas_int) n;
    device_blas_int incdx_ = (device_blas_int) incdx;

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    device::cnrm2( queue, n_, dx, incdx_, result );
}

// -----------------------------------------------------------------------------
/// @ingroup nrm2
void blas::nrm2(
    int64_t n,
    std::complex<double> *dx, int64_t incdx,
    double *result,
    blas::Queue& queue)
{
    // check arguments
    blas_error_if( n < 0 );       // standard BLAS returns, doesn't fail
    blas_error_if( incdx <= 0 );  // standard BLAS returns, doesn't fail

    // check for overflow in native BLAS integer type, if smaller than int64_t
    if (sizeof(int64_t) > sizeof(device_blas_int)) {
        blas_error_if( n     > std::numeric_limits<device_blas_int>::max() );
        blas_error_if( incdx > std::numeric_limits<device_blas_int>::max() );
    }

    device_blas_int n_     = (device_blas_int) n;
    device_blas_int incdx_ = (device_blas_int) incdx;

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    device::znrm2( queue, n_, dx, incdx_, result );
}
