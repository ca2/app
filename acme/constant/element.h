//
// Created by camilo on 2022-10-23 14:16 <3ThomasBorregaardSorensen!!
//
#pragma once


enum enum_element : ::i64
{

   e_element_none,



   // user element
   e_element_frame_window = 0x40000000, // 1'073'741'824
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
   e_element_item_border,
   e_element_hilite_text,
   e_element_icon,
   e_element_background,
   e_element_separator,
   e_element_face,
   e_element_border,
   e_element_lite_border,
   e_element_client,
   //e_element_resize,
   e_element_non_client, // but m_bMouseHoverOnCapture ?
   e_element_area,
   e_element_drop_down,
   e_element_combo_edit,
   e_element_item,
   e_element_search_edit,
   e_element_search_ok,
   e_element_scrollbar,
   e_element_scrollbar_draw,
   e_element_scrollbar_strong,
   e_element_scrollbar_trackbar,
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
   e_element_check,
   e_element_switch_button,
   e_element_switch_icon,
   e_element_top_left_icon,
   e_element_move_grip_minimal,
   e_element_maximize_button,
   e_element_maximize_icon,
   e_element_minimize_button,
   e_element_minimize_icon,
   e_element_resize,
   //e_element_bar_drag_scroll_horizontal,
   //e_element_bar_drag_scroll_vertical,


   e_element_split = 10000,

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
   e_element_desk_change_impact,
   e_element_desk_change_theme,
   e_element_desk_last,

   e_element_start,
   e_element_reset,
   e_element_cancel,

};


DECLARE_ENUMERATION(e_element, enum_element);



