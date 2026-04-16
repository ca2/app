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
//#include "acme/_operating_system.h"
#include "RegistryKey.h"

//#include "aura/message/user.h"
//// #include aaa_<vector>


namespace subsystem
{


   RegistryKey::RegistryKey(::platform::registry_key_interface *rootKey, ::subsystem::SecurityAttributesInterface * psecurityattributes) :
      m_pregistrykey(rootKey),
      m_pregistrykeyRoot(rootKey)
   {
   }

   
   RegistryKey::RegistryKey(::platform::registry_key_interface *rootKey, const ::scoped_string &scopedstrEntry,
                            //bool createIfNotExists, SECURITY_ATTRIBUTES *sa)
                            bool createIfNotExists, ::subsystem::SecurityAttributesInterface * psecurityattributes)
   {
      
      initialize(rootKey, scopedstrEntry, createIfNotExists, psecurityattributes);

   }


   RegistryKey::RegistryKey(RegistryKey *rootKey, const ::scoped_string & scopedstrEntry,
                            //bool createIfNotExists, SECURITY_ATTRIBUTES *sa)
                            bool createIfNotExists, ::subsystem::SecurityAttributesInterface * psecurityattributes)
   {
      initialize(rootKey->m_pregistrykey, scopedstrEntry, createIfNotExists, psecurityattributes);
   }

   RegistryKey::RegistryKey()
   {
   }

   RegistryKey::~RegistryKey()
   {
      close();
   }

   void RegistryKey::open(::platform::registry_key * rootKey,
                          const ::scoped_string & scopedstrEntry,
                          bool createIfNotExists, ::subsystem::SecurityAttributesInterface * psecurityattributes)//                          SECURITY_ATTRIBUTES *sa)
   {
      initialize(rootKey, scopedstrEntry, createIfNotExists, psecurityattributes);
   }

   void RegistryKey::open(RegistryKey *rootKey,
                          const ::scoped_string & scopedstrEntry,
                          bool createIfNotExists, ::subsystem::SecurityAttributesInterface * psecurityattributes)//                          SECURITY_ATTRIBUTES *sa)
   {
      initialize(rootKey->m_pregistrykey, scopedstrEntry, createIfNotExists, psecurityattributes);
   }

   ::platform::registry_key_interface *RegistryKey::get_registry_key() const
   {
      return m_pregistrykey;
   }

   bool RegistryKey::createSubKey(const ::scoped_string & scopedstrSubkey)
   {
      if (!isOpened()) {
         return false;
      }

      RegistryKey regKey(m_pregistrykey, scopedstrSubkey);
      return regKey.isOpened();
   }

   bool RegistryKey::deleteSubKey(const ::scoped_string & scopedstrSubkey)
   {
      if (!isOpened()) {
         return false;
      }

      try
      {
         m_pregistrykey->m_pregistry->erase_key( scopedstrSubkey);
      }
      catch (...)
      {
         return false;

      }
      return true;
   }

   bool RegistryKey::deleteSubKeyTree(const ::scoped_string & scopedstrSubkey)
   {
      if (!isOpened()) {
         return false;
      }

      // bool retVal = true;
      //
      // // Subkey
      // RegistryKey key(this,scopedstrSubkey);
      //
      // memsize subkeys2Count = 0;
      // ::string_array subkeys2Names;
      //
      // //
      // // Delete subkeys of subkey
      // //
      //
      // if (key.getSubKeyNames(subkeys2Names) && subkeys2Names.size() > 0) {
      //    //::string_array subkeys2Names(subkeys2Count);
      //
      //    //key.getSubKeyNames(&subkeys2Names[0], NULL);
      //
      //    // Enumerate subkeys
      //    for (memsize i = 0; i < subkeys2Names.size(); i++) {
      //       if (!key.deleteSubKeyTree(subkeys2Names[i])) {
      //          retVal = false;
      //       }
      //    }
      // } else {
      //    retVal = false;
      // }
      //
      // // Delete subkey
      // if (!deleteSubKey(scopedstrSubkey)) {
      //    retVal = false;
      // }
      //
      // return retVal;
      return false;
   }

   bool RegistryKey::deleteValue(const ::scoped_string & scopedstrName)
   {
      if (!isOpened()) {
         return false;
      }

      m_pregistrykey->erase_payload(scopedstrName);

      //return RegDeleteValue(m_key, ::wstring(scopedstrName)) == ERROR_SUCCESS;
      return true;
   }

