#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/platform/department.h"


#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13


#define RGB_TO_RGBQUAD(rectangle,g,b)   (rgb(b,g,int_rectangle))
#define CLR_TO_RGBQUAD(clr)     (rgb(::blue(clr), ::green(clr), ::red(clr)))


namespace image
{


//sclass image_list;




class CLASS_DECL_AURA imaging :
   virtual public ::acme::department
{
public:


   ::pointer < ::mutex >                             m_pmutexWork;

   ::pointer<image_array>             m_pimageaWork;


   imaging();
   ~imaging() override;


   virtual void initialize(::particle * pparticle) override;


   virtual void pixelate_24CC(unsigned char * pbDest, int xDest, int yDest, int wDest, int cx, int cy, unsigned char * pbSrc, int xSrc, int ySrc, int wSrc, int iSize);

   virtual void alpha_pixelate_24CC(unsigned char * pbDest, int xDest, int yDest, int wDest, int cx, int cy, unsigned char * lpbSrc1, int xSrc1, int ySrc1, int wSrc1, unsigned char * lpbSrc2, int xSrc2, int ySrc2, int wSrc2, int iSize, int iAlpha);

   virtual void blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, int iRadius);

   virtual void blur_32CC_r2(::image::image *ppimageDst, ::image::image *pimageSrc);

   virtual void channel_gray_blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, int iChannel, int iRadius);
   virtual void channel_gray_blur(::draw2d::graphics * pgraphics, const ::int_point & pointDst, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc, int iChannel, int iRadius);
   virtual void channel_gray_blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, int iChannel, int iFilterWidth, int iFilterHeight,  unsigned char * pbFilter);

   virtual void channel_gray_blur(::draw2d::graphics * pgraphics, const ::int_point & pointDst, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc, int iChannel, const ::int_size & sizeFilter,  unsigned char * pbFilter);

   virtual void channel_alpha_gray_blur_32CC(::image::image *ppimageDst, ::image::image *pimageSrc, int iChannel, int iRadius);
   virtual void channel_alpha_gray_blur(::draw2d::graphics * pgraphics, const ::int_point & pointDst, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc, int iChannel, int iRadius);

   void alpha_spread_R2_24CC(unsigned char * pbDest, int xDest, int yDest, int wDest, int cx, int cy, unsigned char * pbSrc, int ySrc, int xSrc, int wSrc, unsigned char bMin);

   void alpha_spread__24CC(unsigned char * pbDest, int xDest, int yDest, int wDest, int cx, int cy, unsigned char * pbSrc, int ySrc, int xSrc, int wSrc, unsigned char bMin, int iRadius);

   void spread__32CC(::image::image *ppimageDst, ::image::image *pimageSrc, int iRadius, const ::color::color & colorSpreadSetColor);


   void channel_spread(
   ::draw2d::graphics * pgraphics,
   const ::int_point & pointDst,
   const ::int_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::int_point & pointSrc,
   int iChannel,
   int iRadius);

   void channel_spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::int_point & pointDst,
   const ::int_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::int_point & pointSrc,
   int iChannel,
   int iRadius,
   const ::color::color & color);

   void spread(
   ::draw2d::graphics * pgraphics,
   const ::int_point & pointDst,
   const ::int_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::int_point & pointSrc,
   int iRadius);

   void spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::int_point & pointDst,
   const ::int_size & size,
   ::draw2d::graphics * pdcSrc,
   const ::int_point & pointSrc,
   int iRadius,
   const ::color::color & color);

   void true_blend(::draw2d::graphics * pgraphics, const ::int_rectangle & rectangle, ::draw2d::graphics * pdcColorAlpha, const ::int_point & pointAlpha, ::image::image *pimageWork = nullptr, ::image::image *pimageWork2 = nullptr, ::image::image *pimageWork3 = nullptr);

   void blur(::image::image *pimage, int iRadius);

   void blur(::image::image *pimage, int_rectangle rectangle, int iRadius);

   void color_blend_24CC(
   unsigned char * pbA,

   int x1,
   int y1,
   int w1,
   int cx,
   int cy,
   ::color32_t color32,
   unsigned char * pbC,

   int x3,
   int y3,
   int w3);




   void clip_color_blend(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size, const ::color::color & color, unsigned char alpha);
   void clip_color_blend(::draw2d::graphics * pgraphics, const ::int_rectangle & rectangle, const ::color::color & color, unsigned char alpha);

   /*
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size, ::color32_t color32, unsigned char alpha, ::draw2d::region * prgnClip);
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::int_rectangle & rectangle, ::color32_t color32, unsigned char alpha, ::draw2d::region * prgnClip);
   */

   void trait(::image::image *pimage, long long iTrait);

