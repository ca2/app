#pragma once


#include "meta.h"

#include "drawer.h"

#include "source.h"


/// <summary>
/// image * -> image_source_pointer concept
/// </summary>
class CLASS_DECL_AURA image :
   virtual public ::image_meta,
   virtual public ::object,
   virtual public ::image_drawer,
   virtual public ::image_source_interface
{
public:


   struct CLASS_DECL_AURA load_options
   {
   public:


      bool sync = true;
      bool cache = true;
      bool helper_maps = false;
      synchronization_object * psync;
      ::function < void(image *) > functionLoaded;

   };




   memory                              m_memoryMap;
   ::rectangle_i32                     m_rectangleTag;


   image();
   ~image() override;


   void on_initialize_object() override;


   using image_meta::clear;
   using object::clear;


   virtual void defer_update_image();


   virtual __pointer(::image) get_image(const ::size_i32 & size);
   virtual __pointer(::image) get_image(::i32 cx, ::i32 cy);


   inline bool is_ok() const { return ::is_set(this) && (::pixmap::is_ok() && ::object::is_ok()); }


   virtual ::draw2d::graphics * get_graphics() const; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::graphics * _get_graphics() const; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::bitmap_pointer get_bitmap() const; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::bitmap_pointer detach_bitmap();


   
   virtual ::count get_image_count() const;
   virtual ::image_pointer get_image(index i);

   
   virtual void set_mipmap(::draw2d::enum_mipmap emipmap);
   virtual void _set_mipmap(::draw2d::enum_mipmap emipmap);

   
   virtual void create_isotropic(::image * pimage);
   virtual void create_isotropic(double_array & daRate, ::enum_priority epriority);


   virtual void set_origin(const ::point_i32 & point);
   virtual void set_font_factor(double dFactor);
   //virtual void set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode);


   virtual void create_helper_map();
   virtual void _create_helper_map();


   virtual void on_load_image();
   virtual void on_exif_orientation();
   virtual void fast_copy(::color32_t * pcolor32FullImage);

   //inline ::size_i32 get_size() const;

   ::size_i32 get_image_drawer_size() const override;


   ::image_pointer image_source_image(const concrete < ::size_i32 > &) override;


   // inline concrete < ::size_i32 > size_i32(const ::size_f64 &, const ::size_f64 &, enum_image_selection) const { return get_size(); }
   concrete < ::size_i32 > image_source_size(const ::size_f64 &, enum_image_selection) const override;
   concrete < ::size_i32 > image_source_size() const override;
   using image_meta::size;
   
   //inline ::rectangle_i32 rectangle(const ::point_i32 & point = nullptr);
   //inline ::rectangle_i32 rectangle(const ::point_i32 & point = nullptr) const;


   //inline ::u64 area() const;
   //inline ::i32 width() const;
   //inline ::i32 height() const;


   //inline int scan_size() const;


   virtual void rate_rgb(int iMul, int iDiv);
   virtual void dc_select(bool bSelect = true);

   virtual ::color::color GetAverageColor();
   virtual ::color::color GetAverageOpaqueColor();
   virtual void blend(::image * pimage, ::image * imageRate);
   virtual void Blend(::image * pimage, ::image * imageA, i32 A);
   virtual void Blend(::image * pimage, ::image * imageA);
   virtual void blend(const ::point_i32 & pointDst, ::image * imageSrc, const ::point_i32 & pointSrc, ::image * imageAlf, const ::point_i32 & pointDstAlf, const ::size_i32 & size);
   virtual void precision_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size);
   virtual void precision_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA);
   virtual void blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size);
   virtual void blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA);
   virtual void blend2(const ::point_i32 & pointDst, ::image * imageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size, byte bA);
   virtual void fork_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size);
   virtual void fork_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA);
   //virtual void bitmap_blend(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle);

   virtual void color_blend(::color32_t color32, byte bAlpha);
   virtual void BitBlt(::image * pimage, i32 op);
   virtual void BitBlt(int cxParam, int cyParam, ::image * pimage, i32 op);
   //virtual i32 cos(i32 i, i32 iAngle);
   //virtual i32 sin(i32 i, i32 iAngle);
   //virtual i32 cos10(i32 i, i32 iAngle);
   //virtual i32 sin10(i32 i, i32 iAngle);

   virtual void hue_offset(double dRate);

   virtual void map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map to m_pcolorref before manipulate it
   virtual void unmap() const; // some implementations may require to unmap from m_pcolorref to update *os* bitmap


   virtual void _map(bool bApplyAlphaTransform = true);
   virtual void _unmap();

   virtual void set_mapped();

   //virtual void flip_vertical(::image * pimage);
   //virtual void flip_horizontal(::image * pimage);
   virtual void flip_horizontally();
   virtual void flip_vertically();
   virtual image_pointer horizontally_flipped();
   virtual image_pointer vertically_flipped();
   //virtual void flipx(::image * pimage);
   //virtual void flipy(::image * pimage);
   //virtual ::image * flipx();
   //virtual ::image * flipy();

   virtual bool is_rgb_black();
   virtual void do_xor(::image * pimage);

   virtual void ToAlpha(i32 i);
   virtual void ToAlphaAndFill(i32 i, ::color32_t color32);
   virtual void GrayToARGB(::color32_t color32);

   virtual void from_alpha();
   virtual void mult_alpha(::image * imageWork, bool bPreserveAlpha = true);

   virtual void mult_alpha();
   virtual void mult_alpha_fast();
   virtual void div_alpha();

   virtual void mult_alpha(const ::point_i32 & point, const ::size_i32 & size);
   virtual void div_alpha(const ::point_i32 & point, const ::size_i32 & size);

   //virtual void rotated(const angle & angle);
   //virtual image_pointer rotated(const angle& angle);
   virtual void rotate(const ::angle& angle, double dScale = 1.0);
   virtual void rotate(::image * pimage, const ::angle& angle, double dScale = 1.0);
   virtual image_pointer rotated(const ::angle& angle, double dScale = 1.0);

   //virtual void rotate(::image * pimage, double dAngle, double dScale);
   //virtual void rotate(::image * pimage, double dAngle);
   virtual void Rotate034(::image * pimage, double dAngle, double dScale);

   //virtual void rotate90(::image * pimage);
   //virtual void rotate180(::image * pimage);
   //virtual void rotate270(::image * piml);
   //virtual void rotate_angle_90();
   //virtual void rotate_angle_180();
   //virtual void rotate_angle_270();
   //virtual void _90_rotated();
   //virtual void _180_rotated();
   //virtual void _270_rotated();
   virtual void e_rotate_90_flip_horizontally(::image * pimage);
   virtual void e_rotate_180_flip_horizontally(::image * pimage);
   virtual void e_rotate_270_flip_horizontally(::image * pimage);
   virtual void e_rotate_90_flip_horizontally();
   virtual void e_rotate_180_flip_horizontally();
   virtual void e_rotate_270_flip_horizontally();


   virtual void set_rgb(::color32_t color32);
   virtual void set_rgb(i32 R, i32 G, i32 B);
   virtual void tint(::image * pimage, const ::color::color & color);
   virtual void set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A);
   virtual void rgb_from(::image * pimage);
   virtual void paint_rgb(const ::color::color & color);

   virtual ::i64 get_rgba_area(const ::color::color & color) const;
   virtual ::i64 get_rgba_area(const ::color::color & color, const RECTANGLE_I32 * lpcrect) const;
   virtual ::i64 _001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const;
   virtual ::i64 _001GetTopLeftWeightedOpaqueArea(int iAlphaMin, const RECTANGLE_I32 * lpcrect) const;


   virtual void saturation(double dRate);
   virtual void lightness(double dRate);
   virtual void opacity(double dRate);


   virtual void SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy);
   virtual void RadialFill(byte a, byte rectangle, byte g, byte b, i32 x, i32 y, i32 iRadius);
   virtual void RadialFill(
   byte a1, byte r1, byte g1, byte b1, // center colors
   byte a2, byte r2, byte g2, byte b2, // border colors
   i32 x, i32 y, i32 iRadius);


   virtual void gradient_fill(::color32_t clr1, ::color32_t clr2, const point_i32 & point1, const point_i32 & point2);
   virtual void gradient_horizontal_fill(::color32_t clr1, ::color32_t clr2, int start, int end);
   virtual void gradient_vertical_fill(::color32_t clr1, ::color32_t clr2, int start, int end);
   virtual void gradient_horizontal_fill(::color32_t clr1, ::color32_t clr2);
   virtual void gradient_vertical_fill(::color32_t clr1, ::color32_t clr2);


   virtual u32 GetPixel(i32 x, i32 y);
   virtual u32 GetPixel(const ::point_i32 & point) { return GetPixel(point.x, point.y); }
   virtual void Mask(::color32_t crMask, ::color32_t crInMask, ::color32_t crOutMask);
   virtual void channel_mask(byte uchFind, byte uchSet, byte uchUnset, ::color::enum_channel echannel);
   virtual void transparent_color(const ::color::color & color);


   virtual void create_thumbnail(const ::string & pszPath);

   virtual void create_ex(const ::size_i32 & size, ::color32_t * pcolorref, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
   virtual void create(::draw2d::graphics* pgraphics);
   virtual void create(const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
   using ::object::initialize;
   virtual void initialize(const ::size_i32 & size, ::color32_t * pcolorref, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG);
   inline void preserve(const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1)
   {

      return create(size, eflagCreate, iGoodStride, true);

   }
   //virtual void     create(i32 iWidth, i32 iHeight, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, void bPreserve = false);


   virtual bool host(const ::pixmap * ppixmap);
   virtual bool on_host_read_pixels(const ::pixmap * ppixmap);
   void destroy() override;
   void destroy_os_data() override;
   //virtual void detach(::image * pimage);

   // realization is semantically const
   // image keeps an image and image will be the same,
   // besides the way the Device Context associated with the image (m_spgraphics)
   // interprets or deals with it, may machine
   virtual void realize(::draw2d::graphics* pgraphics) const;
   virtual void unrealize() const;
   virtual bool is_realized() const;
   virtual void defer_realize(::draw2d::graphics* pgraphics) const;

   virtual void DivideRGB(i32 iDivide);
   virtual void DivideARGB(i32 iDivide);
   virtual void DivideA(i32 iDivide);

   
   //using image_drawer::stretch;
   virtual void stretch_image(::image * pimage);


   //virtual void stretch(::draw2d::graphics * pgraphics);
   //virtual void to(::image * piml) const;
   //virtual void copy(const ::image * pimage, enum_flag eflagCreate = e_flag_success);
   //virtual void stretch(const ::image * pimage);
   //virtual void draw_image(::draw2d::graphics* pgraphics);
   //virtual void draw_image(::draw2d::graphics* pgraphics, const ::size_i32 & size);
   //virtual void from(const ::point_i32 & pointDst, ::draw2d::graphics* pgraphics, const ::point_i32 & pointSrc, const ::size_i32 & size);
   //using image_drawer::draw;
   virtual void _draw_raw(const ::rectangle_i32 & rectangleTarget, ::image * pimage, const ::point_i32 & pointSrc = ::point_i32());
   virtual void blend(const ::rectangle_i32 & rectangleTarget, ::image * pimage, const ::point_i32 & pointSrc, byte bA);
   //virtual void blend(const ::point_i32 & pointDst, ::image * piml, const ::point_i32 & pointSrc, const ::size_i32 & size);
   virtual void draw_ignore_alpha(const ::point_i32 & pointDst, ::image * pimage, const ::rectangle_i32 & rectangleSource);

   //virtual void to(::draw2d::graphics* pgraphics);
   //virtual void to(::draw2d::graphics* pgraphics, const ::point_i32 & point);
   //virtual void to(::draw2d::graphics* pgraphics, const ::size_i32 & size);
   //virtual void to(::draw2d::graphics* pgraphics, const ::point_i32 & point, const ::size_i32 & size);
   //virtual void to(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle);

   //virtual void to(::draw2d::graphics* pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc);


   virtual void pixelate(i32 iSize);



   virtual void fill_channel(i32 C, ::color::enum_channel echannel);
   virtual void white_fill_channel(i32 C, ::color::enum_channel echannel);
   virtual void fill_byte(uchar uch);
   virtual void fill(::color32_t level);
   virtual void clear(const ::color::color & colorFill);
   virtual void fill(i32 A, i32 R, i32 G, i32 B);
   //      virtual void Fill(i32 R, i32 G, i32 B);
   //virtual void set_rgb(i32 R, i32 G, i32 B);
   virtual void fill_glass(i32 R, i32 G, i32 B, i32 A);
   virtual void fill_stippled_glass(i32 R, i32 G, i32 B);
   virtual void invert();
   virtual void channel_invert(::color::enum_channel echannel);
   virtual void channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false);
   virtual void channel_multiply(::color::enum_channel echannel, ::image * pimage, bool bIfAlphaIgnorePreDivPosMult = false);
   virtual void channel_lighten(::color::enum_channel echannel, ::image * pimage);
   virtual void channel_darken(::color::enum_channel echannel, ::image * pimage);
   virtual void channel_from(::color::enum_channel echannel, ::image * pimage);
   virtual void channel_multiply(::color::enum_channel echannel, ::image * pimage, const ::rectangle_i32 & rectangle, bool bIfAlphaIgnorePreDivPosMult = false);

   virtual void channel_from(::color::enum_channel echannel, ::image * pimage, const ::rectangle_i32 & rectangle);

   virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc);
   virtual void channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image * pimage);
   virtual void all_channels_copy(::color::enum_channel echannelSrc, ::image * pimage);

   virtual void Map(i32 ToRgb, i32 FromRgb);

   virtual void create_nanosvg(char * pszXml, double dDpi = 0.0);
   virtual void nanosvg(char * pszXml, double dDpi = 0.0);

   //virtual void _defer_load_multi_frame_image_(memory_pointer pmemory);

   virtual void op(string str);

   //virtual void from( ::image * piml);

   virtual void Blend(::image * piml, i32 A);
   virtual void Darken(::image * piml);
   virtual void Difference(::image * piml);
   virtual void Lighten(::image * piml);
   virtual void Multiply(::image * piml);
   virtual void Screen(::image * piml);

   virtual void lighten(double dRate);

   virtual void copy_from(::image * pimage, const ::point_i32 & point, enum_flag eflagCreate = e_flag_success);
   virtual void copy_from(::image * pimage, enum_flag eflagCreate = e_flag_success);
   //virtual void copy_to(::image * pimage, const ::point_i32 & point = nullptr);

   virtual void fill_rectangle(const ::rectangle_i32 & rectangle, ::color32_t color32);

   virtual void fill_rectangle(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B);


   virtual void fill_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B, i32 A);

   virtual void fill_stippled_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B);


   virtual void BlendRect(::image * piml, i32 x, i32 y, i32 A);
   virtual void DarkenRect(::image * piml, i32 x, i32 y);
   virtual void DifferenceRect(::image * piml, i32 x, i32 y);
   virtual void LightenRect(::image * piml, i32 x, i32 y);
   virtual void MultiplyRect(::image * piml, i32 x, i32 y);
   virtual void ScreenRect(::image * piml, i32 x, i32 y);

   virtual void horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A = 0, i32 x1 = 0, i32 x2 = -1);
   virtual void Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B);
   virtual void LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A);

   virtual void create_frame(const ::size_i32 & size, i32 iFrameCount);
   virtual void set_frame2(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual void set_frame1(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual void get_frame(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual void xor_image_frame2(void * pdata, i32 iFrame, i32 iFrameCount);


   virtual void create_circle(::image * piml, int diameter);
   virtual void create_framed_square(::image * piml, int inner, int outer, ::color32_t color32);


   virtual void invert_rgb(const ::rectangle_i32 & rectangle);
   virtual void invert_rgb();


   //virtual void     create_image(int cx, int cy, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);
   //virtual void     create_image(const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);



   virtual void transform(enum_image eimage);


   double pi() const;

   //static void static_initialize();

   inline ::i32 scan_area() { return scan_area_in_bytes() / sizeof(::color32_t); }
   inline ::i32 scan_area_in_bytes() { return m_iScan * m_size.cy; }



   ::stream & write(::stream & stream) const override;
   ::stream & read(::stream & stream) override;

   
   ::element * clone() const override;


   //inline int line(int line);

   
   //virtual ::draw2d::graphics * g() const; // { return get_graphics(); }
   inline ::draw2d::graphics * g(const ::size_f64 & sizeHint) { return g(); }
   inline ::size_f64 origin() const { return ::size_f64(); }
   
   //inline ::color::color pixel(int x, int y) const;

   
   //inline void is_set() const;


   //inline void is_null() const;


   //inline void is_empty() const;


   //inline ::color32_t * get_data();


   //inline const ::color32_t * get_data() const;


   //inline ::color32_t * colorref();


   //inline const ::color32_t* colorref() const;


   //inline operator ::color32_t* ();


   //inline operator const ::color32_t* () const;


   //inline ::pixmap * pixmap();


   //inline const ::pixmap * pixmap() const;


   //inline operator ::pixmap *();

   
   //inline operator const ::pixmap *() const;


   //::image_extension * extension();


   ::image_extension * get_extension();


   //inline const ::image_extension * extension() const;


   //inline operator ::image_extension * ();


   //inline operator const ::image_extension * () const;



   inline u64 area() const
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

      return m_size.cx;

   }


   inline int height() const
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


   inline ::color32_t * colorref()
   {

      return m_pcolorref1;

   }


   inline const ::color32_t * colorref() const
   {

      return m_pcolorref1;

   }


   inline operator ::color32_t * ()
   {

      return colorref();

   }


   inline operator const ::color32_t * () const
   {

      return colorref();

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


   inline ::image_extension * extension()
   {

      return m_pextension;

   }


   inline const ::image_extension * extension() const
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


   inline ::color32_t * get_data()
   {

      return m_pcolorref1;

   }


   const ::color32_t * get_data() const
   {

      map();

      return colorref();

   }


   //inline ::image & operator = (const ::image & image);
   //inline void operator == (const ::image & image) const;
   //inline void operator != (const ::image & image) const;


   virtual bool _draw_blend(const image_drawing & imagedrawing) override;
   virtual void _draw_raw(const image_drawing & imagedrawing) override;







   inline image& operator = (const image& image)
   {

      copy_from((::image*) & image);

      return *this;

   }


//inline image * image::frame(iptr i) const
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

      return m_pcolorrefRaw == image.m_pcolorrefRaw;

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


//inline ::size_i32 image::size() const
//{
//
//   return m_size;
//
//}


   inline ::rectangle_i32 rectangle(const ::point_i32& point = nullptr)
   {

      return ::rectangle_i32(point, get_size() - point);

   }


   inline ::rectangle_i32 rectangle(const ::point_i32& point = nullptr) const
   {

      return ::rectangle_i32(point, get_size() - point);

   }


   inline ::color::color pixel(int x, int y) const
   {

      if (::is_null(this) || x < 0 || y < 0 || x>= m_size.cx || y >= m_size.cy)
      {

         return 0;

      }

      return ::draw2d::get_pixel(colorref(), scan_size(), width(), x, y);

   }


   inline ::size_i32 get_size() const { return size(); }

   virtual image_pointer get_resized_image(const ::size_i32 & size);


};


////
////
//// Compose, Construct, Create and Add_Reference Porngraphs
////
//// __create      // return __pointer(BASE_TYPE) // _id atom // _new TYPE
//// __compose     // __composite(BASE_TYPE) &    // _id atom // _new TYPE // SOURCE psource
//// __construct   // __pointer(BASE_TYPE) &      // _id atom // _new TYPE // SOURCE psource
//// add_reference // __reference(BASE_TYPE) & SOURCE psource
////
//// >>
////
////
//
//
//inline ::image_pointer __create_image()
//{
//
//   return ::__create<::image>();
//
//}
//
//// template < typename COMPOSER >
//// void __compose(COMPOSER && pcomposer, __ & pimage);
// //
// template < typename COMPOSER >
// inline void __compose(COMPOSER && pcomposer, __composite(::image) & pimage, ::image * pimageSource);
// //
// //
// template < typename COMPOSER >
// inline void __compose(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size_i32 & size, ::enum_flag eflagCreate = OK, int iGoodStride = -1, void bPreserve = false);
// //
// //
// template < typename COMPOSER >
// inline void __preserve(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size_i32 & size, ::enum_flag eflagCreate = OK, int iGoodStride = -1);
// //
//
//void __construct(::image_pointer & pimage);

inline void __construct(::image_pointer & pimage, ::image * pimageSource);
//
//
inline void __construct(::image_pointer & pimage, const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
//
//
inline void __preserve(::image_pointer & pimage, const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1);
//
//
//
template < >
inline bool is_ok(const ::image * pimage)
{

   if (::is_null(pimage))
   {

      return false;

   }

   return pimage->is_ok();

}

template < typename TYPE >
inline  bool not_ok(const TYPE * p) { return is_null(p); }
inline bool not_ok(const ::image * pimage)
{

   return !is_ok(pimage);

}


#include "_image_impl.h"



