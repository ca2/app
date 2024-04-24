///TBS__<3tbs
#pragma once


#include "aqua/_.h"


#if defined(_aura_project)
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


#endif


#include "aura/include/_include.h"



