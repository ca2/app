// Created by camilo on 2021-01-15 17:10 <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME file_open_exception :
   public ::exception
{
public:


   file_open_exception(::e_status estatus = ::error_file_open, const char* pszMessage = nullptr, i32 iSkip = callstack_DEFAULT_SKIP);
   ~file_open_exception() override;


};


