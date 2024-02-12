#include "framework.h"
#include "interaction_impl.h"
#include "interaction.h"
#include "interaction_scaler.h"
#include "system.h"
#include "user.h"
#include "interaction_thread.h"
#include "interaction_graphics_thread.h"
//#include "aura/operating_system/_node.h"
//#include "acme/operating_system/_user.h"
//#include "aura/graphics/graphics/_.h"
//#include "aura/graphics/graphics/_graphics.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/graphics/output_purpose.h"
#include "acme/handler/request.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"
#include "acme/platform/node.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/graphics.h"
#include "acme/platform/scoped_restore.h"
#include "acme/user/user/_text_stream.h"
#include "aura/windowing/text_editor_interface.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/windowing/monitor.h"
#include "aura/windowing/placement_log.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/windowing/display.h"
#include "aura/message/user.h"
#include "aura/platform/message_queue.h"
#include "aura/platform/session.h"
#include "aura/platform/application.h"

#if defined(LINUX)
bool is_ubunt() { return true; }
#else
bool is_ubunt() { return false; }
#endif

#ifdef WINDOWS_DESKTOP


//#include "acme/_operating_system.h"


#endif

point_i32 g_pointLastBottomRight;

#undef ALOG_CONTEXT
#define ALOG_CONTEXT (::trace_object(::trace_category_windowing))

//#include <mutex>


#define TIME_REPORTING 0


#ifdef WINDOWS_DESKTOP
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#endif

CLASS_DECL_ACME void monitor_pointer(void * p);

#define REDRAW_HINTING
//CLASS_DECL_AURA bool task_set_name(const ::string &psz);

#define IMAGE_OK(pimpl) (::is_set(pimpl) && pimpl->area() > 0)
//void windowing_output_debug_string(const ::string & pszDebugString);

#define REDRAW_PROFILE_NORMAL 5

#define REDRAW_PROFILE REDRAW_PROFILE_NORMAL


#define HARD_DEBUG 0
#undef REDRAW_HINTING


namespace user
{


   interaction_impl::interaction_impl()
   {

      user_common_construct();

   }


   interaction_impl::~interaction_impl()
   {

   }


   void interaction_impl::user_common_construct()
   {

      m_pImpl2 = nullptr;

      m_pinteractionimpl = this;

      //m_bOfflineRender = false;

      m_iState1 = 0;

      m_uCodePage = 0;

      m_iLangId = 0;

      m_bPendingRedraw = false;

      m_bEatMoveEvent = false;

      m_bEatSizeEvent = false;

      m_bOkToUpdateScreen = true;
      m_bUpdatingBuffer = false;
      m_bCursorRedraw = false;

      m_bScreenRelativeMouseMessagePosition = true;
      m_bTranslateMouseMessageCursor = true;
      m_bComposite = true;
      m_bUpdateGraphics = false;
      m_bPendingRedraw = false;
      m_bTransparentMouseEvents = false;

      m_bDoingGraphics = false;

#if defined(APPLE_IOS) || defined(ANDROID)

      set_per_second(12.0);

#elif defined(UNIVERSAL_WINDOWS)

      set_per_second(60.0);

#else

      set_per_second(60.0);

#endif

      m_bUpdateBufferPending = false;



   }


   void interaction_impl::on_initialize_particle()
   {

      defer_create_synchronization();

   }


   void interaction_impl::on_tsf_activate(bool bActivate)
   {

   }


   //void interaction_impl::sketch_to_layout(::graphics::buffer_item * pbufferitem)
   //{

   //   m_puserinteraction->sketch_to_layout();

   //   pbufferitem->m_point = m_puserinteraction->const_layout().layout().origin();

   //   pbufferitem->m_size = m_puserinteraction->const_layout().layout().size();

   //}


   ::pointer< ::mutex > interaction_impl::draw_mutex()
   {

      if (m_pmutexDraw == nullptr)
      {

#if REFERENCING_DEBUGGING

         refdbg_top_track refdbgtoptrack(this);

#endif

         __construct(m_pmutexDraw);

      }

      return m_pmutexDraw;

   }


   ::user::interaction_impl * interaction_impl::get_user_interaction_impl()
   {

      return this;

   }


   bool interaction_impl::has_pending_redraw_flags()
   {

      return ::user::primitive_impl::has_pending_redraw_flags();

   }


   void interaction_impl::set_need_layout()
   {

      m_puserinteraction->set_need_layout();

   }


   bool interaction_impl::has_pending_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return false;

      }

      if (::is_null(psession->m_pimplPendingFocus2))
      {

         return false;

      }

      if (psession->m_pimplPendingFocus2 != this)
      {

         return false;

      }

      return true;

   }


   bool interaction_impl::clear_pending_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return false;

      }

      if (::is_null(psession->m_pimplPendingFocus2))
      {

         return false;

      }

      if (psession->m_pimplPendingFocus2 != this)
      {

         return false;

      }

      psession->m_pimplPendingFocus2 = nullptr;

      return true;

   }


   bool interaction_impl::set_pending_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return false;

      }

      psession->m_pimplPendingFocus2 = this;

      return true;

   }


   void interaction_impl::create_message_queue(::user::interaction * pinteraction, const ::string & lpszName)
   {

      if (_is_window())
      {

         auto puserinteraction = m_puserinteraction;

         if (puserinteraction)
         {

            m_puserinteraction->set_window_text(lpszName);

         }

      }
      else
      {

         pinteraction->m_bMessageWindow = true;

         //create_host(pinteraction, e_parallelization_synchronous);
         create_host(pinteraction);

      }

   }



   //void interaction_impl::create_native_window(::user::native_window_initialize* pinitialize)
   //{

   //   UNREFERENCED_PARAMETER(pinitialize);
   //   throw ::interface_only();

   //   return false;

   //}

//#ifdef WINDOWS_DESKTOP
//
//
//   void interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
//   {
//      UNREFERENCED_PARAMETER(pwi);
//      throw ::interface_only();
//      return false;
//   }
//
//   void interaction_impl::GetScrollBarInfo(::i32 idObject,PSCROLLBARINFO psbi) const
//   {
//      UNREFERENCED_PARAMETER(idObject);
//      UNREFERENCED_PARAMETER(psbi);
//      throw ::interface_only();
//      return false;
//   }
//
//   void interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
//   {
//      UNREFERENCED_PARAMETER(pti);
//      throw ::interface_only();
//      return false;
//   }
//
//#endif

#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)


   ::user::interaction_impl * interaction_impl::GetAncestor(::u32 gaFlags) const
   {

      UNREFERENCED_PARAMETER(gaFlags);

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_impl::AnimateWindow(::time ::time,u32 dwFlags)
   //{
   //   UNREFERENCED_PARAMETER(::time);
   //   UNREFERENCED_PARAMETER(dwFlags);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::FlashWindowEx(u32 dwFlags,::u32 uCount,::time tickTimeout)
   //{
   //   UNREFERENCED_PARAMETER(dwFlags);
   //   UNREFERENCED_PARAMETER(uCount);
   //   UNREFERENCED_PARAMETER(tickTimeout);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::SetLayeredWindowAttributes(::color::color crKey,::u8 bAlpha,u32 dwFlags)
   //{
   //   UNREFERENCED_PARAMETER(crKey);
   //   UNREFERENCED_PARAMETER(bAlpha);
   //   UNREFERENCED_PARAMETER(dwFlags);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst,::point_i32 * pptDst,::size_i32 * psize,
   //      ::draw2d::graphics * pDCSrc,::point_i32 * pptSrc,::color::color crKey,BLENDFUNCTION * pblend,u32 dwFlags)
   //{
   //   UNREFERENCED_PARAMETER(pDCDst);
   //   UNREFERENCED_PARAMETER(pptDst);
   //   UNREFERENCED_PARAMETER(psize);
   //   UNREFERENCED_PARAMETER(pDCSrc);
   //   UNREFERENCED_PARAMETER(pptSrc);
   //   UNREFERENCED_PARAMETER(crKey);
   //   UNREFERENCED_PARAMETER(pblend);
   //   UNREFERENCED_PARAMETER(dwFlags);
   //   throw ::interface_only();

   //   return false;
   //}


   //void interaction_impl::GetLayeredWindowAttributes(::color::color * pcrKey,::u8 * pbAlpha,u32 * pdwFlags) const
   //{
   //   UNREFERENCED_PARAMETER(pcrKey);
   //   UNREFERENCED_PARAMETER(pbAlpha);
   //   UNREFERENCED_PARAMETER(pdwFlags);
   //   throw ::interface_only();

   //   return false;
   //}

   //void interaction_impl::PrintWindow(::draw2d::graphics_pointer & pgraphics,::u32 nFlags) const
   //{
   //   UNREFERENCED_PARAMETER(pgraphics);
   //   UNREFERENCED_PARAMETER(nFlags);
   //   throw ::interface_only();

   //   return false;
   //}

#endif


   //lresult interaction_impl::default_window_procedure()
   //{
   //
   //   return default_window_procedure(m_uiMessage, m_wparam, m_lparam);

   //}


   void interaction_impl::pre_subclass_window()
   {

      throw ::interface_only();

   }


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

      throw ::interface_only();

      return nullptr;

   }


   void * interaction_impl::get_os_data() const
   {

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_impl::create_host(::user::interaction * pinteraction, ::user::primitive * pprimitiveParent)
   //{

   //   //if (!pparent)
   //   {

   //      if (!native_create_window())
   //      {

   //         return false;

   //      }

   //   }
   //   //else
   //   //{

   //   //   if (!native_create_window_ex(pinteraction, pusersystem, puiParent->get_safe_handle(), atom))
   //   //   {

   //   //      return false;

   //   //   }

   //   //}

   //   return true;

   //}


   // for child windows
   bool interaction_impl::pre_create_window(::user::system * pusersystem)
   {

      UNREFERENCED_PARAMETER(pusersystem);

      return true;

   }


   //void interaction_impl::operating_system_create_host(enum_parallelization eparallelization)
   void interaction_impl::operating_system_create_host()
   {

      //      auto pwindowMain = system()->m_paurasystem->m_pwindowMain;
      //
      //      if (pwindowMain && !pwindowMain->m_puserinteractionimpl)
      //      {
      //
      //         m_pwindow = system()->m_paurasystem->m_pwindowMain;
      //
      //         m_pwindow->m_puserinteractionimpl = this;
      //
      //         m_puserinteraction->m_pinteractionimpl = this;
      //
      //      }
      //      else
      //      {
      //
      //         //auto estatus =
      //
      //         __construct(m_pwindow);
      //
      //         //if (!estatus)
      //         //{
      //
      //         //   return estatus;
      //
      //         //}
      //
      //         if (!system()->m_paurasystem->m_pwindowMain)
      //         {
      //
      //            system()->m_paurasystem->m_pwindowMain = m_pwindow;
      //
      //         }
      //
      //      }
      //
      //      //auto estatus =
      //
      //      m_pwindow->create_window(this);
      //
      //      //if (!estatus)
      //      //{
      //
      //      //   return estatus;
      //
      //      //}
      //
      //      //return true;

      ::pointer<::user::system>pusersystem;

      if (!m_puserinteraction->is_system_message_window())
      {

         if (m_puserinteraction->m_pusersystem)
         {

            pusersystem = m_puserinteraction->m_pusersystem;

         }
         else
         {

            pusersystem = __allocate< ::user::system >();

         }

      }

//      //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || is_string_ok(pusersystem->m_createstruct.lpszName));
//      //
//      if (!m_puserinteraction->pre_create_window(pusersystem))
//      {
//
//         //return false;
//
//         throw ::exception(error_failed);
//
//      }

      //m_puserinteraction->m_pthreadUserInteraction = ::get_task();

      //m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

      //install_message_routing(m_puserinteraction);

      //bool bOk = true;

      //      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
      //      {
      //
      //         auto pwindowing = m_pwindowwindowing();
      //
      //         m_oswindow = pwindowing->new_message_window(this);
      //
      //         m_puserinteraction->m_bMessageWindow = true;
      //
      //         //send_message(e_message_create, 0, (LPARAM) &cs);
      //
      //      }
      //      else

      //_create_window(eparallelization);

      _create_window();

      //      if(bOk)
      //      {
      //
      //         m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
      //
      //         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
      //
      //      }

      //if (!bOk)
      //{

      //   throw ::exception(error_failed);

      //}


   }


   //void interaction_impl::_create_window(::enum_parallelization eparallelization)
   void interaction_impl::_create_window()
   {

      {

         m_puserinteraction->m_bMessageWindow = false;


         auto procedure = [&]()
            {

               auto psession = get_session();

               auto puser = psession->user();

               auto pwindowing = puser->windowing();

               //      auto psession = get_session();

               //      auto puser = psession->user();

               //      auto pwindowing = puser->windowing();

               pwindowing->new_window(this);

               if (m_pwindow)
               {

                  information() << "operating_system_create_host window created";

               }
               else
               {

                  informationf("operating_system_create_host window not created");

               }

            };


         //if (eparallelization == e_parallelization_asynchronous)
         //{

            ///user_post(procedure);

         //}
         //else
         //{

            user_send(procedure);

         //}


         //});

      }

   }


   void interaction_impl::native_create_host_alternate()
   {

      //      auto pwindowMain = system()->m_paurasystem->m_pwindowMain;
      //
      //      if (pwindowMain && !pwindowMain->m_puserinteractionimpl)
      //      {
      //
      //         m_pwindow = system()->m_paurasystem->m_pwindowMain;
      //
      //         m_pwindow->m_puserinteractionimpl = this;
      //
      //         m_puserinteraction->m_pinteractionimpl = this;
      //
      //      }
      //      else
      //      {
      //
      //         //auto estatus =
      //
      //         __construct(m_pwindow);
      //
      //         //if (!estatus)
      //         //{
      //
      //         //   return estatus;
      //
      //         //}
      //
      //         if (!system()->m_paurasystem->m_pwindowMain)
      //         {
      //
      //            system()->m_paurasystem->m_pwindowMain = m_pwindow;
      //
      //         }
      //
      //      }
      //
      //      //auto estatus =
      //
      //      m_pwindow->create_window(this);
      //
      //      //if (!estatus)
      //      //{
      //
      //      //   return estatus;
      //
      //      //}
      //
      //      //return true;

      ::pointer<::user::system>pusersystem;

      if (m_puserinteraction->m_pusersystem)
      {

         pusersystem = m_puserinteraction->m_pusersystem;

      }
      else
      {

         pusersystem = __allocate< ::user::system >();

      }

      //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || is_string_ok(pusersystem->m_createstruct.lpszName));
      //
      if (!m_puserinteraction->pre_create_window(pusersystem))
      {

         //return false;

         throw ::exception(error_failed);

      }

      m_puserinteraction->m_pthreadUserInteraction = ::get_task();

      //m_pthreadUserImpl = m_puserinteraction->m_pthreadUserInteraction;

      install_message_routing(m_puserinteraction);

      bool bOk = true;

      //      if(pusersystem->m_createstruct.hwndParent == (oswindow) MESSAGE_WINDOW_PARENT)
      //      {
      //
      //         auto pwindowing = m_pwindowwindowing();
      //
      //         m_oswindow = pwindowing->new_message_window(this);
      //
      //         m_puserinteraction->m_bMessageWindow = true;
      //
      //         //send_message(e_message_create, 0, (LPARAM) &cs);
      //
      //      }
      //      else
      {

         m_puserinteraction->m_bMessageWindow = false;

         //auto pwindowing = windowing();
         user_send([&]()
            {

               auto pwindowing = windowing();

               pwindowing->new_window(this);

               if (m_pwindow)
               {

                  informationf("window created");

               }
               else
               {

                  informationf("window not created");

               }

            });

      }

      //      if(bOk)
      //      {
      //
      //         m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);
      //
      //         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;
      //
      //      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   //void interaction_impl::create_host(::user::interaction * puserinteraction, enum_parallelization eparallelization)
   void interaction_impl::create_host(::user::interaction * puserinteraction)
   {

      m_puserinteraction = puserinteraction;

#if REFERENCING_DEBUGGING

      ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });

#endif

      m_puserinteraction->m_pprimitiveimpl = this;

#if REFERENCING_DEBUGGING

      ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });

#endif

      m_puserinteraction->m_pinteractionimpl = this;

#if !defined(UNIVERSAL_WINDOWS) && !defined(WINDOWS_DESKTOP)

      m_puserinteraction->m_ewindowflag |= e_window_flag_postpone_visual_update;

#endif

//      auto pusersystem = puserinteraction->m_pusersystem;
//
//      if(pusersystem)
//      {
//
//         add(pusersystem->m_prequest);
//
//         for(auto & poutputpurpose : pusersystem->m_graphicsoutputpurposea)
//         {
//
//            information() << "adding graphical output_purpose from user::system";
//
//            add(poutputpurpose);
//
//         }
//
//      }

      bool bNewOwnThread = true;

      bool bProdevianThread = true;

      //if (m_puserinteraction->GetStyle() & WS_CHILD)
      //{

      //   // if child, uses parent window thread,

      //   bNewOwnThread = false;

      //   bProdevianThread = false;

      //}

      if (m_puserinteraction->m_bMessageWindow)
      {

         // except if "message"-only-window, in which casen it will have own thread

         bNewOwnThread = true;

         bProdevianThread = false;

      }

      if (m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window)
      {

         if (m_puserinteraction->m_puserinteractionOwner)
         {

            auto pthread = m_puserinteraction->m_puserinteractionOwner->m_pthreadUserInteraction;

            m_puserinteraction->m_pthreadUserInteraction = pthread;

            m_puserthread = pthread.get();

         }

         // all except if satellite window it will use calling thread/parent window thread

         bNewOwnThread = false;

      }

      if (!m_puserinteraction->is_graphical())
      {

         bProdevianThread = false;

      }

      //m_puserinteraction->place(rectangle_i32_dimension(
      //                      pusersystem->m_createstruct.x(),
      //                      pusersystem->m_createstruct.y(),
      //                      pusersystem->m_createstruct.cx(),
      //                      pusersystem->m_createstruct.cy()));

      //auto psynca = __allocate< synchronization_array >();

      //::pointer<manual_reset_event>peventStartedUser;

      //::pointer<manual_reset_event>peventStartedProdevian;

      ::pointer<::user::thread>puserthread;

      if (bNewOwnThread)
      {

         puserthread = __create_new<::user::thread>();

         m_puserthread = puserthread;

         auto papp = get_app();

         if (::is_set(papp))
         {

            papp->add_task(m_puserthread);

         }

         m_puserthread->initialize_user_thread(this);

         m_puserinteraction->m_pthreadUserInteraction = m_puserthread;

         //peventStartedUser = __allocate< manual_reset_event >();

         //m_puserthread->m_peventStarted = peventStartedUser;

      }

#if REFERENCING_DEBUGGING

      ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });

#endif

      m_puserthread->add_task(m_puserinteraction);

      ::pointer<::user::graphics_thread>pgraphicsthread;

      if (bProdevianThread && m_puserinteraction->is_graphical())
      {

         pgraphicsthread = __create_new < ::user::graphics_thread >();

         m_pgraphicsthread = pgraphicsthread;

         //auto pusersystem = m_puserinteraction->m_pusersystem;

         //if (pusersystem)
         //{

         //   auto prequest = pusersystem->m_prequest;

         //   if (prequest)
         //   {

         //      information() << "pgraphicsthread->m_eventReady.ResetEvent();";

         //      pgraphicsthread->m_eventReady.ResetEvent();

         //      prequest->m_procedureaOnFinishRequest.add(
         //         [this, pgraphicsthread]()
         //         {

         //            information() << "pgraphicsthread->m_eventReady.SetEvent();";

         //            pgraphicsthread->m_eventReady.SetEvent();

         //         });

         //   }

         //}

         m_pgraphicsthread->initialize_graphics_thread(this);

         m_puserinteraction->add_task(m_pgraphicsthread);

         m_pgraphicsthread->m_puserthread = m_puserthread;

      }

      if (bNewOwnThread)
      {

         information() << "interaction_impl::create_host user thread branch";

         //if (!m_puserthread->begin_synch())
         //m_puserthread->branch(eparallelization);
        // m_puserthread->branch(e_parallelization_synchronous);
         m_puserthread->branch(e_parallelization_synchronous);
         //{

         //   __release(m_pgraphicsthread);

         //   __release(m_puserthread);

         //   m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);

         //   return false;

         //}

//         psynca->add(peventStartedUser);
//
//         auto proutine = __routine([this, psynca]()
//            {
//
//               if (!m_puserinteraction ||
//                  //(m_puserthread->m_bCreateNativeWindowOnInteractionThread
//                     //&&
//                  !m_puserinteraction->is_window())
//                  //)
//               {
//
//                  return;
//
//               }
//
//               if (m_puserthread->m_result.failed())
//               {
//
//                  if (m_puserinteraction)
//                  {
//
//                     m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);
//
//                  }
//
//                  __release(m_pgraphicsthread);
//
//                  __release(m_puserthread);
//
//                  return;
//
//               }
//
//               //peventStartedUser.release();
//
//               if (::is_set(m_pgraphicsthread))
//               {
//
//                  if (m_pgraphicsthread->m_result.failed())
//                  {
//
//                     if (m_puserinteraction)
//                     {
//
//                        m_puserinteraction->__release(m_puserinteraction->m_pthreadUserInteraction);
//
//                     }
//
//                     __release(m_pgraphicsthread);
//
//                     __release(m_puserthread);
//
//                     return;
//
//                  }
//
//                 // peventStartedProdevian.release();
//
//               }
//
//            });

         //if (pusersystem->m_procedureSuccess)
         //{

         //   fork([psynca, proutine, pusersystem]()
         //   {

         //      psynca->wait();

         //      (*proutine)();

         //      pusersystem->m_procedureSuccess();

         //   });

         //}
         //else
         //{

            ///psynca->wait();

         //   (*proutine)();

         //}

      }
      else
      {

         //psynca->wait(true, one_minute());

         //if (::is_set(m_pgraphicsthread))
         //{

           // peventStartedProdevian.release();

         //}

         //operating_system_create_host(eparallelization);

         operating_system_create_host();

         ////if (!native_create_host())
         //{

         //   return false;

         //}

      }

      //if (m_puserthread && !m_puserthread->m_bCreateNativeWindowOnInteractionThread)
      //{

      //   send_message(e_message_create, 0, (lparam)&pusersystem);

      //   //m_puserinteraction->set_dim(pusersystem->m_createstruct.x(), pusersystem->m_createstruct.cy(), pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy());

      //   send_message(e_message_size, 0, MAKELPARAM(pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy()));

      //   m_puserinteraction->increment_reference_count(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);

      //   m_puserinteraction->m_ewindowflag |= ::e_window_flag_is_window;

      //   m_puserinteraction->m_ewindowflag |= ::e_window_flag_window_created;

      //}

      //return true;

   }


   ::color::color interaction_impl::screen_pixel(int x, int y) const
   {

      if (::is_null(m_pgraphicsgraphics))
      {

         return color::transparent;

      }

      auto origin = m_puserinteraction->const_layout().window().origin();

      //information() << "screen_pixel window().origin() : " << origin;

      return m_pgraphicsgraphics->get_screen_item()->m_pimage2->pixel(x - origin.x(), y - origin.y());

   }


   //void interaction_impl::native_create_window()
   //{
   //   return false;
   //}


