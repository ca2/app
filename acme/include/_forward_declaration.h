//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 22:30
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once


#include "acme/primitive/mathematics/index.h"
#include "acme/primitive/mathematics/count.h"


constexpr ::u64 operator "" _uintmax(unsigned long long int u) { return u << 32LL; }



namespace acme { class system; }
namespace acme { class application; }
namespace apex { class application; }
class thread;
class property_object;
class task;
class task_pool;
class action_context;
class object;
class dump_context;
class synchronization_object;
class __id;
class string_exchange;
class text_stream;
class string;
class wstring;
class lparam;
namespace message { class message; }
class payload;
struct block;
class property_set;
class particle;
class element;
namespace operating_system { class department; }
class exception_translator;
class counter;
enum enum_zero_init
{

   e_zero_init

};
namespace networking
{


   class application;


} // namespace networking

namespace regular_expression
{

   class context;
   class regular_expression;

} // namespace regular_expression



//namespace topic
//{

   class topic;
   class context;

//} // namespace topic
namespace file
{

   class file;
   class item;
   class item_array;


} // namespace file


namespace apex
{


   class savings;


} // namespace apex

class stdio_file;
class string_stream;
class string_buffer;


namespace http
{

   class cookie;
   class cookies;


} // namespace http




CLASS_DECL_ACME void output_error_message(const ansichar * pszMessage, const ansichar * pszTitle = nullptr, int iMessageBox = 0);
CLASS_DECL_ACME void output_debug_string(const ansichar * psz);
CLASS_DECL_ACME void output_debug_string(const wd16char * psz);
CLASS_DECL_ACME void output_debug_string(const wd32char * psz);







class error_code;


namespace user
{


   class tool_item;
   class mouse;
   class drag;
   class drag_client;


} // namespace user


class image;
class e_check;
class tristate;




namespace write_text
{


   class font;
   

} // namespace write_text


namespace interprocess
{

   
   class target;


} // namespace interprocess




struct pixmap;


#define CONSIDER_AS(as, use) using use = as



//typedef natural_ansistring natural_string;
//typedef natural_widestring natural_wstring;

class property;
class payload;
class atom;


struct MESSAGE;

class item;


class memory;


class CLASS_DECL_ACME integral_byte { public: integral_byte(memsize memsize = 1) : m_memsize(memsize) {} memsize m_memsize; operator memsize() const { return m_memsize; } };


inline integral_byte operator ""_kb(long double d)
{
   return (memsize)(1024.0 * d);
}

inline integral_byte operator ""_kb(unsigned long long i)
{
   return (memsize)(1024 * i);
}

inline integral_byte operator ""_mb(long double d)
{
   return (memsize)(1024.0 * 1024.0 * d);
}

inline integral_byte operator ""_mb(unsigned long long i)
{
   return (memsize) (1024 * 1024 * i);
}

inline integral_byte operator ""_gb(long double d)
{
   return (memsize) (1024.0 * 1024.0 * 1024.0 * d);
}

inline integral_byte operator ""_gb(unsigned long long i)
{
   return (memsize) (1024 * 1024 * 1024 * i);
}



