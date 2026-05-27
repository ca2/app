// Created by camilo on 2026-04-07 07:52 <3ThomasBorregaardSørensen!!
#pragma once


namespace user
{



   enum enum_notification : ::u32
   {


      e_notification_default = 0,


      e_notification_button_clicked = 0, // _BN_CLICKED

      e_notification_combo_box_selection_change = 1, // _CBN_SELCHANGE
      e_notification_combo_box_lost_focus = 4, // _CBN_KILLFOCUS

      
      e_notification_edit_update = 4, // _EN_UPDATE
      
      
      e_notification_list_box_selection_change = 1, // _LBN_SELCHANGE
      e_notification_list_box_double_click = 2, // LBN_DBLCLK

   };





} // namespace user




