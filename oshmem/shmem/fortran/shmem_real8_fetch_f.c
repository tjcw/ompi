/*
 * Copyright (c) 2016      Mellanox Technologies, Inc.
 *                         All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "oshmem_config.h"
#include "oshmem/shmem/fortran/bindings.h"
#include "oshmem/include/shmem.h"
#include "oshmem/shmem/shmem_api_logger.h"
#include "oshmem/runtime/runtime.h"
#include "oshmem/mca/atomic/atomic.h"
#include "ompi/datatype/ompi_datatype.h"
#include "oshmem/op/op.h"
#include "stdio.h"

#if OSHMEM_PROFILING
#include "oshmem/shmem/fortran/profile/pbindings.h"
SHMEM_GENERATE_WEAK_BINDINGS(SHMEM_REAL8_FETCH, shmem_real8_fetch)
#include "oshmem/shmem/fortran/profile/defines.h"
#endif

SHMEM_GENERATE_FORTRAN_BINDINGS_FUNCTION (ompi_fortran_real8_t,
        SHMEM_REAL8_FETCH,
        shmem_real8_fetch_,
        shmem_real8_fetch__,
        shmem_real8_fetch_f,
        (FORTRAN_POINTER_T target, MPI_Fint *pe),
        (target,pe) )

ompi_fortran_real8_t shmem_real8_fetch_f(FORTRAN_POINTER_T target, MPI_Fint *pe)
{
    ompi_fortran_real8_t out_value = 0;
    oshmem_op_t* op = oshmem_op_sum_freal8;
    int value = 0;

    MCA_ATOMIC_CALL(fadd(FPTR_2_VOID_PTR(target),
        (void *)&out_value,
        (const void *)&value,
        sizeof(out_value),
        OMPI_FINT_2_INT(*pe),
        op));

    return out_value;
}

