// Created by camilo on 2026-04-17 17:40 <3ThomasBorregaardSørensen!!
// Using HKL (Windows Keyboard Layout) code from TightVNC.
#pragma once
// #ifndef _BASE_WINDOW_H_
// #define _BASE_WINDOW_H_

#include "innate_subsystem/_common_header.h"

namespace innate_subsystem
{

    struct CLASS_DECL_INNATE_SUBSYSTEM keyboard_state_t
    {

        
      // This state doesn't difference between left and right modifiers. It's
       // needed to ToUnicodeEx().
       unsigned char m_viewerKeyState[256];

       // This state does difference between left and right modifiers. It's
       // needed to know the server side state (e.g. to release or restore
       // modifiyers state outside from a real key event).
       unsigned char m_serverKeyState[256];
       bool m_leftMetaIsPressed;
       bool m_rightMetaIsPressed;

       bool m_allowProcessCharEvent;
       bool m_allowProcessDoubleChar;
       bool m_doubleDeadCatched;

       keyboard_state_t();

        void clearKeyState();

       bool isPressed(unsigned char virtKey);

             //void clearKeyState();
       int GettingCharFromCtrlSymbol(int ch);

       //bool isPressed(unsigned char virtKey);

    };

   class KeyboardLayoutInterface :
       virtual public ::Particle
   {
   public:


       virtual bool vkCodeToString(unsigned short virtKey, bool down,
                                  ::wstring *res, keyboard_state_t *pkeyboardstate) = 0;

   };

   //class CLASS_DECL_INNATE_SUBSYSTEM KeyboardLayoutCallback : virtual public Callback<KeyboardLayoutInterface>
   //{
   //public:

   //   ImplementCallbackø(KeyboardLayout, keyboardlayout)
   //};

   class CLASS_DECL_INNATE_SUBSYSTEM KeyboardLayoutComposite : virtual public Composite<KeyboardLayoutInterface>
   {
   public:

      //ImplementCompositeWithCallbackø(KeyboardLayout, window)

       ImplementCompositeø(KeyboardLayout, keyboardlayout) 
           
           
           bool vkCodeToString(unsigned short virtKey, bool down, ::wstring *res, keyboard_state_t *pkeyboardstate) override
       {

           return m_pkeyboardlayout->vkCodeToString(virtKey, down, res, pkeyboardstate);

       }

   };

   class CLASS_DECL_INNATE_SUBSYSTEM KeyboardLayoutAggregate : virtual public Aggregate<KeyboardLayoutComposite>
   {
   public:

      ImplementBaseø(KeyboardLayout)
   };


   class CLASS_DECL_INNATE_SUBSYSTEM KeyboardLayout : virtual public Object<KeyboardLayoutAggregate>
   {
   public:
   };


   
   inline bool isDeadCharacter(int ch)
   {
      return (ch == '^' || ch == 0x00a8 || //
              ch == '~' || ch == 0x00b4 || //
              ch == '`' || ch == 0x02c7 || //
              ch == 0x02d8 || //
              ch == 0x00b0 || //
              ch == 0x02d9 || //
              ch == 0x02dd || //
              ch == 0x00b8 || //
              ch == 0x02db //
      );
   }

   inline bool isDoubleDeadCharacters(wchar_t *buff) { return (isDeadCharacter(buff[0]) && buff[0] == buff[1]); }


} // namespace innate_subsystem
