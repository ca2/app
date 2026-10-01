#include "platform.h"
#include "io.h"


io_exception::io_exception(::e_status estatus, const ::scoped_string & scopedstrMessage, ::i32 iSkip) :
   ::exception(estatus, scopedstrMessage, nullptr, iSkip)
{
   log_constructor("io_exception");

}


io_exception::~io_exception()
{

}



