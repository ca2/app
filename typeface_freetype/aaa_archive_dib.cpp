#include "framework.h"
#include "omp.h"


namespace typeface_freetype
{


   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   image::image::image()
   {

      m_sizeWnd.cx         = 0;
      m_sizeWnd.cy         = 0;
      m_hbitmap            = nullptr;

      zero(m_bitmapinfo);

   }

   //color32_t * pimage::get_data()
   //{
   //   return m_pcolorref;
   //}
   ::draw2d::bitmap_pointer image::get_bitmap() const
   {
      return m_pbitmap;
   }

   ::draw2d::bitmap_pointer image::detach_bitmap()
   {
      return m_pbitmap.detach();
   }


   void image::construct (int cx,  int cy)
   {
      m_pcolorref    = nullptr;
      cx             = 0;
      cy             = 0;
      create(cx, cy);
   }

   image::~image ()
   {

      destroy ();

   }

   bool image::create(::size size)
   {
      return create(size.cx, size.cy);
   }

   bool image::create(int width, int height)
   {

      if(width <= 0 || height <= 0)
         return false;

      if(m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && width == m_size.cx
            && height == m_size.cy)
         return true;

      destroy();

      m_info = {};

      m_info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      m_info.bmiHeader.biWidth         = width;
      m_info.bmiHeader.biHeight        =- height;
      m_info.bmiHeader.biPlanes        = 1;
      m_info.bmiHeader.biBitCount      = 32;
      m_info.bmiHeader.biCompression   = BI_RGB;
      m_info.bmiHeader.biSizeImage     = width * height * 4;

      m_pbitmap.create(this);
      m_spgraphics.create(this);

      if(m_pbitmap.m_p == nullptr)
      {

         m_size.cx       = 0;

         m_size.cy       = 0;

         m_iScan     = 0;

         return false;

      }

      if(!m_pbitmap->CreateDIBSection(nullptr, &m_info, DIB_RGB_COLORS, (void **) &m_pcolorref, &m_iScan, nullptr, 0))
      {

         m_size.cx      = 0;

         m_size.cy      = 0;

         m_iScan        = 0;

         return false;

      }

      if(m_pbitmap->get_os_data() == nullptr)
      {

         destroy();

         return false;

      }

      m_spgraphics->SelectObject(m_pbitmap);

      m_spgraphics->m_pimage = this;

      m_size.cx       = width;

      m_size.cy       = height;

      m_iScan         = m_pbitmap->m_iStride;

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


   bool image::create(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap * pbitmap = (dynamic_cast<::typeface_freetype::graphics * >(pgraphics))->get_current_bitmap();

      if(pbitmap == nullptr)
         return false;

      if (!create(pbitmap->get_size()))
      {
         return false;
      }

      from(pgraphics);

      return true;

   }


   bool image::destroy ()
   {

      m_pbitmap.release();

      m_spgraphics.release();

      m_size         = {};
      m_iScan        = 0;
      m_pcolorref    = nullptr;

      return true;

   }


   bool image::to(::draw2d::graphics * pgraphics, const ::int_point & point, ::size size, point ptSrc)
   {

      return pgraphics->BitBlt(point, size, get_graphics(), ptSrc);

      /*  return SetDIBitsToDevice(
           (dynamic_cast<::typeface_freetype::graphics * >(pgraphics))->get_handle1(),
           point.x, point.y,
           size.cx, size.cy,
           ptSrc.x, ptSrc.y, ptSrc.y, cy - ptSrc.y,
           m_pcolorref, &m_info, 0)
              != false; */

   }


   bool image::from(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap_pointer bitmap(this);

      bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);

      ::draw2d::bitmap * pbitmap = GL2D_GRAPHICS(pgraphics)->SelectObject(bitmap);

      if (pbitmap == nullptr)
      {

         return false;

      }

      ::size size = pbitmap->get_size();

      if(!create(size))
      {

         GL2D_GRAPHICS(pgraphics)->SelectObject(pbitmap);

         return false;

      }

      bool bOk = GetDIBits(GL2D_HDC(pgraphics), (HBITMAP) pbitmap->get_os_data(), 0, m_size.cy, m_pcolorref, &(m_info), DIB_RGB_COLORS) != false;

      GL2D_GRAPHICS(pgraphics)->SelectObject(pbitmap);

      return bOk;

   }


   bool image::from(point ptDest, ::draw2d::graphics * pgraphics, const ::int_point & point, ::size sz)
   {

      if (m_spgraphics.is_null())
         return false;

      return m_spgraphics->BitBlt(ptDest, sz, pgraphics, point) != false;

   }


   /*void image::Fill ( int R, int G, int B )
   {
      color32_t color=rgb ( B, G, R );
      long long size = area();

      color32_t * pcr;

      long long iSize32 = size / 32;
      int i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &m_pcolorref[i];
         pcr[0] = color;
         pcr[1] = color;
         pcr[2] = color;
         pcr[3] = color;
         pcr[4] = color;
         pcr[5] = color;
         pcr[6] = color;
         pcr[7] = color;
         pcr[8] = color;
         pcr[9] = color;
         pcr[10] = color;
         pcr[11] = color;
         pcr[12] = color;
         pcr[13] = color;
         pcr[14] = color;
         pcr[15] = color;
         pcr[16] = color;
         pcr[17] = color;
         pcr[18] = color;
         pcr[19] = color;
         pcr[20] = color;
         pcr[21] = color;
         pcr[22] = color;
         pcr[23] = color;
         pcr[24] = color;
         pcr[25] = color;
         pcr[26] = color;
         pcr[27] = color;
         pcr[28] = color;
         pcr[29] = color;
         pcr[30] = color;
         pcr[31] = color;
      }

      for (i=0; i<size; i++ )
      {
         m_pcolorref[i]=color;
      }
   }

   void image::set_rgb(int R, int G, int B)
   {
      long long size = area();

      unsigned char * pbyte = (unsigned char *) m_pcolorref;

      int i;
      for (i=0; i<size; i++ )
      {
         *pbyte++ = (unsigned char) R;
         *pbyte++ = (unsigned char) G;
         *pbyte++ = (unsigned char) B;
         pbyte++;
      }
   }

   void image::ToAlpha(int i)
   {
      unsigned char *dst=(unsigned char*)m_pcolorref;
      long long size = area();

      while ( size-- )
      {
         dst[3] = dst[i];
         dst+=4;
      }
   }

   void image::from_alpha()
   {
      unsigned char *dst=(unsigned char*)m_pcolorref;
      long long size = area();

      while ( size-- )
      {
         dst[0] = dst[3];
         dst[1] = dst[3];
         dst[2] = dst[3];
         dst+=4;
      }
   }

   //DIB = DIB * SRC_ALPHA

   void image::mult_alpha(::image::image *pimageWork, bool bPreserveAlpha)
   {
      image::mult_alpha(imageWork, bPreserveAlpha);
      return ;
      /*
      if(area() <= 0)
         return;

      //return image::mult_alpha(nullptr, true);
      ::image::image pimageWork;

      if(imageWork == nullptr)
      {
         imageWork.create(this);
         imageWork = imageWork;
      }

      if(imageWork = create_image({width(),  height())})
         return;

      imageWork.FillByte(0);

      imageWork.channel_from(::color::e_channel_opacity, this);

      imageWork.channel_invert(::color::e_channel_opacity);


      BLENDFUNCTION bf;

      bf.BlendOp = AC_SRC_OVER;
      bf.BlendFlags = 0;
      bf.SourceConstantAlpha = 255;
      bf.AlphaFormat = AC_SRC_ALPHA;

      get_graphics()->alpha_blend(size(), imageWork.get_graphics(), bf);

      if(bPreserveAlpha)
      {

         imageWork.channel_invert(::color::e_channel_opacity);

         ::color::e_channel_from(::color::e_channel_opacity, imageWork);

      }

      */

