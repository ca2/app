#include "framework.h"

#include "app-core/gcom/gcom/gcom_slide.h"


namespace browser
{


   pane_impact::pane_impact(::object * pobject) :
      object(pobject),
      ::user::tab_impact(pobject),
      ::userex::pane_tab_impact(pobject),
      place_holder_container(pobject)
   {

      m_pimpactLast = nullptr;
      m_pimpactLastBilbo = nullptr;
      m_prollfps = nullptr;
      m_pimpactdataTopic = nullptr;

      papp->m_ppaneimpact = this;

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

      if (ptabpaneMenu != nullptr && ptabpaneMenu->m_pholder != nullptr)
      {

         ptabpaneMenu->m_pholder->hide();

      }

      if(get_view_id() == MENU_IMPACT
            || get_view_id() == MAIN_IMPACT
            || get_view_id() == MAIN_SWITCHER_IMPACT
            || stra.contains(__string((int)MENU_IMPACT))
            || stra.contains(__string((int)MAIN_IMPACT))
            || stra.contains(__string((int)MAIN_SWITCHER_IMPACT)))
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
            
            auto ptabpaneMenu = get_tab_by_id(MENU_IMPACT);
            
            m_pimpactLast = dynamic_cast < impact_base * > (ptabpaneMenu->m_pholder->get_child_by_id("browser_gcom"));
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = ptabpaneMenu->m_straTitle.implode(" ");

         }
         else if(get_view_id() == MAIN_IMPACT)
         {

            m_pimpactLast = dynamic_cast < impact_base * > (get_pane_by_id(MAIN_IMPACT)->m_pholder->get_child_by_id("browser_view"));
            m_pimpactLastBilbo = dynamic_cast < impact * > (get_pane_by_id(MAIN_IMPACT)->m_pholder->get_child_by_id("browser_view"));
            m_pimpactLast->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(MAIN_IMPACT)->m_straTitle.implode(" ");

         }
         else if (get_view_id() == MAIN_SWITCHER_IMPACT)
         {

            m_pimpactLast = dynamic_cast < impact_base * > (get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_pholder->get_child_by_id("browser_switcher_view"));
            m_pimpactLastBilbo = dynamic_cast < impact * > (get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_pholder->get_child_by_id("browser_switcher_view"));
            m_pimpactLast->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_straTitle.implode(" ");

         }
         else if (stra.contains(__string((int)MAIN_IMPACT))
                  && stra.contains(__string((int)MAIN_SWITCHER_IMPACT)))
         {

            {

               auto pviewLast = dynamic_cast <impact_base *> (get_child_by_id("browser_view"));
               //m_pimpactLastBilbo = dynamic_cast <impact *> (get_pane_by_id(MAIN_IMPACT)->m_pholder->get_child_by_id("browser_view"));
               pviewLast->set_need_layout();
               //m_pimpactdataTopic = m_pimpactdata;
               //m_strTopicTitle = get_pane_by_id(MAIN_IMPACT)->m_straTitle.implode(" ");

            }
            {
               auto pviewLast = dynamic_cast <impact_base *> (get_child_by_id("browser_switcher_view"));
               //m_pimpactLastBilbo = dynamic_cast <impact *> (get_pane_by_id(MAIN_SWITCHER_IMPACT)->m_pholder->get_child_by_id("browser_switcher_view"));
               pviewLast->set_need_layout();
               //m_pimpactdataTopic = m_pimpactdata;
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

         ::user::impact * pimpact = m_pdocMenu->get_view(0);

         m_prollfps = dynamic_cast <::user::plain_edit_impact *> (pimpact->get_child_by_id("roll_fps"));

         m_pimpactLast->data_get("cur_fps_text", str);

         if (m_prollfps != nullptr)
         {

            m_prollfps->_001SetText(str, ::e_source_database);

         }

         if (m_pimpactLastBilbo == m_pimpactLast)
         {

            int i = 1;

            for (auto & pslide : m_pimpactLastBilbo->m_prender->slideshow())
            {

               __pointer(::user::check_box) pcheck = pimpact->get_child_by_id("slide" + __string(i));

               m_checkptraBilbo.add(pcheck);

               m_checkptraBilbo.last()->_001SetCheck(pslide->m_bDatabase ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);

               i++;

            }

         }

      }
      else if (get_view_id() == FONTSEL_IMPACT)
      {

         __pointer(::user::font_list_impact) pfontview = ptabpaneFontSel->m_pholder->get_child_by_id("font_list_impact");

         if (m_pimpactLastBilbo != nullptr && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pimpactLastBilbo->m_prender->m_strFont);

         }

      }
      else if (get_view_id() == COLORSEL_IMPACT)
      {

         if (m_pimpactLastBilbo != nullptr && m_pcolorview != nullptr)
         {

            m_pcolorview->set_color(m_pimpactLastBilbo->m_prender->m_hlsForeground);

         }

      }

