#pragma once


#define __DEBUG_POWER


#include "platform/platform/config.h"


#if defined(__cplusplus)


#define 	   extern "C"
#define 		extern "C" {
#define 		   }


#else


#define 
#define 
#define 


#endif



#ifdef _DEBUG

#ifndef _DEBUG

#define _DEBUG

#endif

#endif

#ifdef _DEBUG

// Mummi: Good Good (GUDDO GUDDO) - [Gato Guri Gato],[Gato Guri Gato]

// #define __DEBUG

// #ifndef DEBUG

// #define DEBUG

// #endif

// #else

// #define NNDEBUG

// #endif

// enable debug at release for debugging release
#define XXDEBUG

#ifdef _ACID_LIBRARY
#define CLASS_DECL_ACE
#elif defined(_APP_ACE_SHARED)
#define CLASS_DECL_ACE CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACE CLASS_DECL_IMPORT
#endif

#if defined(_ACID_LIBRARY)
#define CLASS_DECL_AURA
#elif defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif



