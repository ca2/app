//
//  menu_shared_command.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 23/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


class menu_shared_command :
   public ::user::command        // class private to this file !
{
public: // re-implementations only

   int * m_pestatus;

   menu_shared_command(int * pestatus):
   m_pestatus(pestatus)
   {
   }
   virtual void Enable(bool bOn = TRUE, const ::action_context & context = ::source_system)
   {
         if(bOn)
         {

            *m_pestatus &= ~menu_shared::status_disabled;

         }
         else
         {

            *m_pestatus |= menu_shared::status_disabled;

         }

   }
   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(enum_check echeck, const ::action_context & context = ::source_system)   // 0, 1 or 2 (indeterminate)
   {

      if(echeck == check_checked)
      {

         *m_pestatus |= menu_shared::status_checked;

      }
      else
      {

         *m_pestatus &= ~menu_shared::status_checked;

      }
   }
//   virtual void SetRadio(bool bOn = TRUE, const ::action_context & context = ::source_system);
   //virtual void SetText(const char * pszText, const ::action_context & context = ::source_system);

};

