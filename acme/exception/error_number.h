// Created by camilo on 2022-11-09 04:41 <3ThomasBorregaardSorensen!!
#pragma once


#include "exception.h"


class CLASS_DECL_ACME error_number :
   public ::exception
{
public:


   int m_iErrNo;


#ifdef ANDROID
   error_number(::e_status estatus, int iError, const scoped_string & strMessage = nullptr, const scoped_string & strDetails = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER) :
      ::exception(estatus, pszMessage, pszDetails, iSkip),
#else
   error_number(::e_status estatus, int iError, const scoped_string & strMessage = nullptr, const scoped_string & strDetails = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr) :
      ::exception(estatus, pszMessage, pszDetails, iSkip, caller_address),
#endif
      m_iErrNo(iError)
   {

   }

   ~error_number()
   {

   }


};




