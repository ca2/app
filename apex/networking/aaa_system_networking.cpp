#include "framework.h"
#include "networking.h"


namespace apex
{


   void system::initialize_networking()
   {

      try
      {

         ::e_status estatus = ::success_none;

         auto& pfactoryNetworking = factory("networking", "bsd");

         //if (!pfactoryCrypto)
         //{

         //   warningf("Could not open crypto openssl plugin.");

         //   //return pfactoryCrypto;

         //}

         pfactoryNetworking->merge_to_global_factory();

         //estatus = 
         pfactoryNetworking->constructø(this, m_pnetworking);


         if (!m_pnetworking)
         {

            //estatus = construct_newø(m_psockets);

            //constructø(m_pnetworking);

            //if (!estatus)
            //{

            //   return estatus;

            //}

         }

         //return estatus;

      }
      catch (...)
      {

         m_bNetworking = false;

      }

   }

} // namespace apex



