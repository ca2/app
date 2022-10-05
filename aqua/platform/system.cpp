#include "framework.h"
#include "acme/parallelization/pool.h"
#include "acme/platform/system_setup.h"
#include "aqua/constant/idpool.h"
#include "aqua/multimedia/audio/audio.h"
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

      ::factory::add_factory_item < ::aqua::application, ::apex::application >();
      ::factory::add_factory_item < ::aqua::session, ::apex::session >();
      ::factory::add_factory_item < ::aqua::idpool, ::acme::idpool >();
      ::factory::add_factory_item < ::aqua::multimedia >();

   }


   void system::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::apex::system::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

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
      
      __compose_new(m_pxml);

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
      pfactory->__compose(this, m_paudio);

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


   void system::defer_multimedia()
   {

      if (m_pmultimedia)
      {

         return;

      }

      synchronous_lock synchronouslock(&m_mutexLibrary4);

      try
      {

         auto psetup = ::system_setup::get_first(::system_setup::flag_multimedia);

         if (psetup)
         {

            auto pelement = psetup->create_element();

            //if (!pelement)
            //{

            //   throw ::exception()

            //   //return error_no_factory;

            //}

            //auto estatus = 
            
            __compose(m_pmultimedia, pelement);

            //if (!estatus)
            //{

            //   return estatus;

            //}

         }

      }
      catch (...)
      {

         throw ::exception(error_exception);

      }

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

  //       __compose(m_pmultimedia, ::move_transfer(pgetnewmultimedia()));

//    m_pmultimedia->initialize_multimedia(this);

      //}
      //else
      //{

      //   __compose(m_pmultimedia);

      //}

   }


   void system::defer_audio()
   {

      if(m_bAudio.is_true())
      {

         if (!m_paudio)
         {

            //auto estatus =
            
            create_audio();

            //if (!estatus)
            //{

            //   return estatus;

            //}

            m_bAudio = ::is_set(m_paudio);

            //return estatus;

         }

      }

      //return ::success_none;

   }


   bool system::has_audio()
   {

      return !m_bAudio.undefined() && m_bAudio.is_true();

   }



} // namespace aqua



