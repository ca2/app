#include "framework.h"
#include "encoding_exception.h"



encoding_exception::encoding_exception(const ::scoped_string & scopedstrMessage) :
   exception(::error_encoding, scopedstrMessage)
{



}


CLASS_DECL_ACME void throw_encoding_exception(const_char_pointer pszMessage)
{

   throw encoding_exception(pszMessage);

}



