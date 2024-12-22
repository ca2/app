#pragma once


#include "meta.h"

#include "drawer.h"

#include "source.h"

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
      ::int_rectangle                     m_rectangleTag;


      image();
      ~image() override;


      void on_initialize_particle() override;


      using image_meta::clear;
      //using object::clear;


      virtual void defer_update_image();
      //   virtual void defer_update_all_frames();


      virtual ::pointer<::image::image>get_image(const ::int_size & size);
      virtual ::pointer<::image::image>get_image(int cx, int cy);


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
      virtual void create_isotropic(double_array & daRate, ::enum_priority epriority);


      virtual void set_origin(const ::int_point & point);
      virtual void set_font_factor(double dFactor);
      //virtual void set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode);


      virtual void create_helper_map();
      virtual void _create_helper_map();


      virtual void on_load_image();
      virtual void on_exif_orientation();
      virtual void fast_copy(::image32_t * pcolor32FullImage);

      //inline ::int_size get_size() const;

      ::int_size get_image_drawer_size() const override;


      ::image::image_pointer image_source_image(const ::int_size &) override;


      // inline concrete < ::int_size > int_size(const ::double_size &, const ::double_size &, enum_image_selection) const { return get_size(); }
      ::int_size image_source_size(const ::double_size &, enum_image_selection) const override;
      ::int_size image_source_size() const override;
      using image_meta::size;

      //inline ::int_rectangle rectangle(const ::int_point & point = {});
      //inline ::int_rectangle rectangle(const ::int_point & point = {}) const;


      //inline huge_natural area() const;
      //inline int width() const;
      //inline int height() const;


      //inline int scan_size() const;


      const ::color_indexes & color_indexes() const { return m_colorindexes; }
      ::color_indexes & color_indexes() { return m_colorindexes; }


      virtual void rate_rgb(int iMul, int iDiv);
      virtual void dc_select(bool bSelect = true);

      virtual ::color::color GetAverageColor();
      virtual ::color::color GetAverageOpaqueColor();
      virtual void blend(::image::image *pimage, ::image::image *imageRate);
      virtual void Blend(::image::image *pimage, ::image::image *imageA, int A);
      virtual void Blend(::image::image *pimage, ::image::image *imageA);
      virtual void blend(const ::int_point & pointDst, ::image::image *imageSrc, const ::int_point & pointSrc, ::image::image *imageAlf, const ::int_point & pointDstAlf, const ::int_size & size);
      virtual void precision_blend(const ::int_point & pointDst, ::image::image *imageAlf, const ::int_point & pointAlf, const ::int_size & size);
      virtual void precision_blend(const ::int_point & pointDst, ::image::image *imageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA);
      virtual void blend(const ::int_point & pointDst, ::image::image *imageAlf, const ::int_point & pointAlf, const ::int_size & size);
      virtual void blend(const ::int_point & pointDst, ::image::image *imageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA);
      virtual void blend2(const ::int_point & pointDst, ::image::image *imageSrc, const ::int_point & pointSrc, const ::int_size & size, unsigned char bA);
      virtual void fork_blend(const ::int_point & pointDst, ::image::image *imageAlf, const ::int_point & pointAlf, const ::int_size & size);
      virtual void fork_blend(const ::int_point & pointDst, ::image::image *imageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA);
      //virtual void bitmap_blend(::draw2d::graphics* pgraphics, const ::int_rectangle & rectangle);

      virtual void color_blend(::color::color color, unsigned char bAlpha);
      virtual void BitBlt(::image::image *pimage, int op);
      virtual void BitBlt(int cxParam, int cyParam, ::image::image *pimage, int op);
      //virtual int cos(int i, int iAngle);
      //virtual int sin(int i, int iAngle);
      //virtual int cos10(int i, int iAngle);
      //virtual int sin10(int i, int iAngle);

      virtual void hue_offset(double dRate);

      virtual void map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map to m_pcolorref before manipulate it
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

      virtual void ToAlpha(int i);
      virtual void ToAlphaAndFill(int i, ::color::color color);
      virtual void GrayToARGB(::color::color color);

      virtual void from_alpha();
      virtual void mult_alpha(::image::image *imageWork, bool bPreserveAlpha = true);

      virtual void mult_alpha();
      virtual void mult_alpha_fast();
      virtual void div_alpha();

      virtual void mult_alpha(const ::int_point & point, const ::int_size & size);
      virtual void div_alpha(const ::int_point & point, const ::int_size & size);

      //virtual void rotated(const angle & angle);
      //virtual ::image::image_pointer rotated(const angle& angle);
      virtual void rotate(const ::double_angle & angle, double dScale = 1.0);
      virtual void rotate(::image::image *pimage, const ::double_angle & angle, double dScale = 1.0);
      virtual ::image::image_pointer rotated(const ::double_angle & angle, double dScale = 1.0);

      //virtual void rotate(::image::image *pimage, double dAngle, double dScale);
      //virtual void rotate(::image::image *pimage, double dAngle);
      virtual void Rotate034(::image::image *pimage, double dAngle, double dScale);

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
      virtual void set_rgb(int R, int G, int B);
      virtual void tint(::image::image *pimage, ::color::color color);
      virtual void set_rgb_pre_alpha(int R, int G, int B, int A);
      virtual void rgb_from(::image::image *pimage);
      // paint_rgb
      virtual void multiply_rgb_by_source_alpha(::color::color color);

      virtual huge_integer get_rgba_area(::color::color color) const;
      virtual huge_integer get_rgba_area(::color::color color, const ::int_rectangle &rect) const;
      virtual huge_integer _001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const;
      virtual huge_integer _001GetTopLeftWeightedOpaqueArea(int iAlphaMin, const ::int_rectangle &rect) const;


      virtual void saturation(double dRate);
      virtual void lightness(double dRate);
      virtual void opacity(double dRate);


      virtual void SetIconMask(::image::icon * picon, int cx, int cy);
      virtual void RadialFill(unsigned char a, unsigned char rectangle, unsigned char g, unsigned char b, int x, int y, int iRadius);
      virtual void RadialFill(
      unsigned char a1, unsigned char r1, unsigned char g1, unsigned char b1, // center colors
      unsigned char a2, unsigned char r2, unsigned char g2, unsigned char b2, // border colors
      int x, int y, int iRadius);


      virtual void gradient_fill(::color::color color1, ::color::color color2, const ::int_point & point1, const ::int_point & point2);
      virtual void gradient_horizontal_fill(::color::color color1, ::color::color color2, int start, int end);
      virtual void gradient_vertical_fill(::color::color color1, ::color::color color2, int start, int end);
      virtual void gradient_horizontal_fill(::color::color color1, ::color::color color2);
      virtual void gradient_vertical_fill(::color::color color1, ::color::color color2);


      virtual ::color::color GetPixel(int x, int y);
      virtual ::color::color GetPixel(const ::int_point & point) { return GetPixel(point.x(), point.y()); }
      virtual void Mask(::color::color colorMask, ::color::color colorInMask, ::color::color crOutMask);
      virtual void channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, ::color::enum_channel echannel);
      virtual void transparent_color(::color::color color);


      virtual void create_thumbnail(const ::string & pszPath);

      virtual void create_ex(const ::int_size & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
      virtual void create(::draw2d::graphics* pgraphics);
      virtual void create(const ::int_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
      using ::particle::initialize;
      virtual void initialize(const ::int_size & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG);
      inline void preserve(const ::int_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1)
      {

         return create(size, eflagCreate, iGoodStride, true);

      }
      //virtual void     create(int iWidth, int iHeight, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, void bPreserve = false);


      virtual bool host(::pixmap * ppixmap);
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

      virtual void DivideRGB(int iDivide);
      virtual void DivideARGB(int iDivide);
      virtual void DivideA(int iDivide);


      //using image_drawer::stretch;
      virtual void stretch_image(::image::image *pimage);


      //virtual void stretch(::draw2d::graphics * pgraphics);
      //virtual void to(::image::image *piml) const;
      //virtual void copy(const ::image::image *pimage, enum_flag eflagCreate = e_flag_success);
      //virtual void stretch(const ::image::image *pimage);
      //virtual void draw_image(::draw2d::graphics* pgraphics);
      //virtual void draw_image(::draw2d::graphics* pgraphics, const ::int_size & size);
      //virtual void from(const ::int_point & pointDst, ::draw2d::graphics* pgraphics, const ::int_point & pointSrc, const ::int_size & size);
      //using image_drawer::draw;
      virtual void _draw_raw(const ::int_rectangle & rectangleTarget, ::image::image *pimage, const ::int_point & pointSrc = ::int_point());
      virtual void blend(const ::int_rectangle & rectangleTarget, ::image::image *pimage, const ::int_point & pointSrc, unsigned char bA);
      //virtual void blend(const ::int_point & pointDst, ::image::image *piml, const ::int_point & pointSrc, const ::int_size & size);
      virtual void draw_ignore_alpha(const ::int_point & pointDst, ::image::image *pimage, const ::int_rectangle & rectangleSource);

      //virtual void to(::draw2d::graphics* pgraphics);
      //virtual void to(::draw2d::graphics* pgraphics, const ::int_point & point);
      //virtual void to(::draw2d::graphics* pgraphics, const ::int_size & size);
      //virtual void to(::draw2d::graphics* pgraphics, const ::int_point & point, const ::int_size & size);
      //virtual void to(::draw2d::graphics* pgraphics, const ::int_rectangle & rectangle);

      //virtual void to(::draw2d::graphics* pgraphics, const ::int_point & point, const ::int_size & size, const ::int_point & pointSrc);


      virtual void pixelate(int iSize);



      virtual void fill_channel(int C, ::color::enum_channel echannel);
      virtual void white_fill_channel(int C, ::color::enum_channel echannel);
      virtual void fill_byte(uchar uch);
      //virtual void fill(::color32_t level);
      virtual void clear(::color::color colorFill);
      virtual void clear_argb(int A, int R, int G, int B);
      //      virtual void Fill(int R, int G, int B);
      //virtual void set_rgb(int R, int G, int B);
      virtual void fill_glass(int R, int G, int B, int A);
      virtual void fill_stippled_glass(int R, int G, int B);
      virtual void invert();
      virtual void channel_invert(::color::enum_channel echannel);
      virtual void channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_multiply(::color::enum_channel echannel, ::image::image *pimage, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_lighten(::color::enum_channel echannel, ::image::image *pimage);
      virtual void channel_darken(::color::enum_channel echannel, ::image::image *pimage);
      virtual void channel_from(::color::enum_channel echannel, ::image::image *pimage);
      virtual void channel_multiply(::color::enum_channel echannel, ::image::image *pimage, const ::int_rectangle & rectangle, bool bIfAlphaIgnorePreDivPosMult = false);

      virtual void channel_from(::color::enum_channel echannel, ::image::image *pimage, const ::int_rectangle & rectangle);

      virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc);
      virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image::image *pimage);
      virtual void all_channels_copy(::color::enum_channel echannelSrc, ::image::image *pimage);

      virtual void Map(int ToRgb, int FromRgb);

      virtual void create_nanosvg(char * pszXml, double dDpi = 0.0);
      virtual void nanosvg(char * pszXml, double dDpi = 0.0);

      //virtual void _defer_load_multi_frame_image_(memory_pointer pmemory);

      virtual void op(string str);

      //virtual void from( ::image::image *piml);

      virtual void Blend(::image::image *piml, int A);
      virtual void Darken(::image::image *piml);
      virtual void Difference(::image::image *piml);
      virtual void Lighten(::image::image *piml);
      virtual void Multiply(::image::image *piml);
      virtual void Screen(::image::image *piml);

      virtual void lighten(double dRate);

      virtual void copy_from_no_create(::image::image *pimage, const ::int_point & point);
      virtual void copy_from_no_create(::image::image *pimage);
      virtual void copy_from(::image::image *pimage, const ::int_point & point, enum_flag eflagCreate = e_flag_success);
      virtual void copy_from(::image::image *pimage, enum_flag eflagCreate = e_flag_success);
      //virtual void copy_to(::image::image *pimage, const ::int_point & point = {});

      virtual void fill_rectangle(const ::int_rectangle & rectangle, ::color::color color);

      virtual void fill_rectangle(const ::int_rectangle & rectangle, int R, int G, int B);


      virtual void fill_glass_rect(const ::int_rectangle & rectangle, int R, int G, int B, int A);

      virtual void fill_stippled_glass_rect(const ::int_rectangle & rectangle, int R, int G, int B);


      virtual void BlendRect(::image::image *piml, int x, int y, int A);
      virtual void DarkenRect(::image::image *piml, int x, int y);
      virtual void DifferenceRect(::image::image *piml, int x, int y);
      virtual void LightenRect(::image::image *piml, int x, int y);
      virtual void MultiplyRect(::image::image *piml, int x, int y);
      virtual void ScreenRect(::image::image *piml, int x, int y);

      virtual void horizontal_line(int y, ::color::color color, int x1 = 0, int x2 = -1);
      virtual void vertical_line(int x, ::color::color color, int y1 = 0, int y2 = -1);

      virtual void frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color);
      virtual void frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width);

      virtual void Line(int x1, int y1, int x2, int y2, int R, int G, int B);
      virtual void LineGlass(int x1, int y1, int x2, int y2, int R, int G, int B, int A);

      virtual void create_frame(const ::int_size & size, int iFrameCount);
      virtual void set_frame2(void * pdata, int iFrame, int iFrameCount);

      virtual void set_frame1(void * pdata, int iFrame, int iFrameCount);

      virtual void get_frame(void * pdata, int iFrame, int iFrameCount);

      virtual void xor_image_frame2(void * pdata, int iFrame, int iFrameCount);


      virtual void create_circle(::image::image *piml, int diameter);
      virtual void create_framed_square(::image::image *piml, int inner, int outer, ::color::color color);


      virtual void invert_rgb(const ::int_rectangle & rectangle);
      virtual void invert_rgb();


      //virtual void     create_image(int cx, int cy, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);
      //virtual void     create_image(const ::int_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);



      virtual void transform(enum_image eimage);


      double pi() const;

      //static void static_initialize();

      inline int scan_area() { return scan_area_in_bytes() / sizeof(::image32_t); }
      inline int scan_area_in_bytes() { return m_iScan * m_size.cy(); }



      //::stream & write(::stream & stream) const override;
      //::stream & read(::stream & stream) override;


      ::subparticle_pointer clone() override;


      //inline int line(int line);


      //virtual ::draw2d::graphics * g() const; // { return get_graphics(); }
      inline ::draw2d::graphics * g(const ::double_size & sizeHint) { return g(); }
      inline ::double_size origin() const { return ::double_size(); }

      //inline ::color::color pixel(int x, int y) const;


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



      inline huge_natural area() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_size.area();

      }


      inline int scan_size() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_iScan;

      }


      inline int width() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_size.cx();

      }


      inline int height() const
      {

         if (::is_null(this))
         {

            return 0;

         }

         return m_size.cy();

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

      ::image32_t * line_data(int iLine);

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


      inline int line(int line)
      {

#if defined(__APPLE__)

         return height() - line - 1;

#else

         return line;

#endif

      }


      //inline ::int_size image::size() const
      //{
      //
      //   return m_size;
      //
      //}


      inline ::int_rectangle rectangle(const ::int_point & point = {})
      {

         return ::int_rectangle(point, get_size() - point);

      }


      inline ::int_rectangle rectangle(const ::int_point & point = {}) const
      {

         return ::int_rectangle(point, get_size() - point);

      }


      inline ::color::color pixel(int x, int y) const
      {

         auto pimage32 = image32();

         if (::is_null(this) || ::is_null(pimage32) || x < 0 || y < 0 || x >= m_size.cx() || y >= m_size.cy())
         {

            return {};

         }

         return ::image32_get_pixel(pimage32, m_colorindexes, scan_size(), width(), x, y);

      }


      inline ::int_size get_size() const { return size(); }

      virtual ::image::image_pointer get_resized_image(const ::int_size & size);


   };


} // namespace image