      if (m_pimpactdataOld != nullptr && m_pimpactdataOld->m_atom == FONTSEL_IMPACT)
      {

         __pointer(::user::font_list_impact) pfontview = ptabpaneFontSel->m_pholder->get_child_by_id("font_list_impact");

         if (m_pimpactLastBilbo != nullptr && pfontview.is_set())
         {

            m_pimpactLastBilbo->m_prender->m_strFontHover.Empty();

            m_pimpactLastBilbo->set_need_layout();

         }

      }


   }



   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->m_atom)
      {
      case MENU_IMPACT:
      {

         m_pdocMenu = papp->create_child_form(this,pimpactdata->m_pplaceholder);

         ::user::impact * pimpact = m_pdocMenu->get_view(0);

         m_pimpactdata->m_puserinteraction = pimpact->get_parent_frame();

      }
      break;
      case GCOM_IMPACT:
      {
         create_view < gcom >(pimpactdata);


      }

      break;
      case MAIN_IMPACT:
      {

         papp->m_ptemplateHelloBrowserView->create_subdocument(pimpactdata);

      }
      break;
      case MAIN_SWITCHER_IMPACT:
      {

         papp->m_ptemplateHelloBrowserSwitcher->create_subdocument(pimpactdata);

      }
      break;
      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(m_pdocMenu != nullptr && ptopic->is_about(m_pdocMenu->get_view(0)))
      {

         if(ptopic->m_atom == ::id_after_change_text)
         {

            if(m_prollfps != nullptr && ptopic->user_element_id() == "roll_fps" && !ptopic->m_context.is(::e_source_initialize)
                  && !ptopic->m_context.is(::e_source_database))
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
                     m_pimpactLast->m_durationRoll.Now();
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

               ptopic->m_bRet = true;
               return;


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


            if (::str().begins_eat_ci(strCheck, "slide"))
            {

               if (ptopic->user_interaction() != nullptr && !ptopic->m_context.is(::e_source_initialize)
                     && !ptopic->m_context.is(::e_source_sync))
               {

                  int iCheck = atoi(strCheck);

                  __pointer(::user::check) pcheck = ptopic->user_interaction();

                  if (m_pimpactLastBilbo != nullptr && pcheck.is_set())
                  {

                     auto pslide = m_pimpactLastBilbo->m_prender->slideshow()[iCheck - 1];

                     pslide->enable(pcheck->echeck() == ::e_check_checked);

                     m_pimpactLastBilbo->data_set("slide." + pslide->m_strPath, pslide->m_bDatabase);

                     //m_pimpactLastBilbo->m_prender->defer_update_slide_show();

                  }

                  ptopic->m_bRet = true;
                  return;


               }

            }
         }

      }
      else
      {

         if (m_pfontview != nullptr && ptopic->user_interaction() == m_pfontview->m_pimpact)
         {

            if (ptopic->m_atom == ::id_after_change_cur_sel)
            {

               string strFont = m_pfontview->m_pimpact->get_cur_sel_face_name();

               if (strFont.has_char())
               {

                  m_pimpactLastBilbo->m_prender->m_strFontHover.Empty();

                  m_pimpactLastBilbo->m_prender->m_strFontSel = strFont;

                  m_pimpactLastBilbo->data_set("cur_font", strFont);

                  m_pimpactLastBilbo->set_need_layout();

               }

            }
            else if (ptopic->m_atom == ::id_after_change_cur_hover)
            {

               string strFont = m_pfontview->m_pimpact->get_cur_hover_face_name();

               if (strFont.has_char())
               {

                  m_pimpactLastBilbo->m_prender->m_strFontHover = strFont;

                  m_pimpactLastBilbo->set_need_layout();

               }

            }

         }
         else if (ptopic->user_interaction() == m_pcolorview)
         {


            if (ptopic->m_atom == ::id_after_change_cur_sel
                  || ptopic->m_atom == ::id_after_change_cur_hover)
            {

               m_pcolorview->get_color().get_hls(m_pimpactLastBilbo->m_prender->m_hlsForeground);

               if (ptopic->m_atom == ::id_after_change_cur_sel)
               {

                  m_pimpactLastBilbo->data_set("cur_color", m_pimpactLastBilbo->m_prender->m_hlsForeground);

               }

               m_pimpactLastBilbo->set_need_redraw();

            }

         }


      }


      ::userex::pane_tab_impact::handle(ptopic, pcontext);

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

      if (m_pimpactLastBilbo == m_pimpactLast)
      {

         int i = 1;

         for (auto & pslide : m_pimpactLastBilbo->m_prender->slideshow())
         {

            ::file::path path = pslide->m_strPath;

            string strName = path.title();

            strBilbo += "<input type=\"checkbox\" id=\"slide" + ::str().from(i) + "\" />slide &quot;" + strName + "&quot;<br/>\n<br/>";

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


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {



      ::userex::pane_tab_impact::handle(ptopic, pcontext);

   }


} // namespace browser



