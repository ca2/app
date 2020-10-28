#include "framework.h"
#include "apex/const/id.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"



#if defined(APPLE_IOS)

#include "apex/node/ios/interaction_impl.h"

#endif


#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)


namespace PLATFORM_NAMESPACE
{


   CLASS_DECL_APEX ::user::interaction * create_host_window();


} // namespace PLATFORM_NAMESPACE


#endif


#ifdef CUBE
extern "C"
::apex::application * cube_get_app();
#endif

void defer_term_ui();


CLASS_DECL_ACME bool is_verbose();


int_bool point_is_window_origin(POINT ptHitTest, oswindow oswindowExclude, int iMargin);

#ifdef _UWP

#include "apex/os/uwp/_uwp.h"

#elif defined(LINUX)

void x11_on_start_session();

#endif


namespace apex
{


   session::session()
   {

      m_bSimpleMessageLoop = false;
      m_bMessageThread = true;
      m_iEdge = -1;
      m_paurasession = nullptr;
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pcoresession = nullptr;


      //create_factory < ::user::user >();
      create_factory < ::apex::session, ::apex::session >();

      //m_strAppId                    = "core_session";
      //m_strAppName                  = "core_session";
      //m_strBaseSupportId            = "core_session";
      //m_strInstallToken             = "core_session";

      //m_puiLastUserInputPopup = nullptr;

      //m_pdocs = create_session_docs();

      //m_bLicense				               = false;

      //m_bLicense           = false;
      //m_eexclusiveinstance = ExclusiveInstanceNone;

   }


   session::~session()
   {

      output_debug_string("apex::session::~session()");

   }


   ::estatus session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      m_bSystemSynchronizedScreen      = true;

      set_context_session(this);

      set_context_object(this);

      set_context(this);

      if (get_context_system() != nullptr)
      {

         m_bSystemSynchronizedCursor   = get_context_system()->m_bSystemSynchronizedCursor;

         m_bSystemSynchronizedScreen   = get_context_system()->m_bSystemSynchronizedScreen;

      }

      m_pappCurrent                    = nullptr;

      m_iMainMonitor                   = -1;

      m_bZipIsDir2                     = true;

      m_iEdge                          = 0;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;

