#pragma once


#include "aura/graphics/image/meta.h"

#include "aura/graphics/image/drawer.h"

#include "aura/graphics/image/source.h"

#include "acme/handler/item.h"

#include "acme/graphics/image/_configuration.h"

#include "acme/prototype/prototype/memory.h"


namespace image
{


   /// <summary>
   /// ::image::image *-> ::image::image_source_pointer concept
   /// </summary>
   class CLASS_DECL_AURA image :
      virtual public ::image::image_meta,
      virtual public ::property_object,
      virtual public ::image::image_drawer,
      virtual public ::image::image_source_interface,
      virtual public ::item
   {
   public:


      memory                              m_memoryMap;
      ::i32_rectangle                     m_rectangleTag;


      image();
      ~image() override;


      void on_initialize_particle() override;


      using image_meta::clear;
      //using object::clear;


      virtual void defer_update_image();
      //   virtual void defer_update_all_frames();


      virtual ::pointer<::image::image>get_image(const ::i32_size & size);
      virtual ::pointer<::image::image>get_image(::i32 cx, ::i32 cy);


      bool _is_set() const override;
      bool _is_ok() const override;
      inline bool is_ok() const { return ::is_set(this) && _is_ok(); }
      inline bool nok() const { return !is_ok(); }


      virtual ::draw2d::graphics * get_graphics() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::graphics * _get_graphics() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::bitmap_pointer get_bitmap() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::bitmap_pointer detach_bitmap();



      virtual ::collection::count get_image_count() const;
      virtual ::image::image_pointer get_image(::collection::index i);


      virtual void set_mipmap(::image::enum_mipmap emipmap);
      virtual void _set_mipmap(::image::enum_mipmap emipmap);


      virtual void create_isotropic(::image::image *pimage);
      virtual void create_isotropic(f64_array & daRate, ::enum_priority epriority);


      virtual void set_origin(const ::i32_point & point);
      //virtual void set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode);

      virtual void set_size_scaler(::f64 dSizeScaler);
      
      
      virtual void create_helper_map();
      virtual void _create_helper_map();


      virtual void on_load_image();
      virtual void on_exif_orientation();
      virtual void fast_copy(::image32_t * pcolor32FullImage);

      //inline ::i32_size get_size() const;

      ::i32_size get_image_drawer_size() const override;


      ::image::image_pointer image_source_image(const ::i32_size &) override;


      // inline concrete < ::i32_size > i32_size(const ::f64_size &, const ::f64_size &, enum_image_selection) const { return get_size(); }
      ::i32_size image_source_size(const ::f64_size &, enum_image_selection) const override;
      ::i32_size image_source_size() const override;
      using image_meta::size;

      //inline ::i32_rectangle rectangle(const ::i32_point & point = {});
      //inline ::i32_rectangle rectangle(const ::i32_point & point = {}) const;


      //inline ::u64 area() const;
      //inline ::i32 width() const;
      //inline ::i32 height() const;


      //inline ::i32 scan_size() const;


      const ::color_indexes & color_indexes() const { return m_colorindexes; }
      ::color_indexes & color_indexes() { return m_colorindexes; }


      virtual void rate_rgb(::i32 iMul, ::i32 iDiv);
      virtual void dc_select(bool bSelect = true);

      virtual ::color::color GetAverageColor();
      virtual ::color::color GetAverageOpaqueColor();
      virtual void blend(::image::image *pimage, ::image::image *imageRate);
      virtual void Blend(::image::image *pimage, ::image::image *imageA, ::i32 A);
      virtual void Blend(::image::image *pimage, ::image::image *imageA);
      virtual void blend(const ::i32_point & pointDst, ::image::image *imageSrc, const ::i32_point & pointSrc, ::image::image *imageAlf, const ::i32_point & pointDstAlf, const ::i32_size & size);
      virtual void precision_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size);
      virtual void precision_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
      virtual void blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size);
      virtual void blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
      virtual void blend2(const ::i32_point & pointDst, ::image::image *imageSrc, const ::i32_point & pointSrc, const ::i32_size & size, ::u8 bA);
      virtual void fork_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size);
      virtual void fork_blend(const ::i32_point & pointDst, ::image::image *imageAlf, const ::i32_point & pointAlf, const ::i32_size & size, ::u8 bA);
      //virtual void bitmap_blend(::draw2d::graphics* pgraphics, const ::i32_rectangle & rectangle);

      virtual void color_blend(::color::color color, ::u8 bAlpha);
      virtual void BitBlt(::image::image *pimage, ::i32 op);
      virtual void BitBlt(::i32 cxParam, ::i32 cyParam, ::image::image *pimage, ::i32 op);
      //virtual ::i32 cos(::i32 i, ::i32 iAngle);
      //virtual ::i32 sin(::i32 i, ::i32 iAngle);
      //virtual ::i32 cos10(::i32 i, ::i32 iAngle);
      //virtual ::i32 sin10(::i32 i, ::i32 iAngle);

      virtual void hue_offset(::f64 dRate);

      virtual void map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map_base to m_pcolorref before manipulate it
      virtual void unmap() const; // some implementations may require to unmap from m_pcolorref to update *os* bitmap


      virtual void _map(bool bApplyAlphaTransform = true);
      virtual void _unmap();

      virtual void set_mapped();

      //virtual void flip_vertical(::image::image *pimage);
      //virtual void flip_horizontal(::image::image *pimage);
      virtual void flip_horizontally();
      virtual void flip_vertically();
      virtual ::image::image_pointer horizontally_flipped();
      virtual ::image::image_pointer vertically_flipped();
      //virtual void flipx(::image::image *pimage);
      //virtual void flipy(::image::image *pimage);
      //virtual ::image::image *flipx();
      //virtual ::image::image *flipy();

      virtual bool is_rgb_black();
      virtual void do_xor(::image::image *pimage);

      virtual void ToAlpha(::i32 i);
      virtual void ToAlphaAndFill(::i32 i, ::color::color color);
      virtual void GrayToARGB(::color::color color);

      virtual void from_alpha();
      virtual void mult_alpha(::image::image *imageWork, bool bPreserveAlpha = true);

      virtual void mult_alpha();
      virtual void mult_alpha_fast();
      virtual void div_alpha();

      virtual void mult_alpha(const ::i32_point & point, const ::i32_size & size);
      virtual void div_alpha(const ::i32_point & point, const ::i32_size & size);

      //virtual void rotated(const angle & angle);
      //virtual ::image::image_pointer rotated(const angle& angle);
      virtual void rotate(const ::f64_angle & angle, ::f64 dScale = 1.0);
      virtual void rotate(::image::image *pimage, const ::f64_angle & angle, ::f64 dScale = 1.0);
      virtual ::image::image_pointer rotated(const ::f64_angle & angle, ::f64 dScale = 1.0);

      //virtual void rotate(::image::image *pimage, ::f64 dAngle, ::f64 dScale);
      //virtual void rotate(::image::image *pimage, ::f64 dAngle);
      virtual void Rotate034(::image::image *pimage, ::f64 dAngle, ::f64 dScale);

      //virtual void rotate90(::image::image *pimage);
      //virtual void rotate180(::image::image *pimage);
      //virtual void rotate270(::image::image *piml);
      //virtual void rotate_angle_90();
      //virtual void rotate_angle_180();
      //virtual void rotate_angle_270();
      //virtual void _90_rotated();
      //virtual void _180_rotated();
      //virtual void _270_rotated();
      virtual void e_rotate_90_flip_horizontally(::image::image *pimage);
      virtual void e_rotate_180_flip_horizontally(::image::image *pimage);
      virtual void e_rotate_270_flip_horizontally(::image::image *pimage);
      virtual void e_rotate_90_flip_horizontally();
      virtual void e_rotate_180_flip_horizontally();
      virtual void e_rotate_270_flip_horizontally();


      virtual void set_rgb(::color::color color);
      virtual void set_rgb(::i32 R, ::i32 G, ::i32 B);
      virtual void tint(::image::image *pimage, ::color::color color);
      virtual void set_rgb_pre_alpha(::i32 R, ::i32 G, ::i32 B, ::i32 A);
      virtual void rgb_from(::image::image *pimage);
      // paint_rgb
      virtual void multiply_rgb_by_source_alpha(::color::color color);

      virtual ::i64 get_rgba_area(::color::color color) const;
      virtual ::i64 get_rgba_area(::color::color color, const ::i32_rectangle &rect) const;
      virtual ::i64 _001GetTopLeftWeightedOpaqueArea(::i32 iAlphaMin) const;
      virtual ::i64 _001GetTopLeftWeightedOpaqueArea(::i32 iAlphaMin, const ::i32_rectangle &rect) const;


      virtual void saturation(::f64 dRate);
      virtual void lightness(::f64 dRate);
      virtual void opacity(::f64 dRate);


      virtual void SetIconMask(::image::icon * picon, ::i32 cx, ::i32 cy);
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


      virtual void create_thumbnail(const ::scoped_string & scopedstrPath);

      virtual void create_ex(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
      virtual void create(::draw2d::graphics* pgraphics);
      virtual void create(const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
      using ::particle::initialize;
      virtual void initialize(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG);
      inline void preserve(const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1)
      {

         return create(size, eflagCreate, iGoodStride, true);

      }
      //virtual void     create(::i32 iWidth, ::i32 iHeight, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1, void bPreserve = false);


      virtual bool host(::pixmap * ppixmap, ::windowing::window * pwindow);
      virtual bool on_host_read_pixels(::pixmap * ppixmapHost) const;
      void destroy() override;
      void destroy_os_data() override;
      //virtual void detach(::image::image *pimage);

      // realization is semantically const
      // image keeps an image and image will be the same,
      // besides the way the Device Context associated with the image (m_spgraphics)
      // interprets or deals with it, may machine
      virtual void realize(::draw2d::graphics* pgraphics) const;
      virtual void unrealize() const;
      virtual bool is_realized() const;
      virtual void defer_realize(::draw2d::graphics* pgraphics) const;

      virtual void DivideRGB(::i32 iDivide);
      virtual void DivideARGB(::i32 iDivide);
      virtual void DivideA(::i32 iDivide);


      //using image_drawer::stretch;
      virtual void stretch_image(::image::image *pimage);


      //virtual void stretch(::draw2d::graphics * pgraphics);
      //virtual void to(::image::image *piml) const;
      //virtual void copy(const ::image::image *pimage, enum_flag eflagCreate = e_flag_success);
      //virtual void stretch(const ::image::image *pimage);
      //virtual void draw_image(::draw2d::graphics* pgraphics);
      //virtual void draw_image(::draw2d::graphics* pgraphics, const ::i32_size & size);
      //virtual void from(const ::i32_point & pointDst, ::draw2d::graphics* pgraphics, const ::i32_point & pointSrc, const ::i32_size & size);
      //using image_drawer::draw;
      virtual void _draw_raw(const ::i32_rectangle & rectangleTarget, ::image::image *pimage, const ::i32_point & pointSrc = ::i32_point());
      virtual void blend(const ::i32_rectangle & rectangleTarget, ::image::image *pimage, const ::i32_point & pointSrc, ::u8 bA);
      //virtual void blend(const ::i32_point & pointDst, ::image::image *piml, const ::i32_point & pointSrc, const ::i32_size & size);
      virtual void draw_ignore_alpha(const ::i32_point & pointDst, ::image::image *pimage, const ::i32_rectangle & rectangleSource);

      //virtual void to(::draw2d::graphics* pgraphics);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_point & point);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_size & size);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_point & point, const ::i32_size & size);
      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_rectangle & rectangle);

      //virtual void to(::draw2d::graphics* pgraphics, const ::i32_point & point, const ::i32_size & size, const ::i32_point & pointSrc);


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
      virtual void channel_multiply(::color::enum_channel echannel, ::image::image *pimage, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_lighten(::color::enum_channel echannel, ::image::image *pimage);
      virtual void channel_darken(::color::enum_channel echannel, ::image::image *pimage);
      virtual void channel_from(::color::enum_channel echannel, ::image::image *pimage);
      virtual void channel_multiply(::color::enum_channel echannel, ::image::image *pimage, const ::i32_rectangle & rectangle, bool bIfAlphaIgnorePreDivPosMult = false);

      virtual void channel_from(::color::enum_channel echannel, ::image::image *pimage, const ::i32_rectangle & rectangle);

      virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc);
      virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image::image *pimage);
      virtual void all_channels_copy(::color::enum_channel echannelSrc, ::image::image *pimage);

      virtual void Map(::i32 ToRgb, ::i32 FromRgb);

      virtual void create_nanosvg(char_pointer pszXml, ::f64 dDpi = 0.0);
      virtual void nanosvg(char_pointer pszXml, ::f64 dDpi = 0.0);

      //virtual void _defer_load_multi_frame_image_(memory_pointer pmemory);

      virtual void op(const ::scoped_string & scopedstr);
      
      
      virtual ::memory copy_with_no_stride();
      virtual ::memory vertical_swap_copy_with_no_stride();

      //virtual void from( ::image::image *piml);

      virtual void Blend(::image::image *piml, ::i32 A);
      virtual void Darken(::image::image *piml);
      virtual void Difference(::image::image *piml);
      virtual void Lighten(::image::image *piml);
      virtual void Multiply(::image::image *piml);
      virtual void Screen(::image::image *piml);

      virtual void lighten(::f64 dRate);

      virtual void copy_from_no_create(::image::image *pimage, const ::i32_point & point);
      virtual void copy_from_no_create(::image::image *pimage);
      virtual void copy_from(::image::image *pimage, const ::i32_point & point, enum_flag eflagCreate = e_flag_success);
      virtual void copy_from(::image::image *pimage, enum_flag eflagCreate = e_flag_success);
      //virtual void copy_to(::image::image *pimage, const ::i32_point & point = {});

      virtual void fill_rectangle(const ::i32_rectangle & rectangle, ::color::color color);

      virtual void fill_rectangle(const ::i32_rectangle & rectangle, ::i32 R, ::i32 G, ::i32 B);


      virtual void fill_glass_rect(const ::i32_rectangle & rectangle, ::i32 R, ::i32 G, ::i32 B, ::i32 A);

      virtual void fill_stippled_glass_rect(const ::i32_rectangle & rectangle, ::i32 R, ::i32 G, ::i32 B);


      virtual void BlendRect(::image::image *piml, ::i32 x, ::i32 y, ::i32 A);
      virtual void DarkenRect(::image::image *piml, ::i32 x, ::i32 y);
      virtual void DifferenceRect(::image::image *piml, ::i32 x, ::i32 y);
      virtual void LightenRect(::image::image *piml, ::i32 x, ::i32 y);
      virtual void MultiplyRect(::image::image *piml, ::i32 x, ::i32 y);
      virtual void ScreenRect(::image::image *piml, ::i32 x, ::i32 y);

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


      virtual void create_circle2(::image::image *piml, ::i32 diameter);
      //virtual void create_circle_with_border(::image::image* piml, ::i32 diameter);
      virtual void clip_circle(::f64 dWidth);
      virtual void create_framed_square(::image::image *piml, ::i32 inner, ::i32 outer, ::color::color color);


      virtual void invert_rgb(const ::i32_rectangle & rectangle);
      virtual void invert_rgb();


      //virtual void     create_image(::i32 cx, ::i32 cy, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1);
      //virtual void     create_image(const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1);



      virtual void transform(enum_image eimage);


      ::f64 pi() const;

      //static void static_initialize();

      inline ::i32 scan_area() { return scan_area_in_bytes() / sizeof(::image32_t); }
      inline ::i32 scan_area_in_bytes() { return m_iScan * m_size.cy; }



      //::stream & write(::stream & stream) const override;
      //::stream & read(::stream & stream) override;


      ::subparticle_pointer clone() override;


      //inline ::i32 line(::i32 line);


      //virtual ::draw2d::graphics * g() const; // { return get_graphics(); }
      inline ::draw2d::graphics * g(const ::f64_size & sizeHint) { return g(); }
      inline ::f64_size origin() const { return ::f64_size(); }

      //inline ::color::color pixel(::i32 x, ::i32 y) const;


      //inline void is_set() const;


      //inline void is_null() const;


      //inline void is_empty() const;


      //inline ::image32_t * get_data();


      //inline const ::image32_t * get_data() const;


      //inline ::image32_t * image32();


      //inline const ::image32_t* image32() const;


      //inline operator ::image32_t* ();


      //inline operator const ::image32_t* () const;


      //inline ::pixmap * pixmap();


      //inline const ::pixmap * pixmap() const;


      //inline operator ::pixmap *();


      //inline operator const ::pixmap *() const;


      //::image_extension * extension();


      ::image::image_extension * get_extension();


      //inline const ::image_extension * extension() const;


      //inline operator ::image_extension * ();


      //inline operator const ::image_extension * () const;



      inline ::u64 area() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_size.area();

      }


      inline ::i32 scan_size() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_iScan;

      }


      inline ::i32 width() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_size.cx;

      }


      inline ::i32 height() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_size.cy;

      }




      inline bool is_null() const
      {

         return ::is_null(this) || m_size.area() <= 0;

      }


      inline bool is_set() const
      {

         return !is_null();

      }


      inline bool is_empty() const
      {

         return is_null();

      }


      inline ::draw2d::graphics* g() const
      {

         return get_graphics();

      }


      inline ::image32_t * image32()
      {

         return m_pimage32;

      }


      inline const ::image32_t * image32() const
      {

         return m_pimage32;

      }


      inline operator ::image32_t * ()
      {

         return image32();

      }


      inline operator const ::image32_t * () const
      {

         return image32();

      }


      inline ::pixmap * pixmap()
      {

         return this;

      }


      inline const ::pixmap * pixmap() const
      {

         return this;

      }


      inline operator ::pixmap* ()
      {

         return this;

      }


      inline operator const ::pixmap* () const
      {

         return this;

      }


      inline ::image::image_extension * extension()
      {

         return m_pextension;

      }


      inline const ::image::image_extension * extension() const
      {

         return m_pextension;

      }


      inline operator image_extension* ()
      {

         return m_pextension;

      }


      inline operator const image_extension* () const
      {

         return m_pextension;

      }


      inline ::image32_t * data()
      {

         return m_pimage32;

      }

      ::image32_t * line_data(::i32 iLine);

      inline ::image32_t * begin()
      {

         return this->data();

      }

      inline const ::image32_t * data() const
      {

         return m_pimage32;

      }


      inline const ::image32_t * begin() const
      {

         return this->data();

      }

      const ::image32_t * get_data() const
      {

         map();

         return image32();

      }


      ::image32_t * get_data()
      {

         map();

         return image32();

      }

      //inline ::image::image & operator = (const ::image::image & image);
      //inline void operator == (const ::image::image & image) const;
      //inline void operator != (const ::image::image & image) const;

      void draw(const ::image::image_drawing & imagedrawing) override;
      bool _draw_blend(const ::image::image_drawing & imagedrawing) override;
      void _draw_raw(const ::image::image_drawing & imagedrawing) override;







      inline image& operator = (const image& image)
      {

         copy_from((::image::image*) & image);

         return *this;

      }


      //inline ::image::image *image::frame(iptr i) const
      //{
      //
      //   auto frames = this->frames();
      //
      //   if (::is_null(frames) || frames->is_empty())
      //   {
      //
      //      if (i == 0)
      //      {
      //
      //         return m_pimpl;
      //
      //      }
      //
      //      return nullptr;
      //
      //   }
      //
      //   auto pointer = frames->ptr_at(i);
      //
      //   return ::is_null(pointer) ? nullptr : pointer->m_pimpl;
      //
      //}
      //

      inline bool operator == (const image& image) const
      {

         return m_pimage32Raw == image.m_pimage32Raw;

      }


      inline bool operator != (const image& image) const
      {

         return !operator ==(image);

      }


      inline ::i32 line(::i32 line)
      {

#if defined(__APPLE__)

         return height() - line - 1;

#else

         return line;

#endif

      }


      //inline ::i32_size image::size() const
      //{
      //
      //   return m_size;
      //
      //}


      inline ::i32_rectangle rectangle(const ::i32_point & point = {})
      {

         return ::i32_rectangle(point, get_size() - point);

      }


      inline ::i32_rectangle rectangle(const ::i32_point & point = {}) const
      {

         return ::i32_rectangle(point, get_size() - point);

      }


      inline ::color::color pixel(::i32 x, ::i32 y) const
      {

         auto pimage32 = image32();

         if (::is_null(this) || ::is_null(pimage32) || x < 0 || y < 0 || x >= m_size.cx || y >= m_size.cy)
         {

            return {};

         }

         return ::image32_get_pixel(pimage32, m_colorindexes, scan_size(), width(), x, y);

      }


      inline ::i32_size get_size() const { return size(); }

      virtual ::image::image_pointer get_resized_image(const ::i32_size & size);


   };


} // namespace image

