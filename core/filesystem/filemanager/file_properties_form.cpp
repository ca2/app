#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   file_properties_form::file_properties_form()
   {

   }


   file_properties_form::~file_properties_form()
   {

   }


   ::e_status file_properties_form::initialize(::object * pobject)
   {

      auto estatus = ::user::impact_host::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_ptemplatePane = __new(::user::single_document_template(
         "system/auth",
         __type(::user::document),
         __type(simple_frame_window),
         __type(::userex::pane_tab_view)));

      return estatus;

   }


   __pointer(::user::interaction) file_properties_form::open(__pointer(::user::interaction) puserinteractionParent, ::file::item_array & itema)
   {

      m_itema = itema;

      if (itema.is_empty())
      {

         return nullptr;

      }

      auto pcreate = __create_new< ::create >();

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->finish_initialization();

      m_ptemplatePane->do_request(pcreate);

      __pointer(::user::document) pdocument = ::user::__document(pcreate);

      __pointer(::userex::pane_tab_view) pview = pdocument->get_typed_view < ::userex::pane_tab_view > ();

      m_ptabview = pview;

      pview->create_impact(1, "general", this);

      pview->create_impact(2, "advanced", this);

      pview->set_current_tab_by_id(1);

      return pview->get_parent_frame();

   }


   void file_properties_form::page2()
   {

   }


   void file_properties_form::page1()
   {

      auto pcontext = get_context();

      ::file::path path = pcontext->m_papexcontext->dir().matter("filemanager/file_properties.html");

      if(!m_pdocGeneral->on_open_document(path))
      {

         return;

      }

      if (m_itema.is_empty())
      {

         return;

      }

      auto pinteraction = m_pviewGeneral->get_child_by_name("name");

      string strName = m_itema[0]->m_filepathFinal.name();

      pinteraction->_001SetText(strName, ::e_source_none);

   }


   void file_properties_form::on_create_impact(::user::impact_data * pimpactdata)
   {
      switch(pimpactdata->m_id)
      {
      case 1:
      {

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         m_pdocGeneral = puser->create_form(this, this, m_ptabview);

         if(m_pdocGeneral != nullptr)
         {
            m_pviewGeneral = m_pdocGeneral->get_typed_view < ::user::form > ();
            m_pviewGeneral->set_form_callback(this);
            pimpactdata->m_pdocument = m_pdocGeneral;
            pimpactdata->m_puserinteraction = m_pviewGeneral->get_parent_frame();
         }
      }
      break;
      case 2:
      {
         /*if(m_netcfg.create(m_ptabview))
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
      switch(get_view_id())
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

   void file_properties_form::handle(::subject * psubject, ::context * pcontext)
   {

      if(psubject->m_id == ::e_subject_click)
      {

         if(psubject->user_interaction()->m_id == "submit")
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



