#include "framework.h"
#include "image_frame.h"
#include "image.h"


//#define unequal(a, b, n) ((a) > (b) - (n))
#undef pixel
#ifdef __APPLE__

#define pixel(x, y) (ba[(y) * iScan + (x)])

#else

#define pixel(x, y) (ba[(pframe->m_rectangle.height() - (y) - 1) * iScan + (x)])


#endif

bool draw2d_gif_detect_8bit_borders(::image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex);

bool draw2d_gif_antialias_8bit(::image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex);

bool draw2d_gif_draw_frame(::image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex);


//CLASS_DECL_AURA bool draw2d_gif_load_frame(::image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex)
//{
//
//   if (::is_null(pimageCanvas))
//   {
//
//      __throw(error_bad_argument);
//
//      return false;
//
//   }
//
//   if (pimageCanvas->m_size == pframea->m_size)
//   {
//
//      __throw(error_bad_argument);
//
//      return false;
//
//   }
//
//   pframe->m_pimage->map();
//
//   //::color::color crBack = 0;
//
//   if (uFrameIndex <= 0 && transparentIndex >= 0)
//   {
//
//      draw2d_gif_detect_8bit_borders(pimageCanvas, pframea, pframe, uFrameIndex, ba, iScan, cra, transparentIndex);
//
//   }
//
//   //pframe->m_bTransparent = pframea->m_bTransparent;
//
//   //if (pframea->m_bTransparent)
//   //{
//
//   //   gif_draw_frame(pimageCanvas, pframea, pframe, uFrameIndex, ba, iScan, cra, transparentIndex);
//   //
//   //   if (uFrameIndex > 0 && pframea->element_at(uFrameIndex - 1)->m_edisposal == image_frame::disposal_background)
//   //   {
//
//   //      pimageCanvas.get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//   //      ::color::color crBack = pframea->m_colorBack;
//
//   //      byte bAlpha = colorref_get_a_value(crBack);
//
//   //      if (bAlpha == 0)
//   //      {
//
//   //         crBack = 0;
//
//   //      }
//   //      else
//   //      {
//
//   //         output_debug_string("non zero alpha");
//
//   //      }
//
//   //      ::rectangle_i32 rectangle = pframea->element_at(uFrameIndex - 1)->m_rectangle;
//
//   //      rectangle.offset(5, 5);
//
//   //      pimageCanvas.get_graphics()->fill_rectangle(rectangle, crBack);
//
//   //   }
//
//   //   pimageCanvas.get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//   //   ::const ::point_i32 & point = pframe->m_rectangle.top_left();
//
//   //   ::size_i32 sz = pframe->m_rectangle.size();
//
//   //   pimageCanvas.get_graphics()->BitBlt(point_i32 + point_i32(5, 5), sz, pframe->m_pimage->get_graphics());
//
//   //   pframe->m_pimage->from(pimageCanvas);
//
//   //   if (pframe->m_bTransparent)
//   //   {
//
//   //      crBack = pframea->m_colorTransparent;
//
//   //      pframea->m_iTransparentIndex = transparentIndex;
//
//   //      pframea->m_bTransparent = true;
//
//   //   }
//   //   else
//   //   {
//
//   //      crBack = pframe->m_colorTransparent;
//
//   //      size_i32 s = pframe->m_pimage->get_size();
//
//   //      int cx = s.cx;
//
//   //      int cy = s.cy;
//
//   //      if (pframe->m_rectangle.size() == pframea.m_size)
//   //      {
//
//   //         if (pixel(0, 0) == pixel(cx - 1, 0)) // && pframe->m_rectangle.left == 0 && pframe->m_rectangle.top == 0 && pframe->m_rectangle.right == pframea.width())
//   //         {
//
//   //            transparentIndex = pixel(0, 0);
//
//   //            pframea->m_iTransparentIndex = transparentIndex;
//
//   //         }
//   //         else if (pixel(0, cy - 1) == pixel(cx - 1, cy - 1))// && pframe->m_rectangle.left == 0 && pframe->m_rectangle.bottom == pframea->height() && pframe->m_rectangle.right == pframea.width())
//   //         {
//
//   //            transparentIndex = pixel(0, cy - 1);
//
//   //            pframea->m_iTransparentIndex = transparentIndex;
//
//   //         }
//   //         else
//   //         {
//
//   //            transparentIndex = pframea->m_iTransparentIndex;
//
//   //         }
//
//   //      }
//   //      else
//   //      {
//
//   //         transparentIndex = pframea->m_iTransparentIndex;
//
//   //      }
//
//   //   }
//
//   //   antialias_8bit(pimageCanvas, pframea, pframe, uFrameIndex, ba, iScan, cra, transparentIndex);
//
//   //   pimageCanvas.from(pframe->m_pimage);
//
//
//   //   pframe->m_pimage = create_image(pframea->m_size);
//
//   //   pframe->m_pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//   //   pframe->m_pimage->get_graphics()->BitBlt(nullptr, pframea->m_size, pimageCanvas.get_graphics(), point_i32(5, 5));
//
//
//
//
//
//
//
//
//   //   //if (false)
//   //   //{
//
//
//   //   //   draw2d::fastblur f(pframe->m_pimage->create_new, this);
//
//   //   //   image d(pframe->m_pimage->create_new, this);
//
//   //   //   d->create(pframe->m_pimage->get_size());
//
//   //   //   Sys(pframe->m_pimage->get_application())->draw2d()->imaging()->channel_spread(f->get_graphics(),
//   //   //    nullptr, f->m_size, pimageCanvas.get_graphics(), nullptr, 3, 1);
//
//
//   //   //   f.initialize(pframe->m_pimage->get_size() + size(10, 10), 1);
//
//   //   //   f.channel_copy(::color::e_channel_red, ::color::e_channel_alpha, pimageCanvas);
//
//   //   //   f.channel_invert(::color::e_channel_red);
//
//   //   //   f.blur();
//   //   //   f.channel_multiply(::color::e_channel_red, 1.4);
//   //   //   f.blur();
//   //   //
//   //   //         f.blur();
//
//   //   //   f.channel_invert(::color::e_channel_red);
//
//   //   //   image d(pframe->m_pimage->create_new, this);
//
//   //   //   d->create(pframea->m_size);
//
//   //   //   d->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//   //   //   d->get_graphics()->BitBlt(nullptr, pframea->m_size, f.get_graphics(), point_i32(5, 5));
//
//   //   //   pframe->m_pimage->div_alpha();
//
//   //   //   pframe->m_pimage->channel_copy(::color::e_channel_alpha, ::color::e_channel_red, d);
//
//   //   //   pframe->m_pimage->mult_alpha();
//
//   //   //}
//
//   //}
//   //else // !pframea->m_bTransparent
//   {
//
//      draw2d_gif_draw_frame(pimageCanvas, pframea, pframe, uFrameIndex, ba, iScan, cra, transparentIndex);
//
//
//      if (uFrameIndex > 0 && pframea->element_at(uFrameIndex - 1)->m_edisposal == ::draw2d::disposal_background)
//      {
//
//         pimageCanvas->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//         ::color::color crBack = pframea->m_colorBack;
//
//         byte bAlpha = colorref_get_a_value(crBack);
//
//         if (bAlpha == 0)
//         {
//
//            crBack = 0;
//
//         }
//         else
//         {
//
//            output_debug_string("non zero alpha");
//
//         }
//
//         ::rectangle_i32 rectangle = pframea->element_at(uFrameIndex - 1)->m_rectangle;
//
//         pimageCanvas->g()->fill_rectangle(rectangle, crBack);
//
//      }
//
//      //pimageCanvas.get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//      ::point_i32 point = pframe->m_rectangle.top_left();
//
//      ::size_i32 size = pframe->m_rectangle.size();
//
//
//
//      //if (uFrameIndex <= 0)
//      //{
//
//      //   pobject->__construct(pimageCanvas, pframea->m_size);
//
//      //}
//
//      pimageCanvas->precision_blend(point, pframe->m_pimage, nullptr, size);
//
//      pframe->m_pimage->from(pimageCanvas);
//
//      pframe->m_pimage->create_helper_map();
//
//   }
//
//   return true;
//
//}
//

