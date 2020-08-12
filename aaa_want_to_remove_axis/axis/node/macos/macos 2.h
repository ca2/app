#pragma once


#include "aura/node/macos/macos.h"


string get_error_message(DWORD dwError);

::aura::application *     mac_instantiate_application(::aura::application * pappSystem, const char * pszId);


#include "macos_factory_exchange.h"
#include "macos_window_draw.h"
#include "macos_interaction_impl.h"
#include "macos_copydesk.h"



// xxx CLASS_DECL_AXIS WNDPROC AfxGetAfxWndProc();
#define AfxWndProc (*AfxGetAfxWndProc())

#define MAC_WINDOW(pwnd) (dynamic_cast < ::macos::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))


CLASS_DECL_AXIS void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);
CLASS_DECL_AXIS void __cdecl __pre_translate_message(::message::message * pmessage);
#include "macos_printer.h"
#include "macos_message_queue.h"



i32 CLASS_DECL_AXIS __mac_main(i32 argc, char * argv[]);




#include "round_window.h"




