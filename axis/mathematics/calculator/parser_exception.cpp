#include "framework.h"
#include "acme/constant/id.h"


numeric_parsing_exception::numeric_parsing_exception(const ::string & strMessage):
   ::exception(error_parsing, strMessage)
{

   output_debug_string("numeric_parsing_exception");

}


numeric_parsing_exception::~numeric_parsing_exception()
{

}


bool should_avoid_numeric_parsing_exception()
{

   return task_flag().is_set(e_task_flag_avoid_numeric_parsing_exception);

}


CLASS_DECL_AXIS bool throw_numeric_parsing_exception(const ::string & strMessage)
{

   if (should_avoid_numeric_parsing_exception())
   {

      return false;

   }

   throw numeric_parsing_exception(strMessage);

   return true;

}


//avoid_numeric_parsing_exception::avoid_numeric_parsing_exception()
//{
//
//   task_flag().set(e_task_flag_avoid_numeric_parsing_exception).as(m_iBefore);
//
//   thread_set(id_thread_avoid_numeric_parsing_exception);
//
//}

//avoid_numeric_parsing_exception::~avoid_numeric_parsing_exception()
//{
//
//   thread_property(id_thread_avoid_numeric_parsing_exception) = m_iBefore;
//
//}


