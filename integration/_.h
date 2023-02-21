#pragma once


#include "base/_.h"


#if defined(_app_integration_project)
#define CLASS_DECL_APP_INTEGRATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_INTEGRATION  CLASS_DECL_IMPORT
#endif


namespace app_integration
{


   class application;
   class tab_impact;
   class document;
   class render;

   class menu;


} // namespace flag

