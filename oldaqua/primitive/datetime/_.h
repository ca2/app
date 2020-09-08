#pragma once








#include "value.h"


namespace datetime
{


   CLASS_DECL_AQUA string to_string(::object * pobject, const ::aqua::str_context * pcontext, const ::datetime::value & value);


   CLASS_DECL_AQUA value span_strtotime(::object * pobject, const ::aqua::str_context * pcontext, const char * psz);
   CLASS_DECL_AQUA value strtotime(::object * pobject, const ::aqua::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);


} // namespace datetime


extern "C" CLASS_DECL_AQUA time_t timegm(struct tm *tmp);
extern "C" CLASS_DECL_AQUA int c_localtime_offset();


#include "department.h"



