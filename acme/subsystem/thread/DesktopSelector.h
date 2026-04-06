// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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


#include "acme/subsystem/_common_header.h"
#include "acme/subsystem/_common_header.h"



namespace subsystem
{

    struct desk_t
    {

        union
        {
            void * m_p;
            ::uptr m_u;

        };

    };

   class CLASS_DECL_ACME DesktopSelector :
      virtual public ::subsystem::particle
   {
   public:
      

      DesktopSelector();
      ~DesktopSelector() override;
      // This funtion gets a handle to a desktop that receive user inputs.
      // @return If success the function returns a handle to the desktop.
      // On fail the function returns zero.
      // @remark After use the returned handle must be called the
      // DesktopSelector::closeDesktop() function.
      virtual desk_t getInputDesktop() = 0;

      // This funtion gets a handle to a named desktop by the name.
      // @param: name - pointer to a ::string object that contain a valid
      // desktop name such as "Winlogon".
      // @return if success the function returns a handle to the desktop
      // that receives user inputs. On fail the function returns zero.
      // @remark After use the returned handle must be called the
      // DesktopSelector::closeDesktop() function.
      virtual desk_t getDesktop(const ::scoped_string& name) = 0;

      // This function closes a handle to a desktop.
      // @param hdesk is a handle to a desktop that will be closed.
      // @return If success the function return true else false.
      virtual bool closeDesktop(desk_t hdesk) = 0;

      // This function sets a desktop to a thread from that it was called.
      // @param newDesktop - is a handle to a desktop.
      // @return If success the function return true else false.
      virtual bool setDesktopToCurrentThread(desk_t newDesktop) = 0;

      // This function select a desktop that assigned by name or not to a current
      // thread from that it was called.
      // @param: name - pointer to a ::string object that contain a valid
      // desktop name such as "Winlogon" that will be assigned to the thread. If
      // name is null the input desktop will be assigned.
      // @return If success the function return true else false.
      virtual bool selectDesktop(const ::scoped_string& name = nullptr) = 0;

      // @param desktopName - is a pointer to a ::string object that will be
      // used to store the desktop name. If function has failed then the desktopName
      // object will not change. If the function succeeds, the name of a current
      // input desktop stores in the desktopName object.
      // @return If success the function return true else false.
      virtual ::string getCurrentDesktopName() = 0;

      // @param desktopName - is a pointer to a ::string object that will be
      // used to store the desktop name. If function has failed then the desktopName
      // object will not change. If the function succeeds, the desktop name of the
      // current thread stores in the desktopName object.
      // @return If success the function return true else false.
      virtual ::string getThreadDesktopName() = 0;

      //private:
        // This function gets desktop name by a handle to a desktop.
        // @param desktopName - is a pointer to a ::string object that will be
        // used to store the desktop name. If function has failed then the desktopName
        // object will not change. If the function succeeds, the desktop name
        // stores in the desktopName object.
        // @return If success the function return true else false.
        //static bool getDesktopName(HDESK desktop, ::string & desktopName);
      virtual ::string getDesktopName(desk_t desktop) = 0;


   };


   //
   // class CLASS_DECL_ACME DesktopSelector :
   //     public ::subsystem::composite< DesktopSelectorInterface>
   // {
   // public:
   //
   //
   //    ~DesktopSelector()  override;
   //    // This funtion gets a handle to a desktop that receive user inputs.
   //    // @return If success the function returns a handle to the desktop.
   //    // On fail the function returns zero.
   //    // @remark After use the returned handle must be called the
   //    // DesktopSelector::closeDesktop() function.
   //     desk_t getInputDesktop() override;
   //
   //    // This funtion gets a handle to a named desktop by the name.
   //    // @param: name - pointer to a ::string object that contain a valid
   //    // desktop name such as "Winlogon".
   //    // @return if success the function returns a handle to the desktop
   //    // that receives user inputs. On fail the function returns zero.
   //    // @remark After use the returned handle must be called the
   //    // DesktopSelector::closeDesktop() function.
   //     desk_t getDesktop(const ::scoped_string& name) override;
   //
   //    // This function closes a handle to a desktop.
   //    // @param hdesk is a handle to a desktop that will be closed.
   //    // @return If success the function return true else false.
   //     bool closeDesktop(desk_t hdesk) override;
   //
   //    // This function sets a desktop to a thread from that it was called.
   //    // @param newDesktop - is a handle to a desktop.
   //    // @return If success the function return true else false.
   //     bool setDesktopToCurrentThread(desk_t newDesktop) override;
   //
   //    // This function select a desktop that assigned by name or not to a current
   //    // thread from that it was called.
   //    // @param: name - pointer to a ::string object that contain a valid
   //    // desktop name such as "Winlogon" that will be assigned to the thread. If
   //    // name is null the input desktop will be assigned.
   //    // @return If success the function return true else false.
   //     bool selectDesktop(const ::scoped_string& name = nullptr) override;
   //
   //    // @param desktopName - is a pointer to a ::string object that will be
   //    // used to store the desktop name. If function has failed then the desktopName
   //    // object will not change. If the function succeeds, the name of a current
   //    // input desktop stores in the desktopName object.
   //    // @return If success the function return true else false.
   //     ::string getCurrentDesktopName() override;
   //
   //    // @param desktopName - is a pointer to a ::string object that will be
   //    // used to store the desktop name. If function has failed then the desktopName
   //    // object will not change. If the function succeeds, the desktop name of the
   //    // current thread stores in the desktopName object.
   //    // @return If success the function return true else false.
   //     ::string getThreadDesktopName() override;
   //
   //    //private:
   //      // This function gets desktop name by a handle to a desktop.
   //      // @param desktopName - is a pointer to a ::string object that will be
   //      // used to store the desktop name. If function has failed then the desktopName
   //      // object will not change. If the function succeeds, the desktop name
   //      // stores in the desktopName object.
   //      // @return If success the function return true else false.
   //      //static bool getDesktopName(HDESK desktop, ::string & desktopName) override;
   //     ::string getDesktopName(desk_t desktop) override;
   //
   //
   // } override;


} // namespace subsystem




