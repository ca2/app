#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/platform/department.h"


#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13


#define RGB_TO_RGBQUAD(rectangle,g,b)   (rgb(b,g,i32_rectangle))
#define CLR_TO_RGBQUAD(clr)     (rgb(::blue(clr), ::green(clr), ::red(clr)))


namespace image
{


//sclass image_list;




class CLASS_DECL_AURA imaging :
   virtual public ::platform::department
{
public:


   ::pointer < ::mutex >                             m_pmutexWork;

   ::pointer<image_array>             m_pimageaWork;


   imaging();
   ~imaging() override;


   virtual void initialize(::particle * pparticle) override;


   virtual void pixelate_24CC(::u8 * pbDest, ::i32 xDest, ::i32 yDest, ::i32 wDest, ::i32 cx, ::i32 cy, ::u8 * pbSrc, ::i32 xSrc, ::i32 ySrc, ::i32 wSrc, ::i32 iSize);

   virtual void alpha_pixelate_24CC(::u8 * pbDest, ::i32 xDest, ::i32 yDest, ::i32 wDest, ::i32 cx, ::i32 cy, ::u8 * lpbSrc1, ::i32 xSrc1, ::i32 ySrc1, ::i32 wSrc1, ::u8 * lpbSrc2, ::i32 xSrc2, ::i32 ySrc2, ::i32 wSrc2, ::i32 iSize, ::i32 iAlpha);

   virtual void blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, ::i32 iRadius);

   virtual void blur_32CC_r2(::image::image *ppimageDst, ::image::image *pimageSrc);

   virtual void channel_gray_blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, ::i32 iChannel, ::i32 iRadius);
   virtual void channel_gray_blur(::draw2d::graphics * pgraphics, const ::i32_point & pointDst, const ::i32_size & size, ::draw2d::graphics * pdcSrc, const ::i32_point & pointSrc, ::i32 iChannel, ::i32 iRadius);
   virtual void channel_gray_blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, ::i32 iChannel, ::i32 iFilterWidth, ::i32 iFilterHeight,  ::u8 * pbFilter);

   virtual void channel_gray_blur(::draw2d::graphics * pgraphics, const ::i32_point & pointDst, const ::i32_size & size, ::draw2d::graphics * pdcSrc, const ::i32_point & pointSrc, ::i32 iChannel, const ::i32_size & sizeFilter,  ::u8 * pbFilter);

   virtual void channel_alpha_gray_blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, ::i32 iChannel, ::i32 iRadius);
   virtual void channel_alpha_gray_blur(::draw2d::graphics * pgraphics, const ::i32_point & pointDst, const ::i32_size & size, ::draw2d::graphics * pdcSrc, const ::i32_point & pointSrc, ::i32 iChannel, ::i32 iRadius);

   void alpha_spread_R2_24CC(::u8 * pbDest, ::i32 xDest, ::i32 yDest, ::i32 wDest, ::i32 cx, ::i32 cy, ::u8 * pbSrc, ::i32 ySrc, ::i32 xSrc, ::i32 wSrc, ::u8 bMin);

   void alpha_spread__24CC(::u8 * pbDest, ::i32 xDest, ::i32 yDest, ::i32 wDest, ::i32 cx, ::i32 cy, ::u8 * pbSrc, ::i32 ySrc, ::i32 xSrc, ::i32 wSrc, ::u8 bMin, ::i32 iRadius);

   void spread__32CC(::image::image *ppimageDst, ::image::image *pimageSrc, ::i32 iRadius, const ::color::color & colorSpreadSetColor);


   void channel_spread(
   ::draw2d::graphics * pgraphics,
   const ::i32_point & pointDst,
   const ::i32_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::i32_point & pointSrc,
   ::i32 iChannel,
   ::i32 iRadius);

   void channel_spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::i32_point & pointDst,
   const ::i32_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::i32_point & pointSrc,
   ::i32 iChannel,
   ::i32 iRadius,
   const ::color::color & color);

   void spread(
   ::draw2d::graphics * pgraphics,
   const ::i32_point & pointDst,
   const ::i32_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::i32_point & pointSrc,
   ::i32 iRadius);

   void spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::i32_point & pointDst,
   const ::i32_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::i32_point & pointSrc,
   ::i32 iRadius,
   const ::color::color & color);

   void true_blend(::draw2d::graphics * pgraphics, const ::i32_rectangle & rectangle, ::draw2d::graphics * pdcColorAlpha, const ::i32_point & pointAlpha, ::image::image *pimageWork = nullptr, ::image::image *pimageWork2 = nullptr, ::image::image *pimageWork3 = nullptr);

   void blur(::image::image *pimage, ::i32 iRadius);

   void blur(::image::image *pimage, i32_rectangle rectangle, ::i32 iRadius);

   void color_blend_24CC(
   ::u8 * pbA,

   ::i32 x1,
   ::i32 y1,
   ::i32 w1,
   ::i32 cx,
   ::i32 cy,
   ::color32_t color32,
   ::u8 * pbC,

   ::i32 x3,
   ::i32 y3,
   ::i32 w3);




   void clip_color_blend(::draw2d::graphics * pgraphics, const ::i32_point & point, const ::i32_size & size, const ::color::color & color, ::u8 alpha);
   void clip_color_blend(::draw2d::graphics * pgraphics, const ::i32_rectangle & rectangle, const ::color::color & color, ::u8 alpha);

   /*
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::i32_point & point, const ::i32_size & size, ::color32_t color32, ::u8 alpha, ::draw2d::region * prgnClip);
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::i32_rectangle & rectangle, ::color32_t color32, ::u8 alpha, ::draw2d::region * prgnClip);
   */

   void trait(::image::image *pimage, ::i64 iTrait);

