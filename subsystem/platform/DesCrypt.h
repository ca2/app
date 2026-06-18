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


//#include "subsystem/platform/inttypes.h"


namespace subsystem
{


   class CLASS_DECL_SUBSYSTEM DesCrypt
   {
   public:
      DesCrypt();
      virtual ~DesCrypt();

      // Encrypt the given buffer.
      // The sizes of both "dst" and "src" must be multiples of 8.
      // Both "dst" and "src" may point to the same buffer.
      void encrypt(::u8 *dst, const ::u8 *src, size_t dataLen, const ::u8 *key);

      // Decrypt the given buffer.
      // The sizes of both "dst" and "src" must be multiples of 8.
      // Both "dst" and "src" may point to the same buffer.
      void decrypt(::u8 *dst, const ::u8 *src, size_t dataLen, const ::u8 *key);

   private:
      enum OperationMode
      {
         ENCRYPT,
         DECRYPT
      };

      void clearKey();

      // Sets the internal key register according to the hexadecimal
      // key contained in the 8 bytes of hexkey, according to the DES,
      // for encryption or decryption according to mode.
      void deskey(const ::u8 hexKey[8], OperationMode mode);

      // Encrypts/Decrypts (according to the key currently loaded in the
      // internal key register) one block of eight bytes at address 'from'
      // into the block at address 'to'.  They can be the same.
      void des(const ::u8 from[8], ::u8 to[8]);

      static void scrunch(const ::u8 *outof, ulong *into);
      static void unscrun(const ulong *outof, ::u8 *into);
      static void desfunc(ulong *block, ulong *keys);
      void cookey(ulong *raw1);
      void usekey(ulong *from);


      ulong m_knL[32];
   };


} // namespace subsystem



