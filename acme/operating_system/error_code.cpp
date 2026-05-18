//
//  error_code.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 22:17
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acme/filesystem/file/text_stream.h"
//#include "error_code.h"
#include "shared_posix/c_errno.h"
#include "debug.h"
#include "_api.h"
#ifdef WINDOWS
#include "acme/operating_system/windows/windows.h"
#endif

error_code::error_code(const c_errno & cerrno) :
   m_etype(e_error_code_type_errno),
   m_iOsError(cerrno.m_iErrNo)
{


}


void get_message(::string & strMessage, const ::error_code & errorcode)
{

   string_reference_stream textstream(strMessage);
   
   switch(errorcode.m_etype)
   {
      case e_error_code_type_errno:
         textstream << "errno = " << errorcode.m_iOsError << "\n";
         textstream << ::posix::get_errno_string((int)errorcode.m_iOsError);
         break;
      default:
         textstream << "(Unknown error code type :" << (iptr)errorcode.m_etype << ") (Error code :" << errorcode.m_iOsError << ")";
         break;
   };
   
}


bool error_code::is_clear() const
{
   
   
   if(m_etype == e_error_code_type_none)
   {
      
      return true;
      
   }
   
   if(m_iOsError == 0)
   {
      
      return true;
      
   }
   
   
   return false;
   
}


bool error_code::is_set() const
{

   return !is_clear();
   
}



::string error_code::get_error_message() const
{
   
   ::string strErrorMessage;
 
   if(m_etype == e_error_code_type_none)
   {
      
      strErrorMessage.formatf("{%lld}", m_iOsError);
      
   }
#ifdef WINDOWS
   else if(m_etype == e_error_code_type_last_error)
   {
      
      ::last_error lasterror((::u32) m_iOsError);
      
      strErrorMessage = ::windows::last_error_message(lasterror);
      
   }
#endif
   else if(m_etype == e_error_code_type_errno)
   {
      
      strErrorMessage = strerror((int) m_iOsError);
      
   }
   else
   {
      
      strErrorMessage.format("(unknown error %lld)", m_iOsError);
      
   }

   return strErrorMessage;
   
}


::e_status error_code::as_status() const
{
   
   ::e_status estatus = error_failed;
 
   if(m_etype == e_error_code_type_none)
   {
      
      //strErrorMessage.formatf("{%lld}", m_iOsError);
      
   }
#ifdef WINDOWS
   else if(m_etype == e_error_code_type_last_error)
   {
      
      
      ::last_error lasterror((::u32) m_iOsError);
      // ERROR_CANCELLED
      
      estatus = strErrorMessage = ::windows::last_error_e_status(lasterror);
      
   }
#endif
   else if(m_etype == e_error_code_type_errno)
   {
      
      //strErrorMessage = strerror((int) m_iOsError);
      
   }
   else
   {
      
      //strErrorMessage.format("(unknown error %lld)", m_iOsError);
      
   }

   return estatus;
   
}
