#include "framework.h"
#include "frame_interaction.h"
//#include "key.h"
#include "style.h"
#include "interaction_thread.h"
#include "user.h"
#include "acme/constant/id.h"
#include "acme/constant/user_key.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/pool.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/constant/message.h"
#include "acme/user/user/key.h"
#include "apex/handler/signal.h"
#include "aura/graphics/image/icon.h"
#include "aura/platform/application.h"
#include "aura/platform/draw_context2.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/user/user/alpha_source.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"


namespace user
{


   frame_interaction::frame_interaction()
   {

      m_puserframewindow = nullptr;
      m_bSnapToBars = false;
      m_bAddToTitle = false;
      m_bPrefixTitle = false;

      m_bDerivedHeight = false;
      m_bShowControlBox = true;
      m_bDefaultNotifyIcon2 = false;
      m_bCloseApplicationIfLastVisibleFrame = true;

   }


   frame_interaction::~frame_interaction()
   {

   }


   void frame_interaction::create_window()
   {

      //__øconstruct(windowing_window());

      //windowing_window()->create_window();

      ////void interaction::create_host(enum_parallelization eparallelization)
      //void interaction::create_host()
      //{

         information() << "interaction::create_host(1)";

         if (is_window())
         {

            throw ::exception(error_wrong_state);
            // need to change to destroy window
            // try to make synchronous
            //
            //start_destroying_window();

         }

         //      if (m_pusersystem
         //          && m_pusersystem->m_prequest
         //          && m_pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
         //      {
         //
         //         if (!const_layout().sketch().is_screen_visible())
         //         {
         //
         //            initial_frame_display();
         //
         //         //if(pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
         ////            {
         ////
         ////               information() << "LoadFrame sketch !is_screen_visible going to display_normal (1)";
         ////
         ////               display_normal(e_display_normal, ::user::e_activation_set_foreground);
         ////
         ////            }
         //
         //         }
         //
         //      }

         information() << "interaction::create_host(2)";

         //auto psession = //t_session();

         auto pwindowing = windowing();

         auto pwindowHost = pwindowing->get_application_host_window();

         information() << "interaction::create_host(3)";

         m_ewindowflag += e_window_flag_top_level;

         if (::is_set(pwindowHost))
         {

            information() << "interaction::create_host(3A)";
            
            ::cast < ::windowing::window > pwindowingwindowHost = pwindowHost;

            auto puserinteraction = pwindowingwindowHost->user_interaction();

            create_child(puserinteraction);

            //         pwindowHost->windowing_window()->this->set_need_layout();
            //
            //         pwindowHost->windowing_window()->this->set_need_redraw();
            //
            //         pwindowHost->windowing_window()->this->post_redraw();

            return;

         }

         //__refer(m_pthreadUserInteraction, ::get_task() REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);

         //if (m_pthreadUserInteraction)
         //{

         //   m_pthreadUserInteraction->uiptra().add(this);

         //}

         //try
         //{

         m_bUserElementOk = true;

         //::pointer<interaction_impl> pprimitiveimplNew;

         information() << "interaction::create_host(4)";

         //auto rectangle(this->screen_rectangle());

         /* 

          if (puserinteractionParent == nullptr && psession->get_user_interaction_host().is_set() && psession->get_user_interaction_host() != this)
          {

             puserinteractionParent = __user_interaction(psession->get_user_interaction_host());

          }

          if (puserinteractionParent == nullptr || puserinteractionParent->get_safe_handle() == (oswindow)MESSAGE_WINDOW_PARENT)
          {*/

          //auto estatus =

         //__øconstruct(windowing_window());

         information() << "interaction::create_host(5)";

         /*        if (!estatus)
                 {

                    return estatus;

                 }*/

                 //#ifdef WINDOWS_DESKTOP
                 //
                 //            wstring wstrClassName(pszClassName);
                 //
                 //            wstring wstrWindowName(pszWindowName);
                 //
                 //            ::user::system pusersystem(0, wstrClassName, wstrWindowName, uStyle, rectangle, pcreate);
                 //
                 //#else

                 //auto pusersystem = __allocate ::user::system(uExStyle, uStyle, rectangle, pcreate);

                 //#endif

                 //pusersystem->m_createstruct.hwndParent = ::is_set(puserinteractionParent) ? puserinteractionParent->get_safe_handle() : nullptr;


         //pprimitiveimplNew->create_host(this, eparallelization);
         // 

         //windowing_window()->m_puserinteraction = this;


         //windowing_window()->create_window();
         // 
         ::user::box::create_window();
         //if (!pprimitiveimplNew->create_host(this))
         //{

         //   m_pprimitiveimpl.release();

         //   pprimitiveimplNew.release();

         //}

         //}
         //else
         //{

         //   pprimitiveimplNew = __create_new < ::user::interaction_child >();

         //   //m_pdescriptor.defer_create(this);

         //   if (!pprimitiveimplNew->create_interaction(this, uStyle, rectangle, puserinteractionParent, pcreate))
         //   {

         //      pprimitiveimplNew.release();

         //      m_bUserElementOk = false;

         //      if (m_pthreadUserInteraction)
         //      {

         //         if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
         //         {

         //            m_pthreadUserInteraction->m_puiptraThread->erase(this);

         //         }

         //         __release(m_pthreadUserInteraction REFERENCING_DEBUGGING_COMMA_THIS);

         //      }

         //      return false;

         //   }

         //        }

         //}
         //catch (...)
         //{

         //   m_bUserElementOk = false;

         //   if (m_pthreadUserInteraction)
         //   {

         //      if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
         //      {

         //         m_pthreadUserInteraction->m_puiptraThread->erase(this);

         //      }

         //      __release(m_pthreadUserInteraction REFERENCING_DEBUGGING_COMMA_THIS);

         //   }

         //   //return false;

         //}

         //return true;

      //}


   }


