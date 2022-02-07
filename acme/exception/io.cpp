#include "framework.h"


io_exception::io_exception(::e_status estatus, const char * pszMessage, i32 iSkip) :
   ::exception(estatus, pszMessage, nullptr, iSkip)
{

}


io_exception::~io_exception()
{

}
