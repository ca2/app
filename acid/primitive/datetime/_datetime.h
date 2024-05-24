#pragma once


#ifdef __DEBUG


CLASS_DECL_ACID dump_context & operator <<(dump_context & dumpcontext, ::earth::time time);
CLASS_DECL_ACID dump_context & operator <<(dump_context & dumpcontext, ::earth::time_span time);


#endif


//#include "acid/primitive/datetime/second.h"
//
//
//#include "acid/primitive/datetime/class ::time.h"
//
//
//#include "acid/primitive/datetime/microsecond.h"
//
//
//#include "acid/primitive/datetime/nanosecond.h"
//
//
//
//#include "acid/primitive/datetime/time.h"


class file_time;



#include "acid/primitive/datetime/date_span.h"
#include "acid/primitive/datetime/time_span.h"
////#include "acid/primitive/datetime/earth_time.h"
#include "acid/primitive/datetime/zonetime.h"
#include "acid/primitive/datetime/file_time_span.h"
//#include "acid/primitive/datetime/file_time.h"


//#include "acid/primitive/datetime/time_zone.h"



//#include "department.h"



