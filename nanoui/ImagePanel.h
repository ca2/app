/*
    nanoui/imagepanel.h -- Image panel pwidget which shows a number of
    square-shaped icons

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Widget.h"


namespace nanoui
{


   /**
    * \class ImagePanel imagepanel.h nanoui/imagepanel.h
    *
    * \brief Image panel pwidget which shows a number of square-shaped icons.
    */
   class CLASS_DECL_NANOUI ImagePanel : public Widget
   {
   public:

      typedef ::array<::pair<int, ::string>> Images;
      ::string m_strLoadDirectory;
      bool m_bPendingLoad = false;

      Images m_images;
      ::function<void(::index)> m_callback;
      int m_iThumbSize;
      int m_iSpacing;
      int m_iMargin;
      int m_iMouseIndex;


      ImagePanel(Widget* parent);


      void  load_image_directory(const ::scoped_string& str) { m_strLoadDirectory = str; m_bPendingLoad = true; }

      void set_images(const Images& data) { m_images = data; }
      const Images& images() const { return m_images; }
      ::image* _get_image(::index iImage);

      ::function<void(::index)> callback() const { return m_callback; }
      void set_callback(const ::function<void(::index)>& callback) { m_callback = callback; }

      bool mouse_motion_event(const vector2_i32& p, const vector2_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
      bool mouse_button_event(const vector2_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key& ekeyModifiers) override;
      vector2_i32 preferred_size(::nano2d::context* pcontext, bool bRecalcTextSize = true) override;
      void draw(::nano2d::context* pcontext) override;

      void _defer_load_image_directory(::nano2d::context* pcontext);

      vector2_i32 grid_size() const;
      int index_for_position(const vector2_i32& p) const;
   };



} // namespace nanoui


