#pragma once








#include "value.h"


//namespace datetime
//{
//
//
//   CLASS_DECL_ACME string to_string(::elemental * pobject, const ::acme::str_context * pcontext, const ::datetime::value & value);
//
//
//   CLASS_DECL_ACME value span_strtotime(::elemental * pobject, const ::acme::str_context * pcontext, const char * psz);
//   CLASS_DECL_ACME value strtotime(::elemental * pobject, const ::acme::str_context * pcontext, const char * psz, i32 & iPath, i32 & iPathCount, bool bForceUTC = false);
//
//
//} // namespace datetime


extern "C" CLASS_DECL_ACME time_t timegm(struct tm *tmp);
extern "C" CLASS_DECL_ACME int c_localtime_offset();


//#include "department.h"



