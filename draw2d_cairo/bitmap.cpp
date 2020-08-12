#include "framework.h"


namespace draw2d_cairo
{


   bitmap::bitmap()
   {

      m_pthis = this;

      m_psurface = nullptr;

   }


   bitmap::~bitmap()
   {

      destroy();

   }


   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, i32 cx, i32 cy, UINT nPlanes, UINT nBitcount, const void * pdata, i32 iStrideParam)
   {

      sync_lock ml(cairo_mutex());

      cy = abs(cy);

      cx = abs(cx);

      if(nPlanes != 1 || nBitcount != 32)
      {

         ::exception::throw_not_implemented();

      }

      destroy();

      i32 iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cx);

      m_mem.set_size(iStride * cy);

      if(pdata == nullptr || iStrideParam <= 0)
      {

         __memset(m_mem.get_data(), 0, m_mem.get_size());

      }
      else
      {

         if(iStrideParam != iStride)
         {

            i32 iW = cx * 4;

            for(i32 i = 0; i < cy; i++)
            {

               ::memcpy_dup(&m_mem.get_data()[iStride * i], &((byte *) pdata)[iStrideParam * i], iW);

            }

         }
         else
         {

            ::memcpy_dup(m_mem.get_data(), pdata, iStride * cy);

         }

      }

      m_psurface = cairo_image_surface_create_for_data(m_mem.get_data(), CAIRO_FORMAT_ARGB32, cx, cy, iStride);

      if(m_psurface == nullptr)
      {

         return false;

      }

      m_osdata[0] = m_psurface;

      m_size.cx = cx;

      m_size.cy = cy;

      return true;

   }


   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap)
   {

      return false;

   }


   bool bitmap::CreateDIBSection(::draw2d::graphics * pgraphics, const ::size & size, UINT usage, void ** ppdata, int * pstride, HANDLE hSection, u32 offset)
   {

      try
      {

         sync_lock ml(cairo_mutex());

         destroy();

         ::i32 iScanWidth = -1;

         if(pstride)
         {

            iScanWidth = *pstride / sizeof(COLORREF);

         }

         if(iScanWidth < size.cx)
         {

            iScanWidth = size.cx;

         }

         ::i32 iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, iScanWidth);

#if MEMDLEAK

         m_mem.m_strTag = "image_section=" + __str(cx) + "x" + __str(size.ccy);

#endif

         m_mem.m_bAligned = true;

         m_mem.set_size(iStride * size.cy);

         if(*ppdata != nullptr)
         {

            if(size.cx * 4 != iStride)
            {

               i32 iW = size.cx * 4;

               for(i32 i = 0; i < size.cy; i++)
               {

                  ::memcpy_dup(&m_mem.get_data()[iStride * i], &((byte *) *ppdata)[iW * i], iW);

               }

            }
            else
            {

               ::memcpy_dup(m_mem.get_data(), *ppdata, iStride * size.cy);

            }

         }

         m_psurface = cairo_image_surface_create_for_data(m_mem.get_data(), CAIRO_FORMAT_ARGB32, size.cx, size.cy, iStride);

         int iSurfaceStatus = cairo_surface_status(m_psurface);

         if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
         {

            cairo_surface_destroy(m_psurface);

            m_psurface = nullptr;

            if(iSurfaceStatus == CAIRO_STATUS_INVALID_STRIDE)
            {

               iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, size.cx);

               m_psurface = cairo_image_surface_create_for_data(m_mem.get_data(), CAIRO_FORMAT_ARGB32, size.cx, size.cy, iStride);

               iSurfaceStatus = cairo_surface_status(m_psurface);

               if(iSurfaceStatus != CAIRO_STATUS_SUCCESS)
               {

                  cairo_surface_destroy(m_psurface);

                  m_psurface = nullptr;

                  return false;

               }

            }
            else
            {

               return false;

            }

         }

         if(ppdata != nullptr)
         {

            *ppdata = (COLORREF *) m_mem.get_data();

         }

         if(pstride != nullptr)
         {

            *pstride = iStride;

         }

         m_osdata[0] = m_psurface;

         m_size = size;

         return true;

      }
      catch(...)
      {

      }

      destroy();

      return false;

   }


   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, DWORD flInit, const void *pjBits, UINT iUsage)
   {

      return false;

   }


   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   {

      return 0;

   }


   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   {

      return false;

   }


   bool bitmap::LoadBitmap(const char * lpszResourceName)
   {

      return false;

   }


   size bitmap::SetBitmapDimension(i32 nWidth, i32 nHeight)
   {

      ::exception::throw_not_implemented();

      return ::size(0, 0);

   }


   size bitmap::GetBitmapDimension() const
   {

      if(m_psurface == nullptr)
      {

         return ::size(0, 0);

      }

      return m_size;

   }


   bool bitmap::LoadBitmap(UINT nIDResource)
   {

      return false;

   }


   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {

      return false;

   }


   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 cx, i32 cy)
   {

      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, nullptr, cx * sizeof(COLORREF)))
      {

         return false;

      }

      return true;

   }


   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight)
   {

      return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);

   }


   i32 bitmap::GetBitmap(BITMAP* pBitMap)
   {

      return 0;

   }


   void bitmap::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);

      dumpcontext << "\n";

   }


   void get_surface_size (cairo_surface_t * psurface, LONG * plongWidth, LONG * plongHeight)
   {

      sync_lock ml(cairo_mutex());

      if(plongWidth != nullptr)
      {

         *plongWidth = cairo_image_surface_get_width(psurface);

      }

      if(plongHeight != nullptr)
      {

         *plongHeight = cairo_image_surface_get_height(psurface);

      }

   }


   bool bitmap::attach(void * psurface)
   {

      sync_lock ml(cairo_mutex());

      destroy();

      m_psurface = (cairo_surface_t *) psurface;

      get_surface_size((cairo_surface_t *) psurface, &m_size.cx, &m_size.cy);

      m_osdata[0] = m_psurface;

      return true;

   }


   void bitmap::destroy()
   {

      sync_lock ml(cairo_mutex());

      if (m_psurface == nullptr)
      {

         return;

      }

      cairo_surface_destroy(m_psurface);

      m_psurface = nullptr;

      ::draw2d::bitmap::destroy();

   }


} // namespace draw2d_cairo



