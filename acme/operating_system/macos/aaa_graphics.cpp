#include "framework.h"
#include "internal.h"
//#include "oswindow_data.h"


#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>


bool mm1_get_file_image(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, const ::scoped_string & scopedstr);

bool macos1_get_file_image(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, const ::scoped_string & scopedstr);

//device_context::device_context()
//:
///*  m_colour(wxColourDisplay())
// , m_ok(true)
// , m_clipping(false)
// , m_isInteractive(0)
// , m_isBBoxValid(false)
// , */ m_logicalOriginX(0), m_logicalOriginY(0)
//, m_deviceOriginX(0), m_deviceOriginY(0)
//, m_logicalScaleX(1.0), m_logicalScaleY(1.0)
//, m_userScaleX(1.0), m_userScaleY(1.0)
//, m_scaleX(1.0), m_scaleY(1.0)
//, m_signX(1), m_signY(1)
//, m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
//, m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
///*  , m_logicalFunction(wxCOPY)
// , m_backgroundMode(wxTRANSPARENT)
// , m_mappingMode(wxMM_TEXT)
// , m_ppen() */
///* , m_pbrush()
// , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
// , m_textForegroundColour(*wxBLACK)
// , m_textBackgroundColour(*wxWHITE)
// , m_pfont()
// #if wxUSE_PALETTE
// , m_palette()
// , m_hasCustomPalette(false)
// #endif // wxUSE_PALETTE */
//{
//    m_cgcontext = nullptr;
//}

//
//
//CGColorRef cg_create_color(color32_t color32)
//{
//
//   // Create a color and add it as an attribute to the string.
//   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
//   CGFloat components[] = { color32_u8_red(color32) / 255.0,
//                            color32_u8_green(color32) / 255.0,
//                            color32_u8_blue(color32) / 255.0,
//                            color32_u8_opacity(color32) / 255.0
//                          };
//
//   CGColorRef color = CGColorCreate(rgbColorSpace, components);
//
//   CGColorSpaceRelease(rgbColorSpace);
//
//   return color;
//}
//
//
//i32_bool cg_release_color(CGColorRef colorref)
//{
//   CGColorRelease(colorref);
//   return true;
//}
//



//
//HFONT CreateFontIndirect(const LOGFONT * lf)
//{
//   return nullptr;
//}
//HPEN CreatePen(::i32 iPenStyle, ::i32 iWidth, color32_t crColor)
//{
//   return nullptr;
//}
//HGDIOBJ GetStockObject(::i32 iStockObject)
//{
//   return nullptr;
//}
//i32_bool SelectObject(HDC hdc, HGDIOBJ hgdiobj)
//{
//   return false;
//}
//i32_bool Rectangle(HDC hdc, ::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2)
//{
//   return false;
//}
//i32_bool DeleteObject(HGDIOBJ hgdiobj)
//{
//   return false;
//}
//HDC create_compatible_graphics(HDC hdc)
//{
//   return nullptr;
//}
//HBITMAP WINAPI CreateDIBSection(HDC hdc, ::i32 cx, ::i32 cy, ::u32 usage, void **ppvBits, HANDLE hSection, ::u32 offset)
//{
//   return nullptr;
//}
//i32_bool SetBkMode(HDC hdc, ::i32 iMode)
//{
//   return false;
//}
//i32_bool DeleteDC(HDC hdc)
//{
//   return false;
//}
//i32_bool AlphaBlend(HDC hdcDest, ::i32 xoriginDest, ::i32 yoriginDest, ::i32 wDest, ::i32 hDest, HDC hdcSrc, ::i32 xoriginSrc, ::i32 yoriginSrc, ::i32 wSrc, ::i32 hSrc, BLENDFUNCTION ftn)
//{
//   return false;
//}
//i32_bool GetObject(HGDIOBJ hgdiobj, ::i32 iSize, void * matter)
//{
//   return false;
//}
//i32_bool GetTextExtentPoint(HDC hdc, const ::scoped_string & scopedstrText, ::i32 iSize, ::i32_size * psize)
//{
//   return false;
//}
//
//

//i32_bool SetTextColor(HDC hdc, color32_t crText)
//{
//
//   cg_release_color(hdc->m_cgcolorrefText);
//   hdc->m_cgcolorrefText = cg_create_color(crText);
//   return true;
//}

