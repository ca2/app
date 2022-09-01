#include "framework.h"
#include "apex/networking/networking_bsd/_sockets.h"


namespace networking_bsd
{


   sockets_base::sockets_base()
   {

      m_iErrorCode = -1;

   }


   sockets_base::~sockets_base()
   {



   }


   void sockets_base::initialize(::object * pobject)
   {

      //auto estatus = object::initialize(pobject);

      object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   void sockets_base::destroy()
   {

      ::object::destroy();

      //return ::success;

   }




} // namespace networking_bsd