//   void interaction_impl::create_host(::user::interaction * puserinteraction)
//   {
//
//      m_puserinteraction = puserinteraction;
//      // can't use for desktop or pop-up windows (use create_window_ex instead)
//      //ASSERT(puiParent != nullptr);
//      //ASSERT((uStyle & WS_POPUP) == 0);
//
//      //auto pusersystem = __allocate< ::user::system >();
//
//      //pusersystem->m_createstruct.dwExStyle = 0;
//
////#ifdef WINDOWS
////
////      wstring wstrClassName(pszClassName);
////      pusersystem->m_createstruct.lpszClass = wstrClassName;
////      wstring wstrWindowName(pszWindowName);
////      pusersystem->m_createstruct.lpszName = wstrWindowName;
////
////#else
////
////      pusersystem->m_createstruct.lpszClass = pszClassName;
////      pusersystem->m_createstruct.lpszName = pszWindowName;
////
////#endif
//
//      //pusersystem->m_createstruct.style = uStyle | WS_CHILD;
//      //pusersystem->m_createstruct.x() = rectangle.left();
//      //pusersystem->m_createstruct.y() = rectangle.top();
//      //pusersystem->m_createstruct.cx() = rectangle.width();
//      //pusersystem->m_createstruct.cy() = rectangle.height();
//      //pusersystem->m_createstruct.hwndParent = puiParent->get_safe_handle();
//      //pusersystem->m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (LPVOID)pcreate;
//
//      return native_create_window();
//
//   }


   void interaction_impl::prio_install_message_routing(::channel * pchannel)
   {

      ::user::primitive_impl::prio_install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &interaction_impl::_001OnPrioCreate);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::on_prio_message_set_focus);

   }


   void interaction_impl::last_install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_create, pchannel, this, &interaction_impl::on_message_create);
      MESSAGE_LINK(e_message_pos_create, pchannel, this, &interaction_impl::on_message_pos_create);

      ::user::primitive_impl::last_install_message_routing(pchannel);

      if (!m_puserinteraction->m_bMessageWindow)
      {

         //MESSAGE_LINK(e_message_redraw, pchannel, this, &interaction_impl::_001OnRedraw);
         //MESSAGE_LINK(e_message_apply_visual, pchannel, this, &interaction_impl::_001OnApplyVisual);


         //#ifndef LINUX
         MESSAGE_LINK(e_message_reposition, pchannel, this, &interaction_impl::on_message_reposition);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction_impl::on_message_size);
         //MESSAGE_LINK(e_message_window_position_changed, pchannel, this, &interaction_impl::on_message_window_position_changed);
         //#endif

         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction_impl::on_message_show_window);
         MESSAGE_LINK(e_message_kill_focus, pchannel, this, &interaction_impl::on_message_kill_focus);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &interaction_impl::on_message_set_focus);

      }

      MESSAGE_LINK(e_message_destroy_window, pchannel, this, &interaction_impl::_001OnDestroyWindow);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &interaction_impl::on_message_destroy);

   }


   void interaction_impl::_000OnMouseLeave(::message::message * pmessage)
   {

      if (m_bDestroyImplOnly)
      {

         return;

      }

      //m_puserinteraction->m_pitemHover = nullptr;

#ifdef WINDOWS_DESKTOP
      if (!m_bTransparentMouseEvents)
#endif
      {

         ::point_i32 pointInvalid; // For long future hope still : Invalid

         minimum(pointInvalid.x());
         minimum(pointInvalid.y());

         _on_mouse_move_step(pointInvalid);

         //::pointer<::user::interaction>pinteraction;

         //::rectangle_i32 rectangleUi;

         //auto psession = get_session();

         //auto puser = psession->user();

         //auto pwindowing = puser->windowing();

         //auto pointCursor = pwindowing->get_cursor_position();

         //::user::interaction_array uia;

         //{

         //   _synchronous_lock synchronouslock(this->synchronization());

         //   uia = m_uiptraMouseHover;

         //   m_uiptraMouseHover.erase_all();

         //}

         //for(auto & pinteraction : uia.interactiona())
         //{

         //   try
         //   {

         //      pinteraction->send_message(e_message_mouse_leave);

         //   }
         //   catch (...)
         //   {

         //   }

         //}

      }

   }


   //   void interaction_impl::_001OnTriggerMouseInside()
   //   {
   //
   //      //m_puserinteraction->m_bMouseHover = true;
   //
   //   }


      //void interaction_impl::_008OnMouse(::message::mouse * pmouse)
      //{

      //   if(!m_puserinteraction)
      //   {

      //      return;

      //   }

      //   bool bPointInside;

      //   bPointInside = m_puserinteraction->_001IsPointInside(pmouse->m_point);

      //   if (!bPointInside)
      //   {

      //      if (pmouse->userinteraction() == m_puserinteraction)
      //      {

      //         bPointInside = true;

      //      }

      //   }

      //   if (pmouse->m_atom == e_message_left_button_up)
      //   {

      //      ::acme::get()->platform()->informationf("lbutton_up");

      //   }

      //   if(pmouse->m_atom == ::e_message_left_button_down)
      //   {

      //      on_configuration_change(m_puserinteraction);

      //   }

      //   {

      //      ::user::interaction_array uia;

      //      {

      //         _synchronous_lock synchronouslock(this->synchronization());

      //         for(auto & pinteraction : m_uiptraMouseHover)
      //         {

      //            try
      //            {

      //               if (!pinteraction->_001IsPointInside(pmouse->m_point))
      //               {

      //                  uia.add_interaction(pinteraction);

      //               }

      //            }
      //            catch(...)
      //            {

      //            }

      //         }

      //         ::papaya::array::erase_array(m_uiptraMouseHover, uia.interactiona());

      //      }

      //      for(auto & pinteraction : uia.interactiona())
      //      {

      //         pinteraction->send_message(e_message_mouse_leave);

      //      }

      //   }

      //   auto psession = get_session();

      //   if (!m_puserinteraction->m_bMouseHover && bPointInside)
      //   {

      //      m_puserinteraction->_001OnTriggerMouseInside();

      //   }

      //   if(m_pwindow->has_capture())
      //   {

      //      if (pmouse->m_atom == e_message_left_button_up)
      //      {

      //         ::acme::get()->platform()->informationf("lbutton_up");

      //      }

      //      ::user::interaction * puiCapture = m_puserinteractionCapture;

      //      if (puiCapture == nullptr)
      //      {

      //         puiCapture = m_puserinteraction;

      //      }

      //      try
      //      {

      //         puiCapture->message_handler(pmouse);

      //      }
      //      catch (...)
      //      {

      //      }

      //      return;

      //   }

      //   if (m_puserinteraction != nullptr)
      //   {


      //      if (pmouse->m_atom == e_message_left_button_up)
      //      {

      //         ::acme::get()->platform()->informationf("lbutton_up");

      //      }

      //      //_synchronous_lock synchronouslock(mutex_children());

      //      auto puserinteraction = m_puserinteraction->child_from_point(pmouse->m_point);

      //      if (!puserinteraction)
      //      {

      //         puserinteraction = m_puserinteraction;

      //      }

      //      puserinteraction->message_handler(pmouse);



      //   }

      //   if (pmouse->m_bRet)
      //   {

      //      return;

      //   }

      //}


   void interaction_impl::add(::graphics::output_purpose * pgraphicaloutputpurpose)
   {

      if(::is_null(pgraphicaloutputpurpose))
      {

         return;

      }

      if(pgraphicaloutputpurpose->m_egraphicsoutputpurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      bool bHadNoInterest = !has_graphical_output_purpose();

      bool bAdded = m_graphicaloutputpurposea.add_unique(pgraphicaloutputpurpose);

      if (bAdded && bHadNoInterest)
      {

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::erase(::graphics::output_purpose * pgraphicaloutputpurpose)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_graphicaloutputpurposea.erase(pgraphicaloutputpurpose);

   }


   void interaction_impl::add_graphical_output_purpose(::particle * pparticleGraphicalOutputPurposeOriginator, ::graphics::enum_output_purpose epurpose)
   {

      if(::is_null(pparticleGraphicalOutputPurposeOriginator))
      {

         return;

      }

      if(epurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      auto poutputpurpose = __allocate< ::graphics::output_purpose >(pparticleGraphicalOutputPurposeOriginator, epurpose);

      bool bHadGraphicalOutputPurpose = m_puserinteraction->has_graphical_output_purpose();

      this->add(poutputpurpose);

      bool bHasGraphicalOutputPurpose = m_puserinteraction->has_graphical_output_purpose();

      if (bHasGraphicalOutputPurpose && !bHadGraphicalOutputPurpose)
      {

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

      }

   }


   void interaction_impl::erase_graphical_output_purpose(::particle * pparticleGraphicalOutputPurposeOriginator)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_graphicaloutputpurposea.predicate_erase([pparticleGraphicalOutputPurposeOriginator](auto ppurpose)
                                                {

         return ppurpose->m_pparticleGraphicalOutputPurposeOriginator == pparticleGraphicalOutputPurposeOriginator;

                                                });

   }


   bool interaction_impl::does_particle_has_fps_purpose(const ::particle * pparticleGraphicalOutputPurposeOriginator) const
   {

      _synchronous_lock synchronouslock(this->synchronization());

      return m_graphicaloutputpurposea.predicate_contains([pparticleGraphicalOutputPurposeOriginator](auto ppurpose)
                                                          {

                                                             return ppurpose->m_pparticleGraphicalOutputPurposeOriginator == pparticleGraphicalOutputPurposeOriginator
                                                                    && ppurpose->m_egraphicsoutputpurpose &
                                                                       ::graphics::e_output_purpose_fps;

                                                          });

   }


   void interaction_impl::mouse_hover_add(::user::interaction * pinterface)
   {

      if (pinterface == nullptr)
      {

         return;

      }

      bool bWasEmpty = false;

      {

         _synchronous_lock synchronouslock(this->synchronization());

         bWasEmpty = m_userinteractionaMouseHover.is_empty();

         m_userinteractionaMouseHover.add_unique(pinterface);

         if (bWasEmpty)
         {

            track_mouse_hover();

         }

      }

   }


   void interaction_impl::track_mouse_hover()
   {

      m_pwindow->track_mouse_hover();

   }


   void interaction_impl::track_mouse_leave()
   {

      //__defer_fork(MouseLeave);

   }


   void interaction_impl::_on_mouse_move_step(const ::point_i32 & pointCursor, bool bMouseLeave)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (::index i = 0; i < m_userinteractionaMouseHover.get_count(); )
      {

         auto pinteraction = m_userinteractionaMouseHover[i];

         //if (pinteraction == m_puserinteractionMouseCapture)
         //{

           // i++;

         //}
         if (!bMouseLeave && pinteraction->_001IsPointInsideInline(pointCursor))
         {

            i++;

         }
         else
         {



            m_userinteractionaMouseHover.erase_at(i);

            ///pinteraction->m_bTrackMouseLeave = false;

            synchronouslock.unlock();

            pinteraction->message_handler(e_message_mouse_leave);

            synchronouslock._lock();

         }

      }

   }


   //   void interaction_impl::mouse_hover_step(const __status < ::point_i32 > & statusPointCursor)
   //   {
   //
   //      decltype(m_uiptraMouseHover) uia;
   //
   //      {
   //
   //         _synchronous_lock synchronouslock(this->synchronization());
   //
   //         if (statusPointCursor.m_estatus != success)
   //         {
   //
   //            uia = ::transfer(m_uiptraMouseHover);
   //
   //         }
   //         else
   //         {
   //
   //            for (::index i = 0; i < m_uiptraMouseHover.get_count();)
   //            {
   //
   //               auto pinteraction = m_uiptraMouseHover[i];
   //
   //               try
   //               {
   //
   //                  if (pinteraction->_001IsPointInside(statusPointCursor))
   //                  {
   //
   //                     i++;
   //
   //                  }
   //                  else
   //                  {
   //
   //                     uia.add(pinteraction);
   //
   //                     m_uiptraMouseHover.erase_at(i);
   //
   //                  }
   //
   //               }
   //               catch (...)
   //               {
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      for (auto & pinteraction : uia)
   //      {
   //
   //         pinteraction->send_message((enum_message)e_message_mouse_leave);
   //
   //      }
   //
   //   }


   bool interaction_impl::mouse_hover_erase(::user::interaction * pinterface)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      return m_userinteractionaMouseHover.erase(pinterface) >= 0;

   }


   void interaction_impl::_task_transparent_mouse_event()
   {

      m_pwindow->_task_transparent_mouse_event();

   }


   void interaction_impl::_001OnCaptureChanged(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      m_puserinteractionMouseCapture.release();

   }


   bool interaction_impl::__windows_message_bypass(::windowing::window * pwindow, ::u32 message, wparam wparam, lparam lparam, lresult & lresult)
   {

      return false;

   }


   void interaction_impl::install_message_routing(::channel * pchannel)
   {

      last_install_message_routing(pchannel);

      ::user::primitive_impl::install_message_routing(pchannel);

      m_puserinteraction->install_message_routing(pchannel);

      //#ifdef WINDOWS

      if (!m_puserinteraction->m_bMessageWindow)
      {

         MESSAGE_LINK(e_message_capture_changed, pchannel, this, &interaction_impl::_001OnCaptureChanged);

      }

      //#endif

      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &interaction_impl::on_message_destroy);

      prio_install_message_routing(pchannel);

   }


   void interaction_impl::default_message_handler(::message::message * pmessage)
   {

      m_pwindow->default_message_handler(pmessage);

   }


   void interaction_impl::on_message_destroy(::message::message * pmessage)
   {

      if (m_puserinteraction && ::type(m_puserinteraction).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

      m_pgraphicsgraphics.defer_destroy();

      UNREFERENCED_PARAMETER(pmessage);

      {

         auto psync = synchronization();

         _synchronous_lock synchronouslock(this->synchronization());

         m_userinteractionaMouseHover.erase_all();

      }


   }



   void interaction_impl::post_non_client_destroy()
   {

      string strType = ::type(m_puserinteraction).name();

      //      if (strType.contains("main_frame"))
      //      {
      //
      //         informationf("main_frame");
      //
      //      }

      auto pwindowthread = m_puserthread;

      ::user::primitive_impl::post_non_client_destroy();

      detach_window();

      m_puserinteraction.release();

      if (::is_set(pwindowthread))
      {

         pwindowthread->m_pimpl.release();

      }

      m_pwindow.release();

      m_puserinteractionKeyboardFocus.release();

      m_puserinteractionKeyboardFocusRequest.release();

      m_puserinteractionKeyboardGainingFocusIfAny.release();

      m_puserinteractionMouseCapture.release();

      m_puserinteractionToKillKeyboardFocus.release();

      m_puserthread.release();

      m_pgraphicsgraphics.release();

      m_pgraphicsthread.release();

      m_pwindowing.release();

      m_graphicaloutputpurposea.clear();

      if (m_pthreadMouseLeave)
      {
         m_pthreadMouseLeave->set_finish();

      }
      //m_pthreadMouseLeave.release();

      m_messagelist.clear();

      m_pelementSoftwareKeyboard.release();

      m_pdraw2dgraphics.release();

   }


   void interaction_impl::on_final_release()
   {

   }



   //   void interaction_impl::assert_ok() const
   //   {
   //
   //      ::user::primitive_impl::assert_ok();
   //
   //   }
   //
   //
   //   void interaction_impl::dump(dump_context & dumpcontext) const
   //   {
   //
   //      ::user::primitive_impl::dump(dumpcontext);
   //
   //   }


   void interaction_impl::destroy_impl_only()
   {

      if (!m_bDestroyImplOnly)
      {

         m_bDestroyImplOnly = true;

         m_pgraphicsthread->set_finish();

         if (::is_set(m_puserinteraction))
         {

            information() << ::type(m_puserinteraction).name() << "::destroy_impl_only";

            m_puserinteraction->transfer_handler(m_dispatchermapNormal, this, false);
            m_puserinteraction->transfer_handler(m_dispatchermapProbe, this, true);

         }

         m_puserinteraction->m_pprimitiveimpl.release();

         m_puserinteraction->m_pinteractionimpl.release();

         m_puserinteraction.release();

         auto pwindow = window();

         message_queue_post(pwindow, e_message_destroy_window, 0, 0);

         //return true;

      }
      else if (m_bUserImplCreated)
      {

         if (m_puserinteraction)
         {

            information() << ::type(m_puserinteraction).name() << "::destroy_impl_only ( 2)";

         }

         m_bUserImplCreated = false;

         //return ::DestroyWindow((HWND)get_handle());
         //return false;

      }
      else
      {

         //return false;

      }

   }


   void interaction_impl::start_destroying_window()
   {

      if (has_destroying_flag())
      {

         //return true;

         return;

      }

      if (!has_destroying_flag())
      {

         if (m_pgraphicsthread && m_pgraphicsthread->task_active())
         {

            m_pgraphicsthread->set_finish();

         }

         set_destroying_flag();

         m_puserinteraction->post_message(e_message_destroy_window);

         return;

      }

      //bool bResult = 
      ::user::primitive_impl::start_destroying_window();

      //return bResult;

   }


   void interaction_impl::destroy_window()
   {

      auto strType = ::type(m_puserinteraction).name();

      if (strType.contains("main_frame"))
      {

         informationf("main_frame user::interaction_impl::destroy_window");

      }

      if (!m_puserinteraction->has_destroying_flag())
      {

         m_puserinteraction->set_flag(e_flag_destroying);

      }

      //m_puserinteraction->m_ewindowflag -= e_window_flag_window_created;

      //::destroy_window(get_handle());

      m_pwindow->destroy_window();

   }


   //void interaction_impl::default_window_procedure(::message::message * pmessage)
   //{

   //   UNREFERENCED_PARAMETER(pmessage);

   //}


   void interaction_impl::pre_translate_message(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

   }


   //void interaction_impl::GetWindowText(string & rectangleString)
   //{

   //   UNREFERENCED_PARAMETER(rectangleString);

   //   throw ::interface_only();

   //}


   //i32 interaction_impl::GetChildByIdText(i32 nID,string & rectangleString) const
   //{

   //   UNREFERENCED_PARAMETER(nID);

   //   UNREFERENCED_PARAMETER(rectangleString);

   //   throw ::interface_only();

   //   return 0;

   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   void interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
//
//   {
//
//      UNREFERENCED_PARAMETER(puserinteractionpl);
//
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   void interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
//   {
//
//      UNREFERENCED_PARAMETER(puserinteractionpl);
//
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//#endif


   //void interaction_impl::PrepareForHelp()
   //{

   //   throw ::interface_only();

   //}


   void interaction_impl::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      UNREFERENCED_PARAMETER(pcommand);

      throw ::interface_only();

   }


   void interaction_impl::_002OnDraw(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

   }


   void interaction_impl::message_handler(::message::message * pmessage)
   {

      bool bKeyMessage = false;

      ::message::key * pkey = nullptr;

      if(::is_null(m_puserinteraction))
      {

         return;

      }

      if (m_puserinteraction->pre_message_handler(pkey, bKeyMessage, pmessage))
      {

         information() << "returning on pre_message_handler";

         return;

      }

      if (pmessage->m_atom == e_message_timer)
      {

         //m_pthread->step_timer();

      }
      else if (pmessage->m_atom == e_message_left_button_down)
      {

         informationf("linux::interaction_impl::e_message_left_button_down");

      }
      else if (pmessage->m_atom == e_message_left_button_up)
      {

         informationf("linux::interaction_impl::e_message_left_button_up");

      }
      else if (pmessage->m_atom == e_message_mouse_move)
      {

         //g_iMouseMove++;

         //informationf("interaction_impl::message_handler e_message_mouse_move");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if (pmessage->m_atom == e_message_paint)
      {

      }
      else if (pmessage->m_atom == e_message_left_button_up)
      {

         informationf("e_message_left_button_up (0)");

      }

      //      if(::is_set(m_puserinteraction))
      //      {
      //
      //         m_puserinteraction->pre_translate_message(pmessage);
      //
      //      }

      //      if(tickDebugmessage_handlerTime.timeout(1))
      //      {
      //
      //         iDebugmessage_handlerTime = 0;
      //
      //      }
      //      else
      //      {
      //
      //         if(iDebugmessage_handlerTime > 20)
      //         {
      //
      //            ::acme::get()->platform()->informationf("interaction_impl::message handler flooded?\n");
      //
      //         }
      //         else
      //         {
      //
      //            iDebugmessage_handlerTime++;
      //
      //         }
      //
      //      }

      if (m_puserinteraction != nullptr)
      {

         if (m_puserinteraction->layout().is_moving())
         {
            //informationf("moving: skip pre translate message");
         }
         else if (m_puserinteraction->layout().is_sizing())
         {
            //informationf("sizing: skip pre translate message");
         }
         else
         {

            //m_puserinteraction->pre_translate_message(pmessage);

            //if (pmessage->m_bRet)
            //{

              // return;

            //}

            //pmessage->m_uiMessageFlags |= 1;

         }

      }



      //      if(bKeyMessage)
      //      {
      //
      //         auto psession = get_session();
      //
      //         auto puser = psession->user();
      //
      //         auto pwindowing = puser->windowing();
      //
      //         ::pointer<::message::key>pkey = pmessage;
      //
      //         //pwindowing->set(pkey, get_oswindow(), m_pwindow, pkey->m_atom, pkey->m_wparam, pkey->m_lparam);
      //
      ////         if(pmessage->m_atom == e_message_key_down)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, true);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      ////         else if(pmessage->m_atom == e_message_key_up)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, false);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      //
      //      }

      pmessage->m_lresult = 0;

      if (pmessage->m_atom == e_message_mouse_leave)
      {

         _000OnMouseLeave(pmessage);

         return;

      }

      if (pmessage->m_atom == e_message_left_button_down ||
         pmessage->m_atom == e_message_left_button_up ||
         pmessage->m_atom == e_message_middle_button_down ||
         pmessage->m_atom == e_message_middle_button_up ||
         pmessage->m_atom == e_message_right_button_down ||
         pmessage->m_atom == e_message_right_button_up ||
         pmessage->m_atom == e_message_left_button_double_click ||
         pmessage->m_atom == e_message_mouse_move ||
         pmessage->m_atom == e_message_mouse_wheel)
      {

         ::pointer<::message::mouse>pmouse = pmessage;

         //information() << "msghdl pwnd : " << (::iptr) pmouse->m_pwindow.m_p;

         on_mouse_message(pmouse);

         return;

      }
      /*      else if(pmessage->m_atom == e_message_key_down ||
                    pmessage->m_atom == e_message_key_up ||
                    pmessage->m_atom == e_message_char)*/
      else if (bKeyMessage)
      {

         if (::is_set(pkey))
         {

            information() << "key message";

            ::pointer<::user::interaction>puiKeyboardFocus = m_puserinteractionKeyboardFocus;

            if (puiKeyboardFocus)
            {

               information() << "key message control with keyboard focus : " << ::string(::type(puiKeyboardFocus.m_p));

               puiKeyboardFocus->route_message(pkey);

            }
            else
            {

               m_puserinteraction->route_message(pkey);

            }

         }

         if (pmessage->m_bRet)
         {

            return;

         }

         default_window_procedure(pmessage);

         return;

      }

      if (pmessage->m_atom == e_message_subject)
      {

         if (m_puserinteraction != nullptr)
         {

            m_puserinteraction->handle((::topic *)pmessage->m_lparam.m_lparam, nullptr);

         }
         //         else
         //         {
         //
         //            on_control_event((::user::control_event *) pmessage->m_lparam.m_lparam);
         //
         //         }

         return;

      }

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->route_message(pmessage);

      }
      else
      {

         route_message(pmessage);

      }

      if (!pmessage->m_bRet)
      {
         
         default_window_procedure(pmessage);
         
      }
      
      if(pmessage->m_atom == e_message_create)
      {
         
         //if (m_puserinteraction->m_procedureOnAfterCreate)
         //{

         //   m_puserinteraction->post_message(e_message_pos_create);

         //}

//         if(has_screen_output_purpose())
//         {
//
//            m_puserinteraction->set_need_layout();
//
//            m_puserinteraction->set_need_redraw();
//
//            m_puserinteraction->post_redraw();
//
//         }

         //if(m_puserinteraction->m_setneedredrawa.has_element())
         //{

         //   m_puserinteraction->post_redraw();

         //}
         
      }

   }


   void interaction_impl::_message_handler(::message::message * pmessage)
   {

      if (m_puserinteraction)
      {

         m_bDestroyImplOnly ? route_message(pmessage) : m_puserinteraction.m_p->route_message(pmessage);

      }

   }


   void interaction_impl::default_window_procedure(::message::message * pmessage)
   {

   }


   bool interaction_impl::on_mouse_message(::message::mouse * pmouse)
   {

      pmouse->m_pwindow->m_pointCursor2 = pmouse->m_pointHost;

      if (pmouse->m_atom == e_message_left_button_double_click)
      {

         information() << "e_message_left_button_double_click";

      }
      else if (pmouse->m_atom == e_message_left_button_down)
      {

         information() << "e_message_left_button_down";

      }
      else if (pmouse->m_atom == e_message_mouse_move)
      {

         //information() << "e_message_mouse_move : " << pmouse->m_pointAbsolute;

      }
      else if (pmouse->m_atom == e_message_left_button_up)
      {

         information() << "e_message_left_button_up";

      }

      if (::is_set(m_puserinteraction) && !m_puserinteraction->m_bUserElementOk)
      {

         return false;

      }

      auto psession = get_session();

      //if (pmouse)
      //{

      if (psession != nullptr)
      {

         psession->on_ui_mouse_message(pmouse);

         psession->m_pointCursor = pmouse->m_pointAbsolute;

      }

      //         if(m_puserinteraction != nullptr && m_puserinteraction->get_session()  != nullptr && m_puserinteraction->get_session() != get_session())
      //         {
      //
      //            auto psystem = system();
      //
      //            auto psession = psystem->node();
      //
      //            psession->m_pointCursor = pmouse->m_point;
      //
      //         }


      //   if (m_bTranslateMouseMessageCursor && !pmouse->m_bTranslated)
      //   {
      //      pmouse->m_bTranslated = true;
      //      ::rectangle_i32 rectWindow;
      //      //            if(m_bScreenRelativeMouseMessagePosition)
      //      //            {
      //      //
      //      //               INFO("Screen Relative Mouse Message Position");
      //      //
      //      //               ::rectangle_i32 rectWindow32;
      //      //
      //      //               ::window_rectangle((oswindow) get_handle(), &rectWindow32);
      //      //
      //      //               ::copy(rectWindow, rectWindow32);
      //      //
      //      //            }
      //      //            else
      //      {
      //         m_puserinteraction->window_rectangle(rectWindow);
      //      }

      //      //auto pwindowing = windowing();

      //      //auto pdisplay = pwindowing->display();

      //      //if (pdisplay->get_monitor_count() > 0)
      //      //{

      //      //   ::rectangle_i32 rcMonitor;

      //      //   pdisplay->get_monitor_rectangle(0, rcMonitor);

      //      //   if (rectWindow.left() >= rcMonitor.left())
      //      //   {

      //      //      pmouse->m_point.x() += (::i32)rcMonitor.left();

      //      //   }

      //      //   if (rectWindow.top() >= rcMonitor.top())
      //      //   {

      //      //      //pmouse->m_point.y() += (::i32)rectWindow.top();
      //      //      pmouse->m_point.y() += (::i32)rcMonitor.top();

      //      //   }

      //      //}
      //      //else
      //      {

      //         if (rectWindow.left() >= 0)
      //         {

      //            pmouse->m_point.x() += (::i32)rectWindow.left();

      //         }

      //         if (rectWindow.top() >= 0)
      //         {

      //            pmouse->m_point.y() += (::i32)rectWindow.top();

      //         }

      //      }

      //   }

      //}

      auto pwindowing = windowing();

      pwindowing->set(pmouse, oswindow(), m_pwindow, pmouse->m_atom, pmouse->m_wparam, pmouse->m_lparam);

      //information() << "omousemsg pwnd : " << (::iptr) pmouse->m_pwindow.m_p;

      if (pmouse->m_atom == e_message_mouse_move)
      {

         // We are at the message handler routine.
         // mouse messages originated from message handler and that are mouse transfer events should end up with the correct cursor.
         // So the routine starts by setting to the default cursor,
         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
         // handler has set it to another one.

         m_puserinteraction->m_pinteractionimpl->_on_mouse_move_step(pmouse->m_pointHost);

         //information() << "e_message_mouse_move (2): " << pmouse->m_pointAbsolute;

      }



      //_008OnMouse(pmouse);

      ::user::interaction * puserinteractionMouse = nullptr;

      //if (m_puserinteractionMouseCapture)
      //{

      //   //            if(g_puserinteractionMouseCapture123 == nullptr)
      //   //            {
      //   //
      //   //               g_puserinteractionMouseCapture123 = m_puserinteractionCapture;
      //   //
      //   //            }
      //   //            else if(g_puserinteractionMouseCapture123 != m_puserinteractionCapture)
      //   //            {
      //   //
      //   //               informationf("different capture (1)");
      //   //
      //   //            }

      //   puserinteractionMouse = m_puserinteractionMouseCapture;

      //}

      //         if(g_puserinteractionMouseCapture123 != nullptr)
      //         {
      //
      //            if(g_puserinteractionMouseCapture123 != puserinteractionMouse)
      //            {
      //
      //               informationf("different capture (2)");
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //
      //
      //         }

      if (pmouse->m_atom == e_message_left_button_down)
      {


         informationf("left_button_down (A)");

      }

      pmouse->m_puserinteractionHit = m_puserinteraction->child_from_point(pmouse->m_pointHost);

      if (!puserinteractionMouse)
      {

         puserinteractionMouse = pmouse->m_puserinteractionHit;

      }

      if (pmouse->m_atom == e_message_left_button_down)
      {


         informationf("left_button_down");

      }
      else if (pmouse->m_atom == e_message_left_button_up)
      {


         informationf("left_button_up");

      }

      if (m_puserinteractionMouseCapture)
      {

         //::string strType = ::type(m_puserinteractionMouseCapture).name();

         //information() << "on_mouse_message CAPTURED to object of type : " << strType;

         //information() << "omousemsg pwnd (B) : " << (::iptr) pmouse->m_pwindow.m_p;

         m_puserinteractionMouseCapture->route_as_parent_mouse_message(pmouse);

         //information() << "on_mouse_message (capture): " << pmouse->m_pointAbsolute;

         if (!pmouse->m_bRet && m_puserinteractionMouseCapture)
         {

            m_puserinteractionMouseCapture->on_child_from_point_mouse_message_routing(pmouse);

         }

      }
      else
      {

         //::string strType = ::type(m_puserinteraction).name();

         //information() << "on_mouse_message type : " << strType;

         //information() << "omousemsg this (F) : " << (::iptr) (::user::message *)pmouse;
         //information() << "omousemsg pwnd (F) : " << (::iptr) pmouse->m_pwindow.m_p;

         m_puserinteraction->on_mouse_message(pmouse);

         //information() << "omousemsg this (Q) : " << (::iptr) (::user::message *)pmouse;
         //information() << "omousemsg pwnd (Q) : " << (::iptr) pmouse->m_pwindow.m_p;

      }

      //         string strUserInteractionType(::is_null(puserinteractionMouse) ? "(null)" : ::type(puserinteractionMouse).name());
      //
      //         if(pmouse->m_atom == e_message_mouse_move)
      //         {
      //
      //            static int s_iMotionNotify = 0;
      //
      //            s_iMotionNotify++;
      //
      //            if (strUserInteractionType.case_insensitive_contains("button"))
      //            {
      //
      //               informationf("mouse_move::userinteraction=button");
      //
      //            }
      //            else
      //            {
      //
      //
      //               puserinteractionMouse = m_puserinteraction->child_from_point(pmouse->m_point);
      //
      //
      //
      //            }
      //
      //         }

      //if (puserinteractionMouse)
      //{

      //   //            if(pmouse->m_atom == ::e_message_left_button_double_click && puserinteractionMouse->m_bEatsDoubleClick)
      //   //            {
      //   //
      //   //               pmouse->m_bRet = true;
      //   //
      //   //               return;
      //   //
      //   //            }

      //   auto puserinteractionItem = puserinteractionMouse;

      //   do
      //   {

      //      puserinteractionItem->route_message(pmouse);

      //      if (pmouse->m_bRet)
      //      {

      //         break;

      //      }

      //      puserinteractionItem = puserinteractionItem->get_parent();

      //   } while (puserinteractionItem != nullptr);

      //}

      if (pmouse->m_atom == e_message_left_button_up)
      {

         auto pwindow = pmouse->m_pwindow;

         auto pwindowimpl = pwindow->m_puserinteractionimpl;

         if (::is_set(pwindowimpl))
         {

            if (::is_set(pwindowimpl->m_puiLastLButtonDown))
            {

               pwindowimpl->m_puiLastLButtonDown = nullptr;

            }

            if (::is_set(pwindowimpl->m_pitemLButtonDown))
            {

               pwindowimpl->m_pitemLButtonDown = nullptr;

            }

         }

      }

      return true;

//      if (pmouse->m_atom == e_message_left_button_down)
//      {
//
//         informationf("e_message_left_button_down");
//
//         string strType = ::type(m_puserinteraction).name();
//
//         if (strType.case_insensitive_contains("list_box"))
//         {
//
//            ::acme::get()->platform()->informationf("list_box e_message_left_button_down");
//
//         }
//
//      }
//      else if (pmouse->m_atom == e_message_left_button_up)
//      {
//
//         informationf("e_message_left_button_up");
//
//      }
//      else if (pmouse->m_atom == e_message_non_client_left_button_up)
//      {
//
//         informationf("e_message_non_client_left_button_up");
//
//      }
//      else if (pmouse->m_atom == e_message_non_client_left_button_down)
//      {
//
//         informationf("e_message_non_client_left_button_down");
//
//         string strType;
//
//         if (strType.case_insensitive_contains("list_box"))
//         {
//
//            ::acme::get()->platform()->informationf("list_box e_message_non_client_left_button_down");
//
//         }
//
//      }
//
//      auto psession = get_session();
//
//      if (psession)
//      {
//
//         psession->on_ui_mouse_message(pmouse);
//
//      }
//
//      if (pmouse->m_atom == e_message_mouse_move)
//      {
//         string strType = ::type(m_puserinteraction).name();
//
//         // We are at the message handler procedure.
//         // mouse messages originated from message handler and that are mouse transfer events should end up with the correct cursor.
//         // So the procedure starts by setting to the default cursor,
//         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
//         // handler has set it to another one.
//         auto pwindowing = windowing();
//         auto pcursor = pwindowing->get_cursor(e_cursor_default);
//
//         pmouse->m_pcursor = pcursor;
//
//         //informationf("windows::e_message_mouse_move(%d,%d)", pmouse->m_point.x(), pmouse->m_point.y());
//
//         //string strType;
//
//         if (m_puserinteraction)
//         {
//
//            strType = ::type(m_puserinteraction).name();
//
//            if (strType.case_insensitive_contains("list_box"))
//            {
//
//               //::acme::get()->platform()->informationf("list_box e_message_mouse_move");
//
//            }
//
//         }
//
//      }
//      else if (pmouse->m_atom == e_message_non_client_mouse_move)
//      {
//         // We are at the message handler procedure.
//         // mouse messages originated from message handler and that are mouse transfer events should end up with the correct cursor.
//         // So the procedure starts by setting to the default cursor,
//         // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
//         // handler has set it to another one.
//         auto pwindowing = windowing();
//         auto pcursor = pwindowing->get_cursor(e_cursor_default);
//
//         pmouse->m_pcursor = pcursor;
//
//      }
//
//      _on_mouse_move_step(pmouse->m_point);
//
//      auto puserinteractionMouseCapture = m_puserinteractionMouseCapture;
//
//      if (::is_set(puserinteractionMouseCapture))
//      {
//
//         ::string strType = ::type(puserinteractionMouseCapture).name();
//
//         information() << "on_mouse_message capture type : " << strType;
//
//         puserinteractionMouseCapture->route_message(pmouse);
//
//         return true;
//
//      }
//
//      //auto pchild = m_puserinteraction->child_from_point(pmouse->m_point);
//
//      //if (pchild)
//      //{
//
//      //   string strType = ::type(pchild).name();
//
//      //   if (strType.case_insensitive_contains("button"))
//      //   {
//
//      //      informationf("mouse transfer on button");
//
//      //   }
//      //   else if (strType.case_insensitive_contains("tab"))
//      //   {
//
//      //      informationf("mouse transfer on tab");
//
//      //   }
//
//      //   auto puserinteraction = pchild;
//
//      //   ::user::interaction_array interactionaHandled;
//
//      //   while (::is_set(puserinteraction))
//      //   {
//
//      //      puserinteraction->route_message(pmouse);
//
//      //      interactionaHandled.add_interaction(puserinteraction);
//
//      //      if (pmouse->m_bRet)
//      //      {
//
//      //         break;
//
//      //      }
//
//      //      puserinteraction = puserinteraction->get_parent();
//
//      //      if (::is_set(puserinteraction))
//      //      {
//
//      //         auto pchild = puserinteraction->child_from_point(pmouse->m_point, -1, &interactionaHandled);
//
//      //         if (::is_set(pchild))
//      //         {
//
//      //            pchild->route_message(pmouse);
//
//      //            if (pmouse->m_bRet)
//      //            {
//
//      //               break;
//
//      //            }
//
//      //         }
//
//      //      }
//
//      //   }
//
//      //}
//      //else
//      //{
//
//      //   m_puserinteraction->route_message(pmouse);
//
//      //}
//
//
//      m_puserinteraction->on_mouse_message(pmouse);
//
//      //if (pchild)
//      //{
//
//      //   string strType = ::type(pchild).name();
//
//      //   if (strType.case_insensitive_contains("button"))
//      //   {
//
//      //      informationf("mouse transfer on button");
//
//      //   }
//      //   else if (strType.case_insensitive_contains("tab"))
//      //   {
//
//      //      informationf("mouse transfer on tab");
//
//      //   }
//
//      //   auto puserinteraction = pchild;
//
//      //   ::user::interaction_array interactionaHandled;
//
//      //   while (::is_set(puserinteraction))
//      //   {
//
//      //      puserinteraction->route_message(pmouse);
//
//      //      interactionaHandled.add_interaction(puserinteraction);
//
//      //      if (pmouse->m_bRet)
//      //      {
//
//      //         break;
//
//      //      }
//
//      //      puserinteraction = puserinteraction->get_parent();
//
//      //      if (::is_set(puserinteraction))
//      //      {
//
//      //         auto pchild = puserinteraction->child_from_point(pmouse->m_point, -1, &interactionaHandled);
//
//      //         if (::is_set(pchild))
//      //         {
//
//      //            pchild->route_message(pmouse);
//
//      //            if (pmouse->m_bRet)
//      //            {
//
//      //               break;
//
//      //            }
//
//      //         }
//
//      //      }
//
//      //   }
//
//      //}
//      //else
//      //{
//
//      //   m_puserinteraction->route_message(pmouse);
//
//      //}
//
//      return true;

   }


   bool interaction_impl::IsTopParentActive()
   {

      return m_puserinteraction->window()->is_active_window();

      //return false;

   }


   void interaction_impl::ActivateTopParent()
   {

      throw ::interface_only();

   }


   //i32 interaction_impl::message_box(const ::string & pszText, const ::string & pszCaption,::u32 nType)

   //{
   //   UNREFERENCED_PARAMETER(pszText);

   //   UNREFERENCED_PARAMETER(pszCaption);

   //   UNREFERENCED_PARAMETER(nType);
   //   throw ::interface_only();

   //   return 0;
   //}

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for interaction_impl functions
   //    only works for derived class (eg: ::user::impact) that override 'GetScrollBarCtrl'
   // if the interaction_impl doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

   /*   CScrollBar* interaction_impl::GetScrollBarCtrl(i32) const
   {
   throw ::interface_only();
   }*/

   //i32 interaction_impl::SetScrollPos(i32 nBar,i32 nPos,bool bRedraw)
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(nPos);
   //   UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();

   //   return 0;
   //}

   //i32 interaction_impl::GetScrollPos(i32 nBar) const
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   throw ::interface_only();

   //   return 0;
   //}

   //void interaction_impl::SetScrollRange(i32 nBar,i32 nMinPos,i32 nMaxPos,bool bRedraw)
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(nMinPos);
   //   UNREFERENCED_PARAMETER(nMaxPos);
   //   UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();


   //}


   //void interaction_impl::GetScrollRange(i32 nBar,LPINT pMinPos,LPINT pMaxPos) const

   //{

   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(pMinPos);
   //   UNREFERENCED_PARAMETER(pMaxPos);

   //   throw ::interface_only();

   //}


   //// Turn on/off non-control scrollbars
   ////   for WS_?SCROLL scrollbars - show/hide them
   ////   for control scrollbar - enable/disable them
   //void interaction_impl::EnableScrollBarCtrl(i32 nBar,bool bEnable)
   //{
   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(bEnable);
   //   throw ::interface_only();
   //}


