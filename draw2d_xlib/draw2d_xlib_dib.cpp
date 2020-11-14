#include "framework.h"
#include <math.h>


namespace draw2d_xlib
{


   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////




   image::image_pointer(::layered * pobjectContext) :
      ::object(pobject),
      m_pbitmap(e_create),
      m_spgraphics(e_create)
   {

      m_pcolorref          = nullptr;
      m_bMapped            = false;
      m_pimage             = nullptr;

   }

   color32_t * pimage::get_data()
   {
      return m_pcolorref;
   }
   ::draw2d::bitmap_pointer image::get_bitmap()
   {
      return m_pbitmap;
   }

   ::draw2d::bitmap_pointer image::detach_bitmap()
   {
      return m_pbitmap.detach();
   }


   void image::read(stream & istream)
   {

      image::read(istream);

//      xlib_surface_t * surface = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p)->m_psurface;

      //    xlib_surface_mark_dirty (surface);

   }

   void    image::construct (i32 cx,  i32 cy)
   {

      m_pcolorref    = nullptr;
      cx             = 0;
      cy             = 0;

      create(cx, cy);

   }

   image::~image ()
   {
//      Destroy ();
   }

   bool image::create(::size size)
   {
      return create(size.cx, size.cy);
   }

   bool image::create(i32 width, i32 height)
   {
      if(m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && m_spgraphics.is_set()
            && m_spgraphics->get_os_data() != nullptr
            && width == m_size.cx
            && height == m_size.cy)
         return true;

      Destroy();

      if(width <= 0 || height <= 0)
         return FALSE;

      __memset(&m_info, 0, sizeof (BITMAPINFO));

      m_info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      m_info.bmiHeader.biWidth         = width;
      m_info.bmiHeader.biHeight        =- height;
      m_info.bmiHeader.biPlanes        = 1;
      m_info.bmiHeader.biBitCount      = 32;
      m_info.bmiHeader.biCompression   = BI_RGB;
      m_info.bmiHeader.biSizeImage     = width * height * 4;

      m_bMapped = false;

      m_pbitmap.create(this);
      m_spgraphics.create(this);

      if(m_pbitmap.m_p == nullptr)
      {
         m_size.cx = 0;
         m_size.cy = 0;
         m_iScan = 0;
         return FALSE;
      }

      if(!m_pbitmap->CreateDIBSection(nullptr, &m_info, DIB_RGB_COLORS, (void **) &m_pcolorref, &m_iScan, nullptr, 0))
      {
         m_size.cx = 0;
         m_size.cy = 0;
         m_iScan = 0;
         return FALSE;
      }


      if(m_pbitmap->get_os_data() != nullptr)
      {
         //m_spgraphics->CreateCompatibleDC(nullptr);
         ::draw2d::bitmap * pbitmap = m_spgraphics->SelectObject(m_pbitmap);
         //m_hbitmapOriginal
         /*if(pbitmap == nullptr || pbitmap->get_os_data() == nullptr)
         {
            Destroy();
            return FALSE;
         }
         ((Gdiplus::Bitmap *)pbitmap->get_os_data())->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &m_hbitmapOriginal);*/
         m_size.cx = width;
         m_size.cy = height;
         return TRUE;
      }
      else
      {
         Destroy();
         return FALSE;
      }
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

   bool image::create(::image * pimage)
   {
      ::draw2d::bitmap * pbitmap = (dynamic_cast < ::draw2d_xlib::graphics * > (pgraphics))->get_current_bitmap();
      if(pbitmap == nullptr)
         return FALSE;
      ::size size = pbitmap->get_size();
      if(!create(size.cx, size.cy))
      {
         return FALSE;
      }
      from(pgraphics);
      return TRUE;
   }

   bool image::Destroy ()
   {

      if(m_pimage != nullptr)
      {
         m_ppimage->data = nullptr;
         XDestroyImage(m_pimage);
         m_pimage = nullptr;
      }

      m_pbitmap.release();


      m_spgraphics.release();

      m_size.cx               = 0;
      m_size.cy               = 0;
      m_pcolorref             = nullptr;
      m_bMapped               = false;

      return TRUE;
   }

   bool image::to(::draw2d::graphics * pgraphics, const ::point & point, ::size size, const ::point & pointSrc)
   {

      return pgraphics->BitBlt(point.x, point.y, size.cx, size.cy, get_graphics(), pointSrc.x, pointSrc.y) != FALSE;

      /*  return SetDIBitsToDevice(
           (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(),
           point.x, point.y,
           size.cx, size.cy,
           pointSrc.x, pointSrc.y, pointSrc.y, cy - pointSrc.y,
           m_pcolorref, &m_info, 0)
              != FALSE; */

   }

   bool image::from(::image * pimage)
   {
      ::draw2d::bitmap_pointer bitmap(get_object());
      bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);
      ::draw2d::bitmap * pbitmap = pgraphics->SelectObject(bitmap);
      if(pbitmap == nullptr)
         return false;
      ::size size = pbitmap->get_size();
      if(!create(size))
      {
         pgraphics->SelectObject(pbitmap);
         return false;
      }
      __throw(todo());
      // xxx bool bOk = GetDIBits(LNX_HDC(pgraphics), (HBITMAP) pbitmap->get_os_data(), 0, cy, m_pcolorref, &(m_info), DIB_RGB_COLORS) != FALSE;
      // xxx pgraphics->SelectObject(pbitmap);
      // xxx return bOk;
   }

   bool image::from(point ptDest, ::draw2d::graphics * pgraphics, const ::point & point, ::size sz)
   {
      return m_spgraphics->BitBlt(ptDest.x, ptDest.y, sz.cx, sz.cy, pgraphics, point.x, point.y) != FALSE;
   }

   //void image::Fill ( i32 R, i32 G, i32 B )
   //{
   //   color32_t color=RGB ( B, G, R );
   //   i32 size=cx*cy;

   //   color32_t * pcr;

   //   i32 iSize32 = size / 32;
   //   i32 i;
   //   for (i=0; i < iSize32; i+=32 )
   //   {
   //      pcr = &m_pcolorref[i];
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
   //      m_pcolorref[i]=color;
   //   }
   //}

   //void image::set_rgb(i32 R, i32 G, i32 B)
   //{

   //   map();

   //   i32 size = scan*cy;

   //   byte * pbyte = (byte *) m_pcolorref;

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
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[3] = dst[i];
   //      dst+=4;
   //   }
   //}

   //void image::from_alpha()
   //{
   //   byte *dst=(byte*)m_pcolorref;
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

   //void image::mult_alpha(::image * pimageWork, bool bPreserveAlpha)
   //{
   //   image::mult_alpha(imageWork, bPreserveAlpha);
   //   return ;
   //   /*
   //   if(area() <= 0)
   //      return;

   //   //return image::mult_alpha(nullptr, true);
   //   ::image_pointer pimageWork;

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


   void image::map(bool bApplyAlphaTransform)
   {

      if(m_bMapped)
         return;

      if(m_pcolorref == nullptr)
         return;

      if(m_pbitmap.m_p == nullptr)
         return;

      ::draw2d_xlib::bitmap * pb = m_pbitmap.cast < ::draw2d_xlib::bitmap >();

//      m_pimage = XGetImage(
//                     pb->m_ui.m_window->display(),
//                     pb->m_pixmap,
//                     0, 0,
//                     m_size.cx, m_size.cy,
//                     -1,
//                     ZPixmap);

      ::memcpy_dup(m_pcolorref, m_ppimage->data, m_iScan * m_size.cy);

      m_bMapped = true;

   }

   void image::unmap()
   {

      if(!m_bMapped)
         return;

      if(m_pcolorref == nullptr)
         return;

      if(m_pbitmap.m_p == nullptr)
         return;

      ::draw2d_xlib::bitmap * pb = m_pbitmap.cast < ::draw2d_xlib::bitmap >();

      ::draw2d_xlib::graphics * pg = m_spgraphics.cast < ::draw2d_xlib::graphics >();

      ::memcpy_dup(m_ppimage->data, m_pcolorref, m_iScan * m_size.cy);

//      XPutImage(
//                     pb->m_ui.m_window->display(),
//                     pb->m_pixmap,
//                     pg->m_pdc->m_gc,
//                     m_pimage,
//                     0, 0,
//                     0, 0,
//                     m_size.cx, m_size.cy);

      XDestroyImage(m_pimage);

      m_pimage = nullptr;

      m_bMapped = false;

   }

   //void image::Map(i32 ToRgb, i32 FromRgb)
   //{
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      *dst = (byte) (*dst == FromRgb ? ToRgb : *dst);
   //      dst+=4;
   //   }
   //}


