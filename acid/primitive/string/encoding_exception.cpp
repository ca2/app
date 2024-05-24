#include "framework.h"
#include "encoding_exception.h"



encoding_exception::encoding_exception(const ::string & strMessage) :
   exception(::error_encoding, strMessage)
{



}



CLASS_DECL_ACID void throw_encoding_exception(const ::scoped_string & scopedstrMessage)
{

   throw encoding_exception(scopedstrMessage);

}



