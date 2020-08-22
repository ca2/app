#include "framework.h"


io_exception::io_exception(::estatus estatus, const char * pszMessage, i32 iSkip) :
   ::exception::exception(pszMessage, ::error_io, iSkip)
{

}


io_exception::~io_exception()
{

}
