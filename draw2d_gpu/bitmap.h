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

      //bool Init();
      //bool InitGL();
      //bool InitGLExtensions();
      //bool InitPBuffer();
      //void Cleanup();

      

      void * get_os_data() const;


      bool LoadBitmap(const ::scoped_string & scopedstrResourceName);
      bool LoadBitmap(unsigned int nIDResource);
      bool LoadOEMBitmap(unsigned int nIDBitmap); // for OBM_/OCR_/OIC_
      bool CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, unsigned int nPlanes, unsigned int nBitcount, const void * lpBits, int stride);
//      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight);
      
      void create_bitmap(::draw2d::graphics * pgraphics, const ::int_size& size, void** ppcolorref, int* piScan) override;
      void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void* pjBits, unsigned int iUsage) override;


      //int GetBitmap(BITMAP* pBitMap);


      unsigned int SetBitmapBits(unsigned int dwCount, const void * lpBits);
      // unsigned int GetBitmapBits(unsigned int dwCount, LPVOID lpBits) const;
      ::int_size SetBitmapDimension(int nWidth, int nHeight);
      ::int_size GetBitmapDimension() const;

      // void dump(dump_context & dumpcontext) const override;


      //virtual void attach(void * posdata);
      virtual void * detach();

      //glglgl virtual HBITMAP _GetHBITMAP();
      //glglgl virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_gpu



