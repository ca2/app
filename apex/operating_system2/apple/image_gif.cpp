//
//  visual_apple_image_gif.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/10/17.
//
#include "framework.h"

//#include <ImageIO/ImageIO.h>
//
//#ifdef APPLE_IOS
//
//#import <MobileCoreServices/MobileCoreServices.h>
//
//#endif
//
//
//void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);
//
//
//void imaging::_load_image(::image * pimage, ::pointer<image_frame_array>& pframea, ::memory_pointer pmemory)
//{
//
//   if(!pmemory || pmemory->is_empty())
//   {
//
//      return false;
//
//   }
//
//   int w = 0;
//
//   int h = 0;
//
//   int iScan = 0;
//
//   ::apex::malloc < color32_t * > pcolorref;
//
//   CFDataRef data = CFDataCreateWithBytesNoCopy(nullptr, pmemory->data(), pmemory->size(), kCFAllocatorNull);
//
//   //https://github.com/Flipboard/FLAnimatedImage/blob/master/FLAnimatedImage/FLAnimatedImage.m
//
//   if(data == nullptr)
//   {
//
//      return false;
//
//   }
//
//   CGImageSourceRef imagesource = nullptr;
//
//   {
//
//      CFDictionaryRef   options;
//      CFStringRef       keys[2];
//      CFTypeRef         values[2];
//
//      // Set up options if you want them. The options here are for
//      // caching the image in a decoded form and for using floating-point_i32
//      // values if the image format supports them.
//      keys[0] = kCGImageSourceShouldCache;
//      values[0] = (CFTypeRef)kCFBooleanFalse;
//
//      // Create the dictionary
//      options = CFDictionaryCreate(nullptr, (const void **) keys,
//                                   (const void **) values, 1,
//                                   &kCFTypeDictionaryKeyCallBacks,
//                                   &kCFTypeDictionaryValueCallBacks);
//
//      // Note: We could leverage `CGImageSourceCreateWithURL` too to add a second initializer `-initWithAnimatedGIFContentsOfURL:`.
//      imagesource = CGImageSourceCreateWithData(data, options);
//
//      CFRelease(options);
//
//   }
//
//   // Early return on failure!
//   if (imagesource == nullptr)
//   {
//
//      return false;
//
//   }
//
//   // Early return if not GIF!
//   CFStringRef imagesourcetype = CGImageSourceGetType(imagesource);
//
//   bool bGif = UTTypeConformsTo(imagesourcetype, kUTTypeGIF);
//
//   if (!bGif)
//   {
//
//      CFRelease(imagesource);
//
//      return ::error_failed;
//
//   }
//
//   // Get `LoopCount`
//   // Note: 0 means repeating the animation indefinitely.
//   // Image properties example:
//   // {
//   //     FileSize = 314446;
//   //     "{GIF}" = {
//   //         HasGlobalColorMap = 1;
//   //         LoopCount = 0;
//   //     };
//   // }
//   CFDictionaryRef imageproperties = CGImageSourceCopyProperties(imagesource, nullptr);
//
//   CFDictionaryRef gifproperties = (CFDictionaryRef) CFDictionaryGetValue(imageproperties, kCGImagePropertyGIFDictionary);
//
//   CFNumberRef loopCount = (CFNumberRef) CFDictionaryGetValue(gifproperties, kCGImagePropertyGIFLoopCount);
//
//   int iLoopCount;
//
//   if(!CFNumberGetValue(loopCount, kCFNumberSInt32Type, &iLoopCount))
//   {
//
//      iLoopCount = 0;
//
//   }
//
//   // Iterate through frame images
//   size_t imageCount = CGImageSourceGetCount(imagesource);
//
//   for (size_t i = 0; i < imageCount; i++)
//   {
//
//      CGImageRef pimage = CGImageSourceCreateImageAtIndex(imagesource, i, nullptr);
//
//      if(pimage)
//      {
//
//         int w = 0;
//
//         int h = 0;
//
//         int iScan = 0;
//
//         ::apex::malloc < color32_t * > pdata((color32_t *) cg_image_get_image_data(w, h, iScan, pimage));
//         // Check for valid `frameImage` before parsing its properties as frames can be corrupted (and `frameImage` even `nil` when `frameImageRef` was valid).
//
//         auto p = __new(image_frame);
//
//         p->m_pimage = create_image();
//
//         if(p->m_pimage->create({ w, h }))
//         {
//
//            ::copy_colorref(p->m_pimage->colorref(), w, h, p->m_pimage->scan_size(), pdata, iScan);
//
//            p->m_edisposal = ::draw2d::e_disposal_none;
//
//            p->m_rectangle.left = 0;
//
//            p->m_rectangle.top = 0;
//
//            p->m_rectangle.right = w;
//
//            p->m_rectangle.bottom = h;
//
//            p->m_colorTransparent = 0;
//
//            p->m_bTransparent = false;
//
//            p->m_bLocalPalette = false;
//
//            pframea->m_size.cx() = maximum(w, pframea->m_size.cx());
//
//            pframea->m_size.cy() = maximum(h, pframea->m_size.cy());
//
//            pframea->add(p);
//
//            // Get `DelayTime`
//            // Note: It's not in (1/100) of a second like still falsely described in the documentation as per iOS 8 (rdar://19507384) but in seconds stored as `kCFNumberFloat32Type`.
//            // Frame properties example:
//            // {
//            //     ColorModel = rgb;
//            //     Depth = 8;
//            //     PixelHeight = 960;
//            //     PixelWidth = 640;
//            //     "{GIF}" = {
//            //         DelayTime = "0.4";
//            //         UnclampedDelayTime = "0.4";
//            //     };
//            // }
//
//            CFDictionaryRef frameproperties = CGImageSourceCopyPropertiesAtIndex(imagesource, i, nullptr);
//
//            CFDictionaryRef gifproperties = (CFDictionaryRef) CFDictionaryGetValue(frameproperties, kCGImagePropertyGIFDictionary);
//
//            // Try to use the unclamped delay time; fall back to the normal delay time.
//            CFNumberRef delayTime = (CFNumberRef) CFDictionaryGetValue(gifproperties, kCGImagePropertyGIFUnclampedDelayTime);
//
//            double dDelay = 0.0;
//
//            if(delayTime == nullptr || !CFNumberGetValue(delayTime, kCFNumberFloat64Type, &dDelay))
//            {
//
//               delayTime = (CFNumberRef) CFDictionaryGetValue(gifproperties, kCGImagePropertyGIFDelayTime);
//
//               if(delayTime == nullptr || !CFNumberGetValue(delayTime, kCFNumberFloat64Type, &dDelay))
//               {
//
//                  dDelay = 0.0;
//
//               }
//
//            }
//
//            p->m_tick = (::u32) (dDelay * 1000.0);
//
//            if(p->m_tick < 90)
//            {
//
//               p->m_tick = 90;
//
//            }
//
//            p->m_pimage->create_helper_map();
//
//            pframea->m_timeTotal += p->m_tick;
//
//         }
//
//      }
//
//   }
//
//   CFRelease(gifproperties);
//
//   CFRelease(imagesource);
//
//   CFRelease(imagesourcetype);
//
//   return true;
//
//}
//
//
//
