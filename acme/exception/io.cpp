#include "framework.h"
#include "io.h"


io_exception::io_exception(::e_status estatus, const ::scoped_string & scopedstrMessage, i32 iSkip) :
   ::exception(estatus, scopedstrMessage, nullptr, iSkip)
{

}


io_exception::~io_exception()
{

}



