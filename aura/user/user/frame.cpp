#include "framework.h"
#include "frame.h"
#include "key.h"
#include "style.h"
#include "user.h"
#include "acme/constant/id.h"
#include "acme/constant/user_key.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/pool.h"
#include "acme/constant/message.h"
#include "aura/graphics/image/icon.h"
#include "aura/platform/application.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/windowing/windowing.h"


namespace user
{


   frame::frame()
   {

      m_puserframewindow = nullptr;
      m_bSnapToBars = false;
      m_bAddToTitle = false;
      m_bPrefixTitle = false;

      m_bDerivedHeight = false;
      m_bShowControlBox = true;
      m_bDefaultNotifyIcon = false;
      m_bCloseApplicationIfLastVisibleFrame = true;

   }


   frame::~frame()
   {

   }


   void frame::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);




      add_command_handler("app_exit", { this, &frame::on_message_application_exit });
      

      MESSAGE_LINK(e_message_destroy, pchannel, this, &frame::on_message_destroy);
      MESSAGE_LINK(e_message_application_exit, pchannel, this, &frame::on_message_application_exit);
      MESSAGE_LINK(e_message_key_down, pchannel, this, &frame::on_message_key_down);

      system()->add_signal_handler({ use_t{}, this }, id_operating_system_user_color_change);
//#ifdef WINDOWS_DESKTOP
//
//      if (is_frame_window())
//      {
//
//         MESSAGE_LINK((::enum_message)WM_SYSCOMMAND, pchannel, this, &frame::_001OnSysCommand);
//
//      }
//
//#endif


   }

   
   void frame::on_message_destroy(::message::message * pmessage)
   {

      erase_graphical_output_purpose(this);

   }


   void frame::on_message_application_exit(::message::message* pmessage)
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


   void frame::on_message_key_down(::message::message* pmessage)
   {

      ::pointer<::user::key>pkey(pmessage);
      
      if (get_parent() == nullptr)
      {

         
         if(pkey->m_ekey == ::user::e_key_q && get_session()->is_key_pressed(::user::e_key_command))
         {
            
            post_message(MESSAGE_CLOSE);
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


   ::task_pool * frame::taskpool()
   {

      __defer_construct_new(m_ptaskpool);

      return m_ptaskpool;

   }


   void frame::destroy()
   {

      m_puserstyle.defer_destroy();

      ::user::box::destroy();

   }

//   bool frame::is_os_host() const
//   {
//
//      return false;
//
//   }


   style * frame::get_style() const
   {

      return m_puserstyle;

   }


   ::color::color frame::get_border_main_body_color()
   {

      return color::transparent;

   }


   void frame::add_menu_item(const ::string & strPath, const ::string & strText, const ::string & strId)
   {

      m_straMenuParent.add(strPath);
      m_straMenuName.add(strText);
      m_straMenuId.add(strId);

      //return ::success;

   }


   ::user::tool_window * frame::tool_window(enum_tool etool, bool bCreate)
   {

      return nullptr;

   }


//   ::user::toolbar * frame::get_toolbar(const ::atom & idToolBar)
//   {
//
//      return nullptr;
//
//   }


   void frame::add_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void frame::erase_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void frame::show_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void frame::hide_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


//   ::pointer<::utoolbar>frame::load_toolbar(const ::atom & idToolbar, const ::string & strToolbar, u32 dwCtrlStyle, u32 uStyle, const ::type_atom & typeatom)
//   {
//
//      return false;
//
//   }


   void frame::on_create_bars()
   {

      //return ::success;

   }


   bool frame::should_perform_layout(::draw2d::graphics_pointer & pgraphics)
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



   ::user::interaction* frame::get_active_impact()
   {

      return nullptr;

   }


   void frame::set_active_impact(::user::impact* pImpactNew, bool bNotify)
   {


   }


   void frame::ActivateFrame(::e_display edisplay)
   {


   }



   void frame::set_frame_title(const string& strFrameTitle)
   {

      m_strFrameTitle = strFrameTitle;

      //auto pparent = get_parent();

      //if (pparent && pparent->is < ::user::place_holder >())
      //{

      //   set_place_child_title(m_strFrameTitle);

      //}

   }


   string frame::get_frame_title()
   {

      return m_strFrameTitle;

   }


   ::draw2d::icon* frame::get_draw_icon()
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
      
      __construct(m_pdrawicon);

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


   //void frame::this->rectangle(::rectangle_i32* lprect)
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


   ::color::color frame::get_moveable_border_color()
   {

      if (!m_puserstyle)
      {

         return ::color::color();

      }

      return m_puserstyle->get_style_moveable_border_color(m_estyle);

   }


   bool frame::is_translucid_user_style(enum_style estyle)
   {

      return
         estyle == ::user::StyleTranslucidWarmGray
         || estyle == ::user::StyleTranslucidLightBlue
         || estyle == ::user::StyleTranslucidLightGreen
         || estyle == ::user::StyleTranslucidWarmLiteGray;

   }


   ::user::enum_style frame::translate_user_style(const ::string & pszStyle)
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


   
   void frame::set_user_style(enum_style estyle)
   {

      m_estyle = estyle;

   }


   void frame::set_user_style(const ::string & strStyle)
   {

      m_strStyle = strStyle;

      auto estyle = translate_user_style(strStyle);

      set_user_style(estyle);

   }




   void frame::on_user_style_change()
   {

   }



   enum_window_type frame::get_window_type()
   {

      return e_window_type_frame;

   }


   void frame::handle(::topic * ptopic, ::context * pcontext)
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


   void frame::display_previous_restore()
   {

      ::user::box::display_previous_restore();

   }


   void frame::display_system_minimize()
   {

      ::user::box::display_system_minimize();

   }



   bool frame::is_frame_window()
   {

      return true;

   }


   // bool frame::_001FancyInitialFramePlacement(bool bForceRestore)
   // {

   //    return ::user::box::_001FancyInitialFramePlacement(bForceRestore);

   // }


   void frame::initial_frame_placement()
   {

#if defined(SANDBOXED_PLATFORM)


#else

      WindowDataLoadWindowRectangle();

#endif

   }


   void frame::initial_frame_display()
   {

      information() << "frame::initial_frame_display";

      if (!const_layout().sketch().is_screen_visible())
      {

         display_normal(e_display_normal, e_activation_set_foreground);

      }
      else
      {

         set_activation(e_activation_set_foreground);

      }

      set_need_redraw();
      
      post_redraw();

   }


   size_i32 frame::get_window_minimum_size()
   {

      if (m_sizeMinimum.area() > 0)
      {

         return m_sizeMinimum;

      }
      else if (const_layout().sketch().display() == ::e_display_minimal)
      {

         return ::size_i32(8, 8);

      }
      else
      {

         auto psession = get_session();

         auto puser = psession->m_puser;

         auto pwindowing = puser->m_pwindowing;

         return pwindowing->get_window_minimum_size();

      }

   }


} // namespace user