   bool RegistryKey::setValueAsInt32(const ::scoped_string & scopedstrName, int value)
   {
      if (!isOpened()) {
         return false;
      }
      m_pregistrykey->set_dword(scopedstrName, value);
      //return RegSetValueEx(m_key, ::wstring(scopedstrName), 0, REG_DWORD, (BYTE *)&value, sizeof(value)) == ERROR_SUCCESS;
      return true;
   }

   bool RegistryKey::setValueAsInt64(const ::scoped_string & scopedstrName, long long value)
   {
      if (!isOpened()) {
         return false;
      }
      m_pregistrykey->set_qword(scopedstrName, value);
      //return RegSetValueEx(m_key, ::wstring(scopedstrName), 0, REG_QWORD, (BYTE *)&value, sizeof(value)) == ERROR_SUCCESS;
      return true;
   }

   bool RegistryKey::setValueAsString(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrPayload)
   {
      if (!isOpened()) {
         return false;
      }

      //::wstring wstrPayload(scopedstrPayload);

      m_pregistrykey->set_string(scopedstrName, scopedstrPayload);

      // memsize origSize = (_tcslen(wstrPayload) + 1) * sizeof(TCHAR);
      // DWORD size = (DWORD)origSize;
      // _ASSERT(size == origSize);
      // return RegSetValueEx(m_key, ::wstring(scopedstrName), 0, REG_SZ, (BYTE *)wstrPayload.c_str(), size) == ERROR_SUCCESS;
      return true;
   }

   bool RegistryKey::setValueAsBinary(const ::scoped_string & scopedstrName, const void *value, memsize sizeInBytes)
   {
      if (!isOpened()) {
         return false;
      }
      m_pregistrykey->set_binary(scopedstrName, {value, sizeInBytes});
      // DWORD size = (DWORD)sizeInBytes;
      // _ASSERT(size == sizeInBytes);
      // return RegSetValueEx(m_key,::wstring( scopedstrName), 0, REG_BINARY, (BYTE *)value, size) == ERROR_SUCCESS;
      return true;
   }

   bool RegistryKey::getValueAsInt32(const ::scoped_string & scopedstrName, int *out)
   {
      if (!isOpened()) {
         return false;
      }
      unsigned int u;
      auto estatus = m_pregistrykey->_get_dword(scopedstrName, u);

      if (estatus == error_not_found)
      {

         return false;

      }
      else if (!estatus)
      {

         throw ::exception(estatus);

      }
      // DWORD type = REG_DWORD;
      // DWORD size = 4;
      //
      // return RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, (BYTE *)out, &size) == ERROR_SUCCESS;
      return true;
   }

   bool RegistryKey::getValueAsInt64(const ::scoped_string & scopedstrName, long long *out)
   {
      if (!isOpened()) {
         return false;
      }

      //    DWORD type = REG_QWORD;
      //    DWORD size = 8;
      //
      //    return RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, (BYTE *)out, &size) == ERROR_SUCCESS;
      // }
      *out = m_pregistrykey->get_qword(scopedstrName);
      return true;
   }
   bool RegistryKey::getValueAsString(const ::scoped_string & scopedstrName, ::string & out)
   {
      if (!isOpened()) {
         return false;
      }
out = m_pregistrykey->get_string(scopedstrName);
      // DWORD type = REG_SZ;
      // DWORD size;
      //
      // if (RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, NULL, &size) != ERROR_SUCCESS) {
      //    return false;
      // }
      //
      // ::array_base<TCHAR> buffer(size + 1);
      //
      // if (RegQueryValueEx(m_key, ::wstring(scopedstrName), 0, &type, (BYTE *)&buffer[0], &size) != ERROR_SUCCESS) {
      //    return false;
      // }
      //
      // if (buffer[size] != _T('\0')) {
      //    buffer[size] = _T('\0');
      // }
      //
      // out = buffer.data();
      //
      return true;
   }

