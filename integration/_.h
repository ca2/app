#pragma once


#include "base/_.h"


#ifdef _APP_INTEGRATION_LIBRARY
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

