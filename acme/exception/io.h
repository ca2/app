#pragma once


class CLASS_DECL_ACME io_exception :
   public ::exception
{
public:


   io_exception(::e_status3 estatus = ::error_io, const char * pszMessage = nullptr, i32 iSkip = callstack_DEFAULT_SKIP);
   ~io_exception() override;


};