//#ifdef WINDOWS_DESKTOP
//
//
//   void interaction_impl::SetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,bool bRedraw)
//
//   {
//
//      UNREFERENCED_PARAMETER(nBar);
//      UNREFERENCED_PARAMETER(pScrollInfo);
//
//      UNREFERENCED_PARAMETER(bRedraw);
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//
//   void interaction_impl::GetScrollInfo(i32 nBar,LPSCROLLINFO pScrollInfo,::u32 nMask)
//
//   {
//
//      UNREFERENCED_PARAMETER(nBar);
//      UNREFERENCED_PARAMETER(pScrollInfo);
//
//      UNREFERENCED_PARAMETER(nMask);
//      throw ::interface_only();
//
//      return false;
//
//   }
//
//#endif


   //i32 interaction_impl::GetScrollLimit(i32 nBar)
   //{
   //   
   //   UNREFERENCED_PARAMETER(nBar);
   //   
   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::ScrollWindow(i32 xAmount,i32 yAmount, const ::rectangle_i32 * pcrect, const ::rectangle_i32 * pcrectClip)
   //{

   //   UNREFERENCED_PARAMETER(xAmount);
   //   UNREFERENCED_PARAMETER(yAmount);
   //   UNREFERENCED_PARAMETER(pcrect);
   //   UNREFERENCED_PARAMETER(pcrectClip);

   //   throw ::interface_only();

   //}


   //void interaction_impl::CalcWindowRect(::rectangle_i32 * pClientRect,::u32 nAdjustType)
   //{

   //   UNREFERENCED_PARAMETER(pClientRect);
   //   UNREFERENCED_PARAMETER(nAdjustType);

   //   throw ::interface_only();

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Special keyboard/system command processing

   bool interaction_impl::HandleFloatingSysCommand(::u32 nID, lparam lParam)
   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lParam);

      throw ::interface_only();

      return false;

   }


   bool interaction_impl::OnChildNotify(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

      return false;

   }


   bool interaction_impl::ReflectChildNotify(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      throw ::interface_only();

      return false;

   }


   //   void interaction_impl::OnParentNotify(const ::atom & atom,lparam lParam)
   //   {
   //      UNREFERENCED_PARAMETER(message);
   //      UNREFERENCED_PARAMETER(lParam);
   //      throw ::interface_only();
   //   }
   //
   //   void interaction_impl::OnSetFocus(::user::interaction_impl *)
   //   {
   //      throw ::interface_only();
   //   }
   //
   //   lresult interaction_impl::OnActivateTopLevel(wparam wParam,lparam)
   //   {
   //      UNREFERENCED_PARAMETER(wParam);
   //      throw ::interface_only();
   //   }
   //
   //   void interaction_impl::OnSysColorChange()
   //   {
   //      throw ::interface_only();
   //   }
   //
   //   void interaction_impl::OnSettingChange(::u32 uFlags, const ::string & pszSection)

   //   {
   //      UNREFERENCED_PARAMETER(uFlags);
   //      UNREFERENCED_PARAMETER(pszSection);

   //      throw ::interface_only();
   //   }
   //
   //#ifdef WINDOWS
   //   void interaction_impl::OnDevModeChange(__in char * pDeviceName)

   //   {
   //      UNREFERENCED_PARAMETER(pDeviceName);

   //      throw ::interface_only();
   //   }
   //
   //#ifdef WINDOWS_DESKTOP
   //   void interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   //   {
   //      throw ::interface_only();
   //   }
   //#endif
   //#endif
   //
   //   lresult interaction_impl::OnDisplayChange(wparam,lparam)
   //   {
   //      //   throw ::interface_only();
   //
   //      return 0;
   //
   //   }
   //
   //   lresult interaction_impl::OnDragList(wparam,lparam lParam)
   //   {
   //      UNREFERENCED_PARAMETER(lParam);
   //      throw ::interface_only();
   //   }

      /*   void interaction_impl::OnHScroll(::u32, ::u32, CScrollBar* pScrollBar)
      {
      UNREFERENCED_PARAMETER(pScrollBar);
      throw ::interface_only();
      }

      void interaction_impl::OnVScroll(::u32, ::u32, CScrollBar* pScrollBar)
      {
      UNREFERENCED_PARAMETER(pScrollBar);
      throw ::interface_only();
      }
      */

   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::image * pimage)
   {
      UNREFERENCED_PARAMETER(pimage);
      throw ::interface_only();
   }

   void interaction_impl::_001DeferPaintLayeredWindowBackground(::image * pimage)
   {
      UNREFERENCED_PARAMETER(pimage);
      throw ::interface_only();
   }

   void interaction_impl::_001OnPaint(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      throw ::interface_only();
   }

   void interaction_impl::_001OnPrint(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      throw ::interface_only();
   }

   //void interaction_impl::OnEnterIdle(::u32 /*nWhy*/,::user::interaction_impl * /*pWho*/)
   //{
   //   throw ::interface_only();
   //}

   //void * interaction_impl::OnCtlColor(::draw2d::graphics *,::user::interaction_impl * pwindow,::u32)
   //{
   //   UNREFERENCED_PARAMETER(pwindow);
   //   throw ::interface_only();
   //}


   /////////////////////////////////////////////////////////////////////////////
   // 'dialog data' support

   void interaction_impl::update_data(bool bSaveAndValidate)
   {

      UNREFERENCED_PARAMETER(bSaveAndValidate);

      throw ::interface_only();

      //return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child interaction_impl)

   void interaction_impl::CenterWindow(::user::interaction * pAlternateOwner)
   {

      UNREFERENCED_PARAMETER(pAlternateOwner);

      throw ::interface_only();

   }


   //void interaction_impl::CheckAutoCenter()
   //{
   //   throw ::interface_only();

   //   return false;

   //}

//   /////////////////////////////////////////////////////////////////////////////
//   // Dialog initialization support
//
//   void interaction_impl::ExecuteDlgInit(const ::string & pszResourceName)
//
//   {
//      UNREFERENCED_PARAMETER(pszResourceName);
//
//      throw ::interface_only();
//
//      return false;
//
//   }

//   void interaction_impl::ExecuteDlgInit(LPVOID pResource)
//
//   {
//      UNREFERENCED_PARAMETER(pResource);
//
//      throw ::interface_only();
//
//      return false;
//
//   }

   void interaction_impl::UpdateDialogControls(channel * pTarget, bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);

      throw ::interface_only();

   }



   //void interaction_impl::subclass_window(::windowing::window * pwindow)
   //{
   //   UNREFERENCED_PARAMETER(oswindow);
   //   throw ::interface_only();

   //   return false;

   //}

   //void interaction_impl::SubclassDlgItem(::u32 nID,::user::interaction_impl * pParent)
   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pParent);
   //   throw ::interface_only();

   //   return false;

   //}

   //oswindow interaction_impl::unsubclass_window()
   //{
   //   throw ::interface_only();
   //   return nullptr;
   //}

   //void interaction_impl::IsChild(::user::interaction * pinteraction) const
   //{
   //   UNREFERENCED_PARAMETER(pinteraction);
   //   throw ::interface_only();

   //   return false;

   //}


   bool interaction_impl::_is_window()
   {

      throw ::interface_only();

      return false;

   }


   //atom interaction_impl::SetDlgCtrlId(atom atom)
   //{

   //   UNREFERENCED_PARAMETER(atom);

   //   throw ::interface_only();

   //   return ::atom();

   //}


   //atom interaction_impl::GetDlgCtrlId() const
   //{

   //   throw ::interface_only();

   //   return ::atom();

   //}


   // void interaction_impl::SetWindowDisplayChanged()
   // {

   //    if (m_puserinteraction->is_this_visible() && m_puserinteraction->window_state3().m_edisplay3 != ::e_display_iconic)
   //    {

   //       if (m_puserinteraction->get_parent() == nullptr)
   //       {

   //          m_puserinteraction->check_transparent_mouse_events();

   //       }

   //    }
   //    else
   //    {

   //       //stop_fps_interest();
   //       //child_post_quit("fps_interest");

   //    }

   // }


   //void interaction_impl::layout().is_iconic()
   //{

   //   //throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::IsZoomed()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //::user::interaction * interaction_impl::get_parent() const
   //{

   //   return nullptr;

   //}


