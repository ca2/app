#include "framework.h"
#include "base/user/user/_user.h"
#include "apex/platform/static_setup.h"
#include "base/const/idpool.h"


void __node_base_factory_exchange();


namespace base
{


   system::system()
   {

      m_pbasesystem = this;

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
//      //   TRACE("system::~system: Potentially catastrophical error : error disabling simple factory request");
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

      create_factory < ::base::session, ::apex::session >();
      create_factory < ::base::application, ::apex::application >();
      create_factory < ::base::idpool, ::apex::idpool >();
      create_factory < ::base::user, ::user::user >();

   }


   ::e_status system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::axis::system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      __node_base_factory_exchange();

      return estatus;

   }


   __namespace_system_factory(system);


} // namespace base





void __node_base_factory_exchange()
{


}


