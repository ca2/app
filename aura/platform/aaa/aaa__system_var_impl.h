#pragma once



inline payload::payload()
{

   m_etype = e_type_new;
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
   case e_type_bool:
      return 1;
   case e_type_i32_array:
      return ::is_null(m_pia) ? 0 : m_pia->get_count();
   case e_type_string_array:
      return ::is_null(m_pstra) ? 0 : m_pstra->get_count();
   case type_vara:
      return ::is_null(m_ppayloada) ? 0 : m_ppayloada->get_count();
   case e_type_property_set:
      return ::is_null(m_ppropertyset) ? 0 : m_ppropertyset->get_count();
   case e_type_empty:
   case e_type_null:
   case e_type_new:
   case e_type_empty_argument:
      return 0;
   default:
      return 1;
   }
}


inline ::count payload::array_get_count() const
{
   if(m_etype == e_type_new
         || m_etype == e_type_null
         || m_etype == e_type_empty
         || m_etype == e_type_empty_argument)
   {
      return -1; // indicates that this ::payload is not an array
   }
   else if(is_array())
      return this->get_count();
   else
      return 1; // this ::payload is an scalar or object that can be retrieved through "array_" methods
}



inline index payload::array_get_upper_bound() const
{
   if(m_etype == e_type_new
         || m_etype == e_type_null
         || m_etype == e_type_empty
         || m_etype == e_type_empty_argument)
   {
      return -1; // indicates that this ::payload is not an array
   }
   else if(is_array())
      return this->get_count() - 1;
   else
      return 0; // this ::payload is an scalar or object that can be retrieved through "array_" methods
}


inline bool payload::is_array() const
{

   if(m_etype == e_type_string_array
         || m_etype == e_type_i32_array
         || m_etype == type_vara
         || m_etype == e_type_property_set)
   {
      return true;
   }
   else if(m_etype == type_prop)
   {
      return prop().is_array();
   }
   else if(m_etype == e_type_element)
   {
      return false;
   }
   else
   {
      return false;
   }
}



inline bool CLASS_DECL_AURA operator == (const ::string & str, const ::payload & payload)
{

   return str == payload.get_string();

}



inline atom & atom::operator = (const ::payload & payload)
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

inline atom & atom::operator = (const property & prop)
{

   return operator = ((const ::payload &)prop);

}



inline atom::atom(const ::payload & payload)
{
   m_all= {};
   operator = (payload);

}
