#pragma once


#include "app/helloaura/helloaura.h"
#include "axis/axis/axis.h"



#if defined(_app_core_helloaxis_project)
#define CLASS_DECL_APP_CORE_HELLOAXIS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_HELLOAXIS  CLASS_DECL_IMPORT
#endif


namespace helloaxis
{

   class application;

} // namespace flag


#define APP_TYPE ::helloaxis::application


#include "helloaxis_render.h"


#include "helloaxis_application.h"

