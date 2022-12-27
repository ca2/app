#include "framework.h"


// //thread_int_ptr < iptr > t_iAvoidParsingException;


// parsing_exception::parsing_exception(const ::scoped_string & scopedstrMessage) :
//    ::exception(pszMessage)
// {

//    output_debug_string("parsing_exception");

// }


// parsing_exception::~parsing_exception()
// {

// }


thread_local bool t_bAvoidParsingException = false;

CLASS_DECL_ACME bool get_avoid_parsing_exception()
{

   return t_bAvoidParsingException;

}


CLASS_DECL_ACME void set_avoid_parsing_exception(bool bSet)
{

   t_bAvoidParsingException = bSet;

}


CLASS_DECL_ACME bool throw_parsing_exception(const ::string & strMessage)
{

   if (get_avoid_parsing_exception())
   {

      return false;

   }

   //throw ::exception(parsing_exception(strMessage));

   throw ::parsing_exception(strMessage);

   return true;

}



avoid_parsing_exception::avoid_parsing_exception() :
   m_bAvoidParsingExceptionPrevious(get_avoid_parsing_exception())
{

   set_avoid_parsing_exception(true);

}

avoid_parsing_exception::~avoid_parsing_exception()
{

   set_avoid_parsing_exception(m_bAvoidParsingExceptionPrevious);

}





network_payload_parsing_exception::network_payload_parsing_exception(const ::scoped_string & scopedstrMessage) :
   parsing_exception(pszMessage)
{

   output_debug_string("parsing_exception");

}


network_payload_parsing_exception::~network_payload_parsing_exception()
{

}



CLASS_DECL_ACME bool throw_network_payload_parsing_exception(const ::string & strMessage)
{

   if (get_avoid_parsing_exception())
   {

      return false;

   }

   throw ::exception(network_payload_parsing_exception(strMessage));

   return true;

}
