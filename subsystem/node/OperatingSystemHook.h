// Copyright (C) 2013 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#include "subsystem/_common_header.h"
#include "subsystem/node/OperatingSystemHookListener.h"


namespace subsystem
{


   // Class for intercepting keyboard on low level.
   class CLASS_DECL_SUBSYSTEM OperatingSystemHookInterface :
    virtual public ::subsystem::OperatingSystemHookListener
   {
   public:

      //::pointer_array < ::subsystem::OperatingSystemHookListener > m_listenera;

      //OperatingSystemHookInterface();
      //virtual ~OperatingSystemHookInterface() = 0;


      virtual bool operating_system_hook_on_keyboard_message(::lresult & lresult, ::user::enum_message emessage, ::i32 iVkCode, ::lparam lparam)  = 0;

   //    // Hook procedure.
   //    static LRESULT CALLBACK lowLevelKeyboardHook(::i32 nCode,
   //                                                 WPARAM wParam,
   //                                                 LPARAM lParam);
   //
   //    // Registration of keyboard hook.
   virtual void registerKeyboardHook(::subsystem::OperatingSystemHookListener *phooklistener) = 0;
   //
   //    // Unregistration of keyboard hook.
   virtual void unregisterKeyboardHook(::subsystem::OperatingSystemHookListener *phooklistener) = 0;

      virtual void startKeyboardHook() = 0;
      virtual void stopKeyboardHook() = 0;
   //
   // private:
   //    // Hook object.
   //    static HHOOK s_hooks;
   //
   //    // Handler to the processing hooks function.
   //    static HookEventListener *s_eventListener;
   };

//using OperatingSystemHookInterface = particle_interface<OperatingSystemHookInterface>;


   // Class for intercepting keyboard on low level.
   class CLASS_DECL_SUBSYSTEM OperatingSystemHookComposite :
   virtual public Composite< OperatingSystemHookInterface >
   {
   public:


       ImplementCompositeø(OperatingSystemHook, operatingsystemhook);

      //WinHooks();
      //OperatingSystemHook();
      //~OperatingSystemHook() override;

      //bool operating_system_hook_on_keyboard_message(::lresult & lresult, ::user::enum_message emessage, ::i32 iVkCode) override;

      //    // Hook procedure.
      //    static LRESULT CALLBACK lowLevelKeyboardHook(::i32 nCode,
      //                                                 WPARAM wParam,
      //                                                 LPARAM lParam);
      //
      //    // Registration of keyboard hook.
       void startKeyboardHook() override
       {

          m_poperatingsystemhook->startKeyboardHook();
      }
      //
      //    // Unregistration of keyboard hook.
       void stopKeyboardHook() override
       {

          m_poperatingsystemhook->stopKeyboardHook();

      }


       void registerKeyboardHook(::subsystem::OperatingSystemHookListener* phooklistener) override
       {

          m_poperatingsystemhook->registerKeyboardHook(phooklistener);

         }
      //
      //    // Unregistration of keyboard hook.
       void unregisterKeyboardHook(::subsystem::OperatingSystemHookListener* phooklistener) override
       {

          m_poperatingsystemhook->unregisterKeyboardHook(phooklistener);

      }


       bool operating_system_hook_on_keyboard_message(::lresult& lresult, ::user::enum_message emessage, ::i32 iVkCode,
          ::lparam lparam) override
       {


          return false;
         }

      //
      // private:
      //    // Hook object.
      //    static HHOOK s_hooks;
      //
      //    // Handler to the processing hooks function.
      //    static HookEventListener *s_eventListener;
   };



    class CLASS_DECL_SUBSYSTEM OperatingSystemHookAggregate :
    virtual public Aggregate< OperatingSystemHookComposite >
    {
    public:

        ImplementBaseø(OperatingSystemHook);

    };

   class CLASS_DECL_SUBSYSTEM OperatingSystemHook :
    virtual public Object < OperatingSystemHookAggregate >
   {
   public:

       ImplementObjectø(OperatingSystemHook)

   };


} // namespace subsystem

