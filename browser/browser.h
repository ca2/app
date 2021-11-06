#pragma once


#include "aura/_.h"
#include "app-core/gcom/gcom/gcom.h"


#ifdef _APP_BROWSER_LIBRARY
#define CLASS_DECL_APP_BROWSER  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_BROWSER  CLASS_DECL_IMPORT
#endif


namespace user
{


   typedef ::user::show < ::user::button > button_view;


} // namespace user



namespace browser
{

   class application;
   class main_impact;
   class document;
   class impact;

} // namespace flag


#undef APP_TYPE
#define APP_TYPE ::browser::application


#include "browser_render.h"

#include "browser_document.h"
#include "browser_view_base.h"
#include "browser_gcom.h"
#include "browser_view.h"
#include "browser_main_view.h"
#include "browser_switcher_view.h"
#include "browser_frame.h"
#include "browser_main_frame.h"

#include "browser_pane_view.h"

#include "browser_application.h"



