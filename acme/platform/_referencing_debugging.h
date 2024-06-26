//
//  reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 12:47 <3ThomasBorregaardSorensen
//
#pragma once


#define __FILE_LINE__  __FILE__ "(" STRINGFY(__LINE__) ")"
#define __FUNCTION_LINE__  __FUNCTION__ " (" STRINGFY(__LINE__) ")"
#define __FUNCTION_FILE_LINE__  __FUNCTION__ "\n" __FILE__ "(" STRINGFY(__LINE__) ")"


class particle;
struct reference_count_debug_item;
class reference_count_debug;


#if REFERENCING_DEBUGGING


#define REFDBG_THIS(p) auto refdbg_this = [p]() { return p; }

#define __create __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__create
#define __construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__construct
#define __id_create __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__id_create
#define __create_new __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__create_new
#define __id_construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__id_construct
#define __raw_construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__raw_construct
#define __construct_new __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__construct_new
#define __defer_construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__defer_construct
#define __create_new_clone __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__create_new_clone
#define __defer_construct_new __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__defer_construct_new


#define __new__prefix(x) __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ }, &m_preferer)->
#define __new __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__new
#define __allocate __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__allocate


//#define REFERENCING_DEBUGGING_MAX_COUNT 256
//#define  referer
//#define , 
#define REF_DBG_POINTER nullptr
#define REF_DBG_VAR nullptr
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
//#define  const reference_referer & referer
//#define  const reference_referer & referer = nullptr
//#define , 
//#define , 
#define REFERENCING_DEBUGGING_ARGUMENTS referer
#define COMMA_REFERENCING_DEBUGGING_ARGUMENTS , REFERENCING_DEBUGGING_ARGUMENTS
#define REFERENCING_DEBUGGING_ARGUMENTS_COMMA REFERENCING_DEBUGGING_ARGUMENTS ,
#define REFERENCING_DEBUGGING_PARAMETERS_DEFINITION const ::reference_referer & referer
#define COMMA_REFERENCING_DEBUGGING_PARAMETERS_DEFINITION , REFERENCING_DEBUGGING_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_PARAMETERS_DECLARATION REFERENCING_DEBUGGING_PARAMETERS_DEFINITION = nullptr
#define COMMA_REFERENCING_DEBUGGING_PARAMETERS_DECLARATION , REFERENCING_DEBUGGING_PARAMETERS_DECLARATION
#define  REFERENCING_DEBUGGING_PARAMETERS_DEFINITION ,
#define REFERENCING_DEBUGGING_COMMA_NOTE(note) , {nullptr, note}
#define REFERENCING_DEBUGGING_P(ptr) ptr
#define REFERENCING_DEBUGGING_COMMA_P(ptr) , REFERENCING_DEBUGGING_P(ptr)
//#define  (this)
#define REFERENCING_DEBUGGING_COMMA_THIS , 
#define REFERENCING_DEBUGGING_WILD_NOTE(note) {nullptr, note}
#define REFERENCING_DEBUGGING_WILD_FUNCTION_FILE_LINE REFERENCING_DEBUGGING_WILD_NOTE( __FUNCTION_FILE_LINE__ )
#define REFERENCING_DEBUGGING_COMMA_WILD_NOTE(note) , REFERENCING_DEBUGGING_WILD_NOTE(note)
#define REFERENCING_DEBUGGING_COMMA_WILD_FUNCTION_FILE_LINE , REFERENCING_DEBUGGING_WILD_FUNCTION_FILE_LINE
#define REFERENCING_DEBUGGING_THIS_NOTE(note) {this, note}
#define REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE REFERENCING_DEBUGGING_THIS_NOTE( __FUNCTION_FILE_LINE__ )
#define REFERENCING_DEBUGGING_COMMA_THIS_NOTE(note) , REFERENCING_DEBUGGING_THIS_NOTE(note)
#define REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE , REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE
#define REFERENCING_DEBUGGING_P_NOTE(p, note) {p, note}
#define REFERENCING_DEBUGGING_P_FUNCTION_FILE_LINE(p) REFERENCING_DEBUGGING_P_NOTE(p, __FUNCTION_FILE_LINE__ )
#define REFERENCING_DEBUGGING_COMMA_P_NOTE(p, note) , REFERENCING_DEBUGGING_P_NOTE(p, note)
#define REFERENCING_DEBUGGING_COMMA_P_FUNCTION_FILE_LINE(p) REFERENCING_DEBUGGING_COMMA_P_NOTE(p, __FUNCTION_FILE_LINE__ )
#define tracking_assign(target, ...) reference_count_debug_assign(target, __VA_ARGS__ )
#define tracking_note_assign(target, source, ... ) reference_count_debug_assign(target, source,  __VA_ARGS__ )
#define tracking_named_release(...) reference_count_debug_release( __VA_ARGS__ )
#define tracking_check_pending_releases(x) x->check_pending_releases()
#else


#define REFDBG_THIS(p)

#define __create __call__create
#define __construct __call__construct
#define __id_create __call__id_create
#define __create_new __call__create_new
#define __id_construct __call__id_construct
#define __raw_construct __call__raw_construct
#define __construct_new __call__construct_new
#define __defer_construct __call__defer_construct
#define __create_new_clone __call__create_new_clone
#define __defer_construct_new __call__defer_construct_new


#define __new__prefix(x) 
#define __new __call__new
#define __allocate __call__allocate
#define __allocate_and_initialize __call__allocate_and_initialize
#define __delete __call__delete

//#define __construct_new(p) __call__construct_new(p)

//#define 
//#define
//#define
//#define
//#define 
//#define 
#define REFERENCING_DEBUGGING_PTR(ptr)
//#define 
//#define 
#define REFERENCING_DEBUGGING_COMMA_THIS
#define REFERENCING_DEBUGGING_COMMA_NOTE(note)
#define REFERENCING_DEBUGGING_THIS_NOTE(note)
#define REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE
#define REFERENCING_DEBUGGING_COMMA_THIS_NOTE(note)
#define REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE
#define REF_DBG_COMMA_POINTER
#define REFERENCING_DEBUGGING_P_NOTE(referer, note)
#define REFERENCING_DEBUGGING_P_FUNCTION_LINE(referer)
#define REFERENCING_DEBUGGING_COMMA_P_NOTE(referer, note)
#define REFERENCING_DEBUGGING_COMMA_P_FUNCTION_LINE(referer)
#define tracking_assign(target, source) target = source
#define tracking_note_assign(target, source, note) target = source
#define tracking_named_release(x) ::release(x)
#define tracking_check_pending_releases(x)
#endif



