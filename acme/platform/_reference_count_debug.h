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
//#define REFERENCING_DEBUGGING_MAX_COUNT 256
#define REFERENCING_DEBUGGING_ARGS referer
#define REFERENCING_DEBUGGING_COMMA_ARGS , REFERENCING_DEBUGGING_ARGS
#define REF_DBG_POINTER nullptr
#define REF_DBG_VAR nullptr
#define REF_DBG_COMMA_POINTER , REF_DBG_POINTER
#define REFERENCING_DEBUGGING_PARAMETERS_DEFINITION const reference_referer & referer
#define REFERENCING_DEBUGGING_PARAMETERS const reference_referer & referer = nullptr
#define REFERENCING_DEBUGGING_COMMA_PARAMS_DEFINITION , REFERENCING_DEBUGGING_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_COMMA_PARAMS , REFERENCING_DEBUGGING_PARAMETERS
#define REFERENCING_DEBUGGING_COMMA_NOTE(note) , {nullptr, note}
#define REFERENCING_DEBUGGING_P(ptr) ptr
#define REFERENCING_DEBUGGING_COMMA_P(ptr) , REFERENCING_DEBUGGING_P(ptr)
#define REFERENCING_DEBUGGING_THIS (this)
#define REFERENCING_DEBUGGING_COMMA_THIS , REFERENCING_DEBUGGING_THIS
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
#define REFERENCING_DEBUGGING_ARGS
#define REFERENCING_DEBUGGING_COMMA_ARGS
#define REFERENCING_DEBUGGING_COMMA_PARAMS
#define REFERENCING_DEBUGGING_COMMA_PARAMS_DEFINITION
#define REFERENCING_DEBUGGING_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_PARAMETERS
#define REFERENCING_DEBUGGING_PTR(ptr)
#define REFERENCING_DEBUGGING_THIS
#define REFERENCING_DEBUGGING_THIS
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



