#include "framework.h"


namespace userstack
{


   pane_impact::pane_impact(::object * pobject) :
      ::object(pobject),
      ::user::tab_impact(pobject),
      ::userex::pane_tab_impact(pobject),
      place_holder_container(pobject)
   {

      m_iNewArea        = 0;
      m_iArea           = -1;
      m_pimpactdataOld    = nullptr;

      m_pimpactdata       = nullptr;
      m_pimpactdataOld    = nullptr;

      m_iDisplay        = -1;
      m_ppropform       = nullptr;
      //m_dataid          = "ca2::bergedge::pane_impact";

      get_data()->m_matchanyRestore.add(new ::aura::match::prefix("app:"));

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


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      __pointer(frame) pframe =  (get_parent_frame());
      pframe->m_ppaneimpact = this;


      papp->m_ppaneimpact = this;



      add_tab("menu", CONTEXT_MENU_IMPACT);

      for(i32 i = 0; i < papp->m_varTopicQuery["app"].stra().get_count(); i++)
      {

         string strId = papp->m_varTopicQuery["app"].stra()[i];

         if(i == 0 && strId == "app/sphere/userstack")
            continue;

         add_tab(strId, "app:" + strId);

         set_current_tab_by_id("app:" + papp->m_varTopicQuery["app"].stra()[i]);

      }

      for (i32 i = 0; i < papp->m_varTopicQuery["app/sphere/userstack"]["tab"].stra().get_count(); i++)
      {

         set_current_tab_by_id("app:" + papp->m_varTopicQuery["app/sphere/userstack"]["tab"].stra()[i]);

      }

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::tab_impact::handle(ptopic, pcontext);
      
   }


   void pane_impact::on_change_cur_sel()
   {
      ::userex::pane_tab_impact::on_change_cur_sel();
//      __pointer(frame) pframe =  (get_parent_frame());
      string strId = get_view_id();
      if(::str().begins_eat(strId, "app:"))
      {

         __pointer(::aura::application) pappTab;

         if(psession->appptra().lookup("application:" + strId, pappTab))
         {
            psession->m_pappCurrent = pappTab;
            //psession->m_pappCurrent = pappTab;
         }
         /*            __pointer(::simple_frame_window) pframeApp = dynamic_cast < __pointer(::simple_frame_window) > (m_pimpactdata->m_puserinteraction);
                  if(pframeApp != nullptr)
                  {
                     pframeApp->display(e_display_full_screen);
                  }*/
      }
      //   else if(get_view_id() == CONTEXT_MENU_IMPACT)
      //   {
      //      /*bergedge::menu_impact * pimpact = dynamic_cast < bergedge::menu_impact *  > (get_view());
      //      __pointer(::filemanager::document) pdocument = (pimpact->get_document());
      //      pdocument->FileManagerBrowse(pcontext->m_papexcontext->dir().appdata() / "bergedge\\menu"), ::e_source_system);*/
      //   }
      //   else if(get_view_id() ==CONFIGURATION_IMPACT)
      //   {
      ///*      __pointer(::user::interaction) pinteraction = m_pformOptions->ve_display_bandwidth");
      //      matter * pcheck = dynamic_cast < matter * > (puie);
      //      if(psession->savings().save().has(::ca2::save_display_bandwidth))
      //      {
      //         pcheck->_001SetCheck(e_check_checked, false);
      //      }
      //      else
      //      {
      //         pcheck->_001SetCheck(e_check_unchecked, false);
      //      }*/
      //   }
      //   else if(get_view_id() == ::bergedge::impact_winactionarea)
      //   {
      //      string strDirName;
      //      strDirName.format("desktop-%d", m_iDisplay);
      //      string strDir = pcontext->m_papexcontext->dir().userfolder(strDirName);
      //      if(m_iDisplay <= 0)
      //      {
      //         check_desktop_dir(strDir);
      //      }
      //      __pointer(::filemanager::document) pdocument =  (m_pimpactdata->m_pdocument);
      //      pdocument->FileManagerBrowse(strDir, ::e_source_system);
      //   }
      else
      {
//         pframe->m_bAutoHideOnOutClick = true;
      }
      /*if(m_pimpactdataOld != nullptr)
      {
         if(m_pimpactdataOld->m_puserinteraction != nullptr)
         {
            m_pimpactdataOld->m_puserinteraction->hide();
         }
      }*/
   }

