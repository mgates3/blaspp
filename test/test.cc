#include "test.hh"

#include "blas.hh"

//#include <mkl.h>

// -----------------------------------------------------------------------------
int main()
{
    test_asum();
    test_axpy();
    test_copy();
    test_dot();
    test_iamax();
    test_nrm2();
    test_rot();
    test_rotg();
    test_rotm();
    test_rotmg();
    test_scal();
    test_swap();
    return 0;
}
