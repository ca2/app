#include "framework.h"
#include "image.h"
#include "bitmap.h"
#include "graphics.h"
#include "aura/graphics/image/drawing.h"
#include <math.h>


namespace draw2d_cairo
{


   image::image() //:
//      m_pbitmap(e_create),
  //    m_spgraphics(e_create)
   {

      m_bMapped            = false;
      m_bTrans             = false;

   }

//   color32_t * image::get_data()
//   {
//      return m_pcolorrefMap;
//   }
   ::draw2d::bitmap_pointer image::get_bitmap() const
   {
      return m_pbitmap;
   }
   ::draw2d::bitmap_pointer image::detach_bitmap()
   {

      return m_pbitmap.detach();

   }


   //void image::read(::binary_stream < FILE > & stream)
   //{

   //   synchronous_lock ml(cairo_mutex());

   //   ::image::read(stream);

   //   cairo_surface_t * surface = dynamic_cast <::draw2d_cairo::bitmap *> (m_pbitmap.m_p)->m_psurface;

   //   if (surface != nullptr)
   //   {

   //      cairo_surface_mark_dirty(surface);

   //   }

   //}


   //void image::write(::binary_stream < FILE > & stream) const
   //{

   //   synchronous_lock ml(cairo_mutex());

   //   ::image::write(stream);

   //}


//   void    image::construct (i32 cx,  i32 cy)
//   {
//
//      m_pcolorrefMap    = nullptr;
//      cx             = 0;
//      cy             = 0;
//
//      create(cx, cy);
//
//   }


   image::~image ()
   {

      destroy ();

   }


//   bool image::create(i32 width, i32 height, const ::uid & uidCreateImage, int iGoodStride)
//   {
//
//      return create(::size_i32(width, height), uidCreateImage, iGoodStride);
//
//   }


   void image::create(const ::size_i32 & size, ::enum_flag eflagCreate, int iGoodStride, bool bPreserve)
   {

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && m_pgraphics.is_set()
            && m_pgraphics->get_os_data() != nullptr
            && size == m_sizeRaw)
      {

         //return true;

         return;

      }

      if (size.is_empty())
      {

         throw ::exception(error_invalid_empty_argument);

      }

      auto pbitmap = __create < ::draw2d::bitmap >();

      auto pgraphics = __create < ::draw2d::graphics >();

      //if(pbitmap.is_null() || pgraphics.is_null())
      //{

      //   return false;

      //}

      if (iGoodStride < 0)
      {

         iGoodStride = size.cx * sizeof(color32_t);

      }

      color32_t * pcolorrefRaw = nullptr;

      i32 iScan = iGoodStride;

      pbitmap->create_bitmap(nullptr, size, (void**)&pcolorrefRaw, &iScan);
      //pbitmap->create_bitmap(nullptr, size, nullptr, &iScan);

      //if(!pbitmap->create_bitmap(nullptr, size, (void **) &pcolorrefRaw, &iScan))
      //{

      //   return false;

      //}

      if(bPreserve)
      {

         map();

         if (::is_set(m_pcolorrefRaw))
         {

            copy_colorref(
               pcolorrefRaw,
               minimum(size.cx, m_size.cx),
               minimum(size.cy, m_size.cy),
               iScan,
               m_pcolorrefRaw,
               m_iScan);

         }

      }

      destroy();

      m_pbitmap = pbitmap;

      m_pgraphics = pgraphics;

      m_pgraphics->set(m_pbitmap);
      m_pgraphics->set_origin(m_point);
      m_pgraphics->m_pimage = this;
      m_sizeRaw = size;
      m_sizeAlloc = size;
      m_pcolorref1 = nullptr;

      //init(size, pcolorrefRaw, iScan);
      init(size, nullptr, iScan);

      m_bMapped = false;

      _unmap();

      set(eflagCreate);

      //return true;

   }


   //bool image::dc_select(bool bSelect)
   void image::dc_select(bool bSelect)
   {
      /*      if(bSelect)
            {
               return m_spgraphics->SelectObject(m_pbitmap) != nullptr;
            }
            else
            {
               return m_spgraphics->SelectObject(m_hbitmapOriginal) != nullptr;
            }*/
      
            //return true;

   }


   void image::create(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap * pbitmap = (dynamic_cast < ::draw2d_cairo::graphics * > (pgraphics))->get_current_bitmap();

      //if(pbitmap == nullptr)
      //{

      //   return false;

      //}

      ::size_i32 size = pbitmap->get_size();

      create(size);

      //if(!create(size))
      //{

      //   return false;

      //}

      image_source imagesource(pgraphics);

      rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      g()->draw(imagedrawing);

      //return true;

   }


   void image::destroy()
   {

      ::image::destroy();

      m_pbitmap.release();

      m_pgraphics.release();

      //return ::success;

   }


