#pragma once


#include "acme/prototype/prototype/memory.h"
#include "aura/graphics/draw2d/bitmap.h"



namespace draw2d_gpu
{


   class CLASS_DECL_DRAW2D_GPU bitmap : 
      virtual public ::draw2d::bitmap
   {
   public:


      bool                 m_bTexture;
      //glglgl GLuint               m_texture;
      memory               m_memIn;
      memory               m_memOut;

      bool                 m_bFlashed;
      bool                 m_bPBuffer;
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
//      GLXContext PBufferCtx;
//      GLXContext WinCtx;
//      GLXPbuffer PBuffer;
//      GLXFBConfig* fbc;
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


      ::i32_size               m_sizeOut;
      ::i32_size               m_sizeIn;


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

      //bool Init();
      //bool InitGL();
      //bool InitGLExtensions();
      //bool InitPBuffer();
      //void Cleanup();

      

      void * get_os_data() const;


      bool LoadBitmap(const ::scoped_string & scopedstrResourceName);
      bool LoadBitmap(::u32 nIDResource);
      bool LoadOEMBitmap(::u32 nIDBitmap); // for OBM_/OCR_/OIC_
      bool CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, ::u32 nPlanes, ::u32 nBitcount, const void * lpBits, int stride);
//      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      
      void create_bitmap(::draw2d::graphics * pgraphics, const ::i32_size& size, void** ppcolorref, int* piScan) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, ::u32 flInit, const void* pjBits, ::u32 iUsage) override;


      //int GetBitmap(BITMAP* pBitMap);


      ::u32 SetBitmapBits(::u32 dwCount, const void * lpBits);
      // ::u32 GetBitmapBits(::u32 dwCount, LPVOID lpBits) const;
      ::i32_size SetBitmapDimension(int nWidth, int nHeight);
      ::i32_size GetBitmapDimension() const;

      // void dump(dump_context & dumpcontext) const override;


      //virtual void attach(void * posdata);
      virtual void * detach();

      //glglgl virtual HBITMAP _GetHBITMAP();
      //glglgl virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_gpu



