#include "framework.h"


thread_int_ptr < int_ptr > t_iAvoidDatetimeParserException;


datetime_parser_exception::datetime_parser_exception(::aura::application * papp,const string & strMessage):
::object(papp),
::call_stack(get_app()),
::exception::base(get_app()),
simple_exception(papp,strMessage)
{

}

datetime_parser_exception::~datetime_parser_exception()
{

}


CLASS_DECL_CA2_TIME bool get_avoid_datetime_parser_exception()
{

   return t_iAvoidDatetimeParserException != FALSE;

}

CLASS_DECL_CA2_TIME bool throw_datetime_parser_exception(const string & strMessage)
{

   if(get_avoid_datetime_parser_exception())
      return false;

   _throw(datetime_parser_exception(get_app(),strMessage));

   return true;

}



avoid_datetime_parser_exception::avoid_datetime_parser_exception()
{

   m_iBefore = t_iAvoidDatetimeParserException;

   t_iAvoidDatetimeParserException = TRUE;

}

avoid_datetime_parser_exception::~avoid_datetime_parser_exception()
{

   t_iAvoidDatetimeParserException = m_iBefore;

}


