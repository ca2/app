//
//  object_reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/06/20.
//
#pragma once


#define __FUNCTION_LINE_STRING__  string(__FUNCTION__) + (" (" STRINGFY(__LINE__) ")")


class object_reference_count_debug;


#if OBJECT_REFERENCE_COUNT_DEBUG
//#define OBJECT_REFERENCE_COUNT_DEBUG_MAX_COUNT 256
#define OBJECT_REFERENCE_COUNT_DEBUG_ARGS pReferer, pszObjRefDbg
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS , OBJECT_REFERENCE_COUNT_DEBUG_ARGS
#define REF_DBG_POINTER (::matter *)(::iptr)1
#define REF_DBG_VAR (::matter *)(::iptr)1
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF ::matter * pReferer, const char *pszObjRefDbg
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS ::matter * pReferer = ((::matter*)(::iptr)1), const char *pszObjRefDbg = nullptr
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF , OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS , OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE(note) , note
#define OBJECT_REFERENCE_COUNT_DEBUG_PTR(ptr) ptr
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS ((::matter *) this)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS , OBJECT_REFERENCE_COUNT_DEBUG_THIS
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(note) ((::matter *) this), note
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE( __FUNCTION_LINE_STRING__ )
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE(note) , OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(note)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE , OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE
#define OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pReferer, note) pReferer, note
#define OBJECT_REFERENCE_COUNT_DEBUG_P_FUNCTION_LINE(pReferer) OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pReferer, __FUNCTION_LINE_STRING__ )
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(pReferer, note) , OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pReferer, note)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(pReferer) OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(pReferer, __FUNCTION_LINE_STRING__ )
#define tracking_assign(target, ...) object_reference_count_debug_assign(target, __VA_ARGS__ )
#define tracking_note_assign(target, source, ... ) object_reference_count_debug_assign(target, source,  __VA_ARGS__ )
#define tracking_named_release(...) object_reference_count_debug_release( __VA_ARGS__ )
#define tracking_check_pending_releases(x) x->object_reference_count_debug_check_pending_releases()
#else
#define OBJECT_REFERENCE_COUNT_DEBUG_ARGS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS
#define OBJECT_REFERENCE_COUNT_DEBUG_PTR(ptr)
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE(note)
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(note)
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_NOTE(note)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE
#define REF_DBG_COMMA_POINTER
#define OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(pReferer, note)
#define OBJECT_REFERENCE_COUNT_DEBUG_P_FUNCTION_LINE(pReferer)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(pReferer, note)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_FUNCTION_LINE(pReferer)
#define tracking_assign(target, source) target = source
#define tracking_note_assign(target, source, note) target = source
#define tracking_named_release(x) ::release(x)
#define tracking_check_pending_releases(x)
#endif



