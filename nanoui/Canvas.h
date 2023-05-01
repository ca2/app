/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/canvas.h
 *
 * \brief Canvas widget for rendering OpenGL content.  This widget was
 *        contributed by Jan Winkler.
 */

#pragma once


#include "Widget.h"


namespace nanoui
{


/**
 * \class GLCanvas canvas.h nanoui/canvas.h
 *
 * \brief Canvas widget for rendering OpenGL/GLES2/Metal content
 *
 * Canvas widget that can be used to display arbitrary OpenGL content. This is
 * useful to display and manipulate 3D objects as part of an interactive
 * application. The implementation uses scissoring to ensure that rendered
 * objects don't spill into neighboring widgets.
 *
 * \rst
 * **Usage**
 *     Override :func:`nanoui::GLCanvas::draw_contents` in subclasses to provide
 *     custom drawing code.  See :ref:`nanoui_example_4`.
 *
 * \endrst
 */
   class CLASS_DECL_NANOUI Canvas : public Widget {
   public:
      /**
       * Creates a memory_new Canvas widget
       *
       * \param parent
       *     The parent widget
       *
       * \param samples
       *     The number of pixel samples (MSAA)
       *
       * \param has_depth_buffer
       *     Should the widget allocate a depth buffer for
       *     the underlying render pass?
       *
       * \param has_stencil_buffer
       *     Should the widget allocate a stencil buffer for
       *     the underlying render pass?
       *
       * \param clear
       *     Should the widget clear its color/depth/stencil buffer?
       */
      Canvas(
         Widget * parent,
         uint8_t samples = 4,
         bool has_depth_buffer = true,
         bool has_stencil_buffer = false,
         bool clear = true
      );

      // opengl
      ///// Return the render pass associated with the canvas object
      //RenderPass * render_pass() { return m_render_pass; }

      /// Specify whether to draw the widget border
      void set_draw_border(const bool draw_border) {
         m_draw_border = draw_border;
      }

      /// Return whether the widget border will be drawn
      bool draw_border() const { return m_draw_border; }

      /// Specify the widget border color
      void set_border_color(const ::color::color & border_color) {
         m_border_color = border_color;
      }

      /// Return whether the widget border is drawn
      const ::color::color & border_color() const { return m_border_color; }

      /// Specify the widget background color
      void set_background_color(const ::color::color & background_color);

      /// Return whether the widget border is drawn
      ::color::color background_color() const;

      /// Draw the widget contents. Override this method.
      virtual void draw_contents(::nano2d::context * pcontext);

      /// Draw the widget
      virtual void draw(::nano2d::context * pcontext) override;

   protected:
      ::color::color     m_colorClear;
      ::image_pointer m_pimage;
      // opengl
//      ref<RenderPass> m_render_pass;
//#if defined(NANOUI_USE_METAL)
//      ref<RenderPass> m_render_pass_resolved;
//#endif
      bool m_draw_border;
      ::color::color m_border_color;
      // opengl
      //bool m_render_to_texture;
};



} // namespace nanoui


