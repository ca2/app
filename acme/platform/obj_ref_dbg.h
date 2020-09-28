//
//  obj_ref_dbg.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 20/06/20.
//

#pragma once


class obj_ref_dbg;


#if OBJ_REF_DBG
//#define OBJ_REF_DBG_MAX_COUNT 256
#define OBJ_REF_DBG_ARGS p, pszObjRefDbg
#define OBJ_REF_DBG_ADD_ARGS , OBJ_REF_DBG_ARGS
#define REF_DBG_POINTER (::elemental *)(::iptr)1
#define REF_DBG_VAR (::elemental *)(::iptr)1
#define REF_DBG_ADD_POINTER , REF_DBG_POINTER
#define OBJ_REF_DBG_PARAMS_DEF ::elemental * p, const char *pszObjRefDbg
#define OBJ_REF_DBG_PARAMS ::elemental * p = ((::elemental*)(::iptr)1), const char *pszObjRefDbg = nullptr
#define OBJ_REF_DBG_ADD_PARAMS_DEF , OBJ_REF_DBG_PARAMS_DEF
#define OBJ_REF_DBG_ADD_PARAMS , OBJ_REF_DBG_PARAMS
#define OBJ_REF_DBG_ADD_NOTE(note) , note
#define OBJ_REF_DBG_PTR(ptr) ptr
#define OBJ_REF_DBG_THIS ((::elemental *) this)
#define OBJ_REF_DBG_THIS_NOTE(note) ((::elemental *) this), note
#define OBJ_REF_DBG_P_NOTE(p, note) p, note
#define OBJ_REF_DBG_ADD_P_NOTE(p, note) , OBJ_REF_DBG_P_NOTE(p, note)
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
