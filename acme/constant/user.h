#pragma once





//#define make_int(a, b)      ((int)(((unsigned short)(((dword_ptr)(a)) & 0xffff)) | ((unsigned int)((unsigned short)(((dword_ptr)(b)) & 0xffff))) << 16))



enum enum_position
{
   e_position_none = 0,
   e_position_top = 1,
   e_position_left = 2,
   e_position_top_left = 3,
   e_position_right = 4,
   e_position_top_right = 5,
   e_position_hcenter = 6,
   e_position_top_center = 7,
   e_position_bottom = 8,
   e_position_vcenter = 9,
   e_position_bottom_left = 10,
   e_position_left_center = 11,
   e_position_bottom_right = 12,
   e_position_right_center = 13,
   e_position_bottom_center = 14,
   e_position_center = 15,
};


namespace user
{


   enum enum_layout
   {

      e_layout_sketch, // layouting request ("staging area")
      e_layout_lading, // layouting request ("staging area")
      e_layout_layout, // to layout
      e_layout_design, // ready to process
      //      layout_bitmap, // drawn/ready sketch
      e_layout_output, // screen output 
      e_layout_window, // happening window
      e_layout_normal, // window last restored state

      e_layout_count_child = e_layout_design + 1,
      e_layout_count_owner = e_layout_window + 1,
      e_layout_maximum_count = e_layout_normal + 1,

   };

   enum enum_tool
   {

      e_tool_none,
      e_tool_color,
      e_tool_font,

   };

   enum enum_state
   {

      e_state_none,
      e_state_selected = 1 << 0,
      e_state_hover = 1 << 1,
      e_state_disabled = 1 << 2,
      e_state_pressed = 1 << 3,
      e_state_new_input = 1 << 4,
      e_state_focused = 1 << 5,
      e_state_checked = 1 << 6,

   };
   //// Use Good Variable Names instead of the following

   //using color_text = ::color::color;
   //   using color_text_highlight = ::color::color;
   //   using color_text_selected = ::color::color;
   //   using color_text_selected_highlight = ::color::color;
   //   using color_text_focused = ::color::color;
   //   using color_background = ::color::color;
   //   using color_background_highlight = ::color::color;
   //   using color_background_selected = ::color::color;
   //   using color_background_selected_highlight = ::color::color;
   //   using color_background_selected_hover = ::color::color;
   //   using color_border = ::color::color;
   //   using color_border_hover = ::color::color;
   //   using color_border_press = ::color::color;
   //   using color_border_disabled = ::color::color;
   //   using color_background_hover = ::color::color;
   //   using color_background_press = ::color::color;
   //   using color_background_press_hover = ::color::color;
   //   using color_background_disabled = ::color::color;
   //   using color_text_normal = ::color::color;
   //   using color_text_hover = ::color::color;
   //   using color_text_press = ::color::color;
   //   using color_text_press_hover = ::color::color;
   //   using color_text_disabled = ::color::color;
   //   using color_button_background = ::color::color;
   //   using color_button_background_hover = ::color::color;
   //   using color_button_background_press = ::color::color;
   //   using color_button_background_disabled = ::color::color;
   //   using color_button_text = ::color::color;
   //   using color_button_text_hover = ::color::color;
   //   using color_button_text_press = ::color::color;
   //   using color_button_text_disabled = ::color::color;
   //   using color_face = ::color::color;
   //   using color_face_lite = ::color::color;
   //   using color_list_header = ::color::color;
   //   using color_list_header_background = ::color::color;
   //   using color_list_header_separator = ::color::color;
   //   using color_list_item_background = ::color::color;
   //   using color_list_item_background_hover = ::color::color;
   //   using color_list_item_background_selected = ::color::color;
   //   using color_list_item_background_selected_hover = ::color::color;
   //   using color_list_item_text = ::color::color;
   //   using color_list_item_text_hover = ::color::color;
   //   using color_list_item_text_selected = ::color::color;
   //   using color_list_item_text_selected_hover = ::color::color;
   //   using color_list_background = ::color::color;
   //   using color_edit_text = ::color::color;
   //   using color_edit_background = ::color::color;
   //   using color_edit_text_selected = ::color::color;
   //   using color_edit_background_selected = ::color::color;
   //   using color_edit_text_empty = ::color::color;
   //   using color_tree_background = ::color::color;
   //   using color_impact_background = ::color::color;
   //   using color_toolbar_background = ::color::color;
   //   using color_toolbar_separator = ::color::color;
   //   using color_split_layout_background = ::color::color;
   //   using color_tab_client_background = ::color::color;
   //   using color_tab_layout_background = ::color::color;
   //   using color_action_hover_border_color = ::color::color;
   //   using color_scrollbar = ::color::color;
   //   using color_scrollbar_hover = ::color::color;
   //   using color_scrollbar_draw = ::color::color;
   //   using color_scrollbar_draw_hover = ::color::color;
   //   using color_scrollbar_strong = ::color::color;
   //   using color_scrollbar_strong_hover = ::color::color;
   //   using color_scrollbar_border = ::color::color;
   //   using color_scrollbar_border_hover = ::color::color;
   //   using color_scrollbar_lite_border = ::color::color;
   //   using color_scrollbar_lite_border_hover = ::color::color;
   //   using color_scrollbar_background = ::color::color;
   //   using color_scrollbar_background_hover = ::color::color;
   //   using color_menu_background = ::color::color;

