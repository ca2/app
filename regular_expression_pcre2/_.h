#pragma once


#include "acme/_.h"


#define PCRE2_CODE_UNIT_WIDTH 8
#ifdef CUBE
#define PCRE2_STATIC
#endif


#include <pcre2.h>


#ifdef _REGULAR_EXPRESSION_PCRE2_LIBRARY
#define CLASS_DECL_REGULAR_EXPRESSION_PCRE2  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_REGULAR_EXPRESSION_PCRE2  CLASS_DECL_IMPORT
#endif