   //void image::ToAlphaAndFill(i32 i, color32_t cr)
   //{
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   byte uchB = ::blue(cr);
   //   byte uchG = ::green(cr);
   //   byte uchR = ::red(cr);

   //   while ( size-- )
   //   {
   //      dst[3] = dst[i];
   //      dst[0] = uchB;
   //      dst[1] = uchG;
   //      dst[2] = uchR;
   //      dst+=4;
   //   }
   //}

   //void image::GrayToARGB(color32_t cr)
   //{
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   u32 dwB = ::blue(cr);
   //   u32 dwG = ::green(cr);
   //   u32 dwR = ::red(cr);

   //   while (size-- > 0)
   //   {
   //      dst[3] = dst[0];
   //      dst[0] = (byte)(((dwB * dst[3]) / 256) & 0xff);
   //      dst[1] = (byte)(((dwG * dst[3]) / 256) & 0xff);
   //      dst[2] = (byte)(((dwR * dst[3]) / 256) & 0xff);
   //      dst+=4;
   //   }
   //}


   //void image::BitBlt(imagepimage, i32 op)
   //{
   //   if(op == 123) // zero dest RGB, invert alpha, and OR src RGB
   //   {
   //      i32 isize=cx*cy;
   //      LPDWORD lpbitsSrc= (LPDWORD) pimage->get_data();
   //      LPDWORD lpbitsDest= (LPDWORD) m_pcolorref;

   //      color32_t _colorref = RGB ( 0, 0, 0 ) | (255 << 24);
   //      color32_t colorrefa[2];
   //      colorrefa[0] = _colorref;
   //      colorrefa[1] = _colorref;

   //      color32_t _colorrefN = RGB ( 255, 255, 255) | (0 << 24);
   //      color32_t colorrefaN[2];
   //      colorrefaN[0] = _colorrefN;
   //      colorrefaN[1] = _colorrefN;
   //#if defined(AMD64) || defined(ANDROID)

   //      //x64
   //#else
   //      _asm
   //      {
   //         emms
   //         mov      eax, isize
   //         mov      ebx, lpbitsDest
   //         mov      ecx, lpbitsSrc
   //         movq     mm0, colorrefa
   //         movq     mm7, colorrefaN
   //   fill_loop:
   //         cmp      eax, 1
   //         jle      fill_last
   //         movq     mm1, [ebx]
   //         movq     mm2, [ecx]
   //         pandn    mm1, mm0
   //         pand     mm2, mm7
   //         por      mm1, mm2
   //         movq     [ebx], mm1

   //         sub      eax, 2
   //         add      ebx, 8
   //         add      ecx, 8

   //         jmp      fill_loop

   //   fill_last:
   //         emms
   //      }
   //#endif
   //   }

   //}


   //void image::Invert()
   //{
   //   i32 size=cx*cy;
   //   byte * lpb = (byte *) m_pcolorref;
   //   for ( i32 i=0; i<size; i++ )
   //   {
   //      lpb[0] = 255 - lpb[0];
   //      lpb[1] = 255 - lpb[1];
   //      lpb[2] = 255 - lpb[2];
   //      lpb += 4;
   //   }
   //}

   //void image::color::channel_invert(color::color::rgba::echannel echannel)
   //{
   //   i64 size   = cx * cy;
   //   register i64 size64 = size / 64;
   //   byte * lpb = (byte *) m_pcolorref;
   //   lpb += ((i32)echannel) % 4;
   //   register i64 i = 0;
   //   for(; i < size64; i++)
   //   {
   //      lpb[4 *  0] = 255 - lpb[4 *  0];
   //      lpb[4 *  1] = 255 - lpb[4 *  1];
   //      lpb[4 *  2] = 255 - lpb[4 *  2];
   //      lpb[4 *  3] = 255 - lpb[4 *  3];
   //      lpb[4 *  4] = 255 - lpb[4 *  4];
   //      lpb[4 *  5] = 255 - lpb[4 *  5];
   //      lpb[4 *  6] = 255 - lpb[4 *  6];
   //      lpb[4 *  7] = 255 - lpb[4 *  7];
   //      lpb[4 *  8] = 255 - lpb[4 *  8];
   //      lpb[4 *  9] = 255 - lpb[4 *  9];
   //      lpb[4 * 10] = 255 - lpb[4 * 10];
   //      lpb[4 * 11] = 255 - lpb[4 * 11];
   //      lpb[4 * 12] = 255 - lpb[4 * 12];
   //      lpb[4 * 13] = 255 - lpb[4 * 13];
   //      lpb[4 * 14] = 255 - lpb[4 * 14];
   //      lpb[4 * 15] = 255 - lpb[4 * 15];
   //      lpb[4 * 16] = 255 - lpb[4 * 16];
   //      lpb[4 * 17] = 255 - lpb[4 * 17];
   //      lpb[4 * 18] = 255 - lpb[4 * 18];
   //      lpb[4 * 19] = 255 - lpb[4 * 19];
   //      lpb[4 * 20] = 255 - lpb[4 * 20];
   //      lpb[4 * 21] = 255 - lpb[4 * 21];
   //      lpb[4 * 22] = 255 - lpb[4 * 22];
   //      lpb[4 * 23] = 255 - lpb[4 * 23];
   //      lpb[4 * 24] = 255 - lpb[4 * 24];
   //      lpb[4 * 25] = 255 - lpb[4 * 25];
   //      lpb[4 * 26] = 255 - lpb[4 * 26];
   //      lpb[4 * 27] = 255 - lpb[4 * 27];
   //      lpb[4 * 28] = 255 - lpb[4 * 28];
   //      lpb[4 * 29] = 255 - lpb[4 * 29];
   //      lpb[4 * 30] = 255 - lpb[4 * 30];
   //      lpb[4 * 31] = 255 - lpb[4 * 31];

   //      lpb[4 * 32] = 255 - lpb[4 * 32];
   //      lpb[4 * 33] = 255 - lpb[4 * 33];
   //      lpb[4 * 34] = 255 - lpb[4 * 34];
   //      lpb[4 * 35] = 255 - lpb[4 * 35];
   //      lpb[4 * 36] = 255 - lpb[4 * 36];
   //      lpb[4 * 37] = 255 - lpb[4 * 37];
   //      lpb[4 * 38] = 255 - lpb[4 * 38];
   //      lpb[4 * 39] = 255 - lpb[4 * 39];
   //      lpb[4 * 40] = 255 - lpb[4 * 40];
   //      lpb[4 * 41] = 255 - lpb[4 * 41];
   //      lpb[4 * 42] = 255 - lpb[4 * 42];
   //      lpb[4 * 43] = 255 - lpb[4 * 43];
   //      lpb[4 * 44] = 255 - lpb[4 * 44];
   //      lpb[4 * 45] = 255 - lpb[4 * 45];
   //      lpb[4 * 46] = 255 - lpb[4 * 46];
   //      lpb[4 * 47] = 255 - lpb[4 * 47];
   //      lpb[4 * 48] = 255 - lpb[4 * 48];
   //      lpb[4 * 49] = 255 - lpb[4 * 49];
   //      lpb[4 * 50] = 255 - lpb[4 * 50];
   //      lpb[4 * 51] = 255 - lpb[4 * 51];
   //      lpb[4 * 52] = 255 - lpb[4 * 52];
   //      lpb[4 * 53] = 255 - lpb[4 * 53];
   //      lpb[4 * 54] = 255 - lpb[4 * 54];
   //      lpb[4 * 55] = 255 - lpb[4 * 55];
   //      lpb[4 * 56] = 255 - lpb[4 * 56];
   //      lpb[4 * 57] = 255 - lpb[4 * 57];
   //      lpb[4 * 58] = 255 - lpb[4 * 58];
   //      lpb[4 * 59] = 255 - lpb[4 * 59];
   //      lpb[4 * 60] = 255 - lpb[4 * 60];
   //      lpb[4 * 61] = 255 - lpb[4 * 61];
   //      lpb[4 * 62] = 255 - lpb[4 * 62];
   //      lpb[4 * 63] = 255 - lpb[4 * 63];

   //      lpb += 4 * 64;
   //   }
   //   i *= 64;
   //   for(; i < size; i++ )
   //   {
   //      *lpb = 255 - *lpb;
   //      lpb += 4;
   //   }
   //}
   //void image::color::channel_multiply(color::color::rgba::echannel echannel, double dRate)
   //{
   //   if(dRate < 0)
   //      return;
   //   register i64 size = area();
   //   byte * lpb = (byte *) get_data();
   //   lpb += ((i32)echannel) % 4;
   //   register i32 iDiv = 256 * 256;
   //   register i32 iMul = (i32) (dRate * ((double) iDiv));
   //   register i32 iRes;
   //   for(register i64 i = 0; i < size; i++)
   //   {
   //      iRes = *lpb * iMul / iDiv;
   //      *lpb = (byte) (iRes > 255 ? 255 : iRes);
   //      lpb += 4;
   //   }
   //}

