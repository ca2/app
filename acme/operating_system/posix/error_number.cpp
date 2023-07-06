//
// Created by camilo on Jul/4/2023. 23:37:37 <3ThomasBorregaardSoresen!!
//
#include "framework.h"
#if defined(FREEBSD)
#include <errno.h>
#endif


errno_t c_runtime_error_check(errno_t error)
{

    switch(error)
    {
        case ENOMEM:
            throw ::exception(error_no_memory, nullptr, nullptr, CALLSTACK_DEFAULT_SKIP + 1);
            break;
        case EINVAL:
        case ERANGE:
            throw ::exception(error_bad_argument, nullptr, nullptr, CALLSTACK_DEFAULT_SKIP + 1);
            break;
#if defined(WINDOWS)
            case STRUNCATE:
#endif
        case 0:
            break;
        default:
            throw ::exception(error_bad_argument, nullptr, nullptr, CALLSTACK_DEFAULT_SKIP + 1);
            break;
    }

    return error;

}


::e_status set_last_errno_status()
{

    int iErrorNumber = errno;

    auto estatus = errno_status(iErrorNumber);

    set_last_status(estatus);

    return estatus;

}



