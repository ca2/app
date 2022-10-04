//
//  _forward_declaration.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/09/22 22:30
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


// Created by camilo on 2021-08-31 16:00 BRT <3ThomasBS_!!
#pragma once

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
namespace message { class message; }
class payload;
class stream;


//namespace topic
//{

   class topic;
   class context;

//} // namespace topic



template<class T>
class ___pointer;


template<class T>
class pointer_array;


//#define __composite(TYPE) ::reference < TYPE >


#define __pointer(TYPE) ::___pointer < TYPE >
#define __pointer_array(TYPE) ::pointer_array < TYPE >

//
//template < typename TYPE >
//class ___address
//{
//public:
//
//
//   TYPE* m_p;
//
//   ___address() : m_p(nullptr) {}
//   ~___address() { if (::is_set(m_p)) throw error_wrong_state; }
//
//   TYPE* get() { return m_p; }
//   TYPE* get() const { return m_p; }
//
//   operator TYPE* () const { return m_p; }
//   operator TYPE* () { return m_p; }
//
//   TYPE* operator ->() const { return m_p; }
//   TYPE* operator ->() { return m_p; }
//
//   bool is_null() const { return ::is_null(m_p); }
//   bool is_set() const { return ::is_set(m_p); }
//   bool operator !() const { return is_null(); }
//
//   template < typename OBJECT >
//   __pointer(OBJECT) cast() const;
//
//
//   template < typename INTERMEDIATE >
//   void release(INTERMEDIATE* p) { ::release(p, m_p); }
//
//
//   template < typename ADDRESS >
//   ___address & operator = (ADDRESS & p) { p->increment_reference_count(); release(p); m_p = p; return *this; }
//
//};


//#define throw ::exception(...) throw_exception(__VA_ARGS__)


CLASS_DECL_ACME void output_error_message(const ansichar * pszMessage, const ansichar * pszTitle = nullptr, int iMessageBox = 0);
CLASS_DECL_ACME void output_debug_string(const ansichar * psz);
CLASS_DECL_ACME void output_debug_string(const wd16char * psz);
CLASS_DECL_ACME void output_debug_string(const wd32char * psz);



inline bool is_set_ptr(const void * p) { return (uptr)p > 65536; }



class error_code;


namespace user
{


   class tool_item;


} // namespace user


class image;


template<class T>
   class ___pointer;


template<class T>
   class pointer_array;


using image_pointer = __pointer(::image);


namespace write_text
{


   class font;
   
   using font_pointer = __pointer(font);


} // namespace write_text



