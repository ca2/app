#pragma once


#include "core/_.h"


#if defined(_app_build_project)
#define CLASS_DECL_APP_BUILD  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_BUILD  CLASS_DECL_IMPORT
#endif



namespace app_build
{


   class pane_impact;
   class impact;
   class document;


   class application;


} // namespace app_build