//   ::i32 interaction_impl::get_window_long(i32 nIndex) const
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return (::i32) ::GetWindowLongPtr(get_handle(), nIndex);
//
//#else
//
//      return (::i32) get_window_long_ptr(nIndex);
//
//#endif
//
//   }


//   ::i32 interaction_impl::set_window_long(i32 nIndex,::i32 lValue)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return (::i32) ::SetWindowLongPtr(get_handle(), nIndex, lValue);
//
//#else
//
//      return (::i32) set_window_long_ptr(nIndex, lValue);
//
//#endif
//
//   }


//   iptr interaction_impl::get_window_long_ptr(i32 nIndex) const
//   {
//
//      return m_pwindow->get_window_long_ptr(nIndex);
//
//   }
//
//
//   iptr interaction_impl::set_window_long_ptr(i32 nIndex, iptr lValue)
//   {
//
//      return m_pwindow->set_window_long_ptr(nIndex, lValue);
//
//   }


   //void interaction_impl::ReleaseCapture()
   //{

   //   auto psession = get_session();

   //   auto pwindowing = psession->windowing();

   //   pwindowing->release_capture();

   //   psession->m_puiCapture = nullptr;

   //   return true;

   //}


   //::user::interaction * interaction_impl::get_capture()
   //{

   //   if (!m_pwindow->has_capture())
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionCapture;

   //}


   //void interaction_impl::SetCapture(::user::interaction * pinteraction)
   //{

   //   if (pinteraction == nullptr)
   //   {

   //      pinteraction = m_puserinteraction;

   //   }

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   oswindow w = ::set_capture(get_handle());

   //   informationf("\nSet Capture: oswindow=0x" + ::hex::lower_from((iptr) w));

   //   auto psession = get_session();

   //   psession->m_puiCapture = pinteraction;

   //   return true;

   //}


   //// interaction_impl
   ///* interaction_impl::operator oswindow() const
   //{ return this == nullptr ? nullptr : get_handle(); }*/
   //void interaction_impl::operator==(const interaction_impl& wnd) const
   //{
   //   UNREFERENCED_PARAMETER(wnd);
   //   throw ::interface_only();
   //   return false;
   //}

   //void interaction_impl::operator!=(const interaction_impl& wnd) const
   //{
   //   UNREFERENCED_PARAMETER(wnd);
   //   throw ::interface_only();
   //   return false;
   //}


   //u32 interaction_impl::GetStyle() const
   //{

   //   return ::user::primitive_impl::GetStyle();

   //}


   //u32 interaction_impl::GetExStyle() const
   //{

   //   return ::user::primitive_impl::GetExStyle();

   //}


   //void interaction_impl::ModifyStyle(u32 dwRemove, u32 dwAdd, ::u32 nFlags)
   //{

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   ::u32 dw = get_window_long(GWL_STYLE);

   //   dw &= ~dwRemove;

   //   dw |= dwAdd;

   //   set_window_long(GWL_STYLE, dw);

   //   return false;

   //}


   //void interaction_impl::ModifyStyleEx(u32 dwRemove,u32 dwAdd,::u32 nFlags)
   //{

   //   if (!_is_window())
   //   {

   //      return false;

   //   }

   //   ::u32 dw = get_window_long(GWL_EXSTYLE);

   //   dw &= ~dwRemove;

   //   dw |= dwAdd;

   //   set_window_long(GWL_EXSTYLE, dw);

   //   return false;

   //}


   ::user::primitive * interaction_impl::set_owner(::user::primitive * pprimitiveOwner)
   {

      UNREFERENCED_PARAMETER(pprimitiveOwner);

      //throw ::interface_only();

      return nullptr;

   }


   lresult interaction_impl::send_message(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point)
   {

      auto pmessage = m_puserinteraction->get_message(atom, wparam, lparam);
      
      auto lresult = send_message(pmessage);
      
      return lresult;

   }


   lresult interaction_impl::send_message(::message::message * pmessage)
   {
      
      m_puserinteraction->on_message(pmessage);
      
      return pmessage->m_lresult;

   }


   //#ifdef LINUX
   //
   //
   //   lresult interaction_impl::send_x11_event(void * pevent)
   //   {
   //
   //      UNREFERENCED_PARAMETER(pevent);
   //
   //      throw ::interface_only();
   //
   //      return 0;
   //
   //   }
   //
   //
   //#endif


   void interaction_impl::post_message(const ::atom & atom, wparam wParam, lparam lParam)
   {

      if (!m_puserinteraction)
      {

         //return false;

         throw ::exception(error_wrong_state);

      }

      if (!m_puserinteraction->m_pthreadUserInteraction)
      {

         throw ::exception(error_wrong_state);

      }

#ifdef REPORT_OFFSET

      printf("(14) m_pwindow.m_p (0x%x)\n", m_pwindow.m_p);
      printf("(14) m_pwindow.m_pelement (0x%x)\n", m_pwindow.m_pelement);
      printf("(14) offset of m_pImpl2 in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_pImpl2));
      printf("(14) offset of m_timeLastExposureAddUp in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_timeLastExposureAddUp));
      printf("(14) offset of m_strBitmapSource in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_strBitmapSource));
      printf("(14) offset of m_bCursorRedraw in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bCursorRedraw));
      printf("(14) offset of m_bLockWindowUpdate in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bLockWindowUpdate));
      printf("(14) offset of m_bOkToUpdateScreen in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bOkToUpdateScreen));
      printf("(14) offset of m_sizeDrawn in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_sizeDrawn));
      printf("(14) offset of m_pthreadMouseLeave in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_pthreadMouseLeave));
      printf("(14) offset of m_bPointInside in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_bPointInside));
      printf("(14) offset of m_pwindow in ::user::interaction_impl = %d\n", offsetof(::user::interaction_impl, m_pwindow));

#endif

      auto pwindow = m_pwindow;

      if (!pwindow)
      {

         throw ::exception(error_wrong_state);

      }

      auto oswindow = pwindow->oswindow();

      if (!oswindow)
      {

         throw ::exception(error_wrong_state);

      }

      auto puserinteraction = m_puserinteraction;

      auto pthread = puserinteraction->m_pthreadUserInteraction;

      if (atom == e_message_redraw)
      {

         if (m_pgraphicsthread)
         {

            //puserinteraction->graphics_thread_redraw(wParam & 1);

            m_pgraphicsthread->post_redraw();

            return;

         }

      }

      MESSAGE message = {};

      message.oswindow = oswindow;

      message.m_atom = atom;

      message.wParam = wParam;

      message.lParam = lParam;

      auto pmessagequeue = pthread->get_message_queue();

      if (::is_null(pmessagequeue))
      {

         throw ::exception(error_wrong_state);

      }

      //auto estatus = 
      pmessagequeue->post_message(message);

      //return estatus;

   }


   //void interaction_impl::DragDetect(const ::point_i32 & point) const
   //{
   //   UNREFERENCED_PARAMETER(point);
   //   throw ::interface_only();
   //   return false;
   //}


   void interaction_impl::on_set_window_text()
   {

      auto pwindow = m_pwindow;

      if (pwindow)
      {

         ::string strWindowText = m_puserinteraction->get_window_text();

         pwindow->set_window_text(strWindowText);

      }

   }


   //   void interaction_impl::set_window_text(const ::string& pszString)
   //
   //   {
   //
   //      UNREFERENCED_PARAMETER(pszString);
   //
   //
   //      throw ::interface_only();
   //
   //   }


      //strsize interaction_impl::GetWindowText(char * pszString,i32 nMaxCount)
      //{

      //   UNREFERENCED_PARAMETER(pszString);
      //   UNREFERENCED_PARAMETER(nMaxCount);
      //   throw ::interface_only();

      //   return 0;
      //}


      //strsize interaction_impl::GetWindowTextLength()
      //{

      //   throw ::interface_only();
      //   return 0;

      //}


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      UNREFERENCED_PARAMETER(bAccept);

      throw ::interface_only();

   }


   bool interaction_impl::window_is_iconic()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->const_layout().sketch().display() == ::e_display_iconic;

   }


   bool interaction_impl::window_is_zoomed()
   {

      if (!m_puserinteraction)
      {

         return false;

      }

      return m_puserinteraction->const_layout().sketch().display() == ::e_display_zoomed;

   }


   ::u32 interaction_impl::ArrangeIconicWindows()
   {

      throw ::interface_only();

      return 0;

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * puserinteractionTo, ::point_i32 * pPoint, ::u32 nCount)
   {

      UNREFERENCED_PARAMETER(puserinteractionTo);
      UNREFERENCED_PARAMETER(pPoint);
      UNREFERENCED_PARAMETER(nCount);

      throw ::interface_only();

   }


   void interaction_impl::MapWindowPoints(::user::interaction_impl * puserinteractionTo, ::rectangle_i32 * prectangle)
   {
      UNREFERENCED_PARAMETER(puserinteractionTo);
      UNREFERENCED_PARAMETER(prectangle);

      throw ::interface_only();
   }

   //void interaction_impl::UpdateWindow()
   //{
   //   throw ::interface_only();
   //}

   //void interaction_impl::SetRedraw(bool bRedraw)
   //{
   //   UNREFERENCED_PARAMETER(bRedraw);
   //   throw ::interface_only();
   //}

   //void interaction_impl::GetUpdateRect(::rectangle_i32 * prectangle,bool bErase)

   //{
   //   UNREFERENCED_PARAMETER(prectangle);

   //   UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();

   //   return false;
   //}

   //i32 interaction_impl::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   //{
   //   UNREFERENCED_PARAMETER(pRgn);
   //   UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();

   //   return 0;
   //}


   //void interaction_impl::Invalidate(bool bErase)
   //{

   //   UNREFERENCED_PARAMETER(bErase);

   //   throw ::interface_only();

   //}


   //void interaction_impl::InvalidateRect(const ::rectangle_i32 & rectangle, bool bErase)
   //{

   //   UNREFERENCED_PARAMETER(rectangle);
   //   UNREFERENCED_PARAMETER(bErase);

   //   throw ::interface_only();

   //}


   //void interaction_impl::InvalidateRgn(::draw2d::region * pRgn, bool bErase)
   //{
   //   UNREFERENCED_PARAMETER(pRgn);
   //   UNREFERENCED_PARAMETER(bErase);
   //   throw ::interface_only();
   //}


   //void interaction_impl::ValidateRect(const ::rectangle_i32 & rectangle)
   //{

   //   UNREFERENCED_PARAMETER(rectangle);

   //   throw ::interface_only();

   //}


   //void interaction_impl::ValidateRgn(::draw2d::region * pRgn)
   //{

   //   UNREFERENCED_PARAMETER(pRgn);

   //   throw ::interface_only();

   //}


   ////void interaction_impl::_is_window_visible()
   ////{

   ////   throw ::interface_only();

   ////   return false;

   ////}


   //void interaction_impl::ShowOwnedPopups(bool bShow)
   //{
   //   UNREFERENCED_PARAMETER(bShow);
   //   throw ::interface_only();
   //}


   /*::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region * prgnClip,u32 flags)
   {
      UNREFERENCED_PARAMETER(prgnClip);
      UNREFERENCED_PARAMETER(flags);
      throw ::interface_only();


      return nullptr;
   }*/

   void interaction_impl::LockWindowUpdate()
   {

      throw ::interface_only();

      //return false;

   }


   void interaction_impl::UnlockWindowUpdate()
   {

      throw ::interface_only();

   }


   void interaction_impl::set_need_redraw(const ::rectangle_i32_array & rectangleaHostNeedRedraw, function<void()> function, bool bAscendants)
   {

      _synchronous_lock synchronouslock(synchronization());

      if (rectangleaHostNeedRedraw.is_empty())
      {

         return;

      }

#ifdef EXTRA_LOGGING

      for (auto & rectangle : rectangleaHostNeedRedraw)
      {

         if (rectangle.is_empty())
         {

            information() << "interaction_impl::set_need_redraw empty rectangle : " << rectangle;

         }
         else
         {

            information() << "interaction_impl::set_need_redraw : " << rectangle;

         }

      }

#endif

      bool bFullRedraw = false;

      for (auto & predraw : m_redrawitema)
      {

         if (predraw->m_rectanglea.is_empty())
         {

            return;

         }

         bool bContainsAll = true;

         //rectangle_i32_array rectangleaUnion;

         for (auto & rectangle : rectangleaHostNeedRedraw)
         {

            if (rectangle.is_null())
            {

               bFullRedraw = true;

               break;

            }

            bool bContainsAny = false;

            for (auto & rectangleRedraw : predraw->m_rectanglea)
            {

               if (rectangleRedraw.contains(rectangle))
               {

                  bContainsAny = true;

                  break;

               }

               //auto rectangleUnion = rectangleRedraw.get_union(rectangle);

               //if (rectangleUnion.area() <= (rectangleRedraw.area() + 4 * rectangle.area()))
               //{

               //   rectangleaUnion.add(rectangleUnion);

               //   information() << "set_need_redraw::merged rectangle " << rectangleUnion;

               //}

            }

            if (!bContainsAny)
            {

               bContainsAll = false;

               break;

            }

         }

         if (bFullRedraw)
         {

            break;

         }
         else if (bContainsAll)
         {

            if (function)
            {

               predraw->m_functiona.add(function);

            }

            return;

         }

         //else if (rectangleaUnion.size() == rectangleaHostNeedRedraw.size())
         //{

         //   information() << "set_need_redraw::merged rectangle count " << rectangleaUnion.size();

         //   predraw->m_rectanglea = ::transfer(rectangleaUnion);

         //   if (function)
         //   {

         //      predraw->m_functiona.add(function);

         //   }

         //   return;

         //}

      }

      if (m_bDoingGraphics)
      {

         //informationf("set_need_redraw on doing graphics");

      }

      if (bFullRedraw)
      {

         if (m_redrawitema.is_empty())
         {

            auto predrawitem = __create_new<redraw_item>();

            if (function)
            {

               predrawitem->m_functiona.add(function);

            }

            m_redrawitema.add(predrawitem);

         }
         else
         {

            for (index i = m_redrawitema.get_upper_bound(); i >= 1; i--)
            {

               m_redrawitema.first()->m_functiona.append(m_redrawitema[i]->m_functiona);

               m_redrawitema.erase_at(i);

            }

            m_redrawitema.first()->m_rectanglea.clear();

            if (function)
            {

               m_redrawitema.first()->m_functiona.add(function);

            }

         }

         return;

      }

      auto predrawitem = __create_new<redraw_item>();

      predrawitem->m_rectanglea.append(rectangleaHostNeedRedraw);

      if (function)
      {

         predrawitem->m_functiona.add(function);

      }

      m_redrawitema.add(predrawitem);

      //information() << node()->get_callstack();

   }


   //bool interaction_impl::needs_to_draw(const ::rectangle_i32 & rectangleHostNeedsToDraw, ::draw2d::graphics_pointer & pgraphics)
   //{

   //   _synchronous_lock synchronouslock(synchronization());

   //   if (!m_pgraphics->is_single_buffer_mode())
   //   {

   //      return true;

   //   }

   //   if (pgraphics->m_rectangleaNeedRedraw.is_empty())
   //   {

   //      return true;

   //   }

   //   for (auto & rectangleRedraw : pgraphics->m_rectangleaNeedRedraw)
   //   {

   //      if (rectangleRedraw.intersects(rectangleHostNeedsToDraw))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   void interaction_impl::post_redraw(bool bAscendants)
   {

      if (::is_null(m_pgraphicsthread))
      {

         return;

      }

      if (!m_puserinteraction)
      {

         return;

      }

      //bool bForceUpdateBuffer = false;

      m_pgraphicsthread->post_redraw();

      //m_puserinteraction->post_message(::e_message_redraw, bForceUpdateBuffer);

//      m_pgraphicsthread->graphics_thread_redraw();

   }


   void interaction_impl::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      m_puserinteraction->set_need_redraw();

      //return true;

   }


   //void interaction_impl::EnableScrollBar(i32 nSBFlags,::u32 nArrowFlags)
   //{

   //   UNREFERENCED_PARAMETER(nSBFlags);

   //   UNREFERENCED_PARAMETER(nArrowFlags);

   //   throw ::interface_only();

   //   return false;

   //}


   //::point_i32 interaction_impl::get_cursor_position() const
   //{

   //   auto psession = get_session();

   //   if (!psession)
   //   {

   //      return ::point_i32();

   //   }

   //   return psession->get_cursor_position();

   //}


   void interaction_impl::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if (::is_null(m_pwindow))
      {

         //return ::error_failed;

         return;

      }

      //auto estatus = 

      m_pwindow->set_mouse_cursor(pcursor);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //::windowing::window * interaction_impl::get_window() const
   //{

   //   return m_pwindow;

   //}


   //void interaction_impl::aaa_set_mouse_cursor(enum_cursor ecursor)
   //{

   //   auto psession = get_session();

   //   auto puser = psession->user();

   //   auto pwindowing = puser->windowing();

   //   auto pcursor = pwindowing->get_cursor(ecursor);

   //   auto pwindow = get_window();

   //   auto estatus = pwindow->set_cursor(pcursor);

   //   return estatus;

   //}


   //void interaction_impl::DrawCaption(::draw2d::graphics_pointer & pgraphics,const rectangle_i32 & prc,::u32 uFlags)
   //{

   //   UNREFERENCED_PARAMETER(pgraphics);
   //   UNREFERENCED_PARAMETER(prc);
   //   UNREFERENCED_PARAMETER(uFlags);

   //   throw ::interface_only();

   //   //return false;

   //}


   //void interaction_impl::is_window_enabled() const
   //{

   //   return m_puserinteraction->m_ewindowflag & e_window_flag_enable;

   //}


   void interaction_impl::enable_window(bool bEnable)
   {

      m_puserinteraction->m_ewindowflag.set(e_window_flag_enable, bEnable);

      //return true;

   }


   //::user::interaction * interaction_impl::GetActiveWindow()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction * interaction_impl::set_active_window()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void interaction_impl::set_keyboard_focus()
   //{

   //   return false;

   //}


   //void interaction_impl::CheckDlgButton(i32 nIDButton,::u32 nCheck)
   //{
   //   UNREFERENCED_PARAMETER(nIDButton);
   //   UNREFERENCED_PARAMETER(nCheck);
   //   throw ::interface_only();
   //}

   //void interaction_impl::CheckRadioButton(i32 nIDFirstButton,i32 nIDLastButton,i32 nIDCheckButton)
   //{
   //   UNREFERENCED_PARAMETER(nIDFirstButton);
   //   UNREFERENCED_PARAMETER(nIDLastButton);
   //   UNREFERENCED_PARAMETER(nIDCheckButton);
   //   throw ::interface_only();
   //}

   //i32 interaction_impl::DlgDirList(char * pPathSpec,i32 nIDListBox,i32 nIDStaticPath,::u32 nFileType)

   //{
   //   UNREFERENCED_PARAMETER(pPathSpec);

   //   UNREFERENCED_PARAMETER(nIDListBox);
   //   UNREFERENCED_PARAMETER(nIDStaticPath);
   //   UNREFERENCED_PARAMETER(nFileType);
   //   throw ::interface_only();
   //   return 0;
   //}

   //i32 interaction_impl::DlgDirListComboBox(char * pPathSpec,i32 nIDComboBox,i32 nIDStaticPath,::u32 nFileType)

   //{
   //   UNREFERENCED_PARAMETER(pPathSpec);

   //   UNREFERENCED_PARAMETER(nIDComboBox);
   //   UNREFERENCED_PARAMETER(nIDStaticPath);
   //   UNREFERENCED_PARAMETER(nFileType);
   //   throw ::interface_only();

   //   return 0;
   //}

   //void interaction_impl::DlgDirSelect(char * pString,i32 nSize,i32 nIDListBox)

   //{
   //   UNREFERENCED_PARAMETER(pString);

   //   UNREFERENCED_PARAMETER(nSize);
   //   UNREFERENCED_PARAMETER(nIDListBox);
   //   throw ::interface_only();

   //   return false;
   //}

   //void interaction_impl::DlgDirSelectComboBox(char * pString,i32 nSize,i32 nIDComboBox)

   //{
   //   UNREFERENCED_PARAMETER(pString);

   //   UNREFERENCED_PARAMETER(nSize);
   //   UNREFERENCED_PARAMETER(nIDComboBox);
   //   throw ::interface_only();

   //   return false;
   //}

   //::u32 interaction_impl::GetChildByIdInt(i32 nID,bool* pTrans,bool bSigned) const

   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pTrans);

   //   UNREFERENCED_PARAMETER(bSigned);
   //   throw ::interface_only();

   //   return 0;
   //}

   //i32 interaction_impl::GetChildByIdText(i32 nID,char * pStr,i32 nMaxCount) const

   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pStr);

   //   UNREFERENCED_PARAMETER(nMaxCount);
   //   throw ::interface_only();

   //   return 0;
   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   //{

   //   UNREFERENCED_PARAMETER(pWndCtl);
   //   UNREFERENCED_PARAMETER(bPrevious);

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::user::interaction_impl * interaction_impl::GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious) const
   //{

   //   UNREFERENCED_PARAMETER(pWndCtl);
   //   UNREFERENCED_PARAMETER(bPrevious);

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //::u32 interaction_impl::IsDlgButtonChecked(i32 nIDButton) const
   //{
   //   UNREFERENCED_PARAMETER(nIDButton);
   //   throw ::interface_only();

   //   return 0;
   //}


   //lparam interaction_impl::SendDlgItemMessage(i32 nID, ::u32 message, wparam wParam,lparam lParam)
   //{

   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(message);
   //   UNREFERENCED_PARAMETER(wParam);
   //   UNREFERENCED_PARAMETER(lParam);
   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::SetDlgItemInt(i32 nID,::u32 nValue,bool bSigned)
   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(nValue);
   //   UNREFERENCED_PARAMETER(bSigned);
   //   throw ::interface_only();
   //}

   //void interaction_impl::SetDlgItemText(i32 nID, const ::string & pszString)

   //{
   //   UNREFERENCED_PARAMETER(nID);
   //   UNREFERENCED_PARAMETER(pszString);

   //   throw ::interface_only();
   //}


   //i32 interaction_impl::ScrollWindowEx(i32 Δx,i32 Δy,
   //                                     const ::rectangle_i32 * prectScroll,
   //                                       const ::rectangle_i32 * prectClip,
   //                                     ::draw2d::region* prgnUpdate,::rectangle_i32 * pRectUpdate,::u32 flags)
   //{

   //   UNREFERENCED_PARAMETER(Δx);
   //   UNREFERENCED_PARAMETER(Δy);
   //   UNREFERENCED_PARAMETER(prectScroll);
   //   UNREFERENCED_PARAMETER(prectClip);
   //   UNREFERENCED_PARAMETER(prgnUpdate);
   //   UNREFERENCED_PARAMETER(pRectUpdate);
   //   UNREFERENCED_PARAMETER(flags);

   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::ShowScrollBar(::u32 nBar,bool bShow)
   //{

   //   UNREFERENCED_PARAMETER(nBar);
   //   UNREFERENCED_PARAMETER(bShow);

   //   throw ::interface_only();

   //}


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point_i32 & point)
   {

      UNREFERENCED_PARAMETER(point);

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::ChildWindowFromPoint(const ::point_i32 & point, ::u32 nFlags)
   {

      UNREFERENCED_PARAMETER(point);

      UNREFERENCED_PARAMETER(nFlags);

      throw ::interface_only();

      return nullptr;

   }


   //   ::user::interaction * interaction_impl::get_next_window(::u32 nFlag)
   //   {
   //
   //      UNREFERENCED_PARAMETER(nFlag);
   //
   //      throw ::interface_only();
   //
   //      return nullptr;
   //
   //   }


   ::user::interaction * interaction_impl::GetTopWindow()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::user::interaction * interaction_impl::GetLastActivePopup()
   {

      throw ::interface_only();

      return nullptr;

   }


   //void interaction_impl::FlashWindow(bool bInvert)
   //{

   //   UNREFERENCED_PARAMETER(bInvert);

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::ChangeClipboardChain(::windowing::window * pwindow_Next)
   //{

   //   UNREFERENCED_PARAMETER(oswindow_Next);

   //   throw ::interface_only();

   //   return false;

   //}


   //oswindow interaction_impl::SetClipboardImpacter()
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   //void interaction_impl::OpenClipboard()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_impl::user_interaction_on_hide()
   {

      decltype(m_userinteractionaMouseHover) userinteractiona;

      {

         auto psync = synchronization();

         _synchronous_lock synchronouslock(this->synchronization());

         userinteractiona = m_userinteractionaMouseHover;

         m_userinteractionaMouseHover.erase_all();

      }

      for (auto & pinteraction : userinteractiona)
      {

         pinteraction->post_message(e_message_mouse_leave);

      }

   }


   void interaction_impl::HideCaret()
   {

      throw ::interface_only();

   }


   void interaction_impl::ShowCaret()
   {

      throw ::interface_only();

   }


   //void interaction_impl::set_foreground_window()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::SendNotifyMessage(::u32 message,wparam wParam,lparam lParam)
   //{

   //   UNREFERENCED_PARAMETER(message);
   //   UNREFERENCED_PARAMETER(wParam);
   //   UNREFERENCED_PARAMETER(lParam);

   //   throw ::interface_only();

   //   return false;

   //}


   void interaction_impl::Print(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);

      throw ::interface_only();

   }


   void interaction_impl::PrintClient(::draw2d::graphics_pointer & pgraphics, u32 dwFlags) const
   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(dwFlags);

      throw ::interface_only();

   }


   //void interaction_impl::SetWindowContextHelpId(u32 dwContextHelpId)
   //{

   //   UNREFERENCED_PARAMETER(dwContextHelpId);

   //   throw ::interface_only();

   //   return false;

   //}


   //u32 interaction_impl::GetWindowContextHelpId() const
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   void interaction_impl::on_message_create(::message::message * pmessage)
   {


   }


   void interaction_impl::on_message_pos_create(::message::message * pmessage)
   {

      if (m_puserinteraction)
      {

         m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

      }

      information() << "on_message_pos_create";

      if (m_pgraphicsthread)
      {

         information() << "m_pgraphicsthread->m_bGraphicsThreadEnabled = true";
       
         //m_pgraphicsthread->m_eventReady.SetEvent();

         m_pgraphicsthread->m_bGraphicsThreadEnabled = true;

      }
      
      auto pusersystem = m_puserinteraction->m_pusersystem;

      if(pusersystem)
      {

         add(pusersystem->m_prequest);

         for(auto & poutputpurpose : pusersystem->m_graphicsoutputpurposea)
         {

            information() << "adding graphical output_purpose from user::system";

            add(poutputpurpose);

         }

      }

   }


   void interaction_impl::_001OnPrioCreate(::message::message * pmessage)
   {

      m_puserinteraction->on_after_set_parent();

      // // https://stackoverflow.com/questions/23367775/pragma-packshow-with-gcc - Morten Jensen
      //       /*
      //    The static_assert macro will generate an error at compile-time, if the predicate is false
      //    but will only work for predicates that are resolvable at compile-time!

      //    E.g.: to assert the size of a data structure, static_assert(sizeof(struct_t) == 10)
      // */
      // #define STATIC_ASSERT(COND,MSG)      typedef char static_assertion_##MSG[(!!(COND))*2-1]
      // /* token pasting madness: */
      // #define COMPILE_TIME_ASSERT3(X,L)     STATIC_ASSERT(X,at_line_##L)             /* add line-number to error message for better warnings, especially GCC will tell the name of the variable as well */
      // #define COMPILE_TIME_ASSERT2(X,L)     COMPILE_TIME_ASSERT3(X, L)               /* expand line-number */
      // #define static_assert(X)              COMPILE_TIME_ASSERT2(X, __LINE__)        /* call with line-number macro */

      // #define PACKED  __attribute__ ((gcc_struct, __packed__))

      //   typedef struct
      //   {
      //      uint8_t bytes[3];
      //      uint32_t looong;
      //   } struct_t1;
      //   // static_assert(sizeof(struct_t) == 8);
      //
      //      printf("sizeof(struct_t1) = %" PRIuPTR "\n", sizeof(struct_t1));
      //
      //      #ifdef _DEBUG
      //      printf("_DEBUG defined\n");
      //      #else
      //      printf("_DEBUG not defined\n");
      //      #endif
      //
      //      #ifdef RASPBERRYPIOS
      //      printf("RASPBERRYPIOS defined\n");
      //      #else
      //      printf("RASPBERRYPIOS not defined\n");
      //      #endif

#ifdef REPORT_OFFSET

      printf("(11.0) offset of m_timeFocusStart in ::user::primitive = %d\n", offsetof(::user::primitive, m_timeFocusStart));
      printf("(11.0) offset of m_uUserInteractionFlags in ::user::interaction = %d\n", offsetof(::user::interaction, m_bExtendOnParent));
      printf("(11.0) offset of m_pwindow in ::user::interaction = %d\n", offsetof(::user::interaction, m_pwindow));

      if (::is_null(m_puserinteraction->m_pwindow))
      {

         printf("m_puserinteraction->m_pwindow is null!! (11.1) (0x%x)\n", m_puserinteraction->m_pwindow);
         printf("m_puserinteraction (11.1) (0x%x)\n", m_puserinteraction.m_p);
         printf("&m_pwindow(0x%x)\n", &m_puserinteraction->m_pwindow);

      }
      else
      {

         printf("m_puserinteraction->m_pwindow is set!! (11.1) (0x%x)\n", m_puserinteraction->m_pwindow);
         printf("m_puserinteraction (11.1) (0x%x)\n", m_puserinteraction.m_p);
         printf("&m_pwindow(0x%x)\n", &m_puserinteraction->m_pwindow);

      }

      fflush(stdout);

#endif

      if (::is_null(m_puserinteraction->m_pinteractionScaler))
      {

         m_puserinteraction->m_pinteractionScaler = __allocate< ::user::interaction_scaler >();

      }

#ifdef REPORT_OFFSET

      if (::is_null(m_puserinteraction->m_pwindow))
      {

         printf("m_puserinteraction->m_pwindow is null!! (11) (0x%x)\n", m_puserinteraction->m_pwindow);
         printf("m_puserinteraction (11) (0x%x)\n", m_puserinteraction.m_p);

      }
      else
      {

         printf("m_puserinteraction->m_pwindow is set!! (11) (0x%x)\n", m_puserinteraction->m_pwindow);
         printf("m_puserinteraction (11) (0x%x)\n", m_puserinteraction.m_p);

      }

      fflush(stdout);

#endif

      m_puserinteraction->m_pinteractionScaler->on_display_change(m_puserinteraction);

#ifdef REPORT_OFFSET

      if (::is_null(m_puserinteraction->m_pwindow))
      {

         printf("m_puserinteraction->m_pwindow is null!! (12) (0x%x)\n", m_puserinteraction->m_pwindow);
         printf("m_puserinteraction (12) (0x%x)\n", m_puserinteraction.m_p);

      }
      else
      {

         printf("m_puserinteraction->m_pwindow is set!! (12) (0x%x)\n", m_puserinteraction->m_pwindow);
         printf("m_puserinteraction (12) (0x%x)\n", m_puserinteraction.m_p);

      }

      fflush(stdout);

#endif
      
      string strType = ::type(m_puserinteraction).name();

      m_pwindowing = m_puserinteraction->windowing();

      ::pointer < ::user::thread > puserthread = m_puserinteraction->m_pthreadUserInteraction;
      
      if(puserthread)
      {
         
         puserthread->m_oswindow = window()->m_oswindow;
         
      }

      if (m_puserinteraction->m_ewindowflag & e_window_flag_graphical)
      {

         if (::is_set(m_pgraphicsthread))
         {

            m_pgraphicsthread->set_fps_interest_frames_per_second(get_prodevian_frames_per_second());

            m_pgraphicsthread->set_nominal_frames_per_second(get_nominal_frames_per_second());

            pmessage->previous();

            m_pgraphicsthread->graphics_thread_reset(m_puserinteraction);

         }

         if (m_puserinteraction)
         {

            if (!m_puserinteraction->m_bMessageWindow)
            {

               m_pcsDisplay = __new< critical_section >();

               information() << "interaction_impl m_pgraphics alloc : " << strType;

               update_graphics_resources();

               information() << "interaction_impl on _create_window : " << strType;

            }

            if (m_pgraphicsthread && m_puserinteraction->is_graphical())
            {

               m_pgraphicsthread->graphics_thread_reset(m_puserinteraction);

            }

         }

         if (m_pgraphicsthread)
         {

            m_pgraphicsthread->defer_create_graphics_thread();

         }

      }


   }


   void interaction_impl::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      if (pshowwindow->m_bShow)
      {

         information() << "user::interaction_impl::on_message_show_window bShow = true";

         if (m_puserinteraction->const_layout().design().display() != ::e_display_iconic)
         {

            if (m_puserinteraction->get_parent() == nullptr)
            {

               m_puserinteraction->check_transparent_mouse_events();

            }

         }
         else
         {

            //stop_prodevian();
            //child_post_quit("prodevian");

         }

      }
      else
      {

         information() << "user::interaction_impl::on_message_show_window bShow = false";

         {

            decltype(m_userinteractionaMouseHover) userinteractiona;

            {

               _synchronous_lock synchronouslock(this->synchronization());

               userinteractiona = m_userinteractionaMouseHover;

               m_userinteractionaMouseHover.erase_all();

            }

            for (auto & pinteraction : userinteractiona)
            {

               try
               {

                  pinteraction->send_message(e_message_mouse_leave);

               }
               catch (...)
               {

               }

            }

         }

         {

            auto children = m_puserinteraction->synchronized_get_children();

            // auto puserinteractionpointeraChild = m_puserinteraction->m_puserinteractionpointeraChild;

            // if (puserinteractionpointeraChild)
            {

               //{

               //   _synchronous_lock synchronouslock(this->synchronization());

               //   if(!m_puserinteraction)
               //   {

               //      return;

               //   }

               //   uia = m_puserinteraction->m_puserinteractionpointeraChild;

               //}

               for (auto & pinteraction : children)
               {

                  //synchronouslock.unlock();

                  try
                  {

                     pinteraction->send_message(e_message_show_window, 0, (::i64)e_show_window_parent_closing);

                  }
                  catch (...)
                  {

                  }

                  //synchronouslock.lock();

               }

            }

         }

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction)
      {

         m_puserinteraction->check_transparent_mouse_events();

         set_need_redraw();

      }

   }


