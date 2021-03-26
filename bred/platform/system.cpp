#include "framework.h"
#include "acme/platform/static_setup.h"
#include "bred/const/idpool.h"


namespace bred
{


   system::system()
   {

      common_construct();

   }


   system::~system()
   {


   }


   void system::common_construct()
   {

      create_factory < ::bred::application, ::apex::application >();
      create_factory < ::bred::session, ::apex::session >();
      create_factory < ::bred::idpool, ::apex::idpool >();
      //create_factory < ::core::user, ::user::user >();
      create_factory < ::bred::idpool, ::apex::idpool >();

   }


   ::e_status system::initialize(::object * pobject)
   {

      auto estatus = ::apex::system::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //::e_status system::initialize_rich_text()
   //{

   //   if (!__rich_text_initialize())
   //   {

   //      return false;

   //   }

   //   return ::success;

   //}

  
   __namespace_system_factory(system);


} // namespace bred



