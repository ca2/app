//
//  error_code.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/09/22 ~22:12
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#include "acme/constant/error_code_type.h"


class c_errno;

#ifdef WINDOWS
namespace windows { class last_error; }
#endif


class CLASS_DECL_ACME error_code
{
public:
   
   
   enum_error_code_type m_etype;

   
   ::i64 m_iOsError;


   error_code() :m_etype(e_error_code_type_none), m_iOsError(0) {}
   error_code(const error_code & error_code) : m_etype(error_code.m_etype), m_iOsError(error_code.m_etype) {}
   error_code(const c_errno & cerrno);
#ifdef WINDOWS
   error_code(const ::windows::last_error & lasterror);
#endif
   error_code(enum_error_code_type etype, ::i64 iOsError) :m_etype(etype), m_iOsError(iOsError) {}


   bool is_clear() const;
   //void get_message(::string & strMessage) const;

   bool is_set() const;
   
   ::string get_error_message() const;
   
   ::e_status as_status() const;
   
};

namespace operating_system
{


   CLASS_DECL_ACME ::error_code last_error_code();


} // namespace operating_system

//inline error_code errno_error_code(int iErrNo)
//{
//
//   return { e_error_code_type_errno, iErrNo };
//
//}



