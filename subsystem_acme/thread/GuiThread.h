// Copyright (C) 2011,2012 GlavSoft LLC.
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


#include "subsystem_acme/thread/Thread.h"

namespace subsystem
{

   class CLASS_DECL_ACME GuiThread: public ::subsystem::Thread
   {
   public:
      GuiThread();
      ~GuiThread() override;
      //private:
      // Replacing the base function.
      //static DWORD WINAPI threadProc(LPVOID pThread);

      //virtual void initByDerived() = 0;

      // Desktop for current thread.
      //HDESK m_hDesk;
   };
   // class CLASS_DECL_ACME GuiThread :
   // virtual public ::subsystem::composite< GuiThread
   // {
   // public:
   //    GuiThread();
   //    ~GuiThread() override;
   // //private:
   //    // Replacing the base function.
   //    //static DWORD WINAPI threadProc(LPVOID pThread);
   //
   //    //void initByDerived() override;
   //
   //    // Desktop for current thread.
   //    //HDESK m_hDesk;
   // };

   //// __GUITHREAD_H__
} // namespace subsystem


