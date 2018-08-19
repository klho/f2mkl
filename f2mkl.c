#include "mkl.h"

/* BLAS */

MKL_Complex8
cdotc_(const MKL_INT *n, const MKL_Complex8 *x, const MKL_INT *incx,
                         const MKL_Complex8 *y, const MKL_INT *incy)
{
    MKL_Complex8 res;
    cdotc(&res, n, x, incx, y, incy);
    return res;
}

MKL_Complex8
cdotu_(const MKL_INT *n, const MKL_Complex8 *x, const MKL_INT *incx,
                         const MKL_Complex8 *y, const MKL_INT *incy)
{
    MKL_Complex8 res;
    cdotu(&res, n, x, incx, y, incy);
    return res;
}

MKL_Complex16
zdotc_(const MKL_INT *n, const MKL_Complex16 *x, const MKL_INT *incx,
                         const MKL_Complex16 *y, const MKL_INT *incy)
{
    MKL_Complex16 res;
    zdotc(&res, n, x, incx, y, incy);
    return res;
}

MKL_Complex16
zdotu_(const MKL_INT *n, const MKL_Complex16 *x, const MKL_INT *incx,
                         const MKL_Complex16 *y, const MKL_INT *incy)
{
    MKL_Complex16 res;
    zdotu(&res, n, x, incx, y, incy);
    return res;
}

/* Sparse BLAS */

MKL_Complex8
cdotci_(const MKL_INT *nz, const MKL_Complex8 *x, const MKL_INT *indx,
                           const MKL_Complex8 *y)
{
    MKL_Complex8 res;
    cdotci(&res, nz, x, indx, y);
    return res;
}

MKL_Complex8
cdotui_(const MKL_INT *nz, const MKL_Complex8 *x, const MKL_INT *indx,
                           const MKL_Complex8 *y)
{
    MKL_Complex8 res;
    cdotui(&res, nz, x, indx, y);
    return res;
}

MKL_Complex16
zdotci_(const MKL_INT *nz, const MKL_Complex16 *x, const MKL_INT *indx,
                           const MKL_Complex16 *y)
{
    MKL_Complex16 res;
    zdotci(&res, nz, x, indx, y);
    return res;
}

MKL_Complex16
zdotui_(const MKL_INT *nz, const MKL_Complex16 *x, const MKL_INT *indx,
                           const MKL_Complex16 *y)
{
    MKL_Complex16 res;
    zdotui(&res, nz, x, indx, y);
    return res;
}
