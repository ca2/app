//
//  reference_count_debug.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//

#pragma once


class reference_count_debug;


#if REFERENCING_DEBUGGING
//#define REFERENCING_DEBUGGING_MAX_COUNT 256
#define REFERENCING_DEBUGGING_ARGS p, pszObjRefDbg
#define REFERENCING_DEBUGGING_COMMA_ARGS , REFERENCING_DEBUGGING_ARGS
#define REF_DBG_POINTER (::matter *)(::iptr)1
#define REF_DBG_VAR (::matter *)(::iptr)1
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
#define REFERENCING_DEBUGGING_PARAMETERS_DEFINITION ::matter * p, const ::string &pszObjRefDbg
#define REFERENCING_DEBUGGING_PARAMETERS ::matter * p = ((::matter*)(::iptr)1), const ::string &pszObjRefDbg = nullptr
#define REFERENCING_DEBUGGING_COMMA_PARAMS_DEFINITION , REFERENCING_DEBUGGING_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_COMMA_PARAMS , REFERENCING_DEBUGGING_PARAMETERS
#define REFERENCING_DEBUGGING_COMMA_NOTE(note) , note
#define REFERENCING_DEBUGGING_PTR(ptr) ptr
#define REFERENCING_DEBUGGING_THIS ((::matter *) this)
#define REFERENCING_DEBUGGING_THIS_NOTE(note) ((::matter *) this), note
#define REFERENCING_DEBUGGING_P_NOTE(p, note) p, note
#define REFERENCING_DEBUGGING_COMMA_P_NOTE(p, note) , REFERENCING_DEBUGGING_P_NOTE(p, note)
#define __assign(target, source) ___assign(target, source)
#define __note_assign(target, source, note) ___assign(target, source, note)
#define __named_release(x) ___release(x)
#define __check_pending_releases(x) x->check_pending_releases()
#else
#define REFERENCING_DEBUGGING_ARGS
#define REFERENCING_DEBUGGING_COMMA_ARGS
#define REFERENCING_DEBUGGING_COMMA_PARAMS
#define REFERENCING_DEBUGGING_COMMA_PARAMS_DEFINITION
#define REFERENCING_DEBUGGING_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_PARAMETERS
#define REFERENCING_DEBUGGING_PTR(ptr)
#define REFERENCING_DEBUGGING_THIS
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
