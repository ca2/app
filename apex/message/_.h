#pragma once


namespace message
{


   class message;

   class mouse;


   class simple_command;
   class command;



   enum e_prototype : int;

   CLASS_DECL_APEX e_prototype get_message_prototype(::enum_message emessage, ::u32 uCode);

   class message;
   //class sender; -> oet,chnel (targetable!!evenmoreeasilykillble (dissolve "bad" idea/group/team, not person));
   //class receiver; -> oyet

   ::u32 translate_to_os_message(const ::atom& atom);


   CLASS_DECL_APEX bool is_idle_message(::message::message * pmessage);


   CLASS_DECL_APEX bool is_idle_message(MESSAGE* pmessage);


} // namespace messagse


#define DECLARE_MESSAGE_HANDLER(function) void function(::message::message * pmessage)


//#include "message.h"



