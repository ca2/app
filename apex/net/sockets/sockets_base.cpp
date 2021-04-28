#include "framework.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
{


   sockets_base::sockets_base()
   {

      m_iErrorCode = -1;

   }


   sockets_base::~sockets_base()
   {



   }


   ::e_status sockets_base::initialize(::object * pobject)
   {

      auto estatus = object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::e_status sockets_base::finalize()
   {

      ::object::finalize();

      return ::success;

   }




} // namespace sockets







