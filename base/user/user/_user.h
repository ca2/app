#ifndef BASE_USER_CUBE_H
#define BASE_USER_CUBE_H


#pragma once



//#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
//#endif


namespace user
{

   class form;
   class tooltip;

   class copydesk;
   class create_struct;
   class control_event;
   class interaction_child;
   class interaction_impl;
   class interaction_pointer_array;
   class place_holder;
   class tab;
   class tab_pane;
   class check_box;
   class menu_interaction;
   class menu_button;
   class menu_item;
   class menu_item_ptra;
   class frame_window;
   class toolbar;
   class scroll_bar;
   class split_layout;
   class style;
   class scroll_info;
   class window_map;
   using style_pointer = __pointer(style);
   class system_interaction_impl;
   class menu_central;


   class menu;
   class place_holder;

   class control_event;
   class frame_window;


} // namespace user


namespace experience
{


   class updown;


} // namespace experience


#include "base/user/experience/experience_updown.h"

#include "style.h"


//#include "control_descriptor_set.h"


#include "place_holder.h"
#include "place_holder_container.h"
//#include "menu_command.h"
#include "menu_interaction.h"
#include "menu_item.h"
#include "menu.h"


//#include "control.h"
#include "control_property.h"


#include "form_data.h"


#ifdef WINDOWS_DESKTOP

//#include "aura/node/windows/user.h"

#elif defined(MACOS)

#include "aura/operating_system/macos/user.h"
//#include "aura/operating_system/macos/user.h"

#elif defined(LINUX)

#include "aura/operating_system/linux/user.h"

#endif


namespace user
{


   class tab;


} // namespace user


namespace user
{


   class impact_data;
   class frame_window;

   class frame_window;
   class mdi_child_window;


}


#include "margin.h"


namespace user
{


   namespace rich_text
   {


      class edit_impl;


   } // namespace rich_text


} // namespace user


class simple_frame_window;


namespace userex
{


   class color_view;


} // namespace userex


class cregexp;


namespace database
{

   class selection;

} // namespace database


class image_list;


namespace user
{


   class menu_item_ptra;
   class menu_item;
   class menu_item_ptra;
   class front_end;
   class menu_item;

   class scroll_bar;


} // namespace user


#define USER_TIMER 50000


#include "picture.h"
#include "picture_interaction.h"


namespace user
{

   namespace rich_text
   {


      class edit;
      class data;


   }  // namespace rich_text


} // namespace user


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#ifdef WINDOWS
#include "windows_tsf/edit_window.h"
#endif
#endif

#include "base/user/experience/_constant.h"

#include "impact.h"

#include "show.h"

#include "acme/primitive/primitive/match.h"



#include "tab_callback.h"
#include "tab_pane_array.h"
#include "tab_data.h"
#include "tab.h"




struct CPrintPreviewState;  // forward object (see afxext.h)
namespace user
{
   class control_bar;          // forward object (see afxext.h)
}


class mini_dock_frame_window;    // forward object (see afxpriv.h)


//#include "button.h"
#include "frame_window.h"
//#include "server.h"
//#include "plain_edit.h"

//#include "aura/user/simple_ui/_.h"

//#include "core/user/experience/_.h"



/*


/////////////////////////////////////////////////////////////////////////////
// CMiniFrameWnd

// MiniFrame window styles
#define MFS_SYNCACTIVE      0x00000100L // syncronize activation w/ parent
#define MFS_4THICKFRAME     0x00000200L // thick frame all around (no tiles)
#define MFS_THICKFRAME      0x00000400L // use instead of WS_THICKFRAME
#define MFS_MOVEFRAME       0x00000800L // no sizing, just moving
#define MFS_BLOCKSYSMENU    0x00001000L // block hit testing on system menu

#pragma warning( disable: 4263 )
#pragma warning( disable: 4264 )
class CLASS_DECL_BASE CMiniFrameWnd : public frame_window
{
public:


   CMiniFrameWnd();
   ~CMiniFrameWnd();


   virtual bool create(const ::string & pClassName, const ::string & lpWindowName,

      u32 dwStyle, const ::rectangle_i32 & rectangle,
      ::user::interaction_child* pParentWnd = nullptr, ::u32 nID = 0);
   virtual bool create_window_ex(u32 dwExStyle, const ::string & pClassName, const ::string & lpWindowName,

      u32 dwStyle, const ::rectangle_i32 & rectangle,
      ::user::interaction_child* pParentWnd = nullptr, ::u32 nID = 0);


   bool OnNcActivate(bool bActive);
   LRESULT OnNcHitTest(const ::point_i32 & point);
   void OnSysCommand(::u32 nID, LPARAM lParam);
   void OnGetMinMaxInfo(MINMAXINFO* pMMI);
   LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam);
   LRESULT OnQueryCenterWnd(WPARAM wParam, LPARAM lParam);
   bool OnNcCreate(::user::system * pcs);


public:
   static void CalcBorders(RECTANGLE_I32 * pClientRect, u32 dwStyle = 0, u32 dwExStyle = 0);


protected:
   virtual bool pre_create_window(::user::system * pusersystem);

protected:
   bool m_bSysTracking;
   bool m_bInSys;
   bool m_bActive;
   string m_strCaption;
};
#pragma warning( default: 4263 )
#pragma warning( default: 4264 )


typedef u32 DROPEFFECT;
class COleDataObject;   // forward object (see afxole.h)

*/






