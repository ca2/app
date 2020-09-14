#pragma once




//
//
//inline id::id(const char * psz)
//{
//
//   m_all = {};
//
//   if(psz != nullptr)
//   {
//
//      operator = (::apex::system::id(psz));
//
//   }
//
//}
//
//
//inline id::id(const string & str)
//{
//
//   m_all = {};
//
//   operator = (::apex::system::id(str.c_str()));
//
//}
//
//
//inline id::id(const type & type) :
//   id((const string &) type.to_string())
//{
//
//}
//
//inline id & id::operator = (::i32 i)
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
//inline id & id::operator = (::i64 i)
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
//inline id & id::operator = (::u64 u)
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
//inline id & id::operator = (const ::enum_property & eproperty)
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
//inline id & id::operator = (const ::enum_factory & efactory)
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
//inline id& id::operator = (const ::enum_thread_tool & ethreadtool)
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
