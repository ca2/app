// Included enum_dialog_result camilo on 2021-01-21 05:53 PM <3ThomasBorregaardSørensen
#pragma once

//
//namespace acme
//{
//
//
//   inline ::atom atom(const class ::payload & payload)
//   {
//      
//      return ::atom(payload.atom());
//
//   }
//
//   
//   inline ::atom atom(const ::property & property)
//   {
//      
//      return ::atom(property);
//
//   }
//
//
//   inline ::atom atom(const ::std::type_info& info)
//   {
//
////#ifdef WINDOWS
////
////      return get_id_space()(info.name());
////
////#else
////
//      return info.name();
//
////#endif
//
//   }
//
//
//   inline ::atom atom(const char* psz)
//   {
//
//      return psz;
//
//   }
//
//
//   inline ::atom atom(const string& str)
//   {
//
//      return str;
//
//   }
//
//
//   inline ::atom atom(i64 i)
//   {
//
//      return i;
//
//   }
//
//
//   //inline atom_space& atom()
//   //{
//
//   //   return get_id_space();
//
//   //}
//
//
//} //namespace acme
//

#pragma once



//namespace acme
//{
//
//   inline atom system::atom(const class ::payload & payload)
//   {
//      return ::atom((const char *)(class ::payload &) payload);
//   }
//
//   inline atom system::atom(const property & prop)
//   {
//      return ::atom((const string &)(property &)prop);
//   }
//
//
//   inline atom system::atom(const ::std::type_info & info)
//   {
//#ifdef WINDOWS
//      return get_id_space()(info.name());
//#else
//      return get_id_space()(info.name());
//#endif
//   }
//
//   inline atom system::atom(const char * psz)
//   {
//      return get_id_space()(psz);
//   }
//
//   inline atom system::atom(const ::string & str)
//   {
//      return get_id_space()(str);
//   }
//
//   inline atom system::atom(i64 i)
//   {
//      return get_id_space()(i);
//   }
//
//   inline atom_space & system::atom()
//   {
//      return get_id_space();
//   }
//
//
//} //namespace acme


namespace acme
{

   CLASS_DECL_ACME::atom atom(const char* psz);

} // namespace acme


inline atom::atom(const char* psz)
{

   m_etype = e_type_text;

   ::new(&m_str) ::string(psz);

}


inline atom::atom(const ::string& str)
{

   m_etype = e_type_text;

   ::new(&m_str) ::string(str);

}


//inline atom::atom(const type& type) :
//   atom(type)
//{
//
//}


//template < primitive_integer INTEGER >
//inline atom& atom::operator = (INTEGER i)
//{
//
//   m_etype = e_type_integer;
//
//   m_i = i;
//
//   return *this;
//
//}
//
//
//template < primitive_natural NATURAL >
//inline atom& atom::operator = (NATURAL n)
//{
//
//   m_etype = e_type_integer;
//
//   m_i = n;
//
//   return *this;
//
//}
//
//
//inline atom& atom::operator = (const ::enum_id& eid)
//{
//
//   m_etype = e_type_id;
//
//   m_eid = eid;
//
//   return *this;
//
//}
//
//
//inline atom& atom::operator = (const ::enum_property& eproperty)
//{
//
//   m_etype = e_type_property;
//
//   m_eproperty = eproperty;
//
//   return *this;
//
//}
//
//
//inline atom& atom::operator = (const ::enum_factory& efactory)
//{
//
//   m_etype = e_type_factory;
//
//   m_efactory = efactory;
//
//   return *this;
//
//}
//
//
//inline atom& atom::operator = (const ::enum_task_tool& etasktool)
//{
//
//   m_etype = e_type_task_tool;
//
//   m_etasktool = etasktool;
//
//   return *this;
//
//}
//
//
//inline atom& atom::operator = (const ::enum_timer& etimer)
//{
//
//   m_etype = e_type_timer;
//
//   m_etimer = etimer;
//
//   return *this;
//
//}
//
//
//
//inline atom& atom::operator = (const ::enum_message & emessage)
//{
//
//   m_etype = e_type_message;
//
//   m_emessage = emessage;
//
//   return *this;
//
//}


//inline atom& atom::operator = (const ::atom & atom)
//{
//
//   m_etype = e_type_subject;
//
//   m_etopic = etopic;
//
//   return *this;
//
//}
//

//inline atom & atom::operator = (const ::enum_dialog_result & edialogresult)
//{
//
//   m_etype = e_type_dialog_result;
//
//   m_edialogresult = edialogresult;
//
//   return *this;
//
//}
//
//
//
