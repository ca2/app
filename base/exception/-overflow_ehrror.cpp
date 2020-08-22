#include "framework.h"


overflow_error::overflow_error(const char * pszMessage):
   ::exception::error(pszMessage)
{


}


overflow_error::~overflow_error()
{

}
