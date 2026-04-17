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

#pragma once


//#include "remoting/remoting_common/util/winhdr.h"
//#include "acme/_operating_system.h"

////#include "remoting/remoting_common/thread/LocalMutex.h"
#include "acme/prototype/collection/comparable_list.h"
#include "subsystem/particle.h"
//// #include aaa_<list>

namespace subsystem
{
   /**
    * Base Windows Application class.
    * Have hidden main window and main scopedstrMessage loop.
    */
   class OperatingSystemApplicationInterface :
      virtual public ::Particle
   {
   public:


      //int m_iExitCode = 0;
      /**
       * Creates WindowsApplication instance.
       * @param appInstance parameter that passed to WinMain.
       */
      //OperatingSystemApplicationInterface(::hinstance hinstanceApp, const ::scoped_string & scopedstrwindowClassName);

      //OperatingSystemApplication();

      /**
       * Destroys WindowsApplication instance.
       * @remark it does not shutdown application if it's executing it
       * separate thread.
       */
      //virtual ~OperatingSystemApplicationInterface() = 0;

      //virtual void initialize_operating_system_application(::hinstance hinstanceApp, const ::scoped_string & scopedstrwindowClassName) = 0;

      virtual void initialize_operating_system_application() = 0;



      virtual void doDefaultMainLoop() = 0;
      //virtual void initialize_operating_system_application(const ::scoped_string & scopedstrwindowClassName) = 0;

      /**
       * Runs windows application.
       * @remark really it creates main window and starts windows scopedstrMessage loop.
       * @return application exit code.
       */
      virtual void run() = 0;

      /**
       * Posts close and destroy scopedstrMessage to main window.
       */
      virtual void shutdown() = 0;

      /**
       * Posts scopedstrMessage to main window.
       */
      virtual void postMessage(unsigned int scopedstrMessage, ::wparam wParam = 0, ::lparam lParam = 0) = 0;

      /**
       * Adds modeless dialog to application modeless dialog ::list_base to
       * enable switching between controls by pressing tab button.
       * @param dialogWindow HWND of modeless dialog.
       */
      virtual void addModelessDialog(const ::operating_system::window & operatingsystemwindow) = 0;

      /**
       * Removes dialog from application modeless dialog ::list_base.
       * @param dialogWindow HWND of modeless dialog.
       */
      virtual void removeModelessDialog(const ::operating_system::window & operatingsystemwindow) = 0;

      //protected:
      // Creates a window to receive messages.
      //virtual void createWindow(const ::scoped_string & scopedstrClassName) = 0;
      virtual void createApplicationMainTask() = 0;


      //virtual void postMainThreadMessage(int iMainThreadMessage) = 0;

      // Fills the wndClass argument and registers new class name in the Windows.
      //virtual void registerWindowClass(WNDCLASS *wndClass);

      // Runs main messages process cycle. The run() function returns
      // value returned by this function.
      //virtual int processMessages() = 0;

      /**
       * Windows prodecure for main application window.
       */
      //static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

      //HINSTANCE m_appInstance;
      //HWND m_mainWindow;
      //::wstring m_wstrWindowClassName;
      //protected:
      /**
       * Helper method to process modeless dialog scopedstrMessage for modal dialog.
       * @param msg scopedstrMessage to process.
       * @return true if don't need to translate and dispatch scopedstrMessage in main scopedstrMessage loop.
       */
      //static bool processDialogMessage(MSG *msg);
      //private:
      //static LocalMutex m_MDLMutex; // Modeless dialog ::list_base mutex.
      //static ::comparable_list_base<HWND> m_modelessDialogList;


       virtual int getExitCode() = 0;

      /// <summary>
      /// Callback Function
      /// </summary>
      /// <param name="message"></param>
      /// <param name="wparam"></param>
      /// <param name="lparam"></param>
      virtual void onMainThreadMessage(unsigned int message, ::wparam wparam, ::lparam lparam) = 0;


   };


   class CLASS_DECL_SUBSYSTEM OperatingSystemApplicationCallback
       : virtual public Callback<OperatingSystemApplicationInterface>
   {
   public:

      ImplementCallbackø(OperatingSystemApplication, operatingsystemapplication);

   };

    //using OperatingSystemApplicationInterface = particle_interface<OperatingSystemApplicationInterface>;

