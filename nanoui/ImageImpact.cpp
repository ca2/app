/*
    nanoui/ImageImpact.cpp -- Widget used to display images.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ImageImpact.h"
#include "Screen.h"
#include "nano2d/context.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "aura/graphics/image/image.h"


#define __NANO2D_CONTEXT(ctx) ((::nano2d::context  *) (ctx)->p)


//#include <nanoui/renderpass.h>
//#include <nanoui/shader.h>
//#include <nanoui/texture.h>
//#include <nanoui/pscreen.h>
//#include <nanoui/opengl.h>
//#include <nanoui_resources.h>

namespace nanoui
{


ImageImpact::ImageImpact(Widget * parent) : Canvas(parent, 1, false, false, false) {
   //render_pass()->set_clear_color(0, Color(0.3f, 0.3f, 0.32f, 1.f));

   //m_image_shader = ___new Shader(
   //   render_pass(),
   //   /* An identifying name */
   //   "a_simple_shader",
   //   NANOUI_SHADER("ImageImpact_vertex"),
   //   NANOUI_SHADER("ImageImpact_fragment"),
   //   Shader::BlendMode::AlphaBlend
   //);

   //const float positions[] = {
   //    0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
   //    1.f, 0.f, 1.f, 1.f, 0.f, 1.f
   //};

   //m_image_shader->set_buffer("position", VariableType::Float32, { 6, 2 },
   //   positions);
   //m_render_pass->set_cull_mode(RenderPass::CullMode::Disabled);

   m_image_border_color = m_ptheme->m_colorBorderDark;
   m_draw_image_border = true;
   m_image_background_color = ::color::transparent;
}

// opengl
//void ImageImpact::set_image(Texture * image) {
//   if (image->mag_interpolation_mode() != Texture::InterpolationMode::Nearest)
//      throw std::runtime_error(
//         "ImageImpact::set_image(): interpolation mode must be set to 'Nearest'!");
//   m_image_shader->set_texture("image", image);
//   m_image = image;
//}

void ImageImpact::set_image(::image::image *pimage) {
   m_pimage = pimage;
}


float ImageImpact::scale() const
{
   
   return ::pow(2.f, m_scale / 5.f);
   
}


void ImageImpact::set_scale(float scale) 
{

   m_scale = ::log2(scale) * 5.f;

}


void ImageImpact::center() 
{

   if (!m_pimage)
   {

      return;

   }

   m_offset = m_size * .5f * screen()->pixel_ratio() - m_pimage->size() * scale();

}


void ImageImpact::reset() 
{

   m_scale = 0.f;

   center();

}


float_point ImageImpact::pos_to_pixel(const float_point & p) const
{

   auto p2 = p;

   if (m_bDrawBorder)
   {

      p2 -= ::float_size(1.f, 1.f);

   }

   return (p2 * screen()->pixel_ratio() - m_offset) / scale();

}


float_point ImageImpact::pixel_to_pos(const float_point & p) const
{

   auto pos = (p * scale() + m_offset) / screen()->pixel_ratio();

   if (m_bDrawBorder)
   {

      pos += ::float_size(1.f, 1.f);

   }

   return pos;

}


bool ImageImpact::keyboard_event(::user::enum_key ekey, int /* scancode */, int action, const ::user::e_key & /* ekeyModifiers */, const ::scoped_string & scopedstrText) 
{

   if (!m_bEnabled || !m_pimage)
   {

      return false;

   }

   if (action == ::user::e_message_key_down)
   {
      
      if (ekey == ::user::e_key_r) 
      {
         
         reset();

         return true;

      }

   }
   
   return false;

}


bool ImageImpact::mouse_motion_event(const int_point & /* p */, const int_size & rel, bool bDown, const ::user::e_key & /* modifiers */)
{

   if (!m_bEnabled || !m_pimage || !bDown)
   {

      return false;

   }

   m_offset.cx += (float)rel.cx * screen()->pixel_ratio();

   m_offset.cy += (float)rel.cy * screen()->pixel_ratio();

   return true;

}


bool ImageImpact::scroll_event(const int_point & p, const float_size & rel) 
{

   if (!m_bEnabled || !m_pimage)
   {

      return false;

   }

   float_sequence2 p1 = pos_to_pixel(p - m_pos);
   m_scale += rel.cy;

   // Restrict scaling to a reasonable range
   m_scale = maximum(
      m_scale, minimum(0.f, ::log2(40.f / maximum(m_pimage->width(),
         m_pimage->height())) * 5.f));
   m_scale = ::minimum(m_scale, 45.f);

   float_sequence2 p2 = pos_to_pixel(p - m_pos);
   m_offset += (p2 - p1) * scale();
   return true;

}


