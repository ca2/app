#include "framework.h"


overflow_exception::overflow_exception(const scoped_string & strMessage):
   ::exception(pszMessage)
{


}


overflow_exception::~overflow_exception()
{

}
