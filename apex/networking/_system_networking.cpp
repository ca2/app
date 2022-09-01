#include "framework.h"
#include "networking.h"


namespace apex
{


   void system::initialize_networking()
   {

      ::e_status estatus = ::success_none;

      auto & pfactoryNetworking = factory("networking", "bsd");

      //if (!pfactoryCrypto)
      //{

      //   WARNING("Could not open crypto openssl plugin.");

      //   //return pfactoryCrypto;

      //}

      pfactoryNetworking->merge_to_global_factory();

      //estatus = 
      pfactoryNetworking->__compose(this, m_pnetworking);


      if (!m_pnetworking)
      {

         //estatus = __compose_new(m_psockets);

         //__compose(m_pnetworking);

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //return estatus;

   }

} // namespace apex



