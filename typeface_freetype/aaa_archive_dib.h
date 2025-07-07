#pragma once


namespace typeface_freetype
{



   class CLASS_DECL_TYPEFACE_FREETYPE image :
      virtual public image
   {
   public:


      ::draw2d::bitmap_pointer      m_pbitmap;
      ::draw2d::graphics_pointer    m_spgraphics;
      HBITMAP                    m_hbitmap;
      class size64                       m_sizeWnd;
      BITMAPINFO           m_bitmapinfo;


      image(::particle * pparticle);
      virtual void construct(int cx, int cy);
      virtual ~image();


      virtual ::draw2d::graphics * get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();


      /*virtual color32_t * get_data() const;

      */void stretch_image(::image::image *pimage);

      bool dc_select(bool bSelect = true);





      bool create(::size size);
      bool create(int iWidth, int iHeight);
      bool create(::draw2d::graphics * pgraphics);
      bool destroy();



      bool from(::draw2d::graphics * pgraphics);
      bool from(point ptDest, ::draw2d::graphics * pgraphics, const ::int_point & point, ::size sz);

      bool to(::draw2d::graphics * pgraphics, const ::int_point & point, ::size size, point ptSrc);


      void SetIconMask(::image::icon * picon, int cx, int cy);


      //bool color_blend(color32_t color32, unsigned char bAlpha);
      //bool Blend(imagepimage, ::image::image *pimageA, int A);
      //void BitBlt(::image::image *pimage, int op);
      //color32_t GetAverageColor();
      //int cos(int i, int iAngle);
      //int sin(int i, int iAngle);
      //int cos10(int i, int iAngle);
      //int sin10(int i, int iAngle);

      //bool is_rgb_black();
      //void xor(::image::image *pimage);

      //void ToAlpha(int i);
      //void ToAlphaAndFill(int i, color32_t color32);
      //void GrayToARGB(color32_t color32);

      //void from_alpha();
      //void mult_alpha(::image::image *pimageWork, bool bPreserveAlpha = true);
      //void set_rgb(int R, int G, int B);

      //void rotate(::image::image *pimage, const ::double_rectangle & rectangle, double dAngle, double dScale);
      //void rotate(::image::image *pimage, double dAngle, double dScale);
      //void Rotate034(::image::image *pimage, double dAngle, double dScale);

      //void RadialFill(unsigned char a, unsigned char rectangle, unsigned char g, unsigned char b, int x, int y, int iRadius);
      //void RadialFill(
      //   unsigned char a1, unsigned char r1, unsigned char g1, unsigned char b1, // center colors
      //   unsigned char a2, unsigned char r2, unsigned char g2, unsigned char b2, // border colors
      //   int x, int y, int iRadius);

      //unsigned int GetPixel(int x, int y);
      //void Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask);
      //void ::color::e_channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, color::color::color::rgba::echannel echannel);
      //void transparent_color(::color::color color);
      //void DivideRGB(int iDivide);
      //void DivideARGB(int iDivide);
      //void DivideA(int iDivide);
      //virtual void fill_channel(int C, color::color::color::rgba::echannel echannel);
      //void Fill (int A, int R, int G, int B );
      //void Fill ( int R, int G, int B );
      //void FillGlass ( int R, int G, int B, int A );
      //void FillStippledGlass ( int R, int G, int B );
      //void Invert();
      //void ::color::e_channel_invert(color::color::color::rgba::echannel echannel);
      //void ::color::e_channel_multiply(color::color::color::rgba::echannel echannel, double dRate);

      //void Map (int ToRgb, int FromRgb );

      /*void copy( imageimage );
      void Paste ( imageimage );

      void Blend ( imageimage, int A );
      void Darken ( imageimage );
      void Difference ( imageimage );
      void Lighten ( imageimage );
      void Multiply ( imageimage );
      void Screen ( imageimage );

      void copy ( imageimage, int x, int y );
      void PasteRect ( imageimage, int x, int y );

      void FillRect ( int x, int y, int w, int h, int R, int G, int B );
      void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
      void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );

      void BlendRect ( imageimage, int x, int y, int A );
      void DarkenRect ( imageimage, int x, int y );
      void DifferenceRect ( imageimage, int x, int y );
      void LightenRect ( imageimage, int x, int y );
      void MultiplyRect ( imageimage, int x, int y );
      void ScreenRect ( imageimage, int x, int y );

      void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
      void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );*/

      //void create_frame(::size size, int iFrameCount);
      //void set_frame2(void * lpdata, int iFrame, int iFrameCount);
      //void set_frame1(void * lpdata, int iFrame, int iFrameCount);
      //void get_frame(void * lpdata, int iFrame, int iFrameCount);
      //void xor_image_frame2(void * lpdata, int iFrame, int iFrameCount);


      //double pi();


      virtual void map(bool bApplyTransform = true) const override;
      virtual void unmap() const override;

      //virtual bool update_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage, bool bTransferBuffer = true) override;
      //virtual bool print_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage) override;


   };


} // namespace typeface_freetype



