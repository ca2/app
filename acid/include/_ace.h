// Created by camilo <3ThomasBorregaardSorensen!!
//  ace_ace.h
//
//


#if defined(_ace_project)
#define CLASS_DECL_ACID  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_ACID  CLASS_DECL_IMPORT
#endif

#pragma once


#ifdef UNIVERSAL_WINDOWS
#define INLINE_CLASS_DECL_ACID CLASS_DECL_ACID
#else
#define INLINE_CLASS_DECL_ACID
#endif


#ifdef __OBJC__


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#if defined(__cplusplus)


#define __OBJECTIVE_CPP__

#define __PARTIAL_CPP

#else


#define __OBJECTIVE_C__


#endif


#endif


#ifdef __cplusplus_winrt


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#endif


#ifndef NON_CONVERGING_LANG_IS_TERMINAL_LANG


#define ace_LANGUAGE


#endif









#ifdef ace_LANGUAGE


#if defined(__cplusplus)


#define cplusplus


#else


#define cplus


#endif


#endif


#define __IDENTIFIER_CONCATENATE(a, b) a##b

#define __IDENTIFIER(a) a

#define IDENTIFIER_CONCATENATE(a, b) __IDENTIFIER_CONCATENATE(a,b)

#define IDENTIFIER_SUFFIX_OPERATING_SYSTEM(a) IDENTIFIER_CONCATENATE(__IDENTIFIER(a), __IDENTIFIER(OPERATING_SYSTEM_NAMESPACE))

#define IDENTIFIER_PREFIX_OPERATING_SYSTEM(a) IDENTIFIER_CONCATENATE(__IDENTIFIER(OPERATING_SYSTEM_NAMESPACE), __IDENTIFIER(a))


#define USUAL_OPERATING_SYSTEM_SUPPRESSIONS


#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER)
#define GNU_COMPILER
#endif


#if defined(_MSC_VER) && !defined(__clang__)
#define MICROSOFT_COMPILER
#endif


#if defined(__clang__) && !defined(_MSC_VER) && !defined(__GNUC__)
#define CLANG_COMPILER
#endif


//#include "_start.h"
//#include "_ace.h"
