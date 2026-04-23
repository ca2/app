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
#include "framework.h"
#include "VncPassCrypt.h"
#include "subsystem/_common_header.h"
#include "DesCrypt.h"

const unsigned char VncPassCrypt::m_key[] = { 23, 82, 107, 6, 35, 78, 88, 7 };

VncPassCrypt::VncPassCrypt()
: m_plainPassword(8)
{
}

VncPassCrypt::~VncPassCrypt()
{
  clearPlainPass();
}

void VncPassCrypt::updatePlain(const unsigned char cryptedPass[VNC_PASSWORD_SIZE])
{
  DesCrypt desCrypt;
  desCrypt.decrypt(m_plainPassword.data(), cryptedPass,
                   m_plainPassword.size(), m_key);
}

void VncPassCrypt::getEncryptedPass(unsigned char encryptedPass[VNC_PASSWORD_SIZE],
                                    const unsigned char plainPassword[VNC_PASSWORD_SIZE])
{
  DesCrypt desCrypt;
  desCrypt.encrypt(encryptedPass, plainPassword,
                   VNC_PASSWORD_SIZE, m_key);
}

void VncPassCrypt::getPlainPass(unsigned char plainPassword[VNC_PASSWORD_SIZE],
                                const unsigned char encryptedPass[VNC_PASSWORD_SIZE])
{
  DesCrypt desCrypt;
  desCrypt.decrypt(plainPassword, encryptedPass,
                   VNC_PASSWORD_SIZE, m_key);
}

bool VncPassCrypt::challengeAndResponseIsValid(const unsigned char challenge[16],
                                               const unsigned char response[16])
{
  unsigned char cryptedChallenge[16];
  DesCrypt desCrypt;
  desCrypt.encrypt(cryptedChallenge, challenge,
                   sizeof(cryptedChallenge), m_plainPassword.data());
  if (memcmp(cryptedChallenge, response, sizeof(cryptedChallenge)) == 0) {
    return true;
  } else {
    return false;
  }
}

void VncPassCrypt::clearPlainPass()
{
  memset(m_plainPassword.data(), 0, m_plainPassword.size());
}
