////
////  menu_shared_command.h
////  apex
////
////  Created by Camilo Sasuke Thomas Borregaard Soerensen on 23/09/20.
////  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
////
/// Refactoring (from application_menu and menu_shared) by
/// camilo on 2023-10-26 00:21 <3ThomasBorregaardSorensen
#pragma once


namespace apex
{


   class CLASS_DECL_APEX menu_command :
   virtual public ::particle
   {
   public: // re-implementations only
      
      
      int * m_pestatus;
      
      
      menu_command(int* pestatus);
      
      virtual void enable(bool bOn = true);
      
      virtual void enable(bool bOn, const ::action_context& context);
      
      //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
      virtual void _001SetCheck(enum_check echeck = ::e_check_checked);
      virtual void _001SetCheck(enum_check echeck, const ::action_context& context);  // 0, 1 or 2 (indeterminate)
      
      
      //   virtual void SetRadio(bool bOn = true, const ::action_context & context = ::e_source_system);
      //virtual void SetText(const ::scoped_string & scopedstrText, const ::action_context & context = ::e_source_system);
      
   };


} // namespace apex