   //void image::FillGlass ( i32 R, i32 G, i32 B, i32 A )
   //{
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)(((B-dst[0])*A+(dst[0]<<8))>>8);
   //      dst[1]=(byte)(((G-dst[1])*A+(dst[1]<<8))>>8);
   //      dst[2]=(byte)(((R-dst[2])*A+(dst[2]<<8))>>8);
   //      dst+=4;
   //   }
   //}

   //void image::FillStippledGlass ( i32 R, i32 G, i32 B )
   //{
   //   color32_t color=RGB ( B, G, R );
   //   i32 w=cx;
   //   i32 h=cy;

   //   for ( i32 j=0; j<w; j++ )
   //   {
   //      for ( i32 i=0; i<h; i++ )
   //      {
   //         m_pcolorref[j*w+i]=((i+j)&0x1) ? m_pcolorref[j*w+i] : color;
   //      }
   //   }
   //}

   //void image__copy(::image * pimage)
   //{
   //   // If DibSize Wrong Re-create image
   //   if ( (pimage->cx!=cx) || (pimage->cy!=cy) )
   //      pimage = create_image ( cx, cy );
   //   // do copy
   //   ::memcpy_dup ( pimage->get_data(), m_pcolorref, cx*cy*4 );
   //}


   //void image::Paste ( ::image_pointer pimage )
   //{
   //   // If DibSize Wrong Re-create image
   //   if ( (cx!=pimage->cx) || (cy!=pimage->cy) )
   //      create ( pimage->cx, pimage->cy );
   //   // do Paste
   //   ::memcpy_dup ( m_pcolorref, pimage->get_data(), cx*cy*4 );
   //}

   //bool image::color_blend(color32_t cr, byte bAlpha)
   //{

   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   u32 dwB = ::blue(cr);
   //   u32 dwG = ::green(cr);
   //   u32 dwR = ::red(cr);

   //   u32 dwB_ = dwB << 8;
   //   u32 dwG_ = dwG << 8;
   //   u32 dwR_ = dwR << 8;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)(((dst[0]-dwB)*bAlpha+dwB_)>>8);
   //      dst[1]=(byte)(((dst[1]-dwG)*bAlpha+dwG_)>>8);
   //      dst[2]=(byte)(((dst[2]-dwG)*bAlpha+dwR_)>>8);
   //      dst+=4;
   //   }
   //   return true;
   //}


   //void image::Blend (::image * pimage, i32 A )
   //{
   //   if ( size()!=pimage->size() )
   //      return;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
   //      dst[1]=(byte)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
   //      dst[2]=(byte)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //bool image::Blend(imagepimage, imagepimageA, i32 A)
   //{
   //   if(size() != pimage->size() ||
   //      size() != imageA.size())
   //      return false;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   byte *alf=(byte*)imageA.m_pcolorref;
   //   i32 size=cx*cy;

   //   A = 2 - A;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)(((src[0]-dst[0])*alf[A]+(dst[0]<<8))>>8);
   //      dst[1]=(byte)(((src[1]-dst[1])*alf[A]+(dst[1]<<8))>>8);
   //      dst[2]=(byte)(((src[2]-dst[2])*alf[A]+(dst[2]<<8))>>8);
   //      dst+=4;
   //      src+=4;
   //      alf+=4;
   //   }

   //   return true;
   //}

   //void image::Darken (::image * pimage )
   //{
   //   if ( size()!=pimage->size() )
   //      return;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)((src[0]<dst[0]) ? src[0] : dst[0]);
   //      dst[1]=(byte)((src[1]<dst[1]) ? src[1] : dst[1]);
   //      dst[2]=(byte)((src[2]<dst[2]) ? src[2] : dst[2]);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Difference (::image * pimage )
   //{
   //   if ( size()!=pimage->size() )
   //      return;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      i32 Difference;
   //      Difference=src[0]-dst[0];
   //      dst[0]=(byte)((Difference<0) ? -Difference : Difference);
   //      Difference=src[1]-dst[1];
   //      dst[1]=(byte)((Difference<0) ? -Difference : Difference);
   //      Difference=src[2]-dst[2];
   //      dst[2]=(byte)((Difference<0) ? -Difference : Difference);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Lighten (::image * pimage )
   //{
   //   if ( size()!=pimage->size() )
   //      return;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)((src[0]>dst[0]) ? src[0] : dst[0]);
   //      dst[1]=(byte)((src[1]>dst[1]) ? src[1] : dst[1]);
   //      dst[2]=(byte)((src[2]>dst[2]) ? src[2] : dst[2]);
   //      dst+=4;
   //      src+=4;
   //   }
   //}


   //void image::Multiply (::image * pimage )
   //{
   //   if ( size()!=pimage->size() )
   //      return;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)(((src[0])*(dst[0]))>>8);
   //      dst[1]=(byte)(((src[1])*(dst[1]))>>8);
   //      dst[2]=(byte)(((src[2])*(dst[2]))>>8);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Screen (::image * pimage )
   //{
   //   if ( size()!=pimage->size() )
   //      return;

   //   byte *src=(byte*)pimage->get_data();
   //   byte *dst=(byte*)m_pcolorref;
   //   i32 size=cx*cy;

   //   while ( size-- )
   //   {
   //      dst[0]=(byte)(255-(((255-src[0])*(255-dst[0]))>>8));
   //      dst[1]=(byte)(255-(((255-src[1])*(255-dst[1]))>>8));
   //      dst[2]=(byte)(255-(((255-src[2])*(255-dst[2]))>>8));
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //////////////////////////////////////////////////////////////////////
   // Rectangle Functions
   //////////////////////////////////////////////////////////////////////

   //void image::copy (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to copy return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;
   //   // If DibSize Wrong Re-create image
   //   if ( (dx!=pimage->cx) || (dy!=pimage->cy) )
   //      pimage = create_image ( dx, dy );

   //   // Prepare buffer Addresses
   //   color32_t *src=m_pcolorref+(py*cx)+px;
   //   color32_t *dst=pimage->get_data();

   //   // Do copy
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //         dst[i]=src[i];
   //      src+=cx;
   //      dst+=pimage->cx;
   //   }
   //}

   //void image::PasteRect (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Paste return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   color32_t *src=pimage->get_data()+((py-y)*pimage->cx)+px-x;
   //   color32_t *dst=m_pcolorref+(py*cx)+px;

   //   // Do Paste
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //         dst[i]=src[i];
   //      src+=pimage->cx;
   //      dst+=cx;
   //   }
   //}

   //void image::FillRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+w)<cx) ? w : cx-x;
   //   i32 dy=((y+h)<cy) ? h : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Fill return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   color32_t *dst=m_pcolorref+(py*cx)+px;
   //   color32_t color=RGB ( B, G, R );

   //   // Do Fill
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[i]=color;
   //      }
   //      dst+=cx;
   //   }
   //}

   //void image::FillGlassRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B, i32 A )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+w)<cx) ? w : cx-x;
   //   i32 dy=((y+h)<cy) ? h : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to FillGlass return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do FillGlass
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[0]=(byte)(((B-dst[0])*A+(dst[0]<<8))>>8);
   //         dst[1]=(byte)(((G-dst[1])*A+(dst[1]<<8))>>8);
   //         dst[2]=(byte)(((R-dst[2])*A+(dst[2]<<8))>>8);
   //         dst+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //   }
   //}

   //void image::FillStippledGlassRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+w)<cx) ? w : cx-x;
   //   i32 dy=((y+h)<cy) ? h : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to FillStippledGlass return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   color32_t *dst=m_pcolorref+(py*cx)+px;
   //   color32_t color=RGB ( B, G, R );

   //   // Do FillStippledGlass
   //   for ( i32 j=0; j<dy; j++ )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[i]=((i+j)&0x1) ? dst[i] : color;
   //      }
   //      dst+=cx;
   //   }
   //}

   //void image::BlendRect (::image * pimage, i32 x, i32 y, i32 A )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Blend return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   byte *src=(byte *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Blend
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[0]=(byte)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
   //         dst[1]=(byte)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
   //         dst[2]=(byte)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //      src+=(pimage->cx-dx)<<2;
   //   }
   //}

   //void image::DarkenRect (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Darken return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   byte *src=(byte *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Darken
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[0]=(byte)((src[0]<dst[0]) ? src[0] : dst[0]);
   //         dst[1]=(byte)((src[1]<dst[1]) ? src[1] : dst[1]);
   //         dst[2]=(byte)((src[2]<dst[2]) ? src[2] : dst[2]);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //      src+=(pimage->cx-dx)<<2;
   //   }
   //}

   //void image::DifferenceRect (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Difference return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   byte *src=(byte *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Difference
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         i32 Difference;
   //         Difference=src[0]-dst[0];
   //         dst[0]=(byte)((Difference<0) ? -Difference : Difference);
   //         Difference=src[1]-dst[1];
   //         dst[1]=(byte)((Difference<0) ? -Difference : Difference);
   //         Difference=src[2]-dst[2];
   //         dst[2]=(byte)((Difference<0) ? -Difference : Difference);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //      src+=(pimage->cx-dx)<<2;
   //   }
   //}

   //void image::LightenRect (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Lighten return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   byte *src=(byte *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Lighten
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[0]=(byte)((src[0]>dst[0]) ? src[0] : dst[0]);
   //         dst[1]=(byte)((src[1]>dst[1]) ? src[1] : dst[1]);
   //         dst[2]=(byte)((src[2]>dst[2]) ? src[2] : dst[2]);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //      src+=(pimage->cx-dx)<<2;
   //   }
   //}

   //void image::MultiplyRect (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Multiply return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   byte *src=(byte *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Multiply
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[0]=(byte)(((src[0])*(dst[0]))>>8);
   //         dst[1]=(byte)(((src[1])*(dst[1]))>>8);
   //         dst[2]=(byte)(((src[2])*(dst[2]))>>8);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //      src+=(pimage->cx-dx)<<2;
   //   }
   //}

   //void image::ScreenRect (::image * pimage, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 dx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   i32 dy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   dx=(x>=0) ? dx : dx + x;
   //   dy=(y>=0) ? dy : dy + y;

   //   // If Nothing to Screen return
   //   if ( (dx<=0) || (dy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   byte *src=(byte *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   byte *dst=(byte *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Screen
   //   while ( dy-- )
   //   {
   //      for ( i32 i=0; i<dx; i++ )
   //      {
   //         dst[0]=(byte)(255-(((255-src[0])*(255-dst[0]))>>8));
   //         dst[1]=(byte)(255-(((255-src[1])*(255-dst[1]))>>8));
   //         dst[2]=(byte)(255-(((255-src[2])*(255-dst[2]))>>8));
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-dx)<<2;
   //      src+=(pimage->cx-dx)<<2;
   //   }
   //}

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void image::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
   {
      i32 dx, dy, k1, k2, d, x, y;
      color32_t color=RGB ( B, G, R );

      dx=x2-x1;
      dy=y2-y1;
      d=(dy<<1)-dx;
      k1=dy<<1;
      k2=(dy-dx)<<1;
      x=x1;
      y=y1;

      m_pcolorref[y*cx+x]=color;
      while (x<dx)
      {
         if (d<=0)
         {
            d+=k1;
            x++;
         }
         else
         {
            d+=k2;
            x++;
            y++;
         }
         m_pcolorref[y*cx+x]=color;
      }
   }*/

