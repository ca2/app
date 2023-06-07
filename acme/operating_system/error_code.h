//
//  error_code.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 ~22:12
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


#include "acme/constant/error_code_type.h"


class CLASS_DECL_ACME error_code
{
public:
   
   
   enum_error_code_type m_etype;

   
   ::i64 m_iOsError;


   error_code() :m_etype(e_error_code_type_none), m_iOsError(0) {}
   error_code(const error_code & error_code) : m_etype(error_code.m_etype), m_iOsError(error_code.m_etype) {}
   error_code(enum_error_code_type etype, ::i64 iOsError) :m_etype(etype), m_iOsError(iOsError) {}


   void get_message(::string & strMessage) const;

   
};


inline error_code errno_error_code(int iErrNo)
{
 
   return { e_error_code_type_errno, iErrNo };
   
}



