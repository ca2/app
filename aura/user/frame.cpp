#include "framework.h"
#include "aura/user/_user.h"


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

      add_command_handler("app_exit", this, &frame::on_message_app_exit);

      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &window::on_message_set_cursor);
      MESSAGE_LINK(WM_APPEXIT, pchannel, this, &frame::on_message_app_exit);

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

   

   void frame::on_message_app_exit(::message::message* pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      if (get_parent() != nullptr)
      {

         pmessage->m_bRet = false;

         return;

      }

      __pointer(::aura::application) papplication = get_application();

      papplication->_001TryCloseApplication();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   ::task_pool * frame::taskpool()
   {

      __defer_construct_new(m_ptaskpool);

      return m_ptaskpool;

   }


   bool frame::is_os_host() const
   {

      return false;

   }


   style * frame::get_style() const
   {

      return m_puserstyle;

   }


   ::color::color frame::get_border_main_body_color()
   {

      return 0;

   }


   ::e_status frame::add_menu_item(const ::string & strPath, const ::string & strText, const ::string & strId)
   {

      m_straMenuParent.add(strPath);
      m_straMenuName.add(strText);
      m_straMenuId.add(strId);

      return ::success;

   }


   ::user::tool_window * frame::tool_window(enum_tool etool, bool bCreate)
   {

      return nullptr;

   }


//   ::user::toolbar * frame::get_toolbar(const ::id & idToolBar)
//   {
//
//      return nullptr;
//
//   }


   ::e_status frame::add_control_bar(::user::control_bar * pcontrolbar)
   {

      throw interface_only_exception();

      return error_interface_only;

   }


   ::e_status frame::erase_control_bar(::user::control_bar * pcontrolbar)
   {

      throw interface_only_exception();

      return error_interface_only;

   }


   ::e_status frame::show_control_bar(::user::control_bar * pcontrolbar)
   {

      throw interface_only_exception();

      return error_interface_only;

   }


   ::e_status frame::hide_control_bar(::user::control_bar * pcontrolbar)
   {

      throw interface_only_exception();

      return error_interface_only;

   }


//   __transport(::utoolbar) frame::load_toolbar(const ::id & idToolbar, const ::string & strToolbar, u32 dwCtrlStyle, u32 uStyle, const ::type & type)
//   {
//
//      return false;
//
//   }


   ::e_status frame::on_create_bars()
   {

      return ::success;

   }


   ::user::interaction* frame::get_active_view() const
   {

      return nullptr;

   }


   void frame::set_active_view(::user::impact* pViewNew, bool bNotify)
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


   string frame::get_frame_title() const
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

      auto estatus = __compose(m_pdrawicon);

      if (!estatus)
      {

         return nullptr;

      }

      estatus = m_pdrawicon->initialize_with_windowing_icon(pwindowingicon);

      if (!estatus)
      {

         return nullptr;

      }

      return m_pdrawicon;

   }


   
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



   void frame::handle(::subject * psubject, ::context * pcontext)
   {

      if (psubject->m_id == id_user_style_change)
      {

         on_user_style_change();

      }
      else if (psubject->m_id == id_user_color)
      {

         set_need_redraw();

         post_redraw();

      }

   }


   ::e_status frame::display_previous_restore()
   {

      return ::success;

   }


   void frame::display_system_minimize()
   {


   }



   bool frame::is_frame_window()
   {

      return true;

   }




   void frame::InitialFramePosition(bool bForceRestore)
   {


   }


   size_i32 frame::get_window_minimum_size()
   {

      if (m_sizeMinimum.area() > 0)
      {

         return m_sizeMinimum;

      }
      else if (layout().sketch().display() == ::e_display_minimal)
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