#ifdef WINDOWS_DESKTOP


   void interaction_impl::_001OnWindowPosChanged(::message::message * pmessage)
   {

      throw ::interface_only();

   }


#endif


   void interaction_impl::BeginModalState()
   {

      throw ::interface_only();

   }


   void interaction_impl::EndModalState()
   {

      throw ::interface_only();

   }


   //void interaction_impl::CloseWindow()
   //{

   //   throw ::interface_only();

   //}


   //void interaction_impl::OpenIcon()
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   //i32 interaction_impl::GetCheckedRadioButton(i32 nIDFirstButton,i32 nIDLastButton)
   //{

   //   UNREFERENCED_PARAMETER(nIDFirstButton);
   //   UNREFERENCED_PARAMETER(nIDLastButton);

   //   throw ::interface_only();

   //   return 0;

   //}


   //void interaction_impl::_EnableToolTips(bool bEnable,::u32 nFlag)
   //{

   //   UNREFERENCED_PARAMETER(bEnable);
   //   UNREFERENCED_PARAMETER(nFlag);

   //   throw ::interface_only();

   //   return false;

   //}


   //void interaction_impl::_001BaseWndInterfaceMap()
   //{

   //   psystem->window_map().set(get_handle(), this);

   //}


   interaction_impl * interaction_impl::get_impl() const
   {

      return (::user::interaction_impl *)this;

   }


   void interaction_impl::do_graphics()
   {

      if (!m_puserinteraction || has_destroying_flag())
      {

         return;

      }

      m_bDoingGraphics = true;

      at_end_of_scope
      {

         m_bDoingGraphics = false;

      };

#if TIME_REPORTING

      ::time timeStart;

      timeStart.Now();

#endif

      //::rectangle_i32 rectangleWindow;

      //m_puserinteraction->window_rectangle(rectangleWindow);

      windowing_output_debug_string("\n_001UpdateBuffer : after window_rectangle");

      string strType = ::type(m_puserinteraction).name();

      //      if (strType.contains("list_box"))
      //      {
      //
      //         informationf("list_box");
      //
      //      }

      //preempt(10_s);

      bool bDraw = false;

      //{

      //   ::draw2d::lock draw2dlock(this);

      //   //m_bUpdateBuffer = false;

      //   //m_bUpdateWindow = false;

      //   m_puserinteraction->sketch_to_layout();

      //   if (m_puserinteraction->should_perform_layout(pgraphics))
      //   {

      //      m_puserinteraction->perform_layout(pgraphics);

      //   }

      //   m_puserinteraction->layout_to_design(m_bUpdateBuffer, m_bUpdateWindow);

      //   bool bIsThisScreenVisible = m_puserinteraction->const_layout().design().is_screen_visible();

      //   //if (!m_pimpl)
      //   //{

      //   //   return;

      //   //}

      //   bool bHasProdevian = this->has_prodevian();

      //   if (!m_puserinteraction)
      //   {

      //      return;

      //   }

      //   bool bRedraw = m_puserinteraction->m_bNeedRedraw;

      //   if (!m_puserinteraction)
      //   {

      //      return;

      //   }

      //   bool bHasPendingGraphicalUpdate = m_puserinteraction->has_pending_graphical_update();

      //   if (bIsThisScreenVisible
      //      &&
      //      (//bForce
      //         //||
      //         m_bUpdateBuffer
      //         || bHasProdevian
      //         || bRedraw
      //         || bHasPendingGraphicalUpdate
      //         )
      //      )
      //   {

      //      bDraw = true;

      //   }

      //   if (!m_puserinteraction)
      //   {

      //      return;

      //   }

         /*bool bDraw = false;

         m_bVisualUpdated = false;

         if (!m_puserinteraction)
         {

            return;

         }

         {*/


         //synchronouslock.unlock();

         ////if (!m_puserinteraction->is_sketch_to_design_locked())
         ////{

         //   /*m_puserinteraction->sketch_to_design(bUpdateBuffer, bUpdateWindow);*/

         ////}

         //synchronouslock.lock();

         //if (!m_puserinteraction)
         //{

//   return;

//}

//if (!this->task_get_run())
//{

//   return;

//}

//if (!m_puserinteraction)
//{

//   return;

//}

/*       bool bIsThisScreenVisible = m_puserinteraction->const_layout().design().is_screen_visible();

       if(!m_pimpl)
       {

          return;

       }

       bool bHasProdevian = m_pimpl->has_prodevian();

       if(!m_puserinteraction)
       {

          return;

       }

       bool bRedraw = m_puserinteraction->m_bNeedRedraw;

       if(!m_puserinteraction)
       {

          return;

       }

       bool bHasPendingGraphicalUpdate = m_puserinteraction->has_pending_graphical_update();

       if (bIsThisScreenVisible
          &&
          (bForce
          || bUpdateBuffer
          || bHasProdevian
          || bRedraw
          || bHasPendingGraphicalUpdate
          )
          )
       {

          bDraw = true;

       }

       if(!m_puserinteraction)
       {

          return;

       }*/

       /*      if (m_puserinteraction->m_bOffScreenRender)
             {

                bDraw = true;

             }*/
#ifdef MORE_LOG
information() << "do_graphics(A)";
#endif
update_graphics_resources();

if (bDraw && m_pgraphicsgraphics.is_null())
{

   information() << "do_graphics exit(A1)";

   return;

}

//}

if (m_puserinteraction->has_flag(e_flag_destroying)
   || m_puserinteraction->has_finishing_flag()
   || has_flag(e_flag_destroying)
   || has_finishing_flag())
{

   information() << "do_graphics exit(A2)";

   return;

}


      //::size_i32 sizeDrawn;

      //single_lock synchronouslockObjects(system()->m_paurasystem->draw2d()->get_object_list_mutex());

      //if (!synchronouslockObjects.lock(0_s))
      //{

      //   return;

      //}
      //single_lock synchronouslockImages(system()->m_paurasystem->draw2d()->get_image_list_mutex());

      //if (!synchronouslockImages.lock(0_s))
      //{

      //   return;

      //}
      //single_lock synchronouslockGraphicsContext(system()->m_paurasystem->draw2d()->get_graphics_context_list_mutex());

      //if (!synchronouslockGraphicsContext.lock(0_s))
      //{

      //   return;

      //}

      //m_bUpdateBuffer = false;

      //m_bUpdateWindow = false;

      //m_puserinteraction->sketch_to_layout();

      //m_puserinteraction->layout_to_design(m_bUpdateBuffer, m_bUpdateWindow);

      ::draw2d::graphics_pointer pgraphics;

      m_puserinteraction->defer_do_graphics(pgraphics);



      //if (pgraphics)
      //{

      //   for (::index i = 0; i < pgraphics->m_rectangleaNeedRedraw.size();)
      //   {

      //      bool bErasedAny = false;

      //      for (::index j = 0; j < m_rectangleaNeedRedraw.size();)
      //      {

      //         if (pgraphics->m_rectangleaNeedRedraw[i] == m_rectangleaNeedRedraw[j])
      //         {

      //            m_rectangleaNeedRedraw.erase_at(j);

      //            bErasedAny = true;

      //         }
      //         else
      //         {

      //            j++;

      //         }

      //      }

      //      if (bErasedAny)
      //      {

      //         pgraphics->m_rectangleaNeedRedraw.erase_at(i);

      //      }
      //      else
      //      {

      //         i++;

      //      }

      //   }

      if (m_redrawitema.has_element())
      {

         auto iRequestsDuringDrawing = m_redrawitema.size();

         //information() << iRequestsDuringDrawing << " redraw requests while drawing.";

      }

      //}

   //}

//#if TIME_REPORTING
//
//   auto elapsed = timeStart.elapsed();
//
//   informationf("_001UpdateBuffer " + as_string(elapsed.floating_millisecond().m_d) + "ms\n");
//
//#endif


   }


   void interaction_impl::top_down_prefix()
   {

      m_puserinteraction->top_down_prefix();

   }


   void interaction_impl::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::primitive_impl::_001OnNcClip(pgraphics);

   }


   void interaction_impl::defer_do_graphics(::draw2d::graphics_pointer & pgraphics)
   {


      //{

      //m_puserinteraction->top_down_prefix();

      //m_puserinteraction->layout_to_design();

      ::draw2d::lock draw2dlock(this);


      {


         _synchronous_lock slGraphics(m_pgraphicsgraphics->synchronization());

         //windowing::graphics_lock graphicslock(m_pwindow);

         //m_pgraphics->update_buffer(rectangleWindow.size());



         auto pbufferitem = m_pgraphicsgraphics->on_begin_draw(e_graphics_layout);
         //auto pparticleSynchronization = m_pgraphics->get_buffer_item()->m_pmutex;

         if (!pbufferitem)
         {

            return;

         }

         _synchronous_lock synchronouslock(pbufferitem->m_pmutex);


         //information() << "graphics::on_begin_draw";

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (has_destroying_flag())
         {

            return;

         }

         //::pointer < ::draw2d::graphics > pgraphics = pbufferitem->g();

         pgraphics = pbufferitem->g();



         //#ifdef UNIVERSAL_WINDOWS
         if (::is_null(pgraphics) || pgraphics->nok())
         {

            //#define SEVERITY_HIGH 5

                        //int iSeverity = SEVERITY_HIGH;

                        //for(index i = 0; i < iSeverity * 20; i++)
                        //{

            informationf("m_pgraphics->on_begin_draw FAILED (1)\n");

            //}

            return;

         }

         {

            //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
            //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
            //#endif

            pgraphics->payload("set_transparent") = "";

            pgraphics->m_pgraphicsgraphics = m_pgraphicsgraphics;

            pgraphics->m_pgraphicsbufferitem = pbufferitem;

            pgraphics->on_begin_draw();

            pgraphics->reset_clip();

            pgraphics->set_origin(0., 0.);

            //{

            //   _synchronous_lock synchronouslock(synchronization());

            //   pgraphics->__construct_new(pgraphics->m_puserredraw);

            //   pgraphics->user_redraw()->m_pgraphics = pgraphics;

            //   pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

            //   if (m_redrawitema.has_element())
            //   {

            //      throw "what?!?!";

            //   }

            //}



            //pgraphics->m_egraphics = e_graphics_layout;

            //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
            //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
            //#endif

            //pgraphics->payload("set_transparent") = "";

            //pgraphics->m_pgraphicsgraphics = m_pgraphics;

            //pgraphics->m_pgraphicsbufferitem = pbufferitem;

            //pgraphics->on_begin_draw();

            //pgraphics->reset_clip();

            //pgraphics->set_origin(0., 0.);


            {

               _synchronous_lock synchronouslock(synchronization());

               if (pgraphics->__defer_construct_new(pgraphics->m_puserredraw))
               {

                  if (system()->m_paurasystem->draw2d()->graphics_context_does_full_redraw())
                  {

                     pgraphics->m_puserredraw->m_bEnabled = false;

                  }

               }

               if (pgraphics->m_puserredraw->m_bEnabled)
               {

                  pgraphics->user_redraw()->m_pgraphics = pgraphics;

                  pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

                  if (m_redrawitema.has_element())
                  {

                     throw "what?!?!";

                  }

               }

            }



            //if (!bDraw)
            //{

            //   if (pgraphics->m_rectangleaNeedRedraw.has_element())
            //   {

            //      bDraw = true;

            //   }

            //}

            pgraphics->m_pdraw2dhost = m_puserinteraction;

            pgraphics->m_puserstyle.release();

            if (pgraphics->m_pimage)
            {

               pgraphics->m_pimage->m_rectangleTag.Null();

               //sizeDrawn = pgraphics->m_pimage->m_size;

               ///sizeDrawn = m_puserinteraction->const_layout().design().size();

            }

            string strBitmapSource = payload("bitmap-source");

            if (strBitmapSource.has_char())
            {

               //            ::pointer < ::graphics::bitmap_source_buffer > pbitmapsourcebuffer = pgraphics;
               //
               //            if(pbitmapsourcebuffer)
               //            {
               //
               //
               //
               //
               //            }

            }

            if (m_puserinteraction)
            {

               //auto r = m_puserinteraction->screen_rect();

               if (m_puserinteraction->has_finishing_flag())
               {

                  informationf("::user::interaction_impl set_finish");

               }
               else
               {

                  //pgraphics->m_bDraw = bDraw;

                  pgraphics->m_bDraw = false;

                  pgraphics->m_bInheritDraw = false;

                  //            pgraphics->fill_solid_rectangle({ 0, 0, 200, 200 }, ::color::green);
#ifdef MORE_LOG
                  information() << "defer_do_graphics _000TopCallOnLayout";
#endif
                  m_puserinteraction->_000TopCallOnLayout(pgraphics);

                  //m_puserinteraction->_000CallOnDraw(pgraphics);

                  //                  if (!bDraw && m_redrawa.has_element())
                  //                  {
                  //
                  //                     synchronouslock.unlock();
                  //
                  //                     bDraw = true;
                  //
                  //                     pgraphics->m_bDraw = bDraw;
                  //
                  //                     m_puserinteraction->_000CallOnDraw(pgraphics);
                  //
                  //                  }

               }

               //m_rectangleUpdateBuffer = r;

               //informationf("PrintBuffer (%d, %d)",  r.right(), r.bottom());

               //if (!m_pgraphics)
               //{

               //   return;

               //}

               //m_pgraphics->m_bNewBuffer = true;

            }

            ////if (pgraphics->m_pimage.ok())
            ////{

            ////   //pgraphics->m_pimage->m_rectangleTag = m_rectangleUpdateBuffer;

            ////   //m_sizeDrawn = sizeDrawn;

            ////   pgraphics->m_sizeDrawnAnnotation = sizeDrawn;

            ////}

            //m_sizeLastBuffer = pbufferitem->m_size;

            ////}

            //if (m_pgraphics)
            //{

            //   m_pgraphics->on_end_draw();

            //}

         }

      }

      {


         _synchronous_lock slGraphics(m_pgraphicsgraphics->synchronization());

         //windowing::graphics_lock graphicslock(m_pwindow);

         //m_pgraphics->update_buffer(rectangleWindow.size());



         auto pbufferitem = m_pgraphicsgraphics->on_begin_draw(e_graphics_draw);
         //auto pparticleSynchronization = m_pgraphics->get_buffer_item()->m_pmutex;

         if (!pbufferitem)
         {

            information() << "defer_do_graphics !pbufferitem";

            return;

         }

         _synchronous_lock synchronouslock(pbufferitem->m_pmutex);


         //information() << "graphics::on_begin_draw";

         slGraphics.unlock();

         windowing_output_debug_string("\n_001UpdateBuffer : after on_begin_draw");

         if (has_destroying_flag())
         {

            information() << "defer_do_graphics has_destroying_flag()";

            return;

         }

         //::pointer < ::draw2d::graphics > pgraphics = pbufferitem->g();

         pgraphics = pbufferitem->g();



         //#ifdef UNIVERSAL_WINDOWS
         if (::is_null(pgraphics) || pgraphics->nok())
         {

            //#define SEVERITY_HIGH 5

                        //int iSeverity = SEVERITY_HIGH;

                        //for(index i = 0; i < iSeverity * 20; i++)
                        //{

            information() << "m_pgraphics->on_begin_draw FAILED (1)";

            //}

            return;

         }

         {

            //pgraphics->m_egraphics = e_graphics_draw;

            //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
            //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
            //#endif

            pgraphics->payload("set_transparent") = "";

            pgraphics->m_pgraphicsgraphics = m_pgraphicsgraphics;

            pgraphics->m_pgraphicsbufferitem = pbufferitem;

            pgraphics->on_begin_draw();

            pgraphics->reset_clip();

            pgraphics->set_origin(0., 0.);

            //{

            //   _synchronous_lock synchronouslock(synchronization());

            //   pgraphics->__construct_new(pgraphics->m_puserredraw);

            //   pgraphics->user_redraw()->m_pgraphics = pgraphics;

            //   pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

            //   if (m_redrawitema.has_element())
            //   {

            //      throw "what?!?!";

            //   }

            //}



            //pgraphics->m_egraphics = e_graphics_layout;

            //ASSERT(!(pgraphics->m_egraphics & e_graphics_from_context));
            //ASSERT(pgraphics->m_egraphics & (e_graphics_layout | e_graphics_draw));
            ////#endif

            //pgraphics->payload("set_transparent") = "";

            //pgraphics->m_pgraphicsgraphics = m_pgraphics;

            //pgraphics->m_pgraphicsbufferitem = pbufferitem;

            //pgraphics->on_begin_draw();

            //pgraphics->reset_clip();

            //pgraphics->set_origin(0., 0.);

            //{

            //   _synchronous_lock synchronouslock(synchronization());

            //   pgraphics->__construct_new(pgraphics->m_puserredraw);

            //   pgraphics->user_redraw()->m_pgraphics = pgraphics;

            //   pgraphics->user_redraw()->initialize_and_transfer(m_redrawitema);

            //   if (m_redrawitema.has_element())
            //   {

            //      throw "what?!?!";

            //   }

            //}



            //if (!bDraw)
            //{

            //   if (pgraphics->m_rectangleaNeedRedraw.has_element())
            //   {

            //      bDraw = true;

            //   }

            //}

            //pgraphics->m_pdraw2dhost = m_puserinteraction;

            //pgraphics->m_puserstyle.release();

            //if (pgraphics->m_pimage)
            //{

            //   pgraphics->m_pimage->m_rectangleTag.Null();

            //   //sizeDrawn = pgraphics->m_pimage->m_size;

            //   ///sizeDrawn = m_puserinteraction->const_layout().design().size();

            //}

            //string strBitmapSource = payload("bitmap-source");

            //if (strBitmapSource.has_char())
            //{

            //   //            ::pointer < ::graphics::bitmap_source_buffer > pbitmapsourcebuffer = pgraphics;
            //   //
            //   //            if(pbitmapsourcebuffer)
            //   //            {
            //   //
            //   //
            //   //
            //   //
            //   //            }

            //}

            if (m_puserinteraction)
            {

               //auto r = m_puserinteraction->screen_rect();

               if (m_puserinteraction->has_finishing_flag())
               {

                  informationf("::user::interaction_impl set_finish");

               }
               else
               {

                  //pgraphics->m_bDraw = bDraw;

                  pgraphics->m_bDraw = true;

                  pgraphics->m_bInheritDraw = true;

                  //            pgraphics->fill_solid_rectangle({ 0, 0, 200, 200 }, ::color::green);


#ifdef MORE_LOG
                  information() << "defer_do_graphics _000TopCallOnDraw";
#endif
                  m_puserinteraction->_000TopCallOnDraw(pgraphics);

                  //m_puserinteraction->_000CallOnDraw(pgraphics);

                  //                  if (!bDraw && m_redrawa.has_element())
                  //                  {
                  //
                  //                     synchronouslock.unlock();
                  //
                  //                     bDraw = true;
                  //
                  //                     pgraphics->m_bDraw = bDraw;
                  //
                  //                     m_puserinteraction->_000CallOnDraw(pgraphics);
                  //
                  //                  }

               }

               //m_rectangleUpdateBuffer = r;

               //informationf("PrintBuffer (%d, %d)",  r.right(), r.bottom());

               if (!m_pgraphicsgraphics)
               {

                  return;

               }

               m_pgraphicsgraphics->m_bNewBuffer = true;

            }
            else
            {


               information() << "defer_do_graphics !m_puserinteraction";

            }

            //if (pgraphics->m_pimage.ok())
            //{

            //   //pgraphics->m_pimage->m_rectangleTag = m_rectangleUpdateBuffer;

            //   //m_sizeDrawn = sizeDrawn;

            //   pgraphics->m_sizeDrawnAnnotation = sizeDrawn;

            //}

            m_sizeLastBuffer = pbufferitem->m_size;

            //}

            if (m_pgraphicsgraphics)
            {

               m_pgraphicsgraphics->on_end_draw();

            }

         }

      }

   }


   //void interaction_impl::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   m_bUpdateBuffer = false;

   //   m_bUpdateWindow = false;

   //   if (m_puserinteraction->should_perform_layout(pgraphics))
   //   {

   //      m_puserinteraction->perform_layout(pgraphics);

   //   }

   //}


   //void interaction_impl::_defer_start_prodevian()
   //{

   //   defer_fork("prodevian", [&]() { _thread_prodevian(); });

   //}


   void interaction_impl::set_prodevian_frames_per_second(::frequency frequencyProdevianFramesPerSecond)
   {

      m_frequencyProdevianFramesPerSecond = frequencyProdevianFramesPerSecond;

      if (::is_set(m_pgraphicsthread))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pgraphicsthread->set_fps_interest_frames_per_second(m_frequencyProdevianFramesPerSecond);

         }

      }

   }


   void interaction_impl::set_nominal_frames_per_second(::frequency frequencyNominalFramesPerSecond)
   {

      m_frequencyNominalFramesPerSecond = frequencyNominalFramesPerSecond;

      if (::is_set(m_pgraphicsthread))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pgraphicsthread->set_nominal_frames_per_second(m_frequencyNominalFramesPerSecond);

         }

      }

   }


   void interaction_impl::set_per_second(::frequency frequencyFramesPerSecond)
   {

      m_frequencyNominalFramesPerSecond = frequencyFramesPerSecond;

      m_frequencyProdevianFramesPerSecond = frequencyFramesPerSecond;

      if (::is_set(m_pgraphicsthread))
      {

         if (::is_set(m_puserinteraction) && m_puserinteraction->is_graphical())
         {

            m_pgraphicsthread->set_per_second(frequencyFramesPerSecond);

         }

      }

   }


   ::frequency interaction_impl::get_prodevian_frames_per_second()
   {

      return m_frequencyProdevianFramesPerSecond;

   }


   ::frequency interaction_impl::get_nominal_frames_per_second()
   {

      return m_frequencyNominalFramesPerSecond;

   }


   ::frequency interaction_impl::get_output_per_second()
   {

      return m_frequencyOutputFramesPerSecond;

   }


