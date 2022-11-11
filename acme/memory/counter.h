// Created on 2021-03-42 16:35 <3ThomasBS_!!
#pragma once


#include "acme/primitive/collection/string_map.h"


class CLASS_DECL_ACME memory_counter :
   virtual public ::particle
{
public:


   int m_iMemoryCounters = -1;

   critical_section m_criticalsection;

   int m_iMemoryCountersStartable = 0;

   ::string_map < iptr >      m_mapMemoryCounter;


   void initialize(::particle * pparticle) override;

   bool is_enabled();

   void increment(const char * psz);
   void decrement(const char * psz);


};







///CLASS_DECL_ACME ::file::path memory_counter_base_path(::matter * pmatter);


template < typename T >
const char * memory_counter_id(T* pthis);

template < typename T >
void memory_counter_increment(T* pthis);

template < typename T >
void memory_counter_decrement(T* pthis);

template < typename T >
const char * memory_counter_id(T * pthis)
{

   return typeid(*pthis).name();

}


template < typename T >
void memory_counter_increment(T * pthis)
{

   if (pthis &&
      pthis->acmesystem() &&
      pthis->acmesystem()->m_pmemorycounter &&
      pthis->acmesystem()->m_pmemorycounter->is_enabled())
   {

      auto psz = memory_counter_id(pthis);

      pthis->acmesystem()->m_pmemorycounter->increment(psz);

      //synchronous_lock synchronouslock(g_pmutexMemoryCounters);

      //int i = atoi(acmefile()->as_string(path));

      //acmefile()->put_contents(path, __string(i + 1));
   }

}


template < typename T >
void memory_counter_decrement(T * pthis)
{

   if (pthis->acmesystem()->m_pmemorycounter->is_enabled())
   {

      auto psz = memory_counter_id(pthis);

      pthis->acmesystem()->m_pmemorycounter->decrement(psz);

      //int i = atoi(acmefile()->as_string(path));

      //acmefile()->put_contents(path, __string(i - 1));

   }

}



