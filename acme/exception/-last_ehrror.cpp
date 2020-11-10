#include "framework.h"

#ifdef WINDOWS
last_error_exception::last_error_exception() :
   hresult_exception(HRESULT_FROM_WIN32(::get_last_error()))
{

}


last_error_exception::~last_error_exception()
{

}
#endif