//   void interaction_impl::start_window_visual()
//   {
//
//      if (m_puserthread)
//      {
//
//         m_puserthread->start_window_visual();
//
//      }
//      else
//      {
//
//         m_puserinteraction->post_message(e_message_apply_visual);
//
//      }
//
//      //return true;
//
//   }


   void interaction_impl::_001UpdateWindow()
   {

   }


//   void interaction_impl::_001UpdateScreen()
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization());
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      if (m_bOfflineRender)
//      {
//
//         return;
//
//      }
//
//      string strType = ::type(m_puserinteraction).name();
//
//      if (strType.case_insensitive_contains("list_box"))
//      {
//
//         auto edisplay = m_puserinteraction->const_layout().state(e_layout_design).display();
//
//         bool bGraphicsSet = m_pgraphics.is_set();
//
//         informationf("_001UpdateScreen list_box");
//
//      }
//
//      if (m_pgraphics.is_set())
//      {
//
//         if (m_puserinteraction->layout().is_this_screen_visible())
//         {
//
//            //            //CINFO(prodevian)("going to update_window (1)");
//            //
//            //            auto puserinteraction = m_puserinteraction.m_p;
//            //
//            //            int* pi = (int*)puserinteraction;
//            //
//            //            auto& i = *pi;
//            //
//            //            //monitor_pointer(puserinteraction);
//            //
//            //            auto& iStateCount = m_puserinteraction->layout().m_iStateCount;
//            //
//            //            monitor_pointer(&iStateCount);
//            //
//            //            m_pgraphics->update_screen();
//
//            m_pwindow->window_update_screen_buffer();
//
//            //m_puserinteraction->set_layout_state(m_puserinteraction->const_layout().design(), ::user::e_layout_window);
//
//         }
//
//      }
//
//   }


   void interaction_impl::process_message()
   {

      while (true)
      {

         ::pointer<::message::message>pmessage;

         {

            _synchronous_lock synchronouslock(this->synchronization());

            if (m_messagelist.is_empty())
            {

               return;

            }

            pmessage = ::transfer(m_messagelist.pick_head());

         }

         message_handler(pmessage);

      }

   }


   void interaction_impl::queue_message_handler(::message::message * pmessage)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      bool bWasEmpty = m_messagelist.is_empty();

      m_messagelist.add_tail(pmessage);

      if (bWasEmpty)
      {

         m_puserinteraction->m_pthreadUserInteraction->kick_idle();

      }

   }


   void interaction_impl::set_bitmap_source(const string & strBitmapSource)
   {

      m_strBitmapSource = strBitmapSource;

      if (m_pgraphicsgraphics)
      {

         m_pgraphicsgraphics->set_bitmap_source(strBitmapSource);

      }

      //return ::success;

   }


   void interaction_impl::clear_bitmap_source()
   {

      m_strBitmapSource.empty();

      if (m_pgraphicsgraphics)
      {

         m_pgraphicsgraphics->clear_bitmap_source();

      }

      //return ::success;

   }


   void interaction_impl::update_graphics_resources()
   {

      single_lock synchronouslock(this->synchronization());

      if (m_pgraphicsgraphics.is_null())
      {

         //auto estatus =

         __raw_construct(m_pgraphicsgraphics);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         if (m_pgraphicsgraphics)
         {

            m_pgraphicsgraphics->initialize_graphics_graphics(this);

         }

      }

      //m_pgraphics.is_set() ? ::success : ::error_failed;

   }


   void interaction_impl::interaction_post(const ::procedure & procedure)
   {

      auto puserinteraction = m_puserinteraction;

      if (::is_null(puserinteraction))
      {

         //return error_failed;

         throw ::exception(error_wrong_state);

      }

      auto puserthread = puserinteraction->m_pthreadUserInteraction;

      if (::is_null(puserthread))
      {

         throw ::exception(error_wrong_state);

      }

      puserthread->post_procedure(procedure);

   }


   guie_message_wnd::guie_message_wnd(::property_object * pparticle)
   {

      m_puiForward = nullptr;

   }


   void guie_message_wnd::message_handler(::message::message * pmessage)
   {

      if (m_puiForward != nullptr)
      {

         return m_puiForward->message_handler(pmessage);

      }

   }


   //CLASS_DECL_AURA void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction,const ::rectangle_i32 & rectangle)
   //{

   //   ASSERT(::is_set(pinteraction));

   //   ::pointer<::user::interaction>puiParent = pinteraction->get_parent();

   //   ASSERT(puiParent != nullptr);

   //   ::rectangle_i32 rectangleOld;

   //   pinteraction->window_rectangle(rectangleOld);

   //   rectangleOld += puiParent->screen_to_client();

   //   pinteraction->place(rectangle);

   //   pinteraction->display(e_display_normal, e_activation_no_activate);

   //}


//   void interaction_impl::prodevian_redraw(bool bUpdateBuffer)
//   {
//
//      if (!m_pgraphicsthread)
//      {
//
//         return;
//
//      }
//
//      if (m_puserinteraction->m_ewindowflag & e_window_flag_embedded_prodevian)
//      {
//
//         m_pgraphicsthread->m_message.wParam |= 1;
//
//         m_pgraphicsthread->prodevian_iteration();
//
//      }
//      else
//      {
//
//         m_pgraphicsthread->post_message(e_message_redraw, bUpdateBuffer ? 1 : 0);
//
//      }
//
//   }


   void interaction_impl::set_finish(::particle * pparticleContextFinish)
   {

      if (!has_destroying_flag())
      {

         if (m_pgraphicsgraphics)
         {

            _synchronous_lock slGraphics(m_pgraphicsgraphics->synchronization());

            auto pbufferitem = m_pgraphicsgraphics->get_buffer_item();

            _synchronous_lock synchronouslock(pbufferitem->m_pmutex);

            slGraphics.unlock();

            set_destroying_flag();

         }

      }

      //return 

      ::user::primitive_impl::set_finish();

   }


//   void interaction_impl::prodevian_stop()
//   {
//
//      auto pgraphicsthread = m_pgraphicsthread;
//
//      if (::is_set(pgraphicsthread) && ::is_set(m_pgraphics))
//      {
//
//         {
//
//            _synchronous_lock slGraphics(m_pgraphics->synchronization());
//
//            auto pbufferitem = m_pgraphics->get_buffer_item();
//
//            _synchronous_lock synchronouslock(pbufferitem->m_pmutex);
//
//            slGraphics.unlock();
//
//            //pgraphicsthread->m_puserinteraction = nullptr;
//
//            //pgraphicsthread->m_pimpl = nullptr;
//
//            pgraphicsthread->set_finish();
//
//         }
//
//         //{
//
//         //   _synchronous_lock synchronouslock(this->synchronization());
//
//         //   _synchronous_lock slGraphics(m_pgraphics->synchronization());
//
//         //   m_pgraphicsthread);
//
//         //}
//
//      }
//
//   }


