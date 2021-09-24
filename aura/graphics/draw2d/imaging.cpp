#include "framework.h"


#ifdef WINDOWS_DESKTOP

//void fastblur(::image * ppimg, i32 radius);

#elif defined(_UWP)
//#include <wincodec.h>
//#include <Shcore.h>

#endif

#ifdef ANDROID

#define _stricmp strcasecmp

#endif



#define AC_SRC_ALPHA                0x01


imaging::imaging()
{

   defer_create_mutex();

}


imaging::~imaging()
{


}


::e_status imaging::initialize(::object * pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


void imaging::embossed_text_out(
::draw2d::graphics *        pgraphics,
i32                 x,
i32                 y,
const char *            pcsz,

size_t                  cb,
::color::color                crText,
::color::color                crShadow,
i32                 cx,
i32                 cy)
{


   /* If text length is -1, use lstrlen to get the length
    ** of the text.
    */
   if(cb == -1)
      cb = strlen(pcsz);


   /* If the shadow or text color is -1, use the
    ** system color for that one.
    */

   //   ::color::color                crOld;
   //   ::u32                    uMode;
   SIZE_F64                   sizeText;
   ::rectangle_i32                  rectangleText;

   auto psession = get_session();

//   if(crShadow == (::color::color)-1)
//      crShadow = crButtonShadow;
//
//   if(crText == (::color::color)-1)
//      crText = psession->get_default_color(COLOR_BTNTEXT);

   /* setup the DC, saving off the old values
   */
   //uMode = pgraphics->SetBkMode(OPAQUE);
   //crOld = pgraphics->set_text_color(crShadow);

   /* draw the text at the desired offset using the
   ** shadow color, then again at the normal position
   ** using the text color.  This will the text an 'Embossed'
   ** or 'drop shadowed' look depending on what shadow color
   ** and offset are used.
   */
   sizeText = pgraphics->get_text_extent(string(pcsz,cb));

   rectangleText.left    = x;
   rectangleText.right   = ::i32 (x + cx + sizeText.cx);
   rectangleText.top     = y;
   rectangleText.bottom  = ::i32(y + cy + sizeText.cy);
   //ExtTextOut(hDC, x+cx, y+cy, ETO_OPAQUE, &rectangleText, psz, cb, nullptr);

   //pgraphics->SetBkMode(TRANSPARENT);
   //ExtTextOut(hDC, x-cx, y+cy, nullptr, &rectangleText, psz, cb, nullptr);

   //ExtTextOut(hDC, x-cx, y-cy, nullptr, &rectangleText, psz, cb, nullptr);

   //ExtTextOut(hDC, x+cx, y-cy, nullptr, &rectangleText, psz, cb, nullptr);

   //ExtTextOut(hDC, x+cx, y+cy, nullptr, &rectangleText, psz, cb, nullptr);

   pgraphics->ExtTextOut(x + cx,y + cy,0,nullptr,pcsz,(int)cb,nullptr);

   //pgraphics->SetBkMode(TRANSPARENT);
   //pgraphics->set_text_color(crText);
   if(!pgraphics->ExtTextOut(x,y,0,nullptr,pcsz,(int)cb,nullptr))

   {
      //      TRACE("Failed to ExtTextOut, get_last_error() -->%d\n", get_last_error());
   }

   /* restore the DC
   */
   //pgraphics->set_text_color(crOld);
   //pgraphics->SetBkMode(uMode);


}


//void imaging::GetMultiLineTextExtent(HDC hDC,string_array * pArray,LPSIZE32 pSize)
//
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   TEXTMETRICW tm;
//
//   GetTextMetricsW(hDC,&tm);
//
//   index nIndex;
//   ::count nSize;
//
//   nSize = pArray->get_size();
//   pSize->cx = 0;
//
//   ::size_i32 size;
//   for(nIndex = 0; nIndex < nSize; nIndex++)
//   {
//      const string &str = pArray->get_at(nIndex);
//      wstring wstr(str);
//      GetTextExtentPoint32W(hDC,wstr,(i32)wstr.get_length(),&size);
//      if(size.cx > pSize->cx)
//
//         pSize->cx = size.cx;
//
//   }
//   //   pSize->cy =
//
//   //      (tm.tmHeight +
//   //      tm.tmExternalLeading +
//   //      tm.tmInternalLeading) *
//   nSize;
//   pSize->cy = (::i32)((tm.tmHeight + tm.tmExternalLeading) * nSize);
//
//
//#else
//
//   __throw(todo);
//
//#endif
//
//}
//

//void imaging::DrawMultiLineText(HDC hDC,string_array * pArray)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   TEXTMETRICW tm;
//
//   GetTextMetricsW(hDC,&tm);
//
//   index nIndex;
//   ::count nSize;
//
//   nSize = pArray->get_size();
//
//   i32 yPos = 0;
//
//   for(nIndex = 0; nIndex < nSize; nIndex++)
//   {
//
//      const string &str = pArray->get_at(nIndex);
//      wstring wstr(str);
//      TextOutW(hDC,0,yPos,wstr,(i32)wstr.get_length());
//
//      yPos +=
//      tm.tmHeight +
//      tm.tmExternalLeading +
//      tm.tmInternalLeading;
//
//   }
//
//#else
//
//   __throw(todo);
//
//#endif
//
//}

//bool imaging::GrayVRCP(
//   ::draw2d::graphics * pgraphics,
//   i32 x,
//   i32 y,
//   i32 cx,
//   i32 cy,
//   ::color::color crAlpha)
//{
//   __UNREFERENCED_PARAMETER(pgraphics);
//   __UNREFERENCED_PARAMETER(x);
//   __UNREFERENCED_PARAMETER(y);
//   __UNREFERENCED_PARAMETER(cx);
//   __UNREFERENCED_PARAMETER(cy);
//   __UNREFERENCED_PARAMETER(crAlpha);
//   throw interface_only_exception();
//   ASSERT(false);
//
//   return 0;
//
//}
//
//bool imaging::GrayVRCP(
//   ::draw2d::graphics * pgraphics,
//   ::draw2d::bitmap * pitmap,

//   ::draw2d::bitmap * pitmapMask,

//   const ::rectangle_i32 & rectangle,
//   ::color::color crTransparent)
//{
//
//   return GrayVRCP(
//             pgraphics,
//             pitmap,

//             pitmapMask,

//             rectangle.left,
//             rectangle.top,
//             rectangle.right - rectangle.left,
//             rectangle.bottom - rectangle.top,
//             crTransparent);
//}

/*__pointer(::image_list) imaging::CreateGrayVRCPImageList(
::draw2d::graphics * pgraphics,
__pointer(::image_list) pilGray,
__pointer(::image_list) pilParam)
{
__pointer(::image_list) pil = pilGray;

pil->create(pilParam);

::draw2d::graphics_pointer spgraphics(e_create);

spgraphics->CreateCompatibleDC(pgraphics);

::image_list::info ii;

for(i32 i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
const ::rectangle_i32 & rectangle = ii.m_rectangle;
GrayVRCP(spgraphics->get_os_data(), ii.hbmImage, ii.hbmMask, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), rgb(192, 192, 192));
}
return pil;

}


bool imaging::CreateHueImageList(
::draw2d::graphics * pgraphics,
__pointer(::image_list) pilGray,
__pointer(::image_list) pilParam,
::color::color crHue,
double dCompress)
{
__pointer(::image_list) pil = pilGray;

if(!pil->create(pilParam))
return false;

::draw2d::graphics_pointer spgraphics(e_create);

spgraphics->CreateCompatibleDC(pgraphics);

::image_list::info ii;

for(i32 i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
const ::rectangle_i32 & rectangle = ii.m_rectangle;
HueVRCP(
spgraphics->get_os_data(),
ii.hbmImage,
rectangle.left,
rectangle.top,
rectangle.width(),
rectangle.height(),
crHue,
dCompress);
}
return true;

}*/



bool imaging::change_hue(image_list * pilHue, image_list * pil, const ::color::color& crHue,double dCompress)
{

   pilHue->copy_from(pil);

   HueVRCP(pilHue->m_pimage,crHue,dCompress);

   return true;

}




//
//bool imaging::color_blend(::image * pimage, const ::color::color& color32, byte bAlpha)
//{
//
//   try
//   {
//
//      pimage->unmap();
//
//      if (pimage->g() == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if (pimage->g()->get_os_data() == nullptr)
//      {
//
//         return false;
//
//      }
//
//      color_blend(pimage->g(), nullptr, pimage->size(), color32, bAlpha);
//
//      return true;
//
//   }
//   catch (...)
//   {
//
//      return false;
//
//   }
//
//}


/*
__pointer(::image_list) imaging::CreateGrayVRCPImageList(
::draw2d::graphics * pgraphics,
__pointer(::image_list) pilParam)
{
__pointer(::image_list) pil = new ::image_list();

pil->create(pilParam);

::draw2d::graphics_pointer spgraphics(e_create);

spgraphics->CreateCompatibleDC(pgraphics);

::image_list::info ii;

for(i32 i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
const ::rectangle_i32 & rectangle = ii.m_rectangle;
GrayVRCP(spgraphics->get_os_data(), ii.hbmImage, ii.hbmMask, rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), rgb(192, 192, 192));
}
return pil;

}

*/


//bool imaging::GrayVRCP(
//   ::draw2d::graphics * pgraphics,
//   ::draw2d::bitmap * pitmap,

//   ::draw2d::bitmap * pitmapMask,

//   i32 x,
//   i32 y,
//   i32 cx,
//   i32 cy,
//   ::color::color crAlpha)
//{
//
//   return false;
//
////   __UNREFERENCED_PARAMETER(crAlpha);
////   //::color::color cr3dface = psession->get_default_color(COLOR_3DFACE);
////
////#ifdef WINDOWS_DESKTOP
////
////   ::color::color cr3dshadow = psession->get_default_color(COLOR_3DSHADOW);
////
////#else
////
////   ::color::color cr3dshadow = argb(255,127,127,127);
////
////#endif
////
////   //byte uch3dfaceR = ::red(cr3dface);
////   //byte uch3dfaceG = ::green(cr3dface);
////   //byte uch3dfaceB = ::blue(cr3dface);
////   byte uch3dshadowR = ::red(cr3dshadow);
////   byte uch3dshadowG = ::green(cr3dshadow);
////   byte uch3dshadowB = ::blue(cr3dshadow);
////
////
////#ifdef WINDOWS_DESKTOP
////
////   ::color::color cr3dhighlight = psession->get_default_color(COLOR_3DHILIGHT);
////
////#else
////
////   ::color::color cr3dhighlight = argb(255,192,192,192);
////
////#endif
////
////
////   byte uch3dhighlightR = ::red(cr3dhighlight);
////   byte uch3dhighlightG = ::green(cr3dhighlight);
////   byte uch3dhighlightB = ::blue(cr3dhighlight);
////
////   const ::size_i32 & size = pitmap->get_size();

////
////   ::u32 cbLine = ((size.cx * 3 + 3) & ~3);
////   ::u32 cbImage = size.cy * cbLine;
////
////   ::u32 cbMask = size.cy * ((size.cx + 3) & ~3);
////
////
////   BITMAPINFO bmi;
////
////   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
////   bmi.bmiHeader.biWidth = size.cx;
////   bmi.bmiHeader.biHeight = - size.cy;
////   bmi.bmiHeader.biPlanes = 1;
////   bmi.bmiHeader.biBitCount = 24;
////   bmi.bmiHeader.biCompression = BI_RGB;
////   bmi.bmiHeader.biSizeImage = 0;
////   bmi.bmiHeader.biXPelsPerMeter = 1;
////   bmi.bmiHeader.biYPelsPerMeter = 1;
////   bmi.bmiHeader.biClrUsed = 0;
////   bmi.bmiHeader.biClrImportant = 0;
////
////   byte * pData = (byte *)malloc(cbImage);


////   byte * pShadow = (byte *)malloc(cbMask);


////   byte * pMask = (byte *)malloc(cbMask);


////   //byte * pShadow = pData;




////
////#ifdef WINDOWS_DESKTOP
////
////   ::u32 uScanLines = size.cy;
////
////
////   if(!GetDIBits(
////            (HDC)pgraphics->get_os_data(),
////            (HBITMAP)pitmap->get_os_data(),

////            0,
////            uiScanLines,
////            pData,


////            &bmi,
////            DIB_RGB_COLORS))
////   {
////      return false;
////   }
////
////#else
////
////   __throw(todo);
////
////#endif
////
////   const ::size_i32 & sizeMask = pitmapMask->get_size();

////
////   BITMAPINFO * pmiMask = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

////
////   pmiMask->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

////   pmiMask->bmiHeader.biWidth = sizeMask.cx;

////   pmiMask->bmiHeader.biHeight = - sizeMask.cy;

////   pmiMask->bmiHeader.biPlanes = 1;

////   pmiMask->bmiHeader.biBitCount = 8;

////   pmiMask->bmiHeader.biCompression = BI_RGB;

////   pmiMask->bmiHeader.biSizeImage = 0;

////   pmiMask->bmiHeader.biXPelsPerMeter = 1;

////   pmiMask->bmiHeader.biYPelsPerMeter = 1;

////   pmiMask->bmiHeader.biClrUsed = 0;

////   pmiMask->bmiHeader.biClrImportant = 0;

////
////#ifdef WINDOWS_DESKTOP
////
////   if(!GetDIBits((HDC)pgraphics->get_os_data(),
////                 (HBITMAP)pitmapMask->get_os_data(),

////                 0,uiScanLines,
////                 pMask,pmiMask,DIB_RGB_COLORS))



////   {
////      return false;
////   }
////
////#else
////
////   __throw(todo);
////
////#endif
////
////   //   ::memcpy_dup(pShadow, pData, cbImage);




////
////   byte * pBase = pData + cbLine * y + x * 3;




////   byte * pBaseShift = pData + cbLine * (y + 1) + (x + 1) * 3;




////   byte * pBaseShadow = pShadow + size.cx * y + x * 3;




////   byte * pBaseMask = pMask + size.cx * y + x;




////   byte * pBaseMaskShift = pMask + size.cx * (y + 1) + (x + 1);




////
////
////   byte br,bg,bb;
////
////   //   ::color::color crBtnFace = crButtonFace;
////   //   ::color::color crBtnShad = crButtonShadow;
////   //   ::color::color crWndBack = psession->get_default_color(COLOR_WINDOW);
////
////   //   byte bRBtnFace = ::red(crBtnFace);
////   //   byte bGBtnFace = ::green(crBtnFace);
////   //   byte bBBtnFace = ::blue(crBtnFace);
////
////   //   byte bRBtnShad = ::red(crBtnShad);
////   //   byte bGBtnShad = ::green(crBtnShad);
////   //   byte bBBtnShad = ::blue(crBtnShad);
////
////   //   byte bRWndBack = ::red(crWndBack);
////   //   byte bGWndBack = ::green(crWndBack);
////   //   byte bBWndBack = ::blue(crWndBack);
////
////   i32 i;
////   for(i = 0; i < cy; i ++)
////   {
////      byte * pLine = pBase + cbLine * i;




////      byte * pLineShadow = pBaseShadow + size.cx * i;




////      byte * pLineMask = pBaseMask + size.cy * i;




////      for(i32 j = 0; j < cx; j++)
////      {
////         bb = *pLine++;


////         bg = *pLine++;


////         br = *pLine++;


////         if((((br + bg + bb) / 3) < 192) &&
////               (*pLineMask == 0))


////         {
////            *pLineShadow++ = 1;


////         }
////         else
////         {
////            *pLineShadow++ = 0;


////         }
////         pLineMask++;


////      }
////   }
////
////
////
////
////
////
////
////
////
////
////
////   for(i = 0; i < cy; i ++)
////   {
////      byte * pLine = pBase + cbLine * i;




////      for(i32 j = 0; j < cx; j++)
////      {
////         *pLine++ = 0;


////         *pLine++ = 0;


////         *pLine++ = 0;


////      }
////   }
////
////
////
////
////
////
////
////
////
////
////   for(i = 0; i < cy; i ++)
////   {
////      byte * pLineMask = pBaseMask + size.cx * i;




////      for(i32 j = 0; j < cx; j++)
////      {
////         *pLineMask++ = 1;


////      }
////   }
////
////
////
////
////   i32 cyminus1 = cy - 1;
////   i32 cxminus1 = cx - 1;
////   byte b;
////
////   for(i = 0; i < cyminus1; i ++)
////   {
////      byte * pLine = pBaseShift + cbLine * i;




////      byte * pLineShadow = pBaseShadow + size.cx * i;




////      byte * pLineMask = pBaseMaskShift + size.cx * i;




////      for(i32 j = 0; j < cxminus1; j++)
////      {
////         b = *pLineShadow;


////         pLineShadow++;


////
////         if(b == 1)
////         {
////            *pLine++ = uch3dhighlightB;


////            *pLine++ = uch3dhighlightG;


////            *pLine++ = uch3dhighlightR;


////            *pLineMask++ = 0;


////         }
////         else
////         {
////            pLine += 3;


////            pLineMask++;


////         }
////      }
////   }
////
////
////
////
////
////
////
////   for(i = 0; i < cy; i ++)
////   {
////      byte * pLine = pBase + cbLine * i;




////      byte * pLineShadow = pBaseShadow + size.cx * i;




////      byte * pLineMask = pBaseMask + size.cx * i;




////      for(i32 j = 0; j < cx; j++)
////      {
////         b = *pLineShadow;


////         pLineShadow++;


////
////         if(b == 1)
////         {
////            *pLine++ = uch3dshadowB;


////            *pLine++ = uch3dshadowG;


////            *pLine++ = uch3dshadowR;


////            *pLineMask++ = 0;


////         }
////         else
////         {
////            pLine += 3;


////            pLineMask++;


////         }
////      }
////   }
////
////#ifdef WINDOWS_DESKTOP
////
////   if(!SetDIBits(
////            (HDC)pgraphics->get_os_data(),
////            (HBITMAP)pitmap->get_os_data(),

////            0,
////            uiScanLines,
////            pData,


////            &bmi,
////            DIB_RGB_COLORS))
////   {
////      return false;
////   }
////
////   if(!SetDIBits(
////            (HDC)pgraphics->get_os_data(),
////            (HBITMAP)pitmapMask->get_os_data(),

////            0,
////            uiScanLines,
////            pMask,


////            pmiMask,

////            DIB_RGB_COLORS))
////   {
////      return false;
////   }
////
////#else
////
////   __throw(todo);
////
////#endif
////
////   ::free(pShadow);


////   ::free(pData);


////   ::free(pMask);


////   ::free(pmiMask);

////
////   return true;
//
//}

//bool imaging::GetDeviceContext24BitsCC(
//   ::draw2d::graphics *pgraphics,
//   BITMAP & bm,
//   BITMAPINFO & bmi,
//   memory & memorystorage,
//   ::draw2d::bitmap * pitmap,

//   const rectangle_i32 & rectangleParam,
//   i32 &iWidthParam,
//   ::u32 & uiStartScanLineParam,
//   ::u32 & uiScanLineCountParam,
//   i32 & iLimitYParam)
//{
//   __UNREFERENCED_PARAMETER(pitmap);

//   ::rectangle_i32 rectangle(rectangleParam);
//
//   //   i32 x = rectangle.left;
//   i32 y = rectangle.top;
//   //   i32 cx = rectangle.width();
//   i32 cy = rectangle.height();
//
//   ::draw2d::bitmap_pointer spbmpTemp(this);
//   if(!spbmpTemp->CreateCompatibleBitmap(pgraphics,1,1))
//   {
//      return false;
//   }
//
//   ::draw2d::bitmap * pmpOld = pgraphics->set(spbmpTemp);

//
//   if(pmpOld != nullptr)

//   {
//      try
//      {
//#ifdef WINDOWS_DESKTOP
//         ::draw2d::bitmap * pmp = pmpOld;


//#endif
//
//         throw interface_only_exception();
//         /*         if(!pmp->GetObject(sizeof(bm), &bm))

//         {
//         pgraphics->set(pmpOld);

//         return false;
//         }*/
//
//         bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
//         bmi.bmiHeader.biWidth = bm.bmWidth ;
//         bmi.bmiHeader.biHeight = bm.bmHeight;
//         bmi.bmiHeader.biPlanes = 1;
//         bmi.bmiHeader.biBitCount = 24;
//         bmi.bmiHeader.biCompression = BI_RGB;
//         bmi.bmiHeader.biSizeImage = 0;
//         bmi.bmiHeader.biXPelsPerMeter = 0;
//         bmi.bmiHeader.biYPelsPerMeter = 0;
//         bmi.bmiHeader.biClrUsed = 0;
//         bmi.bmiHeader.biClrImportant = 0;
//         i32 iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
//         iWidthParam = iLineBytes;
//         try
//         {
//            memorystorage.set_size(iLineBytes * cy);
//         }
//         catch(memory_exception * pe)
//         {
//            delete pe;
//            __throw(::exception("integer_exception" + __str($1)));
//         }
//#ifdef WINDOWS_DESKTOP
//
//         LPVOID pv = memorystorage.get_data();

//#endif
//         //       ::point_i32 pointViewport = pgraphics->GetViewportOrg();
//
//         ::u32 uStartScanLine = maximum(0,bm.bmHeight - y - cy);
//         ::u32 uScanLines = cy + minimum(0,bm.bmHeight - y - cy);
//
//         uiStartScanLineParam = uiStartScanLine;
//         uiScanLineCountParam = uiScanLines;
//
//#ifdef WINDOWS_DESKTOP
//
//         if(!(iLimitYParam = GetDIBits
//                             (
//                                (HDC)pgraphics->get_os_data(),
//                                (HBITMAP)pmp->get_os_data(),

//                                uiStartScanLine,
//                                uiScanLines,
//                                pv,

//                                &bmi,
//                                DIB_RGB_COLORS
//                             )
//             ))
//         {
//            pgraphics->set(pmpOld);

//            return false;
//         }
//
//#else
//
//         __throw(todo);
//
//#endif
//
//      }
//      catch(i32)
//      {
//         //         ::u32 user = get_last_error();
//         pgraphics->set(pmpOld);

//         return false;
//      }
//      pgraphics->set(pmpOld);

//      return true;
//   }
//   else
//   {
//      pgraphics->set(pmpOld);

//      return false;
//   }
//}

/*bool imaging::GetDeviceContext24BitsAllCC(
::draw2d::graphics *pgraphics,
BITMAP & bm,
BITMAPINFO & bmi,
memory & memorystorage,
::draw2d::bitmap   ** ppbitmap,
RECTANGLE_I32 * prectangle,

i32 &iWidthParam,
::u32 & uiStartScanLineParam,
::u32 & uiScanLineCountParam,
i32 & iLimitYParam)
{

i32 x = 0;
i32 y = 0;
i32 cx = -1;
i32 cy = -1;

::draw2d::bitmap * pmpOld = pgraphics->get_current_bitmap();

if(pmpOld == nullptr)

{
return false;
}

::draw2d::bitmap spbmpTemp;
if(!spbmpTemp->CreateCompatibleBitmap(pgraphics, 1, 1))
{
return false;
}

if(pgraphics->set(spbmpTemp))
{
// pgraphics is a pointer to a memory device context
try
{
::draw2d::bitmap * pmp = pmpOld;



*ppbitmap = pmp;


// This is a memory device context
if(!pmp->GetObject(sizeof(bm), &bm))

__throw(::exception("integer_exception" + __str($1)));

cx = bm.bmWidth;
cy = bm.bmHeight;

bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
bmi.bmiHeader.biWidth = bm.bmWidth ;
bmi.bmiHeader.biHeight = -bm.bmHeight;
bmi.bmiHeader.biPlanes = 1;
bmi.bmiHeader.biBitCount = 24;
bmi.bmiHeader.biCompression = BI_RGB;
bmi.bmiHeader.biSizeImage = 0;
bmi.bmiHeader.biXPelsPerMeter = 0;
bmi.bmiHeader.biYPelsPerMeter = 0;
bmi.bmiHeader.biClrUsed = 0;
bmi.bmiHeader.biClrImportant = 0;
i32 iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
iWidthParam = iLineBytes;
try
{
memorystorage.set_size(iLineBytes * cy);
}
catch(memory_exception * pe)
{
delete pe;
__throw(::exception("integer_exception" + __str($1)));
}
LPVOID pv = memorystorage.get_data();

::point_i32 pointViewport = pgraphics->GetViewportOrg();

::u32 uStartScanLine = 0;
::u32 uScanLines = cy;

uiStartScanLineParam = uiStartScanLine;
uiScanLineCountParam = uiScanLines;

if(!(iLimitYParam = GetDIBits
(
(HDC)pgraphics->get_os_data(),
(HBITMAP) pmp->get_os_data(),

uiStartScanLine,
uiScanLines,
pv,

&bmi,
DIB_RGB_COLORS
)
))
__throw(::exception("integer_exception" + __str($1)));
}
catch(i32)
{
::u32 user = get_last_error();
pgraphics->set(pmpOld);

return false;
}
}
else
{
try
{
::draw2d::bitmap * pitmap = *ppbitmap;

// this is a display spgraphics

if(pitmap->m_hObject == nullptr)

{
pitmap->CreateBitmap(cx + 100, cy + 100, 1, 24, nullptr);

}
else
{
if(!pitmap->GetObject(sizeof(bm), &bm))

__throw(::exception("integer_exception" + __str($1)));
if(bm.bmWidth < cx ||
bm.bmHeight  < cy)
{
pitmap->delete_object();

pitmap->CreateBitmap(cx + 100, cy + 100, 1, 24, nullptr);

}
}

::draw2d::graphics_pointer graphicsMem(e_create);
graphicsMem->CreateCompatibleDC(pgraphics);
::draw2d::bitmap * pmpMemOld = graphicsMem->set(pitmap);


graphicsMem->BitBlt(
0, 0,
cx, cy,
pgraphics,
x, y,
SRCCOPY);
if(!pitmap->GetObject(sizeof(bm), &bm))

__throw(::exception("integer_exception" + __str($1)));
cx = bm.bmWidth;
cy = bm.bmHeight;


bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
bmi.bmiHeader.biWidth = bm.bmWidth ;
bmi.bmiHeader.biHeight = -bm.bmHeight;
bmi.bmiHeader.biPlanes = 1;
bmi.bmiHeader.biBitCount = 24;
bmi.bmiHeader.biCompression = BI_RGB;
bmi.bmiHeader.biSizeImage = 0;
bmi.bmiHeader.biXPelsPerMeter = 0;
bmi.bmiHeader.biYPelsPerMeter = 0;
bmi.bmiHeader.biClrUsed = 0;
bmi.bmiHeader.biClrImportant = 0;
i32 iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
iWidthParam = iLineBytes;
try
{
memorystorage.set_size(iLineBytes * cy);
}
catch(memory_exception * pe)
{
delete pe;
__throw(::exception("integer_exception" + __str($1)));
}

LPVOID pv = memorystorage.get_data();


::point_i32 pointViewport;
pointViewport = pgraphics->GetViewportOrg();
::u32 uStartScanLine = bm.bmHeight;

uiStartScanLineParam = uiStartScanLine;

//::u32 uStartScanLine = bm.bmHeight - y - cy;
::u32 uScanLines = cy;
uiScanLineCountParam = uiScanLines;
i32 xOffset = (x + pointViewport.x) * 3;
//if(!GetDIBits(dcAux.get_os_data(), bitmap, bm.bmHeight - cy, cy, pv, &bmi, DIB_RGB_COLORS))

//  __throw(::exception("integer_exception" + __str($1)));
i32 iLimitY = cy;
if(!(iLimitYParam =
GetDIBits(
graphicsMem->get_os_data(),
*pitmap,

uiStartScanLine,
uiScanLines,
pv,

&bmi,
DIB_RGB_COLORS)))
__throw(::exception("integer_exception" + __str($1)));
i32 iLimitX = cx;

if(bm.bmWidth - x - pointViewport.x < iLimitX)
{
iLimitX = bm.bmWidth - x - pointViewport.x;
}

graphicsMem->set(pmpMemOld);

graphicsMem->DeleteDC();
pgraphics->set(pmpOld);

return true;
}
catch(i32)
{
return false;
}
}

pgraphics->set(pmpOld);

return true;
}*/

void imaging::BitmapBlend24CC(
byte * pAParam,

i32 x1,
i32 y1,
i32 w1,
i32 cx,
i32 cy,
byte * pBParam,

i32 x2,
i32 y2,
i32 w2,
byte * pCParam,

i32 x3,
i32 y3,
i32 w3)
{
   i32 i,j;
   x1 *= 3;
   x2 *= 3;
   x3 *= 3;
   y1 *= w1;
   y2 *= w2;
   y3 *= w3;

   byte * pA1 = (byte *)pAParam + y1 + x1;

   byte * pB1 = (byte *)pBParam + y2 + x2;

   byte * pC1 = (byte *)pCParam + y3 + x3;


   //   byte dwA;
   for(i = 0; i < cy; i++)
   {

      byte * pA = (byte *)pA1 + (w1 * i);

      byte * pB = (byte *)pB1 + (w2 * i);

      byte * pC = (byte *)pC1 + (w3 * i);

      for(j = 0; j < cx; j++)
      {

         pA[0] = (byte)(((((u32)pA[0]) * ((u32)(255 - pC[0])) + (((u32)pB[0]) * ((u32)pC[0])))) / 255);

         pA[1] = (byte)(((((u32)pA[1]) * ((u32)(255 - pC[1])) + (((u32)pB[1]) * ((u32)pC[1])))) / 255);

         pA[2] = (byte)(((((u32)pA[2]) * ((u32)(255 - pC[2])) + (((u32)pB[2]) * ((u32)pC[2])))) / 255);

         pA+=3;

         pB+=3;

         pC+=3;


      }
   }

}


void imaging::BitmapBlend24CC(
byte * pDestParam,


i32 xDest,
i32 yDest,
i32 wDest,
i32 cx,
i32 cy,
byte * pSrcParam,


i32 xSrc,
i32 ySrc,
i32 wSrc,
byte bAlpha)
{
   i32 i,j;
   xDest *= 3;
   xSrc *= 3;
   yDest *= wDest;
   ySrc *= wSrc;

   //   i32 maxw = cx * 3;
   //   i32 cw = (maxw) & ~3;



   i32 iDestPadding = wDest - cx * 3;
   i32 iSrcPadding = wSrc - cx * 3;


   pDestParam = (byte *)     pDestParam + yDest + xDest;



   pSrcParam = (byte *)pSrcParam + ySrc + xSrc;




   //   byte bAlphaComplement = 255 - bAlpha;
   //   byte dwA;
   if(bAlpha == 0)
   {
   }
   if(bAlpha == 255)
   {
      for(i = 0; i < cy; i++)
      {
         byte * pDst = (byte *)pDestParam + (wDest * i);



         byte * pSrc = (byte *)pSrcParam + (wSrc * i);



         for(j = 0; j < cx; j++)
         {
            *pDst++ = *pSrc++;



            *pDst++ = *pSrc++;



            *pDst++ = *pSrc++;



         }
      }
   }
   else
   {
      byte * pDst = (byte *)pDestParam;



      byte * pSrc = (byte *)pSrcParam;



      for(i = 0; i < cy; i++)
      {

         for(j = 0; j < cx; j++)
         {
            pDst[0] = (byte)(((((i32)pSrc[0] - pDst[0]) * ((i32)(bAlpha))) / 256) + (i32)pDst[0]);





            pDst[1] = (byte)(((((i32)pSrc[1] - pDst[1]) * ((i32)(bAlpha))) / 256) + (i32)pDst[1]);





            pDst[2] = (byte)(((((i32)pSrc[2] - pDst[2]) * ((i32)(bAlpha))) / 256) + (i32)pDst[2]);





            pDst+=3;


            pSrc+=3;


         }
         pDst = (byte *)pDst + iDestPadding;



         pSrc = (byte *)pSrc + iSrcPadding;



      }
      /*      pushDest = (u16 *) pDestParam;



      pushSrc = (u16 *) pSrcParam;



      for(i = 0; i < cy; i++)
      {
      for(j = 0; j < cw; j+=2)
      {
      dwSrc = (*pushSrc & 0xff) | ((*lpushSrc & 0xff00) << 16);

      dwDest = (*pushDest & 0xff) | ((*lpushDest & 0xff00) << 16);

      dwDest = (((dwSrc - dwDest) * bAlpha) / 256) + dwDest;
      *pushDest = (dwDest & 0xff) | ((dwDest & 0x00ff0000) >> 16);

      pushSrc++;

      pushDest++;

      }
      byte * pDst = (byte *) lpushDest;


      byte * pSrc = (byte *) lpushSrc;


      for(;j < maxw; j++)
      {
      *pDst++ = (byte) (((u32) (*pSrc++ - *pDst) * ((u32) (bAlpha))) / 256) + *pDst;







      }
      pDst = (byte *) pDestParam + iDestPadding;




      pSrc = (byte *) pSrcParam + iSrcPadding;




      }*/
   }

}



bool imaging::BitmapDivBlend(
   ::draw2d::graphics * pdcDst, // destination device
   const ::point_i32 & pointDst,
   const ::size_i32 & size,
   ::draw2d::graphics * pdcSrc, // source device
   const ::point_i32 & pointSrc,
   byte bAlpha)
{

   ::image_pointer pimage;

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return false;

   }

   estatus = pimage->create(size);

   if (!estatus)
   {

      return false;

   }

   {

      image_source imagesource(pdcSrc);

      rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);
      
      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimage->draw(imagedrawing);

   }

   pimage->DivideRGB(bAlpha);

   {

      image_source imagesource(pimage, { pointSrc, size });

      image_drawing_options imagedrawingoptions(::rectangle_f64(pointDst, size));

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      return pdcDst->draw(imagedrawing);

   }

}


