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


   class DialogInterface :
      virtual public ::Particle
   {
   public:


      // Dialog();
      // Dialog(::u32 resourceId);
      // Dialog(const char *resourceName);
      //virtual ~DialogInterface() = 0;
//   public:

      virtual void initialize_dialog(::u32 resourceId) = 0;
      virtual void initialize_dialog(const char *resourceName) = 0;

      // Method creates non modal window but not shows it
      virtual void create() = 0;

      //
      // Methods creates windows and show it in nonmodal/modal mode
      //

      //virtual void show() = 0;
      virtual int showModal() = 0;
      
      virtual void doAttachedModal(const ::function < void(int) > & callback) = 0;

      // Returns true if dialog is already created.
      virtual bool isCreated() = 0;

      // Method hides window
      //virtual void hide() = 0;
      // Method closes dialog
      virtual void closeDialog(int code) = 0;
      // Method sets parent window
      //virtual void setParent(ControlInterface *ctrlParent) = 0;
//      // Set resource name for dialog
//      virtual void setResourceName(const char *resourceName) = 0;
//      // Set resource id for dialog.
//      virtual void setResourceId(::u32 id) = 0;
      // Return
      //virtual ControlInterface *getControl() = 0;
      // Setup control by ID
      //virtual void subclassControlById(::innate_subsystem::ControlInterface * pcontrol, ::u32 id) = 0;
      // Icon manipulation
      //virtual void loadIcon(::u32 id) = 0;
      virtual void updateIcon() = 0;



      // Puts this control foreground and activates it
      virtual bool setForeground() = 0;

   //protected:
      /**
       * Sets default push button for dialog.
       * @pararm buttonId new default push button id.
       */
      virtual void setDefaultPushButton(::u32 buttonId) = 0;

   //protected:

      //
      // This methods must be overrided by child classes.
      //

      virtual bool onInitDialog() = 0;
      //virtual bool onNotify(::u32 controlID, ::lparam data) = 0;
      virtual bool onCommand(::u32 controlID, ::u32 notificationID) = 0;
      virtual bool onClose() = 0;
      virtual bool onDestroy() = 0;

      //virtual bool setChildDoubleClick(::u32 controlID, const ::function < bool() > & callback);
      //virtual bool setChildListViewKeyDown(::u32 controlID, const ::function < bool(int) > & callback);
      //virtual bool setChildListViewKeyDown(::u32 controlID, const ::function < bool(int) > & callback);

      //
      // This methods can be overrided by child classes.
      //
//#ifdef WINDOWS
      virtual bool onDrawItem(::wparam controlID, draw_item_t * pdrawitem) = 0;
//#endif
      virtual void onMessageReceived(::u32 uMsg, ::wparam wparam, ::lparam lparam) = 0;

      //
      // Window message proccessing method
      //

      //static INT_PTR CALLBACK dialogProc(const ::operating_system::window & operatingsystemwindow, ::u32 uMsg, ::wparam wparam, ::lparam lparam) = 0;

      virtual bool dialog_procedure(iptr & iptrResult, ::u32 message, ::wparam wparam, ::lparam lparam) = 0;
   //private:
//     virtual ::string getResouceName() = 0;
//     virtual ::u32 getResouceId() = 0;

   //protected:

     // char *m_resourceName;        // Name of dialog resource
      //::u32 m_resourceId;            // Id of dialog resouce
      //Control m_ctrlThis;           // This dialog control
      //Control *m_ctrlParent;        // Parent dialog or NULL if no parent

      //bool m_isModal;
      //bool m_isCreated;

      //HICON m_hicon;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM DialogCallback : virtual public Callback<DialogInterface>
   {
   public:

      ImplementCallbackø(Dialog, dialog)
   };


//   using DialogInterface = ::particle_interface<DialogInterface, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM DialogComposite :
      virtual public window_composite<DialogInterface>
   {
   public:

      ImplementCompositeWithCallbackø(Dialog, dialog)

//       DialogComposite();
//       // Dialog(::u32 resourceId);
//       // Dialog(const char *resourceName);
//       ~DialogComposite();
// //   public:

      void initialize_dialog(::u32 resourceId) override { m_pdialog->initialize_dialog(resourceId); }
      void initialize_dialog(const char *resourceName) override { m_pdialog->initialize_dialog(resourceName); }

      // Method creates non modal window but not shows it
      void create() override { m_pdialog->create(); }

      //
      // Methods creates windows and show it in nonmodal/modal mode
      //

      //void show() override { m_pdialog->show(); }
      int showModal() override { return m_pdialog->showModal(); }
      
      void doAttachedModal(const ::function < void(int) > & callback)
      {
         
         return m_pdialog->doAttachedModal(callback);
         
      }

      // Returns true if dialog is already created.
      bool isCreated() override { return m_pdialog->isCreated(); }

      // Method hides window
      //void hide() override { m_pdialog->hide(); }
      // Method closes dialog
      void closeDialog(int code) override { m_pdialog->closeDialog(code); }
      // Method sets parent window
      //void setParent(ControlInterface *ctrlParent);
      // Set resource name for dialog
//      void setResourceName(const char *resourceName) override { m_pdialog->setResourceName(resourceName); }
//      // Set resource id for dialog.
//      void setResourceId(::u32 id) override { m_pdialog->setResourceId(id); }
      // Return
      //ControlInterface *getControl();
      // Setup control by ID
      //void subclassControlById(::innate_subsystem::ControlInterface * pcontrol, ::u32 id);
      // Icon manipulation
      //void loadIcon(::u32 id) override { m_pdialog->loadIcon(id); }
      void updateIcon() override { m_pdialog->updateIcon(); }

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
      bool setForeground() override { return m_pdialog->setForeground(); }

   //protected:
      /**
       * Sets default push button for dialog.
       * @pararm buttonId new default push button id.
       */
      void setDefaultPushButton(::u32 buttonId) override { m_pdialog->setDefaultPushButton(buttonId); }

   //protected:

      //
      // This methods must be overrided by child classes.
      //

      bool onInitDialog() override { return m_pdialog->onInitDialog(); }
      //bool onNotify(::u32 controlID, ::lparam data);
      bool onCommand(::u32 controlID, ::u32 notificationID) override
      {
         return m_pdialog->onCommand(controlID, notificationID);
      }
      bool onClose() override { return m_pdialog->onClose(); }
      bool onDestroy() override { return m_pdialog->onDestroy(); }

      //
      // This methods can be overrided by child classes.
      //
//#ifdef WINDOWS
      bool onDrawItem(::wparam controlID, draw_item_t * pdrawitem) override { return m_pdialog->onDrawItem(controlID, pdrawitem); }
//#endif
      void onMessageReceived(::u32 uMsg, ::wparam wparam, ::lparam lparam) override { m_pdialog->onMessageReceived(uMsg, wparam, lparam); }

      //
      // Window message proccessing method
      //

      //static INT_PTR CALLBACK dialogProc(const ::operating_system::window & operatingsystemwindow, ::u32 uMsg, ::wparam wparam, ::lparam lparam);

      bool dialog_procedure(iptr & iptrResult, ::u32 message, ::wparam wparam, ::lparam lparam) override { return m_pdialog->dialog_procedure(iptrResult, message, wparam, lparam); }
   //private:
//      ::string getResouceName() override { return m_pdialog->getResouceName(); }
//      ::u32 getResouceId() override { return m_pdialog->getResouceId(); }

   //protected:

     // char *m_resourceName;        // Name of dialog resource
      //::u32 m_resourceId;            // Id of dialog resouce
      //Control m_ctrlThis;           // This dialog control
      //Control *m_ctrlParent;        // Parent dialog or NULL if no parent

      //bool m_isModal;
      //bool m_isCreated;

      //HICON m_hicon;
   };



   class CLASS_DECL_INNATE_SUBSYSTEM DialogAggregate :
   virtual public Aggregate < DialogComposite, ControlAggregate >
   {
   public:

      ImplementAggregateø(Dialog, Control)

      template<typename WIDGET_TYPE>
      ::pointer<WIDGET_TYPE> &dialog_item(::pointer<WIDGET_TYPE> &pwidget, int iDlgItem)
      {

         constructø(pwidget);

         auto operatingsystemwindow = m_pwindow->dialog_item_operating_system_window(iDlgItem);

         pwidget->set_operating_system_window(operatingsystemwindow);

         return pwidget;
      }

      // template<typename WIDGET_TYPE>
      // composite<WIDGET_TYPE> &dialog_item(composite<WIDGET_TYPE> &widget, int iDlgItem)
      // {
      //
      //    // constructø(pwidget);
      //
      //    auto operatingsystemwindow = m_pwindow->dialog_item_operating_system_window(iDlgItem);
      //
      //    widget.set_operating_system_window(operatingsystemwindow);
      //
      //    return widget;
      // }

      template < typename COMPOSITE, typename BASE_AGGREGATE >
      Aggregate<COMPOSITE, BASE_AGGREGATE> &dialog_item(Aggregate<COMPOSITE, BASE_AGGREGATE> &widget, int iDlgItem)
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


   class CLASS_DECL_INNATE_SUBSYSTEM Dialog :
      virtual public WindowObject<DialogAggregate>
   {
   public:

      ImplementObjectø(Dialog);

   };


   // class CLASS_DECL_INNATE_SUBSYSTEM DialogImplementation1 :
   // virtual public Implementation1<DialogInterface>
   // {
   // public:
   //
   //    ImplementImplementation1ø(Dialog);
   //
   // };




} // namespace innate_subsystem
