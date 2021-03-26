#pragma once


//#if !BROAD_PRECOMPILED_HEADER
//#include "_.h"
//#endif
#include "aura/platform/_platform.h"




class prodevian;


namespace user
{


   class control_bar;


   enum e_interaction
   {

      interaction_wfi_up_down_loading = 1 << 0,
      interaction_wfi_up_tool_window = 1 << 1,

   };


} // namespace user


#define SWP_CHANGEVIEWPORTOFFSET  0x100000


namespace message
{


   class key;
   class drag_and_drop;


} // namespace message


namespace user
{
   //class form;
   class tooltip;



   class copydesk;
   //class system;
   class control_event;
   //class control_descriptor;
   class interaction_child;
   class interaction_impl;
   class interaction_array;
   //class place_holder;
   //class tab;
   //class tab_pane;
   //class check_box;
   //class menu_interaction;
   //class menu_button;
   //class menu_item;
   //class menu_item_ptra;
   //class frame_window;
   class toolbar;
   class scroll_bar;
   class split_layout;
   class style;
   class scroll_info;
   //class window_map;
   //class system_interaction;


   //class place_holder;

   //#if defined _UWP
   //
   //   class CLASS_DECL_AURA native_window_initialize
   //   {
   //   public:
   //
   //
   //      Agile < Windows::UI::Core::CoreWindow >         m_window;
   //      ::aura::system_window ^                         m_pwindow;
   //
   //
   //   };
   //
   //#elif defined(APPLE_IOS) || defined(ANDROID)
#if defined(APPLE_IOS) || defined(ANDROID)

   class CLASS_DECL_AURA native_window_initialize
   {
   public:

      RECTANGLE_I32   m_rectangle;

   };

#else

   class native_window_initialize;

#endif


   class control_event;
   //class frame_window;

   CLASS_DECL_AURA bool is_descendant(::user::interaction* puiParent, ::user::interaction* puiChild);


}


namespace experience
{

   class updown;

} // namespace experience


namespace user
{

   class CLASS_DECL_AURA calc_size
   {
   public:


      ::draw2d::graphics_pointer    m_pgraphics;
      size_i32                          m_size;


   };


   class CLASS_DECL_AURA alpha_source :
      virtual public ::matter
   {
   public:


      virtual double get_alpha(::user::interaction* puiTarget);
      virtual void on_alpha_target_initial_frame_position();


   };


   //CLASS_DECL_AURA::mutex * mutex_children2();




}


namespace user
{

   class CLASS_DECL_AURA run_application
   {
   public:


      index                               m_iEdge;
      string                              m_strApp;
      string                              m_strQuery;
      __pointer(::aura::session)          m_pbergedgeParent;
      __pointer(::aura::application)      m_papp;
      bool                                m_bMakeVisible;
      __pointer(::user::interaction)      m_puserinteractionParent;
      property_set                        m_setParameters;

      run_application();


   };


} // namespace user


//#include "aura/primitive/primitive/command.h"
//#include "aura/primitive/primitive/command_line.h"


//#include "command.h"



//#include "style_base.h"


//#include "aura/primitive/primitive/create.h"
#include "system.h"

#include "window_util.h"
#include "aura/graphics/write_text/text_box.h"
#include "aura/graphics/write_text/font_list.h"
#include "window_state.h"
#include "primitive_impl.h"


//#include "aura/database/key.h"

#include "notify_icon_listener.h"

#include "control_descriptor.h"


#include "interaction_layout.h"


#include "prodevian.h"

//#include "aura/platform/str_context.h"


//#include "aura/primitive/primitive/form_property_set.h"


#include "graphics_call.h"


#include "interaction.h"


#include "notify_icon.h"


#include "aura/windowing/menu_item.h"


#include "aura/windowing/menu.h"


//using window_pointer = __pointer(::user::interaction_impl);

//#include "primitive_impl.h"


#include "interaction_impl.h"


