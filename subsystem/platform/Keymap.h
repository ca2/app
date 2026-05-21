// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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

#pragma once


#include "subsystem/_common_header.h"


namespace subsystem
{
   // FIXME: This class is Windows-specific so it should not reside in util/.

   /**
    * FIXME: Update documentation (e.g. methods are not static any more).
    * Class with static methods that allows to make 3 type of translations:
    * 1) X11 key sym to virtual key code;
    * 2) X11 key sym to char.
    * 3) char to X11 key sym.
    */
   class CLASS_DECL_SUBSYSTEM Keymap
   {
   public:
      /**
       * Converts X11 key sym to virtual key code.
       * @param keySym X11 key sym.
       * @param peuserkey [out] virtual key code.
       * @param extended [out] if the key in the Windows must be marked as extended
       * the extended argument will be returned with the true value.
       * @return true if keySym is translated into virtual key code, false otherwise.
       */
      bool keySymToVirtualCode(::u32 keySym, ::user::enum_key * peuserkey, bool *extended);
      /**
       * Converts virtual key code to X11 key sym.
       * @param euserkey virtual key code.
       * @param keySym [out] X11 key sym.
       * @return true if virtual key code is translated into keySym, false otherwise.
       */
      bool virtualCodeToKeySym(::u32 *keySym, ::user::enum_key euserkey);

      /**
       * Converts X11 key sym to TCHAR.
       * @param keySym X11 key sym.
       * @param ch [out] char.
       * @return true if keySym is translated into char, false otherwise.
       */
      bool keySymToUnicodeChar(::u32 keySym, int *ch);

      /**
       * Converts char to X11 key sym.
       * @param ch unicode char.
       * @param keySym [out] X11 key sym.
       * @return true if char is translated to key sym, false otherwise.
       */
      bool unicodeCharToKeySym(int ch, ::u32 *keySym);
   };
} // namespace subsystem