HBRUSH CreateSolidBrush(color32_t color32)
{
   return nullptr;
}



//
//
//CTFontDescriptorRef CreateFontDescriptorFromName(CFStringRef iPostScriptName, CGFloat iSize)
//{
//   assert(iPostScriptName != nullptr);
//   return CTFontDescriptorCreateWithNameAndSize(iPostScriptName, iSize);
//}
//
//
//CTFontDescriptorRef CreateFontDescriptorFromFamilyAndTraits(CFStringRef iFamilyName, CTFontSymbolicTraits iTraits, CGFloat iSize)
//{
//
//   CTFontDescriptorRef descriptor = nullptr;
//   CFMutableDictionaryRef attributes;
//   assert(iFamilyName != nullptr);
//
//   // Create a mutable dictionary to hold our attributes.
//   attributes = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
////   __Check(attributes != nullptr);
//
//   if (attributes != nullptr)
//   {
//
//      CFMutableDictionaryRef traits;
//
//      CFNumberRef symTraits;
//
//      // add a family name to our attributes.
//      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);
//
//      // Create the traits dictionary.
//      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);
//
//      ASSERT(symTraits != nullptr);
//
//      if (symTraits != nullptr)
//      {
//         // Create a dictionary to hold our traits values.
//         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
////         __Check(traits != nullptr);
//
//         if (traits != nullptr)
//         {
//
//            // add the symbolic traits value to the traits dictionary.
//            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);
//
//            // add the traits attribute to our attributes.
//            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);
//
//            CFRelease(traits);
//
//         }
//
//         CFRelease(symTraits);
//
//      }
//
//      // Create the font descriptor with our attributes and input size.
//      descriptor = CTFontDescriptorCreateWithAttributes(attributes);
//
////      __Check(descriptor != nullptr);
//
//      CFRelease(attributes);
//
//   }
//
//   // Return our font descriptor.
//   return descriptor;
//
//}
//
//
//CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
//{
//
////   __Check(iFontDescriptor != nullptr);
//
//   // Create the font from the font descriptor and input size. Pass
//   // nullptr for the matrix parameter to use the default matrix (identity).
//   return CTFontCreateWithFontDescriptor(iFontDescriptor, iSize, nullptr);
//
//}
//
//
//CTFontRef CreateBoldFont(CTFontRef iFont, Boolean iMakeBold)
//{
//
//   CTFontSymbolicTraits desiredTrait = 0;
//
//   CTFontSymbolicTraits traitMask;
//
//   // If we are trying to make the font bold, set the desired trait
//   // to be bold.
//   if (iMakeBold)
//      desiredTrait = kCTFontBoldTrait;
//
//   // Mask off the bold trait to indicate that it is the only trait
//   // desired to be modified. As CTFontSymbolicTraits is a bit field,
//   // we could choose to change multiple traits if we desired.
//   traitMask = kCTFontBoldTrait;
//
//   // Create a copy of the original font with the masked trait set to the
//   // desired value. If the font family does not have the appropriate style,
//   // this will return nullptr.
//
//   return CTFontCreateCopyWithSymbolicTraits(iFont, 0.0, nullptr, desiredTrait, traitMask);
//
//}
//
//
//CTFontRef CreateFontConvertedToFamily(CTFontRef iFont, CFStringRef iFamily)
//{
//
//   // Create a copy of the original font with the aaa_primitive_new family. This call
//   // attempts to preserve traits, and may return nullptr if that is not possible.
//   // Pass in 0.0 and nullptr for i32_size and matrix to preserve the values from
//   // the original font.
//   return CTFontCreateCopyWithFamily(iFont, 0.0, nullptr, iFamily);
//
//}

