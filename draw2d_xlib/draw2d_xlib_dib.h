#pragma once


namespace draw2d_xlib
{

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_DRAW2D_XLIB image :
      virtual public image
   {
   public:




      BITMAPINFO              m_info;
      ::draw2d::bitmap_pointer     m_pbitmap;
      ::draw2d::graphics_pointer   m_spgraphics;
      bool                    m_bMapped;
      //HBITMAP               m_hbitmapOriginal;
      HBITMAP                 m_hbitmap;
      class size64            m_sizeWnd;
      BITMAPINFO              m_bitmapinfo;
      XImage *                m_pimage;






      image(::layered * pobjectContext);
      virtual void construct(i32 cx, i32 cy);
      virtual ~image();


      void map(bool bApplyAlphaTransform = true);
      void unmap();


      virtual ::draw2d::graphics * get_graphics();
      virtual ::draw2d::bitmap_pointer get_bitmap();
      virtual ::draw2d::bitmap_pointer detach_bitmap();


      virtual color32_t * get_data();

      void stretch_image(::image::image * pimage);

      bool dc_select(bool bSelect = true);




      using object::create;
      bool create(::size size);
      bool create(i32 iWidth, i32 iHeight);
      bool create(::image::image * pimage);
      bool Destroy();


      using image::from;
      bool from(::image::image * pimage);
      bool from(point ptDest, ::draw2d::graphics * pgraphics, const ::point & point, ::size sz);

      using image::to;
      bool to(::draw2d::graphics * pgraphics, const ::point & point, ::size size, point ptSrc);

      virtual bool update_window(::window * pwnd, ::message::message * pmessage);
      virtual bool print_window(::window * pwnd, ::message::message * pmessage);

      void SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy);


      //bool color_blend(color32_t cr, byte bAlpha);
      //bool Blend(imagepimage, ::image::image * pimageA, i32 A);
      //void BitBlt(::image::image * pimage, i32 op);
      //color32_t GetAverageColor();
      //i32 cos(i32 i, i32 iAngle);
      //i32 sin(i32 i, i32 iAngle);
      //i32 cos10(i32 i, i32 iAngle);
      //i32 sin10(i32 i, i32 iAngle);

      //bool is_rgb_black();
      //void xor(::image::image * pimage);

      //void ToAlpha(i32 i);
      //void ToAlphaAndFill(i32 i, color32_t cr);
      //void GrayToARGB(color32_t cr);

      //void from_alpha();
      //void mult_alpha(::image::image * pimageWork, bool bPreserveAlpha = true);
      //void set_rgb(i32 R, i32 G, i32 B);

      //void rotate(::image::image * pimage, const ::rect & rect, double dAngle, double dScale);
      //void rotate(::image::image * pimage, double dAngle, double dScale);
      //void Rotate034(::image::image * pimage, double dAngle, double dScale);
      //void RadialFill(byte a, byte rect, byte g, byte b, i32 x, i32 y, i32 iRadius);
      //void RadialFill(
      //   byte a1, byte r1, byte g1, byte b1, // center colors
      //   byte a2, byte r2, byte g2, byte b2, // border colors
      //   i32 x, i32 y, i32 iRadius);

      //u32 GetPixel(i32 x, i32 y);
      //void Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask);
      //void color::channel_mask(byte uchFind, byte uchSet, byte uchUnset, color::color::rgba::echannel echannel);
      //void transparent_color(color color);
      //void DivideRGB(i32 iDivide);
      //void DivideARGB(i32 iDivide);
      //void DivideA(i32 iDivide);
      //virtual void fill_channel(i32 C, color::color::rgba::echannel echannel);
      //void Fill (i32 A, i32 R, i32 G, i32 B );
      //void Fill ( i32 R, i32 G, i32 B );
      //void FillGlass ( i32 R, i32 G, i32 B, i32 A );
      //void FillStippledGlass ( i32 R, i32 G, i32 B );
      //void Invert();
      //void color::channel_invert(color::color::rgba::echannel echannel);
      //void color::channel_multiply(color::color::rgba::echannel echannel, double dRate);

      //void Map (i32 ToRgb, i32 FromRgb );

      /*void __copy( imageimage );
      void Paste ( imageimage );

      void Blend ( imageimage, i32 A );
      void Darken ( imageimage );
      void Difference ( imageimage );
      void Lighten ( imageimage );
      void Multiply ( imageimage );
      void Screen ( imageimage );

      void copy ( imageimage, i32 x, i32 y );
      void PasteRect ( imageimage, i32 x, i32 y );

      void FillRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B );
      void FillGlassRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B, i32 A );
      void FillStippledGlassRect ( i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B );

      void BlendRect ( imageimage, i32 x, i32 y, i32 A );
      void DarkenRect ( imageimage, i32 x, i32 y );
      void DifferenceRect ( imageimage, i32 x, i32 y );
      void LightenRect ( imageimage, i32 x, i32 y );
      void MultiplyRect ( imageimage, i32 x, i32 y );
      void ScreenRect ( imageimage, i32 x, i32 y );

      void Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B );
      void LineGlass ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A );*/

      //void create_frame(::size size, i32 iFrameCount);
      //void set_frame2(void * lpdata, i32 iFrame, i32 iFrameCount);
      //void set_frame1(void * lpdata, i32 iFrame, i32 iFrameCount);
      //void get_frame(void * lpdata, i32 iFrame, i32 iFrameCount);
      //void xor_image_frame2(void * lpdata, i32 iFrame, i32 iFrameCount);


      //double pi();


      virtual void read(stream & istream);


   };


} // namespace draw2d_xlib



