#include "framework.h"


io_exception::io_exception(::e_status estatus, const char * pszMessage, i32 iSkip) :
   ::exception(pszMessage, ::error_io, iSkip)
{

}


io_exception::~io_exception()
{

}
