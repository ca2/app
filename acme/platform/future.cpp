#include "framework.h"

//
//namespace promise
//{
//

   critical_section* g_pcriticalsectionFuture = nullptr;


   critical_section* get_future_critical_section()
   {


      return g_pcriticalsectionFuture;

   }


   void initialize_future_critical_section()
   {

      if (!g_pcriticalsectionFuture)
      {

         g_pcriticalsectionFuture = new critical_section();

      }

   }


   void finalize_future_critical_section()
   {

      if (g_pcriticalsectionFuture)
      {

         delete g_pcriticalsectionFuture;

         g_pcriticalsectionFuture = nullptr;

      }

   }

//
//} // namespace promise
//
