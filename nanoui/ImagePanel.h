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


#include "nanoui/Widget.h"


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

      typedef ::array<::pair<::i32, ::string>> Images;
      ::string m_strLoadDirectory;
      bool m_bPendingLoad = false;

      Images m_images;
      ::function<void(::collection::index)> m_callback;
      ::i32 m_iThumbSize;
      ::i32 m_iSpacing;
      ::i32 m_iMargin;
      ::collection::index m_iMouseIndex;


      ImagePanel(Widget* parent);


      void  load_image_directory(const ::scoped_string& str) { m_strLoadDirectory = str; m_bPendingLoad = true; }

      void set_images(const Images& data) { m_images = data; }
      const Images& images() const { return m_images; }
      ::image::image* _get_image(::collection::index iImage);

      ::function<void(::collection::index)> callback() const { return m_callback; }
      void set_callback(const ::function<void(::collection::index)>& callback) { m_callback = callback; }

      bool mouse_motion_event(const i32_point& p, const i32_size& rel, bool bDown, ::user::e_key_state ekeystate) override;
      bool mouse_button_event(const i32_point & p, ::user::e_key_state ekeystate, bool down, bool bDoubleClick) override;
      i32_size preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize = true) override;
      void draw(::nano2d::context * pcontext) override;

      void _defer_load_image_directory(::nano2d::context * pcontext);

      i32_size grid_size() const;
      
      ::i32 index_for_position(const i32_point& p) const;
      
      
   };


} // namespace nanoui