   //}

   //void image::Map(int ToRgb, int FromRgb)
   //{
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();

   //   while ( size-- )
   //   {
   //      *dst = (unsigned char) (*dst == FromRgb ? ToRgb : *dst);
   //      dst+=4;
   //   }
   //}


   //void image::ToAlphaAndFill(int i, color32_t color32)
   //{
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();

   //   unsigned char uchB = ::blue(color32);
   //   unsigned char uchG = ::green(color32);
   //   unsigned char uchR = ::red(color32);

   //   while ( size-- )
   //   {
   //      dst[3] = dst[i];
   //      dst[0] = uchB;
   //      dst[1] = uchG;
   //      dst[2] = uchR;
   //      dst+=4;
   //   }
   //}

   //void image::GrayToARGB(color32_t color32)
   //{
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();

   //   unsigned int dwB = ::blue(color32);
   //   unsigned int dwG = ::green(color32);
   //   unsigned int dwR = ::red(color32);

   //   while (size-- > 0)
   //   {
   //      dst[3] = dst[0];
   //      dst[0] = (unsigned char)(((dwB * dst[3]) / 256) & 0xff);
   //      dst[1] = (unsigned char)(((dwG * dst[3]) / 256) & 0xff);
   //      dst[2] = (unsigned char)(((dwR * dst[3]) / 256) & 0xff);
   //      dst+=4;
   //   }
   //}


   //void image::BitBlt(imagepimage, int op)
   //{
   //   if(op == 123) // zero dest rgb, invert alpha, and OR src rgb
   //   {
   //      long long isize = area();
   //      LPDWORD lpbitsSrc= (LPDWORD) pimage->get_data();
   //      LPDWORD lpbitsDest= (LPDWORD) m_pcolorref;

   //      color32_t _colorref = rgb ( 0, 0, 0 ) | (255 << 24);
   //      color32_t colorrefa[2];
   //      colorrefa[0] = _colorref;
   //      colorrefa[1] = _colorref;

   //      color32_t _colorrefN = rgb ( 255, 255, 255) | (0 << 24);
   //      color32_t colorrefaN[2];
   //      colorrefaN[0] = _colorrefN;
   //      colorrefaN[1] = _colorrefN;
   //      throw ::exception(todo);
   //   }

   //}


   //void image::Invert()
   //{
   //   long long size = area();
   //   LPBYTE lpb = (LPBYTE) m_pcolorref;
   //   for ( int i=0; i<size; i++ )
   //   {
   //      lpb[0] = 255 - lpb[0];
   //      lpb[1] = 255 - lpb[1];
   //      lpb[2] = 255 - lpb[2];
   //      lpb += 4;
   //   }
   //}

   //void image::color::e_channel_invert(color::color::color::rgba::echannel echannel)
   //{
   //   long long size   = area();
   //   register long long size64 = size / 64;
   //   LPBYTE lpb = (LPBYTE) m_pcolorref;
   //   lpb += ((int)echannel) % 4;
   //   register long long i = 0;
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
   //void image::color::e_channel_multiply(color::color::color::rgba::echannel echannel, double dRate)
   //{
   //   if(dRate < 0)
   //      return;
   //   register long long size = area();
   //   LPBYTE lpb = (LPBYTE) get_data();
   //   lpb += ((int)echannel) % 4;
   //   register int iDiv = 256 * 256;
   //   register int iMul = (int) (dRate * ((double) iDiv));
   //   register int iRes;
   //   for(register long long i = 0; i < size; i++)
   //   {
   //      iRes = *lpb * iMul / iDiv;
   //      *lpb = (unsigned char) (iRes > 255 ? 255 : iRes);
   //      lpb += 4;
   //   }
   //}

