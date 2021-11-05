#pragma once


#include "aura/node/linux/_.h"


#include "port_forward.h"
#include "ip_enum.h"




CLASS_DECL_AXIS void AfxProcessWndProcException(::exception*, ::message::message * pmessage);
CLASS_DECL_AXIS void __cdecl __pre_translate_message(::message::message * pmessage);


int_bool PeekMessage(
LPMESSAGE lpMsg,
oswindow hWnd,
::u32 wMsgFilterMin,
::u32 wMsgFilterMax,
::u32 wRemoveMsg);

int_bool GetMessage(
LPMESSAGE lpMsg,
oswindow hWnd,
::u32 wMsgFilterMin,
::u32 wMsgFilterMax);



#include "copydesk.h"


#include "factory_exchange.h"



