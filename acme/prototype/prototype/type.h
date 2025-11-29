#pragma once


#include "atom.h"


#include "acme/template/safe_bool.h"

#include <typeindex>


//CLASS_DECL_ACME string demangle_name(const_char_pointer pszMangledName);
CLASS_DECL_ACME string type_name(const ::std::type_info& typeinfo);


#ifdef WINDOWS


#define __c_type_name(t) (c_demangle(typeid(t).name()))


inline const_char_pointer c_demangle(const_char_pointer psz)
{

   if (psz[0] == 'c' &&
      psz[1] == 'l' &&
      psz[2] == 'a' &&
      psz[3] == 's' &&
      psz[4] == 's' &&
      psz[5] == ' ')
   {

      return psz + 6;

   }
   else if (psz[0] == 's' &&
      psz[1] == 't' &&
      psz[2] == 'r' &&
      psz[3] == 'u' &&
      psz[4] == 'c' &&
      psz[5] == 't' &&
      psz[6] == ' ')
   {

      return psz + 7;

   }
   else
   {

      return psz;

   }

}
#else
//inline const_char_pointer c_demangle(const ::scoped_string & scopedstr)
//{
//
//   return scopedstr;
//
//}


#endif


//#define __object_type(t) ::type(data_structure_t{}, t)
//
//
//struct data_structure_t {};


//class raw_literal;
//
//
//template < typename OBJECT_NOT_TYPE_ATOM >
//concept primitive_object_not_type_atom =
//   primitive_object < OBJECT_NOT_TYPE_ATOM >
//      && !std::is_same_v < OBJECT_NOT_TYPE_ATOM, raw_literal >
//      && !std::is_base_of_v < raw_literal, OBJECT_NOT_TYPE_ATOM >;
//
//
//class CLASS_DECL_ACME raw_literal
//{
//public:
//
//
//   const char*    m_pszRawName = nullptr;
//   //::string       m_strDemangled;
//
//
//   //type()
//   //{
//   //
//   //}
//
//
//   //using atom::atom;
//
//
////   template < typename TYPE >
////   raw_literal(enum_data_structure_type, const TYPE &) :
////#ifdef WINDOWS
////   atom(c_demangle(typeid(TYPE).name()))
////#else
////   atom(demangle(typeid(TYPE).name()))
////#endif
////   {
////
////
////   }
//
//
//   //raw_literal(const ::scoped_string & scopedstrTypeName) :
//   //   atom(scopedstrTypeName)
//   //{
//   //   
//   //}
//
//
//   raw_literal(const ::raw_literal & type)
//   {
//
//      operator = (type);
//
//   }
//
//
//   raw_literal(::raw_literal && type):
//      m_pszRawName(type.m_pszRawName),
//      m_strDemangled(::transfer(type.m_strDemangled))
//   {
//
//   }
//
//
//   raw_literal(const ::std::type_info & typeinfo);
//
//   raw_literal(const ::quantum * p);
//
//   template < primitive_object_not_type_atom OBJECT_NOT_TYPE_ATOM >
//   raw_literal(OBJECT_NOT_TYPE_ATOM & objectnottypeatom);
//
//   template < typename BASE >
//   raw_literal(const ::pointer<BASE>& p);
//
//
//   //type& operator = (const ::std::type_info& typeinfo);
//
//
//   //type& operator = (const ::type& type);
//
//
//   raw_literal& operator = (const ::raw_literal& datatype)
//   {
//
//      m_pszRawName = datatype.m_pszRawName;
//      m_strDemangled = datatype.m_strDemangled;
//
//      return *this;
//
//   }
//   
//
//   const char * raw_name() const { return this->m_pszRawName; }
//   const ::string& id() const { return this->m_strDemangled; }
//
//
//   bool operator == (const ::std::type_info& typeinfo) const;
//
//
//   bool operator == (const ::raw_literal& type) const;
////
////
////   bool operator == (const ::scoped_string & scopedstrType) const;
//
//
//   bool operator == (const ::atom& atom) const;
//
//
////   bool operator != (const ::std::type_info& typeinfo) const;
////
////
////   bool operator != (const ::raw_literal& type) const;
//
//
//   bool operator == (const ::quantum * p) const;
//
//
//   template < typename TYPE >
//   bool operator == (const ::pointer < TYPE > & p) const;
//
//
//   //bool operator != (const ::quantum* pparticle) const;
//
//
//   inline operator bool() const { return m_pszRawName || m_strDemangled.has_character(); }
//
//   //inline operator const_char_pointer () const { return ::atom::operator const_char_pointer (); }
//
//   //bool name_contains(const_char_pointer psz) const;
//
//
//};
//
//
//template < typename TYPE >
//class typed_type_atom :
//   public ::raw_literal
//{
//public:
//
//
//   typed_type_atom() :
//      raw_literal(typeid(TYPE))
//   {
//   }
//
//};
//
//
//template < typename TYPE >
//inline ::typed_type_atom < TYPE > type()
//{
//
//   return {};
//
//}
//
//
//inline ::raw_literal type(const ::quantum * p)
//{
//
//   return p;
//
//}
//
//
//template < primitive_object OBJECT >
//inline ::raw_literal type(OBJECT & object)
//{
//
//   return object;
//
//}
//
//
////#define typeid(TYPE >()  ___type<TYPE)
//
////#define typeid(TYPE >()  ___type<TYPE)
//
//




