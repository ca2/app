#include "framework.h"

#include "app-core/gcom/gcom/gcom_slide.h"


namespace browser
{


   pane_view::pane_view(::object * pobject) :
      object(pobject),
      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {

      m_pviewLast = nullptr;
      m_pviewLastBilbo = nullptr;
      m_prollfps = nullptr;
      m_pviewdataTopic = nullptr;

      papplication->m_ppaneview = this;

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

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::on_message_create);

   }


   void pane_view::on_message_create(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;

      set_tab("Menu",MENU_IMPACT);
      set_tab("gcom", GCOM_IMPACT);
      set_tab("browser", MAIN_IMPACT);
      set_tab("switcher",MAIN_SWITCHER_IMPACT);
      set_tab("Font",FONTSEL_IMPACT);
      set_tab("Color", COLORSEL_IMPACT);
#if 1
      set_tab("Open", FILEMANAGER_IMPACT);
#endif

      set_current_tab_by_id(MAIN_IMPACT);

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
      m_checkptraBilbo.erase_all();

      stra.explode("->:<-",strId);

      if (get_pane_by_id(MENU_IMPACT) != nullptr && get_pane_by_id(MENU_IMPACT)->m_pholder != nullptr)
      {

         get_pane_by_id(MENU_IMPACT)->m_pholder->hide();

      }

      if(get_view_id() == MENU_IMPACT
            || get_view_id() == MAIN_IMPACT
            || get_view_id() == MAIN_SWITCHER_IMPACT
            || stra.contains(__str((int)MENU_IMPACT))
            || stra.contains(__str((int)MAIN_IMPACT))
            || stra.contains(__str((int)MAIN_SWITCHER_IMPACT)))
      {



         if(ptabpaneFileManager != nullptr && ptabpaneFileManager->m_pholder != nullptr)
         {

            ptabpaneFileManager->m_pholder->hide();

         }

         if (ptabpaneFontSel != nullptr && ptabpaneFontSel->m_pholder != nullptr)
         {

            ptabpaneFontSel->m_pholder->hide();

         }

         if (ptabpaneColorSel != nullptr && ptabpaneColorSel->m_pholder != nullptr)
         {

            ptabpaneColorSel->m_pholder->hide();

         }

         if(get_view_id() == MENU_IMPACT)
         {

            m_pviewLast = dynamic_cast < impact_base * > (get_pane_by_id(MENU_IMPACT)->m_pholder->get_child_by_id("browser_gcom"));
            m_pviewdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(MENU_IMPACT)->m_straTitle.implode(" ");

         }
         else if(get_view_id() == MAIN_IMPACT)
         {

            m_pviewLast = dynamic_cast < impact_base * > (get_pane_by_id(MAIN_IMPACT)->m_pholder->get_child_by_id("browser_view"));
            m_pviewLastBilbo = dynamic_cast < view * > (get_pane_by_id(MAIN_IMPACT)->m_pholder->get_child_by_id("browser_view"));
            m_pviewLast->set_need_layout();
            m_pviewdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(MAIN_IMPACT)->m_straTitle.implode(" ");

         }
         else if (get_view_id() == MAIN_SWITCHER_IMPACT)
         {

            m_pviewLast = dynamic_cast < impact_base * > (get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_pholder->get_child_by_id("browser_switcher_view"));
            m_pviewLastBilbo = dynamic_cast < view * > (get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_pholder->get_child_by_id("browser_switcher_view"));
            m_pviewLast->set_need_layout();
            m_pviewdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_straTitle.implode(" ");

         }
         else if (stra.contains(__str((int)MAIN_IMPACT))
                  && stra.contains(__str((int)MAIN_SWITCHER_IMPACT)))
         {

            {

               auto pviewLast = dynamic_cast <impact_base *> (get_child_by_id("browser_view"));
               //m_pviewLastBilbo = dynamic_cast <view *> (get_pane_by_id(MAIN_IMPACT)->m_pholder->get_child_by_id("browser_view"));
               pviewLast->set_need_layout();
               //m_pviewdataTopic = m_pimpactdata;
               //m_strTopicTitle = get_pane_by_id(MAIN_IMPACT)->m_straTitle.implode(" ");

            }
            {
               auto pviewLast = dynamic_cast <impact_base *> (get_child_by_id("browser_switcher_view"));
               //m_pviewLastBilbo = dynamic_cast <view *> (get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_pholder->get_child_by_id("browser_switcher_view"));
               pviewLast->set_need_layout();
               //m_pviewdataTopic = m_pimpactdata;
               //m_strTopicTitle = get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_straTitle.implode(" ");
            }

         }


      }
      else if (get_view_id() == MENU_IMPACT)
      {

         ::file::path path = prepare_menu_view();

         if (!m_pdocMenu->open_document(path))
         {

            message_box(get_parent_frame(), "Failed to open the menu.", e_message_box_ok);

            return;

         }

         string str;

         ::user::impact * pview = m_pdocMenu->get_view(0);

         m_prollfps = dynamic_cast <::user::plain_edit_view *> (pview->get_child_by_id("roll_fps"));

         m_pviewLast->data_get("cur_fps_text", str);

         if (m_prollfps != nullptr)
         {

            m_prollfps->_001SetText(str, ::e_source_database);

         }

         if (m_pviewLastBilbo == m_pviewLast)
         {

            int i = 1;

            for (auto & pslide : m_pviewLastBilbo->m_prender->slideshow())
            {

               __pointer(::user::check_box) pcheck = pview->get_child_by_id("slide" + __str(i));

               m_checkptraBilbo.add(pcheck);

               m_checkptraBilbo.last()->_001SetCheck(pslide->m_bDatabase ? ::check_checked : ::check_unchecked, ::e_source_sync);

               i++;

            }

         }

      }
      else if (get_view_id() == FONTSEL_IMPACT)
      {

         __pointer(::user::font_list_view) pfontview = ptabpaneFontSel->m_pholder->get_child_by_id("font_list_view");

         if (m_pviewLastBilbo != nullptr && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pviewLastBilbo->m_prender->m_strFont);

         }

      }
      else if (get_view_id() == COLORSEL_IMPACT)
      {

         if (m_pviewLastBilbo != nullptr && m_pcolorview != nullptr)
         {

            m_pcolorview->set_color(m_pviewLastBilbo->m_prender->m_hlsForeground);

         }

      }

      if (m_pimpactdataOld != nullptr && m_pimpactdataOld->m_id == FONTSEL_IMPACT)
      {

         __pointer(::user::font_list_view) pfontview = ptabpaneFontSel->m_pholder->get_child_by_id("font_list_view");

         if (m_pviewLastBilbo != nullptr && pfontview.is_set())
         {

            m_pviewLastBilbo->m_prender->m_strFontHover.Empty();

            m_pviewLastBilbo->set_need_layout();

         }

      }


   }



   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_id)
      {
      case MENU_IMPACT:
      {

         m_pdocMenu = papplication->create_child_form(this,pimpactdata->m_pplaceholder);

         ::user::impact * pview = m_pdocMenu->get_view(0);

         m_pimpactdata->m_puserinteraction = pview->get_parent_frame();

      }
      break;
      case GCOM_IMPACT:
      {
         create_view < gcom >(pimpactdata);


      }

      break;
      case MAIN_IMPACT:
      {

         papplication->m_ptemplateHelloBrowserView->create_subdocument(pimpactdata);

      }
      break;
      case MAIN_SWITCHER_IMPACT:
      {

         papplication->m_ptemplateHelloBrowserSwitcher->create_subdocument(pimpactdata);

      }
      break;
      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::on_control_event(::user::control_event * pevent)
   {

      if(m_pdocMenu != nullptr && dynamic_cast < ::user::impact * > (pevent->get_form()) == m_pdocMenu->get_view(0) && pevent->m_puserinteraction != nullptr)
      {

         if(pevent->m_eevent == ::user::e_event_after_change_text)
         {

            if(m_prollfps != nullptr && pevent->m_puserinteraction->m_id == "roll_fps" && !pevent->m_context.is(::e_source_initialize)
                  && !pevent->m_context.is(::e_source_database))
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

                        ::payload v;

                        v = d;

                        m_pviewLast->data_set("cur_fps",v);

                     }
                     m_pviewLast->m_dFps = d;
                     m_pviewLast->m_millisRoll.Now();
                  }
                  //if(fabs(d) < 0.0000000001)
                  //{
                  //   m_prollspf->_001SetText("",::e_source_initialize);
                  //}
                  //else
                  //{
                  //   m_prollspf->_001SetText(__str(1.0/d),::e_source_initialize);
                  //}
               }
               catch(...)
               {
               }

               pevent->m_bRet = true;
               return;


            }
            //else if(pevent->m_puserinteraction->m_id == "roll_spf" && !pevent->m_context.is_source(::e_source_initialize))
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
            //         m_pflagview->m_dwRoll= ::millis::now();
            //         m_prollfps->_001SetText(__str(1.0 / d),::e_source_initialize);
            //      }
            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }
         else if (pevent->m_eevent == ::user::e_event_set_check && pevent->m_puserinteraction != nullptr)
         {

            string strCheck = pevent->m_puserinteraction->m_id;


            if (::str::begins_eat_ci(strCheck, "slide"))
            {

               if (pevent->m_puserinteraction != nullptr && !pevent->m_context.is(::e_source_initialize)
                     && !pevent->m_context.is(::e_source_sync))
               {

                  int iCheck = atoi(strCheck);

                  __pointer(::user::check) pcheck = pevent->m_puserinteraction;

                  if (m_pviewLastBilbo != nullptr && pcheck.is_set())
                  {

                     auto pslide = m_pviewLastBilbo->m_prender->slideshow()[iCheck - 1];

                     pslide->enable(pcheck->echeck() == ::check_checked);

                     m_pviewLastBilbo->data_set("slide." + pslide->m_strPath, pslide->m_bDatabase);

                     //m_pviewLastBilbo->m_prender->defer_update_slide_show();

                  }

                  pevent->m_bRet = true;
                  return;


               }

            }
         }

      }
      else
      {

         if (m_pfontview != nullptr && pevent->m_puserinteraction == m_pfontview->m_pview)
         {

            if (pevent->m_eevent == ::user::e_event_after_change_cur_sel)
            {

               string strFont = m_pfontview->m_pview->get_cur_sel_face_name();

               if (strFont.has_char())
               {

                  m_pviewLastBilbo->m_prender->m_strFontHover.Empty();

                  m_pviewLastBilbo->m_prender->m_strFontSel = strFont;

                  m_pviewLastBilbo->data_set("cur_font", strFont);

                  m_pviewLastBilbo->set_need_layout();

               }

            }
            else if (pevent->m_eevent == ::user::e_event_after_change_cur_hover)
            {

               string strFont = m_pfontview->m_pview->get_cur_hover_face_name();

               if (strFont.has_char())
               {

                  m_pviewLastBilbo->m_prender->m_strFontHover = strFont;

                  m_pviewLastBilbo->set_need_layout();

               }

            }

         }
         else if (pevent->m_puserinteraction == m_pcolorview)
         {


            if (pevent->m_eevent == ::user::e_event_after_change_cur_sel
                  || pevent->m_eevent == ::user::e_event_after_change_cur_hover)
            {

               m_pcolorview->get_color().get_hls(m_pviewLastBilbo->m_prender->m_hlsForeground);

               if (pevent->m_eevent == ::user::e_event_after_change_cur_sel)
               {

                  m_pviewLastBilbo->data_set("cur_color", m_pviewLastBilbo->m_prender->m_hlsForeground);

               }

               m_pviewLastBilbo->set_need_redraw();

            }

         }


      }


      ::userex::pane_tab_view::on_control_event(pevent);

   }


   ::file::path pane_view::prepare_menu_view()
   {

      string str;

      string strBilbo;

      if (m_pviewLast == nullptr && m_pviewLastBilbo == nullptr)
      {

         str = pcontext->m_papexcontext->file().as_string("matter://home.html");

      }
      else
      {

         str = pcontext->m_papexcontext->file().as_string("matter://menu.html");

      }

      if (m_pviewLastBilbo == m_pviewLast)
      {

         int i = 1;

         for (auto & pslide : m_pviewLastBilbo->m_prender->slideshow())
         {

            ::file::path path = pslide->m_strPath;

            string strName = path.title();

            strBilbo += "<input type=\"checkbox\" id=\"slide" + str::from(i) + "\" />slide &quot;" + strName + "&quot;<br/>\n<br/>";

            i++;

         }

      }

      if (m_strTopicTitle.has_char())
      {

         str.replace("Hellomultiverse!!", m_strTopicTitle);

      }
      else
      {

         str.replace("Hellomultiverse!!", "");

      }

      str.replace("***bilbo***", strBilbo);

      ::file::path path;

      path = pcontext->m_papexcontext->dir().appdata() / "browser_menu.html";

      pcontext->m_papexcontext->file().put_contents(path, str);

      return path;

   }


   void pane_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {



      ::userex::pane_tab_view::on_subject(psubject, pcontext);

   }


} // namespace browser