//
//bool TextOutU_dup(HDC hdc, ::i32 x, ::i32 y, const ::scoped_string & scopedstrUtf8, ::i32 iSize)
//{
//
//   CGContextRef context = hdc->m_cgcontext;
//
//
//   CGContextSetTextMatrix(context, CGAffineTransformIdentity);
//
//
//   // Initialize an attributed string.
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
//   CTFontRef      ctfontrefText     = hdc->m_ctfontref;
//   CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;
//
//
//
//   // Initialize string, font, and context
//   CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
//   CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
//   CFDictionaryRef attributes = CFDictionaryCreate(
//                      kCFAllocatorDefault, (const void**)&keys,
//                      (const void**)&values, sizeof(keys) / sizeof(keys[0]),
//                      &kCFTypeDictionaryKeyCallBacks,
//                      &kCFTypeDictionaryValueCallBacks);
//
//
////   CFIndex iLen = CFStringGetLength(string);
//
//
//   CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
//
//   CFRelease(attributes);
//
//
//
////   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);
//
//
//  // CFStringGetLength
//
//   CTLineRef line = CTLineCreateWithAttributedString(attrString);
//
//
//
//   // Set text position and draw the line into the graphics context
//
//   CGContextSetTextPosition(context, x, y);
//
//   CTLineDraw(line, context);
//
//   CFRelease(line);
//
//
//   CFRelease(attrString);
//   CFRelease(string);
//
//
//   return true;
//
//
//}
//
//
//
//void FillSolidRect_dup(HDC hdc, const ::i32_rectangle & rectangle, color32_t clr)

//{
//   CGColorRef color = cg_create_color(clr);
//   CGRect i32_rectangle;
//   rectangle.origin.x = prectangle->left;

//   rectangle.origin.y = prectangle->top;

//   rectangle.size.width = prectangle->right - prectangle->left;

//   rectangle.size.height = prectangle->bottom - prectangle->top;

//   CGContextFillRect(hdc->m_cgcontext, rectangle);
//   cg_release_color(color);
//}

HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam);

HFONT CreatePointBoldFont_dup(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, ::i32 BOLD, HDC hdc);


//HFONT CreatePointFont_dup(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, HDC hdc)
//
//{
//   return CreatePointBoldFont_dup(nPointSize, pszFaceName, false, hdc);
//
//}
//
//HFONT CreatePointBoldFont_dup(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, ::i32 BOLD, HDC hdc)
//
//{
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszFaceName, kCFStringEncodingUTF8);
//
//   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
//   CFRelease(string);
//   return nullptr;
//}
//
//// pLogFont->nHeight is interpreted as PointSize * 10
//HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam)
//
//{
//
//#ifdef WINDOWS
//
//   HDC hDC;
//   if (hdcParam != nullptr)
//   {
//      hDC = hdcParam;
//   }
//   else
//      hDC = ::GetDC(nullptr);
//
//   // convert nPointSize to logical units based on pgraphics
//   LOGFONT logFont = *pLogFont;
//
//   ::i32_point point;
//   // 72 points/inch, 10 decipoints/i32_point
//   point.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
//   point.x = 0;
//   ::DPtoLP(hDC, &point, 1);
//   const i32_point & pointOrg = { 0, 0 };
//   ::DPtoLP(hDC, &pointOrg, 1);
//   logFont.lfHeight = -abs_dup(point.y - pointOrg.y);
//
//   if(hdcParam == nullptr)
//      ReleaseDC(nullptr, hDC);
//
//   return ::CreateFontIndirect(&logFont);
//
//#else
//
//   /*HDC hDC;
//    if (hdcParam != nullptr)
//    {
//    hDC = hdcParam;
//    }
//    else
//    hDC = ::GetDC(nullptr);*/
//
//   return ::CreateFontIndirect(pLogFont);
//
//
//   /*if(hdcParam == nullptr)
//    ReleaseDC(nullptr, hDC);*/
//
//#endif
//
//}
//
//




//bool macos_get_file_image(::image::image *pimage, const ::scoped_string & scopedstr);

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, ::i32 cx, ::i32 cy);
bool GetImagePixelData(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, CGImageRef inImage);


bool mm_get_file_image(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, const ::scoped_string & scopedstr);