class pointer_key
{
public:

   ::uptr      m_uptr;

   constexpr pointer_key() { m_uptr = 0; }
   constexpr pointer_key(const pointer_key& pointer) :m_uptr(pointer.m_uptr) {}
   template < typename TYPE >
   constexpr pointer_key(const TYPE* p) : m_uptr((::uptr)(void*)p) {}


   constexpr bool operator ==(const pointer_key& pointer) const
   {

      return this->m_uptr == pointer.m_uptr;

   }


   constexpr ::std::strong_ordering operator <=>(const pointer_key& pointer) const
   {

      return this->m_uptr <=> pointer.m_uptr;

   }


};



template < >
inline ::hash32 as_hash32 < pointer_key >(const pointer_key& key)
{

   return ::as_hash32(key.m_uptr);

}


inline ::string type_raw_name(const ::std::type_info & typeinfo)
{

#ifdef WINDOWS

   return (string_literal < const_char_pointer >) typeinfo.raw_name();

#else

   return (string_literal<const_char_pointer>) typeinfo.name();

#endif

}


template < typename TYPE >
inline ::string type_raw_name()
{

   return type_raw_name(typeid(TYPE));

}


template < typename TYPE >
inline ::string type_raw_name(const TYPE* p)
{

   return type_raw_name(typeid(*(TYPE*)p));

}


template < typename TYPE >
inline ::string type_raw_name(const TYPE& t)
{

   return type_raw_name(typeid(t));

}


template < typename BASE >
inline ::string type_raw_name(const ::pointer<BASE>& p)
{

   return type_name(typeid(*p.m_p));

}


//
//
//inline ::string type_name(const ::std::type_info& typeinfo)
//{
//
//   //#ifdef WINDOWS
//
//   return demangle_name(typeinfo.name());
//
//   //#else
//
//
//   //#endif
//
//
//}


class type
{
public:


   ::std::type_index    m_typeindex;
   ::string             m_strRawTypeName;
   ::string             m_strTypeName;


   type():m_typeindex(::std::type_index(typeid(nullptr))){}
   type(const type& type) :
      m_typeindex(type.m_typeindex),
      m_strRawTypeName(type.m_strRawTypeName),
      m_strTypeName(type.m_strTypeName) {}
   explicit type(const ::std::type_info& info) :
      m_typeindex(info),
      m_strRawTypeName(::type_raw_name(info)),
      m_strTypeName(::type_name(info)) {}
   type(const ::scoped_string& scopedstrTypeName) :
      m_typeindex(::std::type_index(typeid(nullptr))),
      m_strTypeName(scopedstrTypeName) {}
   template < typename TYPE >
   type(const TYPE* p) : type(typeid(*(TYPE*)p)) {}
   template < typename TYPE >
   type(const TYPE& t) : type(typeid(t)) {}
   template < typename BASE >
   type(const ::pointer<BASE>& p) : type(p.m_p) {}


   bool operator == (const type& type) const 
   {

      if (m_strRawTypeName.has_character() && type.m_strRawTypeName.has_character())
      {

         return m_strRawTypeName == type.m_strRawTypeName;

      }
      else
      {

         return m_strTypeName == type.m_strTypeName;

      }

   }


   ::std::strong_ordering operator <=> (const type & type) const 
   { 

      if (m_strRawTypeName.has_character() && type.m_strRawTypeName.has_character())
      {

         return m_strRawTypeName <=> type.m_strRawTypeName;

      }
      else
      {

         return m_strTypeName <=> type.m_strTypeName;

      }

   }


   const ::string& raw_name() const { return m_strRawTypeName; }
   const ::string& name() const { return m_strTypeName; }
   const char* c_str() const { return m_strTypeName.c_str(); }
   bool is_set() const { return name().has_character(); }
   bool is_empty() const { return !is_set(); }
   explicit operator bool() const { return is_set(); }
   //explicit operator pointer_key() const { return m_pszRawTypeName; }
   //explicit operator ::string() const { return m_strTypeName; }
   //bool boolean_test() const { return !is_empty(); }


};


//template < typename TYPE >
//inline ::string type_name()
//{
//
//   return type_name(typeid(TYPE));
//
//}
//
//
//template < typename TYPE >
//inline ::string type_name(const TYPE* p)
//{
//
//   return type_name(typeid(*(TYPE*)p));
//
//}
//
//
//template < typename TYPE >
//inline ::string type_name(const TYPE& t)
//{
//
//   return type_name(typeid(t));
//
//}
//
//
//template < typename BASE >
//inline ::string type_name(const ::pointer<BASE>& p)
//{
//
//   return type_name(typeid(*p.m_p));
//
//}
//



//template < >
//inline ::hash32 as_hash32 < type >(const type & type)
//{
//
//   return ::as_hash32(name.m_strTypeName);
//
//}
//
//


template < typename TYPE >
inline ::type as_type()
{

   return typeid(TYPE);

}

