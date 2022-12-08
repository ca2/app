#include "framework.h"
#include "acme/platform/system_setup.h"
#include "apex/platform/application.h"
#include "aqua/platform/session.h"


namespace aqua
{


   session::session()
   {

      m_paquasession = this;

      //set_layer(LAYERED_AQUA, this);

   }


   session::~session()
   {

   }


   void session::common_construct()
   {


   }


   void session::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::apex::session::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void session::on_instantiate_application(::acme::application* papplication)
   {

      apex::session::on_instantiate_application(papplication);

   }


   //__namespace_session_factory(session);


} // namespace aqua



