// Split to pixmap_t.h by camilo on 2026-07-24 01:46 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap_lease.h"
//#include "acme/graphics/image/lock.h"
#include "acme/prototype/geometry2d/angle.h"


template < typename TYPE >
void sort_image_rgb(TYPE& R, TYPE& G, TYPE& B)
{

#if defined(WINDOWS) || defined(LINUX)

   ::__swap(R, B);

#endif

}




#define PIXMAP_TRANSFER(a) \
::pixmap(::transfer(a)), \
PARTICLE_TRANSFER(a)


class CLASS_DECL_ACME pixmap :
   public pixmap_t,
   virtual public ::particle
{
public:

   
   memory                                 m_memoryPixmap;
   ::interlocked_count                    m_interlockedcountMap;
   ::image::enum_copy_disposition         m_ecopydisposition;
   ::image::enum_mipmap                   m_emipmap;
   int                                    m_iExifOrientation;


   pixmap();
   ~pixmap() override;


   virtual void create_as_descriptor(const ::i32_size &size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG,
                       ::i32 iGoodStride = -1);

   virtual void create_from_data(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan,
                                 ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, bool bPreserve = false);


   inline bool is_ok() const { return ::particle::is_ok() && this->_is_ok(); }
   virtual bool _is_ok() const override;

   //virtual pixmap_lease map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map_base to m_pcolorref before manipulate it

   //virtual pixmap_lease map(const ::i32_rectangle & rectangle) const; // some implementations may requrire to map_base to m_pcolorref before manipulate it

   //virtual void unmap(bool bDoUnmap = false) const; // some implementations may require to unmap from m_pcolorref to update *os* bitmap
   virtual void mult_alpha_fast();

   virtual void set_exif_orientation(int iExifOrientation);

   virtual void on_load_image();

   //virtual void defer_update_image();
   virtual void hue_offset(::f64 dRate);


   //virtual void on_load_image();

   ::subparticle_pointer clone() override;

   virtual void on_exif_orientation();

   virtual void copy(const pixmap_t * ppixmap);
   virtual void copy(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan);

   virtual void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan);

   virtual ::pixmap_pointer get_resized_pixmap(const ::i32_size &size);





   inline ::color::color pixel(::i32 x, ::i32 y) const
   {

      auto pimage32 = image32();

      if (::is_null(this) || ::is_null(pimage32) || x < 0 || y < 0 || x >= m_size.cx || y >= m_size.cy)
      {

         return {};

      }

      return ::image32_get_pixel(pimage32, m_colorindexes, scan_size(), width(), x, y);

   }

   virtual void _draw_raw(const ::i32_rectangle & rectangleTarget, ::pixmap * ppixmap, const ::i32_point & pointSrc = ::i32_point());
   virtual void blend(const ::i32_rectangle & rectangleTarget, ::pixmap * ppixmap, const ::i32_point & pointSrc, ::u8 bA);
   //virtual void blend(const ::i32_point & pointDst, ::pixmap * ppixmap, const ::i32_point & pointSrc, const ::i32_size & size);
   virtual void draw_ignore_alpha(const ::i32_point & pointDst, ::pixmap * ppixmap, const ::i32_rectangle & rectangleSource);


   virtual void draw_error_line(::f64 x1, ::f64 h, ::f64 x2, ::i32 iStyle, const ::color::color & color);


   virtual void rate_rgb(::i32 iMul, ::i32 iDiv);
   //virtual void dc_select(bool bSelect = true);

   virtual ::color::color GetAverageColor();
   virtual ::color::color GetAverageOpaqueColor();
   virtual void blend(::pixmap * ppixmap, ::pixmap * ppixmapRate);
   virtual void Blend(::pixmap * ppixmap, ::pixmap * ppixmapA, ::i32 A);
   virtual void Blend(::pixmap * ppixmap, ::pixmap * ppixmapA);
   virtual void blend(const ::i32_point & pointDst, ::pixmap * ppixmapSrc, const ::i32_point & pointSrc, ::pixmap * ppixmapAlf, const ::i32_point & pointDstAlf, const ::i32_size & size);
   virtual void precision_blend(const ::i32_point & pointDst, ::pixmap * ppixmapAlf, const ::i32_point & pointAlf, const ::i32_size & size);
   virtual void precision_blend(const ::i32_point & pointDst, ::pixmap * ppixmapAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
   virtual void blend(const ::i32_point & pointDst, ::pixmap * ppixmapAlf, const ::i32_point & pointAlf, const ::i32_size & size);
   virtual void blend(const ::i32_point & pointDst, ::pixmap * ppixmapAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
   virtual void blend2(const ::i32_point & pointDst, ::pixmap * ppixmapSrc, const ::i32_point & pointSrc, const ::i32_size & size, ::u8 bA);
   virtual void fork_blend(const ::i32_point & pointDst, ::pixmap * ppixmapAlf, const ::i32_point & pointAlf, const ::i32_size & size);
   virtual void fork_blend(const ::i32_point & pointDst, ::pixmap * ppixmapAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
   //virtual void bitmap_blend(::draw2d::graphics* pgraphics, const ::i32_rectangle & rectangle);

   virtual void color_blend(::color::color color, ::u8 bAlpha);
   virtual void BitBlt(::pixmap * ppixmap, ::i32 op);
   virtual void BitBlt(::i32 cxParam, ::i32 cyParam, ::pixmap * ppixmap, ::i32 op);

   //virtual ::image::lock lock(::i32 stride, ::image::enum_copy_disposition ecopydisposition, ::pixmap * ppixmapLock);
   //virtual ::image::lock no_padding_lock(::image::enum_copy_disposition ecopydisposition, ::pixmap * ppixmapLock);
   //virtual ::image::lock source_lock(::image::enum_copy_disposition ecopydisposition, ::pixmap * ppixmapLock);
   virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc);
   virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::pixmap * ppixmap);

         //virtual void flip_vertical(::pixmap * ppixmap);
      //virtual void flip_horizontal(::pixmap * ppixmap);
      virtual void flip_horizontally();
      virtual void flip_vertically();
      virtual ::pixmap_pointer horizontally_flipped();
      virtual ::pixmap_pointer vertically_flipped();
      //virtual void flipx(::pixmap * ppixmap);
      //virtual void flipy(::pixmap * ppixmap);
      //virtual ::pixmap * flipx();
      //virtual ::pixmap * flipy();

      virtual bool is_rgb_black();
      virtual void do_xor(::pixmap * ppixmap);

      virtual void ToAlpha(::i32 i);
      virtual void ToAlphaAndFill(::i32 i, ::color::color color);
      virtual void GrayToARGB(::color::color color);

      virtual void from_alpha();
      virtual void mult_alpha(::pixmap * ppixmapWork, bool bPreserveAlpha = true);

      virtual void mult_alpha();
      //virtual void mult_alpha_fast();
      virtual void div_alpha();

      virtual void mult_alpha(const ::i32_point & point, const ::i32_size & size);
      virtual void div_alpha(const ::i32_point & point, const ::i32_size & size);

      //virtual void rotated(const angle & angle);
      //virtual ::pixmap_pointer rotated(const angle& angle);
      virtual void rotate(const ::f64_angle & angle, ::f64 dScale = 1.0);
      virtual void rotate(::pixmap * ppixmap, const ::f64_angle & angle, ::f64 dScale = 1.0);
      virtual ::pixmap_pointer rotated(const ::f64_angle & angle, ::f64 dScale = 1.0);

      //virtual void rotate(::pixmap * ppixmap, ::f64 dAngle, ::f64 dScale);
      //virtual void rotate(::pixmap * ppixmap, ::f64 dAngle);
      virtual void Rotate034(::pixmap * ppixmap, ::f64 dAngle, ::f64 dScale);

      //virtual void rotate90(::pixmap * ppixmap);
      //virtual void rotate180(::pixmap * ppixmap);
      //virtual void rotate270(::pixmap * ppixmap);
      //virtual void rotate_angle_90();
      //virtual void rotate_angle_180();
      //virtual void rotate_angle_270();
      //virtual void _90_rotated();
      //virtual void _180_rotated();
      //virtual void _270_rotated();
      virtual void e_rotate_90_flip_horizontally(::pixmap * ppixmap);
      virtual void e_rotate_180_flip_horizontally(::pixmap * ppixmap);
      virtual void e_rotate_270_flip_horizontally(::pixmap * ppixmap);
      virtual void e_rotate_90_flip_horizontally();
      virtual void e_rotate_180_flip_horizontally();
      virtual void e_rotate_270_flip_horizontally();


      virtual void set_rgb(::color::color color);
      virtual void set_rgb(::i32 R, ::i32 G, ::i32 B);
      virtual void tint(::pixmap * ppixmap, ::color::color color);
      virtual void set_rgb_pre_alpha(::i32 R, ::i32 G, ::i32 B, ::i32 A);
      virtual void rgb_from(::pixmap * ppixmap);
      // paint_rgb
      virtual void multiply_rgb_by_source_alpha(::color::color color);

      virtual ::i64 get_rgba_area(::color::color color) const;
      virtual ::i64 get_rgba_area(::color::color color, const ::i32_rectangle &rect) const;
      virtual ::i64 _001GetTopLeftWeightedOpaqueArea(::i32 iAlphaMin) const;
      virtual ::i64 _001GetTopLeftWeightedOpaqueArea(::i32 iAlphaMin, const ::i32_rectangle &rect) const;


      virtual void saturation(::f64 dRate);
      virtual void lightness(::f64 dRate);
      virtual void opacity(::f64 dRate);

      virtual void transform(enum_image eimage);

   virtual void set_mipmap(::image::enum_mipmap emipmap);
   virtual void _set_mipmap(::image::enum_mipmap emipmap);


   virtual void create_isotropic(::pixmap * ppixmap, ::f64 fIsotropicRate);
   //virtual void create_isotropic(f64_array & daRate, ::enum_priority epriority);


      virtual void RadialFill(::u8 a, ::u8 rectangle, ::u8 g, ::u8 b, ::i32 x, ::i32 y, ::i32 iRadius);
      virtual void RadialFill(
      ::u8 a1, ::u8 r1, ::u8 g1, ::u8 b1, // center colors
      ::u8 a2, ::u8 r2, ::u8 g2, ::u8 b2, // border colors
      ::i32 x, ::i32 y, ::i32 iRadius);


      virtual void gradient_fill(::color::color color1, ::color::color color2, const ::i32_point & point1, const ::i32_point & point2);
      virtual void gradient_horizontal_fill(::color::color color1, ::color::color color2, ::i32 start, ::i32 end);
      virtual void gradient_vertical_fill(::color::color color1, ::color::color color2, ::i32 start, ::i32 end);
      virtual void gradient_horizontal_fill(::color::color color1, ::color::color color2);
      virtual void gradient_vertical_fill(::color::color color1, ::color::color color2);


      virtual ::color::color GetPixel(::i32 x, ::i32 y);
      virtual ::color::color GetPixel(const ::i32_point & point) { return GetPixel(point.x, point.y); }
      virtual void Mask(::color::color colorMask, ::color::color colorInMask, ::color::color crOutMask);
      virtual void channel_mask(::u8 uchFind, ::u8 uchSet, ::u8 uchUnset, ::color::enum_channel echannel);
      virtual void transparent_color(::color::color color);

   virtual void DivideRGB(::i32 iDivide);
   virtual void DivideARGB(::i32 iDivide);
   virtual void DivideA(::i32 iDivide);




      virtual void pixelate(::i32 iSize);



      virtual void fill_channel(::i32 C, ::color::enum_channel echannel);
      virtual void white_fill_channel(::i32 C, ::color::enum_channel echannel);
      virtual void fill_byte(uchar uch);
      //virtual void fill(::color32_t level);
      virtual void clear(::color::color colorFill);
      virtual void clear_argb(::i32 A, ::i32 R, ::i32 G, ::i32 B);
      //      virtual void Fill(::i32 R, ::i32 G, ::i32 B);
      //virtual void set_rgb(::i32 R, ::i32 G, ::i32 B);
      virtual void fill_glass(::i32 R, ::i32 G, ::i32 B, ::i32 A);
      virtual void fill_stippled_glass(::i32 R, ::i32 G, ::i32 B);
      virtual void invert();
      virtual void channel_invert(::color::enum_channel echannel);
      virtual void channel_multiply(::f64 dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_multiply(::color::enum_channel echannel, ::pixmap * ppixmap, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_lighten(::color::enum_channel echannel, ::pixmap * ppixmap);
      virtual void channel_darken(::color::enum_channel echannel, ::pixmap * ppixmap);
      virtual void channel_from(::color::enum_channel echannel, ::pixmap * ppixmap);
      virtual void channel_multiply(::color::enum_channel echannel, ::pixmap * ppixmap, const ::i32_rectangle & rectangle, bool bIfAlphaIgnorePreDivPosMult = false);

      virtual void channel_from(::color::enum_channel echannel, ::pixmap * ppixmap, const ::i32_rectangle & rectangle);

      virtual void all_channels_copy(::color::enum_channel echannelSrc, ::pixmap * ppixmap);

      virtual void Map(::i32 ToRgb, ::i32 FromRgb);

      //virtual void create_nanosvg(char_pointer pszXml, int iRedLower, ::f64 dDpi = 0.0);
      //virtual void nanosvg(char_pointer pszXml, ::f64 dDpi = 0.0);

      //virtual void _defer_load_multi_frame_image_(memory_pointer pmemory);

      virtual void op(const ::scoped_string & scopedstr);


         virtual ::memory copy_with_no_stride();
      virtual ::memory vertical_swap_copy_with_no_stride();

      //virtual void from( ::pixmap * ppixmap);

      virtual void Blend(::pixmap * ppixmap, ::i32 A);
      virtual void Darken(::pixmap * ppixmap);
      virtual void Difference(::pixmap * ppixmap);
      virtual void Lighten(::pixmap * ppixmap);
      virtual void Multiply(::pixmap * ppixmap);
      virtual void Screen(::pixmap * ppixmap);

      virtual void lighten(::f64 dRate);

      // virtual void copy_from_no_create(::pixmap * ppixmap, const ::i32_point & point);
      // virtual void copy_from_no_create(::pixmap * ppixmap);
      //virtual void copy_from(::pixmap * ppixmap, const ::i32_point & point, enum_flag eflagCreate = e_flag_success);
      //virtual void copy_from(::pixmap * ppixmap, enum_flag eflagCreate = e_flag_success);
      //virtual void copy_to(::pixmap * ppixmap, const ::i32_point & point = {});
      virtual void copy_from(::pixmap * ppixmap);


      virtual void fill_rectangle(const ::i32_rectangle & rectangle, ::color::color color);

      virtual void fill_rectangle(const ::i32_rectangle & rectangle, ::i32 R, ::i32 G, ::i32 B);


      virtual void fill_glass_rect(const ::i32_rectangle & rectangle, ::i32 R, ::i32 G, ::i32 B, ::i32 A);

      virtual void fill_stippled_glass_rect(const ::i32_rectangle & rectangle, ::i32 R, ::i32 G, ::i32 B);


      virtual void BlendRect(::pixmap * ppixmap, ::i32 x, ::i32 y, ::i32 A);
      virtual void DarkenRect(::pixmap * ppixmap, ::i32 x, ::i32 y);
      virtual void DifferenceRect(::pixmap * ppixmap, ::i32 x, ::i32 y);
      virtual void LightenRect(::pixmap * ppixmap, ::i32 x, ::i32 y);
      virtual void MultiplyRect(::pixmap * ppixmap, ::i32 x, ::i32 y);
      virtual void ScreenRect(::pixmap * ppixmap, ::i32 x, ::i32 y);

      virtual void horizontal_line(::i32 y, ::color::color color, ::i32 x1 = 0, ::i32 x2 = -1);
      virtual void vertical_line(::i32 x, ::color::color color, ::i32 y1 = 0, ::i32 y2 = -1);

      virtual void frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color);
      virtual void frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color, ::i32 width);

      virtual void Line(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 R, ::i32 G, ::i32 B);
      virtual void LineGlass(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 R, ::i32 G, ::i32 B, ::i32 A);

      virtual void create_frame(const ::i32_size & size, ::i32 iFrameCount);
      virtual void set_frame2(void * pdata, ::i32 iFrame, ::i32 iFrameCount);

      virtual void set_frame1(void * pdata, ::i32 iFrame, ::i32 iFrameCount);

      virtual void get_frame(void * pdata, ::i32 iFrame, ::i32 iFrameCount);

      virtual void xor_image_frame2(void * pdata, ::i32 iFrame, ::i32 iFrameCount);


      virtual void create_circle2(::pixmap * ppixmap, ::i32 diameter);
      //virtual void create_circle_with_border(::pixmap * ppixmap, ::i32 diameter);
      virtual void clip_circle(::f64 dWidth);
      virtual void create_framed_square(::pixmap * ppixmap, ::i32 inner, ::i32 outer, ::color::color color);


      virtual void invert_rgb(const ::i32_rectangle & rectangle);
      virtual void invert_rgb();


   inline ::i32 line(::i32 line)
   {

#if defined(__APPLE__)

      return height() - line - 1;

#else

      return line;

#endif

   }


   virtual pixmap_lease map(const ::i32_rectangle & rectangle = {}, bool bApplyAlphaTransform = true);


protected:

   friend class pixmap_lease;
   //friend class ::image::lock;

   virtual void _map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform =
                           true); // some implementations may requrire to map_base to m_pcolorref before manipulate it
   
   
   virtual bool _on_map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform = true);

   virtual void
      _unmap(bool bDoUnmap = false); // some implementations may require to unmap from m_pcolorref to update *os* bitmap

   virtual bool
   _on_unmap(bool bDoUnmap = false); // some implementations may require to unmap from m_pcolorref to update *os* bitmap

   //void unlock() override;


};


//#pragma pack(pop, pixmap)



using pixmap_pointer = ::pointer < ::pixmap >;

inline void image32_t::copy(const ::i32_size & size, ::i32 iStrideDst, const ::pixmap_t * ppixmapSrc)
{
   
   copy(size.minimum(ppixmapSrc->size()), iStrideDst, ppixmapSrc->m_pimage32, ppixmapSrc->m_iScan);

}



inline void image32_t::copy(const ::pixmap_t* p)
{
   copy(::i32_point(), p->size(), p->width() * 4, p->image32(), p->m_iScan);
}



