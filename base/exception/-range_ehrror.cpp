#include "framework.h"


range_error::range_error(const char * pszMessage):
   ::exception::error(pszMessage)
{


}


range_error::~range_error()
{

}
