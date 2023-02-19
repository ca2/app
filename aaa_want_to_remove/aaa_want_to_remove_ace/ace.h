#pragma once


#include "_ace.h"


// #ifdef _DEBUG

// #ifndef _DEBUG

// #define _DEBUG

// #endif

// #endif

// #ifdef _DEBUG

// #define __DEBUG

// #ifndef DEBUG

// #define DEBUG

// #endif

// #else

// #define NNDEBUG

// #endif

// enable debug at release for debugging release
#define XXDEBUG

#if defined(_acid_project)
#define CLASS_DECL_ACE
#elif defined(_APP_ACE_SHARED)
#define CLASS_DECL_ACE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACE CLASS_DECL_IMPORT
#endif

#if defined(_acid_project)
#define CLASS_DECL_AURA
#elif defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif



#include "ace_alloc.h"


#define _(c_string_to_be_translated_from_english) c_string_to_be_translated_from_english


#ifdef MACOS

#include "macos.h"

#endif













