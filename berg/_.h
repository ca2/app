///TBS__<3tbs
#pragma once


#include "axis/_.h"


#undef PLATFORM_LAYER_NAME
#define PLATFORM_LAYER_NAME berg


#if defined(_berg_project)
#define CLASS_DECL_BERG  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_BERG  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


#include "berg/include/_include.h"


namespace filemanager
{


   class document;


} // namespace filemanager



