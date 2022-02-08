//Created on bare metal machine at miami by camilo remotely from ca2 on 2021-10-10 05:00 PM BRT <3ThomasBorregaardS�rensen!! Thomas Likes number 5!!
#pragma once


enum enum_topic
{


   id_none = 0xffffffffffffffffll,

   id_not_modified = 0,
   //id_prepare,
   //id_process,
   //id_deliver,
   id_handle,
   id_notify,
   id_call_message, 
   id_trigger_id,


   // user topic
   id_initialize_control = 1'073'741'824, // 0x40000000
   id_action,
   id_left_button_down,
   id_left_button_double_click,
   id_click,
   id_context_menu,
   //subjectnt_m_button_down,
   //subjectnt_m_button_up,
   id_list_clicked,
   //subjectnt_mouse_enter,
   //subjectnt_mouse_leave,
   id_set_check,
   id_timer,
   id_enter_key,
   id_escape,
   id_tab_key,
   id_key_down,
   id_after_change_text,
   id_after_change_text_format,
   id_after_change_cur_sel,
   id_after_change_cur_hover,
   id_mouse_enter,
   id_mouse_leave,
   id_timebar_change,
   id_menu_hover,
   id_context_menu_close,
   id_set_focus,
   id_kill_focus,
   id_on_create_impact,
   id_on_create_tab,
   id_form_initialize,
   id_create,
   id_layout,
   id_calc_item_height,
   id_change_view_style,
   id_item_clicked,
   id_image_list_action,
   id_load_form_data,
   id_save_form_data,
   id_close_app,
   id_switch,


   id_show_view,
   id_load_projects,


   id_task_bar_created,


};




