#pragma once


#include "aura/_.h"


#ifdef _APP_APP_LIBRARY
#define CLASS_DECL_APP_APP  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_APP  CLASS_DECL_IMPORT
#endif


namespace app_app
{


   class application;
   class main_window;


} // namespace app_app



#undef APPLICATION_CLASS
#define APPLICATION_CLASS ::app_app::application
