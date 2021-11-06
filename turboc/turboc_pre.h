#pragma once

#include <math.h>
#include <time.h>

#ifndef CLASS_DECL_TURBOC
#ifdef _APP_TURBOC_LIBRARY
#define CLASS_DECL_TURBOC  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_TURBOC  CLASS_DECL_IMPORT
#endif
#endif

#define WITH_X

namespace turboc
{


   class application;
   class action_context;


} // namespace turboc


#undef APP_TYPE
#define APP_TYPE ::turboc::application


// cax@ca2
typedef int gint;
#define __BEGIN_DECLS
#define __END_DECLS



//----------------------------------------------------------------------------
// Data types.

// A little toy of my own.
typedef struct
{
   gint r,g,b;
}
RgbStruct;
