#include "framework.h"
#include "acme/const/id.h"


//thread_int_ptr < iptr > t_iAvoidNumericParserException;


numeric_parser_exception::numeric_parser_exception(const char * pszMessage):
   ::exception::exception(pszMessage)
{
   output_debug_string("numeric_parser_exception");
}

numeric_parser_exception::~numeric_parser_exception()
{

}


CLASS_DECL_AXIS bool get_avoid_numeric_parser_exception()
{

   return thread_is_set(id_thread_avoid_numeric_parser_exception);

}

CLASS_DECL_AXIS bool throw_numeric_parser_exception(const string & strMessage)
{

   if(get_avoid_numeric_parser_exception())
      return false;

   __throw(error_parsing, strMessage);

   return true;

}



avoid_numeric_parser_exception::avoid_numeric_parser_exception()
{

   m_iBefore = thread_property(id_thread_avoid_numeric_parser_exception);

   thread_set(id_thread_avoid_numeric_parser_exception);

}

avoid_numeric_parser_exception::~avoid_numeric_parser_exception()
{

   thread_property(id_thread_avoid_numeric_parser_exception) = m_iBefore;

}