//   bool image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & ptSrc)
//   {
//
//      return pgraphics->BitBlt(point, size.cx, size.cy, get_graphics(), ptSrc.x, ptSrc.y) != false;
//
//      /*  return SetDIBitsToDevice(
//           (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(),
//           point.x, point.y,
//           size.cx, size.cy,
//           ptSrc.x, ptSrc.y, ptSrc.y, cy - ptSrc.y,
//           m_pcolorrefMap, &m_info, 0)
//              != false; */
//
//   }

   
   void image::_draw_raw(const ::rectangle_i32 & rectangleTarget, ::image * pimage, const ::point_i32 & pointSrc)
   {

      rectangle_f64 rectangle(rectangleTarget);

      image_source imagesource(pimage, ::rectangle_f64(pointSrc, rectangle.size()));

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      return g()->draw(imagedrawing);
//      ::draw2d::bitmap_pointer bitmap;
//      bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);
//      auto estatus = pgraphics->set(bitmap);
//      if(!estatus)
//         return false;
//      ::size_i32 size = bitmap->get_size();
//      if(!create(size))
//      {
//         pgraphics->set(bitmap);
//         return false;
//      }
//      throw ::exception(todo);
//      // xxx bool bOk = GetDIBits(LNX_HDC(pgraphics), (HBITMAP) pbitmap->get_os_data(), 0, cy, m_pcolorrefMap, &(m_info), DIB_RGB_COLORS) != false;
//      // xxx pgraphics->SelectObject(pbitmap);
//      // xxx return bOk;
   }


