#pragma once


// Include payload.h
// Don`t include this file directly


#include "payload.h"


class property;
class action_context;


#include "acme/memory/memory.h"


namespace xml
{

   class disp_option;

} // namespace xml

//::string CLASS_DECL_ACME operator + (const ::scoped_string & scopedstr, const property & prop);
//
//::payload CLASS_DECL_ACME operator - (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator - (u32 user, const property & prop);
//::payload CLASS_DECL_ACME operator - (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator - (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator - (double d, const property & prop);
//::payload CLASS_DECL_ACME operator - (const ::payload & payload, const property & prop);

//::payload CLASS_DECL_ACME operator + (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator + (u32 user, const property & prop);
//::payload CLASS_DECL_ACME operator + (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator + (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator + (double d, const property & prop);
//::payload CLASS_DECL_ACME operator + (const ::payload & payload, const property & prop);

//::payload CLASS_DECL_ACME operator / (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator / (u32 user, const property & prop);
//::payload CLASS_DECL_ACME operator / (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator / (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator / (double d, const property & prop);
//::payload CLASS_DECL_ACME operator / (const ::payload & payload, const property & prop);

//::payload CLASS_DECL_ACME operator * (i32 i, const property & prop);
//::payload CLASS_DECL_ACME operator * (u32 user, const ::property & prop);
//::payload CLASS_DECL_ACME operator * (i64 i, const property & prop);
//::payload CLASS_DECL_ACME operator * (u64 u, const property & prop);
//::payload CLASS_DECL_ACME operator * (double d, const property & prop);
//::payload CLASS_DECL_ACME operator * (const ::payload & payload, const property & prop);


//namespace xml
//{
//
//
//   class disp_option;
//   class department;
//   class document;
//   class node;
//   class tree_schema;
//   class output_tree;
//   class input_tree;
//
//
//} // namespace xml


//using property = payload;


void on_property_construct(property * pproperty);
void on_property_destruct(property * pproperty);


class CLASS_DECL_ACME property : 
   public ::payload
{
public:


   using PRIMITIVE_PAYLOAD_TAG = PRIMITIVE_PAYLOAD_TAG_TYPE;


   using TYPE1 = ::atom;
   using ARG_TYPE1 = const ::atom &;
   using TYPE2 = payload;
   using ARG_TYPE2 = const ::payload &;


   ::atom                 m_atom;


   property() { on_property_construct(this); }
   property(const ::atom& atom) : m_atom(atom) { on_property_construct(this); }
   property(const ::atom& atom, const ::payload& payload) : m_atom(atom), ::payload(payload) { on_property_construct(this); }
   property(const ::property& property) : m_atom(property.m_atom), ::payload((const ::payload &) property) { on_property_construct(this); }
   property(::property&& property) : m_atom(::transfer(property.m_atom)), ::payload((::payload &&)::transfer(property)) { on_property_construct(this); }
   ~property() { on_property_destruct(this); }


   void* operator __new(size_t size)
   {

      return ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_property)->allocate(size, nullptr);

   }


   void* operator __new(size_t size, const char* /* pszFileName */, int /* nLine */)
   {

      return ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_property)->allocate(size, nullptr);

   }


   void operator delete(void * p)
   {

      return ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_property)->free(p);

   }


   void operator delete(void * p, const char* /* pszFileName */, int /* nLine */)
   {

      return ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_property)->free(p);

   }


   ::atom& element1() { return m_atom; };
   const ::atom& element1() const { return m_atom; };
   ::payload& element2() { return *this; };
   const ::payload& element2() const { return *this; };


   using payload::operator =;
   property & operator = (const property & property)
   {

      if(this != &property)
      {

         m_atom = property.m_atom;

         payload::operator=((const ::payload & )property);

      }

      return *this;

   }


   ::atom name() const { return m_atom; }

  
   inline ::string & get_network_payload(::string & str, bool bNewLine = true) const
   {

      str += "\"";

      str += m_atom;

      str += "\"";

      str += ": ";

      payload::get_network_payload(str, bNewLine);

      return str;

   }

  ::string get_network_payload(bool bNewLine = true) const
  {

     ::string str;

     return get_network_payload(str, bNewLine);

  }

   ::string & get_network_arguments(::string & str) const;
   ::string get_network_arguments() const { ::string str; return get_network_arguments(str); }


   template < typename T >
   inline ::pointer< T >& defer_get(::pointer< T >& pointer) { return pointer = cast < T >(); }


   //using payload::operator ::string;

};

