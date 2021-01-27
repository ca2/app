#include "framework.h"

/*
e_type_element = 8000,
e_type_stra,
e_type_inta,
type_vara,
e_type_propset,
type_int64a,
e_type_memory,
e_type_path,
type_image,
__type_last_element,

switch(m_etype)
{
case e_type_element:
case e_type_stra:
case e_type_inta:
case type_vara:
case e_type_propset:
case e_type_memory:
case type_int64a:
case e_type_path:
case type_image:
default:
};

*/


#define VAR_SET_ELEMENT(P, TYPE, ENUM_TYPE) \
payload.P = dynamic_cast < TYPE * >(pobject); \
if(::is_set(payload.m_pstra)) return ENUM_TYPE;


enum_type set_element(::payload & payload, ::matter * pobject)
{

   VAR_SET_ELEMENT(m_pstra    , ::string_array             , ::e_type_stra);
   VAR_SET_ELEMENT(m_pia      , ::int_array           , ::e_type_inta);
   VAR_SET_ELEMENT(m_pvara    , ::var_array           , ::type_vara);
   VAR_SET_ELEMENT(m_pset     , ::property_set        , ::e_type_propset);
   VAR_SET_ELEMENT(m_pi64a    , ::i64_array           , ::e_type_i64a);
   VAR_SET_ELEMENT(m_pmemory  , ::memory              , ::e_type_memory);
   VAR_SET_ELEMENT(m_ppath    , ::file::path_object   , ::e_type_path);
   //VAR_SET_ELEMENT(m_pimage   , ::image               , ::type_image);

   payload.m_p = pobject;

   return ::e_type_element;

}


::enum_type payload::set_element(::matter * pobject)
{

   release();

   m_etype = ::set_element(*this, pobject);

   ::add_ref(pobject);

   return m_etype;

}


::i64 payload::release()
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
   case e_type_element:
      return ::release(m_p);
   case e_type_stra:
      return ::release(m_pstra);
   case e_type_inta:
      return ::release(m_pia);
   case type_vara:
      return ::release(m_pvara);
   case e_type_propset:
      return ::release(m_pset);
   case e_type_i64a:
      return ::release(m_pi64a);
   case e_type_memory:
      return ::release(m_pmemory);
   case e_type_path:
      return ::release(m_ppath);
   //case type_image:
   //   return ::release(m_pimage);
   default:
      return -1;
   };

}



