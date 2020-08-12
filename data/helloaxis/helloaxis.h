#pragma once


#include "axis/axis/axis.h"


#ifdef _APP_CORE_HELLOAXIS_LIBRARY
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

