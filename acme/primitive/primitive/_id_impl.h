// Included enum_dialog_result camilo on 2021-01-21 05:53 PM <3ThomasBorregaardSørensen
#pragma once


namespace acme
{


   inline ::id id(const class ::payload & payload)
   {
      
      return ::id(payload.id());

   }

   
   inline ::id id(const ::property & property)
   {
      
      return ::id(property);

   }


   inline ::id id(const ::std::type_info& info)
   {

#ifdef WINDOWS

      return get_id_space()(info.name());

#else

      return get_id_space()(info.name());

#endif

   }


   inline ::id id(const char* psz)
   {

      return get_id_space()(psz);

   }


   inline ::id id(const string& str)
   {

      return get_id_space()(str);

   }


   inline ::id id(i64 i)
   {

      return get_id_space()(i);

   }


   inline id_space& id()
   {

      return get_id_space();

   }


} //namespace acme


#pragma once



//namespace acme
//{
//
//   inline id system::id(const class ::payload & payload)
//   {
//      return ::id((const char *)(class ::payload &) payload);
//   }
//
//   inline id system::id(const property & prop)
//   {
//      return ::id((const string &)(property &)prop);
//   }
//
//
//   inline id system::id(const ::std::type_info & info)
//   {
//#ifdef WINDOWS
//      return get_id_space()(info.name());
//#else
//      return get_id_space()(info.name());
//#endif
//   }
//
//   inline id system::id(const char * psz)
//   {
//      return get_id_space()(psz);
//   }
//
//   inline id system::id(const ::string & str)
//   {
//      return get_id_space()(str);
//   }
//
//   inline id system::id(i64 i)
//   {
//      return get_id_space()(i);
//   }
//
//   inline id_space & system::id()
//   {
//      return get_id_space();
//   }
//
//
//} //namespace acme


namespace acme
{

   CLASS_DECL_ACME::id id(const char* psz);

} // namespace acme


inline id::id(const char* psz)
{

   m_all = {};

   if (psz != nullptr)
   {

      operator = (::acme::id(psz));

   }

}


inline id::id(const string& str)
{

   m_all = {};

   operator = (::acme::id(str.c_str()));

}


inline id::id(const type& type) :
   id((const string&)type.to_string())
{

}


template < primitive_integer INTEGER >
inline id& id::operator = (INTEGER i)
{

   m_etype = e_type_integer;

   m_i = i;

   return *this;

}


template < primitive_natural NATURAL >
inline id& id::operator = (NATURAL n)
{

   m_etype = e_type_integer;

   m_i = n;

   return *this;

}


inline id& id::operator = (const ::enum_id& eid)
{

   m_etype = e_type_id;

   m_eid = eid;

   return *this;

}


inline id& id::operator = (const ::enum_property& eproperty)
{

   m_etype = e_type_property;

   m_eproperty = eproperty;

   return *this;

}


inline id& id::operator = (const ::enum_factory& efactory)
{

   m_etype = e_type_factory;

   m_efactory = efactory;

   return *this;

}


inline id& id::operator = (const ::enum_task_tool& etasktool)
{

   m_etype = e_type_task_tool;

   m_etasktool = etasktool;

   return *this;

}


inline id& id::operator = (const ::enum_timer& etimer)
{

   m_etype = e_type_timer;

   m_etimer = etimer;

   return *this;

}



inline id& id::operator = (const ::enum_message & emessage)
{

   m_etype = e_type_message;

   m_emessage = emessage;

   return *this;

}


//inline id& id::operator = (const ::id & id)
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

inline id & id::operator = (const ::enum_dialog_result & edialogresult)
{

   m_etype = e_type_dialog_result;

   m_edialogresult = edialogresult;

   return *this;

}



