#pragma once


#include "acme/_operating_system.h"


#include "aura/graphics/image/image.h"


struct OffscreenContext;


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL image :
      virtual public ::image::image
   {
   public:


      HBITMAP                          m_hbitmap;
      class ::size_i64                   m_sizeWnd;
      BITMAPINFO                       m_bitmapinfo;
      OffscreenContext *               m_phost;


      image();
      virtual ~image();


      virtual ::draw2d::graphics * _get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      //virtual ::draw2d::graphics * get_graphics();

      bool host(const ::pixmap* ppixmap);

      void stretch_image(::image::image *pimage) override;

      void dc_select(bool bSelect = true) override;

      using ::image::image::create;

      virtual void create(const ::size_i32& size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false) override;

      virtual void create(::draw2d::graphics* pgraphics);

      void destroy() override;

      bool host(::pixmap * ppixmap) override;

      bool from(::draw2d::graphics * pgraphics);
      //bool from(point_i32 ptDest, ::draw2d::graphics * pgraphics, const ::point_i32 & point, ::size_i32 sz);

      //void to(::draw2d::graphics * pgraphics, const ::point_i32& point, const ::size_i32& size, const ::point_i32& pointSrc) override;


      //void SetIconMask(::image::icon * picon, i32 cx, i32 cy);

      bool on_host_read_pixels(::pixmap* ppixmap) const override;

      //bool color_blend(color32_t color32, ::u8 bAlpha);
      //bool Blend(imagepimage, ::image::image *pimageA, i32 A);
      //void BitBlt(::image::image *pimage, i32 op);
      //color32_t GetAverageColor();
      //i32 cos(i32 i, i32 iAngle);
      //i32 sin(i32 i, i32 iAngle);
      //i32 cos10(i32 i, i32 iAngle);
      //i32 sin10(i32 i, i32 iAngle);

      //bool is_rgb_black();
      //void xor(::image::image *pimage);

      //void ToAlpha(i32 i);
      //void ToAlphaAndFill(i32 i, color32_t color32);
      //void GrayToARGB(color32_t color32);

      //void from_alpha();
      //void mult_alpha(::image::image *pimageWork, bool bPreserveAlpha = true);
      //void set_rgb(i32 R, i32 G, i32 B);

      //void rotate(::image::image *pimage, const ::rectangle_i32 & rectangle, double dAngle, double dScale);
      //void rotate(::image::image *pimage, double dAngle, double dScale);
      //void Rotate034(::image::image *pimage, double dAngle, double dScale);

      //void RadialFill(::u8 a, ::u8 rectangle, ::u8 g, ::u8 b, i32 x, i32 y, i32 iRadius);
      //void RadialFill(
      //   ::u8 a1, ::u8 r1, ::u8 g1, ::u8 b1, // center colors
      //   ::u8 a2, ::u8 r2, ::u8 g2, ::u8 b2, // border colors
      //   i32 x, i32 y, i32 iRadius);

      //u32 GetPixel(i32 x, i32 y);
      //void Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask);
      //void ::color::e_channel_mask(::u8 uchFind, ::u8 uchSet, ::u8 uchUnset, color::color::color::rgba::echannel echannel);
      //void transparent_color(::color::color color);
      //void DivideRGB(i32 iDivide);
      //void DivideARGB(i32 iDivide);
      //void DivideA(i32 iDivide);
      //virtual void fill_channel(i32 C, color::color::color::rgba::echannel echannel);
      //void Fill (i32 A, i32 R, i32 G, i32 B );
      //void Fill ( i32 R, i32 G, i32 B );
      //void FillGlass ( i32 R, i32 G, i32 B, i32 A );
      //void FillStippledGlass ( i32 R, i32 G, i32 B );
      //void Invert();
      //void ::color::e_channel_invert(color::color::color::rgba::echannel echannel);
      //void ::color::e_channel_multiply(color::color::color::rgba::echannel echannel, double dRate);

      //void Map (i32 ToRgb, i32 FromRgb );

      /*void copy( imageimage );
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

      //void create_frame(::size_i32 size, i32 iFrameCount);
      //void set_frame2(void * lpdata, i32 iFrame, i32 iFrameCount);
      //void set_frame1(void * lpdata, i32 iFrame, i32 iFrameCount);
      //void get_frame(void * lpdata, i32 iFrame, i32 iFrameCount);
      //void xor_image_frame2(void * lpdata, i32 iFrame, i32 iFrameCount);


      //double pi();


      void map(bool bApplyAlphaTransform = true) const override; // some implementations may requrire to map to m_pcolorref before manipulate it
      void unmap() const override; // some implementations may require to unmap from m_pcolorref to update *os* bitmap

      //virtual bool update_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage, bool bTransferBuffer = true) override;
      //virtual bool print_window(::aura::draw_interface * puserinteraction, ::message::message * pmessage) override;


   };


} // namespace draw2d_opengl