//   void interaction_impl::prodevian_update_screen()
//   {
//
//
//      //_001UpdateScreen();
//
//      //return true;
//
//   }


   //void interaction_impl::set_handle(::windowing::window * pwindow)
   //{

   //   //if (get_handle() != nullptr)
   //   //{

   //   //   oswindow_erase(get_handle());

   //   //   oswindow_erase_impl(this);

   //   //}

   //   //get_handle() = oswindow;

   //   //if (oswindow != nullptr)
   //   //{

   //   //   oswindow_assign(oswindow, this);

   //   //   _001BaseWndInterfaceMap();

   //   //}

   //}


   //void interaction_impl::attach(::windowing::window * pwindowNew)
   //{

   //   ASSERT(get_handle() == nullptr);

   //   ASSERT(oswindow_interaction(oswindowNew) == nullptr);

   //   if(oswindowNew == nullptr)
   //   {

   //      return false;

   //   }

   //   //set_handle(oswindowNew);

   //   ASSERT(psystem->ui_from_handle(get_handle()) == m_puserinteraction);

   //   return true;

   //}


   void interaction_impl::destroy()
   {

      return ::user::primitive_impl::destroy();

   }


   //oswindow interaction_impl::detach()
   //{

   //   ::windowing::window * pwindow = get_handle();

   //   if(oswindow != nullptr)
   //   {

   //      set_handle(nullptr);

   //   }

   //   return oswindow;

   //}


   //oswindow interaction_impl::get_oswindow() const
   //{
   //    
   //   if(!m_pwindow)
   //   {
   //      
   //      return nullptr;
   //      
   //   }

   //   return (oswindow) m_pwindow->oswindow();

   //}


   bool interaction_impl::is_composite()
   {

      return m_puserinteraction->m_ewindowflag & e_window_flag_composite;

   }


   ::graphics::graphics * interaction_impl::get_window_graphics()
   {

      return m_pgraphicsgraphics;

   }


   ::user::element * interaction_impl::get_keyboard_focus()
   {

      return m_puserinteractionKeyboardFocus;

   }


   void interaction_impl::on_prio_message_set_focus(::message::message * pmessage)
   {

      ::pointer<::message::set_keyboard_focus>psetkeyboardfocus(pmessage);

      //      on_final_set_keyboard_focus();
      //
      //if (m_puserinteraction->m_ewindowflag & e_window_flag_focus)
      //{
      //   
      //   return;
      //
      //}
      //
      //m_puserinteraction->m_ewindowflag |= e_window_flag_focus;

      on_final_set_keyboard_focus();

   }



   void interaction_impl::set_mouse_capture(::user::interaction * puserinteraction)
   {

      window()->set_mouse_capture();

      m_puserinteractionMouseCapture = puserinteraction;

   }


   bool interaction_impl::defer_release_mouse_capture(::user::interaction * puserinteraction)
   {

      if(puserinteraction != m_puserinteractionMouseCapture)
      {

         return false;

      }

      if(!window()->defer_release_mouse_capture())
      {

         return false;

      }

      m_puserinteractionMouseCapture.release();

      return true;

   }


   bool interaction_impl::on_keyboard_focus(::user::primitive * pfocus)
   {

      auto pwindowing = windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         strsize iBeg = 0;

         strsize iEnd = 0;

         pfocus->_001GetSel(iBeg, iEnd);

         string strText;

         pfocus->_001GetText(strText);

         auto pwindowing = windowing();

         auto ptexteditorinterface = pwindowing->get_text_editor_interface();

         ptexteditorinterface->set_editor_selection(iBeg, iEnd);

         ptexteditorinterface->set_editor_text(strText);

         ptexteditorinterface->show_software_keyboard();

      }

      return true;

   }



   //   void interaction_impl::on_final_set_keyboard_focus(::message::set_keyboard_focus * psetkeyboardfocus)
   void interaction_impl::on_final_set_keyboard_focus()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      information() << "on_final_set_keyboard_focus";

      if (m_puserinteractionKeyboardFocusRequest)
      {

         if (m_puserinteractionKeyboardFocusRequest == m_puserinteractionToKillKeyboardFocus)
         {

            m_puserinteractionToKillKeyboardFocus.release();

         }

         information() << "on_final_set_keyboard_focus : " << ::string(::type(m_puserinteractionKeyboardFocusRequest.m_p));

         if (m_puserinteractionKeyboardFocusRequest != m_puserinteractionKeyboardFocus)
         {

            information() << "on_final_set_keyboard_focus : (2)";

            auto puserinteractionKeyboardFocusOld = m_puserinteractionKeyboardFocus;

            m_puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocusRequest;

            m_puserinteractionKeyboardFocusRequest = nullptr;

            auto puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocus;

            if (puserinteractionKeyboardFocusOld)
            {

               puserinteractionKeyboardFocusOld->on_kill_keyboard_focus();

            }

            if (puserinteractionKeyboardFocus)
            {

               synchronouslock.unlock();

               puserinteractionKeyboardFocus->on_set_keyboard_focus();

            }

         }

      }
      //      else
      //      {
      //
      //         m_puserinteractionToKillKeyboardFocus = m_puserinteractionKeyboardFocus;
      //
      //         synchronouslock.unlock();
      //
      //         on_final_kill_keyboard_focus();
      //
      //      }

   }


   bool interaction_impl::keyboard_focus_OnKillFocus(::oswindow oswindowNew)
   {

      informationf("::android::interaction_impl::keyboard_focus_OnKillFocus() (1) \n");

      //      auto pwindowing = windowing();
      //
      //      auto ptexteditorinterface = pwindowing->get_text_editor_interface();
      //
      //      if (::is_set(ptexteditorinterface))
      //      {
      //
      //         ptexteditorinterface->hide_software_keyboard();
      //
      //      }


      //      _synchronous_lock synchronouslock(this->synchronization());
      //
      //      auto puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocus;
      //
      //      if (puserinteractionKeyboardFocus)
      //      {
      //
      //         m_puserinteractionKeyboardFocus.release();
      //
      //         synchronouslock.unlock();
      //
      //         puserinteractionKeyboardFocus->on_kill_keyboard_focus();
      //
      //      }

      return true;

   }

   bool interaction_impl::keyboard_focus_OnChildKillFocus()
   {

      informationf("::android::interaction_impl::keyboard_focus_OnChildKillFocus() (2) \n");

      auto pwindowing = windowing();

      auto ptexteditorinterface = pwindowing->get_text_editor_interface();

      if (::is_set(ptexteditorinterface))
      {

         ptexteditorinterface->hide_software_keyboard();

      }

      return true;

   }



   void interaction_impl::on_message_kill_focus(::message::message * pmessage)
   {

      ::pointer<::message::kill_keyboard_focus>pkillkeyboardfocus(pmessage);

      //if (!(m_puserinteraction->m_ewindowflag & e_window_flag_focus))
      //{

      //   return;

      //}

      //m_puserinteraction->m_ewindowflag -= e_window_flag_focus;

      on_final_kill_keyboard_focus();

   }

   //void interaction_impl::on_final_kill_keyboard_focus(::message::kill_keyboard_focus * pkillkeyboardfocus)

   void interaction_impl::on_final_kill_keyboard_focus()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      information() << "on_final_kill_keyboard_focus";

      auto puserinteractionKeyboardFocus = m_puserinteractionKeyboardFocus;

      m_puserinteractionKeyboardFocusRequest.release();

      m_puserinteractionKeyboardFocus.release();

      synchronouslock.unlock();

      if(puserinteractionKeyboardFocus)
      {

         puserinteractionKeyboardFocus->on_kill_keyboard_focus();

      }

   }


   //void interaction_impl::impl_set_keyboard_focus(::user::primitive * pprimitiveFocusNew)
   //{

   //   ::user::primitive * pprimitiveFocusOld = m_pprimitiveFocus;

   //   if(pprimitiveFocusOld == pprimitiveFocusNew)
   //   {

   //      return true;

   //   }

   //   auto oswindow = get_handle();

   //   auto oswindowPrevious = ::set_keyboard_focus(oswindow);

   //   m_pprimitiveFocus = pprimitiveFocusNew;

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusOld))
   //      {

   //         if(pprimitiveFocusOld->m_bFocus)
   //         {

   //            pprimitiveFocusOld->send_message(e_message_kill_focus);

   //         }

   //         pprimitiveFocusOld->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusNew))
   //      {

   //         if (!pprimitiveFocusNew->m_bFocus)
   //         {

   //            pprimitiveFocusNew->send_message(e_message_set_focus);

   //         }

   //         pprimitiveFocusNew->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


   //void interaction_impl::impl_erase_keyboard_focus(::user::primitive * pprimitiveFocusRemove)
   //{

   //   if (::is_null(pprimitiveFocusRemove))
   //   {

   //      return false;

   //   }

   //   ::user::primitive * pprimitiveFocusKillFocus = m_pprimitiveFocus;

   //   if (pprimitiveFocusKillFocus != pprimitiveFocusRemove)
   //   {

   //      return false;

   //   }

   //   m_pprimitiveFocus = nullptr;

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusKillFocus))
   //      {

   //         if (pprimitiveFocusKillFocus->m_bFocus)
   //         {

   //            pprimitiveFocusKillFocus->send_message(e_message_kill_focus);

   //         }

   //         pprimitiveFocusKillFocus->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


   //void interaction_impl::impl_clear_keyboard_focus()
   //{

   //   ::user::primitive * pprimitiveFocusKillFocus = m_pprimitiveFocus;

   //   m_pprimitiveFocus = nullptr;

   //   try
   //   {

   //      if (::is_set(pprimitiveFocusKillFocus))
   //      {

   //         if (pprimitiveFocusKillFocus->m_bFocus)
   //         {

   //            pprimitiveFocusKillFocus->send_message(e_message_kill_focus);

   //         }

   //         pprimitiveFocusKillFocus->set_need_redraw();

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


   //void interaction_impl::set_keyboard_focus(::user::primitive * pprimitive)
   //{

   //   if(::is_null(pprimitive))
   //   {

   //      impl_clear_keyboard_focus();

   //      return true;

   //   }

   //   auto pinteraction = m_puserinteraction;

   //   if (::is_null(pinteraction))
   //   {

   //      return false;

   //   }

   //   if (!pinteraction->is_ascendant_of(pprimitive, true))
   //   {

   //      return false;

   //   }

   //   impl_set_keyboard_focus(pprimitive);

   //   return true;

   //}


   //void interaction_impl::erase_keyboard_focus(::user::primitive * pprimitive)
   //{

   //   if (pprimitive == nullptr)
   //   {

   //      impl_erase_keyboard_focus(pprimitive);

   //      return true;

   //   }

   //   if (pprimitive == m_puserinteraction || pprimitive == this)
   //   {

   //      impl_erase_keyboard_focus(pprimitive);

   //      return true;

   //   }

   //   ::user::interaction * pinteraction = pprimitive->get_host_user_interaction();

   //   if (pinteraction == nullptr)
   //   {

   //      return false;

   //   }

   //   if (!m_puserinteraction->is_ascendant_of(pinteraction, true))
   //   {

   //      return false;

   //   }

   //   impl_erase_keyboard_focus(pprimitive);

   //   return true;

   //}


   void interaction_impl::clear_keyboard_focus(::user::primitive_impl * pprimitiveimplGainingFocusIfAny)
   {

      auto puserinteraction = m_puserinteraction;

      if (!puserinteraction)
      {

         throw ::exception(error_failed);

      }

      auto pwindow = puserinteraction->window();

      if (!pwindow)
      {

         throw ::exception(error_failed);

      }

      auto pwindowing = pwindow->windowing();

      if (!pwindowing)
      {

         throw ::exception(error_failed);

      }

      //::windowing::window* pwindowGainingFocusIfAny = nullptr;

      //if (pprimitiveimplGainingFocusIfAny)
      //{

      //   pwindowGainingFocusIfAny = pprimitiveimplGainingFocusIfAny->window();

      //}

      if (m_puserinteractionKeyboardFocusRequest == m_puserinteractionKeyboardFocus)
      {

         m_puserinteractionKeyboardFocusRequest.release();

      }

      m_puserinteractionToKillKeyboardFocus = m_puserinteractionKeyboardFocus;

      on_final_kill_keyboard_focus();

      //pwindowing->clear_keyboard_focus(pwindowGainingFocusIfAny);

      //auto puserinteraction = m_puserinteraction;

      //if (::is_null(puserinteraction))
      //{

      //   return false;

      //}

      //::user::interaction * pinteractionHost = puserinteraction->get_host_user_interaction();

      //if (::is_null(pinteractionHost))
      //{

      //   return false;

      //}

      //auto pimplHost = pinteractionHost->m_pimpl;

      //if (::is_null(pimplHost))
      //{

      //   return false;

      //}

      //pimplHost->impl_clear_keyboard_focus();

      //return false;

   }


   void interaction_impl::post_message(::message::message * pmessage)
   {

      //if (m_puserthread)
      //{

      //   _synchronous_lock synchronouslock(m_puserthread->synchronization());

      //   m_puserthread->m_messagebasea.add(pmessage);

      //   m_puserthread->kick_idle();

      //   return true;

      //}

      //m_puserinteraction->post_procedure(__routine([this, pmessage]()
      //{

        // return m_puserinteraction->message_handler(pmessage);

      //}));


      //return 

      m_puserinteraction->post_message(pmessage);

      //return true;

   }



   void interaction_impl::redraw_add(::particle * pparticle)
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      m_particleaRedraw.add(pparticle);

   }


   void interaction_impl::redraw_erase(::particle * pparticle)
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      m_particleaRedraw.erase(pparticle);

   }


   bool interaction_impl::has_redraw()
   {

      _synchronous_lock synchronouslock(mutex_redraw());

      return m_particleaRedraw.has_elements();

   }


   ::particle * interaction_impl::mutex_redraw()
   {

      if (m_pmutexRedraw == nullptr)
      {

         __construct(m_pmutexRedraw);

      }

      return m_pmutexRedraw;

   }


   bool interaction_impl::has_pending_graphical_update()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_particleaRedraw.has_elements())
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::on_after_graphical_update()
   {


      //#ifdef ANDROID
      //
      //      operating_system_driver::get()->m_bRedraw = true;
      //
      //#endif


   }


//   void interaction_impl::_window_request_presentation_locked()
//   {
//
//      m_pwindow->_window_request_presentation_locked();
//
//   }
//
//
//   void interaction_impl::_window_request_presentation_unlocked()
//   {
//
//      if (::is_null(m_puserinteraction))
//      {
//
//         return;
//
//      }
//
//      // Request / Incoming changes / Prepare Internal Buffer
//      auto & stateOutput = m_puserinteraction->const_layout().design();
//
//      // Current/Previous Window State
//      auto & stateWindow = m_puserinteraction->const_layout().window();
//
//      if (stateOutput == stateWindow)
//      {
//
//         return;
//
//      }
//
//      //information() << "Design.state != Window.state";
//
//      auto eactivationOutput = stateOutput.activation();
//
//      auto eactivationWindow = stateWindow.activation();
//
//      ::string_stream stringstreamUnchanged;
//
//      if (eactivationOutput != eactivationWindow)
//      {
//
//         //information() << "Design.activation != Window.activation " << (iptr) eactivationOutput.m_eenum << ", " << (iptr) eactivationWindow.m_eenum;
//
//      }
//      else
//      {
//
//         stringstreamUnchanged << ".activation:" << eactivationOutput;
//
//      }
//
//      auto edisplayOutput = stateOutput.display();
//
//      auto edisplayWindow = stateWindow.display();
//
//      if (edisplayOutput != edisplayWindow)
//      {
//
//         //information() << "Design.display != Window.display " << edisplayOutput << ", " << edisplayWindow;
//
//      }
//      else
//      {
//
//         stringstreamUnchanged << ".display:" << edisplayOutput;
//
//      }
//
//      auto pointOutput = stateOutput.origin();
//
//      auto pointWindow = stateWindow.origin();
//
//      if (pointOutput != pointWindow)
//      {
//
//         //information() << "Design.point != Window.point " << pointOutput << ", " << pointWindow;
//
//      }
//      else
//      {
//
//         stringstreamUnchanged << ".origin:" << pointOutput;
//
//      }
//
//      auto sizeOutput = stateOutput.size();
//
//      auto sizeWindow = stateWindow.size();
//
//      if (sizeOutput != sizeWindow)
//      {
//
//         //information() << "Design.size != Window.size " << sizeOutput << ", " << sizeWindow;
//
//      }
//      else
//      {
//
//         stringstreamUnchanged << ".size:" << sizeOutput;
//
//      }
//
//      auto zOutput = stateOutput.zorder();
//
//      auto zWindow = stateWindow.zorder();
//
//      if (zOutput != zWindow)
//      {
//
//         //information() << "Design.zorder != Window.zorder " << zOutput << ", " << zWindow;
//
//      }
//      else
//      {
//
//         stringstreamUnchanged << ".zorder:" << zOutput;
//
//      }
//
//      if (stringstreamUnchanged.as_string().has_char())
//      {
//
//         //information() << "==" << stringstreamUnchanged.as_string();
//
//      }
//
//      bool shouldGetVisible = ::is_screen_visible(edisplayOutput);
//
//      if (sizeOutput.is_empty())
//      {
//
//         information() << "window_show rectangleUi isEmpty";
//
//         return;
//
//      }
//
//      bool bWindowVisible = m_pwindow->is_window_visible();
//
//      __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_apply_visual);
//
//      //::u32 uFlags = 0;
//
//      //bool bLayered = GetExStyle() & WS_EX_LAYERED;
//
//      //if (bLayered)
//      {
//
//         //uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
//
//      }
//      //else
//      //{
//
//      //   uFlags |= SWP_ASYNCWINDOWPOS  | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
//
//      //}
//
//      //if (eactivationOutput & e_activation_no_activate)
//      //{
//
//      //   uFlags |= SWP_NOACTIVATE;
//
//      //}
//
//      // if GNOME
//      // if Xorg
//      // if Wayland
//
//   //#if !defined(LINUX)
//
//         //if(m_sizeDrawn != sizeOutput)
//         //{
//
//         //   informationf("blank borders (1), drawing extrapoation (1) or cut border (1)??\n");
//
//         //}
//
//         //sizeOutput = m_sizeDrawn;
//
//      bool bSize = true;
//
//      if (sizeWindow == sizeOutput)
//      {
//
//         bSize = false;
//
//         //uFlags |= SWP_NOSIZE;
//
//      }
//      else
//      {
//
//         //uFlags |= SWP_ASYNCWINDOWPOS | SWP_FRAMECHANGED | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
//         ////uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOCOPYBITS | SWP_DEFERERASE;
//         ////uFlags |= SWP_ASYNCWINDOWPOS | SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOCOPYBITS;
//
//      }
//
//      bool bMove = true;
//
//      if (pointWindow == pointOutput)
//      {
//
//         bMove = false;
//
//         //uFlags |= SWP_NOMOVE;
//
//      }
//
//      //#endif
//
//      bool bVisibilityChange = is_different(bWindowVisible, shouldGetVisible);
//
//      bool bShow = false;
//
//      bool bHide = false;
//
//      if (bVisibilityChange)
//      {
//
//         if (shouldGetVisible)
//         {
//
//            bShow = true;
//
//         }
//         else
//         {
//
//            bHide = true;
//
//         }
//
//      }
//      else
//      {
//
//         if (shouldGetVisible)
//         {
//
//            bShow = true;
//
//         }
//
//      }
//
//      //if (eactivationOutput & e_activation_no_activate)
//      //{
//
//      //   uFlags |= SWP_NOACTIVATE;
//
//      //}
//
//      bool bZ = zOutput.is_change_request();
//
//
//
//      //if (!bZ)
//      //{
//
//      //   uFlags |= SWP_NOZORDER;
//
//      //}
//
//      string strType = ::type(m_puserinteraction).name();
//
//      if (strType.contains("font_format"))
//      {
//
//         information() << "font_format going to gather Z-Ordering information";
//
//      }
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      ::zorder zorderNew = (bZ ? zOutput : ::zorder());
//
//      //      if (edisplayWindow == e_display_zoomed)
//      //      {
//      //
//      //         if (edisplayOutput != e_display_zoomed)
//      //         {
//      //
//      //            auto puserinteraction = m_puserinteraction;
//      //
//      //            if (puserinteraction)
//      //            {
//      //
//      //               puserinteraction->_001OnExitZoomed();
//      //
//      //            }
//      //
//      //         }
//      //
//      //      }
//
//            //int iVisibilityChageBefore = (is_ubunt() && edisplayOutput == e_display_zoomed);
//
//      int iVisibilityChageBefore = true;
//
//      if (iVisibilityChageBefore) {
//         if (edisplayOutput != edisplayWindow)
//            //&& !::conditional(bLayered, bHasSetWindowPosition)
//            //)
//         {
//
//            //#ifdef WINDOWS
//            //
//            //         bool bShowOutput = windows_show_window(edisplayOutput, eactivationOutput);
//            //
//            //         bool bShowWindow = windows_show_window(edisplayWindow, eactivationWindow);
//            //
//            //         if (is_different(bShowOutput, bShowWindow))
//            //#endif
//            //         {
//
//            m_puserinteraction->_window_show_change_visibility_unlocked();
//
//            //}
//
//         }
//      }
//
//      //if(is_ubunt())
//      {
//
//         if (edisplayOutput == e_display_zoomed)
//         {
//
//            bMove = true;
//            bSize = true;
//
//         }
//
//      }
//
//      //#endif
//            //m_puserinteraction->_on_show_window();
//      //
//      //               if (is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_visible,
//      //            m_puserinteraction->is_this_visible())
//      //            || is_different(m_puserinteraction->m_ewindowflag & e_window_flag_on_show_window_screen_visible,
//      //               m_puserinteraction->is_window_screen_visible()))
//      //         {
//      //
//      //            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_visible, m_puserinteraction->is_this_visible());
//      //
//      //            m_puserinteraction->m_ewindowflag.set(e_window_flag_on_show_window_screen_visible, m_puserinteraction->is_window_screen_visible());
//      //
//      //            m_puserinteraction->_on_show_window();
//      //
//      //         }
//
//
//      //bool bHasSetWindowPosition = false;
//
//      if (shouldGetVisible
//         //#ifdef WINDOWS_DESKTOP
//           //    && !bLayered
//         //#endif
//         && (
//            //#ifdef WINDOWS_DESKTOP
//            //               !bLayered
//            //#else
//                           //(uFlags & (SWP_NOMOVE | SWP_NOSIZE)) != (SWP_NOMOVE | SWP_NOSIZE)
//            //#endif
//            bMove
//            || bSize
//            || bVisibilityChange
//            || bZ
//            )
//         )
//      {
//
//         string strType = ::type(m_puserinteraction).name();
//
//         if (strType.contains("font_format"))
//         {
//
//            information() << "font_format going to SetWindowPos";
//
//         }
//         else if (strType.contains("textformat"))
//         {
//
//            information() << "text_format going to SetWindowPos";
//
//         }
//
//         // Commented on Windows
//         //if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
//         //{
//
//         //   m_bEatMoveEvent = !(uFlags & SWP_NOMOVE) || !(uFlags & SWP_NOSIZE);
//
//         //   m_bEatSizeEvent = !(uFlags & SWP_NOSIZE);
//
//         //}
//
//         //if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
//         //{
//
//         //   m_bPendingRedraw = true;
//
//         //}
//         // END Commented on Windows
//
//         ::point_i32 pointBottomRight = pointOutput + sizeOutput;
//
//         //informationf("SetWindowPos bottom_right " + as_string(pointBottomRight.x()) + ", " + as_string(pointBottomRight.y()) + "\n");
//
//   //#if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID)
//
//            //if (sizeOutput.cx() > m_sizeDrawn.cx() || sizeOutput.cy() > m_sizeDrawn.cy())
//            // if (sizeOutput != m_sizeDrawn)
//            // {
//
//            //    m_puserinteraction->set_need_layout();
//
//            //    //m_puserinteraction->set_need_redraw();
//
//            //    m_puserinteraction->post_redraw();
//
//            // }
//            // else
//         {
//               m_pwindow->_set_window_position_unlocked(
//               zorderNew,
//               pointOutput.x(),
//               pointOutput.y(),
//               sizeOutput.cx(),
//               sizeOutput.cy(),
//               eactivationOutput, !bZ, !bMove, !bSize, edisplayOutput);
//
//            m_sizeSetWindowSizeRequest = sizeOutput;
//
//         }
//
//         //::SetWindowPos(get_handle(), oswindowInsertAfter,
//         //   pointOutput.x(), pointOutput.y(),
//         //   sizeOutput.cx(), sizeOutput.cy(),
//         //   uFlags);
//
//   //#endif
//
//         if (g_pointLastBottomRight != pointBottomRight)
//         {
//
//            //sinformation() << "::user::interaction_impl::do_graphics Different Bottom Right design size" << m_puserinteraction->const_layout().design().size();
//
//            g_pointLastBottomRight = pointBottomRight;
//
//         }
//
//         zOutput.clear_request();
//
//         m_bOkToUpdateScreen = true;
//
//      }
//
//      if (!iVisibilityChageBefore) {
//
//         if (edisplayOutput != edisplayWindow)
//            //&& !::conditional(bLayered, bHasSetWindowPosition)
//            //)
//         {
//
//            //#ifdef WINDOWS
//            //
//            //         bool bShowOutput = windows_show_window(edisplayOutput, eactivationOutput);
//            //
//            //         bool bShowWindow = windows_show_window(edisplayWindow, eactivationWindow);
//            //
//            //         if (is_different(bShowOutput, bShowWindow))
//            //#endif
//            //         {
//
//            m_puserinteraction->_window_show_change_visibility_unlocked();
//
//            //}
//
//         }
//
//      }
//
//      if (eactivationOutput & e_activation_set_foreground)
//      {
//
//         //throw ::exception(todo);
//         //m_puserinteraction->set();
//
//         m_pwindow->_set_foreground_window_unlocked();
//
//      }
//
//      if (eactivationOutput & e_activation_set_active)
//      {
//
//         //throw ::exception(todo);
//         ///m_puserinteraction->XXXSetActiveWindow();
//
//         m_pwindow->_set_active_window_unlocked();
//
//      }
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      m_puserinteraction->set_display(m_puserinteraction->const_layout().design().display(), e_layout_window);
//
//      m_puserinteraction->reset_pending(e_layout_design);
//
//      m_puserinteraction->set_display(edisplayOutput, e_layout_design);
//
//      ::windowing::window * pwindowFocus = nullptr;
//
//      ::windowing::window * pwindowImpl = nullptr;
//
//      ::user::interaction_impl * pimplFocus = nullptr;
//
//      if (has_pending_focus() && m_puserinteraction != nullptr && m_puserinteraction->is_window_visible())
//      {
//
//         auto psession = get_session();
//
//         auto pimplFocus = psession->m_pimplPendingFocus2;
//
//         psession->m_pimplPendingFocus2 = nullptr;
//
//         auto pwindowing = windowing();
//
//         ::oswindow oswindow = pimplFocus->oswindow();
//
//         if (pimplFocus == this)
//         {
//
//            informationf("optimized out a set_keyboard_focus");
//
//         }
//         else
//         {
//
//            m_puserinteraction->set_keyboard_focus();
//
//         }
//
//      }
//
//      m_puserinteraction->m_bVisualChanged = true;
//
//      m_puserinteraction->check_transparent_mouse_events();
//
//   }


//   void interaction_impl::on_visual_applied()
//   {
//
//   }


   void interaction_impl::ShowWindow(const ::e_display & edisplay)
   {

      //return false;


   }


   void interaction_impl::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   void interaction_impl::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

      on_configuration_change(m_puserinteraction);

   }


   void interaction_impl::on_configuration_change(::user::primitive * pprimitiveSource)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (auto & puserinteraction : m_userinteractionaHideOnConfigurationChange.m_interactiona)
      {

         if (puserinteraction->is_window_screen_visible())
         {

            puserinteraction->hide();

            puserinteraction->set_need_redraw();

            puserinteraction->post_redraw();

         }

      }

   }


//   void interaction_impl::_window_show_change_visibility_unlocked(::e_display edisplay, ::e_activation eactivation)
//   {
//
//      //m_puserinteraction->m_pthreadUserInteraction->post_procedure([this, edisplay, eactivation]()
//        // {
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      __keep_flag_on(m_puserinteraction->layout().m_eflag, ::user::interaction_layout::flag_show_window);
//
//      if (edisplay == e_display_iconic)
//      {
//
//         if (eactivation == e_activation_no_activate)
//         {
//
//            m_pwindow->_show_window_unlocked(edisplay, eactivation);
//
//         }
//         else
//         {
//
//            m_pwindow->_show_window_unlocked(edisplay, eactivation);
//
//         }
//
//      }
//      else
//      {
//
//         m_pwindow->_show_window_unlocked(edisplay, eactivation);
//
//      }
//
//      if (m_puserinteraction)
//      {
//
//         m_puserinteraction->set_activation(e_activation_default, e_layout_design);
//
//      }
//
//         //});
//
//   }


   //void interaction_impl::_001OnRedraw(::message::message * pmessage)
   //{

   //   m_puserinteraction->prodevian_redraw(pmessage->m_wparam & 1);

   //}


