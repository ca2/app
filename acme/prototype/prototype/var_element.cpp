#include "framework.h"
#include "acme/prototype/prototype/memory.h"
//#include "acme/prototype/prototype/payload.h"


/*
e_type_element = 8000,
e_type_string_array,
e_type_int_array,
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
case e_type_int_array:
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
payload.P = dynamic_cast < TYPE * >(pparticle); \
if(::is_set(payload.m_pstra)) return ENUM_TYPE;


enum_type set_element(::payload & payload, ::subparticle * pelement)
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
      case ::e_type_int_array:
         payload.m_pia = dynamic_cast <::int_array*>(pelement);
         break;
      case ::e_type_payload_array:
         payload.m_ppayloada = dynamic_cast <payload_array*>(pelement);
         break;
      case ::e_type_property_set:
         payload.m_ppropertyset = dynamic_cast <::property_set*>(pelement);
         break;
      case ::e_type_huge_integer_array:
         payload.m_pi64a = dynamic_cast <::huge_integer_array*>(pelement);
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


void payload::_set_element(::subparticle * pelement)
{

   auto pelementThis = this->get_subparticle();

   if (pelementThis == pelement)
   {

      return;

   }

#if REFERENCING_DEBUGGING 

   ::reference_referer * preferencereferer = nullptr;
   
   if(pelement->is_referencing_debugging_enabled())
   {

      preferencereferer = __refdbg_add_referer_for(pelement);

   }
   else
   {

      preferencereferer = nullptr;

   }

#endif

   ::increment_reference_count(pelement);

   logical_release();

#if REFERENCING_DEBUGGING 

   m_preferer = preferencereferer;

#endif

   //if (m_etype == ::e_type_payload_pointer)
   //{

   //   //return ->logical_release();

   //   ::set_element(*m_ppayload, pelement);

   //}
   //else if (m_etype == ::e_type_property)
   //{

   //   ::set_element(*m_pproperty, pelement);

   //}
   //else
   {

      ::set_element(*this, pelement);

   }

}


huge_integer payload::logical_release()
{

   //if (m_etype == ::e_type_payload_pointer)
   //{

   //   return m_ppayload->logical_release();

   //}
   //else if (m_etype == ::e_type_property)
   //{

   //   return m_pproperty->logical_release();

   //}
   //else
   {

      return payload_release();

   }


}


huge_integer payload::payload_release()
{

   huge_integer iRelease = -1;

   if (m_etype == e_type_string)
   {

      m_str.::string::~string();

   }
   else if (m_etype == e_type_atom)
   {

      m_atomPayload.::atom::~atom();

   }
   else
   {

      if (is_element())
      {

         if (::is_set(m_p))
         {

            switch (m_etype)
            {
            case e_type_element:
            {

#if REFERENCING_DEBUGGING


               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_p);
            }
            break;
            case e_type_string_array:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_pstra);
            }
            break;
            case e_type_int_array:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_pia);
            }
            break;
            case e_type_payload_array:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_ppayloada);
            }
            break;
            case e_type_property_set:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_ppropertyset);
            }
            break;
            case e_type_huge_integer_array:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_pi64a);
            }
            break;
            case e_type_memory:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_pmemory);
            }
            break;
            case e_type_path:
            {
#if REFERENCING_DEBUGGING

               auto prefererOld = m_preferer;
               m_preferer = nullptr;
               ::allocator::add_releaser(prefererOld);
#endif
               iRelease = ::release(m_ppath);
            }
            break;
            default:
               break;
            };

         }

      }

   }

   m_etype = e_type_new;

   m_payloadall = {};

   return iRelease;

}



