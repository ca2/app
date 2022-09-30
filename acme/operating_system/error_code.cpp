//
//  error_code.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 22:17
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "error_code.h"
#include "_api.h"


void error_code::get_string(::text_stream & textstream) const
{
   
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