//   bool image::from(const ::point_i32 & pointDest, ::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size)
//   {
//
//      return m_spgraphics->BitBlt(pointDest.x, pointDest.y, sz.cx, sz.cy, pgraphics, point.x, point.y);
//
//   }


   //void image::Fill ( i32 R, i32 G, i32 B )
   //{
   //   color32_t color=rgb ( B, G, R );
   //   i32 size=cx*cy;

   //   color32_t * pcr;

   //   i32 iSize32 = size / 32;
   //   i32 i;
   //   for (i=0; i < iSize32; i+=32 )
   //   {
   //      pcr = &m_pcolorrefMap[i];
   //      pcr[0] = color;
   //      pcr[1] = color;
   //      pcr[2] = color;
   //      pcr[3] = color;
   //      pcr[4] = color;
   //      pcr[5] = color;
   //      pcr[6] = color;
   //      pcr[7] = color;
   //      pcr[8] = color;
   //      pcr[9] = color;
   //      pcr[10] = color;
   //      pcr[11] = color;
   //      pcr[12] = color;
   //      pcr[13] = color;
   //      pcr[14] = color;
   //      pcr[15] = color;
   //      pcr[16] = color;
   //      pcr[17] = color;
   //      pcr[18] = color;
   //      pcr[19] = color;
   //      pcr[20] = color;
   //      pcr[21] = color;
   //      pcr[22] = color;
   //      pcr[23] = color;
   //      pcr[24] = color;
   //      pcr[25] = color;
   //      pcr[26] = color;
   //      pcr[27] = color;
   //      pcr[28] = color;
   //      pcr[29] = color;
   //      pcr[30] = color;
   //      pcr[31] = color;
   //   }

   //   for (i=0; i<size_i32; i++ )
   //   {
   //      m_pcolorrefMap[i]=color;
   //   }
   //}

   //void image::set_rgb(i32 R, i32 G, i32 B)
   //{

   //   map();

   //   i32 size = scan*cy;

   //   byte * pbyte = (byte *) m_pcolorrefMap;

   //   i32 i;
   //   i32 j;
   //   i32 rectangle = scan - cx * sizeof(color32_t);
   //   for (i=0; i<cy; i++ )
   //   {
   //      for (j=0; j<cx; j++ )
   //      {
   //         *pbyte++ = (byte) R * pbyte[3] / 255;
   //         *pbyte++ = (byte) G * pbyte[2] / 255;
   //         *pbyte++ = (byte) B * pbyte[1] / 255;
   //         pbyte++;
   //      }
   //      j+= rectangle;
   //   }
   //}

   //void image::ToAlpha(i32 i)
   //{
   //   byte *dst=(byte*)m_pcolorrefMap;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[3] = dst[i];
   //      dst+=4;
   //   }
   //}

   //void image::from_alpha()
   //{
   //   byte *dst=(byte*)m_pcolorrefMap;
   //   i64 size = cx * cy;

   //   while ( size-- )
   //   {
   //      dst[0] = dst[3];
   //      dst[1] = dst[3];
   //      dst[2] = dst[3];
   //      dst+=4;
   //   }
   //}

   ////DIB = DIB * SRC_ALPHA

   //void image::mult_alpha(image_impl imageWork, bool bPreserveAlpha)
   //{
   //   image::mult_alpha(imageWork, bPreserveAlpha);
   //   return ;
   //   /*
   //   if(area() <= 0)
   //      return;

   //   //return image::mult_alpha(nullptr, true);
   //   image_impl imageWork;

   //   if(imageWork == nullptr)
   //   {
   //      imageWork = create_image(this);
   //      imageWork = imageWork;
   //   }

   //   if(imageWork = create_image({width(),  height())})
   //      return;

   //   imageWork.FillByte(0);

   //   imageWork.channel_from(::color::e_channel_alpha, this);

   //   imageWork.channel_invert(::color::e_channel_alpha);


   //   BLENDFUNCTION bf;

   //   bf.BlendOp = AC_SRC_OVER;
   //   bf.BlendFlags = 0;
   //   bf.SourceConstantAlpha = 255;
   //   bf.AlphaFormat = AC_SRC_ALPHA;

   //   get_graphics()->alpha_blend(size(), imageWork.get_graphics(), bf);

   //   if(bPreserveAlpha)
   //   {

   //      imageWork.channel_invert(::color::e_channel_alpha);

   //      ::color::e_channel_from(::color::e_channel_alpha, imageWork);

   //   }

   //   */

   //}


   void image::_map(bool bApplyAlphaTransform)
   {

      synchronous_lock ml(cairo_mutex());

      if (m_bMapped)
      {

         return;

      }

//      if (m_pcolorrefRaw == nullptr)
//      {
//
//         return;
//
//      }
//
      if (m_pbitmap.is_null())
      {

         return;

      }

      cairo_surface_t * surface = m_pbitmap.cast < ::draw2d_cairo::bitmap>()->m_psurface;

      if (surface == nullptr)
      {

         return;

      }

      cairo_surface_flush (surface);

      byte  * pdata = (byte *) cairo_image_surface_get_data(surface);

      m_pcolorrefRaw = (color32_t * ) pdata;

//      if(pdata != (byte *) m_pcolorrefRaw && pdata != nullptr)
//      {
//
//         ::memcpy_dup(m_pcolorrefRaw, pdata, m_sizeRaw.cy * m_iScan);
//
//      }

      //pdata = (byte *) m_pcolorrefRaw;

//      if(!bApplyAlphaTransform)
//      {
//
//         int size = m_iScan * m_sizeRaw.cy / sizeof(color32_t);
//
//         while(size > 0)
//         {
//
//            if(pdata[3] != 0)
//            {
//
//               pdata[0] = pdata[0] * 255 / pdata[3];
//               pdata[1] = pdata[1] * 255 / pdata[3];
//               pdata[2] = pdata[2] * 255 / pdata[3];
//
//            }
//
//            pdata += 4;
//
//            size--;
//
//         }
//
//         ((image *) this)->m_bTrans = true;
//
//      }
//      else
//      {
//
//         ((image *) this)->m_bTrans = false;
//
//      }

      ((image *) this)->m_bMapped = true;

      //return true;

   }


   void image::_unmap()
   {

      synchronous_lock ml(cairo_mutex());

      if (!m_bMapped)
      {

         return;

      }

      if (m_pcolorrefRaw == nullptr)
      {

         return;

      }

      if (m_pbitmap.is_null())
      {

         return;

      }

      cairo_surface_t * surface = m_pbitmap.cast < ::draw2d_cairo::bitmap> ()->m_psurface;

      if (surface == nullptr)
      {

         return;

      }

//      byte * pdata =  (byte *) m_pcolorrefRaw;
//
//      int size = m_iScan * m_sizeRaw.cy / sizeof(color32_t);
//
//      pdata =  (byte *) cairo_image_surface_get_data(surface);
//
//      if(pdata != (byte *)m_pcolorrefRaw && pdata != nullptr)
//      {
//
//         ::memcpy_dup(pdata, m_pcolorrefRaw, m_sizeRaw.cy * m_iScan);
//
//      }

      cairo_surface_mark_dirty (surface);

//      if(m_pgraphics.is_set())
//      {
//
//         m_pgraphics->set(m_pbitmap);
//
//      }

      ((image *) this)->m_bMapped = false;

   }


   void image::SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy)
   {

      throw ::exception(todo);

      //return error_not_implemented;

//      if (!create({cx, cy}))
//      {
//
//         return false;
//
//      }
//
//      if (cx <= 0 || cy <= 0)
//      {
//
//         return false;
//
//      }
//
//      // White blend image_impl
//      auto pimage1 = create_image({cx, cy});
//
//      if (!pimage1)
//      {
//
//         return false;
//
//      }
//
//      pimage1->set_rgb(255, 255, 255);
//
//      pimage1->g()->stretch(::size_i32(cx, cy), picon);
//
//      // Black blend image_impl
//      auto pimage2 = create_image({cx, cy});
//
//      if (!pimage2)
//      {
//
//         return false;
//
//      }
//
//      pimage2->fill(0, 0, 0, 0);
//
//      pimage2->g()->stretch(::size_i32(cx, cy), picon);
//
//      // Mask image_impl
//      auto pimageM = create_image({cx, cy});
//
//      if (!pimageM)
//      {
//
//         return false;
//
//      }
//
//      pimageM->g()->stretch(::size_i32(cx, cy), picon);
//
//      byte * r1=(byte*)pimage1->colorref();
//      byte * r2=(byte*)pimage2->get_data();
//      byte * srcM=(byte*)pimageM->colorref();
//      byte * dest=(byte*)m_pcolorref1;
//      i32 iSize = cx*cy;
//
//      byte b;
//      byte bMax;
//      while ( iSize-- > 0)
//      {
//         if(srcM[0] == 255)
//         {
//            bMax = 0;
//         }
//         else
//         {
//            bMax = 0;
//            b =(byte)(r1[0]  - r2[0]);
//            bMax = maximum(b, bMax);
//            b =(byte)(r1[1]  - r2[1]);
//            bMax = maximum(b, bMax);
//            b =(byte)(r1[2]  - r2[2]);
//            bMax = maximum(b, bMax);
//            bMax = 255 - bMax;
//         }
//         dest[0]  =  bMax;
//         dest[1]  =  bMax;
//         dest[2]  =  bMax;
//         dest     += 4;
//         srcM     += 4;
//         r1       += 4;
//         r2       += 4;
//      }

      //return true;

   }


   //bool image::stretch(const ::image * pimage)
   //{

   //   if (!get_graphics()->stretch(this->rectangle(), pimage->g(), pimage->rectangle()))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   ::draw2d::graphics * image::_get_graphics() const
   {

      return m_pgraphics;

   }


