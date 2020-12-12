#pragma once


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
      e_layout_design, // ready to process
//      layout_bitmap, // drawn/ready sketch
      e_layout_output, // screen output 
      e_layout_window, // event window

      e_layout_count_child = e_layout_design + 1,
      e_layout_count_owner = e_layout_window + 1,

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
      e_state_disabled = 1 << 0,
      e_state_selected = 1 << 1,
      e_state_hover = 1 << 2,
      e_state_pressed = 1 << 3,
      e_state_new_input = 1 << 4,
      e_state_focused = 1 << 5,
      e_state_checked = 1 << 6,

   };
   //// Use Good Variable Names instead of the following

   //using color_text = ::color;
   //   using color_text_highlight = ::color;
   //   using color_text_selected = ::color;
   //   using color_text_selected_highlight = ::color;
   //   using color_text_focused = ::color;
   //   using color_background = ::color;
   //   using color_background_highlight = ::color;
   //   using color_background_selected = ::color;
   //   using color_background_selected_highlight = ::color;
   //   using color_background_selected_hover = ::color;
   //   using color_border = ::color;
   //   using color_border_hover = ::color;
   //   using color_border_press = ::color;
   //   using color_border_disabled = ::color;
   //   using color_background_hover = ::color;
   //   using color_background_press = ::color;
   //   using color_background_press_hover = ::color;
   //   using color_background_disabled = ::color;
   //   using color_text_normal = ::color;
   //   using color_text_hover = ::color;
   //   using color_text_press = ::color;
   //   using color_text_press_hover = ::color;
   //   using color_text_disabled = ::color;
   //   using color_button_background = ::color;
   //   using color_button_background_hover = ::color;
   //   using color_button_background_press = ::color;
   //   using color_button_background_disabled = ::color;
   //   using color_button_text = ::color;
   //   using color_button_text_hover = ::color;
   //   using color_button_text_press = ::color;
   //   using color_button_text_disabled = ::color;
   //   using color_face = ::color;
   //   using color_face_lite = ::color;
   //   using color_list_header = ::color;
   //   using color_list_header_background = ::color;
   //   using color_list_header_separator = ::color;
   //   using color_list_item_background = ::color;
   //   using color_list_item_background_hover = ::color;
   //   using color_list_item_background_selected = ::color;
   //   using color_list_item_background_selected_hover = ::color;
   //   using color_list_item_text = ::color;
   //   using color_list_item_text_hover = ::color;
   //   using color_list_item_text_selected = ::color;
   //   using color_list_item_text_selected_hover = ::color;
   //   using color_list_background = ::color;
   //   using color_edit_text = ::color;
   //   using color_edit_background = ::color;
   //   using color_edit_text_selected = ::color;
   //   using color_edit_background_selected = ::color;
   //   using color_edit_text_empty = ::color;
   //   using color_tree_background = ::color;
   //   using color_view_background = ::color;
   //   using color_toolbar_background = ::color;
   //   using color_toolbar_separator = ::color;
   //   using color_split_layout_background = ::color;
   //   using color_tab_client_background = ::color;
   //   using color_tab_layout_background = ::color;
   //   using color_action_hover_border_color = ::color;
   //   using color_scrollbar = ::color;
   //   using color_scrollbar_hover = ::color;
   //   using color_scrollbar_draw = ::color;
   //   using color_scrollbar_draw_hover = ::color;
   //   using color_scrollbar_strong = ::color;
   //   using color_scrollbar_strong_hover = ::color;
   //   using color_scrollbar_border = ::color;
   //   using color_scrollbar_border_hover = ::color;
   //   using color_scrollbar_lite_border = ::color;
   //   using color_scrollbar_lite_border_hover = ::color;
   //   using color_scrollbar_background = ::color;
   //   using color_scrollbar_background_hover = ::color;
   //   using color_menu_background = ::color;

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
      e_int_scroll_bar_width,

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

   };


   enum enum_element : ::i64
   {

      e_element_none,
      e_element_frame_window,
      e_element_tab,
      e_element_tab_layout_background,
      e_element_tab_client_background,
      e_element_tab_item_background,
      e_element_tab_near_scroll,
      e_element_tab_far_scroll,
      e_element_close_tab_button,
      e_element_status_image,
      e_element_text,
      e_element_list,
      e_element_item_text,
      e_element_item_background,
      e_element_hilite_text,
      e_element_icon,
      e_element_background,
      e_element_separator,
      e_element_face,
      e_element_border,
      e_element_lite_border,
      e_element_client,
      e_element_area,
      e_element_drop_down,
      e_element_combo_edit,
      e_element_item,
      e_element_search_edit,
      e_element_search_ok,
      e_element_scrollbar,
      e_element_scrollbar_draw,
      e_element_scrollbar_strong,
      e_element_scrollbar_rect,
      e_element_scrollbar_rectA,
      e_element_scrollbar_rectB,
      e_element_scrollbar_pageA,
      e_element_scrollbar_pageB,
      e_element_margin_top,
      e_element_margin_left,
      e_element_margin_right,
      e_element_margin_bottom,
      e_element_window_title,
      e_element_image,
      e_element_close_button,
      e_element_close_icon,
      e_element_hilite,
      e_element_dark_shadow,
      e_element_button_text,
      e_element_button_background,
      e_element_button_hilite,
      e_element_button_shadow,
      e_element_button_dark_shadow,


      e_element_split = 10'000,

      e_element_desk_launcher_1,
      e_element_desk_launcher_2,
      e_element_desk_launcher_3,
      e_element_desk_launcher_4,
      e_element_desk_launcher_5,
      e_element_desk_launcher_6,
      e_element_desk_launcher_7,
      e_element_desk_launcher_8,
      e_element_desk_launcher_last = e_element_desk_launcher_8,
      e_element_desk_close,
      e_element_desk_change_view,
      e_element_desk_change_theme,
      e_element_desk_last,

      e_element_start,
      e_element_reset,
      e_element_cancel,

   };


   enum enum_event
   {

      e_event_none,
      e_event_initialize_control,
      e_event_action,
      e_event_button_down,
      e_event_button_clicked,
      e_event_m_button_down,
      e_event_m_button_up,
      e_event_list_clicked,
      e_event_mouse_enter,
      e_event_mouse_leave,
      e_event_set_check,
      e_e_event_timer,
      e_event_enter_key,
      e_event_escape,
      e_event_tab_key,
      e_event_key_down,
      e_event_after_change_text,
      e_event_after_change_text_format,
      e_event_after_change_cur_sel,
      e_event_after_change_cur_hover,
      e_event_timebar_change,
      e_event_menu_hover,
      e_event_context_menu_close,
      e_event_set_focus,
      e_event_kill_focus,
      e_event_on_create_impact,
      e_event_on_create_tab,
      e_event_form_initialize,
      e_event_create,
      e_event_layout,
      e_event_calc_item_height,
      e_event_change_view_style,
      e_event_item_clicked,
      e_event_image_list_action,
      e_event_load_form_data,
      e_event_save_form_data,
      e_event_close_app,

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

   
   enum enum_flag
   {

      e_flag_none,
      e_flag_border = 1<<0,
      e_flag_modifier_impact = 1 << 1,
      e_flag_tool_impact = 1 << 2,
      e_flag_blur_background = 1 << 3,
      e_flag_hide_all_others_on_show = 1 << 4,
      e_flag_hide_topic_on_show = 1 << 5,
      e_flag_strict_update = 1 << 6,
      e_flag_hide_on_kill_focus = 1 << 7,
      e_flag_background_bypass = 1 << 8,

   };


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

      e_mouse_left_button,
      e_mouse_right_button,
      e_mouse_middle_button

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


enum enum_toolbar_item_state
{

   e_toolbar_item_state_none            = 0,
   e_toolbar_item_state_checked         = 0x01,
   e_toolbar_item_state_pressed         = 0x02,
   e_toolbar_item_state_enabled         = 0x04,
   e_toolbar_item_state_hidden          = 0x08,
   e_toolbar_item_state_indeterminate   = 0x10,
   e_toolbar_item_state_wrap            = 0x20,
   e_toolbar_item_state_ellipses        = 0x40,
   e_toolbar_item_state_marked          = 0x80,
   e_toolbar_item_state_hover           = 0x100,

};


enum enum_toolbar_item_style
{

   e_toolbar_item_style_none = e_toolbar_style_none,
   e_toolbar_item_style_separator = e_toolbar_style_separator,
   e_toolbar_item_style_checkbox = e_toolbar_style_check,
   e_toolbar_item_style_group = e_toolbar_style_group,
   e_toolbar_item_style_check_group = e_toolbar_item_style_group | e_toolbar_item_style_checkbox,
   e_toolbar_item_style_dropdown = e_toolbar_style_dropdown,
   e_toolbar_item_style_autosize = e_toolbar_style_autosize,
   e_toolbar_item_style_noprefix = e_toolbar_style_noprefix,
//#define TBBS_AUTOSIZE   MAKELONG(TBSTYLE_AUTOSIZE, 0) // autocalc button width
//#define TBBS_NOPREFIX   MAKELONG(TBSTYLE_NOPREFIX, 0) // no accel prefix for this button
   e_toolbar_item_style_checked = MAKELONG(0, e_toolbar_item_state_checked),
   e_toolbar_item_style_pressed = MAKELONG(0, e_toolbar_item_state_pressed),
   e_toolbar_item_style_disabled = MAKELONG(0, e_toolbar_item_state_enabled),
   e_toolbar_item_style_indeterminate = MAKELONG(0, e_toolbar_item_state_indeterminate),
   e_toolbar_item_style_hidden = MAKELONG(0, e_toolbar_item_state_hidden),
   e_toolbar_item_style_wrapped = MAKELONG(0, e_toolbar_item_state_wrap),
   e_toolbar_item_style_ellipses = MAKELONG(0, e_toolbar_item_state_ellipses),
   e_toolbar_item_style_marked = MAKELONG(0, e_toolbar_item_state_marked),
};