#include "copydesk.h"
#include "interaction_child.h"
#include "scroll_info.h"
//#include "place_holder.h"
//#include "place_holder_container.h"
//#include "job.h"
//#include "core/user/experience/experience_updown.h"
#include "box.h"
#include "tool_window.h"
#include "frame.h"
//#include "menu_command.h"
//#include "menu_interaction.h"
//#include "menu_item.h"
//#include "menu.h"
#include "control_event.h"
#include "window_map.h"

#include "scroll.h"

//#include "aura/primitive/primitive/form_property_set.h"


//#include "control.h"


#include "scroll_bar.h"


#include "callback.h"


//#include "form_data.h"
#include "form.h"

#include "form_callback.h"


#include "message_window.h"



//#ifdef WINDOWS_DESKTOP
//
//#include "aura/node/windows/user.h"
//
//#elif defined(MACOS)
//
//#include "aura/os/macos/user.h"
//#include "aura/node/macos/user.h"
//
//#elif defined(LINUX)
//
//#include "aura/os/linux/user.h"
//
//
//#endif
//
//
//#include "aura/os/_user.h"
//

//#include "keyboard_layout.h"
#include "keyboard.h"


namespace str
{


   CLASS_DECL_AURA void replace_tab(strsize iOffset, string& strParam, int iWidth, strsize_array* piaTab = nullptr, ::array < strsize* > iaTab = nullptr);
   CLASS_DECL_AURA void replace_tab(strsize iOffset, string& strParam, int iWidth, ::array < strsize* > iaTab);


} // namespace str


struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h

// Classes declared in this file

//::draw2d::graphics_pointer
class preview_dc;               // Virtual DC for print preview

class mini_dock_frame_window;

/////////////////////////////////////////////////////////////////////////////
// Global ID ranges (see Technical note TN020 for more details)

// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)

// 8000 -> DFFF : ::account::user commands
// E000 -> EFFF : _ commands and other things
// F000 -> FFFF : standard windows commands and other things etc
// E000 -> E7FF standard commands
// E800 -> E8FF control bars (first 32 are special)
// E900 -> EEFF standard interaction_impl controls/components
// EF00 -> EFFF SC_ menu help
// F000 -> FFFF standard strings
#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + __IDS_SCFIRST)

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::account::user resources
// 7000 -> 7FFF : _ (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes





// flags for wParam in the WM_FLOATSTATUS message
enum
{
   FS_SHOW = 0x01, FS_HIDE = 0x02,
   FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
   FS_ENABLE = 0x10, FS_DISABLE = 0x20,
   FS_SYNCACTIVE = 0x40
};





#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif


//#include "still.h"


#include "progress.h"



//#include "user_job.h"


//#include "user_message.h"

//#include "axis/axis/axis_print_job.h"
//#include "user_print_job.h"


//#include "user_menu_item.h"
//#include "user_menu_command.h"
//#include "user_menu.h"

namespace user
{
   //class interaction_impl;
   //class frame_window;
   class mdi_child_window;
   //class control_bar;


   struct PrintPreviewState;  // forward object (see afxext.h)


}

//#include "user_copydesk.h"


//#include "inline.h"


//
//
//namespace user
//{
//
//   class CLASS_DECL_AURA map_form_window :
//      virtual public strsp(::user::form_control)
//   {
//   public:
//
//   };
//
//} // namespace user
//










//#include "margin.h"

//#include "aura/user/rich_text/_const.h"


namespace user
{


   namespace rich_text
   {


      class edit_impl;


   } // namespace rich_text


} // namespace user


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


   //class menu_item_ptra;
   //class menu_item;
   //class menu_item_ptra;
   class front_end;
   //class menu_item;

   //class list_column_array;



   //class list_header;
   class scroll_bar;
   //class list_column_array;





   //CLASS_DECL_AURA bool set_wallpaper(string strLocalImagePath);
   //CLASS_DECL_AURA string_array get_wallpaper();



} // namespace user


