// Copyright (C) 2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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

    const ::i32 SCROLL_STEP = 5;
   class ScrollBarInterface :
   virtual public ::Particle
   {
   public:
      
      
      // static const ::i32 SCROLL_STEP = 5;
      // //HWND m_hwnd;
      // ::i32 m_vPos, m_hPos;
      // ::i32 m_vMin, m_vMax;
      // ::i32 m_hMin, m_hMax;
      // ::i32 m_vStep;
      // ::i32 m_hStep;
      // bool m_isVirtualScroll;
      // bool m_isVert;
      // bool m_isHorz;
      // bool m_isVVert;
      // bool m_isVHorz;

      //virtual ~ScrollBarInterface() = 0;

      //void setWindow(const ::operating_system::window & operatingsystemwindow)= 0;
      virtual bool showVertScroll(bool show)= 0;
      virtual bool showHorzScroll(bool show)= 0;
      virtual void setHorzRange(::i32 imin, ::i32 imax, ::i32 istep)= 0;
      virtual void setVertRange(::i32 imin, ::i32 imax, ::i32 istep)= 0;
      virtual void setVertPos(::i32 iPos)= 0;
      virtual void setHorzPos(::i32 iPos)= 0;
      virtual void moveUpVert(::i32 iPercent = 0)= 0;
      virtual void moveDownVert(::i32 iPercent = 0)= 0;
      virtual void moveLeftHorz(::i32 iPercent = 0)= 0;
      virtual void moveRightHorz(::i32 inPercent = 0)= 0;
      virtual ::i32 getVertPos()= 0;
      virtual ::i32 getHorzPos()= 0;
      virtual ::i32 getVerticalSize()= 0;
      virtual ::i32 getHorizontalSize()= 0;

   ///protected:
      virtual void enableVirtualScroll()= 0;
      virtual void disableVirtualScroll()= 0;
      virtual bool _showVertScroll(bool show)= 0;
      virtual bool _showHorzScroll(bool show)= 0;
   };

   //using ScrollBarInterface = particle_interface<ScrollBarInterface, WindowInterface>;
   
   class CLASS_DECL_INNATE_SUBSYSTEM ScrollBarComposite :
      virtual public Composite<ScrollBarInterface>
   {
   public:


      ImplementCompositeø(ScrollBar, scrollbar)
      
      
      // static const ::i32 SCROLL_STEP = 5;
      // //HWND m_hwnd;
      // ::i32 m_vPos, m_hPos;
      // ::i32 m_vMin, m_vMax;
      // ::i32 m_hMin, m_hMax;
      // ::i32 m_vStep;
      // ::i32 m_hStep;
      // bool m_isVirtualScroll;
      // bool m_isVert;
      // bool m_isHorz;
      // bool m_isVVert;
      // bool m_isVHorz;
//ScrollBar();
  ///    ~ScrollBar();

      //void setWindow(const ::operating_system::window & operatingsystemwindow);
      bool showVertScroll(bool show)  override{ return m_pscrollbar->showVertScroll(show); }
      bool showHorzScroll(bool show)  override{ return m_pscrollbar->showHorzScroll(show); }
      void setHorzRange(::i32 imin, ::i32 imax, ::i32 istep)  override{ m_pscrollbar->setHorzRange(imin, imax, istep); }
      void setVertRange(::i32 imin, ::i32 imax, ::i32 istep) override { m_pscrollbar->setVertRange(imin, imax, istep); }
      void setVertPos(::i32 iPos) override { m_pscrollbar->setVertPos(iPos); }
      void setHorzPos(::i32 iPos)  override{ m_pscrollbar->setHorzPos(iPos); }
      void moveUpVert(::i32 iPercent = 0) override { m_pscrollbar->moveUpVert(iPercent); }
      void moveDownVert(::i32 iPercent = 0) override { m_pscrollbar->moveDownVert(iPercent); }
      void moveLeftHorz(::i32 iPercent = 0)  override{ m_pscrollbar->moveLeftHorz(iPercent); }
      void moveRightHorz(::i32 inPercent = 0)  override{ m_pscrollbar->moveRightHorz(inPercent); }
      ::i32 getVertPos() override { return m_pscrollbar->getVertPos(); }
      ::i32 getHorzPos() override { return m_pscrollbar->getHorzPos(); }
      ::i32 getVerticalSize() override { return m_pscrollbar->getVerticalSize(); }
      ::i32 getHorizontalSize() override { return m_pscrollbar->getHorizontalSize(); }

      ///protected:
      void enableVirtualScroll()  override{ m_pscrollbar->enableVirtualScroll(); }
      void disableVirtualScroll() override{ m_pscrollbar->disableVirtualScroll(); }
      bool _showVertScroll(bool show)  override{ return m_pscrollbar->_showVertScroll(show); }
      bool _showHorzScroll(bool show) override { return m_pscrollbar->_showHorzScroll(show); }
   };

   class CLASS_DECL_INNATE_SUBSYSTEM ScrollBarAggregate :
   virtual public Aggregate< ScrollBarComposite, WindowAggregate >

   {
   public:

      ImplementAggregateø(ScrollBar, Window)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM ScrollBar :
virtual public Object<ScrollBarAggregate>
   {
   public:

      ImplementObjectø(ScrollBar)

   };


} // namespace innate_subsystem