//#if defined(WINDOWS)
//
//
//   bool image::update_window(::aura::draw_interface * puserinteraction,::message::message * pmessage,bool bTransferBuffer)
//   {
//
//      rectangle_i64 rectangleWindow;
//
//      puserinteraction->get_window_rect(rectangleWindow);
//
//      m_spgraphics->set_origin(0, 0);
//
//      map(true);
//
//      ::rectangle_i32 rectangle(rectangleWindow);
//
//      //papp->window_graphics_update_window(puserinteraction->get_window_graphics(), puserinteraction->get_handle(), m_pcolorrefMap, rectangle,m_size.cx, m_size.cy, m_iScan);
//
//      return true;
//
//   }
//
//
//   bool image::print_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage)
//   {
//
//      ::pointer<::user::message>pusermessage(pmessage);
//
//      if(pusermessage->m_wparam == 0)
//         return false;
//
//      m_spgraphics->attach((HDC) pusermessage->m_wparam);
//
//      ::rectangle_i32 rectx;
//
//      ::draw2d::bitmap * pbitmap = m_spgraphics->get_current_bitmap();
//
//      ::GetCurrentObject((HDC) pusermessage->m_wparam, OBJ_BITMAP);
//
//      //      u32 dw = ::get_last_error();
//      ::size_i32 size = pbitmap->get_size();
//
//      rectx.left = 0;
//      rectx.top = 0;
//      rectx.right = size.cx;
//      rectx.bottom = size.cy;
//
//      try
//      {
//
//         ::rectangle_i32 rectangleWindow;
//
//         puserinteraction->get_window_rect(rectangleWindow);
//
//         ::image_pointer pimage1(this);
//
//         if (!pimage1->create(rectangleWindow.bottom_right()))
//         {
//
//            return false;
//
//         }
//
//         ::draw2d::graphics * pgraphics = pimage1->g();
//
//         if (pgraphics->get_os_data() == nullptr)
//         {
//
//            return false;
//
//         }
//
//         ::rectangle_i32 rectanglePaint;
//         ::rectangle_i32 rectangleUpdate;
//         rectangleUpdate = rectangleWindow;
//         rectanglePaint = rectangleWindow;
//         rectanglePaint.offset(-rectanglePaint.top_left());
//         m_spgraphics->SelectClipRgn(nullptr);
//         puserinteraction->_001OnDeferPaintLayeredWindowBackground(pimage1->g());
//         m_spgraphics->SelectClipRgn(nullptr);
//         m_spgraphics-> set_origin(::point_i32());
//         puserinteraction->_000OnDraw(pimage1->g());
//         m_spgraphics->set_origin(::point_i32());
//         //(dynamic_cast<::win::graphics * >(pgraphics))->FillSolidRect(rectangleUpdate.left, rectangleUpdate.top, 100, 100, 255);
//         m_spgraphics->SelectClipRgn(nullptr);
//         m_spgraphics->set_origin(::point_i32());
//
//         m_spgraphics->SelectClipRgn( nullptr);
//         m_spgraphics->BitBlt(rectanglePaint.left, rectanglePaint.top,
//                              rectanglePaint.width(), rectanglePaint.height(),
//                              pgraphics, rectangleUpdate.left, rectangleUpdate.top,
//                              SRCCOPY);
//
//      }
//      catch(...)
//      {
//      }
//      m_spgraphics->fill_rectangle(rectx, rgb(255, 255, 255));
//      pmessage->m_bRet = true;
//      pusermessage->set_lresult(0);
//
//      return true;
//   }
//
//
//#elif defined(LINUX)
//
//
//
//
////   bool image::print_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage)
////   {
////
////      return true;
////
////   }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////   bool image::update_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage, bool bTransferBuffer)
////   {
////
////
////      rectangle_i64 rectangleWindow;
////
////      puserinteraction->get_window_rect(rectangleWindow);
////
////      m_spgraphics->set_origin(0, 0);
////
////      map(true);
////
////      ::rectangle_i32 rectangle(rectangleWindow);
////
//////      papp->window_graphics_update_window(puserinteraction->get_window_graphics(), puserinteraction->get_handle(), m_pcolorrefMap, rectangle, m_size.cx, m_size.cy, m_iScan, bTransferBuffer);
////
////      return true;
////
////
////   }
////
//
//#elif defined(ANDROID)
//
//
//
//
//
//
//   bool image::print_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage)
//   {
//
//      return true;
//
//   }
//
//
//
//
//
//
//
//
//
//
//   bool image::update_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage, bool bTransferBuffer)
//   {
//
//
//      rectangle_i64 rectangleWindow;
//
//      puserinteraction->get_window_rect(rectangleWindow);
//
//      m_spgraphics->set_origin(0, 0);
//
//      map(false);
//
//      ::rectangle_i32 rectangle(rectangleWindow);
//
//      //papp->window_graphics_update_window(puserinteraction->get_window_graphics(), puserinteraction->get_handle(), m_pcolorrefMap, rectangle, m_size.cx, m_size.cy, m_iScan, bTransferBuffer);
//
//      return true;
//
//
//   }
//
//
//#endif


   void image::blend(const ::point_i32 & pointDstParam, ::image * pimplSrc,  const ::point_i32 & pointSrcParam, const ::size_i32 & sizeParam, byte bA)
   {

      auto size = sizeParam;

      auto pointDst = pointDstParam;

      auto pointSrc = pointSrcParam;

      ::image * pimplDst = this;

      pimplDst->map();

      pimplSrc->map();

      pointDst += m_point;

      if (pointDst.x < 0)
      {
         pointDst.x -= pointSrc.x;
         pointSrc.x = 0;
      }

      if (pointSrc.y < 0)
      {
         pointDst.y -= pointSrc.y;
         pointSrc.y = 0;
      }

      if (pointDst.x < 0)
      {
         size.cx += pointDst.x;
         pointDst.x = 0;
      }

      if (size.cx < 0)
      {

         return;

      }

      if (pointDst.y < 0)
      {
         size.cy += pointDst.y;
         pointDst.y = 0;
      }

      if (size.cy < 0)
      {

         return;

      }

      int xEnd = minimum(size.cx, minimum(pimplSrc->width() - pointSrc.x, pimplDst->width() - pointDst.x));

      int yEnd = minimum(size.cy, minimum(pimplSrc->height() - pointSrc.y, pimplDst->height() - pointDst.y));

      if (xEnd < 0)
      {

         return;

      }

      if (yEnd < 0)
      {

         return;

      }

      i32 scanDst = pimplDst->scan_size();

      i32 scanSrc = pimplSrc->scan_size();

      byte * pdst2;

      byte * psrc2;

#ifdef APPLEOS
      byte * pdst = &((byte *)imageDst.m_pcolorrefMap)[scanDst * (imageDst.height() - ptDst.y - yEnd) + ptDst.x * sizeof(color32_t)];

      byte * psrc = &((byte *)imageSrc.m_pcolorrefMap)[scanSrc * (imageSrc.height() - ptSrc.y - yEnd) + ptSrc.x * sizeof(color32_t)];

#else

      byte * pdst = &((byte *)pimplDst->m_pcolorref1)[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

      byte * psrc = &((byte *)pimplSrc->m_pcolorref1)[scanSrc *  pointSrc.y + pointSrc.x * sizeof(color32_t)];

#endif

//      bool bFontListBlend = true;
//
//      if (bFontListBlend)
//      {
//
//         if (bA == 0)
//         {
//
//         }
//         else if (bA == 255)
//         {
//
//            for (int y = 0; y < yEnd; y++)
//            {
//
//               pdst2 = &pdst[scanDst * y];
//
//               psrc2 = &psrc[scanSrc * y];
//
//               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
//               for (int x = 0; x < xEnd; x++)
//               {
//
//                  //*pdst2 = *psrc2;
//
//                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
//                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
//                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
//                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
//                  byte acomplement = ~psrc2[3];
//                  pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
//                  pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
//                  pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
//                  pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
//
//
//
//                  pdst2 += 4;
//
//                  psrc2 += 4;
//
//               }
//               //pdst2 += xEnd;
//               //psrc2 += xEnd;
//
//            }
//         }
//         else
//         {
//            for (int y = 0; y < yEnd; y++)
//            {
//
//               pdst2 = &pdst[scanDst * y];
//
//               psrc2 = &psrc[scanSrc * y];
//
//               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
//               for (int x = 0; x < xEnd; x++)
//               {
//
//                  //*pdst2 = *psrc2;
//
//                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
//                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
//                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
//                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
//                  //byte acomplement = (~psrc2[3] * bA) >> 8;
//                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
//                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
//                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
//                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
//                  byte acomplement = (~psrc2[3] * bA) >> 8;
//                  pdst2[0] = clip_byte(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
//                  pdst2[1] = clip_byte(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
//                  pdst2[2] = clip_byte(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
//                  pdst2[3] = clip_byte(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);
//
//
//
//                  pdst2 += 4;
//
//                  psrc2 += 4;
//
//               }
//               //pdst2 += xEnd;
//               //psrc2 += xEnd;
//
//            }
//
//         }
//
//         // bFontListData
//
//      }
//      else
      {

         // !bFontListData
         // bBouncingBall...

         if (bA == 0)
         {

         }
         else if (bA == 255)
         {

            for (int y = 0; y < yEnd; y++)
            {

               pdst2 = &pdst[scanDst * y];

               psrc2 = &psrc[scanSrc * y];

               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
               for (int x = 0; x < xEnd; x++)
               {

                  //*pdst2 = *psrc2;

                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
                  byte a = pdst2[3];
                  byte alpha = psrc2[3];
                  if (a == 0)
                  {

                  }
                  else if(alpha == 0)
                  {

                     *((color32_t *)pdst2) = 0;

                  }
                  else
                  {

                     //int d0 = pdst2[0] * 255 / a;
                     //int d1 = pdst2[1] * 255 / a;
                     //int d2 = pdst2[2] * 255 / a;

                     //int s0 = psrc2[0] * 255 / alpha;
                     //int s1 = psrc2[1] * 255 / alpha;
                     //int s2 = psrc2[2] * 255 / alpha;

                     //d0 = ((s0 * a) + (d0 * alpha)) >> 8;
                     //d1 = ((s1 * a) + (d1 * alpha)) >> 8;
                     //d2 = ((s2 * a) + (d2 * alpha)) >> 8;
                     //pdst2[3] = ((psrc2[3] * a) + (pdst2[3] * alpha)) >> 8;

                     //pdst[0] = (d0 * pdst2[3]) >> 8;
                     //pdst[1] = (d1 * pdst2[3]) >> 8;
                     //pdst[2] = (d2 * pdst2[3]) >> 8;

                     //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                     //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                     //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                     //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);

                     pdst2[0] = (pdst2[0] * alpha) >> 8;
                     pdst2[1] = (pdst2[1] * alpha) >> 8;
                     pdst2[2] = (pdst2[2] * alpha) >> 8;
                     pdst2[3] = (pdst2[3] * alpha) >> 8;
                  }



                  pdst2 += 4;

                  psrc2 += 4;

               }
               //pdst2 += xEnd;
               //psrc2 += xEnd;

            }
         }
         else
         {
            for (int y = 0; y < yEnd; y++)
            {

               pdst2 = &pdst[scanDst * y];

               psrc2 = &psrc[scanSrc * y];

               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
               for (int x = 0; x < xEnd; x++)
               {

                  //*pdst2 = *psrc2;

                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
                  //byte acomplement = (~psrc2[3] * bA) >> 8;
                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);

                  byte acomplement = (~psrc2[3] * bA) >> 8;

                  pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
                  pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
                  pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
                  pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);

                  pdst2 += 4;

                  psrc2 += 4;

               }
               //pdst2 += xEnd;
               //psrc2 += xEnd;

            }

         }

      }

      //return true;

   }