    /**
    * Base Windows Application class.
    * Have hidden main window and main scopedstrMessage loop.
    */
   class CLASS_DECL_SUBSYSTEM OperatingSystemApplicationComposite :
      virtual public Composite < OperatingSystemApplicationInterface >
   {
   public:


       ImplementCompositeWithCallbackø(OperatingSystemApplication, operatingsystemapplication);

      //int m_iExitCode = 0;
      /**
       * Creates WindowsApplication instance.
       * @param appInstance parameter that passed to WinMain.
       */

      //OperatingSystemApplicationInterface(::hinstance hinstanceApp, const ::scoped_string & scopedstrwindowClassName);

      //OperatingSystemApplication();
      /**
       * Destroys WindowsApplication instance.
       * @remark it does not shutdown application if it's executing it
       * separate thread.
       */
      //~OperatingSystemApplication() override;


      void initialize_operating_system_application() override
      {

          m_poperatingsystemapplication->initialize_operating_system_application();
      }


             void doDefaultMainLoop() { m_poperatingsystemapplication->doDefaultMainLoop(); }



      //void initialize_operating_system_application(
//                                                   const ::scoped_string &scopedstrwindowClassName) override;
      //void initialize_operating_system_application(::hinstance hinstanceApp, const ::scoped_string & scopedstrwindowClassName) override;
      //void initialize_operating_system_application(const ::scoped_string & scopedstrwindowClassName) override;

      /**
       * Runs windows application.
       * @remark really it creates main window and starts windows scopedstrMessage loop.
       * @return application exit code.
       */
      void run() override
      {

         m_poperatingsystemapplication->run();

      }

      /**
       * Posts close and destroy scopedstrMessage to main window.
       */
      void shutdown() override
      {

         m_poperatingsystemapplication->shutdown();

      }

      /**
       * Posts scopedstrMessage to main window.
       */
      void postMessage(unsigned int uMessage, ::wparam wParam = 0, ::lparam lParam = 0) override
      {

         m_poperatingsystemapplication->postMessage(uMessage, wParam, lParam);

      }

      /**
       * Adds modeless dialog to application modeless dialog ::list_base to
       * enable switching between controls by pressing tab button.
       * @param dialogWindow HWND of modeless dialog.
       */
      void addModelessDialog(const ::operating_system::window & operatingsystemwindow) override
      {

         m_poperatingsystemapplication->addModelessDialog(operatingsystemwindow);

      }

      /**
       * Removes dialog from application modeless dialog ::list_base.
       * @param dialogWindow HWND of modeless dialog.
       */
      void removeModelessDialog(const ::operating_system::window & operatingsystemwindow) override
      {

         m_poperatingsystemapplication->removeModelessDialog(operatingsystemwindow);

      }

      //protected:
      // Creates a window to receive messages.
      //void createWindow(const ::scoped_string & scopedstrClassName) override;
      void createApplicationMainTask() override
      {

         m_poperatingsystemapplication->createApplicationMainTask();

      }

      //void postMainThreadMessage(int iMainThreadMessage) override;

      // Fills the wndClass argument and registers new class name in the Windows.
      //virtual void registerWindowClass(WNDCLASS *wndClass);

      // Runs main messages process cycle. The run() function returns
      // value returned by this function.
      //int processMessages() override;

      /**
       * Windows prodecure for main application window.
       */
      //static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

      //HINSTANCE m_appInstance;
      //HWND m_mainWindow;
      //::wstring m_wstrWindowClassName;
      //protected:
      /**
       * Helper method to process modeless dialog scopedstrMessage for modal dialog.
       * @param msg scopedstrMessage to process.
       * @return true if don't need to translate and dispatch scopedstrMessage in main scopedstrMessage loop.
       */
      //static bool processDialogMessage(MSG *msg);
      //private:
      //static LocalMutex m_MDLMutex; // Modeless dialog ::list_base mutex.
      //static ::comparable_list_base<HWND> m_modelessDialogList;

      int getExitCode() override
      {

         return m_poperatingsystemapplication->getExitCode();

      }


      void onMainThreadMessage(unsigned int message, ::wparam wparam, ::lparam lparam) override
      {


      }

   };


    class CLASS_DECL_SUBSYSTEM OperatingSystemApplicationAggregate :
    virtual public Aggregate< OperatingSystemApplicationComposite >
    {
    public:

        ImplementBaseø(OperatingSystemApplication);

    };


   class CLASS_DECL_SUBSYSTEM OperatingSystemApplication :
 virtual public Object < OperatingSystemApplicationAggregate >
   {
   public:

      ImplementObjectø(OperatingSystemApplication)

   };


} // namespace subsystem



