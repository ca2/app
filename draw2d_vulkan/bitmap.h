#pragma once


#include "acme/prototype/prototype/memory.h"
#include "aura/graphics/draw2d/bitmap.h"


//#include <VK/vk.h>
//#include <VK/vku.h>
//#include <VK/vkext.h>
#ifdef LINUX
#include <VK/vkx.h>
#endif

#pragma warning (disable : 4244)

#include <vulkan/vulkan.h>


//#define WGL_DRAW_TO_PBUFFER_ARB                   0x202D
//#define WGL_MAX_PBUFFER_HEIGHT_ARB                0x2030
//#define WGL_MAX_PBUFFER_PIXELS_ARB                0x202E
//#define WGL_MAX_PBUFFER_WIDTH_ARB                 0x202F
//#define WGL_PBUFFER_HEIGHT_ARB                    0x2035
//#define WGL_PBUFFER_LARGEST_ARB                   0x2033
//#define WGL_PBUFFER_LOST_ARB                      0x2036
//#define WGL_PBUFFER_WIDTH_ARB                     0x2034
//
//DECLARE_HANDLE(HPBUFFERARB);
//
//
////-----------------------------------------------------------------------------
//// WGL_ARB_pixel_format.
////-----------------------------------------------------------------------------
//
//#define WGL_ACCELERATION_ARB                      0x2003
//#define WGL_ACCUM_ALPHA_BITS_ARB                  0x2021
//#define WGL_ACCUM_BITS_ARB                        0x201D
//#define WGL_ACCUM_BLUE_BITS_ARB                   0x2020
//#define WGL_ACCUM_GREEN_BITS_ARB                  0x201F
//#define WGL_ACCUM_RED_BITS_ARB                    0x201E
//#define WGL_ALPHA_BITS_ARB                        0x201B
//#define WGL_ALPHA_SHIFT_ARB                       0x201C
//#define WGL_AUX_BUFFERS_ARB                       0x2024
//#define WGL_BLUE_BITS_ARB                         0x2019
//#define WGL_BLUE_SHIFT_ARB                        0x201A
//#define WGL_COLOR_BITS_ARB                        0x2014
//#define WGL_DEPTH_BITS_ARB                        0x2022
//#define WGL_DOUBLE_BUFFER_ARB                     0x2011
//#define WGL_DRAW_TO_BITMAP_ARB                    0x2002
//#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
//#define WGL_FULL_ACCELERATION_ARB                 0x2027
//#define WGL_GENERIC_ACCELERATION_ARB              0x2026
//#define WGL_GREEN_BITS_ARB                        0x2017
//#define WGL_GREEN_SHIFT_ARB                       0x2018
//#define WGL_NEED_PALETTE_ARB                      0x2004
//#define WGL_NEED_SYSTEM_PALETTE_ARB               0x2005
//#define WGL_NO_ACCELERATION_ARB                   0x2025
//#define WGL_NUMBER_OVERLAYS_ARB                   0x2008
//#define WGL_NUMBER_PIXEL_FORMATS_ARB              0x2000
//#define WGL_NUMBER_UNDERLAYS_ARB                  0x2009
//#define WGL_PIXEL_TYPE_ARB                        0x2013
//#define WGL_RED_BITS_ARB                          0x2015
//#define WGL_RED_SHIFT_ARB                         0x2016
//#define WGL_SHARE_ACCUM_ARB                       0x200E
//#define WGL_SHARE_DEPTH_ARB                       0x200C
//#define WGL_SHARE_STENCIL_ARB                     0x200D
//#define WGL_STENCIL_BITS_ARB                      0x2023
//#define WGL_STEREO_ARB                            0x2012
//#define WGL_SUPPORT_GDI_ARB                       0x200F
//#define WGL_SUPPORT_VULKAN_ARB                    0x2010
//#define WGL_SWAP_COPY_ARB                         0x2029
//#define WGL_SWAP_EXCHANGE_ARB                     0x2028
//#define WGL_SWAP_LAYER_BUFFERS_ARB                0x2006
//#define WGL_SWAP_METHOD_ARB                       0x2007
//#define WGL_SWAP_UNDEFINED_ARB                    0x202A
//#define WGL_TRANSPARENT_ALPHA_VALUE_ARB           0x203A
//#define WGL_TRANSPARENT_ARB                       0x200A
//#define WGL_TRANSPARENT_BLUE_VALUE_ARB            0x2039
//#define WGL_TRANSPARENT_GREEN_VALUE_ARB           0x2038
//#define WGL_TRANSPARENT_INDEX_VALUE_ARB           0x203B
//#define WGL_TRANSPARENT_RED_VALUE_ARB             0x2037
//#define WGL_TYPE_COLORINDEX_ARB                   0x202C
//#define WGL_TYPE_RGBA_ARB                         0x202B
//
//
////-----------------------------------------------------------------------------
//// Globals.
////-----------------------------------------------------------------------------
//
//#define TEXTURE_WIDTH   64
//#define TEXTURE_HEIGHT  64


