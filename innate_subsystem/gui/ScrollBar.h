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


#include "innate_subsystem/gui/Window.h"
// ScrollBar class
// This class doesn't create any window, it only show/hide that is already
// contained in existed window.



namespace innate_subsystem
{

    const int SCROLL_STEP = 5;
   class ScrollBarInterface :
   virtual public ::subsystem::particle_interface<ScrollBarInterface>,
   virtual public Window
   {
   public:
      
      
      // static const int SCROLL_STEP = 5;
      // //HWND m_hwnd;
      // int m_vPos, m_hPos;
      // int m_vMin, m_vMax;
      // int m_hMin, m_hMax;
      // int m_vStep;
      // int m_hStep;
      // bool m_isVirtualScroll;
      // bool m_isVert;
      // bool m_isHorz;
      // bool m_isVVert;
      // bool m_isVHorz;

      //virtual ~ScrollBarInterface() = 0;

      //void setWindow(const ::operating_system::window & operatingsystemwindow)= 0;
      virtual bool showVertScroll(bool show)= 0;
      virtual bool showHorzScroll(bool show)= 0;
      virtual void setHorzRange(int imin, int imax, int istep)= 0;
      virtual void setVertRange(int imin, int imax, int istep)= 0;
      virtual void setVertPos(int iPos)= 0;
      virtual void setHorzPos(int iPos)= 0;
      virtual void moveUpVert(int iPercent = 0)= 0;
      virtual void moveDownVert(int iPercent = 0)= 0;
      virtual void moveLeftHorz(int iPercent = 0)= 0;
      virtual void moveRightHorz(int inPercent = 0)= 0;
      virtual int getVertPos()= 0;
      virtual int getHorzPos()= 0;
      virtual int getVerticalSize()= 0;
      virtual int getHorizontalSize()= 0;

   ///protected:
      virtual void enableVirtualScroll()= 0;
      virtual void disableVirtualScroll()= 0;
      virtual bool _showVertScroll(bool show)= 0;
      virtual bool _showHorzScroll(bool show)= 0;
   };

   class CLASS_DECL_INNATE_SUBSYSTEM ScrollBar :
virtual public ::subsystem::composite<ScrollBarInterface>
   {
   public:
      
      
      // static const int SCROLL_STEP = 5;
      // //HWND m_hwnd;
      // int m_vPos, m_hPos;
      // int m_vMin, m_vMax;
      // int m_hMin, m_hMax;
      // int m_vStep;
      // int m_hStep;
      // bool m_isVirtualScroll;
      // bool m_isVert;
      // bool m_isHorz;
      // bool m_isVVert;
      // bool m_isVHorz;
ScrollBar();
      ~ScrollBar() override;

      //void setWindow(const ::operating_system::window & operatingsystemwindow)override;
      bool showVertScroll(bool show)override;
      bool showHorzScroll(bool show)override;
      void setHorzRange(int imin, int imax, int istep)override;
      void setVertRange(int imin, int imax, int istep)override;
      void setVertPos(int iPos)override;
      void setHorzPos(int iPos)override;
      void moveUpVert(int iPercent = 0)override;
      void moveDownVert(int iPercent = 0)override;
      void moveLeftHorz(int iPercent = 0)override;
      void moveRightHorz(int inPercent = 0)override;
      int getVertPos()override;
      int getHorzPos()override;
      int getVerticalSize()override;
      int getHorizontalSize()override;

      ///protected:
      void enableVirtualScroll()override;
      void disableVirtualScroll()override;
      bool _showVertScroll(bool show)override;
      bool _showHorzScroll(bool show)override;
   };

} // namespace innate_subsystem