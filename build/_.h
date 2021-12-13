#pragma once


#include "core/_.h"



#ifdef _APP_CORE_BUILD_LIBRARY
#define CLASS_DECL_APP_CORE_BUILD  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_BUILD  CLASS_DECL_IMPORT
#endif


namespace app_core_build
{

   class application;
   class main_impact;
   class document;
   class impact;
   class pane_view;

} // namespace flag


#undef APP_TYPE
#define APP_TYPE ::hellomultiverse::application



