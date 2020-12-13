#include "framework.h"



namespace helloworld
{

   pane_view::pane_view(::layered * pobjectContext) :
      object(pobject),
      ::user::tab(pobject),

      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {
      m_pviewLast = nullptr;
      m_pviewLastBilbo = nullptr;
      m_prollfps = nullptr;
      m_pviewdataTopic = nullptr;
   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;

      set_tab("Menu",MENU_IMPACT);
      set_tab("helloworld", ::helloworld::PaneViewHelloWorld);
      set_tab("switcher",::helloworld::PaneViewHelloWorldSwitcher);
      set_tab("Font",FONTSEL_IMPACT);
#if 1
      set_tab("Open", FILEMANAGER_IMPACT);
#endif

      //set_cur_tab_by_id(GCOM_IMPACT);
      set_cur_tab_by_id(::helloworld::PaneViewHelloWorld);



   }



   void pane_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_view::_001OnNcDraw(pgraphics);

   }


   void pane_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_view::_001OnDraw(pgraphics);

   }


   void pane_view::on_change_cur_sel()
   {

      ::userex::pane_tab_view::on_change_cur_sel();
      string strId = get_view_id();
      string_array stra;
      m_prollfps = nullptr;
      m_checkptraBilbo.remove_all();

      stra.explode("->:<-",strId);

      if (get_pane_by_id(MENU_IMPACT)->m_pholder != nullptr)
      {

         get_pane_by_id(MENU_IMPACT)->m_pholder->ShowWindow(SW_HIDE);

      }

      if(get_view_id() == ::helloworld::PaneViewHelloWorld
            || get_view_id() == ::helloworld::PaneViewHelloWorldSwitcher
            || stra.contains(__str((int)::helloworld::PaneViewHelloWorld))
            || stra.contains(__str((int)::helloworld::PaneViewHelloWorldSwitcher)))
      {



         if(get_pane_by_id(FILEMANAGER_IMPACT) != nullptr && get_pane_by_id(FILEMANAGER_IMPACT)->m_pholder != nullptr)
         {

            get_pane_by_id(FILEMANAGER_IMPACT)->m_pholder->ShowWindow(SW_HIDE);

         }

         if (get_pane_by_id(FONTSEL_IMPACT) != nullptr && get_pane_by_id(FONTSEL_IMPACT)->m_pholder != nullptr)
         {

            get_pane_by_id(FONTSEL_IMPACT)->m_pholder->ShowWindow(SW_HIDE);

         }

         m_pviewLast = nullptr;
         m_pviewLastBilbo = nullptr;



         if(get_view_id() == ::helloworld::PaneViewHelloWorld)
         {

            m_pviewLast = dynamic_cast < impact_base * > (get_pane_by_id(::helloworld::PaneViewHelloWorld)->m_pholder->get_child_by_id("helloworld_view"));
            m_pviewLastBilbo = dynamic_cast < view * > (get_pane_by_id(::helloworld::PaneViewHelloWorld)->m_pholder->get_child_by_id("helloworld_view"));
            m_pviewLast->set_need_layout();
            m_pviewdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(::helloworld::PaneViewHelloWorld)->m_straTitle.implode(" ");

         }
         else if (get_view_id() == ::helloworld::PaneViewHelloWorldSwitcher)
         {

            m_pviewLast = dynamic_cast < impact_base * > (get_pane_by_id(::helloworld::PaneViewHelloWorldSwitcher)->m_pholder->get_child_by_id("helloworld_view"));
            m_pviewLastBilbo = dynamic_cast < view * > (get_pane_by_id(::helloworld::PaneViewHelloWorldSwitcher)->m_pholder->get_child_by_id("helloworld_view"));
            m_pviewLast->set_need_layout();
            m_pviewdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(::helloworld::PaneViewHelloWorldSwitcher)->m_straTitle.implode(" ");

         }


      }
      else if (get_view_id() == MENU_IMPACT)
      {

         //::user::tab_pane * ppane = get_pane(id_pane(get_view_id()));

         ::file::path path = prepare_menu_view();

         m_pdocMenu->open_document(path);

         if (m_pimpactdata->m_puserinteraction != nullptr)
         {

            m_pimpactdata->m_puserinteraction->ShowWindow(SW_HIDE);

         }

         string str;

         ::user::impact * pview = m_pdocMenu->get_view(0);

         m_prollfps = dynamic_cast <::calculator::plain_edit_view *> (pview->get_child_by_id("roll_fps"));

         m_pviewLast->data_get("cur_fps_text", str);

         if (m_prollfps != nullptr)
         {

            m_prollfps->_001SetText(str, ::source_database);

         }

         if (m_pviewLastBilbo != nullptr)
         {

            int i = 1;

            for (auto & bilbo : m_pviewLastBilbo->m_prender->m_bilboa)
            {

               m_checkptraBilbo.add(dynamic_cast <::user::check_box *> (pview->get_child_by_id("bilbo" + __str(i))));

               m_checkptraBilbo.last()->_001SetCheck(bilbo.m_b ? ::check_checked : ::check_unchecked, ::source_sync);

               i++;

            }

         }

      }
      else if (get_view_id() == FONTSEL_IMPACT)
      {

         __pointer(::user::font_list_view) pfontview = get_pane_by_id(FONTSEL_IMPACT)->m_pholder->get_child_by_id("font_list_view");

         if (m_pviewLast != nullptr && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pviewLast->m_strFont);

         }

      }


   }



   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_id)
      {
      case impact_menu:
      {

         m_pdocMenu = Application.create_child_form(this,pimpactdata->m_pplaceholder);

         ::user::impact * pview = m_pdocMenu->get_view(0);

         m_pimpactdata->m_puserinteraction = pview->GetParentFrame();


         //::file::path path = prepare_menu_view();

         //m_pdocMenu->open_document(path);


//         m_prollspf = pview->get_child_by_id("roll_spf");
         //try
         //{
         //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(Application.should_auto_launch_clockverse_on_hover(),::source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag")->_001SetCheck(Application.should_bind_flag_country_ca2_domain_image_on_hover(),::source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag_auto")->_001SetCheck(Application.should_auto_launch_flag_on_hover(),::source_initialize);
         //}
         //catch(...)
         //{
         //}



      }
      break;
      case PaneViewHelloWorld:
      {

         Application.m_ptemplateHelloWorldView->create_subdocument(pimpactdata);

      }
      break;
      case PaneViewHelloWorldSwitcher:
      {

         Application.m_ptemplateHelloWorldSwitcher->create_subdocument(pimpactdata);

      }
      break;
      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::on_control_event(::user::control_event * pevent)
   {

      if(m_pdocMenu != nullptr && dynamic_cast < ::user::impact * > (pview) == m_pdocMenu->get_view(0) && pevent->m_puie != nullptr)
      {

         if(pevent->m_eevent == ::user::e_event_after_change_text)
         {

            if(m_prollfps != nullptr && pevent->m_puie->m_id == "roll_fps" && !pevent->m_context.is_source(::source_initialize)
                  && !pevent->m_context.is_source(::source_database))
            {

               try
               {
                  string str;
                  double d = m_prollfps->get_ex_value()["real"];
                  if(m_pviewLast != nullptr)
                  {


                     {

                        string str;

                        m_prollfps->_001GetText(str);

                        m_pviewLast->data_set("cur_fps_text",str);

                     }

                     {

                        payload v;

                        v = d;

                        m_pviewLast->data_set("cur_fps",v);

                     }
                     m_pviewLast->m_dFps = d;
                     m_pviewLast->m_dwRoll= ::millis::now();
                  }
                  //if(fabs(d) < 0.0000000001)
                  //{
                  //   m_prollspf->_001SetText("",::source_initialize);
                  //}
                  //else
                  //{
                  //   m_prollspf->_001SetText(__str(1.0/d),::source_initialize);
                  //}
               }
               catch(...)
               {
               }

            }
            //else if(pevent->m_puie->m_id == "roll_spf" && !pevent->m_context.is_source(::source_initialize))
            //{

            //   try
            //   {
            //      string str;
            //      m_prollspf->_001GetText(str);
            //      double d = atof(str);
            //      if(fabs(d) < 0.0000000001)
            //      {
            //         m_prollfps->_001SetText("",::source_initialize);
            //      }
            //      else
            //      {
            //         m_pflagview->m_dFps = 1.0/ d;
            //         m_pflagview->m_dwRoll= ::millis::now();
            //         m_prollfps->_001SetText(__str(1.0 / d),::source_initialize);
            //      }
            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }
         else if (pevent->m_eevent == ::user::e_event_set_check && pevent->m_puie != nullptr)
         {

            string strCheck = pevent->m_puie->m_id;


            if (::str::begins_eat_ci(strCheck, "bilbo"))
            {

               if (pevent->m_puie != nullptr && !pevent->m_context.is_source(::source_initialize)
                     && !pevent->m_context.is_source(::source_sync))
               {

                  int iCheck = atoi(strCheck);

                  if (m_pviewLastBilbo != nullptr)
                  {

                     m_pviewLastBilbo->m_prender->m_bilboa[iCheck - 1].m_bNew = pevent->m_puie->_001GetCheck() == ::check_checked;

                     m_pviewLastBilbo->m_prender->defer_update_bilbo();

                  }

               }

            }

         }

         //if(pevent->m_puie->m_id == "clockverse")
         //   {
         //      Application.set_binding_clockverse_country_time_zone_set_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "clockverse_auto")
         //   {
         //      Application.set_auto_launch_clockverse_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "flag")
         //   {
         //      Application.set_binding_flag_country_ca2_domain_image_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //   else if(pevent->m_puie->m_id == "flag_auto")
         //   {
         //      Application.set_auto_launch_flag_on_hover(pevent->m_puie->_001GetCheck() == ::check_checked);
         //      return true;
         //   }
         //}
      }

      return false;
   }


   ::file::path pane_view::prepare_menu_view()
   {

      string str;

      string strBilbo;

      if (m_pviewLast == nullptr && m_pviewLastBilbo == nullptr)
      {

         str = Context.file().as_string("matter://home.html");

      }
      else
      {

         str = Context.file().as_string("matter://menu.html");

      }

      if (m_pviewLastBilbo != nullptr)
      {

         int i = 1;

         for (auto & bilbo : m_pviewLastBilbo->m_prender->m_bilboa)
         {

            ::file::path path = bilbo.m_strPath;

            string strName = path.name();

            strBilbo += "<input type=\"checkbox\" id=\"bilbo" + str::from(i) + "\" />bilbo &quot;" + strName + "&quot;<br/>\n<br/>";

            i++;

         }

      }

      if (m_strTopicTitle.has_char())
      {

         str.replace("Helloworld!!", m_strTopicTitle);

      }
      else
      {

         str.replace("Helloworld!!", "");

      }

      str.replace("***bilbo***", strBilbo);

      ::file::path path;

      path = Context.dir().appdata() / "helloworld_menu.html";

      Context.file().put_contents(path, str);

      return path;

   }


   void pane_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::update * pupdate = dynamic_cast <::update *> (pupdate);

      if (pupdate != nullptr)
      {

         if (pupdate->m_ehint == CONTROL_EVENT_UPDATE
               && psubject->m_puserinteraction == m_pfontview
               && m_pviewLast != nullptr)
         {

            if(pupdate->m_pusercontrolevent->m_eevent == ::user::e_event_after_change_cur_sel)
            {

               string strFont = m_pfontview->m_pview->get_cur_sel_face_name();

               if (strFont.has_char())
               {

                  m_pviewLast->m_strHoverFont = strFont;

                  m_pviewLast->m_strNewFont = strFont;

                  m_pviewLast->on_layout(::draw2d::graphics_pointer & pgraphics);

               }

            }
            else if (pupdate->m_pusercontrolevent->m_eevent == ::user::e_event_after_change_cur_hover)
            {

               string strFont = m_pfontview->m_pview->get_cur_hover_face_name();

               if (strFont.has_char())
               {

                  m_pviewLast->m_strHoverFont = strFont;

                  m_pviewLast->on_layout(::draw2d::graphics_pointer & pgraphics);

               }

            }

         }

      }

      ::userex::pane_tab_view::on_subject(psubject, pcontext);

   }


} // namespace helloworld





