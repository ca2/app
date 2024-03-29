// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#include "framework.h"


subparticle::~subparticle()
{


}



#ifdef _DEBUG


i64 subparticle::increment_reference_count()
{

#if REFERENCING_DEBUGGING

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

#endif

   auto c = ++m_countReference;

#if REFERENCING_DEBUGGING

   add_reference_item();

#endif

   return c;

}


i64 subparticle::decrement_reference_count()
{

#if REFERENCING_DEBUGGING

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

#endif

   auto c = --m_countReference;

#if REFERENCING_DEBUGGING

   if (c >= 0)
   {

      erase_reference_item();

   }

#endif

   return c;

}


i64 subparticle::replace_reference()
{

   auto c = m_countReference;

#if REFERENCING_DEBUGGING

   if (c > 0)
   {

      throw ::exception(::error_failed);

      //m_preferenceitema->replace_item();

   }

#endif

   return c;

}


i64 subparticle::release()
{

   i64 i = decrement_reference_count();

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif



bool subparticle::defer_consume_main_arguments(int argc, char ** argv, int & iArgument)
{

   return false;
   
}


enum_type subparticle::get_payload_type() const
{

   return e_type_element;

}


void subparticle::delete_this()
{

   if (!(m_eflagElement & e_flag_statically_allocated))
   {

      //__delete(this, m_pAllocation);

      //delete m_pAllocation;

      delete this;

   }

}



