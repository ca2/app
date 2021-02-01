//
//  menu_shared_command.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 23/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


class CLASS_DECL_APEX menu_shared_command :
   public ::user::command        // class private to this file !
{
public: // re-implementations only

   
   int * m_pestatus;


   menu_shared_command(int* pestatus);


   virtual void enable(bool bOn = true, const ::action_context& context = ::e_source_system);

   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(enum_check echeck, const ::action_context& context = ::e_source_system);  // 0, 1 or 2 (indeterminate)


//   virtual void SetRadio(bool bOn = true, const ::action_context & context = ::e_source_system);
   //virtual void SetText(const char * pszText, const ::action_context & context = ::e_source_system);

};

