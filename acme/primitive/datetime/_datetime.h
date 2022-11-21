#pragma once


#ifdef __DEBUG


CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::earth::time time);
CLASS_DECL_ACME dump_context & operator <<(dump_context & dumpcontext, ::earth::time_span time);


#endif


//#include "acme/primitive/datetime/second.h"
//
//
//#include "acme/primitive/datetime/::duration.h"
//
//
//#include "acme/primitive/datetime/microsecond.h"
//
//
//#include "acme/primitive/datetime/nanosecond.h"
//
//
//
//#include "acme/primitive/datetime/duration.h"


class file_time;



#include "acme/primitive/datetime/date_span.h"
#include "acme/primitive/datetime/time_span.h"
////#include "acme/primitive/datetime/earth_time.h"
#include "acme/primitive/datetime/zonetime.h"
#include "acme/primitive/datetime/file_time_span.h"
//#include "acme/primitive/datetime/file_time.h"


//#include "acme/primitive/datetime/time_zone.h"



//#include "department.h"