namespace draw2d_vulkan
{


   class CLASS_DECL_DRAW2D_VULKAN bitmap : 
      virtual public ::draw2d::bitmap
   {
   public:


      bool                 m_bTexture;
//      VKuint               m_texture;
      memory               m_memIn;
      memory               m_memOut;

      bool                 m_bFlashed;
      bool                 m_bPBuffer;

      VkInstance           m_vkinstance;
#if defined(WINDOWS_DESKTOP)
      HWND m_hwnd;
      HINSTANCE m_hinstance;
#endif
//#ifdef WINDOWS
//
//      HWND  g_hWnd;
//      HDC   g_hDC;
//      HGLRC g_hRC;
//      HDC   g_hPBufferDC;
//      HGLRC g_hPBufferRC;
//      HPBUFFERARB g_hPBuffer;
//
//#else
//      Display *dpy;
//      Window win;
//      VKXContext PBufferCtx;
//      VKXContext WinCtx;
//      VKXPbuffer PBuffer;
//      VKXFBConfig* fbc;
//      XVisualInfo* vi = nullptr;
//      Colormap cmap;
//      XSetWindowAttributes swa;
//      XEvent happening;
//      Bool bRedraw = False;
//      int dummy;
//      int nElements;
//      int nval;
//      int nCounter;
//
//#endif
//

      ::int_size               m_sizeOut;
      ::int_size               m_sizeIn;


      bitmap();
      virtual ~bitmap();

      void destroy_bitmap();

      // Resample Quality
      // 0 - low
      // 1 - good
      // 2 - excelent
      void create_texture(int iResampleQuality);
      //bool flash();
      void defer_reveal();

      bool Init();
      bool InitGL();
      bool InitGLExtensions();
      bool InitPBuffer();
      void Cleanup();

      

      void * get_os_data() const;


      bool LoadBitmap(const ::string & lpszResourceName);
      bool LoadBitmap(unsigned int nIDResource);
      bool LoadOEMBitmap(unsigned int nIDBitmap); // for OBM_/OCR_/OIC_
      bool CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, unsigned int nPlanes, unsigned int nBitcount, const void * lpBits, int stride);
      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      
      void create_bitmap(::draw2d::graphics * pgraphics, const ::int_size& size, void** ppcolorref, int* piScan) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void* pjBits, unsigned int iUsage) override;


      int GetBitmap(BITMAP* pBitMap);


      unsigned int SetBitmapBits(unsigned int dwCount, const void * lpBits);
      unsigned int GetBitmapBits(unsigned int dwCount, LPVOID lpBits) const;
      ::int_size SetBitmapDimension(int nWidth, int nHeight);
      ::int_size GetBitmapDimension() const;

      // void dump(dump_context & dumpcontext) const override;


      //virtual void attach(void * posdata);
      virtual void * detach();

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_vulkan