////
////
//// Compose, Construct, Create and Add_Reference Porngraphs
////
//// __øcreate      // return ::pointer<BASE_TYPE>// _id atom // _new TYPE
//// __øconstruct     // ::pointer<BASE_TYPE>&    // _id atom // _new TYPE // SOURCE psource
//// __øconstruct   // ::pointer<BASE_TYPE>&      // _id atom // _new TYPE // SOURCE psource
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
//   return ::__øcreate<::image::image>();
//
//}
//
//// template < typename COMPOSER >
//// void __øconstruct(COMPOSER && pcomposer, __ & pimage);
// //
// template < typename COMPOSER >
// inline void __øconstruct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, ::image::image *pimageSource);
// //
// //
// template < typename COMPOSER >
// inline void __øconstruct(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::int_size & size, ::enum_flag eflagCreate = OK, int iGoodStride = -1, void bPreserve = false);
// //
// //
// template < typename COMPOSER >
// inline void __preserve(COMPOSER && pcomposer, ::pointer<::image::image>& pimage, const ::int_size & size, ::enum_flag eflagCreate = OK, int iGoodStride = -1);
// //
//
//void __øconstruct(::image::image_pointer & pimage);

inline void __call__construct(::image::image_pointer & pimage, ::image::image *pimageSource);
//
//
inline void __call__construct(::image::image_pointer & pimage, const ::int_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
//
//
inline void __preserve(::image::image_pointer & pimage, const ::int_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1);
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



