#include "framework.h"


overflow_exception::overflow_exception(const char * pszMessage):
   ::exception(pszMessage)
{


}


overflow_exception::~overflow_exception()
{

}
