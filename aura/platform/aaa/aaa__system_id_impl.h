#pragma once



namespace aura
{

   inline atom system::atom(const class ::payload & payload)
   {
      return ::atom((const ::string &)(class ::payload &) ::payload);
   }

   inline atom system::atom(const property & prop)
   {
      return ::atom((const string &)(property &)prop);
   }


   inline atom system::atom(const ::std::type_info & info)
   {
#ifdef WINDOWS
      return get_id_space()(info.name());
#else
      return get_id_space()(info.name());
#endif
   }

   inline atom system::atom(const ::string & psz)
   {
      return get_id_space()(psz);
   }

   inline atom system::atom(const ::string & str)
   {
      return get_id_space()(str);
   }

   inline atom system::atom(i64 i)
   {
      return get_id_space()(i);
   }

   inline atom_space & system::atom()
   {
      return get_id_space();
   }


} //namespace aura



inline atom::atom(const ::string & psz)
{

   m_all = {};

   if(psz != nullptr)
   {

      operator = (::aura::system::atom(psz));

   }

}


inline atom::atom(const ::string & str)
{

   m_all = {};

   operator = (::aura::system::atom(str.c_str()));

}


inline atom::atom(const type & type) :
   atom((const string &) type.to_string())
{

}

inline atom & atom::operator = (::i32 i)
{
   
   m_etype     = type_integer;
   
   m_i         = i;
   
   return *this;

}


inline atom & atom::operator = (::i64 i)
{

   m_etype     = type_integer;

   m_i         = i;

   return *this;

}


inline atom & atom::operator = (::u64 u)
{
   
   m_etype     = type_integer;
   
   m_u         = u;
   
   return *this;
   
}


inline atom & atom::operator = (const ::enum_property & eproperty)
{

   m_etype = type_property;

   m_eproperty = eproperty;

   return *this;

}


inline atom & atom::operator = (const ::enum_factory & efactory)
{

   m_etype = type_factory;

   m_efactory = efactory;

   return *this;

}


inline atom& atom::operator = (const ::enum_task_tool & ethreadtool)
{

   m_etype = type_thread_tool;

   m_ethreadtool = ethreadtool;

   return *this;

}


