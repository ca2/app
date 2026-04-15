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

#include "acme/filesystem/file/string_buffer.h"
#include "subsystem/_common_header.h"
#include "innate_subsystem/gui/Control.h"
//#include "util/::string.h"

namespace innate_subsystem
{


   class DialogSlice :
      virtual public ::particle_base
   {
   public:


      // Dialog();
      // Dialog(unsigned int resourceId);
      // Dialog(const char *resourceName);
      //virtual ~DialogInterface() = 0;
//   public:

      virtual void initialize_dialog(unsigned int resourceId) = 0;
      virtual void initialize_dialog(const char *resourceName) = 0;

      // Method creates non modal window but not shows it
      virtual void create() = 0;

      //
      // Methods creates windows and show it in nonmodal/modal mode
      //

      virtual void show() = 0;
      virtual int showModal() = 0;

      // Returns true if dialog is already created.
      virtual bool isCreated() = 0;

      // Method hides window
      virtual void hide() = 0;
      // Method closes dialog
      virtual void closeDialog(int code) = 0;
      // Method sets parent window
      //virtual void setParent(ControlInterface *ctrlParent) = 0;
      // Set resource name for dialog
      virtual void setResourceName(const char *resourceName) = 0;
      // Set resource id for dialog.
      virtual void setResourceId(unsigned int id) = 0;
      // Return
      //virtual ControlInterface *getControl() = 0;
      // Setup control by ID
      //virtual void subclassControlById(::innate_subsystem::ControlInterface * pcontrol, unsigned int id) = 0;
      // Icon manipulation
      virtual void loadIcon(unsigned int id) = 0;
      virtual void updateIcon() = 0;



      // Puts this control foreground and activates it
      virtual bool setForeground() = 0;

   //protected:
      /**
       * Sets default push button for dialog.
       * @pararm buttonId new default push button id.
       */
      virtual void setDefaultPushButton(unsigned int buttonId) = 0;

   //protected:

      //
      // This methods must be overrided by child classes.
      //

      virtual bool onInitDialog() = 0;
      //virtual bool onNotify(unsigned int controlID, ::lparam data) = 0;
      virtual bool onCommand(unsigned int controlID, unsigned int notificationID) = 0;
      virtual bool onClose() = 0;
      virtual bool onDestroy() = 0;

      //virtual bool setChildDoubleClick(unsigned int controlID, const ::function < bool() > & callback);
      //virtual bool setChildListViewKeyDown(unsigned int controlID, const ::function < bool(int) > & callback);
      //virtual bool setChildListViewKeyDown(unsigned int controlID, const ::function < bool(int) > & callback);

      //
      // This methods can be overrided by child classes.
      //
//#ifdef WINDOWS
      virtual bool onDrawItem(::wparam controlID, draw_item_t * pdrawitem) = 0;
//#endif
      virtual void onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam) = 0;

      //
      // Window message proccessing method
      //

      //static INT_PTR CALLBACK dialogProc(const ::operating_system::window & operatingsystemwindow, unsigned int uMsg, ::wparam wparam, ::lparam lparam) = 0;

