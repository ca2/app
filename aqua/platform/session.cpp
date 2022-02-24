#include "framework.h"
#include "acme/platform/system_setup.h"


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


   void session::initialize(::object * pobject)
   {

      //auto estatus = 
      ::apex::session::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void session::on_instantiate_application(::application* papp)
   {

      apex::session::on_instantiate_application(papp);

      papp->m_paquasession = this;
      papp->m_paquasystem = m_paquasystem;

   }


   //__namespace_session_factory(session);


} // namespace aqua



