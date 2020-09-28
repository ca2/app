#include "framework.h"
#include "apex/platform/static_setup.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "core/user/user/_user.h"
//#endif
#include "bred/const/idpool.h"


//bool __rich_text_initialize();


namespace bred
{


   system::system()
   {

      m_pbredsystem = this;

      common_construct();

   }


   system::~system()
   {



      m_pbredsystem = nullptr;

   }


   void system::common_construct()
   {

      create_factory < ::bred::application, ::apex::application >();
      create_factory < ::bred::session, ::apex::session >();
      //create_factory < ::core::user, ::user::user >();
      create_factory < ::bred::idpool, ::apex::idpool >();

   }


   ::estatus system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //::estatus system::initialize_rich_text()
   //{

   //   if (!__rich_text_initialize())
   //   {

   //      return false;

   //   }

   //   return ::success;

   //}

  
   __namespace_system_factory(system);


} // namespace bred



