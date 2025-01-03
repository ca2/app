//
//  reference_count_debug.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//

#pragma once


class reference_count_debug;

#define _MAKE_STRING(identifier) #identifier
#define MAKE_STRING(identifier) _MAKE_STRING(identifier)
//#define MAKE_STRING(x, y) TOKEN_CONCATENATE(x, y)
//#define UNIQUE static void TOKENPASTE2(Unique_, __LINE__)(void) {}

#if REFERENCING_DEBUGGING
//#define REFERENCING_DEBUGGING_MAX_COUNT 256
#define  p, pszObjRefDbg
#define , 
#define REF_DBG_POINTER (::matter *)(::iptr)1
#define REF_DBG_VAR (::matter *)(::iptr)1
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
#define  ::matter * p, const char *pszObjRefDbg
#define  ::matter * p = ((::matter*)(::iptr)1), const char *pszObjRefDbg = nullptr
#define , 
#define , 
#define REFERENCING_DEBUGGING_COMMA_NOTE(note) , note
#define REFERENCING_DEBUGGING_PTR(ptr) ptr
#define  ((::matter *) this)
#define REFERENCING_DEBUGGING_COMMA_THIS , 
#define REFERENCING_DEBUGGING_THIS_NOTE(note) ((::matter *) this), note
#define REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE REFERENCING_DEBUGGING_THIS_NOTE( __FUNCTION__ " (" MAKE_STRING(__LINE__) ")" )
#define REFERENCING_DEBUGGING_COMMA_THIS_NOTE(note) , REFERENCING_DEBUGGING_THIS_NOTE(note)
#define REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE , REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE
#define REFERENCING_DEBUGGING_P_NOTE(p, note) p, note
#define REFERENCING_DEBUGGING_COMMA_P_NOTE(p, note) , REFERENCING_DEBUGGING_P_NOTE(p, note)
#define __assign(target, source) ___assign(target, source)
#define __note_assign(target, source, note) ___assign(target, source, note)
#define __named_release(x) ___release(x)
#define __check_pending_releases(x) x->check_pending_releases()
#else
#define 
#define
#define
#define
#define 
#define 
#define REFERENCING_DEBUGGING_PTR(ptr)
#define 
#define REFERENCING_DEBUGGING_COMMA_NOTE(note)
#define REFERENCING_DEBUGGING_THIS_NOTE(note)
#define REF_DBG_COMMA_POINTER
#define REFERENCING_DEBUGGING_P_NOTE(p, note)
#define REFERENCING_DEBUGGING_COMMA_P_NOTE(p, note)
#define __assign(target, source) target = source
#define __note_assign(target, source, note) target = source
#define __named_release(x) ::release(x)
#define __check_pending_releases(x)
#endif
