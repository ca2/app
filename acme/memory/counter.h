// Created on 2021-03-42 16:35 <3ThomasBS_!!
#pragma once


#include "acme/platform/acme.h"
#include "acme/primitive/collection/map.h"


namespace heap
{


   template < typename TYPE >
   class counter :
      virtual public ::particle
   {
   public:

      class item
      {

      public:

         ::string m_strDebug;
         ::i64    m_i = 0;


      };

      bool m_bEnabled = false;
      //int                                 m_iMemoryCounters = -1;

      ::critical_section                  m_criticalsection;

      //int                                 m_iMemoryCountersStartable = 0;

      ::map < TYPE, item >       m_mapCounter;


      counter()
      {

         //m_bEnabled = false;

      }
      ~counter() override
      {


      }

      void on_initialize_particle() override
      {
         ::particle::on_initialize_particle();
      }

      bool is_enabled()
      {

         return m_bEnabled;

      }

      //void increment_by_name(const ::scoped_string & scopedstr);
      //void decrement_by_name(const ::scoped_string & scopedstr);


      //template < typename T >
      //const char* memory_counter_id(T* pthis)
      //{

      //   return typeid(*pthis).name();

      //}


      ::i64 get_counter(const TYPE & t)
      {

         critical_section_lock lock(&m_criticalsection);

         if (is_enabled())
         {

            auto & item = m_mapCounter[t];

            return item.m_i;

         }

         return -1;

      }



      void increment_counter(const TYPE & t)
      {

         critical_section_lock lock(&m_criticalsection);

         if (is_enabled())
         {

            auto & item = m_mapCounter[t];

            item.m_i++;

         }

      }


      void decrement_counter(const TYPE & t)
      {

         critical_section_lock lock(&m_criticalsection);

         if (is_enabled())
         {

            auto & i = m_mapCounter[t];

            i--;

         }

      }


   };


} // namespace heap




///CLASS_DECL_ACME ::file::path memory_counter_base_path(::matter * pmatter);


//CLASS_DECL_ACME void initialize_memory_counter();
//CLASS_DECL_ACME void finalize_memory_counter();
//CLASS_DECL_ACME ::memory_counter * get_memory_counter();


//template < typename T >
//const char * memory_counter_id(T* pthis);
//


//template < typename T >
//void memory_counter_increment(T* pthis)
//{
//
//   if (this->platform()->m_pmemorycounter)
//   {
//
//      this->platform()->m_pmemorycounter->memory_counter_increment(pthis);
//
//   }
//
//}
//
//
//template < typename T >
//void memory_counter_decrement(T* pthis)
//{
//
//   if (this->platform()->m_pmemorycounter)
//   {
//
//      this->platform()->m_pmemorycounter->memory_counter_decrement(pthis);
//
//   }
//
//}
//
//

