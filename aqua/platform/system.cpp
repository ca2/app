#include "framework.h"
#include "acme/platform/static_setup.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "core/user/user/_user.h"
//#endif
#include "aqua/const/idpool.h"




//CLASS_DECL_APEX const char* multimedia_get_library_name();



namespace aqua
{


   system::system()
   {

      m_paquasystem = this;
      //set_layer(LAYERED_AQUA, this);

      common_construct();

   }


   system::~system()
   {


   }


   void system::common_construct()
   {

      create_factory < ::aqua::application, ::application >();
      create_factory < ::aqua::session, ::apex::session >();
      create_factory < ::aqua::idpool, ::acme::idpool >();
      create_factory < ::aqua::multimedia >();

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


   void system::on_add_session(::apex::session* papexsession)
   {

      ::apex::system::on_add_session(papexsession);

      if (papexsession->m_iEdge == 0)
      {

         if (!m_paquasession)
         {

            m_paquasession = papexsession->m_paquasession;

         }

      }

      papexsession->m_paquasystem = this;

   }

   //::e_status system::initialize_rich_text()
   //{

   //   if (!__rich_text_initialize())
   //   {

   //      return false;

   //   }

   //   return ::success;

   //}

   ::xml::xml * system::_xml()
   {

      if (m_pxml)
      {

         return m_pxml;

      }

      auto estatus = __compose_new(m_pxml);

      if (!estatus)
      {

         return m_pxml;

      }

      estatus = m_pxml->init1();

      if (!estatus)
      {

         return m_pxml;

      }

      estatus = m_pxml->init();

      if (!estatus)
      {

         return m_pxml;

      }

      return m_pxml;

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


   ::e_status system::defer_multimedia()
   {

      if (m_pmultimedia)
      {

         return success;

      }

      auto psystem = get_system();

      synchronous_lock synchronouslock(&psystem->m_mutexLibrary);

      try
      {

         auto psetup = ::static_setup::get_first(::static_setup::flag_multimedia);

         if (psetup)
         {

            auto pmultimedia = psetup->create_new_object();

            if (!pmultimedia)
            {

               return error_no_factory;

            }

            auto estatus = __compose(m_pmultimedia, pmultimedia);

            if (!estatus)
            {

               return estatus;

            }

         }

      }
      catch (...)
      {

         return error_exception;

      }

      auto estatus = m_pmultimedia->initialize_multimedia(this);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;
      

      //string strName;

      //auto pszName = ::multimedia_get_library_name();

      //if (::is_set(pszName) && !strcmp(pszName, "veriwell_multimedia"))
      //{

      //   strName = "veriwell_multimedia";

      //}
      //else
      //{

      //   strName = "multimedia";

      //}

      //auto plibrary = get_library(strName);

      //if (plibrary)
      //{

//         auto pgetnewmultimedia = plibrary->get<PFUNCTION_GET_NEW_MULTIMEDIA>("get_new_multimedia");

  //       __compose(m_pmultimedia, ::move_transfer(pgetnewmultimedia()));

//    m_pmultimedia->initialize_multimedia(this);

      //}
      //else
      //{

      //   __compose(m_pmultimedia);

      //}

   }


   ::e_status system::defer_audio()
   {

      if(m_bAudio.undefined() || m_bAudio.is_true())
      {

         if (!m_paudio)
         {

            auto estatus = create_audio();

            if (!estatus)
            {

               return estatus;

            }

            return estatus;

         }

      }

      return ::success_none;

   }


   __namespace_system_factory(system);


} // namespace aqua



