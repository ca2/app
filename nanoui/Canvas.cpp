/*
    nanoui/canvas.cpp -- Canvas pwidget for rendering full-fledged
    OpenGL content within its designated area. Very useful for
    displaying and manipulating 3D objects or scenes. Subclass it and
    overload `draw_contents` for rendering.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Canvas.h"
#include "Screen.h"
#include "nano2d/context.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction.h"


#define __NANO2D_CONTEXT(ctx) ((::nano2d::context *) (ctx)->p)
//#include <nanoui/pscreen.h>
//#include <nanoui/canvas.h>
//#include <nanoui/texture.h>
//#include <nanoui/renderpass.h>
//#include <nanoui/theme.h>
//#include <nanoui/opengl.h>
//#include "opengl_check.h"

namespace nanoui
{


Canvas::Canvas(Widget * parent, uint8_t samples,
   bool has_depth_buffer, bool has_stencil_buffer,
   bool clear)
   : Widget(parent), m_bDrawBorder(true) {
   m_size = sequence2_i32(250, 250);
   m_border_color = m_ptheme->m_colorBorderLight;

#if defined(NANOUI_USE_GLES)
   samples = 1;
#endif

   Screen * pscreen = screen();

   if (pscreen == nullptr)
   {

      throw std::runtime_error("Canvas::Canvas(): could not find parent pscreen!");

   }

   // opengl
   //m_render_to_texture = samples != 1
   //   || (has_depth_buffer && !pscreen->has_depth_buffer())
   //   || (has_stencil_buffer && !pscreen->has_stencil_buffer());

   //Object * color_texture = nullptr,
     // * depth_texture = nullptr;

   if (has_stencil_buffer && !has_depth_buffer)
      throw std::runtime_error("Canvas::Canvas(): has_stencil implies has_depth!");


//   if (!m_render_to_texture) {
//      color_texture = pscreen;
//      if (has_depth_buffer) {
//#if defined(NANOUI_USE_METAL)
//         depth_texture = pscreen->depth_stencil_texture();
//#else
//         depth_texture = pscreen;
//#endif
//      }
//   }
//   else {
      /*color_texture = memory_new Texture(
         pscreen->pixel_format(),
         pscreen->component_format(),
         m_size,
         Texture::InterpolationMode::Bilinear,
         Texture::InterpolationMode::Bilinear,
         Texture::WrapMode::ClampToEdge,
         samples,
         Texture::TextureFlags::RenderTarget
      );

#if defined(NANOUI_USE_METAL)
      Texture * color_texture_resolved = nullptr;

      if (samples > 1) {
         color_texture_resolved = memory_new Texture(
            pscreen->pixel_format(),
            pscreen->component_format(),
            m_size,
            Texture::InterpolationMode::Bilinear,
            Texture::InterpolationMode::Bilinear,
            Texture::WrapMode::ClampToEdge,
            1,
            Texture::TextureFlags::RenderTarget
         );

         m_render_pass_resolved = memory_new RenderPass(
            { color_texture_resolved }
         );
      }
#endif

      depth_texture = memory_new Texture(
         has_stencil_buffer ? Texture::PixelFormat::DepthStencil
         : Texture::PixelFormat::Depth,
         Texture::ComponentFormat::Float32,
         m_size,
         Texture::InterpolationMode::Bilinear,
         Texture::InterpolationMode::Bilinear,
         Texture::WrapMode::ClampToEdge,
         samples,
         Texture::TextureFlags::RenderTarget
      );
   }

   m_render_pass = memory_new RenderPass(
      { color_texture },
      depth_texture,
      has_stencil_buffer ? depth_texture : nullptr,
#if defined(NANOUI_USE_METAL)
      m_render_pass_resolved,
#else
      nullptr,
#endif
      clear
   );*/
}


void Canvas::set_background_color(const ::color::color & colorBackground) 
{

   m_colorClear = colorBackground;
   //m_render_pass->set_clear_color(0, colorBackground);

}


::color::color Canvas::colorBackground() const {
   //return m_render_pass->clear_color(0);
   return ::color::color(
      m_colorClear.fr(), 
      m_colorClear.fg(), m_colorClear.fb(), m_colorClear.fa());

}

void Canvas::draw_contents(::nano2d::context * pcontext) { /* No-op. */ }

void Canvas::draw(::nano2d::context * pcontext) {
   if (!m_pimage)
   {

      screen()->m_puserinteraction->__construct(m_pimage);

      m_pimage->create({ m_size.cx(), m_size.cy() });


   }

   pcontext->_draw_image((float)m_pos.x(), (float)m_pos.y(), (float)m_size.cx(), (float)m_size.cy(), m_pimage);
//   Screen * pscreen = screen();
//   if (pscreen == nullptr)
//      throw std::runtime_error("Canvas::draw(): could not find parent pscreen!");
//
//   float pixel_ratio = pscreen->pixel_ratio();
//
//   Widget::draw(pcontext);
//
//   pscreen->::nano2d::_flush();
//
//   sequence2_i32 fbsize = m_size;
//   sequence2_i32 offset = absolute_position();
//   if (m_bDrawBorder)
//      fbsize -= 2;
//
//#if defined(NANOUI_USE_OPENGL) || defined(NANOUI_USE_GLES)
//   if (m_render_to_texture)
//      offset = sequence2_i32(offset.x(), pscreen->size().y() - offset.y() - m_size.cy());
//#endif
//
//   if (m_bDrawBorder)
//      offset += sequence2_i32(1, 1);
//
//   fbsize = sequence2_i32(sequence2_f32(fbsize) * pixel_ratio);
//   offset = sequence2_i32(sequence2_f32(offset) * pixel_ratio);
//
//   if (m_render_to_texture) {
//      m_render_pass->resize(fbsize);
//#if defined(NANOUI_USE_METAL)
//      if (m_render_pass_resolved)
//         m_render_pass_resolved->resize(fbsize);
//#endif
//   }
//   else {
//      m_render_pass->resize(pscreen->framebuffer_size());
//      m_render_pass->set_context(offset, fbsize);
//   }
//
//   m_render_pass->begin();
//   draw_contents();
//   m_render_pass->end();
//
//   if (m_bDrawBorder) {
//      pcontext->begin_path();
//      pcontext->stroke_width(1.f);
//      pcontext->stroke_color(m_border_color);
//      ::nano2d::RoundedRect(ctx, m_pos.x() + .5f, m_pos.y() + .5f,
//         m_size.cx() - 1.f, m_size.cy() - 1.f,
//         m_ptheme->m_iWindowCorderRadius);
//      pcontext->stroke();
//   }
//
//   if (m_render_to_texture) {
//      RenderPass * rp = m_render_pass;
//#if defined(NANOUI_USE_METAL)
//      if (m_render_pass_resolved)
//         rp = m_render_pass_resolved;
//#endif
//      rp->blit_to(sequence2_i32(0, 0), fbsize, pscreen, offset);
//   }
}



} // namespace nanoui


