// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
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

#pragma once


#include "subsystem/_common_header.h"
//#include "remoting/remoting_common/util/winhdr.h"
//#include "acme/_operating_system.h"

////#include "subsystem/particle.h"

//#include "../SystemException.h"

namespace subsystem
{
   /**
    * Wrapper on base WinAPI keyboard functions.
    */
   class KeyboardInterface :
      virtual public ::particle_base
   {
   public:




      //Keyboard();
      //virtual ~KeyboardInterface() = 0;
      /**
       * Copied current keyboard state (256 virtual keys state) to state array.
       * @param state [out] array of 256 virtual key states.
       * @throws SystemException on error.
       */
      virtual void getState(unsigned char state[256]) = 0;

      /**
       * Sets current keyboard state.
       * @param state array of 256 virtual key states.
       * @throws SystemException on error.
       */
      virtual void setState(unsigned char state[256]) = 0;

      /**
       * Check if specified key is in pressed state.
       * @param vkCode virtual code of key.
       * @return true if key is pressed, false if released.
       */
      virtual bool isKeyPressed(unsigned char vkCode) = 0;

   };


    //using KeyboardInterface = particle_interface<KeyboardInterface>;

   /**
    * Wrapper on base WinAPI keyboard functions.
    */
   class CLASS_DECL_SUBSYSTEM KeyboardComposite :
   virtual public composite <KeyboardInterface>
   {
   public:


       implement_compositeø(Keyboard, keyboard )

      //Keyboard();
      //~Keyboard() override;
      /**
       * Copied current keyboard state (256 virtual keys state) to state array.
       * @param state [out] array of 256 virtual key states.
       * @throws SystemException on error.
       */
      void getState(unsigned char state[256]) override
       {
          m_pkeyboard->getState(state);
       }

      /**
       * Sets current keyboard state.
       * @param state array of 256 virtual key states.
       * @throws SystemException on error.
       */
      void setState(unsigned char state[256]) override
       {
          m_pkeyboard->setState(state);
       }

      /**
       * Check if specified key is in pressed state.
       * @param vkCode virtual code of key.
       * @return true if key is pressed, false if released.
       */
      bool isKeyPressed(unsigned char vkCode) override
       {
          return m_pkeyboard->isKeyPressed(vkCode);
       }

   };



    class CLASS_DECL_SUBSYSTEM Keyboard :
    virtual public aggregate< KeyboardComposite >
    {
    public:

        implement_baseø(Keyboard);

    };





} // namespace subsystem


