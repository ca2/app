#pragma once

#include "aura/node/_UWP/_UWP.h"

#define SECURITY_WIN32

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>

//#include "_UWP_exception.h"




#include "_UWP_axis_dir.h"
//#include "_UWP_folder_watch.h"
#include "_UWP_factory_exchange.h"
//#include "_UWP_uac_tools.h"
//#include "_UWP_window_draw.h"
//#include "_UWP_thread.h"
//#include "_UWP_interaction_impl.h"
#include "_UWP_port_forward.h"
//#include "_UWP_file.h"
//#include "_UWP_stdio_file.h"
//#include "_UWP_file_set.h"
#include "_UWP_axis_file_system.h"
//#include "_UWP_os.h"
#include "_UWP_ip_enum.h"
//
//#define NULL_REF(class) (*((class *) nullptr))
////CLASS_DECL_AXIS WNDPROC __get_window_procedure();
//#define __window_procedure (*__get_window_procedure())
//
//#define WIN_THREAD(pthread) (dynamic_cast < ::_UWP::thread * > (dynamic_cast < ::thread * >(pthread)))
//#define WIN_WINDOW(pwnd) (dynamic_cast < ::_UWP::window * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))
//#define _UWP_DC(pgraphics) (dynamic_cast < ::_UWP::graphics * > (pgraphics))
//#define _UWP_BITMAP(pbitmap) (dynamic_cast < ::_UWP::bitmap * > (pbitmap))
//#define _UWP_PEN(ppen) (dynamic_cast < ::_UWP::pen * > (ppen))
//#define _UWP_BRUSH(pbrush) (dynamic_cast < ::_UWP::brush * > (pbrush))
//#define _UWP_PATH(ppath) (dynamic_cast < ::_UWP::graphics_path * > (ppath))
//#define _UWP_FONT(pfont) (dynamic_cast < ::_UWP::font * > (pfont))
//#define SP_DC(pgraphics) (dynamic_cast < ::_UWP::graphics * > (( ::draw2d::graphics * )(pgraphics)))
//#define WIN_DIB(pimage) (dynamic_cast < ::_UWP::image_pointer * > (dynamic_cast < ::image_pointer >(pimage)))
//
//
//
//CLASS_DECL_AXIS void __trace_message(const char * pszPrefix, ::message::message * pmessage);

//CLASS_DECL_AXIS void __trace_message(const char * pszPrefix, LPMESSAGE lpmsg);

//
//CLASS_DECL_AXIS bool __cdecl __is_idle_message(::message::message * pmessage);
//CLASS_DECL_AXIS bool __cdecl __is_idle_message(MESSAGE * pMsg);
//
//
//CLASS_DECL_AXIS void __process_window_procedure_exception(::exception::exception*, ::message::message * pmessage);
//CLASS_DECL_AXIS void __cdecl __pre_translate_message(::message::message * pmessage);
//
//#include "_UWP_copydesk.h"
#include "_UWP_crypto.h"
//
//#include "_UWP_printer.h"
//
//#include "_UWP_application.h"
//
//
//#include "_UWP_directx.h"
//#include "_UWP_directx_application.h"




#define SECURITY_WIN32

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>



//#include "_UWP_message_queue.h"


string get_error_message(DWORD dwError);


#include "_UWP_factory_exchange.h"
//#include "_UWP_window_draw.h"
//#include "_UWP_interaction_impl.h"

//#include "axis/node/windows/windows_message_queue.h"

#define NULL_REF(class) (*((class *) nullptr))
//CLASS_DECL_AXIS WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

//#define WIN_THREAD(pthread) (dynamic_cast < ::_UWP::thread * > (dynamic_cast < ::thread * >(pthread)))
#define WIN_WINDOW(pwnd) (dynamic_cast < ::_UWP::interaction_impl * > (dynamic_cast < ::user::interaction_impl * >(pwnd)))
//#define _UWP_DC(pgraphics) (dynamic_cast < ::_UWP::graphics * > (pgraphics))
//#define _UWP_BITMAP(pbitmap) (dynamic_cast < ::_UWP::bitmap * > (pbitmap))
//#define _UWP_PEN(ppen) (dynamic_cast < ::_UWP::pen * > (ppen))
//#define _UWP_BRUSH(pbrush) (dynamic_cast < ::_UWP::brush * > (pbrush))
//#define _UWP_PATH(ppath) (dynamic_cast < ::_UWP::graphics_path * > (ppath))
//#define _UWP_FONT(pfont) (dynamic_cast < ::_UWP::font * > (pfont))
//#define SP_DC(pgraphics) (dynamic_cast < ::_UWP::graphics * > (( ::draw2d::graphics * )(pgraphics)))
/*#define WIN_DIB(pimage) (dynamic_cast < ::_UWP::image_pointer * > (dynamic_cast < ::image_pointer >(pimage)))



//CLASS_DECL_AXIS void __trace_message(const char * pszPrefix, ::message::message * pmessage);

//CLASS_DECL_AXIS void __trace_message(const char * pszPrefix, LPMESSAGE lpmsg);


//CLASS_DECL_AXIS bool __cdecl __is_idle_message(::message::message * pmessage);
//CLASS_DECL_AXIS bool __cdecl __is_idle_message(MESSAGE * pMsg);


CLASS_DECL_AXIS void __process_window_procedure_exception(::exception::exception*,::message::message * pmessage);
CLASS_DECL_AXIS void __cdecl __pre_translate_message(::message::message * pmessage);

#include "_UWP_copydesk.h"




//#include "_UWP_directx.h"
//#include "_UWP_directx_application.h"


//#include "_UWP_native_buffer.h" #include "_UWP_native_buffer.cpp" // soon, to aura library 2015-07-17 20:06 Livecoding(.tv)


