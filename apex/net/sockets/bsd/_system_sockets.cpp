#include "framework.h"
#include "apex/net/sockets/_.h"


namespace apex
{


   ::estatus system::initialize_sockets()
   {

      ::estatus estatus = ::success_none;

      if (!m_psockets)
      {

         estatus = __compose_new(m_psockets);

         if (!estatus)
         {

            return estatus;

         }

      }

      return estatus;

   }

} // namespace apex



