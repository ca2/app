#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace apex
{


   void system::initialize_sockets()
   {

      ::e_status3 estatus = ::success_none;

      if (!m_psockets)
      {

         //estatus = __compose_new(m_psockets);

         __compose_new(m_psockets);

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //return estatus;

   }

} // namespace apex



