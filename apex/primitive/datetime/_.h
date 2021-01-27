#pragma once


namespace datetime
{


   CLASS_DECL_APEX string to_string(::layered * pobjectContext, const ::apex::str_context * pcontext, const ::datetime::result & payload);

   CLASS_DECL_APEX result span_strtotime(::layered * pobjectContext, const ::apex::str_context * pcontext, const char * psz);
   CLASS_DECL_APEX result strtotime(::layered * pobjectContext, const ::apex::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);


} // namespace datetime


#include "department.h"



