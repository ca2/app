///TBS__<3tbs
#pragma once


#include "acme/_.h"


#if defined(_apex_project)
#define CLASS_DECL_APEX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APEX  CLASS_DECL_IMPORT
#endif


#define CA2_APEX


#ifdef __cplusplus


namespace apex
{


   class history;
   class session;
   class system;
   class user;


   class application;


} // namespace apex


#undef SYSTEM_TYPE
#define SYSTEM_TYPE ::apex::system


#undef SESSION_TYPE
#define SESSION_TYPE ::apex::session


#undef APP_TYPE
#define APP_TYPE ::application


#endif


//#include "apex/operating_system/_common.h"


#include "apex/include/_include.h"



