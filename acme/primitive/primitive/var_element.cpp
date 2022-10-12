#include "framework.h"

/*
e_type_element = 8000,
e_type_string_array,
e_type_i32_array,
type_vara,
e_type_property_set,
type_int64a,
e_type_memory,
e_type_path,
type_image,
__type_last_element,

switch(m_etype)
{
case e_type_element:
case e_type_string_array:
case e_type_i32_array:
case type_vara:
case e_type_property_set:
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


enum_type set_element(::payload & payload, ::particle * pelement)
{

   if (::is_null(pelement))
   {

      payload.m_p = nullptr;

      payload.m_etype = e_type_element;

   }
   else
   {

      payload.m_etype = pelement->get_payload_type();

      switch (payload.m_etype)
      {
      case ::e_type_string_array:
         payload.m_pstra = dynamic_cast <::string_array*>(pelement);
         break;
      case ::e_type_i32_array:
         payload.m_pia = dynamic_cast <::int_array*>(pelement);
         break;
      case ::e_type_payload_array:
         payload.m_ppayloada = dynamic_cast <payload_array*>(pelement);
         break;
      case ::e_type_property_set:
         payload.m_ppropertyset = dynamic_cast <::property_set*>(pelement);
         break;
      case ::e_type_i64_array:
         payload.m_pi64a = dynamic_cast <::i64_array*>(pelement);
         break;
      case ::e_type_memory:
         payload.m_pmemory = dynamic_cast <::memory*>(pelement);
         break;
      case ::e_type_path:
         payload.m_ppath = dynamic_cast <::file::path_object*>(pelement);
         break;
      default:
         payload.m_p = pelement;
      }

   }

   return payload.m_etype;

}


//void payload::_set_matter(::matter * pmatter)
//{
//
//   set_type(e_type_element, false);
//
//   m_p = pmatter;
//
//   ::increment_reference_count(pmatter);
//
//}


void payload::_set_element(::particle * pelement)
{

   ::increment_reference_count(pelement);

   release();

   ::set_element(*this, pelement);

}


::i64 payload::release()
{

   if (m_etype == e_type_string)
   {

      m_str.::string::~string();

      return 0;

   }
   else if (m_etype == e_type_id)
   {

      m_atom.::atom::~atom();

      return 0;

   }
   else
   {

      if (is_element())
      {

         if (::is_null(m_p))
         {

            return -1;

         }

         switch (m_etype)
         {
         case e_type_element:
            return ::release(m_p);
         case e_type_string_array:
            return ::release(m_pstra);
         case e_type_i32_array:
            return ::release(m_pia);
         case e_type_payload_array:
            return ::release(m_ppayloada);
         case e_type_property_set:
            return ::release(m_ppropertyset);
         case e_type_i64_array:
            return ::release(m_pi64a);
         case e_type_memory:
            return ::release(m_pmemory);
         case e_type_path:
            return ::release(m_ppath);
         default:
            return -1;
         };

      }

   }

   return 0;

}



