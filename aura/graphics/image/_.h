// Created by camilo on 2022-03-11 08:24 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "_constant.h"


//#include "acme/primitive/geometry2d/point.h"
//#include "acme/primitive/geometry2d/size.h"
//#include "acme/primitive/geometry2d/rectangle.h"


namespace image
{


   class imaging;
   class image_drawing;
   class image_drawing_options;
   class image_frame;
   class image_frame_array;


   class size_image;

   class image_map;


   class fastblur;


   class image_list;


   using image_list_pointer = ::pointer<::image::image_list>;


   using icon_pointer = ::pointer<icon>;


} // namespace image





//class CLASS_DECL_AURA image_base :
//   virtual public object
//{
//public:
//
//
//   static float Cosines[360];
//   static float Sines[360];
//   static i64 CosN[360]; // * 1 << 31
//   static i64 SinN[360];
//   static i64 Cos10N[10]; // until 10 degress
//   static i64 Sin10N[10]; // more precision * 1 << 34
//   static double dPi;
//
//
//
//   //virtual bool dispose_current_frame()= 0;
//   //virtual bool overlay_frame(int iFrame)= 0;
//   virtual void defer_update()= 0;
//
//
//
//   //virtual bool load_image(::payload payloadFile, bool bCache = true, bool bCreateHelperMaps = false)= 0;
//   //virtual bool load_image(const ::string & pszMatter, bool bCache = true, bool bCreateHelperMaps = false)= 0;
//   ////virtual bool read_from_file(file_pointer  pfile)= 0;
//
//
//   //virtual bool load_matter_icon(string_array & straMatter, string strIcon)= 0;
//
//
//   //virtual bool load_thumbnail(::payload payloadFile, int w, int h)= 0;
//
//
//   //virtual bool save_image(::payload payloadFile, ::save_image * psaveimage = nullptr) = 0;
//   //virtual bool save_dib(::payload payloadFile) = 0;
//
//   virtual image get_image(::payload payloadFile, bool bSync = false) = 0;
//   virtual image matter_image(string strMatter, bool bSync = false) = 0;
//   virtual image load_image(::payload payloadFile, bool bCreateHelperMaps = false) = 0;
//   virtual image load_matter_image(const ::string & pszMatter, bool bCache = true, bool bCreateHelperMaps = false) = 0;
//   virtual image load_matter_icon(string_array & straMatter, string strIcon) = 0;
//   virtual image load_thumbnail(::payload payloadFile, int w, int h) = 0;
//   virtual image load_thumbnail(const ::string & pszPath) = 0;
//   virtual image load_dib(const ::file::path & pathDib) = 0;
//
//
//   virtual bool save_image(::payload payloadFile, ::save_image * psaveimage = nullptr) = 0;
//   virtual bool save_dib(const ::file::path & pathDib) = 0;
//
//
//   virtual ::draw2d::graphics * get_graphics() const= 0; // is semantically const (besides may not be implementationly constant)
//   virtual ::draw2d::bitmap_pointer get_bitmap() const= 0; // is semantically const (besides may not be implementationly constant)
//   virtual ::draw2d::bitmap_pointer detach_bitmap()= 0;
//
//   virtual ::collection::count get_image_count() const= 0;
//   virtual ::image::image_pointer get_image(::collection::index i)= 0;
//
//   virtual ::color::color * get_data() const= 0;
//
//   virtual bool set_mipmap(::draw2d::enum_mipmap emipmap)= 0;
//   virtual bool _set_mipmap(::draw2d::enum_mipmap emipmap)= 0;
//
//   virtual bool create_isotropic(::image::image *pimage)= 0;
//   virtual bool create_isotropic(f64_array & daRate, ::enum_priority epriority)= 0;
//
//   virtual bool set_origin(const ::point_i32 & point)= 0;
//   virtual bool set_font_factor(double dFactor)= 0;
//   virtual bool set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode)= 0;
//
//   virtual bool create_helper_map()= 0;
//
//   virtual bool on_load_image()= 0;
//   virtual bool on_exif_orientation()= 0;
//
//   virtual ::size_i32 get_size() const= 0;
//
//
//
//   virtual bool rate_rgb(int iMul, int iDiv)= 0;
//   virtual bool dc_select(bool bSelect = true)= 0;
//
//   virtual ::color::color GetAverageColor()= 0;
//   virtual ::color::color GetAverageOpaqueColor()= 0;
//   virtual bool blend(::image::image *pimage, ::image::image *pimageRate)= 0;
//   virtual bool Blend(::image::image *pimage, ::image::image *pimageA, i32 A)= 0;
//   virtual bool Blend(::image::image *pimage, ::image::image *pimageA)= 0;
//   virtual bool blend(const ::point_i32 & pointDst, ::image::image *pimageSrc, const ::point_i32 & pointSrc, ::image::image *pimageAlf, const ::point_i32 & pointDstAlf, const ::size_i32 & size)= 0;
//   virtual bool precision_blend(const ::point_i32 & pointDst, ::image::image *pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size)= 0;
//   virtual bool precision_blend(const ::point_i32 & pointDst, ::image::image *pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, ::u8 bA)= 0;
//   virtual bool blend(const ::point_i32 & pointDst, ::image::image *pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size)= 0;
//   virtual bool blend(const ::point_i32 & pointDst, ::image::image *pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, ::u8 bA)= 0;
//   virtual bool blend2(const ::point_i32 & pointDst, ::image::image *pimageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size, ::u8 bA)= 0;
//   virtual bool fork_blend(const ::point_i32 & pointDst, ::image::image *pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size)= 0;
//   virtual bool fork_blend(const ::point_i32 & pointDst, ::image::image *pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, ::u8 bA)= 0;
//   virtual bool bitmap_blend(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)= 0;
//
//   virtual bool color_blend(::color32_t color32, ::u8 bAlpha)= 0;
//   virtual bool BitBlt(::image::image *pimage, i32 op)= 0;
//   virtual bool BitBlt(int cxParam, int cyParam, ::image::image *pimage, i32 op)= 0;
//   virtual i32 cos(i32 i, i32 iAngle)= 0;
//   virtual i32 sin(i32 i, i32 iAngle)= 0;
//   virtual i32 cos10(i32 i, i32 iAngle)= 0;
//   virtual i32 sin10(i32 i, i32 iAngle)= 0;
//
//   virtual bool hue_offset(double dRate)= 0;
//
//   virtual bool map(bool bApplyAlphaTransform = true) const= 0; // some implementations may requrire to map to m_pcolorref before manipulate it
//   virtual bool unmap() const= 0; // some implementations may require to unmap from m_pcolorref to update *os* bitmap
//   virtual bool set_mapped()= 0;
//
//   virtual bool flip_vertical(::image::image *pimage)= 0;
//   virtual bool flip_horizontal(::image::image *pimage)= 0;
//   virtual bool flipx(::image::image *pimage)= 0;
//   virtual bool flipy(::image::image *pimage)= 0;
//   virtual ::image::image_pointer flipx()= 0;
//   virtual ::image::image_pointer flipy()= 0;
//
//   virtual bool is_rgb_black()= 0;
//   virtual bool do_xor(::image::image *pimage)= 0;
//
//   virtual bool ToAlpha(i32 i)= 0;
//   virtual bool ToAlphaAndFill(i32 i, ::color32_t color32)= 0;
//   virtual bool GrayToARGB(::color32_t color32)= 0;
//
//   virtual bool from_alpha()= 0;
//   virtual bool mult_alpha(::image::image *pimageWork, bool bPreserveAlpha = true)= 0;
//
//   virtual bool mult_alpha()= 0;
//   virtual bool mult_alpha_fast()= 0;
//   virtual bool div_alpha()= 0;
//
//   virtual bool mult_alpha(const ::point_i32 & point, const ::size_i32 & size)= 0;
//   virtual bool div_alpha(const ::point_i32 & point, const ::size_i32 & size)= 0;
//
//   virtual bool rotate(::image::image *pimage, const ::rectangle_i32 & rectangle, double dAngle, double dScale)= 0;
//
//   virtual bool rotate(::image::image *pimage, double dAngle, double dScale)= 0;
//   virtual bool rotate(::image::image *pimage, double dAngle)= 0;
//   virtual bool Rotate034(::image::image *pimage, double dAngle, double dScale)= 0;
//
//   virtual bool rotate90(::image::image *pimage)= 0;
//   virtual bool rotate180(::image::image *pimage)= 0;
//   virtual bool rotate270(::image::image *pimage)= 0;
//   virtual bool rotate90()= 0;
//   virtual bool rotate180()= 0;
//   virtual bool rotate270()= 0;
//   virtual bool rotate90flipx(::image::image *pimage)= 0;
//   virtual bool rotate180flipx(::image::image *pimage)= 0;
//   virtual bool rotate270flipx(::image::image *pimage)= 0;
//   virtual bool rotate90flipx()= 0;
//   virtual bool rotate180flipx()= 0;
//   virtual bool rotate270flipx()= 0;
//
//
//   virtual bool set_rgb(::color32_t color32)= 0;
//   virtual bool set_rgb(i32 R, i32 G, i32 B)= 0;
//   virtual bool tint(::image::image *pimage, const rgb & rgb)= 0;
//   virtual bool set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A)= 0;
//   virtual bool rgb_from(::image::image *pimage)= 0;
//   virtual bool paint_rgb(::color::color color)= 0;
//
//
//   virtual bool saturation(double dRate)= 0;
//   virtual bool lightness(double dRate) = 0;
//   virtual bool opacity(double dRate) = 0;
//
//
//   virtual bool SetIconMask(::image::icon * picon, i32 cx, i32 cy)= 0;
//   virtual bool RadialFill(::u8 a, ::u8 rectangle, ::u8 g, ::u8 b, i32 x, i32 y, i32 iRadius)= 0;
//   virtual bool RadialFill(
//   ::u8 a1, ::u8 r1, ::u8 g1, ::u8 b1, // center colors
//   ::u8 a2, ::u8 r2, ::u8 g2, ::u8 b2, // border colors
//   i32 x, i32 y, i32 iRadius)= 0;
//
//   virtual bool gradient_fill(::color::color clr1, ::color::color clr2, const point_i32 & point1, const point_i32 & point2)= 0;
//   virtual bool gradient_horizontal_fill(::color::color clr1, ::color::color clr2, int start, int end)= 0;
//   virtual bool gradient_vertical_fill(::color::color clr1, ::color::color clr2, int start, int end)= 0;
//   virtual bool gradient_horizontal_fill(::color::color clr1, ::color::color clr2)= 0;
//   virtual bool gradient_vertical_fill(::color::color clr1, ::color::color clr2)= 0;
//
//
//   virtual u32 GetPixel(i32 x, i32 y)= 0;
//   virtual bool Mask(::color::color crMask, ::color::color crInMask, ::color::color crOutMask)= 0;
//   virtual bool channel_mask(::u8 uchFind, ::u8 uchSet, ::u8 uchUnset, ::color::enum_channel echannel)= 0;
//   virtual bool transparent_color(::color::color color)= 0;
//
//   virtual bool create_thumbnail(const ::string & pszPath) = 0;
//
//   virtual bool create(const ::size_i32 & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)= 0;
//   virtual bool create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)= 0;
//   virtual bool host(const pixmap* ppixmap)= 0;
//   virtual bool on_host_read_pixels(const pixmap* ppixmap) = 0;
//   virtual bool create(::draw2d::graphics_pointer & pgraphics)= 0;
//   virtual bool destroy()= 0;
//   // virtual bool detach(::image::image *pimage) = 0;
//
//   // realization is semantically const
//   // image keeps an image and image will be the same,
//   // besides the way the Device Context associated with the image (m_spgraphics)
//   // interprets or deals with it, may machine
//   virtual bool realize(::draw2d::graphics_pointer & pgraphics) const= 0;
//   virtual bool unrealize() const= 0;
//   virtual bool is_realized() const= 0;
//   virtual bool defer_realize(::draw2d::graphics_pointer & pgraphics) const= 0;
//
//   virtual bool DivideRGB(i32 iDivide)= 0;
//   virtual bool DivideARGB(i32 iDivide)= 0;
//   virtual bool DivideA(i32 iDivide)= 0;
//
//
//   virtual bool stretch_image(::image::image *pimage) = 0;
//
//
//   virtual bool to(::image::image *pimage) const= 0;
//   virtual bool from(const ::image::image *pimage)= 0;
//   virtual bool from(::draw2d::graphics_pointer & pgraphics)= 0;
//   virtual bool from(const ::point_i32 & pointDst, ::draw2d::graphics_pointer & pgraphics, const ::point_i32 & pointSrc, const ::size_i32 & size)= 0;
//   virtual bool from(const ::point_i32 & pointDst, ::image::image *pimage, const ::point_i32 & pointSrc, const ::size_i32 & size)= 0;
//   virtual bool from(const ::point_i32 & pointDst, ::image::image *pimage, const ::point_i32 & pointSrc, const ::size_i32 & size, ::u8 bA)= 0;
//   //virtual bool blend(const ::point_i32 & pointDst, ::image::image *pimage, const ::point_i32 & pointSrc, const ::size_i32 & size)= 0;
//   virtual bool from_ignore_alpha(const ::point_i32 & pointDst, ::image::image *pimage, const ::point_i32 & pointSrc, const ::size_i32 & size)= 0;
//
//   virtual bool to(::draw2d::graphics_pointer & pgraphics)= 0;
//   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point)= 0;
//   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::size_i32 & size)= 0;
//   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point, const ::size_i32 & size)= 0;
//   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle)= 0;
//
//   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc)= 0;
//
//
//   virtual bool pixelate(i32 iSize)= 0;
//
//
//
//   virtual bool fill_channel(i32 C, ::color::enum_channel echannel)= 0;
//   virtual bool white_fill_channel(i32 C, ::color::enum_channel echannel)= 0;
//   virtual bool fill_byte(uchar uch)= 0;
//   virtual bool fill(::color::color level)= 0;
//   virtual bool fill(i32 A, i32 R, i32 G, i32 B)= 0;
//   //      virtual bool Fill(i32 R, i32 G, i32 B)= 0;
//   //virtual bool set(i32 R, i32 G, i32 B)= 0;
//   virtual bool fill_glass(i32 R, i32 G, i32 B, i32 A)= 0;
//   virtual bool fill_stippled_glass(i32 R, i32 G, i32 B)= 0;
//   virtual bool invert()= 0;
//   virtual bool channel_invert(::color::enum_channel echannel)= 0;
//   virtual bool channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false)= 0;
//   virtual bool channel_multiply(::color::enum_channel echannel, ::image::image *pimage, bool bIfAlphaIgnorePreDivPosMult = false)= 0;
//   virtual bool channel_lighten(::color::enum_channel echannel, ::image::image *pimage)= 0;
//   virtual bool channel_darken(::color::enum_channel echannel, ::image::image *pimage)= 0;
//   virtual bool channel_from(::color::enum_channel echannel, ::image::image *pimage)= 0;
//   virtual bool channel_multiply(::color::enum_channel echannel, ::image::image *pimage, const ::rectangle_i32 & rectangle, bool bIfAlphaIgnorePreDivPosMult = false)= 0;
//
//   virtual bool channel_from(::color::enum_channel echannel, ::image::image *pimage, const ::rectangle_i32 & rectangle)= 0;
//
//   virtual bool channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc)= 0;
//   virtual bool channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image::image *pimage)= 0;
//
//   virtual bool Map(i32 ToRgb, i32 FromRgb)= 0;
//
//   virtual bool create_nanosvg(char * pszXml, double dDpi = 0.0) = 0;
//   virtual bool nanosvg(char * pszXml, double dDpi = 0.0)= 0;
//
//   virtual bool op(string str)= 0;
//
//   //virtual bool from( ::image::image *pimage)= 0;
//
//   virtual bool Blend(::image::image *pimage, i32 A)= 0;
//   virtual bool Darken(::image::image *pimage)= 0;
//   virtual bool Difference(::image::image *pimage)= 0;
//   virtual bool Lighten(::image::image *pimage)= 0;
//   virtual bool Multiply(::image::image *pimage)= 0;
//   virtual bool Screen(::image::image *pimage)= 0;
//
//   virtual bool lighten(double dRate)= 0;
//
//   virtual bool copy(::image::image *pimage, i32 x, i32 y)= 0;
//   virtual bool PasteRect(::image::image *pimage, i32 x, i32 y)= 0;
//
//   virtual bool fill_rectangle(const ::rectangle_i32 & rectangle, ::color32_t color32)= 0;
//
//   virtual bool fill_rectangle(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B)= 0;
//
//
//   virtual bool fill_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B, i32 A)= 0;
//
//   virtual bool fill_stippled_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B)= 0;
//
//
//   virtual bool BlendRect(::image::image *pimage, i32 x, i32 y, i32 A)= 0;
//   virtual bool DarkenRect(::image::image *pimage, i32 x, i32 y)= 0;
//   virtual bool DifferenceRect(::image::image *pimage, i32 x, i32 y)= 0;
//   virtual bool LightenRect(::image::image *pimage, i32 x, i32 y)= 0;
//   virtual bool MultiplyRect(::image::image *pimage, i32 x, i32 y)= 0;
//   virtual bool ScreenRect(::image::image *pimage, i32 x, i32 y)= 0;
//
//   virtual bool horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A = 0, i32 x1 = 0, i32 x2 = -1)= 0;
//   virtual bool Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B)= 0;
//   virtual bool LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A)= 0;
//
//   virtual bool create_frame(const ::size_i32 & size, i32 iFrameCount)= 0;
//   virtual bool set_frame2(void * pdata, i32 iFrame, i32 iFrameCount)= 0;
//
//   virtual bool set_frame1(void * pdata, i32 iFrame, i32 iFrameCount)= 0;
//
//   virtual bool get_frame(void * pdata, i32 iFrame, i32 iFrameCount)= 0;
//
//   virtual bool xor_image_frame2(void * pdata, i32 iFrame, i32 iFrameCount)= 0;
//
//
//   virtual bool create_circle(::image::image *pimage, int diameter)= 0;
//   virtual bool create_framed_square(::image::image *pimage, int inner, int outer, ::color32_t color32)= 0;
//
//
//   virtual bool invert_rgb(const ::rectangle_i32 & rectangle)= 0;
//   virtual bool invert_rgb() = 0;
//
//
//
//   virtual ::i32 scan_area()= 0;
//
//
//
//   inline bool fill_rect_dim(i32 x, i32 y, i32 w, i32 h, ::color32_t color32) { return fill_rectangle(rectangle_i32_dimension(x, y, w, h), color32); }
//   inline bool fill_rect_dim(i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B) { return fill_rectangle(rectangle_i32_dimension(x, y, w, h), R, G, B); }
//   inline bool fill_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, ::color32_t color32) { return fill_rectangle(::rectangle_i32(x1, y1, x2, y2), color32); }
//   inline bool fill_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B) { return fill_rectangle(::rectangle_i32(x1, y1, x2, y2), R, G, B); }
//
//
//   //virtual void defer_save_to_cache()= 0;
//
//   //virtual bool save_to_image(const ::file::path & pathDib)= 0;
//   //virtual bool load_from_image(const ::file::path & pathDib)= 0;
//
//
//
//   virtual ::pointer<::object>clone() const = 0;
//
//
//
//};
//
//



//inline void copy_image32(::color32_t * pimage32Dst, const ::size_i32 & size, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc)
//{
//
//   return copy_image32(pimage32Dst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
//
//}


//
