///TBS__<3tbs
#pragma once


#include "aqua/_.h"


#if defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif


#define CA2_AURA


#ifdef __cplusplus


namespace aura
{


   class history;
   class application;
   class session;
   class system;


} // namespace aura


#undef SYSTEM_TYPE
#define SYSTEM_TYPE ::aura::system

#undef SESSION_TYPE
#define SESSION_TYPE ::aura::session

#undef APP_TYPE
#define APP_TYPE ::aura::application


#endif


#include "aura/node/operating_system/operating_system.h"


#include "aura/include/_include.h"



