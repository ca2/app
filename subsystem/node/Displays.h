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
//#include "subsystem/platform/particle.h"
#include "subsystem/_common_header.h"

//#include "subsystem/platform/::earth::time.h"
//// #include aaa_<vector>
//#include "remoting/remoting/thread/LocalMutex.h"

namespace  subsystem
{
   class DisplaysInterface :
   virtual public ::Particle
   {
   public:
      //Displays();
      //virtual ~DisplaysInterface() =0;

      // If a display does not exist now the function return an empty rectangle.
      virtual void getDisplayCoordinates(unsigned char displayNumber, ::int_rectangle *rect) = 0;

      virtual ::array_base<::int_rectangle> getDisplaysCoords() = 0;

      // Returns a ::array_base that contain dispalys coordinates at the current time.
      virtual ::array_base<::int_rectangle> getDisplays() = 0;

   //private:
      // Updates internal information to a current state.
      virtual void update() = 0;

      // static BOOL CALLBACK monitorEnumProc(HMONITOR hMonitor,
      //                                      HDC hdcMonitor,
      //                                      LPRECT lprcMonitor,
      //                                      LPARAM dwData);

      // Returns true if the update() function has been called lately.
      virtual bool isAlreadyUpdated() = 0;

      // int m_xVirtualScreen;
      // int m_yVirtualScreen;
      //
      // ::array_base<::int_rectangle> m_displayRects;
      // LocalMutex m_displayRectsMutex;
      //
      // static const unsigned int UPDATE_INTERVAL = 3000;
      // class ::time m_latestUpdateTime;
   };

   //using DisplaysInterface = particle_interface<DisplaysInterface>;

   class CLASS_DECL_SUBSYSTEM DisplaysComposite:
virtual public Composite<DisplaysInterface>
   {
   public:


      ImplementCompositeø(Displays, displays)


      //Displays();
       //~Displays() override;

      // If a display does not exist now the function return an empty rectangle.
      void getDisplayCoordinates(unsigned char displayNumber, ::int_rectangle *rect) override
      {

         m_pdisplays->getDisplayCoordinates(displayNumber, rect);

      }

      ::array_base<::int_rectangle> getDisplaysCoords() override
      {

         return m_pdisplays->getDisplaysCoords();
      }

      // Returns a ::array_base that contain dispalys coordinates at the current time.
      ::array_base<::int_rectangle> getDisplays() override
      {

         return m_pdisplays->getDisplays();
      }

   //private:
      // Updates internal information to a current state.
      void update() override
      {

         return m_pdisplays->update();
      }

      // static BOOL CALLBACK monitorEnumProc(HMONITOR hMonitor,
      //                                      HDC hdcMonitor,
      //                                      LPRECT lprcMonitor,
      //                                      LPARAM dwData);

      // Returns true if the update() function has been called lately.
      bool isAlreadyUpdated() override
      {

         return m_pdisplays->isAlreadyUpdated();

      }

      // int m_xVirtualScreen;
      // int m_yVirtualScreen;
      //
      // ::array_base<::int_rectangle> m_displayRects;
      // LocalMutex m_displayRectsMutex;
      //
      // static const unsigned int UPDATE_INTERVAL = 3000;
      // class ::time m_latestUpdateTime;
   };


   class CLASS_DECL_SUBSYSTEM DisplaysAggregate :
 virtual public Aggregate < DisplaysComposite >
   {
   public:

   };

   class CLASS_DECL_SUBSYSTEM Displays :
 virtual public Object < DisplaysAggregate >
   {
   public:

   };



} // namespace  subsystem