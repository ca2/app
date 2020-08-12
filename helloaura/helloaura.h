#pragma once


#include "aura/.h"


#ifdef _APP_CORE_HELLOAURA_LIBRARY
#define CLASS_DECL_APP_CORE_HELLOAURA  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_HELLOAURA  CLASS_DECL_IMPORT
#endif


namespace helloaura
{

   class application;

} // namespace flag


#define APP_TYPE ::helloaura::application


#include "helloaura_render.h"


#include "helloaura_application.h"

