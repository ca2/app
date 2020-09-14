#pragma once


#include "_.h"
#define PCRE2_CODE_UNIT_WIDTH 8
#ifdef CUBE
#define PCRE2_STATIC
#endif

#ifdef __APPLE__
#include <pcre/pcre2.h>
#else
#include <pcre2.h>
#endif



#include "context_impl.h"
#include "code_impl.h"
#include "util_impl.h"

