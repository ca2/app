#include "framework.h"



namespace helloworld
{

   pane_impact::pane_impact(::particle * pparticle) :
      object(pparticle),
      ::user::tab(pparticle),

      ::user::tab_impact(pparticle),
      ::userex::pane_tab_impact(pparticle),
      place_holder_container(pparticle)
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
      set_tab("helloworld", ::helloworld::PaneImpactHelloWorld);
      set_tab("switcher",::helloworld::PaneImpactHelloWorldSwitcher);
      set_tab("Font",FONTSEL_IMPACT);
#if 1
      set_tab("Open", FILEMANAGER_IMPACT);
#endif

      //set_current_tab_by_id(GCOM_IMPACT);
      set_current_tab_by_id(::helloworld::PaneImpactHelloWorld);



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
      string strId = get_impact_id();
      string_array stra;
      m_prollfps = nullptr;
      m_checkptraBilbo.erase_all();

      stra.explode("->:<-",strId);

      auto ptabpaneMenu = get_tab_by_id(MENU_IMPACT);

      if (ptabpaneMenu->m_pholder != nullptr)
      {

         ptabpaneMenu->m_pholder->show_window(SW_HIDE);

      }

      if(get_impact_id() == ::helloworld::PaneImpactHelloWorld
            || get_impact_id() == ::helloworld::PaneImpactHelloWorldSwitcher
            || stra.contains(as_string((int)::helloworld::PaneImpactHelloWorld))
            || stra.contains(as_string((int)::helloworld::PaneImpactHelloWorldSwitcher)))
      {



         if(ptabpaneFileManager != nullptr && ptabpaneFileManager->m_pholder != nullptr)
         {

            ptabpaneFileManager->m_pholder->show_window(SW_HIDE);

         }

         if (ptabpaneFontSel != nullptr && ptabpaneFontSel->m_pholder != nullptr)
         {

            ptabpaneFontSel->m_pholder->show_window(SW_HIDE);

         }

         m_pimpactLast = nullptr;
         m_pimpactLastBilbo = nullptr;



         if(get_impact_id() == ::helloworld::PaneImpactHelloWorld)
         {

            m_pimpactLast = dynamic_cast < impact_base * > (get_pane_by_id(::helloworld::PaneImpactHelloWorld)->m_pholder->get_child_by_id("helloworld_impact"));
            m_pimpactLastBilbo = dynamic_cast < impact * > (get_pane_by_id(::helloworld::PaneImpactHelloWorld)->m_pholder->get_child_by_id("helloworld_impact"));
            m_pimpactLast->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(::helloworld::PaneImpactHelloWorld)->m_straTitle.implode(" ");

         }
         else if (get_impact_id() == ::helloworld::PaneImpactHelloWorldSwitcher)
         {

            m_pimpactLast = dynamic_cast < impact_base * > (get_pane_by_id(::helloworld::PaneImpactHelloWorldSwitcher)->m_pholder->get_child_by_id("helloworld_impact"));
            m_pimpactLastBilbo = dynamic_cast < impact * > (get_pane_by_id(::helloworld::PaneImpactHelloWorldSwitcher)->m_pholder->get_child_by_id("helloworld_impact"));
            m_pimpactLast->set_need_layout();
            m_pimpactdataTopic = m_pimpactdata;
            m_strTopicTitle = get_pane_by_id(::helloworld::PaneImpactHelloWorldSwitcher)->m_straTitle.implode(" ");

         }


      }
      else if (get_impact_id() == MENU_IMPACT)
      {

         //::user::tab_pane * ppane = get_pane(id_pane(get_impact_id()));

         ::file::path path = prepare_menu_impact();

         m_pdocMenu->open_document(path);

         if (m_pimpactdata->m_puserinteraction != nullptr)
         {

            m_pimpactdata->m_puserinteraction->show_window(SW_HIDE);

         }

         string str;

         ::user::impact * pimpact = m_pdocMenu->get_impact(0);

         m_prollfps = dynamic_cast <::calculator::plain_edit_impact *> (pimpact->get_child_by_id("roll_per_second"));

         m_pimpactLast->datastream()->get("cur_fps_text", str);

         if (m_prollfps != nullptr)
         {

            m_prollfps->set_text(str, ::e_source_database);

         }

         if (m_pimpactLastBilbo != nullptr)
         {

            int i = 1;

            for (auto & bilbo : m_pimpactLastBilbo->m_prender->m_bilboa)
            {

               m_checkptraBilbo.add(dynamic_cast <::user::check_box *> (pimpact->get_child_by_id("bilbo" + as_string(i))));

               m_checkptraBilbo.last()->set_check(bilbo.m_b ? ::e_check_checked : ::e_check_unchecked, ::e_source_sync);

               i++;

            }

         }

      }
      else if (get_impact_id() == FONTSEL_IMPACT)
      {

         ::pointer<::user::font_list_impact>pfontview = ptabpaneFontSel->m_pholder->get_child_by_id("font_list_impact");

         if (m_pimpactLast != nullptr && pfontview.is_set())
         {

            pfontview->set_sel_by_name(m_pimpactLast->m_strFont);

         }

      }


   }



   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      switch(pimpactdata->id())
      {
      case impact_menu:
      {

         m_pdocMenu = papp->create_child_form(this,pimpactdata->m_pplaceholder);

         ::user::impact * pimpact = m_pdocMenu->get_impact(0);

         m_pimpactdata->m_puserinteraction = pimpact->get_parent_frame();


         //::file::path path = prepare_menu_impact();

         //m_pdocMenu->open_document(path);


//         m_prollspf = pimpact->get_child_by_id("roll_spf");
         //try
         //{
         //   pform->get_child_by_id("clockverse_auto")->set_check(papp->should_auto_launch_clockverse_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag")->set_check(papp->should_bind_flag_country_ca2_domain_image_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}

         //try
         //{
         //   pform->get_child_by_id("flag_auto")->set_check(papp->should_auto_launch_flag_on_hover(),::e_source_initialize);
         //}
         //catch(...)
         //{
         //}



      }
      break;
      case PaneImpactHelloWorld:
      {

         papp->m_ptemplateHelloWorldView->create_subdocument(pimpactdata);

      }
      break;
      case PaneImpactHelloWorldSwitcher:
      {

         papp->m_ptemplateHelloWorldSwitcher->create_subdocument(pimpactdata);

      }
      break;
      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      if(m_pdocMenu != nullptr && dynamic_cast < ::user::impact * > (pimpact) == m_pdocMenu->get_impact(0) && ptopic->user_interaction() != nullptr)
      {

         if(ptopic->id() == ::id_after_change_text)
         {

            if(m_prollfps != nullptr && ptopic->user_interaction_id() == "roll_per_second" && !ptopic->m_context.is_source(::e_source_initialize)
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

                        m_prollfps->get_text(str);

                        m_pimpactLast->datastream()->set("cur_fps_text",str);

                     }

                     {

                        ::payload v;

                        v = d;

                        m_pimpactLast->datastream()->set("cur_per_second",v);

                     }
                     m_pimpactLast->m_frequencyFramesPerSecond = d;
                     m_pimpactLast->m_dwRoll= ::time::now();
                  }
                  //if(fabs(d) < 0.0000000001)
                  //{
                  //   m_prollspf->set_text("",::e_source_initialize);
                  //}
                  //else
                  //{
                  //   m_prollspf->set_text(as_string(1.0/d),::e_source_initialize);
                  //}
               }
               catch(...)
               {
               }

            }
            //else if(ptopic->user_interaction_id() == "roll_spf" && !ptopic->m_context.is_source(::e_source_initialize))
            //{

            //   try
            //   {
            //      string str;
            //      m_prollspf->get_text(str);
            //      double d = atof(str);
            //      if(fabs(d) < 0.0000000001)
            //      {
            //         m_prollfps->set_text("",::e_source_initialize);
            //      }
            //      else
            //      {
            //         m_pflagview->m_frequencyFramesPerSecond = 1.0/ d;
            //         m_pflagview->m_dwRoll= ::time::now();
            //         m_prollfps->set_text(as_string(1.0 / d),::e_source_initialize);
            //      }
            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }
         else if (ptopic->id() == ::id_set_check && ptopic->user_interaction() != nullptr)
         {

            string strCheck = ptopic->user_interaction_id();


            if (strCheck.case_insensitive_begins_eat("bilbo"))
            {

               if (ptopic->user_interaction() != nullptr && !ptopic->m_context.is_source(::e_source_initialize)
                     && !ptopic->m_context.is_source(::e_source_sync))
               {

                  int iCheck = atoi(strCheck);

                  if (m_pimpactLastBilbo != nullptr)
                  {

                     m_pimpactLastBilbo->m_prender->m_bilboa[iCheck - 1].m_bNew = ptopic->user_interaction()->get_check() == ::e_check_checked;

                     m_pimpactLastBilbo->m_prender->defer_update_bilbo();

                  }

               }

            }

         }

         //if(ptopic->user_interaction_id() == "clockverse")
         //   {
         //      papp->set_binding_clockverse_country_time_zone_set_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "clockverse_auto")
         //   {
         //      papp->set_auto_launch_clockverse_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "flag")
         //   {
         //      papp->set_binding_flag_country_ca2_domain_image_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //   else if(ptopic->user_interaction_id() == "flag_auto")
         //   {
         //      papp->set_auto_launch_flag_on_hover(ptopic->user_interaction()->get_check() == ::e_check_checked);
         //      return true;
         //   }
         //}
      }

      return false;
   }


   ::file::path pane_impact::prepare_menu_impact()
   {

      string str;

      string strBilbo;

      if (m_pimpactLast == nullptr && m_pimpactLastBilbo == nullptr)
      {

         str = file()->as_string("matter://home.html");

      }
      else
      {

         str = file()->as_string("matter://menu.html");

      }

      if (m_pimpactLastBilbo != nullptr)
      {

         int i = 1;

         for (auto & bilbo : m_pimpactLastBilbo->m_prender->m_bilboa)
         {

            ::file::path path = bilbo.m_strPath;

            string strName = path.name();

            strBilbo += "<input type=\"checkbox\" id=\"bilbo" + ::str::from(i) + "\" />bilbo &quot;" + strName + "&quot;<br/>\n<br/>";

            i++;

         }

      }

      if (m_strTopicTitle.has_character())
      {

         str.replace("Helloworld!!", m_strTopicTitle);

      }
      else
      {

         str.replace("Helloworld!!", "");

      }

      str.replace("***bilbo***", strBilbo);

      ::file::path path;

      path = directory()->appdata() / "helloworld_menu.html";

      file()->put_contents(path, str);

      return path;

   }


   void pane_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      ::update * pupdate = dynamic_cast <::update *> (pupdate);

      if (pupdate != nullptr)
      {

         if (pupdate->m_ehint == CONTROL_EVENT_UPDATE
               && ptopic->user_interaction() == m_pfontimpact
               && m_pimpactLast != nullptr)
         {

            if(pupdate->m_pusercontrolevent->m_ehappening == ::id_after_change_cur_sel)
            {

               string strFont = m_pfontimpact->m_pimpact->get_cur_sel_face_name();

               if (strFont.has_character())
               {

                  m_pimpactLast->m_strHoverFont = strFont;

                  m_pimpactLast->m_strNewFont = strFont;

                  m_pimpactLast->on_layout(pgraphics);

               }

            }
            else if (pupdate->m_pusercontrolevent->m_ehappening == ::id_after_change_cur_hover)
            {

               string strFont = m_pfontimpact->m_pimpact->get_cur_hover_face_name();

               if (strFont.has_character())
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





