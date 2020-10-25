#pragma once



inline var::var()
{

   m_etype = type_new;
   clear_data();

}


inline var::var(enum_type etype)
{

   m_etype = etype;
   clear_data();

}


//inline var::var(const ::estatus & estatus)
//{
//
//   set_type(type_enum_status);
//
//   m_estatus = estatus;
//
//}


//inline var::var(enum_command ecommand)
//{
//
//   set_type(type_enum_command);
//
//   m_ecommand = ecommand;
//
//}


//inline var::var(enum_check echeck)
//{
//
//   set_type(type_enum_check);
//
//   m_echeck = echeck;
//
//}


inline var::var(std::nullptr_t)
{

   m_etype = e_type_null;

}


inline ::count var::get_count() const
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


inline ::count var::array_get_count() const
{
   if(m_etype == type_new
         || m_etype == e_type_null
         || m_etype == type_empty
         || m_etype == type_empty_argument)
   {
      return -1; // indicates that this var is not an array
   }
   else if(is_array())
      return this->get_count();
   else
      return 1; // this var is an scalar or object that can be retrieved through "array_" methods
}



inline index var::array_get_upper_bound() const
{
   if(m_etype == type_new
         || m_etype == e_type_null
         || m_etype == type_empty
         || m_etype == type_empty_argument)
   {
      return -1; // indicates that this var is not an array
   }
   else if(is_array())
      return this->get_count() - 1;
   else
      return 0; // this var is an scalar or object that can be retrieved through "array_" methods
}


inline bool var::is_array() const
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



inline bool CLASS_DECL_AURA operator == (const string & str, const var & var)
{

   return str == var.get_string();

}



inline id & id::operator = (const var & var)
{

   if(var.is_null())
   {
      m_all = {};
      return *this;
   }
   else if(var.is_empty())
   {
      return operator =("");
   }
   else if(var.is_integer())
   {
      return operator = (var.iptr());
   }
   else
   {
      return operator = (var.get_string());
   }

}

inline id & id::operator = (const property & prop)
{

   return operator = ((const var &)prop);

}



inline id::id(const var & var)
{
   m_all= {};
   operator = (var);

}
