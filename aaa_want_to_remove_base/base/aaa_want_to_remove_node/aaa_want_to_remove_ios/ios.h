#pragma once


#include "app/axis/axis/axis/axis.h"

#include "app/axis/axis/node/ios/ios.h"


////#define CLASS_DECL_AURA

//struct plane_system
//{
//   
//   ::plane::system *    m_psystem;
//   
//   plane_system(const char * pszId);
//   
//   UIWindow * init_part_2ex(CGRect rect);
//   
//   void begin();
//   
//};


string get_error_message(DWORD dwError);

::aura::application *     ios_instantiate_application(::aura::application * pappSystem, const char * pszId);


#include "ios_implementation.h"
//#include "ios_dir.h"
#include "ios_factory_exchange.h"
//#include "ios_window_draw.h"
//#include "ios_thread.h"
//#include "ios_interaction_impl.h"
//#include "ios_os.h"
//#include "ios_port_forward.h"
//#include "ios_copydesk.h"
//#include "ios_crypto.h"
//#include "ios_ip_enum.h"
#define IOS_WINDOW(pwnd) (dynamic_cast < ::ios::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))


CLASS_DECL_BASE void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);
CLASS_DECL_BASE void __cdecl __pre_translate_message(::message::message * pmessage);

//#include "ios_printer.h"

//#include "ios_application.h"



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

