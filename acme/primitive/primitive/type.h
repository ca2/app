#pragma once


#include "atom.h"


CLASS_DECL_ACME string demangle(const char * psz);


#ifdef WINDOWS


#define __c_type_name(t) (c_demangle(typeid(t).name()))


inline const char * c_demangle(const char * psz)
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
//inline const char * c_demangle(const char * psz)
//{
//
//   return psz;
//
//}


#endif


#define __object_type(t) ::type(e_data_structure_type, t)


enum enum_data_structure_type
{

   e_data_structure_type

};


class CLASS_DECL_ACME type :
   public atom
{
public:


   type()
   {

   }


   template < typename TYPE >
   type(enum_data_structure_type, const TYPE &) :
#ifdef WINDOWS
   atom(c_demangle(typeid(TYPE).name()))
#else
   atom(demangle(typeid(TYPE).name()))
#endif
   {


   }


   type(const char * pszTypeName) :
      atom(pszTypeName)
   {
      
   }


   type(const ::type & type)
   {

      operator = (type);

   }


   type(::type && type):
      atom((::atom &&)::move(type))
   {

   }


   type(const ::std::type_info & typeinfo)
   {

      operator = (typeinfo);

   }

   type(const ::particle * pparticle);

   template < typename BASE >
   type(const ::pointer<BASE>& point);


   type& operator = (const ::std::type_info& typeinfo);


   type& operator = (const ::type& type);
   

   const ::atom & name() const { return *this; }


   bool operator == (const ::std::type_info& typeinfo) const;


   bool operator == (const ::type& type) const;


   bool operator == (const ::string& strType) const;


   bool operator == (const ::atom& atom) const;


   bool operator != (const ::std::type_info& typeinfo) const;


   bool operator != (const ::type& type) const;


   bool operator == (const ::particle* pparticle) const;


   bool operator != (const ::particle* pparticle) const;


   inline operator bool() const { return ::atom::has_char(); }

   inline operator const char * () const { return ::atom::operator const char *(); }

   bool name_contains(const char * psz) const
   {

      return m_str.contains(psz) == 0;

   }


};


template < typename TYPE >
::type ___type()
{

   return ::type(typeid(TYPE));

}


//#define __type(TYPE)  ___type<TYPE>()

#define __type(TYPE)  ___type<TYPE>()


template < typename TYPE >
inline string __type_name()
{

   auto pszType = typeid(TYPE).name();

   string strName = demangle(pszType);

   return strName;

}


template < typename TYPE >
inline string __type_name(const TYPE & t)
{

   auto pszType = typeid(t).name();

   string strName = demangle(pszType);

   return strName;

}


inline bool type::operator == (const ::atom& atom) const
{

   return ::atom::operator ==(atom);

}


template < typename BASE >
inline type::type(const ::pointer<BASE>& point)
{

   auto name = typeid(*((BASE *)point.m_p)).name();

   ::atom::operator = (demangle(name));

}



