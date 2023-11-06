#include "framework.h"
#include "_opengl.h"
#include "image.h"


namespace draw2d_opengl
{


   image::image()
   {

      m_sizeWnd.cx()         = 0;
      m_sizeWnd.cy()         = 0;
      m_hbitmap            = nullptr;
      m_phost = nullptr;
      zero(m_bitmapinfo);

   }


   ::draw2d::bitmap_pointer image::get_bitmap() const
   {

      return m_pbitmap;

   }


   ::draw2d::bitmap_pointer image::detach_bitmap()
   {
      return m_pbitmap.detach();
   }



   //void    image::construct (i32 cx,  i32 cy)
   //{
   //   m_pcolorref    = nullptr;
   //   cx             = 0;
   //   cy             = 0;
   //   create(cx, cy);
   //}

   image::~image ()
   {

      destroy ();

   }



   void image::create(const ::size_i32& size, ::enum_flag eobjectCreate, int iGoodStride, bool bPreserve)
   {

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && m_size == size)
         //return true;
         return;

      destroy();

      if (size.is_empty())
      {

         //return true;

         return;

      }

      m_bitmapinfo = {};

      int iStride = size.cx() * 4;

      //{
      //   iGoodStride
      //}

      m_bitmapinfo.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
      m_bitmapinfo.bmiHeader.biWidth         = size.cx();
      m_bitmapinfo.bmiHeader.biHeight        =- size.cy();
      m_bitmapinfo.bmiHeader.biPlanes        = 1;
      m_bitmapinfo.bmiHeader.biBitCount      = 32;
      m_bitmapinfo.bmiHeader.biCompression   = BI_RGB;
      m_bitmapinfo.bmiHeader.biSizeImage     = iStride  * size.cy();

      __construct(m_pbitmap);

      image32_t * pimage32 = nullptr;
      m_pbitmap->create_bitmap(nullptr, size, (void **)&pimage32, &iStride);
      //if(!m_pbitmap->create_bitmap(nullptr, size, (void **) & pimage32, &iStride))
      //{

        // return false;

      //}

      if(m_pbitmap->get_os_data() == nullptr)
      {

         destroy();

         //return false;

         return;

      }


      this->init(size, pimage32, iStride);

      m_eflagElement = eobjectCreate;

      set_ok_flag();

      m_estatus = ::success;

