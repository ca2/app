#include "framework.h"
#include "apex/operating_system.h"
#include "acme/id.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"



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


int_bool point_is_window_origin(POINT_I32 ptHitTest, ::windowing::window * pwindowExclude, int iMargin);

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


   ::e_status session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      set_context_session(this);

      set_context_object(this);

      set_context(this);

      if (get_context_system() != nullptr)
      {

         m_bSystemSynchronizedCursor   = System->m_bSystemSynchronizedCursor;

      }

      m_pappCurrent                    = nullptr;

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

   
   //void session::enum_display_monitors()
   //{


   //}
   

   //index session::get_main_monitor(RECTANGLE_I32* prectangle)
   //{

   //   return -1;

   //}


   //::count session::get_monitor_count()
   //{

   //   return -1;

   //}

   
   //bool  session::get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}

   
   //::count session::get_desk_monitor_count()
   //{

   //   return -1;

   //}


   //bool  session::get_desk_monitor_rect(index iMonitor, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //index session::get_main_workspace(RECTANGLE_I32* prectangle)
   //{

   //   return -1;

   //}


   //::count session::get_workspace_count()
   //{

   //   return -1;

   //}


   //bool  session::get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}

   //
   //::count session::get_desk_workspace_count()
   //{

   //   return -1;

   //}
  
   //
   //bool  session::get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //bool session::set_main_monitor(index iMonitor)
   //{

   //   return false;

   //}
   

   //bool session::set_main_workspace(index iWorkspace)
   //{

   //   return false;

   //}


   //bool session::workspace_to_monitor(RECTANGLE_I32* prectangle, index iMonitor, index iWorkspace)
   //{

   //   return false;

   //}


   //bool session::monitor_to_workspace(RECTANGLE_I32* prectangle, index iWorkspace, index iMonitor)
   //{

   //   return false;

   //}


   //bool session::workspace_to_monitor(RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //bool session::monitor_to_workspace(RECTANGLE_I32* prectangle)
   //{

   //   return false;

   //}


   //void session::get_monitor(rect_array& rectaMonitor, rect_array& rectaIntersect, const ::rectangle_i32& rectangle)
   //{


   //}


   ::color::color session::get_default_color(u64 u)
   {

      auto pnode = System->node();

      if (!pnode)
      {

         return argb(127, 0, 0, 0);

      }

      return pnode->get_default_color(u);

   }






   //size_i32 session::get_window_minimum_size()
   //{

   //   return size_i32(300, 300);

   //}


   ::e_status session::init_thread()
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


   ::e_status session::process_init()
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


   ::e_status session::init_session()
   {

      auto estatus = init1();

      if (!estatus)
      {

         output_debug_string("\nFailed to init1 the session (::apex::session or ::apex::session derived)");

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

   //::e_status session::init()
   //{



   //   return true;

   //}


   //void session::term()
   //{

   //   m_paccount.release();






   //}


   void session::term2()
   {



   }


   void session::term1()
   {


   }


   void session::process_term()
   {

      System->session_remove(m_iEdge);

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
//      ::e_status estatus = __compose(m_puiSession, ::move(create_system_message_window(this)));
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

      if (System->is_console_app())
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
            //   __pointer(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->get_parent_frame());
            //   if(pframe != nullptr)
            //   {
            //      pframe->display(e_display_normal);
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

               if(System->has_property("install")
                     || System->has_property("uninstall"))
               {

                  ::parallelization::finish(System);

               }
               else
               {

                  message_box("Could not create requested application: \"" + strApp + "\"");

                  ::count c = System->payload("app").array_get_count();

                  if (c == 1 && System->payload("app").at(0) == strApp)
                  {

                     ::parallelization::finish(System);

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

               //if (System->is_true("install"))
               if (is_true("install"))
               {

                  papp->do_install();

                  System->finalize();

               }
               else
               {

                  if (!papp->is_system() && !papp->is_session())
                  {

                     System->merge_accumulated_on_open_file(pcreate);

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

   //   __throw(error_interface_only);

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

      string strProtocol = System->url().get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = System->url().get_server(strPathName);

         string str = System->url().get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreate->m_pcommandline->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.extension();

         string_array straApp;

         __throw(todo, "filehandler");

         //System->filehandler().get_extension_app(straApp, strExtension);

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
         catch (const ::exception::exception & e)
         {

            // apex::session, axis::session and ::base::session, could get more specialized handling in apex::application (apex::system)
            // Thank you Mummi (em Santos, cuidando do Lucinho e ajudando um monte a Carô e o Lúcio e Eu 2019-01-15) !! Thank you God!! <3tbs

            handle_exception(e);

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


   //bool session::set_cursor(::user::interaction * pinteraction, enum_cursor ecursor)
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


   //bool session::set_default_cursor(::user::interaction * pinteraction, enum_cursor ecursor)
   //{

   //   if (ecursor == e_cursor_default)
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


//  void session::get_cursor_position(POINT_I32 * ppoint)
//  {
//
//
////   __throw(todo("aura"));
////     if (m_bSystemSynchronizedCursor)
////     {
////
////        POINT_I32 point_i32;
////
////        ::GetCursorPos(&point);
////
////        m_pointCursor = point;
////
////     }
//
//     if (ppoint != nullptr)
//     {
//
//        *ppoint = m_pointCursor;
//
//     }
//
//  }

//
//   oswindow session::get_capture()
//   {
//
//      return ::get_capture();
//
//   }
//
//
//   void session::set_cursor_pos(const ::point_i32 & point)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      ::SetCursorPos(point.x, point.y);
//
//#endif
//
//   }
//
//
//   bool session::ReleaseCapture()
//   {
//
//      // ::windowing::window * pwindowCapture = ::get_capture();
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

   //   ::windowing::window * pwindowCapture = ::get_capture();

   //   if (oswindowCapture == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   __pointer(::user::interaction) pinteraction = System->ui_from_handle(oswindowCapture);

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





   //index session::initial_frame_position(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, bool bMove, ::user::interaction * pinteraction)
   //{

   //   ::rectangle_i32 rectRestore(rectParam);

   //   ::rectangle_i32 rectMonitor;

   //   index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

   //   ::size_i32 sizeMin;

   //   if (pinteraction != nullptr)
   //   {

   //      sizeMin  = pinteraction->get_window_minimum_size();

   //   }
   //   else
   //   {

   //      sizeMin = get_window_minimum_size();

   //   }

   //   ::rectangle_i32 rectIntersect;

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

   //      if (rectMonitor.width() / 7 + maximum(sizeMin.cx, rectMonitor.width() * 2 / 5) > rectMonitor.width()
   //            || rectMonitor.height() / 7 + maximum(sizeMin.cy, rectMonitor.height() * 2 / 5) > rectMonitor.width())
   //      {

   //         rectRestore = rectMonitor;

   //      }
   //      else
   //      {

   //         rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

   //         rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

   //         rectRestore.right = rectRestore.left + maximum(sizeMin.cx, rectMonitor.width() * 2 / 5);

   //         rectRestore.bottom = rectRestore.top + maximum(sizeMin.cy, rectMonitor.height() * 2 / 5);

   //         if (rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
   //         {

   //            rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right, 0);

   //         }

   //         if (rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
   //         {

   //            rectRestore.offset(0, rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

   //         }

   //      }

   //      *prectangle = rectRestore;

   //      return iMatchingMonitor;

   //   }
   //   else
   //   {

   //      if (!bMove)
   //      {

   //         *prectangle = rectIntersect;

   //      }

   //      return -1;

   //   }

   //}


   //index session::get_window_restore_1(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   //{

   //   ::rectangle_i32 rectRestore(rectParam);

   //   ::rectangle_i32 rectWorkspace;

   //   ::size_i32 sizeMin;

   //   index iMatchingWorkspace;

   //   ::size_i32 sizeBroad;

   //   ::size_i32 sizeCompact;

   //   if (pinteraction != nullptr)
   //   {

   //      sizeMin = pinteraction->get_window_minimum_size();

   //      iMatchingWorkspace = pinteraction->calculate_broad_and_compact_restore(rectWorkspace, sizeMin, rectParam);

   //      sizeBroad = pinteraction->m_sizeRestoreBroad;

   //      sizeCompact = pinteraction->m_sizeRestoreCompact;

   //   }
   //   else
   //   {

   //      sizeMin = get_window_minimum_size();

   //      iMatchingWorkspace = get_best_workspace(&rectWorkspace, rectParam);

   //      sizeBroad = sizeMin.maximum(rectWorkspace.size() * 4 / 5);

   //      sizeCompact = sizeMin.maximum(rectWorkspace.size() * 2 / 5);

   //   }

   //   auto rectIntersect = rectWorkspace & rectParam;

   //   auto rectTolerance(rectWorkspace);

   //   auto sizeMax = rectWorkspace.size() * 0.8;

   //   bool b1 = !rectTolerance.contains(rectRestore);
   //   bool b2 = rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy;
   //   bool b3 = rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy;
   //   bool b4 = (edisplayRestore == e_display_compact && rectRestore.size() != sizeCompact);
   //   bool b5 = (edisplayRestore == e_display_broad && rectRestore.size() != sizeBroad);
   //   bool b6 = (rectRestore.size() == sizeCompact || rectRestore.size() == sizeBroad);
   //   bool b66 = !(edisplayRestore == e_display_compact || edisplayRestore == e_display_broad);

   //   bool bNotHappyWithTheSizeAndOrPosition = b1 || b2 || b3 || b4 || b5 || (b6 && b66);

   //   if (bNotHappyWithTheSizeAndOrPosition)
   //   {

   //      if (edisplayRestore == e_display_broad || sizeCompact == rectRestore.size())
   //      {

   //         rectRestore.set_size(sizeBroad);

   //      }
   //      else
   //      {

   //         rectRestore.set_size(sizeCompact);

   //      }

   //      ::rectangle_i32 rectWorkspaceBitSmaller(rectWorkspace);

   //      rectWorkspaceBitSmaller.deflate(5);

   //      if (!rectWorkspaceBitSmaller.contains(rectRestore))
   //      {

   //         rectRestore.move_to(rectWorkspace.origin() + rectWorkspace.size() / 10);

   //      }

   //      *prectangle = rectRestore;

   //      return iMatchingWorkspace;

   //   }
   //   else
   //   {

   //      return -1;

   //   }

   //}


   //index session::get_window_restore_2(RECTANGLE_I32* prectangle, const rectangle_i32& rectParam, ::user::interaction* pinteraction, edisplay edisplayRestore)
   //{

   //   ::rectangle_i32 rectangle(rectParam);

   //   index iBestWorkspace = get_window_restore_1(prectangle, rectangle, pinteraction, edisplayRestore);

   //   bool bChangedSize = ::size_i32(prectangle) != rectParam.size();

   //   if (iBestWorkspace < 0 && !bChangedSize)
   //   {

   //      return -1;

   //   }

   //   ::rectangle_i32 rectWorkspace;

   //   ::rectangle_i32 rectStart(prectangle);

   //   ::point_i32 pointLineStart(::top_left(prectangle));

   //   get_workspace_rectangle(iBestWorkspace, rectWorkspace);

   //   if (rectStart > pinteraction->m_sizeRestoreCompact)
   //   {

   //      pointLineStart = rectWorkspace.origin();

   //      pointLineStart.offset(49, 49);

   //      rectangle.move_to(pointLineStart);

   //   }

   //   if(::is_window(pinteraction->get_handle()))
   //   {

   //      do
   //      {

   //         if (!point_is_window_origin(::top_left(prectangle), pinteraction->get_handle(), 49))
   //         {

   //            return iBestWorkspace;

   //         }

   //         rectangle = *prectangle;

   //         if (rectangle_i32 > pinteraction->m_sizeRestoreCompact)
   //         {

   //            rectangle.offset(49, 0);

   //            if (!rectWorkspace.contains(rectangle))
   //            {

   //               pointLineStart.offset(0, 49);

   //               rectangle.move_to(pointLineStart);

   //               if (!rectWorkspace.contains(rectangle))
   //               {

   //                  break;

   //               }

   //            }

   //         }
   //         else
   //         {

   //            rectangle.offset(49, 49);

   //         }

   //         *prectangle = rectangle;

   //      }
   //      while (rectWorkspace.contains(rectangle));

   //   }

   //   if (rectangle.size() >= pinteraction->m_sizeRestoreCompact)
   //   {

   //      pointLineStart = rectWorkspace.origin();

   //      pointLineStart.offset(49, 49);

   //      rectangle.move_to(pointLineStart);

   //      *prectangle = rectangle;

   //      return iBestWorkspace;

   //   }

   //   rectangle = rectStart;

   //   rectangle.set_size(pinteraction->m_sizeRestoreCompact);

   //   if(::is_window(pinteraction->get_handle()))
   //   {

   //      do
   //      {

   //         if (!point_is_window_origin(::top_left(prectangle), pinteraction->get_handle(), 49))
   //         {

   //            return iBestWorkspace;

   //         }

   //         rectangle = *prectangle;

   //         rectangle.offset(49, 49);

   //         *prectangle = rectangle;

   //      } while (rectWorkspace.contains(rectangle));

   //   }

   //   pointLineStart = rectWorkspace.origin();

   //   pointLineStart.offset(49, 49);

   //   rectangle.move_to(pointLineStart);

   //   if(::is_window(pinteraction->get_handle()))
   //   {

   //      do
   //      {

   //         if (!point_is_window_origin(::top_left(prectangle), pinteraction->get_handle(), 49))
   //         {

   //            return iBestWorkspace;

   //         }

   //         rectangle = *prectangle;

   //         rectangle.offset(49, 0);

   //         if (!rectWorkspace.contains(rectangle))
   //         {

   //            pointLineStart.offset(0, 49);

   //            rectangle.move_to(pointLineStart);

   //            if (!rectWorkspace.contains(rectangle))
   //            {

   //               break;

   //            }

   //         }

   //         *prectangle = rectangle;

   //      } while (rectWorkspace.contains(rectangle));

   //   }

   //   pointLineStart = rectWorkspace.origin();

   //   pointLineStart.offset(49, 49);

   //   rectangle.move_to(pointLineStart);

   //   *prectangle = rectangle;

   //   return iBestWorkspace;

   //}


   //index session::get_good_move(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::user::interaction * pinteraction)
   //{

   //   index iMatchingMonitor = initial_frame_position(prectangle, rectParam, true, pinteraction);

   //   if (__memcmp(prectangle, &rectParam, sizeof(const rectangle_i32 &)))
   //   {

   //      return iMatchingMonitor;

   //   }
   //   else
   //   {

   //      return -1;

   //   }

   //}


   //index session::get_ui_workspace(::user::interaction * pinteraction)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      return System->get_ui_workspace(pinteraction);

   //   }
   //   else
   //   {

   //      ::rectangle_i32 rectangle;

   //      pinteraction->get_window_rect(rectangle);

   //      return get_best_workspace(nullptr, rectangle);

   //   }

   //}


   bool session::is_key_pressed(::user::enum_key ekey)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::enum_key, bool >;

      }

      bool bPressed = false;
      if (ekey == ::user::e_key_shift)
      {
         m_pmapKeyPressed->lookup(::user::e_key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_command)
      {
         m_pmapKeyPressed->lookup(::user::e_key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lcommand, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_rcommand, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_control)
      {
         m_pmapKeyPressed->lookup(::user::e_key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_alt)
      {
         m_pmapKeyPressed->lookup(::user::e_key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_ralt, bPressed);
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


   void session::set_key_pressed(::user::enum_key ekey, bool bPressed)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::enum_key, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }


   

   ::e_status session::init1()
   {

      auto estatus = __compose_new(m_pfs);

      if (!estatus)
      {

         output_debug_string("\nFailed to __compose_new(m_pfs)");

         m_result.add(estatus);

         return false;

      }

      // __throw(todo("interaction"));
      //if (System->m_bUser)
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


   ::e_status session::defer_initialize_host_window(const RECTANGLE_I32 * lpcrect)
   {

      return ::success;

   }


   ::e_status session::init2()
   {

      ::e_status estatus;

      INFO("apex::session::init2 .1");

      if (System->m_bUser)
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


   ::e_status session::init()
   {

      ::e_status estatus = ::success;

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


   ::u32 session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}


   //bool session::on_create_frame_window()
   //{

   //   return true;

   //}


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






   //::e_status session::initialize(::layered * pobjectContext)
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


   ::e_status     session::do_request(::create* pcreate)
   {

      return ::thread::do_request(pcreate);

   }




   void session::request_topic_file(::payload& varQuery)
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


      return get_context()->os().is_remote_session();


   }


   //bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   //{

   //   if (emouse == ::user::e_mouse_left_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_lbutton);
   //   }
   //   else if (emouse == ::user::e_mouse_right_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_rbutton);
   //   }
   //   else if (emouse == ::user::e_mouse_middle_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_mbutton);
   //   }
   //   else
   //   {
   //      __throw(::exception::exception("not expected enum_mouse value"));
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


      //::e_status session::os_native_bergedge_start()
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

   //   return System->draw2d()->get_cursor(m_ecursorDefault);

   //}


   ::e_status     session::main()
   {

      //return ::apex::session::main();
      return ::thread::main();

   }


   //::apex::session * session::query_bergedge()
   //{

   //   ::apex::session * psession = nullptr;

   //   if(System->m_pbergedgemap == nullptr)
   //      return nullptr;

   //   if(!System->m_pbergedgemap->lookup(0,psession))
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


   //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32& rectangle, ::draw2d::brush_pointer& brushText)
   //{

   //   string_array& straTitle = pane.m_straTitle;

   //   pgraphics->set(brushText);

   //   if (straTitle.get_count() <= 1)
   //   {

   //      pgraphics->_DrawText(pane.get_title(), recte_bottom_left, e_draw_text_no_prefix);

   //   }
   //   else
   //   {

   //      ::rectangle_i32 rectText(rectangle);


   //      ::write_text::font_pointer font;
   //      font = pgraphics->get_current_font();
   //      size_i32 sSep = ptab->get_data()->m_sizeSep;
   //      ::rectangle_i32 rectEmp;
   //      for (index i = 0; i < straTitle.get_size(); i++)
   //      {
   //         string str = straTitle[i];
   //         size_i32 s = pane.m_sizeaText[i];
   //         rectText.right = rectText.left + s.cx;
   //         pgraphics->_DrawText(str, rectTexte_bottom_left, e_draw_text_no_prefix);
   //         rectText.left += s.cx;
   //         if (i < straTitle.get_upper_bound())
   //         {
   //            rectText.right = rectText.left + sSep.cx;
   //            rectEmp = rectText;
   //            rectEmp.deflate(1, 1);
   //            ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
   //            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
   //            if (ptab->m_itemHover == (::user::enum_element)(::user::e_element_split + i))
   //            {
   //               pgraphics->fill_rectangle(rectEmp, argb(128, 150, 184, 255));
   //               pgraphics->set(ptab->get_data()->m_brushTextHover);
   //            }
   //            else
   //            {
   //               //pgraphics->fill_rectangle(rectEmp,argb(128,208,223,233));
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

      //      str = System->url().url_decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }


   ::user::interaction * session::get_host_window()
   {
      
      return __user_interaction(m_puiHost); 
   
   }


   void session::frame_pre_translate_message(::message::message* pmessage)
   {

//      if (pmessage->m_id == WM_GETTEXT
//         || pmessage->m_id == WM_GETTEXTLENGTH
//         )
//      {
//
//         pmessage->m_uiMessageFlags |= 3; // message considered pre translated
//         pmessage->m_uiMessageFlags |= 16384; //  by early optmization
//
//         return;
//
//      }
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
      //      catch (const ::exception::exception & e)
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
      //catch (const ::exception::exception & e)
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



