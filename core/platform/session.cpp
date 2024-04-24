#include "framework.h"
#include "session.h"
#include "acme/platform/system_setup.h"
#include "apex/platform/application.h"


namespace core
{


   session::session()
   {

      m_pcoresession = this;

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
      
      ::base::session::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void session::on_instantiate_application(::acme::application* papp)
   {

      ::bred::session::on_instantiate_application(papp);

      //papp->m_pcoresession = this;
      //papp->m_pcoresystem = m_pcoresystem;

   }

   //__namespace_session_factory(session);


} // namespace core



