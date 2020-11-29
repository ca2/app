#include "framework.h"
#include "apex/platform/static_setup.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif
#include "core/const/idpool.h"


bool __rich_text_initialize();


namespace core
{


   system::system()
   {

      m_pcoresystem = this;

      common_construct();

   }


   system::~system()
   {



      m_pcoresystem = nullptr;

   }


   void system::common_construct()
   {

      create_factory < ::core::application, ::apex::application >();
      create_factory < ::core::session, ::apex::session >();
      create_factory < ::core::idpool, ::apex::idpool >();
      create_factory < ::core::user, ::user::user >();
      create_factory < ::core::idpool, ::apex::idpool >();

   }


   ::estatus system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::base::system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus system::initialize_rich_text()
   {

      if (!__rich_text_initialize())
      {

         return false;

      }

      return ::success;

   }


   __namespace_system_factory(system);


} // namespace core



