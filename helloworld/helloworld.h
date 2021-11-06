#pragma once


#include "hellobase/hellobase.h"
#include "aura/_.h"
#include "aura/filesystem/filemanager/filemanager.h"
#include "core/user/userex/userex.h"
#include "aura/user/html/html/html.h"


#ifdef _APP_HELLOWORLD_LIBRARY
#define CLASS_DECL_APP_HELLOWORLD  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_HELLOWORLD  CLASS_DECL_IMPORT
#endif


namespace user
{

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace helloworld
{

   class application;
   class main_impact;
   class document;
   class impact;

} // namespace flag


#undef APP_TYPE
#define APP_TYPE ::helloworld::application


#include "helloworld_render.h"

#include "helloworld_document.h"
#include "helloworld_view_base.h"
#include "helloworld_view.h"
//#include "helloworld_lite_view.h"
//#include "helloworld_full_view.h"
#include "helloworld_main_view.h"
#include "helloworld_switcher_view.h"
#include "helloworld_frame.h"
#include "helloworld_main_frame.h"

#include "helloworld_pane_view.h"

#include "helloworld_application.h"

