#pragma once


class CLASS_DECL_ACME io_exception :
   public ::exception::exception
{
public:


   io_exception(::e_status estatus = ::error_io, const char * pszMessage = nullptr, i32 iSkip = callstack_DEFAULT_SKIP);
   virtual ~io_exception();


};











