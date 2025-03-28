//
//  reference_count_debug.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 20/06/20.
//  More work on 2023-11-22 12:47 <3ThomasBorregaardSorensen
//
#pragma once


#define __FILE_LINE__  __FILE__ "(" MAKE_STRING(__LINE__) ")"
#define __FUNCTION_LINE__  __FUNCTION__, " (" MAKE_STRING(__LINE__) ")"
#define __FUNCTION_FILE_LINE__  __FUNCTION__, __FILE__ "(" MAKE_STRING(__LINE__) ")"

class subparticle;


#if REFERENCING_DEBUGGING

class reference_referer;
struct reference_count_debug_item;
class reference_count_debug;
CLASS_DECL_ACME::subparticle * refdbg_this();

#define REFDBG_THIS(p) auto refdbg_this = [p]() { return p; }

//#define __øcreate __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->template __call__create
//#define __øconstruct __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__construct
//#define __id_create __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__id_create
//#define __create_new __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->template __call__create_new
//#define __id_construct __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__id_construct
//#define __raw_construct __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__raw_construct
//#define __construct_new __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__construct_new
//#define __defer_construct __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__defer_construct
//#define __create_new_clone __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__create_new_clone
//#define __defer_construct_new __call__add_referer2({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__defer_construct_new

#define __øcreate __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->template __call__create
#define __øconstruct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__construct
#define __id_create __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__id_create
#define __create_new __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->template __call__create_new
#define __id_construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__id_construct
#define __raw_construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__raw_construct
#define __construct_new __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__construct_new
#define __defer_construct __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__defer_construct
#define __create_new_clone __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__create_new_clone
#define __defer_construct_new __call__add_referer2({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__defer_construct_new


//#define __raw_construct_new(C) __construct_site(C, { refdbg_this(), __FUNCTION_FILE_LINE__ })


//#define __new__prefix(x) __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ }, &prefererNew)->




//#define __new__prefix(pprefererGet) __new_site({ nullptr, refdbg_this(), __FUNCTION_FILE_LINE__ }, pprefererGet) <<
#define __new__prefix(pprefererGet) __new_site({ refdbg_this(), __FUNCTION_FILE_LINE__ }, pprefererGet) <<



//#define ___new __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__new
//#define __allocate __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ })->__call__allocate
//#define __allocate __call__add_referer({ refdbg_this(), __FUNCTION_FILE_LINE__ })

//#define __refdbg_function_file_line_for__(p) { p, refdbg_this(), __FUNCTION_FILE_LINE__ }
//#define __comma_refdbg_function_file_line_for__(p) , __refdbg_function_file_line_for__(p)
//
//#define __refdbg_function_file_line__ __refdbg_function_file_line_for__(nullptr)
//#define __comma_refdbg_function_file_line__ __comma_refdbg_function_file_line_for__(nullptr)
//
//#define __refdbg_function_file_line_for__preferernew(p) __refdbg_function_file_line_for__(p), &prefererNew
//#define __comma_refdbg_function_file_line_for__preferernew(p) , __refdbg_function_file_line_for__preferernew(p)
//
//#define __refdbg_function_file_line__preferernew __refdbg_function_file_line_for__preferernew(nullptr)
//#define __comma_refdbg_function_file_line__preferernew , __refdbg_function_file_line_for__preferernew(nullptr)
//
//#define __refdbg_call_add_referer_for(p) __call__add_referer({ p, refdbg_this(), __FUNCTION_FILE_LINE__ }) <<
//#define __refdbg_call_add_referer __refdbg_call_add_referer_for(nullptr) <<


#define __refdbg_function_file_line_for__(p) { refdbg_this(), __FUNCTION_FILE_LINE__ }
#define __comma_refdbg_function_file_line_for__(p) , __refdbg_function_file_line_for__(p)

#define __refdbg_function_file_line__ __refdbg_function_file_line_for__(nullptr)
#define __comma_refdbg_function_file_line__ __comma_refdbg_function_file_line_for__(nullptr)

