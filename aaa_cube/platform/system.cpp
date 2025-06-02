#include "framework.h"
#include "acme/platform/system_setup.h"
#include "bred/const/idpool.h"
#include "application.h"
#include "session.h"
#include "system.h"


namespace bred
{


   system::system()
   {

      common_construct();

      factory()->add_factory_item < ::bred::application, ::apex::application >();
      factory()->add_factory_item < ::bred::session, ::apex::session >();


   }


   system::~system()
   {


   }


   void system::common_construct()
   {

      //factory()->add_factory_item < ::bred::idpool, ::acme::idpool >();
      //add_factory_item < ::core::user, ::user::user >();
      //add_factory_item < ::bred::idpool, ::apex::idpool >();

   }


   // void system::on_set_platform()
   // {
   //
   //    ::base::system::on_set_platform();
   //
   //    factory()->add_factory_item < ::bred::application, ::apex::application >();
   //    factory()->add_factory_item < ::bred::session, ::apex::session >();
   //
   //
   // }


   // void system::initialize(::particle * pparticle)
   // {
   //
   //    //auto estatus =
   //
   //    ::base::system::initialize(pparticle);
   //
   //    //if (!estatus)
   //    //{
   //
   //    //   return estatus;
   //
   //    //}
   //
   //    //return estatus;
   //
   // }



   //void system::on_add_session(::apex::session* papexsession)
   //{

   //   ::base::system::on_add_session(papexsession);

   //   if (papexsession->m_iEdge == 0)
   //   {

   //      if (!m_pbredsession)
   //      {

   //         m_pbredsession = papexsession->m_pbredsession;

   //      }

   //   }

   //   papexsession->m_pbredsystem = this;

   //}
   //void system::initialize_rich_text()
   //{

   //   if (!__rich_text_initialize())
   //   {

   //      return false;

   //   }

   //   return ::success;

   //}

  
   //__namespace_system_factory(system);


} // namespace bred



