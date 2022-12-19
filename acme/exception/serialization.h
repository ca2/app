// Created by camilo on 2021-01-15 16:44 <3ThomasBorregaardSørensen!!
#pragma once


//#include "exception.h"


class CLASS_DECL_ACME serialization_exception :
   public ::exception
{
public:


   serialization_exception(::e_status estatus = ::error_serialization, const scoped_string & strMessage = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP);
   ~serialization_exception() override;


};



