#include "framework.h"
#include "system.h"
#include "application.h"
#include "session.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/pool.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system_setup.h"
#include "aqua/constant/idpool.h"
#include "aqua/audio/audio.h"
#include "aqua/audio/audio_mixer.h"
#include "aqua/multimedia/multimedia.h"
#include "aqua/xml/xml.h"


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

      //factory()->add_factory_item < ::aqua::application, ::apex::application >();
      //factory()->add_factory_item < ::aqua::idpool, ::acme::idpool >();
      //factory()->add_factory_item < ::aqua::multimedia >();

   }


   void system::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::apex::system::initialize(pparticle);


      factory()->add_factory_item < ::aqua::session, ::apex::session >();


      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::on_add_session(::acme::session* papexsession)
   {

      ::apex::system::on_add_session(papexsession);

      //if (papexsession->m_iEdge == 0)
      //{

      //   if (!m_papex)
      //   {

      //      m_paquasession = papexsession->m_paquasession;

      //   }

      //}

      //papexsession->m_paquasystem = this;

   }

   //void system::initialize_rich_text()
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

      //auto estatus = 
      
      __construct_new(m_pxml);

      //if (!estatus)
      //{

      //   return m_pxml;

      //}

      //estatus =
      
      m_pxml->init1();

      //if (!estatus)
      //{

      //   return m_pxml;

      //}

      //estatus = 
      m_pxml->init();

      //if (!estatus)
      //{

      //   return m_pxml;

      //}

      return m_pxml;

   }


   void system::create_audio()
   {

      auto & pfactory = factory("audio");

      //if (!pfactory)
      //{

      //   return pfactory;

      //}

      //auto estatus = 
      pfactory->__construct(this, m_paudio);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ///estatus = 
      m_paudio->init3();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::aqua::multimedia* system::defer_get_multimedia()
   {

      if (!m_pmultimedia)
      {

         defer_multimedia();

      }

      return m_pmultimedia;

   }


   ::aqua::audio_mixer * system::get_audio_mixer()
   {

      if (!m_paudiomixer)
      {

         defer_audio_mixer();

      }

      return m_paudiomixer;

   }


   void system::defer_multimedia()
   {

      if (m_pmultimedia)
      {

         return;

      }

//      critical_section_lock synchronouslock(&m_psubsystem->m_criticalsection);

      //try
      //{

//         auto psetup = ::system_setup::get_first(::system_setup::flag_multimedia);
//
//         if (psetup)
//         {
//
//            auto pelement = psetup->create_particle();

            //if (!pelement)
            //{

            //   throw ::exception()

            //   //return error_no_factory;

            //}

            //auto estatus = 
            
//            __construct(m_pmultimedia, pelement);
      __construct(m_pmultimedia);

            //if (!estatus)
            //{

            //   return estatus;

            //}

//         }
//
//      }
//      catch (...)
//      {
//
//         throw ::exception(error_exception);
//
//      }

      ///auto estatus = 
      
      m_pmultimedia->initialize_multimedia(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;
      

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

  //       __construct(m_pmultimedia, ::pointer_transfer(pgetnewmultimedia()));

//    m_pmultimedia->initialize_multimedia(this);

      //}
      //else
      //{

      //   __construct(m_pmultimedia);

      //}

   }


   void system::defer_audio_mixer()
   {

      if (m_paudiomixer)
      {

         return;

      }

      ::factory::factory_pointer pfactory;

#ifdef WINDOWS_DESKTOP

      pfactory = factory("audio_mixer", "mmsystem");

#elif defined(LINUX)

      pfactory = factory("audio_mixer", "alsa");

#endif

      pfactory->merge_to_global_factory();

      pfactory->__construct(this, m_paudiomixer);

      if (m_paudiomixer)
      {

         m_paudiomixer->init1();

      }

   }


   void system::defer_audio()
   {

      if(acmeapplication()->m_bAudio.is_true())
      {

         if (!m_paudio)
         {

            //auto estatus =
            
            create_audio();

            //if (!estatus)
            //{

            //   return estatus;

            //}

            acmeapplication()->m_bAudio = ::is_set(m_paudio);

            //return estatus;

         }

      }

      //return ::success_none;

   }


   bool system::has_audio()
   {

      return !acmeapplication()->m_bAudio.undefined() && acmeapplication()->m_bAudio.is_true();

   }



} // namespace aqua



