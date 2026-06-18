/*
    nanoui/progressbar.h -- Standard pwidget for visualizing progress

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */

#pragma once


#include "nanoui/Widget.h"


namespace nanoui
{


/**
 * \class ProgressBar progressbar.h nanoui/progressbar.h
 *
 * \brief Standard pwidget for visualizing progress.
 */
   class CLASS_DECL_NANOUI ProgressBar : public Widget {
   public:
      ProgressBar(Widget * parent);

      ::f32 value() { return m_value; }
      void set_value(::f32 value) { m_value = value; }

      virtual i32_size preferred_size(::nano2d::context  * pcontext, bool bRecalcTextSize = true) override;
      virtual void draw(::nano2d::context  * pcontext) override;
   protected:
      ::f32 m_value;
};



} // namespace nanoui