//bool imaging::bitmap_blend(
//::draw2d::graphics * pdcDst, // destination device
//const ::point_i32 & pointDst,
//const ::size_i32 & size,
//::draw2d::graphics * pdcSrc, // source device
//const ::point_i32 & pointSrc,
//byte bAlpha)
//{
//
//   return pdcDst->alpha_blend(rectangle_f64(pointDst, size), pdcSrc, pointSrc, bAlpha / 255.0);
//
//}
//
//
//bool imaging::bitmap_blend(::draw2d::graphics * pdcDst,
//                           const ::point_i32 & pointDst,
//                           const ::size_i32 & size,
//                           ::image * pimage,
//                           const ::point_i32 & pointSrc,
//                           byte bAlpha)
//{
//
//   return pdcDst->alpha_blend(::rectangle_f64(pointDst, size), pimage, pointSrc, bAlpha / 255.0);
//
//}
//

bool imaging::ColorInvert(::draw2d::graphics * pgraphics,i32 x,i32 y,i32 cx,i32 cy)
{


   if (cx <= 0 || cy <= 0)
   {

      return true;

   }

   return false;

   //    single_lock synchronouslock(&m_csMem, true);

   /*i32 iOriginalMapMode ;

   ::draw2d::bitmap_pointer spbmpTemp(this);

   ::draw2d::bitmap_pointer bitmapA(this);

   iOriginalMapMode = pgraphics->GetMapMode();
   pgraphics->SetMapMode(MM_TEXT);
   if(!spbmpTemp->CreateCompatibleBitmap(pgraphics, 1, 1))
   {
   pgraphics->SetMapMode(iOriginalMapMode);
   return false;
   }

   if(!pgraphics->set(spbmpTemp))
   {
   try
   {
   // this is a display spgraphics

   if(bitmapA->get_os_data() == nullptr)
   {
   bitmapA->CreateBitmap(cx + 100, cy + 100, 1, 24, nullptr);
   }
   else
   {
   BITMAP bm;
   if(!bitmapA->GetObject(sizeof(bm), &bm))
   __throw(::exception("integer_exception" + __str($1)));
   if(bm.bmWidth < cx ||
   bm.bmHeight  < cy)
   {
   bitmapA->CreateBitmap(cx + 100, cy + 100, 1, 24, nullptr);
   }
   }

   ::draw2d::graphics_pointer graphicsMem(e_create);
   graphicsMem->CreateCompatibleDC(pgraphics);
   ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapA);

   graphicsMem->BitBlt(
   0, 0,
   cx, cy,
   pgraphics,
   x, y,
   SRCCOPY);
   BITMAP bm;
   if(!bitmapA->GetObject(sizeof(bm), &bm))
   __throw(::exception("integer_exception" + __str($1)));

   memory memstorageA;


   BITMAPINFO bmi;
   bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
   bmi.bmiHeader.biWidth = bm.bmWidth ;
   bmi.bmiHeader.biHeight = -bm.bmHeight;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 24;
   bmi.bmiHeader.biCompression = BI_RGB;
   bmi.bmiHeader.biSizeImage = 0;
   bmi.bmiHeader.biXPelsPerMeter = 0;
   bmi.bmiHeader.biYPelsPerMeter = 0;
   bmi.bmiHeader.biClrUsed = 0;
   bmi.bmiHeader.biClrImportant = 0;
   i32 iLineBytes =  (bm.bmWidthBytes + 3) & ~3;
   try
   {
   memstorageA.set_size(iLineBytes * cy);
   }
   catch(memory_exception * pe)
   {
   delete pe;
   __throw(::exception("integer_exception" + __str($1)));
   }

   LPVOID pv = memstorageA.get_data();


   ::point_i32 pointViewport;
   pointViewport = pgraphics->GetViewportOrg();
   ::u32 uStartScanLine = bm.bmHeight - y - cy - pointViewport.y;
   //::u32 uStartScanLine = bm.bmHeight - y - cy;
   ::u32 uScanLines = cy;
   i32 xOffset = (x + pointViewport.x) * 3;
   //if(!GetDIBits(dcAux.get_os_data(), bitmapA, bm.bmHeight - cy, cy, pv, &bmi, DIB_RGB_COLORS))

   //  __throw(::exception("integer_exception" + __str($1)));
   i32 iLimitY = cy;
   if(!(iLimitY =
   GetDIBits(
   (HDC)graphicsMem->get_os_data(),
   (HBITMAP)bitmapA->get_os_data(),
   uiStartScanLine,
   uiScanLines,
   pv,

   &bmi,
   DIB_RGB_COLORS)))
   return false;
   i32 iLimitX = cx;

   if(bm.bmWidth - x - pointViewport.x < iLimitX)
   {
   iLimitX = bm.bmWidth - x - pointViewport.x;
   }

   byte * p;


   i32 i, j;
   for(i = 0; i < iLimitY; i++)
   {
   p = (byte *) lpv + (iLineBytes * i) + xOffset;


   for(j = 0; j < iLimitX; j++)
   {
   *p++ = (byte) 255 - *p;




   *p++ = (byte) 255 - *p;




   *p++ = (byte) 255 - *p;




   }
   }
   if(!SetDIBits(
   (HDC)graphicsMem->get_os_data(),
   (HBITMAP)bitmapA->get_os_data(),
   uiStartScanLine,
   uiScanLines,
   pv,

   &bmi,
   DIB_RGB_COLORS))
   __throw(::exception("integer_exception" + __str($1)));
   pgraphics->BitBlt(x, y, cx, cy, graphicsMem, 0, 0);
   graphicsMem->set(pmpMemOld);

   graphicsMem->DeleteDC();
   pgraphics->SetMapMode(iOriginalMapMode);
   return true;
   }
   catch(i32)
   {
   pgraphics->SetMapMode(iOriginalMapMode);
   return false;
   }
   }
   else
   {
   try
   {

   // This is a memory device context
   BITMAP bm;
   if(!pmp->GetObject(sizeof(bm), &bm))

   __throw(::exception("integer_exception" + __str($1)));

   BITMAPINFO bmi;
   bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
   bmi.bmiHeader.biWidth = bm.bmWidth ;
   bmi.bmiHeader.biHeight = -bm.bmHeight;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 24;
   bmi.bmiHeader.biCompression = BI_RGB;
   bmi.bmiHeader.biSizeImage = 0;
   bmi.bmiHeader.biXPelsPerMeter = 0;
   bmi.bmiHeader.biYPelsPerMeter = 0;
   bmi.bmiHeader.biClrUsed = 0;
   bmi.bmiHeader.biClrImportant = 0;
   i32 iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;

   memory memstorageA;
   try
   {
   memstorageA.set_size(iLineBytes * cy);
   }
   catch(memory_exception * pe)
   {
   delete pe;
   __throw(::exception("integer_exception" + __str($1)));
   }
   LPVOID pv = memstorageA.get_data();

   ::point_i32 pointViewport = pgraphics->GetViewportOrg();
   ::u32 uStartScanLine = bm.bmHeight - y - cy - pointViewport.y;
   //::u32 uStartScanLine = bm.bmHeight - y - cy;
   ::u32 uScanLines = cy;
   i32 xOffset = (x + pointViewport.x) * 3;


   //i32 xOffset = (x) * 3;
   i32 iLimitY = cy;
   if(!(iLimitY =
   GetDIBits(
   (HDC)pgraphics->get_os_data(),
   (HBITMAP) pmp->get_os_data(),

   uiStartScanLine,
   uiScanLines,
   pv,

   &bmi,
   DIB_RGB_COLORS)))
   __throw(::exception("integer_exception" + __str($1)));
   i32 iLimitX = cx;


   if(bm.bmWidth - x - pointViewport.x < iLimitX)
   {
   iLimitX = bm.bmWidth - x - pointViewport.x;
   }

   byte * p;


   i32 i, j;
   for(i = 0; i < iLimitY; i++)
   {
   p = (byte *) lpv + (iLineBytes * i) + xOffset;


   if(p < lpv)


   continue;
   for(j = 0; j < iLimitX; j++)
   {
   *p++ = (byte) 255 - *p ;




   *p++ = (byte) 255 - *p;




   *p++ = (byte) 255 - *p;




   }
   }

   if(!SetDIBits((HDC)pgraphics->get_os_data(),
   (HBITMAP) pmp->get_os_data(),

   uiStartScanLine, uiScanLines,
   pv, &bmi, DIB_RGB_COLORS))

   __throw(::exception("integer_exception" + __str($1)));
   }
   catch(i32)
   {
   pgraphics->SetMapMode(iOriginalMapMode);
   return false;
   }
   }
   pgraphics->SetMapMode(iOriginalMapMode);
   return true;*/
}

