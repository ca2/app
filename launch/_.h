#pragma once


#include "acme/_.h"



#if defined(_launch_project)
#define CLASS_DECL_LAUNCH  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_LAUNCH  CLASS_DECL_IMPORT
#endif



namespace launch
{


   class application;

   class launch;


} // namespace launch



