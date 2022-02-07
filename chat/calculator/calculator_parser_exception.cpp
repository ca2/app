#include "framework.h"


thread_int_ptr < iptr > t_iAvoidNumericParserException;


numeric_parsing_exception::numeric_parsing_exception(::object * pobject, const ::string & strMessage):
::object(pobject),
::call_stack(this),
::exception(),
::exception(strMessage)
{

}

numeric_parsing_exception::~numeric_parsing_exception()
{

}


CLASS_DECL_CA2_MATH bool get_avoid_numeric_parsing_exception()
{

   return t_iAvoidNumericParserException != false;

}

CLASS_DECL_CA2_MATH bool throw_numeric_parsing_exception(const ::string & strMessage)
{

   if(get_avoid_numeric_parsing_exception())
      return false;

   throw ::exception(numeric_parsing_exception(strMessage));

   return true;

}



avoid_numeric_parsing_exception::avoid_numeric_parsing_exception()
{

   m_iBefore = t_iAvoidNumericParserException;

   t_iAvoidNumericParserException = true;

}

avoid_numeric_parsing_exception::~avoid_numeric_parsing_exception()
{

   t_iAvoidNumericParserException = m_iBefore;

}