#define USER_TIMER 50000


//class simple_mesh_data;

//
//enum enum_position
//{
//   e_position_none = 0,
//   e_position_top = 1,
//   e_position_left = 2,
//   position_top_left = 3,
//   e_position_right = 4,
//   position_top_right = 5,
//   position_hcenter = 6,
//   position_top_center = 7,
//   e_position_bottom = 8,
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
//   enum enum_line_hit
//   {
//      e_line_hit_none,
//      e_line_hit_normal,
//      e_line_hit_link,
//   };
//}
//

//#include "picture.h"
//#include "picture_interaction.h"


namespace user
{

   namespace rich_text
   {


      class edit;
      class data;


   }  // namespace rich_text


} // namespace user

///#include "aura/os/_user.h"



//#include "aura/user/rich_text/edit.h"


//#include "list_column.h"
//
//#include "list_column_array.h"
//
//#include "list_header.h"
//#include "tool_window.h"

// #ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
// #ifdef WINDOWS
// #include "windows_tsf/edit_window.h"
// #endif
// #endif


#include "button.h"


#include "check_box.h"


#include "still.h"


#include "text_composition.h"


#include "plain_edit.h"


//#include "combo_box.h"
//#include "combo_list.h"


//#include "check_box.h"


struct CPrintPreviewState;  // forward object (see afxext.h)
namespace user
{
   class control_bar;          // forward object (see afxext.h)
}


class mini_dock_frame_window;    // forward object (see afxpriv.h)


//#include "button.h"
//#include "plain_edit.h"



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
class CLASS_DECL_AURA CMiniFrameWnd : public frame_window
{
public:


   CMiniFrameWnd();
   ~CMiniFrameWnd();


   virtual bool create(const char * pClassName, const char * lpWindowName,

      u32 dwStyle, const ::rectangle_i32 & rectangle,
      ::user::interaction_child* pParentWnd = nullptr, ::u32 nID = 0);
   virtual bool create_window_ex(u32 dwExStyle, const char * pClassName, const char * lpWindowName,

      u32 dwStyle, const ::rectangle_i32 & rectangle,
      ::user::interaction_child* pParentWnd = nullptr, ::u32 nID = 0);


   bool OnNcActivate(bool bActive);
   lresult OnNcHitTest(const ::point_i32 & point);
   void OnSysCommand(::u32 nID, lparam lParam);
   void OnGetMinMaxInfo(MINMAXINFO* pMMI);
   lresult OnFloatStatus(wparam wParam, lparam lParam);
   lresult OnQueryCenterWnd(wparam wParam, lparam lParam);
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






//#include "network_configuration.h"
//#include "shell.h"
//#include "keyboard_layout_cfg.h"



//#include "document_manager.h"


//#include "data_exchange.h"


//#include "view_container.h"
//#include "view_creator.h"

//#include "job.h"




struct __SIZEPARENTPARAMS;


namespace user
{


   class user;


} // namespace user


//#include "combo_box.h"
//#include "combo_list.h"


#ifdef LINUX
typedef struct _AppIndicator AppIndicator;
#endif


//#include "slider.h"


//#define new AURA_NEW


#include "user.h"


#include "main_window.h"


#include "message_box.h"


#include "box.h"



#include "_impl.h"



namespace user
{


   template < typename CONTROL_STYLE >
   void style::get(__pointer(CONTROL_STYLE) & pcontrolstyleImpl, ::draw2d::graphics_pointer & pgraphics, ::user::interaction * pinteraction)
   {

      auto & pcontrolstyle = m_controlstyle[pinteraction->m_econtroltype];

      if (!pcontrolstyle)
      {

         pcontrolstyle = __new(CONTROL_STYLE);

      }

      if (!pcontrolstyle->is_up_to_date(this))
      {

         pcontrolstyle->update(pgraphics, this, pinteraction);

      }

      pcontrolstyleImpl = pcontrolstyle;

   }


} // namespace user


#include "user.h"