   //   // Use Good Variable Names instead of the following

   enum enum_int
   {

      e_int_none,
      e_int_border,
      e_int_element_padding,
      e_int_menu_check_padding,
      e_int_check_box_size,
      e_int_still_text_align,
      e_int_button_text_align,
      e_int_button_text_and_image_align,
      e_int_edit_text_align,
      e_int_menu_item_text_align,
      e_int_list_item_text_align,
      e_int_still_draw_text_flags,
      e_int_button_draw_text_flags,
      e_int_button_draw_text_and_image_flags,
      e_int_edit_draw_text_flags,
      e_int_menu_item_draw_text_flags,
      e_int_list_item_draw_text_flags,
      e_int_top_level_drawing_order,
      e_int_button_press_shift_cx,
      e_int_button_press_shift_cy,
      e_int_scroll_bar_thickness,

   };


   enum enum_object
   {

      e_object_list,
      e_object_tree

   };


   enum enum_theme
   {

      e_theme_lite,
      e_theme_blue,
      e_theme_dark

   };


   enum enum_translucency
   {

      e_translucency_undefined,
      e_translucency_none,
      e_translucency_present,
      e_translucency_total

   };


   enum enum_control_type
   {
      e_control_type_none,
      e_control_type_static,
      e_control_type_check_box,
      e_control_type_edit,
      e_control_type_simple_list,
      e_control_type_button,
      e_control_type_combo_box,
      e_control_type_edit_plain_text,
      e_control_type_list,
      e_control_type_mesh,
      e_control_type_tree,
      e_control_type_split,
      e_control_type_tab,
      e_control_type_toolbar,
      e_control_type_statusbar,
      e_control_type_menu,
      e_control_type_menu_popup,
      e_control_type_menu_button,
      e_control_type_menu_button_close,
      e_control_type_system_menu,
      e_control_type_system_menu_popup,
      e_control_type_system_menu_button,
      e_control_type_system_menu_close,
      e_control_type_form,
      e_control_type_scroll_bar,
      e_control_type_multiple_option,

   };






   //enum e_font
   //{

   //   font_default,
   //   font_button,
   //   font_plain_edit,
   //   font_tree,
   //   font_list_item,
   //   font_list_hover,
   //   font_list_header,
   //   font_static,
   //   font_toolbar,
   //   font_tab,
   //   font_tab_hover,
   //   font_tab_sel,
   //   font_tab_sel_hover,
   //   font_tab_big_bold,
   //   font_window_title,

   //};



   //enum e_rect
   //{
   //   // Use Good Variable Names instead of the following

   //   rect_none,
   //   rect_button_margin,
   //   rect_button_padding,
   //   rect_button_border,
   //   rect_menu_margin,
   //   rect_menu_padding,
   //   rect_menu_border,
   //   rect_menu_item_margin,
   //   rect_menu_item_padding,
   //   rect_menu_item_border,
   //   rect_edit_padding,
   //   rect_tab_margin,
   //   rect_tab_border,
   //   rect_tab_padding,

   //};



#define DRAWING_ORDER_FRAME_OVER 0
#define DRAWING_ORDER_CLIENT_OVER 1

   //      // Use Good Variable Names instead of the following

   enum enum_double
   {

      e_double_none,
      e_double_default_one_min,
      e_double_width_rate,
      e_double_list_item_height_rate,
      e_double_tree_item_height_rate,
      e_double_default_one_max,
      e_double_focus_height_width,

   };


