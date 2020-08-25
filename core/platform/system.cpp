#include "framework.h"
#include "aura/platform/static_setup.h"


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

      create_factory < ::core::application, ::aura::application >();
      create_factory < ::core::session, ::aura::session >();
      create_factory < ::core::user, ::user::user >();

   }


   ::estatus system::initialize(::object* pobjectContext)
   {

      auto estatus = ::base::system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_system_factory(system);


} // namespace core



