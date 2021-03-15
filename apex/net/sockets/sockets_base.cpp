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


   ::e_status sockets_base::initialize(::context_object * pcontextobject)
   {

      auto estatus = object::initialize(pcontextobject);

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







