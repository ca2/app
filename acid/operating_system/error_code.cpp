//
//  error_code.cpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 22:17
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acid/filesystem/file/text_stream.h"
//#include "error_code.h"
#include "shared_posix/c_error_number.h"
#include "debug.h"
#include "_api.h"


error_code::error_code(const c_error_number & error_code) :
   m_etype(e_error_code_type_errno),
   m_iOsError(error_code.m_iErrorNumber)
{


}


void get_message(::string & strMessage, const ::error_code & errorcode)
{

   string_reference_stream textstream(strMessage);
   
   switch(errorcode.m_etype)
   {
      case e_error_code_type_errno:
         textstream << "errno = " << errorcode.m_iOsError << "\n";
         textstream << ::posix::get_errno_string((::i32)errorcode.m_iOsError);
         break;
      default:
         textstream << "(Unknown error code type :" << (iptr)errorcode.m_etype << ") (Error code :" << errorcode.m_iOsError << ")";
         break;
   };
   
}


