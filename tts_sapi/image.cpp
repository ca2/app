#include "framework.h"


namespace draw2d_gdiplus
{


   image::image()
   {

      m_sizeWnd.cx = 0;
      m_sizeWnd.cy = 0;
      m_hbitmap = nullptr;

      __zero(m_bitmapinfo);

   }


   image::~image()
   {

      destroy();

   }


   ::draw2d::bitmap_pointer image::get_bitmap() const
   {

      return m_pbitmap;

   }


   ::draw2d::bitmap_pointer image::detach_bitmap()
   {

      return m_pbitmap.detach();

   }


   bool image::map(bool)
   {

      return true;

   }


   bool image::_unmap()
   {

      return true;

   }

   
   bool image::on_host_read_pixels(const ::pixmap* pixmap)
   {

      return false;

   }


   bool image::host(const ::pixmap * ppixmap)
   {

      if (!ppixmap->is_ok())
      {

         return false;

      }

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && ppixmap->size() == size()
            && ppixmap->colorref() == colorref()
            && ppixmap->scan_size() == scan_size())
      {

         return true;

      }

      //destroy();

      m_pbitmap.defer_create();

      m_pgraphics.defer_create();

      if (m_pbitmap.is_null())
      {

         m_sizeRaw.cx = 0;

         m_sizeRaw.cy = 0;

         m_sizeAlloc.cx = 0;

         m_sizeAlloc.cy = 0;

         m_iScan = 0;

         return false;

      }

      if (!m_pbitmap->host_bitmap(nullptr, ppixmap))
      {

         m_sizeRaw.cx = 0;

         m_sizeRaw.cy = 0;

         m_sizeAlloc.cx = 0;

         m_sizeAlloc.cy = 0;

         m_iScan = 0;

         return false;

      }

      if (m_pbitmap->get_os_data() == nullptr)
      {

         destroy();

         return false;

      }

      init(ppixmap->size(), ppixmap->colorref(), ppixmap->m_iScan);

      m_pgraphics->set(m_pbitmap);

      m_pgraphics->m_pimage = this;

      m_pgraphics->SetViewportOrg(0, 0);

      m_sizeAlloc = ppixmap->size();

      set_ok();