/*bool imaging::allocate(i32 iSize)
{
if(iSize > m_iSize)
{
m_lpVoid = malloc(iSize);
if(m_lpVoid == nullptr)
{
return false;
}
else
{
m_iSize = iSize;
}
}
return true;

}*/

//   void imaging::SaveJpeg(const ::string & pcszFile,::draw2d::bitmap_pointer pitmap)


//   {
//
//#ifdef _UWP
//
//      __throw(todo);
//
//#else
//      FIBITMAP * fi= HBITMAPtoFI(pitmap);

//      fi = FreeImage_ConvertTo24Bits(fi);
//      if(FreeImage_Save(FIF_JPEG,fi,pcszFile,JPEG_QUALITYBAD))

//      {
//         //
//      }
//      FreeImage_Unload(fi);
//#endif
//#endif
//   }
//
//   void imaging::SavePng(const ::string & pcszFile,::draw2d::bitmap_pointer pitmap)


//   {
//
//#ifdef _UWP
//
//      __throw(todo);
//
//#else
//      FIBITMAP * fi= HBITMAPtoFI(pitmap);

//      if(FreeImage_Save(FIF_PNG,fi,pcszFile,0))

//      {
//         //
//      }
//      FreeImage_Unload(fi);
//#endif
//#endif
//
//   }



//   ::draw2d::bitmap_pointer imaging::LoadImageSync(const ::string & pcszImageFilePath,::aura::application * papp)

//   {
//#ifdef AXIS_FREEIMAGE
//      FIBITMAP * pfi = imaging::LoadImageFile(pcszImageFilePath,papp);

//
//      if(pfi == nullptr)
//         return nullptr;
//
//      return FItoHBITMAP(pfi,true);
//#endif
//      return nullptr;
//   }




bool imaging::clip_color_blend(::draw2d::graphics * pgraphics, const rectangle_i32 & rectangleParam, ::color32_t color32, byte alpha)
{

   ::rectangle_i32 rectangle(rectangleParam);

   return clip_color_blend(
          pgraphics,
          rectangle.origin(),
          rectangle.size(),
          color32,
          alpha);
}


bool imaging::clip_color_blend(::draw2d::graphics * pgraphics,const ::point_i32 & point,const ::size_i32 & size,::color32_t color32,byte bA)
{

   pgraphics->fill_rectangle(rectangle_i32(size), argb(bA,colorref_get_r_value(color32),colorref_get_g_value(color32),colorref_get_b_value(color32)));

   return true;

}


::e_status imaging::trait(::image * pimage, ::i64 iTrait)
{

   return pimage->transform((enum_image)iTrait);

}


//bool imaging::color_blend(::draw2d::graphics * pgraphics, const ::rectangle_i64 & rectangle, ::color32_t color32, byte alpha)
//{
//
//   return color_blend(pgraphics,(const ::rectangle_i32 &)rectangle,color32,alpha);
//
//}


//bool imaging::color_blend(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, ::color32_t color32, byte alpha)
//{
//
//   return color_blend(pgraphics, rectangle.origin(), rectangle.size(), color32, alpha);
//
//}


//bool imaging::color_blend(::draw2d::graphics * pgraphics,i32 x,i32 y,i32 cx,i32 cy,::color32_t color32,byte bA)
//{
//
//   return color_blend(pgraphics,point_i32(x,y),size_i32(cx,cy),color32,bA);
//
//}


//bool imaging::color_blend(::draw2d::graphics * pgraphics,const ::point_i32 & point,const ::size_i32 & size,::color32_t color32,byte bA)
//{
//
//   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//   pgraphics->fill_rectangle(rectangle_i32(point, size), (color32 & 0x00ffffff) | (bA << 24));
//
//   return true;
//
//}


bool imaging::CreateBitmap(::draw2d::graphics * pgraphics, ::draw2d::graphics * pdcScreen, ::draw2d::bitmap * pbitmap, ::draw2d::bitmap * pbitmapOld, i32 cx, i32 cy)
{
   
   i32 cxout = cx;

   i32 cyout = cy;

   pgraphics->set(pbitmapOld);

   bool bCreate = true;

   if(pbitmap->get_os_data() != nullptr)
   {

      const ::size_i32 & size = pbitmap->get_size();

      if(size.cx >= cx && size.cy >= cy)
      {

         bCreate = false;

      }

   }

   if(bCreate)
   {

      if(!pbitmap->CreateCompatibleBitmap(pdcScreen,cxout,cyout))
      {

         return false;

      }

   }

   if(!pgraphics->set(pbitmap))
   {

      if(!pbitmap->CreateCompatibleBitmap(pdcScreen, cxout, cyout))
      {

         return false;

      }

      if(!pgraphics->set(pbitmap))
      {

         return false;

      }

   }

   if(bCreate)
   {

      pgraphics->fill_rectangle(rectangle_i32(0,0,cxout,cyout), 0);

   }

   return true;

}


bool imaging::CreateBitmap(::draw2d::graphics *pgraphics,::draw2d::bitmap * pitmapOld,::draw2d::bitmap *pitmap,i32 cx,i32 cy)
{

   i32 cxout = cx;

   i32 cyout = cy;

   pgraphics->set(pitmapOld);

   bool bCreate = true;

   if(pitmap->get_os_data())
   {

      const ::size_i32 & size = pitmap->get_size();

      if(size.cx >= cx && size.cy >= cy)
      {

         bCreate = false;

      }

   }

   if(bCreate)
   {

      if(!pitmap->CreateCompatibleBitmap(pgraphics,cxout,cyout))
      {

         return false;

      }

   }

   if(!pgraphics->set(pitmap))
   {

      if(!pitmap->CreateCompatibleBitmap(pgraphics,cxout,cyout))
      {

         return false;

      }

      if(!pgraphics->set(pitmap))
      {

         return false;

      }

   }

   if(bCreate)
   {

      ::color::color color(255, 196, 255);

      pgraphics->fill_rectangle(rectangle_i32(0,0,cxout,cyout), color);

   }

   return true;

}


bool imaging::blur(::image * pimage, i32 iRadius)
{

   if (!pimage->is_ok())
   {

      return false;

   }

   ::draw2d::fastblur f;

   f.blur(pimage, iRadius);

   return true;

}


bool imaging::blur(::image * pimage, rectangle_i32 rectangle, i32 iRadius)
{

   if (!pimage->is_ok())
   {

      return false;

   }

   ::draw2d::fastblur fastblur;

   if (!fastblur.initialize(rectangle.size(), abs(iRadius)))
      return false;

   {

      pixmap_lock lock(pimage, rectangle);

      fastblur.blur(pimage, iRadius);

   }

   return true;

}