   bool pane_impact::pre_create_window(::user::system * pusersystem)
   {


      return ::user::impact::pre_create_window(pusersystem);
   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      string strId = pimpactdata->m_atom;

      if(::str().begins_eat(strId, "app:"))
      {

         __pointer(::aura::application) pappTab;

         if(!psession->appptra().lookup("application:" + strId, pappTab))
         {

            application_bias * pappbias = new application_bias;
            pappbias->m_puserinteractionParent = pimpactdata->m_pplaceholder;

            __pointer(::create) pcreate(e_create);
            pcreate->m_pappbias = pappbias;
            pcreate->_001ParseCommandFork(strId);


            string str;

            if(papp->has_property(strId))
            {

               pcreate->).merge(papp->m_varTopicQuery[(const ::string &) strId].propset());

               if(papp->m_varTopicQuery[(const ::string &) strId].has_property("file"))
               {

                  pcreate->m_payloadFile = papp->m_varTopicQuery[(const ::string &) strId]["file"];

               }

            }

            str = __string((iptr) pcreate->m_pappbias->m_puserinteractionParent);

            pcreate->m_eventReady.ResetEvent();

            psession->on_request(pcreate);

            pcreate->m_eventReady.wait();

         }

         __pointer(::aura::application) pappCurrent = psession->m_pappCurrent;

         papp->appptra_add(pappCurrent);

         string strTypeId = typeid(*pappCurrent.m_p).name();

         string strIcon = Sess(pappCurrent).dir().matter("mainframe/icon48.png");

         ::user::tab_pane * ppane = (::user::tab_pane *) get_pane_by_id(pimpactdata->m_atom);

         pappCurrent = psession->m_pappCurrent;

         if(Sess(pappCurrent).file().exists(strIcon))
         {

/*            ppane->m_pimage->create(this);

/*            ppane->m_pimage = load_image(strIcon);

         }
         else
         {

            ppane->set_title(pimpactdata->m_atom);

         }

         on_layout(pgraphics);

      }

      ::userex::pane_tab_impact::on_create_impact(pimpactdata);

   }



   void pane_impact::_001OnMenuMessage(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      set_current_tab_by_id(m_pimpactdataOld->m_atom);
   }

   void pane_impact::install_message_routing(::channel * pchannel)
   {
      ::userex::pane_tab_impact::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);
      MESSAGE_LINK(WM_USER + 1122, this, this, &pane_impact::_001OnMenuMessage);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &pane_impact::on_message_right_button_up);
      add_command_handler("properties", &pane_impact::_001OnProperties);
   }

   void pane_impact::rotate()
   {
   }

   /*void pane_impact::OnFileManagerOpenFile(
         ::filemanager::data * pdata,
         ::file::item_array & itema)
   {
      if(itema.get_size() > 0)
      {
         i32 i = (i32) ::ShellExecuteW(
            get_top_level()->get_handle(),
            nullptr,
            L"\"" + utf8_to_unicode(itema[0].m_strPath) + L"\"",
            nullptr,
            L"\"" + utf8_to_unicode(pcontext->m_papexcontext->dir().name(itema[0].m_strPath)) + L"\"",
            SW_SHOWNORMAL);
         string str;
         str.format("%d", i);
         //message_box(str);
         if(i == ERROR_FILE_NOT_FOUND)
         {
         }
      }
      //get_parent_frame()->hide();
   }*/

   void pane_impact::check_menu_dir(const ::file::path & psz)
   {

      ::file::listing straPath(get_app());

      straPath.rls(pcontext->m_papexcontext->dir().commonprograms());

      for(i32 i = 0; i < straPath.get_size(); i++)
      {

         ::file::path str = psz/straPath[i].relative();

         pcontext->m_papexcontext->dir().create(str.folder());

         pcontext->m_papexcontext->file().copy(str, straPath[i], true);

      }

      straPath.clear_results();

      straPath.rls(pcontext->m_papexcontext->dir().userprograms(nullptr));

      for(i32 i = 0; i < straPath.get_size(); i++)

      {
         ::file::path str = psz / straPath[i].relative();

         pcontext->m_papexcontext->dir().create(str.folder());

         pcontext->m_papexcontext->file().copy(str, straPath[i], true);

      }

   }


   void pane_impact::check_3click_dir(const ::file::path & psz)
   {

      if(pcontext->m_papexcontext->dir().is(psz))
      {

         return;

      }

      pcontext->m_papexcontext->dir().create(psz);

      string strDir(psz);

      POSITION pos = psystem->m_mapAppLibrary.get_start_position();

      string strApp;

      string strLibrary;

      while(pos != nullptr)
      {

         psystem->m_mapAppLibrary.get_next_assoc(pos, strApp, strLibrary);

         if(::str().begins_eat(strApp, "application:"))
         {

            pcontext->m_papexcontext->file().put_contents(strDir / strApp + ".ca2", "ca2prompt\r\n"+ strApp);

         }

      }

      //pcontext->m_papexcontext->file().put_contents(pcontext->m_papexcontext->dir().path(strDir, "veriwell Musical Player.ca2"), "ca2prompt\r\nmplite");
      /*      string_array straPath;
            string_array straRelative;
            straPath.erase_all();
            pcontext->m_papexcontext->dir().rls(pcontext->m_papexcontext->dir().userquicklaunch(), &straPath, nullptr, &straRelative);
            for(i32 i = 0; i < straPath.get_size(); i++)
            {
               string str = pcontext->m_papexcontext->dir().path(psz, straRelative[i]);
               pcontext->m_papexcontext->dir().create(pcontext->m_papexcontext->dir().name(str));
               ::CopyFile(straPath[i], str, true);
            }*/
   }


   void pane_impact::check_desktop_dir(const ::file::path & psz)
   {

#ifdef WINDOWS_DESKTOP

      ::file::listing listing(get_app());

//      wchar_t buf[4096];
//      __memset(buf, 0, sizeof(buf));
//      SHGetSpecialFolderPath(
//      nullptr,
//      buf,
//      CSIDL_COMMON_DESKTOPDIRECTORY,
//      false);
//      if(wcslen(buf) > 0)
//      {
//         if(wcslen(buf) > 0)
//         {
//            listing.rls(buf);
//            for(i32 i = 0; i < listing.get_size(); i++)
//            {
//
//               ::file::path str = psz / listing[i].relative();
//
//               pcontext->m_papexcontext->dir().create(str.folder());
//
//               ::CopyFileW(wstring(listing[i]), wstring(str), true);
//
//            }
//         }
//      }
//      __memset(buf, 0, sizeof(buf));
//      SHGetSpecialFolderPath(
//      nullptr,
//      buf,
//      CSIDL_DESKTOPDIRECTORY,
//      false);
//      if(strlen(buf) > 0)
//      {
//         if(strlen(buf) > 0)
//         {
//            listing.clear_results();
//            listing.rls(buf);
//            for(i32 i = 0; i < listing.get_size(); i++)
//            {
//               ::file::path str = psz / listing[i].relative();
//               pcontext->m_papexcontext->dir().create(listing[i].folder());
//               ::CopyFile(listing[i], str, true);
//            }
//         }
//      }
//#else
//      throw ::exception(todo);
#endif
   }


   void pane_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_iNewArea != m_iArea)
      {
         m_iArea = m_iNewArea;
         //string strWallpaper;
         /*
               switch(m_iArea)
               {
               case 0:
                  strWallpaper = pcontext->m_papexcontext->dir().standard_square_matter("windeskframe1_23.bmp");
                  break;
               case 1:
                  strWallpaper = pcontext->m_papexcontext->dir().standard_square_matter("windeskframe1_24.bmp");
                  break;
               case 2:
                  strWallpaper = pcontext->m_papexcontext->dir().standard_square_matter("windeskframe1_25.bmp");
                  break;
               case 3:on_create_on_crea
                  strWallpaper = pcontext->m_papexcontext->dir().standard_square_matter("windeskframe1_26.bmp");
                  break;
               default:
                  strWallpaper = pcontext->m_papexcontext->dir().standard_square_matter("windeskframe1_23.bmp");
                  break;
               }
               FIBITMAP * pfi;

               ::draw2d::memory_graphics pgraphics(this);

               pfi = psystem->imaging().LoadImageFile(strWallpaper);

/*               m_pimage->From((HDC)pgraphics->get_os_data(), pfi, true);

               */
         //set_need_redraw();
      }

      //m_pimage->to(pgraphics, 0, 0, rectangleClient->right, rectangleClient->bottom);

      ::userex::pane_tab_impact::_001OnDraw(pgraphics);

   }



