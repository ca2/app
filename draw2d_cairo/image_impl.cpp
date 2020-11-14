#include "framework.h"
#include "aura/graphics/_.h"
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


   ::stream & image::read(::stream & stream)
   {

      sync_lock ml(cairo_mutex());

      ::image::read(stream);

      cairo_surface_t * surface = dynamic_cast <::draw2d_cairo::bitmap *> (m_pbitmap.m_p)->m_psurface;

      if (surface != nullptr)
      {

         cairo_surface_mark_dirty(surface);

      }

      return stream;

   }


   stream & image::write(::stream & stream) const
   {

      sync_lock ml(cairo_mutex());

      ::image::write(stream);

      return stream;

   }


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
//      return create(::size(width, height), uidCreateImage, iGoodStride);
//
//   }


   ::estatus image::create(const ::size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
   {

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && m_pgraphics.is_set()
            && m_pgraphics->get_os_data() != nullptr
            && size == m_sizeRaw)
      {

         return true;

      }

      destroy();

      if (size.is_empty())
      {

         return false;

      }

      m_pbitmap.create();

      m_pgraphics.create();

      if(m_pbitmap.is_null() || m_pgraphics.is_null())
      {

         m_sizeRaw.cx = 0;
         m_sizeRaw.cy = 0;
         m_iScan = 0;
         m_pcolorrefRaw = nullptr;
         m_pcolorref1 = nullptr;
         m_pbitmap.release();
         m_pgraphics.release();
         return false;

      }

      if (iGoodStride < 0)
      {

         iGoodStride = size.cx * sizeof(color32_t);

      }

      color32_t * pcolorrefRaw = nullptr;

      i32 iScan = iGoodStride;

      if(!m_pbitmap->create_bitmap(nullptr, size, (void **) &pcolorrefRaw, &iScan))
      {

         m_sizeRaw.cx = 0;
         m_sizeRaw.cy = 0;
         m_iScan = 0;
         m_pcolorrefRaw = nullptr;
         m_pcolorref1 = nullptr;
         m_pbitmap.release();
         m_pgraphics.release();
         return false;

      }

      if (m_pbitmap->get_os_data() == nullptr)
      {

         destroy();

      }

      m_pgraphics->set(m_pbitmap);
      m_pgraphics->SetViewportOrg(m_point);
      m_pgraphics->m_pimage = this;
      m_sizeRaw = size;
      m_sizeAlloc = size;
      m_pcolorref1 = nullptr;

      init(size, pcolorrefRaw, iScan);

      m_bMapped = false;

      _unmap();

      m_eobject = eobjectCreate;

      return true;

   }


   bool image::dc_select(bool bSelect)
   {
      /*      if(bSelect)
            {
               return m_spgraphics->SelectObject(m_pbitmap) != nullptr;
            }
            else
            {
               return m_spgraphics->SelectObject(m_hbitmapOriginal) != nullptr;
            }*/
      return true;
   }

   ::estatus image::create(::draw2d::graphics * pgraphics)
   {
      ::draw2d::bitmap * pbitmap = (dynamic_cast < ::draw2d_cairo::graphics * > (pgraphics))->get_current_bitmap();
      if(pbitmap == nullptr)
         return FALSE;
      ::size size = pbitmap->get_size();
      if(!create(size))
      {
         return FALSE;
      }
      from(pgraphics);
      return TRUE;
   }


   bool image::destroy ()
   {

      ::image::destroy();

      m_pbitmap.release();

      m_pgraphics.release();

      return true;

   }


   bool image::to(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, const ::point & ptSrc)
   {

      return pgraphics->BitBlt(point.x, point.y, size.cx, size.cy, get_graphics(), ptSrc.x, ptSrc.y) != FALSE;

      /*  return SetDIBitsToDevice(
           (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(),
           point.x, point.y,
           size.cx, size.cy,
           ptSrc.x, ptSrc.y, ptSrc.y, cy - ptSrc.y,
           m_pcolorrefMap, &m_info, 0)
              != FALSE; */

   }

   bool image::from(::draw2d::graphics * pgraphics)
   {
      ::draw2d::bitmap_pointer bitmap;
      bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);
      auto estatus = pgraphics->set(bitmap);
      if(!estatus)
         return false;
      ::size size = bitmap->get_size();
      if(!create(size))
      {
         pgraphics->set(bitmap);
         return false;
      }
      __throw(todo());
      // xxx bool bOk = GetDIBits(LNX_HDC(pgraphics), (HBITMAP) pbitmap->get_os_data(), 0, cy, m_pcolorrefMap, &(m_info), DIB_RGB_COLORS) != FALSE;
      // xxx pgraphics->SelectObject(pbitmap);
      // xxx return bOk;
   }