//
//
//bool GetImagePixelData(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, CGImageRef inImage)
//{
//
//   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);
//
//   if (cgctx == nullptr)
//   {
//
//      return false;
//
//   }
//
//   CGRect rectangle = {{0,0},{(CGFloat)cx,(CGFloat)cy}};
//
//   CGContextDrawImage(cgctx, rectangle, inImage);
//
//   void *data = CGBitmapContextGetData (cgctx);
//
//   ::u8 * pdest = (::u8 * ) pcr;
//
//   if (data != nullptr)
//   {
//
//      for(::i32 y = cy - 1; y >= 0; y--)
//      {
//
//         ::u8 * pline = (::u8 *) &((::u32*)data)[y * cx];
//
//         ::memory_copy(pdest, pline, cx* 4);
//
//         pdest += iScan;
//
//      }
//
//   }
//
//   CGContextRelease(cgctx);
//
//   return data != nullptr;
//
//}
//
//
//CGContextRef CreateARGBBitmapContext (CGImageRef inImage, ::i32 cx, ::i32 cy)
//{
//
//   CGContextRef    context = nullptr;
//
//   CGColorSpaceRef colorSpace;
//
//   void *          bitmapData;
//
//   ::i32             bitmapByteCount;
//
//   ::i32             bitmapBytesPerRow;
//
//   bitmapBytesPerRow   = (cx * 4);
//
//   bitmapByteCount     = (bitmapBytesPerRow * cy);
//
//   colorSpace = CGColorSpaceCreateDeviceRGB();
//
//   if (colorSpace == nullptr)
//   {
//
//      informationf("CreateARGBBitmapContext: Error allocating color space\n");
//
//      return nullptr;
//
//   }
//
//   //   bitmapData = malloc( bitmapByteCount );
//   //
//   //   if (bitmapData == nullptr)
//   //   {
//   //
//   //      informationf("CreateARGBBitmapContext: Memory not allocated!");
//   //
//   //      CGColorSpaceRelease( colorSpace );
//   //
//   //      return nullptr;
//   //
//   //   }
//   //
//   //   memory_set(bitmapData, 0, bitmapByteCount);
//
//   // Create the bitmap context. We want pre-multiplied argb, 8-bits
//   // per component. Regardless of what the source image format is
//   // (CMYK, Grayscale, and so on) it will be converted over to the format
//   // specified here by CGBitmapContextCreate.
//   context =
//   CGBitmapContextCreate (
//   nullptr,
//   cx,
//   cy,
//   8,
//   bitmapBytesPerRow,
//   colorSpace,
//   kCGImageAlphaPremultipliedLast);
//
//   //   if (context == nullptr)
//   //   {
//   //
//   //      free (bitmapData);
//   //
//   //      informationf("CreateARGBBitmapContext: Context not created!");
//   //
//   //   }
//
//   CGColorSpaceRelease( colorSpace );
//
//   return context;
//}
//





//bool macos_get_file_image(::image::image *pimage, const ::scoped_string & scopedstr);

CGContextRef CreateARGBBitmapContext (CGImageRef inImage, ::i32 cx, ::i32 cy);
bool GetImagePixelData(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, CGImageRef inImage);


bool mm_get_file_image(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, const ::scoped_string & scopedstr);


bool mm1_get_file_image(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, const ::scoped_string & scopedstr);


#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>



// device_context::device_context()
// :
// /*  m_colour(wxColourDisplay())
//  , m_ok(true)
//  , m_clipping(false)
//  , m_isInteractive(0)
//  , m_isBBoxValid(false)
//  , */ m_logicalOriginX(0), m_logicalOriginY(0)
// , m_deviceOriginX(0), m_deviceOriginY(0)
// , m_logicalScaleX(1.0), m_logicalScaleY(1.0)
// , m_userScaleX(1.0), m_userScaleY(1.0)
// , m_scaleX(1.0), m_scaleY(1.0)
// , m_signX(1), m_signY(1)
// , m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
// , m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
// /*  , m_logicalFunction(wxCOPY)
//  , m_backgroundMode(wxTRANSPARENT)
//  , m_mappingMode(wxMM_TEXT)
//  , m_ppen() */
// /* , m_pbrush()
//  , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
//  , m_textForegroundColour(*wxBLACK)
//  , m_textBackgroundColour(*wxWHITE)
//  , m_pfont()
//  #if wxUSE_PALETTE
//  , m_palette()
//  , m_hasCustomPalette(false)
//  #endif // wxUSE_PALETTE */
// {
//     m_cgcontext = nullptr;
// }