      virtual bool dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam) = 0;
   //private:
     virtual char *getResouceName() = 0;

   //protected:

     // char *m_resourceName;        // Name of dialog resource
      //unsigned int m_resourceId;            // Id of dialog resouce
      //Control m_ctrlThis;           // This dialog control
      //Control *m_ctrlParent;        // Parent dialog or NULL if no parent

      //bool m_isModal;
      //bool m_isCreated;

      //HICON m_hicon;
   };


   using DialogInterface = ::particle_interface<DialogSlice, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM DialogComposite :
      virtual public window_composite<DialogSlice, Control>
   {
   public:

      implement_compositeø(Dialog, Control, dialog)

//       DialogComposite();
//       // Dialog(unsigned int resourceId);
//       // Dialog(const char *resourceName);
//       ~DialogComposite();
// //   public:

      virtual void initialize_dialog(unsigned int resourceId) { m_pdialog->initialize_dialog(resourceId); }
      virtual void initialize_dialog(const char *resourceName) { m_pdialog->initialize_dialog(resourceName); }

      // Method creates non modal window but not shows it
      virtual void create() { m_pdialog->create(); }

      //
      // Methods creates windows and show it in nonmodal/modal mode
      //

      virtual void show() { m_pdialog->show(); }
      virtual int showModal() { return m_pdialog->showModal(); }

      // Returns true if dialog is already created.
      virtual bool isCreated() { return m_pdialog->isCreated(); }

      // Method hides window
      virtual void hide() { m_pdialog->hide(); }
      // Method closes dialog
      virtual void closeDialog(int code) { m_pdialog->closeDialog(code); }
      // Method sets parent window
      //virtual void setParent(ControlInterface *ctrlParent);
      // Set resource name for dialog
      virtual void setResourceName(const char *resourceName) { m_pdialog->setResourceName(resourceName); }
      // Set resource id for dialog.
      virtual void setResourceId(unsigned int id) { m_pdialog->setResourceId(id); }
      // Return
      //virtual ControlInterface *getControl();
      // Setup control by ID
      //virtual void subclassControlById(::innate_subsystem::ControlInterface * pcontrol, unsigned int id);
      // Icon manipulation
      virtual void loadIcon(unsigned int id) { m_pdialog->loadIcon(id); }
      virtual void updateIcon() { m_pdialog->updateIcon(); }

      //template<typename WIDGET_TYPE>
      //::pointer<WIDGET_TYPE> &dialog_item(::pointer<WIDGET_TYPE> &pwidget, int iDlgItem)
      //{

      //   return m_pdialog->dialog_item(pwidget, iDlgItem);

      //}

      //template<typename WIDGET_TYPE>
      //composite<WIDGET_TYPE> &dialog_item(composite<WIDGET_TYPE> &widget, int iDlgItem)
      //{

      //   // constructø(pwidget);

      //   return m_pdialog->dialog_item(widget, iDlgItem);

      //}

      //template<typename WIDGET_TYPE = ::innate_subsystem::Control>
      //::pointer<WIDGET_TYPE> dialog_item(int iDlgItem)
      //{

      //   return m_pdialog->dialog_item<WIDGET_TYPE>(iDlgItem);

      //}

      // template < typename WIDGET_TYPE >
      // ::pointer < WIDGET_TYPE > & dialog_item(::pointer < WIDGET_TYPE > & pwidget, int iDlgItem)
      // {
      //
      //    constructø(pwidget);
      //
      //    auto operatingsystemwindow = dialog_item_operating_system_window(iDlgItem);
      //
      //    pwidget->set_operating_system_window(operatingsystemwindow);
      //
      //    return pwidget;
      //
      //
      // }
      //
      // template < typename WIDGET_TYPE  = ::innate_subsystem::Control>
      // ::pointer < WIDGET_TYPE > dialog_item(int iDlgItem)
      // {
      //
      //    ::pointer < WIDGET_TYPE> pwidget;
      //
      //    dialog_item(pwidget, iDlgItem);
      //
      //    return pwidget;
      //
      //
      // }



      // Puts this control foreground and activates it
      virtual bool setForeground() { return m_pdialog->setForeground(); }

   //protected:
      /**
       * Sets default push button for dialog.
       * @pararm buttonId new default push button id.
       */
      virtual void setDefaultPushButton(unsigned int buttonId) { m_pdialog->setDefaultPushButton(buttonId); }

   //protected:

      //
      // This methods must be overrided by child classes.
      //

      virtual bool onInitDialog() { return m_pdialog->onInitDialog(); }
      //virtual bool onNotify(unsigned int controlID, ::lparam data);
      virtual bool onCommand(unsigned int controlID, unsigned int notificationID) { return m_pdialog->onCommand(controlID, notificationID); }
      virtual bool onClose() { return m_pdialog->onClose(); }
      virtual bool onDestroy() { return m_pdialog->onDestroy(); }

      //
      // This methods can be overrided by child classes.
      //
//#ifdef WINDOWS
      virtual bool onDrawItem(::wparam controlID, draw_item_t * pdrawitem) { return m_pdialog->onDrawItem(controlID, pdrawitem); }
//#endif
      virtual void onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam) { m_pdialog->onMessageReceived(uMsg, wparam, lparam); }

      //
      // Window message proccessing method
      //

      //static INT_PTR CALLBACK dialogProc(const ::operating_system::window & operatingsystemwindow, unsigned int uMsg, ::wparam wparam, ::lparam lparam);

      virtual bool dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam) { return m_pdialog->dialog_procedure(iptrResult, message, wparam, lparam); }
   //private:
      virtual char *getResouceName() { return m_pdialog->getResouceName(); }

   //protected:

     // char *m_resourceName;        // Name of dialog resource
      //unsigned int m_resourceId;            // Id of dialog resouce
      //Control m_ctrlThis;           // This dialog control
      //Control *m_ctrlParent;        // Parent dialog or NULL if no parent

      //bool m_isModal;
      //bool m_isCreated;

      //HICON m_hicon;
   };



   class CLASS_DECL_INNATE_SUBSYSTEM Dialog : virtual public DialogComposite,
                                              virtual public Control
   {
   public:


      template<typename WIDGET_TYPE>
      ::pointer<WIDGET_TYPE> &dialog_item(::pointer<WIDGET_TYPE> &pwidget, int iDlgItem)
      {

         constructø(pwidget);

         auto operatingsystemwindow = m_pwindow->dialog_item_operating_system_window(iDlgItem);

         pwidget->set_operating_system_window(operatingsystemwindow);

         return pwidget;
      }

      template<typename WIDGET_TYPE>
      composite<WIDGET_TYPE> &dialog_item(composite<WIDGET_TYPE> &widget, int iDlgItem)
      {

         // constructø(pwidget);

         auto operatingsystemwindow = m_pwindow->dialog_item_operating_system_window(iDlgItem);

         widget.set_operating_system_window(operatingsystemwindow);

         return widget;
      }

      template<typename WIDGET_TYPE = ::innate_subsystem::Control>
      ::pointer<WIDGET_TYPE> dialog_item(int iDlgItem)
      {

         ::pointer<WIDGET_TYPE> pwidget;

         dialog_item(pwidget, iDlgItem);

         return pwidget;
      }

   };


   //#endif
} // namespace innate_subsystem
