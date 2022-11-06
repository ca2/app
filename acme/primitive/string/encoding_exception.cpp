#include "framework.h"
#include "encoding_exception.h"



encoding_exception::encoding_exception(const ::string & strMessage) :
   exception(::error_encoding, strMessage)
{



}



CLASS_DECL_ACME void throw_encoding_exception(const char * pszMessage)
{

   throw encoding_exception(pszMessage);

}



