#include "framework.h"
#include "frame.h"
#include "image.h"
#include "imaging.h"
#include "acme/graphics/image/image32.h"
#include "acme/graphics/draw2d/color_array.h"


//#define unequal(a, b, n) ((a) > (b) - (n))
#undef pixel
#ifdef __APPLE__

#define pixel(x, y) (ba[(y) * iScan + (x)])

#else

#define pixel(x, y) (ba[(pframe->m_rectangle.height() - (y) - 1) * iScan + (x)])


#endif

namespace image
{

   bool draw2d_gif_detect_8bit_borders(::image::image * pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, int uFrameIndex, unsigned char * ba, int iScan, color_array & cra, int transparentIndex);

   bool draw2d_gif_antialias_8bit(::image::image * pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, int uFrameIndex, unsigned char * ba, int iScan, color_array & cra, int transparentIndex);

   bool draw2d_gif_draw_frame(::image::image * pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, int uFrameIndex, unsigned char * ba, int iScan, color_array & cra, int transparentIndex);


   //CLASS_DECL_AURA bool draw2d_gif_load_frame(::image::image *pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, int uFrameIndex, unsigned char * ba, int iScan, colorref_array & cra, int transparentIndex)
   //{
   //
   //   if (::is_null(pimageCanvas))
   //   {
   //
   //      throw ::exception(error_bad_argument);
   //
   //      return false;
   //
   //   }
   //
   //   if (pimageCanvas->m_size == pframea->m_size)
   //   {
   //
   //      throw ::exception(error_bad_argument);
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
   //   //   if (uFrameIndex > 0 && pframea->element_at(uFrameIndex - 1)->m_edisposal == ::image::image_frame::e_disposal_background)
   //   //   {
   //
   //   //      pimageCanvas.get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //
   //   //      ::color::color crBack = pframea->m_colorBack;
   //
   //   //      unsigned char bAlpha = color32_byte_opacity(crBack);
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
   //   //         informationf("non zero alpha");
   //
   //   //      }
   //
   //   //      ::int_rectangle rectangle = pframea->element_at(uFrameIndex - 1)->m_rectangle;
   //
   //   //      rectangle.offset(5, 5);
   //
   //   //      pimageCanvas.get_graphics()->fill_rectangle(rectangle, crBack);
   //
   //   //   }
   //
   //   //   pimageCanvas.get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //
   //   //   ::const ::int_point & point = pframe->m_rectangle.top_left();
   //
   //   //   ::int_size sz = pframe->m_rectangle.size();
   //
   //   //   pimageCanvas.get_graphics()->BitBlt(int_point + int_point(5, 5), sz, pframe->m_pimage->get_graphics());
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
   //   //      int_size s = pframe->m_pimage->get_size();
   //
   //   //      int cx = s.cx();
   //
   //   //      int cy = s.cy();
   //
   //   //      if (pframe->m_rectangle.size() == pframea.m_size)
   //   //      {
   //
   //   //         if (pixel(0, 0) == pixel(cx - 1, 0)) // && pframe->m_rectangle.left() == 0 && pframe->m_rectangle.top() == 0 && pframe->m_rectangle.right() == pframea.width())
   //   //         {
   //
   //   //            transparentIndex = pixel(0, 0);
   //
   //   //            pframea->m_iTransparentIndex = transparentIndex;
   //
   //   //         }
   //   //         else if (pixel(0, cy - 1) == pixel(cx - 1, cy - 1))// && pframe->m_rectangle.left() == 0 && pframe->m_rectangle.bottom() == pframea->height() && pframe->m_rectangle.right() == pframea.width())
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
   //   //   pframe->m_pimage->get_graphics()->BitBlt(nullptr, pframea->m_size, pimageCanvas.get_graphics(), int_point(5, 5));
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
   //   //   //   Sys(pframe->m_pimage->get_app())->draw2d()->imaging()->channel_spread(f->get_graphics(),
   //   //   //    nullptr, f->m_size, pimageCanvas.get_graphics(), nullptr, 3, 1);
   //
   //
   //   //   //   f.initialize(pframe->m_pimage->get_size() + size(10, 10), 1);
   //
   //   //   //   f.channel_copy(::color::e_channel_red, ::color::e_channel_opacity, pimageCanvas);
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
   //   //   //   d->get_graphics()->BitBlt(nullptr, pframea->m_size, f.get_graphics(), int_point(5, 5));
   //
   //   //   //   pframe->m_pimage->div_alpha();
   //
   //   //   //   pframe->m_pimage->channel_copy(::color::e_channel_opacity, ::color::e_channel_red, d);
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
   //      if (uFrameIndex > 0 && pframea->element_at(uFrameIndex - 1)->m_edisposal == ::draw2d::e_disposal_background)
   //      {
   //
   //         pimageCanvas->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //
   //         ::color::color crBack = pframea->m_colorBack;
   //
   //         unsigned char bAlpha = color32_byte_opacity(crBack);
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
   //            informationf("non zero alpha");
   //
   //         }
   //
   //         ::int_rectangle rectangle = pframea->element_at(uFrameIndex - 1)->m_rectangle;
   //
   //         pimageCanvas->g()->fill_rectangle(rectangle, crBack);
   //
   //      }
   //
   //      //pimageCanvas.get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //
   //      ::int_point point = pframe->m_rectangle.top_left();
   //
   //      ::int_size size = pframe->m_rectangle.size();
   //
   //
   //
   //      //if (uFrameIndex <= 0)
   //      //{
   //
   //      //   pparticle->__øconstruct(pimageCanvas, pframea->m_size);
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