//CGColorRef cg_create_color(color32_t color32)
//{
//
//   // Create a color and add it as an attribute to the string.
//   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
//   CGFloat components[] = { color32_u8_red(color32) / 255.0,
//      color32_u8_green(color32) / 255.0,
//      color32_u8_blue(color32) / 255.0,
//      color32_u8_opacity(color32) / 255.0};
//
//   CGColorRef color = CGColorCreate(rgbColorSpace, components);
//
//   CGColorSpaceRelease(rgbColorSpace);
//
//   return color;
//}


//i32_bool cg_release_color(CGColorRef colorref)
//{
//   CGColorRelease(colorref);
//   return true;
//}
//


// HDC GetWindowDC(oswindow hwnd)
// {
//    return GetDC(hwnd);
// }

// HDC GetDC(oswindow hwnd)
// {

//     HDC hdc = aaa_primitive_new device_context;


//     hdc->m_window = hwnd;
//     hdc->m_cgcontext = get_nswindow_cgcontext(hwnd);
// /*    hdc->m_windowPort = GetWindowPort(hwnd);
//     GetPortBounds(hdc->m_windowPort, &hdc->m_portBounds);

//     hdc->m_wasSwapped = QDSwapPort(hdc->m_windowPort, &hwnd->m_savedPort);


//     /* ... QuickDraw Drawing Commands ... */
//     // at windowPort


//   /*  QDBeginCGContext(hdc->m_windowPort, &hdc->m_cgcontext);
//     SyncCGContextOriginWithPort(hdc->m_cgcontext, hdc->m_windowPort);
//     //ClipCGContextToRegion(cgContext, &portBounds, clippingRegion);
//     //DisposeRgn(clippingRegion);
//     //clippingRegion = nullptr;

//     /* ... Quartz Drawing Commands ... */


//     hdc->m_cgcolorrefText = cg_create_color(0);
//     hdc->m_cgcolorrefBk = cg_create_color(rgb(255, 255, 255));

//     return hdc;

// }


// i32_bool ReleaseDC(oswindow hwnd, HDC hdc)
// {

//    if(hdc == nullptr)
//       return false;

//    /*QDEndCGContext(hdc->m_windowPort, &hdc->m_cgcontext);

//    if(hdc->m_wasSwapped)
//    {
//       QDSwapPort(hdc->m_savedPort, &hdc->m_savedPort);
//    }*/

//    delete hdc;
//    return true;

// }


//i32_bool this->rectangle(oswindow hwnd, ::i32_rectangle * prectangle)
//
//{
//   /*   XWindowAttributes attrs;
//     Fill attribute structure with information about root window */
//   /* if(XGetWindowAttributes(XOpenxDisplay(nullptr), hwnd, &attrs) == 0)
//    {
//    return false;
//    }
//    prectangle->left      = 0;
//
//    prectangle->top       = 0;
//
//    prectangle->right     = prectangle->left    + attrs.width;
//
//    prectangle->bottom    = prectangle->top     + attrs.height;*/
//
//
//   if(!window_rectangle(hwnd, prectangle))
//
//      return false;
//
//   prectangle->right   -=  prectangle->left;
//
//   prectangle->bottom  -=  prectangle->top;
//
//   prectangle->left    =   0;
//
//   prectangle->top     =   0;
//
//
//   return true;
//
//}

//
//i32_bool window_rectangle(oswindow hwnd, ::i32_rectangle * prectangle)
//
//{
//   /* XWindowAttributes attrs;
//     Fill attribute structure with information about root window */
//   /*   if(XGetWindowAttributes(XOpenxDisplay(nullptr), hwnd, &attrs) == 0)
//    {
//    return false;
//    }
//    prectangle->left      = attrs.x;
//
//    prectangle->top       = attrs.y;
//
//    prectangle->right     = prectangle->left    + attrs.width;
//
//    prectangle->bottom    = prectangle->top     + attrs.height;*/
//
//
//   //if(!hwnd->m_bNsWindowRect)
//   {
//
//      get_nswindow_rect(hwnd, &hwnd->m_rectangleNsWindow);
//
//      // hwnd->m_bNsWindowRect = true;
//
//   }
//
//   *prectangle = hwnd->m_rectangleNsWindow;
//
//
//
//   //::copy(prectangle, hwnd->m_pimpl->m_rectangleParentClient);
//
//
//   return true;
//
//
//
//}


