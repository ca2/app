#include "framework.h"



namespace helloworld
{

   pane_impact::pane_impact(::object * pobject) :
      object(pobject),
      ::user::tab(pobject),

      ::user::tab_impact(pobject),
      ::userex::pane_tab_impact(pobject),
      place_holder_container(pobject)
   {
      m_pimpactLast = nullptr;
      m_pimpactLastBilbo = nullptr;
      m_prollfps = nullptr;
      m_pimpactdataTopic = nullptr;
   }


   pane_impact::~pane_impact()
   {

   }


   void pane_impact::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void pane_impact::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::userex::pane_tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);

   }


   void pane_impact::on_message_create(::message::message * pmessage)
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

      //set_current_tab_by_id(GCOM_IMPACT);
      set_current_tab_by_id(::helloworld::PaneViewHelloWorld);



   }



   void pane_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnNcDraw(pgraphics);

   }


   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::userex::pane_tab_impact::_001OnDraw(pgraphics);

   }


   void pane_impact::on_change_cur_sel()
   {

      ::userex::pane_tab_impact::on_change_cur_sel();
      string strId = get_view_id();
      string_array stra;
      m_prollfps = nullptr;
      m_checkptraBilbo.erase_all();

      stra.explode("->:<-",strId);

      auto ptabpaneMenu = get_tab_by_id(MENU_IMPACT);

      if (ptabpaneMenu->m_pholder != nullptr)
      {

         ptabpaneMenu->m_pholder->ShowWindow(SW_HIDE);

      }

      if(get_view_id() == ::helloworld::PaneViewHelloWorld
            || get_view_id() == ::helloworld::PaneViewHelloWorldSwitcher
            || stra.contains(__string((int)::helloworld::PaneViewHelloWorld))
            || stra.contains(__string((int)::helloworld::PaneViewHelloWorldSwitcher)))
      {



         if(ptabpaneFileManager != nullptr && ptabpaneFileManager->m_pholder != nullptr)
         {

            ptabpaneFileManager->m_pholder->ShowWindow(SW_HIDE);

         }

         if (ptabpaneFontSel != nullptr && ptabpaneFontSel->m_pholder != nullptr)
         {

            ptabpaneFontSel->m_pholder->ShowWindow(SW_HIDE);

         }

         m_pimpactLast = nullptr;
         m_pimpactLastBilbo = nullptr;



         if(get_view_id() == ::helloworld::PaneViewHelloWorld)
         {

            m_pimpactLast = dynamic_cast < impact_base * > (get_pane_by_id(::helloworld::PaneViewHelloWorld)->m_pholder->get_child_by_id("helloworld_view"));
            m_pimpactLastBilbo = dynamic_cast < impact * > (get_pane_by_id(::helloworld::PaneViewHelloWorld)->m_pholder->get_child_by_id("helloworld_view"));
            m_pimpactLast->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(::helloworld::PaneViewHelloWorld)->m_straTitle.implode(" ");

         }
         else if (get_view_id() == ::helloworld::PaneViewHelloWorldSwitcher)
         {

            m_pimpactLast = dynamic_cast < impact_base * > (get_pane_by_id(::helloworld::PaneViewHelloWorldSwitcher)->m_pholder->get_child_by_id("helloworld_view"));
            m_pimpactLastBilbo = dynamic_cast < impact * > (get_pane_by_id(::helloworld::PaneViewHelloWorldSwitcher)->m_pholder->get_child_by_id("helloworld_view"));
            m_pimpactLast->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
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

         ::user::impact * pimpact = m_pdocMenu->get_view(0);

         m_prollfps = dynamic_cast <::calculator::plain_edit_view *> (pimpact->get_child_by_id("roll_fps"));

         m_pimpactLast->data_get("cur_fps_text", str);

         if (m_prollfps != nullptr)
         {

            m_prollfps->_001SetText(str, ::e_source_database);

         }

         if (m_pimpactLastBilbo != nullptr)
         {

            int i = 1;

            for (auto & bilbo : m_pimpactLastBilbo->m_prender->m_bilboa)
            {

               m_checkptraBilbo.add(dynamic_cast <::user::check_box *> (pimpact->get_child_by_id("bilbo" + __string(i))));

               m_checkptraBilbo.last()->_001SetCheck(bilbo.m_b ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);

               i++;

            }

         }

      }
      else if (get_view_id() == FONTSEL_IMPACT)
      {

         __pointer(::user::font_list_view) pfontview = ptabpaneFontSel->m_pholder->get_child_by_id("font_list_view");

         if (m_pimpactLast != nullptr && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pimpactLast->m_strFont);

         }

      }


   }



   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_atom)
      {
      case impact_menu:
      {

         m_pdocMenu = papp->create_child_form(this,pimpactdata->m_pplaceholder);

         ::user::impact * pimpact = m_pdocMenu->get_view(0);

         m_pimpactdata->m_puserinteraction = pimpact->get_parent_frame();


         //::file::path path = prepare_menu_view();

         //m_pdocMenu->open_document(path);


//         m_prollspf = pimpact->get_child_by_id("roll_spf");
         //try
         //{
         //   pform->get_child_by_id("clockverse_auto")->_001SetCheck(papp->should_auto_launch_clockverse_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag")->_001SetCheck(papp->should_bind_flag_country_ca2_domain_image_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag_auto")->_001SetCheck(papp->should_auto_launch_flag_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}



      }
      break;
      case PaneViewHelloWorld:
      {

         papp->m_ptemplateHelloWorldView->create_subdocument(pimpactdata);

      }
      break;
      case PaneViewHelloWorldSwitcher:
      {

         papp->m_ptemplateHelloWorldSwitcher->create_subdocument(pimpactdata);

      }
      break;
      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(m_pdocMenu != nullptr && dynamic_cast < ::user::impact * > (pimpact) == m_pdocMenu->get_view(0) && ptopic->user_interaction() != nullptr)
      {

         if(ptopic->m_atom == ::id_after_change_text)
         {

            if(m_prollfps != nullptr && ptopic->user_element_id() == "roll_fps" && !ptopic->m_context.is_source(::e_source_initialize)
                  && !ptopic->m_context.is_source(::e_source_database))
            {

               try
               {
                  string str;
                  double d = m_prollfps->get_ex_value()["real"];
                  if(m_pimpactLast != nullptr)
                  {


                     {

                        string str;

                        m_prollfps->_001GetText(str);

                        m_pimpactLast->data_set("cur_fps_text",str);

                     }

                     {

                        ::payload v;

                        v = d;

                        m_pimpactLast->data_set("cur_fps",v);

                     }
                     m_pimpactLast->m_dFps = d;
                     m_pimpactLast->m_dwRoll= ::duration::now();
                  }
                  //if(fabs(d) < 0.0000000001)
                  //{
                  //   m_prollspf->_001SetText("",::e_source_initialize);
                  //}
                  //else
                  //{
                  //   m_prollspf->_001SetText(__string(1.0/d),::e_source_initialize);
                  //}
               }
               catch(...)
               {
               }

            }
            //else if(ptopic->user_element_id() == "roll_spf" && !ptopic->m_context.is_source(::e_source_initialize))
            //{

            //   try
            //   {
            //      string str;
            //      m_prollspf->_001GetText(str);
            //      double d = atof(str);
            //      if(fabs(d) < 0.0000000001)
            //      {
            //         m_prollfps->_001SetText("",::e_source_initialize);
            //      }
            //      else
            //      {
            //         m_pflagview->m_dFps = 1.0/ d;
            //         m_pflagview->m_dwRoll= ::duration::now();
            //         m_prollfps->_001SetText(__string(1.0 / d),::e_source_initialize);
            //      }
            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }
         else if (ptopic->m_atom == ::id_set_check && ptopic->user_interaction() != nullptr)
         {

            string strCheck = ptopic->user_element_id();


            if (::str().begins_eat_ci(strCheck, "bilbo"))
            {

               if (ptopic->user_interaction() != nullptr && !ptopic->m_context.is_source(::e_source_initialize)
                     && !ptopic->m_context.is_source(::e_source_sync))
               {

                  int iCheck = atoi(strCheck);

                  if (m_pimpactLastBilbo != nullptr)
                  {

                     m_pimpactLastBilbo->m_prender->m_bilboa[iCheck - 1].m_bNew = ptopic->user_interaction()->_001GetCheck() == ::e_check_checked;

                     m_pimpactLastBilbo->m_prender->defer_update_bilbo();

                  }

               }

            }

         }

         //if(ptopic->user_element_id() == "clockverse")
         //   {
         //      papp->set_binding_clockverse_country_time_zone_set_on_hover(ptopic->user_interaction()->_001GetCheck() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_element_id() == "clockverse_auto")
         //   {
         //      papp->set_auto_launch_clockverse_on_hover(ptopic->user_interaction()->_001GetCheck() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_element_id() == "flag")
         //   {
         //      papp->set_binding_flag_country_ca2_domain_image_on_hover(ptopic->user_interaction()->_001GetCheck() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_element_id() == "flag_auto")
         //   {
         //      papp->set_auto_launch_flag_on_hover(ptopic->user_interaction()->_001GetCheck() == ::e_check_checked);
         //      return true;
         //   }
         //}
      }

      return false;
   }


   ::file::path pane_impact::prepare_menu_view()
   {

      string str;

      string strBilbo;

      if (m_pimpactLast == nullptr && m_pimpactLastBilbo == nullptr)
      {

         str = pcontext->m_papexcontext->file().as_string("matter://home.html");

      }
      else
      {

         str = pcontext->m_papexcontext->file().as_string("matter://menu.html");

      }

      if (m_pimpactLastBilbo != nullptr)
      {

         int i = 1;

         for (auto & bilbo : m_pimpactLastBilbo->m_prender->m_bilboa)
         {

            ::file::path path = bilbo.m_strPath;

            string strName = path.name();

            strBilbo += "<input type=\"checkbox\" id=\"bilbo" + ::str().from(i) + "\" />bilbo &quot;" + strName + "&quot;<br/>\n<br/>";

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

      path = pcontext->m_papexcontext->dir().appdata() / "helloworld_menu.html";

      pcontext->m_papexcontext->file().put_contents(path, str);

      return path;

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::update * pupdate = dynamic_cast <::update *> (pupdate);

      if (pupdate != nullptr)
      {

         if (pupdate->m_ehint == CONTROL_EVENT_UPDATE
               && ptopic->user_interaction() == m_pfontview
               && m_pimpactLast != nullptr)
         {

            if(pupdate->m_pusercontrolevent->m_eevent == ::id_after_change_cur_sel)
            {

               string strFont = m_pfontview->m_pimpact->get_cur_sel_face_name();

               if (strFont.has_char())
               {

                  m_pimpactLast->m_strHoverFont = strFont;

                  m_pimpactLast->m_strNewFont = strFont;

                  m_pimpactLast->on_layout(pgraphics);

               }

            }
            else if (pupdate->m_pusercontrolevent->m_eevent == ::id_after_change_cur_hover)
            {

               string strFont = m_pfontview->m_pimpact->get_cur_hover_face_name();

               if (strFont.has_char())
               {

                  m_pimpactLast->m_strHoverFont = strFont;

                  m_pimpactLast->on_layout(pgraphics);

               }

            }

         }

      }

      ::userex::pane_tab_impact::handle(ptopic, pcontext);

   }


} // namespace helloworld





