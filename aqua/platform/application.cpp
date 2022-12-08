#include "framework.h"
#include "application.h"
#include "system.h"
#include "session.h"
#include "aqua/multimedia/multimedia.h"
#include "aqua/xml/document.h"


namespace aqua
{



   //void initialize()
   //{

   //   factory()->add_factory_item< ::aqua::system, ::acme::system >();


   //}


   application::application()
   {

      factory()->add_factory_item< ::aqua::system, ::acme::system >();
      factory()->add_factory_item < ::aqua::session, ::acme::session >();
      //::aqua::initialize();

      m_paquaapplication = this;
      ///set_layer(LAYERED_AQUA, this);


   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::apex::application::initialize(pparticle);


      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //void application::on_initialize_application(::main* pmain)
   //{

   //   pmain->m_psubsystem->factory()->add_factory_item< ::aqua::system, ::acme::system >();

   //}


   void application::exit_application()
   {

      if (acmesystem()->m_paquasystem->m_pmultimedia)
      {

         //auto estatus = 
         
         acmesystem()->m_paquasystem->m_pmultimedia->exit_application();

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //auto estatus = 
      
      ::apex::application::exit_application();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application::init2()
   {

      ::apex::application::init2();

      acmesystem()->m_paquasystem->defer_audio();

   }




   void application::game_on_create(::aqua::game * pgame)
   {

   }


   bool application::load_cached_string(string& str, const ::atom& atom, bool bLoadStringTable)
   {

      auto pxmldocument = __create_new < ::xml::document >();

      try
      {

         pxmldocument->load(atom);

      }
      catch(...)
      {

         return load_cached_string_by_id(str, atom, bLoadStringTable);

      }

      auto pnodeRoot = pxmldocument->root();

      if (!pnodeRoot)
      {

         return atom;

      }

      if (pnodeRoot->get_name() == "string")
      {

         string strId = pnodeRoot->attribute("id");

         if (!load_cached_string_by_id(str, strId, bLoadStringTable))
         {

            str = pnodeRoot->get_value();

         }

         return true;

      }

      return false;

   }


   //LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   acmesystem()-

   //}


   //::aqua::system* applicationacmesystem()
   //{

   //   return dynamic_cast <::aqua::system*> (acmesystem());

   //}


} // namespace aqua



