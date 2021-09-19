// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once


class system;
class application;
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
namespace message { class message; }
class payload;
class stream;


//namespace subject
//{

   class subject;
   class context;

//} // namespace subject



template<class T>
class ___pointer;


template<class T>
class pointer_array;


//#define __composite(TYPE) ::reference < TYPE >


#define __pointer(TYPE) ::___pointer < TYPE >
#define __pointer_array(TYPE) ::pointer_array < TYPE >
#define __address_array(TYPE) ::comparable_array < TYPE * >


#define __throw(...) throw_exception(__VA_ARGS__)


CLASS_DECL_ACME void output_error_message(const ansichar * pszMessage, const ansichar * pszTitle = nullptr, int iMessageBox = 0);
CLASS_DECL_ACME void output_debug_string(const ansichar * psz);
CLASS_DECL_ACME void output_debug_string(const wd16char * psz);
CLASS_DECL_ACME void output_debug_string(const wd32char * psz);



inline bool is_set_ptr(const void * p) { return (uptr)p > 65536; }