//   void interaction_impl::_001OnDoShowWindow(::message::message * pmessage)
//   {
//
//      m_puserinteraction->_window_show_change_visibility();
//
//   }


//   void interaction_impl::_001OnApplyVisual(::message::message * pmessage)
//   {
//
//      if (!m_puserinteraction)
//      {
//
//         return;
//
//      }
//
//      string strType = ::type(m_puserinteraction).name();
//
//      if (strType.case_insensitive_contains("filemanager"))
//      {
//
//         information() << "filemanager apply visual";
//
//      }
//
//      if (m_puserinteraction->is_graphical())
//      {
//
//         window_show();
//
//         //if (::is_set(m_puserthread))
//         //{
//
//         //   m_puserthread->m_evApplyVisual.set_event();
//
//         //}
//
//      }
//
//   }

//                  auto pwindowing = windowing();
//
//                  if(pwindowing)
//                  {
//
//                     auto pdisplay = pwindowing->display();
//
//                     if(pdisplay)
//                     {
//
//                        auto pmonitor = pdisplay->get_best_monitor(rectangle);
//
//                        if(::is_set(pmonitor))
//                        {
//
//                           auto rectangleBig = pmonitor->monitor_rectangle();
//
//                           auto rectangleSmall = rectangleBig;
//
//                           rectangleSmall.deflate(rectangleBig.width() / 10, rectangleBig.height() / 10);
//
//                           auto pointDesign = m_puserinteraction->const_layout().design().origin();
//
//                           if(rectangle.top() >= rectangleBig.top() && rectangle.top() <= rectangleSmall.top()
//                           && rectangleRequest.top()>= rectangleBig.top() && rectangleRequest.top() <= rectangleSmall.top()
//                           && rectangleRequest.top() < rectangle.top())
//                           {
//
//                              pmonitor->set_workspace_rectangle_top(rectangle.top());
//
//                           }
//
//                           if(rectangle.left() >= rectangleBig.left() && rectangle.left() <= rectangleSmall.left()
//                              && rectangleRequest.left()>= rectangleBig.left() && rectangleRequest.left() <= rectangleSmall.left()
//                              && rectangleRequest.left() < rectangle.left())
//                           {
//
//                              pmonitor->set_workspace_rectangle_left(rectangle.left());
//
//                           }
//
//                           if(rectangle.right() >= rectangleSmall.right() && rectangle.right() <= rectangleBig.right()
//                              && rectangleRequest.right()>= rectangleSmall.right() && rectangleRequest.right() <= rectangleBig.right()
//                              && rectangleRequest.right() > rectangle.right())
//                           {
//
//                              pmonitor->set_workspace_rectangle_right(rectangle.right());
//
//                           }
//
//                           if(rectangle.bottom() >= rectangleSmall.bottom() && rectangle.bottom() <= rectangleBig.bottom()
//                              && rectangleRequest.bottom()>= rectangleSmall.bottom() && rectangleRequest.bottom() <= rectangleBig.bottom()
//                              && rectangleRequest.bottom() > rectangle.bottom())
//                           {
//
//                              pmonitor->set_workspace_rectangle_bottom(rectangle.bottom());
//
//                           }
//
//                        }
//
//                     }
//
//                  }

   //         if(!m_puserinteraction->is_window_resizing()
//             && !m_puserinteraction->is_window_repositioning()
//             && !m_puserinteraction->is_window_docking())


   void interaction_impl::on_configure(const ::rectangle_i32 & rectangle)
   {

      if(!m_puserinteraction->is_window_repositioning()
      && !m_puserinteraction->is_window_resizing()
      && !m_puserinteraction->is_window_docking())
      {

         m_puserinteraction->post_procedure([this, rectangle]()
                                            {

                                               _on_configure(rectangle);

                                            });

      }

   }


   void interaction_impl::_on_configure(const ::rectangle_i32 & rectangle)
   {

      if (m_puserinteraction->const_layout().sketch().display() !=
          e_display_iconic)
      {

         auto rectangleRequest = m_puserinteraction->const_layout().design().parent_raw_rectangle();

         auto rectangleWindow = m_puserinteraction->const_layout().window().parent_raw_rectangle();

         if (rectangle != rectangleRequest)
         {

            information() << "on configure; setting to window rectangle : "
                          << rectangle;

            auto point = rectangle.origin();

            auto size = rectangle.size();

            if (point != rectangleRequest.origin())
            {

               m_puserinteraction->set_position(point, e_layout_window);

               m_puserinteraction->set_position(point, e_layout_sketch);

               m_puserinteraction->set_reposition();

            }

            if (size != rectangleRequest.size())
            {

               m_puserinteraction->set_size(size, e_layout_window);

               m_puserinteraction->set_size(size, e_layout_sketch);

               m_puserinteraction->set_need_layout();

            }

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }
         else if (rectangle != rectangleWindow)
         {

            information()
               << "on configure; setting to window rectangle (2) : "
               << rectangle;

            if (rectangle.origin() != rectangleWindow.origin())
            {

               m_puserinteraction->set_position(rectangle.origin(),
                                                e_layout_window);

            }

            if (rectangle.size() != rectangleWindow.size())
            {

               m_puserinteraction->set_size(rectangle.size(), e_layout_window);

            }

         }

      }

   }

//   void interaction_impl::on_resize(const ::size_i32 & size)
//   {
//
//      if (m_puserinteraction->const_layout().sketch().display() != e_display_iconic)
//      {
//
//         //if (!m_pwindow->placement_log()->has_recent(size)
//         if(!m_puserinteraction->is_window_resizing()
//             && !m_puserinteraction->is_window_repositioning()
//             && !m_puserinteraction->is_window_docking())
//         {
//
//            m_puserinteraction->post_procedure([this, size]()
//            {
//
//               if(size != m_puserinteraction->const_layout().design().size())
//               {
//
//                  information() << "on resize; setting to window size : " << size;
//
//                  m_puserinteraction->set_size(size, e_layout_window);
//
//                  m_puserinteraction->set_size(size, e_layout_sketch);
//
//                  int cx = m_puserinteraction->const_layout().sketch().size().width();
//
//                  int cy = m_puserinteraction->const_layout().sketch().size().height();
//                  //         m_puserinteraction->layout().design().size() = m_puserinteraction->layout().window().size();
//
//
//                  m_puserinteraction->set_need_layout();
//
//                  m_puserinteraction->set_need_redraw();
//
//                  m_puserinteraction->post_redraw();
//
//               }
//               else if(size != m_puserinteraction->const_layout().window().size())
//               {
//
//                  information() << "on reposition; setting to window size (2) : " << size;
//
//                  m_puserinteraction->set_size(size, e_layout_window);
//
//               }
//
//
//            });
//
//         }
//
//      }
//
//   }


   void interaction_impl::on_message_reposition(::message::message * pmessage)
   {

      m_puserinteraction->m_pinteractionScaler->on_display_change(m_puserinteraction);

      if (m_bEatMoveEvent)
      {

         m_bEatMoveEvent = false;

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      //      if (m_puserinteraction->layout().m_eflag)
      //      {
      //
      //         return;
      //
      //      }

      ::pointer<::message::reposition>preposition(pmessage);

      //      if(m_puserinteraction->m_ewindowflag & e_window_flag_postpone_visual_update)
      //      {
      //
      //         return;
      //
      //      }

      //      bool bLayered = m_puserinteraction->GetExStyle() & WS_EX_LAYERED;
      //
      //#ifndef WINDOWS_DESKTOP
      //
      //      bLayered = false;
      //
      //#endif
      //
      //      if(!bLayered)
      //      {
      //
      //         m_puserinteraction->layout().sketch().origin() = preposition->m_point;
      //
      //         m_puserinteraction->screen_origin() = preposition->m_point;
      //
      //      }

               //m_pwindow->m_point = preposition->m_point;

      auto & layout = m_puserinteraction->const_layout();

      auto sketch_origin = layout.sketch().origin();

      auto window_origin = layout.window().origin();

      //information() << "interaction_impl::on_message_reposition preposition->m_point " << preposition->m_point;

      //information() << "interaction_impl::on_message_reposition window_origin " << window_origin;

      //information() << "interaction_impl::on_message_reposition sketch_origin " << sketch_origin;

      //if(preposition->m_point.x() == 0)
      //{

      //  information() << "interaction_impl::on_message_reposition x is zero";

      //}
      //m_puserinteraction->set_position(preposition->m_point, e_layout_window);

      if (!m_pwindow->is_iconic())
      {


         if (!m_pwindow->placement_log()->has_recent(preposition->m_point)
         && !m_puserinteraction->is_window_resizing()
         && !m_puserinteraction->is_window_repositioning()
            && !m_puserinteraction->is_window_docking())
         {

            information() << "interaction_impl::on_message_reposition " << preposition->m_point;

            m_puserinteraction->set_position(preposition->m_point, e_layout_sketch);

            m_puserinteraction->set_reposition();

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }

      }

      //if (m_puserinteraction->layout().is_moving())
      //{

        // information() << "\nWindow is Moving :: on_message_move";

      //}

      //m_puserinteraction->layout().sketch().origin() = preposition->m_point;

      //if (m_puserinteraction->layout().sketch().display() != e_display_normal)
      //{

        // m_puserinteraction->display(e_display_normal);

      //}

      //m_puserinteraction->set_reposition();

      //m_puserinteraction->set_need_redraw();

      //m_puserinteraction->post_redraw();

   //}

   }


   void interaction_impl::on_message_size(::message::message * pmessage)
   {

      if (m_bEatSizeEvent)
      {

         m_bEatSizeEvent = false;

         return;

      }

      if (m_bDestroyImplOnly)
      {

         return;

      }

      if (m_puserinteraction->layout().m_eflag)
      {

         return;

      }

      ::pointer<::message::size>psize(pmessage);

      //      bool bLayered = m_puserinteraction->GetExStyle() & WS_EX_LAYERED;
      //
      //#ifndef WINDOWS_DESKTOP
      //
      //      bLayered = false;
      //
      //#endif
      //
      //      if(!bLayered)
      //      {
      //
      //         m_puserinteraction->layout().window() = psize->m_size;
      //
      //      }

      //      if (m_puserinteraction->layout().sketch().size() != psize->m_size)
      //      {
      //
      //         m_puserinteraction->layout().sketch() = psize->m_size;
      //
      //         if (m_puserinteraction->layout().sketch().display() != e_display_normal)
      //         {
      //
      //            m_puserinteraction->display(e_display_normal);
      //
      //         }
      //
      //         m_puserinteraction->set_need_layout();
      //
      //         m_puserinteraction->set_need_redraw();
      //
      //         m_puserinteraction->post_redraw();
      //
      //      }

            //m_pwindow->m_size = psize->m_size;

      //m_puserinteraction->set_size(psize->m_size, e_layout_window);
      //m_puserinteraction->set_size(psize->m_size, e_layout_window);

      m_sizeSetWindowSizeRequest = psize->m_size;

      if (!m_pwindow->placement_log()->has_recent(psize->m_size)
      && !m_puserinteraction->is_window_resizing()
      && !m_puserinteraction->is_window_repositioning()
      && !m_puserinteraction->is_window_docking())
      {

         information() << "interaction_impl::on_message_size " << psize->m_size;

         m_puserinteraction->set_size(psize->m_size, e_layout_sketch);

         int cx = m_puserinteraction->const_layout().sketch().size().width();

         int cy = m_puserinteraction->const_layout().sketch().size().height();
         //         m_puserinteraction->layout().design().size() = m_puserinteraction->layout().window().size();


         m_puserinteraction->set_need_layout();

         m_puserinteraction->set_need_redraw();

         m_puserinteraction->post_redraw();

         //
         //         m_puserinteraction->post_redraw();


         //if (m_puserinteraction->layout().is_moving())
         //{

         // information() << "\nWindow is Moving :: on_message_move";

         //}

         //m_puserinteraction->layout().sketch().origin() = preposition->m_point;

         //if (m_puserinteraction->layout().sketch().display() != e_display_normal)
         //{

         // m_puserinteraction->display(e_display_normal);

         //}

   //         m_puserinteraction->set_reposition();
   //
   //         m_puserinteraction->set_need_redraw();
   //
   //         m_puserinteraction->post_redraw();

      }

   }




   void interaction_impl::_001OnDestroyWindow(::message::message * pmessage)
   {

      if (m_puserinteraction && ::type(m_puserinteraction).name().contains("notify_icon"))
      {

         information() << "notify_icon";

      }

      if (m_bDestroyImplOnly)
      {

         destroy_impl_only();

      }
      else if (m_puserinteraction)
      {

         m_puserinteraction->destroy_window();

         informationf("destroy_window");

      }

   }


   void interaction_impl::show_software_keyboard(::user::element * pelement)
   {

      throw ::interface_only();

   }


   void interaction_impl::hide_software_keyboard(::user::element * pelement)
   {

      throw ::interface_only();

   }


   void interaction_impl::non_top_most_upper_window_rects(::rectangle_i32_array & recta)
   {

      m_pwindow->non_top_most_upper_window_rects(recta);

   }


   bool interaction_impl::is_occluded()
   {

      ::rectangle_i32_array recta;

      non_top_most_upper_window_rects(recta);

      ::rectangle_i32 rectangle;

      m_puserinteraction->window_rectangle(rectangle);

      ::rectangle_i32 rTest;

      for (auto & rHigher : recta)
      {

         if (rTest.intersect(rHigher, rectangle))
         {

            return true;

         }

      }

      return false;

   }


   void interaction_impl::approximate_occlusion_rects(rectangle_i32_array & raTest)
   {

      raTest.erase_all();

      ::rectangle_i32_array ra;

      non_top_most_upper_window_rects(ra);

      if (ra.is_empty())
      {

         return;

      }

      ::rectangle_i32 rectangle;

      m_puserinteraction->window_rectangle(rectangle);

      for (auto & rHigher : ra)
      {

         ::rectangle_i32 rTest;

         if (rTest.intersect(rHigher, rectangle))
         {

            raTest.add(rTest);

         }

      }

      // First Exclude Full Intersections

   restartFullIntersectionExclusion:

      for (index i = 0; i < raTest.get_count(); i++)
      {

         for (index j = i + 1; j < raTest.get_count(); j++)
         {

            int iArea = raTest[i].area();

            int jArea = raTest[j].area();

            int iMinArea = maximum(iArea, jArea);

            if (raTest[i].intersection(raTest[j]).area() == iMinArea)
            {

               if (iArea == iMinArea)
               {

                  raTest.erase_at(i);

               }
               else
               {

                  raTest.erase_at(j);

               }

               goto restartFullIntersectionExclusion;

            }

         }

      }

      // Second Remove Partial Intersections which:
      // Intersection area is less than third the area of the rectangle_i32 with bigger area.

   restartPartialIntersectionExclusionEx:

      for (index i = 0; i < raTest.get_count(); i++)
      {

         for (index j = i + 1; j < raTest.get_count(); j++)
         {

            int iArea = raTest[i].area();

            int jArea = raTest[j].area();

            int iMaxArea = maximum(iArea, jArea);

            if (raTest[i].intersection(raTest[j]).area() < iMaxArea / 3)
            {

               if (iArea == iMaxArea)
               {

                  raTest.erase_at(j);

               }
               else
               {

                  raTest.erase_at(i);

               }

               goto restartPartialIntersectionExclusionEx;

            }

         }

      }

   }


   i64 interaction_impl::approximate_occlusion_area()
   {

      rectangle_i32_array ra;

      approximate_occlusion_rects(ra);

      return ra.total_area();

   }


   i64 interaction_impl::opaque_area(const ::rectangle_i32 & rect)
   {

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslock(pitem->m_pmutex);

      ::color::color colorTransparent(0);

      ::rectangle_i32 rectangle(rect);

      m_puserinteraction->screen_to_client()(rectangle);

      return rectangle.area() - pitem->m_pimage2->get_rgba_area(colorTransparent, rectangle);

   }


   i64 interaction_impl::_001GetRectTopLeftWeightedArea(const ::rectangle_i32 & rect)
   {

      ::rectangle_i32 rectangle(rect);

      m_puserinteraction->screen_to_client()(rectangle);

      return m_pgraphicsgraphics->_001GetTopLeftWeightedOpaqueArea(rectangle);

   }


   i64 interaction_impl::opaque_area()
   {

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslock(pitem->m_pmutex);

      ::color::color colorTransparent(0);

      ::rectangle_i32 rectangle;

      m_puserinteraction->window_rectangle(rectangle);

      return rectangle.area() - pitem->m_pimage2->get_rgba_area(colorTransparent);

   }


   i64 interaction_impl::_001GetTopLeftWeightedArea()
   {

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslock(pitem->m_pmutex);

      ::color::color colorTransparent(0);

      ::rectangle_i32 rectangle;

      m_puserinteraction->window_rectangle(rectangle);

      if (::is_null(m_pgraphicsgraphics))
      {

         return 0;

      }

      auto pimage = pitem->m_pimage2;

      if (::is_null(pimage))
      {

         return 0;

      }

      return pimage->_001GetTopLeftWeightedOpaqueArea(colorTransparent.u8_opacity());

   }


   i64 interaction_impl::approximate_occlusion_area_except_self_transparent()
   {

      rectangle_i32_array ra;

      approximate_occlusion_rects(ra);

      ::i64 cApproxOpaqueArea = 0;

      for (auto & r : ra)
      {

         cApproxOpaqueArea += opaque_area(r);

      }

      return cApproxOpaqueArea;

   }


   double interaction_impl::approximate_occlusion_rate_except_self_transparent()
   {

      return (double)approximate_occlusion_area_except_self_transparent() / (double)opaque_area();

   }


   i64 interaction_impl::_001GetTopLeftWeightedOccludedOpaqueArea()
   {

      rectangle_i32_array ra;

      approximate_occlusion_rects(ra);

      ::i64 cApproxOpaqueArea = 0;

      for (auto & r : ra)
      {

         cApproxOpaqueArea += _001GetRectTopLeftWeightedArea(r);

      }

      return cApproxOpaqueArea;

   }


   double interaction_impl::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      auto iWeightedOccludedOpaqueArea = _001GetTopLeftWeightedOccludedOpaqueArea();

      auto iWeightedOpaqueArea = _001GetTopLeftWeightedArea();

      double dWeightedOccludedOpaqueArea = (double)iWeightedOccludedOpaqueArea;

      double dWeightedOpaqueArea = (double)iWeightedOpaqueArea;

      double dRate = dWeightedOccludedOpaqueArea / dWeightedOpaqueArea;

      return dRate;

   }


   double interaction_impl::approximate_occlusion_rate()
   {

      return (double)approximate_occlusion_area() / (double)m_puserinteraction->layout().area();

   }


//   bool interaction_impl::is_there_graphics_output_interest() const
//   {
//
//      return m_particleaAutoRefresh;
//
//   }


//   ::graphics::enum_output_purpose interaction_impl::most_demanding_graphical_output_purpose() const
//   {
//
//      ::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;
//
//      for(auto & ppurpose : m_graphicaloutputpurposea)
//      {
//
//         if(ppurpose->m_epurpose > epurposeMostDemanding)
//         {
//
//            epurposeMostDemanding = ppurpose->m_epurpose;
//
//         }
//
//      }
//
//      return epurposeMostDemanding;
//
//   }


   bool interaction_impl::has_screen_output_purpose() const
   {

      //::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;

      for(auto & ppurpose : m_graphicaloutputpurposea)
      {

         if(ppurpose->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
         {

            return true;

         }

      }

      //return epurposeMostDemanding;

      return false;

   }


   bool interaction_impl::has_graphical_output_purpose() const
   {

      return m_graphicaloutputpurposea.has_element();

   }


   bool interaction_impl::has_fps_output_purpose() const
   {

      //::graphics::enum_output_purpose epurposeMostDemanding = ::graphics::e_output_purpose_none;

      for(auto & ppurpose : m_graphicaloutputpurposea)
      {

         if(ppurpose->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_fps)
         {

            return true;

         }

      }

      //return epurposeMostDemanding;

      return false;

   }


//   bool interaction_impl::is_this_visible(enum_layout elayout)
//   {
//
//      if (!m_puserinteraction)
//      {
//
//         return false;
//
//      }
//
////      if (m_bOfflineRender)
////      {
////
////         return true;
////
////      }
//
//      if (!(m_puserinteraction->m_ewindowflag & e_window_flag_is_window))
//      {
//
//         return false;
//
//      }
//
//      if (m_puserinteraction->m_ewindowflag & e_window_flag_not_visible)
//      {
//
//         return false;
//
//      }
//
//      if (!m_puserinteraction->const_layout().state(elayout).is_visible())
//      {
//
//         return false;
//
//      }
//
////      if(!m_puserinteraction->m_bVisible)
////      {
////
////         return false;
////
////      }
//
//      return true;
//
//   }


   //   strsize interaction_impl::get_window_text(char* sz, strsize s)
   //   {
   //
   //      if (!m_pwindow)
   //      {
   //
   //         return -1;
   //
   //      }
   //
   //      auto iSize = m_pwindow->get_window_text(sz, s);
   //
   //      return iSize;
   //
   //   }
   //
   //
   //
   //   void interaction_impl::get_window_text(string& str)
   //   {
   //
   //      if (!m_pwindow)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      m_pwindow->get_window_text(str);
   //
   //   }
   //
   //
   //   strsize interaction_impl::get_window_text_length()
   //   {
   //
   //      return -1;
   //
   //   }


   void interaction_impl::set_icon(::windowing::icon *)
   {

      //return ::success;

   }


   ::pointer<::windowing::icon>interaction_impl::get_icon() const
   {

      return nullptr;

   }


   void interaction_impl::set_tool_window(bool bSet)
   {

      return m_pwindow->set_tool_window(bSet);

   }


   void interaction_impl::android_fill_plasma(const void * pixels, int width, int height, int stride, ::i64 time_ms)
   {

      auto pitem = m_pgraphicsgraphics->get_screen_item();

      _synchronous_lock synchronouslock(pitem->m_pmutex);

      //_synchronous_lock synchronouslock(pitem->m_pmutex);

      auto pimageSource = pitem->m_pimage2;

      pimageSource->map();

      auto wSource = pimageSource->width();

      auto hSource = pimageSource->height();

      auto pdataSource = pimageSource->get_data();

      auto scanSource = pimageSource->m_iScan;

#ifdef __i386__

      ::copy_image32_swap_red_blue((image32_t *)pixels, minimum(width, wSource), minimum(height, hSource), stride, pdataSource, scanSource);

#else

      ::copy_image32((image32_t *)pixels, minimum(width, wSource), minimum(height, hSource), stride, pdataSource, scanSource);

#endif

   }


   ::oswindow interaction_impl::oswindow() const
   {

      return m_pwindow->m_oswindow;

   }


   ::user::interaction_impl * message_interaction_impl(::user::message * pusermessage)
   {

      auto pwindow = pusermessage->window();

      return pwindow ? pwindow->m_puserinteractionimpl : nullptr;

   }


} // namespace user


CLASS_DECL_AURA::user::interaction * __interaction(::windowing::window * pwindow)
{

   if (::is_null(pwindow)) return nullptr;

   auto puserinteractionimpl = pwindow->m_puserinteractionimpl;

   if (!puserinteractionimpl) return nullptr;

   return puserinteractionimpl->m_puserinteraction;

}


CLASS_DECL_AURA::user::interaction_impl * __interaction_impl(::windowing::window * pwindow)
{

   if (::is_null(pwindow)) return nullptr;

   auto pimpl = pwindow->m_puserinteractionimpl.m_p;

   if (::is_null(pimpl)) return nullptr;

   return pimpl;

}


