#include "framework.h"
#include "graphics.h"
#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CoreText.h>


#define user user2
#include <sys/param.h>
#include <sys/sysctl.h>
#undef user



CGColorRef cg_create_color(color32_t cr)
{

   // Create a color and add it as an attribute to the string.
   CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
   CGFloat components[] = { colorref_get_r_value(cr) / 255.0,
                            colorref_get_g_value(cr) / 255.0,
                            colorref_get_b_value(cr) / 255.0,
                            colorref_get_a_value(cr) / 255.0
                          };

   CGColorRef color = CGColorCreate(rgbColorSpace, components);

   CGColorSpaceRelease(rgbColorSpace);

   return color;
}


int_bool cg_release_color(CGColorRef colorref)
{
   CGColorRelease(colorref);
   return true;
}


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
// , m_pen() */
///* , m_brush()
// , m_backgroundBrush(*wxTRANSPARENT_BRUSH)
// , m_textForegroundColour(*wxBLACK)
// , m_textBackgroundColour(*wxWHITE)
// , m_font()
// #if wxUSE_PALETTE
// , m_palette()
// , m_hasCustomPalette(false)
// #endif // wxUSE_PALETTE */
//{
//   m_cgcontext = nullptr;
//}
//

CTFontDescriptorRef CreateFontDescriptorFromName(CFStringRef iPostScriptName, CGFloat iSize)
{
   assert(iPostScriptName != nullptr);
   return CTFontDescriptorCreateWithNameAndSize(iPostScriptName, iSize);
}


CTFontDescriptorRef CreateFontDescriptorFromFamilyAndTraits(CFStringRef iFamilyName, CTFontSymbolicTraits iTraits, CGFloat iSize)
{

   CTFontDescriptorRef descriptor = nullptr;
   CFMutableDictionaryRef attributes;
   assert(iFamilyName != nullptr);

   // Create a mutable dictionary to hold our attributes.
   attributes = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

//   __Check(attributes != nullptr);

   if (attributes != nullptr)
   {

      CFMutableDictionaryRef traits;

      CFNumberRef symTraits;

      // add a family name to our attributes.
      CFDictionaryAddValue(attributes, kCTFontFamilyNameAttribute, iFamilyName);

      // Create the traits dictionary.
      symTraits = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &iTraits);

      //(symTraits != nullptr);

      if (symTraits != nullptr)
      {
         // Create a dictionary to hold our traits values.
         traits = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

//         __Check(traits != nullptr);

         if (traits != nullptr)
         {

            // add the symbolic traits value to the traits dictionary.
            CFDictionaryAddValue(traits, kCTFontSymbolicTrait, symTraits);

            // add the traits attribute to our attributes.
            CFDictionaryAddValue(attributes, kCTFontTraitsAttribute, traits);

            CFRelease(traits);

         }

         CFRelease(symTraits);

      }

      // Create the font descriptor with our attributes and input size.
      descriptor = CTFontDescriptorCreateWithAttributes(attributes);

//      __Check(descriptor != nullptr);

      CFRelease(attributes);

   }

   // Return our font descriptor.
   return descriptor;

}


CTFontRef CreateFont(CTFontDescriptorRef iFontDescriptor, CGFloat iSize)
{

//   __Check(iFontDescriptor != nullptr);

   // Create the font from the font descriptor and input size. Pass
   // nullptr for the matrix parameter to use the default matrix (identity).
   return CTFontCreateWithFontDescriptor(iFontDescriptor, iSize, nullptr);

}


CTFontRef CreateBoldFont(CTFontRef iFont, Boolean iMakeBold)
{

   CTFontSymbolicTraits desiredTrait = 0;

   CTFontSymbolicTraits traitMask;

   // If we are trying to make the font bold, set the desired trait
   // to be bold.
   if (iMakeBold)
      desiredTrait = kCTFontBoldTrait;

   // Mask off the bold trait to indicate that it is the only trait
   // desired to be modified. As CTFontSymbolicTraits is a bit field,
   // we could choose to change multiple traits if we desired.
   traitMask = kCTFontBoldTrait;

   // Create a copy of the original font with the masked trait set to the
   // desired value. If the font family does not have the appropriate style,
   // this will return nullptr.

   return CTFontCreateCopyWithSymbolicTraits(iFont, 0.0, nullptr, desiredTrait, traitMask);

}


