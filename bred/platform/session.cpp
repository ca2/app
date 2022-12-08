#include "framework.h"
#include "acme/platform/system_setup.h"
#include "apex/platform/application.h"
#include "session.h"


namespace bred
{


   session::session()
   {

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


   void session::on_instantiate_application(::acme::application* papp)
   {

      ::base::session::on_instantiate_application(papp);

      //papp->m_pbredsession = this;
      //papp->m_pbredsystem = m_pbredsystem;

   }


   //__namespace_session_factory(session);


} // namespace bred