#include "network_configuration.h"
//#include "shell.h"
//#include "keyboard_layout_cfg.h"



#include "document_manager.h"


#include "data_exchange.h"


//#include "view_container.h"
//#include "view_creator.h"

//#include "job.h"




//#include "xfplayer_view_line.h"
//#include "xfplayer_view_lines.h"

//#include "tool_tip_tool.h"
//#include "tool_tip_window.h"



struct __SIZEPARENTPARAMS;


namespace user
{


   class user;


} // namespace user


#include "static_control.h"

#include "control_bar.h"


#include "toolbar.h"

#include "document.h"

#include "split_bar.h"
#include "split_layout.h"


#include "form_control.h"


#include "form_document.h"
#include "form_window.h"
//#include "form_mesh.h"
//#include "form_list.h"
#include "form_impact.h"
//#include "form_list_view.h"
#include "split_bar.h"


#include "impact_data.h"


#include "impact_kit.h"


#include "impact_host.h"


#include "split_view.h"


//#include "edit_plain_text_view.h"


//#include "form.h"
#include "tab_impact.h"
#include "tab_drop_target_window.h"



#include "document_manager.h"

#if defined(LINUX) || defined(FREEBSD)
typedef struct _AppIndicator AppIndicator;
#endif


//#include "notification_area.h"
//#include "notify_icon.h"
//#include "notify_icon_listener.h"







//#include "slider.h"
//#include "step_slider.h"
//#include "elastic_slider.h"






//#include "image_manager.h"

//#include "aura.h"












//#include "aura/filesystem/filemanager/filemanager.h"




//#include "aura/user/netuser/_.h"


#define new ACME_NEW


//#include "form_mesh.h"


//#include "font_list.h"


#include "server.h"


#include "impact_system.h"
#include "single_document_template.h"
#include "multiple_document_template.h"


//
//namespace base
//{
//
//
//   class CLASS_DECL_BASE session_docs :
//      virtual public ::object
//   {
//   public:
//
//
//      ::user::single_document_template *                 m_ptemplate_bergedge;
//      ::user::single_document_template *                 m_ptemplate_platform;
//      ::user::single_document_template *                 m_ptemplate_nature;
//      ::user::single_document_template *                 m_ptemplate_html;
//      __pointer(::user::document)                               m_pbergedgedocument;
//      __pointer(::user::document)                               m_pplatformdocument;
//      __pointer(::user::document)                               m_pnaturedocument;
//
//
//      session_docs();
//
//      virtual ~session_docs();
//
//      void close_all_documents();
//
//   };
//
//
//   session_docs * create_session_docs();
//   void destroy_session_docs(session_docs * pdocs);
//
//
//} // namespace base
//
//






//#include "edit_plain_text_view.h"


#include "static_control.h"




#include "acme/constant/activate.h"
#include "aura/message/user.h"
#include "aura/message/timer.h"


//#include "main_window.h"


//#include "command.h"


//#include "a/primitive/primitive/update.h"


#include "user.h"




#include "_impl.h"



namespace base
{


   inline ::base::user* session::user() const
   { 
      
      return m_puser ? m_puser->m_pbaseuser : nullptr; 
   
   }


} // namespace base


#endif // BASE_USER_CUBE_H