      return true;

   }


   ::e_status image::create(const ::size_i32& size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
   {

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && size == m_sizeRaw)
      {

         return true;

      }

      ::draw2d::bitmap_pointer pbitmapPrevious;

      ::draw2d::graphics_pointer pgraphicsPrevious;

      if (bPreserve)
      {

         pbitmapPrevious = m_pbitmap;

         pgraphicsPrevious = m_pgraphics;

         m_pbitmap.create();

         m_pgraphics.create();

      }
      else
      {

         m_pbitmap.defer_create();

         m_pgraphics.defer_create();

      }

      //destroy();

      //if (!size_i32)
      //{

      //   return true;

      //}


      if (m_pbitmap.is_null() || m_pgraphics.is_null())
      {

         destroy();

         return false;

      }

      int iScan = 0;

      color32_t * pcolorref = nullptr;

      if (!m_pbitmap->create_bitmap(nullptr, size, (void**)&pcolorref, &iScan))
      {

         destroy();

         return false;

      }

      if (m_pbitmap->get_os_data() == nullptr)
      {

         destroy();

         return false;

      }

      pixmap::init(size, pcolorref, iScan);

      m_pgraphics->set(m_pbitmap);
      m_pgraphics->SetViewportOrg(origin());

      m_pgraphics->m_pimage = this;
      //m_sizeRaw.cx = width;
      //m_sizeRaw.cy = height;
      m_sizeAlloc = size;
      //m_sizeAlloc.cy = height;

      if (pbitmapPrevious && pgraphicsPrevious)
      {

         Gdiplus::Rect r(0, 0, pbitmapPrevious->m_size.cx, pbitmapPrevious->m_size.cy);
         __graphics(m_pgraphics)->m_pgraphics->DrawImage(
            pbitmapPrevious.cast <::draw2d_gdiplus::bitmap>()->m_pbitmap,
            r, r.X, r.Y, r.Width, r.Height, Gdiplus::UnitPixel);

      }
      
      m_bMapped = false;

      m_eobject = eobjectCreate;

      return true;

   }


   bool image::dc_select(bool bSelect)
   {

      return true;

   }


   ::e_status image::create(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap * pbitmap = (dynamic_cast<::draw2d_gdiplus::graphics *>(pgraphics))->get_current_bitmap();

      if (pbitmap == nullptr)
      {

         return false;

      }

      if (!create(pbitmap->get_size()))
      {

         return false;

      }

      copy(pgraphics->m_pimage);

      return true;

   }


   bool image::destroy()
   {

      ::image::destroy();

      m_pgraphics.release();

      m_pbitmap.release();

      return true;

   }


   //bool image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc)
   //{

   //   return pgraphics->draw(point, size, get_graphics(), pointSrc);

   //}


   bool image::stretch(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap_pointer bitmap(get_context_application());

      bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);

      const ::size_i32 & size = bitmap->get_size();

      if (!create(size))
      {

         return false;

      }

      HDC hdc = __graphics(pgraphics)->get_hdc();

      bool bOk = GetDIBits(hdc, (HBITMAP)bitmap->get_os_data(), 0, height(), m_pcolorrefRaw, nullptr, DIB_RGB_COLORS) != false;

      g()->set(bitmap);

      __graphics(pgraphics)->release_hdc(hdc);

      auto estatus = pgraphics->set(bitmap);

      if (!estatus)
      {

         return false;

      }

      return bOk;

   }


   //bool image::draw(const ::point_i32 & pointDest, ::image * pimage, const ::rectangle_i32 & rectSrc)
   //{

   //   return m_pgraphics->draw(pointDest, pimage, rectSrc) != false;

   //}


   bool image::draw(const ::rectangle_i32 & rectDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam)
   {

      ::rectangle_i32 rectDst(rectDstParam);

      ::point_i32 pointSrc(pointSrcParam);

      ::size_i32 size(rectDst.size());

      ::image * pimageDst = this;

      if (pimageDst->m_bMapped && pimageSrc->m_bMapped)
      {

         rectDst += m_point;

         if (pointSrc.x < 0)
         {

            rectDst.left -= pointSrc.x;

            pointSrc.x = 0;

         }

         if (pointSrc.y < 0)
         {

            rectDst.top -= pointSrc.y;

            pointSrc.y = 0;

         }

         if (rectDst.left < 0)
         {

            size.cx += rectDst.left;

            pointSrc.x -= rectDst.left;

            rectDst.left = 0;

         }

         if (size.cx < 0)
         {

            return true;

         }

         if (rectDst.top < 0)
         {

            size.cy += rectDst.top;

            pointSrc.y -= rectDst.top;

            rectDst.top = 0;

         }

         if (size.cy < 0)
         {

            return true;

         }

         int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectDst.left));

         int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectDst.top));

         if (xEnd < 0)
         {

            return false;

         }

         if (yEnd < 0)
         {

            return false;

         }

         i32 scanDst = pimageDst->scan_size();

         i32 scanSrc = pimageSrc->scan_size();

         u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * rectDst.top + rectDst.left * sizeof(COLORREF)];

         u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(COLORREF)];

         COLORREF * pdst2;

         COLORREF * psrc2;

         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = (COLORREF *)&pdst[scanDst * y];

            psrc2 = (COLORREF *)&psrc[scanSrc * y];

            memcpy_dup(pdst2, psrc2, xEnd * 4);

         }

      }
      else
      {

         pimageDst->g()->draw(::rectangle_f64(rectDst.top_left(), size_i32 ), pimageSrc->g(), pointSrc);

      }

      return true;

   }


 /*  bool image::draw(const ::rectangle_i32 & rectDst, ::image * pimage, const ::point_i32 & pointSrc)
   {

      return ::image::draw(rectDst, pimage, pointSrc);

   }*/


   ::e_status image::SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy)
   {

      if (cx <= 0 || cy <= 0)
      {

         return error_invalid_parameter;

      }

      auto estatus = create({ cx, cy });

      if (!estatus)
      {

         return estatus;

      }

      // White blend image
      ::image_pointer pimage1;

      estatus = __construct(pimage1);

      if (!estatus)
      {

         return estatus;

      }
      
      estatus = pimage1->create({ cx, cy });

      if (!estatus)
      {

         return estatus;

      }



      pimage1->set_rgb(255, 255, 255);

      pimage1->g()->draw(::rect_dim(0, 0, cx, cy), picon);

      // Black blend image
      ::image_pointer pimage2;

      estatus = __construct(pimage2);
      
      if (!estatus)
      {

         return estatus;

      }

      estatus= pimage2->create( 
      { cx, cy } );

      if (!estatus)
      {

         return estatus;

      }

      pimage2->fill(0, 0, 0, 0);

      pimage2->g()->draw(::rect_dim(0, 0, cx, cy), picon);

      //nullptr,
      //DI_IMAGE | DI_MASK);

      // Mask image
      ::image_pointer pimageM;

      estatus = __construct(pimageM);

      if (!estatus)
      {

         return estatus;

      }

      estatus = pimageM->create(
         { cx, cy });

      if (!estatus)
      {

         return estatus;

      }

      pimageM->g()->draw(::rect_dim(0, 0, cx, cy), picon);

      u8 * r1 = (u8 *)pimage1->colorref();
      u8 * r2 = (u8 *)pimage2->colorref();
      u8 * srcM = (u8 *)pimageM->colorref();
      u8 * dest = (u8 *)colorref();
      i32 iSize = cx*cy;

      byte b;
      byte bMax;
      while (iSize-- > 0)
      {
         if (srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b = (byte)(r1[0] - r2[0]);
            bMax = maximum(b, bMax);
            b = (byte)(r1[1] - r2[1]);
            bMax = maximum(b, bMax);
            b = (byte)(r1[2] - r2[2]);
            bMax = maximum(b, bMax);
            bMax = 255 - bMax;
         }
         dest[0] = bMax;
         dest[1] = bMax;
         dest[2] = bMax;
         dest += 4;
         srcM += 4;
         r1 += 4;
         r2 += 4;
      }

      return ::success;

   }


   ::draw2d::graphics * image::_get_graphics() const
   {

      return m_pgraphics;

   }


   void image::draw2d_gdiplus_image_common_construct()
   {

      m_pbitmap.release();
      m_pgraphics.release();
      m_hbitmap               = nullptr;
      m_sizeWnd               = ::size_i64(0, 0);
      __zero(m_bitmapinfo);

   }


   bool image::_load_thumbnail(const char * psz)
   {

      ::Gdiplus::Graphics * pgraphics = (::Gdiplus::Graphics *)get_graphics()->get_os_data();

      wstring wstr(psz);

      // Create an image and a thumbnail of the pimage->
      ::Gdiplus::Image image(wstr);

      ap(::Gdiplus::Image) pthumbnail = (Gdiplus::Image *)image.GetThumbnailImage(width(), height(), nullptr, nullptr);

      // Draw the original and the thumbnail images.
      pgraphics->DrawImage(pthumbnail, 0, 0, pthumbnail->GetWidth(), pthumbnail->GetHeight());

      return true;

   }


   bool image::on_exif_orientation()
   {

      return ::image::on_exif_orientation();

   }


} // namespace draw2d_gdiplus



