#pragma once


////#include "base/user/user/_component.h"
//
//
//#define SWP_CHANGEVIEWPORTOFFSET  0x100000
//
//
//namespace message
//{
//
//
//   class key;
//   class drag_and_drop;
//
//
//} // namespace message
//
//
//namespace user
//{
//
//   class form;
//   class tooltip;
//
//
//
//   class copydesk;
//   class create_struct;
//   class control_event;
//   //class control_descriptor;
//   class interaction_child;
//   class interaction_impl;
//   class interaction_pointer_array;
//   class place_holder;
//   class tab;
//   class tab_pane;
//   class check_box;
//   class menu_interaction;
//   class menu_button;
//   class menu_item;
//   class menu_item_ptra;
//   class frame_window;
//   class toolbar;
//   class scroll_bar;
//   class split_layout;
//   class style;
//   class scroll_info;
//   class window_map;
//   using style_pointer = ::pointer<style>
//   class system_interaction_impl;
//
//
//   class place_holder;
//
//   //#if defined UNIVERSAL_WINDOWS
//   //
//   //   class CLASS_DECL_CORE native_window_initialize
//   //   {
//   //   public:
//   //
//   //
//   //      Agile < ::winrt::Windows::UI::Core::CoreWindow >         m_window;
//   //      ::aura::system_window ^                         m_pwindow;
//   //
//   //
//   //   };
//   //
//   //#elif defined(APPLE_IOS) || defined(ANDROID)
//#if defined(APPLE_IOS) || defined(ANDROID)
//
//   //class CLASS_DECL_CORE native_window_initialize
//   //{
//   //public:
//
//   //   ::rectangle_i32   m_rectangle;
//
//   //};
//
//#else
//
//   class native_window_initialize;
//
//#endif
//
//
//   namespace rich_text
//   {
//
//      
//      class format;
//
//
//   } // namespace rich_text
//
//
//} // namespace user
//
//
//namespace experience
//{
//
//   class updown;
//
//} // namespace experience
//
//
//
//
//
//
//
//
//
////
////#ifdef WINDOWS_DESKTOP
////
////#include "aura/node/windows/user.h"
////
////#elif defined(MACOS)
////
////#include "aura/os/macos/user.h"
////#include "aura/node/macos/user.h"
////
////#elif defined(LINUX)
////
////#include "aura/os/linux/user.h"
////
////
////#endif
//
//
//
//namespace user
//{
//
//   class mesh;
//   class mesh_item;
//   class list_item;
//   class list_column;
//   class mesh_data;
//   class list_column_array;
//   class tab;
//
//   class draw_mesh_item;
//
//} // namespace user
//
//
//
//
//namespace user
//{
//
//   class impact_data;
//   class frame_window;
//
//
//} // namespace user
//
////#include "user_windowing.h"
//
//
////// Note: ::windows_definition::Data.cxBorder and ::windows_definition::Data.cyBorder aren't used anymore
////#define CX_BORDER   1
////#define CY_BORDER   1
//
//
//
//
// structures
//struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h
//
//// Classes declared in this file
//
////::draw2d::graphics_pointer
//class thumbnail_dc;               // Virtual DC for print thumbnail
//
//class mini_dock_frame_window;
//
///////////////////////////////////////////////////////////////////////////////
//// Global ID ranges (see Technical note TN020 for more details)
//
//// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
//#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)
//
//// 8000 -> DFFF : ::account::user commands
//// E000 -> EFFF : _ commands and other things
//// F000 -> FFFF : standard windows commands and other things etc
//// E000 -> E7FF standard commands
//// E800 -> E8FF control bars (first 32 are special)
//// E900 -> EEFF standard interaction_impl controls/components
//// EF00 -> EFFF SC_ menu help
//// F000 -> FFFF standard strings
//#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + __IDS_SCFIRST)
//
//// 0000 -> 7FFF IDR range
//// 0000 -> 6FFF : ::account::user resources
//// 7000 -> 7FFF : _ (and standard windows) resources
//// IDR ranges (NOTE: IDR_ values must be <32768)
//#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)
//
///////////////////////////////////////////////////////////////////////////////
//// Context sensitive help support (see Technical note TN028 for more details)
//
//// Help ID bases
//#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
//#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
//#define HID_BASE_PROMPT     0x00030000UL        // IDP
//#define HID_BASE_NCAREAS    0x00040000UL
//#define HID_BASE_CONTROL    0x00050000UL        // IDC
//#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes
//
//
//
//
//
//
//
//
//
//
//#ifndef LAYOUT_LTR
//#define LAYOUT_LTR                         0x00000000
//#endif
//
//
//namespace user
//{
//   //class interaction_impl;
//   class frame_window;
//   class mdi_child_window;
//   class control_bar;
//
//
//   
//
//
//}
//
//
//
//
//
//#include "core/user/rich_text/_const.h"
//
//
//namespace user
//{
//
//
//   namespace rich_text
//   {
//
//
//      class edit_impl;
//
//
//   } // namespace rich_text
//
//
//} // namespace user
//
//
//class simple_frame_window;
//
//
//namespace userex
//{
//
//
//   class color_impact;
//
//
//} // namespace userex
//
//
//class cregexp;
//
//namespace database
//{
//
//   class selection;
//
//} // namespace database
//
//class image_list;
//class simple_list_data;
//
//
//namespace user
//{
//
//
//   class menu_item_ptra;
//   class menu_item;
//   class menu_item_ptra;
//   class front_end;
//   class menu_item;
//
//   class list_column_array;
//
//   class list;
//
//   class list_header;
//   class scroll_bar;
//   class list_column_array;
//
//
//
//
//
//   //CLASS_DECL_CORE bool set_wallpaper(string strLocalImagePath);
//   //CLASS_DECL_CORE string_array get_wallpaper();
//
//
//
//} // namespace user
//
//
//#define USER_TIMER 50000
//
//
//class simple_mesh_data;
//
////
////enum enum_position
////{
////   e_position_none = 0,
////   e_position_top = 1,
////   e_position_left = 2,
////   position_top_left = 3,
////   e_position_right = 4,
////   position_top_right = 5,
////   position_hcenter = 6,
////   position_top_center = 7,
////   e_position_bottom = 8,
////   position_vcenter = 9,
////   position_bottom_left = 10,
////   position_left_center = 11,
////   position_bottom_right = 12,
////   position_right_center = 13,
////   position_bottom_center = 14,
////   position_center = 15,
////};
////
////
////namespace user
////{
////   enum enum_line_hit
////   {
////      e_line_hit_none,
////      e_line_hit_normal,
////      e_line_hit_link,
////   };
////}
////
//
//
//namespace user
//{
//
//   namespace rich_text
//   {
//
//
//      class edit;
//      class data;
//
//
//   }  // namespace rich_text
//
//
//} // namespace user
//
//
////#include "core/user/rich_text/edit.h"
//
//
//#include "list_column.h"
//
//#include "list_column_array.h"
//
//#include "list_header.h"
////#include "tool_window.h"
//
//
//
//#include "color_combo_box.h"
//#include "font_combo_box.h"
//
//
//#include "toggle_switch.h"
//
//
//#include "mesh_item.h"
//#include "list_item.h"
//
//#include "mesh_cache_interface.h"
//
//
//
//#include "mesh.h"
//#include "list.h"
//
//#include "list_impact.h"
//#include "mesh_cache.h"
//#include "list_cache.h"
//
//#include "core/user/simple/mesh_data.h"
//#include "core/user/simple/list_data.h"
//
//
//
//
//
//
//namespace user
//{
//   
//}
//
//class simple_frame_window;
//
//
//
//
//
//
//
//
//#include "xfplayer_impact_line.h"
//#include "xfplayer_impact_lines.h"
//
////#include "tool_tip_tool.h"
////#include "tool_tip_window.h"
//
//
//
//struct __SIZEPARENTPARAMS;
//
//
//namespace user
//{
//
//
//   class user;
//
//
//} // namespace user
//
//
////#include "toolbar_control.h"
//
////#include "statusbar.h"
//
//#include "form_mesh.h"
//#include "form_list.h"
//#include "form_list_impact.h"
//
//
////#include "step_slider.h"
////#include "elastic_slider.h"
//
//
//#include "image_manager.h"
//
//
//#include "core/user/netuser/_.h"
//
//
////#define memory_new ACME_NEW
//
//
//#include "form_mesh.h"
//
//
////#include "font_list.h"
//
//
//
////#include "tooltip.h"
//
//
//#include "aura/user/user/shell.h"
//
//
//#include "core/filesystem/filemanager/component.h"
//
//
//
//#include "core/user/user/user.h"
//
//
//
//#if !BROAD_PRECOMPILED_HEADER
//#include "_impl.h"
//#endif
//
//
//
//
//
