#include "framework.h"
#include "acme/constant/id.h"
#include "acme/parallelization/task_flag.h"
////#include "acme/exception/exception.h"


//datetime_parsing_exception::datetime_parsing_exception(const ::scoped_string & scopedstrMessage):
//::exception(strMessage)
//{
//
//}
//
//datetime_parsing_exception::~datetime_parsing_exception()
//{
//
//}


CLASS_DECL_CA2_TIME bool should_avoid_datetime_parsing_exception()
{

   return ::task_flag().is_set(e_task_flag_avoid_datetime_parsing_exception);

}

CLASS_DECL_CA2_TIME bool throw_datetime_parsing_exception(const ::scoped_string & scopedstrMessage)
{

   if (should_avoid_datetime_parsing_exception())
   {

      return false;

   }

   throw ::exception(error_datetime_parser, scopedstrMessage);

   return true;

}


//
//avoid_datetime_parsing_exception::avoid_datetime_parsing_exception()
//{
//
//   m_bBefore = get_avoid_datetime_parsing_exception();
//
//   ::get_task()->payload(id_thread_avoid_datetime_parsing_exception) = true;
//
//}
//
//avoid_datetime_parsing_exception::~avoid_datetime_parsing_exception()
//{
//
//   ::get_task()->payload(id_thread_avoid_datetime_parsing_exception) = m_bBefore;
//
//}
//
//