      //return true;

   }

   bool image::host(::pixmap * ppixmap)
   {

      if (::is_null(ppixmap) || ppixmap->nok())
      {

         return false;

      }
         
      

      if (ppixmap->m_pimage32Raw == m_pimage32Raw
         && m_size == ppixmap->m_size)
      {

         return true;

      }

      memcpy((::pixmap *) this, ppixmap, sizeof(::pixmap));

      //__construct(m_pbitmap);
      __defer_construct(m_pgraphics);
      //m_pgraphics->set(m_pbitmap);

      m_pgraphics->create_memory_graphics(ppixmap->m_size);


      m_eflagElement = DEFAULT_CREATE_IMAGE_FLAG;

      m_pgraphics->m_pimage = this;

      set_ok_flag();

      m_estatus = ::success;

      return true;

   }

   void image::dc_select(bool bSelect)
   {
      /*      if(bSelect)
            {
               return m_pgraphics->set(m_pbitmap) != nullptr;
            }
            else
            {
               return m_pgraphics->set(m_hbitmapOriginal) != nullptr;
            }*/

      //return true;

   }


   void image::create(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap * pbitmap = (dynamic_cast<::draw2d_opengl::graphics * >(pgraphics))->get_current_bitmap();

      if (pbitmap == nullptr)
      {

         return;
         //return false;

      }

      //if (!create(pbitmap->get_size()))
      create(pbitmap->get_size());
      {
         //return false;//
      }

      from(pgraphics);

      //return true;

   }


   void image::destroy ()
   {

      m_pbitmap.release();

      m_pgraphics.release();

      set_nok();

      //return true;

   }


   //bool image::to(::draw2d::graphics * pgraphics, const ::point_i32& point, const ::size_i32& size, const ::point_i32& pointSrc)
   //{

   //   return pgraphics->draw(point, size, get_graphics(), point);

   //  
   //}


   bool image::from(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap_pointer bitmap;

      bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);

      //auto estatus =
      GL2D_GRAPHICS(pgraphics)->set(bitmap);

      //if (!estatus)
      //{

      //   return false;

      //}

      ::size_i32 size = pgraphics->m_pimage->get_size();

      //if(!create(size))
      create(size);
      //{

      //   return false;

      //}

      throw ::exception(todo, "::opengl::image");

      //bool bOk = GetDIBits(GL2D_HDC(pgraphics), (HBITMAP) pbitmap->get_os_data(), 0, m_size.cy(), get_data(), &(m_bitmapinfo), DIB_RGB_COLORS) != false;

      //GL2D_GRAPHICS(pgraphics)->set(pbitmap);

      //return bOk;

   }


   //bool image::from(point_i32 ptDest, ::draw2d::graphics * pgraphics, const ::point_i32 & point, ::size_i32 sz)
   //{

   //   if (m_pgraphics.is_null())
   //      return false;

   //   return m_pgraphics->BitBlt(ptDest, sz, pgraphics, point_i32) != false;

   //}


   /*void image::Fill ( i32 R, i32 G, i32 B )
   {
      color32_t color=rgb ( B, G, R );
      i64 size = area();

      color32_t * pcr;

      i64 iSize32 = size / 32;
      i32 i;
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

      for (i=0; i<size_i32; i++ )
      {
         m_pcolorref[i]=color;
      }
   }

   void image::set_rgb(i32 R, i32 G, i32 B)
   {
      i64 size = area();

      ::u8 * pbyte = (::u8 *) m_pcolorref;

      i32 i;
      for (i=0; i<size_i32; i++ )
      {
         *pbyte++ = (::u8) R;
         *pbyte++ = (::u8) G;
         *pbyte++ = (::u8) B;
         pbyte++;
      }
   }

   void image::ToAlpha(i32 i)
   {
      ::u8 *dst=(::u8*)m_pcolorref;
      i64 size = area();

      while ( size-- )
      {
         dst[3] = dst[i];
         dst+=4;
      }
   }

   void image::from_alpha()
   {
      ::u8 *dst=(::u8*)m_pcolorref;
      i64 size = area();

      while ( size-- )
      {
         dst[0] = dst[3];
         dst[1] = dst[3];
         dst[2] = dst[3];
         dst+=4;
      }
   }

   //DIB = DIB * SRC_ALPHA

   void image::mult_alpha(image imageWork, bool bPreserveAlpha)
   {
      image::mult_alpha(imageWork, bPreserveAlpha);
      return ;
      /*
      if(area() <= 0)
         return;

      //return image::mult_alpha(nullptr, true);
      image imageWork;

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

   //void image::Map(i32 ToRgb, i32 FromRgb)
   //{
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();

   //   while ( size-- )
   //   {
   //      *dst = (::u8) (*dst == FromRgb ? ToRgb : *dst);
   //      dst+=4;
   //   }
   //}


   //void image::ToAlphaAndFill(i32 i, color32_t color32)
   //{
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();

   //   ::u8 uchB = ::blue(color32);
   //   ::u8 uchG = ::green(color32);
   //   ::u8 uchR = ::red(color32);

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
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();

   //   ::u32 dwB = ::blue(color32);
   //   ::u32 dwG = ::green(color32);
   //   ::u32 dwR = ::red(color32);

   //   while (size-- > 0)
   //   {
   //      dst[3] = dst[0];
   //      dst[0] = (::u8)(((dwB * dst[3]) / 256) & 0xff);
   //      dst[1] = (::u8)(((dwG * dst[3]) / 256) & 0xff);
   //      dst[2] = (::u8)(((dwR * dst[3]) / 256) & 0xff);
   //      dst+=4;
   //   }
   //}


   //void image::BitBlt(imagepimage, i32 op)
   //{
   //   if(op == 123) // zero dest rgb, invert alpha, and OR src rgb
   //   {
   //      i64 isize = area();
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
   //   i64 size = area();
   //   LPBYTE lpb = (LPBYTE) m_pcolorref;
   //   for ( i32 i=0; i<size_i32; i++ )
   //   {
   //      lpb[0] = 255 - lpb[0];
   //      lpb[1] = 255 - lpb[1];
   //      lpb[2] = 255 - lpb[2];
   //      lpb += 4;
   //   }
   //}

   //void image::color::e_channel_invert(color::color::color::rgba::echannel echannel)
   //{
   //   i64 size_i32   = area();
   //   register i64 size_i64 = size / 64;
   //   LPBYTE lpb = (LPBYTE) m_pcolorref;
   //   lpb += ((i32)echannel) % 4;
   //   register i64 i = 0;
   //   for(; i < size_i64; i++)
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
   //   register i64 size = area();
   //   LPBYTE lpb = (LPBYTE) get_data();
   //   lpb += ((i32)echannel) % 4;
   //   register i32 iDiv = 256 * 256;
   //   register i32 iMul = (i32) (dRate * ((double) iDiv));
   //   register i32 iRes;
   //   for(register i64 i = 0; i < size; i++)
   //   {
   //      iRes = *lpb * iMul / iDiv;
   //      *lpb = (::u8) (iRes > 255 ? 255 : iRes);
   //      lpb += 4;
   //   }
   //}

   //void image::FillGlass ( i32 R, i32 G, i32 B, i32 A )
   //{
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)(((B-dst[0])*A+(dst[0]<<8))>>8);
   //      dst[1]=(::u8)(((G-dst[1])*A+(dst[1]<<8))>>8);
   //      dst[2]=(::u8)(((R-dst[2])*A+(dst[2]<<8))>>8);
   //      dst+=4;
   //   }
   //}

   //void image::FillStippledGlass ( i32 R, i32 G, i32 B )
   //{
   //   color32_t color=rgb ( B, G, R );
   //   i32 w=m_size.cx();
   //   i32 h=m_size.cy();

   //   for ( i32 j=0; j<w; j++ )
   //   {
   //      for ( i32 i=0; i<h; i++ )
   //      {
   //         m_pcolorref[j*w+i]=((i+j)&0x1) ? m_pcolorref[j*w+i] : color;
   //      }
   //   }
   //}

   //void imagecopy(image image)
   //{
   //   // If DibSize Wrong Re-create image
   //   if (pimage->get_size() != m_size)
   //      image = create_image (m_size);
   //   // do copy
   //   ::memory_copy ( pimage->get_data(), m_pcolorref, (size_t) area() * sizeof(color32_t) );
   //}


   //void image::Paste ( image image )
   //{
   //   // If DibSize Wrong Re-create image
   //   if (m_size !=pimage.get_size() )
   //      create ( pimage->get_size() );
   //   // do Paste
   //   ::memory_copy ( m_pcolorref, pimage->get_data(), (size_t) area() * sizeof(color32_t) );
   //}

   //bool image::color_blend(color32_t color32, ::u8 bAlpha)
   //{

   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();

   //   ::u32 dwB = ::blue(color32);
   //   ::u32 dwG = ::green(color32);
   //   ::u32 dwR = ::red(color32);
   //
   //   ::u32 dwB_ = dwB << 8;
   //   ::u32 dwG_ = dwG << 8;
   //   ::u32 dwR_ = dwR << 8;
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)(((dst[0]-dwB)*bAlpha+dwB_)>>8);
   //      dst[1]=(::u8)(((dst[1]-dwG)*bAlpha+dwG_)>>8);
   //      dst[2]=(::u8)(((dst[2]-dwG)*bAlpha+dwR_)>>8);
   //      dst+=4;
   //   }
   //   return true;
   //}


   //void image::Blend (image image, i32 A )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
   //      dst[1]=(::u8)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
   //      dst[2]=(::u8)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //bool image::Blend(imagepimage, imagepimageA, i32 A)
   //{
   //   if(size() != pimage->size() ||
   //      size() != imageA.size())
   //      return false;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   ::u8 *alf=(::u8*)imageA.m_pcolorref;
   //   i64 size = area();

   //   A = 2 - A;
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)(((src[0]-dst[0])*alf[A]+(dst[0]<<8))>>8);
   //      dst[1]=(::u8)(((src[1]-dst[1])*alf[A]+(dst[1]<<8))>>8);
   //      dst[2]=(::u8)(((src[2]-dst[2])*alf[A]+(dst[2]<<8))>>8);
   //      dst+=4;
   //      src+=4;
   //      alf+=4;
   //   }

   //   return true;
   //}

   //void image::Darken (image image )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)((src[0]<dst[0]) ? src[0] : dst[0]);
   //      dst[1]=(::u8)((src[1]<dst[1]) ? src[1] : dst[1]);
   //      dst[2]=(::u8)((src[2]<dst[2]) ? src[2] : dst[2]);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Difference (image image )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      i32 Difference;
   //      Difference=src[0]-dst[0];
   //      dst[0]=(::u8)((Difference<0) ? -Difference : Difference);
   //      Difference=src[1]-dst[1];
   //      dst[1]=(::u8)((Difference<0) ? -Difference : Difference);
   //      Difference=src[2]-dst[2];
   //      dst[2]=(::u8)((Difference<0) ? -Difference : Difference);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Lighten (image image )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)((src[0]>dst[0]) ? src[0] : dst[0]);
   //      dst[1]=(::u8)((src[1]>dst[1]) ? src[1] : dst[1]);
   //      dst[2]=(::u8)((src[2]>dst[2]) ? src[2] : dst[2]);
   //      dst+=4;
   //      src+=4;
   //   }
   //}


   //void image::Multiply (image image )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)(((src[0])*(dst[0]))>>8);
   //      dst[1]=(::u8)(((src[1])*(dst[1]))>>8);
   //      dst[2]=(::u8)(((src[2])*(dst[2]))>>8);
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   //void image::Screen (image image )
   //{
   //   if(size() != pimage->size())
   //      return;

   //   ::u8 *src=(::u8*)pimage->get_data();
   //   ::u8 *dst=(::u8*)m_pcolorref;
   //   i64 size = area();
   //
   //   while ( size-- )
   //   {
   //      dst[0]=(::u8)(255-(((255-src[0])*(255-dst[0]))>>8));
   //      dst[1]=(::u8)(255-(((255-src[1])*(255-dst[1]))>>8));
   //      dst[2]=(::u8)(255-(((255-src[2])*(255-dst[2]))>>8));
   //      dst+=4;
   //      src+=4;
   //   }
   //}

   ////////////////////////////////////////////////////////////////////////
   //// Rectangle Functions
   ////////////////////////////////////////////////////////////////////////

   //void image::copy (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->width())<m_size.cx()) ? pimage.width() : m_size.cx()-x;
   //   i32 Δy=((y+pimage->height())<m_size.cy()) ? pimage.height() : m_size.cy()-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to copy return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;
   //   // If DibSize Wrong Re-create image
   //   if ( (Δx!=pimage->width()) || (Δy!=pimage->height()) )
   //      image = create_image ( Δx, Δy );

   //   // Prepare buffer Addresses
   //   color32_t *src=m_pcolorref+(py*m_size.cx())+px;
   //   color32_t *dst=pimage->get_data();

   //   // Do copy
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //         dst[i]=src[i];
   //      src+=m_size.cx();
   //      dst+=pimage->width();
   //   }
   //}

   //void image::PasteRect (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->width())<m_size.cx()) ? pimage.width() : m_size.cx()-x;
   //   i32 Δy=((y+pimage->height())<m_size.cy()) ? pimage.height() : m_size.cy()-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Paste return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   color32_t *src=pimage->get_data()+((py-y)*pimage->width())+px-x;
   //   color32_t *dst=m_pcolorref+(py*m_size.cx())+px;

   //   // Do Paste
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //         dst[i]=src[i];
   //      src+=pimage->width();
   //      dst+=m_size.cx();
   //   }
   //}

   //void image::FillRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+w)<m_size.cx()) ? w : m_size.cx()-x;
   //   i32 Δy=((y+h)<m_size.cy()) ? h : m_size.cy()-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Fill return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   color32_t *dst=m_pcolorref+(py*m_size.cx())+px;
   //   color32_t color=rgb ( B, G, R );

   //   // Do Fill
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[i]=color;
   //      }
   //      dst+=m_size.cx();
   //   }
   //}

   //void image::FillGlassRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B, i32 A )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+w)<m_size.cx()) ? w : m_size.cx()-x;
   //   i32 Δy=((y+h)<m_size.cy()) ? h : m_size.cy()-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to FillGlass return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*m_size.cx())+px)*4;

   //   // Do FillGlass
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(::u8)(((B-dst[0])*A+(dst[0]<<8))>>8);
   //         dst[1]=(::u8)(((G-dst[1])*A+(dst[1]<<8))>>8);
   //         dst[2]=(::u8)(((R-dst[2])*A+(dst[2]<<8))>>8);
   //         dst+=4;
   //      }
   //      dst+=(m_size.cx()-Δx)<<2;
   //   }
   //}

   //void image::FillStippledGlassRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+w)<m_size.cx()) ? w : m_size.cx()-x;
   //   i32 Δy=((y+h)<m_size.cy()) ? h : m_size.cy()-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to FillStippledGlass return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Address
   //   color32_t *dst=m_pcolorref+(py*m_size.cx())+px;
   //   color32_t color=rgb ( B, G, R );

   //   // Do FillStippledGlass
   //   for ( i32 j=0; j<Δy; j++ )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[i]=((i+j)&0x1) ? dst[i] : color;
   //      }
   //      dst+=m_size.cx();
   //   }
   //}

   //void image::BlendRect (image image, i32 x, i32 y, i32 A )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->width())<m_size.cx()) ? pimage.width() : m_size.cx()-x;
   //   i32 Δy=((y+pimage->height())<m_size.cy()) ? pimage.height() : m_size.cy()-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Blend return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   ::u8 *src=(::u8 *)pimage->get_data()+(((py-y)*pimage->width())+px-x)*4;
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*m_size.cx())+px)*4;

   //   // Do Blend
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(::u8)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
   //         dst[1]=(::u8)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
   //         dst[2]=(::u8)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(m_size.cx()-Δx)<<2;
   //      src+=(pimage->width()-Δx)<<2;
   //   }
   //}

   //void image::DarkenRect (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->cx())<cx) ? pimage->cx() : cx-x;
   //   i32 Δy=((y+pimage->cy())<cy) ? pimage->cy() : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Darken return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   ::u8 *src=(::u8 *)pimage->get_data()+(((py-y)*pimage->cx())+px-x)*4;
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Darken
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(::u8)((src[0]<dst[0]) ? src[0] : dst[0]);
   //         dst[1]=(::u8)((src[1]<dst[1]) ? src[1] : dst[1]);
   //         dst[2]=(::u8)((src[2]<dst[2]) ? src[2] : dst[2]);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx()-Δx)<<2;
   //   }
   //}

   //void image::DifferenceRect (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->cx())<cx) ? pimage->cx() : cx-x;
   //   i32 Δy=((y+pimage->cy())<cy) ? pimage->cy() : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Difference return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   ::u8 *src=(::u8 *)pimage->get_data()+(((py-y)*pimage->cx())+px-x)*4;
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Difference
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         i32 Difference;
   //         Difference=src[0]-dst[0];
   //         dst[0]=(::u8)((Difference<0) ? -Difference : Difference);
   //         Difference=src[1]-dst[1];
   //         dst[1]=(::u8)((Difference<0) ? -Difference : Difference);
   //         Difference=src[2]-dst[2];
   //         dst[2]=(::u8)((Difference<0) ? -Difference : Difference);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx()-Δx)<<2;
   //   }
   //}

   //void image::LightenRect (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->cx())<cx) ? pimage->cx() : cx-x;
   //   i32 Δy=((y+pimage->cy())<cy) ? pimage->cy() : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Lighten return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   ::u8 *src=(::u8 *)pimage->get_data()+(((py-y)*pimage->cx())+px-x)*4;
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Lighten
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(::u8)((src[0]>dst[0]) ? src[0] : dst[0]);
   //         dst[1]=(::u8)((src[1]>dst[1]) ? src[1] : dst[1]);
   //         dst[2]=(::u8)((src[2]>dst[2]) ? src[2] : dst[2]);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx()-Δx)<<2;
   //   }
   //}

   //void image::MultiplyRect (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->cx())<cx) ? pimage->cx() : cx-x;
   //   i32 Δy=((y+pimage->cy())<cy) ? pimage->cy() : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Multiply return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   ::u8 *src=(::u8 *)pimage->get_data()+(((py-y)*pimage->cx())+px-x)*4;
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Multiply
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(::u8)(((src[0])*(dst[0]))>>8);
   //         dst[1]=(::u8)(((src[1])*(dst[1]))>>8);
   //         dst[2]=(::u8)(((src[2])*(dst[2]))>>8);
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx()-Δx)<<2;
   //   }
   //}

   //void image::ScreenRect (image image, i32 x, i32 y )
   //{
   //   // Clip Rect
   //   i32 px=(x>=0) ? x : 0;
   //   i32 py=(y>=0) ? y : 0;
   //   i32 Δx=((x+pimage->cx())<cx) ? pimage->cx() : cx-x;
   //   i32 Δy=((y+pimage->cy())<cy) ? pimage->cy() : cy-y;
   //   Δx=(x>=0) ? Δx : Δx + x;
   //   Δy=(y>=0) ? Δy : Δy + y;

   //   // If Nothing to Screen return
   //   if ( (Δx<=0) || (Δy<=0) )
   //      return;

   //   // Prepare buffer Addresses
   //   ::u8 *src=(::u8 *)pimage->get_data()+(((py-y)*pimage->cx())+px-x)*4;
   //   ::u8 *dst=(::u8 *)m_pcolorref+((py*cx)+px)*4;

   //   // Do Screen
   //   while ( Δy-- )
   //   {
   //      for ( i32 i=0; i<Δx; i++ )
   //      {
   //         dst[0]=(::u8)(255-(((255-src[0])*(255-dst[0]))>>8));
   //         dst[1]=(::u8)(255-(((255-src[1])*(255-dst[1]))>>8));
   //         dst[2]=(::u8)(255-(((255-src[2])*(255-dst[2]))>>8));
   //         dst+=4;
   //         src+=4;
   //      }
   //      dst+=(cx-Δx)<<2;
   //      src+=(pimage->cx()-Δx)<<2;
   //   }
   //}

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void image::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
   {
      i32 Δx, Δy, k1, k2, d, x, y;
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

//   void image::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
//   {
//      i32 d, x, y, ax, ay, sx, sy, Δx, Δy;
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
//   void image::LineGlass ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A )
//   {
//      i32 d, x, y, ax, ay, sx, sy, Δx, Δy;
////      color32_t color=rgb ( B, G, R );
//      ::u8 *dst=(::u8 *)m_pcolorref;
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
//            dst[(y*cx+x)<<2]=(::u8)(((B-dst[(y*cx+x)<<2])*A+(dst[(y*cx+x)<<2]<<8))>>8);
//            dst[((y*cx+x)<<2)+1]=(::u8)(((G-dst[((y*cx+x)<<2)+1])*A+(dst[((y*cx+x)<<2)+1]<<8))>>8);
//            dst[((y*cx+x)<<2)+2]=(::u8)(((R-dst[((y*cx+x)<<2)+2])*A+(dst[((y*cx+x)<<2)+2]<<8))>>8);
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
//            dst[(y*cx+x)<<2]=(::u8)(((B-dst[(y*cx+x)<<2])*A+(dst[(y*cx+x)<<2]<<8))>>8);
//            dst[((y*cx+x)<<2)+1]=(::u8)(((G-dst[((y*cx+x)<<2)+1])*A+(dst[((y*cx+x)<<2)+1]<<8))>>8);
//            dst[((y*cx+x)<<2)+2]=(::u8)(((R-dst[((y*cx+x)<<2)+2])*A+(dst[((y*cx+x)<<2)+2]<<8))>>8);
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

   //   i32 size=cx*cy;

   //   for ( i32 i=0; i<size_i32; i++ )
   //      if(m_pcolorref[i]== crFind)
   //         m_pcolorref[i] = crSet;
   //      else
   //         m_pcolorref[i] = crUnset;

   //}

   //void image::transparent_color(::color::color color)
   //{
   //   color32_t crFind = color.get_rgb();
   //   i64 size = area();

   //   for ( i32 i=0; i<size_i32; i++ )
   //      if((m_pcolorref[i] & 0x00ffffff) == crFind)
   //         ((LPBYTE)&m_pcolorref[i])[3] = 255;
   //      else
   //         ((LPBYTE)&m_pcolorref[i])[3] = 0;
   //}

   //void image::color::e_channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, color::color::color::rgba::echannel echannel)
   //{
   //   i32 size = cx * cy;
   //   uchar * puch = (uchar * ) m_pcolorref;
   //   puch += ((i32) echannel) % 4;

   //   for(i32 i = 0; i < size; i++)
   //   {
   //      if(*puch == uchFind)
   //         *puch = uchSet;
   //      else
   //         *puch = uchUnset;
   //      puch += 4;
   //   }
   //}

   //u32 image::GetPixel(i32 x, i32 y)
   //{
   //   ::u32 dw = *(m_pcolorref + x + (cy - y - 1) * cx);
   //   return rgb(::blue(dw), ::green(dw), ::red(dw));
   //}

   // too slow for animation on AMD XP gen_hon.
   // TOP SUGGESTION:
   // The gradient cant have more then 256 levels of the most bright color
   // (white). So creating a radial fill of radius 256 and then using fasting
   // stretching algorithms is much faster than calculating radial fill.
//   void image::RadialFill(::u8 alpha, ::u8 red, ::u8 green, ::u8 blue, i32 xCenter, i32 yCenter, i32 iRadius)
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
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         ::u8 *dst = ((::u8*)(m_pcolorref + xL + yL * cx));
//         ::u32 dwAdd = ((cx - 1 - xU) + xL) * 4;
//         i32 size=cx*cy;
//         double iLevel;
//
//         i32 Δx, Δy;
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
//         LPBYTE lpb = (LPBYTE) (((i32) lpbAlloc + 3) & ~3);
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
//               lpb[x + y * iRadius] = (::u8) b;
//               lpb[y + x * iRadius] = (::u8) b;
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
//         ::u8 *dst = ((::u8*)(m_pcolorref + xL + yL * cx));
//         ::u32 dwAdd = ((cx - 1 - xU) + xL) * 4;
////         i32 size=cx*cy;
//
//         i32 Δx, Δy;
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
//               dst[0] = (::u8) (blue     * b / 255);
//               dst[1] = (::u8) (green    * b / 255);
//               dst[2] = (::u8) (red      * b / 255);
//               dst[3] = (::u8) (alpha    * b / 255);
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
//      ::u8 alpha1, ::u8 red1, ::u8 green1, ::u8 blue1,
//      ::u8 alpha2, ::u8 red2, ::u8 green2, ::u8 blue2,
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
//         if(xU >= cx) xU = cx - 1;
//         if(yL < 0) yL = 0;
//         if(yU >= cy) yU = cy - 1;
//
//
//         ::u8 *dst = ((::u8*)(m_pcolorref + xL + yL * cx));
//         ::u32 dwAdd = ((cx - 1 - xU) + xL) * 4;
//         i32 size=cx*cy;
//         double iLevel;
//
//         i32 Δx, Δy;
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
//               lpb[x + y * iRadius] = (::u8) b;
//               lpb[y + x * iRadius] = (::u8) b;
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
//         ::u8 *dst = ((::u8*)(m_pcolorref + xL + yL * cx));
//         ::u32 dwAdd = ((cx - 1 - xU) + xL) * 4;
////         i32 size=cx*cy;
//
//         i32 Δx, Δy;
//
//         ::u8 bComp;
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
//               bComp = (::u8) ~b;
//               dst[0] = (::u8) (((blue1  * b) + (blue2  * bComp)) / 255);
//               dst[1] = (::u8) (((green1 * b) + (green2 * bComp)) / 255);
//               dst[2] = (::u8) (((red1   * b) + (red2   * bComp)) / 255);
//               dst[3] = (::u8) (((alpha1 * b) + (alpha2 * bComp)) / 255);
//               dst += 4;
//            }
//            dst += dwAdd;
//         }
//
//         free(lpbAlloc);
//      }
//   }

   //void image::SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy)
   //{
   //   create(cx, cy);

   //   if(cx <= 0 || cy <= 0)
   //      return;




   //   // White blend image
   //   image pimage1(this);
   //   pimage1 = create_image({cx,  cy});
   //   pimage1->set(255, 255, 255);

   //   pimage1->m_pgraphics->DrawIcon(
   //   0, 0,
   //   picon,
   //   cx, cy,
   //   0,
   //   nullptr,
   //   DI_IMAGE | DI_MASK);

   //   // Black blend image
   //   image pimage2;
   //   pimage2 = create_image({cx,  cy});
   //   pimage2->Fill(0, 0, 0, 0);

   //   pimage2->get_graphics()->DrawIcon(
   //   0, 0,
   //   picon,
   //   cx, cy,
   //   0,
   //   nullptr,
   //   DI_IMAGE | DI_MASK);

   //   // Mask image
   //   image imageM(this);
   //   imageM = create_image({cx,  cy});

   //   imageM.m_pgraphics->DrawIcon(
   //   0, 0,
   //   picon,
   //   cx, cy,
   //   0,
   //   nullptr,
   //   DI_MASK);

   //   ::u8 * r1=(::u8*)pimage1->m_pcolorref;
   //   ::u8 * r2=(::u8*)pimage2->get_data();
   //   ::u8 * srcM=(::u8*)imageM.m_pcolorref;
   //   ::u8 * dest=(::u8*)m_pcolorref;
   //   i32 iSize = cx*cy;

   //   ::u8 b;
   //   ::u8 bMax;
   //   while ( iSize-- > 0)
   //   {
   //      if(srcM[0] == 255)
   //      {
   //         bMax = 0;
   //      }
   //      else
   //      {
   //         bMax = 0;
   //         b =(::u8)(r1[0]  - r2[0]);
   //         bMax = maximum(b, bMax);
   //         b =(::u8)(r1[1]  - r2[1]);
   //         bMax = maximum(b, bMax);
   //         b =(::u8)(r1[2]  - r2[2]);
   //         bMax = maximum(b, bMax);
   //         bMax = 255 - bMax;
   //      }
   //      dest[0]  =  bMax;
   //      dest[1]  =  bMax;
   //      dest[2]  =  bMax;
   //      dest     += 4;
   //      srcM     += 4;
   //      r1       += 4;
   //      r2       += 4;
   //   }



   //}

   //void image::rotate(image image, double dAngle, double dScale)
   //{
   //  // image image;
   ////   pimage->Paste(this);

   //   i32 cx = this->cx();
   //   i32 cy = this->cy();

   //   i32 l = maximum(cx, cy);

   //
   //   i32 jmax = minimum(l, cy / 2);
   //   i32 jmin = - jmax;
   //   i32 imax = minimum(l, cx / 2);
   //   i32 imin = - imax;


   //   i32 joff = cy / 2;
   //   i32 ioff = cx / 2;

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


   //
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}


   //void image::Rotate034(image image, double dAngle, double dScale)
   //{
   //
   //   i32 cx = this->cx();
   //   i32 cy = this->cy();

   //   i32 l = maximum(cx, cy);

   //
   //   i32 jmax = minimum(l, cy / 2);
   //   i32 jmin = - jmax;
   //   i32 imax = minimum(l, cx / 2);
   //   i32 imin = - imax;


   //   if((cy % 2) == 1)
   //      jmax++;

   //   if((cx % 2) == 1)
   //      imax++;
   //
   //   i32 joff = cy / 2;
   //   i32 ioff = cx / 2;

   //
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


   //
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}

   //void image::rotate(
   //   image image,
   //   const ::rectangle_i32 & rectangle,
   //   double dAngle,
   //   double dScale)
   //{
   //  // image image;
   ////   pimage->Paste(this);



   //   ::rectangle_i32 rectangle(rectangle);

   //   i32 cx = rectangle.width();
   //   i32 cy = rectangle.height();

   //   i32 l = maximum(cx, cy);
   //
   //   i32 jmax = minimum(l, cy / 2);
   //   i32 jmin = - jmax;
   //   i32 imax = minimum(l, cx / 2);
   //   i32 imin = - imax;


   //   i32 joff = cy / 2 + rectangle.left();
   //   i32 ioff = cx / 2 + rectangle.top();

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


   //
   //         m_pcolorref[(j+joff)*cx+(i+ioff)]=
   //            pimage->get_data()[y * cx + x];
   //         k++;
   //      }
   //   }
   //}

   ///*i32 image::cos(i32 i, i32 iAngle)
   //{
   //   return (i32) (((_int64) i * CosN[iAngle]) >> 32);
   //}

   //i32 image::sin(i32 i, i32 iAngle)
   //{
   //   return (i32) (((_int64) i * SinN[iAngle]) >> 32);
   //}*/




   //void image::Fill (i32 A, i32 R, i32 G, i32 B )
   //{
   //   color32_t color = rgb ( B, G, R ) | (A << 24);
   //   i32 size=cx*cy;

   //   color32_t * pcr;

   //   i64 iSize32 = size / 32;
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

   //   for (i=0; i<size_i32; i++ )
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
   //      LPBYTE lpb = (LPBYTE) m_pcolorref;
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
   //      return rgb(iR, iG, iB);
   //   }
   //   else
   //   {
   //      return 0;
   //   }
   //
   //}


   //void image::xor(image image)
   //{
   //   if(cx != pimage->cx()
   //   || cy != pimage->cy())
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

   //void image::create_frame(::size_i32 size, i32 iFrameCount)
   //{
   //   i32 iSliceCount = (i32) sqrt((double) iFrameCount);
   //   i32 iFrameWidth = size.cx() / iSliceCount;
   //   i32 iFrameHeight = size.cy() / iSliceCount;
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
   //   LPBYTE lp = ((LPBYTE) m_pcolorref);
   //   i32 i = 0;
   //   i32 iCount1 = iCount - iCount % 8;
   //   for(; i < iCount1; i++)
   //   {
   //      lp[0] /= (::u8) iDivide;
   //      lp[1] /= (::u8) iDivide;
   //      lp[2] /= (::u8) iDivide;

   //      lp[4] /= (::u8) iDivide;
   //      lp[5] /= (::u8) iDivide;
   //      lp[6] /= (::u8) iDivide;

   //      lp[8] /= (::u8) iDivide;
   //      lp[9] /= (::u8) iDivide;
   //      lp[10] /= (::u8) iDivide;

   //      lp[12] /= (::u8) iDivide;
   //      lp[13] /= (::u8) iDivide;
   //      lp[14] /= (::u8) iDivide;

   //      lp[16] /= (::u8) iDivide;
   //      lp[17] /= (::u8) iDivide;
   //      lp[28] /= (::u8) iDivide;

   //      lp[20] /= (::u8) iDivide;
   //      lp[21] /= (::u8) iDivide;
   //      lp[22] /= (::u8) iDivide;

   //      lp[24] /= (::u8) iDivide;
   //      lp[25] /= (::u8) iDivide;
   //      lp[26] /= (::u8) iDivide;

   //      lp[28] /= (::u8) iDivide;
   //      lp[29] /= (::u8) iDivide;
   //      lp[30] /= (::u8) iDivide;

   //      lp += 4 * 8;
   //   }
   //   for(; i < iCount; i++)
   //   {
   //      lp[0] /= (::u8) iDivide;
   //      lp[1] /= (::u8) iDivide;
   //      lp[2] /= (::u8) iDivide;
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
   //   LPBYTE lp = ((LPBYTE) m_pcolorref);
   //   for(i32 i = 0; i < iCount; i++)
   //   {
   //      lp[0] /= (::u8) iDivide;
   //      lp[1] /= (::u8) iDivide;
   //      lp[2] /= (::u8) iDivide;
   //      lp[3] /= (::u8) iDivide;
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
   //   LPBYTE lp = ((LPBYTE) m_pcolorref);
   //   for(i32 i = 0; i < iCount; i++)
   //   {
   //      lp[3] /= (::u8) iDivide;
   //      lp +=4;
   //   }
   //}


   void image::stretch_image(::image * pimage)
   {

      if (::is_null(pimage))
      {

         return;

      }

      //plusplus::rectF rectangleDest(0, 0, (plusplus::REAL) m_size.cx(), (plusplus::REAL) m_size.cy());

      //plusplus::rectF rectangleSource(0, 0, (plusplus::REAL) pimage->width(), (plusplus::REAL) pimage->height());

      unmap();
      
      pimage->unmap();

      m_pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //((plusplus::Graphics * ) m_pgraphics->get_os_data())->DrawImage(((plusplus::Bitmap *)pimage->get_bitmap()->get_os_data()), rectangleDest, rectangleSource, plusplus::UnitPixel);

      //return true;

   }


   ::draw2d::graphics * image::_get_graphics() const
   {

      if (m_pgraphics)
      {

         return m_pgraphics;

      }

      //::draw2d::graphics * image::_get_graphics()
      //{

  /*       if (m_pgraphics)
         {

            return pgraphics;

         }*/

         if (!m_pbitmap)
         {

      /*      m_size.cx() = 0;

            m_size.cy() = 0;

            m_iScan = 0;*/

            return m_pgraphics;

         }

         ((image *)this)->__construct(((image*)this)->m_pgraphics);


         ((image *)this)->m_pgraphics->set(m_pbitmap);

         ((image *)this)->m_pgraphics->create_memory_graphics(m_size);

         ((image *)this)->m_pgraphics->m_pimage = (image *) this;

         return m_pgraphics;


      //unmap();

      //m_pgraphics->set(m_pbitmap);

      //return m_pgraphics;

   }


   // double image::pi()
   // {
   //    return dPi;
   // }

   // void image::fill_channel(i32 intensity, color::color::color::rgba::echannel echannel)
   // {
   //     i32 offset = ((i32)echannel) % 4;
   //    i32 size=m_size.cx()*cy;

   //    ::u8 * pb;

   //    i32 iSize32 = size;
   //    i32 i;
   //    for (i=0; i < iSize32; i+=32 )
   //    {
   //       pb = ((::u8 * ) &m_pcolorref[i]) + offset;
   //       pb[0 * 4] = (::u8) intensity;
   //       pb[1 * 4] = (::u8) intensity;
   //       pb[2 * 4] = (::u8) intensity;
   //       pb[3 * 4] = (::u8) intensity;
   //       pb[4 * 4] = (::u8) intensity;
   //       pb[5 * 4] = (::u8) intensity;
   //       pb[6 * 4] = (::u8) intensity;
   //       pb[7 * 4] = (::u8) intensity;
   //       pb[8 * 4] = (::u8) intensity;
   //       pb[9 * 4] = (::u8) intensity;
   //       pb[10 * 4] = (::u8) intensity;
   //       pb[11 * 4] = (::u8) intensity;
   //       pb[12 * 4] = (::u8) intensity;
   //       pb[13 * 4] = (::u8) intensity;
   //       pb[14 * 4] = (::u8) intensity;
   //       pb[15 * 4] = (::u8) intensity;
   //       pb[16 * 4] = (::u8) intensity;
   //       pb[17 * 4] = (::u8) intensity;
   //       pb[18 * 4] = (::u8) intensity;
   //       pb[19 * 4] = (::u8) intensity;
   //       pb[20 * 4] = (::u8) intensity;
   //       pb[21 * 4] = (::u8) intensity;
   //       pb[22 * 4] = (::u8) intensity;
   //       pb[23 * 4] = (::u8) intensity;
   //       pb[24 * 4] = (::u8) intensity;
   //       pb[25 * 4] = (::u8) intensity;
   //       pb[26 * 4] = (::u8) intensity;
   //       pb[27 * 4] = (::u8) intensity;
   //       pb[28 * 4] = (::u8) intensity;
   //       pb[29 * 4] = (::u8) intensity;
   //       pb[30 * 4] = (::u8) intensity;
   //       pb[31 * 4] = (::u8) intensity;
   //    }

   //    for (; i<size_i32; i++ )
   //    {
   //       *(((::u8 * ) &m_pcolorref[i]) + offset) = (::u8) intensity;
   //    }
   //}


   // i32 image::cos(i32 i, i32 iAngle)
   // {
   //    return (i32) (((_int64) i * CosN[iAngle]) >> 31);
   // }

   // i32 image::sin(i32 i, i32 iAngle)
   // {
   //    return (i32) (((_int64) i * SinN[iAngle]) >> 31);
   // }

   // i32 image::cos10(i32 i, i32 iAngle)
   // {
   //    return (i32) (((_int64) i * Cos10N[iAngle]) >> 34);
   // }

   // i32 image::sin10(i32 i, i32 iAngle)
   // {
   //    return (i32) (((_int64) i * Sin10N[iAngle]) >> 34);
   // }

   /*   i32 image::width()
      {
         return m_size.cx();
      }

      i32 image::height()
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
//      rectangle_i64 rectangleWindow;
//
//      puserinteraction->window_rectangle(rectangleWindow);
//
////#if !NO_SCREEN_PRE_MULTIPLY_ALPHA
////      if(bTransferBuffer && puserinteraction->is_composite() && !m_bReduced)
////      {
////
////         m_bReduced = true;
////
////         m_pgraphics->set_origin(0,0);
////
////         map();
////
////         //pre_multiply_alpha((unsigned int *) get_data(),m_size.cx(),m_size.cy(),m_size.cx() * 4);
////
////         ::u8 *dstR=(::u8*)get_data();
////         ::u8 *dstG=dstR + 1;
////         ::u8 *dstB=dstR + 2;
////         ::u8 *dstA=dstR + 3;
////         i64 size = area() * 4;
////
////
////         // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255
//////#if defined(_OPENMP)
//////         #pragma omp parallel num_threads(3)
//////                  {
//////
//////                     ::u8 *dst = dstR + omp_get_thread_num();
//////      #pragma omp parallel for
//////                     for(index i = 0; i < size; i+=4)
//////                     {
//////                           dst[i] = lower_u8(((i32)dst[i] * (i32)dstA[i]) >> 8);
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
////////               for(index i = 0; i < size; i+=4)
////////               {
////////                  if(dstA[i] <= 3)
////////                  {
////////                     dst[i>>2] = 0;
////////                  }
////////               }
////////            }
////////            else
////////            {
////////               ::u8 *dst = dstR + omp_get_thread_num();
////////#pragma omp parallel for
////////               for(index i = 0; i < size; i+=4)
////////               {
////////                  if(dstA[i] > 3)
////////                  {
////////                     dst[i] = lower_u8(((i32)dst[i] * (i32)dstA[i]) >> 8);
////////                  }
////////               }
////////            }
////////         }
//////#else
//////         for(index i = 0; i < size; i+=4)
//////         {
//////            dstR[i] = lower_u8(((i32)dstR[i] * (i32)dstA[i]) >> 8);
//////            dstG[i] = lower_u8(((i32)dstG[i] * (i32)dstA[i]) >> 8);
//////            dstB[i] = lower_u8(((i32)dstB[i] * (i32)dstA[i]) >> 8);
//////         }
//////#endif
//////
////      }
////#endif
//      ::rectangle_i32 rectangle(rectangleWindow);
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
//         int totalBytes = b->m_sizeOut.cx() * b.m_sizeOut.cy() * 4;
//         ::u8 * p = (::u8*)b->m_memOut.get_data();
//         for (int i = 0; i < totalBytes; i += 4)
//         {
//            p[0] = (::u8)(p[0] * p[3] / 255);
//            p[1] = (::u8)(p[1] * p[3] / 255);
//            p[2] = (::u8)(p[2] * p[3] / 255);
//            p+=4;
//         }
//      }
//
//
//      puserinteraction->get_window_graphics()->update_window(puserinteraction->get_handle(),(color32_t*)b->m_memOut.get_data(),rectangle, b->m_sizeOut.cx(), b.m_sizeOut.cy(), b.m_sizeOut.cx() * 4,bTransferBuffer);
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
//      m_pgraphics->attach((HDC) pusermessage->m_wparam);
//
//      ::rectangle_i32 rectx;
//
//      ::draw2d::bitmap * pbitmap = m_pgraphics->get_current_bitmap();
//
//      ::GetCurrentObject((HDC) pusermessage->m_wparam, OBJ_BITMAP);
//
//      //      u32 dw = ::get_last_error();
//      ::size_i32 size = pbitmap->get_size();
//
//      rectx.left() = 0;
//      rectx.top() = 0;
//      rectx.right() = size.cx();
//      rectx.bottom() = size.cy();
//
//      try
//      {
//
//         ::rectangle_i32 rectangleWindow;
//
//         puserinteraction->window_rectangle(rectangleWindow);
//
//         image image;
//
//         if(!image = create_image(rectangleWindow.bottom_right()))
//            return false;
//
//         ::draw2d::graphics * pgraphics = pimage->get_graphics();
//
//         if(pgraphics->get_os_data() == nullptr)
//            return false;
//
//         ::rectangle_i32 rectanglePaint;
//         ::rectangle_i32 rectangleUpdate;
//         rectangleUpdate = rectangleWindow;
//         rectanglePaint = rectangleWindow;
//         rectanglePaint.offset(-rectanglePaint.top_left());
//         m_pgraphics->SelectClipRgn(nullptr);
//         puserinteraction->_001OnDeferPaintLayeredWindowBackground(pimage->get_graphics());
//         m_pgraphics->SelectClipRgn(nullptr);
//         m_pgraphics-> set_origin(::point_i32());
//         puserinteraction->_000OnDraw(pimage->get_graphics());
//         m_pgraphics->set_origin(::point_i32());
//         //(dynamic_cast<::win::graphics * >(pgraphics))->FillSolidRect(rectangleUpdate.left(), rectangleUpdate.top(), 100, 100, 255);
//         m_pgraphics->SelectClipRgn(nullptr);
//         m_pgraphics->set_origin(::point_i32());
//
//         m_pgraphics->SelectClipRgn( nullptr);
//         m_pgraphics->BitBlt(rectanglePaint.left(), rectanglePaint.top(),
//            rectanglePaint.width(), rectanglePaint.height(),
//            pgraphics, rectangleUpdate.left(), rectangleUpdate.top(),
//            SRCCOPY);
//
//      }
//      catch(...)
//      {
//      }
//      m_pgraphics->FillSolidRect(rectx, rgb(255, 255, 255));
//      pmessage->m_bRet = true;
//      pusermessage->set_lresult(0);
//
//      return true;
//
//   }
//


//#define memory_new ACME_NEW


   void image::map(bool bApplyTransform) const
   {

      return;

      if (m_bMapped)
      {

         //return true;

         return;

      }

      if (!m_pgraphics)
      {

         //return false;

         return;

      }

      if (m_size.is_empty())
      {

         //return false;

         return;

      }

      if (::is_null(m_pimage32Raw))
      {

         //return false;

         return;

      }

      m_pgraphics->thread_select();

      int hasAlphaBits = 0;

      glGetIntegerv(GL_ALPHA_BITS, &hasAlphaBits);

      glFlush();

      //glReadBuffer(GL_BACK);
      //glReadBuffer(GL_FRONT);



      ::pointer < graphics > pgraphics = m_pgraphics;

      int cx = pgraphics->m_sizeWindow.cx();

      int cy = pgraphics->m_sizeWindow.cy();

      ::opengl::resize(pgraphics->m_sizeWindow);

      glReadBuffer(GL_BACK);

      glPixelStorei(GL_PACK_SWAP_BYTES, 0);

      glPixelStorei(GL_PACK_ROW_LENGTH, m_iScan/4);

      glReadPixels(0, 0, cx, cy, GL_BGRA, GL_UNSIGNED_BYTE, m_pimage32Raw);

      //glReadPixels(0, 0, m_size.cx(), m_size.cy(), GL_ARGB, GL_UNSIGNED_BYTE, m_pimage32Raw);

      int i1280 = GL_INVALID_ENUM;

      int i1281 = GL_INVALID_VALUE;

      int iError = glGetError();

      m_bMapped = true;

      //return true;

   }


   void image::unmap() const
   {

      if (!m_bMapped)
      {

         //return true;

         return;

      }

      if (!m_pgraphics)
      {

         //return false;

         return;

      }

      if (m_size.is_empty())
      {

         //return false;

         return;

      }

      if (::is_null(m_pimage32Raw))
      {

         //return false;

         return;

      }

      m_pgraphics->thread_select();

      glDrawPixels(m_size.cx(), m_size.cy(), GL_BGRA, GL_UNSIGNED_BYTE, m_pimage32Raw);

      m_bMapped = false;

      //return true;

   }


   bool image::host(const ::pixmap* ppixmap)
   {
    /*  if (m_phost == nullptr)
      {
         m_phost = create_offscreen_context(ppixmap->m_size.cx(), ppixmap.m_size.cy());

      }
*/
      return false;

   }


   bool image::on_host_read_pixels(::pixmap* ppixmap) const
   {

      return false;

/*      if (!m_pgraphics)
      {

         return false;

      }

      if (!ppixmap->m_size)
      {

         return false;

      }

      if (::is_null(ppixmap->m_pimage32Raw))
      {

         return false;

      }

      m_pgraphics->thread_select();

      glReadBuffer(GL_BACK);

      glReadPixels(0, 0, ppixmap->m_size.cx(), ppixmap.m_size.cy(), GL_BGRA, GL_UNSIGNED_BYTE, ppixmap.m_pimage32);

      *///return true;

   }


} // namespace draw2d_opengl



