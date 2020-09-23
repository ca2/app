#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "apex/user/menu_shared_command.h"


namespace user
{


   frame::frame()
   {

      m_bDerivedHeight = false;
      m_bShowControlBox = true;
      m_bDefaultNotifyIcon = false;
      m_bCloseApplicationIfLastVisibleFrame = true;
      m_pframe = this;

   }


   frame::~frame()
   {

   }


   void frame::install_message_routing(::channel* pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      connect_command("app_exit", &frame::_001OnAppExit);

      IGUI_MSG_LINK(WM_APPEXIT, pchannel, this, &frame::_001OnAppExit);

   }


   void frame::_001OnAppExit(::message::message* pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (GetParent() != nullptr)
      {

         pmessage->m_bRet = false;

         return;

      }

      Application._001CloseApplication();

      DestroyWindow();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }


   }



   style * frame::_get_style() const
   {

      return m_puserstyle;

   }


   int frame::get_derived_height(int iWidth)
   {

      return -1;


   }


   int frame::get_derived_width(int iHeight)
   {

      return -1;


   }


   ::color frame::get_border_main_body_color()
   {

      return 0;

   }


   ::estatus frame::add_menu_item(const string & strPath, const string & strText, const string & strId)
   {

      m_straMenuParent.add(strPath);
      m_straMenuName.add(strText);
      m_straMenuId.add(strId);

      return ::success;

   }


   ::user::interaction* frame::GetActiveView() const
   {

      return nullptr;

   }


   void frame::SetActiveView(::user::interaction* pViewNew, bool bNotify)
   {


   }

   void frame::ActivateFrame(::edisplay edisplay)
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


   ::user::tool_window * frame::tool_window(enum_tool etool, bool bCreate)
   {

      return nullptr;

   }


   bool frame::is_frame_window()
   {

      return true;

   }


   bool frame::LoadToolBar(id idToolBar, const char* pszToolBar, u32 dwCtrlStyle, u32 uStyle)
   {

      return false;

   }


   void frame::InitialFramePosition(bool bForceRestore)
   {


   }


   size frame::get_window_minimum_size()
   {

      if (m_sizeMinimum.area() > 0)
      {

         return m_sizeMinimum;

      }
      else if (layout().sketch().display() == ::display_minimal)
      {

         return ::size(8, 8);

      }
      else
      {

         return Session.get_window_minimum_size();

      }

   }


} // namespace user





void menu_shared_idle(::user::frame * pframe)
{

   menu_shared * pmenushared = pframe->m_pmenushared;

   if(::is_null(pmenushared))
   {

      return;

   }

   for(int i = 0; i < pmenushared->m_iCount; i++)
   {

      void * pitem = pmenushared->m_ositema[i];

      if(pitem)
      {

         ::message::id id(pmenushared->m_ppszId[i],::message::type_command_probe);

         menu_shared_command command(&pmenushared->m_statusa[i]);

         command.m_id = id;

         pframe->on_command_probe(&command);

      }

   }

   pmenushared->on_idle_update();

}
