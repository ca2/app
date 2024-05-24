#pragma once


#include "profiler.h"


#ifndef __PARTIAL_CPP


//
//#ifdef WINDOWS
//
//
//interface ID2D1DeviceContext;
//
//
//#endif

class image_list;
//

//namespace user
//{
//
//   class printer;
//   class single_document_template;
//   class main_frame;
//
//
//} // namespace user


//namespace experience
//{
//
//   class frame_window;
//
//} // namespace experience


//class service_base;
//
//
//namespace filehandler
//{
//
//
//   class handler;
//
//
//} // namespace filehandler

//
//namespace html
//{
//
//
//   class html_ex;
//
//
//} // namespace html
//
//
//namespace userfs
//{
//
//
//   class userfs;
//
//
//} // namespace userfs

//
//namespace userex
//{
//
//
//   class userex;
//
//
//} // namespace userex

//
//namespace filemanager
//{
//
//
//   class document;
//   class data;
//
//
//} // namespace filemanager


namespace acid
{


   CLASS_DECL_ACID bool init_core();

   CLASS_DECL_ACID bool term_core();


} // namespace acid


#pragma warning(disable: 4250)


//class stdio_file;
struct memory_state;


#include "const.h"


#include "less.h"


#define ASSERT_KINDOF(class_name, matter) ASSERT(base_class < class_name > ::bases(matter))
#define DYNAMIC_CAST(class_name, matter) (dynamic_cast < class_name * > (matter))
#define ZERO_INIT_JUST_THIS(base_class) memory_set(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));


#include "constraint.h"


namespace acid
{


   CLASS_DECL_ACID void format_strings(string& rString, const ::scoped_string & scopedstrFormat, const char* const* rgpsz, i32 nString);

   CLASS_DECL_ACID bool extract_sub_string(string& rString, const ::scoped_string & scopedstrFullString, i32 iSubString, char chSep = '\n');


}


#include "acid/primitive/collection/std_iterator.h"
#include "acid/primitive/collection/insert_iterator.h"
#include "acid/primitive/collection/back_insert_iterator.h"
#include "acid/primitive/collection/std_pair.h"

//#include "acid/primitive/primitive/tupe.h"


//#include "muldiv32.h"


#include "logic.h"


#endif



