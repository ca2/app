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
#include "debug.h"
#include "_api.h"


void error_code::get_message(::string & strMessage) const
{

   string_reference_stream textstream(strMessage);
   
   switch(m_etype)
   {
      case e_error_code_type_errno:
         textstream << "errno = " << m_iOsError << "\n";
         textstream << ::posix::get_errno_string((::i32)m_iOsError);
         break;
      default:
         textstream << "(Unknown error code type :" << (iptr) m_etype << ") (Error code :" << m_iOsError << ")";
         break;
   };
   
}


