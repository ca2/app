//
//  error_code.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 ~22:12
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


#include "acme/constant/error_code_type.h"


class text_stream;


class CLASS_DECL_ACME error_code
{
public:
   
   enum_error_code_type m_etype;

   ::i64 m_iOsError;
   
   void get_string(::text_stream & stream) const;
   
};


inline error_code errno_error_code(int iErrNo)
{
 
   return { e_error_code_type_errno, iErrNo };
   
}



