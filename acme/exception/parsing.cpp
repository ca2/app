#include "framework.h"
#include "parsing.h"


parsing_exception::parsing_exception(const ::scoped_string & scopedstrMessage) :
   ::exception(error_parsing, scopedstrMessage)
{

   information("parsing_exception");

}


parsing_exception::~parsing_exception()
{

}


thread_local bool t_bAvoidParsingException = false;


CLASS_DECL_ACME bool should_avoid_parsing_exception()
{

   return task_flag().is_set(e_task_flag_avoid_parsing_exception);

}


CLASS_DECL_ACME void set_avoid_parsing_exception(bool bSet)
{

   task_flag().set(e_task_flag_avoid_parsing_exception, bSet);

}


CLASS_DECL_ACME bool throw_parsing_exception(const ::scoped_string & scopedstrMessage)
{

   if (should_avoid_parsing_exception())
   {

      return false;

   }

   throw ::parsing_exception(scopedstrMessage);

   return true;

}



//avoid_parsing_exception::avoid_parsing_exception() :
//   m_bAvoidParsingExceptionPrevious(get_avoid_parsing_exception())
//{
//
//   set_avoid_parsing_exception(true);
//
//}
//
//avoid_parsing_exception::~avoid_parsing_exception()
//{
//
//   set_avoid_parsing_exception(m_bAvoidParsingExceptionPrevious);
//
//}





network_payload_parsing_exception::network_payload_parsing_exception(const ::scoped_string & scopedstrMessage) :
   parsing_exception(scopedstrMessage)
{

   information("parsing_exception");

}


network_payload_parsing_exception::~network_payload_parsing_exception()
{

}



CLASS_DECL_ACME bool throw_network_payload_parsing_exception(const ::scoped_string & scopedstrMessage)
{

   if (should_avoid_parsing_exception())
   {

      return false;

   }

   throw ::exception(error_network_payload_parsing, scopedstrMessage);

   return true;

}
