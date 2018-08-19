# f2mkl
This is an extremely simple adapter for `LD_PRELOAD`-ing Intel MKL in applications linked against Fortran BLAS.

- [BLAS](http://www.netlib.org/blas/) is a set of linear algebraic primitives with widespread adoption in high-performance computing. The original library was written in Fortran and many binaries still call BLAS through Fortran symbols.

- [Intel MKL](https://software.intel.com/en-us/mkl) provides a highly optimized BLAS implementation (among others) that can be much faster than generic BLAS libraries.

- [`LD_PRELOAD`](http://man7.org/linux/man-pages/man8/ld.so.8.html#ENVIRONMENT) is a code injection mechanism for ELF shared objects as commonly used in Unix-based systems. The point is that we can use this to "replace" standard BLAS with MKL at runtime and get a free speed-up.

## Overview

Suppose that you have a program compiled against some standard BLAS that you would like to accelerate by linking against MKL instead. For me, this was stock Octave in Ubuntu, so let's use that as a running example. The natural thing to do then is something like:

```bash
alias myoctave="LD_PRELOAD=\"/opt/intel/mkl/lib/intel64/libmkl_rt.so /opt/intel/lib/intel64/libiomp5.so\" octave"
```

and to use `myoctave` instead of `octave`.

On my machine, this immediately produces the intended effect; for example:

```bash
$ octave --eval "n = 1024; A = rand(n); tic; A*A; toc"
Elapsed time is 0.14859 seconds.
```

while

```bash
$ myoctave --eval "n = 1024; A = rand(n); tic; A*A; toc"
Elapsed time is 0.11987 seconds.
```

So, great!--we're done, right? Well, not quite. Some more testing shows that:

```bash
$ myoctave --eval "dot(1i,1i)"
Segmentation fault (core dumped)
```

and similarly for any Octave function that works with complex numbers in a certain way. The problem appears to be due to how MKL handles [complex return values in C vs. Fortran](https://software.intel.com/en-us/mkl-linux-developer-guide-calling-blas-functions-that-return-the-complex-values-in-c-c-code). Indeed, rebinding the Fortran symbols to call the corresponding C functions as in:

```c
MKL_Complex16
zdotc_(const MKL_INT *n, const MKL_Complex16 *x, const MKL_INT *incx,
                         const MKL_Complex16 *y, const MKL_INT *incy)
{
    MKL_Complex16 res;
    zdotc(&res, n, x, incx, y, incy);
    return res;
}
```

seems to fix the issue. The f2mkl adapter simply consists of all such required redefinitions, including `cdotc_`, `cdotu_`, `zdotc_`, and `zdotu_` for BLAS; and `cdotci_`, `cdotui_`, `zdotci_`, and `zdotui_` for a basic version of Sparse BLAS.

Compiling f2mkl and preloading as in:

```bash
alias myoctave="LD_PRELOAD=\"libf2mkl.so /opt/intel/mkl/lib/intel64/libmkl_rt.so /opt/intel/lib/intel64/libiomp5.so\" octave"
```

then gives:

```bash
$ myoctave --eval "dot(1i,1i)"
ans = 1
```

as expected.

## Instructions

1. Compile by typing `make`, with `$MKLROOT` (default: `/opt/intel/mkl`) set appropriately so that `mkl.h` can be found.
2. `LD_PRELOAD` `libf2mkl.so` first and then the MKL libraries as above.
3. ????
4. Profit!
