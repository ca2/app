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


//inline bool type_atom::name_contains(const ::ansi_character * psz) const
//{
//
//   return m_str.contains(psz);
//
//}


inline bool type_atom::operator == (const ::atom& atom) const
{

   return ::atom::operator ==(atom);

}


type_atom::type_atom(const ::quantum * p)
{

   if(::is_null(p))
   {

      set_type(atom::e_type_null);

   }
   else
   {

      auto name = typeid(*(::quantum *) p).name();

      ::atom::operator=(demangle(name));

   }

}


template < primitive_object_not_type_atom OBJECT_NOT_TYPE_ATOM >
type_atom::type_atom(OBJECT_NOT_TYPE_ATOM & objectnottypeatom)
{

   auto name = typeid(*(&(non_const < OBJECT_NOT_TYPE_ATOM > &)objectnottypeatom)).name();

   ::atom::operator = (demangle(name));

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


inline bool type_atom::operator == (const ::quantum * p) const
{

   return operator ==(::type_atom(p));

}



template < typename TYPE >
inline bool type_atom::operator == (const ::pointer < TYPE > & p) const
{

   return this->operator==(p.m_p);

}