CLASS_DECL_ACME binary_stream & operator << (::binary_stream& stream, const property & property);
CLASS_DECL_ACME binary_stream & operator >> (::binary_stream& stream, property & property);
//CLASS_DECL_ACME binary_stream& operator << (::binary_stream& stream, const property_particle& property);
//CLASS_DECL_ACME binary_stream& operator >> (::binary_stream& stream, property_particle& property);
CLASS_DECL_ACME binary_stream& binary_stream_write_property(::binary_stream& stream, const property& property);
CLASS_DECL_ACME binary_stream& binary_stream_read_property(::binary_stream& stream, property& property);

using property_pointer = ::property *;


CLASS_DECL_ACME void property_parse_network_payload_item(atom & atom, ::ansi_range & range);
CLASS_DECL_ACME void property_parse_network_payload_payload(::payload & payload, ::ansi_range & range);
CLASS_DECL_ACME void property_skip_network_payload_item(::ansi_range & range);
CLASS_DECL_ACME void property_skip_network_payload_payload(::ansi_range & range);


#include "acme/prototype/collection/ptr_array.h"
#include "acme/prototype/collection/auto_ptr_array.h"
#include "acme/prototype/collection/raw_pointer_array.h"


using property_array = ::array < ::property >;

//using property_map = map < ::atom, const ::atom &, payload, const ::payload &, ::property >;


//inline bool operator == (const ::string & str, const property & prop)
//{
//
//   return str == prop.get_string();
//
//}



//inline ::payload CLASS_DECL_ACME operator - (i32 i, const property& prop) { return operator - (i, (const ::payload &) prop); }
//inline ::payload CLASS_DECL_ACME operator - (u32 user, const property& prop) { return operator - (user, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (i64 i, const property& prop) { return operator - (i, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (u64 u, const property& prop) { return operator - (u, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (double d, const property& prop) { return operator - (d, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator - (const ::payload & payload, const property& prop) { return operator - (payload, (const ::payload &)prop); }

//inline ::payload CLASS_DECL_ACME operator + (i32 i, const property& prop) { return operator + (i, (const ::payload &) prop); }
//inline ::payload CLASS_DECL_ACME operator + (u32 user, const property& prop) { return operator + (user, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (i64 i, const property& prop) { return operator + (i, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (u64 u, const property& prop) { return operator + (u, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (double d, const property& prop) { return operator + (d, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator + (const ::payload & payload, const property& prop) { return payload, (const ::payload &)prop); }

//inline ::payload CLASS_DECL_ACME operator / (i32 i, const property& prop) { return operator / (i, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator / (u32 user, const property& prop) { return operator / (user, (const ::payload &)prop); }
//inline ::payload CLASS_DECL_ACME operator / (i64 i, const property& prop) { return operator / (i, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator / (u64 u, const property& prop) { return operator / (u, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator / (double d, const property& prop) { return operator / (d, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator / (const ::payload & payload, const property& prop) { return operator / (payload, (const ::payload&) prop); }

//inline ::payload CLASS_DECL_ACME operator * (i32 i, const property& prop) { return operator * (i, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator * (u32 user, const ::property& prop) { return operator * (user, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator * (i64 i, const property& prop) { return operator * (i, (const ::payload&) prop); }
//inline ::payload CLASS_DECL_ACME operator * (u64 u, const property& prop) { return operator * (u, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator * (double d, const property& prop) { return operator * (d, (const ::payload&)prop); }
//inline ::payload CLASS_DECL_ACME operator * (const ::payload & payload, const property& prop) { return operator * (payload, (const ::payload&)prop); }





//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR >::string_base(const ::property & property) :
//   string_base(property.string())
//{
//
//
//}
//


//template < typename TYPE_CHAR >
//string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const ::property & property)
//{
//
//   return append(property);
//
//}
//


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const ::property & property) :
//   string_base(property.as_string())
//{
//
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::property & property)
//{
//
//   assign(property.as_string());
//
//   return *this;
//
//}


//template < strsize n >
//::string operator + (const ::property & property, const char (&cha)[n])
//{
//
//   return ::transfer(property.get_string() + cha);
//
//}
//

template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const ::property & property)
{

   return operator=(property.as_string());

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator += (const ::property & property)
{

   return this->append(property);

}


template < typename ITERATOR_TYPE >
string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::append(const ::property & property)
{

   return append((const ::payload &)property);

}

namespace file
{


   inline path::path(const ::property & property) :
      path(property.as_file_path())
   {

   }


} // namespace file






