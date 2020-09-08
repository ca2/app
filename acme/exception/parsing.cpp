#include "framework.h"


//thread_int_ptr < iptr > t_iAvoidParsingException;


parsing_exception::parsing_exception(const char * pszMessage) :
   ::exception::exception(pszMessage)
{

   output_debug_string("parsing_exception");

}


parsing_exception::~parsing_exception()
{

}


CLASS_DECL_ACME bool get_avoid_parsing_exception()
{

   return thread_value("avoid_parsing_exception");

}

CLASS_DECL_ACME bool throw_parsing_exception(const string & strMessage)
{

   if(get_avoid_parsing_exception())
      return false;

   __throw(parsing_exception(strMessage));

   return true;

}



avoid_parsing_exception::avoid_parsing_exception() :
   m_varAvoidParsingException(thread_value("avoid_parsing_exception"))
{

   m_iBefore = m_varAvoidParsingException;

   m_varAvoidParsingException = true;

}

avoid_parsing_exception::~avoid_parsing_exception()
{

   m_varAvoidParsingException = m_iBefore;

}





json_parsing_exception::json_parsing_exception(const char * pszMessage) :
   parsing_exception(pszMessage)
{

   output_debug_string("parsing_exception");

}


json_parsing_exception::~json_parsing_exception()
{

}



CLASS_DECL_ACME bool throw_json_parsing_exception(const string & strMessage)
{

   if (get_avoid_parsing_exception())
      return false;

   __throw(json_parsing_exception(strMessage));

   return true;

}