#define __refdbg_function_file_line_for__preferernew(p) __refdbg_function_file_line_for__(p), &prefererNew
#define __comma_refdbg_function_file_line_for__preferernew(p) , __refdbg_function_file_line_for__preferernew(p)

#define __refdbg_function_file_line__preferernew __refdbg_function_file_line_for__preferernew(nullptr)
#define __comma_refdbg_function_file_line__preferernew , __refdbg_function_file_line_for__preferernew(nullptr)

#define __refdbg_call_add_referer_for(p) __call__add_referer({ p, refdbg_this(), __FUNCTION_FILE_LINE__ }) <<
#define __refdbg_call_add_referer __refdbg_call_add_referer_for(nullptr) <<


#define __fn_refdbg_referer__ refdbg_referer() 

#define __refdbg_referer__ referer

#define __comma_refdbg_m_preferer__ , m_preferer
#define __comma_refdbg_preferer__ , preferer

#define __raw_construct_new(C) __construct_site(C __comma_refdbg_function_file_line__)


#define __check_refdbg check_refdbg();

//#define __refdbg_add_referer ::allocator::push_referer({nullptr, refdbg_this(), __FUNCTION_FILE_LINE__});
//#define __refdbg_add_referer_for(p) ::allocator::defer_push_referer(p, {p, refdbg_this(), __FUNCTION_FILE_LINE__});
//#define __refdbg_assign_referer_for(p) m_preferer = ::allocator::defer_push_referer(p, {p, refdbg_this(), __FUNCTION_FILE_LINE__});
//#define __refdbg_add_releaser(preferer) ::allocator::add_releaser(preferer);

#define __refdbg_add_referer ::allocator::push_referer({refdbg_this(), __FUNCTION_FILE_LINE__});
#define __refdbg_add_referer_for(p) ::allocator::defer_push_referer(p, {refdbg_this(), __FUNCTION_FILE_LINE__});
#define __refdbg_assign_referer_for(p) m_preferer = ::allocator::defer_push_referer(p, {refdbg_this(), __FUNCTION_FILE_LINE__});
#define __refdbg_add_releaser(preferer) ::allocator::add_releaser(preferer);
#define __refdbg_this(pparticle) auto refdbg_this= [pparticle]() { return pparticle; }
CLASS_DECL_ACME void check_refdbg();


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
#define  REFERENCING_DEBUGGING_PARAMETERS_DEFINITION2 ,
#define REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION ::reference_referer * preferer
#define COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION , REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION = nullptr
#define COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION , REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION
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
#define REFERENCING_DEBUGGING_P_FUNCTION_NOTE(p, function, note) {p, function, note}
#define REFERENCING_DEBUGGING_P_FUNCTION_FILE_LINE(p) REFERENCING_DEBUGGING_P_FUNCTION_NOTE(p, __FUNCTION_FILE_LINE__ )
#define REFERENCING_DEBUGGING_COMMA_P_FUNCTION_NOTE(p, function, note) , REFERENCING_DEBUGGING_P_FUNCTION_NOTE(p, function, note)
#define REFERENCING_DEBUGGING_COMMA_P_FUNCTION_FILE_LINE(p) REFERENCING_DEBUGGING_COMMA_P_NOTE(p, __FUNCTION_FILE_LINE__ )
#define tracking_assign(target, ...) reference_count_debug_assign(target, __VA_ARGS__ )
#define tracking_note_assign(target, source, ... ) reference_count_debug_assign(target, source,  __VA_ARGS__ )
#define tracking_named_release(...) reference_count_debug_release( __VA_ARGS__ )
#define tracking_check_pending_releases(x) x->check_pending_releases()


CLASS_DECL_ACME ::reference_referer* refdbg_get_top_referer();
CLASS_DECL_ACME ::subparticle* refdbg_get_track_allocation();
CLASS_DECL_ACME ::reference_referer* refdbg_get_top_releaser();


#else


#define REFDBG_THIS(p)

#define __øcreate __call__create
#define __øconstruct __call__construct
#define __id_create __call__id_create
#define __create_new __call__create_new
#define __id_construct __call__id_construct
#define __raw_construct __call__raw_construct
#define __construct_new __call__construct_new
#define __defer_construct __call__defer_construct
#define __create_new_clone __call__create_new_clone
#define __defer_construct_new __call__defer_construct_new


