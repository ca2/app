#include "framework.h"


io_exception::io_exception(void estatus, const char * pszMessage, i32 iSkip) :
   ::exception(estatus, pszMessage, iSkip)
{

}


io_exception::~io_exception()
{

}
