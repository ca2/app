// Created by camilo on 2021-01-15 16:44 <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME serialization_exception :
   public ::exception
{
public:


   serialization_exception(::e_status estatus = ::error_serialization, const char* pszMessage = nullptr, i32 iSkip = callstack_DEFAULT_SKIP);
   ~serialization_exception() override;


};



