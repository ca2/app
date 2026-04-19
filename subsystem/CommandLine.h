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
#pragma once


#include "subsystem/_common_header.h"
//// #include aaa_<vector>
#include "subsystem/CommandLineArguments.h"
#include "subsystem/KeyContainer.h"
//#include "util/CommonHeader.h"

namespace subsystem
{


   typedef enum UseArgument
   {
      NO_ARG,
      NEEDS_ARG
   };

   struct CommandLineFormat
   {
      const char *keyName;
      UseArgument useArg;
   };

   class CLASS_DECL_SUBSYSTEM CommandLine : virtual public ::particle
   {
   public:
      CommandLine();
      ~CommandLine();

      /**
       * Parse the command line string using the specified format data.
       * This function must be called before calling optionSpecified() or
       * getOption().
       * @param format array of CommandLineFormat structures.
       * @param formatSize count of CommandLineFormat array elements.
       * @param commandLine command line to proccess.
       * @return true on successful parsing, false otherwise.
       */
      bool parse(const CommandLineFormat *format, int formatSize, const CommandLineArguments *cmdArgs);

      /**
       * Check if the option was actually specified in the command line.
       * @param key zero-terminated TCHAR string containing the command line key.
       * @param arg output value for argument of key (optional).
       * @return true if option has been found, false otherwise.
       */
      bool optionSpecified(const scoped_string &scopedstrKey, ::string *arg = nullptr) const;

      /**
       * Gets option with the specified index.
       * @param index index of key.
       * @param key output value for key.
       * @param arg output value for argument of key (optional).
       * @return true if option at the specified index exists, false otherwise.
       */
      bool getOption(int index, ::string *key, ::string *arg = nullptr) const;

   //protected:
      bool _matchKey(const char * pszKeyTemplate, ::string *key);
      bool _removeKeyPrefix(::string *key);

      ::array_base<KeyContainer> m_foundKeys;
   };

//#endif // __COMMANDLINE_H__

} // namespace subsystem