bool draw2d_gif_draw_frame(image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex)
{

   auto colorref = pframe->m_pimage->colorref();

   int w = pframe->m_pimage->scan_size() / sizeof(::color32_t);

   for (index y = 0; y < pframe->m_rectangle.height(); y++)
   {

      for (index x = 0; x < pframe->m_rectangle.width(); x++)
      {

         index iIndex = pixel(x, y);

         if (iIndex >= cra.get_count())
         {

            colorref[y*w + x] = 0;

            continue;

         }

         if (iIndex == transparentIndex)
         {

            colorref[y*w + x] = 0;

            continue;

         }

         ::color32_t color32 = cra[iIndex];

         byte bA = colorref_get_a_value(color32);

//#if defined(__APPLE__) || (defined(ANDROID) && defined(__arm__))
//#if defined(__APPLE__) || defined(ANDROID)
// ANDROID -> // LITTLE_LIT_LIGHT_LITE_LITLE_ENDIANS!!!!!!!!!!
//#if defined(__APPLE__) || defined(ANDROID)
//
//         //byte bR = colorref_get_r_value(color32);
//         //byte bG = colorref_get_g_value(color32);
//         //byte bB = colorref_get_b_value(color32);
//
//         //pframe->m_pimage->m_pcolorref[y*w + x] = argb(bA, bB, bG, bR);
//
//         pframe->m_pimage->m_pcolorref[y*w + x] = ((color32 << 16) & 0xff0000) | ((color32 >> 16) & 0xff) | (color32 & 0xff00ff00);
//
//#else
         byte bR = colorref_get_r_value(color32);
         byte bG = colorref_get_g_value(color32);
         byte bB = colorref_get_b_value(color32);
         if (bA != 255)
         {

            output_debug_string("test255");
         }
         colorref[y*w + x] = argb(bA, bA * bR / 255, bA * bG / 255, bA * bB / 255);

//#endif

      }

   }

   return true;

}