   void frame_interaction::on_before_create_window(acme::windowing::window* pacmewindowingwindow)
   {

      ::user::box::on_before_create_window(pacmewindowingwindow);

      m_bMaximizeBox = true;
      m_bMinimizeBox = true;
      m_bResizeable = true;

   }


   void frame_interaction::destroy()
   {

      if (m_pacmewindowingwindow)
      {

         m_pacmewindowingwindow->destroy();

      }

      // ownership

      //if(m_pinteractiondraw2d)
      //{
      //if (m_pshapeaClip) m_pshapeaClip->destroy();
      if (m_pdrawcontext) m_pdrawcontext->destroy();

      m_puserstyleFrameInteraction.defer_destroy();

      m_pdrawicon.defer_destroy();
      //}
      m_pusersystem.defer_destroy();
      //      if (m_playout) m_playout->destroy();
      m_pgraphicscalla.defer_destroy();
      m_puserinteractionCustomWindowProc.defer_destroy();
      m_puiLabel.defer_destroy();
      //if (m_puseritema) m_puseritema->destroy_all();
      // tasks should not be destroyed in destroy
      //m_pform && m_pform != this && m_pform->destroy();
      if (m_palphasource) m_palphasource->destroy();
      //if (m_pdrawableBackground) m_pdrawableBackground->destroy();
      //if (m_pprimitiveimpl) m_pprimitiveimpl->destroy();
      if (m_pacmewindowingwindow) m_pacmewindowingwindow->destroy();

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_puserinteractionpointeraOwned) m_puserinteractionpointeraOwned->destroy();

      }

      ::pointer < ::windowing::window > pwindow = m_pacmewindowingwindow;

      if (pwindow)
      {

         _synchronous_lock synchronouslock(pwindow ? pwindow->m_pparticleChildrenSynchronization : nullptr);

         if (m_puserinteractionpointeraChild) m_puserinteractionpointeraChild->destroy();

      }

      //m_pthreadUserInteraction && m_pthreadUserInteraction->destroy();
      // tasks should not be destroyed in destroy
      //m_pthreadUserInteraction && m_pthreadUserInteraction->destroy();
      m_ptooltip.defer_destroy();
      m_pmenuitem.defer_destroy();
      m_menua.destroy();

      // ownership
      //if(m_pinteractiondraw2d)
      {
         //m_pshapeaClip.release();
         m_pdrawcontext.release();

      }

      m_pusersystem.release();
      ///m_playout.release();
      m_pgraphicscalla.release();
      m_puserinteractionCustomWindowProc.release();
      m_puiLabel.release();
      //if (m_puseritema) m_puseritema->erase_all();
      m_pform.release();
      m_palphasource.release();
      //m_pdrawableBackground.release();
      //m_pprimitiveimpl.release();
      //windowing_window().release();

      //windowing_window().release();

      //m_pacmew

      m_pinteractionScaler.defer_destroy();

      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_puserinteractionpointeraOwned.release();

      }

      ::pointer < ::windowing::window > pwindow2 = m_pacmewindowingwindow;

      if (pwindow2)
      {

         _synchronous_lock synchronouslock(pwindow2 ? pwindow2->m_pparticleChildrenSynchronization : nullptr);

         m_puserinteractionpointeraChild.release();

      }

      m_ptooltip.release();
      m_pmenuitem.release();
      m_menua.erase_all();


      // references
      m_pitemComposing.release();
      //m_pthreadUserInteraction.release();
      m_puserinteractionParent.release();
      m_pupdowntarget.release();
      m_ptaskModal.release();
      //windowing_window().release();
      //return ::success;
      ::user::box::destroy();
      ::user::drag_client::destroy();
      //::user::interaction_base::destroy();

   }


   //void frame_interaction::start_destroying_window()
   //{

   //   ::user::interaction::start_destroying_window();

   //   //window()->start_destroying_window();

   //}


   void frame_interaction::destroy_window()
   {

      ::user::interaction::destroy_window();

      //window()->destroy_window();

   }


   void frame_interaction::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);




      add_command_handler("try_close_application", { this, &frame_interaction::on_message_application_exit });
      

      MESSAGE_LINK(e_message_destroy, pchannel, this, &frame_interaction::on_message_destroy);
      MESSAGE_LINK(e_message_application_exit, pchannel, this, &frame_interaction::on_message_application_exit);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &frame_interaction::on_message_key_down);

      system()->signal(id_operating_system_user_color_change)->add_handler(this);
