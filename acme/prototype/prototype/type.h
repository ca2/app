#pragma once


//#include "atom.h"


#include "acme/template/safe_bool.h"

#include <typeindex>

#include "atom.h"


constexpr ::std::strong_ordering order(bool b1, bool b2)
{

   if (!!b1)
   {

      if (!!b2)
      {

         return ::std::strong_ordering::equal;

      }
      else
      {

         return ::std::strong_ordering::greater;

      }

   }
   else if (!!b2)
   {

      return ::std::strong_ordering::less;

   }

   return ::std::strong_ordering::equal;

}

class type_id
{
public:


   /// type index as obtained from ::std::type_index(typeid())
   ::std::type_index m_typeindex;
   /// raw type name as obtained from typeid().raw_name()
   ::string m_strRawTypeName;
   /// type name as obtained from demangle(typeid().name())
   ::string m_strTypeName;


   inline type_id();
   inline type_id(const ::type_id &type_id);
   inline type_id(const ::std::type_info &info);


   inline bool is_set() const;
   inline bool is_empty() const {return !this->is_set();}

   inline bool operator == (const ::type_id & type_id) const;
   inline ::std::strong_ordering operator <=> (const ::type_id & type_id) const;

   ::string as_string() const;

};


template < typename TYPE >
constexpr TYPE minus_one_or_greater(const TYPE & t)
{
   return t <= -1 ? -1 : t;
}

class type_iptr_pair : 
   public ::pair<::iptr, ::iptr>
{
public:


   type_iptr_pair(::iptr i1 = -1, ::iptr i2 = -1):
   ::pair<::iptr, ::iptr>(i1, i2)
   {


   }

   template < typename ENUM>
   requires(::std::is_enum_v<ENUM>)
   type_iptr_pair(::atom::enum_type etype, const ENUM & eenum) :
   type_iptr_pair((::iptr) etype,(::iptr) eenum)
   {


   }

   type_iptr_pair(enum_task_tool etasktool) :
   type_iptr_pair(::atom::e_type_task_tool, etasktool)
   {


   }


   constexpr bool is_empty() const { return this->m_element1 < 0; }
   constexpr bool is_set() const { return !this->is_empty(); }

   constexpr iptr normal1() const { return (::iptr)::minus_one_or_greater(this->m_element1); }
   constexpr iptr normal2() const { return (::iptr)::minus_one_or_greater(this->m_element2); }


   constexpr inline bool operator == (const ::type_iptr_pair & ipair) const
   {

      return this->normal1() == ipair.normal1()  && this->normal2() == ipair.normal2();

   }


   constexpr ::std::strong_ordering operator <=> (const ::type_iptr_pair & ipair) const
   {

      auto order = this->normal1() <=> ipair.normal1();

      if (order != 0)
      {

         return order;

      }

      order = this->normal2() <=> ipair.normal2();

      return order;

   }


   ::string as_string() const;


}; 
template<>
constexpr ::hash32 as_hash32<type_iptr_pair>(const type_iptr_pair &pair)
{
   return (::hash32)abs(pair.normal1()) +
          (::hash32)abs(pair.normal2());
}

class type_custom_id
{
public:

   //::string m_strText;
   /// m_strText if present, is just a key and/or a
   /// string representation of the type,
   /// not literally the real type name.
   ::string m_strNameId;
   /// m_ipair isn't empty it can be used as a key
   ::type_iptr_pair m_ipairId;

   type_custom_id();
   type_custom_id(const_char_pointer pszNameId);
   type_custom_id(const ::string_literal < const_char_pointer > & strliteralNameId);
   type_custom_id(const ::scoped_string & scopedstrNameId);
   type_custom_id(const ::type_iptr_pair & ipairId);
   type_custom_id(const ::scoped_string & scopedstrNameId, const ::type_iptr_pair & ipairId);
   type_custom_id(const ::atom & atom);
   type_custom_id(enum_task_tool etasktool);


   constexpr bool is_set() const;
   constexpr bool is_empty() const{return !this->is_set();}