   //void image::FillGlass ( int R, int G, int B, int A )
   //{
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)(((B-dst[0])*A+(dst[0]<<8))>>8);
   //      dst[1]=(unsigned char)(((G-dst[1])*A+(dst[1]<<8))>>8);
   //      dst[2]=(unsigned char)(((R-dst[2])*A+(dst[2]<<8))>>8);
   //      dst+=4;
   //   }
   //}

   //void image::FillStippledGlass ( int R, int G, int B )
   //{
   //   color32_t color=rgb ( B, G, R );
   //   int w=m_size.cx;
   //   int h=m_size.cy;

   //   for ( int j=0; j<w; j++ )
   //   {
   //      for ( int i=0; i<h; i++ )
   //      {
   //         m_pcolorref[j*w+i]=((i+j)&0x1) ? m_pcolorref[j*w+i] : color;
   //      }
   //   }
   //}

   //void imagecopy(::image::image *pimage)
   //{
   //   // If DibSize Wrong Re-create image
   //   if (pimage->get_size() != m_size)
   //      pimage = create_image (m_size);
   //   // do copy
   //   ::memory_copy ( pimage->get_data(), m_pcolorref, (size_t) area() * sizeof(color32_t) );
   //}


   //void image::Paste ( ::image::image pimage )
   //{
   //   // If DibSize Wrong Re-create image
   //   if (m_size !=pimage.get_size() )
   //      create ( pimage->get_size() );
   //   // do Paste
   //   ::memory_copy ( m_pcolorref, pimage->get_data(), (size_t) area() * sizeof(color32_t) );
   //}

   //bool image::color_blend(color32_t color32, unsigned char bAlpha)
   //{

   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();

   //   unsigned int dwB = ::blue(color32);
   //   unsigned int dwG = ::green(color32);
   //   unsigned int dwR = ::red(color32);
   //
   //   unsigned int dwB_ = dwB << 8;
   //   unsigned int dwG_ = dwG << 8;
   //   unsigned int dwR_ = dwR << 8;
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)(((dst[0]-dwB)*bAlpha+dwB_)>>8);
   //      dst[1]=(unsigned char)(((dst[1]-dwG)*bAlpha+dwG_)>>8);
   //      dst[2]=(unsigned char)(((dst[2]-dwG)*bAlpha+dwR_)>>8);
   //      dst+=4;
   //   }
   //   return true;
   //}


   //void image::Blend (::image::image *pimage, int A )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
   //      dst[1]=(unsigned char)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
   //      dst[2]=(unsigned char)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //bool image::Blend(imagepimage, imagepimageA, int A)
   //{
   //   if(size() != pimage->size() ||
   //      size() != imageA.size())
   //      return false;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   unsigned char *alf=(unsigned char*)imageA.m_pcolorref;
   //   long long size = area();

   //   A = 2 - A;
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)(((src[0]-dst[0])*alf[A]+(dst[0]<<8))>>8);
   //      dst[1]=(unsigned char)(((src[1]-dst[1])*alf[A]+(dst[1]<<8))>>8);
   //      dst[2]=(unsigned char)(((src[2]-dst[2])*alf[A]+(dst[2]<<8))>>8);
   //      dst+=4;
   //      src+=4;
   //      alf+=4;
   //   }

   //   return true;
   //}

   //void image::Darken (::image::image *pimage )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)((src[0]<dst[0]) ? src[0] : dst[0]);
   //      dst[1]=(unsigned char)((src[1]<dst[1]) ? src[1] : dst[1]);
   //      dst[2]=(unsigned char)((src[2]<dst[2]) ? src[2] : dst[2]);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Difference (::image::image *pimage )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      int Difference;
   //      Difference=src[0]-dst[0];
   //      dst[0]=(unsigned char)((Difference<0) ? -Difference : Difference);
   //      Difference=src[1]-dst[1];
   //      dst[1]=(unsigned char)((Difference<0) ? -Difference : Difference);
   //      Difference=src[2]-dst[2];
   //      dst[2]=(unsigned char)((Difference<0) ? -Difference : Difference);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Lighten (::image::image *pimage )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)((src[0]>dst[0]) ? src[0] : dst[0]);
   //      dst[1]=(unsigned char)((src[1]>dst[1]) ? src[1] : dst[1]);
   //      dst[2]=(unsigned char)((src[2]>dst[2]) ? src[2] : dst[2]);
   //      dst+=4;
   //      src+=4;
   //   }
   //}


   //void image::Multiply (::image::image *pimage )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)(((src[0])*(dst[0]))>>8);
   //      dst[1]=(unsigned char)(((src[1])*(dst[1]))>>8);
   //      dst[2]=(unsigned char)(((src[2])*(dst[2]))>>8);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Screen (::image::image *pimage )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   unsigned char *src=(unsigned char*)pimage->get_data();
   //   unsigned char *dst=(unsigned char*)m_pcolorref;
   //   long long size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(unsigned char)(255-(((255-src[0])*(255-dst[0]))>>8));
   //      dst[1]=(unsigned char)(255-(((255-src[1])*(255-dst[1]))>>8));
   //      dst[2]=(unsigned char)(255-(((255-src[2])*(255-dst[2]))>>8));
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   ////////////////////////////////////////////////////////////////////////
   //// Rectangle Functions
   ////////////////////////////////////////////////////////////////////////

   //void image::copy (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->width())<m_size.cx) ? pimage.width() : m_size.cx-x;
   //   int Δy=((y+pimage->height())<m_size.cy) ? pimage.height() : m_size.cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to copy return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;
   //   // If DibSize Wrong Re-create image
   //   if ( (Δx!=pimage->width()) || (Δy!=pimage->height()) )
   //      pimage = create_image ( Δx, Δy );

   //   // Prepare buffer Addresses
   //   color32_t *src=m_pcolorref+(py*m_size.cx)+px;
   //   color32_t *dst=pimage->get_data();

   //   // Do copy
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //         dst[i]=src[i];
   //      src+=m_size.cx;
   //      dst+=pimage->width();
   //   }
   //}

   //void image::PasteRect (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->width())<m_size.cx) ? pimage.width() : m_size.cx-x;
   //   int Δy=((y+pimage->height())<m_size.cy) ? pimage.height() : m_size.cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Paste return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   color32_t *src=pimage->get_data()+((py-y)*pimage->width())+px-x;
   //   color32_t *dst=m_pcolorref+(py*m_size.cx)+px;

   //   // Do Paste
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //         dst[i]=src[i];
   //      src+=pimage->width();
   //      dst+=m_size.cx;
   //   }
   //}

   //void image::FillRect ( int x, int y, int w, int h, int R, int G, int B )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+w)<m_size.cx) ? w : m_size.cx-x;
   //   int Δy=((y+h)<m_size.cy) ? h : m_size.cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Fill return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   color32_t *dst=m_pcolorref+(py*m_size.cx)+px;
   //   color32_t color=rgb ( B, G, R );

   //   // Do Fill
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[i]=color;
   //      }
   //      dst+=m_size.cx;
   //   }
   //}

   //void image::FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+w)<m_size.cx) ? w : m_size.cx-x;
   //   int Δy=((y+h)<m_size.cy) ? h : m_size.cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to FillGlass return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*m_size.cx)+px)*4;

   //   // Do FillGlass
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(unsigned char)(((B-dst[0])*A+(dst[0]<<8))>>8);
   //         dst[1]=(unsigned char)(((G-dst[1])*A+(dst[1]<<8))>>8);
   //         dst[2]=(unsigned char)(((R-dst[2])*A+(dst[2]<<8))>>8);
   //         dst+=4;
   //      }
   //      dst+=(m_size.cx-Δx)<<2;
   //   }
   //}

   //void image::FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+w)<m_size.cx) ? w : m_size.cx-x;
   //   int Δy=((y+h)<m_size.cy) ? h : m_size.cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to FillStippledGlass return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   color32_t *dst=m_pcolorref+(py*m_size.cx)+px;
   //   color32_t color=rgb ( B, G, R );

   //   // Do FillStippledGlass
   //   for ( int j=0; j<Δy; j++ )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[i]=((i+j)&0x1) ? dst[i] : color;
   //      }
   //      dst+=m_size.cx;
   //   }
   //}

   //void image::BlendRect (::image::image *pimage, int x, int y, int A )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->width())<m_size.cx) ? pimage.width() : m_size.cx-x;
   //   int Δy=((y+pimage->height())<m_size.cy) ? pimage.height() : m_size.cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Blend return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   unsigned char *src=(unsigned char *)pimage->get_data()+(((py-y)*pimage->width())+px-x)*4;
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*m_size.cx)+px)*4;

   //   // Do Blend
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(unsigned char)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
   //         dst[1]=(unsigned char)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
   //         dst[2]=(unsigned char)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(m_size.cx-Δx)<<2;
   //      src+=(pimage->width()-Δx)<<2;
   //   }
   //}

   //void image::DarkenRect (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   int Δy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Darken return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   unsigned char *src=(unsigned char *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Darken
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(unsigned char)((src[0]<dst[0]) ? src[0] : dst[0]);
   //         dst[1]=(unsigned char)((src[1]<dst[1]) ? src[1] : dst[1]);
   //         dst[2]=(unsigned char)((src[2]<dst[2]) ? src[2] : dst[2]);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx-Δx)<<2;
   //   }
   //}

   //void image::DifferenceRect (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   int Δy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Difference return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   unsigned char *src=(unsigned char *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Difference
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         int Difference;
   //         Difference=src[0]-dst[0];
   //         dst[0]=(unsigned char)((Difference<0) ? -Difference : Difference);
   //         Difference=src[1]-dst[1];
   //         dst[1]=(unsigned char)((Difference<0) ? -Difference : Difference);
   //         Difference=src[2]-dst[2];
   //         dst[2]=(unsigned char)((Difference<0) ? -Difference : Difference);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx-Δx)<<2;
   //   }
   //}

   //void image::LightenRect (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   int Δy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Lighten return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   unsigned char *src=(unsigned char *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Lighten
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(unsigned char)((src[0]>dst[0]) ? src[0] : dst[0]);
   //         dst[1]=(unsigned char)((src[1]>dst[1]) ? src[1] : dst[1]);
   //         dst[2]=(unsigned char)((src[2]>dst[2]) ? src[2] : dst[2]);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx-Δx)<<2;
   //   }
   //}

   //void image::MultiplyRect (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   int Δy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Multiply return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   unsigned char *src=(unsigned char *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Multiply
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(unsigned char)(((src[0])*(dst[0]))>>8);
   //         dst[1]=(unsigned char)(((src[1])*(dst[1]))>>8);
   //         dst[2]=(unsigned char)(((src[2])*(dst[2]))>>8);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx-Δx)<<2;
   //   }
   //}

   //void image::ScreenRect (::image::image *pimage, int x, int y )
   //{
   //   // Clip Rect
   //   int px=(x>=0) ? x : 0;
   //   int py=(y>=0) ? y : 0;
   //   int Δx=((x+pimage->cx)<cx) ? pimage->cx : cx-x;
   //   int Δy=((y+pimage->cy)<cy) ? pimage->cy : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Screen return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   unsigned char *src=(unsigned char *)pimage->get_data()+(((py-y)*pimage->cx)+px-x)*4;
   //   unsigned char *dst=(unsigned char *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Screen
   //   while ( Δy-- )
   //   {
   //      for ( int i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(unsigned char)(255-(((255-src[0])*(255-dst[0]))>>8));
   //         dst[1]=(unsigned char)(255-(((255-src[1])*(255-dst[1]))>>8));
   //         dst[2]=(unsigned char)(255-(((255-src[2])*(255-dst[2]))>>8));
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx-Δx)<<2;
   //   }
   //}

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void image::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
   {
      int Δx, Δy, k1, k2, d, x, y;
      color32_t color=rgb ( B, G, R );

      Δx=x2-x1;
      Δy=y2-y1;
      d=(Δy<<1)-Δx;
      k1=Δy<<1;
      k2=(Δy-Δx)<<1;
      x=x1;
      y=y1;

      m_pcolorref[y*cx+x]=color;
      while (x<Δx)
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

//   void image::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
//   {
//      int d, x, y, ax, ay, sx, sy, Δx, Δy;
//      color32_t color=rgb ( B, G, R );
//
//      Δx=x2-x1;
//      ax=abs ( Δx )<<1;
//      sx=(Δx<0) ? -1 : 1;
//      Δy=y2-y1;
//      ay=abs ( Δy )<<1;
//      sy=(Δy<0) ? -1 : 1;
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
//   void image::LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A )
//   {
//      int d, x, y, ax, ay, sx, sy, Δx, Δy;
////      color32_t color=rgb ( B, G, R );
//      unsigned char *dst=(unsigned char *)m_pcolorref;
//
//      Δx=x2-x1;
//      ax=abs ( Δx )<<1;
//      sx=(Δx<0) ? -1 : 1;
//      Δy=y2-y1;
//      ay=abs ( Δy )<<1;
//      sy=(Δy<0) ? -1 : 1;
//      x=x1;
//      y=y1;
//
//      if ( ax>ay )
//      {
//         d=ay-(ax>>1);
//         while ( x!=x2 )
//         {
//            dst[(y*cx+x)<<2]=(unsigned char)(((B-dst[(y*cx+x)<<2])*A+(dst[(y*cx+x)<<2]<<8))>>8);
//            dst[((y*cx+x)<<2)+1]=(unsigned char)(((G-dst[((y*cx+x)<<2)+1])*A+(dst[((y*cx+x)<<2)+1]<<8))>>8);
//            dst[((y*cx+x)<<2)+2]=(unsigned char)(((R-dst[((y*cx+x)<<2)+2])*A+(dst[((y*cx+x)<<2)+2]<<8))>>8);
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
//            dst[(y*cx+x)<<2]=(unsigned char)(((B-dst[(y*cx+x)<<2])*A+(dst[(y*cx+x)<<2]<<8))>>8);
//            dst[((y*cx+x)<<2)+1]=(unsigned char)(((G-dst[((y*cx+x)<<2)+1])*A+(dst[((y*cx+x)<<2)+1]<<8))>>8);
//            dst[((y*cx+x)<<2)+2]=(unsigned char)(((R-dst[((y*cx+x)<<2)+2])*A+(dst[((y*cx+x)<<2)+2]<<8))>>8);
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

   //void image::Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask)
   //{
   //   color32_t crFind = rgb(::blue(crMask), ::green(crMask), ::red(crMask));
   //   color32_t crSet = rgb(::blue(crInMask), ::green(crInMask), ::red(crInMask));
   //   color32_t crUnset  = rgb(::blue(crOutMask), ::green(crOutMask), ::red(crOutMask));

   //   int size=cx*cy;

   //   for ( int i=0; i<size; i++ )
   //      if(m_pcolorref[i]== crFind)
   //         m_pcolorref[i] = crSet;
   //      else
   //         m_pcolorref[i] = crUnset;

   //}

   //void image::transparent_color(::color::color color)
   //{
   //   color32_t crFind = color.get_rgb();
   //   long long size = area();

   //   for ( int i=0; i<size; i++ )
   //      if((m_pcolorref[i] & 0x00ffffff) == crFind)
   //         ((LPBYTE)&m_pcolorref[i])[3] = 255;
   //      else
   //         ((LPBYTE)&m_pcolorref[i])[3] = 0;
   //}

   //void image::color::e_channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, color::color::color::rgba::echannel echannel)
   //{
   //   int size = cx * cy;
   //   uchar * puch = (uchar * ) m_pcolorref;
   //   puch += ((int) echannel) % 4;

   //   for(int i = 0; i < size; i++)
   //   {
   //      if(*puch == uchFind)
   //         *puch = uchSet;
   //      else
   //         *puch = uchUnset;
   //      puch += 4;
   //   }
   //}

   //unsigned int image::GetPixel(int x, int y)
   //{
   //   unsigned int dw = *(m_pcolorref + x + (cy - y - 1) * cx);
   //   return rgb(::blue(dw), ::green(dw), ::red(dw));
   //}

   // too slow for animation on AMD XP gen_hon.
   // TOP SUGGESTION:
   // The gradient cant have more then 256 levels of the most bright color
   // (white). So creating a radial fill of radius 256 and then using fasting
   // stretching algorithms is much faster than calculating radial fill.
//   void image::RadialFill(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue, int xCenter, int yCenter, int iRadius)
//   {
//      if (iRadius == 0)
//         return;
//      /*if(version == 0)
//      {
//
//         int iR = iRadius - 1;
//
//         int xL = xCenter - iR;
//         int xU = xCenter + iR;
//         int yL = yCenter - iR;
//         int yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         unsigned char *dst = ((unsigned char*)(m_pcolorref + xL + yL * cx));
//         unsigned int dwAdd = ((cx - 1 - xU) + xL) * 4;
//         int size=cx*cy;
//         double iLevel;
//
//         int Δx, Δy;
//         int dx0, dy0;
//         int dx1, dy1;
//         int dx2, dy2;
//         int dx3, dy3;
//         int dx4, dy4;
//         int dx5, dy5;
//         int dx6, dy6;
//         int dx7, dy7;
//         int dx8, dy8;
//         int dx9, dy9;
//         int dxA, dyA;
//         int dxB, dyB;
//         int dxC, dyC;
//         int dxD, dyD;
//         int dxE, dyE;
//         int dxF, dyF;
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
//         int x, y;
//
//         {
//            for(y = yL; y <= yU; y++)
//            {
//               for(x = xL; x <= xU; x++)
//               {
//                  Δx = abs(x - xCenter);
//                  Δy = abs(y - yCenter);
//                  isqrt((Δx * Δx) + (Δy * Δy), &dr, &dq);
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
//         LPBYTE lpbAlloc = (LPBYTE) malloc((iRadius * iRadius) + 4);
//         LPBYTE lpb = (LPBYTE) (((int) lpbAlloc + 3) & ~3);
//
//
//         int x, y;
//         int b;
//
////         int r2 = iRadius * iRadius;
//
//         for(y = 0; y < iRadius; y++)
//         {
//            for(x = y; x < iRadius; x++)
//            {
//               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
//               if(b > 255)
//                  b = 0;
//               else
//                  b = 255 - b;
//
//
//               lpb[x + y * iRadius] = (unsigned char) b;
//               lpb[y + x * iRadius] = (unsigned char) b;
//            }
//         }
//
//
//         int iR = iRadius - 1;
//
//         int xL = xCenter - iR;
//         int xU = xCenter + iR;
//         int yL = yCenter - iR;
//         int yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         unsigned char *dst = ((unsigned char*)(m_pcolorref + xL + yL * cx));
//         unsigned int dwAdd = ((cx - 1 - xU) + xL) * 4;
////         int size=cx*cy;
//
//         int Δx, Δy;
//
//         // Top Left
//
//         for(y = yL; y <= yU; y++)
//         {
//            for(x = xL; x <= xU; x++)
//            {
//               Δx = abs(x - xCenter);
//               Δy = abs(y - yCenter);
//               b = lpb[Δx + Δy * iRadius];
//               dst[0] = (unsigned char) (blue     * b / 255);
//               dst[1] = (unsigned char) (green    * b / 255);
//               dst[2] = (unsigned char) (red      * b / 255);
//               dst[3] = (unsigned char) (alpha    * b / 255);
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
//      unsigned char alpha1, unsigned char red1, unsigned char green1, unsigned char blue1,
//      unsigned char alpha2, unsigned char red2, unsigned char green2, unsigned char blue2,
//      int xCenter, int yCenter, int iRadius)
//   {
//      if (iRadius == 0)
//         return;
//      /*if(version == 0)
//      {
//
//         int iR = iRadius - 1;
//
//         int xL = xCenter - iR;
//         int xU = xCenter + iR;
//         int yL = yCenter - iR;
//         int yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         unsigned char *dst = ((unsigned char*)(m_pcolorref + xL + yL * cx));
//         unsigned int dwAdd = ((cx - 1 - xU) + xL) * 4;
//         int size=cx*cy;
//         double iLevel;
//
//         int Δx, Δy;
//         int dx0, dy0;
//         int dx1, dy1;
//         int dx2, dy2;
//         int dx3, dy3;
//         int dx4, dy4;
//         int dx5, dy5;
//         int dx6, dy6;
//         int dx7, dy7;
//         int dx8, dy8;
//         int dx9, dy9;
//         int dxA, dyA;
//         int dxB, dyB;
//         int dxC, dyC;
//         int dxD, dyD;
//         int dxE, dyE;
//         int dxF, dyF;
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
//         int x, y;
//
//         {
//            for(y = yL; y <= yU; y++)
//            {
//               for(x = xL; x <= xU; x++)
//               {
//                  Δx = abs(x - xCenter);
//                  Δy = abs(y - yCenter);
//                  isqrt((Δx * Δx) + (Δy * Δy), &dr, &dq);
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
//         LPBYTE lpbAlloc = (LPBYTE) malloc((iRadius * iRadius) + 4);
//         LPBYTE lpb = (LPBYTE) (((iptr) lpbAlloc + 3) & ~3);
//
//
//         int x, y;
//         int b;
//
////         int r2 = iRadius * iRadius;
//
//         for(y = 0; y < iRadius; y++)
//         {
//            for(x = y; x < iRadius; x++)
//            {
//               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
//               if(b > 255)
//                  b = 0;
//               else
//                  b = ~b;
//
//
//               lpb[x + y * iRadius] = (unsigned char) b;
//               lpb[y + x * iRadius] = (unsigned char) b;
//            }
//         }
//
//
//         int iR = iRadius - 1;
//
//         int xL = xCenter - iR;
//         int xU = xCenter + iR;
//         int yL = yCenter - iR;
//         int yU = yCenter + iR;
//
//
//         if(xL < 0) xL = 0;
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         unsigned char *dst = ((unsigned char*)(m_pcolorref + xL + yL * cx));
//         unsigned int dwAdd = ((cx - 1 - xU) + xL) * 4;
////         int size=cx*cy;
//
//         int Δx, Δy;
//
//         unsigned char bComp;
//
//         // Top Left
//
//         for(y = yL; y <= yU; y++)
//         {
//            for(x = xL; x <= xU; x++)
//            {
//               Δx = abs(x - xCenter);
//               Δy = abs(y - yCenter);
//               b = lpb[Δx + Δy * iRadius];
//               bComp = (unsigned char) ~b;
//               dst[0] = (unsigned char) (((blue1  * b) + (blue2  * bComp)) / 255);
//               dst[1] = (unsigned char) (((green1 * b) + (green2 * bComp)) / 255);
//               dst[2] = (unsigned char) (((red1   * b) + (red2   * bComp)) / 255);
//               dst[3] = (unsigned char) (((alpha1 * b) + (alpha2 * bComp)) / 255);
//               dst += 4;
//            }
//            dst += dwAdd;
//         }
//
//         free(lpbAlloc);
//      }
//   }

   void image::SetIconMask(::image::icon * picon, int cx, int cy)
   {
      create(cx, cy);

      if(cx <= 0 || cy <= 0)
         return;




      // White blend image
      ::image::image pimage1(this);
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
      ::image::image pimage2;
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
      ::image::image pimageM(this);
      imageM = create_image({cx,  cy});

      imageM.m_spgraphics->DrawIcon(
      0, 0,
      picon,
      cx, cy,
      0,
      nullptr,
      DI_MASK);

      unsigned char * r1=(unsigned char*)pimage1->m_pcolorref;
      unsigned char * r2=(unsigned char*)pimage2->get_data();
      unsigned char * srcM=(unsigned char*)imageM.m_pcolorref;
      unsigned char * dest=(unsigned char*)m_pcolorref;
      int iSize = cx*cy;

      unsigned char b;
      unsigned char bMax;
      while ( iSize-- > 0)
      {
         if(srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b =(unsigned char)(r1[0]  - r2[0]);
            bMax = maximum(b, bMax);
            b =(unsigned char)(r1[1]  - r2[1]);
            bMax = maximum(b, bMax);
            b =(unsigned char)(r1[2]  - r2[2]);
            bMax = maximum(b, bMax);
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

   //void image::rotate(::image::image *pimage, double dAngle, double dScale)
   //{
   //  // ::image::image pimage;
   ////   pimage->Paste(this);

   //   int cx = this->cx;
   //   int cy = this->cy;

   //   int l = maximum(cx, cy);

   //
   //   int jmax = minimum(l, cy / 2);
   //   int jmin = - jmax;
   //   int imax = minimum(l, cx / 2);
   //   int imin = - imax;


   //   int joff = cy / 2;
   //   int ioff = cx / 2;

   //   //int iAngle = iStep % 360;
   //   //int iAngle = iStep;
   //   //int iAngle = 1;
   //   //int k = 0;

   ///*     for ( int j=jmin; j<jmax; j++ )
   //   {
   //      for ( int i=imin; i<imax; i++ )
   //      {
   //         int x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
   //         y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->m_pcolorref[abs(y%cy)*cx+abs(x%cx)];
   //         //k++;
   //      }
   //      (j+joff)*cx+(i+ioff)
   //   }*/

   //   int k = 0;
   //   double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
   //   double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
   //   int cx1 = cx - 1;
   //   int cy1 = cy - 1;
   //     for ( int j=jmin; j<jmax; j++ )
   //   {
   //      for ( int i=imin; i<imax; i++ )
   //      {
   //         int x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         //x=abs((int(dCos * i - dSin * j) + ioff) % cx);
   //         //y=abs((int(dSin * i + dCos * j) + joff) % cy);

   //         x = (int) abs((dCos * i - dSin * j) + ioff);
   //         y = (int) abs((dSin * i + dCos * j) + joff);

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


   //
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}


   //void image::Rotate034(::image::image *pimage, double dAngle, double dScale)
   //{
   //
   //   int cx = this->cx;
   //   int cy = this->cy;

   //   int l = maximum(cx, cy);

   //
   //   int jmax = minimum(l, cy / 2);
   //   int jmin = - jmax;
   //   int imax = minimum(l, cx / 2);
   //   int imin = - imax;


   //   if((cy % 2) == 1)
   //      jmax++;

   //   if((cx % 2) == 1)
   //      imax++;
   //
   //   int joff = cy / 2;
   //   int ioff = cx / 2;

   //
   //   int k = 0;
   //   double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
   //   double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
   //   int cx1 = cx - 1;
   //   int cy1 = cy - 1;
   //     for ( int j=jmin; j<jmax; j++ )
   //   {
   //      for ( int i=imin; i<imax; i++ )
   //      {
   //         int x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         //x=abs((int(dCos * i - dSin * j) + ioff) % cx);
   //         //y=abs((int(dSin * i + dCos * j) + joff) % cy);

   //         x = (int) abs((dCos * i - dSin * j) + ioff);
   //         y = (int) abs((dSin * i + dCos * j) + joff);

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


   //
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}

   //void image::rotate(
   //   ::image::image *pimage,
   //   const ::double_rectangle & rectangle,
   //   double dAngle,
   //   double dScale)
   //{
   //  // ::image::image pimage;
   ////   pimage->Paste(this);



   //   ::double_rectangle rectangle(rectangle);

   //   int cx = rectangle.width();
   //   int cy = rectangle.height();

   //   int l = maximum(cx, cy);
   //
   //   int jmax = minimum(l, cy / 2);
   //   int jmin = - jmax;
   //   int imax = minimum(l, cx / 2);
   //   int imin = - imax;


   //   int joff = cy / 2 + rectangle.left;
   //   int ioff = cx / 2 + rectangle.top;

   //   //int iAngle = iStep % 360;
   //   //int iAngle = iStep;
   //   //int iAngle = 1;
   //   //int k = 0;

   ///*     for ( int j=jmin; j<jmax; j++ )
   //   {
   //      for ( int i=imin; i<imax; i++ )
   //      {
   //         int x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
   //         y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->m_pcolorref[abs(y%cy)*cx+abs(x%cx)];
   //         //k++;
   //      }
   //      (j+joff)*cx+(i+ioff)
   //   }*/

   //   int k = 0;
   //   double dCos = ::cos(dAngle * dPi / 180.0) * dScale;
   //   double dSin = ::sin(dAngle * dPi / 180.0) * dScale;
   //   int cx1 = cx - 1;
   //   int cy1 = cy - 1;
   //     for ( int j=jmin; j<jmax; j++ )
   //   {
   //      for ( int i=imin; i<imax; i++ )
   //      {
   //         int x, y;

   //         // A Combination of a 2d Translation/rotation/Scale Matrix
   //         //x=abs((int(dCos * i - dSin * j) + ioff) % cx);
   //         //y=abs((int(dSin * i + dCos * j) + joff) % cy);

   //         x = (int) abs((dCos * i - dSin * j) + ioff);
   //         y = (int) abs((dSin * i + dCos * j) + joff);

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


   //
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}

   ///*int image::cos(int i, int iAngle)
   //{
   //   return (int) (((_int64) i * CosN[iAngle]) >> 32);
   //}

   //int image::sin(int i, int iAngle)
   //{
   //   return (int) (((_int64) i * SinN[iAngle]) >> 32);
   //}*/




   //void image::Fill (int A, int R, int G, int B )
   //{
   //   color32_t color = rgb ( B, G, R ) | (A << 24);
   //   int size=cx*cy;

   //   color32_t * pcr;

   //   long long iSize32 = size / 32;
   //   int i;
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
   //   int iRLine;
   //   int iGLine;
   //   int iBLine;
   //   double dDiv = cx * cy;
   //   if(dDiv > 0)
   //   {
   //      LPBYTE lpb = (LPBYTE) m_pcolorref;
   //      for (int y = 0; y < cy; y++)
   //      {
   //         iRLine = 0;
   //         iGLine = 0;
   //         iBLine = 0;
   //         for (int x = 0; x < cx; x++)
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
   //      int iR = (int) dR;
   //      int iG = (int) dG;
   //      int iB = (int) dB;
   //      return rgb(iR, iG, iB);
   //   }
   //   else
   //   {
   //      return 0;
   //   }
   //
   //}


   //void image::xor(::image::image *pimage)
   //{
   //   if(cx != pimage->cx
   //   || cy != pimage->cy)
   //   {
   //      return;
   //   }
   //   int iCount = cx * cy;
   //   LPDWORD lpd1 = (LPDWORD) m_pcolorref;
   //   LPDWORD lpd2 = (LPDWORD) pimage->get_data();
   //   for(int i = 0; i < iCount; i++)
   //   {
   //      *lpd1 = *lpd1 ^ *lpd2;
   //      lpd1++;
   //      lpd2++;
   //   }
   //}

   //void image::create_frame(::size size, int iFrameCount)
   //{
   //   int iSliceCount = (int) sqrt((double) iFrameCount);
   //   int iFrameWidth = size.cx / iSliceCount;
   //   int iFrameHeight = size.cy / iSliceCount;
   //   create(iFrameWidth, iFrameHeight);
   //}

   //void image::set_frame1(void * lpdata, int iFrame, int iFrameCount)
   //{
   //   int iSliceCount = (int) sqrt((double) iFrameCount);
   //   if(iSliceCount == 0)
   //      iSliceCount = 1;
   //   int iFrameWidth = cx / iSliceCount;
   //   int iFrameHeight = cy / iSliceCount;
   //   int iX = iFrame % iSliceCount;
   //   int iY = iFrame / iSliceCount;
   //   color32_t * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * cx];
   //   color32_t * lpSrc = (color32_t *) lpdata;
   //   color32_t * lpDestLine;
   //   for(int y = 0; y < iFrameHeight; y++)
   //   {
   //      lpDestLine = &lpDest[y * cx];
   //      for(int x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDestLine = *lpSrc;
   //          lpDestLine++;
   //          lpSrc++;
   //      }
   //   }
   //}

   //void image::set_frame2(void * lpdata, int iFrame, int iFrameCount)
   //{
   //   if(lpdata == nullptr)
   //      return;
   //   int iSliceCount = (int) sqrt((double) iFrameCount);
   //   if(iSliceCount == 0)
   //      iSliceCount = 1;
   //   int iFrameWidth = cx / iSliceCount;
   //   int iFrameHeight = cy / iSliceCount;
   //   int iX = iFrame % iSliceCount;
   //   int iY = iFrame / iSliceCount;
   //   color32_t * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * cx];
   //   color32_t * lpSrc = (color32_t *) lpdata;
   //   color32_t * lpDestLine;
   //   for(int y = iFrameHeight - 1; y >= 0; y--)
   //   {
   //      lpDestLine = &lpDest[y * cx];
   //      for(int x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDestLine = *lpSrc;
   //          lpDestLine++;
   //          lpSrc++;
   //      }
   //   }
   //}

   //void image::xor_image_frame2(void * lpdata, int iFrame, int iFrameCount)
   //{
   //   if(lpdata == nullptr)
   //      return;
   //   int iSliceCount = (int) sqrt((double) iFrameCount);
   //   if(iSliceCount == 0)
   //      iSliceCount = 1;
   //   int iFrameWidth = cx / iSliceCount;
   //   int iFrameHeight = cy / iSliceCount;
   //   int iX = iFrame % iSliceCount;
   //   int iY = iFrame / iSliceCount;
   //   color32_t * lpDest = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight * cx];
   //   color32_t * lpSrc = (color32_t *) lpdata;
   //   color32_t * lpDestLine;
   //   for(int y = iFrameHeight - 1; y >= 0; y--)
   //   {
   //      lpDestLine = &lpDest[y * cx];
   //      for(int x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDestLine ^= *lpSrc;
   //          lpDestLine++;
   //          lpSrc++;
   //      }
   //   }
   //}

   //void image::get_frame(void * lpdata, int iFrame, int iFrameCount)
   //{
   //   int iSliceCount = (int) sqrt((double) iFrameCount);
   //   int iFrameWidth = cx / iSliceCount;
   //   int iFrameHeight = cy / iSliceCount;
   //   int iX = iFrame % iSliceCount;
   //   int iY = iFrame / iSliceCount;
   //   color32_t * lpSrc = &m_pcolorref[iFrameWidth * iX + iY * iFrameHeight *  cx];
   //   color32_t * lpDest = (color32_t *) lpdata;
   //   color32_t * lpSrcLine;
   //   for(int y = 0; y < iFrameHeight; y++)
   //   {
   //      lpSrcLine = &lpSrc[y * cx];
   //      for(int x = 0; x < iFrameWidth; x++)
   //      {
   //          *lpDest = *lpSrcLine;
   //          lpDest++;
   //          lpSrcLine++;
   //      }
   //   }
   //}

   //bool image::is_rgb_black()
   //{
   //   int iSize = cx * cy;
   //   color32_t * lp = m_pcolorref;
   //   for(int i = 0; i < iSize; i++)
   //   {
   //      if((*lp & 0x00FFFFFF) != 0)
   //         return false;
   //      lp++;
   //   }
   //   return true;
   //}

   //void image::DivideRGB(int iDivide)
   //{
   //   if(iDivide == 0)
   //   {
   //      return;
   //   }
   //   int iCount = cx * cy;
   //   LPBYTE lp = ((LPBYTE) m_pcolorref);
   //   int i = 0;
   //   int iCount1 = iCount - iCount % 8;
   //   for(; i < iCount1; i++)
   //   {
   //      lp[0] /= (unsigned char) iDivide;
   //      lp[1] /= (unsigned char) iDivide;
   //      lp[2] /= (unsigned char) iDivide;

   //      lp[4] /= (unsigned char) iDivide;
   //      lp[5] /= (unsigned char) iDivide;
   //      lp[6] /= (unsigned char) iDivide;

   //      lp[8] /= (unsigned char) iDivide;
   //      lp[9] /= (unsigned char) iDivide;
   //      lp[10] /= (unsigned char) iDivide;

   //      lp[12] /= (unsigned char) iDivide;
   //      lp[13] /= (unsigned char) iDivide;
   //      lp[14] /= (unsigned char) iDivide;

   //      lp[16] /= (unsigned char) iDivide;
   //      lp[17] /= (unsigned char) iDivide;
   //      lp[28] /= (unsigned char) iDivide;

   //      lp[20] /= (unsigned char) iDivide;
   //      lp[21] /= (unsigned char) iDivide;
   //      lp[22] /= (unsigned char) iDivide;

   //      lp[24] /= (unsigned char) iDivide;
   //      lp[25] /= (unsigned char) iDivide;
   //      lp[26] /= (unsigned char) iDivide;

   //      lp[28] /= (unsigned char) iDivide;
   //      lp[29] /= (unsigned char) iDivide;
   //      lp[30] /= (unsigned char) iDivide;

   //      lp += 4 * 8;
   //   }
   //   for(; i < iCount; i++)
   //   {
   //      lp[0] /= (unsigned char) iDivide;
   //      lp[1] /= (unsigned char) iDivide;
   //      lp[2] /= (unsigned char) iDivide;
   //      lp +=4;
   //   }
   //}

   //void image::DivideARGB(int iDivide)
   //{
   //   if(iDivide == 0)
   //   {
   //      return;
   //   }
   //   int iCount = cx * cy;
   //   LPBYTE lp = ((LPBYTE) m_pcolorref);
   //   for(int i = 0; i < iCount; i++)
   //   {
   //      lp[0] /= (unsigned char) iDivide;
   //      lp[1] /= (unsigned char) iDivide;
   //      lp[2] /= (unsigned char) iDivide;
   //      lp[3] /= (unsigned char) iDivide;
   //      lp +=4;
   //   }
   //}

   //void image::DivideA(int iDivide)
   //{
   //   if(iDivide == 0)
   //   {
   //      return;
   //   }
   //   int iCount = cx * cy;
   //   LPBYTE lp = ((LPBYTE) m_pcolorref);
   //   for(int i = 0; i < iCount; i++)
   //   {
   //      lp[3] /= (unsigned char) iDivide;
   //      lp +=4;
   //   }
   //}


   void image::stretch_image(::image::image *pimage)
   {

      if (area() <= 0 || pimage->area() <= 0)
         return;

      //plusplus::rectF rectangleDest(0, 0, (plusplus::REAL) m_size.cx, (plusplus::REAL) m_size.cy);

      //plusplus::rectF rectangleSource(0, 0, (plusplus::REAL) pimage->width(), (plusplus::REAL) pimage->height());

      unmap();
      pimage->unmap();

      m_spgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //((plusplus::Graphics * ) m_spgraphics->get_os_data())->DrawImage(((plusplus::Bitmap *)pimage->get_bitmap()->get_os_data()), rectangleDest, rectangleSource, plusplus::UnitPixel);

   }


   ::draw2d::graphics * pimage::get_graphics() const
   {
      ((image *) this)->unmap();

      m_spgraphics->SelectObject(m_pbitmap);

      return m_spgraphics;

   }


   // double image::pi()
   // {
   //    return dPi;
   // }

   // void image::fill_channel(int intensity, color::color::color::rgba::echannel echannel)
   // {
   //     int offset = ((int)echannel) % 4;
   //    int size=m_size.cx*cy;

   //    unsigned char * pb;

   //    int iSize32 = size;
   //    int i;
   //    for (i=0; i < iSize32; i+=32 )
   //    {
   //       pb = ((unsigned char * ) &m_pcolorref[i]) + offset;
   //       pb[0 * 4] = (unsigned char) intensity;
   //       pb[1 * 4] = (unsigned char) intensity;
   //       pb[2 * 4] = (unsigned char) intensity;
   //       pb[3 * 4] = (unsigned char) intensity;
   //       pb[4 * 4] = (unsigned char) intensity;
   //       pb[5 * 4] = (unsigned char) intensity;
   //       pb[6 * 4] = (unsigned char) intensity;
   //       pb[7 * 4] = (unsigned char) intensity;
   //       pb[8 * 4] = (unsigned char) intensity;
   //       pb[9 * 4] = (unsigned char) intensity;
   //       pb[10 * 4] = (unsigned char) intensity;
   //       pb[11 * 4] = (unsigned char) intensity;
   //       pb[12 * 4] = (unsigned char) intensity;
   //       pb[13 * 4] = (unsigned char) intensity;
   //       pb[14 * 4] = (unsigned char) intensity;
   //       pb[15 * 4] = (unsigned char) intensity;
   //       pb[16 * 4] = (unsigned char) intensity;
   //       pb[17 * 4] = (unsigned char) intensity;
   //       pb[18 * 4] = (unsigned char) intensity;
   //       pb[19 * 4] = (unsigned char) intensity;
   //       pb[20 * 4] = (unsigned char) intensity;
   //       pb[21 * 4] = (unsigned char) intensity;
   //       pb[22 * 4] = (unsigned char) intensity;
   //       pb[23 * 4] = (unsigned char) intensity;
   //       pb[24 * 4] = (unsigned char) intensity;
   //       pb[25 * 4] = (unsigned char) intensity;
   //       pb[26 * 4] = (unsigned char) intensity;
   //       pb[27 * 4] = (unsigned char) intensity;
   //       pb[28 * 4] = (unsigned char) intensity;
   //       pb[29 * 4] = (unsigned char) intensity;
   //       pb[30 * 4] = (unsigned char) intensity;
   //       pb[31 * 4] = (unsigned char) intensity;
   //    }

   //    for (; i<size; i++ )
   //    {
   //       *(((unsigned char * ) &m_pcolorref[i]) + offset) = (unsigned char) intensity;
   //    }
   //}


   // int image::cos(int i, int iAngle)
   // {
   //    return (int) (((_int64) i * CosN[iAngle]) >> 31);
   // }

   // int image::sin(int i, int iAngle)
   // {
   //    return (int) (((_int64) i * SinN[iAngle]) >> 31);
   // }

   // int image::cos10(int i, int iAngle)
   // {
   //    return (int) (((_int64) i * Cos10N[iAngle]) >> 34);
   // }

   // int image::sin10(int i, int iAngle)
   // {
   //    return (int) (((_int64) i * Sin10N[iAngle]) >> 34);
   // }

   /*   int image::width()
      {
         return m_size.cx;
      }

      int image::height()
      {
         return cy;
      }
      */


//#define NO_SCREEN_PRE_MULTIPLY_ALPHA 0
//
//   bool image::update_window(::aura::draw_interface * puserinteraction,::message::message * pmessage,bool bTransferBuffer)
//   {
//
//
//      rect64 rectangleWindow;
//
//      puserinteraction->window_rectangle(rectangleWindow);
//
////#if !NO_SCREEN_PRE_MULTIPLY_ALPHA
////      if(bTransferBuffer && puserinteraction->is_composite() && !m_bReduced)
////      {
////
////         m_bReduced = true;
////
////         m_spgraphics->set_origin(0,0);
////
////         map();
////
////         //pre_multiply_alpha((unsigned int *) get_data(),m_size.cx,m_size.cy,m_size.cx * 4);
////
////         unsigned char *dstR=(unsigned char*)get_data();
////         unsigned char *dstG=dstR + 1;
////         unsigned char *dstB=dstR + 2;
////         unsigned char *dstA=dstR + 3;
////         long long size = area() * 4;
////
////
////         // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255
//////#if defined(_OPENMP)
//////         #pragma omp parallel num_threads(3)
//////                  {
//////
//////                     unsigned char *dst = dstR + omp_get_thread_num();
//////      #pragma omp parallel for
//////                     for(::collection::index i = 0; i < size; i+=4)
//////                     {
//////                           dst[i] = lower_byte(((int)dst[i] * (int)dstA[i]) >> 8);
//////                     }
//////                  }
//////
////////#pragma omp parallel num_threads(4)
////////         {
////////
////////            if(omp_get_thread_num() == 3)
////////            {
////////               color32_t *dst = get_data();
////////#pragma omp parallel for
////////               for(::collection::index i = 0; i < size; i+=4)
////////               {
////////                  if(dstA[i] <= 3)
////////                  {
////////                     dst[i>>2] = 0;
////////                  }
////////               }
////////            }
////////            else
////////            {
////////               unsigned char *dst = dstR + omp_get_thread_num();
////////#pragma omp parallel for
////////               for(::collection::index i = 0; i < size; i+=4)
////////               {
////////                  if(dstA[i] > 3)
////////                  {
////////                     dst[i] = lower_byte(((int)dst[i] * (int)dstA[i]) >> 8);
////////                  }
////////               }
////////            }
////////         }
//////#else
//////         for(::collection::index i = 0; i < size; i+=4)
//////         {
//////            dstR[i] = lower_byte(((int)dstR[i] * (int)dstA[i]) >> 8);
//////            dstG[i] = lower_byte(((int)dstG[i] * (int)dstA[i]) >> 8);
//////            dstB[i] = lower_byte(((int)dstB[i] * (int)dstA[i]) >> 8);
//////         }
//////#endif
//////
////      }
////#endif
//      ::double_rectangle rectangle(rectangleWindow);
//
//      // Copy the contents of the framebuffer - which in our case is our pbuffer -
//      // to our bitmap image in local system memory. Notice that we also need
//      // to invert the pbuffer's pixel data since OpenGL by default orients the
//      // bitmap image bottom up. Our Windows DIB wrapper expects images to be
//      // top down in orientation.
//
//      //synchronous_lock synchronouslock(&m);
//
//      glFlush();
//
//      ::pointer<bitmap>b = m_pbitmap;
//
//      b->defer_reveal();
//
//      {
//         // This is a special case. When the image width is already a multiple
//         // of 4 the image does not require any padding bytes at the end of each
//         // scan line. Consequently we do not need to address each scan line
//         // separately. This is much faster than the below case where the image
//         // width is not a multiple of 4.
//
//         int totalBytes = b->m_sizeOut.cx * b.m_sizeOut.cy * 4;
//         unsigned char * p = (unsigned char*)b->m_memOut.get_data();
//         for (int i = 0; i < totalBytes; i += 4)
//         {
//            p[0] = (unsigned char)(p[0] * p[3] / 255);
//            p[1] = (unsigned char)(p[1] * p[3] / 255);
//            p[2] = (unsigned char)(p[2] * p[3] / 255);
//            p+=4;
//         }
//      }
//
//
//      puserinteraction->get_window_graphics()->update_window(puserinteraction->get_handle(),(color32_t*)b->m_memOut.get_data(),rectangle, b->m_sizeOut.cx, b.m_sizeOut.cy, b.m_sizeOut.cx * 4,bTransferBuffer);
//      b->m_bFlashed = true;
//
//      return true;
//
//   }
//
//
//   bool image::print_window(::aura::draw_interface * puserinteraction,::message::message * pmessage)
//   {
//
//      ::pointer<::user::message>pusermessage(pmessage);
//
//      if(pusermessage->m_wparam == nullptr)
//         return false;
//
//      m_spgraphics->attach((HDC) pusermessage->m_wparam);
//
//      ::double_rectangle rectx;
//
//      ::draw2d::bitmap * pbitmap = m_spgraphics->get_current_bitmap();
//
//      ::GetCurrentObject((HDC) pusermessage->m_wparam, OBJ_BITMAP);
//
//      //      unsigned int dw = ::get_last_error();
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
//         ::double_rectangle rectangleWindow;
//
//         puserinteraction->window_rectangle(rectangleWindow);
//
//         ::image::image pimage;
//
//         if(!pimage = create_image(rectangleWindow.bottom_right()))
//            return false;
//
//         ::draw2d::graphics * pgraphics = pimage->get_graphics();
//
//         if(pgraphics->get_os_data() == nullptr)
//            return false;
//
//         ::double_rectangle rectanglePaint;
//         ::double_rectangle rectangleUpdate;
//         rectangleUpdate = rectangleWindow;
//         rectanglePaint = rectangleWindow;
//         rectanglePaint.offset(-rectanglePaint.top_left());
//         m_spgraphics->SelectClipRgn(nullptr);
//         puserinteraction->_001OnDeferPaintLayeredWindowBackground(pimage->get_graphics());
//         m_spgraphics->SelectClipRgn(nullptr);
//         m_spgraphics-> set_origin(::int_point());
//         puserinteraction->_000OnDraw(pimage->get_graphics());
//         m_spgraphics->set_origin(::int_point());
//         //(dynamic_cast<::win::graphics * >(pgraphics))->FillSolidRect(rectangleUpdate.left, rectangleUpdate.top, 100, 100, 255);
//         m_spgraphics->SelectClipRgn(nullptr);
//         m_spgraphics->set_origin(::int_point());
//
//         m_spgraphics->SelectClipRgn( nullptr);
//         m_spgraphics->BitBlt(rectanglePaint.left, rectanglePaint.top,
//            rectanglePaint.width(), rectanglePaint.height(),
//            pgraphics, rectangleUpdate.left, rectangleUpdate.top,
//            SRCCOPY);
//
//      }
//      catch(...)
//      {
//      }
//      m_spgraphics->FillSolidRect(rectx, rgb(255, 255, 255));
//      pmessage->m_bRet = true;
//      pusermessage->set_lresult(0);
//
//      return true;
//
//   }
//




   void image::map(bool bApplyTransform) const
   {
      __UNREFERENCED_PARAMETER(bApplyTransform);

      if (!m_bMapped)
      {

         ((image*)this)->m_bMapped = true;

      }

      if (m_pbitmap.is_set())
      {

         m_pbitmap.cast < bitmap >()->defer_reveal();

      }

//      if (m_spgraphics.is_null())
      //       return;

      //  m_spgraphics->flush();

   }


   void image::unmap() const
   {
      if (m_bMapped)
      {
         if (m_spgraphics.is_set())
         {
            ((image*)this)->m_point = m_spgraphics.get_origin();

         }

         ((image*)this)->m_bMapped = false;

      }


      if (m_pbitmap.is_set())
      {

         m_pbitmap.cast < bitmap >()->flash();

      }

      //m_spgraphics->SelectObject(m_pbitmap);

   }



} // namespace typeface_freetype