//#ifdef WINDOWS_DESKTOP
//
//      if (is_frame_window())
//      {
//
//         MESSAGE_LINK((::enum_message)WM_SYSCOMMAND, pchannel, this, &frame_interaction::_001OnSysCommand);
//
//      }
//
//#endif


   }

   
   void frame_interaction::on_message_destroy(::message::message * pmessage)
   {

      erase_graphical_output_purpose(this);

   }


   void frame_interaction::on_message_application_exit(::message::message* pmessage)
   {

      ::pointer<::user::message>pusermessage(pmessage);

      if (get_parent() != nullptr)
      {

         pmessage->m_bRet = false;

         return;

      }

      ::pointer<::aura::application>papp = get_app();

      papp->_001TryCloseApplication();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void frame_interaction::on_message_key_down(::message::message* pmessage)
   {

      ::pointer<::user::key>pkey(pmessage);
      
      if (get_parent() == nullptr)
      {

         
         if(pkey->m_ekey == ::user::e_key_q && session()->is_key_pressed(::user::e_key_command))
         {
            
            post_message(e_message_close);
            pmessage->m_bRet = true;
            
         }

         return;

      }

//      ::pointer<::aura::application>papp = get_app();
//
//      papp->_001TryCloseApplication();
//
//      if (pmessage != nullptr)
//      {
//
//         pmessage->m_bRet = true;
//
//      }

   }


   ::task_pool * frame_interaction::taskpool()
   {

      __defer_construct_new(m_ptaskpool);

      return m_ptaskpool;

   }


   //void frame_interaction::destroy()
   //{

   //   m_puserstyle.defer_destroy();

   //   ::user::box::destroy();

   //}

//   bool frame_interaction::is_os_host() const
//   {
//
//      return false;
//
//   }


   style * frame_interaction::get_style() const
   {

      return m_puserstyleFrameInteraction;

   }


   ::color::color frame_interaction::get_border_main_body_color()
   {

      return color::transparent;

   }


   void frame_interaction::add_menu_item(const ::string & strPath, const ::string & strText, const ::string & strId)
   {

      m_straMenuParent.add(strPath);
      m_straMenuName.add(strText);
      m_straMenuId.add(strId);

      //return ::success;

   }


   ::user::tool_window * frame_interaction::tool_window(enum_tool etool, bool bCreate)
   {

      return nullptr;

   }


//   ::user::toolbar * frame_interaction::get_toolbar(const ::atom & idToolBar)
//   {
//
//      return nullptr;
//
//   }


   void frame_interaction::add_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void frame_interaction::erase_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void frame_interaction::show_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void frame_interaction::hide_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


//   ::pointer<::utoolbar>frame_interaction::load_toolbar(const ::atom & idToolbar, const ::string & strToolbar, unsigned int dwCtrlStyle, unsigned int uStyle, const ::type_atom & typeatom)
//   {
//
//      return false;
//
//   }


   void frame_interaction::on_create_bars()
   {

      //return ::success;

   }


   bool frame_interaction::should_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

      if(m_bNeedPerformLayout)
      {
            
         return true;

      }

      if (size(e_layout_sketch) != size(e_layout_design))
      {

         return true;


      }

      return false;

   }



   ::user::interaction* frame_interaction::get_active_impact()
   {

      return nullptr;

   }


   void frame_interaction::set_active_impact(::user::impact* pImpactNew, bool bNotify)
   {


   }


   void frame_interaction::ActivateFrame(::e_display edisplay)
   {


   }



   void frame_interaction::set_frame_title(const string& strFrameTitle)
   {

      m_strFrameTitle = strFrameTitle;

      //auto pparent = get_parent();

      //if (pparent && pparent->is < ::user::place_holder >())
      //{

      //   set_place_child_title(m_strFrameTitle);

      //}

   }


   string frame_interaction::get_frame_title()
   {

      return m_strFrameTitle;

   }


   ::image::icon* frame_interaction::get_draw_icon()
   {

      if (::is_set(m_pdrawicon))
      {

         return m_pdrawicon;

      }

      auto pwindowingicon = get_windowing_icon();

      if (::is_null(pwindowingicon))
      {

         return nullptr;

      }

      ///auto estatus = 
      
      __øconstruct(m_pdrawicon);

      //if (!estatus)
      //{

      //   return nullptr;

      //}

      //estatus =
      
      m_pdrawicon->initialize_with_windowing_icon(pwindowingicon);

      //if (!estatus)
      //{

      //   return nullptr;

      //}

      return m_pdrawicon;

   }


   //void frame_interaction::this->rectangle(::int_rectangle* lprect)
   //{
   //   
   //   ::user::interaction::this->rectangle(lprect);
   //   
   //   if((m_ewindowflag & e_window_flag_top_level) && window())
   //   {
   //   
   //      lprect->top() += window()->get_top_margin();
   //      
   //   }
   //   
   //}


   ::color::color frame_interaction::get_moveable_border_color()
   {

      if (!m_puserstyleFrameInteraction)
      {

         return ::color::color();

      }

      return m_puserstyleFrameInteraction->get_style_moveable_border_color(m_estyle);

   }


   bool frame_interaction::is_translucid_user_style(enum_style estyle)
   {

      return
         estyle == ::user::StyleTranslucidWarmGray
         || estyle == ::user::StyleTranslucidLightBlue
         || estyle == ::user::StyleTranslucidLightGreen
         || estyle == ::user::StyleTranslucidWarmLiteGray;

   }


   ::user::enum_style frame_interaction::translate_user_style(const ::string & pszStyle)
   {

      string strStyle(pszStyle);

      if (strStyle == "TranslucidLightBlue")
      {

         return StyleTranslucidLightBlue;

      }
      else if (strStyle == "DarkRed")
      {

         return StyleDarkRed;

      }
      else if (strStyle == "TranslucidLightGreen")
      {

         return StyleTranslucidLightGreen;

      }
      else if (strStyle == "TranslucidWarmGray")
      {

         return StyleTranslucidWarmGray;

      }
      else if (strStyle == "TranslucidWarmLiteGray")
      {

         return StyleTranslucidWarmLiteGray;

      }
      else if (strStyle == "DarkWarmBlue")
      {

         return StyleDarkWarmBlue;

      }
      else if (strStyle == "WarmGray")
      {

         return StyleTranslucidWarmGray;

      }
      else if (strStyle == "BlueRedPurple")
      {

         return StyleBlueRedPurple;

      }
      else if (strStyle == "RedOrange")
      {

         return StyleRedOrange;

      }
      else if (strStyle == "LightBlue")
      {

         return StyleLightBlue;

      }
      else if (strStyle == "BlackBorder")
      {

         return StyleBlackBorder;

      }
      else if (strStyle == "LightGreen")
      {

         return StyleLightGreen;

      }
      else if (strStyle == "EveningSun")
      {

         return StyleEveningSun;

      }
      else if (strStyle == "BlackPiano")
      {

         return StyleBlackPiano;

      }
      else
      {

         return StyleLightBlue;

      }

   }


   
   void frame_interaction::set_user_style(enum_style estyle)
   {

      m_estyle = estyle;

   }


   void frame_interaction::set_user_style(const ::string & strStyle)
   {

      m_strStyle = strStyle;

      auto estyle = translate_user_style(strStyle);

      set_user_style(estyle);

   }




   void frame_interaction::on_user_style_change()
   {

   }



   enum_window_type frame_interaction::get_window_type()
   {

      return e_window_type_frame;

   }


   void frame_interaction::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_user_style_change)
      {

         on_user_style_change();

      }
      else if (ptopic->m_atom == id_operating_system_user_color_change)
      {

         set_need_redraw();

         post_redraw();

      }

   }


   void frame_interaction::display_previous_restore()
   {

      ::user::box::display_previous_restore();

   }


   void frame_interaction::display_system_minimize()
   {

      ::user::box::display_system_minimize();

   }



   bool frame_interaction::is_frame_window()
   {

      return true;

   }


   // bool frame_interaction::_001FancyInitialFramePlacement(bool bForceRestore)
   // {

   //    return ::user::box::_001FancyInitialFramePlacement(bForceRestore);

   // }


   void frame_interaction::initial_frame_placement()
   {

#if defined(SANDBOXED_WINDOWING)

      display_zoomed();

#else

      WindowDataLoadWindowRectangle();

#endif

   }


   void frame_interaction::initial_frame_display()
   {

      information() << "frame_interaction::initial_frame_display";

      if (!const_layout().sketch().is_screen_visible())
      {

         display_normal(e_display_normal, { ::user::e_activation_set_foreground, window()->get_initial_frame_display_activation_token() });

      }
      else
      {

         set_activation({ ::user::e_activation_set_foreground, window()->get_initial_frame_display_activation_token() });

      }

      set_need_redraw();
      
      post_redraw();

   }


   int_size frame_interaction::get_window_minimum_size()
   {

      if (m_sizeMinimum.area() > 0)
      {

         return m_sizeMinimum;

      }
      else if (const_layout().sketch().display() == ::e_display_minimal)
      {

         return ::int_size(8, 8);

      }
      else
      {

         auto pwindowing = system()->windowing();

         return pwindowing->get_window_minimum_size();

      }

   }


   void frame_interaction::user_interaction_on_destroy()
   {

      ::user::interaction::user_interaction_on_destroy();

      //windowing_window().release();
         

   }


   //::user::thread * frame_interaction::user_thread()
   //{

   //   return m_puserthread;

   //}


   ::user::interaction_base * frame_interaction::set_parent(::user::interaction_base * puserinteractionParent)
   {

      if (puserinteractionParent == nullptr && get_parent() == nullptr)
      {

         return nullptr;

      }

      if (puserinteractionParent != nullptr && is_descendant(puserinteractionParent, true))
      {

         return get_parent();

      }

      if (!on_before_set_parent(puserinteractionParent))
      {

         return get_parent();

      }

      auto puserthread = user_thread();

      if (puserthread)
      {

         if (::is_set(puserthread->m_puserinteractionbaseaThread))
         {

            puserthread->m_puserinteractionbaseaThread->erase(this);

         }

         //m_pthreadUserInteraction.release();

      }

      ::pointer<interaction> pparentOld = get_parent();

      if (puserinteractionParent == nullptr)
      {

         auto pwindowNew = __øcreate<::windowing::window>();

         auto strName = get_window_text();

         const ::scoped_string & scopedstrClassName = nullptr;

         m_bEnableSaveWindowRect2 = true;

         on_set_parent(nullptr);

         if (m_ewindowflag & e_window_flag_load_window_rect_on_impl)
         {

            WindowDataLoadWindowRectangle();

         }

         //auto rectangleRequest = this->screen_rectangle(::user::e_layout_sketch);

         //auto pusersystem = __allocate ::user::system();

         //pusersystem->add_visible(is_visible(layout().sketch().display()));

         //pprimitiveimplNew->create_host(this, e_parallelization_synchronous);

         create_window();

         on_after_set_parent();

      }
      else // puserinteractionParent != nullptr
      {

         on_set_parent(puserinteractionParent);

         //auto pprimitiveimplNew = __create_new<::user::interaction_child>();

         //pprimitiveimplNew->m_puserinteraction = this;

         ::pointer<::aura::application> papp = get_app();

         //psession->erase_frame(this); // no more a top level frame_interaction if it were one
         papp->erase_user_interaction(this); // no more a top level frame_interaction if it were one

         //m_pprimitiveimpl = pprimitiveimplNew;

         string strName;

         //int iStyle = get_window_long(GWL_STYLE);

         //iStyle |= WS_CHILD;

         //if (is_visible(layout().sketch().display()))
         //{

         //   iStyle |= WS_VISIBLE;

         //}

         ::int_rectangle rectangleWindow;

         ::pointer<::user::interaction> pparent = puserinteractionParent;

         if (pparent)
         {

            pparent->get_child_rect(rectangleWindow);

         }

         if (::is_set(windowing_window()))
         {

            windowing_window()->destroy_impl_only();

         }

         //pprimitiveimplNew->create_child(this, pparent);

         //if (!pprimitiveimplNew->create_child(this, pparent))
         //{

         //   throw ::exception(error_failed, "could not impl interaction");

         //}
         //else
         {

            on_after_set_parent();

         }

      }

      return pparentOld;

   }


} // namespace user





