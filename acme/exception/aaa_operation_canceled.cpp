#include "framework.h"


operation_canceled_exception::operation_canceled_exception(const ::scoped_string & scopedstrMessage):
   ::exception(pszMessage)
{

}


operation_canceled_exception::~operation_canceled_exception()
{

}
