#include "framework.h"



namespace networking_bsd
{


   sockets_base::sockets_base()
   {

      m_iErrorCode = -1;

   }


   sockets_base::~sockets_base()
   {



   }


   void sockets_base::initialize(::particle * pparticle)
   {

      //auto estatus = object::initialize(pparticle);

      object::initialize(pparticle);

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