void ImageImpact::draw(::nano2d::context  * pcontext) 
{

   //if (!m_bEnabled || !m_pimage)
     // return;


   pcontext->_draw_image((float) m_pos.x, (float)m_pos.y, (float)m_size.cx, (float)m_size.cy, m_pimage);

   //Canvas::draw(pcontext);

   //int_sequence2 top_left = int_sequence2(pixel_to_pos(float_sequence2(0.f, 0.f))),
   //   size = int_sequence2(pixel_to_pos(float_sequence2(m_pimage->width(), m_pimage->height())) - float_sequence2(top_left));

   //if (m_draw_image_border) {
   //   pcontext->begin_path();
   //   pcontext->stroke_width(1.f);
   //   pcontext->stroke_color(m_image_border_color);
   //   pcontext->rectangle(m_pos.x - .5f + top_left.x,
   //      m_pos.y - .5f + top_left.y,
   //      size.cx + 1.f, size.cy + 1.f);
   //   pcontext->stroke();
   //}

   //pcontext->save();
   //::nano2d::IntersectScissor(ctx, m_pos.x, m_pos.y, m_size.cx, m_size.cy);

   //if (scale() > 100 && m_pixel_callback) {
   //   float font_size = scale() / 10.f;
   //   float alpha = ::minimum(1.f, (scale() - 100) / 100.f);
   //   pcontext->font_size(font_size);
   //   pcontext->font_face("sans-bold");
   //   pcontext->text_align(::nano2d::e_align_center | ::nano2d::e_align_middle);

   //   int_sequence2 start = max(int_sequence2(0), int_sequence2(pos_to_pixel(float_sequence2(0.f, 0.f))) - 1),
   //      end = ::nanoui::min(int_sequence2(pos_to_pixel(float_sequence2(m_size))) + int_sequence2(1, 1), int_sequence2(m_pimage->width(), m_pimage->height()) + int_sequence2(-1, -1));

   //   char text_buf[80],
   //      * text[4] = { text_buf, text_buf + 20, text_buf + 40, text_buf + 60 };

   //   for (int y = start.y; y <= end.y; ++y) {
   //      for (int x = start.x; x <= end.x; ++x) {
   //         int_sequence2 pos = int_sequence2(pixel_to_pos(float_sequence2(x + .5f, y + .5f)));

   //         m_pixel_callback(int_sequence2(x, y), text, 20);

   //         for (int ch = 0; ch < 4; ++ch) {
   //            Color col(0.f, 0.f, 0.f, alpha);
   //            pcontext->fill_color(col);
   //            ::nano2d::FontBlur(ctx, 2);
   //            float xpos = m_pos.x + pos.x,
   //               ypos = m_pos.y + pos.y + (ch - 1.5f) * font_size;
   //            pcontext->text(xpos, ypos, text[ch], nullptr);
   //            col = Color(0.3f, 0.3f, 0.3f, alpha);
   //            if (ch == 3)
   //               col[0] = col[1] = col[2] = 1.f;
   //            else
   //               col[ch] = 1.f;
   //            pcontext->fill_color(col);
   //            ::nano2d::FontBlur(ctx, 0);
   //            pcontext->text(xpos, ypos, text[ch], nullptr);
   //         }
   //      }
   //   }
   //}

   //pcontext->restore();
}

void ImageImpact::draw_contents(::nano2d::context  * pcontext) 
{
   //if (!m_pimage)
      //return;

   Canvas::draw_contents(pcontext);

   /* Ensure that 'offset' is a multiple of the pixel ratio */
   //float pixel_ratio = screen()->pixel_ratio();
   //m_offset = (float_sequence2(int_sequence2(m_offset / pixel_ratio)) * pixel_ratio);

   //float_sequence2 bound1 = float_sequence2(m_size) * pixel_ratio,
   //   bound2 = -float_sequence2(m_pimage->width(), m_pimage->height()) * scale();

   //if ((m_offset.x >= bound1.x) != (m_offset.x < bound2.x))
   //   m_offset.x = ::maximum(::minimum(m_offset.x, bound1.x), bound2.x);
   //if ((m_offset.y >= bound1.y) != (m_offset.y < bound2.y))
   //   m_offset.y = ::maximum(::minimum(m_offset.y, bound1.y), bound2.y);

//   int_sequence2 viewport_size = render_pass()->viewport().second;

   //float scale = std::pow(2.f, m_scale / 5.f);

   //Matrix4f matrix_background =
   //   Matrix4f::scale(Vector3f(m_pimage->width() * scale / 20.f,
   //      m_image->height() * scale / 20.f, 1.f));

   //Matrix4f matrix_image =
   //   Matrix4f::ortho(0.f, viewport_size.cx, viewport_size.cy, 0.f, -1.f, 1.f) *
   //   Matrix4f::translate(Vector3f(m_offset.x, (int)m_offset.y, 0.f)) *
   //   Matrix4f::scale(Vector3f(m_image->size().x * scale,
   //      m_image->size().y * scale, 1.f));

   //m_image_shader->set_uniform("matrix_image", Matrix4f(matrix_image));
   //m_image_shader->set_uniform("matrix_background", Matrix4f(matrix_background));
   //m_image_shader->set_uniform("colorBackground", m_image_background_color);

   //m_image_shader->begin();
   //m_image_shader->draw_array(Shader::PrimitiveType::Triangle, 0, 6, false);
   //m_image_shader->end();
}



} // namespace nanoui


