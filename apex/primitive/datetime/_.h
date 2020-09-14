#pragma once








//#include "value.h"
//
//
namespace datetime
{


   CLASS_DECL_APEX string to_string(::layered * pobjectContext, const ::apex::str_context * pcontext, const ::datetime::value & value);


   CLASS_DECL_APEX value span_strtotime(::layered * pobjectContext, const ::apex::str_context * pcontext, const char * psz);
   CLASS_DECL_APEX value strtotime(::layered * pobjectContext, const ::apex::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);


} // namespace datetime
//
//
//extern "C" CLASS_DECL_APEX time_t timegm(struct tm *tmp);
//extern "C" CLASS_DECL_APEX int c_localtime_offset();
//

#include "department.h"



