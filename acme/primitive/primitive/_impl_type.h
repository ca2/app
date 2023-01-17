//
// Created by camilo on 23/12/2022 02:48 <3ThomasBorregaardSørensen!!
//
#pragma once


inline type::type(const ::std::type_info & typeinfo) :
#ifdef WINDOWS
        atom(c_demangle(typeinfo.name()))
#else
        atom(demangle(typeinfo.name()))
#endif
{

}


inline bool type::name_contains(const ::ansi_character * psz) const
{

   return m_str.contains(psz);

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

   auto pszType = typeid(*p).name();

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



