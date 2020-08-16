#pragma once


#include "aura/node/linux/_.h"


#include "port_forward.h"
#include "ip_enum.h"




CLASS_DECL_AXIS void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);
CLASS_DECL_AXIS void __cdecl __pre_translate_message(::message::message * pmessage);


WINBOOL PeekMessage(
LPMESSAGE lpMsg,
oswindow hWnd,
UINT wMsgFilterMin,
UINT wMsgFilterMax,
UINT wRemoveMsg);

WINBOOL GetMessage(
LPMESSAGE lpMsg,
oswindow hWnd,
UINT wMsgFilterMin,
UINT wMsgFilterMax);



#include "copydesk.h"


#include "factory_exchange.h"



