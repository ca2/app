//Created on bare metal machine at miami by camilo remotely from ca2 on 2021-10-10 05:00 PM BRT <3ThomasBorregaardS�rensen!! Thomas Likes number 5!!
#pragma once


enum enum_subject
{


   e_subject_none = 0xffffffffffffffffll,

   e_subject_not_modified = 0,
   //e_subject_prepare,
   //e_subject_process,
   //e_subject_deliver,
   e_subject_handle,
   e_subject_notify,


   // user subject
   e_subject_initialize_control = 1'073'741'824, // 0x40000000
   e_subject_action,
   e_subject_left_button_down,
   e_subject_left_button_double_click,
   e_subject_click,
   e_subject_context_menu,
   //subjectnt_m_button_down,
   //subjectnt_m_button_up,
   e_subject_list_clicked,
   //subjectnt_mouse_enter,
   //subjectnt_mouse_leave,
   e_subject_set_check,
   e_subject_timer,
   e_subject_enter_key,
   e_subject_escape,
   e_subject_tab_key,
   e_subject_key_down,
   e_subject_after_change_text,
   e_subject_after_change_text_format,
   e_subject_after_change_cur_sel,
   e_subject_after_change_cur_hover,
   e_subject_mouse_enter,
   e_subject_mouse_leave,
   e_subject_timebar_change,
   e_subject_menu_hover,
   e_subject_context_menu_close,
   e_subject_set_focus,
   e_subject_kill_focus,
   e_subject_on_create_impact,
   e_subject_on_create_tab,
   e_subject_form_initialize,
   e_subject_create,
   e_subject_layout,
   e_subject_calc_item_height,
   e_subject_change_view_style,
   e_subject_item_clicked,
   e_subject_image_list_action,
   e_subject_load_form_data,
   e_subject_save_form_data,
   e_subject_close_app,
   e_subject_switch,


   e_subject_show_view,
   e_subject_load_projects,


   e_subject_task_bar_created,


};




