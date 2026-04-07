// Copyright (C) 2012 GlavSoft LLC.
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
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "WindowsProcessCommandLine.h"
#include "WindowsCommandLineArguments.h"

namespace windows
{
   WindowsProcessCommandLine::WindowsProcessCommandLine()
   {
      ::string_array out;

      construct_newø(m_pwindowscommandlinearguments);
      m_pwindowscommandlinearguments->initialize_windows_command_line_arguments(GetCommandLine());

      out = m_pwindowscommandlinearguments->getArguments();
      for (size_t i = 0; i < out.size(); i++) {
         if (out[i][0] != _T('-')) {
            m_strParam.add(out[i]);
         } else {
            optionParser(out[i]);
         }
      }
   }

   void WindowsProcessCommandLine::optionParser(::string & out)
   {
      ::pair<::string, ::string> strPair;

      out.erase((character_count)0, (character_count)1);
      auto ipos = out.find_first_character('=');
      if (::is_null(ipos)) {
         strPair.m_element1 = *out;
         strPair.m_element2= "";
      } else {
         strPair.m_element1 = out.substr(0, ipos);
         strPair.m_element2 = out.substr(ipos + 1);
      }
      strPair.m_element1.make_lower();
      m_strParams.add(strPair);
   }

   size_t WindowsProcessCommandLine::getArgumentsCount()
   {
      return m_strParam.size();
   }

   size_t WindowsProcessCommandLine::getOptionsCount()
   {
      return m_strParams.size();
   }

   bool WindowsProcessCommandLine::findOptionValue(const ::string valName, ::string &  strOut)
   {
      for (size_t i = 0; i < getOptionsCount(); i++) {
         if (m_strParams[i].m_element2 == valName) {
            strOut = m_strParams[i].m_element2;

            return true;
         }
      }
      return false;
   }

   bool WindowsProcessCommandLine::getArgument(size_t index, ::string &  strOut)
   {
      if (index < getArgumentsCount()) {
         strOut = m_strParam[index];

         return true;
      }
      return false;
   }

   bool WindowsProcessCommandLine::getOption(size_t index, ::string &  strOut)
   {
      if (index < getOptionsCount()) {
         strOut = m_strParams[index].m_element1;

         return true;
      }
      return false;
   }

   WindowsProcessCommandLine::~WindowsProcessCommandLine()
   {
      //if (m_wcla) {
        // delete m_wcla;
      //}
   }
} // namespace windows