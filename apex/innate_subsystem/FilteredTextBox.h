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

#ifndef _FILTERED_TEXT_BOX_H_
#define _FILTERED_TEXT_BOX_H_

#include "TextBox.h"
#include "BalloonTip.h"
#include "StringFilter.h"
#include "util/::string.h"

class FilteredTextBox : public TextBox
{
public:
  FilteredTextBox();
  ~FilteredTextBox();

  // Override Control::setWindow method
  void setWindow(const ::operating_system::window & operatingsystemwindow);
  void setText(char *text);
  void setErrorBalloonTip(BalloonTip *tip);
  void setStringFilter(StringFilter *filter);
  LRESULT makeCheck();

protected:
  virtual bool isStringValid(const char *string);
  virtual LRESULT onKeyDown(::wparam code, ::lparam params);

  static LRESULT CALLBACK windowProc(const ::operating_system::window & operatingsystemwindow, unsigned int uMsg, ::wparam wparam, ::lparam lparam);

protected:
  LONG_PTR m_oldWindowProc;
  ::string m_text;
  BalloonTip *m_tip;
  StringFilter *m_filter;
};

#endif