//   void image::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
//   {
//      i32 d, x, y, ax, ay, sx, sy, dx, dy;
//      color32_t color=RGB ( B, G, R );
//
//      dx=x2-x1;
//      ax=abs ( dx )<<1;
//      sx=(dx<0) ? -1 : 1;
//      dy=y2-y1;
//      ay=abs ( dy )<<1;
//      sy=(dy<0) ? -1 : 1;
//      x=x1;
//      y=y1;
//
//      if ( ax>ay )
//      {
//         d=ay-(ax>>1);
//         while ( x!=x2 )
//         {
//            m_pcolorref[y*cx+x]=color;
//            if ( d>=0 )
//            {
//               y+=sy;
//               d-=ax;
//            }
//            x+=sx;
//            d+=ay;
//         }
//      }
//      else
//      {
//         d=ax-(ay>>1);
//         while ( y!=y2 )
//         {
//            m_pcolorref[y*cx+x]=color;
//            if ( d>=0 )
//            {
//               x+=sx;
//               d-=ay;
//            }
//            y+=sy;
//            d+=ax;
//         }
//      }
//   }
//
//   void image::LineGlass ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A )
//   {
//      i32 d, x, y, ax, ay, sx, sy, dx, dy;
////      color32_t color=RGB ( B, G, R );
//      byte *dst=(byte *)m_pcolorref;
//
//      dx=x2-x1;
//      ax=abs ( dx )<<1;
//      sx=(dx<0) ? -1 : 1;
//      dy=y2-y1;
//      ay=abs ( dy )<<1;
//      sy=(dy<0) ? -1 : 1;
//      x=x1;
//      y=y1;
//
//      if ( ax>ay )
//      {
//         d=ay-(ax>>1);
//         while ( x!=x2 )
//         {
//            dst[(y*cx+x)<<2]=(byte)(((B-dst[(y*cx+x)<<2])*A+(dst[(y*cx+x)<<2]<<8))>>8);
//            dst[((y*cx+x)<<2)+1]=(byte)(((G-dst[((y*cx+x)<<2)+1])*A+(dst[((y*cx+x)<<2)+1]<<8))>>8);
//            dst[((y*cx+x)<<2)+2]=(byte)(((R-dst[((y*cx+x)<<2)+2])*A+(dst[((y*cx+x)<<2)+2]<<8))>>8);
//            if ( d>=0 )
//            {
//               y+=sy;
//               d-=ax;
//            }
//            x+=sx;
//            d+=ay;
//         }
//      }
//      else
//      {
//         d=ax-(ay>>1);
//         while ( y!=y2 )
//         {
//            dst[(y*cx+x)<<2]=(byte)(((B-dst[(y*cx+x)<<2])*A+(dst[(y*cx+x)<<2]<<8))>>8);
//            dst[((y*cx+x)<<2)+1]=(byte)(((G-dst[((y*cx+x)<<2)+1])*A+(dst[((y*cx+x)<<2)+1]<<8))>>8);
//            dst[((y*cx+x)<<2)+2]=(byte)(((R-dst[((y*cx+x)<<2)+2])*A+(dst[((y*cx+x)<<2)+2]<<8))>>8);
//            if ( d>=0 )
//            {
//               x+=sx;
//               d-=ay;
//            }
//            y+=sy;
//            d+=ax;
//         }
//      }
//   }
//
//   void image::Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask)
//   {
//      color32_t crFind = RGB(::blue(crMask), ::green(crMask), ::red(crMask));
//      color32_t crSet = RGB(::blue(crInMask), ::green(crInMask), ::red(crInMask));
//      color32_t crUnset  = RGB(::blue(crOutMask), ::green(crOutMask), ::red(crOutMask));
//
//      i32 size=cx*cy;
//
//      for ( i32 i=0; i<size; i++ )
//         if(m_pcolorref[i]== crFind)
//            m_pcolorref[i] = crSet;
//         else
//            m_pcolorref[i] = crUnset;
//
//   }
//
//   void image::transparent_color(color color)
//   {
//      color32_t crFind = color.get_rgb();
//      i64 size = area();
//
//      for ( i32 i=0; i<size; i++ )
//         if((m_pcolorref[i] & 0x00ffffff) == crFind)
//            ((byte *)&m_pcolorref[i])[3] = 255;
//         else
//            ((byte *)&m_pcolorref[i])[3] = 0;
//   }
//
//   void image::color::channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, color::color::rgba::echannel echannel)
//   {
//      i32 size = cx * cy;
//      unsigned char * puch = (unsigned char * ) m_pcolorref;
//      puch += ((i32) echannel) % 4;
//
//      for(i32 i = 0; i < size; i++)
//      {
//         if(*puch == uchFind)
//            *puch = uchSet;
//         else
//            *puch = uchUnset;
//         puch += 4;
//      }
//   }
//
//   u32 image::GetPixel(i32 x, i32 y)
//   {
//      u32 dw = *(m_pcolorref + x + (cy - y - 1) * cx);
//      return RGB(::blue(dw), ::green(dw), ::red(dw));
//   }
//
//   // too slow for animation on AMD XP gen_hon.
//   // TOP SUGGESTION:
//   // The gradient can\B4t have more then 256 levels of the most bright color
//   // (white). So creating a radial fill of radius 256 and then using fasting
//   // stretching algorithms is much faster than calculating radial fill.
//   void image::RadialFill(byte alpha, byte red, byte green, byte blue, i32 xCenter, i32 yCenter, i32 iRadius)
//   {
//      if (iRadius == 0)
//         return;
//      /*if(version == 0)
//      {
//
//         i32 iR = iRadius - 1;
//
//         i32 xL = xCenter - iR;
//         i32 xU = xCenter + iR;
//         i32 yL = yCenter - iR;
//         i32 yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= m_Size.cx) xU = m_Size.cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= m_Size.cy) yU = m_Size.cy - 1;
//
//
//         byte *dst = ((byte*)(m_pcolorref + xL + yL * m_Size.cx));
//         u32 dwAdd = ((m_Size.cx - 1 - xU) + xL) * 4;
//         i32 size=m_Size.cx*m_Size.cy;
//         double iLevel;
//
//         i32 dx, dy;
//         i32 dx0, dy0;
//         i32 dx1, dy1;
//         i32 dx2, dy2;
//         i32 dx3, dy3;
//         i32 dx4, dy4;
//         i32 dx5, dy5;
//         i32 dx6, dy6;
//         i32 dx7, dy7;
//         i32 dx8, dy8;
//         i32 dx9, dy9;
//         i32 dxA, dyA;
//         i32 dxB, dyB;
//         i32 dxC, dyC;
//         i32 dxD, dyD;
//         i32 dxE, dyE;
//         i32 dxF, dyF;
//
//         unsigned long dr;
//         unsigned long dq;
//         unsigned long dr0, dq0;
//         unsigned long dr1, dq1;
//         unsigned long dr2, dq2;
//         unsigned long dr3, dq3;
//         unsigned long dr4, dq4;
//         unsigned long dr5, dq5;
//         unsigned long dr6, dq6;
//         unsigned long dr7, dq7;
//         unsigned long dr8, dq8;
//         unsigned long dr9, dq9;
//         unsigned long drA, dqA;
//         unsigned long drB, dqB;
//         unsigned long drC, dqC;
//         unsigned long drD, dqD;
//         unsigned long drE, dqE;
//         unsigned long drF, dqF;
//         i32 x, y;
//
//         {
//            for(y = yL; y <= yU; y++)
//            {
//               for(x = xL; x <= xU; x++)
//               {
//                  dx = abs(x - xCenter);
//                  dy = abs(y - yCenter);
//                  isqrt((dx * dx) + (dy * dy), &dr, &dq);
//                  if(dr < iRadius)
//                  {
//                     iLevel = 1.0 - dr * 1.0 / iRadius;
//                     dst[0] = blue  * iLevel;
//                     dst[1] = green * iLevel;
//                     dst[2] = red   * iLevel;
//                  }
//                  dst += 4;
//               }
//               dst += dwAdd;
//            }
//         }
//      }
//      else if(version == 1)*/
//      {
//
//         byte * lpbAlloc = (byte *) malloc((iRadius * iRadius) + 4);
//         byte * lpb = (byte *) (((iptr) lpbAlloc + 3) & ~3);
//
//
//         i32 x, y;
//         i32 b;
//
////         i32 r2 = iRadius * iRadius;
//
//         for(y = 0; y < iRadius; y++)
//         {
//            for(x = y; x < iRadius; x++)
//            {
//               b = (i32) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
//               if(b > 255)
//                  b = 0;
//               else
//                  b = 255 - b;
//
//
//               lpb[x + y * iRadius] = (byte) b;
//               lpb[y + x * iRadius] = (byte) b;
//            }
//         }
//
//
//         i32 iR = iRadius - 1;
//
//         i32 xL = xCenter - iR;
//         i32 xU = xCenter + iR;
//         i32 yL = yCenter - iR;
//         i32 yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         byte *dst = ((byte*)(m_pcolorref + xL + yL * cx));
//         u32 dwAdd = ((cx - 1 - xU) + xL) * 4;
////         i32 size=cx*cy;
//
//         i32 dx, dy;
//
//         // Top Left
//
//         for(y = yL; y <= yU; y++)
//         {
//            for(x = xL; x <= xU; x++)
//            {
//               dx = abs(x - xCenter);
//               dy = abs(y - yCenter);
//               b = lpb[dx + dy * iRadius];
//               dst[0] = (byte) (blue     * b / 255);
//               dst[1] = (byte) (green    * b / 255);
//               dst[2] = (byte) (red      * b / 255);
//               dst[3] = (byte) (alpha    * b / 255);
//               dst += 4;
//            }
//            dst += dwAdd;
//         }
//
//         free(lpbAlloc);
//      }
//   }
//
//
//   void image::RadialFill(
//      byte alpha1, byte red1, byte green1, byte blue1,
//      byte alpha2, byte red2, byte green2, byte blue2,
//      i32 xCenter, i32 yCenter, i32 iRadius)
//   {
//      if (iRadius == 0)
//         return;
//      /*if(version == 0)
//      {
//
//         i32 iR = iRadius - 1;
//
//         i32 xL = xCenter - iR;
//         i32 xU = xCenter + iR;
//         i32 yL = yCenter - iR;
//         i32 yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= m_Size.cx) xU = m_Size.cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= m_Size.cy) yU = m_Size.cy - 1;
//
//
//         byte *dst = ((byte*)(m_pcolorref + xL + yL * m_Size.cx));
//         u32 dwAdd = ((m_Size.cx - 1 - xU) + xL) * 4;
//         i32 size=m_Size.cx*m_Size.cy;
//         double iLevel;
//
//         i32 dx, dy;
//         i32 dx0, dy0;
//         i32 dx1, dy1;
//         i32 dx2, dy2;
//         i32 dx3, dy3;
//         i32 dx4, dy4;
//         i32 dx5, dy5;
//         i32 dx6, dy6;
//         i32 dx7, dy7;
//         i32 dx8, dy8;
//         i32 dx9, dy9;
//         i32 dxA, dyA;
//         i32 dxB, dyB;
//         i32 dxC, dyC;
//         i32 dxD, dyD;
//         i32 dxE, dyE;
//         i32 dxF, dyF;
//
//         unsigned long dr;
//         unsigned long dq;
//         unsigned long dr0, dq0;
//         unsigned long dr1, dq1;
//         unsigned long dr2, dq2;
//         unsigned long dr3, dq3;
//         unsigned long dr4, dq4;
//         unsigned long dr5, dq5;
//         unsigned long dr6, dq6;
//         unsigned long dr7, dq7;
//         unsigned long dr8, dq8;
//         unsigned long dr9, dq9;
//         unsigned long drA, dqA;
//         unsigned long drB, dqB;
//         unsigned long drC, dqC;
//         unsigned long drD, dqD;
//         unsigned long drE, dqE;
//         unsigned long drF, dqF;
//         i32 x, y;
//
//         {
//            for(y = yL; y <= yU; y++)
//            {
//               for(x = xL; x <= xU; x++)
//               {
//                  dx = abs(x - xCenter);
//                  dy = abs(y - yCenter);
//                  isqrt((dx * dx) + (dy * dy), &dr, &dq);
//                  if(dr < iRadius)
//                  {
//                     iLevel = 1.0 - dr * 1.0 / iRadius;
//                     dst[0] = blue  * iLevel;
//                     dst[1] = green * iLevel;
//                     dst[2] = red   * iLevel;
//                  }
//                  dst += 4;
//               }
//               dst += dwAdd;
//            }
//         }
//      }
//      else if(version == 1)*/
//      {
//
//         byte * lpbAlloc = (byte *) malloc((iRadius * iRadius) + 4);
//         byte * lpb = (byte *) (((iptr) lpbAlloc + 3) & ~3);
//
//
//         i32 x, y;
//         i32 b;
//
////         i32 r2 = iRadius * iRadius;
//
//         for(y = 0; y < iRadius; y++)
//         {
//            for(x = y; x < iRadius; x++)
//            {
//               b = (i32) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
//               if(b > 255)
//                  b = 0;
//               else
//                  b = ~b;
//
//
//               lpb[x + y * iRadius] = (byte) b;
//               lpb[y + x * iRadius] = (byte) b;
//            }
//         }
//
//
//         i32 iR = iRadius - 1;
//
//         i32 xL = xCenter - iR;
//         i32 xU = xCenter + iR;
//         i32 yL = yCenter - iR;
//         i32 yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         byte *dst = ((byte*)(m_pcolorref + xL + yL * cx));
//         u32 dwAdd = ((cx - 1 - xU) + xL) * 4;
////         i32 size=cx*cy;
//
//         i32 dx, dy;
//
//         byte bComp;
//
//         // Top Left
//
//         for(y = yL; y <= yU; y++)
//         {
//            for(x = xL; x <= xU; x++)
//            {
//               dx = abs(x - xCenter);
//               dy = abs(y - yCenter);
//               b = lpb[dx + dy * iRadius];
//               bComp = (byte) ~b;
//               dst[0] = (byte) (((blue1  * b) + (blue2  * bComp)) / 255);
//               dst[1] = (byte) (((green1 * b) + (green2 * bComp)) / 255);
//               dst[2] = (byte) (((red1   * b) + (red2   * bComp)) / 255);
//               dst[3] = (byte) (((alpha1 * b) + (alpha2 * bComp)) / 255);
//               dst += 4;
//            }
//            dst += dwAdd;
//         }
//
//         free(lpbAlloc);
//      }
//   }
//
   void image::SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy)
   {
      create(cx, cy);

      if(cx <= 0 || cy <= 0)
         return;




      // White blend image
      ::image_pointer pimage1(get_object());
      pimage1 = create_image({cx,  cy});
      pimage1->set(255, 255, 255);

      pimage1->m_spgraphics->DrawIcon(
      0, 0,
      picon,
      cx, cy,
      0,
      nullptr,
      DI_IMAGE | DI_MASK);

      // Black blend image
      ::image_pointer pimage2;
      pimage2 = create_image({cx,  cy});
      pimage2->Fill(0, 0, 0, 0);

      pimage2->get_graphics()->DrawIcon(
      0, 0,
      picon,
      cx, cy,
      0,
      nullptr,
      DI_IMAGE | DI_MASK);

      // Mask image
      ::image_pointer pimageM(get_object());
      imageM = create_image({cx,  cy});

      imageM.m_spgraphics->DrawIcon(
      0, 0,
      picon,
      cx, cy,
      0,
      nullptr,
      DI_MASK);

      byte * r1=(byte*)pimage1->m_pcolorref;
      byte * r2=(byte*)pimage2->get_data();
      byte * srcM=(byte*)imageM.m_pcolorref;
      byte * dest=(byte*)m_pcolorref;
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



   }
