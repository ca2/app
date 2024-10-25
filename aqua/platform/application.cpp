#include "framework.h"
#include "application.h"
#include "system.h"
#include "session.h"
#include "acme/handler/request.h"
#include "aqua/multimedia/media_item.h"
#include "aqua/multimedia/multimedia.h"
#include "aqua/xml/document.h"


namespace aqua
{



   //void initialize()
   //{

   //   factory()->add_factory_item< ::aqua::system, ::platform::system >();


   //}


   application::application()
   {

      //::aqua::initialize();

      //m_paquaapplication = this;
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


   void application::on_set_platform()
   {

      ::apex::application::on_set_platform();

      factory()->add_factory_item< ::aqua::system, ::platform::system >();
      factory()->add_factory_item < ::aqua::session, ::platform::session >();

   }


   //void application::on_initialize_application(::main* pmain)
   //{

   //   pmain->m_pplatform->factory()->add_factory_item< ::aqua::system, ::platform::system >();

   //}


   void application::exit_application()
   {

      if (system()->m_pmultimedia)
      {

         //auto estatus = 
         
         system()->m_pmultimedia->exit_application();

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

      system()->defer_audio();

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

         return false;

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

   //   system()-

   //}


   //::aqua::system* applicationacmesystem()
   //{

   //   return dynamic_cast <::aqua::system*> (system());

   //}

   void application::did_pick_media_item(::aqua::media_item * pmediaitem)
   {
      
      auto prequest = __create_new <::request>();
      
      prequest->m_payloadFile._set_element(pmediaitem);
      
      prequest->m_ecommand = ::e_command_file_open;
      
      this->request(prequest);

   }

::aqua::media_player * application::assign_media_player_to_media_item(::aqua::media_item * pmediaitem)
{
   
   if(pmediaitem->m_pmediaplayer)
   {
      
      return pmediaitem->m_pmediaplayer;
      
   }
   
   pmediaitem->assign_media_player();
   
   return pmediaitem->m_pmediaplayer;
   
}


} // namespace aqua



