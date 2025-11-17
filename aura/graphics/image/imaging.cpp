#include "framework.h"
#include "imaging.h"
#include "list.h"
#include "fastblur.h"
#include "context.h"
#include "array.h"
#include "acme/graphics/image/image32.h"
#include "acme/graphics/image/pixmap_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/drawing.h"


#ifdef WINDOWS_DESKTOP

//void fastblur(::image::image *ppimg, int radius);

#elif defined(UNIVERSAL_WINDOWS)
//#include <wincodec.h>
//#include <Shcore.h>

#endif

//#ifdef __ANDROID__
//
//#define _stricmp strcasecmp
//
//#endif



#define AC_SRC_ALPHA                0x01


namespace image
{


imaging::imaging()
{

   defer_create_synchronization();

}


imaging::~imaging()
{


}


void imaging::initialize(::particle * pparticle)
{

   //auto estatus =
   
   ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

   øconstruct_new(m_pimageaWork);

}


void imaging::embossed_text_out(
::draw2d::graphics *        pgraphics,
int                 x,
int                 y,
const_char_pointer           pcsz,

size_t                  cb,
::color::color                crText,
::color::color                crShadow,
int                 cx,
int                 cy)
{


   /* If text length is -1, use lstrlen to get the length
    ** of the text.
    */
   if(cb == -1)
      cb = ansi_len(pcsz);


   /* If the shadow or text color is -1, use the
    ** system color for that one.
    */

   //   ::color::color                crOld;
   //   unsigned int                    uMode;
   ::double_size                   sizeText;
   ::int_rectangle                  rectangleText;

   auto psession = session();

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

   rectangleText.left()    = x;
   rectangleText.right()   = int (x + cx + sizeText.cx());
   rectangleText.top()     = y;
   rectangleText.bottom()  = int(y + cy + sizeText.cy());
   //ExtTextOut(hDC, x+cx, y+cy, ETO_OPAQUE, &rectangleText, psz, cb, nullptr);

   //pgraphics->SetBkMode(TRANSPARENT);
   //ExtTextOut(hDC, x-cx, y+cy, nullptr, &rectangleText, psz, cb, nullptr);

   //ExtTextOut(hDC, x-cx, y-cy, nullptr, &rectangleText, psz, cb, nullptr);

   //ExtTextOut(hDC, x+cx, y-cy, nullptr, &rectangleText, psz, cb, nullptr);

   //ExtTextOut(hDC, x+cx, y+cy, nullptr, &rectangleText, psz, cb, nullptr);

   pgraphics->text_out(x + cx,y + cy,string(pcsz,cb));

   //pgraphics->SetBkMode(TRANSPARENT);
   //pgraphics->set_text_color(crText);
   //if(!pgraphics->text_out(x,y, string(pcsz, cb)))
   pgraphics->text_out(x, y, string(pcsz, cb));
   //{
   //   //      informationf("Failed to ExtTextOut, get_last_error() -->%d\n", get_last_error());
   //}

   /* restore the DC
   */
   //pgraphics->set_text_color(crOld);
   //pgraphics->SetBkMode(uMode);


}


//void imaging::GetMultiLineTextExtent(HDC hDC,string_array_base * pArray,LPSIZE32 pSize)
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
//   ::collection::count nSize;
//
//   nSize = pArray->get_size();
//   pSize->cx() = 0;
//
//   ::int_size size;
//   for(nIndex = 0; nIndex < nSize; nIndex++)
//   {
//      const ::scoped_string & scopedstr = pArray->get_at(nIndex);
//      wstring wstr(str);
//      GetTextExtentPoint32W(hDC,wstr,(int)wstr.get_length(),&size);
//      if(size.cx() > pSize->cx())
//
//         pSize->cx() = size.cx();
//
//   }
//   //   pSize->cy() =
//
//   //      (tm.tmHeight +
//   //      tm.tmExternalLeading +
//   //      tm.tmInternalLeading) *
//   nSize;
//   pSize->cy() = (int)((tm.tmHeight + tm.tmExternalLeading) * nSize);
//
//
//#else
//
//   throw ::exception(todo);
//
//#endif
//
//}
//

//void imaging::DrawMultiLineText(HDC hDC,string_array_base * pArray)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   TEXTMETRICW tm;
//
//   GetTextMetricsW(hDC,&tm);
//
//   index nIndex;
//   ::collection::count nSize;
//
//   nSize = pArray->get_size();
//
//   int yPos = 0;
//
//   for(nIndex = 0; nIndex < nSize; nIndex++)
//   {
//
//      const ::scoped_string & scopedstr = pArray->get_at(nIndex);
//      wstring wstr(str);
//      TextOutW(hDC,0,yPos,wstr,(int)wstr.get_length());
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
//   throw ::exception(todo);
//
//#endif
//
//}

//void imaging::GrayVRCP(
//   ::draw2d::graphics * pgraphics,
//   int x,
//   int y,
//   int cx,
//   int cy,
//   ::color::color crAlpha)
//{
//   __UNREFERENCED_PARAMETER(pgraphics);
//   __UNREFERENCED_PARAMETER(x);
//   __UNREFERENCED_PARAMETER(y);
//   __UNREFERENCED_PARAMETER(cx);
//   __UNREFERENCED_PARAMETER(cy);
//   __UNREFERENCED_PARAMETER(crAlpha);
//   throw ::interface_only();
//   ASSERT(false);
//
//   return 0;
//
//}
//
//void imaging::GrayVRCP(
//   ::draw2d::graphics * pgraphics,
//   ::draw2d::bitmap * pitmap,

//   ::draw2d::bitmap * pitmapMask,

//   const ::int_rectangle & rectangle,
//   ::color::color crTransparent)
//{
//
//   return GrayVRCP(
//             pgraphics,
//             pitmap,

//             pitmapMask,

//             rectangle.left(),
//             rectangle.top(),
//             rectangle.right() - rectangle.left(),
//             rectangle.bottom() - rectangle.top(),
//             crTransparent);
//}

/*::image::image_list_pointer imaging::CreateGrayVRCPImageList(
::draw2d::graphics * pgraphics,
::image::image_list_pointer pilGray,
::image::image_list_pointer pilParam)
{
::image::image_list_pointer pil = pilGray;

pil->create(pilParam);

::draw2d::graphics_pointer spgraphics(e_create);

spgraphics->CreateCompatibleDC(pgraphics);

::image::image_list::info ii;

for(int i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
const ::int_rectangle & rectangle = ii.m_rectangle;
GrayVRCP(spgraphics->get_os_data(), ii.hbmImage, ii.hbmMask, rectangle.left(), rectangle.top(), rectangle.width(), rectangle.height(), rgb(192, 192, 192));
}
return pil;

}


void imaging::CreateHueImageList(
::draw2d::graphics * pgraphics,
::image::image_list_pointer pilGray,
::image::image_list_pointer pilParam,
::color::color crHue,
double dCompress)
{
::image::image_list_pointer pil = pilGray;

if(!pil->create(pilParam))
return false;

::draw2d::graphics_pointer spgraphics(e_create);

spgraphics->CreateCompatibleDC(pgraphics);

::image::image_list::info ii;

for(int i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
const ::int_rectangle & rectangle = ii.m_rectangle;
HueVRCP(
spgraphics->get_os_data(),
ii.hbmImage,
rectangle.left(),
rectangle.top(),
rectangle.width(),
rectangle.height(),
crHue,
dCompress);
}
return true;

}*/



void imaging::change_hue(image_list * pilHue, image_list * pil, const ::color::color& crHue,double dCompress)
{

   pilHue->copy_from(pil);

   HueVRCP(pilHue->m_pimage,crHue,dCompress);

   //return true;

}




//
//void imaging::color_blend(::image::image *pimage, const ::color::color& color32, unsigned char bAlpha)
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
::image::image_list_pointer imaging::CreateGrayVRCPImageList(
::draw2d::graphics * pgraphics,
::image::image_list_pointer pilParam)
{
::image::image_list_pointer pil = ___new ::image::image_list ();

pil->create(pilParam);

::draw2d::graphics_pointer spgraphics(e_create);

spgraphics->CreateCompatibleDC(pgraphics);

::image::image_list::info ii;

for(int i = 0; i < pil->get_image_count(); i++)
{
VERIFY(pil->get_image_info(i, &ii));
const ::int_rectangle & rectangle = ii.m_rectangle;
GrayVRCP(spgraphics->get_os_data(), ii.hbmImage, ii.hbmMask, rectangle.left(), rectangle.top(), rectangle.width(), rectangle.height(), rgb(192, 192, 192));
}
return pil;

}

*/


//void imaging::GrayVRCP(
//   ::draw2d::graphics * pgraphics,
//   ::draw2d::bitmap * pitmap,

//   ::draw2d::bitmap * pitmapMask,

//   int x,
//   int y,
//   int cx,
//   int cy,
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
////   //unsigned char uch3dfaceR = ::red(cr3dface);
////   //unsigned char uch3dfaceG = ::green(cr3dface);
////   //unsigned char uch3dfaceB = ::blue(cr3dface);
////   unsigned char uch3dshadowR = ::red(cr3dshadow);
////   unsigned char uch3dshadowG = ::green(cr3dshadow);
////   unsigned char uch3dshadowB = ::blue(cr3dshadow);
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
////   unsigned char uch3dhighlightR = ::red(cr3dhighlight);
////   unsigned char uch3dhighlightG = ::green(cr3dhighlight);
////   unsigned char uch3dhighlightB = ::blue(cr3dhighlight);
////
////   const ::int_size & size = pitmap->get_size();

////
////   unsigned int cbLine = ((size.cx() * 3 + 3) & ~3);
////   unsigned int cbImage = size.cy() * cbLine;
////
////   unsigned int cbMask = size.cy() * ((size.cx() + 3) & ~3);
////
////
////   BITMAPINFO bmi;
////
////   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
////   bmi.bmiHeader.biWidth = size.cx();
////   bmi.bmiHeader.biHeight = - size.cy();
////   bmi.bmiHeader.biPlanes = 1;
////   bmi.bmiHeader.biBitCount = 24;
////   bmi.bmiHeader.biCompression = BI_RGB;
////   bmi.bmiHeader.biSizeImage = 0;
////   bmi.bmiHeader.biXPelsPerMeter = 1;
////   bmi.bmiHeader.biYPelsPerMeter = 1;
////   bmi.bmiHeader.biClrUsed = 0;
////   bmi.bmiHeader.biClrImportant = 0;
////
////   unsigned char * pData = (unsigned char *)malloc(cbImage);


////   unsigned char * pShadow = (unsigned char *)malloc(cbMask);


////   unsigned char * pMask = (unsigned char *)malloc(cbMask);


////   //unsigned char * pShadow = pData;




////
////#ifdef WINDOWS_DESKTOP
////
////   unsigned int uScanLines = size.cy();
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
////   throw ::exception(todo);
////
////#endif
////
////   const ::int_size & sizeMask = pitmapMask->get_size();

////
////   BITMAPINFO * pmiMask = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

////
////   pmiMask->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

////   pmiMask->bmiHeader.biWidth = sizeMask.cx();

////   pmiMask->bmiHeader.biHeight = - sizeMask.cy();

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
////   throw ::exception(todo);
////
////#endif
////
////   //   ::memory_copy(pShadow, pData, cbImage);




////
////   unsigned char * pBase = pData + cbLine * y + x * 3;




////   unsigned char * pBaseShift = pData + cbLine * (y + 1) + (x + 1) * 3;




////   unsigned char * pBaseShadow = pShadow + size.cx() * y + x * 3;




////   unsigned char * pBaseMask = pMask + size.cx() * y + x;




////   unsigned char * pBaseMaskShift = pMask + size.cx() * (y + 1) + (x + 1);




////
////
////   unsigned char br,bg,bb;
////
////   //   ::color::color crBtnFace = crButtonFace;
////   //   ::color::color crBtnShad = crButtonShadow;
////   //   ::color::color crWndBack = psession->get_default_color(COLOR_WINDOW);
////
////   //   unsigned char bRBtnFace = ::red(crBtnFace);
////   //   unsigned char bGBtnFace = ::green(crBtnFace);
////   //   unsigned char bBBtnFace = ::blue(crBtnFace);
////
////   //   unsigned char bRBtnShad = ::red(crBtnShad);
////   //   unsigned char bGBtnShad = ::green(crBtnShad);
////   //   unsigned char bBBtnShad = ::blue(crBtnShad);
////
////   //   unsigned char bRWndBack = ::red(crWndBack);
////   //   unsigned char bGWndBack = ::green(crWndBack);
////   //   unsigned char bBWndBack = ::blue(crWndBack);
////
////   int i;
////   for(i = 0; i < cy; i ++)
////   {
////      unsigned char * pLine = pBase + cbLine * i;




////      unsigned char * pLineShadow = pBaseShadow + size.cx() * i;




////      unsigned char * pLineMask = pBaseMask + size.cy() * i;




////      for(int j = 0; j < cx; j++)
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
////      unsigned char * pLine = pBase + cbLine * i;




////      for(int j = 0; j < cx; j++)
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
////      unsigned char * pLineMask = pBaseMask + size.cx() * i;




////      for(int j = 0; j < cx; j++)
////      {
////         *pLineMask++ = 1;


////      }
////   }
////
////
////
////
////   int cyminus1 = cy - 1;
////   int cxminus1 = cx - 1;
////   unsigned char b;
////
////   for(i = 0; i < cyminus1; i ++)
////   {
////      unsigned char * pLine = pBaseShift + cbLine * i;




////      unsigned char * pLineShadow = pBaseShadow + size.cx() * i;




////      unsigned char * pLineMask = pBaseMaskShift + size.cx() * i;




////      for(int j = 0; j < cxminus1; j++)
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
////      unsigned char * pLine = pBase + cbLine * i;




////      unsigned char * pLineShadow = pBaseShadow + size.cx() * i;




////      unsigned char * pLineMask = pBaseMask + size.cx() * i;




////      for(int j = 0; j < cx; j++)
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
////   throw ::exception(todo);
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

//void imaging::GetDeviceContext24BitsCC(
//   ::draw2d::graphics *pgraphics,
//   BITMAP & bm,
//   BITMAPINFO & bmi,
//   memory & memorystorage,
//   ::draw2d::bitmap * pitmap,

//   const int_rectangle & rectangleParam,
//   int &iWidthParam,
//   unsigned int & uiStartScanLineParam,
//   unsigned int & uiScanLineCountParam,
//   int & iLimitYParam)
//{
//   __UNREFERENCED_PARAMETER(pitmap);

//   ::int_rectangle rectangle(rectangleParam);
//
//   //   int x = rectangle.left();
//   int y = rectangle.top();
//   //   int cx = rectangle.width();
//   int cy = rectangle.height();
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
//         throw ::interface_only();
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
//         int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
//         iWidthParam = iLineBytes;
//         try
//         {
//            memorystorage.set_size(iLineBytes * cy);
//         }
//         catch(memory_exception * pe)
//         {
//            delete pe;
//            throw ::exception(::exception("integer_exception" + as_string($1)));
//         }
//#ifdef WINDOWS_DESKTOP
//
//         LPVOID pv = memorystorage.get_data();

//#endif
//         //       ::int_point pointContext = pgraphics->get_origin();
//
//         unsigned int uStartScanLine = maximum(0,bm.bmHeight - y - cy);
//         unsigned int uScanLines = cy + minimum(0,bm.bmHeight - y - cy);
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
//         throw ::exception(todo);
//
//#endif
//
//      }
//      catch(int)
//      {
//         //         unsigned int user = get_last_error();
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

/*void imaging::GetDeviceContext24BitsAllCC(
::draw2d::graphics *pgraphics,
BITMAP & bm,
BITMAPINFO & bmi,
memory & memorystorage,
::draw2d::bitmap   ** ppbitmap,
::int_rectangle * prectangle,

int &iWidthParam,
unsigned int & uiStartScanLineParam,
unsigned int & uiScanLineCountParam,
int & iLimitYParam)
{

int x = 0;
int y = 0;
int cx = -1;
int cy = -1;

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

throw ::exception(::exception("integer_exception" + as_string($1)));

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
int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
iWidthParam = iLineBytes;
try
{
memorystorage.set_size(iLineBytes * cy);
}
catch(memory_exception * pe)
{
delete pe;
throw ::exception(::exception("integer_exception" + as_string($1)));
}
LPVOID pv = memorystorage.get_data();

::int_point pointContext = pgraphics->get_origin();

unsigned int uStartScanLine = 0;
unsigned int uScanLines = cy;

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
throw ::exception(::exception("integer_exception" + as_string($1)));
}
catch(int)
{
unsigned int user = get_last_error();
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

throw ::exception(::exception("integer_exception" + as_string($1)));
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

throw ::exception(::exception("integer_exception" + as_string($1)));
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
int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;
iWidthParam = iLineBytes;
try
{
memorystorage.set_size(iLineBytes * cy);
}
catch(memory_exception * pe)
{
delete pe;
throw ::exception(::exception("integer_exception" + as_string($1)));
}

LPVOID pv = memorystorage.get_data();


::int_point pointContext;
pointContext = pgraphics->get_origin();
unsigned int uStartScanLine = bm.bmHeight;

uiStartScanLineParam = uiStartScanLine;

//unsigned int uStartScanLine = bm.bmHeight - y - cy;
unsigned int uScanLines = cy;
uiScanLineCountParam = uiScanLines;
int xOffset = (x + pointContext.x) * 3;
//if(!GetDIBits(dcAux.get_os_data(), bitmap, bm.bmHeight - cy, cy, pv, &bmi, DIB_RGB_COLORS))

//  throw ::exception(::exception("integer_exception" + as_string($1)));
int iLimitY = cy;
if(!(iLimitYParam =
GetDIBits(
graphicsMem->get_os_data(),
*pitmap,

uiStartScanLine,
uiScanLines,
pv,

&bmi,
DIB_RGB_COLORS)))
throw ::exception(::exception("integer_exception" + as_string($1)));
int iLimitX = cx;

if(bm.bmWidth - x - pointContext.x < iLimitX)
{
iLimitX = bm.bmWidth - x - pointContext.x;
}

graphicsMem->set(pmpMemOld);

graphicsMem->DeleteDC();
pgraphics->set(pmpOld);

return true;
}
catch(int)
{
return false;
}
}

pgraphics->set(pmpOld);

return true;
}*/

void imaging::BitmapBlend24CC(
unsigned char * pAParam,

int x1,
int y1,
int w1,
int cx,
int cy,
unsigned char * pBParam,

int x2,
int y2,
int w2,
unsigned char * pCParam,

int x3,
int y3,
int w3)
{
   int i,j;
   x1 *= 3;
   x2 *= 3;
   x3 *= 3;
   y1 *= w1;
   y2 *= w2;
   y3 *= w3;

   unsigned char * pA1 = (unsigned char *)pAParam + y1 + x1;

   unsigned char * pB1 = (unsigned char *)pBParam + y2 + x2;

   unsigned char * pC1 = (unsigned char *)pCParam + y3 + x3;


   //   unsigned char dwA;
   for(i = 0; i < cy; i++)
   {

      unsigned char * pA = (unsigned char *)pA1 + (w1 * i);

      unsigned char * pB = (unsigned char *)pB1 + (w2 * i);

      unsigned char * pC = (unsigned char *)pC1 + (w3 * i);

      for(j = 0; j < cx; j++)
      {

         pA[0] = (unsigned char)(((((unsigned int)pA[0]) * ((unsigned int)(255 - pC[0])) + (((unsigned int)pB[0]) * ((unsigned int)pC[0])))) / 255);

         pA[1] = (unsigned char)(((((unsigned int)pA[1]) * ((unsigned int)(255 - pC[1])) + (((unsigned int)pB[1]) * ((unsigned int)pC[1])))) / 255);

         pA[2] = (unsigned char)(((((unsigned int)pA[2]) * ((unsigned int)(255 - pC[2])) + (((unsigned int)pB[2]) * ((unsigned int)pC[2])))) / 255);

         pA+=3;

         pB+=3;

         pC+=3;


      }
   }

}


void imaging::BitmapBlend24CC(
unsigned char * pDestParam,


int xDest,
int yDest,
int wDest,
int cx,
int cy,
unsigned char * pSrcParam,


int xSrc,
int ySrc,
int wSrc,
unsigned char bAlpha)
{
   int i,j;
   xDest *= 3;
   xSrc *= 3;
   yDest *= wDest;
   ySrc *= wSrc;

   //   int maxw = cx * 3;
   //   int cw = (maxw) & ~3;



   int iDestPadding = wDest - cx * 3;
   int iSrcPadding = wSrc - cx * 3;


   pDestParam = (unsigned char *)     pDestParam + yDest + xDest;



   pSrcParam = (unsigned char *)pSrcParam + ySrc + xSrc;




   //   unsigned char bAlphaComplement = 255 - bAlpha;
   //   unsigned char dwA;
   if(bAlpha == 0)
   {
   }
   if(bAlpha == 255)
   {
      for(i = 0; i < cy; i++)
      {
         unsigned char * pDst = (unsigned char *)pDestParam + (wDest * i);



         unsigned char * pSrc = (unsigned char *)pSrcParam + (wSrc * i);



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
      unsigned char * pDst = (unsigned char *)pDestParam;



      unsigned char * pSrc = (unsigned char *)pSrcParam;



      for(i = 0; i < cy; i++)
      {

         for(j = 0; j < cx; j++)
         {
            pDst[0] = (unsigned char)(((((int)pSrc[0] - pDst[0]) * ((int)(bAlpha))) / 256) + (int)pDst[0]);





            pDst[1] = (unsigned char)(((((int)pSrc[1] - pDst[1]) * ((int)(bAlpha))) / 256) + (int)pDst[1]);





            pDst[2] = (unsigned char)(((((int)pSrc[2] - pDst[2]) * ((int)(bAlpha))) / 256) + (int)pDst[2]);





            pDst+=3;


            pSrc+=3;


         }
         pDst = (unsigned char *)pDst + iDestPadding;



         pSrc = (unsigned char *)pSrc + iSrcPadding;



      }
      /*      pushDest = (unsigned short *) pDestParam;



      pushSrc = (unsigned short *) pSrcParam;



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
      unsigned char * pDst = (unsigned char *) lpushDest;


      unsigned char * pSrc = (unsigned char *) lpushSrc;


      for(;j < maxw; j++)
      {
      *pDst++ = (unsigned char) (((unsigned int) (*pSrc++ - *pDst) * ((unsigned int) (bAlpha))) / 256) + *pDst;







      }
      pDst = (unsigned char *) pDestParam + iDestPadding;




      pSrc = (unsigned char *) pSrcParam + iSrcPadding;




      }*/
   }

}



void imaging::BitmapDivBlend(
   ::draw2d::graphics * pdcDst, // destination device
   const ::int_point & pointDst,
   const ::int_size & size,
   ::draw2d::graphics * pdcSrc, // source device
   const ::int_point & pointSrc,
   unsigned char bAlpha)
{

   ::image::image_pointer pimage;

   //auto estatus = 
   øconstruct(pimage);

   /*if (!estatus)
   {

      return false;

   }*/

   //estatus = 
   
   pimage->create(size);

   //if (!estatus)
   //{

   //   return false;

   //}

   {

      ::image::image_source imagesource(pdcSrc);

      double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);
      
      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimage->draw(imagedrawing);

   }

   pimage->DivideRGB(bAlpha);

   {

      ::image::image_source imagesource(pimage, { pointSrc, size });

      ::image::image_drawing_options imagedrawingoptions(::double_rectangle(pointDst, size));

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pdcDst->draw(imagedrawing);

   }

}


//void imaging::bitmap_blend(
//::draw2d::graphics * pdcDst, // destination device
//const ::int_point & pointDst,
//const ::int_size & size,
//::draw2d::graphics * pdcSrc, // source device
//const ::int_point & pointSrc,
//unsigned char bAlpha)
//{
//
//   return pdcDst->alpha_blend(double_rectangle(pointDst, size), pdcSrc, pointSrc, bAlpha / 255.0);
//
//}
//
//
//void imaging::bitmap_blend(::draw2d::graphics * pdcDst,
//                           const ::int_point & pointDst,
//                           const ::int_size & size,
//                           ::image::image *pimage,
//                           const ::int_point & pointSrc,
//                           unsigned char bAlpha)
//{
//
//   return pdcDst->alpha_blend(::double_rectangle(pointDst, size), pimage, pointSrc, bAlpha / 255.0);
//
//}
//

void imaging::ColorInvert(::draw2d::graphics * pgraphics,int x,int y,int cx,int cy)
{


   if (cx <= 0 || cy <= 0)
   {

      //return true;

      throw ::exception(error_failed);

   }

   //return false;

   //    single_lock synchronouslock(&m_csMem, true);

   /*int iOriginalMapMode ;

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
   throw ::exception(::exception("integer_exception" + as_string($1)));
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
   throw ::exception(::exception("integer_exception" + as_string($1)));

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
   int iLineBytes =  (bm.bmWidthBytes + 3) & ~3;
   try
   {
   memstorageA.set_size(iLineBytes * cy);
   }
   catch(memory_exception * pe)
   {
   delete pe;
   throw ::exception(::exception("integer_exception" + as_string($1)));
   }

   LPVOID pv = memstorageA.get_data();


   ::int_point pointContext;
   pointContext = pgraphics->get_origin();
   unsigned int uStartScanLine = bm.bmHeight - y - cy - pointContext.y;
   //unsigned int uStartScanLine = bm.bmHeight - y - cy;
   unsigned int uScanLines = cy;
   int xOffset = (x + pointContext.x) * 3;
   //if(!GetDIBits(dcAux.get_os_data(), bitmapA, bm.bmHeight - cy, cy, pv, &bmi, DIB_RGB_COLORS))

   //  throw ::exception(::exception("integer_exception" + as_string($1)));
   int iLimitY = cy;
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
   int iLimitX = cx;

   if(bm.bmWidth - x - pointContext.x < iLimitX)
   {
   iLimitX = bm.bmWidth - x - pointContext.x;
   }

   unsigned char * p;


   int i, j;
   for(i = 0; i < iLimitY; i++)
   {
   p = (unsigned char *) lpv + (iLineBytes * i) + xOffset;


   for(j = 0; j < iLimitX; j++)
   {
   *p++ = (unsigned char) 255 - *p;




   *p++ = (unsigned char) 255 - *p;




   *p++ = (unsigned char) 255 - *p;




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
   throw ::exception(::exception("integer_exception" + as_string($1)));
   pgraphics->BitBlt(x, y, cx, cy, graphicsMem, 0, 0);
   graphicsMem->set(pmpMemOld);

   graphicsMem->DeleteDC();
   pgraphics->SetMapMode(iOriginalMapMode);
   return true;
   }
   catch(int)
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

   throw ::exception(::exception("integer_exception" + as_string($1)));

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
   int iLineBytes =  ((bm.bmWidth * 3) + 3) & ~3;

   memory memstorageA;
   try
   {
   memstorageA.set_size(iLineBytes * cy);
   }
   catch(memory_exception * pe)
   {
   delete pe;
   throw ::exception(::exception("integer_exception" + as_string($1)));
   }
   LPVOID pv = memstorageA.get_data();

   ::int_point pointContext = pgraphics->get_origin();
   unsigned int uStartScanLine = bm.bmHeight - y - cy - pointContext.y;
   //unsigned int uStartScanLine = bm.bmHeight - y - cy;
   unsigned int uScanLines = cy;
   int xOffset = (x + pointContext.x) * 3;


   //int xOffset = (x) * 3;
   int iLimitY = cy;
   if(!(iLimitY =
   GetDIBits(
   (HDC)pgraphics->get_os_data(),
   (HBITMAP) pmp->get_os_data(),

   uiStartScanLine,
   uiScanLines,
   pv,

   &bmi,
   DIB_RGB_COLORS)))
   throw ::exception(::exception("integer_exception" + as_string($1)));
   int iLimitX = cx;


   if(bm.bmWidth - x - pointContext.x < iLimitX)
   {
   iLimitX = bm.bmWidth - x - pointContext.x;
   }

   unsigned char * p;


   int i, j;
   for(i = 0; i < iLimitY; i++)
   {
   p = (unsigned char *) lpv + (iLineBytes * i) + xOffset;


   if(p < lpv)


   continue;
   for(j = 0; j < iLimitX; j++)
   {
   *p++ = (unsigned char) 255 - *p ;




   *p++ = (unsigned char) 255 - *p;




   *p++ = (unsigned char) 255 - *p;




   }
   }

   if(!SetDIBits((HDC)pgraphics->get_os_data(),
   (HBITMAP) pmp->get_os_data(),

   uiStartScanLine, uiScanLines,
   pv, &bmi, DIB_RGB_COLORS))

   throw ::exception(::exception("integer_exception" + as_string($1)));
   }
   catch(int)
   {
   pgraphics->SetMapMode(iOriginalMapMode);
   return false;
   }
   }
   pgraphics->SetMapMode(iOriginalMapMode);
   return true;*/
}

/*void imaging::allocate(int iSize)
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

//   void imaging::SaveJpeg(const ::scoped_string & scopedstrFile,::draw2d::bitmap_pointer pitmap)


//   {
//
//#ifdef UNIVERSAL_WINDOWS
//
//      throw ::exception(todo);
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
//   void imaging::SavePng(const ::scoped_string & scopedstrFile,::draw2d::bitmap_pointer pitmap)


//   {
//
//#ifdef UNIVERSAL_WINDOWS
//
//      throw ::exception(todo);
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



//   ::draw2d::bitmap_pointer imaging::LoadImageSync(const ::scoped_string & scopedstrImageFilePath,::aura::application * papp)

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




void imaging::clip_color_blend(::draw2d::graphics * pgraphics, const int_rectangle & rectangleParam, const ::color::color & color, unsigned char alpha)
{

   ::int_rectangle rectangle(rectangleParam);

   return clip_color_blend(
          pgraphics,
          rectangle.origin(),
          rectangle.size(),
          color,
          alpha);
}


void imaging::clip_color_blend(::draw2d::graphics * pgraphics,const ::int_point & point,const ::int_size & size, const ::color::color & color,unsigned char bA)
{

   pgraphics->fill_rectangle(int_rectangle(size), color & ::opacity(bA));

   //return true;

}


void imaging::trait(::image::image *pimage, long long iTrait)
{

   return pimage->transform((enum_image)iTrait);

}


//void imaging::color_blend(::draw2d::graphics * pgraphics, const ::long_long_rectangle & rectangle, ::color32_t color32, unsigned char alpha)
//{
//
//   return color_blend(pgraphics,(const ::int_rectangle &)rectangle,color32,alpha);
//
//}


//void imaging::color_blend(::draw2d::graphics * pgraphics, const ::int_rectangle & rectangle, ::color32_t color32, unsigned char alpha)
//{
//
//   return color_blend(pgraphics, rectangle.origin(), rectangle.size(), color32, alpha);
//
//}


//void imaging::color_blend(::draw2d::graphics * pgraphics,int x,int y,int cx,int cy,::color32_t color32,unsigned char bA)
//{
//
//   return color_blend(pgraphics,int_point(x,y),int_size(cx,cy),color32,bA);
//
//}


//void imaging::color_blend(::draw2d::graphics * pgraphics,const ::int_point & point,const ::int_size & size,::color32_t color32,unsigned char bA)
//{
//
//   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//   pgraphics->fill_rectangle(int_rectangle(point, size), (color32 & 0x00ffffff) | (bA << 24));
//
//   return true;
//
//}


//void imaging::CreateBitmap(::draw2d::graphics * pgraphics, ::draw2d::graphics * pdcScreen, ::draw2d::bitmap * pbitmap, ::draw2d::bitmap * pbitmapOld, int cx, int cy)
//{
//   
//   int cxout = cx;
//
//   int cyout = cy;
//
//   pgraphics->set(pbitmapOld);
//
//   bool bCreate = true;
//
//   if(pbitmap->get_os_data() != nullptr)
//   {
//
//      const ::int_size & size = pbitmap->get_size();
//
//      if(size.cx() >= cx && size.cy() >= cy)
//      {
//
//         bCreate = false;
//
//      }
//
//   }
//
//   if(bCreate)
//   {
//
//      if(!pbitmap->CreateCompatibleBitmap(pdcScreen,cxout,cyout))
//      {
//
//         //return false;
//
//      }
//
//   }
//
//   //if(!pgraphics->set(pbitmap))
//   pgraphics->set(pbitmap);
//   //{
//
//   //   if(!pbitmap->CreateCompatibleBitmap(pdcScreen, cxout, cyout))
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //   if(!pgraphics->set(pbitmap))
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //}
//
//   if(bCreate)
//   {
//
//      pgraphics->fill_rectangle(int_rectangle(0,0,cxout,cyout), 0);
//
//   }
//
//   return true;
//
//}
//
//
//void imaging::CreateBitmap(::draw2d::graphics *pgraphics,::draw2d::bitmap * pitmapOld,::draw2d::bitmap *pitmap,int cx,int cy)
//{
//
//   int cxout = cx;
//
//   int cyout = cy;
//
//   pgraphics->set(pitmapOld);
//
//   bool bCreate = true;
//
//   if(pitmap->get_os_data())
//   {
//
//      const ::int_size & size = pitmap->get_size();
//
//      if(size.cx() >= cx && size.cy() >= cy)
//      {
//
//         bCreate = false;
//
//      }
//
//   }
//
//   if(bCreate)
//   {
//
//      if(!pitmap->CreateCompatibleBitmap(pgraphics,cxout,cyout))
//      {
//
//         return false;
//
//      }
//
//   }
//
//   //if(!pgraphics->set(pitmap))
//
//   pgraphics->set(pitmap);
//   //{
//
//   //   if(!pitmap->CreateCompatibleBitmap(pgraphics,cxout,cyout))
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //   if(!pgraphics->set(pitmap))
//   //   {
//
//   //      return false;
//
//   //   }
//
//   //}
//
//   if(bCreate)
//   {
//
//      ::color::color color(255, 196, 255);
//
//      pgraphics->fill_rectangle(int_rectangle(0,0,cxout,cyout), color);
//
//   }
//
//   return true;
//
//}


void imaging::blur(::image::image *pimage, int iRadius)
{

   if (!pimage->is_ok())
   {

      throw ::exception(error_bad_argument);

   }

   ::image::fastblur f;

   f.initialize(pimage->size(), iRadius);

   f.blur(pimage);

   //return true;

}


void imaging::blur(::image::image *pimage, int_rectangle rectangle, int iRadius)
{

   if (!pimage->is_ok())
   {

      throw ::exception(error_bad_argument);

   }

   ::image::fastblur fastblur;

   fastblur.initialize(rectangle.size(), abs(iRadius));
      //return false;

   {

      pixmap_lock lock(pimage, rectangle);

      //fastblur.initialize(pimage->size(), iRadisu)

      fastblur.blur(pimage);

   }

   //return true;

}


void imaging::blur_32CC(::image::image *pimageDst, ::image::image *pimageSrc,int iRadius)
{
   int iFilterWidth = iRadius * 2 + 1;
   int iFilterHeight = iRadius * 2 + 1;
   int divisor = iFilterWidth * iFilterHeight;
   unsigned char *pSource;


   unsigned char *pDestination;


   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pFilter;

   unsigned char * pFilterData = øraw_new  unsigned char[iFilterHeight *iFilterWidth];
   memory_set(pFilterData,1,iFilterHeight * iFilterWidth);

   unsigned char * pSrc = (unsigned char *)pimageSrc->get_data();


   unsigned char * pDst = (unsigned char *)pimageDst->get_data();


   int cx = pimageSrc->width();
   int cy = pimageSrc->height();
   //int wSrc = cx * 4;
   //int wDest = cx * 4;
   int wSrc = pimageSrc->scan_size();
   int wDest = pimageDst->scan_size();
   int maxx1 = cx;
   int maxy1 = cy;
   //   int maxy2 = cy - iFilterWidth;
   //   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 4;
   //   int max3x2 = (maxx1 - iFilterHeight) * 4;
   //   int max3x3 = (maxx1 - iFilterHeight / 2) * 4;
   //int bm3Width = (cy * 3 + 3) & ~0x3L;
   //   int w = cx * 3;
   //   ::memory_copy(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   ::memory_copy(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(int y = 0; y < cy; y++)
   {
   pSource = pSrc + wSrc * y;



   pDestination = pDst + wDest * y;




   for(int x = 0; x < w; x++)
   {
   *pDestination = *pSource;




   pDestination++;


   pSource++;


   }
   }*/
   unsigned int dwR;
   unsigned int dwG;
   unsigned int dwB;
   unsigned int dwA;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLowerBound[4];
   int yUpperBound[4];
   int xLowerBound[4];
   int xUpperBound[4];

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

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLowerBound[i];
   int yU = yUpperBound[i];
   int xL = xLowerBound[i];
   int xU = xUpperBound[i];
   for(int y1 = yL; y1 < yU; y1++)
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




