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
#include "Sockets.h"
#include "subsystem/Exception.h"


namespace subsystem
{
   Sockets::Sockets()
   {
      m_bIsStarted = false;
   }


   Sockets::~Sockets()
   {

      if (m_bIsStarted)
      {

            cleanup();
      }


   }



   void Sockets::startup(int loVer, int hiVer)
   {
      if (m_bIsStarted) {
         throw ::subsystem::Exception("Sockets already initialized.");
      }

      m_bIsStarted = true;

      try
      {
         _startup(loVer, hiVer);
      }
      catch (...)
      {

         m_bIsStarted = false;

      }

   }

   void Sockets::_startup(int loVer, int hiVer)
   {


      
   }

   void Sockets::cleanup()
   {
      if (!m_bIsStarted) {
         throw ::subsystem::Exception("Sockets don't initialized.");
      }

      m_bIsStarted = false;

      _cleanup();

      // if (WSACleanup() == SOCKET_ERROR) {
      //    throw ::subsystem::Exception("Failed to deinitialize Sockets.");
      // }
   }


   void Sockets::_cleanup()
   {



   }

} // namespace subsystem_bsd_sockets