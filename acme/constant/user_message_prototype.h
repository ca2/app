//
// Created by camilo on 22/10/22.
// From apex/message/_constant.h by camilo on 2022-11-02 06:28 <3ThomasBorregaardSorensen!!
// From message_prototype.h by camilo on 2025-09-01 18:12 <3ThomasBorregardSorensen!!
//
#pragma once


namespace user
{


   enum enum_message_prototype : int
   {

      e_message_prototype_none,
      e_message_prototype_mouse,
      e_message_prototype_scroll,
      e_message_prototype_size,
      e_message_prototype_move,
      e_message_prototype_measure_item,
      e_message_prototype_create,
      e_message_prototype_activate,
      e_message_prototype_non_client_activate,
      e_message_prototype_mouse_activate,
      e_message_prototype_erase_background,
      e_message_prototype_show_window,
      e_message_prototype_set_cursor,
      e_message_prototype_timer,
      e_message_prototype_mouse_wheel,
      e_message_prototype_init_menu_popup,
      e_message_prototype_enable,
      e_message_prototype_non_client_hit_test,
      e_message_prototype_key,
      e_message_prototype_notify,
      e_message_prototype_update_command_user_interface,
      e_message_prototype_ctl_color,
      e_message_prototype_ctl_color_reflect,
      e_message_prototype_kill_focus,
      e_message_prototype_set_focus,
      e_message_prototype_command,
      e_message_prototype_window_pos,
      e_message_prototype_non_client_calc_size,
      e_message_prototype_on_draw,
      e_message_prototype_simple_command,
      e_message_prototype_object,

   };


} // namespace user



