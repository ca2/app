#include "framework.h"


invalid_handle_exception::invalid_handle_exception(const ::scoped_string & scopedstrMessage) :
   os_exception(pszMessage)
{


}


invalid_handle_exception::~invalid_handle_exception()
{

}