   enum enum_control_function
   {
      // Text got from control m_uiId member
      e_control_function_static,
      // Text got from control m_uiText member
      e_control_function_static2,
      e_control_function_data_selection,
      e_control_function_check_box,
      e_control_function_duplicate_on_check_box,
      e_control_function_disable_on_check_box,
      e_control_function_save_on_change,
      e_control_function_vms_data_edit,
      e_control_function_action,
      e_control_function_edit_multi_line,
   };


   enum enum_control_data_type
   {
      e_control_data_type_string,
      e_control_data_type_natural,
   };


   enum enum_control_ddx
   {

      e_control_ddx_none,
      e_control_ddx_flags,
      e_control_ddx_dbflags,

   };


   enum enum_mouse
   {

      e_mouse_none = 0,
      e_mouse_left_button = 1,
      e_mouse_right_button = 2,
      e_mouse_middle_button = 4,

   };

   enum enum_line_hit
   {
      e_line_hit_none,
      e_line_hit_normal,
      e_line_hit_link,
   };

   enum enum_tree_element
   {
      e_tree_element_expand_box,
      e_tree_element_image,
      e_tree_element_text,
   };


   enum enum_input_type
   {

      e_input_type_none,
      e_input_type_action,
      e_input_type_toggle,
      e_input_type_list,
      e_input_type_text,

   };



   enum enum_activation
   {


      e_activation_default = 0,
      e_activation_no_activate = 1 << 0,
      e_activation_set_active = 1 << 1,
      e_activation_under_mouse_cursor = 1 << 3,
      e_activation_display_change = 1 << 5,
      e_activation_for_context_menu = 1 << 7,
      e_activation_set_popup = 1 << 14,
      e_activation_on_center_of_screen = 1 << 15,
      e_activation_set_foreground = 1 << 16,

   };


} // namespace user


enum enum_toolbar_style
{

   e_toolbar_style_none = 0,
   e_toolbar_style_button = 0,
   e_toolbar_style_separator = 1,
   e_toolbar_style_check = 2,
   e_toolbar_style_group = 4,
   e_toolbar_style_check_group = e_toolbar_style_check | e_toolbar_style_group,
   e_toolbar_style_dropdown = 8,
   e_toolbar_style_autosize = 16,
   e_toolbar_style_noprefix = 32,
   e_toolbar_style_tooltips = 256,
   e_toolbar_style_wrapable = 512,
   e_toolbar_style_alt_drag = 1024,
   e_toolbar_style_flat = 2048,
   e_toolbar_style_list = 4096,
   e_toolbar_style_custom_erase = 8192,
   e_toolbar_style_register_drop = 16384,
   e_toolbar_style_transparent = 32768,

};


enum enum_toolbar_style_ex
{
   e_toolbar_style_ex_none = 0,
   e_toolbar_style_ex_drawddarrows = 1,

};


enum enum_scroll_command
{

   e_scroll_command_line_near = 0,
   e_scroll_command_line_up = e_scroll_command_line_near,
   e_scroll_command_line_left = e_scroll_command_line_near,
   e_scroll_command_line_far = 1,
   e_scroll_command_line_down = e_scroll_command_line_far,
   e_scroll_command_line_right = e_scroll_command_line_far,
   e_scroll_command_page_near = 2,
   e_scroll_command_page_up = e_scroll_command_page_near,
   e_scroll_command_page_left = e_scroll_command_page_near,
   e_scroll_command_page_far = 3,
   e_scroll_command_page_down = e_scroll_command_page_far,
   e_scroll_command_page_right = e_scroll_command_page_far,
   e_scroll_command_thumb_position = 4,
   e_scroll_command_thumb_track = 5,
   e_scroll_command_home = 6,
   e_scroll_command_top = e_scroll_command_home,
   e_scroll_command_left = e_scroll_command_home,
   e_scroll_command_end = 7,
   e_scroll_command_bottom = e_scroll_command_end,
   e_scroll_command_right = e_scroll_command_end,
   e_scroll_command_wheel_near = 8,
   e_scroll_command_wheel_up = e_scroll_command_wheel_near,
   e_scroll_command_wheel_far = 9,
   e_scroll_command_wheel_down = e_scroll_command_wheel_far,
   e_scroll_command_end_scroll = 10,

};