/*
 ::i32 FillRect(HDC hdc, const ::i32_rectangle & prc, HBRUSH hbr)

 {

 CGRect i32_rectangle;

 rectangle.origin.x     = prc->left;

 rectangle.origin.y     = prc->top;

 rectangle.size.width   = prc->right - lprc->left;

 rectangle.size.height  = prc->bottom - lprc->top;


 CGContextSetRGBFillColor(hdc->m_cgcontext, color32_u8_red(hbr->lbColor), color32_u8_green(hbr->lbColor), color32_u8_blue(hbr->lbColor), color32_u8_opacity(hbr->lbColor));

 CGContextFillRect(hdc->m_cgcontext, rectangle);

 return 1;
 }
 */

// HDC BeginPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    HDC hdc = GetDC(hwnd);

//    this->rectangle(hwnd, &ps->rcPaint);

//    return hdc;

// }


// i32_bool EndPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    return ReleaseDC(hwnd, ps->hdc);

// }







/*::i32 _cx_XErrorHandler(Display * display, XErrorEvent * perrorevent)
 {
 return 0;
 }*/




// HFONT CreateFontIndirect(const LOGFONT * lf)
// {
//     return nullptr;
// }
// HPEN CreatePen(::i32 iPenStyle, ::i32 iWidth, color32_t crColor)
// {
//     return nullptr;
// }
// HGDIOBJ GetStockObject(::i32 iStockObject)
// {
//     return nullptr;
// }
// i32_bool SelectObject(HDC hdc, HGDIOBJ hgdiobj)
// {
//     return false;
// }
// i32_bool Rectangle(HDC hdc, ::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2)
// {
//     return false;
// }
// i32_bool DeleteObject(HGDIOBJ hgdiobj)
// {
//     return false;
// }
// HDC create_compatible_graphics(HDC hdc)
// {
//     return nullptr;
// }
// HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *pbmi, ::u32 usage, void **ppvBits, HANDLE hSection, ::u32 offset)

// {
//     return nullptr;
// }
// i32_bool SetBkMode(HDC hdc, ::i32 iMode)
// {
//     return false;
// }
// i32_bool DeleteDC(HDC hdc)
// {
//     return false;
// }
// i32_bool AlphaBlend(HDC hdcDest, ::i32 xoriginDest, ::i32 yoriginDest, ::i32 wDest, ::i32 hDest, HDC hdcSrc, ::i32 xoriginSrc, ::i32 yoriginSrc, ::i32 wSrc, ::i32 hSrc, BLENDFUNCTION ftn)
// {
//     return false;
// }
// i32_bool GetObject(HGDIOBJ hgdiobj, ::i32 iSize, void * matter)
// {
//     return false;
// }
// i32_bool GetTextExtentPoint(HDC hdc, const ::scoped_string & scopedstrText, ::i32 iSize, ::i32_size * psize)
// {
//     return false;
// }



// i32_bool SetTextColor(HDC hdc, color32_t crText)
// {

//    cg_release_color(hdc->m_cgcolorrefText);
//    hdc->m_cgcolorrefText = cg_create_color(crText);
//    return true;
// }

// HBRUSH CreateSolidBrush(color32_t color32)
// {
//     return nullptr;
// }