//   bool image::from(const ::point & pointDest, ::draw2d::graphics * pgraphics, const ::point & point, const ::size & size)
//   {
//
//      return m_spgraphics->BitBlt(pointDest.x, pointDest.y, sz.cx, sz.cy, pgraphics, point.x, point.y);
//
//   }


   //void image::Fill ( i32 R, i32 G, i32 B )
   //{
   //   color32_t color=RGB ( B, G, R );
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

   //   for (i=0; i<size; i++ )
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
   //   i32 rect = scan - cx * sizeof(color32_t);
   //   for (i=0; i<cy; i++ )
   //   {
   //      for (j=0; j<cx; j++ )
   //      {
   //         *pbyte++ = (byte) R * pbyte[3] / 255;
   //         *pbyte++ = (byte) G * pbyte[2] / 255;
   //         *pbyte++ = (byte) B * pbyte[1] / 255;
   //         pbyte++;
   //      }
   //      j+= rect;
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
   //      imageWork = create_image(get_object());
   //      imageWork = imageWork;
   //   }

   //   if(imageWork = create_image({width(),  height())})
   //      return;

   //   imageWork.FillByte(0);

   //   imageWork.channel_from(::color::channel_alpha, this);

   //   imageWork.channel_invert(::color::channel_alpha);


   //   BLENDFUNCTION bf;

   //   bf.BlendOp = AC_SRC_OVER;
   //   bf.BlendFlags = 0;
   //   bf.SourceConstantAlpha = 255;
   //   bf.AlphaFormat = AC_SRC_ALPHA;

   //   get_graphics()->alpha_blend(size(), imageWork.get_graphics(), bf);

   //   if(bPreserveAlpha)
   //   {

   //      imageWork.channel_invert(::color::channel_alpha);

   //      color::channel_from(::color::channel_alpha, imageWork);

   //   }

   //   */

   //}


   bool image::_map(bool bApplyAlphaTransform)
   {

      sync_lock ml(cairo_mutex());

      if (m_bMapped)
      {

         return true;

      }

      if (m_pcolorrefRaw == nullptr)
      {

         return true;

      }

      if (m_pbitmap.is_null())
      {

         return true;

      }

      cairo_surface_t * surface = m_pbitmap.cast < ::draw2d_cairo::bitmap>()->m_psurface;

      if (surface == nullptr)
      {

         return false;

      }

      cairo_surface_flush (surface);

      byte  * pdata = (byte *) cairo_image_surface_get_data(surface);

      if(pdata != (byte *) m_pcolorrefRaw && pdata != nullptr)
      {

         ::memcpy_dup(m_pcolorrefRaw, pdata, m_sizeRaw.cy * m_iScan);

      }

      pdata = (byte *) m_pcolorrefRaw;

      if(!bApplyAlphaTransform)
      {

         int size = m_iScan * m_sizeRaw.cy / sizeof(color32_t);

         while(size > 0)
         {

            if(pdata[3] != 0)
            {

               pdata[0] = pdata[0] * 255 / pdata[3];
               pdata[1] = pdata[1] * 255 / pdata[3];
               pdata[2] = pdata[2] * 255 / pdata[3];

            }

            pdata += 4;

            size--;

         }

         ((image *) this)->m_bTrans = true;

      }
      else
      {

         ((image *) this)->m_bTrans = false;

      }

      ((image *) this)->m_bMapped = true;

      return true;

   }


   bool image::_unmap()
   {

      sync_lock ml(cairo_mutex());

      if (!m_bMapped)
      {

         return true;

      }

      if (m_pcolorrefRaw == nullptr)
      {

         return true;

      }

      if (m_pbitmap.is_null())
      {

         return true;

      }

      cairo_surface_t * surface = m_pbitmap.cast < ::draw2d_cairo::bitmap> ()->m_psurface;

      if (surface == nullptr)
      {

         return true;

      }

      byte * pdata =  (byte *) m_pcolorrefRaw;

      int size = m_iScan * m_sizeRaw.cy / sizeof(color32_t);

      pdata =  (byte *) cairo_image_surface_get_data(surface);

      if(pdata != (byte *)m_pcolorrefRaw && pdata != nullptr)
      {

         ::memcpy_dup(pdata, m_pcolorrefRaw, m_sizeRaw.cy * m_iScan);

      }

      cairo_surface_mark_dirty (surface);

      if(m_pgraphics.is_set())
      {

         m_pgraphics->set(m_pbitmap);

      }

      ((image *) this)->m_bMapped = false;

      return true;

   }


   ::estatus image::SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy)
   {

      if (!create({cx, cy}))
      {

         return false;

      }

      if (cx <= 0 || cy <= 0)
      {

         return false;

      }

      // White blend image_impl
      auto pimage1 = create_image({cx, cy});

      if (!pimage1)
      {

         return false;

      }

      pimage1->set_rgb(255, 255, 255);

      pimage1->g()->DrawIcon(0, 0, picon, cx, cy, 0, nullptr, DI_IMAGE | DI_MASK);

      // Black blend image_impl
      auto pimage2 = create_image({cx, cy});

      if (!pimage2)
      {

         return false;

      }

      pimage2->fill(0, 0, 0, 0);

      pimage2->g()->DrawIcon(0, 0, picon, cx, cy, 0, nullptr, DI_IMAGE | DI_MASK);

      // Mask image_impl
      auto pimageM = create_image({cx, cy});

      if (!pimageM)
      {

         return false;

      }

      pimageM->g()->DrawIcon(0, 0, picon, cx, cy, 0, nullptr, DI_MASK);

      byte * r1=(byte*)pimage1->colorref();
      byte * r2=(byte*)pimage2->get_data();
      byte * srcM=(byte*)pimageM->colorref();
      byte * dest=(byte*)m_pcolorref1;
      i32 iSize = cx*cy;

      byte b;
      byte bMax;
      while ( iSize-- > 0)
      {
         if(srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b =(byte)(r1[0]  - r2[0]);
            bMax = max(b, bMax);
            b =(byte)(r1[1]  - r2[1]);
            bMax = max(b, bMax);
            b =(byte)(r1[2]  - r2[2]);
            bMax = max(b, bMax);
            bMax = 255 - bMax;
         }
         dest[0]  =  bMax;
         dest[1]  =  bMax;
         dest[2]  =  bMax;
         dest     += 4;
         srcM     += 4;
         r1       += 4;
         r2       += 4;
      }

      return true;

   }


   bool image::stretch_image(::image * pimage)
   {

      if (!get_graphics()->draw(rect(), pimage->g(), pimage->rect()))
      {

         return false;

      }

      return true;

   }


   ::draw2d::graphics * image::_get_graphics() const
   {

      return m_pgraphics;

   }


