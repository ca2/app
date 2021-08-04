#include "framework.h"
#include "acme/const/id.h"


numeric_parser_exception::numeric_parser_exception(const ::string & pszMessage):
   ::exception::exception(error_parsing, pszMessage)
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

CLASS_DECL_AXIS bool throw_numeric_parser_exception(const ::string & strMessage)
{

   if (get_avoid_numeric_parser_exception())
   {

      return false;

   }

   throw numeric_parser_exception(strMessage);

   return true;

}



avoid_numeric_parser_exception::avoid_numeric_parser_exception()
{

   thread_property(id_thread_avoid_numeric_parser_exception).as(m_iBefore);

   thread_set(id_thread_avoid_numeric_parser_exception);

}

avoid_numeric_parser_exception::~avoid_numeric_parser_exception()
{

   thread_property(id_thread_avoid_numeric_parser_exception) = m_iBefore;

}


