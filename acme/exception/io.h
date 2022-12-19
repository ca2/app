#pragma once


//#include "exception.h"


class CLASS_DECL_ACME io_exception :
   public ::exception
{
public:


   io_exception(::e_status estatus = ::error_io, const scoped_string & strMessage = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP);
   ~io_exception() override;


};











