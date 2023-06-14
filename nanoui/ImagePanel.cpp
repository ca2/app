/*
    src/imagepanel.cpp -- Image panel pwidget which shows a number of
    square-shaped icons

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
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



void CLASS_DECL_NANOUI load_image_directory(::nano2d::context * pcontext, ::array<::pair<int, ::string>> & images, const ::scoped_string & path);


ImagePanel::ImagePanel(Widget * parent)
   : Widget(parent), m_iThumbSize(64), m_iSpacing(10), m_iMargin(10),
   m_iMouseIndex(-1), m_bPendingLoad(false)
{
   
}


size_i32 ImagePanel::grid_size() const
{
   int n_cols = 1 + ::maximum(0,
      (int)((m_size.cx() - 2 * m_iMargin - m_iThumbSize) /
         (float)(m_iThumbSize + m_iSpacing)));
   int n_rows = ((int)m_images.size() + n_cols - 1) / n_cols;
   return sequence2_i32(n_cols, n_rows);
}


int ImagePanel::index_for_position(const point_i32 & p) const
{
   
   //auto pointClient = p - m_pos;
   
   auto pointClient = p - size_i32(m_iMargin, m_iMargin);
   
   point_f32 cursorrate = pointClient / (float)(m_iThumbSize + m_iSpacing);
   
   float icon_region = m_iThumbSize / (float)(m_iThumbSize + m_iSpacing);
   
   bool over_image =
      fmodf(cursorrate.x(), 1.f) < icon_region &&
      fmodf(cursorrate.y(), 1.f) < icon_region;
   
   
   ::point_i32 gridindex(cursorrate);
   
   auto gridsize = grid_size();
   
   over_image &= cursorrate.x() >= 0.f
      && cursorrate.y() >= 0.f
      && gridindex.x() >= 0
      && gridindex.y() >= 0
      && gridindex.x() < gridsize.cx()
      && gridindex.y() < gridsize.cy();
   
   return over_image ? (gridindex.x() + gridindex.y() * gridsize.cx()) : -1;
   
}


bool ImagePanel::mouse_motion_event(const point_i32 & p, const size_i32 & /* rel */, bool bDown, const ::user::e_key & /* modifiers */) 
{

   m_iMouseIndex = index_for_position(p);

   return false;

}


bool ImagePanel::mouse_button_event(const point_i32& p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & /* modifiers */)
{

   ::index iIndex = index_for_position(p);

   if (iIndex >= 0 && iIndex < (int)m_images.size() && m_callback && down)
   {

      m_callback(iIndex);

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


size_i32 ImagePanel::preferred_size(::nano2d::context * pcontext, bool bRecalcTextSize)
{

   auto gridsize = grid_size();
   
   ((ImagePanel *)this)->_defer_load_image_directory(pcontext);
   
   return size_i32(
      gridsize.cx() * m_iThumbSize + (gridsize.cx() - 1) * m_iSpacing + 2 * m_iMargin,
      gridsize.cy() * m_iThumbSize + (gridsize.cy() - 1) * m_iSpacing + 2 * m_iMargin
   );
}


void ImagePanel::draw(::nano2d::context * pcontext) 
{
   
   _defer_load_image_directory(pcontext);

   auto gridsize = grid_size();

   auto pvscrollpanel = dynamic_cast <VScrollPanel *>(parent());

   auto pparticle = get_nano2d_object(pcontext);

   auto pgraphics = dynamic_cast <::draw2d::graphics *>(pparticle);

   scoped_restore(pgraphics->m_bUseImageMipMapsOrResizedImages);

   pgraphics->m_bUseImageMipMapsOrResizedImages = true;

   for (::index iImageIndex = 0; iImageIndex < m_images.size(); ++iImageIndex)
   {
      
      point_i32 gridindex((int) iImageIndex % gridsize.cx(), (int) iImageIndex / gridsize.cx());
    
      point_i32 image_top_left =
         m_pos
         + ::size_i32(m_iMargin, m_iMargin)
         +  gridindex * (m_iThumbSize + m_iSpacing);
      
      if (pvscrollpanel)
      {

         ::rectangle_i32 rectangleViewableImagePanel(
            pvscrollpanel->m_pos.x(),
            pvscrollpanel->m_pos.y(),
            pvscrollpanel->m_pos.x() + pvscrollpanel->m_size.cx(),
            pvscrollpanel->m_pos.y() + pvscrollpanel->m_size.cy());

         ::rectangle_i32 rectangleImageFinalPlacement(
            image_top_left,
            ::size_i32(m_iThumbSize, m_iThumbSize));

         rectangleImageFinalPlacement.offset_y((int)-pvscrollpanel->scroll());

         if (!rectangleViewableImagePanel.intersects(rectangleImageFinalPlacement))
         {

            continue;
         }

      }
      
      int imgw, imgh;

      pcontext->image_size(m_images[iImageIndex].m_element1, &imgw, &imgh);

      float iw, ih, ix, iy;
      
      if (imgh < imgw)
      {
         iw = (float)m_iThumbSize;
         ih = iw * (float)imgh / (float)imgw;
         ix = 0;
         iy = -(ih - m_iThumbSize) * 0.5f;
      }
      else
      {
         ih = (float)m_iThumbSize;
         iw = ih * (float)imgw / (float)imgh;
         ix = -(iw - m_iThumbSize) * 0.5f;
         iy = 0;
      }
      
      float opacity = m_iMouseIndex == iImageIndex ? 1.0f : 0.7f;

      ::nano2d::paint img_paint = pcontext->image_pattern_from_index(
         image_top_left.x() + ix,
         image_top_left.y() + iy,
         iw, ih,
         0,
         opacity,
         m_images[iImageIndex].m_element1);

      pcontext->begin_path();
      pcontext->rounded_rectangle(
                                  (float)image_top_left.x(), (float)image_top_left.y(), (float)m_iThumbSize, (float)m_iThumbSize, 5);
      pcontext->fill_paint(img_paint);
      pcontext->fill();

      ::nano2d::paint shadow_paint =
         pcontext->box_gradient(image_top_left.x() - 1.f, (float)image_top_left.y(), m_iThumbSize + 2.f, m_iThumbSize + 2.f, 5.f, 3.f,
            ::rgba(0, 0, 0, 128), ::rgba(0, 0, 0, 0));
      pcontext->begin_path();
      pcontext->rectangle(image_top_left.x() - 5.f, image_top_left.y() - 5.f, m_iThumbSize + 10.f, m_iThumbSize + 10.f);
      pcontext->rounded_rectangle((float)image_top_left.x(), (float)image_top_left.y(), (float)m_iThumbSize, (float)m_iThumbSize, 6.f);
      pcontext->path_winding(::nano2d::e_solidity_hole);
      pcontext->fill_paint(shadow_paint);
      pcontext->fill();

      pcontext->begin_path();
      pcontext->rounded_rectangle(image_top_left.x() + 0.5f, image_top_left.y() + 0.5f, m_iThumbSize - 1.f, m_iThumbSize - 1.f, 4.f - 0.5f);
      pcontext->stroke_width(1.0f);
      pcontext->stroke_color(::rgba(255, 255, 255, 80));
      pcontext->stroke();

   }

}


::image * ImagePanel::_get_image(::index iImage)
{

   auto pimage = screen()->m_puserinteraction->m_pcontext->context_image()->integer_image(m_images[iImage].m_element1);

   return pimage;

}


} // namespace nanoui




