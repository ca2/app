//
// Created by camilo on Jul/4/2023. 23:37:37 <3ThomasBorregaardSoresen!!
//
#include "framework.h"
#include "c_error_number.h"
#if defined(FREEBSD)
#include <errno.h>
#include <string.h>
#endif


c_error_number::c_error_number() :
   c_error_number(s_errno())
{

}


#ifdef WINDOWS


c_error_number::c_error_number(errno_t iErrNo) :
   m_iErrorNumber(iErrNo)
{


}


#endif

c_error_number::c_error_number(c_error_number_t, ::i32 iErrorNumber) :
   m_iErrorNumber(iErrorNumber)
{


}


c_error_number::c_error_number(const c_error_number & errornumber) :
   m_iErrorNumber(errornumber.m_iErrorNumber)
{


}


::string c_error_number::get_error_description()
{

   return s_get_error_description(*this);

}


c_error_number c_error_number::s_errno()
{

   return { c_error_number_t{}, errno };

}


string c_error_number::s_get_error_description(c_error_number cerrornumber)
{

   return strerror(cerrornumber.m_iErrorNumber);

}


void c_error_number::s_throw_exception(c_error_number cerrornumber)
{

    switch(cerrornumber.m_iErrorNumber)
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

}


::e_status c_error_number::as_status()
{

   int iErrorNumber = m_iErrorNumber;

   auto estatus = errno_status(iErrorNumber);

   return estatus;

}


::e_status c_error_number::set_last_errno_status()
{

   auto estatus = this->as_status();

   set_last_status(estatus);

   return estatus;

}