//
//CTFontDescriptorRef CreateFontDescriptorFromName(CFStringRef iPostScriptName, CGFloat iSize)
//{
//   assert(iPostScriptName != nullptr);
//   return CTFontDescriptorCreateWithNameAndSize(iPostScriptName, iSize);
//}
//
//
//CTFontDescriptorRef CreateFontDescriptorFromFamilyAndTraits(CFStringRef iFamilyName, CTFontSymbolicTraits iTraits, CGFloat iSize)
//{
//
//   CTFontDescriptorRef descriptor = nullptr;
//   CFMutableDictionaryRef attributes;
//   assert(iFamilyName != nullptr);
//
//   // Create a mutable dictionary to hold our attributes.
//   attributes = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
//   //   __Check(attributes != nullptr);
//
//   if (attributes != nullptr)
//   {
//
//      CFMutableDictionaryRef traits;
//
//      CFNumberRef symTraits;
//
//      // add a family name to our attributes.
//      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);
//
//      // Create the traits dictionary.
//      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);
//
//      (symTraits != nullptr);
//
//      if (symTraits != nullptr)
//      {
//         // Create a dictionary to hold our traits values.
//         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
//
//         //         __Check(traits != nullptr);
//
//         if (traits != nullptr)
//         {
//
//            // add the symbolic traits value to the traits dictionary.
//            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);
//
//            // add the traits attribute to our attributes.
//            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);
//
//            CFRelease(traits);
//
//         }
//
//         CFRelease(symTraits);
//
//      }
//
//      // Create the font descriptor with our attributes and input size.
//      descriptor = CTFontDescriptorCreateWithAttributes(attributes);
//
//      //      __Check(descriptor != nullptr);
//
//      CFRelease(attributes);
//
//   }
//
//   // Return our font descriptor.
//   return descriptor;
//
//}
//
//
//CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
//{
//
//   //   __Check(iFontDescriptor != nullptr);
//
//   // Create the font from the font descriptor and input size. Pass
//   // nullptr for the matrix parameter to use the default matrix (identity).
//   return CTFontCreateWithFontDescriptor(iFontDescriptor, iSize, nullptr);
//
//}
//
//
//CTFontRef CreateBoldFont(CTFontRef iFont, Boolean iMakeBold)
//{
//
//   CTFontSymbolicTraits desiredTrait = 0;
//
//   CTFontSymbolicTraits traitMask;
//
//   // If we are trying to make the font bold, set the desired trait
//   // to be bold.
//   if (iMakeBold)
//      desiredTrait = kCTFontBoldTrait;
//
//   // Mask off the bold trait to indicate that it is the only trait
//   // desired to be modified. As CTFontSymbolicTraits is a bit field,
//   // we could choose to change multiple traits if we desired.
//   traitMask = kCTFontBoldTrait;
//
//   // Create a copy of the original font with the masked trait set to the
//   // desired value. If the font family does not have the appropriate style,
//   // this will return nullptr.
//
//   return CTFontCreateCopyWithSymbolicTraits(iFont, 0.0, nullptr, desiredTrait, traitMask);
//
//}
//
//
//CTFontRef CreateFontConvertedToFamily(CTFontRef iFont, CFStringRef iFamily)
//{
//
//   // Create a copy of the original font with the aaa_primitive_new family. This call
//   // attempts to preserve traits, and may return nullptr if that is not possible.
//   // Pass in 0.0 and nullptr for i32_size and matrix to preserve the values from
//   // the original font.
//   return CTFontCreateCopyWithFamily(iFont, 0.0, nullptr, iFamily);
//
//}

// bool TextOutU_dup(HDC hdc, ::i32 x, ::i32 y, const ::scoped_string & scopedstrUtf8, ::i32 iSize)
// {

//    CGContextRef context = hdc->m_cgcontext;


//    CGContextSetTextMatrix(context, CGAffineTransformIdentity);


//    // Initialize an attributed string.
//    CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
//    CTFontRef      ctfontrefText     = hdc->m_ctfontref;
//    CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;



//    // Initialize string, font, and context
//    CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
//    CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
//    CFDictionaryRef attributes = CFDictionaryCreate(
//                       kCFAllocatorDefault, (const void**)&keys,
//                       (const void**)&values, sizeof(keys) / sizeof(keys[0]),
//                       &kCFTypeDictionaryKeyCallBacks,
//                       &kCFTypeDictionaryValueCallBacks);


// //   CFIndex iLen = CFStringGetLength(string);


//    CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);

//    CFRelease(attributes);



// //   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);


//   // CFStringGetLength

//    CTLineRef line = CTLineCreateWithAttributedString(attrString);



//    // Set text position and draw the line into the graphics context

//    CGContextSetTextPosition(context, x, y);

//    CTLineDraw(line, context);

//    CFRelease(line);


//    CFRelease(attrString);
//    CFRelease(string);


//    return true;


// }



// void FillSolidRect_dup(HDC hdc, const ::i32_rectangle & rectangle, color32_t clr)

// {
//    CGColorRef color = cg_create_color(clr);
//    CGRect i32_rectangle;
//    rectangle.origin.x = prectangle->left;

//    rectangle.origin.y = prectangle->top;

//    rectangle.size.width = prectangle->right - prectangle->left;

//    rectangle.size.height = prectangle->bottom - prectangle->top;