   void pane_impact::set_display(i32 iDisplay)
   {
      m_iDisplay = iDisplay;
   }

   void pane_impact::on_message_right_button_up(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      auto pmouse = pmessage->m_union.m_pmouse;
      /*if(get_view_id() == ::bergedge::impact_winactionarea)
      {
         ::user::menu menu(this);
         menu.LoadXmlMenu("bergedge\\popup_winactionarea.xml");
         ::user::menu menuPopup(get_app(), menu.GetSubMenu(0));
         get_parent_frame()->set_active_view(this);
         menuPopup.track_popup_menu(0, pmouse->m_point.x, pmouse->m_point.y, get_parent_frame());
      }*/
   }

   void pane_impact::OnFileManagerOpenContextMenu(::filemanager::data * pdata)
   {

      __UNREFERENCED_PARAMETER(pdata);

      //if(get_view_id() == ::bergedge::impact_winactionarea)
      //{

      //   track_popup_xml_matter_menu("bergedge/popup_winactionarea.xml", 0);

      //}





   }

   /*void pane_impact::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, ::file::item & item)
   {
   }
   */
   void pane_impact::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::file::item_array & itema)
   {
      __UNREFERENCED_PARAMETER(pdata);
      m_itema = itema;
      //set_current_tab_by_id(::bergedge::impact_properties);
   }



   void pane_impact::_001OnProperties(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
//      if(get_view_id() == ::bergedge::impact_winactionarea)
//      {
//
//#ifndef _UWP
//         ::aura::shell_launcher launcher(nullptr, nullptr, "control.exe", "desk.cpl", nullptr, SW_SHOWNORMAL);
//
//         launcher.execute();
//#else
//
//         throw ::exception(todo);
//
//#endif
//
//      }
   }


   void pane_impact::_001InitializeFormPreData(::user::form * pform)
   {

      auto pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::e_control_type_check_box);
      pinteraction->m_atom = "save_display_bandwidth";
      pinteraction->set_ddx_dbflags("ca2.savings", ::e_resource_display_bandwidth);
      //pform->_001AddControl(pinteraction);

      pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::e_control_type_check_box);
      pinteraction->m_atom = "save_processing";
      pinteraction->set_ddx_dbflags("ca2.savings", ::e_resource_processing);
      //pform->_001AddControl(pinteraction);

      pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::e_control_type_check_box);
      pinteraction->m_atom = "save_memory";
      pinteraction->set_ddx_dbflags("ca2.savings", ::e_resource_memory);
      //pform->_001AddControl(pinteraction);

      pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::e_control_type_check_box);
      pinteraction->m_atom = "enable_wallpaper";
      pinteraction->set_ddx_dbflags("ca2.bergedge", 0);
      //pform->_001AddControl(pinteraction);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(pevent);

   }


} // namespace bergedge
