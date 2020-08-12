#include "framework.h"


namespace draw2d_direct2d
{


   bitmap::bitmap()
   {


   }


   bitmap::~bitmap()
   {

      destroy();

   }


   bool bitmap::CreateBitmap(::draw2d::graphics* pgraphics, const ::size& sizeParam, UINT nPlanes, UINT nBitcount, const void * lpBits, int stride)
   {

      ::draw2d::lock draw2dlock;

      if (m_pbitmap != nullptr)
      {

         destroy();

      }

      D2D1_SIZE_U size;

      size.width = sizeParam.cx;
      size.height = sizeParam.cy;

      D2D1_BITMAP_PROPERTIES props;

      props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
      props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

      draw2d_direct2d::graphics * pgraphics2d = dynamic_cast < ::draw2d_direct2d::graphics * > (pgraphics);

      pgraphics2d->m_prendertarget->GetDpi(&props.dpiX, &props.dpiY); // Thank you https://repo.anl-external.org/repos/BlueTBB/tbb41_20130314oss/examples/common/gui/d2dvideo.cpp

      //props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
      //props.colorContext = nullptr;

      //if(ppdata != nullptr)
      {
         // g.m_pdc->CreateBitmap(size, *ppdata, cx * sizeof(COLORREF), props, &m_pbitmap);
      }
      //else
      //{
      HRESULT hr = ((ID2D1DeviceContext *)pgraphics->get_os_data())->CreateBitmap(size, lpBits, stride, props, &m_pbitmap);

      //}

      if (FAILED(hr))
      {

         return false;

      }

      xxf_zero(m_map);
      //    m_pbitmap->Map(D2D1_MAP_OPTIONS_READ | D2D1_MAP_OPTIONS_WRITE, &m_map);
      //
      //if(ppdata != nullptr)
      // *ppdata = (COLORREF *) m_map.bits;
      m_osdata[0] = m_pbitmap.Get();

      return true;

   }

   
   bool bitmap::CreateBitmapIndirect(::draw2d::graphics* pgraphics, LPBITMAP lpBitmap)
   {
      
      return false;

   }


   bool bitmap::CreateDIBSection(::draw2d::graphics* pgraphics, const ::size & size, UINT usage, void **ppvBits, int * stride, HANDLE hSection, u32 offset)
   {

      ::draw2d::lock draw2dlock;

      if (m_pbitmap != nullptr)
      {

         destroy();

      }

      D2D1_SIZE_U usize;

      usize.width = abs(size.cx);

      usize.height = abs(size.cy);

      D2D1_BITMAP_PROPERTIES1 props = {};

      props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

      props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

      draw2d_direct2d::graphics * pgraphics2d = dynamic_cast < ::draw2d_direct2d::graphics * > (pgraphics);

      pgraphics2d->m_prendertarget->GetDpi(&props.dpiX, &props.dpiY); // Thank you again https://repo.anl-external.org/repos/BlueTBB/tbb41_20130314oss/examples/common/gui/d2dvideo.cpp      props.bitmapOptions = D2D1_BITMAP_OPTIONS_CPU_READ | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

      props.colorContext = nullptr;

      //props.bitmapOptions = D2D1_BITMAP_OPTIONS_NONE;

      props.bitmapOptions = D2D1_BITMAP_OPTIONS_CPU_READ | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

      props.bitmapOptions = D2D1_BITMAP_OPTIONS_CPU_READ | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

      //props.bitmapOptions = D2D1_BITMAP_OPTIONS_CPU_READ | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

      //m_memory.set_size(size.width * size.height * sizeof(COLORREF));

      HRESULT hr;

      //if(ppvBits == nullptr || *ppvBits == nullptr)
      {

         // hr = METROWIN_DC(pgraphics)->m_pdc->CreateBitmap(size, nullptr, 0, props, &m_pbitmap);

      }
      //else
      {

         //hr = METROWIN_DC(pgraphics)->m_pdevicecontext->CreateBitmap(size, m_memory.get_data(), size.width * sizeof(COLORREF), props, &m_pbitmap1);

      }

      hr = ((ID2D1DeviceContext *)pgraphics->get_os_data())->CreateBitmap(usize, nullptr, 0, props, &m_pbitmap1);

      if (FAILED(hr) || m_pbitmap1 == nullptr)
      {

         return false;

      }

      if (FAILED(m_pbitmap1.As(&m_pbitmap)))
      {

         return false;

      }

      m_osdata[0] = m_pbitmap.Get();

      m_osdata[1] = m_pbitmap1.Get();

      return true;

   }


   bool bitmap::CreateDIBitmap(::draw2d::graphics* pgraphics, int cx, int cy, u32 flInit, const void *pjBits, UINT iUsage)
   {

      return false;

   }


