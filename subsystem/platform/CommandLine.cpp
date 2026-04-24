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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "CommandLine.h"

namespace subsystem
{

   CommandLine::CommandLine() {}

   CommandLine::~CommandLine() {}

   bool CommandLine::parse(const CommandLineFormat *format, int formatSize, const CommandLineArguments *cmdArgs)
   {
      ::string_array_base argContainer;
      ::string_array_base::iterator argIter;
      argContainer = cmdArgs->getArgs();

      bool result = true;
      for (argIter = argContainer.begin(); argIter != argContainer.end() && result; argIter++)
      {
         auto pstringKey = &(*argIter);
         if (!_removeKeyPrefix(pstringKey))
         {
            result = false;
            break;
         }

         pstringKey->make_lower();

         result = false;
         for (int i = 0; i < formatSize; i++)
         {
            if (_matchKey(format[i].keyName, pstringKey))
            {
               KeyContainer keyContainer;
               result = true;

               if (format[i].useArg == NEEDS_ARG)
               {
                  argIter++;
                  if (argIter == argContainer.end())
                  {
                     return false;
                  }
                  keyContainer.m_bIsArgument = true;
                  keyContainer.m_strArgument = *argIter;
               }
               keyContainer.m_strKey = format[i].keyName;
               m_foundKeys.add(keyContainer);
            }
         }
      }

      return result;
   }


   bool CommandLine::optionSpecified(const scoped_string &scopedstrKey, string *arg) const
   {
      bool found = false;
      //std::vector<KeyContainer>::const_iterator iter;
      for (auto iter = m_foundKeys.begin(); iter != m_foundKeys.end(); iter++)
      {
         auto foundKey = &(*iter);
         if (foundKey->m_strKey == scopedstrKey)
         {
            found = true;
            if (foundKey->m_bIsArgument && arg != 0)
            {
               *arg = foundKey->m_strArgument;
            }
         }
      }
      return found;
   }

   bool CommandLine::getOption(int index, string *key, string *arg) const
   {
      if (index < 0 || (size_t)index >= m_foundKeys.size())
      {
         return false;
      }

      const KeyContainer *foundKey = &m_foundKeys[(size_t)index];

      *key = foundKey->m_strKey;

      if (foundKey->m_bIsArgument && arg != 0)
      {
         *arg = foundKey->m_strArgument;
      }

      return true;
   }

   bool CommandLine::_matchKey(const char * pszKeyTemplate, string *key)
   {
      return *key == (++pszKeyTemplate);
   }


   bool CommandLine::_removeKeyPrefix(string *key)
   {
      try
      {
         key->erase(0, 1);
         return true;
      }
      catch (...)
      {
         return false;
      }
   }


} // namespace subsystem
 



