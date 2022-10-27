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
   type(enum_data_structure_type, TYPE) :
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
      atom(::move(type))
   {

   }


   type(const ::std::type_info & typeinfo)
   {

      operator = (typeinfo);

   }

   type(const ::particle * pparticle);

   template < typename BASE >
   type(const ::pointer<BASE>& point);


   type & operator = (const ::std::type_info & typeinfo)
   {

      ::string strName = typeinfo.name();
      
      strName = demangle(strName);
      
      ::atom::operator =(strName);

      return *this;

   }


   type & operator = (const ::type & type)
   {

      if (this != &type)
      {

         ::atom::operator =(type);

      }

      return *this;

   }


   const ::atom & name() const { return *this; }


   bool operator == (const ::std::type_info & typeinfo) const
   {

      ::string strName = ::type(typeinfo).name();

      strName = demangle(strName);

      return operator==(strName);

   }


   bool operator == (const ::type & type) const
   {

      return ::atom::operator == (type);

   }

   bool operator == (const ::string & strType) const
   {

      return ::atom::operator == (strType);

   }


   bool operator == (const ::atom& atom) const;


   bool operator != (const ::std::type_info & typeinfo) const
   {

      return !operator==(typeinfo);

   }


   bool operator != (const ::type & type) const
   {

      return !operator==(type);

   }


   bool operator == (const ::particle * pparticle) const
   {

      return operator ==(::type(pparticle));

   }


   bool operator != (const ::particle * pparticle) const
   {

      return !operator==(pparticle);

   }


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
inline string __type_name(const TYPE * p)
{

   TYPE * pNonConst = (TYPE *) p;

   auto pszType = typeid(*pNonConst).name();

   string strName = demangle(pszType);

   return strName;

}


template < typename TYPE >
inline string __type_name(const ::pointer<TYPE>& pointer)
{

   return __type_name((const TYPE *) pointer.m_p);

}


template < non_pointer NON_POINTER >
inline string __type_name(const NON_POINTER & t)
{

   NON_POINTER & tNonConst = (NON_POINTER &) t;

   auto pszType = typeid(tNonConst).name();

   string strName = demangle(pszType);

   return strName;

}


template < >
inline uptr uptr_hash < const type & >(const ::type & type)
{

   return uptr_hash < const ::atom & > (type);

}



inline bool type::operator == (const ::atom& atom) const
{

   return ::atom::operator ==(atom);

}