//   static void CreateBitmap(
//   ::draw2d::graphics * pgraphics,
//   ::draw2d::bitmap * pbitmapOld,
//   ::draw2d::bitmap * pbitmap,
////  BITMAP * pbmp,
//   ::i32 cx,
//   ::i32 cy);

   //static bool CreateBitmap(
   //   ::draw2d::graphics * pgraphics,
   //::draw2d::graphics * pdcScreen,
   //::draw2d::bitmap * pbitmap,
   //::draw2d::bitmap * pbitmapOld,
   ////BITMAP * pbmp,
   //::i32 cx,
   //::i32 cy);

   void AlphaTextOut(::draw2d::graphics * pgraphics, ::i32 left, ::i32 top, const ::scoped_string & scopedstr, const ::color::color & color, ::f64 dBlend);


   /*

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::i32_rectangle & rectangle);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::i32_rectangle & rectangle);

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::i32_rectangle & rectangle,
         ::draw2d::region * prgnClip);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::i32_rectangle & rectangle,
         ::draw2d::region * prgnClip);

   */

//   bool GetDeviceContext24BitsCC(
//      ::draw2d::graphics *pdc,
//      BITMAP & bm,
//      BITMAPINFO & bmi,
//      memory & memomrystorage,
//      ::draw2d::bitmap * pbitmap,
//      const ::i32_rectangle & rectangle,
//      ::i32 & iWidth,
//      ::u32 & uiStartScanLine,
//      ::u32 & uiScanLineCount,
//      ::i32 & iLimitYParam);
//
//
//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::draw2d::bitmap * pbitmap,
//      ::draw2d::bitmap * pbitmapMask,
//      ::i32 x,
//      ::i32 y,
//      ::i32 cx,
//      ::i32 cy,
//      ::color::color crTransparent);

   void HueVRCP(::image::image *pimage, ::color::color crHue, ::f64 dCompress);

//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::draw2d::bitmap * pbitmap,
//      ::draw2d::bitmap * pbitmapMask,
//      const ::i32_rectangle & rectangle,
//      ::color::color crTransparent);
//
//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::i32 x,
//      ::i32 y,
//      ::i32 cx,
//      ::i32 cy,
//      ::color::color crAlpha);

   void change_hue(image_list * pilHue, image_list * pil, const ::color::color & crHue, ::f64 dCompress);

   void BitmapBlend2(::draw2d::graphics * pdcDst, const ::i32_point & point, const ::i32_size & size, ::draw2d::graphics * pdcSrc, const ::i32_point & pointSrc,
                     ::draw2d::graphics * pdcAlpha, // alpha information device (in alpha channel)
                     const ::i32_point & pointAlpha);

   void BitmapDivBlend(::draw2d::graphics * pdcDst, const ::i32_point & point, const ::i32_size & size, ::draw2d::graphics * pdcSrc, const ::i32_point & pointSrc, ::u8 bAlpha);

   //bool bitmap_blend(::draw2d::graphics * pdcDst, const ::i32_point & point, const ::i32_size & size, ::draw2d::graphics * pdcSrc, const ::i32_point & pointSrc, ::u8 bAlpha);

//   bool bitmap_blend(::draw2d::graphics * pdcDst, const ::i32_point & point, const ::i32_size & size, ::image::image *pimage, const ::i32_point & pointSrc, ::u8 bAlpha);

   void BitmapBlend24CC(
   ::u8 * pbA,

   ::i32 x1,
   ::i32 y1,
   ::i32 w1,
   ::i32 cx,
   ::i32 cy,
   ::u8 * pbB,

   ::i32 x2,
   ::i32 y2,
   ::i32 w2,
   ::u8 * pbC,

   ::i32 x3,
   ::i32 y3,
   ::i32 w3);
   void BitmapBlend24CC(
   ::u8 * pbDest,

   ::i32 xDest,
   ::i32 yDest,
   ::i32 wDest,
   ::i32 cx,
   ::i32 cy,
   ::u8 * pbSrc,

   ::i32 xSrc,
   ::i32 ySrc,
   ::i32 wSrc,
   ::u8 bAlpha);

   virtual void ColorInvert(::draw2d::graphics * pgraphics, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy);


   //inline void load_image(::image::image_pointer & pimage, ::memory_pointer pmemory)
   //{ 

   //   auto estatus = constructø(pimage);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }
   //
   //   return load_image(pimage, pmemory); 
   //
   //}

   //inline void load_image(::image::image_pointer & pimage, ::pointer<image_frame_array>& pframea, ::memory_pointer pmemory)
   //{

   //   auto estatus = constructø(pimage);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return load_image(pimage, pframea, pmemory);

   //}

   

   void embossed_text_out(
   ::draw2d::graphics *        pdc,
   ::i32                 x,
   ::i32                 y,
   const_char_pointer pcsz,

   size_t                  cb,
   ::color::color                crText,
   ::color::color                crShadow,
   ::i32                 cx,
   ::i32                 cy);

   //void GetMultiLineTextExtent(HDC hDC, string_array_base *pArray, LPSIZE32 pSize);

   //void DrawMultiLineText(HDC hDC, string_array_base *pArray);


   ::image::image_pointer get_work_image();
   void free_work_image(::image::image *pimage);
   

   virtual bool draw2d_gif_draw_frame(::image::image *pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, ::i32 uFrameIndex, ::u8 * ba, ::i32 iScan, color_array & colora, ::i32 transparentIndex);

   virtual bool nanosvg(::image::load_image *pimage, void * pNSVGimage, ::i32 iRedLower, ::i32 iWidth, ::i32 iHeight);

   
};


} // namespace image