#define __allocate__prefix(x) 
//#define __allocate __call__allocate
//#define __allocate __call__allocate
//#define __allocate_and_initialize __call__allocate_and_initialize
//#define __delete __call__delete

//#define __construct_new(p) __call__construct_new(p)
#define __new__prefix(pprefererGet) __new_site() <<

#define __refdbg_function_file_line__
#define __comma_refdbg_function_file_line__

#define __refdbg_function_file_line__preferernew
#define __comma_refdbg_function_file_line__preferernew

#define __refdbg_call_add_referer

#define __fn_refdbg_referer__

#define __refdbg_referer__

#define __comma_refdbg_m_preferer__
#define __comma_refdbg_preferer__


#define __raw_construct_new(C) __call__raw_construct_new(C)


#define __check_refdbg

#define __refdbg_add_referer
#define __refdbg_add_referer_for(p)
#define __refdbg_assign_referer_for(p)
#define __refdbg_add_releaser(preferer)
#define __refdbg_this(pparticle)
//#define 
//#define
//#define
//#define
//#define 
//#define 
#define REFERENCING_DEBUGGING_ARGUMENTS 
#define COMMA_REFERENCING_DEBUGGING_ARGUMENTS
#define REFERENCING_DEBUGGING_ARGUMENTS_COMMA
#define REFERENCING_DEBUGGING_PARAMETERS_DEFINITION 
#define COMMA_REFERENCING_DEBUGGING_PARAMETERS_DEFINITION 
#define REFERENCING_DEBUGGING_PARAMETERS_DECLARATION 
#define COMMA_REFERENCING_DEBUGGING_PARAMETERS_DECLARATION
#define  REFERENCING_DEBUGGING_PARAMETERS_DEFINITION2
#define REFERENCING_DEBUGGING_COMMA_NOTE(note)
#define REFERENCING_DEBUGGING_P(ptr) 
#define REFERENCING_DEBUGGING_COMMA_P(ptr) 
//#define  (this)
#define REFERENCING_DEBUGGING_COMMA_THIS 
#define REFERENCING_DEBUGGING_WILD_NOTE(note)
#define REFERENCING_DEBUGGING_WILD_FUNCTION_FILE_LINE
#define REFERENCING_DEBUGGING_COMMA_WILD_NOTE(note) 
#define REFERENCING_DEBUGGING_COMMA_WILD_FUNCTION_FILE_LINE 
#define REFERENCING_DEBUGGING_THIS_NOTE(note) 
#define REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE 
#define REFERENCING_DEBUGGING_COMMA_THIS_NOTE(note) 
#define REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE 
#define REFERENCING_DEBUGGING_P_FUNCTION_NOTE(p, function, note) 
#define REFERENCING_DEBUGGING_P_FUNCTION_FILE_LINE(p) 
#define REFERENCING_DEBUGGING_COMMA_P_FUNCTION_NOTE(p, function, note) 
#define REFERENCING_DEBUGGING_COMMA_P_FUNCTION_FILE_LINE(p) 
#define REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION
#define COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DEFINITION
#define REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION
#define COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION
#define tracking_assign(target, source) target = source
#define tracking_note_assign(target, source, note) target = source
#define tracking_named_release(x) ::release(x)
#define tracking_check_pending_releases(x)


#define __refdbg_call_add_referer 

#define __refdbg_function_file_line__

#endif


class __new_site;
class __delete_site;
class __raw_new_site;
class __new_refdbg_continuation_site;


#define ___new __new_site ( __refdbg_function_file_line__ ) << new
#define __delete delete __delete_site(__refdbg_referer__) <<


#define __raw_new __raw_new_site() << new


#define __new_refdbg_continuation __new_refdbg_continuation_site() << new

//#define __raw_new new




//CLASS_DECL_ACME abc __call__add_referer(const ::reference_referer& referer, ::reference_referer** ppreferer);


