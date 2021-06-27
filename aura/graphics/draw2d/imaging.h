#pragma once


#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13


#define RGB_TO_RGBQUAD(rectangle,g,b)   (rgb(b,g,rectangle_i32))
#define CLR_TO_RGBQUAD(clr)     (rgb(::blue(clr), ::green(clr), ::red(clr)))


class image_list;


class CLASS_DECL_AURA imaging :
   virtual public ::acme::department
{
public:


   ::mutex                             m_mutexWork;

   image_array                         m_imageaWork;


   imaging();
   virtual ~imaging();


   virtual ::e_status initialize(::object * pobject) override;


   virtual void pixelate_24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 xSrc, i32 ySrc, i32 wSrc, i32 iSize);

   virtual void alpha_pixelate_24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * lpbSrc1, i32 xSrc1, i32 ySrc1, i32 wSrc1, byte * lpbSrc2, i32 xSrc2, i32 ySrc2, i32 wSrc2, i32 iSize, i32 iAlpha);

   virtual void blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iRadius);

   virtual void blur_32CC_r2(::image * ppimageDst, ::image * pimageSrc);

   virtual bool channel_gray_blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius);
   virtual bool channel_gray_blur(::draw2d::graphics * pgraphics, const ::point_i32 & pointDst, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc, i32 iChannel, i32 iRadius);
   virtual bool channel_gray_blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iChannel, i32 iFilterWidth, i32 iFilterHeight,  byte * pbFilter);

   virtual bool channel_gray_blur(::draw2d::graphics * pgraphics, const ::point_i32 & pointDst, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc, i32 iChannel, const ::size_i32 & sizeFilter,  byte * pbFilter);

   virtual bool channel_alpha_gray_blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius);
   virtual bool channel_alpha_gray_blur(::draw2d::graphics * pgraphics, const ::point_i32 & pointDst, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc, i32 iChannel, i32 iRadius);

   void alpha_spread_R2_24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, byte bMin);

   void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, byte bMin, i32 iRadius);

   bool spread__32CC(::image * ppimageDst, ::image * pimageSrc, i32 iRadius, ::color32_t color32);


   bool channel_spread(
   ::draw2d::graphics * pgraphics,
   const ::point_i32 & pointDst,
   const ::size_i32 & size,
   ::draw2d::graphics * pdcSrc,
   const ::point_i32 & pointSrc,
   i32 iChannel,
   i32 iRadius);

   bool channel_spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::point_i32 & pointDst,
   const ::size_i32 & size,
   ::draw2d::graphics * pdcSrc,
   const ::point_i32 & pointSrc,
   i32 iChannel,
   i32 iRadius,
   ::color32_t color32);

   bool spread(
   ::draw2d::graphics * pgraphics,
   const ::point_i32 & pointDst,
   const ::size_i32 & size,
   ::draw2d::graphics * pdcSrc,
   const ::point_i32 & pointSrc,
   i32 iRadius);

   bool spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::point_i32 & pointDst,
   const ::size_i32 & size,
   ::draw2d::graphics * pdcSrc,
   const ::point_i32 & pointSrc,
   i32 iRadius,
   ::color32_t color32);

   bool true_blend(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::graphics * pdcColorAlpha, const ::point_i32 & pointAlpha, ::image * pimageWork = nullptr, ::image * pimageWork2 = nullptr, ::image * pimageWork3 = nullptr);

   bool blur(::image * pimage, int iRadius);

   bool blur(::image * pimage, rectangle_i32 rectangle, i32 iRadius);

   void color_blend_24CC(
   byte * pbA,

   i32 x1,
   i32 y1,
   i32 w1,
   i32 cx,
   i32 cy,
   ::color32_t color32,
   byte * pbC,

   i32 x3,
   i32 y3,
   i32 w3);




   bool clip_color_blend(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, ::color32_t color32, byte alpha);
   bool clip_color_blend(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, ::color32_t color32, byte alpha);

   /*
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, ::color32_t color32, byte alpha, ::draw2d::region * prgnClip);
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, ::color32_t color32, byte alpha, ::draw2d::region * prgnClip);
   */

   ::e_status trait(::image * pimage, ::i64 iTrait);

   static bool CreateBitmap(
   ::draw2d::graphics * pgraphics,
   ::draw2d::bitmap * pbitmapOld,
   ::draw2d::bitmap * pbitmap,
//  BITMAP * pbmp,
   i32 cx,
   i32 cy);

   static bool CreateBitmap(
      ::draw2d::graphics * pgraphics,
   ::draw2d::graphics * pdcScreen,
   ::draw2d::bitmap * pbitmap,
   ::draw2d::bitmap * pbitmapOld,
   //BITMAP * pbmp,
   i32 cx,
   i32 cy);

   void AlphaTextOut(::draw2d::graphics * pgraphics, i32 left, i32 top, const char * pcsz, i32 len, ::color32_t color32, double dBlend);


   /*

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rectangle_i32 & rectangle);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rectangle_i32 & rectangle);

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rectangle_i32 & rectangle,
         ::draw2d::region * prgnClip);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rectangle_i32 & rectangle,
         ::draw2d::region * prgnClip);

   */

