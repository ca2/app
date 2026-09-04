// Created by camilo on 2022-06-23 20:53 <3ThomasBorregaardSoerensen!!
#include "platform.h"
#include "holdee.h"


namespace draw2d
{


   void holdee_group::destroy()
   {

      m_patha.defer_destroy_and_release();
      m_brusha.defer_destroy_and_release();
      m_pena.defer_destroy_and_release();
      m_fonta.defer_destroy_and_release();


   }


   holdee::holdee()
   {


   }


   holdee::~holdee()
   {


   }


   void holdee::destroy()
   {

      for (auto & map2 : m_map.payloads())
      {

         try
         {

            for (auto & pholdeegroup : map2.payloads())
            {

               try
               {

                  pholdeegroup.defer_destroy_and_release();

               }
               catch (...)
               {


               }

            }


         }
         catch (...)
         {


         }

      }


   }
   

} // namespace draw2d



