//
// Created by camilo on Jul/4/2023. 23:37:37 <3ThomasBorregaardSoresen!!
//
#include "framework.h"
#include "c_errno.h"
#include "acme/prototype/string/from_integer.h"
#if defined(__BSD__) || defined(__APPLE__)
#include <errno.h>
#include <string.h>
#endif


c_errno::c_errno() :
   c_errno(s_errno())
{

}


#ifdef WINDOWS


c_errno::c_errno(c_errno_t, errno_t iErrNo) :
   m_iErrNo(iErrNo)
{


}

#else

c_errno::c_errno(c_errno_t, ::i32 iErrorNumber) : m_iErrNo(iErrorNumber) {}

#endif




c_errno::c_errno(const c_errno & errornumber) :
   m_iErrNo(errornumber.m_iErrNo)
{


}


::string c_errno::get_error_description() const
{

   return s_get_error_description(*this);

}


::string c_errno::name() const
{

 switch (m_iErrNo)
   {
      case 0:
         return "NOERROR";
      case EEXIST:
         return "EXIST";
      case EPERM:
         return "EPERM";
      case EACCES:
         return "EACCES";
      case EBADF:
         return "EBADF";
         //      case EDEADLOCK:
         //       return ::file::exception::sharingViolation;
      case EMFILE:
         return "EMFILE";
      case ENOENT:
         return "ENOENT";
      case ENFILE:
         return "ENFILE";
      case ENOTDIR:
         return "ENOTDIR";
      case ENOSPC:
         return "ENOSPC";
      case EINVAL:
         return "EINVAL";
      case EIO:
         return "EIO";
      default:
         return "E*UNKNOWN(" + ::string_from(m_iErrNo) + ")";
   }

}


class ::error_code c_errno::error_code() const
{

   return { e_error_code_type_errno, (::i64) m_iErrNo};

}


::e_status c_errno::estatus() const
{

   switch (m_iErrNo)
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


::e_status c_errno::failed_estatus() const
{

   if(m_iErrNo == 0)
   {

      return error_some_error_has_occurred;

   }

   return this->estatus();

}


c_errno c_errno::s_errno()
{

   return { c_errno_t{}, errno };

}


string c_errno::s_get_error_description(c_errno cerrno)
{

   return strerror(cerrno.m_iErrNo);

}


void c_errno::s_throw_exception(c_errno cerrno)
{

    switch(cerrno.m_iErrNo)
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


//::e_status c_errno::as_status()
//{
//
//   ::i32 iErrorNumber = m_iErrNo;
//
//   auto estatus = cerrno.estatus();
//
//   return estatus;
//
//}


::e_status c_errno::set_last_errno_status()
{

   auto estatus = this->estatus();

   set_last_status(estatus);

   return estatus;

}



