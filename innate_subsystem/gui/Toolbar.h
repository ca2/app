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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once

//#include "subsystem/particle.h"


#include "Control.h"
#include "innate_subsystem/_common_header.h"


///#include "util/CommonHeader.h"
///
namespace innate_subsystem
{

          static const int TB_Style_sep = 0;
      static const int TB_Style_gap = 1;

   class ToolbarInterface :
      virtual  public ::Particle
   {
   public:
      //Toolbar();
      //virtual ~ToolbarInterface() = 0;


      /////////////////////////////////////////////////////////
      // Auto mode procedures
      /////////////////////////////////////////////////////////

      // setViewAutoButtons()
      // It used only for auto buttons creation from
      // bitmap and making gaps or separators.
      virtual void setViewAutoButtons(int iButton, int style) = 0;

      // loadToolbarfromRes()
      // This procedure will load a toolbar image from resource
      // id is a number of bitmap. It means that buttons are
      // square(for example 16x16).
      virtual void loadToolbarfromRes(unsigned int id) = 0;


       virtual void loadToolbarFromMatter(const ::file::path & pathMatter) = 0;

      // setButtonsRange()
      // If we want to catch the message from toolbar that some buttons
      // are pressed then we must set a range for message, we pass only
      // first item, and next is id+1 and so on.
      virtual void setButtonsRange(unsigned int id) = 0;

      // attachToolbar()
      // This one will create and attach toolbar window to
      // which handle is passed in hwnd. Only for toolbar from bitmap.
      virtual void attachToolbar(const ::operating_system::window & operatingsystemwindow) = 0;

      /////////////////////////////////////////////////////////
      // Manual mode procedures
      /////////////////////////////////////////////////////////

      // create() creates a windows toolbar. dwStyle is a combination of
      // the toolbar control and button styles. It returns true if successful,
      // or false otherwise.
      virtual bool create(int tbID, const ::operating_system::window & operatingsystemwindowParent,
           unsigned int dwStyle = e_style_child | e_style_visible | e_style_flat_toolbar) = 0;

      // addBitmap() adds one or more images from resources to
      // the list of button images available for a toolbar.
      // Returns the index of the first new image if successful,
      // or -1 otherwise.
      virtual ::lresult addBitmap(int nButtons, unsigned int bitmapID) = 0;

      // addSystemBitmap() adds the system-defined button bitmaps to the list
      // of the toolbar button specifying by stdBitmapID. Returns the index of
      // the first new image if successful, or -1 otherwise.
      virtual ::lresult addSystemBitmap(unsigned int stdBitmapID) = 0;

      // addNButton() adds nButtons buttons to a toolbar.
      virtual bool addNButton(int nButtons, toolbar_button_t * ptoolbarbutton) = 0;

      // addButton() adds one button.
      virtual bool addButton(int iBitmap, int idCommand, unsigned char state = e_toolbar_item_state_enabled,
                     unsigned char style= e_toolbar_item_style_button,  unsigned int dwData=0, int iString=0) = 0;

      // checkButton() checks or unchecks a given button in a toolbar control.
      virtual bool checkButton(int idButton, bool check) = 0;

      // enableButton() enables or disables the specified button
      // in the toolbar.
      virtual bool enableButton(int idButton, bool enable) = 0;

      // pressButton() presses or releases the specified button in the toolbar.
      virtual bool pressButton(int idButton, bool press) = 0;

      // getButtonRect() gets the bounding rectangle of a button in a toolbar.
      virtual bool getButtonRect(int nIndex, ::int_rectangle & buttonRect) = 0;

      // setButtonSize() sets the size of the buttons to be added to a toolbar.
      // Button size must be largen the button bitmap.
      virtual bool setButtonsSize(const ::int_size & size) = 0;

      // autoSize() resizes the toolbar window.
      virtual void autoSize() = 0;

      // getButtonsHeight() retrieves the height of the toolbar buttons.
      virtual int getButtonsHeight() = 0;

      // getButtonsWidth() retrieves the width of the toolbar buttons.
      virtual int getButtonsWidth() = 0;

      // isVisible() check the toolbar window on visible.
      //virtual bool isVisible() = 0;

      // hide() hides the toolbar window.
      //virtual void hide() = 0;

      // show() displays the toolbar window.
      //virtual void show() = 0;

      // getTotalWidth() returns the total size of all buttons and
      // separators in the toolbar.
      virtual int getTotalWidth() = 0;

      // getHeight() returns the toolbar window height.
      virtual int getHeight() = 0;

      // getState() gets button state
      virtual ::lresult getState(int idButton) = 0;

   // private:
   //    int m_initialStr;
   //    int m_numberTB;
   //    unsigned int m_id;
   //    int m_width, m_height;
   //    HWND m_hWndToolbar;
   //
   //    std::map<int, int> m_autoButtons;
   };

   //using ToolbarInterface = particle_interface<ToolbarInterface, ControlInterface>;
   
