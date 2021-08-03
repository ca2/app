#include "framework.h"


thread_int_ptr < iptr > t_iAvoidNumericParserException;


numeric_parser_exception::numeric_parser_exception(::object * pobject,const ::string & strMessage):
::object(pobject),
::call_stack(this),
::exception::exception(),
::exception::exception(strMessage)
{

}

numeric_parser_exception::~numeric_parser_exception()
{

}


CLASS_DECL_CA2_MATH bool get_avoid_numeric_parser_exception()
{

   return t_iAvoidNumericParserException != false;

}

CLASS_DECL_CA2_MATH bool throw_numeric_parser_exception(const ::string & strMessage)
{

   if(get_avoid_numeric_parser_exception())
      return false;

   __throw(numeric_parser_exception(strMessage));

   return true;

}



avoid_numeric_parser_exception::avoid_numeric_parser_exception()
{

   m_iBefore = t_iAvoidNumericParserException;

   t_iAvoidNumericParserException = true;

}

avoid_numeric_parser_exception::~avoid_numeric_parser_exception()
{

   t_iAvoidNumericParserException = m_iBefore;

}


