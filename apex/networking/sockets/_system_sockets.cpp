#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace apex
{


   void system::initialize_sockets()
   {

      void estatus = ::success_none;

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