void imaging::blur_32CC(::image * pimageDst, ::image * pimageSrc,i32 iRadius)
{
   i32 iFilterWidth = iRadius * 2 + 1;
   i32 iFilterHeight = iRadius * 2 + 1;
   i32 divisor = iFilterWidth * iFilterHeight;
   byte *pSource;


   byte *pDestination;


   byte *pSource1;


   byte *pSource2;


   byte *pFilter;

   byte * pFilterData = new byte[iFilterHeight *iFilterWidth];
   __memset(pFilterData,1,iFilterHeight * iFilterWidth);

   byte * pSrc = (byte *)pimageSrc->get_data();


   byte * pDst = (byte *)pimageDst->get_data();


   i32 cx = pimageSrc->width();
   i32 cy = pimageSrc->height();
   //i32 wSrc = cx * 4;
   //i32 wDest = cx * 4;
   i32 wSrc = pimageSrc->scan_size();
   i32 wDest = pimageDst->scan_size();
   i32 maxx1 = cx;
   i32 maxy1 = cy;
   //   i32 maxy2 = cy - iFilterWidth;
   //   i32 maxy3 = cy - iFilterWidth / 2;
   i32 max3x1 = maxx1 * 4;
   //   i32 max3x2 = (maxx1 - iFilterHeight) * 4;
   //   i32 max3x3 = (maxx1 - iFilterHeight / 2) * 4;
   //i32 bm3Width = (cy * 3 + 3) & ~0x3L;
   //   i32 w = cx * 3;
   //   ::memcpy_dup(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   ::memcpy_dup(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(i32 y = 0; y < cy; y++)
   {
   pSource = pSrc + wSrc * y;



   pDestination = pDst + wDest * y;




   for(i32 x = 0; x < w; x++)
   {
   *pDestination = *pSource;




   pDestination++;


   pSource++;


   }
   }*/
   u32 dwR;
   u32 dwG;
   u32 dwB;
   u32 dwA;

   i32 iFilterXBegin;
   i32 iFilterXEnd;
   i32 iFilterYBegin;
   i32 iFilterYEnd;

   i32 yLowerBound[4];
   i32 yUpperBound[4];
   i32 xLowerBound[4];
   i32 xUpperBound[4];

   // top
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterWidth / 2;
   xLowerBound[0] = 0;
   xUpperBound[0] = max3x1;

   // left
   yLowerBound[1] = iFilterWidth / 2;
   yUpperBound[1] = maxy1 - iFilterWidth / 2;
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterWidth / 2;

   // right
   yLowerBound[2] = iFilterWidth / 2;
   yUpperBound[2] = maxy1 - iFilterWidth / 2;
   xLowerBound[2] = max3x1 - iFilterWidth / 2;
   xUpperBound[2] = max3x1;

   // bottom
   yLowerBound[3] = maxy1 - iFilterWidth / 2;
   yUpperBound[3] = maxy1;
   xLowerBound[3] = 0;
   xUpperBound[3] = max3x1;

   /*   for(i32 i = 0; i < 4; i++)
   {
   i32 yL = yLowerBound[i];
   i32 yU = yUpperBound[i];
   i32 xL = xLowerBound[i];
   i32 xU = xUpperBound[i];
   for(i32 y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   pSource = pSrc + (wSrc * maximum((y1 - iFilterWidth / 2), 0));



   pDestination = pDst + (wDest  * y1);




   for(i32 x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   pSource1 = pSource + ((maximum(x1 - iFilterWidth / 2 * 3, 0)));




   pFilter = pFilter;

   //            pConv = pConv;


   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(i32 y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(i32 x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *pSource2++ * *lpFilter;


   dwG += *pSource2++ * *lpFilter;


   dwB += *pSource2++ * *lpFilter++;



   }
   }
   pDestination_1 = pDestination + x1;



   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   pDestination_1[0] = maximum(0, minimum(dwR, 255));


   pDestination_1[1] = maximum(0, minimum(dwG, 255));


   pDestination_1[2] = minimum(0, minimum(dwB, 255));


   }
   else
   {
   pDestination_1[0] = dwR / divisor;


   pDestination_1[1] = dwG / divisor;


   pDestination_1[2] = dwB / divisor;


   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   i32 iFilterHalfWidth = iFilterWidth / 2;
   i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   i32 yL = iFilterHalfWidth;
   i32 yU = maxy1 - iFilterHalfWidth;
   i32 xL = iFilterHalfWidthBytes;
   i32 xU = max3x1 - iFilterHalfWidthBytes;


   i32 y1 = yL;
   i32 y2 = yL - iFilterHalfWidth;
   i32 x1;
   i32 x2;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

   for(; y1 < yU;)
   {
      pSource = pSrc + (wSrc * y2);




      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      pDestination = pDst + (wDest  * y1) + x1;



      for(; x1 < xU;)
      {
         pSource1 = pSource + x2;



         pFilter = pFilterData;


         dwR = 0;
         dwG = 0;
         dwB = 0;
         dwA = 0;
         for(i32 yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            pSource2 = pSource1 + (wSrc * yFilter);



            for(i32 xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwR += *pSource2++ * *pFilter;


               dwG += *pSource2++ * *pFilter;


               dwB += *pSource2++ * *pFilter;


               dwA += *pSource2++ * *pFilter;



            }
         }


         *pDestination++ = (uchar)(dwR / divisor);


         *pDestination++ = (uchar)(dwG / divisor);


         *pDestination++ = (uchar)(dwB / divisor);


         *pDestination++ = (uchar)(dwA / divisor);


         x1 += 3;
         x2 += 3;
      }
      y1++;
      y2++;
   }

   delete[] pFilterData;

}


void imaging::blur_32CC_r2(::image * pimageDst, ::image * pimageSrc)
{

   byte * pSrc = (byte *)pimageSrc->get_data();


   byte * pDst = (byte *)pimageDst->get_data();



   i32 cx = pimageSrc->width();
   i32 cy = pimageSrc->height();
   //i32 wSrc = cx * 4;
   //i32 wDest = cx * 4;
   i32 wSrc = pimageSrc->scan_size();
   i32 wDest = pimageDst->scan_size();

   byte *pSource;


   byte *pDestination;


   byte *pSource1;


   byte *pSource2[5];




   if(cx <= 0)
      return;
   if(cy <= 0)
      return;

   i32 maxx1 = cx;
   i32 maxy1 = cy;
   //   i32 maxy2 = cy - 5;
   //   i32 maxy3 = cy - 2;
   i32 max3x1 = maxx1 * 4;
   //   i32 max3x2 = (maxx1 - 5) * 4;
   ///   i32 max3x3 = (maxx1 - 2) * 4;
   //   i32 w = cx * 3;
   u32 dwR;
   u32 dwG;
   u32 dwB;
   u32 dwA;

   i32 yL = 2;
   i32 yU = maxy1 - 2;
   i32 xL = 8;
   i32 xU = max3x1 - 8;


   i32 y1 = 2;
   i32 y2 = yL - 2;
   i32 x1;
   i32 x2;

   for(; y1 < yU;)
   {
      pSource = pSrc + (wSrc * y2);




      x1 = xL;
      x2 = xL - 8;
      pDestination = pDst + (wDest  * y1) + x1;




      for(; x1 < xU;)
      {
         pSource1 = pSource + x2;




         dwR = 0;
         dwG = 0;
         dwB = 0;
         dwA = 0;
         pSource2[0] = pSource1;


         pSource2[1] = pSource1 + wSrc;


         pSource2[2] = pSource1 + wSrc * 2;


         pSource2[3] = pSource1 + wSrc * 3;


         pSource2[4] = pSource1 + wSrc * 4;



         // red
         pDestination[0] =


         (pSource2[0][0] + pSource2[0][4] + pSource2[0][8] + pSource2[0][12] + pSource2[0][16]










          + pSource2[1][0] + pSource2[1][4] + pSource2[1][8] + pSource2[1][12] + pSource2[1][16]









          + pSource2[2][0] + pSource2[2][4] + pSource2[2][8] + pSource2[2][12] + pSource2[2][16]










          + pSource2[3][0] + pSource2[3][4] + pSource2[3][8] + pSource2[3][12] + pSource2[3][16]










          + pSource2[4][0] + pSource2[4][4] + pSource2[4][8] + pSource2[4][12] + pSource2[4][16]










         ) / 25;

         // green
         pDestination[1] =


         (pSource2[0][1] + pSource2[0][5] + pSource2[0][9] + pSource2[0][13] + pSource2[0][17]










          + pSource2[1][1] + pSource2[1][5] + pSource2[1][9] + pSource2[1][13] + pSource2[1][17]










          + pSource2[2][1] + pSource2[2][5] + pSource2[2][9] + pSource2[2][13] + pSource2[2][17]










          + pSource2[3][1] + pSource2[3][5] + pSource2[3][9] + pSource2[3][13] + pSource2[3][17]










          + pSource2[4][1] + pSource2[4][5] + pSource2[4][9] + pSource2[4][13] + pSource2[4][17]










         ) / 25;

         // blue
         pDestination[2] =


         (pSource2[0][2] + pSource2[0][6] + pSource2[0][10] + pSource2[0][14] + pSource2[0][18]










          + pSource2[1][2] + pSource2[1][6] + pSource2[1][10] + pSource2[1][14] + pSource2[1][18]










          + pSource2[2][2] + pSource2[2][6] + pSource2[2][10] + pSource2[2][14] + pSource2[2][18]










          + pSource2[3][2] + pSource2[3][6] + pSource2[3][10] + pSource2[3][14] + pSource2[3][18]










          + pSource2[4][2] + pSource2[4][6] + pSource2[4][10] + pSource2[4][14] + pSource2[4][18]










         ) / 25;

         // alpha
         pDestination[3] =


         (pSource2[0][3] + pSource2[0][7] + pSource2[0][11] + pSource2[0][15] + pSource2[0][19]










          + pSource2[1][3] + pSource2[1][7] + pSource2[1][11] + pSource2[1][15] + pSource2[1][19]










          + pSource2[2][3] + pSource2[2][7] + pSource2[2][11] + pSource2[2][15] + pSource2[2][19]










          + pSource2[3][3] + pSource2[3][7] + pSource2[3][11] + pSource2[3][15] + pSource2[3][19]










          + pSource2[4][3] + pSource2[4][7] + pSource2[4][11] + pSource2[4][15] + pSource2[4][19]










         ) / 25;

         pDestination += 4;


         x1 += 4;
         x2 += 4;
      }
      y1++;
      y2++;
   }

}


bool imaging::channel_gray_blur(::draw2d::graphics *pdcDst,const ::point_i32 & pointDst,const ::size_i32 & size,::draw2d::graphics * pdcSrc,const ::point_i32 & pointSrc,i32 iChannel,i32 iRadius)
{

   if (size.cx <= 0 || size.cy <= 0)
   {

      return true;

   }

   ::image_pointer pimageDst = m_pcontext->context_image()->create_image(size);

   if (!pimageDst)
   {

      return false;

   }

   ::image_pointer pimageSrc = m_pcontext->context_image()->create_image(size);

   if (!pimageSrc)
   {

      return false;

   }

   pimageSrc->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   image_source imagesource(pdcSrc, ::rectangle_f64(pointSrc, size));

   rectangle_f64 rectangle(size);

   image_drawing_options imagedrawingoptions(rectangle);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   if (!pdcSrc->draw(imagedrawing))
   {

      return false;

   }

   if(!channel_gray_blur_32CC(
         pimageDst,
         pimageSrc,
         iChannel,
         iRadius))
      return false;

   {

      image_source imagesource(pimageDst);

      rectangle_f64 rectangle(pointDst, size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pdcDst->draw(imagedrawing))
      {

         return false;

      }

   }

   return true;

}


bool imaging::channel_alpha_gray_blur(::draw2d::graphics * pdcDst, const ::point_i32 & pointDst, const ::size_i32 & size, ::draw2d::graphics * pdcSrc, const ::point_i32 & pointSrc, i32 iChannel, i32 iRadius)
{

   if (size.area() <= 0)
   {

      return true;

   }

   ::image_pointer pimageDst = m_pcontext->context_image()->create_image(size);

   if (!pimageDst)
   {

      return false;

   }

   ::image_pointer pimageSrc = m_pcontext->context_image()->create_image(size);

   if (!pimageSrc)
   {

      return false;

   }

   pimageSrc->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   {

      image_source imagesource(pdcSrc, ::rectangle_f64(pointSrc, size));

      ::rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pimageSrc->g()->draw(imagedrawing))
      {

         return false;

      }

   }

   if (!channel_alpha_gray_blur_32CC(
      pimageDst,
      pimageSrc,
      iChannel,
      iRadius))
      return false;

   {

      image_source imagesource(pimageDst);

      rectangle_f64 rectangle(pointDst, size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pdcDst->draw(imagedrawing))
      {

         return false;

      }

   }

   return true;

}


bool imaging::channel_gray_blur_32CC(::image * pimageDst, ::image * pimageSrc,
                                     i32 iChannel,i32 iRadius)
{

   if(iRadius <= 0)
      return true;

   i32 cx = pimageDst->width();
   i32 cy = pimageDst->height();

   if(cx != pimageSrc->width()
         || cy != pimageSrc->height())
      return false;

   byte * pDst = (byte *)pimageDst->get_data();


   byte * pSrc = (byte *)pimageSrc->get_data();



   //i32 wSrc = cx * 4;
   //i32 wDst = cx * 4;
   i32 wSrc = pimageSrc->scan_size();
   i32 wDst = pimageDst->scan_size();

   i32 iFilterW = iRadius * 2 + 1;
   i32 iFilterH = iRadius * 2 + 1;
   i32 iFilterHalfW = iRadius;
   i32 iFilterHalfH = iRadius;
   //   i32 iFilterArea = iFilterW * iFilterH;
   i32 iDivisor;

   byte *pDestination;


   byte *pDestination_1;




   byte *pSource;


   byte *pSource1;


   byte *pSource2;


   byte *pSource_3;



   u32 dwI;

   i32 x,y;
   i32 x2;
   i32 x3;
   i32 iFilterXLowerBound;
   i32 iFilterXUpperBound;
   i32 iFilterYLowerBound;
   i32 iFilterYUpperBound;
   i32 xFilter;
   i32 yFilter;

   i32 xLowerBound[4];
   i32 xUpperBound[4];
   i32 yLowerBound[4];
   i32 yUpperBound[4];

   i32 xmax = cx - 1;
   i32 ymax = cy - 1;

   // top
   xLowerBound[0] = 0;
   xUpperBound[0] = cx - 1;
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterHalfH - 1;

   // left
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterHalfW - 1;
   yLowerBound[1] = iFilterHalfH;
   yUpperBound[1] = cy - iFilterHalfH - 1;

   // right
   xLowerBound[2] = cx - iFilterHalfW;
   xUpperBound[2] = cx - 1;
   yLowerBound[2] = iFilterHalfH;
   yUpperBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLowerBound[3] = 0;
   xUpperBound[3] = cx - 1;
   yLowerBound[3] = cy - iFilterHalfW;
   yUpperBound[3] = cy - 1;


   i32 iFilterLine;

   for(i32 i = 0; i < 4; i++)
   {
      i32 xL = xLowerBound[i];
      i32 xU = xUpperBound[i];
      i32 yL = yLowerBound[i];
      i32 yU = yUpperBound[i];
      for(y = yL; y <= yU; y++)
      {
         iFilterYLowerBound = y - iFilterHalfH;
         if(iFilterYLowerBound < 0)
            iFilterYLowerBound = 0;
         iFilterYUpperBound = y + iFilterHalfH;
         if(iFilterYUpperBound > ymax)
            iFilterYUpperBound = ymax;

         pSource = pSrc + (wSrc * maximum(iFilterYLowerBound,0));



         pDestination = pDst + (wDst  * y);




         x = xL;
         x2 = x - iFilterHalfW;
         x3 = x * 4;
         for(; x <= xU; x++,x3+=4)
         {
            iFilterXLowerBound = x - iFilterHalfW;
            if(iFilterXLowerBound < 0)
               iFilterXLowerBound = 0;
            iFilterXUpperBound = x + iFilterHalfW;
            if(iFilterXUpperBound > xmax)
               iFilterXUpperBound = xmax;

            pSource1 = pSource + maximum(iFilterXLowerBound,0) * 4 + iChannel;





            dwI = 0;
            iFilterLine = 0;
            for(yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {
               pSource2 = pSource1 + (wSrc * iFilterLine);


               for(xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {
                  dwI += *pSource2;


                  pSource2 += 4;


               }
               iFilterLine++;
            }
            pDestination_1 = pDestination + x3;



            iDivisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);
            if(iDivisor == 0)
            {
               pDestination_1[0] = (byte)maximum(0u,minimum(dwI,255u));


               pDestination_1[1] = (byte)maximum(0u,minimum(dwI,255u));


               pDestination_1[2] = (byte)minimum(0u,minimum(dwI,255u));


            }
            else
            {
               pDestination_1[0] = (byte)(dwI / iDivisor);


               pDestination_1[1] = pDestination_1[0];



               pDestination_1[2] = pDestination_1[0];



            }
         }
      }
   }

   iDivisor = iFilterW * iFilterH;

   iFilterYLowerBound     = 0;
   iFilterYUpperBound     = iFilterW - 1;
   iFilterXLowerBound     = 0;
   iFilterXUpperBound     = iFilterH - 1;

   i32 yL = iFilterHalfH;
   i32 yU = cy - iFilterHalfH + (iFilterHalfH % 2 == 1 ? 0 : 1);
   i32 xL = iFilterHalfW;
   i32 xU = cx - iFilterHalfW + (iFilterHalfW % 2 == 1 ? 0 : 1);

   i32 y1 = yL;
   i32 x1;

   iDivisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);

   i32 wDiff = wDst - (xU - xL) * 4;
   pSource = pSrc + iChannel;



   pDestination = pDst + (wDst * yL) + xL * 4;




   for(; y1 < yU;)
   {
      x1 = xL;
      pSource1 = pSource;




      for(; x1 < xU;)
      {
         dwI = 0;
         pSource2 = pSource1;


         for(i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
         {
            pSource_3 = pSource2;




            for(i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
            {
               dwI += *pSource_3;


               pSource_3 += 4;


            }

            pSource2 += wSrc;


         }

         dwI /= iDivisor;
         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)pSrc[(wDst * yL) + xL * 4];




         x1++;
         pSource1 += 4;


      }
      pDestination += wDiff;


      y1++;
      pSource += wSrc;


   }

   return true;

}

bool imaging::channel_alpha_gray_blur_32CC(::image * pimageDst, ::image * pimageSrc,
      i32 iChannel,i32 iRadius)
{

   if(iRadius <= 0)
      return true;

   i32 cx = pimageDst->width();
   i32 cy = pimageDst->height();

   if(cx != pimageSrc->width()
         || cy != pimageSrc->height())
      return false;

   pimageDst->map();

   pimageSrc->map();

   byte * pDst = (byte *)pimageDst->get_data();


   byte * pSrc = (byte *)pimageSrc->get_data();



   //i32 wSrc = cx * 4;
   //i32 wDst = cx * 4;
   i32 wSrc = pimageSrc->scan_size();
   i32 wDst = pimageDst->scan_size();

   i32 iFilterW = iRadius * 2 + 1;
   i32 iFilterH = iRadius * 2 + 1;
   i32 iFilterHalfW = iRadius;
   i32 iFilterHalfH = iRadius;
   //   i32 iFilterArea = iFilterW * iFilterH;
   i32 iDivisor;

   byte *pDestination;


   byte *pDestination_1;




   byte *pSource;


   byte *pSource1;


   byte *pSource2;


   byte *pSource_3;



   u32 dwI;

   i32 x,y;
   i32 x2;
   i32 x3;
   i32 iFilterXLowerBound;
   i32 iFilterXUpperBound;
   i32 iFilterYLowerBound;
   i32 iFilterYUpperBound;
   i32 xFilter;
   i32 yFilter;

   i32 xLowerBound[4];
   i32 xUpperBound[4];
   i32 yLowerBound[4];
   i32 yUpperBound[4];

   i32 xmax = cx - 1;
   i32 ymax = cy - 1;

   // top
   xLowerBound[0] = 0;
   xUpperBound[0] = cx - 1;
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterHalfH - 1;

   // left
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterHalfW - 1;
   yLowerBound[1] = iFilterHalfH;
   yUpperBound[1] = cy - iFilterHalfH - 1;

   // right
   xLowerBound[2] = cx - iFilterHalfW;
   xUpperBound[2] = cx - 1;
   yLowerBound[2] = iFilterHalfH;
   yUpperBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLowerBound[3] = 0;
   xUpperBound[3] = cx - 1;
   yLowerBound[3] = cy - iFilterHalfW;
   yUpperBound[3] = cy - 1;


   i32 iFilterLine;

   for(i32 i = 0; i < 4; i++)
   {
      i32 xL = xLowerBound[i];
      i32 xU = xUpperBound[i];
      i32 yL = yLowerBound[i];
      i32 yU = yUpperBound[i];
      for(y = yL; y <= yU; y++)
      {
         iFilterYLowerBound = y - iFilterHalfH;
         if(iFilterYLowerBound < 0)
            iFilterYLowerBound = 0;
         iFilterYUpperBound = y + iFilterHalfH;
         if(iFilterYUpperBound > ymax)
            iFilterYUpperBound = ymax;

         pSource = pSrc + (wSrc * maximum(iFilterYLowerBound,0));



         pDestination = pDst + (wDst  * y);




         x = xL;
         x2 = x - iFilterHalfW;
         x3 = x * 4;
         for(; x <= xU; x++,x3+=4)
         {
            iFilterXLowerBound = x - iFilterHalfW;
            if(iFilterXLowerBound < 0)
               iFilterXLowerBound = 0;
            iFilterXUpperBound = x + iFilterHalfW;
            if(iFilterXUpperBound > xmax)
               iFilterXUpperBound = xmax;

            pSource1 = pSource + maximum(iFilterXLowerBound,0) * 4 + iChannel;





            dwI = 0;
            iFilterLine = 0;
            for(yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {
               pSource2 = pSource1 + (wSrc * iFilterLine);


               for(xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {
                  dwI += *pSource2;


                  pSource2 += 4;


               }
               iFilterLine++;
            }
            pDestination_1 = pDestination + x3;



            iDivisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);
            if(iDivisor == 0)
            {
               pDestination_1[0] = (byte)maximum(0u,minimum(dwI,255u));


               pDestination_1[1] = (byte)maximum(0u,minimum(dwI,255u));


               pDestination_1[2] = (byte)minimum(0u,minimum(dwI,255u));


               pDestination_1[3] = (byte)minimum(0u,minimum(dwI,255u));


            }
            else
            {
               pDestination_1[0] = (byte)(dwI / iDivisor);


               pDestination_1[1] = pDestination_1[0];



               pDestination_1[2] = pDestination_1[0];



               pDestination_1[3] = pDestination_1[0];



            }
         }
      }
   }

   iDivisor = iFilterW * iFilterH;

   iFilterYLowerBound     = 0;
   iFilterYUpperBound     = iFilterW - 1;
   iFilterXLowerBound     = 0;
   iFilterXUpperBound     = iFilterH - 1;

   i32 yL = iFilterHalfH;
   i32 yU = cy - iFilterHalfH;
   i32 xL = iFilterHalfW;
   i32 xU = cx - iFilterHalfW;

   i32 y1 = yL;
   i32 x1;

   iDivisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);

   i32 wDiff = wDst - (xU - xL) * 4;
   pSource = pSrc + iChannel;



   pDestination = pDst + (wDst * yL) + xL * 4;




   for(; y1 < yU;)
   {
      x1 = xL;
      pSource1 = pSource;




      for(; x1 < xU;)
      {
         dwI = 0;
         pSource2 = pSource1;


         for(i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
         {
            pSource_3 = pSource2;




            for(i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
            {
               dwI += *pSource_3;


               pSource_3 += 4;


            }

            pSource2 += wSrc;


         }

         dwI /= iDivisor;
         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;



         x1++;
         pSource1 += 4;


      }
      pDestination += wDiff;


      y1++;
      pSource += wSrc;


   }

   return true;

}

bool imaging::channel_gray_blur(
::draw2d::graphics * pdcDst,
const ::point_i32 & pointDst,
const ::size_i32 & size,
::draw2d::graphics * pdcSrc,
const ::point_i32 & pointSrc,
i32 iChannel,
const ::size_i32 & sizeFilter,
byte * pFilter)
{

   if (size.cx <= 0 || size.cy <= 0)
   {

      return true;

   }

   ::image_pointer pimageDst = m_pcontext->context_image()->create_image(size);

   if (!pimageDst)
   {

      return false;

   }

   ::image_pointer pimageSrc = m_pcontext->context_image()->create_image(size);

   if (!pimageSrc)
   {

      return false;

   }

   {

      image_source imagesource(pimageSrc, ::rectangle_f64(pointSrc, size));

      rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pdcSrc->draw(imagedrawing))
      {

         return false;

      }

   }

   if (!channel_gray_blur_32CC(
         pimageDst,
         pimageSrc,
         iChannel,
         sizeFilter.cx,
         sizeFilter.cy,
         pFilter))
   {

      return false;

   }


   {

      image_source imagesource(pimageDst, ::rectangle_f64(pointDst, size));

      rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pdcDst->draw(imagedrawing))
      {

         return false;

      }

   }

   return true;

}


bool imaging::channel_gray_blur_32CC(::image * pimageDst, ::image * pimageSrc,
                                     i32 iChannel,
                                     i32 iFilterWidth,
                                     i32 iFilterHeight,
                                     byte * pFilterParam)


{

   i32 cx = pimageDst->width();
   i32 cy = pimageDst->height();

   if(cx != pimageSrc->width()
         || cy != pimageSrc->height())
      return false;

   byte * pDst = (byte *)pimageDst->get_data();


   byte * pSrc = (byte *)pimageSrc->get_data();



   //i32 wSrc = cx * 4;
   //i32 wDst = cx * 4;
   i32 wSrc = pimageSrc->scan_size();
   i32 wDst = pimageDst->scan_size();

   i32 iFilterArea = iFilterWidth * iFilterHeight;
   i32 divisor;

   byte *pDestination;




   byte *pSource;


   byte *pSource1;


   byte *pSource2;


   byte *pSource_3;



   byte *pFilter;

   byte * pFilterData = new byte[iFilterHeight *iFilterWidth];

   __memset(pFilterData,1,iFilterHeight * iFilterWidth);

   i32 maxx1 = cx;
   i32 maxy1 = cy;
   //   i32 maxy2 = cy - iFilterWidth;
   //   i32 maxy3 = cy - iFilterWidth / 2;
   i32 max3x1 = maxx1 * 4;
   //   i32 max3x2 = (maxx1 - iFilterHeight) * 4;
   //   i32 max3x3 = (maxx1 - iFilterHeight / 2) * 4;
   //i32 bm3Width = (cy * 3 + 3) & ~0x3L;
   //   i32 w = cx * 4;
   //   ::memcpy_dup(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   ::memcpy_dup(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(i32 y = 0; y < cy; y++)
   {
   pSource = pSrc + wSrc * y;



   pDestination = pDst + wDest * y;




   for(i32 x = 0; x < w; x++)
   {
   *pDestination = *pSource;




   pDestination++;


   pSource++;


   }
   }*/
   u32 dwI;

   i32 iFilterXBegin;
   i32 iFilterXEnd;
   i32 iFilterYBegin;
   i32 iFilterYEnd;

   i32 yLowerBound[4];
   i32 yUpperBound[4];
   i32 xLowerBound[4];
   i32 xUpperBound[4];

   // top
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterWidth / 2;
   xLowerBound[0] = 0;
   xUpperBound[0] = max3x1;

   // left
   yLowerBound[1] = iFilterWidth / 2;
   yUpperBound[1] = maxy1 - iFilterWidth / 2;
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterWidth / 2;

   // right
   yLowerBound[2] = iFilterWidth / 2;
   yUpperBound[2] = maxy1 - iFilterWidth / 2;
   xLowerBound[2] = max3x1 - iFilterWidth / 2;
   xUpperBound[2] = max3x1;

   // bottom
   yLowerBound[3] = maxy1 - iFilterWidth / 2;
   yUpperBound[3] = maxy1;
   xLowerBound[3] = 0;
   xUpperBound[3] = max3x1;

   /*   for(i32 i = 0; i < 4; i++)
   {
   i32 yL = yLowerBound[i];
   i32 yU = yUpperBound[i];
   i32 xL = xLowerBound[i];
   i32 xU = xUpperBound[i];
   for(i32 y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   pSource = pSrc + (wSrc * maximum((y1 - iFilterWidth / 2), 0));



   pDestination = pDst + (wDest  * y1);




   for(i32 x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   pSource1 = pSource + ((maximum(x1 - iFilterWidth / 2 * 3, 0)));




   pFilter = pFilter;

   //            pConv = pConv;


   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(i32 y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(i32 x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *pSource2++ * *lpFilter;


   dwG += *pSource2++ * *lpFilter;


   dwB += *pSource2++ * *lpFilter++;



   }
   }
   pDestination_1 = pDestination + x1;



   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   pDestination_1[0] = maximum(0, minimum(dwR, 255));


   pDestination_1[1] = maximum(0, minimum(dwG, 255));


   pDestination_1[2] = minimum(0, minimum(dwB, 255));


   }
   else
   {
   pDestination_1[0] = dwR / divisor;


   pDestination_1[1] = dwG / divisor;


   pDestination_1[2] = dwB / divisor;


   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   divisor = 0;
   pFilter = pFilterData;



   for(i32 i = 0; i < iFilterArea; i++)
   {
      divisor += *pFilter++;

   }

   i32 iFilterHalfWidth = iFilterWidth / 2;
   //   i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   i32 yL = iFilterHalfWidth;
   i32 yU = cy - iFilterHalfWidth;
   i32 xL = iFilterHalfWidth;
   i32 xU = cx - iFilterHalfWidth;


   i32 y1 = yL;
   //i32 y2 = yL - iFilterHalfWidth;
   i32 x1;
   //i32 x2;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

   i32 wDiff = wDst - (xU - xL) * 4;
   pSource = pSrc + iChannel;



   pDestination = pDst + (wDst  * yL) + xL * 4;




   for(; y1 < yU;)
   {


      x1 = xL;
      //x2 = xL - iFilterHalfWidth;

      pSource1 = pSource;




      for(; x1 < xU;)
      {

         pFilter = pFilterData;


         dwI = 0;
         pSource2 = pSource1;


         for(i32 yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            pSource_3 = pSource2;




            for(i32 xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwI += *pSource_3 * *pFilter++;


               pSource_3 += 4;


            }

            pSource2 += wSrc;


         }

         dwI /= divisor;
         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)dwI;


         *pDestination++ = (uchar)pSource1[3];


         //      x1 += 3;
         x1++;
         pSource1 += 4;


         //x2 += 3;
      }
      pDestination += wDiff;


      y1++;
      //y2++;
      pSource += wSrc;


   }

   delete[]pFilter;

   return true;

}



//bool imaging::color_blend(::draw2d::graphics * pgraphics,const ::rectangle_i32 & rectangle,::draw2d::graphics * pdcColorAlpha,const ::point_i32 & pointAlpha, ::image * pimageWork)
//{
//
//   return pgraphics->stretch(rectangle, pdcColorAlpha, ::rectangle_f64(pointAlpha, rectangle.size()));
//
//}


bool imaging::true_blend(::draw2d::graphics * pgraphics,const ::rectangle_i32 & rectangle,::draw2d::graphics * pdcColorAlpha,const ::point_i32 & pointAlpha, ::image * pimageWork, ::image * pimageWork2, ::image * pimageWork3)
{

   image_source imagesource(pdcColorAlpha, { pointAlpha, rectangle.size() } );

   image_drawing_options imagedrawingoptions(rectangle);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   return pgraphics->draw(imagedrawing);

}

// COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

/*
bool imaging::color_blend(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, ::draw2d::graphics * pdcColorAlpha, const ::point_i32 & pointAlpha, ::image * pimageWork, ::image * pimageWork2)
{






}
*/


//bool imaging::color_blend(::draw2d::graphics * pgraphics, const ::point_i32 & pointParam,const ::size_i32 & size,::draw2d::graphics * pdcColorAlpha,const ::point_i32 & pointAlphaParam,double dBlend)
//{
//
//   ::point_i32 point(pointParam);
//
//   ::point_i32 pointAlpha(pointAlphaParam);
//
//   if(point.x < 0)
//   {
//      pointAlpha.x += -point.x;
//      point.x = 0;
//   }
//
//   if(point.y < 0)
//   {
//      pointAlpha.y += -point.y;
//      point.y = 0;
//   }
//
//
//   if (dBlend >= 1.0)
//   {
//
//      return pgraphics->draw(::rectangle_f64(point, size), pdcColorAlpha, pointAlpha) != false;
//
//   }
//   else
//   {
//
//      ::image_pointer pimage = m_pcontext->context_image()->create_image(size);
//
//      if (!pimage)
//      {
//
//         return false;
//
//      }
//
//      pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//      pimage->g()->stretch(::rectangle_f64(size), pdcColorAlpha, ::rectangle_f64(pointAlpha, size));
//
//      pimage->channel_multiply(dBlend, ::color::e_channel_alpha);
//
//      return pgraphics->draw(::rectangle_f64(point, size), pimage) != false;
//
//   }
//
//}
//
//
//bool imaging::color_blend(::draw2d::graphics * pgraphics,const rectangle_i32 & rectangleParam,::draw2d::graphics * pdcColorAlpha,const ::point_i32 & pointAlpha,double dBlend)
//{
//
//   ::rectangle_i32 rectangle(rectangleParam);
//
//   return color_blend(pgraphics,rectangle.top_left(),rectangle.size(),pdcColorAlpha,pointAlpha,dBlend);
//
//}



void imaging::color_blend_24CC(
byte * pAParam,

i32 x1,
i32 y1,
i32 w1,
i32 cx,
i32 cy,
::color32_t color32,
byte * pCParam,

i32 x3,
i32 y3,
i32 w3)
{
   i32 i,j;
   x1 *= 3;
   x3 *= 3;
   y1 *= w1;
   y3 *= w3;

   byte bR = ::red(color32);
   byte bG = ::green(color32);
   byte bB = ::blue(color32);

   pAParam = (byte *)pAParam + y1 + x1;



   pCParam = (byte *)pCParam + y3 + x3;




   //   byte dwA;
   for(i = 0; i < cy; i++)
   {
      byte * pA = (byte *)pAParam + (w1 * i);




      byte * pC = (byte *)pCParam + (w3 * i);




      for(j = 0; j < cx; j++)
      {
         pA[0] = (byte)(((((u32)pA[0]) * ((u32)(255 - pC[0])) + (((u32)bB) * ((u32)pC[0])))) / 255);








         pA[1] = (byte)(((((u32)pA[1]) * ((u32)(255 - pC[1])) + (((u32)bG) * ((u32)pC[1])))) / 255);








         pA[2] = (byte)(((((u32)pA[2]) * ((u32)(255 - pC[2])) + (((u32)bR) * ((u32)pC[2])))) / 255);








         pA += 3;


         pC += 3;


      }
   }

}





//bool imaging::alpha_spread_R2(::draw2d::graphics *pdcDst,const ::point_i32 & pointDst,const ::size_i32 & size,::draw2d::graphics * pdcSrc,const ::point_i32 & pointSrc,byte bMin)
//{
//   if(size.cx <= 0 || size.cy <= 0)
//      return true;
//
//   ::u32 user;
//   ::u32 uStartScanLine;
//   ::u32 uScanLineCount;
//
//
//   ::rectangle_i32 rectangleTarget(pointDst, size);
//   ::rectangle_i32 rectangleSource(pointSrc, size);
//
//   i32 iwDest;
//
//   BITMAPINFO bmiDst;
//   BITMAP   bmDst;
//   i32 iLimitYDst;
//
//   ::draw2d::bitmap_pointer bitmapDst(this);
//
//   memory memstorageA;
//   memory memstorageB;
//
//   if(!GetDeviceContext24BitsCC(
//            pdcDst,
//            bmDst,
//            bmiDst,
//            memstorageA,
//            bitmapDst,
//            rectangleTarget,
//            iwDest,
//            uiStartScanLine,
//            uiScanLineCount,
//            iLimitYDst))
//   {
//      return false;
//   }
//
//   byte * pDst = memstorageA.get_data();


//
//
//   i32 iwSrc;
//
//   BITMAPINFO bmiSrc;
//   BITMAP   bmSrc;
//   i32 iLimitYSrc;
//
//   ::draw2d::bitmap_pointer bitmapSrc(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcSrc,bmSrc,bmiSrc,
//            memstorageB,
//            bitmapSrc,
//            rectangleSource,
//            iwSrc,
//            user,
//            user,
//            iLimitYSrc))
//   {
//      return false;
//   }
//
//   byte * pSrc = memstorageB.get_data();


//
//
//   const ::point_i32 & pointViewportDst = pdcDst->GetViewportOrg();
//   const ::point_i32 & pointViewportSrc = pdcSrc->GetViewportOrg();
//
//   i32 xvpDst = pointDst.x + pointViewportDst.x;
//   i32 xvpSrc = pointSrc.x + pointViewportSrc.x;
//
//   i32 iLimitX = size.cx;
//
//   if(bmDst.bmWidth - xvpDst < iLimitX)
//   {
//      iLimitX = bmDst.bmWidth - xvpDst;
//   }
//   if(bmSrc.bmWidth - xvpSrc < iLimitX)
//   {
//      iLimitX = bmSrc.bmWidth - xvpSrc;
//   }
//
//
//   if(xvpDst < 0)
//      return false;
//   if(xvpSrc < 0)
//      return false;
//
//   i32 iLimitY = minimum(iLimitYDst,iLimitYSrc);
//
//   alpha_spread_R2_24CC(
//      pDst,


//      xvpDst,
//      0,
//      iwDest,
//      iLimitX,
//      iLimitY,
//      pSrc,


//      xvpSrc,
//      0,
//      iwSrc,
//      bMin);
//
//
//#ifdef WINDOWS_DESKTOP
//
//   ::draw2d::bitmap * pmpOld = pdcDst->get_current_bitmap();

//
//   if(pmpOld == nullptr)

//   {
//      ::draw2d::graphics_pointer graphicsMem(e_create);
//      graphicsMem->CreateCompatibleDC(pdcDst);
//      if(!SetDIBits(
//               (HDC)graphicsMem->get_os_data(),
//               (HBITMAP)bitmapDst->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDst,
//               DIB_RGB_COLORS))
//         __throw(::exception("integer_exception" + __str($1)));
//      ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapDst);

//      if(!pdcDst->BitBlt(pointDst.x,pointDst.y,size.cx,size.cy,graphicsMem,pointSrc.x,pointSrc.y))
//      {
//         ASSERT(false);
//      }
//      graphicsMem->set(pmpMemOld);

//   }
//   else
//   {
//      ::draw2d::bitmap_pointer bitmap(this);
//      bitmap->CreateCompatibleBitmap(pdcDst,1,1);
//      //      ::draw2d::bitmap * pitmap = pdcDst->set(bitmap);

//      if(!SetDIBits(
//               (HDC)pdcDst->get_os_data(),
//               (HBITMAP)bitmapDst->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDst,
//               DIB_RGB_COLORS))
//         __throw(::exception("integer_exception" + __str($1)));
//      pdcDst->set(bitmapDst);
//   }
//
//#else
//
//   __throw(todo);
//
//#endif
//
//   return true;
//
//}


//bool imaging::alpha_spread(::draw2d::graphics *pdcDst,const ::point_i32 & pointDst,const ::size_i32 & size,::draw2d::graphics * pdcSrc,const ::point_i32 & pointSrc,byte bMin,i32 iRadius)
//{
//
//   if(size.cx <= 0 || size.cy <= 0)
//      return true;
//
//   //   single_lock synchronouslock(&m_csMem, true);
//
//
//   ::u32 user;
//   ::u32 uStartScanLine;
//   ::u32 uScanLineCount;
//
//
//   ::rectangle_i32 rectangleDest(pointDst, size);
//   ::rectangle_i32 rectangleSource(pointSrc, size);
//
//   i32 iwDest;
//
//   BITMAPINFO bmiDest;
//   BITMAP   bmDest;
//   i32 iLimitYDest;
//
//
//
//   ::draw2d::bitmap_pointer bitmapDest(this);
//   memory memstorageA;
//   memory memstorageB;
//
//   if(!GetDeviceContext24BitsCC(
//            pdcDst,
//            bmDest,
//            bmiDest,
//            memstorageA,
//            bitmapDest,
//            rectangleDest,
//            iwDest,
//            uiStartScanLine,
//            uiScanLineCount,
//            iLimitYDest))
//   {
//      return false;
//   }
//
//   byte * pDst = memstorageA.get_data();


//
//
//   i32 iwSrc;
//
//   BITMAPINFO bmiSrc;
//   BITMAP   bmSrc;
//   i32 iLimitYSrc;
//
//   ::draw2d::bitmap_pointer bitmapSrc(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcSrc,bmSrc,bmiSrc,
//            memstorageB,
//            bitmapSrc,
//            rectangleSource,
//            iwSrc,
//            user,
//            user,
//            iLimitYSrc))
//   {
//      return false;
//   }
//
//   byte * pSrc = memstorageB.get_data();


//
//
//   const ::point_i32 & pointViewportDest = pdcDst->GetViewportOrg();
//   const ::point_i32 & pointViewportSrc = pdcSrc->GetViewportOrg();
//
//   i32 xvpDest = pointDst.x + pointViewportDest.x;
//   i32 xvpSrc = pointDst.y + pointViewportSrc.x;
//
//   i32 iLimitX = size.cx;
//
//   if(bmDest.bmWidth - xvpDest < iLimitX)
//   {
//      iLimitX = bmDest.bmWidth - xvpDest;
//   }
//   if(bmSrc.bmWidth - xvpSrc < iLimitX)
//   {
//      iLimitX = bmSrc.bmWidth - xvpSrc;
//   }
//
//
//   if(xvpDest < 0)
//      return false;
//   if(xvpSrc < 0)
//      return false;
//
//   i32 iLimitY = minimum(iLimitYDest,iLimitYSrc);
//
//   alpha_spread__24CC(
//      pDst,


//      xvpDest,
//      0,
//      iwDest,
//      iLimitX,
//      iLimitY,
//      pSrc,


//      xvpSrc,
//      0,
//      iwSrc,
//      bMin,iRadius);
//
//
//#ifdef WINDOWS_DESKTOP
//
//   ::draw2d::bitmap * pmpOld = pdcDst->get_current_bitmap();

//
//   if(pmpOld == nullptr)

//   {
//      ::draw2d::graphics_pointer graphicsMem(e_create);
//      graphicsMem->CreateCompatibleDC(pdcDst);
//      if(!SetDIBits(
//               (HDC)graphicsMem->get_os_data(),
//               (HBITMAP)bitmapDest->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDest,
//               DIB_RGB_COLORS))
//         __throw(::exception("integer_exception" + __str($1)));
//      ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapDest);

//      if(!pdcDst->BitBlt(pointDst.x,pointDst.y,size.cx,size.cy,graphicsMem,pointSrc.x,pointSrc.y))
//      {
//         ASSERT(false);
//      }
//      graphicsMem->set(pmpMemOld);

//   }
//   else
//   {
//      ::draw2d::bitmap_pointer bitmap(this);
//      bitmap->CreateCompatibleBitmap(pdcDst,1,1);
//      //      ::draw2d::bitmap * pitmap = pdcDst->set(bitmap);

//      if(!SetDIBits(
//               (HDC)pdcDst->get_os_data(),
//               (HBITMAP)bitmapDest->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDest,
//               DIB_RGB_COLORS))
//         __throw(::exception("integer_exception" + __str($1)));
//      pdcDst->set(bitmapDest);
//   }
//
//   return true;
//
//#else
//
//   __throw(todo);
//
//#endif
//
//}


void imaging::alpha_spread_R2_24CC(byte * pDst,i32 xDest,i32 yDest,i32 wDest,i32 cx,i32 cy,byte * pSrc,i32 xSrc,i32 ySrc,i32 wSrc,byte bMin)



{

   __UNREFERENCED_PARAMETER(xDest);
   __UNREFERENCED_PARAMETER(yDest);
   __UNREFERENCED_PARAMETER(xSrc);
   __UNREFERENCED_PARAMETER(ySrc);
   i32 iFilterWidth = 2 * 2 + 1;
   i32 iFilterHeight = 2 * 2 + 1;
   i32 divisor = iFilterWidth * iFilterHeight;
   byte *pSource;


   byte *pSource1;


   byte *pSource2;


   byte *pDestination;


   byte *pFilter;

   byte * pFilterData = new byte[iFilterHeight *iFilterWidth];
   __memset(pFilterData,1,iFilterHeight * iFilterWidth);

   i32 maxx1 = cx;
   i32 maxy1 = cy;
   //   i32 maxy2 = cy - iFilterWidth;
   //   i32 maxy3 = cy - iFilterWidth / 2;
   i32 max3x1 = maxx1 * 3;
   //   i32 max3x2 = (maxx1 - iFilterHeight) * 3;
   //   i32 max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //   i32 w = cx * 3;
   u32 dwR;
   u32 dwG;
   u32 dwB;

   i32 iFilterXBegin;
   i32 iFilterXEnd;
   i32 iFilterYBegin;
   i32 iFilterYEnd;

   i32 yLowerBound[4];
   i32 yUpperBound[4];
   i32 xLowerBound[4];
   i32 xUpperBound[4];

   // top
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterWidth / 2;
   xLowerBound[0] = 0;
   xUpperBound[0] = max3x1;

   // left
   yLowerBound[1] = iFilterWidth / 2;
   yUpperBound[1] = maxy1 - iFilterWidth / 2;
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterWidth / 2;

   // right
   yLowerBound[2] = iFilterWidth / 2;
   yUpperBound[2] = maxy1 - iFilterWidth / 2;
   xLowerBound[2] = max3x1 - iFilterWidth / 2;
   xUpperBound[2] = max3x1;

   // bottom
   yLowerBound[3] = maxy1 - iFilterWidth / 2;
   yUpperBound[3] = maxy1;
   xLowerBound[3] = 0;
   xUpperBound[3] = max3x1;

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   i32 iFilterHalfWidth = iFilterWidth / 2;
   i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   i32 yL = iFilterHalfWidth;
   i32 yU = maxy1 - iFilterHalfWidth;
   i32 xL = iFilterHalfWidthBytes;
   i32 xU = max3x1 - iFilterHalfWidthBytes;


   i32 y1 = yL;
   i32 y2 = yL - iFilterHalfWidth;
   i32 x1;
   i32 x2;

   u32 bMin3 = bMin * 3;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

   bool bSpread;

   for(; y1 < yU;)
   {
      pSource = pSrc + (wSrc * y2);




      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      pDestination = pDst + (wDest  * y1) + x1;




      for(; x1 < xU;)
      {
         pSource1 = pSource + x2;




         pFilter = pFilterData;


         dwR = 0;
         dwG = 0;
         dwB = 0;
         bSpread = false;
         for(i32 yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            pSource2 = pSource1 + (wSrc * yFilter);


            for(i32 xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwB = pSource2[0];


               dwG = pSource2[1];


               dwR = pSource2[2];



               if(dwR + dwG + dwB > bMin3)
               {
                  bSpread = true;
                  break;
               }
               pSource2 += 3;


            }
         }

         if(bSpread)
         {
            *((u32 *)pDestination) |= 0x00ffffff;


            pDestination += 3;


         }
         else
         {
            pDestination += 3;


         }
         x1 += 3;
         x2 += 3;
      }
      y1++;
      y2++;
   }

   delete[] pFilterData;

}



bool imaging::channel_spread(
::draw2d::graphics *pdcDst,
const ::point_i32 & pointDst,
const ::size_i32 & size,
::draw2d::graphics * pdcSrc,
const ::point_i32 & pointSrc,
i32 iChannel,i32 iRadius)
{

   return channel_spread_set_color(
          pdcDst,
          pointDst,
          size,
          pdcSrc,
          pointSrc,
          iChannel,
          iRadius,
          0xffffffff);

}


bool imaging::channel_spread_set_color(
::draw2d::graphics *pdcDst,
const ::point_i32 & pointDst,
const ::size_i32 & size,
::draw2d::graphics * pdcSrc,
const ::point_i32 & pointSrc,
i32 iChannel,i32 iRadius,
::color32_t color32)
{

   if(size.is_empty())
      return true;

   ::image_pointer pimageDst = m_pcontext->context_image()->create_image(size);

   if (!pimageDst)
   {

      return false;

   }

   ::image_pointer pimageSrc = m_pcontext->context_image()->create_image(size);

   if (!pimageSrc)
   {

      return false;

   }

   pimageSrc->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   {

      image_source imagesource(pdcSrc, ::rectangle_f64(pointSrc, size));

      ::rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pimageSrc->g()->draw(imagedrawing))
      {

         return false;

      }

   }

   auto psystem = m_psystem->m_paurasystem;

   auto pdraw2d = psystem->draw2d();

   if (!pdraw2d->channel_spread__32CC(
         pimageDst,
         pimageSrc,
         iChannel,
         iRadius, color32))
   {

      return false;

   }

   {

      image_source imagesource(pimageDst, ::rectangle_f64(pointDst, size));

      ::rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pdcDst->draw(imagedrawing))
      {

         return false;

      }

   }

   return true;

}


