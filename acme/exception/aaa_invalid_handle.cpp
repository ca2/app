#include "framework.h"


invalid_handle_exception::invalid_handle_exception(const scoped_string & strMessage) :
   os_exception(pszMessage)
{


}


invalid_handle_exception::~invalid_handle_exception()
{

}
