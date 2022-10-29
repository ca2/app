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



namespace acme 
{ 
   
   class system; 
   class context; 
   class library;
   class node; 
   class application;
   class exclusive;

} // namespace acme


namespace apex { class application; }
class thread;
class task;
class property_object;
class task;
class task_pool;
class action_context;
class object;
class dump_context;
//class synchronization;
class __id;
class string_exchange;
class text_stream;
//class string;
//class wstring;
class lparam;
class wait;
class timer_callback;
namespace message { class message; }
class payload;
struct block;
class property_set;
class particle;
class element;
class matter;
class exception_translator;
class counter;
class type;

class acme_file;
class acme_path;
class acme_directory;

class dir_context;
class dir_system;
class file_context;
class file_system;

enum enum_zero_init
{

   e_zero_init

};
namespace networking
{


   class application;


} // namespace networking


namespace operating_system
{

   class department;

   class process;

   class exit_status;

} // namespace operating_system


namespace regular_expression
{

   class context;
   class regular_expression;

} // namespace regular_expression


namespace file
{


   class path;
   class path_object;
   struct file_status;


} // namespace file


namespace data
{


   class node;
   class item;


} // namespace data


class memory_base;

struct PAYLOAD_TAG { };
//struct PROPERTY_TAG { };
struct ATOM_TAG { };
struct STRING_TAG { };

class handler;
class manager;
class context;
class topic;
class extended_topic;


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

   class primitive;
   class element;
   class primitive_impl;

   class object;


} // namespace user


class conversation;


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




class istring;


class property_set;


class payload_array;


class property;


class timer_future;


namespace acme
{

   class Timer;

};


class timer;
class timer_task;

namespace message
{


   class mouse;


} // namespace message





class form_property_set;


namespace acme
{


   //class application;
   //class system;
   //class application_message;

   class command;


} // namespace acme


namespace gpu
{

   class approach;

} // namespace gpu


namespace data
{


   class listener;


   class data;


   class simple_data;


   class data_container_base;


} // namespace data

namespace sockets // only usable from base.dll and dependants
{

   class sockets; // only usable from base.dll and dependants


} // namespace sockets // only usable from base.dll and dependants


namespace url
{

   class department; // only usable from base.dll and dependants


} // namespace url


class compress_department; // only usable from axis.dll and dependants


class channel;


class dump_context;


//class atom_space;


class ptra;


class factory_item_base;


class fixed_alloc_no_sync;


class critical_section;


class channel;


class critical_section;


class mutex;


class atom;

namespace colorertake5
{

   class ParserFactory;


} // namespace colorertake5


//class pixmap;


class memory;


namespace datetime
{


   class department;


   class time;


   class time_span;


} // namespace datetime




namespace file
{

   class listing;


   class path;


   class file;


   enum enum_type
   {

      e_type_unknown = 0,
      e_type_exists = 1 << 0,
      e_type_folder = e_type_exists | (1 << 1),
      e_type_file = e_type_exists | (1 << 2),
      e_type_file_or_folder = e_type_folder | e_type_file,
      e_type_element = e_type_exists | (1 << 3),
      e_type_doesnt_exist = 0x80000000,

   };


} // namespace file


namespace install
{


   class installer;


} // namespace install

//#include "acme/primitive/primitive/move.h"

class task;




class machine_event_data;

namespace hotplugin
{

   class host;


   class plugin;

}


namespace html
{


   class html;


   class element;


} // namespace html


namespace audio
{


   class plugin;


} // namespace audio

class file_time;

class duration;

namespace earth
{
   class date_span;

   class time_span;
} // namespace earth
class folder;

class memory_file;

extern "C"
typedef ::acme::library * NEW_LIBRARY();

typedef NEW_LIBRARY * PFN_NEW_LIBRARY;




namespace draw2d
{


   class graphics;



} // namespace draw2d


namespace handle
{


   class ini;


} // namespace handle


struct system_time_t;




