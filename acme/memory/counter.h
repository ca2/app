// Created on 2021-03-42 16:35 <3ThomasBS_!!
#pragma once


#include "acme/platform/acme.h"
#include "acme/primitive/collection/string_map.h"


class CLASS_DECL_ACME memory_counter :
   virtual public ::particle
{
public:


   int                        m_iMemoryCounters = -1;

   ::critical_section         m_criticalsection;

   int                        m_iMemoryCountersStartable = 0;

   ::string_map < iptr >      m_mapMemoryCounter;


   void initialize(::particle * pparticle) override;

   bool is_enabled();

   void increment_by_name(const ::scoped_string & scopedstr);
   void decrement_by_name(const ::scoped_string & scopedstr);


   template < typename T >
   const char* memory_counter_id(T* pthis)
   {

      return typeid(*pthis).name();

   }


   template < typename T >
   void memory_counter_increment(T* pthis)
   {

      if (is_enabled())
      {

         auto psz = memory_counter_id(pthis);

         increment_by_name(psz);

         //synchronous_lock synchronouslock(g_pmutexMemoryCounters);

         //int i = atoi(acmefile()->as_string(path));

         //acmefile()->put_contents(path, as_string(i + 1));
      }

   }


   template < typename T >
   void memory_counter_decrement(T* pthis)
   {

      if (is_enabled())
      {

         auto psz = memory_counter_id(pthis);

         decrement_by_name(psz);

         //int i = atoi(acmefile()->as_string(path));

         //acmefile()->put_contents(path, as_string(i - 1));

      }

   }






};







///CLASS_DECL_ACME ::file::path memory_counter_base_path(::matter * pmatter);


CLASS_DECL_ACME void initialize_memory_counter();
CLASS_DECL_ACME void finalize_memory_counter();
CLASS_DECL_ACME ::memory_counter * get_memory_counter();





//template < typename T >
//const char * memory_counter_id(T* pthis);
//
template < typename T >
void memory_counter_increment(T* pthis)
{

   if (::acme::acme::g_p->m_pmemorycounter)
   {

      ::acme::acme::g_p->m_pmemorycounter->memory_counter_increment(pthis);

   }

}


template < typename T >
void memory_counter_decrement(T* pthis)
{

   if (::acme::acme::g_p->m_pmemorycounter)
   {

      ::acme::acme::g_p->m_pmemorycounter->memory_counter_decrement(pthis);

   }

}



