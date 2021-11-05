#include "framework.h"


invalid_handle_exception::invalid_handle_exception(const char * pszMessage) :
   os_exception(pszMessage)
{


}


invalid_handle_exception::~invalid_handle_exception()
{

}