//   void image::blend2(const ::point_i32& pointDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, const ::size_i32& sizeParam, byte bA)
//   {
//
//      ::image* pimageDst = this;
//
//      pimageDst->map();
//
//      pimageSrc->map();
//
//      ::point_i32 pointDst(pointDstParam);
//
//      ::point_i32 pointSrc(pointSrcParam);
//
//      ::size_i32 size(sizeParam);
//
//      pointDst += m_point;
//
//      if (pointSrc.x < 0)
//      {
//         pointDst.x -= pointSrc.x;
//         pointSrc.x = 0;
//      }
//
//      if (pointSrc.y < 0)
//      {
//         pointDst.y -= pointSrc.y;
//         pointSrc.y = 0;
//      }
//
//      if (pointDst.x < 0)
//      {
//         size.cx += pointDst.x;
//         pointDst.x = 0;
//      }
//
//      if (size.cx < 0)
//      {
//
//         return;
//
//      }
//      //return true;
//
//      if (pointDst.y < 0)
//      {
//         size.cy += pointDst.y;
//         pointDst.y = 0;
//      }
//
//      if (size.cy < 0)
//      {
//         //   return true;
//
//         return;
//      }
//
//      int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));
//
//      int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));
//
//      if (xEnd < 0)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (yEnd < 0)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      i32 scanDst = pimageDst->m_iScan;
//
//      i32 scanSrc = pimageSrc->m_iScan;
//
//      byte * pdst = ((byte *) pimageDst->colorref()) + (scanDst * pointDst.y) + (pointDst.x * sizeof(color32_t));
//
//      byte * psrc = ((byte *) pimageSrc->colorref()) + (scanSrc * pointSrc.y) + (pointSrc.x * sizeof(color32_t));
//
//      byte * pdst2;
//
//      byte * psrc2;
//
//      if (bA == 0)
//      {
//
//      }
//      else if (bA == 255)
//      {
//
//         for (int y = 0; y < yEnd; y++)
//         {
//
//            pdst2 = pdst + scanDst * y;
//
//            psrc2 = psrc + scanSrc * y;
//
//            for (int x = 0; x < xEnd; x++)
//            {
//
//               int aDst = pdst2[3];
//
//               int aSrc = psrc2[3];
//
//               if (aDst == 0)
//               {
//
//               }
//               else if (aSrc == 0)
//               {
//
//                  *((color32_t*)pdst2) = 0;
//
//               }
//               else
//               {
//
////                  int r = (pdst2[0] * 255) / aDst;
////                  int g = (pdst2[1] * 255) / aDst;
////                  int b = (pdst2[2] * 255) / aDst;
//
//                  //int a = (aSrc * aDst) / 255;
//
//                  pdst2[0] = pdst2[0] * aSrc / 255;
//                  pdst2[1] = pdst2[1] * aSrc / 255;
//                  pdst2[2] = pdst2[2] * aSrc / 255;
//                  pdst2[3] = pdst2[3] * aSrc / 255;
//
//
//               }
//
//               pdst2 += 4;
//
//               psrc2 += 4;
//
//            }
//
//         }
//
//      }
//      else
//      {
//
//         for (int y = 0; y < yEnd; y++)
//         {
//
//            pdst2 = &pdst[scanDst * y];
//
//            psrc2 = &psrc[scanSrc * y];
//
//            //::memcpy_dup(pdst2, psrc2, xEnd * 4);
//            for (int x = 0; x < xEnd; x++)
//            {
//
//               //*pdst2 = *psrc2;
//
//               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
//               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
//               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
//               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
//               //byte acomplement = (~psrc2[3] * bA) >> 8;
//               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
//               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
//               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
//               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
//               byte acomplement = (~psrc2[3] * bA) >> 8;
//               pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
//               pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
//               pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
//               pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);
//
//               pdst2 += 4;
//
//               psrc2 += 4;
//
//            }
//            //pdst2 += xEnd;
//            //psrc2 += xEnd;
//
//         }
//
//      }
//
//      //return true;
//
//   }