//
//   void image::rotate(::image * pimage, double dAngle, double dScale)
//   {
//     // ::image_pointer pimage(get_object());
//   //   pimage->Paste(this);
//
//      i32 cx = this->cx;
//      i32 cy = this->cy;
//
//      i32 l = max(cx, cy);
//
//
//      i32 jmax = min(l, cy / 2);
//      i32 jmin = - jmax;
//      i32 imax = min(l, cx / 2);
//      i32 imin = - imax;
//
//
//      i32 joff = cy / 2;
//      i32 ioff = cx / 2;
//
//      //i32 iAngle = iStep % 360;
//      //i32 iAngle = iStep;
//      //i32 iAngle = 1;
//      //i32 k = 0;
//
//   /*     for ( i32 j=jmin; j<jmax; j++ )
//      {
//         for ( i32 i=imin; i<imax; i++ )
//         {
//            i32 x, y;
//
//            // A Combination of a 2d Translation/rotation/Scale Matrix
//            x=i32(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
//            y=i32(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
//            m_pcolorref[(j+joff)*cx+(i+ioff)]=
//               pimage->m_pcolorref[abs(y%cy)*cx+abs(x%cx)];
//            //k++;
//         }
//         (j+joff)*cx+(i+ioff)
//      }*/
//
//      i32 k = 0;
//      double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
//      double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
//      i32 cx1 = cx - 1;
//      i32 cy1 = cy - 1;
//        for ( i32 j=jmin; j<jmax; j++ )
//      {
//         for ( i32 i=imin; i<imax; i++ )
//         {
//            i32 x, y;
//
//            // A Combination of a 2d Translation/rotation/Scale Matrix
//            //x=abs((i32(dCos * i - dSin * j) + ioff) % cx);
//            //y=abs((i32(dSin * i + dCos * j) + joff) % cy);
//
//            x = (i32) abs((dCos * i - dSin * j) + ioff);
//            y = (i32) abs((dSin * i + dCos * j) + joff);
//
//            if((x / cx) % 2 == 0)
//            {
//               x %= cx;
//            }
//            else
//            {
//               x = cx1 - (x % cx);
//            }
//
//            if((y / cy) % 2 == 0)
//            {
//               y %= cy;
//            }
//            else
//            {
//               y = cy1 - (y % cy);
//            }
//
//
//
//            m_pcolorref[(j+joff)*cx+(i+ioff)]=
//               pimage->get_data()[y * cx + x];
//            k++;
//         }
//      }
//   }


   //void image::Rotate034(::image * pimage, double dAngle, double dScale)
   //{

   //   i32 cx = this->cx;
   //   i32 cy = this->cy;

   //   i32 l = max(cx, cy);


   //   i32 jmax = min(l, cy / 2);
   //   i32 jmin = - jmax;
   //   i32 imax = min(l, cx / 2);
   //   i32 imin = - imax;


   //   if((cy % 2) == 1)
   //      jmax++;

   //   if((cx % 2) == 1)
   //      imax++;

   //   i32 joff = cy / 2;
   //   i32 ioff = cx / 2;


   //   i32 k = 0;
   //   double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
   //   double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
   //   i32 cx1 = cx - 1;
   //   i32 cy1 = cy - 1;
   //     for ( i32 j=jmin; j<jmax; j++ )
   //   {
   //      for ( i32 i=imin; i<imax; i++ )
   //      {
   //         i32 x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         //x=abs((i32(dCos * i - dSin * j) + ioff) % cx);
   //         //y=abs((i32(dSin * i + dCos * j) + joff) % cy);

   //         x = (i32) abs((dCos * i - dSin * j) + ioff);
   //         y = (i32) abs((dSin * i + dCos * j) + joff);

   //         if((x / cx) % 2 == 0)
   //         {
   //            x %= cx;
   //         }
   //         else
   //         {
   //            x = cx1 - (x % cx);
   //         }

   //         if((y / cy) % 2 == 0)
   //         {
   //            y %= cy;
   //         }
   //         else
   //         {
   //            y = cy1 - (y % cy);
   //         }



   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}

   //void image::rotate(
   //   ::image * pimage,
   //   const ::rect & rect,
   //   double dAngle,
   //   double dScale)
   //{
   //  // ::image_pointer pimage(get_object());
   ////   pimage->Paste(this);



   //   ::rect rect(rect);

   //   i32 cx = rect.width();
   //   i32 cy = rect.height();

   //   i32 l = max(cx, cy);

   //   i32 jmax = min(l, cy / 2);
   //   i32 jmin = - jmax;
   //   i32 imax = min(l, cx / 2);
   //   i32 imin = - imax;


   //   i32 joff = cy / 2 + rect.left;
   //   i32 ioff = cx / 2 + rect.top;

   //   //i32 iAngle = iStep % 360;
   //   //i32 iAngle = iStep;
   //   //i32 iAngle = 1;
   //   //i32 k = 0;

   ///*     for ( i32 j=jmin; j<jmax; j++ )
   //   {
   //      for ( i32 i=imin; i<imax; i++ )
   //      {
   //         i32 x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         x=i32(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
   //         y=i32(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->m_pcolorref[abs(y%cy)*cx+abs(x%cx)];
   //         //k++;
   //      }
   //      (j+joff)*cx+(i+ioff)
   //   }*/

   //   i32 k = 0;
   //   double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
   //   double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
   //   i32 cx1 = cx - 1;
   //   i32 cy1 = cy - 1;
   //     for ( i32 j=jmin; j<jmax; j++ )
   //   {
   //      for ( i32 i=imin; i<imax; i++ )
   //      {
   //         i32 x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         //x=abs((i32(dCos * i - dSin * j) + ioff) % cx);
   //         //y=abs((i32(dSin * i + dCos * j) + joff) % cy);

   //         x = (i32) abs((dCos * i - dSin * j) + ioff);
   //         y = (i32) abs((dSin * i + dCos * j) + joff);

   //         if((x / cx) % 2 == 0)
   //         {
   //            x %= cx;
   //         }
   //         else
   //         {
   //            x = cx1 - (x % cx);
   //         }

   //         if((y / cy) % 2 == 0)
   //         {
   //            y %= cy;
   //         }
   //         else
   //         {
   //            y = cy1 - (y % cy);
   //         }



   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}

   /*i32 image::cos(i32 i, i32 iAngle)
   {
      return (i32) (((_int64) i * CosN[iAngle]) >> 32);
   }

   i32 image::sin(i32 i, i32 iAngle)
   {
      return (i32) (((_int64) i * SinN[iAngle]) >> 32);
   }*/




   //void image::Fill (i32 A, i32 R, i32 G, i32 B )
   //{
   //   map();

   //   color32_t color = RGB ( B, G, R ) | (A << 24);
   //   i32 size=cx*cy;

   //   color32_t * pcr;

   //   i32 iSize32 = size / 32;
   //   i32 i;
   //   for (i=0; i < iSize32; i+=32 )
   //   {
   //      pcr = &m_pcolorref[i];
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
   //      m_pcolorref[i]=color;
   //   }

   //}

   //color32_t image::GetAverageColor()
   //{
   //   double dR = 0.0;
   //   double dG = 0.0;
   //   double dB = 0.0;
   //   i32 iRLine;
   //   i32 iGLine;
   //   i32 iBLine;
   //   double dDiv = cx * cy;
   //   if(dDiv > 0)
   //   {
   //      byte * lpb = (byte *) m_pcolorref;
   //      for (i32 y = 0; y < cy; y++)
   //      {
   //         iRLine = 0;
   //         iGLine = 0;
   //         iBLine = 0;
   //         for (i32 x = 0; x < cx; x++)
   //         {
   //            iRLine += lpb[2];
   //            iGLine += lpb[1];
   //            iBLine += lpb[0];
   //            lpb += 4;
   //         }
   //         dR += iRLine / dDiv;
   //         dG += iGLine / dDiv;
   //         dB += iBLine / dDiv;
   //      }
   //      i32 iR = (i32) dR;
   //      i32 iG = (i32) dG;
   //      i32 iB = (i32) dB;
   //      return RGB(iR, iG, iB);
   //   }
   //   else
   //   {
   //      return 0;
   //   }

   //}


   //void image::_xor(::image * pimage)
   //{
   //   if(cx != pimage->cx
   //   || cy != pimage->cy)
   //   {
   //      return;
   //   }
   //   i32 iCount = cx * cy;
   //   LPDWORD lpd1 = (LPDWORD) m_pcolorref;
   //   LPDWORD lpd2 = (LPDWORD) pimage->get_data();
   //   for(i32 i = 0; i < iCount; i++)
   //   {
   //      *lpd1 = *lpd1 ^ *lpd2;
   //      lpd1++;
   //      lpd2++;
   //   }
   //}

   //void image::create_frame(::size size, i32 iFrameCount)
   //{
   //   i32 iSliceCount = (i32) sqrt((double) iFrameCount);
   //   i32 iFrameWidth = size.cx / iSliceCount;
   //   i32 iFrameHeight = size.cy / iSliceCount;
   //   create(iFrameWidth, iFrameHeight);
   //}

   //void image::set_frame1(void * lpdata, i32 iFrame, i32 iFrameCount)
   //{
   //   i32 iSliceCount = (i32) sqrt((double) iFrameCount);
   //   if(iSliceCount == 0)
   //      iSliceCount = 1;
   //   i32 iFrameWidth = cx / iSliceCount;
   //   i32 iFrameHeight = cy / iSliceCount;
   //   i32 iX = iFrame % iSliceCount;
   //   i32 iY = iFrame / iSliceCount;
   //   color32_t * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * cx];
   //   color32_t * lpSrc = (color32_t *) lpdata;
   //   color32_t * lpDestLine;
   //   for(i32 y = 0; y < iFrameHeight; y++)
   //   {
   //      lpDestLine = &lpDest[y * cx];
   //      for(i32 x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDestLine = *lpSrc;
   //          lpDestLine++;
   //          lpSrc++;
   //      }
   //   }
   //}

   //void image::set_frame2(void * lpdata, i32 iFrame, i32 iFrameCount)
   //{
   //   if(lpdata == nullptr)
   //      return;
   //   i32 iSliceCount = (i32) sqrt((double) iFrameCount);
   //   if(iSliceCount == 0)
   //      iSliceCount = 1;
   //   i32 iFrameWidth = cx / iSliceCount;
   //   i32 iFrameHeight = cy / iSliceCount;
   //   i32 iX = iFrame % iSliceCount;
   //   i32 iY = iFrame / iSliceCount;
   //   color32_t * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * cx];
   //   color32_t * lpSrc = (color32_t *) lpdata;
   //   color32_t * lpDestLine;
   //   for(i32 y = iFrameHeight - 1; y >= 0; y--)
   //   {
   //      lpDestLine = &lpDest[y * cx];
   //      for(i32 x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDestLine = *lpSrc;
   //          lpDestLine++;
   //          lpSrc++;
   //      }
   //   }
   //}

   //void image::xor_image_frame2(void * lpdata, i32 iFrame, i32 iFrameCount)
   //{
   //   if(lpdata == nullptr)
   //      return;
   //   i32 iSliceCount = (i32) sqrt((double) iFrameCount);
   //   if(iSliceCount == 0)
   //      iSliceCount = 1;
   //   i32 iFrameWidth = cx / iSliceCount;
   //   i32 iFrameHeight = cy / iSliceCount;
   //   i32 iX = iFrame % iSliceCount;
   //   i32 iY = iFrame / iSliceCount;
   //   color32_t * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * cx];
   //   color32_t * lpSrc = (color32_t *) lpdata;
   //   color32_t * lpDestLine;
   //   for(i32 y = iFrameHeight - 1; y >= 0; y--)
   //   {
   //      lpDestLine = &lpDest[y * cx];
   //      for(i32 x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDestLine ^= *lpSrc;
   //          lpDestLine++;
   //          lpSrc++;
   //      }
   //   }
   //}

   //void image::get_frame(void * lpdata, i32 iFrame, i32 iFrameCount)
   //{
   //   i32 iSliceCount = (i32) sqrt((double) iFrameCount);
   //   i32 iFrameWidth = cx / iSliceCount;
   //   i32 iFrameHeight = cy / iSliceCount;
   //   i32 iX = iFrame % iSliceCount;
   //   i32 iY = iFrame / iSliceCount;
   //   color32_t * lpSrc = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight *  cx];
   //   color32_t * lpDest = (color32_t *) lpdata;
   //   color32_t * lpSrcLine;
   //   for(i32 y = 0; y < iFrameHeight; y++)
   //   {
   //      lpSrcLine = &lpSrc[y * cx];
   //      for(i32 x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDest = *lpSrcLine;
   //          lpDest++;
   //          lpSrcLine++;
   //      }
   //   }
   //}

   //bool image::is_rgb_black()
   //{
   //   i32 iSize = cx * cy;
   //   color32_t * lp = m_pcolorref;
   //   for(i32 i = 0; i < iSize; i++)
   //   {
   //      if((*lp & 0x00FFFFFF) != 0)
   //         return false;
   //      lp++;
   //   }
   //   return true;
   //}

   //void image::DivideRGB(i32 iDivide)
   //{
   //   if(iDivide == 0)
   //   {
   //      return;
   //   }
   //   i32 iCount = cx * cy;
   //   byte * lp = ((byte *) m_pcolorref);
   //   i32 i = 0;
   //   i32 iCount1 = iCount - iCount % 8;
   //   for(; i < iCount1; i++)
   //   {
   //      lp[0] /= (byte) iDivide;
   //      lp[1] /= (byte) iDivide;
   //      lp[2] /= (byte) iDivide;

   //      lp[4] /= (byte) iDivide;
   //      lp[5] /= (byte) iDivide;
   //      lp[6] /= (byte) iDivide;

   //      lp[8] /= (byte) iDivide;
   //      lp[9] /= (byte) iDivide;
   //      lp[10] /= (byte) iDivide;

   //      lp[12] /= (byte) iDivide;
   //      lp[13] /= (byte) iDivide;
   //      lp[14] /= (byte) iDivide;

   //      lp[16] /= (byte) iDivide;
   //      lp[17] /= (byte) iDivide;
   //      lp[28] /= (byte) iDivide;

   //      lp[20] /= (byte) iDivide;
   //      lp[21] /= (byte) iDivide;
   //      lp[22] /= (byte) iDivide;

   //      lp[24] /= (byte) iDivide;
   //      lp[25] /= (byte) iDivide;
   //      lp[26] /= (byte) iDivide;

   //      lp[28] /= (byte) iDivide;
   //      lp[29] /= (byte) iDivide;
   //      lp[30] /= (byte) iDivide;

   //      lp += 4 * 8;
   //   }
   //   for(; i < iCount; i++)
   //   {
   //      lp[0] /= (byte) iDivide;
   //      lp[1] /= (byte) iDivide;
   //      lp[2] /= (byte) iDivide;
   //      lp +=4;
   //   }
   //}

   //void image::DivideARGB(i32 iDivide)
   //{
   //   if(iDivide == 0)
   //   {
   //      return;
   //   }
   //   i32 iCount = cx * cy;
   //   byte * lp = ((byte *) m_pcolorref);
   //   for(i32 i = 0; i < iCount; i++)
   //   {
   //      lp[0] /= (byte) iDivide;
   //      lp[1] /= (byte) iDivide;
   //      lp[2] /= (byte) iDivide;
   //      lp[3] /= (byte) iDivide;
   //      lp +=4;
   //   }
   //}

   //void image::DivideA(i32 iDivide)
   //{
   //   if(iDivide == 0)
   //   {
   //      return;
   //   }
   //   i32 iCount = cx * cy;
   //   byte * lp = ((byte *) m_pcolorref);
   //   for(i32 i = 0; i < iCount; i++)
   //   {
   //      lp[3] /= (byte) iDivide;
   //      lp +=4;
   //   }
   //}


   void image::stretch_image(::image * pimage)
   {

      __throw(todo());

      /* xxx

      Gdiplus::RectF rectDest(0, 0, (Gdiplus::REAL) width(), (Gdiplus::REAL) height());

      Gdiplus::RectF rectSource(0, 0, (Gdiplus::REAL) pimage->width(), (Gdiplus::REAL) pimage->height());

      ((Gdiplus::Graphics * ) m_spgraphics->get_os_data())->DrawImage(((Gdiplus::Bitmap *)pimage->get_bitmap()->get_os_data()), rectDest, rectSource, Gdiplus::UnitPixel);

      */

      /*
      ::StretchDIBits(
         SP_HDC(m_spgraphics),
         0, 0,
         cx, cy,
         0, 0,
         pimage->cx, pimage->cy,
         pimage->get_data(),
         &CAIRO_DIB(pimage)->m_info,
         DIB_RGB_COLORS,
         SRCCOPY);*/

   }

   ::draw2d::graphics * pimage::get_graphics()
   {
      unmap();
      return m_spgraphics;
   }

   /*   double image::pi()
      {
         return dPi;
      }*/

   // void image::fill_channel(i32 intensity, color::color::rgba::echannel echannel)
   // {
   //     i32 offset = ((i32)echannel) % 4;
   //    i32 size=cx*cy;

   //    byte * pb;

   //    i32 iSize32 = size / 32;
   //    i32 i;
   //    for (i=0; i < iSize32; i+=32 )
   //    {
   //       pb = ((byte * ) &m_pcolorref[i]) + offset;
   //       pb[0 * 4] = (byte) intensity;
   //       pb[1 * 4] = (byte) intensity;
   //       pb[2 * 4] = (byte) intensity;
   //       pb[3 * 4] = (byte) intensity;
   //       pb[4 * 4] = (byte) intensity;
   //       pb[5 * 4] = (byte) intensity;
   //       pb[6 * 4] = (byte) intensity;
   //       pb[7 * 4] = (byte) intensity;
   //       pb[8 * 4] = (byte) intensity;
   //       pb[9 * 4] = (byte) intensity;
   //       pb[10 * 4] = (byte) intensity;
   //       pb[11 * 4] = (byte) intensity;
   //       pb[12 * 4] = (byte) intensity;
   //       pb[13 * 4] = (byte) intensity;
   //       pb[14 * 4] = (byte) intensity;
   //       pb[15 * 4] = (byte) intensity;
   //       pb[16 * 4] = (byte) intensity;
   //       pb[17 * 4] = (byte) intensity;
   //       pb[18 * 4] = (byte) intensity;
   //       pb[19 * 4] = (byte) intensity;
   //       pb[20 * 4] = (byte) intensity;
   //       pb[21 * 4] = (byte) intensity;
   //       pb[22 * 4] = (byte) intensity;
   //       pb[23 * 4] = (byte) intensity;
   //       pb[24 * 4] = (byte) intensity;
   //       pb[25 * 4] = (byte) intensity;
   //       pb[26 * 4] = (byte) intensity;
   //       pb[27 * 4] = (byte) intensity;
   //       pb[28 * 4] = (byte) intensity;
   //       pb[29 * 4] = (byte) intensity;
   //       pb[30 * 4] = (byte) intensity;
   //       pb[31 * 4] = (byte) intensity;
   //    }

   //    for (i=0; i<size; i++ )
   //    {
   //       *(((byte * ) &m_pcolorref[i]) + offset) = (byte) intensity;
   //    }
   //}


   //i32 image::cos(i32 i, i32 iAngle)
   //{
   //   return (i32) (((i64) i * CosN[iAngle]) >> 31);
   //}

   //i32 image::sin(i32 i, i32 iAngle)
   //{
   //   return (i32) (((i64) i * SinN[iAngle]) >> 31);
   //}

   //i32 image::cos10(i32 i, i32 iAngle)
   //{
   //   return (i32) (((i64) i * Cos10N[iAngle]) >> 34);
   //}

   //i32 image::sin10(i32 i, i32 iAngle)
   //{
   //   return (i32) (((i64) i * Sin10N[iAngle]) >> 34);
   //}

   //i32 image::width()
   //{
   //   return cx;
   //}

   //i32 image::height()
   //{
   //   return cy;
   //}


   bool image::print_window(::window * pwnd, ::message::message * pmessage)
   {

      return true;

   }