   class CLASS_DECL_INNATE_SUBSYSTEM ToolbarComposite :
      virtual  public Composite<ToolbarInterface>
   {
   public:


      ImplementCompositeø(Toolbar, toolbar)

      //Toolbar();
      //~Toolbar() override;

      // static const int TB_Style_sep override;
      // static const int TB_Style_gap = 1;

      /////////////////////////////////////////////////////////
      // Auto mode procedures
      /////////////////////////////////////////////////////////

      // setViewAutoButtons()
      // It used only for auto buttons creation from
      // bitmap and making gaps or separators.
      void setViewAutoButtons(int iButton, int style) override { m_ptoolbar->setViewAutoButtons(iButton, style); }

      // loadToolbarfromRes()
      // This procedure will load a toolbar image from resource
      // id is a number of bitmap. It means that buttons are
      // square(for example 16x16).
      void loadToolbarfromRes(unsigned int id) override { m_ptoolbar->loadToolbarfromRes(id); }


    void loadToolbarFromMatter(const ::file::path & pathMatter) override { m_ptoolbar->loadToolbarFromMatter(pathMatter); }

      // setButtonsRange()
      // If we want to catch the message from toolbar that some buttons
      // are pressed then we must set a range for message, we pass only
      // first item, and next is id+1 and so on.
      void setButtonsRange(unsigned int id) override { m_ptoolbar->setButtonsRange(id); }

      // attachToolbar()
      // This one will create and attach toolbar window to
      // which handle is passed in hwnd. Only for toolbar from bitmap.
      void attachToolbar(const ::operating_system::window & operatingsystemwindow) override { m_ptoolbar->attachToolbar(operatingsystemwindow); }

      /////////////////////////////////////////////////////////
      // Manual mode procedures
      /////////////////////////////////////////////////////////

      // create() creates a windows toolbar. dwStyle is a combination of
      // the toolbar control and button styles. It returns true if successful,
      // or false otherwise.
      bool create(int tbID, const ::operating_system::window & operatingsystemwindowParent,
           unsigned int dwStyle = e_style_child | e_style_visible | e_style_flat_toolbar) override { return m_ptoolbar->create(tbID, operatingsystemwindowParent, dwStyle); }

      // addBitmap() adds one or more images from resources to
      // the list of button images available for a toolbar.
      // Returns the index of the first new image if successful,
      // or -1 otherwise.
      ::lresult addBitmap(int nButtons, unsigned int bitmapID) override { return m_ptoolbar->addBitmap(nButtons, bitmapID); }

      // addSystemBitmap() adds the system-defined button bitmaps to the list
      // of the toolbar button specifying by stdBitmapID. Returns the index of
      // the first new image if successful, or -1 otherwise.
      ::lresult addSystemBitmap(unsigned int stdBitmapID) override { return m_ptoolbar->addSystemBitmap(stdBitmapID); }

      // addNButton() adds nButtons buttons to a toolbar.
      bool addNButton(int nButtons, toolbar_button_t * ptoolbarbutton) override { return m_ptoolbar->addNButton(nButtons, ptoolbarbutton); }

      // addButton() adds one button.
      bool addButton(int iBitmap, int idCommand, unsigned char state = e_toolbar_item_state_enabled,
                     unsigned char style= e_toolbar_item_style_button,  unsigned int dwData=0, int iString=0) override { return m_ptoolbar->addButton(iBitmap, idCommand, state, style, dwData, iString); }

      // checkButton() checks or unchecks a given button in a toolbar control.
      bool checkButton(int idButton, bool check) override { return m_ptoolbar->checkButton(idButton, check); }

      // enableButton() enables or disables the specified button
      // in the toolbar.
      bool enableButton(int idButton, bool enable) override { return m_ptoolbar->enableButton(idButton, enable); }

      // pressButton() presses or releases the specified button in the toolbar.
      bool pressButton(int idButton, bool press) override { return m_ptoolbar->pressButton(idButton, press); }

      // getButtonRect() gets the bounding rectangle of a button in a toolbar.
      bool getButtonRect(int nIndex, ::int_rectangle & buttonRect) override { return m_ptoolbar->getButtonRect(nIndex, buttonRect); }

      // setButtonSize() sets the size of the buttons to be added to a toolbar.
      // Button size must be largen the button bitmap.
      bool setButtonsSize(const ::int_size & size) override { return m_ptoolbar->setButtonsSize(size); }

      // autoSize() resizes the toolbar window.
      void autoSize() override { m_ptoolbar->autoSize(); }

      // getButtonsHeight() retrieves the height of the toolbar buttons.
      int getButtonsHeight() override { return m_ptoolbar->getButtonsHeight(); }

      // getButtonsWidth() retrieves the width of the toolbar buttons.
      int getButtonsWidth() override { return m_ptoolbar->getButtonsWidth(); }

      // isVisible() check the toolbar window on visible.
      //bool isVisible() override { return m_ptoolbar->isVisible(); }

      // hide() hides the toolbar window.
      //void hide() override { m_ptoolbar->hide(); }

      // show() displays the toolbar window.
      //void show() override { m_ptoolbar->show(); }

      // getTotalWidth() returns the total size of all buttons and
      // separators in the toolbar.
      int getTotalWidth() override { return m_ptoolbar->getTotalWidth(); }

      // getHeight() returns the toolbar window height.
      int getHeight() override { return m_ptoolbar->getHeight(); }

      // getState() gets button state
      ::lresult getState(int idButton) override { return m_ptoolbar->getState(idButton); }

   // private:
   //    int m_initialStr;
   //    int m_numberTB;
   //    unsigned int m_id;
   //    int m_width, m_height;
   //    HWND m_hWndToolbar;
   //
   //    std::map<int, int> m_autoButtons;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM ToolbarAggregate :
   virtual  public Aggregate< ToolbarComposite, Control >
   {
   public:

   };


   class CLASS_DECL_INNATE_SUBSYSTEM Toolbar :
virtual public Object<ToolbarAggregate>
   {
   public:

      ImplementObjectø(Toolbar)

   };


} // namespace innate_subsystem
