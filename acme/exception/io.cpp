#include "framework.h"


io_exception::io_exception(::e_status3 estatus, const char * pszMessage, i32 iSkip) :
   ::exception(estatus, pszMessage, iSkip)
{

}


io_exception::~io_exception()
{

}
