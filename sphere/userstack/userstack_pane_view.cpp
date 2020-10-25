#include "framework.h"


namespace userstack
{


   pane_view::pane_view(::layered * pobjectContext) :
      ::object(pobject),
      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {

      m_iNewArea        = 0;
      m_iArea           = -1;
      m_pimpactdataOld    = nullptr;

      m_pimpactdata       = nullptr;
      m_pimpactdataOld    = nullptr;

      m_iDisplay        = -1;
      m_ppropform       = nullptr;
      //m_dataid          = "ca2::bergedge::pane_view";

      get_data()->m_matchanyRestore.add(new ::aura::match::prefix("app:"));

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


   void pane_view::_001OnCreate(::message::message * pmessage)
   {

      if(pmessage->previous())
         return;

      __pointer(frame) pframe =  (GetParentFrame());
      pframe->m_ppaneview = this;


      Application.m_ppaneview = this;



      add_tab("menu", CONTEXT_MENU_IMPACT);

      for(i32 i = 0; i < Application.m_varTopicQuery["app"].stra().get_count(); i++)
      {

         string strId = Application.m_varTopicQuery["app"].stra()[i];

         if(i == 0 && strId == "app/sphere/userstack")
            continue;

         add_tab(strId, "app:" + strId);

         set_cur_tab_by_id("app:" + Application.m_varTopicQuery["app"].stra()[i]);

      }

      for (i32 i = 0; i < Application.m_varTopicQuery["app/sphere/userstack"]["tab"].stra().get_count(); i++)
      {

         set_cur_tab_by_id("app:" + Application.m_varTopicQuery["app/sphere/userstack"]["tab"].stra()[i]);

      }

   }


   void pane_view::on_apply(::action * paction)
   {

      ::user::tab_view::on_apply(paction);
      
   }


   void pane_view::on_change_cur_sel()
   {
      ::userex::pane_tab_view::on_change_cur_sel();
//      __pointer(frame) pframe =  (GetParentFrame());
      string strId = get_view_id();
      if(::str::begins_eat(strId, "app:"))
      {

         __pointer(::aura::application) pappTab;

         if(Session.appptra().lookup("application:" + strId, pappTab))
         {
            Session.m_pappCurrent = pappTab;
            //Session.m_pappCurrent = pappTab;
         }
         /*            __pointer(::simple_frame_window) pframeApp = dynamic_cast < __pointer(::simple_frame_window) > (m_pimpactdata->m_puserinteraction);
                  if(pframeApp != nullptr)
                  {
                     pframeApp->display(display_full_screen);
                  }*/
      }
      //   else if(get_view_id() == CONTEXT_MENU_IMPACT)
      //   {
      //      /*bergedge::menu_view * pview = dynamic_cast < bergedge::menu_view *  > (get_view());
      //      __pointer(::filemanager::document) pdocument = (pview->get_document());
      //      pdocument->FileManagerBrowse(Context.dir().appdata() / "bergedge\\menu"), ::source_system);*/
      //   }
      //   else if(get_view_id() ==CONFIGURATION_IMPACT)
      //   {
      ///*      __pointer(::user::interaction) pinteraction = m_pformOptions->ve_display_bandwidth");
      //      matter * pcheck = dynamic_cast < matter * > (puie);
      //      if(Session.savings().save().has(::ca2::save_display_bandwidth))
      //      {
      //         pcheck->_001SetCheck(check_checked, false);
      //      }
      //      else
      //      {
      //         pcheck->_001SetCheck(check_unchecked, false);
      //      }*/
      //   }
      //   else if(get_view_id() == ::bergedge::impact_winactionarea)
      //   {
      //      string strDirName;
      //      strDirName.Format("desktop-%d", m_iDisplay);
      //      string strDir = Context.dir().userfolder(strDirName);
      //      if(m_iDisplay <= 0)
      //      {
      //         check_desktop_dir(strDir);
      //      }
      //      __pointer(::filemanager::document) pdocument =  (m_pimpactdata->m_pdocument);
      //      pdocument->FileManagerBrowse(strDir, ::source_system);
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

   bool pane_view::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }


   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      string strId = pimpactdata->m_id;

      if(::str::begins_eat(strId, "app:"))
      {

         __pointer(::aura::application) pappTab;

         if(!Session.appptra().lookup("application:" + strId, pappTab))
         {

            application_bias * papplicationbias = new application_bias;
            papplicationbias->m_puserinteractionParent = pimpactdata->m_pplaceholder;

            __pointer(::create) pcreate(e_create);
            pcreate->m_papplicationbias = papplicationbias;
            pcreate->m_pcommandline->_001ParseCommandFork(strId);


            string str;

            if(Application.has_property(strId))
            {

               pcreate->m_pcommandline->m_varQuery.propset().merge(Application.m_varTopicQuery[(const char *) strId].propset());

               if(Application.m_varTopicQuery[(const char *) strId].has_property("file"))
               {

                  pcreate->m_pcommandline->m_varFile = Application.m_varTopicQuery[(const char *) strId]["file"];

               }

            }

            str = __str((iptr) pcreate->m_papplicationbias->m_puserinteractionParent);

            pcreate->m_pcommandline->m_eventReady.ResetEvent();

            Session.on_request(pcreate);

            pcreate->m_pcommandline->m_eventReady.wait();

         }

         __pointer(::aura::application) pappCurrent = Session.m_pappCurrent;

         Application.appptra_add(pappCurrent);

         string strTypeId = typeid(*pappCurrent.m_p).name();

         string strIcon = Sess(pappCurrent).dir().matter("mainframe/icon48.png");

         ::user::tab_pane * ppane = (::user::tab_pane *) get_pane_by_id(pimpactdata->m_id);

         pappCurrent = Session.m_pappCurrent;

         if(Sess(pappCurrent).file().exists(strIcon))
         {

/*            ppane->m_pimage->create(this);

/*            ppane->m_pimage = load_image(strIcon);

         }
         else
         {

            ppane->set_title(pimpactdata->m_id);

         }

         on_layout(::draw2d::graphics_pointer & pgraphics);

      }

      ::userex::pane_tab_view::on_create_impact(pimpactdata);

   }



   void pane_view::_001OnMenuMessage(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      set_cur_tab_by_id(m_pimpactdataOld->m_id);
   }

   void pane_view::install_message_routing(::channel * pchannel)
   {
      ::userex::pane_tab_view::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &pane_view::_001OnCreate);
      MESSAGE_LINK(WM_USER + 1122, this, this, &pane_view::_001OnMenuMessage);
      MESSAGE_LINK(WM_RBUTTONUP, pchannel, this, &pane_view::_001OnRButtonUp);
      connect_command("properties", &pane_view::_001OnProperties);
   }

   void pane_view::rotate()
   {
   }

   /*void pane_view::OnFileManagerOpenFile(
         ::filemanager::data * pdata,
         ::file::item_array & itema)
   {
      if(itema.get_size() > 0)
      {
         i32 i = (i32) ::ShellExecuteW(
            GetTopLevel()->get_handle(),
            nullptr,
            L"\"" + ::str::international::utf8_to_unicode(itema[0].m_strPath) + L"\"",
            nullptr,
            L"\"" + ::str::international::utf8_to_unicode(Context.dir().name(itema[0].m_strPath)) + L"\"",
            SW_SHOWNORMAL);
         string str;
         str.Format("%d", i);
         //System.message_box(str);
         if(i == ERROR_FILE_NOT_FOUND)
         {
         }
      }
      //GetParentFrame()->hide();
   }*/

   void pane_view::check_menu_dir(const ::file::path & psz)
   {

      ::file::listing straPath(get_context_application());

      straPath.rls(Context.dir().commonprograms());

      for(i32 i = 0; i < straPath.get_size(); i++)
      {

         ::file::path str = psz/straPath[i].relative();

         Context.dir().mk(str.folder());

         Context.file().copy(str, straPath[i], true);

      }

      straPath.clear_results();

      straPath.rls(Context.dir().userprograms(nullptr));

      for(i32 i = 0; i < straPath.get_size(); i++)

      {
         ::file::path str = psz / straPath[i].relative();

         Context.dir().mk(str.folder());

         Context.file().copy(str, straPath[i], true);

      }

   }


   void pane_view::check_3click_dir(const ::file::path & psz)
   {

      if(Context.dir().is(psz))
      {

         return;

      }

      Context.dir().mk(psz);

      string strDir(psz);

      POSITION pos = System.m_mapAppLibrary.get_start_position();

      string strApp;

      string strLibrary;

      while(pos != nullptr)
      {

         System.m_mapAppLibrary.get_next_assoc(pos, strApp, strLibrary);

         if(::str::begins_eat(strApp, "application:"))
         {

            Context.file().put_contents(strDir / strApp + ".ca2", "ca2prompt\r\n"+ strApp);

         }

      }

      //Context.file().put_contents(Context.dir().path(strDir, "veriwell Musical Player.ca2"), "ca2prompt\r\nmplite");
      /*      string_array straPath;
            string_array straRelative;
            straPath.remove_all();
            Context.dir().rls(Context.dir().userquicklaunch(), &straPath, nullptr, &straRelative);
            for(i32 i = 0; i < straPath.get_size(); i++)
            {
               string str = Context.dir().path(psz, straRelative[i]);
               Context.dir().mk(Context.dir().name(str));
               ::CopyFile(straPath[i], str, TRUE);
            }*/
   }


   void pane_view::check_desktop_dir(const ::file::path & psz)
   {

#ifdef WINDOWS_DESKTOP

      ::file::listing listing(get_context_application());

//      wchar_t buf[4096];
//      __memset(buf, 0, sizeof(buf));
//      SHGetSpecialFolderPath(
//      nullptr,
//      buf,
//      CSIDL_COMMON_DESKTOPDIRECTORY,
//      FALSE);
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
//               Context.dir().mk(str.folder());
//
//               ::CopyFileW(wstring(listing[i]), wstring(str), TRUE);
//
//            }
//         }
//      }
//      __memset(buf, 0, sizeof(buf));
//      SHGetSpecialFolderPath(
//      nullptr,
//      buf,
//      CSIDL_DESKTOPDIRECTORY,
//      FALSE);
//      if(strlen(buf) > 0)
//      {
//         if(strlen(buf) > 0)
//         {
//            listing.clear_results();
//            listing.rls(buf);
//            for(i32 i = 0; i < listing.get_size(); i++)
//            {
//               ::file::path str = psz / listing[i].relative();
//               Context.dir().mk(listing[i].folder());
//               ::CopyFile(listing[i], str, TRUE);
//            }
//         }
//      }
//#else
//      __throw(todo());
#endif
   }


   void pane_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_iNewArea != m_iArea)
      {
         m_iArea = m_iNewArea;
         //string strWallpaper;
         /*
               switch(m_iArea)
               {
               case 0:
                  strWallpaper = Context.dir().standard_square_matter("windeskframe1_23.bmp");
                  break;
               case 1:
                  strWallpaper = Context.dir().standard_square_matter("windeskframe1_24.bmp");
                  break;
               case 2:
                  strWallpaper = Context.dir().standard_square_matter("windeskframe1_25.bmp");
                  break;
               case 3:on_create_on_crea
                  strWallpaper = Context.dir().standard_square_matter("windeskframe1_26.bmp");
                  break;
               default:
                  strWallpaper = Context.dir().standard_square_matter("windeskframe1_23.bmp");
                  break;
               }
               FIBITMAP * pfi;

               ::draw2d::memory_graphics pgraphics(this);

               pfi = System.imaging().LoadImageFile(strWallpaper);

/*               m_pimage->From((HDC)pgraphics->get_os_data(), pfi, true);

               */
         //set_need_redraw();
      }

      //m_pimage->to(pgraphics, 0, 0, rectClient->right, rectClient->bottom);

      ::userex::pane_tab_view::_001OnDraw(pgraphics);

   }



   void pane_view::set_display(i32 iDisplay)
   {
      m_iDisplay = iDisplay;
   }

   void pane_view::_001OnRButtonUp(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      SCAST_PTR(::message::mouse, pmouse, pmessage);
      /*if(get_view_id() == ::bergedge::impact_winactionarea)
      {
         ::user::menu menu(get_object());
         menu.LoadXmlMenu("bergedge\\popup_winactionarea.xml");
         ::user::menu menuPopup(get_context_application(), menu.GetSubMenu(0));
         GetParentFrame()->SetActiveView(this);
         menuPopup.track_popup_menu(0, pmouse->m_point.x, pmouse->m_point.y, GetParentFrame());
      }*/
   }

   void pane_view::OnFileManagerOpenContextMenu(::filemanager::data * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

      //if(get_view_id() == ::bergedge::impact_winactionarea)
      //{

      //   track_popup_xml_matter_menu("bergedge/popup_winactionarea.xml", 0);

      //}





   }

   /*void pane_view::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, ::file::item & item)
   {
   }
   */
   void pane_view::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_itema = itema;
      //set_cur_tab_by_id(::bergedge::impact_properties);
   }