//    CGContextFillRect(hdc->m_cgcontext, rectangle);
//    cg_release_color(color);
// }

HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam);

HFONT CreatePointBoldFont_dup(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, ::i32 BOLD, HDC hdc);


//HFONT CreatePointFont_dup(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, HDC hdc)

//{
//   return CreatePointBoldFont_dup(nPointSize, pszFaceName, false, hdc);

//}
//
//HFONT CreatePointBoldFont_dup(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, ::i32 BOLD, HDC hdc)

//{
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszFaceName, kCFStringEncodingUTF8);

//   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
//   CFRelease(string);
//   return nullptr;
//}
//
//// pLogFont->nHeight is interpreted as PointSize * 10
//HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam)

//{
//
//   return ::CreateFontIndirect(pLogFont);

//
//}



bool macos1_get_file_image(::u32 * pcr, ::i32 cx, ::i32 cy, ::i32 iScan, const ::scoped_string & scopedstr)
{

   static ::pointer< ::mutex > pmutex = nullptr;

   if(pmutex == nullptr)
   {

      pmutex = aaa_primitive_new ::pointer < ::mutex >();

   }

   synchronous_lock synchronouslock(pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);


   return mm1_get_file_image(pcr, cx, cy, iScan, psz);


}




//bool macos_get_file_image(::image::image *pimage, const ::scoped_string & scopedstr)
//{
//
//   pimage->map();
//
//   if(!macos1_get_file_image(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), psz))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}









bool os_init_imaging()
{
   
   return true;
   
}


void os_term_imaging()
{
   
}



//i32_bool window_rectangle(oswindow hwnd, ::i32_rectangle * prectangle)
//
//{
//   /* XWindowAttributes attrs;
//    Fill attribute structure with information about root window */
//   /*   if(XGetWindowAttributes(XOpenxDisplay(nullptr), hwnd, &attrs) == 0)
//    {
//    return false;
//    }
//    prectangle->left      = attrs.x;
//    
//    prectangle->top       = attrs.y;
//    
//    prectangle->right     = prectangle->left    + attrs.width;
//    
//    prectangle->bottom    = prectangle->top     + attrs.height;*/
//   
//   
//   //if(!hwnd->m_bNsWindowRect)
//   {
//      
//      get_nswindow_rect(hwnd, &hwnd->m_rectangleNsWindow);
//      
//      // hwnd->m_bNsWindowRect = true;
//      
//   }
//   
//   *prectangle = hwnd->m_rectangleNsWindow;
//   
//   
//   
//   //::copy(prectangle, hwnd->m_pimpl->m_rectangleParentClient);
//   
//   
//   return true;
//   
//   
//   
//}
//
//
//


i32_bool delete_hcursor(HCURSOR h)
{
   
   return 1;
   
}


::f64 font_similarity(const ::scoped_string & scopedstrSystem, const ::scoped_string & scopedstrUser)
{

   if (::is_null(scopedstrSystem) || ::is_null(scopedstrUser))
   {

      return 0.0;

   }

   if (!stricmp(scopedstrSystem, pszUser))
   {

      return 1.0;

   }

   return 0.0;
   
}


namespace draw2d
{


   string default_font_name()
   {
 
      return "Helvetica";
   
   }


} // namespace draw2d





void * cg_image_get_image_data(::i32 & width, ::i32 & height, ::i32 & iScan, CGImageRef image)
{

   if(image == nullptr)
   {

      return nullptr;

   }

   //https://www.raywenderlich.com/69855/image-processing-in-ios-part-1-raw-bitmap-modification
   // 1.
   width = (::i32) CGImageGetWidth(image);
   height = (::i32) CGImageGetHeight(image);

   // 2.
   long bytesPerPixel = 4;
   long bytesPerRow = bytesPerPixel * width;
   long bitsPerComponent = 8;

   ::u32 * pixels;
   pixels = (::u32 *) calloc(height * width, sizeof(::u32));
   
   iScan = width * sizeof(::u32);

   // 3.
   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
   CGContextRef context = CGBitmapContextCreate(pixels, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);

   // 4.
   CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);

   // 5. Cleanup
   CGColorSpaceRelease(colorSpace);

   CGContextRelease(context);

   return pixels;

}