#if defined(WINDOWS)

   bool image::update_window(::user::user::interaction_impl * pwnd, ::message::message * pmessage)
   {


      rect64 rectWindow;

      rectWindow = pwnd->m_rectParentClient;

      m_spgraphics->SetViewportOrg(0, 0);

      map(true);

      ::rect rect(rectWindow);

      window_graphics::update_window(pwnd->m_pgraphics, pwnd->get_handle(), m_pcolorref, rect, m_iScan);

      return true;

   }


   bool image::print_window(::user::user::interaction_impl * pwnd, ::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if(pbase->m_wparam == nullptr)
         return false;

      m_spgraphics->attach((HDC) pbase->m_wparam);

      ::rect rectx;

      ::draw2d::bitmap * pbitmap = m_spgraphics->get_current_bitmap();

      ::GetCurrentObject((HDC) pbase->m_wparam, OBJ_BITMAP);

      //      u32 dw = ::get_last_error();
      ::size size = pbitmap->get_size();

      rectx.left = 0;
      rectx.top = 0;
      rectx.right = size.cx;
      rectx.bottom = size.cy;

      try
      {

         ::rect rectWindow;

         pwnd->get_window_rect(rectWindow);

         ::image_pointer pimage;

         if(!pimage = create_image(rectWindow.bottom_right()))
            return false;

         ::draw2d::graphics * pgraphics = pimage->get_graphics();

         if(pgraphics->get_os_data() == nullptr)
            return false;

         ::rect rectPaint;
         ::rect rectUpdate;
         rectUpdate = rectWindow;
         rectPaint = rectWindow;
         rectPaint.offset(-rectPaint.top_left());
         m_spgraphics->SelectClipRgn(nullptr);
         if(pwnd->m_pguie != nullptr && pwnd->m_pguie != this)
         {
            pwnd->m_pguie->_001OnDeferPaintLayeredWindowBackground(pgraphics);
         }
         else
         {
            pwnd->_001OnDeferPaintLayeredWindowBackground(pgraphics);
         }
         m_spgraphics->SelectClipRgn(nullptr);
         m_spgraphics-> SetViewportOrg(::point());
         pwnd->_000OnDraw(pgraphics);
         m_spgraphics->SetViewportOrg(::point());
         //(dynamic_cast<::win::graphics * >(pgraphics))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
         m_spgraphics->SelectClipRgn(nullptr);
         m_spgraphics->SetViewportOrg(::point());

         m_spgraphics->SelectClipRgn( nullptr);
         m_spgraphics->BitBlt(rectPaint.left, rectPaint.top,
                              rectPaint.width(), rectPaint.height(),
                              pgraphics, rectUpdate.left, rectUpdate.top,
                              SRCCOPY);

         m_spgraphics->text_out(0, 0, "Xlib Drawing!!", 11);
      }
      catch(...)
      {
      }
      m_spgraphics->FillSolidRect(rectx, RGB(255, 255, 255));
      pmessage->m_bRet = true;
      pbase->set_lresult(0);

      return true;
   }


#endif


   bool image::update_window(::window * pwnd, ::message::message * pmessage)
   {

//      rect64 rectWindow;
//
//      rectWindow = pwnd->m_rectParentClient;
//
//      m_spgraphics->SetViewportOrg(0, 0);
//
//      map(true);
//
//      ::rect rect(rectWindow);
//
//      window_graphics::update_window(pwnd->m_pgraphics, pwnd->get_handle(), m_pcolorref, rect, m_iScan);

      return true;


   }





} // namespace draw2d_xlib
