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


   void placement_log::add(const ::rectangle_i32& rectangle)
   {

      placement_log_item item;

      item.m_rectangle = rectangle;
      item.m_time.Now();

      synchronous_lock synchronouslock(this->synchronization());

      insert_at(0, item);

   }
      
   
   bool placement_log::has_recent(const ::rectangle_i32& rectangle)
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
   

   bool placement_log::has_recent(const ::size_i32& size)
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


   bool placement_log::has_recent(const ::point_i32& point)
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

      synchronous_lock synchronouslock(this->synchronization());

      for (::index i = this->upper_bound(); i >= 0; i--)
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



