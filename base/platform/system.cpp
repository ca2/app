#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
#include "acme/platform/system_setup.h"
#include "aura/user/user/interaction.h"
#include "base/constant/idpool.h"
#include "base/user/user/user.h"


//void base_factory(::factory::factory * pfactory);


namespace base
{


   system::system()
   {

      common_construct();

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
//      //   ::acme::del(m_pmachineeventcentral);
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
//      //   TRACE("system::~system: Potentially catastrophical error : error disabling simple factory_item request");
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

      m_pbasesystem = this;

      //factory()->add_factory_item < ::base::session, ::apex::session >();
      //factory()->add_factory_item < ::base::application, ::apex::application >();
      //factory()->add_factory_item < ::base::idpool, ::acme::idpool >();

   }


   void system::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::axis::system::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //base_factory(factory());


      //factory()->add_factory_item < ::base::user, ::user::user >();

      //return estatus;

   }


   //void system::on_add_session(::acm::session* papexsession)
   //{

   //   ::axis::system::on_add_session(papexsession);

   //   if (papexsession->m_iEdge == 0)
   //   {

   //      if (!m_pbasesession)
   //      {

   //         m_pbasesession = papexsession->m_pbasesession;

   //      }

   //   }

   //   papexsession->m_pbasesystem = this;

   //}


   //__namespace_system_factory(system);


} // namespace base


//void base_factory(::factory::factory * pfactory)
//{
//
//
//}