bool imaging::spread(
::draw2d::graphics *pdcDst,
const ::point_i32 & pointDst,
const ::size_i32 & size,
::draw2d::graphics * pdcSrc,
const ::point_i32 & pointSrc,
i32 iRadius)
{

   return spread_set_color(
          pdcDst,
          pointDst,
          size,
          pdcSrc,
          pointSrc,
          iRadius,
          0xffffffff);

}


bool imaging::spread_set_color(
::draw2d::graphics *pdcDst,
const ::point_i32 & pointDst,
const ::size_i32 & size,
::draw2d::graphics * pdcSrc,
const ::point_i32 & pointSrc,
i32 iRadius,
::color32_t color32)
{

   if(size.is_empty())
      return true;

   ::image_pointer pimageDst = m_pcontext->context_image()->create_image(size);

   if (!pimageDst)
   {

      return false;

   }

   ::image_pointer pimageSrc = m_pcontext->context_image()->create_image(size);

   if (!pimageSrc)
   {

      return false;

   }

   pimageSrc->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   {

      image_source imagesource(pdcSrc, ::rectangle_f64(pointSrc, size));

      ::rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pimageSrc->g()->draw(imagedrawing))
      {

         return false;

      }

   }

   if (!spread__32CC(
         pimageDst,
         pimageSrc,
         iRadius, color32))
   {

      return false;

   }

   {

      image_source imagesource(pimageDst, ::rectangle_f64(pointDst, size));

      ::rectangle_f64 rectangle(size);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      if (!pdcDst->draw(imagedrawing))
      {

         return false;

      }

   }

   return true;

}