   u32 bitmap::SetBitmapBits(u32 dwCount, const void * lpBits)
   {

      //return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits);
      return 0;

   }
   u32 bitmap::GetBitmapBits(u32 dwCount, LPVOID lpBits) const
   {
      //return ::GetBitmapBits((HBITMAP)get_handle(), dwCount, lpBits);
      return 0;
   }
   bool bitmap::LoadBitmap(const char * lpszResourceName)
   {
      //   return Attach(::LoadBitmap(::aura::FindResourceHandle(
      //lpszResourceName, RT_BITMAP), lpszResourceName));
      return FALSE;

   }

   //size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   //{


   //   ::exception::throw_not_implemented();

   //   return ::size(0, 0);

   //}

   size bitmap::GetBitmapDimension() const
   {

      if (m_pbitmap == nullptr)
         return ::size(0, 0);

      D2D1_SIZE_U size = m_pbitmap->GetPixelSize();

      return ::size(size.width, size.height);

   }


   bool bitmap::LoadBitmap(UINT nIDResource)
   {

      //return Attach(::LoadBitmap(::aura::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return false;

   }


   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {

      //return Attach(::LoadBitmap(nullptr, MAKEINTRESOURCE(nIDBitmap)));
      return false;

   }


   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics* pgraphics, int nWidth, int nHeight)
   {

      ::draw2d::lock draw2dlock;

      if (m_pbitmap != nullptr)
      {

         destroy();

      }

      D2D1_SIZE_U size;

      size.width = nWidth;
      size.height = nHeight;

      D2D1_BITMAP_PROPERTIES1 props;

      props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
      props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

      draw2d_direct2d::graphics * pgraphics2d = dynamic_cast < ::draw2d_direct2d::graphics * > (pgraphics);

      pgraphics2d->m_prendertarget->GetDpi(&props.dpiX, &props.dpiY); // Thanks again and a third time https://repo.anl-external.org/repos/BlueTBB/tbb41_20130314oss/examples/common/gui/d2dvideo.cpp      props.bitmapOptions = D2D1_BITMAP_OPTIONS_CPU_READ | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

      props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CPU_READ;

      //if(ppdata != nullptr)
      {
         // g.m_pdc->CreateBitmap(size, *ppdata, cx * sizeof(COLORREF), props, &m_pbitmap);
      }
      //else
      //      ID2D1Bitmap1 * pbitmap1;
      {
         ((ID2D1DeviceContext *)pgraphics->get_os_data())->CreateBitmap(size, nullptr, size.width * sizeof(COLORREF), props, &m_pbitmap1);
      }
      m_pbitmap = m_pbitmap1;

      m_osdata[0] = m_pbitmap.Get();

      m_osdata[1] = m_pbitmap1.Get();

      return true;

   }


   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics* pgraphics, int nWidth, int nHeight)
   {

      ::draw2d::lock draw2dlock;

      if (m_pbitmap != nullptr)
      {

         destroy();

      }

      D2D1_SIZE_U size;

      size.width = nWidth;
      size.height = nHeight;

      D2D1_BITMAP_PROPERTIES1 props;

      props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
      props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

      draw2d_direct2d::graphics * pgraphics2d = dynamic_cast < ::draw2d_direct2d::graphics * > (pgraphics);

      pgraphics2d->m_prendertarget->GetDpi(&props.dpiX, &props.dpiY); // One more time, Thank you very much https://repo.anl-external.org/repos/BlueTBB/tbb41_20130314oss/examples/common/gui/d2dvideo.cpp      props.bitmapOptions = D2D1_BITMAP_OPTIONS_CPU_READ | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

      props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CPU_READ;

      //if(ppdata != nullptr)
      {
         // g.m_pdc->CreateBitmap(size, *ppdata, cx * sizeof(COLORREF), props, &m_pbitmap);
      }
      //else
      {
         ((ID2D1DeviceContext *)pgraphics->get_os_data())->CreateBitmap(size, nullptr, size.width * sizeof(COLORREF), &props, &m_pbitmap1);
      }
      m_pbitmap = m_pbitmap1;

      m_osdata[0] = m_pbitmap.Get();

      m_osdata[1] = m_pbitmap1.Get();

      //m_pbitmap->Map(D2D1_MAP_OPTIONS_READ | D2D1_MAP_OPTIONS_WRITE, &m_map);

      //if(ppdata != nullptr)
      // *ppdata = (COLORREF *) m_map.bits;


      return true;

   }


   void bitmap::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

      dumpcontext << "\n";

   }


   void bitmap::defer_update(::draw2d::graphics* pgraphics) const
   {

   }


   bool bitmap::attach(void * hbitmap)
   {

      if (m_pbitmap != nullptr)
      {

         destroy();

      }

      m_pbitmap = (ID2D1Bitmap *)hbitmap;

      m_pbitmap.As(&m_pbitmap1);

      m_osdata[0] = m_pbitmap.Get();

      m_osdata[1] = m_pbitmap1.Get();

      return true;

   }

   void * bitmap::detach()
   {

      clear_os_data();

      m_pbitmap1 = nullptr;

      return m_pbitmap.Detach();

   }


   void bitmap::destroy()
   {

      m_pbitmap = nullptr;

      m_pbitmap1 = nullptr;

      clear_os_data();

   }


} // namespace draw2d_direct2d