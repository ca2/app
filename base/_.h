///TBS__<3tbs
#pragma once


#include "axis/_.h"


#if defined(_base_project)
#define CLASS_DECL_BASE  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_BASE  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


#include "base/include/_include.h"


namespace filemanager
{


   class document;


} // namespace filemanager


//#include "base/user/user/document.h"
//
//
//#include "base/user/user/impact.h"
//
//
//#include "base/user/simple/frame_window.h"






