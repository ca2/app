#include "framework.h"
#include "aura/const/id.h"


//thread_int_ptr < iptr > t_iAvoidDatetimeParserException;


datetime_parser_exception::datetime_parser_exception(const string & strMessage):
   ::exception::exception(strMessage)
{

}

datetime_parser_exception::~datetime_parser_exception()
{

}


CLASS_DECL_CA2_TIME bool get_avoid_datetime_parser_exception()
{

   return thread_is_set(id_thread_avoid_datetime_parser_exception);

}

CLASS_DECL_CA2_TIME bool throw_datetime_parser_exception(const string & strMessage)
{

   if(get_avoid_datetime_parser_exception())
      return false;

   __throw(datetime_parser_exception(strMessage));

   return true;

}



avoid_datetime_parser_exception::avoid_datetime_parser_exception()
{

   m_iBefore = thread_value(id_thread_avoid_datetime_parser_exception);

   thread_set(id_thread_avoid_datetime_parser_exception);

}

avoid_datetime_parser_exception::~avoid_datetime_parser_exception()
{

   thread_value(id_thread_avoid_datetime_parser_exception) = m_iBefore;

}