   bool imaging::draw2d_gif_draw_frame(::image::image * pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, int uFrameIndex, unsigned char * ba, int iScan, color_array & colora, int transparentIndex)
   {

      auto pimage32 = pframe->m_pimage->image32();

      int w = pframe->m_pimage->scan_size() / sizeof(::color32_t);

      for (::collection::index y = 0; y < pframe->m_rectangle.height(); y++)
      {

         for (::collection::index x = 0; x < pframe->m_rectangle.width(); x++)
         {

            ::collection::index iIndex = pixel(x, y);

            if (iIndex >= colora.get_count())
            {

               pimage32[y * w + x] = {};

               continue;

            }

            if (iIndex == transparentIndex)
            {

               pimage32[y * w + x] = {};

               continue;

            }

            auto color = colora[iIndex];

            unsigned char bA = color.byte_opacity();

            //#if defined(__APPLE__) || (defined(__ANDROID__) && defined(__arm__))
            //#if defined(__APPLE__) || defined(__ANDROID__)
            // __ANDROID__ -> // LITTLE_LIT_LIGHT_LITE_LITLE_ENDIANS!!!!!!!!!!
            //#if defined(__APPLE__) || defined(__ANDROID__)
            //
            //         //unsigned char bR = color32_byte_red(color32);
            //         //unsigned char bG = color32_byte_green(color32);
            //         //unsigned char bB = color32_byte_blue(color32);
            //
            //         //pframe->m_pimage->m_pcolorref[y*w + x] = argb(bA, bB, bG, bR);
            //
            //         pframe->m_pimage->m_pcolorref[y*w + x] = ((color32 << 16) & 0xff0000) | ((color32 >> 16) & 0xff) | (color32 & 0xff00ff00);
            //
            //#else
            unsigned char bR = color.byte_red();
            unsigned char bG = color.byte_green();
            unsigned char bB = color.byte_blue();
            if (bA != 255)
            {

               informationf("test255");
            }
            pimage32[y * w + x].assign(argb(bA, bA * bR / 255, bA * bG / 255, bA * bB / 255), pimageCanvas->color_indexes());

            //#endif

         }

      }

      return true;

   }


} // namespace image


