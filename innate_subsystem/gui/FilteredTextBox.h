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

#pragma once
// #ifndef _FILTERED_TEXT_BOX_H_
// #define _FILTERED_TEXT_BOX_H_

#include "innate_subsystem/gui/TextBox.h"
//#include "BalloonTip.h"
#include "innate_subsystem/gui/StringFilter.h"
//#include "util/::string.h"

namespace innate_subsystem
{
   class FilteredTextBoxInterface :
   virtual public ::Particle
   {
   public:
      //FilteredTextBox();
      //virtual ~FilteredTextBoxInterface() = 0;

      // Override Control::setWindow method
      virtual void setWindow(const ::operating_system::window & operatingsystemwindow) = 0;
      virtual void setText(char *text) = 0;
      virtual void setErrorBalloonTip(TooltipInterface *tip) = 0;
      //virtual void setErrorToolTip(TooltipInterface *tip) = 0;
      virtual void setStringFilter(StringFilter *filter) = 0;
      virtual ::lresult makeCheck() = 0;

   // protected:
       virtual bool isStringValid(const char *string) = 0;
       virtual ::lresult onKeyDown(::wparam code, ::lparam params) = 0;
   //
   //    static LRESULT CALLBACK windowProc(const ::operating_system::window & operatingsystemwindow, unsigned int uMsg, ::wparam wparam, ::lparam lparam);
   //
   // protected:
   //    LONG_PTR m_oldWindowProc;
   //    ::string m_text;
   //    BalloonTip *m_tip;
   //    StringFilter *m_filter;
   };

   //using FilteredTextBoxInterface = ::particle_interface<FilteredTextBoxInterface, TextBoxInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM FilteredTextBoxComposite :
      virtual public Composite<FilteredTextBoxInterface>
   {
   public:

      ImplementCompositeø(FilteredTextBox, filteredtextbox)

      // FilteredTextBox();
      // virtual ~FilteredTextBox() = 0;

      // Override Control::setWindow method
      void setWindow(const ::operating_system::window & operatingsystemwindow) override { m_pfilteredtextbox->setWindow(operatingsystemwindow); }
      void setText(char *text) override { m_pfilteredtextbox->setText(text); }
      void setErrorBalloonTip(TooltipInterface *tip) override { m_pfilteredtextbox->setErrorBalloonTip(tip); }
      //void setErrorToolTip(TooltipInterface *tip) override;
      void setStringFilter(StringFilter *filter) override { m_pfilteredtextbox->setStringFilter(filter); }
      ::lresult makeCheck() override { return m_pfilteredtextbox->makeCheck(); }

      // protected:
      bool isStringValid(const char *string) override { return m_pfilteredtextbox->isStringValid(string); }
      //    virtual LRESULT onKeyDown(::wparam code, ::lparam params);
      //
      //    static LRESULT CALLBACK windowProc(const ::operating_system::window & operatingsystemwindow, unsigned int uMsg, ::wparam wparam, ::lparam lparam);
      //
      // protected:
      //    LONG_PTR m_oldWindowProc;
      //    ::string m_text;
      //    BalloonTip *m_tip;
      //    StringFilter *m_filter;
   };

   class CLASS_DECL_INNATE_SUBSYSTEM FilteredTextBoxAggregate :
   virtual public Aggregate< FilteredTextBoxComposite, TextBox >
   {
   public:

      ImplementAggregateø(FilteredTextBox, TextBox)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM FilteredTextBox :
virtual public Object<FilteredTextBoxAggregate>
   {
   public:


   };


} // namespace innate_subsystem


