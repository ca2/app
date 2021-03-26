#include "framework.h"
#include "acme/platform/static_setup.h"


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


   ::e_status session::initialize(::object * pobject)
   {

      auto estatus = ::apex::session::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void session::on_instantiate_application(::apex::application* papp)
   {

      ::aura::session::on_instantiate_application(papp);

      papp->m_pbredsession = this;

   }


   __namespace_session_factory(session);


} // namespace bred



