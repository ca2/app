#include "framework.h"
#include "calculator.h"
#include "aura/const/id.h"


//thread_int_ptr < iptr > t_iAvoidNumericParserException;


numeric_parser_exception::numeric_parser_exception(const char * pszMessage):
   ::exception::exception(pszMessage)
{
   output_debug_string("numeric_parser_exception");
}

numeric_parser_exception::~numeric_parser_exception()
{

}


CLASS_DECL_CORE bool get_avoid_numeric_parser_exception()
{

   return thread_is_set(id_thread_avoid_numeric_parser_exception);

}

CLASS_DECL_CORE bool throw_numeric_parser_exception(const string & strMessage)
{

   if(get_avoid_numeric_parser_exception())
      return false;

   __throw(numeric_parser_exception(strMessage));

   return true;

}



avoid_numeric_parser_exception::avoid_numeric_parser_exception()
{

   m_iBefore = thread_value(id_thread_avoid_numeric_parser_exception);

   thread_set(id_thread_avoid_numeric_parser_exception);

}

avoid_numeric_parser_exception::~avoid_numeric_parser_exception()
{

   thread_value(id_thread_avoid_numeric_parser_exception) = m_iBefore;

}


