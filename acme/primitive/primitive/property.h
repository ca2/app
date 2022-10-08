#pragma once



class property;
class action_context;


#include "acme/memory/property_memory_allocate.h"


namespace xml
{

   class disp_option;

} // namespace xml

//::string CLASS_DECL_ACME operator + (const char * psz, const property & prop);
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


class CLASS_DECL_ACME property : public ::payload
{
public:


   using TYPE1 = ::atom;
   using ARG_TYPE1 = const ::atom &;
   using TYPE2 = payload;
   using ARG_TYPE2 = const ::payload &;


   ::atom              m_atom;


   property() { on_property_construct(this); }
   property(const ::atom& atom) : m_atom(atom) { on_property_construct(this); }
   property(const ::atom& atom, const ::payload& varValue) : m_atom(atom), ::payload(varValue) { on_property_construct(this); }
   property(const ::property& property) : m_atom(property.m_atom), ::payload(property) { on_property_construct(this); }
   property(::property&& property) : m_atom(::move(property.m_atom)), ::payload(::move(property)) { on_property_construct(this); }
   ~property() { on_property_destruct(this); }


   void* operator new(size_t size)
   {

      return property_memory_allocate(size);

   }


   void* operator new(size_t size, const char* /* pszFileName */, int /* nLine */)
   {

      return property_memory_allocate(size);

   }


   void operator delete(void * p)
   {

      return property_memory_free(p);

   }


   void operator delete(void * p, const char* /* pszFileName */, int /* nLine */)
   {

      return property_memory_free(p);

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
   inline __pointer(T)& defer_get(__pointer(T)& pointer) { return pointer = cast < T >(); }

};


using property_pointer = ::property *;


CLASS_DECL_ACME void property_parse_network_payload_id(atom & atom, const char *& pszJson, const char * pszEnd);
CLASS_DECL_ACME void property_parse_network_payload_value(::payload & payload, const char *& pszJson, const char * pszEnd);
CLASS_DECL_ACME void property_skip_network_payload_id(const char *& pszJson, const char * pszEnd);
CLASS_DECL_ACME void property_skip_network_payload_value(const char *& pszJson, const char * pszEnd);


#include "acme/primitive/collection/ptr_array.h"
#include "acme/primitive/collection/auto_ptr_array.h"


using property_ptra = auto_ptr_array < ::property >;

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


//#define memory_new ACME_NEW
