// Created by camilo <3ThomasBorregaardSorensen!!
//  acme_acme.h
//
//


#if defined(_acme_project)
#define CLASS_DECL_ACME  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_ACME  CLASS_DECL_IMPORT
#endif

#pragma once


#if defined(_MSC_VER) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#define MS_COMPILER _MSC_VER
#endif


#ifdef UNIVERSAL_WINDOWS
#define INLINE_CLASS_DECL_ACME CLASS_DECL_ACME
#else
#define INLINE_CLASS_DECL_ACME
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


#define ACME_LANGUAGE


#endif






#ifdef ACME_LANGUAGE


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


#if defined(__clang__)

//#error "__clang__"

#if defined(__has_feature)

//#error "__has_feature"

//#include <sanitizer/asan_interface.h>

#if __has_feature(address_sanitizer)

//#error "address_sanitizer"

#define __ADDRESS_SANITIZER__

#endif

#endif

#elif defined(__GNUC__)

#ifdef __SANITIZE_ADDRESS__

#define __ADDRESS_SANITIZER__

#endif

#endif



