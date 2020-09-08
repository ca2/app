#pragma once



class CLASS_DECL_AURA image :
   virtual public ::image_meta,
   virtual public ::context_object
{
public:


   memory                              m_memoryMap;



   image();
   virtual ~image();


   virtual void defer_update_image();


   inline bool is_ok() const { return ::is_set(this) && (::pixmap::is_ok() && ::context_object::is_ok()); }


   virtual ::draw2d::graphics * get_graphics() const; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::graphics * _get_graphics() const; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::bitmap_pointer get_bitmap() const; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::bitmap_pointer detach_bitmap();


   
   virtual ::count get_image_count() const;
   virtual ::image_pointer get_image(index i);

   
   virtual bool set_mipmap(::draw2d::e_mipmap emipmap);
   virtual bool _set_mipmap(::draw2d::e_mipmap emipmap);

   
   virtual bool create_isotropic(::image * pimage);
   virtual bool create_isotropic(double_array & daRate, ::e_priority epriority);


   virtual bool SetViewportOrg(const ::point & point);
   virtual bool set_font_factor(double dFactor);
   virtual bool set_alpha_mode(::draw2d::e_alpha_mode e_alpha_mode);


   //virtual void delete_this();


   virtual bool create_helper_map();
   virtual bool _create_helper_map();


   virtual bool on_load_image();
   virtual bool on_exif_orientation();


   inline ::size get_size() const;
   //inline ::size size() const;

   
   inline ::rect rect(const ::point & point = nullptr);
   inline ::rect rect(const ::point & point = nullptr) const;


   inline ::u64 area() const;
   inline ::i32 width() const;
   inline ::i32 height() const;


   inline int scan_size() const;


   virtual bool rate_rgb(int iMul, int iDiv);
   virtual bool dc_select(bool bSelect = true);

   virtual COLORREF GetAverageColor();
   virtual COLORREF GetAverageOpaqueColor();
   virtual bool blend(::image * pimage, ::image * imageRate);
   virtual bool Blend(::image * pimage, ::image * imageA, i32 A);
   virtual bool Blend(::image * pimage, ::image * imageA);
   virtual bool blend(const ::point & pointDst, ::image * imageSrc, const ::point & pointSrc, ::image * imageAlf, const ::point & pointDstAlf, const ::size & size);
   virtual bool precision_blend(const ::point & pointDst, ::image * imageAlf, const ::point & pointAlf, const ::size & size);
   virtual bool precision_blend(const ::point & pointDst, ::image * imageAlf, const ::point & pointAlf, const ::size & size, byte bA);
   virtual bool blend(const ::point & pointDst, ::image * imageAlf, const ::point & pointAlf, const ::size & size);
   virtual bool blend(const ::point & pointDst, ::image * imageAlf, const ::point & pointAlf, const ::size & size, byte bA);
   virtual bool blend2(const ::point & pointDst, ::image * imageSrc, const ::point & pointSrc, const ::size & size, byte bA);
   virtual bool fork_blend(const ::point & pointDst, ::image * imageAlf, const ::point & pointAlf, const ::size & size);
   virtual bool fork_blend(const ::point & pointDst, ::image * imageAlf, const ::point & pointAlf, const ::size & size, byte bA);
   virtual bool bitmap_blend(::draw2d::graphics* pgraphics, const ::rect & rect);

   virtual bool color_blend(COLORREF cr, BYTE bAlpha);
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
   virtual bool flipx(::image * pimage);
   virtual bool flipy(::image * pimage);
   virtual ::image * flipx();
   virtual ::image * flipy();

   virtual bool is_rgb_black();
   virtual bool do_xor(::image * pimage);

   virtual bool ToAlpha(i32 i);
   virtual bool ToAlphaAndFill(i32 i, COLORREF cr);
   virtual bool GrayToARGB(COLORREF cr);

   virtual bool from_alpha();
   virtual bool mult_alpha(::image * imageWork, bool bPreserveAlpha = true);

   virtual bool mult_alpha();
   virtual bool mult_alpha_fast();
   virtual bool div_alpha();

   virtual bool mult_alpha(const ::point & point, const ::size & size);
   virtual bool div_alpha(const ::point & point, const ::size & size);

   virtual bool rotate(::image * pimage, const ::rect & rect, double dAngle, double dScale);

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


   virtual bool set_rgb(COLORREF cr);
   virtual bool set_rgb(i32 R, i32 G, i32 B);
   virtual bool tint(::image * pimage, const rgb & rgb);
   virtual bool set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A);
   virtual bool rgb_from(::image * pimage);
   virtual bool paint_rgb(color c);

   virtual ::i64 get_rgba_area(const rgba & rgba) const;
   virtual ::i64 get_rgba_area(const rgba& rgba, LPCRECT lpcrect) const;
   virtual ::i64 _001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const;
   virtual ::i64 _001GetTopLeftWeightedOpaqueArea(int iAlphaMin, LPCRECT lpcrect) const;


   virtual bool saturation(double dRate);
   virtual bool lightness(double dRate);
   virtual bool opacity(double dRate);


   virtual ::estatus SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy);
   virtual bool RadialFill(BYTE a, BYTE rect, BYTE g, BYTE b, i32 x, i32 y, i32 iRadius);
   virtual bool RadialFill(
   BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
   BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
   i32 x, i32 y, i32 iRadius);

   virtual bool gradient_fill(COLORREF clr1, COLORREF clr2, const point & point1, const point & point2);
   virtual bool gradient_horizontal_fill(COLORREF clr1, COLORREF clr2, int start, int end);
   virtual bool gradient_vertical_fill(COLORREF clr1, COLORREF clr2, int start, int end);
   virtual bool gradient_horizontal_fill(COLORREF clr1, COLORREF clr2);
   virtual bool gradient_vertical_fill(COLORREF clr1, COLORREF clr2);


   virtual u32 GetPixel(i32 x, i32 y);
   virtual u32 GetPixel(const ::point & point) { return GetPixel(point.x, point.y); }
   virtual bool Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
   virtual bool channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, color::e_channel echannel);
   virtual bool transparent_color(color color);


   virtual bool create_thumbnail(const char * pszPath);


   //using ::context_object::create;
   virtual ::estatus create(::draw2d::graphics* pgraphics);
   virtual ::estatus create(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false);
   inline ::estatus preserve(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)
   {

      return create(size, eobjectCreate, iGoodStride, true);

   }
   //virtual ::estatus     create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false);


   virtual bool host(const ::pixmap * ppixmap);
   virtual bool on_host_read_pixels(const ::pixmap * ppixmap);
   virtual bool destroy();
   //virtual bool detach(::image * pimage);

   // realization is semantically const
   // image keeps an image and image will be the same,
   // besides the way the Device Context associated with the image (m_spgraphics)
   // interprets or deals with it, may change
   virtual bool realize(::draw2d::graphics* pgraphics) const;
   virtual bool unrealize() const;
   virtual bool is_realized() const;
   virtual bool defer_realize(::draw2d::graphics* pgraphics) const;

   virtual bool DivideRGB(i32 iDivide);
   virtual bool DivideARGB(i32 iDivide);
   virtual bool DivideA(i32 iDivide);


   virtual bool stretch_image(::image * pimpl);


   virtual bool to(::image * piml) const;
   virtual bool from(const ::image * pimage);
   virtual bool from(::draw2d::graphics* pgraphics);
   virtual bool from(::draw2d::graphics* pgraphics, const ::size & size);
   virtual bool from(const ::point & pointDst, ::draw2d::graphics* pgraphics, const ::point & pointSrc, const ::size & size);
   virtual bool from(const ::point & pointDst, ::image * piml, const ::point & pointSrc, const ::size & size);
   virtual bool from(const ::point & pointDst, ::image * piml, const ::point & pointSrc, const ::size & size, byte bA);
   //virtual bool blend(const ::point & pointDst, ::image * piml, const ::point & pointSrc, const ::size & size);
   virtual bool from_ignore_alpha(const ::point & pointDst, ::image * piml, const ::point & pointSrc, const ::size & size);

   virtual bool to(::draw2d::graphics* pgraphics);
   virtual bool to(::draw2d::graphics* pgraphics, const ::point & point);
   virtual bool to(::draw2d::graphics* pgraphics, const ::size & size);
   virtual bool to(::draw2d::graphics* pgraphics, const ::point & point, const ::size & size);
   virtual bool to(::draw2d::graphics* pgraphics, const ::rect & rect);

   virtual bool to(::draw2d::graphics* pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc);


   virtual bool pixelate(i32 iSize);



   virtual bool fill_channel(i32 C, color::e_channel echannel);
   virtual bool white_fill_channel(i32 C, color::e_channel echannel);
   virtual bool fill_byte(uchar uch);
   virtual bool fill(COLORREF level);
   virtual bool fill(i32 A, i32 R, i32 G, i32 B);
   //      virtual bool Fill(i32 R, i32 G, i32 B);
   //virtual bool set_rgb(i32 R, i32 G, i32 B);
   virtual bool fill_glass(i32 R, i32 G, i32 B, i32 A);
   virtual bool fill_stippled_glass(i32 R, i32 G, i32 B);
   virtual bool invert();
   virtual bool channel_invert(color::e_channel echannel);
   virtual bool channel_multiply(double dRate, color::e_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false);
   virtual bool channel_multiply(color::e_channel echannel, ::image * pimage, bool bIfAlphaIgnorePreDivPosMult = false);
   virtual bool channel_lighten(color::e_channel echannel, ::image * pimage);
   virtual bool channel_darken(color::e_channel echannel, ::image * pimage);
   virtual bool channel_from(color::e_channel echannel, ::image * pimage);
   virtual bool channel_multiply(color::e_channel echannel, ::image * pimage, const ::rect & rect, bool bIfAlphaIgnorePreDivPosMult = false);

   virtual bool channel_from(color::e_channel echannel, ::image * pimage, const ::rect & rect);

   virtual bool channel_copy(color::e_channel echannelDst, color::e_channel echannelSrc);
   virtual bool channel_copy(color::e_channel echannelDst, color::e_channel echannelSrc, ::image * pimage);

   virtual bool Map(i32 ToRgb, i32 FromRgb);

   virtual bool create_nanosvg(char * pszXml, double dDpi = 0.0);
   virtual bool nanosvg(char * pszXml, double dDpi = 0.0);

   virtual bool _defer_load_multi_frame_image_(memory_pointer pmemory);

   virtual bool op(string str);

   //virtual bool from( ::image * piml);

   virtual bool Blend(::image * piml, i32 A);
   virtual bool Darken(::image * piml);
   virtual bool Difference(::image * piml);
   virtual bool Lighten(::image * piml);
   virtual bool Multiply(::image * piml);
   virtual bool Screen(::image * piml);

   virtual bool lighten(double dRate);

   virtual bool copy_from(::image * pimage, i32 x = 0, i32 y = 0);
   virtual bool copy_to(::image * pimage, i32 x = 0, i32 y = 0);

   virtual bool fill_rect(const ::rect & rect, COLORREF cr);

   virtual bool fill_rect(const ::rect & rect, i32 R, i32 G, i32 B);


   virtual bool fill_glass_rect(const ::rect & rect, i32 R, i32 G, i32 B, i32 A);

   virtual bool fill_stippled_glass_rect(const ::rect & rect, i32 R, i32 G, i32 B);


   virtual bool BlendRect(::image * piml, i32 x, i32 y, i32 A);
   virtual bool DarkenRect(::image * piml, i32 x, i32 y);
   virtual bool DifferenceRect(::image * piml, i32 x, i32 y);
   virtual bool LightenRect(::image * piml, i32 x, i32 y);
   virtual bool MultiplyRect(::image * piml, i32 x, i32 y);
   virtual bool ScreenRect(::image * piml, i32 x, i32 y);

   virtual bool horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A = 0, i32 x1 = 0, i32 x2 = -1);
   virtual bool Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B);
   virtual bool LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A);

   virtual bool create_frame(const ::size & size, i32 iFrameCount);
   virtual bool set_frame2(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual bool set_frame1(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual bool get_frame(void * pdata, i32 iFrame, i32 iFrameCount);

   virtual bool xor_image_frame2(void * pdata, i32 iFrame, i32 iFrameCount);


   virtual bool create_circle(::image * piml, int diameter);
   virtual bool create_framed_square(::image * piml, int inner, int outer, COLORREF cr);


   virtual bool invert_rgb(const ::rect & rect);
   virtual bool invert_rgb();


   //virtual ::estatus     create_image(int cx, int cy, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);
   //virtual ::estatus     create_image(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);



   virtual ::estatus transform(e_image eimage);


   double pi() const;

   //static void static_initialize();

   inline LONG scan_area() { return scan_area_in_bytes() / sizeof(COLORREF); }
   inline LONG scan_area_in_bytes() { return m_iScan * m_size.cy; }



   virtual ::stream & write(::stream & stream) const;
   virtual ::stream & read(::stream & stream);

   
   virtual ::generic_object * clone() const;


   inline int line(int line);

   
   virtual ::draw2d::graphics * g() const; // { return get_graphics(); }

   
   inline COLORREF pixel(int x, int y) const;

   
   inline bool is_set() const;


   inline bool is_null() const;


   inline bool is_empty() const;


   inline COLORREF * get_data();


   inline const COLORREF * get_data() const;


   inline COLORREF * colorref();


   inline const COLORREF * colorref() const;


   inline operator COLORREF * ();


   inline operator const COLORREF * () const;


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
//inline ::image_result __create_image()
//{
//
//   return ::__create<::image>();
//
//}
//
//// template < typename COMPOSER >
//// ::estatus __compose(COMPOSER && pcomposer, __ & pimage);
// //
// template < typename COMPOSER >
// inline ::estatus __compose(COMPOSER && pcomposer, __composite(::image) & pimage, ::image * pimageSource);
// //
// //
// template < typename COMPOSER >
// inline ::estatus __compose(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);
// //
// //
// template < typename COMPOSER >
// inline ::estatus __preserve(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1);
// //
//
//::estatus __construct(::image_pointer & pimage);

inline ::estatus __construct(::image_pointer & pimage, ::image * pimageSource);
//
//
inline ::estatus __construct(::image_pointer & pimage, const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);
//
//
inline ::estatus __preserve(::image_pointer & pimage, const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1);
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
