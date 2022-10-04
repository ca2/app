//
//  object_reference_count_debug.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 20/06/20.
//

#pragma once


class object_reference_count_debug;


#if OBJECT_REFERENCE_COUNT_DEBUG
//#define OBJECT_REFERENCE_COUNT_DEBUG_MAX_COUNT 256
#define OBJECT_REFERENCE_COUNT_DEBUG_ARGS p, pszObjRefDbg
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS , OBJECT_REFERENCE_COUNT_DEBUG_ARGS
#define REF_DBG_POINTER (::matter *)(::iptr)1
#define REF_DBG_VAR (::matter *)(::iptr)1
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF ::matter * p, const ::string &pszObjRefDbg
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS ::matter * p = ((::matter*)(::iptr)1), const ::string &pszObjRefDbg = nullptr
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF , OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS , OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE(note) , note
#define OBJECT_REFERENCE_COUNT_DEBUG_PTR(ptr) ptr
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS ((::matter *) this)
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(note) ((::matter *) this), note
#define OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(p, note) p, note
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(p, note) , OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(p, note)
#define __assign(target, source) ___assign(target, source)
#define __note_assign(target, source, note) ___assign(target, source, note)
#define __named_release(x) ___release(x)
#define __check_pending_releases(x) x->check_pending_releases()
#else
#define OBJECT_REFERENCE_COUNT_DEBUG_ARGS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF
#define OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS
#define OBJECT_REFERENCE_COUNT_DEBUG_PTR(ptr)
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE(note)
#define OBJECT_REFERENCE_COUNT_DEBUG_THIS_NOTE(note)
#define REF_DBG_COMMA_POINTER
#define OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(p, note)
#define OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(p, note)
#define __assign(target, source) target = source
#define __note_assign(target, source, note) target = source
#define __named_release(x) ::release(x)
#define __check_pending_releases(x)
#endif