CTFontRef CreateFontConvertedToFamily(CTFontRef iFont, CFStringRef iFamily)
{

   // Create a copy of the original font with the new family. This call
   // attempts to preserve traits, and may return nullptr if that is not possible.
   // Pass in 0.0 and nullptr for size and matrix to preserve the values from
   // the original font.
   return CTFontCreateCopyWithFamily(iFont, 0.0, nullptr, iFamily);

}

//bool TextOutU_dup(HDC hdc, int x, int y, const char * pszUtf8, int iSize)
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



//void FillSolidRect_dup(HDC hdc, const ::rectangle & rectangle, color32_t clr)

//{
//   CGColorRef color = cg_create_color(clr);
//   CGRect rectangle;
//   rectangle.origin.x = prect->left;

//   rectangle.origin.y = prect->top;

//   rectangle.size.width = prect->right - prect->left;

//   rectangle.size.height = prect->bottom - prect->top;

//   CGContextFillRect(hdc->m_cgcontext, rectangle);
//   cg_release_color(color);
//}

//HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam);

//HFONT CreatePointBoldFont_dup(int nPointSize, const char * pszFaceName, int BOLD, HDC hdc);

//
//HFONT CreatePointFont_dup(int nPointSize, const char * pszFaceName, HDC hdc)

//{
//   return CreatePointBoldFont_dup(nPointSize, pszFaceName, false, hdc);

//}
//
//HFONT CreatePointBoldFont_dup(int nPointSize, const char * pszFaceName, int BOLD, HDC hdc)

//{
//   CFStringRef    string            = CFStringCreateWithCString(kCFAllocatorDefault, pszFaceName, kCFStringEncodingUTF8);

//   CreateFontDescriptorFromFamilyAndTraits(string, BOLD, nPointSize);
//   CFRelease(string);
//   return nullptr;
//}
//
//HFONT CreatePointFontIndirect_dup(const LOGFONT* pLogFont, HDC hdcParam)

//{
//
//
//   return ::CreateFontIndirect(pLogFont);

//
//
//}
//
//
//



CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);










CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy);
bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage);


bool mm_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);




bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage)
{

   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);

   if (cgctx == nullptr)
   {

      return false;

   }

   CGRect rectangle = {{0,0},{(CGFloat)cx,(CGFloat)cy}};

   CGContextDrawImage(cgctx, rectangle, inImage);

   void *data = CGBitmapContextGetData (cgctx);

   u8 * pdest = (u8 * ) pcr;

   if (data != nullptr)
   {

      for(int y = cy - 1; y >= 0; y--)
      {

         u8 * pline = (u8 *) &((unsigned int*)data)[y * cx];

         ::memcpy_dup(pdest, pline, cx* 4);

         pdest += iScan;

      }

   }

   CGContextRelease(cgctx);

   return data != nullptr;

}


CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
{

   CGContextRef    context = nullptr;

   CGColorSpaceRef colorSpace;

   void *          bitmapData;

   int             bitmapByteCount;

   int             bitmapBytesPerRow;

   bitmapBytesPerRow   = (cx * 4);

   bitmapByteCount     = (bitmapBytesPerRow * cy);

   colorSpace = CGColorSpaceCreateDeviceRGB();

   if (colorSpace == nullptr)
   {

      output_debug_string("CreateARGBBitmapContext: Error allocating color space\n");

      return nullptr;

   }

   //   bitmapData = malloc( bitmapByteCount );
   //
   //   if (bitmapData == nullptr)
   //   {
   //
   //      output_debug_string("CreateARGBBitmapContext: Memory not allocated!");
   //
   //      CGColorSpaceRelease( colorSpace );
   //
   //      return nullptr;
   //
   //   }
   //
   //   __memset(bitmapData, 0, bitmapByteCount);

   // Create the bitmap context. We want pre-multiplied argb, 8-bits
   // per component. Regardless of what the source image format is
   // (CMYK, Grayscale, and so on) it will be converted over to the format
   // specified here by CGBitmapContextCreate.
   context =
   CGBitmapContextCreate (
   nullptr,
   cx,
   cy,
   8,
   bitmapBytesPerRow,
   colorSpace,
   kCGImageAlphaPremultipliedLast);

   //   if (context == nullptr)
   //   {
   //
   //      free (bitmapData);
   //
   //      output_debug_string("CreateARGBBitmapContext: Context not created!");
   //
   //   }

   CGColorSpaceRelease( colorSpace );

   return context;
}


