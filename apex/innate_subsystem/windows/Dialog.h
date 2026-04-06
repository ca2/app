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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once
//#define _BASE_DIALOG_H_

#include "acme/subsystem/_common_header.h"
#include "apex/innate_subsystem/Control.h"
//#include "util/StringStorage.h"

namespace innate_subsystem
{


   class BaseDialog :
      virtual public Control
   {
   public:


      BaseDialog();
      BaseDialog(unsigned int resourceId);
      BaseDialog(const char *resourceName);
      ~BaseDialog() override;
//   public:

      virtual void initialize_base_dialog(unsigned int resourceId);
      virtual void initialize_base_dialog(const char *resourceName);

      // Method creates non modal window but not shows it
      virtual void create();

      //
      // Methods creates windows and show it in nonmodal/modal mode
      //

      virtual int show();
      virtual int showModal();

      // Returns true if dialog is already created.
      virtual bool isCreated();

      // Method hides window
      virtual void hide();
      // Method closes dialog
      virtual void closeDialog(int code);
      // Method sets parent window
      virtual void setParent(Control *ctrlParent);
      // Set resource name for dialog
      virtual void setResourceName(const char *resourceName);
      // Set resource id for dialog.
      virtual void setResourceId(unsigned int id);
      // Return
      virtual Control *getControl() { return this; }
      // Setup control by ID
      virtual void subclassControlById(::innate_subsystem::Control * pcontrol, unsigned int id);
      // Icon manipulation
      virtual void loadIcon(unsigned int id);
      virtual void updateIcon();

      // Puts this control foreground and activates it
      virtual bool setForeground();

   //protected:
      /**
       * Sets default push button for dialog.
       * @pararm buttonId new default push button id.
       */
      virtual void setDefaultPushButton(unsigned int buttonId);

   //protected:

      //
      // This methods must be overrided by child classes.
      //

      virtual bool onInitDialog();
      virtual bool onNotify(unsigned int controlID, ::lparam data);
      virtual bool onCommand(unsigned int controlID, unsigned int notificationID);
      virtual bool onClose();
      virtual bool onDestroy();

      //
      // This methods can be overrided by child classes.
      //
//#ifdef WINDOWS
  //    virtual bool onDrawItem(::wparam controlID, LPDRAWITEMSTRUCT dis);
//#endif
      virtual void onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam);

      //
      // Window message proccessing method
      //

      //static INT_PTR CALLBACK dialogProc(HWND hwnd, unsigned int uMsg, ::wparam wparam, ::lparam lparam);

      virtual bool dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam);
   //private:
     virtual char *getResouceName();

   //protected:

     // TCHAR *m_resourceName;        // Name of dialog resource
      //DWORD m_resourceId;            // Id of dialog resouce
      //Control m_ctrlThis;           // This dialog control
      //Control *m_ctrlParent;        // Parent dialog or NULL if no parent

      //bool m_isModal;
      //bool m_isCreated;

      //HICON m_hicon;
   };

   //#endif
} // namespace innate_subsystem