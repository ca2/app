#pragma once


#include "atom.h"


CLASS_DECL_ACME string demangle(const char * pszMangledName);


#ifdef WINDOWS


#define __c_type_name(t) (c_demangle(typeid(t).name()))


inline const char * c_demangle(const ::ansi_character * psz)
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
//inline const char * c_demangle(const ::scoped_string & scopedstr)
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


class type_atom;


template < typename OBJECT_NOT_TYPE_ATOM >
concept primitive_object_not_type_atom =
   primitive_object < OBJECT_NOT_TYPE_ATOM >
      && !std::is_same_v < OBJECT_NOT_TYPE_ATOM, type_atom >
      && !std::is_base_of_v < type_atom, OBJECT_NOT_TYPE_ATOM >;


class CLASS_DECL_ACME type_atom :
   public atom
{
public:


   //type()
   //{
   //
   //}


   using atom::atom;


//   template < typename TYPE >
//   type_atom(enum_data_structure_type, const TYPE &) :
//#ifdef WINDOWS
//   atom(c_demangle(typeid(TYPE).name()))
//#else
//   atom(demangle(typeid(TYPE).name()))
//#endif
//   {
//
//
//   }


   //type_atom(const ::scoped_string & scopedstrTypeName) :
   //   atom(scopedstrTypeName)
   //{
   //   
   //}


   type_atom(const ::type_atom & typeatom)
   {

      operator = (typeatom);

   }


   type_atom(::type_atom && typeatom):
      atom((::atom &&)::transfer(typeatom))
   {

   }


   type_atom(const ::std::type_info & typeinfo);

   type_atom(const ::quantum * p);

   template < primitive_object_not_type_atom OBJECT_NOT_TYPE_ATOM >
   type_atom(OBJECT_NOT_TYPE_ATOM & objectnottypeatom);

   template < typename BASE >
   type_atom(const ::pointer<BASE>& p);


   //type& operator = (const ::std::type_info& typeinfo);


   //type& operator = (const ::type& type);


   type_atom& operator = (const ::type_atom& datatype)
   {

      ::atom::operator = (datatype);

      return *this;

   }
   

   ::string name() const { return this->as_string(); }


   bool operator == (const ::std::type_info& typeinfo) const;


//   bool operator == (const ::type_atom& datatype) const;
//
//
//   bool operator == (const ::scoped_string & scopedstrType) const;


   bool operator == (const ::atom& atom) const;


//   bool operator != (const ::std::type_info& typeinfo) const;
//
//
//   bool operator != (const ::type_atom& type) const;


   bool operator == (const ::quantum * p) const;


   template < typename TYPE >
   bool operator == (const ::pointer < TYPE > & p) const;


   //bool operator != (const ::quantum* pparticle) const;


   inline operator bool() const { return ::atom::has_character(); }

   //inline operator const char * () const { return ::atom::operator const char *(); }

   //bool name_contains(const ::ansi_character * psz) const;


};


template < typename TYPE >
class typed_type_atom :
   public ::type_atom
{
public:


   typed_type_atom() :
      type_atom(typeid(TYPE))
   {
   }

};


template < typename TYPE >
inline ::typed_type_atom < TYPE > type()
{

   return {};

}


inline ::type_atom type(const ::quantum * p)
{

   return p;

}


template < primitive_object OBJECT >
inline ::type_atom type(OBJECT & object)
{

   return object;

}


//#define ::type < TYPE >()  ___type<TYPE>()

//#define ::type < TYPE >()  ___type<TYPE>()


//template < typename TYPE >
//inline string __type_name();


//template < typename TYPE >
//inline string __type_name(const TYPE * p);


//template < typename TYPE >
//inline string __type_name(const TYPE & t);


//template < typename BASE >
//inline type::type(const ::pointer<BASE>& point);



