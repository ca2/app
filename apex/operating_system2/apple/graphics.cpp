#include "framework.h"
#include "graphics.h"
//#include <CoreFoundation/CoreFoundation.h>
//#include <CoreText/CoreText.h>
//
//
//#define user user2
//#include <sys/param.h>
//#include <sys/sysctl.h>
//#undef user
//
//
//
//CGColorRef cg_create_color(color32_t color32)
//{
//
//   // Create a color and add it as an attribute to the string.
//   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
//   CGFloat components[] = { color32_byte_red(color32) / 255.0,
//                            color32_byte_green(color32) / 255.0,
//                            color32_byte_blue(color32) / 255.0,
//                            color32_byte_opacity(color32) / 255.0
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
//int_bool cg_release_color(CGColorRef colorref)
//{
//   CGColorRelease(colorref);
//   return true;
//}
//
//
////device_context::device_context()
////:
/////*  m_colour(wxColourDisplay())
//// , m_ok(true)
//// , m_clipping(false)
//// , m_isInteractive(0)
//// , m_isBBoxValid(false)
//// , */ m_logicalOriginX(0), m_logicalOriginY(0)
////, m_deviceOriginX(0), m_deviceOriginY(0)
////, m_logicalScaleX(1.0), m_logicalScaleY(1.0)
////, m_userScaleX(1.0), m_userScaleY(1.0)
////, m_scaleX(1.0), m_scaleY(1.0)
////, m_signX(1), m_signY(1)
////, m_minX(0), m_minY(0), m_maxX(0), m_maxY(0)
////, m_clipX1(0), m_clipY1(0), m_clipX2(0), m_clipY2(0)
/////*  , m_logicalFunction(wxCOPY)
//// , m_backgroundMode(wxTRANSPARENT)
//// , m_mappingMode(wxMM_TEXT)
//// , m_ppen() */
/////* , m_pbrush()
//// , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
//// , m_textForegroundColour(*wxBLACK)
//// , m_textBackgroundColour(*wxWHITE)
//// , m_pfont()
//// #if wxUSE_PALETTE
//// , m_palette()
//// , m_hasCustomPalette(false)
//// #endif // wxUSE_PALETTE */
////{
////   m_cgcontext = nullptr;
////}
////
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
//      //(symTraits != nullptr);
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
//   // Create a copy of the original font with the ___new family. This call
//   // attempts to preserve traits, and may return nullptr if that is not possible.
//   // Pass in 0.0 and nullptr for int_size and matrix to preserve the values from
//   // the original font.
//   return CTFontCreateCopyWithFamily(iFont, 0.0, nullptr, iFamily);
//
//}
//
////bool TextOutU_dup(HDC hdc, int x, int y, const ::scoped_string & scopedstrUtf8, int iSize)
////{
////
////   CGContextRef context = hdc->m_cgcontext;
////
////
////   CGContextSetTextMatrix(context, CGAffineTransformIdentity);
////
////
////   // Initialize an attributed string.
////   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszUtf8, kCFStringEncodingUTF8);
////   CTFontRef      ctfontrefText     = hdc->m_ctfontref;
////   CGColorRef     cgcolorrefText    = hdc->m_cgcolorrefText;
////
////
////
////   // Initialize string, font, and context
////   CFStringRef keys[] = { kCTFontAttributeName, kCTForegroundColorAttributeName };
////   CFTypeRef values[] = { ctfontrefText, cgcolorrefText };
////   CFDictionaryRef attributes = CFDictionaryCreate(
////                      kCFAllocatorDefault, (const void**)&keys,
////                      (const void**)&values, sizeof(keys) / sizeof(keys[0]),
////                      &kCFTypeDictionaryKeyCallBacks,
////                      &kCFTypeDictionaryValueCallBacks);
////
////
//////   CFIndex iLen = CFStringGetLength(string);
////
////
////   CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
////
////   CFRelease(attributes);
////
////
////
//////   CFAttributedStringSetAttribute(attrString, CFRangeMake(0, iLen), (CFStringRef) , (CFTypeRef) textcolor);
////
////
////  // CFStringGetLength
////
////   CTLineRef line = CTLineCreateWithAttributedString(attrString);
////
////
////
////   // Set text position and draw the line into the graphics context
////
////   CGContextSetTextPosition(context, x, y);
////
////   CTLineDraw(line, context);
////
////   CFRelease(line);
////
////
////   CFRelease(attrString);
////   CFRelease(string);
////
////
////   return true;
////
////
////}
//
//
//
////void FillSolidRect_dup(HDC hdc, const ::int_rectangle & rectangle, color32_t clr)
//
////{
////   CGColorRef color = cg_create_color(clr);
////   CGRect int_rectangle;
////   rectangle.origin.x() = prectangle->left();
//
////   rectangle.origin.y() = prectangle->top();
//
////   rectangle.size.width = prectangle->right() - prectangle->left();
//
////   rectangle.size.height = prectangle->bottom() - prectangle->top();
//
////   CGContextFillRect(hdc->m_cgcontext, rectangle);
////   cg_release_color(color);
////}
//
////HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam);
//
////HFONT CreatePointBoldFont_dup(int nPointSize, const ::scoped_string & scopedstrFaceName, int BOLD, HDC hdc);
//
////
////HFONT CreatePointFont_dup(int nPointSize, const ::scoped_string & scopedstrFaceName, HDC hdc)
//
////{
////   return CreatePointBoldFont_dup(nPointSize, pszFaceName, false, hdc);
//
////}
////
////HFONT CreatePointBoldFont_dup(int nPointSize, const ::scoped_string & scopedstrFaceName, int BOLD, HDC hdc)
//
////{
////   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszFaceName, kCFStringEncodingUTF8);
//
////   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
////   CFRelease(string);
////   return nullptr;
////}
////
////HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam)
//
////{
////
////
////   return ::CreateFontIndirect(pLogFont);
//
////
////
////}
////
////
////
//
//
//
//CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
//bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);
//
//
//bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const ::scoped_string & scopedstr);
//
//
//
//
//
//
//
//
//
//
//CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
//bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);
//
//
//bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const ::scoped_string & scopedstr);
//
//
//
//
//
