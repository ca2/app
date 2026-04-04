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
#include "acme/_operating_system.h"
#include "RegistryKey.h"
//#include <vector>

RegistryKey::RegistryKey(HKEY rootKey, const ::scoped_string & scopedstrEntry,
                         bool createIfNotExists, SECURITY_ATTRIBUTES *sa)
{
  initialize(rootKey, scopedstrEntry, createIfNotExists, sa);
}

RegistryKey::RegistryKey(RegistryKey *rootKey, const ::scoped_string & scopedstrEntry,
                         bool createIfNotExists, SECURITY_ATTRIBUTES *sa)
{
  initialize(rootKey->m_key, scopedstrEntry, createIfNotExists, sa);
}

RegistryKey::RegistryKey(HKEY rootKey)
: m_key(rootKey), m_rootKey(rootKey)
{
  m_entry= "";
}

RegistryKey::RegistryKey()
{
}

RegistryKey::~RegistryKey()
{
  close();
}

void RegistryKey::open(HKEY rootKey,
                       const ::scoped_string & scopedstrEntry,
                       bool createIfNotExists,
                       SECURITY_ATTRIBUTES *sa)
{
  initialize(rootKey, scopedstrEntry, createIfNotExists, sa);
}

void RegistryKey::open(RegistryKey *rootKey,
                       const ::scoped_string & scopedstrEntry,
                       bool createIfNotExists,
                       SECURITY_ATTRIBUTES *sa)
{
  initialize(rootKey->m_key, scopedstrEntry, createIfNotExists, sa);
}

HKEY RegistryKey::getHKEY() const
{
  return m_key;
}

bool RegistryKey::createSubKey(const ::scoped_string & scopedstrSubkey)
{
  if (!isOpened()) {
    return false;
  }

  RegistryKey regKey(m_key, scopedstrSubkey);
  return regKey.isOpened();
}

bool RegistryKey::deleteSubKey(const ::scoped_string & scopedstrSubkey)
{
  if (!isOpened()) {
    return false;
  }

  return RegDeleteKey(m_key,::wstring( scopedstrSubkey)) == ERROR_SUCCESS;
}

bool RegistryKey::deleteSubKeyTree(const ::scoped_string & scopedstrSubkey)
{
  if (!isOpened()) {
    return false;
  }

  bool retVal = true;

  // Subkey
  RegistryKey key(this,scopedstrSubkey);

  size_t subkeys2Count = 0;
  ::string_array subkeys2Names;

  //
  // Delete subkeys of subkey
  //

  if (key.getSubKeyNames(subkeys2Names) && subkeys2Names.size() > 0) {
    //::string_array subkeys2Names(subkeys2Count);

    //key.getSubKeyNames(&subkeys2Names[0], NULL);

    // Enumerate subkeys
    for (size_t i = 0; i < subkeys2Names.size(); i++) {
      if (!key.deleteSubKeyTree(subkeys2Names[i])) {
        retVal = false;
      }
    }
  } else {
    retVal = false;
  }

  // Delete subkey
  if (!deleteSubKey(scopedstrSubkey)) {
    retVal = false;
  }

  return retVal;
}

bool RegistryKey::deleteValue(const ::scoped_string & scopedstrName)
{
  if (!isOpened()) {
    return false;
  }

  return RegDeleteValue(m_key, ::wstring(scopedstrName)) == ERROR_SUCCESS;
}

bool RegistryKey::setValueAsInt32(const ::scoped_string & scopedstrName, int value)
{
  if (!isOpened()) {
    return false;
  }

  return RegSetValueEx(m_key, ::wstring(scopedstrName), 0, REG_DWORD, (BYTE *)&value, sizeof(value)) == ERROR_SUCCESS;
}

bool RegistryKey::setValueAsInt64(const ::scoped_string & scopedstrName, long value)
{
  if (!isOpened()) {
    return false;
  }

  return RegSetValueEx(m_key, ::wstring(scopedstrName), 0, REG_QWORD, (BYTE *)&value, sizeof(value)) == ERROR_SUCCESS;
}

bool RegistryKey::setValueAsString(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrPayload)
{
  if (!isOpened()) {
    return false;
  }

   ::wstring wstrPayload(scopedstrPayload);

  size_t origSize = (_tcslen(wstrPayload) + 1) * sizeof(TCHAR);
  DWORD size = (DWORD)origSize;
  _ASSERT(size == origSize);
  return RegSetValueEx(m_key, ::wstring(scopedstrName), 0, REG_SZ, (BYTE *)wstrPayload.c_str(), size) == ERROR_SUCCESS;
}

bool RegistryKey::setValueAsBinary(const ::scoped_string & scopedstrName, const void *value, size_t sizeInBytes)
{
  if (!isOpened()) {
    return false;
  }

  DWORD size = (DWORD)sizeInBytes;
  _ASSERT(size == sizeInBytes);
  return RegSetValueEx(m_key,::wstring( scopedstrName), 0, REG_BINARY, (BYTE *)value, size) == ERROR_SUCCESS;
}

