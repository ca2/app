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


   ::estatus file_properties_form::initialize(::layered * pobjectContext)
   {

      auto estatus = ::user::impact_host::initialize(pobjectContext);

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


   __pointer(::user::interaction) file_properties_form::open(__pointer(::user::interaction) puieParent, ::file::item_array & itema)
   {

      m_itema = itema;

      if (itema.is_empty())
      {

         return nullptr;

      }

      auto pcreate = __new(create(this));

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserinteractionParent = puieParent;

      m_ptemplatePane->do_request(pcreate);

      __pointer(::user::document) pdocument = ::user::__document(pcreate);

      __pointer(::userex::pane_tab_view) pview = pdocument->get_typed_view < ::userex::pane_tab_view > ();

      m_ptabview = pview;

      pview->create_impact(1, "general", this);

      pview->create_impact(2, "advanced", this);

      pview->set_cur_tab_by_id(1);

      return pview->GetParentFrame();

   }


   void file_properties_form::page2()
   {

   }


   void file_properties_form::page1()
   {

      if(!m_pdocGeneral->on_open_document(Context.dir().matter("filemanager/file_properties.html")))
      {

         return;

      }

      if(m_itema.get_count() <= 0)
         return;

      __pointer(::user::interaction) pinteraction = m_pviewGeneral->get_child_by_name("name");

      pinteraction->_001SetText(m_itema[0]->m_filepathFinal.name(), ::source_none);

   }


   void file_properties_form::on_create_impact(::user::impact_data * pimpactdata)
   {
      switch(pimpactdata->m_id)
      {
      case 1:
      {
         m_pdocGeneral = User.create_form(this, this, m_ptabview);
         if(m_pdocGeneral != nullptr)
         {
            m_pviewGeneral = m_pdocGeneral->get_typed_view < ::user::form > ();
            m_pviewGeneral->set_form_callback(this);
            pimpactdata->m_pdocument = m_pdocGeneral;
            pimpactdata->m_puserinteraction = m_pviewGeneral->GetParentFrame();
         }
      }
      break;
      case 2:
      {
         /*if(m_netcfg.create(m_ptabview))
         {
            pimpactdata->m_pdocument = m_netcfg.m_pdocument;
            pimpactdata->m_puserinteraction = m_netcfg.m_pview->GetParentFrame();
         }*/

      }
      break;
      }
      if(pimpactdata->m_puserinteraction != nullptr)
      {
         pimpactdata->m_eflag.add(::user::flag_hide_all_others_on_show);
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

   void file_properties_form::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "submit")
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



