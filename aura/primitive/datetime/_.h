#pragma once








#include "value.h"


namespace datetime
{


   CLASS_DECL_AURA string to_string(::object * pobject, const ::aura::str_context * pcontext, const ::datetime::value & value);


   CLASS_DECL_AURA value span_strtotime(::object * pobject, const ::aura::str_context * pcontext, const char * psz);
   CLASS_DECL_AURA value strtotime(::object * pobject, const ::aura::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);


} // namespace datetime


extern "C" CLASS_DECL_AURA time_t timegm(struct tm *tmp);
extern "C" CLASS_DECL_AURA int c_localtime_offset();


#include "department.h"