//   static void CreateBitmap(
//   ::draw2d::graphics * pgraphics,
//   ::draw2d::bitmap * pbitmapOld,
//   ::draw2d::bitmap * pbitmap,
////  BITMAP * pbmp,
//   int cx,
//   int cy);

   //static bool CreateBitmap(
   //   ::draw2d::graphics * pgraphics,
   //::draw2d::graphics * pdcScreen,
   //::draw2d::bitmap * pbitmap,
   //::draw2d::bitmap * pbitmapOld,
   ////BITMAP * pbmp,
   //int cx,
   //int cy);

   void AlphaTextOut(::draw2d::graphics * pgraphics, int left, int top, const ::scoped_string & scopedstr, const ::color::color & color, double dBlend);


   /*

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::int_rectangle & rectangle);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::int_rectangle & rectangle);

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::int_rectangle & rectangle,
         ::draw2d::region * prgnClip);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::int_rectangle & rectangle,
         ::draw2d::region * prgnClip);

   */

//   bool GetDeviceContext24BitsCC(
//      ::draw2d::graphics *pdc,
//      BITMAP & bm,
//      BITMAPINFO & bmi,
//      memory & memomrystorage,
//      ::draw2d::bitmap * pbitmap,
//      const ::int_rectangle & rectangle,
//      int & iWidth,
//      unsigned int & uiStartScanLine,
//      unsigned int & uiScanLineCount,
//      int & iLimitYParam);
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
//      int x,
//      int y,
//      int cx,
//      int cy,
//      ::color::color crTransparent);

   void HueVRCP(::image::image *pimage, ::color::color crHue, double dCompress);

//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::draw2d::bitmap * pbitmap,
//      ::draw2d::bitmap * pbitmapMask,
//      const ::int_rectangle & rectangle,
//      ::color::color crTransparent);
//
//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      int x,
//      int y,
//      int cx,
//      int cy,
//      ::color::color crAlpha);

   void change_hue(image_list * pilHue, image_list * pil, const ::color::color & crHue, double dCompress);

   void BitmapBlend2(::draw2d::graphics * pdcDst, const ::int_point & point, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc,
                     ::draw2d::graphics * pdcAlpha, // alpha information device (in alpha channel)
                     const ::int_point & pointAlpha);

   void BitmapDivBlend(::draw2d::graphics * pdcDst, const ::int_point & point, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc, unsigned char bAlpha);

   //bool bitmap_blend(::draw2d::graphics * pdcDst, const ::int_point & point, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc, unsigned char bAlpha);

//   bool bitmap_blend(::draw2d::graphics * pdcDst, const ::int_point & point, const ::int_size & size, ::image::image *pimage, const ::int_point & pointSrc, unsigned char bAlpha);

   void BitmapBlend24CC(
   unsigned char * pbA,

   int x1,
   int y1,
   int w1,
   int cx,
   int cy,
   unsigned char * pbB,

   int x2,
   int y2,
   int w2,
   unsigned char * pbC,

   int x3,
   int y3,
   int w3);
   void BitmapBlend24CC(
   unsigned char * pbDest,

   int xDest,
   int yDest,
   int wDest,
   int cx,
   int cy,
   unsigned char * pbSrc,

   int xSrc,
   int ySrc,
   int wSrc,
   unsigned char bAlpha);

   virtual void ColorInvert(::draw2d::graphics * pgraphics, int x, int y, int cx, int cy);


   //inline void load_image(::image::image_pointer & pimage, ::memory_pointer pmemory)
   //{ 

   //   auto estatus = __øconstruct(pimage);

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

   //   auto estatus = __øconstruct(pimage);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return load_image(pimage, pframea, pmemory);

   //}

   

   void embossed_text_out(
   ::draw2d::graphics *        pdc,
   int                 x,
   int                 y,
   const_char_pointer           pcsz,

   size_t                  cb,
   ::color::color                crText,
   ::color::color                crShadow,
   int                 cx,
   int                 cy);

   //void GetMultiLineTextExtent(HDC hDC, string_array *pArray, LPSIZE32 pSize);

   //void DrawMultiLineText(HDC hDC, string_array *pArray);


   ::image::image_pointer get_work_image();
   void free_work_image(::image::image *pimage);
   

   virtual bool draw2d_gif_draw_frame(::image::image *pimageCanvas, image_frame_array * pframea, ::image::image_frame * pframe, int uFrameIndex, unsigned char * ba, int iScan, color_array & colora, int transparentIndex);

   virtual bool nanosvg(::image::image *pimage, void * pNSVGimage, int iRedLower);

   
};


} // namespace image




