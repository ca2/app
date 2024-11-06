#pragma once


//#include "ace/_ace.h"


//#ifndef CLASS_DECL_APEX
//
//#define CLASS_DECL_APEX
//
//#endif
//

#ifdef __cplusplus

CLASS_DECL_APEX void c_post_system_event(huge_natural u, void * pparam = 0);

#else

CLASS_DECL_APEX void c_post_system_event(huge_integer iId, void * pparam);

#endif



