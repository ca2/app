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


//#include "subsystem/inttypes.h"
//#include aaa_<vector>

class CLASS_DECL_REMOTING VncPassCrypt
{
public:

  VncPassCrypt();
  virtual ~VncPassCrypt();

  static const int VNC_PASSWORD_SIZE = 8;

  void updatePlain(const unsigned char cryptedPass[VNC_PASSWORD_SIZE]);

  // Encrypt the plain password and fills by encrypted values the
  // encryptedPass[8] array.
  static void getEncryptedPass(unsigned char encryptedPass[VNC_PASSWORD_SIZE],
                               const unsigned char plainPassword[VNC_PASSWORD_SIZE]);

  // Decrypt the encrypted password and fills by decrypted values the
  // plainPassword[8] array.
  static void getPlainPass(unsigned char plainPassword[VNC_PASSWORD_SIZE],
                                         const unsigned char encryptedPass[VNC_PASSWORD_SIZE]);

  // Returns true if it's matched.
  bool challengeAndResponseIsValid(const unsigned char challenge[16],
                                   const unsigned char response[16]);
  void clearPlainPass();

private:
  static const unsigned char m_key[];
  // The ::array_base uses to protect a password from containing in the stack
  // because the stack available for a public on a bug.
  ::array_base<unsigned char> m_plainPassword;
};

//// __VNCPASSCRYPT_H__
