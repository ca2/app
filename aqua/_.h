///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "apex/_.h"
#ifdef	_STDIO_H_
#error "already included?!?! WHAT?!?! (At aqua:a)"
#endif


#if defined(_aqua_project)
#define CLASS_DECL_AQUA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AQUA  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


#include "aqua/include/_include.h"



