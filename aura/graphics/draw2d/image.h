#pragma once


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


   };




   memory                              m_memoryMap;
   ::rectangle_i32                     m_rectangleTag;


   image();
   ~image() override;


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

   
   virtual bool set_mipmap(::draw2d::e_mipmap emipmap);
   virtual bool _set_mipmap(::draw2d::e_mipmap emipmap);

   
   virtual bool create_isotropic(::image * pimage);
   virtual bool create_isotropic(double_array & daRate, ::enum_priority epriority);


   virtual bool SetViewportOrg(const ::point_i32 & point);
   virtual bool set_font_factor(double dFactor);
   virtual bool set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode);


   virtual bool create_helper_map();
   virtual bool _create_helper_map();


   virtual bool on_load_image();
   virtual bool on_exif_orientation();
   virtual void fast_copy(::color32_t * pcolor32FullImage);

   inline ::size_i32 get_size() const;

   ::size_i32 get_image_drawer_size() const override;


   ::image_pointer image_source_image(const concrete < ::size_i32 > &) override;


   // inline concrete < ::size_i32 > size_i32(const ::size_f64 &, const ::size_f64 &, enum_image_selection) const { return get_size(); }
   concrete < ::size_i32 > image_source_size(const ::size_f64 &, enum_image_selection) const override;
   concrete < ::size_i32 > image_source_size() const override;
   using image_meta::size;
   
   inline ::rectangle_i32 rectangle(const ::point_i32 & point = nullptr);
   inline ::rectangle_i32 rectangle(const ::point_i32 & point = nullptr) const;


   inline ::u64 area() const;
   inline ::i32 width() const;
   inline ::i32 height() const;


   inline int scan_size() const;


   virtual bool rate_rgb(int iMul, int iDiv);
   virtual bool dc_select(bool bSelect = true);

   virtual ::color::color GetAverageColor();
   virtual ::color::color GetAverageOpaqueColor();
   virtual bool blend(::image * pimage, ::image * imageRate);
   virtual bool Blend(::image * pimage, ::image * imageA, i32 A);
   virtual bool Blend(::image * pimage, ::image * imageA);
   virtual bool blend(const ::point_i32 & pointDst, ::image * imageSrc, const ::point_i32 & pointSrc, ::image * imageAlf, const ::point_i32 & pointDstAlf, const ::size_i32 & size);
   virtual bool precision_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size);
   virtual bool precision_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA);
   virtual bool blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size);
   virtual bool blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA);
   virtual bool blend2(const ::point_i32 & pointDst, ::image * imageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size, byte bA);
   virtual bool fork_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size);
   virtual bool fork_blend(const ::point_i32 & pointDst, ::image * imageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA);
   //virtual bool bitmap_blend(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle);

   virtual bool color_blend(::color32_t color32, byte bAlpha);
   virtual bool BitBlt(::image * pimage, i32 op);
   virtual bool BitBlt(int cxParam, int cyParam, ::image * pimage, i32 op);
   virtual i32 cos(i32 i, i32 iAngle);
   virtual i32 sin(i32 i, i32 iAngle);
   virtual i32 cos10(i32 i, i32 iAngle);
   virtual i32 sin10(i32 i, i32 iAngle);

   virtual bool hue_offset(double dRate);

   virtual bool map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map to m_pcolorref before manipulate it
   virtual bool unmap() const; // some implementations may require to unmap from m_pcolorref to update *os* bitmap


   virtual bool _map(bool bApplyAlphaTransform = true);
   virtual bool _unmap();

   virtual bool set_mapped();

   virtual bool flip_vertical(::image * pimage);
   virtual bool flip_horizontal(::image * pimage);
   virtual bool flip_horizontal();
   virtual bool flip_vertical();
   virtual bool flipx(::image * pimage);
   virtual bool flipy(::image * pimage);
   virtual ::image * flipx();
   virtual ::image * flipy();

   virtual bool is_rgb_black();
   virtual bool do_xor(::image * pimage);

   virtual bool ToAlpha(i32 i);
   virtual bool ToAlphaAndFill(i32 i, ::color32_t color32);
   virtual bool GrayToARGB(::color32_t color32);

   virtual bool from_alpha();
   virtual bool mult_alpha(::image * imageWork, bool bPreserveAlpha = true);

   virtual bool mult_alpha();
   virtual bool mult_alpha_fast();
   virtual bool div_alpha();

   virtual bool mult_alpha(const ::point_i32 & point, const ::size_i32 & size);
   virtual bool div_alpha(const ::point_i32 & point, const ::size_i32 & size);

   virtual bool rotate(::image * pimage, const ::rectangle_i32 & rectangle, double dAngle, double dScale);

   virtual bool rotate(::image * pimage, double dAngle, double dScale);
   virtual bool rotate(::image * pimage, double dAngle);
   virtual bool Rotate034(::image * pimage, double dAngle, double dScale);

   virtual bool rotate90(::image * pimage);
   virtual bool rotate180(::image * pimage);
   virtual bool rotate270(::image * piml);
   virtual bool rotate90();
   virtual bool rotate180();
   virtual bool rotate270();
   virtual bool rotate90flipx(::image * piml);
   virtual bool rotate180flipx(::image * piml);
   virtual bool rotate270flipx(::image * piml);
   virtual bool rotate90flipx();
   virtual bool rotate180flipx();
   virtual bool rotate270flipx();


   virtual bool set_rgb(::color32_t color32);
   virtual bool set_rgb(i32 R, i32 G, i32 B);
   virtual bool tint(::image * pimage, const ::color::color & color);
   virtual bool set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A);
   virtual bool rgb_from(::image * pimage);
   virtual bool paint_rgb(const ::color::color & color);

   virtual ::i64 get_rgba_area(const ::color::color & color) const;
   virtual ::i64 get_rgba_area(const ::color::color & color, const RECTANGLE_I32 * lpcrect) const;
   virtual ::i64 _001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const;
   virtual ::i64 _001GetTopLeftWeightedOpaqueArea(int iAlphaMin, const RECTANGLE_I32 * lpcrect) const;


   virtual bool saturation(double dRate);
   virtual bool lightness(double dRate);
   virtual bool opacity(double dRate);


   virtual ::e_status SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy);
   virtual bool RadialFill(byte a, byte rectangle, byte g, byte b, i32 x, i32 y, i32 iRadius);
   virtual bool RadialFill(
   byte a1, byte r1, byte g1, byte b1, // center colors
   byte a2, byte r2, byte g2, byte b2, // border colors
   i32 x, i32 y, i32 iRadius);


   virtual bool gradient_fill(::color32_t clr1, ::color32_t clr2, const point_i32 & point1, const point_i32 & point2);
   virtual bool gradient_horizontal_fill(::color32_t clr1, ::color32_t clr2, int start, int end);
   virtual bool gradient_vertical_fill(::color32_t clr1, ::color32_t clr2, int start, int end);
   virtual bool gradient_horizontal_fill(::color32_t clr1, ::color32_t clr2);
   virtual bool gradient_vertical_fill(::color32_t clr1, ::color32_t clr2);


   virtual u32 GetPixel(i32 x, i32 y);
   virtual u32 GetPixel(const ::point_i32 & point) { return GetPixel(point.x, point.y); }
   virtual bool Mask(::color32_t crMask, ::color32_t crInMask, ::color32_t crOutMask);
   virtual bool channel_mask(byte uchFind, byte uchSet, byte uchUnset, ::color::enum_channel echannel);
   virtual bool transparent_color(const ::color::color & color);


   virtual bool create_thumbnail(const ::string & pszPath);

   virtual ::e_status create_ex(const ::size_i32 & size, ::color32_t * pcolorref, int iScan, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false);
   virtual ::e_status create(::draw2d::graphics* pgraphics);
   virtual ::e_status create(const ::size_i32 & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false);
   using ::object::initialize;
   virtual ::e_status initialize(const ::size_i32 & size, ::color32_t * pcolorref, int iScan, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG);
   inline ::e_status preserve(const ::size_i32 & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)
   {

      return create(size, eobjectCreate, iGoodStride, true);

   }
   //virtual ::e_status     create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false);


   virtual bool host(const ::pixmap * ppixmap);
   virtual bool on_host_read_pixels(const ::pixmap * ppixmap);
   ::e_status destroy() override;
   //virtual bool detach(::image * pimage);

   // realization is semantically const
   // image keeps an image and image will be the same,
   // besides the way the Device Context associated with the image (m_spgraphics)
   // interprets or deals with it, may machine
   virtual bool realize(::draw2d::graphics* pgraphics) const;
   virtual bool unrealize() const;
   virtual bool is_realized() const;
   virtual bool defer_realize(::draw2d::graphics* pgraphics) const;

   virtual bool DivideRGB(i32 iDivide);
   virtual bool DivideARGB(i32 iDivide);
   virtual bool DivideA(i32 iDivide);

   
   //using image_drawer::stretch;
   virtual bool stretch_image(::image * pimage);


   //virtual bool stretch(::draw2d::graphics * pgraphics);
   //virtual bool to(::image * piml) const;
   //virtual bool copy(const ::image * pimage, eobject eobjectCreate = e_object_success);
   //virtual bool stretch(const ::image * pimage);
   //virtual bool draw_image(::draw2d::graphics* pgraphics);
   //virtual bool draw_image(::draw2d::graphics* pgraphics, const ::size_i32 & size);
   //virtual bool from(const ::point_i32 & pointDst, ::draw2d::graphics* pgraphics, const ::point_i32 & pointSrc, const ::size_i32 & size);
   //using image_drawer::draw;
   virtual bool _draw_raw(const ::rectangle_i32 & rectangleTarget, ::image * pimage, const ::point_i32 & pointSrc = ::point_i32());
   virtual bool blend(const ::rectangle_i32 & rectangleTarget, ::image * pimage, const ::point_i32 & pointSrc, byte bA);
   //virtual bool blend(const ::point_i32 & pointDst, ::image * piml, const ::point_i32 & pointSrc, const ::size_i32 & size);
   virtual bool draw_ignore_alpha(const ::point_i32 & pointDst, ::image * pimage, const ::rectangle_i32 & rectangleSource);

   //virtual bool to(::draw2d::graphics* pgraphics);
   //virtual bool to(::draw2d::graphics* pgraphics, const ::point_i32 & point);
   //virtual bool to(::draw2d::graphics* pgraphics, const ::size_i32 & size);
   //virtual bool to(::draw2d::graphics* pgraphics, const ::point_i32 & point, const ::size_i32 & size);
   //virtual bool to(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle);

   //virtual bool to(::draw2d::graphics* pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc);


   virtual bool pixelate(i32 iSize);



   virtual bool fill_channel(i32 C, ::color::enum_channel echannel);
   virtual bool white_fill_channel(i32 C, ::color::enum_channel echannel);
   virtual bool fill_byte(uchar uch);
   virtual bool fill(::color32_t level);
   virtual bool fill(i32 A, i32 R, i32 G, i32 B);
   //      virtual bool Fill(i32 R, i32 G, i32 B);
   //virtual bool set_rgb(i32 R, i32 G, i32 B);
   virtual bool fill_glass(i32 R, i32 G, i32 B, i32 A);
   virtual bool fill_stippled_glass(i32 R, i32 G, i32 B);
   virtual bool invert();
   virtual bool channel_invert(::color::enum_channel echannel);
   virtual bool channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false);
   virtual bool channel_multiply(::color::enum_channel echannel, ::image * pimage, bool bIfAlphaIgnorePreDivPosMult = false);
   virtual bool channel_lighten(::color::enum_channel echannel, ::image * pimage);
   virtual bool channel_darken(::color::enum_channel echannel, ::image * pimage);
   virtual bool channel_from(::color::enum_channel echannel, ::image * pimage);
   virtual bool channel_multiply(::color::enum_channel echannel, ::image * pimage, const ::rectangle_i32 & rectangle, bool bIfAlphaIgnorePreDivPosMult = false);

   virtual bool channel_from(::color::enum_channel echannel, ::image * pimage, const ::rectangle_i32 & rectangle);

   virtual bool channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc);
   virtual bool channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image * pimage);

   virtual bool Map(i32 ToRgb, i32 FromRgb);

   virtual bool create_nanosvg(char * pszXml, double dDpi = 0.0);
   virtual bool nanosvg(char * pszXml, double dDpi = 0.0);

   //virtual bool _defer_load_multi_frame_image_(memory_pointer pmemory);

   virtual bool op(string str);

   //virtual bool from( ::image * piml);

   virtual bool Blend(::image * piml, i32 A);
   virtual bool Darken(::image * piml);
   virtual bool Difference(::image * piml);
   virtual bool Lighten(::image * piml);
   virtual bool Multiply(::image * piml);
   virtual bool Screen(::image * piml);

   virtual bool lighten(double dRate);

   virtual bool copy_from(::image * pimage, const ::point_i32 & point, eobject eobjectCreate = e_object_success);
   virtual bool copy_from(::image * pimage, eobject eobjectCreate = e_object_success);
   //virtual bool copy_to(::image * pimage, const ::point_i32 & point = nullptr);

   virtual bool fill_rectangle(const ::rectangle_i32 & rectangle, ::color32_t color32);

   virtual bool fill_rectangle(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B);


   virtual bool fill_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B, i32 A);

   virtual bool fill_stippled_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B);


   virtual bool BlendRect(::image * piml, i32 x, i32 y, i32 A);
   virtual bool DarkenRect(::image * piml, i32 x, i32 y);
   virtual bool DifferenceRect(::image * piml, i32 x, i32 y);
   virtual bool LightenRect(::image * piml, i32 x, i32 y);
   virtual bool MultiplyRect(::image * piml, i32 x, i32 y);
   virtual bool ScreenRect(::image * piml, i32 x, i32 y);

   virtual bool horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A = 0, i32 x1 = 0, i32 x2 = -1);
   virtual bool Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B);
   virtual bool LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A);

   virtual bool create_frame(const ::size_i32 & size, i32 iFrameCount);
   virtual bool set_frame2(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual bool set_frame1(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual bool get_frame(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual bool xor_image_frame2(void * pdata, i32 iFrame, i32 iFrameCount);


   virtual bool create_circle(::image * piml, int diameter);
   virtual bool create_framed_square(::image * piml, int inner, int outer, ::color32_t color32);


   virtual bool invert_rgb(const ::rectangle_i32 & rectangle);
   virtual bool invert_rgb();


   //virtual ::e_status     create_image(int cx, int cy, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);
   //virtual ::e_status     create_image(const ::size_i32 & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);



   virtual ::e_status transform(enum_image eimage);


   double pi() const;

   //static void static_initialize();

   inline ::i32 scan_area() { return scan_area_in_bytes() / sizeof(::color32_t); }
   inline ::i32 scan_area_in_bytes() { return m_iScan * m_size.cy; }



   ::stream & write(::stream & stream) const override;
   ::stream & read(::stream & stream) override;

   
   ::matter * clone() const override;


   inline int line(int line);

   
   virtual ::draw2d::graphics * g() const; // { return get_graphics(); }
   inline ::draw2d::graphics * g(const ::size_f64 & sizeHint) { return g(); }
   inline ::size_f64 origin() const { return ::size_f64(); }
   
   inline ::color::color pixel(int x, int y) const;

   
   inline bool is_set() const;


   inline bool is_null() const;


   inline bool is_empty() const;


   inline ::color32_t * get_data();


   inline const ::color32_t * get_data() const;


   inline ::color32_t * colorref();


   inline const ::color32_t* colorref() const;


   inline operator ::color32_t* ();


   inline operator const ::color32_t* () const;


   inline ::pixmap * pixmap();


   inline const ::pixmap * pixmap() const;


   inline operator ::pixmap *();

   
   inline operator const ::pixmap *() const;


   inline ::image_extension * extension();


   ::image_extension * get_extension();


   inline const ::image_extension * extension() const;


   inline operator ::image_extension * ();


   inline operator const ::image_extension * () const;


   inline ::image & operator = (const ::image & image);
   inline bool operator == (const ::image & image) const;
   inline bool operator != (const ::image & image) const;


   virtual bool _draw_blend(const image_drawing & imagedrawing) override;
   virtual bool _draw_raw(const image_drawing & imagedrawing) override;


};


////
////
//// Compose, Construct, Create and Add_Reference Porngraphs
////
//// __create      // return __pointer(BASE_TYPE) // _id id // _new TYPE
//// __compose     // __composite(BASE_TYPE) &    // _id id // _new TYPE // SOURCE psource
//// __construct   // __pointer(BASE_TYPE) &      // _id id // _new TYPE // SOURCE psource
//// add_reference // __reference(BASE_TYPE) & SOURCE psource
////
//// >>
////
////
//
//
//inline ::image_transport __create_image()
//{
//
//   return ::__create<::image>();
//
//}
//
//// template < typename COMPOSER >
//// ::e_status __compose(COMPOSER && pcomposer, __ & pimage);
// //
// template < typename COMPOSER >
// inline ::e_status __compose(COMPOSER && pcomposer, __composite(::image) & pimage, ::image * pimageSource);
// //
// //
// template < typename COMPOSER >
// inline ::e_status __compose(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);
// //
// //
// template < typename COMPOSER >
// inline ::e_status __preserve(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1);
// //
//
//::e_status __construct(::image_pointer & pimage);

inline ::e_status __construct(::image_pointer & pimage, ::image * pimageSource);
//
//
inline ::e_status __construct(::image_pointer & pimage, const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);
//
//
inline ::e_status __preserve(::image_pointer & pimage, const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1);
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
