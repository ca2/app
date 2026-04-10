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
#include "acme/subsystem/_common_header.h"
#include "ProcessCommandLine.h"
#include "acme/subsystem/CommandLineArguments.h"

namespace subsystem
{
   
   ProcessCommandLineInterface::ProcessCommandLineInterface()
   {
      // ::string_array out;
      //
      // construct_newø(m_pwindowscommandlinearguments);
      // m_pwindowscommandlinearguments->initialize_windows_command_line_arguments(GetCommandLine());
      //
      // out = m_pwindowscommandlinearguments->getArguments();
      // for (size_t i = 0; i < out.size(); i++) {
      //    if (out[i][0] != _T('-')) {
      //       m_strParam.add(out[i]);
      //    } else {
      //       optionParser(out[i]);
      //    }
      // }
   }



   ProcessCommandLineInterface::~ProcessCommandLineInterface()
      {
         //if (m_wcla) {
         // delete m_wcla;
         //}
      }

   void ProcessCommandLineInterface::initialize_process_command_line()
   {
      // ::string_array out;
      //
      // construct_newø(m_pwindowscommandlinearguments);
      // m_pwindowscommandlinearguments->initialize_windows_command_line_arguments(GetCommandLine());
      //
      // out = m_pwindowscommandlinearguments->getArguments();
      // for (size_t i = 0; i < out.size(); i++) {
      //    if (out[i][0] != _T('-')) {
      //       m_strParam.add(out[i]);
      //    } else {
      //       optionParser(out[i]);
      //    }
      // }
   }


   void ProcessCommandLineInterface::optionParser(::string & out)
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

   ::collection::count ProcessCommandLineInterface::getArgumentsCount()
   {
      return m_strParam.size();
   }

   ::collection::count ProcessCommandLineInterface::getOptionsCount()
   {
      return m_strParams.size();
   }

   bool ProcessCommandLineInterface::findOptionValue(const ::scoped_string & scopedstrOptionName, ::string &  strOut)
   {
      for (::collection::index i = 0; i < getOptionsCount(); i++) {
         if (m_strParams[i].m_element2 == scopedstrOptionName) {
            strOut = m_strParams[i].m_element2;

            return true;
         }
      }
      return false;
   }

   bool ProcessCommandLineInterface::getArgument(::collection::index index, ::string &  strOut)
   {
      if (index < getArgumentsCount()) {
         strOut = m_strParam[index];

         return true;
      }
      return false;
   }

   bool ProcessCommandLineInterface::getOption(::collection::index index, ::string &  strOut)
   {
      if (index < getOptionsCount()) {
         strOut = m_strParams[index].m_element1;

         return true;
      }
      return false;
   }

   ProcessCommandLine::ProcessCommandLine()
   {
//      ::string_array out;
      //
      // construct_newø(m_pwindowscommandlinearguments);
      // m_pwindowscommandlinearguments->initialize_windows_command_line_arguments(GetCommandLine());
      //
      // out = m_pwindowscommandlinearguments->getArguments();
      // for (size_t i = 0; i < out.size(); i++) {
      //    if (out[i][0] != _T('-')) {
      //       m_strParam.add(out[i]);
      //    } else {
      //       optionParser(out[i]);
      //    }
      // }
   }


         ProcessCommandLine::~ProcessCommandLine()
   {
      //if (m_wcla) {
      // delete m_wcla;
      //}
   }


   void ProcessCommandLine::optionParser(::string & out)
   {
      m_pparticleThis->optionParser(out);
      // ::pair<::string, ::string> strPair;
      //
      // out.erase((character_count)0, (character_count)1);
      // auto ipos = out.find_first_character('=');
      // if (::is_null(ipos)) {
      //    strPair.m_element1 = *out;
      //    strPair.m_element2= "";
      // } else {
      //    strPair.m_element1 = out.substr(0, ipos);
      //    strPair.m_element2 = out.substr(ipos + 1);
      // }
      // strPair.m_element1.make_lower();
      // m_strParams.add(strPair);
   }

   ::collection::count ProcessCommandLine::getArgumentsCount()
   {
      //return m_strParam.size();
      return m_pparticleThis->getArgumentsCount();
   }

   ::collection::count ProcessCommandLine::getOptionsCount()
   {

      return m_pparticleThis->getOptionsCount();
      //return m_strParams.size();//
   }

   bool ProcessCommandLine::findOptionValue(const ::scoped_string  &scopedstrOptionName, ::string &  strOut)
   {

      return m_pparticleThis->findOptionValue(scopedstrOptionName, strOut);
      // for (size_t i = 0; i < getOptionsCount(); i++) {
      //    if (m_strParams[i].m_element2 == valName) {
      //       strOut = m_strParams[i].m_element2;
      //
      //       return true;
      //    }
      // }
      // return false;
   }

   bool ProcessCommandLine::getArgument(::collection::index index, ::string &  strOut)
   {

      return m_pparticleThis->getArgument(index, strOut);
      // if (index < getArgumentsCount()) {
      //    strOut = m_strParam[index];
      //
      //    return true;
      // }
      // return false;
   }

   bool ProcessCommandLine::getOption(::collection::index index, ::string &  strOut)
   {

      return m_pparticleThis->getOption(index, strOut);
      // if (index < getOptionsCount()) {
      //    strOut = m_strParams[index].m_element1;
      //
      //    return true;
      // }
      // return false;
   }

} // namespace windows