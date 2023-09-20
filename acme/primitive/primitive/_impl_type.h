//
// Created by camilo on 23/12/2022 02:48 <3ThomasBorregaardSorensen!!
//
#pragma once


inline type_atom::type_atom(const ::std::type_info & typeinfo) :
#ifdef WINDOWS
        atom(c_demangle(typeinfo.name()))
#else
        atom(demangle(typeinfo.name()))
#endif
{

}


inline bool type_atom::name_contains(const ::ansi_character * psz) const
{

   return m_str.contains(psz);

}


inline bool type_atom::operator == (const ::atom& atom) const
{

   return ::atom::operator ==(atom);

}


template < typename BASE >
inline type_atom::type_atom(const ::pointer<BASE>& p)
{

   auto name = typeid(*((BASE *)p.m_p)).name();

   ::atom::operator = (demangle(name));

}


//template < typename TYPE >
//inline string __type_name()
//{
//
//   auto pszType = typeid(TYPE).name();
//
//   string strName = demangle(pszType);
//
//   return strName;
//
//}
//
//
//template < typename TYPE >
//inline string __type_name(const TYPE * p)
//{
//
//   auto pszType = typeid(*p).name();
//
//   string strName = demangle(pszType);
//
//   return strName;
//
//}
//
//
//template < typename TYPE >
//inline string __type_name(const TYPE & t)
//{
//
//   auto pszType = typeid(t).name();
//
//   string strName = demangle(pszType);
//
//   return strName;
//
//}