      return ::success;

   }


   void session::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {


   }


   string session::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   bool session::is_session() const
   {

      return true;

   }

   
   void session::enum_display_monitors()
   {


   }
   

   index session::get_main_monitor(RECT* prect)
   {

      return -1;

   }


   ::count session::get_monitor_count()
   {

      return -1;

   }

   
   bool  session::get_monitor_rect(index iMonitor, RECT* prect)
   {

      return false;

   }

   
   ::count session::get_desk_monitor_count()
   {

      return -1;

   }


   bool  session::get_desk_monitor_rect(index iMonitor, RECT* prect)
   {

      return false;

   }


   index session::get_main_wkspace(RECT* prect)
   {

      return -1;

   }


   ::count session::get_wkspace_count()
   {

      return -1;

   }


   bool  session::get_wkspace_rect(index iWkspace, RECT* prect)
   {

      return false;

   }

   
   ::count session::get_desk_wkspace_count()
   {

      return -1;

   }
  
   
   bool  session::get_desk_wkspace_rect(index iWkspace, RECT* prect)
   {

      return false;

   }


   bool session::set_main_monitor(index iMonitor)
   {

      return false;

   }
   

   bool session::set_main_wkspace(index iWkspace)
   {

      return false;

   }


   bool session::wkspace_to_monitor(RECT* prect, index iMonitor, index iWkspace)
   {

      return false;

   }


   bool session::monitor_to_wkspace(RECT* prect, index iWkspace, index iMonitor)
   {

      return false;

   }


   bool session::wkspace_to_monitor(RECT* prect)
   {

      return false;

   }


   bool session::monitor_to_wkspace(RECT* prect)
   {

      return false;

   }


   void session::get_monitor(rect_array& rectaMonitor, rect_array& rectaIntersect, const ::rect& rect)
   {


   }


   COLORREF session::get_default_color(u64 ui)
   {

      switch (ui)
      {
      case COLOR_3DFACE:
         return ARGB(127, 192, 192, 184);
      case COLOR_WINDOW:
         return ARGB(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return ARGB(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return ARGB(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return ARGB(127, 90, 90, 80);
      default:
         break;
      }

      return ARGB(127, 0, 0, 0);

   }






   size session::get_window_minimum_size()
   {

      return size(300, 300);

   }


   ::estatus session::init_thread()
   {

      auto estatus = process_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init_session();

      if (!estatus)
      {

         return estatus;

      }

      // // now there is attempt here
      //estatus = defer_initialize_host_window();

      //if(!estatus)
      //{

      //   __throw(::exception::exception(estatus));

      //}


      INFO(".1");

      return true;

      return estatus;

   }


   void session::term_thread()
   {

      try
      {

         term_session();

      }
      catch (...)
      {

      }

      try
      {

         process_term();

      }
      catch(...)
      {

      }

      ::thread::term_thread();

   }


   ::estatus session::process_init()
   {

      INFO("apex::session::process_init");

      auto estatus = ::context::initialize_context();

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_puserstrcontext);

      if (!estatus)
      {

         INFO("apex::str_context Failed to Allocate!!");

         return estatus;

      }

      INFO("apex::str_context Succeeded to Allocate!!");

      INFO("apex::session::process_init success");

      return ::success;

   }


   ::estatus session::init_session()
   {

      auto estatus = init1();

      if (!estatus)
      {

         message_box("::apex::session::init1 Failed");

         return estatus;

      }

      estatus = init2();

      if (!estatus)
      {

         return estatus;

      }

      estatus = init();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void session::term_session()
   {

      try
      {

         term2();

      }
      catch (...)
      {

      }

      try
      {

         term1();

      }
      catch (...)
      {

      }

      try
      {

         term();

      }
      catch (...)
      {

      }



   }

   //::estatus session::init()
   //{



   //   return true;

   //}


   //void session::term()
   //{

   //   m_paccount.release();






   //}


   void session::term2()
   {

#ifdef WINDOWS_DESKTOP

      __release(m_puiSession);

#endif

   }


   void session::term1()
   {


   }


   void session::process_term()
   {

      System.session_remove(m_iEdge);

   }


//   bool session::defer_create_session_frame_window()
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      if (m_puiSession)
//      {
//
//         return true;
//
//      }
//
//      ::estatus estatus = __compose(m_puiSession, ::move(create_system_message_window(this)));
//
//      if (!estatus)
//      {
//
//         return false;
//
//      }
//
//#endif
//
//      return true;
//
//   }


   bool session::on_get_thread_name(string& strThreadName)
   {

      if (get_context_system()->is_console_app())
      {

         return false;

      }

      return ::apex::context_thread::on_get_thread_name(strThreadName);

   }


   void session::on_request(::create * pcreate)
   {

      // it was here
      //auto estatus = defer_initialize_host_window();
      //
      //if(!estatus)
      //{
      //
      //   __throw(::exception::exception(estatus));
      //
      //}

      if (pcreate->m_ecommand == command_protocol)
      {

         m_pappCurrent->do_request(pcreate);

         return;

      }

      TRACE("::apex::session::on_request(__pointer(::create)) " + string(type_name()));

      INFO("::apex::session::on_request(__pointer(::create)) %s ", __c_str(THIS_FRIENDLY_NAME()));

      if (pcreate->m_strAppId.has_char())
      {

         INFO("m_strAppId = " + pcreate->m_strAppId);

         auto papp = start_application(pcreate->m_strAppId, pcreate, m_strLocale, m_strSchema);

         if (!papp)
         {

            finish(get_context());

         }

         return;

      }

      INFO("m_strAppId Is Empty!!");

      string strApp = pcreate->m_pcommandline->m_strApp;

      if (strApp == "app/sphere/userstack")
      {

         start_application("app/sphere/userstack", pcreate, m_strLocale, m_strSchema);

      }

      m_varCurrentViewFile = pcreate->m_pcommandline->m_varFile;


      //string strApp;

      //if ((pcreate->m_pcommandline->m_varQuery["app"].array_get_count() > 1
      //      || pcreate->m_pcommandline->m_varQuery["show_platform"] == 1 || m_varTopicQuery["show_platform"] == 1)
      //      && (!(bool)pcreate->m_pcommandline->m_varQuery.has_property("client_only") && !(bool)has_property("client_only"))
      //      && (!pcreate->m_pcommandline->m_varQuery.has_property("client_only") && !has_property("client_only")))
      //{
      //   m_bShowPlatform = true;
      //}

      bool bCreate = true;
      if (pcreate->m_pcommandline->m_strApp.is_empty())
      {
         if (!pcreate->m_pcommandline->m_varFile.is_empty())
         {
            if (!open_by_file_extension(pcreate))
            {
               if (m_pappCurrent != nullptr)
               {
                  App(m_pappCurrent).request({pcreate});
               }
            }
         }
         else if (m_bShowPlatform)
         {
            //create_bergedge(pcreate);
            //if(get_document() != nullptr && get_document()->get_typed_view < ::bergedge::view >() != nullptr)
            //{
            //   __pointer(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
            //   if(pframe != nullptr)
            //   {
            //      pframe->display(display_normal);
            //      pframe->InitialFramePosition();
            //   }
            //}
         }
         if (pcreate->m_pcommandline->m_varQuery["app"].array_get_count() <= 0)
         {
            bCreate = false;
         }
      }
      if (bCreate)
      {
         if (pcreate->m_pcommandline->m_strApp == "bergedge")
         {
            if (pcreate->m_pcommandline->m_varQuery.has_property("session_start"))
            {
               strApp = pcreate->m_pcommandline->m_varQuery["session_start"];
            }
            else
            {
               strApp = "bergedge";
            }
         }
         else
         {
            strApp = pcreate->m_pcommandline->m_strApp;
         }


         if (pcreate->m_pcommandline->m_varQuery["app"].stra().find_first_ci(strApp) < 0)
         {

            pcreate->m_pcommandline->m_varQuery["app"].stra().insert_at(0, strApp);

         }

         for (i32 i = 0; i < pcreate->m_pcommandline->m_varQuery["app"].stra().get_count(); i++)
         {

            strApp = pcreate->m_pcommandline->m_varQuery["app"].stra()[i];

            if (strApp.is_empty() || strApp == "bergedge")
            {

               return;

            }

            if (strApp == "session")
            {

               continue;

            }

            ::apex::application * papp = application_get(strApp, true, true, pcreate);

            if (papp == nullptr)
            {

               if(System.has_property("install")
                     || System.has_property("uninstall"))
               {

                  ::multithreading::finish(&System);

               }
               else
               {

                  message_box("Could not create requested application: \"" + strApp + "\"");

                  ::count c = System.value("app").array_get_count();

                  if (c == 1 && System.value("app").at(0) == strApp)
                  {

                     ::multithreading::finish(&System);

                  }

               }

               return;

            }

            pcreate->m_pcommandline->m_eventReady.ResetEvent();

            if (strApp != "bergedge")
            {

               if(!papp->on_start_application())
               {

                  TRACE("One or more errors occurred during on_start_application execution.");

               }

               //if (System.is_true("install"))
               if (is_true("install"))
               {

                  papp->do_install();

                  System.finalize();

               }
               else
               {

                  if (!papp->is_system() && !papp->is_session())
                  {

                     System.merge_accumulated_on_open_file(pcreate);

                  }

                  papp->request({pcreate});

               }

               m_pappCurrent = papp;

            }

         }

      }

   }


   //__pointer(::user::menu_interaction) session::create_menu_button(::user::style_pointer & pstyle,::user::menu_item * pitem)
   //{

   //   __throw(interface_only_exception());

   //   return nullptr;

   //}


   bool session::open_by_file_extension(const char * pszPathName, ::create * pcreate)
   {

      auto pcreateNew = __create_new < ::create >();

      pcreateNew->m_pcommandline->m_varFile = pszPathName;

      pcreateNew->m_puserinteractionParent = pcreate->m_puserinteractionParent;

      return open_by_file_extension(pcreateNew);

      //return Application.platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      //return Application.platform_open_by_file_extension(m_iEdge, pcc);

      string strId;

      string strOriginalPathName(pcreate->m_pcommandline->m_varFile);

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if (iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if (::str::ends_ci(strPathName, ".ca2"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreate->m_pcommandline->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.extension();

         string_array straApp;

         __throw(todo("filehandler"));

         //System.filehandler().get_extension_app(straApp, strExtension);

         //if (straApp.get_count() == 1)
         //{

         //   strId = straApp[0];

         //}
         //else
         //{

         //   strId = "app/sphere/default_file_handler";

         //}

      }

      ::apex::application* papp = application_get(strId, true, true, pcreate);

      if (papp == nullptr)
      {

         return false;

      }

      papp->do_request(pcreate);

      return true;

   }


   ::apex::application * session::application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate)
   {

      __pointer(::apex::application) papp;

      if (m_applicationa.lookup(pszAppId, papp))
      {

         return papp;

      }
      else
      {

         if (!bCreate)
         {

            return nullptr;

         }

         papp = nullptr;

         try
         {

            papp = create_application(pszAppId, bSynch, pcreate);

         }
         catch (::exception_pointer pe)
         {

            // apex::session, axis::session and ::base::session, could get more specialized handling in apex::application (apex::system)
            // Thank you Mummi (em Santos, cuidando do Lucinho e ajudando um monte a Carô e o Lúcio e Eu 2019-01-15) !! Thank you God!! <3tbs

            handle_exception(pe);

            //if (!Sys(this).on_run_exception(esp))
            //{

            //   if (!App(this).on_run_exception(esp))
            //   {

            //      papp = nullptr;

            //   }

            //}

            //papp = nullptr;

         }
         catch (...)
         {

            //papp = nullptr;

         }

         if (!papp)
         {

            return nullptr;

         }

         app_add(papp);

         return papp;

      }

   }




   bool session::is_licensed(const char * pszAppId, bool bInteractive)
   {

      if (has_property("install"))
      {

         return true;

      }

      if (has_property("uninstall"))
      {

         return true;

      }

      return false;

      //if(m_paccount.is_null())
      //{

      //   return false;

      //}

      //return m_paccount->is_licensed(pszAppId, bInteractive);

   }


   //::account::user * session::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   //{

   //   if(m_paccount.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return m_paccount->get_user(pathUrl, bFetch, bInteractive);

   //}


//   ::account::user * session::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->interactive_get_user();
//
//   }
//
//
//   ::account::user * session::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->noninteractive_get_user(pathUrl);
//
//   }


   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      throw 0;

      return false;

      //return account()->get_auth(pszForm, strUsername, strPassword);

   }


   //void session::defer_initialize_user_presence()
   //{


   //}

   //void session::translate_os_key_message(::user::key * pkey)
   //{

   //}


   //bool session::set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor)
   //{

   //   m_ecursor = cursor_draw2d;

   //   m_pcursor = pcursor;

   //   if (pcursor != nullptr)
   //   {

   //      if (!pcursor->set_current(pinteraction, this))
   //      {

   //         return false;

   //      }

   //   }
   //   else
   //   {

   //      if (!::draw2d::cursor::reset(pinteraction, this))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //bool session::set_cursor(::user::interaction * pinteraction, e_cursor ecursor)
   //{

   //   m_ecursor = ecursor;

   //   ::draw2d::cursor * pcursor = get_cursor();

   //   if (pcursor != nullptr)
   //   {

   //      if (!pcursor->set_current(pinteraction, this))
   //      {

   //         return false;

   //      }

   //   }
   //   else
   //   {

   //      if (!::draw2d::cursor::reset(pinteraction, this))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //bool session::set_default_cursor(::user::interaction * pinteraction, e_cursor ecursor)
   //{

   //   if (ecursor == cursor_default)
   //   {

   //      m_ecursorDefault = cursor_arrow;

   //   }
   //   else
   //   {

   //      m_ecursorDefault = ecursor;

   //   }

   //   return true;

   //}


   //bool session::on_create_frame_window()
   //{

   //   defer_create_session_frame_window();

   //   return true;

   //}


  void session::get_cursor_pos(LPPOINT ppoint)
  {


//   __throw(todo("aura"));
//     if (m_bSystemSynchronizedCursor)
//     {
//
//        POINT point;
//
//        ::GetCursorPos(&point);
//
//        m_pointCursor = point;
//
//     }

     if (ppoint != nullptr)
     {

        *ppoint = m_pointCursor;

     }

  }

//
//   oswindow session::get_capture()
//   {
//
//      return ::get_capture();
//
//   }
//
//
   void session::set_cursor_pos(const ::point & point)
   {

#ifdef WINDOWS_DESKTOP

      ::SetCursorPos(point.x, point.y);

#endif

   }
//
//
//   bool session::ReleaseCapture()
//   {
//
//      // oswindow oswindowCapture = ::get_capture();
//
//      // if (oswindowCapture == nullptr)
//      // {
//
//      //    return false;
//
//      // }
//
//      ::release_capture();
//
//      m_puiCapture = nullptr;
//
//      return true;
//
//
//   }
//

   //__pointer(::user::interaction) session::GetCapture()
   //{

   //   oswindow oswindowCapture = ::get_capture();

   //   if (oswindowCapture == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   __pointer(::user::interaction) pinteraction = System.ui_from_handle(oswindowCapture);

   //   if (pinteraction.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->GetCapture();

   //}


   //::user::copydesk& session::copydesk()
   //{

   //   if (!m_pcopydesk)
   //   {

   //      __compose(m_pcopydesk);

   //   }

   //   return *m_pcopydesk;

   //}



#define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;

   index session::_get_best_zoneing(edisplay * pedisplay, ::rect * prect, const ::rect & rectRequest, bool bPreserveSize)
   {

      ::rect rect(rectRequest);

      ::rect rectWkspace;

      index iBestWkspace = get_best_wkspace(&rectWkspace, rect);

      edisplay edisplay;

      ::edisplay edisplayPrevious = *pedisplay;

      double dMargin = System.m_dpi;

      if (ZONEING_COMPARE::is_equal(rect.top, rectWkspace.top, dMargin, !(edisplayPrevious & display_top)))
      {

         edisplay |= display_top;

         if (bPreserveSize)
         {

            rect.move_top_to(rectWkspace.top);

         }
         else
         {

            rect.top = rectWkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rect.bottom, rectWkspace.bottom, dMargin, !(edisplayPrevious & display_bottom)))
      {

         edisplay |= display_bottom;

         if (bPreserveSize)
         {

            rect.move_bottom_to(rectWkspace.bottom);

         }
         else
         {

            rect.bottom = rectWkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectRequest.left, rectWkspace.left, dMargin, !(edisplayPrevious & display_left)))
      {

         edisplay |= display_left;

         if (bPreserveSize)
         {

            rect.move_left_to(rectWkspace.left);

         }
         else
         {

            rect.left = rectWkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectRequest.right, rectWkspace.right, dMargin, !(edisplayPrevious & display_right)))
      {

         edisplay |= display_right;

         if (bPreserveSize)
         {

            rect.move_right_to(rectWkspace.right);

         }
         else
         {

            rect.right = rectWkspace.right;

         }

      }

      if (!(edisplay & display_top || edisplay & display_bottom)
         && is_different(edisplay & display_left, edisplay & display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.top, rect.top, rect.bottom, rectWkspace.bottom))
         {

            edisplay |= display_bottom;

            edisplay |= display_top;

            rect.bottom = rectWkspace.bottom;

            rect.top = rectWkspace.top;

         }

      }

      if (!(edisplay & display_left || edisplay & display_right)
         && is_different(edisplay & display_top, edisplay & display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.left, rect.left, rect.right, rectWkspace.right))
         {

            edisplay |= display_left;

            edisplay |= display_right;

            rect.left = rectWkspace.left;

            rect.right = rectWkspace.right;

         }

      }

      bool bLeftXorRight = is_different(edisplay & display_left, edisplay & display_right);

      bool bTopXorBottom = is_different(edisplay & display_top, edisplay & display_bottom);

      bool bTopAndBottom = edisplay & display_top && edisplay & display_bottom;

      bool bLeftAndRight = edisplay & display_left && edisplay & display_right;

      if (bLeftXorRight && bTopXorBottom)
      {

      }
      else if (bTopAndBottom && bLeftAndRight)
      {

         edisplay = display_zoomed;

      }
      else
      {

         if (bLeftXorRight && !bTopAndBottom)
         {

            edisplay = display_none;

         }

         if (bTopXorBottom && !bLeftAndRight)
         {

            edisplay = display_none;

         }

         if (bTopAndBottom)
         {

            edisplay -= display_top;

            edisplay -= display_bottom;

         }

         if (bLeftAndRight)
         {

            edisplay -= display_left;

            edisplay -= display_right;

         }

      }

      if (edisplay == display_none)
      {

         edisplay = display_normal;

      }

      if (is_docking_appearance(edisplay))
      {

         *prect = rect;

      }
      else if (edisplay == display_zoomed)
      {

         *prect = rectWkspace;

      }
      else
      {

         *prect = rectRequest;

      }

      if (pedisplay)
      {

         *pedisplay = edisplay;

      }

      //if (g_i_get_best_zoneing % 10 == 0)
      //{

      //   string strE("e");
      //   if (edisplay & display_left)
      //      strE += "L";
      //   if (edisplay & display_top)
      //      strE += "T";
      //   if (edisplay & display_right)
      //      strE += "R";
      //   if (edisplay & display_bottom)
      //      strE += "B";

      //   string strP("p");
      //   if (edisplayPrevious & display_left)
      //      strP += "L";
      //   if (edisplayPrevious & display_top)
      //      strP += "T";
      //   if (edisplayPrevious & display_right)
      //      strP += "R";
      //   if (edisplayPrevious & display_bottom)
      //      strP += "B";

      //   ::output_debug_string(
      //      "w" + ::str::from(rectWkspace.left) + ","
      //      + ::str::from(rectWkspace.top) + ","
      //      + ::str::from(rectWkspace.right) + ","
      //      + ::str::from(rectWkspace.bottom) + " " +
      //      "r" + ::str::from(prect->left) + ","
      //      + ::str::from(prect->top) + ","
      //      + ::str::from(prect->right) + ","
      //      + ::str::from(prect->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectWkspace.left,
      //   rectWkspace.top,
      //   rectWkspace.right,
      //   rectWkspace.bottom,
      //   (edisplay & display_left)?'L':' ',
      //   (edisplay & display_top) ? 'T':' ',
      //   (edisplay & display_right) ? 'R':' ',
      //   (edisplay & display_bottom) ? 'B':' ',
      //   (edisplayPrevious & display_left) ? 'L':' ',
      //   (edisplayPrevious & display_top) ? 'T':' ',
      //   (edisplayPrevious & display_right) ? 'R':' ',
      //   (edisplayPrevious & display_bottom) ? 'B':' ');

      return iBestWkspace;

   }


   index session::get_best_monitor(RECT * prect, const rect & rectParam, ::eactivation eactivation)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rect rectMatch;

      ::rect rect(rectParam);

      if (eactivation & activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = get_cursor_pos();

         rect.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rect, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rect))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prect != nullptr)
         {

            *prect = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(prect);

      return iMatchingMonitor;

   }


   index session::get_best_wkspace(::rect * prect, const rect & rectParam, ::eactivation eactivation)
   {

      index iMatchingWkspace = -1;

      i64 iBestArea = -1;

      ::rect rectMatch;

      ::rect rect(rectParam);

      if (eactivation & activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = get_cursor_pos();

         rect.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_wkspace_rect(iWkspace, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rect, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rect))
            {

               iMatchingWkspace = iWkspace;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingWkspace >= 0)
      {

         if(prect != nullptr)
         {

            *prect = rectMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_wkspace(prect);

      return iMatchingWkspace;

   }


   index session::get_good_iconify(RECT * prect, const rect & rectParam)
   {

      ::rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      prect->left = rectMonitor.left;

      prect->top = rectMonitor.top;

      prect->right = rectMonitor.left;

      prect->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }


   //index session::initial_frame_position(RECT * prect, const rect & rectParam, bool bMove, ::user::interaction * pinteraction)
   //{

   //   ::rect rectRestore(rectParam);

   //   ::rect rectMonitor;

   //   index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

   //   ::size sizeMin;

   //   if (pinteraction != nullptr)
   //   {

   //      sizeMin  = pinteraction->get_window_minimum_size();

   //   }
   //   else
   //   {

   //      sizeMin = get_window_minimum_size();

   //   }

   //   ::rect rectIntersect;

   //   if (bMove)
   //   {

   //      rect_array rectaMonitor;

   //      rect_array rectaIntersect;

   //      get_monitor(rectaMonitor, rectaIntersect, rectParam);

   //      rectaIntersect.get_box(rectIntersect);

   //   }
   //   else
   //   {

   //      rectIntersect.intersect(rectMonitor, &rectParam);

   //   }

   //   auto sizeMax = rectMonitor.size() * 0.9;

   //   if (rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy
   //      || rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy )
   //   {

   //      if (rectMonitor.width() / 7 + max(sizeMin.cx, rectMonitor.width() * 2 / 5) > rectMonitor.width()
   //            || rectMonitor.height() / 7 + max(sizeMin.cy, rectMonitor.height() * 2 / 5) > rectMonitor.width())
   //      {

   //         rectRestore = rectMonitor;

   //      }
   //      else
   //      {

   //         rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

   //         rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

   //         rectRestore.right = rectRestore.left + max(sizeMin.cx, rectMonitor.width() * 2 / 5);

   //         rectRestore.bottom = rectRestore.top + max(sizeMin.cy, rectMonitor.height() * 2 / 5);

   //         if (rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
   //         {

   //            rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right, 0);

   //         }

   //         if (rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
   //         {

   //            rectRestore.offset(0, rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

   //         }

   //      }

   //      *prect = rectRestore;

   //      return iMatchingMonitor;

   //   }
   //   else
   //   {

   //      if (!bMove)
   //      {

   //         *prect = rectIntersect;

   //      }

   //      return -1;

   //   }

   //}


   //index session::get_window_restore_1(RECT * prect, const rect & rectParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   //{

   //   ::rect rectRestore(rectParam);

   //   ::rect rectWkspace;

   //   ::size sizeMin;

   //   index iMatchingWkspace;

   //   ::size sizeBroad;

   //   ::size sizeCompact;

   //   if (pinteraction != nullptr)
   //   {

   //      sizeMin = pinteraction->get_window_minimum_size();

   //      iMatchingWkspace = pinteraction->calculate_broad_and_compact_restore(rectWkspace, sizeMin, rectParam);

   //      sizeBroad = pinteraction->m_sizeRestoreBroad;

   //      sizeCompact = pinteraction->m_sizeRestoreCompact;

   //   }
   //   else
   //   {

   //      sizeMin = get_window_minimum_size();

   //      iMatchingWkspace = get_best_wkspace(&rectWkspace, rectParam);

   //      sizeBroad = sizeMin.max(rectWkspace.size() * 4 / 5);

   //      sizeCompact = sizeMin.max(rectWkspace.size() * 2 / 5);

   //   }

   //   auto rectIntersect = rectWkspace & rectParam;

   //   auto rectTolerance(rectWkspace);

   //   auto sizeMax = rectWkspace.size() * 0.8;

   //   bool b1 = !rectTolerance.contains(rectRestore);
   //   bool b2 = rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy;
   //   bool b3 = rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy;
   //   bool b4 = (edisplayRestore == display_compact && rectRestore.size() != sizeCompact);
   //   bool b5 = (edisplayRestore == display_broad && rectRestore.size() != sizeBroad);
   //   bool b6 = (rectRestore.size() == sizeCompact || rectRestore.size() == sizeBroad);
   //   bool b66 = !(edisplayRestore == display_compact || edisplayRestore == display_broad);

   //   bool bNotHappyWithTheSizeAndOrPosition = b1 || b2 || b3 || b4 || b5 || (b6 && b66);

   //   if (bNotHappyWithTheSizeAndOrPosition)
   //   {

   //      if (edisplayRestore == display_broad || sizeCompact == rectRestore.size())
   //      {

   //         rectRestore.set_size(sizeBroad);

   //      }
   //      else
   //      {

   //         rectRestore.set_size(sizeCompact);

   //      }

   //      ::rect rectWkspaceBitSmaller(rectWkspace);

   //      rectWkspaceBitSmaller.deflate(5);

   //      if (!rectWkspaceBitSmaller.contains(rectRestore))
   //      {

   //         rectRestore.move_to(rectWkspace.origin() + rectWkspace.size() / 10);

   //      }

   //      *prect = rectRestore;

   //      return iMatchingWkspace;

   //   }
   //   else
   //   {

   //      return -1;

   //   }

   //}


   //index session::get_window_restore_2(RECT* prect, const rect& rectParam, ::user::interaction* pinteraction, edisplay edisplayRestore)
   //{

   //   ::rect rect(rectParam);

   //   index iBestWkspace = get_window_restore_1(prect, rect, pinteraction, edisplayRestore);

   //   bool bChangedSize = ::size(prect) != rectParam.size();

   //   if (iBestWkspace < 0 && !bChangedSize)
   //   {

   //      return -1;

   //   }

   //   ::rect rectWkspace;

   //   ::rect rectStart(prect);

   //   ::point pointLineStart(::top_left(prect));

   //   get_wkspace_rect(iBestWkspace, rectWkspace);

   //   if (rectStart > pinteraction->m_sizeRestoreCompact)
   //   {

   //      pointLineStart = rectWkspace.origin();

   //      pointLineStart.offset(49, 49);

   //      rect.move_to(pointLineStart);

   //   }

   //   if(::is_window(pinteraction->get_handle()))
   //   {

   //      do
   //      {

   //         if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
   //         {

   //            return iBestWkspace;

   //         }

   //         rect = *prect;

   //         if (rect > pinteraction->m_sizeRestoreCompact)
   //         {

   //            rect.offset(49, 0);

   //            if (!rectWkspace.contains(rect))
   //            {

   //               pointLineStart.offset(0, 49);

   //               rect.move_to(pointLineStart);

   //               if (!rectWkspace.contains(rect))
   //               {

   //                  break;

   //               }

   //            }

   //         }
   //         else
   //         {

   //            rect.offset(49, 49);

   //         }

   //         *prect = rect;

   //      }
   //      while (rectWkspace.contains(rect));

   //   }

   //   if (rect.size() >= pinteraction->m_sizeRestoreCompact)
   //   {

   //      pointLineStart = rectWkspace.origin();

   //      pointLineStart.offset(49, 49);

   //      rect.move_to(pointLineStart);

   //      *prect = rect;

   //      return iBestWkspace;

   //   }

   //   rect = rectStart;

   //   rect.set_size(pinteraction->m_sizeRestoreCompact);

   //   if(::is_window(pinteraction->get_handle()))
   //   {

   //      do
   //      {

   //         if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
   //         {

   //            return iBestWkspace;

   //         }

   //         rect = *prect;

   //         rect.offset(49, 49);

   //         *prect = rect;

   //      } while (rectWkspace.contains(rect));

   //   }

   //   pointLineStart = rectWkspace.origin();

   //   pointLineStart.offset(49, 49);

   //   rect.move_to(pointLineStart);

   //   if(::is_window(pinteraction->get_handle()))
   //   {

   //      do
   //      {

   //         if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
   //         {

   //            return iBestWkspace;

   //         }

   //         rect = *prect;

   //         rect.offset(49, 0);

   //         if (!rectWkspace.contains(rect))
   //         {

   //            pointLineStart.offset(0, 49);

   //            rect.move_to(pointLineStart);

   //            if (!rectWkspace.contains(rect))
   //            {

   //               break;

   //            }

   //         }

   //         *prect = rect;

   //      } while (rectWkspace.contains(rect));

   //   }

   //   pointLineStart = rectWkspace.origin();

   //   pointLineStart.offset(49, 49);

   //   rect.move_to(pointLineStart);

   //   *prect = rect;

   //   return iBestWkspace;

   //}


   //index session::get_good_move(RECT * prect, const rect & rectParam, ::user::interaction * pinteraction)
   //{

   //   index iMatchingMonitor = initial_frame_position(prect, rectParam, true, pinteraction);

   //   if (__memcmp(prect, &rectParam, sizeof(const rect &)))
   //   {

   //      return iMatchingMonitor;

   //   }
   //   else
   //   {

   //      return -1;

   //   }

   //}


   //index session::get_ui_wkspace(::user::interaction * pinteraction)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System.get_ui_wkspace(pinteraction);

   //   }
   //   else
   //   {

   //      ::rect rect;

   //      pinteraction->get_window_rect(rect);

   //      return get_best_wkspace(nullptr, rect);

   //   }

   //}


   bool session::is_key_pressed(::user::e_key ekey)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      bool bPressed = false;
      if (ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->lookup(::user::key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_command)
      {
         m_pmapKeyPressed->lookup(::user::key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lcommand, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rcommand, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_control)
      {
         m_pmapKeyPressed->lookup(::user::key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->lookup(::user::key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_ralt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->lookup(ekey, bPressed);

      }

ret:

      return bPressed;

   }


   void session::set_key_pressed(::user::e_key ekey, bool bPressed)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }


   ::user::interaction * session::get_session_window()
   {

#ifdef WINDOWS_DESKTOP

      return __user_interaction(m_puiSession);

#else

      return nullptr;

#endif

   }


   ::estatus session::init1()
   {

      auto estatus = __compose_new(m_pfs);

      if (!estatus)
      {

         m_result.add(estatus);

         return false;

      }

      // __throw(todo("interaction"));
      //if (System.m_bUser)
      //{

      //   bool bCreateSessionWindow = defer_create_session_frame_window();

      //   if (!bCreateSessionWindow)
      //   {

      //      WARN("Could not create session window");

      //   }

      //}

      //estatus = __compose_new(m_puserpresence);

      //if (!estatus)
      //{

      //   m_result.add(estatus);

      //   TRACE("Failed to create new User Presence");

      //   return false;

      //}

      if (!m_pifs)
      {

         estatus = __compose(m_pifs, __new(ifs("")));

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create ifs");

         }

      }

      if (!m_premotefs)
      {

         estatus = __compose(m_premotefs, __new(::fs::remote_native("")));

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create remotefs");

         }

      }

      //if (!m_pftpfs)
      //{

      //   auto pftpfs = __new(ftpfs);

      //   auto estatus = pftpfs->initialize_ftpfs(this, "");

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create ftpfs");

      //   }

      //   __compose(m_pftpfs, pftpfs);

      //}

      if (!m_pfsdata)
      {

         auto pset = __create_new<::fs::set>();

         auto plink = __create_new < ::fs::link>();

         plink->fill_os_user();

         pset->m_spafsdata.add(plink);

         pset->m_spafsdata.add(__create_new < ::fs::native>());

         estatus = __compose(m_pfsdata, pset);

         if (!estatus)
         {

            m_result.add(estatus);

            TRACE("Failed to create fsdata");

         }


      }

      INFO(".2");


      return true;

   }


   ::estatus session::defer_initialize_host_window(LPCRECT lpcrect)
   {

      return ::success;

   }


   ::estatus session::init2()
   {

      ::estatus estatus;

      INFO("apex::session::init2 .1");

      if (System.m_bUser)
      {

         //if (!m_paccount)
         //{

         //   estatus = __compose_new(m_paccount);

         //   if (!estatus)
         //   {

         //      FATAL("apex::session::init2 Failed to create account department");

         //      return false;

         //   }

         //}

         //if (!m_paccount->init_instance())
         //{

         //   return false;

         //}

         //if(System.m_bDraw2d)
         //{

         //   m_pfontCopyDesk = ::draw2d::point_font(FONT_SANS, 14.0);

         //}

      }

      //initialize_bergedge_application_interface();

      //SetRegistryKey("ca2core");

      if (!InitializeLocalDataCentral())
      {

         message_box("Could not initialize Local data central");

         return false;

      }

      return true;

   }


   ::estatus session::init()
   {

      ::estatus estatus = ::success;

      __pointer(::fs::set) pfsset = m_pfsdata;

      if (m_bIfs)
      {

         if (m_pfsdata.is_null())
         {

            __compose(m_pfsdata, __new(::fs::set));

         }

         pfsset = m_pfsdata;

         if (pfsset.is_null())
         {

            pfsset->m_spafsdata.add_unique(m_pifs);

            pfsset->m_spafsdata.add_unique(m_premotefs);

         }

         ::file::listing patha;

         m_pfsdata->root_ones(patha);

      }


      return estatus;

   }


   void session::term()
   {

      try
      {

         ::acme::del(m_pmapKeyPressed);

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

   }


   DWORD session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}


   bool session::on_create_frame_window()
   {

      return true;

   }


//   void session::translate_os_key_message(::user::key * pkey)
//   {
//
////      psession->keyboard().translate_os_key_message(pkey);
//
//   }


   void session::pre_translate_message(::message::message * pmessage)
   {

      if (::is_set(m_pappCurrent))
      {

         m_pappCurrent->pre_translate_message(pmessage);

      }

   }


   // ::user::style* session::get_user_style() const
   // {

   //    return m_puserstyle;

   // }


} // namespace apex








#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace apex
{






   //::estatus session::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::apex::session::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   void session::install_message_routing(::channel* pchannel)
   {

      ::thread::install_message_routing(pchannel);

   //   //apex::application::install_message_routing(pchannel);
   //   apex::session::install_message_routing(pchannel);

   }


   void session::_001OnFileNew()
   {

   }


   void session::launch_app(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   ::estatus     session::do_request(::create* pcreate)
   {

      return ::thread::do_request(pcreate);

   }




   void session::request_topic_file(var& varQuery)
   {

      auto psession = Session;

      request_file(psession->m_varTopicFile, varQuery);

   }


   void session::request_topic_file()
   {

      auto psession = Session;

      request_file(psession->m_varTopicFile);

   }


   __pointer(::apex::application) session::get_current_application()
   {

      auto psession = Session;

      return psession->m_pappCurrent;

   }

   bool session::is_remote_session()
   {


      return Context.os().is_remote_session();


   }


   //bool session::is_mouse_button_pressed(::user::e_mouse emouse)
   //{

   //   if (emouse == ::user::mouse_left_button)
   //   {
   //      return psession->is_key_pressed(::user::key_lbutton);
   //   }
   //   else if (emouse == ::user::mouse_right_button)
   //   {
   //      return psession->is_key_pressed(::user::key_rbutton);
   //   }
   //   else if (emouse == ::user::mouse_middle_button)
   //   {
   //      return psession->is_key_pressed(::user::key_mbutton);
   //   }
   //   else
   //   {
   //      __throw(::exception::exception("not expected e_mouse value"));
   //   }


   //}





//
//   bool session::open_file(::filemanager::data* pdata, ::file::item_array& itema)
//   {
//
//      UNREFERENCED_PARAMETER(pdata);
//
//      if (itema.get_size() > 0)
//      {
//
//         return true;
//
//      }
//
//      return false;
//
//   }








   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = new nature::database(this);

      //if(m_pdatabase == nullptr)
      //{
      //   TRACE("VmpLightApp::init_instance failed to instatiate LightDB\n");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   TRACE("VmpLightApp::init_instance failed to initialize LightDB\n");
      //   return false;
      //}

      return true;

   }


   void session::check_topic_file_change()
   {

      auto psession = Session;

      if (psession->m_varCurrentViewFile != psession->m_varTopicFile && !psession->m_varTopicFile.is_empty())
      {

         psession->m_varCurrentViewFile = psession->m_varTopicFile;

         request_topic_file();

      }

   }


   //::user::place_holder_ptra session::get_place_holder(__pointer(::user::frame_window) pmainframe, ::create * pcreate)
   //{

   //   UNREFERENCED_PARAMETER(pcreate);

   //   ::user::place_holder_ptra holderptra;


   //   ::apex::application & app = App(pmainframe->get_context_application());

   //   string strAppName = app.m_strAppName;

   //   //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
   //   //{

   //   //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName)));

   //   //}
   //   //else
   //   //{

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::view >());

   //   //}

   //   return holderptra;

   //}

   //bool session::place(::user::main_frame* pmainframe, ::create* pcreate)
   //{

   //   //get_place_holder(pmainframe, pcreate).hold(pmainframe);

   //   return true;

   //}





   void session::set_app_title(const char* pszAppId, const char* pszTitle)
   {

      __pointer(::apex::application) papp;

      if (m_applicationa.lookup(pszAppId, papp) && papp)
      {

         //__pointer(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         //if(ppaneview != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

         //   if(ppane != nullptr)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneview->on_layout(::draw2d::graphics_pointer & pgraphics);

         //   }

         //}

      }

   }



   __pointer(::apex::session) session::get_context_session()
   {

      return this;

   }



   //   bool session::is_serviceable() const
   //   {
   //
   //
   ////      return ::session::application::is_serviceable();
   //      return false;
   //
   //
   //   }


      //bool session::on_uninstall()
      //{


      //   bool bOk1 = true;
      //   bool bOk2 = true;

      //   try
      //   {

      //      bOk1 = ::apex::session::on_uninstall();

      //   }
      //   catch(...)
      //   {
      //      bOk1 = false;
      //   }




      //   return bOk1 && bOk2;


      //}


      //::estatus session::os_native_bergedge_start()
      //{

      //   if (!::apex::application::os_native_bergedge_start())
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //service_base * session::allocate_new_service()
      //{


      //   return ::apex::application::allocate_new_service();


      //}





   //::draw2d::cursor* session::get_default_cursor()
   //{

   //   return System.draw2d().get_cursor(m_ecursorDefault);

   //}


   ::estatus     session::main()
   {

      //return ::apex::session::main();
      return ::thread::main();

   }


   //::apex::session * session::query_bergedge()
   //{

   //   ::apex::session * psession = nullptr;

   //   if(System.m_pbergedgemap == nullptr)
   //      return nullptr;

   //   if(!System.m_pbergedgemap->lookup(0,psession))
   //   {
   //      return nullptr;
   //   }

   //   return psession;

   //}


   //void session::on_user_logon(::account::user* puser)
   //{

   //   ::apex::session::on_user_logon(puser);

   //}


//   void session::interactive_credentials(::account::credentials* pcredentials)
//   {
//
//
//      //if (!USER)
//      //{
//
//      //   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;
//
//      //   return;
//
//      //}
//      pcredentials->m_estatus = error_failed;
//
//      manual_reset_event ev;
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      //if (m_pmainpane != nullptr && m_pmainpane == nullptr)
//      //{
//
//      //   try
//      //   {
//
//      //      m_pmainpane->interactive_credentials(pcredentials);
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
//      if (pcredentials->m_estatus == ::success_credentials ||
//         ::failed(pcredentials->m_estatus, STATUS_RANGE_AUTHENTICATION))
//      {
//
//         return;
//
//      }
//
//#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)
//      //attach_thread_input_to_main_thread(false);
//#endif
//
//      ::apex::session::interactive_credentials(pcredentials);
//
//      if (pcredentials->m_estatus == ::success_credentials)
//      {
//
//         return;
//
//      }
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      auto puser = pcredentials->m_puser;
//
//      //auto pdialog = ::__create_new<::account::dialog>();
//
//      //pdialog->initialize_account_dialog(pcredentials);
//
//      //pdialog->get_credentials();
//
//      //pdialog->DestroyWindow();
//
//
//   }


   //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText)
   //{

   //   string_array& straTitle = pane.m_straTitle;

   //   pgraphics->set(brushText);

   //   if (straTitle.get_count() <= 1)
   //   {

   //      pgraphics->_DrawText(pane.get_title(), recte_bottom_left, e_draw_text_no_prefix);

   //   }
   //   else
   //   {

   //      ::rect rectText(rect);


   //      ::draw2d::font_pointer font;
   //      font = pgraphics->get_current_font();
   //      size sSep = ptab->get_data()->m_sizeSep;
   //      ::rect rectEmp;
   //      for (index i = 0; i < straTitle.get_size(); i++)
   //      {
   //         string str = straTitle[i];
   //         size s = pane.m_sizeaText[i];
   //         rectText.right = rectText.left + s.cx;
   //         pgraphics->_DrawText(str, rectTexte_bottom_left, e_draw_text_no_prefix);
   //         rectText.left += s.cx;
   //         if (i < straTitle.get_upper_bound())
   //         {
   //            rectText.right = rectText.left + sSep.cx;
   //            rectEmp = rectText;
   //            rectEmp.deflate(1, 1);
   //            ::draw2d::e_alpha_mode emode = pgraphics->m_ealphamode;
   //            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
   //            if (ptab->m_itemHover == (::user::e_element)(::user::element_split + i))
   //            {
   //               pgraphics->fill_rect(rectEmp, ARGB(128, 150, 184, 255));
   //               pgraphics->set(ptab->get_data()->m_brushTextHover);
   //            }
   //            else
   //            {
   //               //pgraphics->fill_rect(rectEmp,ARGB(128,208,223,233));
   //               pgraphics->set(ptab->get_data()->m_brushText);
   //            }
   //            pgraphics->set(ptab->m_pfontTab);
   //            pgraphics->set_alpha_mode(emode);
   //            pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectText, e_align_center, e_draw_text_no_prefix);
   //            rectText.left += sSep.cx;
   //            pgraphics->set(font);
   //            pgraphics->set(brushText);
   //         }
   //      }

   //   }

   //}


   string_array session::get_user_wallpaper()
   {

      string_array stra;

      //string_array straSource = psession->userex()->get_wallpaper();

      //for (string str : straSource)
      //{

      //   if (::str::begins_eat_ci(str, "file://"))
      //   {

      //      str = System.url().url_decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }



   void session::frame_pre_translate_message(::message::message* pmessage)
   {

      if (pmessage->m_id == WM_GETTEXT
         || pmessage->m_id == WM_GETTEXTLENGTH
         )
      {

         pmessage->m_uiMessageFlags |= 3; // message considered pre translated
         pmessage->m_uiMessageFlags |= 16384; //  by early optmization

         return;

      }
      //else if (pmessage->m_id == e_message_mouse_move)
      //{

      //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
      //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   return;

      //}

      //try
      //{

      //   __pointer(::user::interaction) pinteraction;

      //   while (get_frame(pinteraction))
      //   {

      //      try
      //      {

      //         if (pinteraction != nullptr)
      //         {

      //            pinteraction->pre_translate_message(pmessage);

      //            if (pmessage->m_bRet)
      //               return;

      //         }

      //      }
      //      catch (::exception_pointer pe)
      //      {

      //         if (e.is < ::exit_exception>())
      //         {

      //            __rethrow(::move(e));

      //         }

      //      }
      //      catch (...)
      //      {
      //      }

      //   }

      //}
      //catch (::exception_pointer pe)
      //{

      //   if (e.is < ::exit_exception>())
      //   {

      //      __rethrow(::move(e));

      //   }

      //}
      //catch (...)
      //{

      //   pmessage->m_bRet = true;

      //}

   }



   void session::finalize()
   {

      ::application_container::m_applicationa.remove_all();

      ::apex::context_thread::finalize();

   }

   
   __namespace_session_factory(session);


} // namespace apex



