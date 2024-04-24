#include "framework.h"




installing_exception::installing_exception(const ::scoped_string & scopedstrTip):
   temporary_exception(pszTip)
{

}

installing_exception::~installing_exception()
{
}

