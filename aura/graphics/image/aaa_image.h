// From draw2d/_image.h by camilo on 2022-03-11 19:53 <3ThomasBorregaardSorensen!!
#pragma once
//
//
//class image_frame_array;
//class ::image::image_frame;
//class colorref_array;
//class image_extension;
//class image_map;
//class image_array;
//
//
//CLASS_DECL_AURA void cra_from_quada(colorref_array & colorrefa, WINRGBQUAD * prgbquad, int iCount);
//
//
//CLASS_DECL_AURA void vertical_swap(pixmap * ppixmap);
//CLASS_DECL_AURA void vertical_swap_copy_image32(::color32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void vertical_swap_copy_image32_swap_red_blue(::color32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, int x, int y, int cx, int cy, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, const ::int_size & size, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, const ::int_point & point, const ::int_size & size, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, const ::int_rectangle & rectangle, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void copy_image32_swap_red_blue(::color32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//CLASS_DECL_AURA void _001ProperCopyColorref(::color32_t * pimage32Dst, int cx, int cy, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc = -1);
//
//
//
//namespace draw2d
//{
//
//
//   CLASS_DECL_AURA void image_copy(::image::image *imagethis, ::image::image *pimage);
//   CLASS_DECL_AURA void image_create(::particle * pparticle, ::image::image *& image);
//   CLASS_DECL_AURA void image_create_image(::image::image *pimage, const ::int_size & size);
//   CLASS_DECL_AURA unsigned int * image_get_data(::image::image *pimage);
//   CLASS_DECL_AURA graphics * image_get_graphics(::image::image *pimage);
//
//
//} // namespace draw2d
//
//
//CLASS_DECL_AURA enum_rotate_flip exif_orientation_rotate_flip(int orientation);
//
//
////class CLASS_DECL_AURA image_base :
////   virtual public object
////{
////public:
////
////
////   static float Cosines[360];
////   static float Sines[360];
////   static long long CosN[360]; // * 1 << 31
////   static long long SinN[360];
////   static long long Cos10N[10]; // until 10 degress
////   static long long Sin10N[10]; // more precision * 1 << 34
////   static double dPi;
////
////
////
////   //virtual bool dispose_current_frame()= 0;
////   //virtual bool overlay_frame(int iFrame)= 0;
////   virtual void defer_update()= 0;
////
////
////
////   //virtual bool load_image(::payload payloadFile, bool bCache = true, bool bCreateHelperMaps = false)= 0;
////   //virtual bool load_image(const ::string & pszMatter, bool bCache = true, bool bCreateHelperMaps = false)= 0;
////   ////virtual bool read_from_file(file_pointer  pfile)= 0;
////
////
////   //virtual bool load_matter_icon(string_array & straMatter, string strIcon)= 0;
////
////
////   //virtual bool load_thumbnail(::payload payloadFile, int w, int h)= 0;
////
////
////   //virtual bool save_image(::payload payloadFile, ::save_image * psaveimage = nullptr) = 0;
////   //virtual bool save_dib(::payload payloadFile) = 0;
////
////   virtual image get_image(::payload payloadFile, bool bSync = false) = 0;
////   virtual image matter_image(string strMatter, bool bSync = false) = 0;
////   virtual image load_image(::payload payloadFile, bool bCreateHelperMaps = false) = 0;
////   virtual image load_matter_image(const ::string & pszMatter, bool bCache = true, bool bCreateHelperMaps = false) = 0;
////   virtual image load_matter_icon(string_array & straMatter, string strIcon) = 0;
////   virtual image load_thumbnail(::payload payloadFile, int w, int h) = 0;
////   virtual image load_thumbnail(const ::string & pszPath) = 0;
////   virtual image load_dib(const ::file::path & pathDib) = 0;
////
////
////   virtual bool save_image(::payload payloadFile, ::save_image * psaveimage = nullptr) = 0;
////   virtual bool save_dib(const ::file::path & pathDib) = 0;
////
////
////   virtual ::draw2d::graphics * get_graphics() const= 0; // is semantically const (besides may not be implementationly constant)
////   virtual ::draw2d::bitmap_pointer get_bitmap() const= 0; // is semantically const (besides may not be implementationly constant)
////   virtual ::draw2d::bitmap_pointer detach_bitmap()= 0;
////
////   virtual ::collection::count get_image_count() const= 0;
////   virtual ::image::image_pointer get_image(::collection::index i)= 0;
////
////   virtual ::color::color * get_data() const= 0;
////
////   virtual bool set_mipmap(::draw2d::enum_mipmap emipmap)= 0;
////   virtual bool _set_mipmap(::draw2d::enum_mipmap emipmap)= 0;
////
////   virtual bool create_isotropic(::image::image *pimage)= 0;
////   virtual bool create_isotropic(double_array & daRate, ::enum_priority epriority)= 0;
////
////   virtual bool set_origin(const ::int_point & point)= 0;
////   virtual bool set_font_factor(double dFactor)= 0;
////   virtual bool set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode)= 0;
////
////   virtual bool create_helper_map()= 0;
////
////   virtual bool on_load_image()= 0;
////   virtual bool on_exif_orientation()= 0;
////
////   virtual ::int_size get_size() const= 0;
////
////
////
////   virtual bool rate_rgb(int iMul, int iDiv)= 0;
////   virtual bool dc_select(bool bSelect = true)= 0;
////
////   virtual ::color::color GetAverageColor()= 0;
////   virtual ::color::color GetAverageOpaqueColor()= 0;
////   virtual bool blend(::image::image *pimage, ::image::image *pimageRate)= 0;
////   virtual bool Blend(::image::image *pimage, ::image::image *pimageA, int A)= 0;
////   virtual bool Blend(::image::image *pimage, ::image::image *pimageA)= 0;
////   virtual bool blend(const ::int_point & pointDst, ::image::image *pimageSrc, const ::int_point & pointSrc, ::image::image *pimageAlf, const ::int_point & pointDstAlf, const ::int_size & size)= 0;
////   virtual bool precision_blend(const ::int_point & pointDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size)= 0;
////   virtual bool precision_blend(const ::int_point & pointDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA)= 0;
////   virtual bool blend(const ::int_point & pointDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size)= 0;
////   virtual bool blend(const ::int_point & pointDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA)= 0;
////   virtual bool blend2(const ::int_point & pointDst, ::image::image *pimageSrc, const ::int_point & pointSrc, const ::int_size & size, unsigned char bA)= 0;
////   virtual bool fork_blend(const ::int_point & pointDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size)= 0;
////   virtual bool fork_blend(const ::int_point & pointDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA)= 0;
////   virtual bool bitmap_blend(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)= 0;
////
////   virtual bool color_blend(::color32_t color32, unsigned char bAlpha)= 0;
////   virtual bool BitBlt(::image::image *pimage, int op)= 0;
////   virtual bool BitBlt(int cxParam, int cyParam, ::image::image *pimage, int op)= 0;
////   virtual int cos(int i, int iAngle)= 0;
////   virtual int sin(int i, int iAngle)= 0;
////   virtual int cos10(int i, int iAngle)= 0;
////   virtual int sin10(int i, int iAngle)= 0;
////
////   virtual bool hue_offset(double dRate)= 0;
////
////   virtual bool map(bool bApplyAlphaTransform = true) const= 0; // some implementations may requrire to map to m_pcolorref before manipulate it
////   virtual bool unmap() const= 0; // some implementations may require to unmap from m_pcolorref to update *os* bitmap
////   virtual bool set_mapped()= 0;
////
////   virtual bool flip_vertical(::image::image *pimage)= 0;
////   virtual bool flip_horizontal(::image::image *pimage)= 0;
////   virtual bool flipx(::image::image *pimage)= 0;
////   virtual bool flipy(::image::image *pimage)= 0;
////   virtual ::image::image_pointer flipx()= 0;
////   virtual ::image::image_pointer flipy()= 0;
////
////   virtual bool is_rgb_black()= 0;
////   virtual bool do_xor(::image::image *pimage)= 0;
////
////   virtual bool ToAlpha(int i)= 0;
////   virtual bool ToAlphaAndFill(int i, ::color32_t color32)= 0;
////   virtual bool GrayToARGB(::color32_t color32)= 0;
////
////   virtual bool from_alpha()= 0;
////   virtual bool mult_alpha(::image::image *pimageWork, bool bPreserveAlpha = true)= 0;
////
////   virtual bool mult_alpha()= 0;
////   virtual bool mult_alpha_fast()= 0;
////   virtual bool div_alpha()= 0;
////
////   virtual bool mult_alpha(const ::int_point & point, const ::int_size & size)= 0;
////   virtual bool div_alpha(const ::int_point & point, const ::int_size & size)= 0;
////
////   virtual bool rotate(::image::image *pimage, const ::int_rectangle & rectangle, double dAngle, double dScale)= 0;
////
////   virtual bool rotate(::image::image *pimage, double dAngle, double dScale)= 0;
////   virtual bool rotate(::image::image *pimage, double dAngle)= 0;
////   virtual bool Rotate034(::image::image *pimage, double dAngle, double dScale)= 0;
////
////   virtual bool rotate90(::image::image *pimage)= 0;
////   virtual bool rotate180(::image::image *pimage)= 0;
////   virtual bool rotate270(::image::image *pimage)= 0;
////   virtual bool rotate90()= 0;
////   virtual bool rotate180()= 0;
////   virtual bool rotate270()= 0;
////   virtual bool rotate90flipx(::image::image *pimage)= 0;
////   virtual bool rotate180flipx(::image::image *pimage)= 0;
////   virtual bool rotate270flipx(::image::image *pimage)= 0;
////   virtual bool rotate90flipx()= 0;
////   virtual bool rotate180flipx()= 0;
////   virtual bool rotate270flipx()= 0;
////
////
////   virtual bool set_rgb(::color32_t color32)= 0;
////   virtual bool set_rgb(int R, int G, int B)= 0;
////   virtual bool tint(::image::image *pimage, const rgb & rgb)= 0;
////   virtual bool set_rgb_pre_alpha(int R, int G, int B, int A)= 0;
////   virtual bool rgb_from(::image::image *pimage)= 0;
////   virtual bool paint_rgb(::color::color color)= 0;
////
////
////   virtual bool saturation(double dRate)= 0;
////   virtual bool lightness(double dRate) = 0;
////   virtual bool opacity(double dRate) = 0;
////
////
////   virtual bool SetIconMask(::image::icon * picon, int cx, int cy)= 0;
////   virtual bool RadialFill(unsigned char a, unsigned char rectangle, unsigned char g, unsigned char b, int x, int y, int iRadius)= 0;
////   virtual bool RadialFill(
////   unsigned char a1, unsigned char r1, unsigned char g1, unsigned char b1, // center colors
////   unsigned char a2, unsigned char r2, unsigned char g2, unsigned char b2, // border colors
////   int x, int y, int iRadius)= 0;
////
////   virtual bool gradient_fill(::color::color clr1, ::color::color clr2, const int_point & point1, const int_point & point2)= 0;
////   virtual bool gradient_horizontal_fill(::color::color clr1, ::color::color clr2, int start, int end)= 0;
////   virtual bool gradient_vertical_fill(::color::color clr1, ::color::color clr2, int start, int end)= 0;
////   virtual bool gradient_horizontal_fill(::color::color clr1, ::color::color clr2)= 0;
////   virtual bool gradient_vertical_fill(::color::color clr1, ::color::color clr2)= 0;
////
////
////   virtual unsigned int GetPixel(int x, int y)= 0;
////   virtual bool Mask(::color::color crMask, ::color::color crInMask, ::color::color crOutMask)= 0;
////   virtual bool channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, ::color::enum_channel echannel)= 0;
////   virtual bool transparent_color(::color::color color)= 0;
////
////   virtual bool create_thumbnail(const ::string & pszPath) = 0;
////
////   virtual bool create(const ::int_size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)= 0;
////   virtual bool create(int iWidth, int iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1)= 0;
////   virtual bool host(const pixmap* ppixmap)= 0;
////   virtual bool on_host_read_pixels(const pixmap* ppixmap) = 0;
////   virtual bool create(::draw2d::graphics_pointer & pgraphics)= 0;
////   virtual bool destroy()= 0;
////   // virtual bool detach(::image::image *pimage) = 0;
////
////   // realization is semantically const
////   // image keeps an image and image will be the same,
////   // besides the way the Device Context associated with the image (m_spgraphics)
////   // interprets or deals with it, may machine
////   virtual bool realize(::draw2d::graphics_pointer & pgraphics) const= 0;
////   virtual bool unrealize() const= 0;
////   virtual bool is_realized() const= 0;
////   virtual bool defer_realize(::draw2d::graphics_pointer & pgraphics) const= 0;
////
////   virtual bool DivideRGB(int iDivide)= 0;
////   virtual bool DivideARGB(int iDivide)= 0;
////   virtual bool DivideA(int iDivide)= 0;
////
////
////   virtual bool stretch_image(::image::image *pimage) = 0;
////
////
////   virtual bool to(::image::image *pimage) const= 0;
////   virtual bool from(const ::image::image *pimage)= 0;
////   virtual bool from(::draw2d::graphics_pointer & pgraphics)= 0;
////   virtual bool from(const ::int_point & pointDst, ::draw2d::graphics_pointer & pgraphics, const ::int_point & pointSrc, const ::int_size & size)= 0;
////   virtual bool from(const ::int_point & pointDst, ::image::image *pimage, const ::int_point & pointSrc, const ::int_size & size)= 0;
////   virtual bool from(const ::int_point & pointDst, ::image::image *pimage, const ::int_point & pointSrc, const ::int_size & size, unsigned char bA)= 0;
////   //virtual bool blend(const ::int_point & pointDst, ::image::image *pimage, const ::int_point & pointSrc, const ::int_size & size)= 0;
////   virtual bool from_ignore_alpha(const ::int_point & pointDst, ::image::image *pimage, const ::int_point & pointSrc, const ::int_size & size)= 0;
////
////   virtual bool to(::draw2d::graphics_pointer & pgraphics)= 0;
////   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::int_point & point)= 0;
////   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::int_size & size)= 0;
////   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::int_point & point, const ::int_size & size)= 0;
////   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle)= 0;
////
////   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::int_point & point, const ::int_size & size, const ::int_point & pointSrc)= 0;
////
////
////   virtual bool pixelate(int iSize)= 0;
////
////
////
////   virtual bool fill_channel(int C, ::color::enum_channel echannel)= 0;
////   virtual bool white_fill_channel(int C, ::color::enum_channel echannel)= 0;
////   virtual bool fill_byte(uchar uch)= 0;
////   virtual bool fill(::color::color level)= 0;
////   virtual bool fill(int A, int R, int G, int B)= 0;
////   //      virtual bool Fill(int R, int G, int B)= 0;
////   //virtual bool set(int R, int G, int B)= 0;
////   virtual bool fill_glass(int R, int G, int B, int A)= 0;
////   virtual bool fill_stippled_glass(int R, int G, int B)= 0;
////   virtual bool invert()= 0;
////   virtual bool channel_invert(::color::enum_channel echannel)= 0;
////   virtual bool channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false)= 0;
////   virtual bool channel_multiply(::color::enum_channel echannel, ::image::image *pimage, bool bIfAlphaIgnorePreDivPosMult = false)= 0;
////   virtual bool channel_lighten(::color::enum_channel echannel, ::image::image *pimage)= 0;
////   virtual bool channel_darken(::color::enum_channel echannel, ::image::image *pimage)= 0;
////   virtual bool channel_from(::color::enum_channel echannel, ::image::image *pimage)= 0;
////   virtual bool channel_multiply(::color::enum_channel echannel, ::image::image *pimage, const ::int_rectangle & rectangle, bool bIfAlphaIgnorePreDivPosMult = false)= 0;
////
////   virtual bool channel_from(::color::enum_channel echannel, ::image::image *pimage, const ::int_rectangle & rectangle)= 0;
////
////   virtual bool channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc)= 0;
////   virtual bool channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image::image *pimage)= 0;
////
////   virtual bool Map(int ToRgb, int FromRgb)= 0;
////
////   virtual bool create_nanosvg(char * pszXml, double dDpi = 0.0) = 0;
////   virtual bool nanosvg(char * pszXml, double dDpi = 0.0)= 0;
////
////   virtual bool op(string str)= 0;
////
////   //virtual bool from( ::image::image *pimage)= 0;
////
////   virtual bool Blend(::image::image *pimage, int A)= 0;
////   virtual bool Darken(::image::image *pimage)= 0;
////   virtual bool Difference(::image::image *pimage)= 0;
////   virtual bool Lighten(::image::image *pimage)= 0;
////   virtual bool Multiply(::image::image *pimage)= 0;
////   virtual bool Screen(::image::image *pimage)= 0;
////
////   virtual bool lighten(double dRate)= 0;
////
////   virtual bool copy(::image::image *pimage, int x, int y)= 0;
////   virtual bool PasteRect(::image::image *pimage, int x, int y)= 0;
////
////   virtual bool fill_rectangle(const ::int_rectangle & rectangle, ::color32_t color32)= 0;
////
////   virtual bool fill_rectangle(const ::int_rectangle & rectangle, int R, int G, int B)= 0;
////
////
////   virtual bool fill_glass_rect(const ::int_rectangle & rectangle, int R, int G, int B, int A)= 0;
////
////   virtual bool fill_stippled_glass_rect(const ::int_rectangle & rectangle, int R, int G, int B)= 0;
////
////
////   virtual bool BlendRect(::image::image *pimage, int x, int y, int A)= 0;
////   virtual bool DarkenRect(::image::image *pimage, int x, int y)= 0;
////   virtual bool DifferenceRect(::image::image *pimage, int x, int y)= 0;
////   virtual bool LightenRect(::image::image *pimage, int x, int y)= 0;
////   virtual bool MultiplyRect(::image::image *pimage, int x, int y)= 0;
////   virtual bool ScreenRect(::image::image *pimage, int x, int y)= 0;
////
////   virtual bool horizontal_line(int y, int R, int G, int B, int A = 0, int x1 = 0, int x2 = -1)= 0;
////   virtual bool Line(int x1, int y1, int x2, int y2, int R, int G, int B)= 0;
////   virtual bool LineGlass(int x1, int y1, int x2, int y2, int R, int G, int B, int A)= 0;
////
////   virtual bool create_frame(const ::int_size & size, int iFrameCount)= 0;
////   virtual bool set_frame2(void * pdata, int iFrame, int iFrameCount)= 0;
////
////   virtual bool set_frame1(void * pdata, int iFrame, int iFrameCount)= 0;
////
////   virtual bool get_frame(void * pdata, int iFrame, int iFrameCount)= 0;
////
////   virtual bool xor_image_frame2(void * pdata, int iFrame, int iFrameCount)= 0;
////
////
////   virtual bool create_circle(::image::image *pimage, int diameter)= 0;
////   virtual bool create_framed_square(::image::image *pimage, int inner, int outer, ::color32_t color32)= 0;
////
////
////   virtual bool invert_rgb(const ::int_rectangle & rectangle)= 0;
////   virtual bool invert_rgb() = 0;
////
////
////
////   virtual int scan_area()= 0;
////
////
////
////   inline bool fill_rect_dim(int x, int y, int w, int h, ::color32_t color32) { return fill_rectangle(int_rectangle_dimension(x, y, w, h), color32); }
////   inline bool fill_rect_dim(int x, int y, int w, int h, int R, int G, int B) { return fill_rectangle(int_rectangle_dimension(x, y, w, h), R, G, B); }
////   inline bool fill_rect_coord(int x1, int y1, int x2, int y2, ::color32_t color32) { return fill_rectangle(::int_rectangle(x1, y1, x2, y2), color32); }
////   inline bool fill_rect_coord(int x1, int y1, int x2, int y2, int R, int G, int B) { return fill_rectangle(::int_rectangle(x1, y1, x2, y2), R, G, B); }
////
////
////   //virtual void defer_save_to_cache()= 0;
////
////   //virtual bool save_to_image(const ::file::path & pathDib)= 0;
////   //virtual bool load_from_image(const ::file::path & pathDib)= 0;
////
////
////
////   virtual ::pointer<::object>clone() const = 0;
////
////
////
////};
////
////
//
//
//
////inline void copy_image32(::color32_t * pimage32Dst, const ::int_size & size, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc)
////{
////
////   return copy_image32(pimage32Dst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
////
////}
//
//
//inline CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, const ::int_point & point, const ::int_size & size, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc)
//{
//
//   unsigned char * pDst = (unsigned char *)pimage32Dst;
//
//   return copy_image32((::color32_t *)pDst + point.x() * sizeof(::color32_t) + point.y() * iStrideDst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);
//
//}
//
//
//inline CLASS_DECL_AURA void copy_image32(::color32_t * pimage32Dst, const ::int_rectangle & rectangle, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc)
//{
//
//   return copy_image32(pimage32Dst, rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);
//
//}
//
////
//#include "_image.h"
//
//
//#include "source.h"
//
//
//#include "drawer.h"
//
//
//#include "drawing.h"
//
//
//#include "header.h"
//
//
//#include "image.h"
//
//
//#include "dynamic.h"
//#include "meta.h"
//
//
//#include "drawer.h"
//
//
//#include "image.h"
//#include "frame.h"
//#include "frame_array.h"
//#include "extension.h"
//#include "map.h"
//#include "map_ex1.h"
//
//
//#include "cursor.h"
//#include "icon.h"
//
////#include "cursor_set.h"
//
//#include "fastblur.h"
//
//
//#include "imaging.h"
//
//#include "load_image.h"
//
//#include "image_context.h"
//
//
//
