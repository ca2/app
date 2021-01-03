#pragma once



inline payload::payload()
{

   m_etype = type_new;
   clear_data();

}


inline payload::payload(enum_type etype)
{

   m_etype = etype;
   clear_data();

}


//inline payload::payload(const ::e_status & estatus)
//{
//
//   set_type(type_enum_status);
//
//   m_estatus = estatus;
//
//}


//inline payload::payload(enum_command ecommand)
//{
//
//   set_type(type_enum_command);
//
//   m_ecommand = ecommand;
//
//}


//inline payload::payload(enum_check echeck)
//{
//
//   set_type(type_enum_check);
//
//   m_echeck = echeck;
//
//}


inline payload::payload(std::nullptr_t)
{

   m_etype = e_type_null;

}


inline ::count payload::get_count() const
{
   switch(m_etype)
   {
   case type_bool:
      return 1;
   case type_inta:
      return ::is_null(m_pia) ? 0 : m_pia->get_count();
   case type_stra:
      return ::is_null(m_pstra) ? 0 : m_pstra->get_count();
   case type_vara:
      return ::is_null(m_pvara) ? 0 : m_pvara->get_count();
   case type_propset:
      return ::is_null(m_pset) ? 0 : m_pset->get_count();
   case type_empty:
   case e_type_null:
   case type_new:
   case type_empty_argument:
      return 0;
   default:
      return 1;
   }
}


inline ::count payload::array_get_count() const
{
   if(m_etype == type_new
         || m_etype == e_type_null
         || m_etype == type_empty
         || m_etype == type_empty_argument)
   {
      return -1; // indicates that this payload is not an array
   }
   else if(is_array())
      return this->get_count();
   else
      return 1; // this payload is an scalar or object that can be retrieved through "array_" methods
}



inline index payload::array_get_upper_bound() const
{
   if(m_etype == type_new
         || m_etype == e_type_null
         || m_etype == type_empty
         || m_etype == type_empty_argument)
   {
      return -1; // indicates that this payload is not an array
   }
   else if(is_array())
      return this->get_count() - 1;
   else
      return 0; // this payload is an scalar or object that can be retrieved through "array_" methods
}


inline bool payload::is_array() const
{

   if(m_etype == type_stra
         || m_etype == type_inta
         || m_etype == type_vara
         || m_etype == type_propset)
   {
      return true;
   }
   else if(m_etype == type_prop)
   {
      return prop().is_array();
   }
   else if(m_etype == type_element)
   {
      return false;
   }
   else
   {
      return false;
   }
}



inline bool CLASS_DECL_AURA operator == (const string & str, const payload & payload)
{

   return str == payload.get_string();

}



inline id & id::operator = (const payload & payload)
{

   if(payload.is_null())
   {
      m_all = {};
      return *this;
   }
   else if(payload.is_empty())
   {
      return operator =("");
   }
   else if(payload.is_integer())
   {
      return operator = (payload.iptr());
   }
   else
   {
      return operator = (payload.get_string());
   }

}

inline id & id::operator = (const property & prop)
{

   return operator = ((const payload &)prop);

}



inline id::id(const payload & payload)
{
   m_all= {};
   operator = (payload);

}