bool RegistryKey::getValueAsInt32(const ::scoped_string & scopedstrName, int *out)
{
  if (!isOpened()) {
    return false;
  }

  DWORD type = REG_DWORD;
  DWORD size = 4;

  return RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, (BYTE *)out, &size) == ERROR_SUCCESS;
}

bool RegistryKey::getValueAsInt64(const ::scoped_string & scopedstrName, long *out)
{
  if (!isOpened()) {
    return false;
  }

  DWORD type = REG_QWORD;
  DWORD size = 8;

  return RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, (BYTE *)out, &size) == ERROR_SUCCESS;
}

bool RegistryKey::getValueAsString(const ::scoped_string & scopedstrName, ::string & out)
{
  if (!isOpened()) {
    return false;
  }

  DWORD type = REG_SZ;
  DWORD size;

  if (RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, NULL, &size) != ERROR_SUCCESS) {
    return false;
  }

  ::array_base<TCHAR> buffer(size + 1);

  if (RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, (BYTE *)&buffer[0], &size) != ERROR_SUCCESS) {
    return false;
  }

  if (buffer[size] != _T('\0')) {
    buffer[size] = _T('\0');
  }

  out = buffer.data();

  return true;
}

bool RegistryKey::getValueAsBinary(const ::scoped_string & scopedstrName, void *value, size_t *sizeInBytes)
{
  if (!isOpened()) {
    return false;
  }

  DWORD type = REG_BINARY;
  DWORD size = (DWORD)*sizeInBytes;

  if (RegQueryValueEx(m_key,wstring( scopedstrName), 0, &type, (LPBYTE)value, &size) != ERROR_SUCCESS) {
    return false;
  }
  *sizeInBytes = (size_t)size;
  return true;
}

bool RegistryKey::getSubKeyNames(::string_array & straKeyNames)
{
  if (!isOpened()) {
    return false;
  }

  DWORD ret = 0;
  DWORD i = 0;

  while (true) {
    ::string keyName;

    ret = enumKey(i, keyName);

    if (ret == ERROR_SUCCESS) {
      //if (subKeyNames != NULL) {
        straKeyNames.ø(i)= keyName;
      //}
      i++;
    } else if (ret == ERROR_NO_MORE_ITEMS) {
      break;
    } else {
      break;
    }
  } // while

  //if (count != NULL) {
    //*count = (size_t)i;
  //}

  return ret == ERROR_NO_MORE_ITEMS;
} // void

bool RegistryKey::isOpened()
{
  return m_key != 0;
}

void RegistryKey::close()
{
  if (isOpened()) {
    if (m_key != m_rootKey) {
      RegCloseKey(m_key);
    }
    m_key = 0;
  }
}

void RegistryKey::initialize(HKEY rootKey, const ::scoped_string & scopedstrEntry, bool createIfNotExists, SECURITY_ATTRIBUTES *sa)
{
  m_rootKey = rootKey;
  m_key = 0;

  m_entry= scopedstrEntry;

  // if (!m_entry.is_empty() && !m_entry.ends(_T('\\'))) {
  //   m_entry.appendString("\\");
  // }

  tryOpenSubKey(m_rootKey, m_entry, &m_key, createIfNotExists, sa);
}

DWORD RegistryKey::enumKey(DWORD i, ::string & name)
{
  DWORD length = 1024;
  DWORD increaseStep = 1024;

  ::array_base<TCHAR> buffer;

  DWORD ret;

  while (true) {
    buffer.resize(length + 1);

    ret = RegEnumKey(m_key, i, buffer.data(), length);

    if (ret == ERROR_SUCCESS) {
      name= buffer.data();
      break;
    } else if (ret == ERROR_MORE_DATA) {
      length += increaseStep;
    } else {
      break;
    }
  } // while

  return ret;
}

bool RegistryKey::tryOpenSubKey(HKEY key, const ::scoped_string & scopedstrSubkey, HKEY *openedKey, bool createIfNotExists, SECURITY_ATTRIBUTES *sa)
{
  if (RegOpenKey(key,::wstring(scopedstrSubkey), openedKey) != ERROR_SUCCESS) {
    if (createIfNotExists) {
      DWORD ret = 0;

      if (sa != 0) {
        DWORD dwDisposition;

        ret = RegCreateKeyEx(key, ::wstring(scopedstrSubkey), 0, (LPTSTR) "", 0,
                             KEY_READ | KEY_WRITE,
                             sa, openedKey, &dwDisposition);
      } else {
        ret = RegCreateKey(key, ::wstring(scopedstrSubkey), openedKey);
      }
      if (ret != ERROR_SUCCESS) {
        return false;
      } // if cannot create key.
    } else {
      return false;
    }
  } // if cannot open key

  return true;
}