   for(int x1 = xL; x1 < xU; x1+=3)
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
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
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

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

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
         for(int yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            pSource2 = pSource1 + (wSrc * yFilter);



            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
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


void imaging::blur_32CC_r2(::image::image *pimageDst, ::image::image *pimageSrc)
{

   unsigned char * pSrc = (unsigned char *)pimageSrc->get_data();


   unsigned char * pDst = (unsigned char *)pimageDst->get_data();



   int cx = pimageSrc->width();
   int cy = pimageSrc->height();
   //int wSrc = cx * 4;
   //int wDest = cx * 4;
   int wSrc = pimageSrc->scan_size();
   int wDest = pimageDst->scan_size();

   unsigned char *pSource;


   unsigned char *pDestination;


   unsigned char *pSource1;


   unsigned char *pSource2[5];




   if(cx <= 0)
      return;
   if(cy <= 0)
      return;

   int maxx1 = cx;
   int maxy1 = cy;
   //   int maxy2 = cy - 5;
   //   int maxy3 = cy - 2;
   int max3x1 = maxx1 * 4;
   //   int max3x2 = (maxx1 - 5) * 4;
   ///   int max3x3 = (maxx1 - 2) * 4;
   //   int w = cx * 3;
   //unsigned int dwR;
   //unsigned int dwG;
   //unsigned int dwB;
   //unsigned int dwA;

   int yL = 2;
   int yU = maxy1 - 2;
   int xL = 8;
   int xU = max3x1 - 8;


   int y1 = 2;
   int y2 = yL - 2;
   int x1;
   int x2;

   for(; y1 < yU;)
   {
      pSource = pSrc + (wSrc * y2);




      x1 = xL;
      x2 = xL - 8;
      pDestination = pDst + (wDest  * y1) + x1;




      for(; x1 < xU;)
      {
         pSource1 = pSource + x2;




         //dwR = 0;
         //dwG = 0;
         //dwB = 0;
         //dwA = 0;
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


void imaging::channel_gray_blur(::draw2d::graphics *pdcDst,const ::int_point & pointDst,const ::int_size & size,::draw2d::graphics * pdcSrc,const ::int_point & pointSrc,int iChannel,int iRadius)
{

   if (size.cx() <= 0 || size.cy() <= 0)
   {

      throw ::exception(error_wrong_state);

   }

   ::image::image_pointer pimageDst = image()->create_image(size);

   if (!pimageDst)
   {

      throw ::exception(error_wrong_state);

   }

   ::image::image_pointer pimageSrc = image()->create_image(size);

   if (!pimageSrc)
   {

      throw ::exception(error_wrong_state);

   }

   pimageSrc->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   ::image::image_source imagesource(pdcSrc, ::double_rectangle(pointSrc, size));

   double_rectangle rectangle(size);

   ::image::image_drawing_options imagedrawingoptions(rectangle);

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   //if (!pdcSrc->draw(imagedrawing))
   pdcSrc->draw(imagedrawing);
   //{

   //   return false;

   //}

   //if(!
   
   channel_gray_blur_32CC(
      pimageDst,
      pimageSrc,
      iChannel,
      iRadius);
//      return false;

   {

      ::image::image_source imagesource(pimageDst);

      double_rectangle rectangle(pointDst, size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      //if (!pdcDst->draw(imagedrawing))
      pdcDst->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   //return true;

}


void imaging::channel_alpha_gray_blur(::draw2d::graphics * pdcDst, const ::int_point & pointDst, const ::int_size & size, ::draw2d::graphics * pdcSrc, const ::int_point & pointSrc, int iChannel, int iRadius)
{

   if (size.area() <= 0)
   {

      throw ::exception(error_wrong_state);

   }

   ::image::image_pointer pimageDst = image()->create_image(size);

   if (!pimageDst)
   {

      throw ::exception(error_wrong_state);

   }

   ::image::image_pointer pimageSrc = image()->create_image(size);

   if (!pimageSrc)
   {

      throw ::exception(error_wrong_state);

   }

   pimageSrc->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   {

      ::image::image_source imagesource(pdcSrc, ::double_rectangle(pointSrc, size));

      ::double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimageSrc->g()->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   /*if (!*/channel_alpha_gray_blur_32CC(
      pimageDst,
      pimageSrc,
      iChannel,
      iRadius)/*)
      return false*/;

   {

      ::image::image_source imagesource(pimageDst);

      double_rectangle rectangle(pointDst, size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      /*if (!*/pdcDst->draw(imagedrawing);/*
      {

         return false*/;

      /*}*/

   }

   /*return true;*/

}


void imaging::channel_gray_blur_32CC(::image::image *pimageDst, ::image::image *pimageSrc,
                                     int iChannel,int iRadius)
{

   if(iRadius <= 0)
      throw ::exception(error_wrong_state);

   int cx = pimageDst->width();
   int cy = pimageDst->height();

   if(cx != pimageSrc->width()
         || cy != pimageSrc->height())
      throw ::exception(error_wrong_state);

   unsigned char * pDst = (unsigned char *)pimageDst->get_data();


   unsigned char * pSrc = (unsigned char *)pimageSrc->get_data();



   //int wSrc = cx * 4;
   //int wDst = cx * 4;
   int wSrc = pimageSrc->scan_size();
   int wDst = pimageDst->scan_size();

   int iFilterW = iRadius * 2 + 1;
   int iFilterH = iRadius * 2 + 1;
   int iFilterHalfW = iRadius;
   int iFilterHalfH = iRadius;
   //   int iFilterArea = iFilterW * iFilterH;
   int iDivisor;

   unsigned char *pDestination;


   unsigned char *pDestination_1;




   unsigned char *pSource;


   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pSource_3;



   unsigned int dwI;

   int x,y;
   //int x2;
   int x3;
   int iFilterXLowerBound;
   int iFilterXUpperBound;
   int iFilterYLowerBound;
   int iFilterYUpperBound;
   int xFilter;
   int yFilter;

   int xLowerBound[4];
   int xUpperBound[4];
   int yLowerBound[4];
   int yUpperBound[4];

   int xmax = cx - 1;
   int ymax = cy - 1;

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


   int iFilterLine;

   for(int i = 0; i < 4; i++)
   {
      int xL = xLowerBound[i];
      int xU = xUpperBound[i];
      int yL = yLowerBound[i];
      int yU = yUpperBound[i];
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
         //x2 = x - iFilterHalfW;
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
               pDestination_1[0] = (unsigned char)maximum(0u,minimum(dwI,255u));


               pDestination_1[1] = (unsigned char)maximum(0u,minimum(dwI,255u));


               pDestination_1[2] = (unsigned char)minimum(0u,minimum(dwI,255u));


            }
            else
            {
               pDestination_1[0] = (unsigned char)(dwI / iDivisor);


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

   int yL = iFilterHalfH;
   int yU = cy - iFilterHalfH + (iFilterHalfH % 2 == 1 ? 0 : 1);
   int xL = iFilterHalfW;
   int xU = cx - iFilterHalfW + (iFilterHalfW % 2 == 1 ? 0 : 1);

   int y1 = yL;
   int x1;

   iDivisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);

   int wDiff = wDst - (xU - xL) * 4;
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


         for(int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
         {
            pSource_3 = pSource2;




            for(int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
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

   //return true;

}


void imaging::channel_alpha_gray_blur_32CC(::image::image *pimageDst, ::image::image *pimageSrc,
      int iChannel,int iRadius)
{

   if(iRadius <= 0)
      throw ::exception(error_wrong_state);

   int cx = pimageDst->width();
   int cy = pimageDst->height();

   if(cx != pimageSrc->width()
         || cy != pimageSrc->height())
      throw ::exception(error_wrong_state);

   pimageDst->map();

   pimageSrc->map();

   unsigned char * pDst = (unsigned char *)pimageDst->get_data();


   unsigned char * pSrc = (unsigned char *)pimageSrc->get_data();



   //int wSrc = cx * 4;
   //int wDst = cx * 4;
   int wSrc = pimageSrc->scan_size();
   int wDst = pimageDst->scan_size();

   int iFilterW = iRadius * 2 + 1;
   int iFilterH = iRadius * 2 + 1;
   int iFilterHalfW = iRadius;
   int iFilterHalfH = iRadius;
   //   int iFilterArea = iFilterW * iFilterH;
   int iDivisor;

   unsigned char *pDestination;


   unsigned char *pDestination_1;




   unsigned char *pSource;


   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pSource_3;



   unsigned int dwI;

   int x,y;
   //int x2;
   int x3;
   int iFilterXLowerBound;
   int iFilterXUpperBound;
   int iFilterYLowerBound;
   int iFilterYUpperBound;
   int xFilter;
   int yFilter;

   int xLowerBound[4];
   int xUpperBound[4];
   int yLowerBound[4];
   int yUpperBound[4];

   int xmax = cx - 1;
   int ymax = cy - 1;

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


   int iFilterLine;

   for(int i = 0; i < 4; i++)
   {
      int xL = xLowerBound[i];
      int xU = xUpperBound[i];
      int yL = yLowerBound[i];
      int yU = yUpperBound[i];
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
         //x2 = x - iFilterHalfW;
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
               pDestination_1[0] = (unsigned char)maximum(0u,minimum(dwI,255u));


               pDestination_1[1] = (unsigned char)maximum(0u,minimum(dwI,255u));


               pDestination_1[2] = (unsigned char)minimum(0u,minimum(dwI,255u));


               pDestination_1[3] = (unsigned char)minimum(0u,minimum(dwI,255u));


            }
            else
            {
               pDestination_1[0] = (unsigned char)(dwI / iDivisor);


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

   int yL = iFilterHalfH;
   int yU = cy - iFilterHalfH;
   int xL = iFilterHalfW;
   int xU = cx - iFilterHalfW;

   int y1 = yL;
   int x1;

   iDivisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);

   int wDiff = wDst - (xU - xL) * 4;
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


         for(int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
         {
            pSource_3 = pSource2;




            for(int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
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

   //return true;

}


void imaging::channel_gray_blur(
::draw2d::graphics * pdcDst,
const ::int_point & pointDst,
const ::int_size & size,
::draw2d::graphics * pdcSrc,
const ::int_point & pointSrc,
int iChannel,
const ::int_size & sizeFilter,
unsigned char * pFilter)
{

   if (size.cx() <= 0 || size.cy() <= 0)
   {

      throw ::exception(error_wrong_state);

   }

   ::image::image_pointer pimageDst = image()->create_image(size);

   if (!pimageDst)
   {

      throw ::exception(error_wrong_state);

   }

   ::image::image_pointer pimageSrc = image()->create_image(size);

   if (!pimageSrc)
   {

      throw ::exception(error_wrong_state);

   }

   {

      ::image::image_source imagesource(pimageSrc, ::double_rectangle(pointSrc, size));

      double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      /*if (!*/pdcSrc->draw(imagedrawing);/*)
      {

         throw ::exception(error_wrong_state);

      }*/

   }

   channel_gray_blur_32CC(
      pimageDst,
      pimageSrc,
      iChannel,
      sizeFilter.cx(),
      sizeFilter.cy(),
      pFilter);
   /*{

      return false;

   }*/


   {

      ::image::image_source imagesource(pimageDst, ::double_rectangle(pointDst, size));

      double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pdcDst->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   //return true;

}


void imaging::channel_gray_blur_32CC(::image::image *pimageDst, ::image::image *pimageSrc,
                                     int iChannel,
                                     int iFilterWidth,
                                     int iFilterHeight,
                                     unsigned char * pFilterParam)


{

   int cx = pimageDst->width();
   int cy = pimageDst->height();

   if(cx != pimageSrc->width()
         || cy != pimageSrc->height())
      throw ::exception(error_wrong_state);

   unsigned char * pDst = (unsigned char *)pimageDst->get_data();


   unsigned char * pSrc = (unsigned char *)pimageSrc->get_data();



   //int wSrc = cx * 4;
   //int wDst = cx * 4;
   int wSrc = pimageSrc->scan_size();
   int wDst = pimageDst->scan_size();

   int iFilterArea = iFilterWidth * iFilterHeight;
   int divisor;

   unsigned char *pDestination;




   unsigned char *pSource;


   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pSource_3;



   unsigned char *pFilter;

   unsigned char * pFilterData = øraw_new unsigned char [iFilterHeight *iFilterWidth];

   memory_set(pFilterData,1,iFilterHeight * iFilterWidth);

   int maxx1 = cx;
   int maxy1 = cy;
   //   int maxy2 = cy - iFilterWidth;
   //   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 4;
   //   int max3x2 = (maxx1 - iFilterHeight) * 4;
   //   int max3x3 = (maxx1 - iFilterHeight / 2) * 4;
   //int bm3Width = (cy * 3 + 3) & ~0x3L;
   //   int w = cx * 4;
   //   ::memory_copy(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   ::memory_copy(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(int y = 0; y < cy; y++)
   {
   pSource = pSrc + wSrc * y;



   pDestination = pDst + wDest * y;




   for(int x = 0; x < w; x++)
   {
   *pDestination = *pSource;




   pDestination++;


   pSource++;


   }
   }*/
   unsigned int dwI;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLowerBound[4];
   int yUpperBound[4];
   int xLowerBound[4];
   int xUpperBound[4];

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

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLowerBound[i];
   int yU = yUpperBound[i];
   int xL = xLowerBound[i];
   int xU = xUpperBound[i];
   for(int y1 = yL; y1 < yU; y1++)
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




   for(int x1 = xL; x1 < xU; x1+=3)
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
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
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



   for(int i = 0; i < iFilterArea; i++)
   {
      divisor += *pFilter++;

   }

   int iFilterHalfWidth = iFilterWidth / 2;
   //   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = cy - iFilterHalfWidth;
   int xL = iFilterHalfWidth;
   int xU = cx - iFilterHalfWidth;


   int y1 = yL;
   //int y2 = yL - iFilterHalfWidth;
   int x1;
   //int x2;

   divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

   int wDiff = wDst - (xU - xL) * 4;
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


         for(int yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            pSource_3 = pSource2;




            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
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

   //return true;

}



//void imaging::color_blend(::draw2d::graphics * pgraphics,const ::int_rectangle & rectangle,::draw2d::graphics * pdcColorAlpha,const ::int_point & pointAlpha, ::image::image *pimageWork)
//{
//
//   return pgraphics->stretch(rectangle, pdcColorAlpha, ::double_rectangle(pointAlpha, rectangle.size()));
//
//}


void imaging::true_blend(::draw2d::graphics * pgraphics,const ::int_rectangle & rectangle,::draw2d::graphics * pdcColorAlpha,const ::int_point & pointAlpha, ::image::image *pimageWork, ::image::image *pimageWork2, ::image::image *pimageWork3)
{

   ::image::image_source imagesource(pdcColorAlpha, { pointAlpha, rectangle.size() } );

   ::image::image_drawing_options imagedrawingoptions(rectangle);

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   return pgraphics->draw(imagedrawing);

}

// COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

/*
void imaging::color_blend(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size, ::draw2d::graphics * pdcColorAlpha, const ::int_point & pointAlpha, ::image::image *pimageWork, ::image::image *pimageWork2)
{






}
*/


//void imaging::color_blend(::draw2d::graphics * pgraphics, const ::int_point & pointParam,const ::int_size & size,::draw2d::graphics * pdcColorAlpha,const ::int_point & pointAlphaParam,double dBlend)
//{
//
//   ::int_point point(pointParam);
//
//   ::int_point pointAlpha(pointAlphaParam);
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
//      return pgraphics->draw(::double_rectangle(point, size), pdcColorAlpha, pointAlpha) != false;
//
//   }
//   else
//   {
//
//      ::image::image_pointer pimage = image()->create_image(size);
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
//      pimage->g()->stretch(::double_rectangle(size), pdcColorAlpha, ::double_rectangle(pointAlpha, size));
//
//      pimage->channel_multiply(dBlend, ::color::e_channel_opacity);
//
//      return pgraphics->draw(::double_rectangle(point, size), pimage) != false;
//
//   }
//
//}
//
//
//void imaging::color_blend(::draw2d::graphics * pgraphics,const int_rectangle & rectangleParam,::draw2d::graphics * pdcColorAlpha,const ::int_point & pointAlpha,double dBlend)
//{
//
//   ::int_rectangle rectangle(rectangleParam);
//
//   return color_blend(pgraphics,rectangle.top_left(),rectangle.size(),pdcColorAlpha,pointAlpha,dBlend);
//
//}



void imaging::color_blend_24CC(
unsigned char * pAParam,

int x1,
int y1,
int w1,
int cx,
int cy,
::color32_t color32,
unsigned char * pCParam,

int x3,
int y3,
int w3)
{
   int i,j;
   x1 *= 3;
   x3 *= 3;
   y1 *= w1;
   y3 *= w3;

   unsigned char bR = color32.byte_red();
   unsigned char bG = color32.byte_green();
   unsigned char bB = color32.byte_blue();

   pAParam = (unsigned char *)pAParam + y1 + x1;



   pCParam = (unsigned char *)pCParam + y3 + x3;




   //   unsigned char dwA;
   for(i = 0; i < cy; i++)
   {
      unsigned char * pA = (unsigned char *)pAParam + (w1 * i);




      unsigned char * pC = (unsigned char *)pCParam + (w3 * i);




      for(j = 0; j < cx; j++)
      {
         pA[0] = (unsigned char)(((((unsigned int)pA[0]) * ((unsigned int)(255 - pC[0])) + (((unsigned int)bB) * ((unsigned int)pC[0])))) / 255);








         pA[1] = (unsigned char)(((((unsigned int)pA[1]) * ((unsigned int)(255 - pC[1])) + (((unsigned int)bG) * ((unsigned int)pC[1])))) / 255);








         pA[2] = (unsigned char)(((((unsigned int)pA[2]) * ((unsigned int)(255 - pC[2])) + (((unsigned int)bR) * ((unsigned int)pC[2])))) / 255);








         pA += 3;


         pC += 3;


      }
   }

}





//void imaging::alpha_spread_R2(::draw2d::graphics *pdcDst,const ::int_point & pointDst,const ::int_size & size,::draw2d::graphics * pdcSrc,const ::int_point & pointSrc,unsigned char bMin)
//{
//   if(size.cx() <= 0 || size.cy() <= 0)
//      return true;
//
//   unsigned int user;
//   unsigned int uStartScanLine;
//   unsigned int uScanLineCount;
//
//
//   ::int_rectangle rectangleTarget(pointDst, size);
//   ::int_rectangle rectangleSource(pointSrc, size);
//
//   int iwDest;
//
//   BITMAPINFO bmiDst;
//   BITMAP   bmDst;
//   int iLimitYDst;
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
//   unsigned char * pDst = memstorageA.get_data();


//
//
//   int iwSrc;
//
//   BITMAPINFO bmiSrc;
//   BITMAP   bmSrc;
//   int iLimitYSrc;
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
//   unsigned char * pSrc = memstorageB.get_data();


//
//
//   const ::int_point & pointContextDst = pdcDst->get_origin();
//   const ::int_point & pointContextSrc = pdcSrc->get_origin();
//
//   int xvpDst = pointDst.x + pointContextDst.x;
//   int xvpSrc = pointSrc.x + pointContextSrc.x;
//
//   int iLimitX = size.cx();
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
//   int iLimitY = minimum(iLimitYDst,iLimitYSrc);
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
//         throw ::exception(::exception("integer_exception" + as_string($1)));
//      ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapDst);

//      if(!pdcDst->BitBlt(pointDst.x,pointDst.y,size.cx(),size.cy(),graphicsMem,pointSrc.x,pointSrc.y))
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
//         throw ::exception(::exception("integer_exception" + as_string($1)));
//      pdcDst->set(bitmapDst);
//   }
//
//#else
//
//   throw ::exception(todo);
//
//#endif
//
//   return true;
//
//}


//void imaging::alpha_spread(::draw2d::graphics *pdcDst,const ::int_point & pointDst,const ::int_size & size,::draw2d::graphics * pdcSrc,const ::int_point & pointSrc,unsigned char bMin,int iRadius)
//{
//
//   if(size.cx() <= 0 || size.cy() <= 0)
//      return true;
//
//   //   single_lock synchronouslock(&m_csMem, true);
//
//
//   unsigned int user;
//   unsigned int uStartScanLine;
//   unsigned int uScanLineCount;
//
//
//   ::int_rectangle rectangleDest(pointDst, size);
//   ::int_rectangle rectangleSource(pointSrc, size);
//
//   int iwDest;
//
//   BITMAPINFO bmiDest;
//   BITMAP   bmDest;
//   int iLimitYDest;
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
//   unsigned char * pDst = memstorageA.get_data();


//
//
//   int iwSrc;
//
//   BITMAPINFO bmiSrc;
//   BITMAP   bmSrc;
//   int iLimitYSrc;
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
//   unsigned char * pSrc = memstorageB.get_data();


//
//
//   const ::int_point & pointContextDest = pdcDst->get_origin();
//   const ::int_point & pointContextSrc = pdcSrc->get_origin();
//
//   int xvpDest = pointDst.x + pointContextDest.x;
//   int xvpSrc = pointDst.y + pointContextSrc.x;
//
//   int iLimitX = size.cx();
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
//   int iLimitY = minimum(iLimitYDest,iLimitYSrc);
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
//         throw ::exception(::exception("integer_exception" + as_string($1)));
//      ::draw2d::bitmap * pmpMemOld = graphicsMem->set(bitmapDest);

//      if(!pdcDst->BitBlt(pointDst.x,pointDst.y,size.cx(),size.cy(),graphicsMem,pointSrc.x,pointSrc.y))
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
//         throw ::exception(::exception("integer_exception" + as_string($1)));
//      pdcDst->set(bitmapDest);
//   }
//
//   return true;
//
//#else
//
//   throw ::exception(todo);
//
//#endif
//
//}


void imaging::alpha_spread_R2_24CC(unsigned char * pDst,int xDest,int yDest,int wDest,int cx,int cy,unsigned char * pSrc,int xSrc,int ySrc,int wSrc,unsigned char bMin)



{

   __UNREFERENCED_PARAMETER(xDest);
   __UNREFERENCED_PARAMETER(yDest);
   __UNREFERENCED_PARAMETER(xSrc);
   __UNREFERENCED_PARAMETER(ySrc);
   int iFilterWidth = 2 * 2 + 1;
   int iFilterHeight = 2 * 2 + 1;
   //int divisor = iFilterWidth * iFilterHeight;
   unsigned char *pSource;


   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pDestination;


   //unsigned char *pFilter;

   unsigned char * pFilterData = øraw_new  unsigned char[iFilterHeight *iFilterWidth];
   memory_set(pFilterData,1,iFilterHeight * iFilterWidth);

   int maxx1 = cx;
   int maxy1 = cy;
   //   int maxy2 = cy - iFilterWidth;
   //   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 3;
   //   int max3x2 = (maxx1 - iFilterHeight) * 3;
   //   int max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //   int w = cx * 3;
   unsigned int dwR;
   unsigned int dwG;
   unsigned int dwB;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLowerBound[4];
   int yUpperBound[4];
   int xLowerBound[4];
   int xUpperBound[4];

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

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   unsigned int bMin3 = bMin * 3;

   //divisor = (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

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




         //pFilter = pFilterData;


         dwR = 0;
         dwG = 0;
         dwB = 0;
         bSpread = false;
         for(int yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            pSource2 = pSource1 + (wSrc * yFilter);


            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
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
            *((unsigned int *)pDestination) |= 0x00ffffff;


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



void imaging::channel_spread(
::draw2d::graphics *pdcDst,
const ::int_point & pointDst,
const ::int_size & size,
::draw2d::graphics * pdcSrc,
const ::int_point & pointSrc,
int iChannel,int iRadius)
{

   return channel_spread_set_color(
          pdcDst,
          pointDst,
          size,
          pdcSrc,
          pointSrc,
          iChannel,
          iRadius,
          ::color::white);

}


void imaging::channel_spread_set_color(
::draw2d::graphics *pdcDst,
const ::int_point & pointDst,
const ::int_size & size,
::draw2d::graphics * pdcSrc,
const ::int_point & pointSrc,
int iChannel,int iRadius,
const ::color::color & color)
{

   if (size.is_empty())
      throw ::exception(error_bad_argument);

   ::image::image_pointer pimageDst = image()->create_image(size);

   ::image::image_pointer pimageSrc = image()->create_image(size);

   pimageSrc->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   {

      ::image::image_source imagesource(pdcSrc, ::double_rectangle(pointSrc, size));

      ::double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      //if (!)
      pimageSrc->g()->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   auto psystem = system();

   auto pdraw2d = psystem->draw2d();

   /*if (!*/pdraw2d->channel_spread__32CC(
      pimageDst,
      pimageSrc,
      iChannel,
      iRadius, color);
   //{

   //   return false;

   //}

   {

      ::image::image_source imagesource(pimageDst, ::double_rectangle(pointDst, size));

      ::double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pdcDst->draw(imagedrawing);
      //if (!)
      //{

      //   return false;

      //}

   }

   //return true;

}


void imaging::spread(
::draw2d::graphics *pdcDst,
const ::int_point & pointDst,
const ::int_size & size,
::draw2d::graphics * pdcSrc,
const ::int_point & pointSrc,
int iRadius)
{

   return spread_set_color(
          pdcDst,
          pointDst,
          size,
          pdcSrc,
          pointSrc,
          iRadius,
          color::white);

}


void imaging::spread_set_color(
::draw2d::graphics *pdcDst,
const ::int_point & pointDst,
const ::int_size & size,
::draw2d::graphics * pdcSrc,
const ::int_point & pointSrc,
int iRadius,
const ::color::color & color)
{

   if (size.is_empty())
      throw ::exception(error_bad_argument);

   ::image::image_pointer pimageDst = image()->create_image(size);

   ::image::image_pointer pimageSrc = image()->create_image(size);

   pimageSrc->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   {

      ::image::image_source imagesource(pdcSrc, ::double_rectangle(pointSrc, size));

      ::double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimageSrc->g()->draw(imagedrawing);
      //if (!pimageSrc->g()->draw(imagedrawing))
      //{

      //   return false;

      //}

   }

   //if (!
   spread__32CC(
      pimageDst,
      pimageSrc,
      iRadius, color);
   //{

   //   return false;

   //}

   {

      ::image::image_source imagesource(pimageDst, ::double_rectangle(pointDst, size));

      ::double_rectangle rectangle(size);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pdcDst->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   //return true;

}


void imaging::spread__32CC(::image::image *pimageDst, ::image::image *pimageSrc,int iRadius, const ::color::color& colorSpreadSetColor)
{

   if (iRadius <= 1)
   {

      //throw ::exception(error_bad_argument);
      
      return;

   }

   if (iRadius > 1024)
   {

      iRadius = 1024;

   }

   int iFilterW      = iRadius * 2 + 1;
   int iFilterH      = iRadius * 2 + 1;
   int iFilterHalfW  = iRadius;
   int iFilterHalfH  = iRadius;
   int iFilterArea   = iFilterW * iFilterH;
   //int divisor       = iFilterW * iFilterH;
   unsigned char *pSource;


   image32_t imageSpreadSetColor(colorSpreadSetColor, pimageDst->color_indexes());


   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pDestination;


   unsigned char *pFilter;

   int i;
   int x;
   int y;
   int x1;
   int y1;
   int x2;
   int y2;

   pimageDst->map();

   pimageSrc->map();

   //if(!pimageDst || !pimageSrc)
   //{

   //   return false;

   //}

   int iRadius2 = iRadius * iRadius;
   int r2;

   auto psystem = system();

   auto pdraw2d = psystem->draw2d();

   synchronous_lock synchronouslock(pdraw2d->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto & pmemory = pdraw2d->m_alpha_spread__32CC_filterMap[iRadius];

   system()->øconstruct_new(pmemory);

   if (pmemory->size() != iFilterArea)
   {

      pmemory->set_size(iFilterArea);

      unsigned char * pdata = pmemory->data();

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

            pdata[x + y * iFilterW] = (unsigned char)i;

         }

      }

   }

   synchronouslock.unlock();

   unsigned char * pFilterData = pmemory->data();

   int cx = pimageDst->width();

   int cy = pimageDst->height();

   if (cx != pimageSrc->width() || cy != pimageSrc->height())
   {

      throw ::exception(error_bad_argument);

   }

   unsigned char * pDst = (unsigned char *)pimageDst->get_data();

   unsigned char * pSrc = (unsigned char *)pimageSrc->get_data();

   int wSrc = pimageSrc->scan_size();

   int wDst = pimageDst->scan_size();

   int maxx1 = cx;

   int maxy1 = cy;

   int max3x1 = maxx1 * 4;

   ((::image32_t*)pDst)->copy(cx, cy, pimageDst->scan_size(), (::image32_t *)pSrc, pimageSrc->scan_size());


   int iFilterXLowerBound;
   int iFilterXUpperBound;
   int iFilterYLowerBound;
   int iFilterYUpperBound;


   int yLowerBound[4];
   int yUpperBound[4];
   int xLowerBound[4];
   int xUpperBound[4];

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

   int xL;

   int xU;

   int yL;

   int yU;

   int xMax = cx - 1;

   int yMax = cy - 1;

   // limits due the filter
   int xMaxFilterBound = xMax - iFilterHalfW;

   int yMaxFilterBound = yMax - iFilterHalfH;

   int xFilterMax = iFilterW - 1;

   int yFilterMax = iFilterH - 1;

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

         if(*((unsigned int *)pDestination) != colorSpreadSetColor)
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

               if (*((unsigned int *)pDestination) != colorSpreadSetColor)
               {

                  for (int yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
                  {

                     pSource2 = pSource1 + (wSrc * yFilter);

                     pFilter = pFilterData + yFilter * iFilterW + iFilterXLowerBound;

                     for (int xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                     {

                        if (*pFilter >= 1)
                        {

                           if (*((unsigned int *)pSource2))
                           {

                              *((image32_t *)pDestination) = imageSpreadSetColor;

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

   int iFilterHalfWidth = iFilterW / 2;

   int iFilterHalfWidthBytes = iFilterHalfWidth * 4;

   yL = iFilterHalfWidth;
   
   yU = maxy1 - iFilterHalfWidth;
   
   xL = iFilterHalfWidthBytes;
   
   xU = max3x1 - iFilterHalfWidthBytes;

   y1 = yL;

   y2 = yL - iFilterHalfWidth;

   //divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);

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

         if(*((unsigned int *)pDestination) != 0xffffffff)
         {

            for(int yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {

               pSource2 = pSource1 + (wSrc * yFilter);

               pFilter = pFilterData + yFilter * iFilterW + iFilterXLowerBound;

               for(int xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {

                  if(*pFilter >= 1)
                  {

                     if(pSource2[0] > 0)
                     {

                        *((image32_t *)pDestination) =imageSpreadSetColor;

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

   //return true;
}

































































//void imaging::pixelate(::draw2d::graphics *pdcDst,int xDest,int yDest,int cx,int cy,::draw2d::graphics * pdcSrc,int xSrc,int ySrc,int iSize)
//{
//
//   /*::draw2d::graphics_pointer & imageA.get_graphics()  = pthreadsafedata->m_dcA;
//   ::draw2d::graphics_pointer & imageB.get_graphics()  = pthreadsafedata->m_dcA;
//
//   ::draw2d::bitmap & bitmapA  = pthreadsafedata->bitmapA;
//   ::draw2d::bitmap & bitmapB  = pthreadsafedata->bitmapB;
//
//   int cxDest = cx / iSize;
//   int cyDest = cy / iSize;
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
//   throw ::exception(::exception("integer_exception" + as_string($1)));
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
//   int x1 = xDest;
//   int x2 = xDest + iSize;
//   int y1;
//   int y2;
//   for(int x = 0; x < cxDest; x++)
//   {
//   y1 = yDest;
//   y2 = yDest + iSize;
//   for(int y = 0; y < cyDest; y++)
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
//   if(cx <= 0 || cy <= 0)
//      return true;
//
//   unsigned int user;
//   unsigned int uStartScanLine;
//   unsigned int uScanLineCount;
//
//
//   memory memstorageA;
//   memory memstorageB;
//   memory memstorageC;
//
//   ::int_rectangle rectangleDest;
//   rectangleDest.left() = xDest;
//   rectangleDest.right() = xDest + cx;
//   rectangleDest.top() = yDest;
//   rectangleDest.bottom() = yDest + cy;
//
//   ::int_rectangle rectangleSource;
//   rectangleSource.left() = xSrc;
//   rectangleSource.right() = xSrc + cx;
//   rectangleSource.top() = ySrc;
//   rectangleSource.bottom() = ySrc + cy;
//
//   int iwDest;
//
//   BITMAPINFO bmiDest;
//   BITMAP   bmDest;
//   int iLimitYDest;
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
//   unsigned char * pDst = memstorageA.get_data();


//
//
//   int iwSrc;
//
//   BITMAPINFO bmiSrc;
//   BITMAP   bmSrc;
//   int iLimitYSrc;
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
//   unsigned char * pSrc = memstorageB.get_data();


//
//   memstorageC.set_size((cx + iSize) / iSize * (cy + iSize) / iSize);
//   //   unsigned char * pc = memstorageC.get_data();

//
//
//   const ::int_point & pointContextDest = pdcDst->get_origin();
//   const ::int_point & pointContextSrc = pdcSrc->get_origin();
//
//   int xvpDest = xDest + pointContextDest.x;
//   int xvpSrc = xSrc + pointContextSrc.x;
//
//   int iLimitX = cx;
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
//   int iLimitY = minimum(iLimitYDest,iLimitYSrc);
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
//         throw ::exception(::exception("integer_exception" + as_string($1)));
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
//   throw ::exception(todo);
//
//#endif
//
//}


void imaging::pixelate_24CC(
unsigned char *   pDst,


int      xDest,
int      yDest,
int      wDest,
int      cx,
int      cy,
unsigned char *   pSrc,


int      xSrc,
int      ySrc,
int      wSrc,
int      iSize)
{
   __UNREFERENCED_PARAMETER(xDest);
   __UNREFERENCED_PARAMETER(yDest);
   __UNREFERENCED_PARAMETER(xSrc);
   __UNREFERENCED_PARAMETER(ySrc);
   int      divisor;
   unsigned char *   pSource;


   unsigned char *   pDestination;


   unsigned char *   pDestination_1;


   unsigned char *   pDestination_2;


   unsigned char *   pSource1;


   unsigned char *   pSource2;



   int iFilterWidth = iSize;
   int iFilterHeight = iSize;
   int maxx1 = cx;
   int maxy1 = cy;
   //   int maxy2 = cy - iFilterWidth;
   //   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 3;
   //   int max3x2 = (maxx1 - iFilterHeight) * 3;
   //   int max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //int w = cx * 3;

   unsigned int dwR;
   unsigned int dwG;
   unsigned int dwB;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLowerBound[4];
   int yUpperBound[4];
   int xLowerBound[4];
   int xUpperBound[4];

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

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLowerBound[i];
   int yU = yUpperBound[i];
   int xL = xLowerBound[i];
   int xU = xUpperBound[i];
   for(int y1 = yL; y1 < yU; y1++)
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




   for(int x1 = xL; x1 < xU; x1+=3)
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
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
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

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   //int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   divisor = (iFilterYEnd - iFilterYBegin)
             * (iFilterXEnd - iFilterXBegin);


   int cDest   = wDest - (iFilterWidth * 3);
   int cSrc    = wSrc - (iFilterWidth * 3);
   int iSize3  = iSize * 3;

   int cyDest  = wDest * iSize;
   int cySrc   = wSrc  * iSize;



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


         int yFilter;
         for(yFilter = iFilterYBegin; yFilter < iFilterYEnd; yFilter++)
         {
            for(int xFilter = iFilterXBegin; xFilter < iFilterXEnd; xFilter++)
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
            for(int xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               pDestination_2[0] = (unsigned char)dwR;


               pDestination_2[1] = (unsigned char)dwG;


               pDestination_2[2] = (unsigned char)dwB;


               pDestination_2 += 3;


            }
            pDestination_2 += cDest;


         }


         x1 += iSize3;
         x2 += iSize3;
      }
      y1 += iSize;
      //y2 += iSize;
      pSource         += cySrc;


      pDestination    += cyDest;


   }

}


//void imaging::alpha_pixelate(
//   ::draw2d::graphics *pdcDst,
//   int xDest,
//   int yDest,
//   int cx,
//   int cy,
//   ::draw2d::graphics * pdcSrc1,
//   int xSrc1,
//   int ySrc1,
//   ::draw2d::graphics * pdcSrc2,
//   int xSrc2,
//   int ySrc2,
//   int iSize,
//   int iAlpha)
//{
//   if(cx <= 0 || cy <= 0)
//      return true;
//
//   memory memstorageA;
//   memory memstorageB;
//   memory memstorageC;
//
//
//   unsigned int user;
//   unsigned int uStartScanLine;
//   unsigned int uScanLineCount;
//
//
//   ::int_rectangle rectangleDest;
//   rectangleDest.left() = xDest;
//   rectangleDest.right() = xDest + cx;
//   rectangleDest.top() = yDest;
//   rectangleDest.bottom() = yDest + cy;
//
//   ::int_rectangle rectangleSrc1;
//   rectangleSrc1.left() = xSrc1;
//   rectangleSrc1.right() = xSrc1 + cx;
//   rectangleSrc1.top() = ySrc1;
//   rectangleSrc1.bottom() = ySrc1 + cy;
//
//   ::int_rectangle rectangleSrc2;
//   rectangleSrc2.left() = xSrc2;
//   rectangleSrc2.right() = xSrc2 + cx;
//   rectangleSrc2.top() = ySrc2;
//   rectangleSrc2.bottom() = ySrc2 + cy;
//
//   int iwDest;
//
//   BITMAPINFO bmiDest;
//   BITMAP   bmDest;
//   int iLimitYDest;
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
//   unsigned char * pDst = memstorageA.get_data();


//
//
//   int iwSrc1;
//   int iwSrc2;
//
//   BITMAPINFO bmiSrc1;
//   BITMAP   bmSrc1;
//   int iLimitYSrc1;
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
//   unsigned char * pSrc1 = memstorageB.get_data();


//
//   BITMAPINFO bmiSrc2;
//   BITMAP   bmSrc2;
//   int iLimitYSrc2;
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
//   unsigned char * pSrc2 = memstorageC.get_data();


//
//   const ::int_point & pointContextDest = pdcDst->get_origin();
//   const ::int_point & pointContextSrc1 = pdcSrc1->get_origin();
//   const ::int_point & pointContextSrc2 = pdcSrc2->get_origin();
//
//   int xvpDest = xDest + pointContextDest.x;
//   int xvpSrc1 = xSrc1 + pointContextSrc1.x;
//   int xvpSrc2 = xSrc2 + pointContextSrc2.x;
//
//   int iLimitX = cx;
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
//   int iLimitY = minimum(minimum(iLimitYDest,iLimitYSrc1),iLimitYSrc2);
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
//         throw ::exception(::exception("integer_exception" + as_string($1)));
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
//   throw ::exception(todo);
//
//#endif
//
//}


void imaging::alpha_pixelate_24CC(
unsigned char * pDst,


int xDest,
int yDest,
int wDest,
int cx,
int cy,
unsigned char * pSrc1,


int xSrc1,
int ySrc1,
int wSrc1,
unsigned char * pSrc2,


int xSrc2,
int ySrc2,
int wSrc2,
int iSize,
int iAlpha)
{
   __UNREFERENCED_PARAMETER(xDest);
   __UNREFERENCED_PARAMETER(yDest);
   __UNREFERENCED_PARAMETER(xSrc1);
   __UNREFERENCED_PARAMETER(ySrc1);
   __UNREFERENCED_PARAMETER(xSrc2);
   __UNREFERENCED_PARAMETER(ySrc2);
   //   const int constFilterWidth = 3;
   //   const int constFilterHeight = 3;
   int divisor = iSize * iSize;
   unsigned char *pSource1;


   unsigned char *pSource2;


   unsigned char *pDestination;


   unsigned char *pDestination_1;


   unsigned char *pDestination_2;


   unsigned char *pSource1_1;


   unsigned char *pSource1_2;


   unsigned char *pSource2_1;


   unsigned char *pSource2_2;


   //   unsigned short *pDestination_2;


   //   unsigned char *pFilter;

   //unsigned int *pConv;

   //   unsigned char pFilter[constFilterHeight *constFilterWidth];
   //unsigned int pConv[constFilterHeight * constFilterWidth * 3];
   //   memory_set(pFilter, 1, constFilterHeight * constFilterWidth);

   int iFilterWidth = iSize;
   int iFilterHeight = iSize;
   int maxx1 = cx;
   int maxy1 = cy;
   //   int maxy2 = cy - iFilterWidth;
   //   int maxy3 = cy - iFilterWidth / 2;
   int max3x1 = maxx1 * 3;
   //   int max3x2 = (maxx1 - iFilterHeight) * 3;
   //   int max3x3 = (maxx1 - iFilterHeight / 2) * 3;
   //int bm3Width = (cy * 3 + 3) & ~0x3L;
   //   int w = cx * 3;
   //   ::memory_copy(m_lpwDestination, m_lpbSource, bmWidth * bmHeight * 3);
   //   ::memory_copy(m_lpwDestination, m_lpbSource, bm3Width * bmHeight);
   /*for(int y = 0; y < cy; y++)
   {
   pSource = pSrc + wSrc * y;



   pDestination = pDst + wDest * y;




   for(int x = 0; x < w; x++)
   {
   *pDestination = *pSource;




   pDestination++;


   pSource++;


   }
   }*/
   unsigned int dwR1;
   unsigned int dwG1;
   unsigned int dwB1;
   unsigned int dwR2;
   unsigned int dwG2;
   unsigned int dwB2;

   int iFilterXBegin;
   int iFilterXEnd;
   int iFilterYBegin;
   int iFilterYEnd;

   int yLowerBound[4];
   int yUpperBound[4];
   int xLowerBound[4];
   int xUpperBound[4];

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

   /*   for(int i = 0; i < 4; i++)
   {
   int yL = yLowerBound[i];
   int yU = yUpperBound[i];
   int xL = xLowerBound[i];
   int xU = xUpperBound[i];
   for(int y1 = yL; y1 < yU; y1++)
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




   for(int x1 = xL; x1 < xU; x1+=3)
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
   for(int y2 = iFilterYBegin; y2 < iFilterYEnd; y2++)
   {
   pSource2 = pSource1 + (wSrc * y2);


   for(int x2 = iFilterXBegin; x2 < iFilterXEnd; x2++)
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

   int iFilterHalfWidth = iFilterWidth / 2;
   int iFilterHalfWidthBytes = iFilterHalfWidth * 3;

   int yL = iFilterHalfWidth;
   int yU = maxy1 - iFilterHalfWidth;
   int xL = iFilterHalfWidthBytes;
   int xU = max3x1 - iFilterHalfWidthBytes;


   int y1 = yL;
   int y2 = yL - iFilterHalfWidth;
   int x1;
   int x2;

   divisor = 255 * (iFilterYEnd - iFilterYBegin) * (iFilterXEnd - iFilterXBegin);

   int iRate1 = iAlpha;
   int iRate2 = 255 - iAlpha;

   unsigned int dwR;
   unsigned int dwG;
   unsigned int dwB;

   int cFilter  = wDest - iFilterWidth * 3;
   int cFilter1 = wSrc1 - iFilterWidth * 3;
   int cFilter2 = wSrc2 - iFilterWidth * 3;

   int iSize3 = iSize * 3;

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




         int yFilter;
         for(yFilter = 0; yFilter < iFilterYEnd; yFilter++)
         {
            for(int xFilter = 0; xFilter < iFilterXEnd; xFilter++)
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
            for(int xFilter = 0; xFilter < iFilterXEnd; xFilter++)
            {
               pDestination_2[0] = (unsigned char)dwR;


               pDestination_2[1] = (unsigned char)dwG;


               pDestination_2[2] = (unsigned char)dwB;


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
void imaging::HueVRCP(::image::image *pimage,::color::color crHue,double dCompress)
{

   pimage->map();

   /*if(pimage->get_data() == nullptr)
   {

      pimage->unmap();

      return false;

   }*/

   ::color::color cra[256];

   ::color::color color;

   for(int i = 0; i < 256; i++)
   {

      color.set(crHue);

      color.hls_mult(1.0,(i / 255.0) * (1.0 - dCompress) + dCompress,1.0);

      cra[i] = color.bgr();

   }

   unsigned char * p = (unsigned char *)pimage->get_data();

   long long area = pimage->area();

   for(long long i = 0; i < area; i++)
   {

      ((image32_t *)p)->assign(cra[(p[0] + p[1] + p[2]) / 3] & ::opacity(p[3]), pimage->color_indexes());











      p += 4;



   }

   pimage->unmap();

   //return true;

}

//// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
//void imaging::_desk_to_image(::image::image* pimage)
//{
//
//   return false;
//
//}
//// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
//void imaging::_desk_has_image()
//{
//
//   return false;
//
//}

//// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
//void imaging::_image_to_desk(const ::image::image* pimage)
//{
//
//   return false;
//
//}


void imaging::AlphaTextOut(::draw2d::graphics *pgraphics,int left,int top, const ::scoped_string & scopedstr, const ::color::color & color,double dBlend)
{

   string str(scopedstr);

   if (dBlend <= 0.0)
   {

      return;

   }

   auto pbrushText = øcreate < ::draw2d::brush > ();

   if(dBlend >= 1.0)
   {

      pbrushText->create_solid(color);

      pgraphics->set(pbrushText);

      pgraphics->text_out(left,top,str);

      return;

   }

   pbrushText->create_solid(color & ::opacity(dBlend));

   pgraphics->set(pbrushText);

   pgraphics->text_out(left,top,str);

}


//#ifndef __APPLE__
//
// void imaging::_load_image(::image_context * pparticle, ::image::image *pimageParam, const ::payload & payloadFile, bool bSync, bool bCreateHelperMaps)
// {
//
//   return ::error_failed;
//
// }
//
//
// void imaging::_load_image(::image::image *pimage, ::pointer<image_frame_array>& pframea, ::memory_pointer pmemory)
// {
//
//    return ::error_failed;
//
// }
//
//
// void imaging::save_image(memory & memory, const ::image::image *pimage, ::save_image * psaveimage)
// {
//
//    return ::error_failed;
//
// }
//
//#endif
//
//#if !defined(WINDOWS_DESKTOP) && !defined(LINUX)
//
//
//hcursor image_context::CreateAlphaCursor(::windowing::window * pwindow, const ::image::image *pimage, int xHotSpot, int yHotSpot)
//{
//
//   return 0;
//
//}
//
//
////hcursor image_context::load_default_cursor(enum_cursor ecursor)
////{
////
////   return NULL;
////
////}
////
////
//
//#endif

void image_context::set_cursor_image(const ::image::image *pimage, int xHotSpot, int yHotSpot)
{

}






::image::image_pointer imaging::get_work_image()
{

   synchronous_lock synchronouslock(m_pmutexWork, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   if (m_pimageaWork->has_no_image())
   {

      synchronouslock.unlock();

      return image()->create_image();

   }

   auto pimpl = m_pimageaWork->m_imagea.pop();

   synchronouslock.unlock();

   if (pimpl.is_null())
   {

      pimpl = image()->create_image();

   }

   return pimpl;

}


void imaging::free_work_image(::image::image *pimage)
{

   if (::is_null(pimage))
   {

      return;

   }

   synchronous_lock synchronouslock(m_pmutexWork, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   m_pimageaWork->m_imagea.push(pimage);

}


void image_context::load_svg(::image::image *pimage, memory & memory)
{

   const_char_pointer psz = (const_char_pointer )memory.data();

   auto size = memory.size();

   if (::is_null(psz))
   {

      //return pimage->m_estatus;

      throw ::exception(error_null_pointer);

   }

   if (memory_find(psz, size, "<svg", 4) != nullptr)
   {

      char * pszXml = (char *) memory.data();

      pimage->create_nanosvg(pszXml);

      pimage->mult_alpha_fast();

      pimage->on_load_image();

      pimage->set_ok_flag();

      //pimage->notify(OK);

      pimage->m_estatus = ::success;

      //return pimage->m_estatus;

   }

   //return ::error_failed;

}


} // namespace image