   bool RegistryKey::getValueAsBinary(const ::scoped_string & scopedstrName, void *value, memsize *sizeInBytes)
   {
      if (!isOpened()) {
         return false;
      }
auto memory =m_pregistrykey->get_binary(scopedstrName);


      auto s = minimum(memory.size(), *sizeInBytes);
      memory.copy_to(value, s);

      *sizeInBytes = s;
      // DWORD type = REG_BINARY;
      // DWORD size = (DWORD)*sizeInBytes;
      //
      // if (RegQueryValueEx(m_key,wstring( scopedstrName), 0, &type, (LPBYTE)value, &size) != ERROR_SUCCESS) {
      //    return false;
      // }
      // *sizeInBytes = (memsize)size;
      return true;
   }

   bool RegistryKey::getSubKeyNames(::string_array & straKeyNames)
   {
      if (!isOpened()) {
         return false;
      }

      // DWORD ret = 0;
      // DWORD i = 0;
      //
      // while (true) {
      //    ::string keyName;
      //
      //    ret = enumKey(i, keyName);
      //
      //    if (ret == ERROR_SUCCESS) {
      //       //if (subKeyNames != NULL) {
      //       straKeyNames.ø(i)= keyName;
      //       //}
      //       i++;
      //    } else if (ret == ERROR_NO_MORE_ITEMS) {
      //       break;
      //    } else {
      //       break;
      //    }
      // } // while
      //
      // //if (count != NULL) {
      // //*count = (memsize)i;
      // //}
      //
      // return ret == ERROR_NO_MORE_ITEMS;
      return false;
   } // void

   bool RegistryKey::isOpened()
   {
      return m_pregistrykey != nullptr;
   }

   void RegistryKey::close()
   {
      if (isOpened()) {
         //if (m_key != m_rootKey) {
           // RegCloseKey(m_key);
         //}
         //m_key = 0;
         ::release(m_pregistrykey);
         ::release(m_pregistrykeyRoot);
      }
   }


   void RegistryKey::initialize(::platform::registry_key_interface *rootKey, const ::scoped_string &scopedstrEntry,
                                bool createIfNotExists, ::subsystem::SecurityAttributesInterface * psecurityattributes) //, SECURITY_ATTRIBUTES *sa)
   {
      m_pregistrykey = rootKey;
      m_pregistrykeyRoot = rootKey;

      m_entry= scopedstrEntry;

      // if (!m_entry.is_empty() && !m_entry.ends(_T('\\'))) {
      //   m_entry.appendString("\\");
      // }

      tryOpenSubKey(m_pregistrykeyRoot, m_entry, m_pregistrykey, createIfNotExists, psecurityattributes);//, sa);
   }

   unsigned int RegistryKey::enumKey(unsigned int i, ::string & name)
   {
      // DWORD length = 1024;
      // DWORD increaseStep = 1024;
      //
      // ::array_base<TCHAR> buffer;
      //
      // DWORD ret;
      //
      // while (true) {
      //    buffer.resize(length + 1);
      //
      //    ret = RegEnumKey(m_key, i, buffer.data(), length);
      //
      //    if (ret == ERROR_SUCCESS) {
      //       name= buffer.data();
      //       break;
      //    } else if (ret == ERROR_MORE_DATA) {
      //       length += increaseStep;
      //    } else {
      //       break;
      //    }
      // } // while
      //
//      return ret;
      return 0;
   }

   bool RegistryKey::tryOpenSubKey(::platform::registry_key_interface *key, const ::scoped_string &scopedstrSubkey,
                                   ::pointer<::platform::registry_key_interface> &openedKey,
                                   bool createIfNotExists, ::subsystem::SecurityAttributesInterface * psecurityattributes) //, SECURITY_ATTRIBUTES *sa)
   {
      // if (RegOpenKey(key,::wstring(scopedstrSubkey), openedKey) != ERROR_SUCCESS) {
      //    if (createIfNotExists) {
      //       DWORD ret = 0;
      //
      //       if (sa != 0) {
      //          DWORD dwDisposition;
      //
      //          ret = RegCreateKeyEx(key, ::wstring(scopedstrSubkey), 0, (LPTSTR) "", 0,
      //                               KEY_READ | KEY_WRITE,
      //                               sa, openedKey, &dwDisposition);
      //       } else {
      //          ret = RegCreateKey(key, ::wstring(scopedstrSubkey), openedKey);
      //       }
      //       if (ret != ERROR_SUCCESS) {
      //          return false;
      //       } // if cannot create key.
      //    } else {
      //       return false;
      //    }
      // } // if cannot open key

      return true;

   }


} // namespace subsystem


