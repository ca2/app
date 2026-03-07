//
//  notification_listener.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-03-07 01:42
//  ♥️ Jeg Elsker Dig Thomas Borregaard Sørensen!!
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


namespace user
{


enum enum_notification
{
  e_notification_none,
   e_notification_keyboard_layout_change,
   
};

   class CLASS_DECL_AURA notification_listener :
      virtual public ::particle
   {
   public:
      
      ::comparable_raw_array_base<enum_notification> m_enotificationa;
      
      notification_listener();
      ~notification_listener() override;
      
      
      virtual void on_keyboard_layout_change(const char * pszKeyboardLayoutId);
      
   };


} // namespace user
