#include "framework.h"
#include "apex/platform/static_setup.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "core/user/user/_user.h"
//#endif
#include "aqua/const/idpool.h"




CLASS_DECL_APEX const char* multimedia_get_library_name();



namespace aqua
{


   system::system()
   {

      set_layer(LAYERED_AQUA, this);

      common_construct();

   }


   system::~system()
   {


   }


   void system::common_construct()
   {

      create_factory < ::aqua::application, ::apex::application >();
      create_factory < ::aqua::session, ::apex::session >();
      create_factory < ::aqua::idpool, ::apex::idpool >();
      create_factory < ::aqua::multimedia >();

   }


   ::e_status system::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::system::initialize(pobjectContext);

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

   ::e_status system::defer_xml()
   {

      if (m_pxml)
      {

         return ::success;

      }

      auto estatus = __compose_new(m_pxml);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pxml->init1();

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pxml->init();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::create_audio()
   {

      auto plibrary = get_library("audio");

      if (!plibrary)
      {

         return error_failed;

      }

      auto estatus = plibrary->factory_exchange(::factory::get_factory_map());

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose(m_paudio);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_paudio->init3();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::aqua::multimedia* system::defer_get_multimedia()
   {

      if (!m_pmultimedia)
      {

         defer_multimedia();

      }

      return m_pmultimedia;

   }


   void system::defer_multimedia()
   {

      string strName;

      auto pszName = ::multimedia_get_library_name();

      if (::is_set(pszName) && !strcmp(pszName, "veriwell_multimedia"))
      {

         strName = "veriwell_multimedia";

      }
      else
      {

         strName = "multimedia";

      }

      auto plibrary = get_library(strName);

      if (plibrary)
      {

         auto pgetnewmultimedia = plibrary->get<PFUNCTION_GET_NEW_MULTIMEDIA>("get_new_multimedia");

         __compose(m_pmultimedia, ::move_transfer(pgetnewmultimedia()));

         m_pmultimedia->initialize_multimedia(this);

      }
      else
      {

         __compose(m_pmultimedia);

      }

   }


   ::aqua::audio* system::defer_get_audio()
   {

      if (!m_paudio)
      {

         create_audio();

      }

      return m_paudio;

   }


   __namespace_system_factory(system);


} // namespace aqua



