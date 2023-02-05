/*
    nanoui/ImageImpact.h -- Widget used to display images.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Canvas.h"


NAMESPACE_BEGIN(nanoui)

/**
 * \class ImageImpact ImageImpact.h nanoui/ImageImpact.h
 *
 * \brief A widget for displaying, panning, and zooming images. Numerical RGBA
 * pixel information is shown at large magnifications.
 */
   class NANOUI_EXPORT ImageImpact : public Canvas {
   public:
      using PixelCallback = ::function<void(const Vector2i &, char **, size_t)>;

      /// Initialize the widget
      ImageImpact(Widget * parent);


      // opengl
      /// Return the currently active image
      // Texture * image() { return m_image; }
      ::image * image() { return m_pimage; }
      /// Return the currently active image (const version)
      // opengl
      // const Texture * image() const { return m_image.get(); }
      const ::image * image() const { return m_pimage; }
      /// Set the currently active image
      // opengl
      // void set_image(Texture * image);

      void set_image(::image * pimage);

      /// Center the image on the screen
      void center();

      /// Center the image on the screen and set the scale to 1:1
      void reset();

      /// Set the callback that is used to acquire information about pixel components
      void set_pixel_callback(const PixelCallback & pixel_callback) {
         m_pixel_callback = pixel_callback;
      }
      /// Return the callback that is used to acquire information about pixel components
      const PixelCallback & pixel_callback() const { return m_pixel_callback; }

      /// Return the pixel offset of the zoomed image rectangle
      Vector2f offset() const { return m_offset; }
      /// Set the pixel offset of the zoomed image rectangle
      void set_offset(const Vector2f & offset) { m_offset = offset; }

      /// Return the current magnification of the image
      float scale() const;
      /// Set the current magnification of the image
      void set_scale(float scale);

      /// Convert a position within the widget to a pixel position in the image
      Vector2f pos_to_pixel(const Vector2f & p) const;
      /// Convert a pixel position in the image to a position within the widget
      Vector2f pixel_to_pos(const Vector2f & p) const;

      // Widget implementation
      bool keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key & ekeyModifiers, const ::string & strText) override;
      bool mouse_drag_event(const Vector2i & p, const Vector2i & rel, const ::user::e_key & ekeyModifiers) override;
      bool scroll_event(const Vector2i & p, const Vector2f & rel) override;
      void draw(::nano2d::context * pcontext) override;
      void draw_contents(::nano2d::context * pcontext) override;

   protected:
      // opengl
      //nanoui::ref<Shader> m_image_shader;
      // opengl
      //nanoui::ref<Texture> m_image;
      //::image_pointer m_pimage;
      float m_scale = 0;
      Vector2f m_offset = 0;
      bool m_draw_image_border;
      Color m_image_border_color;
      Color m_image_background_color;
      PixelCallback m_pixel_callback;
};

NAMESPACE_END(nanoui)
