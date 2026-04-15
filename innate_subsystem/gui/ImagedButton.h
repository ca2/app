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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

//#ifndef _IMAGED_BUTTON_H_
//#define _IMAGED_BUTTON_H_

#pragma once

#include "innate_subsystem/gui/Control.h"
//#include "ThemeLib.h"

namespace innate_subsystem
{
    //
    // Owner draw button, that displays button with image and text.
    //

    class ImagedButtonSlice : virtual public ::particle_base
    {
    public:
       /// ImagedButton();
        //virtual ~ImagedButtonInterface() = 0;

        //
        // Draws this ownder-draw button.
        // This method must be called in WM_DRAWITEM message handler of parent control
        //

        //virtual void drawItem(LPDRAWITEMSTRUCT dis);

        virtual void setWindow(const ::operating_system::window & window) =0;

        //virtual void setIcon(::pointer < IconInterface > &icon, const ::int_size & size);
        virtual void setIcon(IconInterface * picon, const ::int_size & size) = 0;

    //private:

        //
        // Parameters:
        //
        // IN buttonRect - button area rectangle
        // IN isButtonPressed - flag that true if button pressed
        // IN textWidth - width of button text that will be drawn in pixels
        // IN textHeight - height of button text that will be drawn in pixels
        // IN imageWidth - width of image in pixels
        // IN imageHeight - height of image in pixels
        // OUT textRect - output text rectangle
        // OUT imageRect - output image rectangle
        //

        virtual void calcRect(::int_rectangle & buttonRect, bool isButtonPressed,
                      unsigned int textWidth, unsigned int textHeight,
                      unsigned int imageWidth, unsigned int imageHeight,
                      ::int_rectangle &textRect, ::int_rectangle & imageRect) = 0;

        //virtual void drawIcon(DeviceContextInterface* dc, const ::int_rectangle & imageRect, bool isPressed, bool isDisabled);
    //protected:
      //  bool m_isUsingTheme;
        //bool m_mouseOver;
        //HTHEME m_theme;

        //
        // Icon to display
        //

        //::pointer < IconInterface > &m_icon;

        //int m_iconWidth;
        //int m_iconHeight;
  //  private:
    //    static LRESULT CALLBACK wndProc(HWND hWnd, unsigned int message, ::wparam wparam, ::lparam lparam);
    };


   using ImagedButtonInterface = particle_interface<ImagedButtonSlice, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM ImagedButtonComposite :

   virtual public composite<ImagedButtonSlice, Control>
   {
   public:

      implement_compositeø(ImagedButton, Control, imagedbutton)

      //ImagedButton();
      //~ImagedButton() override;

      //
      // Draws this ownder-draw button.
      // This method must be called in WM_DRAWITEM message handler of parent control
      //

      //virtual void drawItem(LPDRAWITEMSTRUCT dis);

      virtual void setWindow(const ::operating_system::window & window) { m_pimagedbutton->setWindow(window); }

      //virtual void setIcon(::pointer < IconInterface > &icon, const ::int_size & size);
      virtual void setIcon(IconInterface * picon, const ::int_size & size) { m_pimagedbutton->setIcon(picon, size); }

      //private:

      //
      // Parameters:
      //
      // IN buttonRect - button area rectangle
      // IN isButtonPressed - flag that true if button pressed
      // IN textWidth - width of button text that will be drawn in pixels
      // IN textHeight - height of button text that will be drawn in pixels
      // IN imageWidth - width of image in pixels
      // IN imageHeight - height of image in pixels
      // OUT textRect - output text rectangle
      // OUT imageRect - output image rectangle
      //

      virtual void calcRect(::int_rectangle & buttonRect, bool isButtonPressed,
                    unsigned int textWidth, unsigned int textHeight,
                    unsigned int imageWidth, unsigned int imageHeight,
                    ::int_rectangle &textRect, ::int_rectangle & imageRect) override { m_pimagedbutton->calcRect(buttonRect, isButtonPressed, textWidth, textHeight, imageWidth, imageHeight, textRect, imageRect); }

      //virtual void drawIcon(DeviceContextInterface* dc, const ::int_rectangle & imageRect, bool isPressed, bool isDisabled);
      //protected:
      //  bool m_isUsingTheme;
      //bool m_mouseOver;
      //HTHEME m_theme;

      //
      // Icon to display
      //

      //::pointer < IconInterface > &m_icon;

      //int m_iconWidth;
      //int m_iconHeight;
      //  private:
      //    static LRESULT CALLBACK wndProc(HWND hWnd, unsigned int message, ::wparam wparam, ::lparam lparam);
   };


//#endif
} // namespace innate_subsystem


