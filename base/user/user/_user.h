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
   //class control_descriptor;
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
//   class theme;
   class scroll_info;
   class window_map;
   using style_pointer = __pointer(style);
   class system_interaction_impl;
   class menu_central;


   class menu;
   class place_holder;

//
//#if defined(APPLE_IOS) || defined(ANDROID)
//
//
//   class CLASS_DECL_BASE native_window_initialize
//   {
//   public:
//
//      RECT32   m_rect;
//
//   };
//
//
//#else
//
//
//   class native_window_initialize;
//
//
//#endif


   class control_event;
   class frame_window;


} // namespace user


namespace experience
{


   class updown;


} // namespace experience


//#include "aura/primitive/primitive/match.h"


#include "base/user/experience/experience_updown.h"

#include "style.h"


#include "control_descriptor_set.h"


#include "place_holder.h"
#include "place_holder_container.h"
#include "menu_command.h"
#include "menu_interaction.h"
#include "menu_item.h"
#include "menu.h"


//#include "box.h"
#include "control.h"
#include "control_property.h"


//#include "tool_window.h"

//#include "callback.h"


#include "form_data.h"
//#include "form.h"


#ifdef WINDOWS_DESKTOP

#include "aura/node/windows/user.h"

#elif defined(MACOS)

#include "aura/os/macos/user.h"
#include "aura/node/macos/user.h"

#elif defined(LINUX)

#include "aura/os/linux/user.h"

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

//#include "aura/user/rich_text/_const.h"


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
//class simple_list_data;


namespace user
{


   class menu_item_ptra;
   class menu_item;
   class menu_item_ptra;
   class front_end;
   class menu_item;

   //class list_column_array;



   //class list_header;
   class scroll_bar;
   //class list_column_array;





   //CLASS_DECL_BASE bool set_wallpaper(string strLocalImagePath);
   //CLASS_DECL_BASE string_array get_wallpaper();



} // namespace user


#define USER_TIMER 50000


//class simple_mesh_data;

//
//enum e_position
//{
//   position_none = 0,
//   position_top = 1,
//   position_left = 2,
//   position_top_left = 3,
//   position_right = 4,
//   position_top_right = 5,
//   position_hcenter = 6,
//   position_top_center = 7,
//   position_bottom = 8,
//   position_vcenter = 9,
//   position_bottom_left = 10,
//   position_left_center = 11,
//   position_bottom_right = 12,
//   position_right_center = 13,
//   position_bottom_center = 14,
//   position_center = 15,
//};
//
//
//namespace user
//{
//   enum e_line_hit
//   {
//      line_hit_none,
//      line_hit_normal,
//      line_hit_link,
//   };
//}
//

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


//#include "imm_client.h"


//#include "aura/user/rich_text/edit.h"


//#include "list_column.h"
//
//#include "list_column_array.h"
//
//#include "list_header.h"
//#include "tool_window.h"

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#ifdef WINDOWS
#include "windows_tsf/edit_window.h"
#endif
#endif

//#include "plain_edit.h"

//#include "combo_box.h"
//#include "combo_list.h"

#include "base/user/experience/_const.h"

//#include "check_box.h"
//#include "toggle_switch.h"




//#include "mesh.h"
//#include "list.h"

#include "impact.h"

//#include "list_view.h"
//#include "mesh_cache_interface.h"
//#include "mesh_cache.h"
//#include "list_cache.h"

//#include "aura/user/simple/mesh_data.h"
//#include "aura/user/simple/list_data.h"

//#include "tree.h"

//#include "form.h"
//#include "form_list.h"
//#include "form_list_view.h"



//#include "place_holder.h"
//#include "place_holder_container.h"

#include "acme/primitive/primitive/match.h"



#include "tab_callback.h"
#include "tab.h"




struct CPrintPreviewState;  // forward context_object (see afxext.h)
namespace user
{
   class control_bar;          // forward context_object (see afxext.h)
}


class mini_dock_frame_window;    // forward context_object (see afxpriv.h)


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


   virtual bool create(const char * pClassName, const char * lpWindowName,

      u32 dwStyle, const ::rect & rect,
      ::user::interaction_child* pParentWnd = nullptr, ::u32 nID = 0);
   virtual bool create_window_ex(u32 dwExStyle, const char * pClassName, const char * lpWindowName,

      u32 dwStyle, const ::rect & rect,
      ::user::interaction_child* pParentWnd = nullptr, ::u32 nID = 0);


   bool OnNcActivate(bool bActive);
   LRESULT OnNcHitTest(const ::point & point);
   void OnSysCommand(::u32 nID, LPARAM lParam);
   void OnGetMinMaxInfo(MINMAXINFO* pMMI);
   LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam);
   LRESULT OnQueryCenterWnd(WPARAM wParam, LPARAM lParam);
   bool OnNcCreate(::user::create_struct * pcs);


public:
   static void CalcBorders(RECT32 * pClientRect, u32 dwStyle = 0, u32 dwExStyle = 0);


protected:
   virtual bool pre_create_window(::user::create_struct& cs);

protected:
   bool m_bSysTracking;
   bool m_bInSys;
   bool m_bActive;
   string m_strCaption;
};
#pragma warning( default: 4263 )
#pragma warning( default: 4264 )


typedef u32 DROPEFFECT;
class COleDataObject;   // forward context_object (see afxole.h)

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
#include "form_view.h"
//#include "form_list_view.h"
#include "split_bar.h"


#include "impact_data.h"


#include "impact_host.h"


#include "split_view.h"


#include "edit_plain_text_view.h"


//#include "form.h"
#include "tab_view.h"
#include "tab_drop_target_window.h"



#include "document_manager.h"

#ifdef LINUX
typedef struct _AppIndicator AppIndicator;
#endif


#include "notification_area.h"
#include "notify_icon.h"
#include "notify_icon_listener.h"







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






#include "edit_plain_text_view.h"


#include "static_control.h"





#include "aura/message/user.h"
#include "aura/message/timer.h"


//#include "main_window.h"


//#include "command.h"


//#include "a/primitive/primitive/update.h"


#include "user.h"


#undef Usr
#define Usr(pobject) (Sess(pobject)->user()->m_pbaseuser)


#include "_impl.h"




