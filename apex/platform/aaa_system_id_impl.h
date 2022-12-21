#pragma once




//
//
//inline atom::atom(const ::scoped_string & scopedstr)
//{
//
//   m_all = {};
//
//   if(psz != nullptr)
//   {
//
//      operator = (::apex::system::atom(psz));
//
//   }
//
//}
//
//
//inline atom::atom(const ::string & str)
//{
//
//   m_all = {};
//
//   operator = (::apex::system::atom(str.c_str()));
//
//}
//
//
//inline atom::atom(const type & type) :
//   atom((const string &) type.to_string())
//{
//
//}
//
//inline atom & atom::operator = (::i32 i)
//{
//   
//   m_etype     = type_integer;
//   
//   m_i         = i;
//   
//   return *this;
//
//}
//
//
//inline atom & atom::operator = (::i64 i)
//{
//
//   m_etype     = type_integer;
//
//   m_i         = i;
//
//   return *this;
//
//}
//
//
//inline atom & atom::operator = (::u64 u)
//{
//   
//   m_etype     = type_integer;
//   
//   m_u         = u;
//   
//   return *this;
//   
//}
//
//
//inline atom & atom::operator = (const ::enum_property & eproperty)
//{
//
//   m_etype = type_property;
//
//   m_eproperty = eproperty;
//
//   return *this;
//
//}
//
//
//inline atom & atom::operator = (const ::enum_factory & efactory)
//{
//
//   m_etype = type_factory;
//
//   m_efactory = efactory;
//
//   return *this;
//
//}
//
//
//inline atom& atom::operator = (const ::enum_task_tool & ethreadtool)
//{
//
//   m_etype = type_thread_tool;
//
//   m_ethreadtool = ethreadtool;
//
//   return *this;
//
//}
//
//
