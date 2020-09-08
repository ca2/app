#pragma once


namespace message
{

   class message;
   //class sender; -> oet,chnel (targetable!!evenmoreeasilykillble (dissolve "bad" idea/group/team, not person));
   //class receiver; -> oyet

} // namespace message


#define DECL_GEN_SIGNAL(function) void function(::message::message * pmessage)


#include "const.h"
#include "id.h"
#include "receiver.h"
#include "route.h"
#include "message.h"
#include "definition.h"
#include "channel.h"
#include "base.h"
#include "_impl.h"
#include "listener_smart_pointer_array.h"


#ifdef WINDOWS_DESKTOP

#define MESSAGE MSG
#define LPMESSAGE LPMSG

#endif

namespace message
{


   CLASS_DECL_AQUA bool is_idle_message(::message::message * pmessage);


   CLASS_DECL_AQUA bool is_idle_message(MESSAGE* pMsg);


} // namespace message




