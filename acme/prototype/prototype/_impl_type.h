//
// Created by camilo on 23/12/2022 02:48 <3ThomasBorregaardSorensen!!
//
#pragma once


//inline type_name::type(const ::std::type_info & typeinfo) :
//   m_pszRawName(typeinfo.raw_name())
//{
//
//}
//
//
//inline bool type_name::operator == (const ::type& type) const
//{
//
//   return m_pszRawName == type.m_pszRawName
//      || !strcmp(m_pszRawName, type.m_pszRawName)
//      || m_strDemangled == type.m_strDemangled;
//
//}
//
//
//
//inline bool type_name::operator == (const ::atom& atom) const
//{
//
//   return atom.as_string() == m_pszRawName ||
//      m_strDemangled == atom.as_string();
//
//}
//
//
//inline type_name::type(const ::quantum * p)
//{
//
//   if(::is_null(p))
//   {
//
//      m_pszRawName = nullptr;
//      m_strDemangled.empty();
//
//   }
//   else
//   {
//
//      this->operator=(typeid(*(::quantum*)p));
//
//   }
//
//}
//
//
//template < primitive_object_not_type_atom OBJECT_NOT_TYPE_ATOM >
//type_name::type(OBJECT_NOT_TYPE_ATOM & objectnottypeatom)
//{
//
//   this->operator = (typeid(*(&(non_const < OBJECT_NOT_TYPE_ATOM > &)objectnottypeatom)));
//
//}
//
//
//template < typename BASE >
//inline type_name::type(const ::pointer<BASE>& p)
//{
//
//   this->operator = (typeid(*((BASE*)p.m_p)));
//
//}


//template < typename TYPE >
//inline string __type_name()
//{
//
//   auto pszType = typeid(TYPE).name();
//
//   string strName = demangle(scopedstrType);
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
//   string strName = demangle(scopedstrType);
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
//   string strName = demangle(scopedstrType);
//
//   return strName;
//
//}
//
//
//inline bool type_name::operator == (const ::quantum * p) const
//{
//
//   return operator ==(::type(p));
//
//}
//
//
//
//template < typename TYPE >
//inline bool type_name::operator == (const ::pointer < TYPE > & p) const
//{
//
//   return this->operator==(p.m_p);
//
//}
//
//