   inline bool operator == (const ::type_custom_id & typecustomid) const;
   inline ::std::strong_ordering operator <=> (const ::type_custom_id & typecustomid) const;

   ::string as_string() const;

};
CLASS_DECL_ACME string type_name(const ::std::type_info& typeinfo);

template<typename TYPE>
inline ::std::type_index type_index() { return typeid(TYPE); }


template<typename TYPE>
inline ::string type_name()
{
   return type_name(typeid(TYPE));
}

inline ::std::type_index void_type_index()
{

   return typeid(void);

}


inline bool is_type_index_empty(const ::std::type_index & typeindex)
{

   return typeindex == ::void_type_index();

}


inline bool is_type_index_set(const ::std::type_index & typeindex)
{

   return !is_type_index_empty(typeindex);

}


inline ::std::type_index type_index(const ::std::type_info &typeinfo) { return typeinfo; }


#ifdef WINDOWS


#define __c_type_name(t) (c_demangle(::type<t>().name()))


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


//#define __object_type(t) ::platform::type(data_structure_t{}, t)
//
//
//struct data_structure_t {};


//class raw_literal;
//
//
//template < typename OBJECT_NOT_TYPE_ATOM >
//concept prototype_object_not_type_atom =
//   prototype_object < OBJECT_NOT_TYPE_ATOM >
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
////   atom(c_demangle(::type<TYPE>().name()))
////#else
////   atom(demangle(::type<TYPE>().name()))
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
//   template < prototype_object_not_type_atom OBJECT_NOT_TYPE_ATOM >
//   raw_literal(OBJECT_NOT_TYPE_ATOM & objectnottypeatom);
//
//   template < typename BASE >
//   raw_literal(const ::pointer<BASE>& p);
//
//
//   //type& operator = (const ::std::type_info& typeinfo);
//
//
//   //type& operator = (const ::platform::type & type);
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
//      raw_literal(::type<TYPE>())
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
//template < prototype_object OBJECT >
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


namespace platform
{


   class CLASS_DECL_ACME type
   {
   public:


      ::type_id            m_typeid;
      ::type_custom_id     m_customid;


      //type();
      //explicit type(const ::std::type_info &info);
      //type(const ::scoped_string &scopedstrTypeName);
      //template < typename TYPE >
      //type(const TYPE* p) : type(typeid(*(TYPE*)p)) {}
      //template < typename TYPE >
      //type(const TYPE& t) : type(typeid(t)) {}
      //template < typename BASE >
      //type(const ::pointer<BASE>& p) : type(p.m_p) {}


      type();
      type(const ::platform::type &type);
      type(const ::std::type_info &info);
      type(const ::scoped_string &scopedstrTypeName);
      type(const ::type_iptr_pair &ipair);
      type(const ::atom &atom);


      template<typename TYPE>
      type(const TYPE *p);
      template<typename TYPE>
      type(const TYPE &t)
         requires (!is_raw_pointer <TYPE>);
      template<typename BASE>
      type(const ::pointer<BASE> &p);


      const ::string &raw_name() const;
      const ::string &name() const;
      const char *c_str() const;
      const ::string & text() const;
      bool is_set() const;
      bool is_empty() const;
      explicit operator bool() const;
      
      bool operator==(const ::platform::type &type) const;

      ::std::strong_ordering operator<=>(const ::platform::type &type) const;

      ::string as_string() const;


   };


} // namespace platform


template<typename TYPE>
inline ::platform::type type();
inline ::platform::type type(const ::std::type_info &info);
inline ::platform::type type(const ::scoped_string &scopedstrTypeName);


template<typename TYPE>
inline ::platform::type type(const TYPE *p);

template<typename TYPE>
inline ::platform::type type(const TYPE &t);

template<typename BASE>
inline ::platform::type type(const ::pointer<BASE> &p);






//template < >
//inline ::hash32 as_hash32 < type >(const ::platform::type & type)
//{
//
//   return ::as_hash32(name.m_strTypeName);
//
//}
//
//


//template < typename TYPE >
//inline ::type as_type()
//{
//
//   return typeid(TYPE);
//
//}

