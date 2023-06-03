/*
    nanoui/toolbutton.h -- Simple radio+toggle button with an icon

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Button.h"


namespace nanoui
{


/**
 * \class ToolButton toolbutton.h nanoui/toolbutton.h
 *
 * \brief Simple radio+toggle button with an icon.
 */
   class ToolButton : public Button {
   public:
      ToolButton(Widget * parent, int icon,
         const ::scoped_string & caption = "")
         : Button(parent, caption, icon) {
         set_flags(Flags::RadioButton | Flags::ToggleButton);
         set_fixed_size(sequence2_i32(25, 25));
      }
};



} // namespace nanoui


