#pragma once


#include "hellobase/hellobase.h"
#include "aura/_.h"
#include "aura/filesystem/filemanager/filemanager.h"
#include "core/user/userex/userex.h"
#include "aura/user/html/html/html.h"


#if defined(_app_helloworld_project)
#define CLASS_DECL_APP_HELLOWORLD  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_HELLOWORLD  CLASS_DECL_IMPORT
#endif


namespace user
{

   typedef ::user::show < ::user::button > button_impact;

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
#include "helloworld_impact_base.h"
#include "helloworld_impact.h"
//#include "helloworld_lite_impact.h"
//#include "helloworld_full_impact.h"
#include "helloworld_main_impact.h"
#include "helloworld_switcher_impact.h"
#include "helloworld_frame.h"
#include "helloworld_main_frame.h"

#include "helloworld_pane_impact.h"

#include "helloworld_application.h"

