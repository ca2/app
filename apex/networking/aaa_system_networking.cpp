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

         //   WARNING("Could not open crypto openssl plugin.");

         //   //return pfactoryCrypto;

         //}

         pfactoryNetworking->merge_to_global_factory();

         //estatus = 
         pfactoryNetworking->__construct(this, m_pnetworking);


         if (!m_pnetworking)
         {

            //estatus = __construct_new(m_psockets);

            //__construct(m_pnetworking);

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