//#if defined(WINDOWS)
//
//
//   bool image::update_window(::aura::draw_interface * pwnd,::message::message * pmessage,bool bTransferBuffer)
//   {
//
//      rect64 rectWindow;
//
//      pwnd->get_window_rect(rectWindow);
//
//      m_spgraphics->SetViewportOrg(0, 0);
//
//      map(true);
//
//      ::rect rect(rectWindow);
//
//      //Application.window_graphics_update_window(pwnd->get_window_graphics(), pwnd->get_handle(), m_pcolorrefMap, rect,m_size.cx, m_size.cy, m_iScan);
//
//      return true;
//
//   }
//
//
//   bool image::print_window(::aura::draw_interface * pwnd, ::message::message * pmessage)
//   {
//
//      SCAST_PTR(::message::base, pbase, pmessage);
//
//      if(pbase->m_wparam == 0)
//         return false;
//
//      m_spgraphics->attach((HDC) pbase->m_wparam);
//
//      ::rect rectx;
//
//      ::draw2d::bitmap * pbitmap = m_spgraphics->get_current_bitmap();
//
//      ::GetCurrentObject((HDC) pbase->m_wparam, OBJ_BITMAP);
//
//      //      u32 dw = ::get_last_error();
//      ::size size = pbitmap->get_size();
//
//      rectx.left = 0;
//      rectx.top = 0;
//      rectx.right = size.cx;
//      rectx.bottom = size.cy;
//
//      try
//      {
//
//         ::rect rectWindow;
//
//         pwnd->get_window_rect(rectWindow);
//
//         ::image_pointer pimage1(get_object());
//
//         if (!pimage1->create(rectWindow.bottom_right()))
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
//         ::rect rectPaint;
//         ::rect rectUpdate;
//         rectUpdate = rectWindow;
//         rectPaint = rectWindow;
//         rectPaint.offset(-rectPaint.top_left());
//         m_spgraphics->SelectClipRgn(nullptr);
//         pwnd->_001OnDeferPaintLayeredWindowBackground(pimage1->g());
//         m_spgraphics->SelectClipRgn(nullptr);
//         m_spgraphics-> SetViewportOrg(::point());
//         pwnd->_000OnDraw(pimage1->g());
//         m_spgraphics->SetViewportOrg(::point());
//         //(dynamic_cast<::win::graphics * >(pgraphics))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
//         m_spgraphics->SelectClipRgn(nullptr);
//         m_spgraphics->SetViewportOrg(::point());
//
//         m_spgraphics->SelectClipRgn( nullptr);
//         m_spgraphics->BitBlt(rectPaint.left, rectPaint.top,
//                              rectPaint.width(), rectPaint.height(),
//                              pgraphics, rectUpdate.left, rectUpdate.top,
//                              SRCCOPY);
//
//      }
//      catch(...)
//      {
//      }
//      m_spgraphics->fill_rect(rectx, RGB(255, 255, 255));
//      pmessage->m_bRet = true;
//      pbase->set_lresult(0);
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
////   bool image::print_window(::aura::draw_interface * pwnd, ::message::message * pmessage)
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
////   bool image::update_window(::aura::draw_interface * pwnd, ::message::message * pmessage, bool bTransferBuffer)
////   {
////
////
////      rect64 rectWindow;
////
////      pwnd->get_window_rect(rectWindow);
////
////      m_spgraphics->SetViewportOrg(0, 0);
////
////      map(true);
////
////      ::rect rect(rectWindow);
////
//////      Application.window_graphics_update_window(pwnd->get_window_graphics(), pwnd->get_handle(), m_pcolorrefMap, rect, m_size.cx, m_size.cy, m_iScan, bTransferBuffer);
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
//   bool image::print_window(::aura::draw_interface * pwnd, ::message::message * pmessage)
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
//   bool image::update_window(::aura::draw_interface * pwnd, ::message::message * pmessage, bool bTransferBuffer)
//   {
//
//
//      rect64 rectWindow;
//
//      pwnd->get_window_rect(rectWindow);
//
//      m_spgraphics->SetViewportOrg(0, 0);
//
//      map(false);
//
//      ::rect rect(rectWindow);
//
//      //Application.window_graphics_update_window(pwnd->get_window_graphics(), pwnd->get_handle(), m_pcolorrefMap, rect, m_size.cx, m_size.cy, m_iScan, bTransferBuffer);
//
//      return true;
//
//
//   }
//
//
//#endif


   bool image::blend(const ::point & pointDstParam, ::image * pimplSrc,  const ::point & pointSrcParam, const ::size & sizeParam, byte bA)
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
         return true;

      if (pointDst.y < 0)
      {
         size.cy += pointDst.y;
         pointDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = min(size.cx, min(pimplSrc->width() - pointSrc.x, pimplDst->width() - pointDst.x));

      int yEnd = min(size.cy, min(pimplSrc->height() - pointSrc.y, pimplDst->height() - pointDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

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

      return true;

   }


   bool image::on_host_read_pixels(const ::pixmap * ppixmap)
   {

    return false;

   }


} // namespace draw2d_cairo



