//
//  obj_ref_dbg.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 20/06/20.
//

#pragma once

#define _STRINGFY(identifier) #identifier
#define STRINGFY(identifier) _STRINGFY(identifier)
#define __FUNCTION_LINE__  __FUNCTION__ " (" STRINGFY(__LINE__) ")"

class obj_ref_dbg;

//#define STRINGFY(x, y) TOKENPASTE(x, y)
//#define UNIQUE static void TOKENPASTE2(Unique_, __LINE__)(void) {}

#if OBJ_REF_DBG
//#define OBJ_REF_DBG_MAX_COUNT 256
#define OBJ_REF_DBG_ARGS pReferer, pszObjRefDbg
#define OBJ_REF_DBG_ADD_ARGS , OBJ_REF_DBG_ARGS
#define REF_DBG_POINTER (::matter *)(::iptr)1
#define REF_DBG_VAR (::matter *)(::iptr)1
#define REF_DBG_ADD_POINTER , REF_DBG_POINTER
#define OBJ_REF_DBG_PARAMS_DEF ::matter * pReferer, const char *pszObjRefDbg
#define OBJ_REF_DBG_PARAMS ::matter * pReferer = ((::matter*)(::iptr)1), const char *pszObjRefDbg = nullptr
#define OBJ_REF_DBG_ADD_PARAMS_DEF , OBJ_REF_DBG_PARAMS_DEF
#define OBJ_REF_DBG_ADD_PARAMS , OBJ_REF_DBG_PARAMS
#define OBJ_REF_DBG_ADD_NOTE(note) , note
#define OBJ_REF_DBG_PTR(ptr) ptr
#define OBJ_REF_DBG_THIS ((::matter *) this)
#define OBJ_REF_DBG_ADD_THIS , OBJ_REF_DBG_THIS
#define OBJ_REF_DBG_THIS_NOTE(note) ((::matter *) this), note
#define OBJ_REF_DBG_THIS_FUNCTION_LINE OBJ_REF_DBG_THIS_NOTE(__FUNCTION_LINE__ )
#define OBJ_REF_DBG_ADD_THIS_NOTE(note) , OBJ_REF_DBG_THIS_NOTE(note)
#define OBJ_REF_DBG_ADD_THIS_FUNCTION_LINE , OBJ_REF_DBG_THIS_FUNCTION_LINE
#define OBJ_REF_DBG_P_NOTE(pReferer, note) pReferer, note
#define OBJ_REF_DBG_P_FUNCTION_LINE(pReferer) OBJ_REF_DBG_P_NOTE(pReferer, __FUNCTION_LINE__)
#define OBJ_REF_DBG_ADD_P_NOTE(pReferer, note) , OBJ_REF_DBG_P_NOTE(pReferer, note)
#define OBJ_REF_DBG_ADD_P_FUNCTION_LINE(pReferer) OBJ_REF_DBG_ADD_P_NOTE(pReferer, __FUNCTION_LINE__)
#define __assign(target, source) ___assign(target, source)
#define __note_assign(target, source, note) ___assign(target, source, note)
#define __named_release(x) ___release(x)
#define __check_pending_releases(x) x->check_pending_releases()
#else
#define OBJ_REF_DBG_ARGS
#define OBJ_REF_DBG_ADD_ARGS
#define OBJ_REF_DBG_ADD_PARAMS
#define OBJ_REF_DBG_ADD_PARAMS_DEF
#define OBJ_REF_DBG_PARAMS_DEF
#define OBJ_REF_DBG_PARAMS
#define OBJ_REF_DBG_PTR(ptr)
#define OBJ_REF_DBG_THIS
#define OBJ_REF_DBG_ADD_NOTE(note)
#define OBJ_REF_DBG_THIS_NOTE(note)
#define REF_DBG_ADD_POINTER
#define OBJ_REF_DBG_P_NOTE(p, note)
#define OBJ_REF_DBG_ADD_P_NOTE(p, note)
#define __assign(target, source) target = source
#define __note_assign(target, source, note) target = source
#define __named_release(x) ::release(x)
#define __check_pending_releases(x)
#endif

