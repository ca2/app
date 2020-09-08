#include "framework.h"

/*
type_element = 8000,
type_stra,
type_inta,
type_vara,
type_propset,
type_int64a,
type_memory,
type_path,
type_image,
__type_last_element,

switch(m_etype)
{
case type_element:
case type_stra:
case type_inta:
case type_vara:
case type_propset:
case type_memory:
case type_int64a:
case type_path:
case type_image:
default:
};

*/


#define VAR_SET_ELEMENT(P, TYPE, ENUM_TYPE) \
var.P = dynamic_cast < TYPE * >(pobject); \
if(::is_set(var.m_pstra)) return ENUM_TYPE;


e_type set_element(var & var, ::generic * pobject)
{

   VAR_SET_ELEMENT(m_pstra    , ::string_array             , ::type_stra);
   VAR_SET_ELEMENT(m_pia      , ::int_array           , ::type_inta);
   VAR_SET_ELEMENT(m_pvara    , ::var_array           , ::type_vara);
   VAR_SET_ELEMENT(m_pset     , ::property_set        , ::type_propset);
   VAR_SET_ELEMENT(m_pi64a    , ::i64_array           , ::type_i64a);
   VAR_SET_ELEMENT(m_pmemory  , ::memory              , ::type_memory);
   VAR_SET_ELEMENT(m_ppath    , ::file::path_object   , ::type_path);
   //VAR_SET_ELEMENT(m_pimage   , ::image               , ::type_image);

   var.m_p = pobject;

   return ::type_element;

}


::e_type var::set_element(::generic * pobject)
{

   release();

   m_etype = ::set_element(*this, pobject);

   ::add_ref(pobject);

   return m_etype;

}


::i64 var::release()
{

   if (!is_element())
   {

      return -1;

   }

   if (::is_null(m_p))
   {

      return -1;

   }

   switch (m_etype)
   {
   case type_element:
      return ::release(m_p);
   case type_stra:
      return ::release(m_pstra);
   case type_inta:
      return ::release(m_pia);
   case type_vara:
      return ::release(m_pvara);
   case type_propset:
      return ::release(m_pset);
   case type_i64a:
      return ::release(m_pi64a);
   case type_memory:
      return ::release(m_pmemory);
   case type_path:
      return ::release(m_ppath);
   //case type_image:
   //   return ::release(m_pimage);
   default:
      return -1;
   };

}



