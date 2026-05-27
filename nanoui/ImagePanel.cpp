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
#include "acme/platform/application.h"
#include "aura/graphics/image/context.h"
#include "aura/user/user/interaction.h"
#include "acme/platform/scoped_restore.h"
#include "nano2d/context.h"



//::object * get_nano2d_object(::nano2d::context  * pcontext);

namespace nanoui
{



   void CLASS_DECL_NANOUI load_image_directory(::nano2d::context  * pcontext, ::array<::pair<::i32, ::string>> & images, const ::scoped_string & path);


   ImagePanel::ImagePanel(Widget * parent)
      : Widget(parent), m_iThumbSize(64), m_iSpacing(10), m_iMargin(10),
      m_iMouseIndex(-1), m_bPendingLoad(false)
   {

   }


   i32_size ImagePanel::grid_size() const
   {
      ::i32 n_cols = 1 + ::maximum(0,
         (::i32)((m_size.cx - 2 * m_iMargin - m_iThumbSize) /
            (::f32)(m_iThumbSize + m_iSpacing)));
      ::i32 n_rows = ((::i32)m_images.size() + n_cols - 1) / n_cols;
      return int_sequence2(n_cols, n_rows);
   }


   ::i32 ImagePanel::index_for_position(const i32_point & p) const
   {

      //auto pointClient = p - m_pos;

      auto pointClient = p - i32_size(m_iMargin, m_iMargin);

      ::f32_point cursorrate = pointClient / (::f32)(m_iThumbSize + m_iSpacing);

      ::f32 icon_region = m_iThumbSize / (::f32)(m_iThumbSize + m_iSpacing);

      bool over_image =
         fmodf(cursorrate.x, 1.f) < icon_region &&
         fmodf(cursorrate.y, 1.f) < icon_region;


      ::i32_point gridindex(cursorrate);

      auto gridsize = grid_size();

      over_image &= cursorrate.x >= 0.f
         && cursorrate.y >= 0.f
         && gridindex.x >= 0
         && gridindex.y >= 0
         && gridindex.x < gridsize.cx
         && gridindex.y < gridsize.cy;

      return over_image ? (gridindex.x + gridindex.y * gridsize.cx) : -1;

   }


   bool ImagePanel::mouse_motion_event(const i32_point & p, const i32_size & /* rel */, bool bDown, const ::user::e_key & /* modifiers */)
   {

      auto iIndex = index_for_position(p);

      if (iIndex != m_iMouseIndex)
      {

         m_iMouseIndex = iIndex;

         set_need_redraw();

         post_redraw();


      }

      return false;

   }


   bool ImagePanel::mouse_button_event(const i32_point & p, ::user::e_mouse emouse, bool down, bool bDoubleClick, const ::user::e_key & /* modifiers */)
   {

      ::collection::index iIndex = index_for_position(p);

      if (iIndex >= 0 && iIndex < (::i32)m_images.size() && m_callback && down)
      {

         m_callback(iIndex);

      }

      return true;

   }


   void ImagePanel::_defer_load_image_directory(::nano2d::context  * pcontext)
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


   i32_size ImagePanel::preferred_size(::nano2d::context  * pcontext, bool bRecalcTextSize)
   {

      ((ImagePanel *)this)->_defer_load_image_directory(pcontext);

      auto gridsize = grid_size();

      return i32_size(
         gridsize.cx * m_iThumbSize + (gridsize.cx - 1) * m_iSpacing + 2 * m_iMargin,
         gridsize.cy * m_iThumbSize + (gridsize.cy - 1) * m_iSpacing + 2 * m_iMargin
      );
   }


