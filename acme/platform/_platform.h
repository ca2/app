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

//
//namespace user
//{
//
//
//   class form_callback;
//
//   class combo_box;
//   class list_box;
//
//
//} // namespace user
//
//
//namespace dynamic_source
//{
//
//
//   class script;
//   class script_manager;
//
//
//} // namespace dynamic_source


namespace acme
{


   CLASS_DECL_ACME bool init_core();

   CLASS_DECL_ACME bool term_core();


} // namespace acme


#pragma warning(disable: 4250)


class stdio_file;
struct memory_state;


#include "const.h"


#include "less.h"


#define ASSERT_KINDOF(class_name, matter) ASSERT(base_class < class_name > ::bases(matter))
#define DYNAMIC_CAST(class_name, matter) (dynamic_cast < class_name * > (matter))
#define ZERO_INIT_JUST_THIS(base_class) __memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));


#include "constraint.h"


namespace acme
{


   CLASS_DECL_ACME void format_strings(string& rString, const char* pszFormat, const char* const* rgpsz, i32 nString);

   CLASS_DECL_ACME bool extract_sub_string(string& rString, const char* pszFullString, i32 iSubString, char chSep = '\n');


}


#include "acme/primitive/collection/std_iterator.h"
#include "acme/primitive/collection/insert_iterator.h"
#include "acme/primitive/collection/back_insert_iterator.h"
#include "acme/primitive/collection/std_pair.h"


#include "muldiv32.h"


#include "logic.h"


#endif



