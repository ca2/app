#pragma once


#define XFM_LOAD_IMAGE 12
#define XFM_RETURN_LOADED_IMAGE 13


#define RGB_TO_RGBQUAD(rect,g,b)   (RGB(b,g,rect))
#define CLR_TO_RGBQUAD(clr)     (RGB(::blue(clr), ::green(clr), ::red(clr)))


class image_list;


class CLASS_DECL_AURA imaging :
   virtual public ::object
{
public:


   ::mutex                             m_mutexWork;

   image_array                         m_imageaWork;


   imaging();
   virtual ~imaging();


   virtual ::estatus initialize(::object * pobjectContext) override;


   virtual void pixelate_24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 xSrc, i32 ySrc, i32 wSrc, i32 iSize);

   virtual void alpha_pixelate_24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * lpbSrc1, i32 xSrc1, i32 ySrc1, i32 wSrc1, byte * lpbSrc2, i32 xSrc2, i32 ySrc2, i32 wSrc2, i32 iSize, i32 iAlpha);

   virtual void blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iRadius);

   virtual void blur_32CC_r2(::image * ppimageDst, ::image * pimageSrc);

   virtual bool channel_gray_blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius);
   virtual bool channel_gray_blur(::draw2d::graphics * pgraphics, const ::point & pointDst, const ::size & size, ::draw2d::graphics * pdcSrc, const ::point & pointSrc, i32 iChannel, i32 iRadius);
   virtual bool channel_gray_blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iChannel, i32 iFilterWidth, i32 iFilterHeight,  byte * pbFilter);

   virtual bool channel_gray_blur(::draw2d::graphics * pgraphics, const ::point & pointDst, const ::size & size, ::draw2d::graphics * pdcSrc, const ::point & pointSrc, i32 iChannel, const ::size & sizeFilter,  byte * pbFilter);

   virtual bool channel_alpha_gray_blur_32CC(::image * ppimageDst, ::image * pimageSrc, i32 iChannel, i32 iRadius);
   virtual bool channel_alpha_gray_blur(::draw2d::graphics * pgraphics, const ::point & pointDst, const ::size & size, ::draw2d::graphics * pdcSrc, const ::point & pointSrc, i32 iChannel, i32 iRadius);

   void alpha_spread_R2_24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, BYTE bMin);

   void alpha_spread__24CC(byte * pbDest, i32 xDest, i32 yDest, i32 wDest, i32 cx, i32 cy, byte * pbSrc, i32 ySrc, i32 xSrc, i32 wSrc, BYTE bMin, i32 iRadius);

   bool spread__32CC(::image * ppimageDst, ::image * pimageSrc, i32 iRadius, COLORREF cr);


   bool channel_spread(
   ::draw2d::graphics * pgraphics,
   const ::point & pointDst,
   const ::size & size,
   ::draw2d::graphics * pdcSrc,
   const ::point & pointSrc,
   i32 iChannel,
   i32 iRadius);

   bool channel_spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::point & pointDst,
   const ::size & size,
   ::draw2d::graphics * pdcSrc,
   const ::point & pointSrc,
   i32 iChannel,
   i32 iRadius,
   COLORREF cr);

   bool spread(
   ::draw2d::graphics * pgraphics,
   const ::point & pointDst,
   const ::size & size,
   ::draw2d::graphics * pdcSrc,
   const ::point & pointSrc,
   i32 iRadius);

   bool spread_set_color(
   ::draw2d::graphics * pgraphics,
   const ::point & pointDst,
   const ::size & size,
   ::draw2d::graphics * pdcSrc,
   const ::point & pointSrc,
   i32 iRadius,
   COLORREF cr);

   bool true_blend(::draw2d::graphics * pgraphics, const ::rect & rect, ::draw2d::graphics * pdcColorAlpha, const ::point & pointAlpha, ::image * pimageWork = nullptr, ::image * pimageWork2 = nullptr, ::image * pimageWork3 = nullptr);

   bool blur(::image * pimage, int iRadius);

   bool blur(::image * pimage, rect rect, i32 iRadius);

   void color_blend_24CC(
   byte * pbA,

   i32 x1,
   i32 y1,
   i32 w1,
   i32 cx,
   i32 cy,
   COLORREF cr,
   byte * pbC,

   i32 x3,
   i32 y3,
   i32 w3);


   bool color_blend(::draw2d::graphics * pgraphics, const ::rect & rect, ::draw2d::graphics * pdcColorAlpha, const ::point & pointAlpha, ::image * pimageWork = nullptr);

   bool color_blend(::draw2d::graphics * pgraphics, const ::rect & rect, ::draw2d::graphics * pdcColorAlpha, const ::point & pointAlpha, double dBlend);
   bool color_blend(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, ::draw2d::graphics * pdcColorAlpha, const ::point & pointAlpha, double dBlend);

   bool color_blend(::draw2d::graphics * pgraphics, i32 x, i32 y, i32 cx, i32 cy, COLORREF cr, BYTE bAlpha);
   bool color_blend(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, COLORREF cr, BYTE alpha);
   bool color_blend(::draw2d::graphics * pgraphics, const ::rect & rect, COLORREF cr, BYTE alpha);
   bool color_blend(::draw2d::graphics * pgraphics,   const ::rect64 & rect, COLORREF cr,   BYTE alpha);


   bool clip_color_blend(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, COLORREF cr, BYTE alpha);
   bool clip_color_blend(::draw2d::graphics * pgraphics, const ::rect & rect, COLORREF cr, BYTE alpha);

   /*
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, COLORREF cr, BYTE alpha, ::draw2d::region * prgnClip);
      bool clip_color_blend(::draw2d::graphics * pgraphics, const ::rect & rect, COLORREF cr, BYTE alpha, ::draw2d::region * prgnClip);
   */

   ::estatus trait(::image * pimage, ::i64 iTrait);

   static bool CreateBitmap(
   ::draw2d::graphics * pgraphics,
   ::draw2d::bitmap * pbitmapOld,
   ::draw2d::bitmap * pbitmap,
   BITMAP * pbmp,
   i32 cx,
   i32 cy);

   static bool CreateBitmap(
      ::draw2d::graphics * pgraphics,
   ::draw2d::graphics * pdcScreen,
   ::draw2d::bitmap * pbitmap,
   ::draw2d::bitmap * pbitmapOld,
   BITMAP * pbmp,
   i32 cx,
   i32 cy);

   void AlphaTextOut(::draw2d::graphics * pgraphics, i32 left, i32 top, const char * pcsz, i32 len, COLORREF cr, double dBlend);

   virtual bool _desk_to_image(::image* pimage);
   virtual bool _desk_has_image();
   virtual bool _image_to_desk(const ::image* pimage);

   /*

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rect & rect);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rect & rect);

      bool ClipSave(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rect & rect,
         ::draw2d::region * prgnClip);

      bool ClipRestore(
         ::draw2d::graphics * pgraphics,
         ::draw2d::bitmap * pbitmap,
         ::draw2d::bitmap * pbitmapOld,
         BITMAP * pbmp,
         const ::rect & rect,
         ::draw2d::region * prgnClip);

   */