   void ImagePanel::draw(::nano2d::context  * pcontext)
   {

      _defer_load_image_directory(pcontext);

      auto gridsize = grid_size();

      auto pvscrollpanel = dynamic_cast <VScrollPanel *>(parent());

      auto pparticle = get_nano2d_object(pcontext);

      auto pgraphics = dynamic_cast <::draw2d::graphics *>(pparticle);

      scoped_restore(pgraphics->m_bUseImageMipMapsOrResizedImages);

      pgraphics->m_bUseImageMipMapsOrResizedImages = true;

      for (::collection::index iImageIndex = 0; iImageIndex < m_images.size(); ++iImageIndex)
      {

         i32_point gridindex((::i32)iImageIndex % gridsize.cx, (::i32)iImageIndex / gridsize.cx);

         i32_point image_top_left =
            m_pos
            + ::i32_size(m_iMargin, m_iMargin)
            + gridindex * (m_iThumbSize + m_iSpacing);

         if (pvscrollpanel)
         {

            ::i32_rectangle rectangleViewableImagePanel(
               pvscrollpanel->m_pos.x,
               pvscrollpanel->m_pos.y,
               pvscrollpanel->m_pos.x + pvscrollpanel->m_size.cx,
               pvscrollpanel->m_pos.y + pvscrollpanel->m_size.cy);

            ::i32_rectangle rectangleImageFinalPlacement(
               image_top_left,
               ::i32_size(m_iThumbSize, m_iThumbSize));

            rectangleImageFinalPlacement.offset_y((::i32)pvscrollpanel->get_scroll_offset().cy);

            if (!rectangleViewableImagePanel.intersects(rectangleImageFinalPlacement))
            {

               continue;
            }

         }

         ::i32 imgw, imgh;

         pcontext->image_size(m_images[iImageIndex].m_element1, &imgw, &imgh);

         ::f32 iw, ih, ix, iy;

         if (imgh < imgw)
         {
            iw = (::f32)m_iThumbSize;
            ih = iw * (::f32)imgh / (::f32)imgw;
            ix = 0;
            iy = -(ih - m_iThumbSize) * 0.5f;
         }
         else
         {
            ih = (::f32)m_iThumbSize;
            iw = ih * (::f32)imgw / (::f32)imgh;
            ix = -(iw - m_iThumbSize) * 0.5f;
            iy = 0;
         }

         ::f32 opacity = m_iMouseIndex == iImageIndex ? 1.0f : 0.7f;

         ::nano2d::paint img_paint = pcontext->image_pattern_from_index(
            image_top_left.x + ix,
            image_top_left.y + iy,
            iw, ih,
            0,
            opacity,
            m_images[iImageIndex].m_element1);

         pcontext->begin_path();
         pcontext->rounded_rectangle(
                                     (::f32)image_top_left.x, (::f32)image_top_left.y, (::f32)m_iThumbSize, (::f32)m_iThumbSize, 5);
         pcontext->fill_paint(img_paint);
         pcontext->fill();

         ::nano2d::paint shadow_paint =
            pcontext->box_gradient(image_top_left.x - 1.f, (::f32)image_top_left.y, m_iThumbSize + 2.f, m_iThumbSize + 2.f, 5.f, 3.f,
               ::rgba(0, 0, 0, 128), ::rgba(0, 0, 0, 0));
         pcontext->begin_path();
         pcontext->rectangle(image_top_left.x - 5.f, image_top_left.y - 5.f, m_iThumbSize + 10.f, m_iThumbSize + 10.f);
         pcontext->rounded_rectangle((::f32)image_top_left.x, (::f32)image_top_left.y, (::f32)m_iThumbSize, (::f32)m_iThumbSize, 6.f);
         pcontext->path_winding(::nano2d::e_solidity_hole);
         pcontext->fill_paint(shadow_paint);
         pcontext->fill();

         pcontext->begin_path();
         pcontext->rounded_rectangle(image_top_left.x + 0.5f, image_top_left.y + 0.5f, m_iThumbSize - 1.f, m_iThumbSize - 1.f, 4.f - 0.5f);
         pcontext->stroke_width(1.0f);
         pcontext->stroke_color(::rgba(255, 255, 255, 80));
         pcontext->stroke();

      }

   }


   ::image::image *ImagePanel::_get_image(::collection::index iImage)
   {

      auto pimage = screen()->m_puserinteraction->image()->integer_image(m_images[iImage].m_element1);

      return pimage;

   }


} // namespace nanoui




