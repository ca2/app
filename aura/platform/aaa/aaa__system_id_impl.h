#pragma once



namespace aura
{

   inline id system::id(const class payload & payload)
   {
      return ::id((const char *)(class payload &) payload);
   }

   inline id system::id(const property & prop)
   {
      return ::id((const string &)(property &)prop);
   }


   inline id system::id(const ::std::type_info & info)
   {
#ifdef WINDOWS
      return get_id_space()(info.name());
#else
      return get_id_space()(info.name());
#endif
   }

   inline id system::id(const char * psz)
   {
      return get_id_space()(psz);
   }

   inline id system::id(const string & str)
   {
      return get_id_space()(str);
   }

   inline id system::id(i64 i)
   {
      return get_id_space()(i);
   }

   inline id_space & system::id()
   {
      return get_id_space();
   }


} //namespace aura



inline id::id(const char * psz)
{

   m_all = {};

   if(psz != nullptr)
   {

      operator = (::aura::system::id(psz));

   }

}


inline id::id(const string & str)
{

   m_all = {};

   operator = (::aura::system::id(str.c_str()));

}


inline id::id(const type & type) :
   id((const string &) type.to_string())
{

}

inline id & id::operator = (::i32 i)
{
   
   m_etype     = type_integer;
   
   m_i         = i;
   
   return *this;

}


inline id & id::operator = (::i64 i)
{

   m_etype     = type_integer;

   m_i         = i;

   return *this;

}


inline id & id::operator = (::u64 u)
{
   
   m_etype     = type_integer;
   
   m_u         = u;
   
   return *this;
   
}


inline id & id::operator = (const ::enum_property & eproperty)
{

   m_etype = type_property;

   m_eproperty = eproperty;

   return *this;

}


inline id & id::operator = (const ::enum_factory & efactory)
{

   m_etype = type_factory;

   m_efactory = efactory;

   return *this;

}


inline id& id::operator = (const ::enum_thread_tool & ethreadtool)
{

   m_etype = type_thread_tool;

   m_ethreadtool = ethreadtool;

   return *this;

}