//   bool GetDeviceContext24BitsCC(
//      ::draw2d::graphics *pdc,
//      BITMAP & bm,
//      BITMAPINFO & bmi,
//      memory & memomrystorage,
//      ::draw2d::bitmap * pbitmap,
//      const ::rectangle_i32 & rectangle,
//      i32 & iWidth,
//      ::u32 & uiStartScanLine,
//      ::u32 & uiScanLineCount,
//      i32 & iLimitYParam);
//
//
//
//
//
//
//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::draw2d::bitmap * pbitmap,
//      ::draw2d::bitmap * pbitmapMask,
//      i32 x,
//      i32 y,
//      i32 cx,
//      i32 cy,
//      ::color::color crTransparent);

   bool HueVRCP(::image * pimage, ::color::color crHue, double dCompress);

//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::draw2d::bitmap * pbitmap,
//      ::draw2d::bitmap * pbitmapMask,
//      const ::rectangle_i32 & rectangle,
//      ::color::color crTransparent);
//
//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      i32 x,
//      i32 y,
//      i32 cx,
//      i32 cy,
//      ::color::color crAlpha);

   bool change_hue(image_list * pilHue, image_list * pil, const ::color::color & crHue, double dCompress);

   bool BitmapBlend2(::draw2d::graphics * pdcDst, const ::point_i32 & point, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc,
                     ::draw2d::graphics * pdcAlpha, // alpha information device (in alpha channel)
                     const ::point_i32 & pointAlpha);

   bool BitmapDivBlend(::draw2d::graphics * pdcDst, const ::point_i32 & point, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc, byte bAlpha);

   //bool bitmap_blend(::draw2d::graphics * pdcDst, const ::point_i32 & point, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc, byte bAlpha);

//   bool bitmap_blend(::draw2d::graphics * pdcDst, const ::point_i32 & point, const ::size_i32 & size, ::image * pimage, const ::point_i32 & pointSrc, byte bAlpha);

   void BitmapBlend24CC(
   byte * pbA,

   i32 x1,
   i32 y1,
   i32 w1,
   i32 cx,
   i32 cy,
   byte * pbB,

   i32 x2,
   i32 y2,
   i32 w2,
   byte * pbC,

   i32 x3,
   i32 y3,
   i32 w3);
   void BitmapBlend24CC(
   byte * pbDest,

   i32 xDest,
   i32 yDest,
   i32 wDest,
   i32 cx,
   i32 cy,
   byte * pbSrc,

   i32 xSrc,
   i32 ySrc,
   i32 wSrc,
   byte bAlpha);

   virtual bool ColorInvert(::draw2d::graphics * pgraphics, i32 x, i32 y, i32 cx, i32 cy);


   //inline ::e_status load_image(::image_pointer & pimage, ::memory_pointer pmemory)
   //{ 

   //   auto estatus = __construct(pimage);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }
   //
   //   return load_image(pimage, pmemory); 
   //
   //}

   //inline ::e_status load_image(::image_pointer & pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory)
   //{

   //   auto estatus = __construct(pimage);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return load_image(pimage, pframea, pmemory);

   //}

   

   void embossed_text_out(
   ::draw2d::graphics *        pdc,
   i32                 x,
   i32                 y,
   const char *            pcsz,

   size_t                  cb,
   ::color::color                crText,
   ::color::color                crShadow,
   i32                 cx,
   i32                 cy);

   //void GetMultiLineTextExtent(HDC hDC, string_array *pArray, LPSIZE32 pSize);

   //void DrawMultiLineText(HDC hDC, string_array *pArray);


   ::image_pointer get_work_image();
   void free_work_image(::image * pimage);
   
   
   

   
   
};


