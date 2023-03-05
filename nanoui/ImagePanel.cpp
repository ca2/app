﻿/*
    src/imagepanel.cpp -- Image panel widget which shows a number of
    square-shaped icons

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "ImagePanel.h"
#include "VScrollPanel.h"
#include "Screen.h"
#include "acme/platform/context.h"
#include "aura/graphics/image/context_image.h"
#include "aura/user/user/interaction.h"
#include "acme/platform/scoped_restore.h"
#include "nano2d/context.h"



//::object * get_nano2d_object(::nano2d::context * pcontext);

namespace nanoui
{



void CLASS_DECL_NANOUI load_image_directory(::nano2d::context * pcontext, ::array<std::pair<int, ::string>> & images, const ::scoped_string & path);


ImagePanel::ImagePanel(Widget * parent)
   : Widget(parent), m_thumb_size(64), m_spacing(10), m_margin(10),
   m_mouse_index(-1), m_bPendingLoad(false)
{
   
}

Vector2i ImagePanel::grid_size() const
{
   int n_cols = 1 + std::max(0,
      (int)((m_size.x() - 2 * m_margin - m_thumb_size) /
         (float)(m_thumb_size + m_spacing)));
   int n_rows = ((int)m_images.size() + n_cols - 1) / n_cols;
   return Vector2i(n_cols, n_rows);
}

int ImagePanel::index_for_position(const Vector2i & p) const {
   Vector2f pp = (Vector2f(p - m_pos) - Vector2f((float)m_margin)) /
      (float)(m_thumb_size + m_spacing);
   float icon_region = m_thumb_size / (float)(m_thumb_size + m_spacing);
   bool over_image = pp.x() - std::floor(pp.x()) < icon_region &&
      pp.y() - std::floor(pp.y()) < icon_region;
   Vector2i grid_pos(pp), grid = grid_size();
   over_image &= grid_pos.x() >= 0 && grid_pos.y() >= 0 && pp.x() >= 0 &&
      pp.y() >= 0 && grid_pos.x() < grid.x() &&
      grid_pos.y() < grid.y();
   return over_image ? (grid_pos.x() + grid_pos.y() * grid.x()) : -1;
}


bool ImagePanel::mouse_motion_event(const Vector2i & p, const Vector2i & /* rel */, const ::user::e_key & /* modifiers */) 
{

   m_mouse_index = index_for_position(p);

   return true;

}


bool ImagePanel::mouse_button_event(const Vector2i& p, ::user::e_mouse emouse, bool down, const ::user::e_key & /* modifiers */) 
{

   int index = index_for_position(p);

   if (index >= 0 && index < (int)m_images.size() && m_callback && down)
   {

      m_callback(index);

   }

   return true;

}


void ImagePanel::_defer_load_image_directory(::nano2d::context * pcontext)
{

   if (m_bPendingLoad)
   {

      m_bPendingLoad = false;

      if (m_strLoadDirectory.size() > 0)
      {

         ::nanoui::load_image_directory(pcontext, m_images, m_strLoadDirectory);

      }

   }

}


Vector2i ImagePanel::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize) {
   Vector2i grid = grid_size();
   ((ImagePanel *)this)->_defer_load_image_directory(pcontext);
   return Vector2i(
      grid.x() * m_thumb_size + (grid.x() - 1) * m_spacing + 2 * m_margin,
      grid.y() * m_thumb_size + (grid.y() - 1) * m_spacing + 2 * m_margin
   );
}


void ImagePanel::draw(::nano2d::context * pcontext) 
{
   
   _defer_load_image_directory(pcontext);

   Vector2i grid = grid_size();

   auto pvscrollpanel = dynamic_cast <VScrollPanel *>(parent());

   auto pparticle = get_nano2d_object(pcontext);

   auto pgraphics = dynamic_cast <::draw2d::graphics *>(pparticle);

   scoped_restore(pgraphics->m_bUseImageMipMapsOrResizedImages);

   pgraphics->m_bUseImageMipMapsOrResizedImages = true;

   for (::index i = 0; i < m_images.size(); ++i) {
      Vector2i p = m_pos + Vector2i(m_margin) +
         Vector2i((int)i % grid.x(), (int)i / grid.x()) * (m_thumb_size + m_spacing);
      int imgw, imgh;

      if (pvscrollpanel)
      {


         ::rectangle_i32 rectangleViewableImagePanel(
            pvscrollpanel->m_pos.x(),
            pvscrollpanel->m_pos.y(),
            pvscrollpanel->m_pos.x() + pvscrollpanel->m_size.x(),
            pvscrollpanel->m_pos.y() + pvscrollpanel->m_size.y());

         ::rectangle_i32 rectangleImageFinalPlacement(
            p.x(),
            p.y(),
            p.x() + m_thumb_size,
            p.y() + m_thumb_size);

         rectangleImageFinalPlacement.offset_y((int)-pvscrollpanel->scroll());

            if (!rectangleViewableImagePanel.intersects(rectangleImageFinalPlacement))
         {

            continue;
         }

      }

      pcontext->image_size(m_images[i].first, &imgw, &imgh);

      float iw, ih, ix, iy;
      if (imgh < imgw) {
         iw = (float)m_thumb_size;
         ih = iw * (float)imgh / (float)imgw;
         ix = 0;
         iy = -(ih - m_thumb_size) * 0.5f;
      }
      else {
         ih = (float)m_thumb_size;
         iw = ih * (float)imgw / (float)imgh;
         ix = -(iw - m_thumb_size) * 0.5f;
         iy = 0;
      }

      ::nano2d::paint img_paint = pcontext->image_pattern(
         p.x() + ix, p.y() + iy, iw, ih, 0, m_images[i].first,
         m_mouse_index == (int)i ? 1.0f : 0.7f);

      pcontext->begin_path();
      pcontext->rounded_rectangle((float)p.x(), (float)p.y(), (float)m_thumb_size, (float)m_thumb_size, 5);
      pcontext->fill_paint(img_paint);
      pcontext->fill();

      ::nano2d::paint shadow_paint =
         pcontext->box_gradient(p.x() - 1.f, (float)p.y(), m_thumb_size + 2.f, m_thumb_size + 2.f, 5.f, 3.f,
            ::nano2d::RGBA_color(0, 0, 0, 128), ::nano2d::RGBA_color(0, 0, 0, 0));
      pcontext->begin_path();
      pcontext->rectangle(p.x() - 5.f, p.y() - 5.f, m_thumb_size + 10.f, m_thumb_size + 10.f);
      pcontext->rounded_rectangle((float)p.x(), (float)p.y(), (float)m_thumb_size, (float)m_thumb_size, 6.f);
      pcontext->path_winding(::nano2d::e_solidity_hole);
      pcontext->fill_paint(shadow_paint);
      pcontext->fill();

      pcontext->begin_path();
      pcontext->rounded_rectangle(p.x() + 0.5f, p.y() + 0.5f, m_thumb_size - 1.f, m_thumb_size - 1.f, 4.f - 0.5f);
      pcontext->stroke_width(1.0f);
      pcontext->stroke_color(::nano2d::RGBA_color(255, 255, 255, 80));
      pcontext->stroke();
   }
}

::image * ImagePanel::_get_image(int iImage)
{

   auto pimage = screen()->m_puserinteraction->m_pcontext->context_image()->integer_image(m_images[iImage].first);

   return pimage;

}



} // namespace nanoui