//   void image::blend2(const ::point_i32 & pointDstParam, ::image * pimplSrc,  const ::point_i32 & pointSrcParam, const ::size_i32 & sizeParam, byte bA)
//   {
//
//      auto size = sizeParam;
//
//      auto pointDst = pointDstParam;
//
//      auto pointSrc = pointSrcParam;
//
//      ::image * pimplDst = this;
//
//      pimplDst->map();
//
//      pimplSrc->map();
//
//      pointDst += m_point;
//
//      if (pointDst.x < 0)
//      {
//         pointDst.x -= pointSrc.x;
//         pointSrc.x = 0;
//      }
//
//      if (pointSrc.y < 0)
//      {
//         pointDst.y -= pointSrc.y;
//         pointSrc.y = 0;
//      }
//
//      if (pointDst.x < 0)
//      {
//         size.cx += pointDst.x;
//         pointDst.x = 0;
//      }
//
//      if (size.cx < 0)
//      {
//
//         return;
//
//      }
//
//      if (pointDst.y < 0)
//      {
//         size.cy += pointDst.y;
//         pointDst.y = 0;
//      }
//
//      if (size.cy < 0)
//      {
//
//         return;
//
//      }
//
//      int xEnd = minimum(size.cx, minimum(pimplSrc->width() - pointSrc.x, pimplDst->width() - pointDst.x));
//
//      int yEnd = minimum(size.cy, minimum(pimplSrc->height() - pointSrc.y, pimplDst->height() - pointDst.y));
//
//      if (xEnd < 0)
//      {
//
//         return;
//
//      }
//
//      if (yEnd < 0)
//      {
//
//         return;
//
//      }
//
//      i32 scanDst = pimplDst->scan_size();
//
//      i32 scanSrc = pimplSrc->scan_size();
//
//      byte * pdst2;
//
//      byte * psrc2;
//
//#ifdef APPLEOS
//      byte * pdst = &((byte *)imageDst.m_pcolorrefMap)[scanDst * (imageDst.height() - ptDst.y - yEnd) + ptDst.x * sizeof(color32_t)];
//
//      byte * psrc = &((byte *)imageSrc.m_pcolorrefMap)[scanSrc * (imageSrc.height() - ptSrc.y - yEnd) + ptSrc.x * sizeof(color32_t)];
//
//#else
//
//      byte * pdst = &((byte *)pimplDst->m_pcolorref1)[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];
//
//      byte * psrc = &((byte *)pimplSrc->m_pcolorref1)[scanSrc *  pointSrc.y + pointSrc.x * sizeof(color32_t)];
//
//#endif
//
////      bool bFontListBlend = true;
////
////      if (bFontListBlend)
////      {
////
////         if (bA == 0)
////         {
////
////         }
////         else if (bA == 255)
////         {
////
////            for (int y = 0; y < yEnd; y++)
////            {
////
////               pdst2 = &pdst[scanDst * y];
////
////               psrc2 = &psrc[scanSrc * y];
////
////               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
////               for (int x = 0; x < xEnd; x++)
////               {
////
////                  //*pdst2 = *psrc2;
////
////                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
////                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
////                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
////                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
////                  byte acomplement = ~psrc2[3];
////                  pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
////                  pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
////                  pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
////                  pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
////
////
////
////                  pdst2 += 4;
////
////                  psrc2 += 4;
////
////               }
////               //pdst2 += xEnd;
////               //psrc2 += xEnd;
////
////            }
////         }
////         else
////         {
////            for (int y = 0; y < yEnd; y++)
////            {
////
////               pdst2 = &pdst[scanDst * y];
////
////               psrc2 = &psrc[scanSrc * y];
////
////               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
////               for (int x = 0; x < xEnd; x++)
////               {
////
////                  //*pdst2 = *psrc2;
////
////                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
////                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
////                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
////                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
////                  //byte acomplement = (~psrc2[3] * bA) >> 8;
////                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
////                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
////                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
////                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
////                  byte acomplement = (~psrc2[3] * bA) >> 8;
////                  pdst2[0] = clip_byte(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
////                  pdst2[1] = clip_byte(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
////                  pdst2[2] = clip_byte(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
////                  pdst2[3] = clip_byte(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);
////
////
////
////                  pdst2 += 4;
////
////                  psrc2 += 4;
////
////               }
////               //pdst2 += xEnd;
////               //psrc2 += xEnd;
////
////            }
////
////         }
////
////         // bFontListData
////
////      }
////      else
//      {
//
//         // !bFontListData
//         // bBouncingBall...
//
//         if (bA == 0)
//         {
//
//         }
//         else if (bA == 255)
//         {
//
//            for (int y = 0; y < yEnd; y++)
//            {
//
//               pdst2 = &pdst[scanDst * y];
//
//               psrc2 = &psrc[scanSrc * y];
//
//               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
//               for (int x = 0; x < xEnd; x++)
//               {
//
//                  //*pdst2 = *psrc2;
//
//                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
//                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
//                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
//                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
//                  byte a = pdst2[3];
//                  byte alpha = psrc2[3];
//                  if (a == 0)
//                  {
//
//                  }
//                  else if(alpha == 0)
//                  {
//
//                     *((color32_t *)pdst2) = 0;
//
//                  }
//                  else
//                  {
//
//                     //int d0 = pdst2[0] * 255 / a;
//                     //int d1 = pdst2[1] * 255 / a;
//                     //int d2 = pdst2[2] * 255 / a;
//
//                     //int s0 = psrc2[0] * 255 / alpha;
//                     //int s1 = psrc2[1] * 255 / alpha;
//                     //int s2 = psrc2[2] * 255 / alpha;
//
//                     //d0 = ((s0 * a) + (d0 * alpha)) >> 8;
//                     //d1 = ((s1 * a) + (d1 * alpha)) >> 8;
//                     //d2 = ((s2 * a) + (d2 * alpha)) >> 8;
//                     //pdst2[3] = ((psrc2[3] * a) + (pdst2[3] * alpha)) >> 8;
//
//                     //pdst[0] = (d0 * pdst2[3]) >> 8;
//                     //pdst[1] = (d1 * pdst2[3]) >> 8;
//                     //pdst[2] = (d2 * pdst2[3]) >> 8;
//
//                     //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
//                     //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
//                     //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
//                     //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
//
//                     int alpha2 = alpha * a;
//
//                     pdst2[0] = (pdst2[0] * alpha2) >> 8;
//                     pdst2[1] = (pdst2[1] * alpha2) >> 8;
//                     pdst2[2] = (pdst2[2] * alpha2) >> 8;
//                     pdst2[3] = (alpha2) >> 8;
//                  }
//
//
//
//                  pdst2 += 4;
//
//                  psrc2 += 4;
//
//               }
//               //pdst2 += xEnd;
//               //psrc2 += xEnd;
//
//            }
//         }
//         else
//         {
//            for (int y = 0; y < yEnd; y++)
//            {
//
//               pdst2 = &pdst[scanDst * y];
//
//               psrc2 = &psrc[scanSrc * y];
//
//               //::memcpy_dup(pdst2, psrc2, xEnd * 4);
//               for (int x = 0; x < xEnd; x++)
//               {
//
//                  //*pdst2 = *psrc2;
//
//                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
//                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
//                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
//                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
//                  //byte acomplement = (~psrc2[3] * bA) >> 8;
//                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
//                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
//                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
//                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
//
//                  byte acomplement = (~psrc2[3] * bA) >> 8;
//
//                  pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
//                  pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
//                  pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
//                  pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);
//
//                  pdst2 += 4;
//
//                  psrc2 += 4;
//
//               }
//               //pdst2 += xEnd;
//               //psrc2 += xEnd;
//
//            }
//
//         }
//
//      }
//
//      //return true;
//
//   }


   bool image::on_host_read_pixels(const ::pixmap * ppixmap)
   {

    return false;

   }


} // namespace draw2d_cairo



