#include "framework.h"
#include "aura/id.h"



//datetime_parser_exception::datetime_parser_exception(const ::string & strMessage):
//::exception(strMessage)
//{
//
//}
//
//datetime_parser_exception::~datetime_parser_exception()
//{
//
//}


CLASS_DECL_CA2_TIME bool get_avoid_datetime_parser_exception()
{

   return ::get_task()->payload(id_thread_avoid_datetime_parser_exception).is_true();

}

CLASS_DECL_CA2_TIME bool throw_datetime_parser_exception(const ::string & strMessage)
{

   if (get_avoid_datetime_parser_exception())
   {

      return false;

   }

   __throw(error_datetime_parser, strMessage);

   return true;

}



avoid_datetime_parser_exception::avoid_datetime_parser_exception()
{

   m_bBefore = get_avoid_datetime_parser_exception();

   ::get_task()->payload(id_thread_avoid_datetime_parser_exception) = true;

}

avoid_datetime_parser_exception::~avoid_datetime_parser_exception()
{

   ::get_task()->payload(id_thread_avoid_datetime_parser_exception) = m_bBefore;

}


