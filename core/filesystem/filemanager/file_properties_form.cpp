#include "framework.h"
#include "file_properties_form.h"
#include "acme/constant/id.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "acme/handler/request.h"
#include "core/user/userex/pane_tab_impact.h"
#include "core/user/user/user.h"
#include "core/platform/session.h"
#include "base/user/simple/frame_window.h"
#include "base/user/user/single_document_template.h"
#include "base/user/user/document.h"
#include "base/user/form/document.h"


namespace filemanager
{


   file_properties_form::file_properties_form()
   {

   }


   file_properties_form::~file_properties_form()
   {

   }


   void file_properties_form::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::user::impact_host::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_ptemplatePane = __new(::user::single_document_template(
         "system/auth",
         __type(::user::document),
         __type(simple_frame_window),
         __type(::userex::pane_tab_impact)));

      //return estatus;

   }


   ::pointer<::user::interaction>file_properties_form::open(::pointer<::user::interaction>puserinteractionParent, ::file::item_array & itema)
   {

      m_itema = itema;

      if (itema.is_empty())
      {

         return nullptr;

      }

      auto prequest = __create_new< ::request >();

      prequest->m_bMakeVisible = false;

      prequest->m_puserelementParent = puserinteractionParent;

      prequest->finish_initialization();

      m_ptemplatePane->request(prequest);

      ::pointer<::user::document>pdocument = ::user::__document(prequest);

      ::pointer<::userex::pane_tab_impact>ptabimpact = pdocument->get_typed_impact < ::userex::pane_tab_impact > ();

      m_ptabimpact = ptabimpact;

      auto pimpactkit = ptabimpact->get_impact_kit();

      pimpactkit->add_impact_item(1, "general", this);

      pimpactkit->add_impact_item(2, "advanced", this);

      ptabimpact->add_impact_kit_items();

      ptabimpact->set_current_tab_by_id(1);

      return ptabimpact->parent_frame();

   }


   void file_properties_form::page2()
   {

   }


   void file_properties_form::page1()
   {

      auto pcontext = get_context();

      ::file::path path = dir()->matter("filemanager/file_properties.html");

      if(!m_pdocGeneral->on_open_document(path))
      {

         return;

      }

      if (m_itema.is_empty())
      {

         return;

      }

      auto pinteraction = m_pviewGeneral->get_child_by_name("name");

      string strName = m_itema[0]->final_path().name();

      pinteraction->_001SetText(strName, ::e_source_none);

   }


   //::pointer<::user::impact_kit>file_properties_form::get_impact_kit()
   //{

   //   auto pimpactkit = __create_new < ::user::impact_kit >();

   //   pimpactkit->add_impact_item(1, "general", this);



   //}


   void file_properties_form::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_atom.as_i32())
      {
      case 1:
      {

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pacmesession->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         m_pdocGeneral = puser->create_form(this, nullptr, this, m_ptabimpact);

         if(m_pdocGeneral != nullptr)
         {
            m_pviewGeneral = m_pdocGeneral->get_typed_impact < ::user::form > ();
            m_pviewGeneral->set_form_callback(this);
            pimpactdata->m_pdocument = m_pdocGeneral;
            pimpactdata->m_puserinteraction = m_pviewGeneral->parent_frame();
         }
      }
      break;
      case 2:
      {
         /*if(m_netcfg.create(m_ptabimpact))
         {
            pimpactdata->m_pdocument = m_netcfg.m_pdocument;
            pimpactdata->m_puserinteraction = m_netcfg.m_pimpact->get_parent_frame();
         }*/

      }
      break;
      }
      if(pimpactdata->m_puserinteraction != nullptr)
      {
         pimpactdata->m_eflag.add(::user::e_flag_hide_all_others_on_show);
      }

   }


   void file_properties_form::on_change_cur_sel()
   {

      switch(get_impact_id().as_i32())
      {
      case 1:
      {
         page1();
      }
      break;
      case 2:
      {
         //m_netcfg.on_show();
      }
      break;
      }
   }

   void file_properties_form::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_interaction()->m_atom == "submit")
         {

         }

      }

   }


   /*::form_property_set * file_properties_form::get_form_property_set()
   {

      auto pset = form_callback::get_form_property_set();

      if(pset)
      {

         return pset;

      }

      pset = ::user::impact_host::get_form_property_set();

      if(pset)
      {

         return pset;

      }

      return nullptr;

   }*/


} // namespace filemanager