   void pane_view::_001OnProperties(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      if(get_view_id() == ::bergedge::impact_winactionarea)
//      {
//
//#ifndef _UWP
//         ::aura::shell_launcher launcher(nullptr, nullptr, "control.exe", "desk.cpl", nullptr, SW_SHOWNORMAL);
//
//         launcher.execute();
//#else
//
//         __throw(todo());
//
//#endif
//
//      }
   }


   void pane_view::_001InitializeFormPreData(::user::form * pform)
   {

      auto pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::control_type_check_box);
      pinteraction->m_id = "save_display_bandwidth";
      pinteraction->set_ddx_dbflags("ca2.savings", ::e_resource_display_bandwidth);
      //pform->_001AddControl(pinteraction);

      pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::control_type_check_box);
      pinteraction->m_id = "save_processing";
      pinteraction->set_ddx_dbflags("ca2.savings", ::e_resource_processing);
      //pform->_001AddControl(pinteraction);

      pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::control_type_check_box);
      pinteraction->m_id = "save_memory";
      pinteraction->set_ddx_dbflags("ca2.savings", ::e_resource_memory);
      //pform->_001AddControl(pinteraction);

      pinteraction = pform->new_form_control();;
      pinteraction->m_bTransparent = true;
      pinteraction->set_control_type(user::control_type_check_box);
      pinteraction->m_id = "enable_wallpaper";
      pinteraction->set_ddx_dbflags("ca2.bergedge", 0);
      //pform->_001AddControl(pinteraction);

   }


   void pane_view::on_control_event(::user::control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


} // namespace bergedge