//   bool GetDeviceContext24BitsCC(
//      ::draw2d::graphics *pdc,
//      BITMAP & bm,
//      BITMAPINFO & bmi,
//      memory & memomrystorage,
//      ::draw2d::bitmap * pbitmap,
//      const ::rect & rect,
//      i32 & iWidth,
//      UINT & uiStartScanLine,
//      UINT & uiScanLineCount,
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
//      COLORREF crTransparent);

   bool HueVRCP(::image * pimage, COLORREF crHue, double dCompress);

//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      ::draw2d::bitmap * pbitmap,
//      ::draw2d::bitmap * pbitmapMask,
//      const ::rect & rect,
//      COLORREF crTransparent);
//
//   bool GrayVRCP(
//      ::draw2d::graphics * pgraphics,
//      i32 x,
//      i32 y,
//      i32 cx,
//      i32 cy,
//      COLORREF crAlpha);

   bool change_hue(image_list * pilHue, image_list * pil, COLORREF crHue, double dCompress);
   bool color_blend(image_list * pilBlend, image_list * pil, COLORREF cr, BYTE bAlpha);
   bool color_blend(::image * pimage, COLORREF cr, BYTE bAlpha);

   bool BitmapBlend2(::draw2d::graphics * pdcDst, const ::point & point, const ::size & size, ::draw2d::graphics * pdcSrc, const ::point & pointSrc,
                     ::draw2d::graphics * pdcAlpha, // alpha information device (in alpha channel)
                     const ::point & pointAlpha);

   bool BitmapDivBlend(::draw2d::graphics * pdcDst, const ::point & point, const ::size & size, ::draw2d::graphics * pdcSrc, const ::point & pointSrc, BYTE bAlpha);

   bool bitmap_blend(::draw2d::graphics * pdcDst, const ::point & point, const ::size & size, ::draw2d::graphics * pdcSrc, const ::point & pointSrc, BYTE bAlpha);

   bool bitmap_blend(::draw2d::graphics * pdcDst, const ::point & point, const ::size & size, ::image * pimage, const ::point & pointSrc, BYTE bAlpha);

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
   BYTE bAlpha);

   virtual bool color_blend_3dRect(::draw2d::graphics * pgraphics, const ::rect & rect, COLORREF crTopLeft, BYTE bAlphaTopLeft, COLORREF crBottomRight, BYTE bAlphaBottomRight);

   virtual bool ColorInvert(::draw2d::graphics * pgraphics, i32 x, i32 y, i32 cx, i32 cy);


   inline ::estatus load_image(::image_pointer & pimage, ::memory_pointer pmemory)
   { 

      auto estatus = __construct(pimage);

      if (!estatus)
      {

         return estatus;

      }
   
      return load_image(pimage, pmemory); 
   
   }

   inline ::estatus load_image(::image_pointer & pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory)
   {

      auto estatus = __construct(pimage);

      if (!estatus)
      {

         return estatus;

      }

      return load_image(pimage, pframea, pmemory);

   }

   
   virtual ::estatus _load_image(::context * pcontext, ::image * pimage, const var & varFile, bool bSync, bool bCreateHelperMaps);


   virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory);
   virtual ::estatus save_image(memory & memory, const ::image * pimage, ::save_image * psaveimage);


   virtual ::estatus load_cursor(::draw2d::cursor * pcursor, ::file::path path, bool bSync, bool bCache = true);

   void EmbossedTextOut(
   ::draw2d::graphics *        pdc,
   i32                 x,
   i32                 y,
   const char *            pcsz,

   size_t                  cb,
   COLORREF                crText,
   COLORREF                crShadow,
   i32                 cx,
   i32                 cy);

   void GetMultiLineTextExtent(HDC hDC, string_array *pArray, LPSIZE pSize);

   void DrawMultiLineText(HDC hDC, string_array *pArray);


   ::image_pointer get_work_image();
   void free_work_image(::image * pimage);
   
   
   virtual ::estatus load_svg(::image * pimage, ::memory_pointer pmemory);

   virtual HCURSOR CreateAlphaCursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);
   virtual HCURSOR load_default_cursor(e_cursor ecursor);
   virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot);

   virtual WINBOOL window_set_mouse_cursor(oswindow window, HCURSOR hcursor);
   
   
};


