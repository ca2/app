#include "framework.h"




installing_exception::installing_exception(const scoped_string & strTip):
   temporary_exception(pszTip)
{

}

installing_exception::~installing_exception()
{
}

