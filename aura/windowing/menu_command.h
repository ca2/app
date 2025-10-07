//
//  menu_command.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 23/09/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#include "aura/user/menu/command.h"


namespace windowing
{

   class menu_item;

   class CLASS_DECL_AURA menu_command :
      public ::menu::command        // class private to this file !
   {
   public: // re-implementations only


      ::pointer<menu_item>      m_pitem;


      menu_command(menu_item * pitem);


      virtual void enable(bool bOn = true, const ::action_context & context = ::e_source_system);

      //   virtual void set_check(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
      virtual void set_check(enum_check echeck, const ::action_context & context = ::e_source_system);  // 0, 1 or 2 (indeterminate)


   //   virtual void SetRadio(bool bOn = true, const ::action_context & context = ::e_source_system);
      //virtual void SetText(const ::scoped_string & scopedstrText, const ::action_context & context = ::e_source_system);

   };


} // namespace windowing