bool imaging::spread__32CC(::image * pimageDst, ::image * pimageSrc,i32 iRadius, const ::color::color& colorSpreadSetColor)
{

   if (iRadius <= 1)
   {

      return false;

   }

   if (iRadius > 1024)
   {

      iRadius = 1024;

   }

   i32 iFilterW      = iRadius * 2 + 1;
   i32 iFilterH      = iRadius * 2 + 1;
   i32 iFilterHalfW  = iRadius;
   i32 iFilterHalfH  = iRadius;
   i32 iFilterArea   = iFilterW * iFilterH;
   i32 divisor       = iFilterW * iFilterH;
   byte *pSource;


   byte *pSource1;


   byte *pSource2;


   byte *pDestination;


   byte *pFilter;

   i32 i;
   i32 x;
   i32 y;
   i32 x1;
   i32 y1;
   i32 x2;
   i32 y2;

   pimageDst->map();

   pimageSrc->map();

   if(!pimageDst || !pimageSrc)
   {

      return false;

   }

   i32 iRadius2 = iRadius * iRadius;
   i32 r2;

   auto psystem = m_psystem->m_paurasystem;

   auto pdraw2d = psystem->draw2d();

   synchronous_lock synchronouslock(pdraw2d->mutex());

   auto & pmemory = pdraw2d->m_alpha_spread__32CC_filterMap[iRadius];

   m_psystem->__construct_new(pmemory);

   if (pmemory->size() != iFilterArea)
   {

      pmemory->set_size(iFilterArea);

      byte * pdata = pmemory->get_data();

      for(y = 0; y < iFilterHalfH; y++)
      {

         for(x = 0; x < iFilterHalfW; x++)
         {

            x1 = iFilterHalfW - x;

            y1 = iFilterHalfH - y;

            r2 = x1 * x1 + y1 * y1;

            if (r2 <= iRadius2)
            {

               i = 1;

            }
            else
            {

               i = 0;

            }

            pdata[x + y * iFilterW] = (byte)i;

         }

      }

   }

   synchronouslock.unlock();

   byte * pFilterData = pmemory->get_data();

   i32 cx = pimageDst->width();

   i32 cy = pimageDst->height();

   if (cx != pimageSrc->width() || cy != pimageSrc->height())
   {

      return false;

   }

   byte * pDst = (byte *)pimageDst->get_data();

   byte * pSrc = (byte *)pimageSrc->get_data();

   i32 wSrc = pimageSrc->scan_size();

   i32 wDst = pimageDst->scan_size();

   i32 maxx1 = cx;

   i32 maxy1 = cy;

   i32 max3x1 = maxx1 * 4;

   ::copy_colorref((::color32_t*)pDst, cx,cy,pimageDst->scan_size(),(::color32_t *)pSrc,pimageSrc->scan_size());


   i32 iFilterXLowerBound;
   i32 iFilterXUpperBound;
   i32 iFilterYLowerBound;
   i32 iFilterYUpperBound;


   i32 yLowerBound[4];
   i32 yUpperBound[4];
   i32 xLowerBound[4];
   i32 xUpperBound[4];

   // top
   xLowerBound[0] = 0;
   
   xUpperBound[0] = cx - 1;

   yLowerBound[0] = 0;

   yUpperBound[0] = iFilterHalfH - 1;

   // left
   xLowerBound[1] = 0;

   xUpperBound[1] = iFilterHalfW - 1;

   yLowerBound[1] = iFilterHalfH;

   yUpperBound[1] = cy - iFilterHalfH - 1;

   // right
   xLowerBound[2] = cx - iFilterHalfW;
   
   xUpperBound[2] = cx - 1;
   
   yLowerBound[2] = iFilterHalfH;

   yUpperBound[2] = cy - iFilterHalfH - 1;

   // bottom
   xLowerBound[3] = 0;
   
   xUpperBound[3] = cx - 1;

   yLowerBound[3] = cy - iFilterHalfH;

   yUpperBound[3] = cy - 1;

   i32 xL;

   i32 xU;

   i32 yL;

   i32 yU;

   i32 xMax = cx - 1;

   i32 yMax = cy - 1;

   // limits due the filter
   i32 xMaxFilterBound = xMax - iFilterHalfW;

   i32 yMaxFilterBound = yMax - iFilterHalfH;

   i32 xFilterMax = iFilterW - 1;

   i32 yFilterMax = iFilterH - 1;

   for(i = 0; i < 4; i++)
   {

      xL = xLowerBound[i];

      xU = xUpperBound[i];

      yL = yLowerBound[i];

      yU = yUpperBound[i];

      y1 = yL;

      y2 = y1 - iFilterHalfH;

      for(; y1 <= yU;)
      {

         if(y1 < iFilterHalfH)
         {

            iFilterYLowerBound = iFilterHalfH - y1;

         }
         else
         {

            iFilterYLowerBound = 0;

         }

         if(y1 > yMaxFilterBound)
         {

            iFilterYUpperBound = yFilterMax - (y1 - yMaxFilterBound);

         }
         else
         {

            iFilterYUpperBound = yFilterMax;

         }

         pSource = pSrc + wSrc * y2;

         x1 = xL;

         x2 = (x1 - iFilterHalfW) * 4;

         pDestination = pDst + (wDst  * y1) + x1 * 4;

         if(*((u32 *)pDestination) != colorSpreadSetColor)
         {

            for(; x1 <= xU; x1++)
            {

               if(x1 < iFilterHalfH)
               {

                  iFilterXLowerBound = iFilterHalfH - x1;

               }
               else
               {

                  iFilterXLowerBound = 0;

               }

               if(x1 > xMaxFilterBound)
               {

                  iFilterXUpperBound = xFilterMax - (x1 - xMaxFilterBound);

               }
               else
               {

                  iFilterXUpperBound = xFilterMax;

               }

               pSource1 = pSource;

               if (*((u32 *)pDestination) != colorSpreadSetColor)
               {

                  for (i32 yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
                  {

                     pSource2 = pSource1 + (wSrc * yFilter);

                     pFilter = pFilterData + yFilter * iFilterW + iFilterXLowerBound;

                     for (i32 xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                     {

                        if (*pFilter >= 1)
                        {

                           if (*((u32 *)pSource2))
                           {

                              *((u32 *)pDestination) = colorSpreadSetColor;

                              goto breakFilter;

                           }

                        }

                        pFilter++;

                        pSource2 += 4;

                     }

                  }

               }

            breakFilter:

               pDestination += 4;

               x2 += 4;

            }

         }

         y1++;

         y2++;

      }

   }

   iFilterYLowerBound = 0;
   
   iFilterYUpperBound = iFilterW - 1;
   
   iFilterXLowerBound = 0;
   
   iFilterXUpperBound = iFilterH - 1;

   i32 iFilterHalfWidth = iFilterW / 2;

   i32 iFilterHalfWidthBytes = iFilterHalfWidth * 4;

   yL = iFilterHalfWidth;
   
   yU = maxy1 - iFilterHalfWidth;
   
   xL = iFilterHalfWidthBytes;
   
   xU = max3x1 - iFilterHalfWidthBytes;

   y1 = yL;

   y2 = yL - iFilterHalfWidth;

   divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);

   for(; y1 < yU;)
   {

      pSource = pSrc + (wSrc * y2);

      x1 = xL;

      x2 = xL - iFilterHalfWidthBytes;

      pDestination = pDst + (wDst  * y1) + x1;

      for(; x1 < xU;)
      {

         pSource1 = pSource + x2;

         pFilter = pFilterData;

         if(*((u32 *)pDestination) != 0xffffffff)
         {

            for(i32 yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {

               pSource2 = pSource1 + (wSrc * yFilter);

               pFilter = pFilterData + yFilter * iFilterW + iFilterXLowerBound;

               for(i32 xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {

                  if(*pFilter >= 1)
                  {

                     if(pSource2[0] > 0)
                     {

                        *((u32 *)pDestination) = colorSpreadSetColor;

                        goto breakFilter2;

                     }

                  }
                  pFilter++;

                  pSource2 += 4;


               }
            }
         }
breakFilter2:
         pDestination += 4;


         x1 += 4;
         x2 += 4;
      }
      y1++;
      y2++;
   }

   return true;
}

































































//bool imaging::pixelate(::draw2d::graphics *pdcDst,i32 xDest,i32 yDest,i32 cx,i32 cy,::draw2d::graphics * pdcSrc,i32 xSrc,i32 ySrc,i32 iSize)
//{
//
//   /*::draw2d::graphics_pointer & imageA.get_graphics()  = pthreadsafedata->m_dcA;
//   ::draw2d::graphics_pointer & imageB.get_graphics()  = pthreadsafedata->m_dcA;
//
//   ::draw2d::bitmap & bitmapA  = pthreadsafedata->bitmapA;
//   ::draw2d::bitmap & bitmapB  = pthreadsafedata->bitmapB;
//
//   i32 cxDest = cx / iSize;
//   i32 cyDest = cy / iSize;
//
//   if(imageA.get_graphics()->get_os_data() == nullptr)
//   {
//   ::draw2d::graphics_pointer dcScreen;
//   spgraphicsScreen->CreateDC("DISPLAY", nullptr, nullptr, nullptr);
//   imageA.get_graphics()->CreateCompatibleDC(&dcScreen);
//   }
//   if(imageB.get_graphics()->get_os_data() == nullptr)
//   {
//   ::draw2d::graphics_pointer dcScreen;
//   spgraphicsScreen->CreateDC("DISPLAY", nullptr, nullptr, nullptr);
//   imageB.get_graphics()->CreateCompatibleDC(&dcScreen);
//   }
//   if(spbitmapB->m_hObject == nullptr)
//   {
//   ::draw2d::graphics_pointer dcScreen;
//   spgraphicsScreen->CreateDC("DISPLAY", nullptr, nullptr, nullptr);
//   spbitmapB->CreateBitmap(cxDest + 100, cyDest + 100, 1, 32, nullptr);
//
//   }
//   else
//   {
//   BITMAP bm;
//   if(!spbitmapB->GetObject(sizeof(bm), &bm))
//   __throw(::exception("integer_exception" + __str($1)));
//   if(bm.bmWidth < cx ||
//   bm.bmHeight  < cy)
//   {
//   spbitmapB->delete_object();
//   spbitmapB->CreateBitmap(cxDest + 100, cyDest + 100, 1, 32, nullptr);
//   }
//   }
//   imageB.get_graphics()->set(bitmapB);
//
//   imageB.get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
//   imageB.get_graphics()->StretchBlt(0, 0, cxDest, cyDest, pdcSrc, xSrc, ySrc, cx, cy);
//
//   i32 x1 = xDest;
//   i32 x2 = xDest + iSize;
//   i32 y1;
//   i32 y2;
//   for(i32 x = 0; x < cxDest; x++)
//   {
//   y1 = yDest;
//   y2 = yDest + iSize;
//   for(i32 y = 0; y < cyDest; y++)
//   {
//   pdcDst->fill_rectangle(x1, y1, x2, y2, imageB.get_graphics()->GetPixel(x, y));
//   y1 += iSize;
//   y2 += iSize;
//   }
//   x1 += iSize;
//   x2 += iSize;
//   }
//
//   return true;*/
//
//
//
//
//   if(cx <= 0 || cy <= 0)
//      return true;
//
//   ::u32 user;
//   ::u32 uStartScanLine;
//   ::u32 uScanLineCount;
//
//
//   memory memstorageA;
//   memory memstorageB;
//   memory memstorageC;
//
//   ::rectangle_i32 rectangleDest;
//   rectangleDest.left = xDest;
//   rectangleDest.right = xDest + cx;
//   rectangleDest.top = yDest;
//   rectangleDest.bottom = yDest + cy;
//
//   ::rectangle_i32 rectangleSource;
//   rectangleSource.left = xSrc;
//   rectangleSource.right = xSrc + cx;
//   rectangleSource.top = ySrc;
//   rectangleSource.bottom = ySrc + cy;
//
//   i32 iwDest;
//
//   BITMAPINFO bmiDest;
//   BITMAP   bmDest;
//   i32 iLimitYDest;
//
//   ::draw2d::bitmap_pointer bitmapDest(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcDst,
//            bmDest,
//            bmiDest,
//            memstorageA,
//            bitmapDest,
//            rectangleDest,
//            iwDest,
//            uiStartScanLine,
//            uiScanLineCount,
//            iLimitYDest))
//   {
//      return false;
//   }
//
//   byte * pDst = memstorageA.get_data();


//
//
//   i32 iwSrc;
//
//   BITMAPINFO bmiSrc;
//   BITMAP   bmSrc;
//   i32 iLimitYSrc;
//
//   ::draw2d::bitmap_pointer bitmapSrc(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcSrc,bmSrc,bmiSrc,
//            memstorageB,
//            bitmapSrc,
//            rectangleSource,
//            iwSrc,
//            user,
//            user,
//            iLimitYSrc))
//   {
//      return false;
//   }
//
//   byte * pSrc = memstorageB.get_data();


//
//   memstorageC.set_size((cx + iSize) / iSize * (cy + iSize) / iSize);
//   //   byte * pc = memstorageC.get_data();

//
//
//   const ::point_i32 & pointViewportDest = pdcDst->GetViewportOrg();
//   const ::point_i32 & pointViewportSrc = pdcSrc->GetViewportOrg();
//
//   i32 xvpDest = xDest + pointViewportDest.x;
//   i32 xvpSrc = xSrc + pointViewportSrc.x;
//
//   i32 iLimitX = cx;
//
//   if(bmDest.bmWidth - xvpDest < iLimitX)
//   {
//      iLimitX = bmDest.bmWidth - xvpDest;
//   }
//   if(bmSrc.bmWidth - xvpSrc < iLimitX)
//   {
//      iLimitX = bmSrc.bmWidth - xvpSrc;
//   }
//
//
//   if(xvpDest < 0)
//      return false;
//   if(xvpSrc < 0)
//      return false;
//
//   i32 iLimitY = minimum(iLimitYDest,iLimitYSrc);
//
//   pixelate_24CC(
//      pDst + xvpDest * 3,


//      0,
//      0,
//      iwDest,
//      iLimitX,
//      iLimitY,
//      pSrc + xvpSrc * 3,


//      0,
//      0,
//      iwSrc,
//      iSize);
//
//
//#ifdef WINDOWS_DESKTOP
//
//   ::draw2d::bitmap * pmpOld = pdcDst->get_current_bitmap();

//
//   if(pmpOld == nullptr)

//   {
//      ::draw2d::graphics_pointer graphicsMem(e_create);
//      graphicsMem->CreateCompatibleDC(pdcDst);
//      if(!SetDIBits(
//               (HDC)graphicsMem->get_os_data(),
//               (HBITMAP)bitmapDest->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDest,
//               DIB_RGB_COLORS))
//         __throw(::exception("integer_exception" + __str($1)));
//      ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapDest);

//      if(!pdcDst->BitBlt(xDest,yDest,cx,cy,graphicsMem,xSrc,ySrc))
//      {
//         ASSERT(false);
//      }
//      graphicsMem->set(pmpMemOld);

//   }
//   else
//   {
//      ::draw2d::bitmap_pointer bitmap(this);
//      bitmap->CreateCompatibleBitmap(pdcDst,1,1);
//      //      ::draw2d::bitmap * pitmap = pdcDst->set(bitmap);

//      if(!SetDIBits(
//               (HDC)pdcDst->get_os_data(),
//               (HBITMAP)bitmapDest->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDest,
//               DIB_RGB_COLORS))
//      {
//         pdcDst->set(bitmapDest);
//         return false;
//      }
//      pdcDst->set(bitmapDest);
//   }
//
//   return true;
//
//#else
//
//   __throw(todo);
//
//#endif
//
//}


void imaging::pixelate_24CC(
byte *   pDst,


i32      xDest,
i32      yDest,
i32      wDest,
i32      cx,
i32      cy,
byte *   pSrc,


i32      xSrc,
i32      ySrc,
i32      wSrc,
i32      iSize)
{
   __UNREFERENCED_PARAMETER(xDest);
   __UNREFERENCED_PARAMETER(yDest);
   __UNREFERENCED_PARAMETER(xSrc);
   __UNREFERENCED_PARAMETER(ySrc);
   i32      divisor;
   byte *   pSource;


   byte *   pDestination;


   byte *   pDestination_1;


   byte *   pDestination_2;


   byte *   pSource1;


   byte *   pSource2;



   i32 iFilterWidth = iSize;
   i32 iFilterHeight = iSize;
   i32 maxx1 = cx;
   i32 maxy1 = cy;
   //   i32 maxy2 = cy - iFilterWidth;
   //   i32 maxy3 = cy - iFilterWidth / 2;
   i32 max3x1 = maxx1 * 3;
   //   i32 max3x2 = (maxx1 - iFilterHeight) * 3;
   //   i32 max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //i32 w = cx * 3;

   u32 dwR;
   u32 dwG;
   u32 dwB;

   i32 iFilterXBegin;
   i32 iFilterXEnd;
   i32 iFilterYBegin;
   i32 iFilterYEnd;

   i32 yLowerBound[4];
   i32 yUpperBound[4];
   i32 xLowerBound[4];
   i32 xUpperBound[4];

   // top
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterWidth / 2;
   xLowerBound[0] = 0;
   xUpperBound[0] = max3x1;

   // left
   yLowerBound[1] = iFilterWidth / 2;
   yUpperBound[1] = maxy1 - iFilterWidth / 2;
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterWidth / 2;

   // right
   yLowerBound[2] = iFilterWidth / 2;
   yUpperBound[2] = maxy1 - iFilterWidth / 2;
   xLowerBound[2] = max3x1 - iFilterWidth / 2;
   xUpperBound[2] = max3x1;

   // bottom
   yLowerBound[3] = maxy1 - iFilterWidth / 2;
   yUpperBound[3] = maxy1;
   xLowerBound[3] = 0;
   xUpperBound[3] = max3x1;

   /*   for(i32 i = 0; i < 4; i++)
   {
   i32 yL = yLowerBound[i];
   i32 yU = yUpperBound[i];
   i32 xL = xLowerBound[i];
   i32 xU = xUpperBound[i];
   for(i32 y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   pSource = pSrc + (wSrc * maximum((y1 - iFilterWidth / 2), 0));



   pDestination = pDst + (wDest  * y1);




   for(i32 x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   pSource1 = pSource + ((maximum(x1 - iFilterWidth / 2 * 3, 0)));




   pFilter = pFilter;

   //            pConv = pConv;


   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(i32 y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(i32 x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *pSource2++ * *lpFilter;


   dwG += *pSource2++ * *lpFilter;


   dwB += *pSource2++ * *lpFilter++;



   }
   }
   pDestination_1 = pDestination + x1;



   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   pDestination_1[0] = maximum(0, minimum(dwR, 255));


   pDestination_1[1] = maximum(0, minimum(dwG, 255));


   pDestination_1[2] = minimum(0, minimum(dwB, 255));


   }
   else
   {
   pDestination_1[0] = dwR / divisor;


   pDestination_1[1] = dwG / divisor;


   pDestination_1[2] = dwB / divisor;


   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   i32 iFilterHalfWidth = iFilterWidth / 2;
   i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   i32 yL = iFilterHalfWidth;
   i32 yU = maxy1 - iFilterHalfWidth;
   i32 xL = iFilterHalfWidthBytes;
   i32 xU = max3x1 - iFilterHalfWidthBytes;


   i32 y1 = yL;
   i32 y2 = yL - iFilterHalfWidth;
   i32 x1;
   i32 x2;

   divisor = (iFilterYEnd - iFilterYBegin)
             * (iFilterXEnd - iFilterXBegin);


   i32 cDest   = wDest - (iFilterWidth * 3);
   i32 cSrc    = wSrc - (iFilterWidth * 3);
   i32 iSize3  = iSize * 3;

   i32 cyDest  = wDest * iSize;
   i32 cySrc   = wSrc  * iSize;



   pSource         = pSrc;



   pDestination    = pDst;




   for(; y1 < yU;)
   {
      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;
      for(; x1 < xU;)
      {
         pSource1 = pSource + x2;





         dwR = 0;
         dwG = 0;
         dwB = 0;
         pSource2 = pSource1;


         i32 yFilter;
         for(yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            for(i32 xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
            {
               dwR += *pSource2++;


               dwG += *pSource2++;


               dwB += *pSource2++;


            }
            pSource2 += cSrc;


         }

         dwR /= divisor;
         dwG /= divisor;
         dwB /= divisor;

         pDestination_1 = pDestination + x2;



         pDestination_2 = pDestination_1;



         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(i32 xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               pDestination_2[0] = (byte)dwR;


               pDestination_2[1] = (byte)dwG;


               pDestination_2[2] = (byte)dwB;


               pDestination_2 += 3;


            }
            pDestination_2 += cDest;


         }


         x1 += iSize3;
         x2 += iSize3;
      }
      y1 += iSize;
      y2 += iSize;
      pSource         += cySrc;


      pDestination    += cyDest;


   }

}


//bool imaging::alpha_pixelate(
//   ::draw2d::graphics *pdcDst,
//   i32 xDest,
//   i32 yDest,
//   i32 cx,
//   i32 cy,
//   ::draw2d::graphics * pdcSrc1,
//   i32 xSrc1,
//   i32 ySrc1,
//   ::draw2d::graphics * pdcSrc2,
//   i32 xSrc2,
//   i32 ySrc2,
//   i32 iSize,
//   i32 iAlpha)
//{
//   if(cx <= 0 || cy <= 0)
//      return true;
//
//   memory memstorageA;
//   memory memstorageB;
//   memory memstorageC;
//
//
//   ::u32 user;
//   ::u32 uStartScanLine;
//   ::u32 uScanLineCount;
//
//
//   ::rectangle_i32 rectangleDest;
//   rectangleDest.left = xDest;
//   rectangleDest.right = xDest + cx;
//   rectangleDest.top = yDest;
//   rectangleDest.bottom = yDest + cy;
//
//   ::rectangle_i32 rectangleSrc1;
//   rectangleSrc1.left = xSrc1;
//   rectangleSrc1.right = xSrc1 + cx;
//   rectangleSrc1.top = ySrc1;
//   rectangleSrc1.bottom = ySrc1 + cy;
//
//   ::rectangle_i32 rectangleSrc2;
//   rectangleSrc2.left = xSrc2;
//   rectangleSrc2.right = xSrc2 + cx;
//   rectangleSrc2.top = ySrc2;
//   rectangleSrc2.bottom = ySrc2 + cy;
//
//   i32 iwDest;
//
//   BITMAPINFO bmiDest;
//   BITMAP   bmDest;
//   i32 iLimitYDest;
//
//   ::draw2d::bitmap_pointer bitmapDest(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcDst,
//            bmDest,
//            bmiDest,
//            memstorageA,
//            bitmapDest,
//            rectangleDest,
//            iwDest,
//            uiStartScanLine,
//            uiScanLineCount,
//            iLimitYDest))
//   {
//      return false;
//   }
//
//   byte * pDst = memstorageA.get_data();


//
//
//   i32 iwSrc1;
//   i32 iwSrc2;
//
//   BITMAPINFO bmiSrc1;
//   BITMAP   bmSrc1;
//   i32 iLimitYSrc1;
//
//   ::draw2d::bitmap_pointer bitmapSrc1(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcSrc1,bmSrc1,bmiSrc1,
//            memstorageB,
//            bitmapSrc1,
//            rectangleSrc1,
//            iwSrc1,
//            user,
//            user,
//            iLimitYSrc1))
//   {
//      return false;
//   }
//
//   byte * pSrc1 = memstorageB.get_data();


//
//   BITMAPINFO bmiSrc2;
//   BITMAP   bmSrc2;
//   i32 iLimitYSrc2;
//
//   ::draw2d::bitmap_pointer bitmapSrc2(this);
//
//   if(!GetDeviceContext24BitsCC(
//            pdcSrc2,bmSrc2,bmiSrc2,
//            memstorageC,
//            bitmapSrc2,
//            rectangleSrc2,
//            iwSrc2,
//            user,
//            user,
//            iLimitYSrc2))
//   {
//      return false;
//   }
//
//   byte * pSrc2 = memstorageC.get_data();


//
//   const ::point_i32 & pointViewportDest = pdcDst->GetViewportOrg();
//   const ::point_i32 & pointViewportSrc1 = pdcSrc1->GetViewportOrg();
//   const ::point_i32 & pointViewportSrc2 = pdcSrc2->GetViewportOrg();
//
//   i32 xvpDest = xDest + pointViewportDest.x;
//   i32 xvpSrc1 = xSrc1 + pointViewportSrc1.x;
//   i32 xvpSrc2 = xSrc2 + pointViewportSrc2.x;
//
//   i32 iLimitX = cx;
//
//   if(bmDest.bmWidth - xvpDest < iLimitX)
//   {
//      iLimitX = bmDest.bmWidth - xvpDest;
//   }
//   if(bmSrc1.bmWidth - xvpSrc1 < iLimitX)
//   {
//      iLimitX = bmSrc1.bmWidth - xvpSrc1;
//   }
//   if(bmSrc2.bmWidth - xvpSrc2 < iLimitX)
//   {
//      iLimitX = bmSrc2.bmWidth - xvpSrc2;
//   }
//
//
//   if(xvpDest < 0)
//      return false;
//   if(xvpSrc1 < 0)
//      return false;
//   if(xvpSrc2 < 0)
//      return false;
//
//   i32 iLimitY = minimum(minimum(iLimitYDest,iLimitYSrc1),iLimitYSrc2);
//
//   alpha_pixelate_24CC(
//      pDst + xvpDest * 3,


//      0,
//      0,
//      iwDest,
//      iLimitX,
//      iLimitY,
//      pSrc1 + xvpSrc1 * 3,


//      0,
//      0,
//      iwSrc1,
//      pSrc2 + xvpSrc2 * 3,


//      0,
//      0,
//      iwSrc2,
//      iSize,
//      iAlpha);
//
//#ifdef WINDOWS_DESKTOP
//
//   ::draw2d::bitmap * pmpOld = pdcDst->get_current_bitmap();

//
//   if(pmpOld == nullptr)

//   {
//      ::draw2d::graphics_pointer graphicsMem(e_create);
//      graphicsMem->CreateCompatibleDC(pdcDst);
//      if(!SetDIBits(
//               (HDC)graphicsMem->get_os_data(),
//               (HBITMAP)bitmapDest->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDest,
//               DIB_RGB_COLORS))
//         __throw(::exception("integer_exception" + __str($1)));
//      ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapDest);

//      if(!pdcDst->BitBlt(xDest,yDest,cx,cy,graphicsMem,xDest,yDest))
//      {
//         ASSERT(false);
//      }
//      graphicsMem->set(pmpMemOld);

//   }
//   else
//   {
//      ::draw2d::bitmap_pointer bitmap(this);
//      bitmap->CreateCompatibleBitmap(pdcDst,1,1);
//      //      ::draw2d::bitmap * pitmap = pdcDst->set(bitmap);

//      if(!SetDIBits(
//               (HDC)pdcDst->get_os_data(),
//               (HBITMAP)bitmapDest->get_os_data(),
//               uiStartScanLine,
//               uiScanLineCount,
//               pDst,


//               &bmiDest,
//               DIB_RGB_COLORS))
//      {
//         pdcDst->set(bitmapDest);
//         return false;
//      }
//      pdcDst->set(bitmapDest);
//   }
//
//   return true;
//
//#else
//
//   __throw(todo);
//
//#endif
//
//}


void imaging::alpha_pixelate_24CC(
byte * pDst,


i32 xDest,
i32 yDest,
i32 wDest,
i32 cx,
i32 cy,
byte * pSrc1,


i32 xSrc1,
i32 ySrc1,
i32 wSrc1,
byte * pSrc2,


i32 xSrc2,
i32 ySrc2,
i32 wSrc2,
i32 iSize,
i32 iAlpha)
{
   __UNREFERENCED_PARAMETER(xDest);
   __UNREFERENCED_PARAMETER(yDest);
   __UNREFERENCED_PARAMETER(xSrc1);
   __UNREFERENCED_PARAMETER(ySrc1);
   __UNREFERENCED_PARAMETER(xSrc2);
   __UNREFERENCED_PARAMETER(ySrc2);
   //   const i32 constFilterWidth = 3;
   //   const i32 constFilterHeight = 3;
   i32 divisor = iSize * iSize;
   byte *pSource1;


   byte *pSource2;


   byte *pDestination;


   byte *pDestination_1;


   byte *pDestination_2;


   byte *pSource1_1;


   byte *pSource1_2;


   byte *pSource2_1;


   byte *pSource2_2;


   //   ::u16 *pDestination_2;


   //   byte *pFilter;

   //u32 *pConv;

   //   byte pFilter[constFilterHeight *constFilterWidth];
   //u32 pConv[constFilterHeight * constFilterWidth * 3];
   //   __memset(pFilter, 1, constFilterHeight * constFilterWidth);

   i32 iFilterWidth = iSize;
   i32 iFilterHeight = iSize;
   i32 maxx1 = cx;
   i32 maxy1 = cy;
   //   i32 maxy2 = cy - iFilterWidth;
   //   i32 maxy3 = cy - iFilterWidth / 2;
   i32 max3x1 = maxx1 * 3;
   //   i32 max3x2 = (maxx1 - iFilterHeight) * 3;
   //   i32 max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //i32 bm3Width = (cy * 3 + 3) & ~0x3L;
   //   i32 w = cx * 3;
   //   ::memcpy_dup(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   ::memcpy_dup(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(i32 y = 0; y < cy; y++)
   {
   pSource = pSrc + wSrc * y;



   pDestination = pDst + wDest * y;




   for(i32 x = 0; x < w; x++)
   {
   *pDestination = *pSource;




   pDestination++;


   pSource++;


   }
   }*/
   u32 dwR1;
   u32 dwG1;
   u32 dwB1;
   u32 dwR2;
   u32 dwG2;
   u32 dwB2;

   i32 iFilterXBegin;
   i32 iFilterXEnd;
   i32 iFilterYBegin;
   i32 iFilterYEnd;

   i32 yLowerBound[4];
   i32 yUpperBound[4];
   i32 xLowerBound[4];
   i32 xUpperBound[4];

   // top
   yLowerBound[0] = 0;
   yUpperBound[0] = iFilterWidth / 2;
   xLowerBound[0] = 0;
   xUpperBound[0] = max3x1;

   // left
   yLowerBound[1] = iFilterWidth / 2;
   yUpperBound[1] = maxy1 - iFilterWidth / 2;
   xLowerBound[1] = 0;
   xUpperBound[1] = iFilterWidth / 2;

   // right
   yLowerBound[2] = iFilterWidth / 2;
   yUpperBound[2] = maxy1 - iFilterWidth / 2;
   xLowerBound[2] = max3x1 - iFilterWidth / 2;
   xUpperBound[2] = max3x1;

   // bottom
   yLowerBound[3] = maxy1 - iFilterWidth / 2;
   yUpperBound[3] = maxy1;
   xLowerBound[3] = 0;
   xUpperBound[3] = max3x1;

   /*   for(i32 i = 0; i < 4; i++)
   {
   i32 yL = yLowerBound[i];
   i32 yU = yUpperBound[i];
   i32 xL = xLowerBound[i];
   i32 xU = xUpperBound[i];
   for(i32 y1 = yL; y1 < yU; y1++)
   {
   if(y1 < iFilterWidth / 2)
   {
   iFilterYBegin = iFilterWidth / 2 - y1;
   }
   else
   {
   iFilterYBegin = 0;
   }
   if(y1 > maxy3)
   {
   iFilterYEnd = iFilterWidth - y1 - maxy3;
   }
   else
   {
   iFilterYEnd = iFilterWidth;
   }
   pSource = pSrc + (wSrc * maximum((y1 - iFilterWidth / 2), 0));



   pDestination = pDst + (wDest  * y1);




   for(i32 x1 = xL; x1 < xU; x1+=3)
   {
   if(x1 < iFilterHeight /2)
   {
   iFilterXBegin = iFilterHeight / 2 - x1;
   }
   else
   {
   iFilterXBegin = 0;
   }
   if(x1 > max3x3)
   {
   iFilterXEnd = iFilterHeight  - x1 + max3x3;
   }
   else
   {
   iFilterXEnd = iFilterHeight;
   }
   pSource1 = pSource + ((maximum(x1 - iFilterWidth / 2 * 3, 0)));




   pFilter = pFilter;

   //            pConv = pConv;


   dwR = 0;
   dwG = 0;
   dwB = 0;
   for(i32 y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(i32 x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
   {
   dwR += *pSource2++ * *lpFilter;


   dwG += *pSource2++ * *lpFilter;


   dwB += *pSource2++ * *lpFilter++;



   }
   }
   pDestination_1 = pDestination + x1;



   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin );
   if(divisor == 0)
   {
   pDestination_1[0] = maximum(0, minimum(dwR, 255));


   pDestination_1[1] = maximum(0, minimum(dwG, 255));


   pDestination_1[2] = minimum(0, minimum(dwB, 255));


   }
   else
   {
   pDestination_1[0] = dwR / divisor;


   pDestination_1[1] = dwG / divisor;


   pDestination_1[2] = dwB / divisor;


   }
   }
   }
   }*/

   iFilterYBegin  = 0;
   iFilterYEnd    = iFilterWidth;
   iFilterXBegin = 0;
   iFilterXEnd = iFilterHeight;

   i32 iFilterHalfWidth = iFilterWidth / 2;
   i32 iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   i32 yL = iFilterHalfWidth;
   i32 yU = maxy1 - iFilterHalfWidth;
   i32 xL = iFilterHalfWidthBytes;
   i32 xU = max3x1 - iFilterHalfWidthBytes;


   i32 y1 = yL;
   i32 y2 = yL - iFilterHalfWidth;
   i32 x1;
   i32 x2;

   divisor = 255 * (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

   i32 iRate1 = iAlpha;
   i32 iRate2 = 255 - iAlpha;

   u32 dwR;
   u32 dwG;
   u32 dwB;

   i32 cFilter  = wDest - iFilterWidth * 3;
   i32 cFilter1 = wSrc1 - iFilterWidth * 3;
   i32 cFilter2 = wSrc2 - iFilterWidth * 3;

   i32 iSize3 = iSize * 3;

   for(; y1 < yU;)
   {
      pSource1     = pSrc1 + (wSrc1 * y2);




      pSource2     = pSrc2 + (wSrc2 * y2);




      pDestination = pDst + (wDest * y2);





      x1 = xL;
      x2 = xL - iFilterHalfWidthBytes;

      for(; x1 < xU;)
      {
         pSource1_1 = pSource1 + x2;




         pSource2_1 = pSource2 + x2;






         dwR1 = 0;
         dwG1 = 0;
         dwB1 = 0;
         dwR2 = 0;
         dwG2 = 0;
         dwB2 = 0;
         pSource1_2 = pSource1_1;




         pSource2_2 = pSource2_1;




         i32 yFilter;
         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(i32 xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               dwR1 += *pSource1_2++;


               dwG1 += *pSource1_2++;


               dwB1 += *pSource1_2++;


               dwR2 += *pSource2_2++;


               dwG2 += *pSource2_2++;


               dwB2 += *pSource2_2++;


            }
            pSource1_2 += cFilter1;


            pSource2_2 += cFilter2;


         }

         dwR = (dwR1 * iRate1 + dwR2 * iRate2) / divisor;
         dwG = (dwG1 * iRate1 + dwG2 * iRate2) / divisor;
         dwB = (dwB1 * iRate1 + dwB2 * iRate2) / divisor;

         pDestination_1 = pDestination + x2;



         pDestination_2 = pDestination_1;



         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(i32 xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               pDestination_2[0] = (byte)dwR;


               pDestination_2[1] = (byte)dwG;


               pDestination_2[2] = (byte)dwB;


               pDestination_2 += 3;


            }
            pDestination_2 += cFilter;


         }


         x1 += iSize3;
         x2 += iSize3;
      }
      y1 += iSize;
      y2 += iSize;
   }

}



// dCompress de 0 a 1
bool imaging::HueVRCP(::image * pimage,::color::color crHue,double dCompress)
{

   pimage->map();

   if(pimage->get_data() == nullptr)
   {

      pimage->unmap();

      return false;

   }

   ::color::color cra[256];

   ::color::color color;

   for(i32 i = 0; i < 256; i++)
   {

      color.set_rgb(crHue);

      color.hls_mult(1.0,(i / 255.0) * (1.0 - dCompress) + dCompress,1.0);

      cra[i] = color.get_bgr();

   }

   byte * p = (byte *)pimage->get_data();



   i64 area = pimage->area();

   for(i64 i = 0; i < area; i++)
   {

      *((u32 *)p) = (cra[(p[0] + p[1] + p[2]) / 3]) | p[3] << 24;











      p += 4;



   }

   pimage->unmap();

   return true;

}

//// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
//bool imaging::_desk_to_image(::image* pimage)
//{
//
//   return false;
//
//}
//// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
//bool imaging::_desk_has_image()
//{
//
//   return false;
//
//}

//// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
//bool imaging::_image_to_desk(const ::image* pimage)
//{
//
//   return false;
//
//}


void imaging::AlphaTextOut(::draw2d::graphics *pgraphics,i32 left,i32 top, const ::string & pcsz,i32 len,::color32_t color32,double dBlend)
{

   string str(pcsz,len);

   if (dBlend <= 0.0)
   {

      return;

   }

   auto pbrushText = __create < ::draw2d::brush > ();

   if(dBlend >= 1.0)
   {

      pbrushText->create_solid(color32);

      pgraphics->set(pbrushText);

      pgraphics->text_out(left,top,str);

      return;

   }

   pbrushText->create_solid(argb((byte)(255 * dBlend),colorref_get_r_value(color32),colorref_get_g_value(color32),colorref_get_b_value(color32)));

   pgraphics->set(pbrushText);

   pgraphics->text_out(left,top,str);

}


//#ifndef __APPLE__
//
// ::e_status imaging::_load_image(::context_image * pobject, ::image * pimageParam, const ::payload & varFile, bool bSync, bool bCreateHelperMaps)
// {
//
//   return ::error_failed;
//
// }
//
//
// ::e_status imaging::_load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory)
// {
//
//    return ::error_failed;
//
// }
//
//
// ::e_status imaging::save_image(memory & memory, const ::image * pimage, ::save_image * psaveimage)
// {
//
//    return ::error_failed;
//
// }
//
//
//
//
//
//#endif
//
//#if !defined(WINDOWS_DESKTOP) && !defined(LINUX)
//
//
//hcursor context_image::CreateAlphaCursor(::windowing::window * pwindow, const image * pimage, int xHotSpot, int yHotSpot)
//{
//
//   return 0;
//
//}
//
//
////hcursor context_image::load_default_cursor(enum_cursor ecursor)
////{
////
////   return NULL;
////
////}
////
////
//
//#endif

void context_image::set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot)
{

}






::image_pointer imaging::get_work_image()
{

   synchronous_lock synchronouslock(&m_mutexWork);

   if (m_imageaWork.is_empty())
   {

      synchronouslock.unlock();

      return m_pcontext->context_image()->create_image();

   }

   auto pimpl = m_imageaWork.pop();

   synchronouslock.unlock();

   if (pimpl.is_null())
   {

      pimpl = m_pcontext->context_image()->create_image();

   }

   return pimpl;

}


void imaging::free_work_image(::image * pimage)
{

   if (::is_null(pimage))
   {

      return;

   }

   synchronous_lock synchronouslock(&m_mutexWork);

   m_imageaWork.push(pimage);

}


::e_status context_image::load_svg(::image * pimage, memory & memory)
{

   const char * psz = (const char *)memory.get_data();

   auto size = memory.get_size();

   if (::is_null(psz))
   {

      return pimage->m_estatus;

   }

   if (memmem(psz, size, "<svg", 4) != nullptr)
   {

      char * pszXml = memory.c_str();

      if (pimage->create_nanosvg(pszXml))
      {

         pimage->mult_alpha_fast();

         pimage->on_load_image();

         pimage->set_ok();

         //pimage->notify(OK);

         pimage->m_estatus = ::success;

         return pimage->m_estatus;

      }

   }

   return ::error_failed;

}


