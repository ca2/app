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

#include "apex/innate_subsystem/TextBox.h"
//#include "BalloonTip.h"
#include "apex/innate_subsystem/StringFilter.h"
//#include "util/::string.h"

namespace innate_subsystem
{
   class CLASS_DECL_APEX FilteredTextBoxInterface :
   virtual public TextBox
   {
   public:
      //FilteredTextBox();
      virtual ~FilteredTextBoxInterface() = 0;

      // Override Control::setWindow method
      virtual void setWindow(const ::operating_system::window & operatingsystemwindow) = 0;
      virtual void setText(char *text) = 0;
      //virtual void setErrorBalloonTip(BalloonTip *tip) = 0;
      virtual void setErrorToolTip(TooltipInterface *tip) = 0;
      virtual void setStringFilter(StringFilter *filter) = 0;
      virtual ::lresult makeCheck() = 0;

   // protected:
       virtual bool isStringValid(const char *string) = 0;
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

   class CLASS_DECL_APEX FilteredTextBox :
      virtual public ::subsystem::composite<FilteredTextBoxInterface>
   {
   public:
      FilteredTextBox();
      virtual ~FilteredTextBox() = 0;

      // Override Control::setWindow method
      void setWindow(const ::operating_system::window & operatingsystemwindow) override;
      void setText(char *text) override;
      //void setErrorBalloonTip(BalloonTip *tip) override;
      void setErrorToolTip(TooltipInterface *tip) override;
      void setStringFilter(StringFilter *filter) override;
      ::lresult makeCheck() override;

      // protected:
      bool isStringValid(const char *string) override;
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

   //#endif
} // namespace innate_subsystem


