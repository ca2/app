//
//  obj_ref_debug.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 20/06/20.
//

#pragma once

#define _STRINGFY(identifier) #identifier
#define STRINGFY(identifier) _STRINGFY(identifier)
#define __FUNCTION_LINE_STRING__  string(__FUNCTION__) + (" (" STRINGFY(__LINE__) ")")

class obj_ref_debug;

//#define STRINGFY(x, y) TOKENPASTE(x, y)
//#define UNIQUE static void TOKENPASTE2(Unique_, __LINE__)(void) {}

#if OBJECT_REF_DEBUG
//#define OBJECT_REF_DEBUG_MAX_COUNT 256
#define OBJECT_REF_DEBUG_ARGS pReferer, pszObjRefDbg
#define OBJECT_REF_DEBUG_COMMA_ARGS , OBJECT_REF_DEBUG_ARGS
#define REF_DBG_POINTER (::matter *)(::iptr)1
#define REF_DBG_VAR (::matter *)(::iptr)1
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
#define OBJECT_REF_DEBUG_PARAMS_DEF ::matter * pReferer, const char *pszObjRefDbg
#define OBJECT_REF_DEBUG_PARAMS ::matter * pReferer = ((::matter*)(::iptr)1), const char *pszObjRefDbg = nullptr
#define OBJECT_REF_DEBUG_COMMA_PARAMS_DEF , OBJECT_REF_DEBUG_PARAMS_DEF
#define OBJECT_REF_DEBUG_COMMA_PARAMS , OBJECT_REF_DEBUG_PARAMS
#define OBJECT_REF_DEBUG_COMMA_NOTE(note) , note
#define OBJECT_REF_DEBUG_PTR(ptr) ptr
#define OBJECT_REF_DEBUG_THIS ((::matter *) this)
#define OBJECT_REF_DEBUG_COMMA_THIS , OBJECT_REF_DEBUG_THIS
#define OBJECT_REF_DEBUG_THIS_NOTE(note) ((::matter *) this), note
#define OBJECT_REF_DEBUG_THIS_FUNCTION_LINE OBJECT_REF_DEBUG_THIS_NOTE( __FUNCTION_LINE_STRING__ )
#define OBJECT_REF_DEBUG_COMMA_THIS_NOTE(note) , OBJECT_REF_DEBUG_THIS_NOTE(note)
#define OBJECT_REF_DEBUG_COMMA_THIS_FUNCTION_LINE , OBJECT_REF_DEBUG_THIS_FUNCTION_LINE
#define OBJECT_REF_DEBUG_P_NOTE(pReferer, note) pReferer, note
#define OBJECT_REF_DEBUG_P_FUNCTION_LINE(pReferer) OBJECT_REF_DEBUG_P_NOTE(pReferer, __FUNCTION_LINE_STRING__ )
#define OBJECT_REF_DEBUG_COMMA_P_NOTE(pReferer, note) , OBJECT_REF_DEBUG_P_NOTE(pReferer, note)
#define OBJECT_REF_DEBUG_COMMA_P_FUNCTION_LINE(pReferer) OBJECT_REF_DEBUG_COMMA_P_NOTE(pReferer, __FUNCTION_LINE_STRING__ )
#define __assign(target, ...) ___assign(target, __VA_ARGS__ )
#define __note_assign(target, source, ... ) ___assign(target, source,  __VA_ARGS__ )
#define __named_release(...) ___release( __VA_ARGS__ )
#define __check_pending_releases(x) x->check_pending_releases()
#else
#define OBJECT_REF_DEBUG_ARGS
#define OBJECT_REF_DEBUG_COMMA_ARGS
#define OBJECT_REF_DEBUG_COMMA_PARAMS
#define OBJECT_REF_DEBUG_COMMA_PARAMS_DEF
#define OBJECT_REF_DEBUG_PARAMS_DEF
#define OBJECT_REF_DEBUG_PARAMS
#define OBJECT_REF_DEBUG_PTR(ptr)
#define OBJECT_REF_DEBUG_THIS
#define OBJECT_REF_DEBUG_THIS
#define OBJECT_REF_DEBUG_COMMA_THIS
#define OBJECT_REF_DEBUG_COMMA_NOTE(note)
#define OBJECT_REF_DEBUG_THIS_NOTE(note)
#define OBJECT_REF_DEBUG_THIS_FUNCTION_LINE
#define OBJECT_REF_DEBUG_COMMA_THIS_NOTE(note)
#define OBJECT_REF_DEBUG_COMMA_THIS_FUNCTION_LINE
#define REF_DBG_COMMA_POINTER
#define OBJECT_REF_DEBUG_P_NOTE(pReferer, note)
#define OBJECT_REF_DEBUG_P_FUNCTION_LINE(pReferer)
#define OBJECT_REF_DEBUG_COMMA_P_NOTE(pReferer, note)
#define OBJECT_REF_DEBUG_COMMA_P_FUNCTION_LINE(pReferer)
#define __assign(target, source) target = source
#define __note_assign(target, source, note) target = source
#define __named_release(x) ::release(x)
#define __check_pending_releases(x)
#endif