enum enum_hit_test
{
   e_hit_test_error = -2,
   e_hit_test_transparent = -1,
   e_hit_test_nowhere = 0,
   e_hit_test_client = 1,
   e_hit_test_caption = 2,
   e_hit_test_sysmenu = 3,
   e_hit_test_grow_box = 4,
   e_hit_test_size = e_hit_test_grow_box,
   e_hit_test_menu = 5,
   e_hit_test_hscroll = 6,
   e_hit_test_vscroll = 7,
   e_hit_test_minimize_button = 8,
   e_hit_test_maximize_button = 9,
   e_hit_test_left = 10,
   e_hit_test_right = 11,
   e_hit_test_top = 12,
   e_hit_test_top_left = 13,
   e_hit_test_top_right = 14,
   e_hit_test_bottom = 15,
   e_hit_test_bottom_left = 16,
   e_hit_test_bottom_right = 17,
   e_hit_test_border = 18,
   e_hit_test_reduce = e_hit_test_minimize_button,
   e_hit_test_zoom = e_hit_test_maximize_button,
   e_hit_test_size_first = e_hit_test_left,
   e_hit_test_size_last = e_hit_test_bottom_right,
   e_hit_test_object = 19,
   e_hit_test_close = 20,
   e_hit_test_help = 21,

};


#include "acme/constant/activate.h"



namespace user
{


   enum enum_flag
   {

      e_flag_none,
      e_flag_border = 1 << 0,
      e_flag_modifier_impact = 1 << 1,
      e_flag_tool_impact = 1 << 2,
      e_flag_blur_background = 1 << 3,
      e_flag_hide_all_others_on_show = 1 << 4,
      e_flag_hidid_on_show = 1 << 5,
      e_flag_strict_update = 1 << 6,
      e_flag_hide_on_kill_focus = 1 << 7,
      e_flag_background_bypass = 1 << 8,

   };

   enum enum_interaction : long long
   {

      e_interaction_none = 0,
      e_interaction_system_context_menu = 1 << 0,
      e_interaction_wfi_up_down_loading2 = 1 << 1,
      e_interaction_wfi_up_tool_window2 = 1 << 2,


   };



   enum enum_zorder
   {

      e_zorder_none = 0,
      e_zorder_front = 1,
      e_zorder_back = 2,
      e_zorder_any = e_zorder_front | e_zorder_back,

   };





} // namespace user




//
//  tool_item.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 03/Oct/22 20:28
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


enum enum_tool_item_state : long long
{

   e_tool_item_state_none,
   e_tool_item_state_checked = 1 << 0,
   e_tool_item_state_pressed = 1 << 1,
   e_tool_item_state_enabled = 1 << 2,
   e_tool_item_state_hidden = 1 << 3,
   e_tool_item_state_indeterminate = 1 << 4,
   e_tool_item_state_wrap = 1 << 5,
   e_tool_item_state_ellipses = 1 << 6,
   e_tool_item_state_marked = 1 << 7,
   e_tool_item_state_hover = 1 << 8,

};


enum enum_tool_item_style : long long
{

   e_tool_item_style_none = e_toolbar_style_none,
   e_tool_item_style_separator = e_toolbar_style_separator,
   e_tool_item_style_checkbox = e_toolbar_style_check,
   e_tool_item_style_group = e_toolbar_style_group,
   e_tool_item_style_check_group = e_tool_item_style_group | e_tool_item_style_checkbox,
   e_tool_item_style_dropdown = e_toolbar_style_dropdown,
   e_tool_item_style_autosize = e_toolbar_style_autosize,
   e_tool_item_style_noprefix = e_toolbar_style_noprefix,
   e_tool_item_style_custom_control = 1_uintmax,
   //#define TBBS_AUTOSIZE   make_int(TBSTYLE_AUTOSIZE, 0) // autocalc button width
   //#define TBBS_NOPREFIX   make_int(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
   e_tool_item_style_checked = make_int(0, e_tool_item_state_checked),
   e_tool_item_style_pressed = make_int(0, e_tool_item_state_pressed),
   e_tool_item_style_disabled = make_int(0, e_tool_item_state_enabled),
   e_tool_item_style_indeterminate = make_int(0, e_tool_item_state_indeterminate),
   e_tool_item_style_hidden = make_int(0, e_tool_item_state_hidden),
   e_tool_item_style_wrapped = make_int(0, e_tool_item_state_wrap),
   e_tool_item_style_ellipses = make_int(0, e_tool_item_state_ellipses),
   e_tool_item_style_marked = make_int(0, e_tool_item_state_marked),
};


