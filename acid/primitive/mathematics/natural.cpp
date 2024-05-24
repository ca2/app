#include "framework.h"
////#include "acid/exception/exception.h"


CLASS_DECL_ACID void throw_cast_overflow()
{

   throw ::exception(error_overflow, "cast overflow");

}
