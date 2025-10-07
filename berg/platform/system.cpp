#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/platform/system_setup.h"
#include "aura/user/user/interaction.h"
#include "berg/constant/idpool.h"
#include "berg/user/user/user.h"


//void base_factory(::factory::factory * pfactory);


namespace berg
{


   system::system()
   {

      common_construct();

      factory()->add_factory_item< ::berg::session, ::platform::session>();
      factory()->add_factory_item< ::berg::user, ::user::user>();

   }


   system::~system()
   {

//
//      ::acme::del(m_ppatch);
//
//      if (g_p == this)
//      {
//
//         g_p = nullptr;
//
//      }
//
//      //::acme::del(m_purldepartment);
//
//      //::acme::del(m_pcompress);
//
//      ::acme::del(g_pmutexImage);
//
//      //try
//      //{
//
//      //   ::acme::del(m_pmachinehappeningcentral);
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //try
//      //{
//
//      //   if (m_pfactory.is_set())
//      //   {
//
//      //      m_pfactory->enable_simple_factory_request(false);
//
//      //      m_pfactory.release();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//      //   informationf("system::~system: Potentially catastrophical error : error disabling simple factory_item request");
//      //}
//
//      if (g_p == this)
//      {
//
//         g_p = nullptr;
//
//      }
//
//#ifdef LINUX
//
//      os_post_quit();
//
//#elif defined(__APPLE__)
//
//      os_post_quit();
//
//#endif
//
//#ifndef WINDOWS
//
//      exception::translator::detach();
//
//#endif

   }


   void system::common_construct()
   {

      //m_pbasesystem = this;

      //factory()->add_factory_item < ::berg::session, ::apex::session >();
      //factory()->add_factory_item < ::berg::application, ::apex::application >();
      //factory()->add_factory_item < ::base::idpool, ::acme::idpool >();



   }


   // void system::on_set_platform()
   // {
   //
   //    axis::system::on_set_platform();
   //
   //    factory()->add_factory_item< ::berg::session, ::platform::session>();
   //    factory()->add_factory_item< ::berg::user, ::user::user>();
   //
   // }


   void system::on_initialize_particle()
   {

      //auto estatus = 
      
      ::axis::system::on_initialize_particle();




      //if (!estatus)
      //{

      //   return estatus;

      //}

      //base_factory(factory());


      //factory()->add_factory_item < ::berg::user, ::user::user >();

      //return estatus;

   }


   //void system::on_add_session(::acm::session* papexsession)
   //{

   //   ::axis::system::on_add_session(papexsession);

   //   if (papexsession->m_iEdge == 0)
   //   {

   //      if (!m_pbasesession)
   //      {

   //         m_pbasesession = papexsession;

   //      }

   //   }

   //   papexsession = this;

   //}


   //__namespace_system_factory(system);


} // namespace berg


//void base_factory(::factory::factory * pfactory)
//{
//
//
//}


