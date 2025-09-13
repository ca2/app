// Created by camilo on 2023-06-27 23:22 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "placement_log.h"
#include "acme/parallelization/synchronous_lock.h"



namespace windowing
{


   void placement_log::on_initialize_particle()
   {

      defer_create_synchronization();

   }


   void placement_log::add(const ::int_rectangle& rectangle)
   {

      placement_log_item item;

      item.m_rectangle = rectangle;
      item.m_time.Now();

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      insert_at(0, item);

   }
      
   
   bool placement_log::has_recent(const ::int_rectangle& rectangle)
   {

      clean_recent();

      for (auto& item : *this)
      {

         if (item.m_rectangle == rectangle)
         {

            return true;

         }

      }

      return false;


   }
   

   bool placement_log::has_recent(const ::int_size& size)
   {

      clean_recent();

      for (auto& item : *this)
      {

         if (item.m_rectangle.size() == size)
         {

            return true;

         }

      }

      return false;


   }


   bool placement_log::has_recent(const ::int_point& point)
   {

      clean_recent();

      for (auto& item : *this)
      {

         if (item.m_rectangle.top_left() == point)
         {

            return true;

         }

      }

      return false;


   }


   void placement_log::clean_recent()
   {

      const auto timeRecent = 3_s;

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      for (::collection::index i = this->upper_bound(); i >= 0; i--)
      {

         if (element_at(i).m_time.elapsed() > timeRecent)
         {

            erase_at(i);

         }
         else
         {

            break;

         }

      }

   }


} // namespace windowing



