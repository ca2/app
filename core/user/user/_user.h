#pragma once


#include "aura/user/_user.h"


#include "core/filesystem/filemanager/component.h"



#define SWP_CHANGEVIEWPORTOFFSET  0x100000


namespace message
{


   class key;
   class drag_and_drop;


} // namespace message


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
   class menu_central;
   class menu_item;
   class menu_item_ptra;
   class frame_window;
   class toolbar;
   class scroll_bar;
   class split_layout;
   class style;
   class theme;
   class scroll_info;
   class window_map;
   using style_pointer = __pointer(style);
   using theme_pointer = __pointer(theme);
   class system_interaction_impl;


   class place_holder;

   //#if defined _UWP
   //
   //   class CLASS_DECL_CORE native_window_initialize
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

   class CLASS_DECL_CORE native_window_initialize
   {
   public:

      RECT   m_rect;

   };

#else

   class native_window_initialize;

#endif


}


namespace experience
{

   class updown;

} // namespace experience





#include "core/user/experience/experience_updown.h"



//
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



namespace user
{

   class mesh;
   class mesh_item;
   class list_item;
   class list_column;
   class mesh_data;
   class list_column_array;
   class tab;

   class draw_mesh_item;

} // namespace user




namespace user
{

   class impact_data;
   class frame_window;


} // namespace user

//#include "user_windowing.h"


//// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
//#define CX_BORDER   1
//#define CY_BORDER   1




// Implementation structures
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










#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif


namespace user
{
   //class interaction_impl;
   class frame_window;
   class mdi_child_window;
   class control_bar;


   struct PrintPreviewState;  // forward context_object (see afxext.h)


}





#include "core/user/rich_text/_const.h"


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
class simple_list_data;


namespace user
{


   class menu_item_ptra;
   class menu_item;
   class menu_item_ptra;
   class front_end;
   class menu_item;

   class list_column_array;

   class list;

   class list_header;
   class scroll_bar;
   class list_column_array;





   //CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath);
   //CLASS_DECL_CORE string_array get_wallpaper();



} // namespace user


#define USER_TIMER 50000


class simple_mesh_data;

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


namespace user
{

   namespace rich_text
   {


      class edit;
      class data;


   }  // namespace rich_text


} // namespace user


#include "core/user/rich_text/edit.h"


#include "list_column.h"

#include "list_column_array.h"

#include "list_header.h"
#include "tool_window.h"



#include "color_combo_box.h"
#include "font_combo_box.h"


#include "toggle_switch.h"


#include "mesh_item.h"
#include "list_item.h"

#include "mesh_cache_interface.h"



#include "mesh.h"
#include "list.h"

#include "list_view.h"
#include "mesh_cache.h"
#include "list_cache.h"

#include "core/user/simple/mesh_data.h"
#include "core/user/simple/list_data.h"





struct CPrintPreviewState;  // forward context_object (see afxext.h)
namespace user
{
   class control_bar;          // forward context_object (see afxext.h)
}
class CReBar;               // forward context_object (see afxext.h)
class simple_frame_window;
class CDockBar;             // forward context_object (see afxpriv.h)
class mini_dock_frame_window;    // forward context_object (see afxpriv.h)
class CDockState;           // forward context_object (see afxpriv.h)

#include "core/user/simple_ui/_.h"

#include "core/user/experience/_.h"



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
class CLASS_DECL_CORE CMiniFrameWnd : public frame_window
{
public:


   CMiniFrameWnd();
   ~CMiniFrameWnd();


   virtual bool create(const char * pClassName, const char * lpWindowName,

      u32 dwStyle, const ::rect & rect,
      ::user::interaction_child* pParentWnd = nullptr, UINT nID = 0);
   virtual bool create_window_ex(u32 dwExStyle, const char * pClassName, const char * lpWindowName,

      u32 dwStyle, const ::rect & rect,
      ::user::interaction_child* pParentWnd = nullptr, UINT nID = 0);


   bool OnNcActivate(bool bActive);
   LRESULT OnNcHitTest(const ::point & point);
   void OnSysCommand(UINT nID, LPARAM lParam);
   void OnGetMinMaxInfo(MINMAXINFO* pMMI);
   LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam);
   LRESULT OnQueryCenterWnd(WPARAM wParam, LPARAM lParam);
   bool OnNcCreate(::user::create_struct * pcs);


public:
   static void CalcBorders(RECT * pClientRect, u32 dwStyle = 0, u32 dwExStyle = 0);


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





//
//#include "network_configuration.h"



#include "xfplayer_view_line.h"
#include "xfplayer_view_lines.h"

//#include "tool_tip_tool.h"
//#include "tool_tip_window.h"



struct __SIZEPARENTPARAMS;


namespace user
{


   class user;


} // namespace user

#include "core/user/account/view.h"



#include "toolbar_control.h"

#include "toolbar.h"
#include "statusbar.h"


#include "form_mesh.h"
#include "form_list.h"
#include "form_list_view.h"






#include "step_slider.h"
#include "elastic_slider.h"






#include "image_manager.h"

//#include "aura.h"












//#include "aura/filesystem/filemanager/filemanager.h"




#include "core/user/netuser/_.h"


#define new AURA_NEW


#include "form_mesh.h"


#include "font_list.h"



#include "tooltip.h"



#include "core/user/userex/user.h"



#include "_impl.h"