////
////
//// Compose, Construct, Create and Add_Reference Porngraphs
////
//// createø      // return ::pointer<BASE_TYPE>// _id atom // _new TYPE
//// constructø     // ::pointer<BASE_TYPE>&    // _id atom // _new TYPE // SOURCE psource
//// constructø   // ::pointer<BASE_TYPE>&      // _id atom // _new TYPE // SOURCE psource
//// add_reference // ::pointer<BASE_TYPE>& SOURCE psource
////
//// >>
////
////
//
//
//inline ::image::image_pointer __create_image()
//{
//
//   return ::createø<::image::image>();
//
//}
//
//// template < typename COMPOSER >
//// void constructø(COMPOSER && pcomposer, __ & pimage);
// //
// template < typename COMPOSER >
// inline void constructø(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, ::image::image *pimageSource);
// //
// //
// template < typename COMPOSER >
// inline void constructø(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::i32_size & size, ::enum_flag eflagCreate = OK, ::i32 iGoodStride = -1, void bPreserve = false);
// //
// //
// template < typename COMPOSER >
// inline void __preserve(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::i32_size & size, ::enum_flag eflagCreate = OK, ::i32 iGoodStride = -1);
// //
//
//void constructø(::image::image_pointer & pimage);

inline void __call__construct(::image::image_pointer & pimage, ::image::image *pimageSource);
//
//
inline void __call__construct(::image::image_pointer & pimage, const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
//
//
inline void __preserve(::image::image_pointer & pimage, const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1);
//
//
//


//template < >
//inline bool is_ok(const ::image::image *pimage)
//{
//
//   if (::is_null(pimage))
//   {
//
//      return false;
//
//   }
//
//   return pimage->is_ok();
//
//}
//
//
//template < typename TYPE >
//inline bool not_ok(const TYPE * p) { return is_null(p); }


//inline bool not_ok(const ::image::image *pimage)
//{
//
//   return !is_ok(pimage);
//
//}


#include "_image_impl.h"



