#pragma once


//#include "acme/regular_expression/_regular_expression.h"



//#ifdef __APPLE__
//#include <pcre/pcre2.h>
//#else
// apt install libpcre2-dev
#ifdef __APPLE__
#include "port/pcre2.h"
#else
#include <pcre2.h>
#endif
//#endif


namespace regular_expression_pcre2
{


   class context;


} // namespace regular_expression_pcre2


#include "context.h"


#include "regular_expression.h"


#include "result.h"



