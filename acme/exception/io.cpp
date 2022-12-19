#include "framework.h"
#include "io.h"


io_exception::io_exception(::e_status estatus, const scoped_string & strMessage, i32 iSkip) :
   ::exception(estatus, pszMessage, nullptr, iSkip)
{

}


io_exception::~io_exception()
{

}



