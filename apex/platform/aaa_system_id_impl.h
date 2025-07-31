#pragma once




//
//
//inline atom::atom(const ::scoped_string & scopedstr)
//{
//
//   m_all = {};
//
//   if(scopedstr != nullptr)
//   {
//
//      operator = (::apex::system::atom(scopedstr));
//
//   }
//
//}
//
//
//inline atom::atom(const ::scoped_string & scopedstr)
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
//inline atom & atom::operator = (int i)
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
//inline atom & atom::operator = (long long i)
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
//inline atom & atom::operator = (unsigned long long u)
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
