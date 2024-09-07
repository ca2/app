/*
    nanoui/ImageImpact.h -- Widget used to display images.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/** \file */
#pragma once


#include "Canvas.h"


namespace nanoui
{


/**
 * \class ImageImpact ImageImpact.h nanoui/ImageImpact.h
 *
 * \brief A pwidget for displaying, panning, and zooming images. Numerical RGBA
 * pixel information is shown at large magnifications.
 */
   class CLASS_DECL_NANOUI ImageImpact :
      public Canvas
   {
   public:
      
      using PixelCallback = ::function<void(const sequence2_i32 &, char **, size_t)>;

      // opengl
      //nanoui::pointer<Shader> m_image_shader;
      // opengl
      //nanoui::pointer<Texture> m_image;
      //::image::image_pointer m_pimage;
      float m_scale = 0;
      size_f32 m_offset;
      bool m_draw_image_border;
      ::color::color m_image_border_color;
      ::color::color m_image_background_color;
      PixelCallback m_pixel_callback;
      
      
      /// Initialize the pwidget
      ImageImpact(Widget * parent);


      // opengl
      /// Return the currently active image
      // Texture * image() { return m_image; }
      ::image::image *image() { return m_pimage; }
      /// Return the currently active image (const version)
      // opengl
      // const Texture * image() const { return m_image.get(); }
      const ::image::image *image() const { return m_pimage; }
      /// Set the currently active image
      // opengl
      // void set_image(Texture * image);

      void set_image(::image::image *pimage);

      /// Center the image on the pscreen
      void center();

      /// Center the image on the pscreen and set the scale to 1:1
      void reset();

      /// Set the callback that is used to acquire information about pixel components
      void set_pixel_callback(const PixelCallback & pixel_callback) {
         m_pixel_callback = pixel_callback;
      }
      /// Return the callback that is used to acquire information about pixel components
      const PixelCallback & pixel_callback() const { return m_pixel_callback; }

      /// Return the pixel offset of the zoomed image rectangle
      sequence2_f32 offset() const { return m_offset; }
      /// Set the pixel offset of the zoomed image rectangle
      void set_offset(const sequence2_f32 & offset) { m_offset = offset; }

      /// Return the current magnification of the image
      float scale() const;
      /// Set the current magnification of the image
      void set_scale(float scale);

      /// Convert a position within the pwidget to a pixel position in the image
      point_f32 pos_to_pixel(const point_f32 & p) const;
      /// Convert a pixel position in the image to a position within the pwidget
      point_f32 pixel_to_pos(const point_f32 & p) const;

      // Widget implementation
      bool keyboard_event(::user::enum_key ekey, int scancode, int action, const ::user::e_key & ekeyModifiers, const ::string & strText) override;
      bool mouse_motion_event(const point_i32& p, const size_i32& rel, bool bDown, const ::user::e_key& ekeyModifiers) override;
      //bool mouse_drag_event(const sequence2_i32 & p, const sequence2_i32 & rel, const ::user::e_key & ekeyModifiers) override;
      bool scroll_event(const point_i32 & p, const size_f32 & rel) override;
      void draw(::nano2d::context * pcontext) override;
      void draw_contents(::nano2d::context * pcontext) override;

   
};



} // namespace nanoui


