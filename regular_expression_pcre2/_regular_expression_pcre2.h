#pragma once


//#include "acme/regular_expression/_regular_expression.h"


#define PCRE2_CODE_UNIT_WIDTH 8
#ifdef CUBE
#define PCRE2_STATIC
#endif

#ifdef __APPLE__
#include <pcre/pcre2.h>
#else
// apt install libpcre2-dev
#include <pcre2.h>
#endif


namespace regular_expression_pcre2
{


   class context;


} // namespace regular_expression_pcre2


#include "context.h"


#include "regular_expression.h"


#include "topic.h"



//#include "code_impl.h"
//#include "context_impl.h"
//#include "util_impl.h"

