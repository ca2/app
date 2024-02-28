//
// Created by camilo on Jul/4/2023. 23:37:37 <3ThomasBorregaardSoresen!!
//
#include "framework.h"
#include "c_error_number.h"
#if defined(FREEBSD) || defined(__APPLE__)
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


class ::error_code c_error_number::error_code() const
{

   return { e_error_code_type_errno, (::i64) m_iErrorNumber};

}


::e_status c_error_number::estatus() const
{

   switch (m_iErrorNumber)
   {
      case 0:
         return ::success;
      case EEXIST:
         return ::error_already_exists;
      case EPERM:
      case EACCES:
         return error_file_access_denied;
      case EBADF:
         return error_invalid_file;
         //      case EDEADLOCK:
         //       return ::file::exception::sharingViolation;
      case EMFILE:
         return error_too_many_open_files;
      case ENOENT:
      case ENFILE:
         return error_file_not_found;
      case ENOTDIR:
         return error_not_a_directory;
      case ENOSPC:
         return error_disk_full;
      case EINVAL:
      case EIO:
         return error_hard_io;
      default:
         return ::error_failed;
   }

}


::e_status c_error_number::failed_estatus() const
{

   if(m_iErrorNumber == 0)
   {

      return error_some_error_has_occurred;

   }

   return this->estatus();

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


//::e_status c_error_number::as_status()
//{
//
//   int iErrorNumber = m_iErrorNumber;
//
//   auto estatus = cerrornumber.estatus();
//
//   return estatus;
//
//}


::e_status c_error_number::set_last_errno_status()
{

   auto estatus = this->estatus();

   set_last_status(estatus);

   return estatus;

}



