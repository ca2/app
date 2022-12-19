#include "framework.h"


range_exception::range_exception(const scoped_string & strMessage):
   ::exception(pszMessage)
{


}


range_exception::~range_exception()
{

}
