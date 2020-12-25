#pragma once


#include "acme/user/_const.h"


//
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
//
//
//
//namespace user
//{
//
//
//   enum enum_layout
//   {
//
//      e_layout_sketch, // layouting request ("staging area")
//      e_layout_design, // ready to process
////      layout_bitmap, // drawn/ready sketch
//      e_layout_output, // screen output
//      e_layout_window, // event window
//
//      e_layout_count_child = e_layout_design + 1,
//      e_layout_count_owner = e_layout_window + 1,
//
//   };
//
//   enum enum_tool
//   {
//
//      e_tool_none,
//      e_tool_color,
//      e_tool_font,
//
//   };
//
//   enum enum_state
//   {
//
//      e_state_none,
//      e_state_disabled = 1 << 0,
//      e_state_selected = 1 << 1,
//      e_state_hover = 1 << 2,
//      e_state_pressed = 1 << 3,
//      e_state_new_input = 1 << 4,
//      e_state_focused = 1 << 5,
//      e_state_checked = 1 << 6,
//
//   };
//   //// Use Good Variable Names instead of the following
//
//   //using color_text = ::color;
//   //   using color_text_highlight = ::color;
//   //   using color_text_selected = ::color;
//   //   using color_text_selected_highlight = ::color;
//   //   using color_text_focused = ::color;
//   //   using color_background = ::color;
//   //   using color_background_highlight = ::color;
//   //   using color_background_selected = ::color;
//   //   using color_background_selected_highlight = ::color;
//   //   using color_background_selected_hover = ::color;
//   //   using color_border = ::color;
//   //   using color_border_hover = ::color;
//   //   using color_border_press = ::color;
//   //   using color_border_disabled = ::color;
//   //   using color_background_hover = ::color;
//   //   using color_background_press = ::color;
//   //   using color_background_press_hover = ::color;
//   //   using color_background_disabled = ::color;
//   //   using color_text_normal = ::color;
//   //   using color_text_hover = ::color;
//   //   using color_text_press = ::color;
//   //   using color_text_press_hover = ::color;
//   //   using color_text_disabled = ::color;
//   //   using color_button_background = ::color;
//   //   using color_button_background_hover = ::color;
//   //   using color_button_background_press = ::color;
//   //   using color_button_background_disabled = ::color;
//   //   using color_button_text = ::color;
//   //   using color_button_text_hover = ::color;
//   //   using color_button_text_press = ::color;
//   //   using color_button_text_disabled = ::color;
//   //   using color_face = ::color;
//   //   using color_face_lite = ::color;
//   //   using color_list_header = ::color;
//   //   using color_list_header_background = ::color;
//   //   using color_list_header_separator = ::color;
//   //   using color_list_item_background = ::color;
//   //   using color_list_item_background_hover = ::color;
//   //   using color_list_item_background_selected = ::color;
//   //   using color_list_item_background_selected_hover = ::color;
//   //   using color_list_item_text = ::color;
//   //   using color_list_item_text_hover = ::color;
//   //   using color_list_item_text_selected = ::color;
//   //   using color_list_item_text_selected_hover = ::color;
//   //   using color_list_background = ::color;
//   //   using color_edit_text = ::color;
//   //   using color_edit_background = ::color;
//   //   using color_edit_text_selected = ::color;
//   //   using color_edit_background_selected = ::color;
//   //   using color_edit_text_empty = ::color;
//   //   using color_tree_background = ::color;
//   //   using color_view_background = ::color;
//   //   using color_toolbar_background = ::color;
//   //   using color_toolbar_separator = ::color;
//   //   using color_split_layout_background = ::color;
//   //   using color_tab_client_background = ::color;
//   //   using color_tab_layout_background = ::color;
//   //   using color_action_hover_border_color = ::color;
//   //   using color_scrollbar = ::color;
//   //   using color_scrollbar_hover = ::color;
//   //   using color_scrollbar_draw = ::color;
//   //   using color_scrollbar_draw_hover = ::color;
//   //   using color_scrollbar_strong = ::color;
//   //   using color_scrollbar_strong_hover = ::color;
//   //   using color_scrollbar_border = ::color;
//   //   using color_scrollbar_border_hover = ::color;
//   //   using color_scrollbar_lite_border = ::color;
//   //   using color_scrollbar_lite_border_hover = ::color;
//   //   using color_scrollbar_background = ::color;
//   //   using color_scrollbar_background_hover = ::color;
//   //   using color_menu_background = ::color;
//
//   //   // Use Good Variable Names instead of the following
//
//   enum enum_int
//   {
//
//      int_none,
//      int_border,
//      int_element_padding,
//      int_menu_check_padding,
//      int_check_box_size,
//      int_still_draw_text_flags,
//      int_button_draw_text_flags,
//      int_button_draw_text_and_image_flags,
//      int_edit_draw_text_flags,
//      int_menu_item_draw_text_flags,
//      int_list_item_draw_text_flags,
//      int_top_level_drawing_order,
//      int_button_press_shift_cx,
//      int_button_press_shift_cy,
//      int_scroll_bar_width,
//
//   };
//
//
//   enum e_object
//   {
//
//      object_list,
//      object_tree
//
//   };
//
//
//   enum e_theme
//   {
//
//      e_theme_lite,
//      theme_blue,
//      e_theme_dark
//
//   };
//
//
//   enum enum_translucency
//   {
//
//      e_translucency_undefined,
//      translucency_none,
//      e_translucency_present,
//      e_translucency_total
//
//   };
//
//
//   enum enum_control_type
//   {
//      e_control_type_none,
//      e_control_type_static,
//      e_control_type_check_box,
//      e_control_type_edit,
//      e_control_type_simple_list,
//      e_control_type_button,
//      e_control_type_combo_box,
//      e_control_type_edit_plain_text,
//      e_control_type_list,
//      control_type_mesh,
//      control_type_tree,
//      control_type_split,
//      control_type_tab,
//      control_type_toolbar,
//      control_type_statusbar,
//      e_control_type_menu,
//      control_type_menu_popup,
//      e_control_type_menu_button,
//      control_type_menu_button_close,
//      control_type_system_menu,
//      control_type_system_menu_popup,
//      control_type_system_menu_button,
//      control_type_system_menu_close,
//
//   };
//
//
//   enum enum_element : ::i64
//   {
//
//      e_element_none,
//      element_frame_window,
//      e_element_tab,
//      element_tab_layout_background,
//      element_tab_client_background,
//      e_element_tab_near_scroll,
//      e_element_tab_far_scroll,
//      e_element_close_tab_button,
//      element_status_image,
//      e_element_text,
//      element_list,
//      element_item_text,
//      element_item_background,
//      element_hilite_text,
//      e_element_icon,
//      e_element_background,
//      element_separator,
//      element_face,
//      e_element_border,
//      element_lite_border,
//      e_element_client,
//      element_area,
//      e_element_drop_down,
//      e_element_combo_edit,
//      e_element_item,
//      element_search_edit,
//      element_search_ok,
//      element_scrollbar,
//      element_scrollbar_draw,
//      element_scrollbar_strong,
//      element_scrollbar_rect,
//      element_scrollbar_rectA,
//      element_scrollbar_rectB,
//      element_scrollbar_pageA,
//      element_scrollbar_pageB,
//      element_margin_top,
//      element_margin_left,
//      element_margin_right,
//      element_margin_bottom,
//      element_window_title,
//      element_image,
//      element_close_button,
//      element_close_icon,
//
//
//      e_element_split = 10'000,
//
//      element_desk_launcher_1,
//      element_desk_launcher_2,
//      element_desk_launcher_3,
//      element_desk_launcher_4,
//      element_desk_launcher_5,
//      element_desk_launcher_6,
//      element_desk_launcher_7,
//      element_desk_launcher_8,
//      element_desk_launcher_last = element_desk_launcher_8,
//      element_desk_close,
//      element_desk_change_view,
//      element_desk_change_theme,
//      element_desk_last,
//
//      element_start,
//      element_reset,
//      element_cancel,
//
//   };
//
//
//   enum e_event
//   {
//
//      e_event_none,
//      event_initialize_control,
//      event_action,
//      event_button_down,
//      event_button_clicked,
//      event_m_button_down,
//      event_m_button_up,
//      event_list_clicked,
//      e_event_mouse_enter,
//      e_event_mouse_leave,
//      event_set_check,
//      event_timer,
//      event_enter_key,
//      event_escape,
//      event_tab_key,
//      event_key_down,
//      event_after_change_text,
//      event_after_change_text_format,
//      event_after_change_cur_sel,
//      event_after_change_cur_hover,
//      event_timebar_change,
//      event_menu_hover,
//      event_context_menu_close,
//      event_set_focus,
//      event_kill_focus,
//      event_on_create_impact,
//      event_on_create_tab,
//      event_form_initialize,
//      event_create,
//      event_layout,
//      event_calc_item_height,
//      event_change_view_style,
//      event_item_clicked,
//      event_image_list_action,
//      event_load_form_data,
//      event_save_form_data,
//      event_close_app,
//
//   };
//
//
//
//
//
//   //enum e_font
//   //{
//
//   //   font_default,
//   //   font_button,
//   //   font_plain_edit,
//   //   font_tree,
//   //   font_list_item,
//   //   font_list_hover,
//   //   font_list_header,
//   //   font_static,
//   //   font_toolbar,
//   //   font_tab,
//   //   font_tab_hover,
//   //   font_tab_sel,
//   //   font_tab_sel_hover,
//   //   font_tab_big_bold,
//   //   font_window_title,
//
//   //};
//
//
//   enum enum_flag
//   {
//
//      e_flag_none,
//      flag_border = 1<<0,
//      flag_modifier_impact = 1 << 1,
//      flag_tool_impact = 1 << 2,
//      flag_blur_background = 1 << 3,
//      e_flag_hide_all_others_on_show = 1 << 4,
//      flag_hide_topic_on_show = 1 << 5,
//      flag_strict_update = 1 << 6,
//      flag_hide_on_kill_focus = 1 << 7,
//      e_flag_background_bypass = 1 << 8,
//
//   };
//
//
//   //enum e_rect
//   //{
//   //   // Use Good Variable Names instead of the following
//
//   //   rect_none,
//   //   rect_button_margin,
//   //   rect_button_padding,
//   //   rect_button_border,
//   //   rect_menu_margin,
//   //   rect_menu_padding,
//   //   rect_menu_border,
//   //   rect_menu_item_margin,
//   //   rect_menu_item_padding,
//   //   rect_menu_item_border,
//   //   rect_edit_padding,
//   //   rect_tab_margin,
//   //   rect_tab_border,
//   //   rect_tab_padding,
//
//   //};
//
//
//
//#define DRAWING_ORDER_FRAME_OVER 0
//#define DRAWING_ORDER_CLIENT_OVER 1
//
//   //      // Use Good Variable Names instead of the following
//
//   enum enum_double
//   {
//
//      e_double_none,
//      e_double_default_one_min,
//      e_double_width_rate,
//      e_double_list_item_height_rate,
//      e_double_tree_item_height_rate,
//      e_double_default_one_max,
//
//   };
//
//
//   enum enum_control_function
//   {
//      // Text got from control m_uiId member
//      e_control_function_static,
//      // Text got from control m_uiText member
//      e_control_function_static2,
//      e_control_function_data_selection,
//      e_control_function_check_box,
//      e_control_function_duplicate_on_check_box,
//      e_control_function_disable_on_check_box,
//      e_control_function_save_on_change,
//      e_control_function_vms_data_edit,
//      e_control_function_action,
//      e_control_function_edit_multi_line,
//   };
//
//
//   enum enum_control_data_type
//   {
//      e_control_data_type_string,
//      e_control_data_type_natural,
//   };
//
//
//   enum enum_control_ddx
//   {
//
//      control_ddx_none,
//      control_ddx_flags,
//      e_control_ddx_dbflags,
//
//   };
//
//
//   enum enum_mouse
//   {
//
//      mouse_left_button,
//      mouse_right_button,
//      mouse_middle_button
//
//   };
//
//   enum enum_line_hit
//   {
//      e_line_hit_none,
//      e_line_hit_normal,
//      e_line_hit_link,
//   };
//
//   enum enum_tree_element
//   {
//      e_tree_element_expand_box,
//      e_tree_element_image,
//      e_tree_element_text,
//   };
//
//
//} // namespace user
//
//
//
//
////#include "_ewindowflag.h"
//



