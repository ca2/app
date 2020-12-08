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


   ::estatus sockets_base::initialize(::layered * pobjectContext)
   {

      auto estatus = object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void sockets_base::finalize()
   {

      ::object::finalize();


   }




} // namespace sockets







