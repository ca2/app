#include "framework.h"
#include "acme/constant/id.h"



//datetime_parsing_exception::datetime_parsing_exception(const ::string & strMessage):
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

CLASS_DECL_CA2_TIME bool throw_datetime_parsing_exception(const ::string & strMessage)
{

   if (should_avoid_datetime_parsing_exception())
   {

      return false;

   }

   throw ::exception(error_datetime_parser, strMessage);

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
