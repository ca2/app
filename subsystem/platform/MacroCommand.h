// Copyright (C) 2010,2011,2012 GlavSoft LLC.
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


#include "Command.h"
#include "acme/prototype/collection/list.h"

//#include aaa_<list>

namespace subsystem
{
   /**
    * Command that executes sequence of commands.
    */
   class CLASS_DECL_SUBSYSTEM MacroCommand : public ::subsystem::Command
   {
   public:
      /**
       * Creates macro command with empty command ::list_base.
       */
      MacroCommand();
      /**
       * Destructor, does nothing.
       */
      ~MacroCommand() override;
      /**
       * Executes macro command (sequence of commands that pushed to macro by
       * calling of addCommand() method).
       */
      void onRunCommand() override;

      /**
       * Adds command to the end of ::list_base of commands to execute.
       */
      void addCommand(::subsystem::Command *command);

   private:
      /**
       * List of commands to execute.
       */
      ø<::list_base<::pointer < Command >>> m_listCommand;
   };


} // namespace subsystem


