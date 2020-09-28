#include "framework.h"
#include "apex/platform/static_setup.h"


namespace aqua
{


   session::session()
   {

      m_paquasession = this;

   }


   session::~session()
   {



      m_paquasession = nullptr;

   }

   void session::common_construct()
   {


   }


   ::estatus session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace aqua



