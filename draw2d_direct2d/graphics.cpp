#include "framework.h"
#include "aura/user/_user.h"
#include "CustomRenderer.h"
#include <math.h>


void dpi_initialize(ID2D1Factory* pFactory);


CLASS_DECL_AURA float os_get_dpi();


#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define multi_threaded D2D1_FACTORY_TYPE_MULTI_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?


#ifdef WINDOWS_DESKTOP

CLASS_DECL_AURA void directx_debug();

#endif


namespace draw2d_direct2d
{


   graphics::state::state()
   {

   }


   graphics::state::~state()
   {

   }


   graphics::graphics()
   {

      m_ealphamodeDevice = ::draw2d::alpha_mode_none;

      clear_os_data();

      m_pthis = this;

      defer_create_mutex();

      m_pstate = __new(state);

      m_bSaveClip = false;

      m_hdcAttach = nullptr;

      m_ppen.create();

      m_iType     = 0;

      m_interpolationmode = D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC;

      m_bitmapinterpolationmode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;

   }


   graphics::~graphics()
   {

      destroy();

   }


   void graphics::assert_valid() const
   {

      context_object::assert_valid();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {

      context_object::dump(dumpcontext);

      dumpcontext << "get_handle1() = " << (::iptr) get_handle1();
      dumpcontext << "\nm_hAttribDC = " << (::iptr) get_handle2();
      dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";

   }


   bool graphics::IsPrinting()
   {

      return m_bPrinting;

   }


   bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      __throw(todo());
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }


   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

      __throw(todo());

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics *)
   {

      ::draw2d::lock draw2dlock;

      if (m_iType != 0)
      {

         destroy();

      }

      defer_direct2d_initialize();

      HRESULT hr;

      Microsoft::WRL::ComPtr<ID2D1DeviceContext> pdevicecontextTemplate;

      if (FAILED(hr = global_draw_get_d2d1_device()->CreateDeviceContext(
                      D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
                      //D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
                      &pdevicecontextTemplate)))
      {

         trace_hr("graphics::CreateCompatibleDC, CreateDeviceContext (1) ", hr);

         return false;

      }

      Microsoft::WRL::ComPtr<ID2D1RenderTarget> prendertargetTemplate;

      auto dpi = os_get_dpi();

      if (dpi <= 0.0)
      {

         ASSERT(FALSE);

         return false;

      }

      pdevicecontextTemplate->SetDpi(dpi, dpi);

      if (FAILED(hr = pdevicecontextTemplate->QueryInterface(IID_ID2D1RenderTarget,(void **)&prendertargetTemplate)))
      {

         trace_hr("graphics::CreateCompatibleDC, QueryInterface (2) ",hr);

         return false;

      }

      D2D1_SIZE_U sizeu = D2D1::SizeU(1, 1);

      D2D1_PIXEL_FORMAT pixelformat;

      pixelformat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

      pixelformat.format = DXGI_FORMAT_B8G8R8A8_UNORM;

      if (FAILED(hr = prendertargetTemplate->CreateCompatibleRenderTarget(
                      nullptr,
                      &sizeu,
                      &pixelformat,
                      D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_NONE,
                      &m_pbitmaprendertarget)))
      {

         trace_hr("graphics::CreateCompatibleDC, CreateCompatibleRenderTarget (3) ", hr);

         return false;

      }

      hr = m_pbitmaprendertarget.As(&m_prendertarget);

      if(FAILED(hr))
      {

         m_pbitmaprendertarget = nullptr;

         return false;

      }

      hr = m_pbitmaprendertarget.As(&m_pdevicecontext);

      if(FAILED(hr))
      {

         m_prendertarget = nullptr;

         m_pbitmaprendertarget = nullptr;

         return false;
      }

      if (m_pbitmap.is_null())
      {

         m_pbitmap.create();

      }

      ID2D1Bitmap * pbitmap;

      hr = m_pbitmaprendertarget->GetBitmap(&pbitmap);

      if(FAILED(hr))
      {

         m_pbitmaprendertarget = nullptr;

         return false;

      }

      m_pbitmap->attach(pbitmap);

      m_iType = 3;

      m_osdata[data_device_context] = m_pdevicecontext.Get();

      m_osdata[data_render_target] = m_prendertarget.Get();

      return true;

   }


   int graphics::GetDeviceCaps(int nIndex)
   {

      __throw(todo());

   }


   point graphics::GetBrushOrg()
   {
      __throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //::point point;
      //VERIFY(::GetBrushOrgEx(get_handle1(), &point));
      //return point;
   }

   point graphics::SetBrushOrg(int x, int y)
   {
      __throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //::point point;
      //VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
      //return point;
   }

   point graphics::SetBrushOrg(const ::point & point)
   {
      __throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
      //return point;
   }

   int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      __throw(todo());
      //ASSERT(get_handle2() != nullptr);
      //return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);
   }

   bool graphics::BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop)
   {

      //return ::draw2d::graphics::BitBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop);

      //if (m_pimageAlphaBlend->is_set())
      //{
      //   //return true;

      //   // Reference implementation

      //   ::rect rectAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

      //   if (x < 0)
      //   {

      //      xSrc -= x;

      //      nWidth += x;

      //      x = 0;

      //   }

      //   if (y < 0)
      //   {

      //      ySrc -= y;

      //      nHeight += y;

      //      y = 0;

      //   }

      //   point ::point(x, y);

      //   size size(nWidth, nHeight);

      //   ::rect rectBlend(point, size);

      //   ::rect rectIntersect;

      //   if (rectIntersect.intersect(rectAlphaBlend, rectBlend))
      //   {

      //      ::image_pointer pimage1;

      //      pimage1 = create_image(size);

      //      ::rect rectDib1(::point(), pimage1->m_size);

      //      pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //      pimage1->get_graphics()->fill_rect(rectDib1, ARGB(0, 0, 0, 0));

      //      if (!pimage1->from(::point(), pgraphicsSrc, ::point(xSrc, ySrc), size))
      //      {

      //         return false;

      //      }

      //      ::image_pointer pimage2;

      //      pimage2 = create_image(size);

      //      pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //      pimage2->get_graphics()->fill_rect(rectDib1, ARGB(255, 0, 0, 0));

      //      if (!pimage2->from(::point(), m_pimageAlphaBlend, point - m_pointAlphaBlend, rectIntersect.size()))
      //      {

      //         return false;

      //      }

      //      __pointer(::draw2d_direct2d::graphics) pgraphicsDib1 = pimage1->get_graphics();

      //      __pointer(::draw2d_direct2d::graphics) pgraphicsDib2 = pimage2->get_graphics();

      //      HRESULT hr = ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->EndDraw();

      //      pgraphicsDib2->m_pdevicecontext->DrawImage(
      //      (ID2D1Bitmap *)pgraphicsDib1->get_current_bitmap()->get_os_data(),
      //      D2D1::Point2F(0.f, 0.f),
      //      d2d1::rectf(rectDib1),
      //      D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
      //      D2D1_COMPOSITE_MODE_SOURCE_OVER);

      //      if (SUCCEEDED(hr))
      //      {

      //         ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->BeginDraw();

      //      }

      //      set_alpha_mode(::draw2d::alpha_mode_blend);

      //      BitBltRaw(x, y, nWidth, nHeight, pimage2->get_graphics(), 0, 0, dwRop);

      //      return true;

      //   }

      //}

      //return false;

      if (m_pimageAlphaBlend->is_set())
      {

         if (x < 0)
         {

            xSrc -= x;

            nWidth += x;

            x = 0;

         }

         if (y < 0)
         {

            ySrc -= y;

            nHeight += y;

            y = 0;

         }


         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         ::rect rectBlt(point((i64)x, (i64)y), size(nWidth, nHeight));

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            //if (m_pointAlphaBlend.x < 0)
            //{

            //   xSrc += -m_pointAlphaBlend.x;

            //}
            //if (m_pointAlphaBlend.y < 0)
            //{

            //   ySrc += -m_pointAlphaBlend.y;

            //}

            // The following commented out code does not work well when there is clipping
            // and some calculations are not precise
            //if (m_pimageimplDraw2dGraphics->is_set() && pgraphicsSrc->m_pimageimplDraw2dGraphics->is_set())
            //{

            //   ::point pointOff = GetViewportOrg();

            //   x += pointOff.x;

            //   y += pointOff.y;

            //   return m_pimageimplDraw2dGraphics->blend(::point(x, y), pgraphicsSrc->m_pimageimplDraw2dGraphics, ::point(xSrc, ySrc), m_pimageAlphaBlend, point(m_pointAlphaBlend.x - x, m_pointAlphaBlend.y - y), rectBlt.size());

            //}
            //else
            {

               auto pimage1 = create_image(rectBlt.size());

               pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               if (!pimage1->from(::point(), pgraphicsSrc, ::point(xSrc, ySrc), rectBlt.size()))
                  return false;

               pimage1->blend2(::point(), m_pimageAlphaBlend, point(x - m_pointAlphaBlend.x, y - m_pointAlphaBlend.y), rectBlt.size(), 255);

               BitBltRaw(x, y, nWidth, nHeight, pimage1->get_graphics(), 0, 0, dwRop);

            }

            return true;

         }

      }

      return false;
   }


   bool graphics::TextOutAlphaBlend(double x, double y, const string & str)
   {

      ASSERT(m_pimageAlphaBlend->is_ok());
      ASSERT(str.has_char());

      // "Reference" implementation for TextOutAlphaBlend

      ::size size = ::size(GetTextExtent(str));

      ::rect rectAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

      ::point point((LONG) (x), (LONG)(y));

      ::rect rectText(point, size);

      ::rect rectIntersect;

      if (rectIntersect.intersect(rectAlphaBlend, rectText))
      {

         ::draw2d::lock draw2dlock;

         auto pimage1 = create_image(size);

         ::rect rectDib1(::point(), size);

         pimage1->get_graphics()->set(get_current_font());

         pimage1->get_graphics()->set(get_current_brush());

         pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         pimage1->get_graphics()->fill_rect(rectDib1, ARGB(0, 0, 0, 0));

         pimage1->get_graphics()->text_out(0, 0, str);

         ::image_pointer pimage2;

         pimage2->create(size);

         pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         pimage2->get_graphics()->fill_rect(rectDib1, ARGB(255, 0, 0, 0));

         if (!pimage2->from(::point(), m_pimageAlphaBlend, __point(point - m_pointAlphaBlend), rectIntersect.size()))
         {

            return false;

         }

         __pointer(::draw2d_direct2d::graphics) pgraphicsDib1 = pimage1->get_graphics();

         __pointer(::draw2d_direct2d::graphics) pgraphicsDib2 = pimage2->get_graphics();

         HRESULT hr = ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->EndDraw();

         pgraphicsDib1->m_pdevicecontext->DrawImage(
         (ID2D1Bitmap *)pgraphicsDib2->get_current_bitmap()->m_osdata[0],
         D2D1::Point2F(0.f, 0.f),
         d2d1::rectf(rectDib1),
         D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
         D2D1_COMPOSITE_MODE_DESTINATION_IN);

         if (SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->BeginDraw();

         }

         set_alpha_mode(::draw2d::alpha_mode_blend);

         BitBltRaw((int)x, (int)y, rectText.width(), rectText.height(), pimage1->get_graphics(), 0, 0, SRCCOPY);

         return true;

      }

      return false;

   }


   ::estatus graphics::set(::draw2d::bitmap* pbitmap)
   {

      if (::is_null(pbitmap))
      {

         return ::error_failed;

      }

      if(m_prendertarget == nullptr)
      {

         CreateCompatibleDC(nullptr);

      }

      m_pdevicecontext->SetTarget((ID2D1Bitmap *)pbitmap->m_osdata[0]);

      m_pbitmap = pbitmap;

      m_iType = 3;

      return ::success;

   }


   //COLORREF graphics::GetNearestColor(const ::color & color)
   //{

   //   __throw(todo());

   //}


   //UINT graphics::RealizePalette()
   //{

   //   __throw(todo());
   //   
   //}


   //void graphics::UpdateColors()
   //{

   //   __throw(todo());
   //   //::UpdateColors(get_handle1());

   //}


   int graphics::GetPolyFillMode()
   {
      __throw(todo());
      //return ::GetPolyFillMode(get_handle2());
   }

   int graphics::GetROP2()
   {
      __throw(todo());
      //return ::GetROP2(get_handle2());
   }

   int graphics::GetStretchBltMode()
   {
      __throw(todo());
      //return ::GetStretchBltMode(get_handle2());
   }

   int graphics::GetMapMode()
   {
      __throw(todo());
      //return ::GetMapMode(get_handle2());
   }

   int graphics::GetGraphicsMode()
   {
      __throw(todo());
      //return ::GetGraphicsMode(get_handle2());
   }


   bool graphics::GetWorldTransform(XFORM* pXform)
   {

      __throw(todo());

   }


   bool graphics::_get(::draw2d::matrix & matrix)
   {

      D2D1::Matrix3x2F m;

      m_prendertarget->GetTransform(&m);

      matrix = ::draw2d::matrix();

      matrix.a1 = m._11;
      matrix.a2 = m._12;
      matrix.b1 = m._21;
      matrix.b2 = m._22;
      matrix.c1 = m._31;
      matrix.c2 = m._32;

      return true;

   }


   bool graphics::_set(const ::draw2d::matrix & matrix)
   {
      
      if (!m_prendertarget)
      {

         return false;

      }

      D2D1::Matrix3x2F m;

      m._11 = (FLOAT) matrix.a1;
      m._12 = (FLOAT) matrix.a2;
      m._21 = (FLOAT) matrix.b1;
      m._22 = (FLOAT) matrix.b2;
      m._31 = (FLOAT) matrix.c1;
      m._32 = (FLOAT) matrix.c2;

      m_prendertarget->SetTransform(&m);

      return true;

   }


   point graphics::GetViewportOrg()
   {

      return ::draw2d::graphics::GetViewportOrg();

   }


   size graphics::GetViewportExt()
   {

      __throw(todo());

   }

   point graphics::GetWindowOrg()
   {

      __throw(todo());

   }


   size graphics::GetWindowExt()
   {
      __throw(todo());
      //::size size;
      //::GetWindowExtEx(get_handle2(), &size);
      //return size;
   }


   point graphics::SetViewportOrg(const ::point & point)
   {

      return ::draw2d::graphics::SetViewportOrg(point.x, point.y);

   }


   size graphics::SetViewportExt(const ::size & size)
   {

      return ::draw2d::graphics::SetViewportExt(size.cx, size.cy);

   }


   point graphics::SetWindowOrg(const ::point & point)
   {
      return SetWindowOrg(point.x, point.y);
   }

   size graphics::SetWindowExt(const ::size & size)
   {
      return SetWindowExt(size.cx, size.cy);
   }


   void graphics::DPtoLP(LPPOINT lpPoints, count nCount)
   {

      __throw(todo());
      //::DPtoLP(get_handle2(), lpPoints, nCount);

   }


   void graphics::DPtoLP(RECT * prect)
   {

      __throw(todo());
      //::DPtoLP(get_handle2(), (LPPOINT)rect, 2);

   }


   void graphics::LPtoDP(LPPOINT lpPoints, count nCount)
   {

      __throw(todo());
      //::LPtoDP(get_handle2(), lpPoints, nCount);

   }


   void graphics::LPtoDP(RECT * prect)
   {

      __throw(todo());
      //::LPtoDP(get_handle2(), (LPPOINT)rect, 2);

   }


   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      __throw(todo());
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != FALSE;

   }


   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight)
   {

      __throw(todo());
      //return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != FALSE;

   }


   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {
      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != FALSE;

   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

      __throw(todo());
      //ASSERT(get_handle1() != nullptr);

      //return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != FALSE;

   }

   //bool graphics::PtVisible(int x, int y)
   //{

   //   __throw(todo());
   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::PtVisible(get_handle1(), x, y) != FALSE;

   //}

   //bool graphics::PtVisible(const ::point & point)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return PtVisible(point.x, point.y);

   //} // call virtual


   //bool graphics::RectVisible(const ::rect & rect)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::RectVisible(get_handle1(), rect) != FALSE;

   //}


   pointd graphics::current_position()
   {

      __throw(todo());
      //ASSERT(get_handle2() != nullptr);
      //::point point;
      //VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
      //return point;

   }


   bool graphics::Arc(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      ::draw2d::path_pointer path(e_create);

      double pi = 3.1415927f;

      ::rect rect(x1, y1, x2, y2);

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery, x3 - centerx) * 180.0 / pi;
      double end        = atan2(y4 - centery, x4 - centerx) * 180.0 / pi;

      //path->begin_figure(false, ::draw2d::fill_mode_winding);
      path->begin_figure();
      path->add_arc(rect, (int) start, (int) fmod(end + 360.0 - start, 360.0));
      //path->end_figure(false);
      //path->close_figure();

      return this->path(path);

   }

   bool graphics::Arc(double x1, double y1, double w, double h, angle start, angle extends)
   {

      ::draw2d::path_pointer path(e_create);

      ::rect rect((LONG) x1, (LONG)y1, (LONG)(x1 + w), (LONG)(y1 + h));

      //path->begin_figure(false, ::draw2d::fill_mode_winding);
      path->begin_figure();
      path->add_arc(rect, start, extends);
      //path->end_figure(false);
      //path->close(false);

      return this->path(path);

   }


   bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      ::draw2d::path_pointer path(e_create);

      double pi = 3.1415927f;

      ::rect rect((LONG)x1, (LONG)y1, (LONG)x2, (LONG)y2);

      double centerx = (x2 + x1) / 2.0;
      double centery = (y2 + y1) / 2.0;

      double start = atan2(y3 - centery, x3 - centerx) * 180.0 / pi;
      double end = atan2(y4 - centery, x4 - centerx) * 180.0 / pi;

      //path->begin_figure(false, ::draw2d::fill_mode_winding);
      path->begin_figure();
      path->add_arc(rect, start, end - start);
      //path->end_figure(false);

      return this->path(path);

   }


   bool graphics::Arc(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      ASSERT(get_handle1() != nullptr);

      return Arc(rect.left, rect.top, rect.right, rect.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y)  != FALSE;

   }


   bool graphics::Polyline(const POINT* lpPoints, count nCount)
   {

      ::draw2d::path_pointer path(e_create);

      //path->begin_figure(false, ::draw2d::fill_mode_winding);

      path->begin_figure();

      path->add_lines(lpPoints, nCount);

      //path->end_figure(false);

      //path->end_figure();

      return this->draw_path(path);

   }


   void graphics::frame_rect(const ::rect & rectParam, ::draw2d::brush* pbrush)
   {

      if (m_prendertarget == nullptr)
      {

         return;

      }

      D2D1_RECT_F rect;

      __copy(rect, rectParam);

      m_prendertarget->DrawRectangle(rect, pbrush->get_os_data < ID2D1Brush * > (this));

   }


   void graphics::invert_rect(const ::rect & rect)
   {

      __throw(todo());

   }


   bool graphics::DrawIcon(int x, int y, ::draw2d::icon * picon)
   {
      __throw(todo());
      //ASSERT(get_handle1() != nullptr);

      //if(picon == nullptr)
      //   return false;

      //return ::DrawIcon(get_handle1(), x, y, picon->m_hicon) != FALSE;

   }

   bool graphics::DrawIcon(const ::point & point, ::draw2d::icon * picon)
   {
      __throw(todo());
      //ASSERT(get_handle1() != nullptr);

      //if(picon == nullptr)
      //   return false;

      //return ::DrawIcon(get_handle1(), point.x, point.y, picon->m_hicon) != FALSE;

   }

   bool graphics::DrawIcon(int x, int y, ::draw2d::icon * picon, int cx, int cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {

#ifdef _UWP

      //::exception::throw_not_implemented();
      return false;

#else

      try
      {

         if(picon == nullptr)
            return FALSE;

         if(m_prendertarget == nullptr)
            return FALSE;

         bool bOk = FALSE;

         BITMAPINFO info;
         COLORREF * pcolorref;

         ZeroMemory(&info, sizeof (BITMAPINFO));

         info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
         info.bmiHeader.biWidth         = cx;
         info.bmiHeader.biHeight        = - cy;
         info.bmiHeader.biPlanes        = 1;
         info.bmiHeader.biBitCount      = 32;
         info.bmiHeader.biCompression   = BI_RGB;
         info.bmiHeader.biSizeImage     = cx * cy * 4;

         HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pcolorref, nullptr, 0);

         HDC hdc = ::CreateCompatibleDC(nullptr);

         HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, nullptr, DI_IMAGE | DI_MASK))
         {

            ::SelectObject(hdc, hbitmapOld);

            try
            {

               //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (BYTE *) pcolorref);

               ::draw2d::bitmap_pointer b(e_create);

               b->CreateBitmap(this, ::size(cx, cy), 1, 32, pcolorref, cx * sizeof(COLORREF));

               D2D1_RECT_F rect;

               rect.left   = (FLOAT) x;
               rect.top    = (FLOAT) y;
               rect.right  = rect.left    + cx;
               rect.bottom = rect.top     + cy;

               m_prendertarget->DrawBitmap((ID2D1Bitmap *) b->get_os_data(), rect);

            }
            catch(...)
            {
            }

         }

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);

         return bOk;

      }
      catch(...)
      {
      }

      return false;

#endif

   }

   bool graphics::DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {

      __throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   bool graphics::DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {


      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }


   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   {


      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }

   bool graphics::DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags, bool bPrefixText, int nTextLen, HBRUSH hBrush)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::DrawState(get_handle1(), hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

   bool graphics::DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags, bool bPrefixText, int nTextLen, ::draw2d::brush* pBrush)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

#ifdef WINDOWS_DESKTOP

   /*
   bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr); return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

   }

   bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr); return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

   }
   */

#endif


   //bool graphics::DrawEdge(RECT * prect, UINT nEdge, UINT nFlags)
   //{

   //   __throw(todo());

   //   ASSERT(get_handle1() != nullptr);

   //   //return ::DrawEdge(get_handle1(), rect, nEdge, nFlags) != FALSE;

   //}


   //bool graphics::DrawFrameControl(RECT * prect, UINT nType, UINT nState)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr); return ::DrawFrameControl(get_handle1(), rect, nType, nState) != FALSE;

   //}

   bool graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      __throw(todo());

      ASSERT(get_handle1() != nullptr);

      //return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;

   }

   bool graphics::Chord(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      __throw(todo());

      ASSERT(get_handle1() != nullptr);

      //return ::Chord(get_handle1(), rect.left, rect.top, rect.right, rect.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y) != FALSE;

   }


   void graphics::DrawFocusRect(const ::rect & rect)
   {

      __throw(todo());

      ASSERT(get_handle1() != nullptr);

   }


   bool graphics::fill_ellipse(const ::rectd & rect)
   {

      if (m_pbrush.is_null())
      {

         return false;

      }

      auto pbrush = m_pbrush->get_os_data < ID2D1Brush * >(this);

      if (!pbrush)
      {

         return false;

      }

      D2D1_ELLIPSE ellipse;

      ellipse.point.x = (float)(rect.right + rect.left) / 2.f;
      ellipse.point.y = (float)(rect.bottom + rect.top) / 2.f;
      ellipse.radiusX = (float)(rect.right - rect.left) / 2.f;
      ellipse.radiusY = (float)(rect.bottom - rect.top) / 2.f;

      defer_primitive_blend();

      m_pdevicecontext->FillEllipse(&ellipse, pbrush);

      return true;

   }


   bool graphics::draw_ellipse(const ::rectd & rect)
   {

      if (m_ppen.is_null())
      {

         return false;

      }

      auto pbrush = m_ppen->get_os_data < ID2D1Brush * >(this);

      if (!pbrush)
      {

         return false;

      }

      D2D1_ELLIPSE ellipse;

      ellipse.point.x = (float)(rect.right + rect.left) / 2.f;
      ellipse.point.y = (float)(rect.bottom + rect.top) / 2.f;
      ellipse.radiusX = (float)(rect.right - rect.left) / 2.f;
      ellipse.radiusY = (float)(rect.bottom - rect.top) / 2.f;

      defer_primitive_blend();

      m_pdevicecontext->DrawEllipse(&ellipse, pbrush,(FLOAT) m_ppen->m_dWidth);

      return true;

   }


   bool graphics::Pie(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      __throw(todo());

   }


   bool graphics::Pie(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      __throw(todo());

   }


   bool graphics::polygon(const POINTD * lppoints, count nCount)
   {

      ::draw2d::path_pointer path(e_create);

      //path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->begin_figure();

      path->add_lines(lppoints, nCount);

      //path->end_figure(true);

      path->close_figure();

      return this->path(path);

   }


   bool graphics::draw_polygon(const POINTD * lppoints, count nCount)
   {

      ::draw2d::path_pointer path(e_create);

      //path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->begin_figure();

      path->add_lines(lppoints, nCount);

      //path->end_figure(true);

      path->close_figure();

      return this->draw_path(path);

   }


   bool graphics::fill_polygon(const POINTD * lppoints,count nCount)
   {

      ::draw2d::path_pointer path(e_create);

      //path->begin_figure(true,::draw2d::fill_mode_winding);

      path->begin_figure();

      path->add_lines(lppoints,nCount);

      //path->end_figure(true);

      path->close_figure();

      return this->fill_path(path);

   }


   bool graphics::rectangle(const ::rectd & rect)
   {

      bool bOk1;

      bOk1 = fill_rect(rect);

      bool bOk2;

      bOk2 = draw_rect(rect);

      return bOk1 && bOk2;

   }


   bool graphics::draw_rect(const ::rectd & rectParam, ::draw2d::pen * ppen)
   {

      if (ppen == nullptr)
      {

         return false;

      }

      if (ppen->m_etype == ::draw2d::pen::type_null)
      {

         return true;

      }

      D2D1_RECT_F rect;

      __copy(rect, rectParam);

      ::draw2d_direct2d::pen * ppen2 = dynamic_cast <::draw2d_direct2d::pen *> (ppen);

      defer_primitive_blend();

      m_prendertarget->DrawRectangle(&rect, ppen2->get_os_data < ID2D1Brush * >(this), (FLOAT)m_ppen->m_dWidth);

      return true;

   }


   bool graphics::fill_rect(const ::rectd & rectParam, ::draw2d::brush * pbrush)
   {

      if (pbrush == nullptr)
      {

         return false;

      }

      if (pbrush->m_etype == ::draw2d::brush::type_null)
      {

         return true;

      }

      D2D1_RECT_F rect;

      __copy(rect, rectParam);

      ::draw2d_direct2d::brush * pbrush2 = dynamic_cast <::draw2d_direct2d::brush *> (pbrush);

      defer_primitive_blend();

      m_prendertarget->FillRectangle(rect, pbrush2->get_os_data < ID2D1Brush * >(this));

      return true;

   }


   bool graphics::round_rect(const ::rectd & rectParam, const ::pointd & point)
   {

      D2D1_ROUNDED_RECT rect;

      __copy(rect.rect, rectParam);

      __copy(rect.radiusX, point);

      if (m_pbrush.is_set() && m_pbrush->m_etype != ::draw2d::brush::type_null)
      {

         auto pbrush = m_pbrush.cast <::draw2d_direct2d::brush > ();

         defer_primitive_blend();

         m_prendertarget->FillRoundedRectangle(rect, pbrush->get_os_data < ID2D1Brush * > (this));

      }

      if (m_pbrush.is_set() && m_pbrush->m_etype != ::draw2d::brush::type_null)
      {

         auto ppen = m_ppen.cast <::draw2d_direct2d::pen >();
         
         defer_primitive_blend();

         m_prendertarget->DrawRoundedRectangle(rect, ppen->get_os_data < ID2D1Brush * > (this), (FLOAT) ppen->m_dWidth);

      }

      return true;

   }


   bool graphics::PatBlt(int x, int y, int nWidth, int nHeight, u32 dwRop)
   {

      __throw(todo());

   }


   bool graphics::BitBltRaw(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, u32 dwRop)
   {

      ::draw2d::lock draw2dlock;

      try
      {

         if (pgraphicsSrc == nullptr)
         {

            return false;

         }

         if (pgraphicsSrc->get_current_bitmap() == nullptr)
         {

            return false;

         }

         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
         {

            return false;

         }

         if (x < 0)
         {

            xSrc -= x;

            nWidth += x;

            x = 0;

         }

         if (y < 0)
         {

            ySrc -= y;

            nHeight += y;

            y = 0;

         }

         if (get_current_bitmap() && get_current_bitmap()->is_set())
         {

            D2D1_SIZE_U sz = get_current_bitmap()->get_os_data < ID2D1Bitmap * >()->GetPixelSize();

            if (natural(nWidth + x + GetViewportOrg().x) > sz.width)
            {

               nWidth = sz.width - x - GetViewportOrg().x;

            }

            if (natural(nHeight + y + GetViewportOrg().y) > sz.height)
            {

               nHeight = sz.height - y - GetViewportOrg().y;

            }

         }

         {

            D2D1_SIZE_U sz = ((ID2D1Bitmap *)pgraphicsSrc->get_current_bitmap()->get_os_data())->GetPixelSize();

            if (natural(nWidth + xSrc) > sz.width)
            {

               nWidth = sz.width - xSrc;

            }

            if (natural(nHeight + ySrc) > sz.height)
            {

               nHeight = sz.height - ySrc;

            }

         }

         D2D1_RECT_F rectDst = D2D1::RectF((float) x, (float) y, (float) (x + nWidth), (float) (y + nHeight));

         D2D1_RECT_F rectSrc = D2D1::RectF((float) xSrc, (float) ySrc, (float) (xSrc + nWidth), (float) (ySrc + nHeight));

         HRESULT hr = ((ID2D1DeviceContext *) pgraphicsSrc->get_os_data())->EndDraw();

         defer_primitive_blend();

         m_pdevicecontext->DrawBitmap((ID2D1Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), rectDst, 1.0, D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rectSrc);

         if(SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pgraphicsSrc->get_os_data())->BeginDraw();

         }

         return true;

      }
      catch(...)
      {
         
         return FALSE;

      }

   }


   bool graphics::StretchBltRaw(double xDst, double yDst, double nDstWidth, double nDstHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, u32 dwRop)
   {

      try
      {

         if (pgraphicsSrc == nullptr)
         {

            return false;

         }

         if (pgraphicsSrc->get_current_bitmap() == nullptr)
         {

            return false;

         }

         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
         {

            return false;

         }

         D2D1_RECT_F rectDst = D2D1::RectF((float) xDst, (float) yDst, (float) (xDst + nDstWidth), (float) (yDst + nDstHeight));

         D2D1_RECT_F rectSrc = D2D1::RectF((float) xSrc, (float) ySrc, (float) (xSrc + nSrcWidth), (float) (ySrc + nSrcHeight));

         HRESULT hr = ((ID2D1DeviceContext *) pgraphicsSrc->get_os_data())->EndDraw();

         defer_primitive_blend();

         if(m_prendertarget != nullptr)
         {

            m_prendertarget->DrawBitmap((ID2D1Bitmap *)pgraphicsSrc->get_current_bitmap()->get_os_data(), &rectDst, 1.0,m_bitmapinterpolationmode,& rectSrc);

         }
         else
         {

            m_pdevicecontext->DrawBitmap((ID2D1Bitmap *)pgraphicsSrc->get_current_bitmap()->get_os_data(), rectDst, 1.0,m_interpolationmode,rectSrc);

         }

         if(SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pgraphicsSrc->get_os_data())->BeginDraw();

         }
         else
         {

            output_debug_string("direct2d graphics::StretchBltRaw hr failed");

         }

         return true;

      }
      catch(...)
      {

      }

      return false;

   }


   ::color graphics::GetPixel(int x, int y)
   {

      __throw(todo());

   }


   ::color graphics::GetPixel(const ::point & point)
   {

      __throw(todo());

   }


   ::color graphics::SetPixel(int x, int y, const ::color & color)
   {

      __throw(todo());

   }


   ::color graphics::SetPixel(const ::point & point, const ::color & color)
   {

      __throw(todo());

   }


   bool graphics::FloodFill(int x, int y, const ::color & color)
   {

      __throw(todo());

   }


   bool graphics::ExtFloodFill(int x, int y, const ::color & color, UINT nFillType)
   {

      __throw(todo());

   }


   bool graphics::text_out(int x, int y, const string & str)
   {

      return text_out((double)x, (double)y, str);

   }


   bool graphics::text_out(double x, double y, const string & str)
   {

      return text_out((int) x, (int) y, str, (int) str.get_length());

   }


   bool graphics::ExtTextOut(int x, int y, UINT nOptions, const ::rect & rect, const char * lpszString, strsize nCount, LPINT lpDxWidths)
   {

      __throw(todo());

   }


   bool graphics::ExtTextOut(int x, int y, UINT nOptions, const ::rect & rect, const string & str, LPINT lpDxWidths)
   {

      __throw(todo());

   }


   size graphics::TabbedTextOut(int x, int y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      __throw(todo());

   }


   size graphics::TabbedTextOut(int x, int y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      __throw(todo());

   }


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(todo());

   }


   size graphics::GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(todo());

   }


   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(todo());

   }


   size graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(todo());

   }


   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, int nCount,int x, int y, int nWidth, int nHeight)
   {

      __throw(todo());

   }


   UINT graphics::GetTextAlign()
   {

      __throw(todo());

   }


   int graphics::GetTextFace(count nCount, LPTSTR lpszFacename)
   {

      __throw(todo());

   }


   int graphics::GetTextFace(string & rString)
   {

      __throw(todo());

   }


   bool graphics::get_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      if (m_pfont.is_null())
      {

         ((graphics*)this)->m_pfont.create();

      }

      if (m_pfont.is_null())
      {

         return false;

      }

      Microsoft::WRL::ComPtr<IDWriteFontCollection> pcollection;

      WCHAR name[256];
      UINT32 findex;
      BOOL exists;

      auto pwritetextformat = m_pfont->get_os_data < IDWriteTextFormat * >(this);

      if (::is_null(pwritetextformat))
      {

         lpMetrics->tmAscent = 0;
         lpMetrics->tmDescent = 0;
         lpMetrics->tmHeight = 0;

         return true;

      }

      pwritetextformat->GetFontFamilyName(name, 256);

      pwritetextformat->GetFontCollection(&pcollection);

      if (pcollection == nullptr)
      {

         lpMetrics->tmAscent = 0;
         lpMetrics->tmDescent = 0;
         lpMetrics->tmHeight = 0;

         return true;

      }

      pcollection->FindFamilyName(name, &findex, &exists);

      if (!exists)
      {

         lpMetrics->tmAscent = 0;
         lpMetrics->tmDescent = 0;
         lpMetrics->tmHeight = 0;

         return true;

      }

      Microsoft::WRL::ComPtr<IDWriteFontFamily> ffamily;

      pcollection->GetFontFamily(findex, &ffamily);

      if (ffamily == nullptr)
      {

         lpMetrics->tmAscent = 0;
         lpMetrics->tmDescent = 0;
         lpMetrics->tmHeight = 0;

         return true;

      }

      Microsoft::WRL::ComPtr<IDWriteFont> pfont;

      ffamily->GetFirstMatchingFont(pwritetextformat->GetFontWeight(), pwritetextformat->GetFontStretch(), pwritetextformat->GetFontStyle(), &pfont);

      if (pfont == nullptr)
      {

         lpMetrics->tmAscent = 0;
         lpMetrics->tmDescent = 0;
         lpMetrics->tmHeight = 0;

         return true;

      }

      DWRITE_FONT_METRICS metrics;

      pfont->GetMetrics(&metrics);

      double ratio = pwritetextformat->GetFontSize() / (float)metrics.designUnitsPerEm;

      lpMetrics->tmAscent = (LONG) (metrics.ascent * ratio);
      lpMetrics->tmDescent = (LONG) (metrics.descent * ratio);
      lpMetrics->tmInternalLeading = (LONG) 0;
      lpMetrics->tmExternalLeading = (LONG) (metrics.lineGap * ratio);
      lpMetrics->tmHeight = (LONG) ((metrics.ascent + metrics.descent + metrics.lineGap) * ratio);

      return true;

   }


   bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::GetTextMetrics(get_handle1(), lpMetrics) != FALSE;

   }


//   int graphics::GetTextCharacterExtra()
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetTextCharacterExtra(get_handle2());
//
//   }
//
//
//   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;
//
//   }
//
//   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;
//
//   }
//
//   u32 graphics::GetFontLanguageInfo()
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::GetFontLanguageInfo(get_handle1());
//
//   }
//
//#ifdef WINDOWS_DESKTOP
//
//   /*   u32 graphics::GetCharacterPlacement(const char * lpString, int nCount, int nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
//      {
//
//         __throw(todo());
//
//         //ASSERT(get_handle1() != nullptr);
//
//         //return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);
//
//      }
//
//      u32 graphics::GetCharacterPlacement(string & str, int nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
//      {
//
//         __throw(todo());
//
//         //ASSERT(get_handle1() != nullptr);
//
//         //return ::GetCharacterPlacement(get_handle1(), (const char *)str, (int) str.get_length(), nMaxExtent, lpResults, dwFlags);
//
//      }
//      */
//#endif
//
//   size graphics::GetAspectRatioFilter()
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//      //::size size;
//      //VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
//      //return size;
//
//   }
//
//   bool graphics::ScrollDC(int dx, int dy, const ::rect & rectScroll, const ::rect & rectClip, ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::ScrollDC(get_handle1(), dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != FALSE;
//
//   }
//
//   // Printer Escape Functions
//   int graphics::Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);
//
//   }

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const ::rect & rectBounds, UINT flags)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetBoundsRect(get_handle1(), rectBounds, flags);

   }


   UINT graphics::GetBoundsRect(LPRECT rectBounds, UINT flags)
   {

      __throw(todo());

      //ASSERT(get_handle2() != nullptr);

      //return ::GetBoundsRect(get_handle2(), rectBounds, flags);

   }

   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {

      __throw(todo());

      //ASSERT(get_handle2() != nullptr);

      //return ::ResetDC(get_handle2(), lpDevMode) != nullptr;

   }

#ifdef WINDOWS_DESKTOP

   /*   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm)
      {

         __throw(todo());

         //ASSERT(get_handle2() != nullptr);

         //return ::GetOutlineTextMetrics(get_handle2(), cbData, lpotm);

      }

      bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc)
      {

         __throw(todo());

         //ASSERT(get_handle2() != nullptr);

         //return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != FALSE;

      }
      */
#endif

//   u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);
//
//   }
//
//#ifdef WINDOWS_DESKTOP
//
//   /*
//   int graphics::GetKerningPairs(int nPairs, LPKERNINGPAIR lpkrnpair)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);
//
//   }
//
//   u32 graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,  u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetGlyphOutline(get_handle2(), nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);
//
//   }
//
//   // ::userbase::document handling functions
//   int graphics::StartDoc(LPDOCINFO lpDocInfo)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::StartDoc(get_handle1(), lpDocInfo);
//
//   }
//   */
//#endif

   int graphics::StartPage()
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::StartPage(get_handle1());

   }

   int graphics::EndPage()
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::EndPage(get_handle1());

   }


   int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   }


   int graphics::AbortDoc()
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::AbortDoc(get_handle1());

   }


   int graphics::EndDoc()
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::EndDoc(get_handle1());

   }


   bool graphics::MaskBlt(int x, int y, int nWidth, int nHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, ::draw2d::bitmap& maskBitmap, int xMask, int yMask, u32 dwRop)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != FALSE;

   }


   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nWidth, int nHeight, ::draw2d::bitmap& maskBitmap, int xMask, int yMask)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != FALSE;

   }


   bool graphics::SetPixelV(int x, int y, const ::color & color)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;

   }

   bool graphics::SetPixelV(const ::point & point, const ::color & color)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;

   }

   bool graphics::AngleArc(int x, int y, int nRadius, angle fStartAngle, angle fSweepAngle)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != FALSE;

   }


   bool graphics::ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ArcTo(rect.left, rect.top, rect.right, rect.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);

   }

   int graphics::GetArcDirection()
   {

      __throw(todo());

      //ASSERT(get_handle2() != nullptr);

      //return ::GetArcDirection(get_handle2());

   }

   bool graphics::PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::PolyPolyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != FALSE;

   }

#ifdef WINDOWS_DESKTOP
   /*
      bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust)
      {

         __throw(todo());

         //ASSERT(get_handle2() != nullptr);

         //return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;

      }
      */
#endif


   bool graphics::PolyBezier(const POINT* lpPoints, count nCount)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::PolyBezier(get_handle1(), lpPoints, nCount) != FALSE;

   }


//   int graphics::DrawEscape(int nEscape, int nInputSize, const char * lpszInputData)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);
//
//   }
//
//
//   int graphics::Escape(int nEscape, int nInputSize, const char * lpszInputData, int nOutputSize, char * lpszOutputData)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
//
//   }
//
//
//#ifdef WINDOWS_DESKTOP
//   /*
//      bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF)
//      {
//
//         __throw(todo());
//
//         //ASSERT(get_handle2() != nullptr);
//         //
//         //return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;
//
//      }
//      */
//#endif
//
//   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;
//
//   }


   bool graphics::abort_path()
   {

      __throw(todo());

      //if(m_ppath != nullptr)
      //{
      //   delete m_ppath;
      //   m_ppath = nullptr;
      //}
      //return true;


   }

   bool graphics::begin_path()
   {

      __throw(todo());

   }


   bool graphics::close_figure()
   {

      __throw(todo());

      //ASSERT(m_ppath != nullptr);
      //return m_ppath->CloseFigure() == Gdiplus::Status::Ok;

   }


   bool graphics::end_path()
   {

      __throw(todo());

      //if(m_ppath == nullptr)
      //   return FALSE;

      //m_ppathPaint   = m_ppath;
      //m_ppath        = nullptr;

      //return true;

   }

   bool graphics::fill_path()
   {

      __throw(todo());

      //return m_prendertarget->FillPath(direct2d_brush(), m_ppath) == Gdiplus::Status::Ok;

   }

   bool graphics::flatten_path()
   {

      __throw(todo());

      //return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }

   float graphics::GetMiterLimit()
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //float fMiterLimit;
      //VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      //return fMiterLimit;

   }


   i32 graphics::GetPath(LPPOINT lpPoints, byte * lpTypes, ::count nCount)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::GetPath(get_handle1(), lpPoints, lpTypes, nCount);

   }


   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != FALSE;

   }


   bool graphics::stroke_and_fill_path()
   {

      __throw(todo());

      //bool bOk1 = m_prendertarget->FillPath(direct2d_brush(), m_ppathPaint) == Gdiplus::Status::Ok;

      //bool bOk2 = m_prendertarget->DrawPath(direct2d_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

      //return bOk1 && bOk2;

   }


   bool graphics::stroke_path()
   {

      __throw(todo());

//      return m_prendertarget->DrawPath(direct2d_pen(), m_ppathPaint) == Gdiplus::Status::Ok;
   }


   bool graphics::widen_path()
   {

      __throw(todo());


//      return m_ppath->Widen(direct2d_pen()) == Gdiplus::Status::Ok;
   }


   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {

      __throw(todo());


      //ASSERT(get_handle1() != nullptr);
      //return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;
   }


   /*bool CALLBACK metaCallback(
   EmfPlusRecordType recordType,
   unsigned int flags,
   unsigned int dataSize,
   const unsigned char* pStr,
   void* callbackData)
   {
   // Play only EmfPlusRecordTypeFillEllipse records.
   if (recordType == EmfPlusRecordTypeFillEllipse)
   {
   // Explicitly cast callbackData as a metafile pointer, and use it to call
   // the PlayRecord method.
   static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
   }
   return TRUE;
   }

   VOID Example_EnumerateMetafile9(HDC hdc)
   {
   Graphics graphics(hdc);
   // Create a Metafile object from an existing disk metafile.
   Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
   {
   // Fill a rectangle and an ellipse in pMeta.
   Graphics metaGraphics(pMeta);
   metaGraphics.fill_rect(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
   metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
   }
   // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
   graphics.EnumerateMetafile(
   pMeta,
   Rect(0, 0, 300, 50),
   metaCallback,
   pMeta);
   // Draw pMeta as an pimage->
   graphics.DrawImage(pMeta, Point(0, 150));
   delete pMeta;;
   }*/
   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::rect & rectBounds)
   {

      __throw(todo());

      //Gdiplus::RectF rect((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

      //Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);

      ////m_pgraphcis->EnumerateMetafile(pMeta, rect, metaCallback, PMETAHEADER);

      //bool bOk = m_prendertarget->DrawImage(pMeta, rect) == Gdiplus::Status::Ok;

      //delete pMeta;

      //return bOk ? TRUE : FALSE;
      ////return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

   }

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   // Thank you
   // Jiju George T
   // Web Developer
   // India India
   // Member

   bool graphics::alpha_blendRaw(int xDst, int yDst, int nDstWidth, int nDstHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, double dRate)
   {

      ::draw2d::lock draw2dlock;

      /*      float fA = (float) dRate;

            Gdiplus::ColorMatrix matrix = {
               1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
               0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
               0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
               0.0f, 0.0f, 0.0f, fA  , 0.0f,
               0.0f, 0.0f, 0.0f, 0.0f, 1.0f
            };

            Gdiplus::ImageAttributes attributes;

            attributes.SetColorMatrix(&matrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

            Gdiplus::RectF dstRect((Gdiplus::REAL) xDest, (Gdiplus::REAL) yDest, (Gdiplus::REAL) nDestWidth, (Gdiplus::REAL) nDestHeight);

            m_prendertarget->DrawImage((Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), dstRect,
               (Gdiplus::REAL) xSrc, (Gdiplus::REAL) ySrc, (Gdiplus::REAL) nSrcWidth, (Gdiplus::REAL) nSrcHeight, Gdiplus::UnitPixel, &attributes);*/

      try
      {

         if(pgraphicsSrc == nullptr)
            return FALSE;

         if(pgraphicsSrc->get_current_bitmap() == nullptr)
            return FALSE;

         if(pgraphicsSrc->get_current_bitmap()->m_osdata[0] == nullptr)
            return FALSE;

         //D2D1_RECT_F rectDst = D2D1::RectF((float) xDst, (float) yDst, (float) (xDst + nDstWidth), (float) (yDst + nDstHeight));
         //D2D1_RECT_F rectSrc = D2D1::RectF((float) xSrc, (float) ySrc, (float) (xSrc + nSrcWidth), (float) (ySrc + nSrcHeight));
         /*
                  if (get_current_bitmap() != nullptr && get_current_bitmap()->get_os_data() != nullptr)
                  {

                     D2D1_SIZE_U sz = ((ID2D1Bitmap *)get_current_bitmap()->get_os_data())->GetPixelSize();

                     if (natural(nDstWidth + xDst) > sz.width)
                        nDstWidth = sz.width - xDst;

                     if (natural(nDstHeight + yDst) > sz.height)
                        nDstHeight = sz.height - yDst;

                  }

                  {

                     D2D1_SIZE_U sz = ((ID2D1Bitmap *)pgraphicsSrc->get_current_bitmap()->get_os_data())->GetPixelSize();

                     if (natural(nSrcWidth + xSrc) > sz.width)
                        nSrcWidth = sz.width - xSrc;

                     if (natural(nSrcHeight + ySrc) > sz.height)
                        nSrcHeight = sz.height - ySrc;

                  }*/

         D2D1_RECT_F rectDst = D2D1::RectF((float)xDst, (float)yDst, (float)(xDst + nDstWidth), (float)(yDst + nDstHeight));
         D2D1_RECT_F rectSrc = D2D1::RectF((float)xSrc, (float)ySrc, (float)(xSrc + nSrcWidth), (float)(ySrc + nSrcHeight));


         //dynamic_cast <::draw2d_direct2d::graphics *> (pgraphicsSrc)->SaveClip();

         HRESULT hr = ((ID2D1DeviceContext *) pgraphicsSrc->get_os_data())->EndDraw();

         defer_primitive_blend();

         if(m_pdevicecontext != nullptr)
         {

            m_pdevicecontext->DrawBitmap((ID2D1Bitmap*)pgraphicsSrc->get_current_bitmap()->get_os_data(), rectDst, (float)dRate, m_interpolationmode, rectSrc);

         }
         else
         {

            m_prendertarget->DrawBitmap((ID2D1Bitmap*)pgraphicsSrc->get_current_bitmap()->get_os_data(), rectDst, (float)dRate, m_bitmapinterpolationmode, rectSrc);

         }


         //auto pimage = (ID2D1Bitmap*)pgraphicsSrc->get_current_bitmap()->get_os_data();
         //auto ecomposite = m_ealphamode == ::draw2d::alpha_mode_blend ? D2D1_COMPOSITE_MODE_SOURCE_OVER : D2D1_COMPOSITE_MODE_SOURCE_IN;

         //m_pdevicecontext->DrawImage(pimage, pointDst, rectSrc, m_interpolationmode, ecomposite);


         //hr = m_prendertarget->Flush();
         //flush();

         if(SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pgraphicsSrc->get_os_data())->BeginDraw();

            //dynamic_cast <::draw2d_direct2d::graphics *> (pgraphicsSrc)->RestoreClip();

         }

         return true;

      }
      catch(...)
      {
         return FALSE;
      }



      return true;

   }


   /*bool graphics::alpha_blend(int xDest, int yDest, int nDestWidth, int nDestHeight,
   ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, BLENDFUNCTION blend)
   {

   __throw(not_implemented_exception());
   //if(get_handle1() == nullptr)
   // return false;


   if(m_pimageAlphaBlend->is_set())
   {


   ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


   ::image_pointer pimageWork = nullptr;
   ::image_pointer pimageWork2 = nullptr;
   //         ::image_pointer pimageWork3 = nullptr;
   ::image_pointer pimageWork4 = nullptr;


   ::point pointSrc(xSrc, ySrc);
   ::point pointDest(xDest, yDest);
   ::size size(nDestWidth, nDestHeight);



   ::image_pointer pimage;
   if(imageWork == nullptr)
   {
   pimage = create_image(get_object());
   imageWork = pimage;
   }
   if(imageWork == nullptr)
   return false;
   if(!imageWork = create_image(size))
   return false;
   if(!imageWork.from(::point(), pgraphicsSrc, pointSrc, size))
   return false;




   ::image_pointer pimage2;
   if(imageWork2 == nullptr)
   {
   pimage2 = create_image(get_object());
   imageWork2 = pimage2;
   }


   ::image_pointer pimage4;
   if(imageWork4 == nullptr)
   {
   image4 = create_image(get_object());
   imageWork4 = image4;
   }
   if(imageWork4 == nullptr)
   return false;
   if(!imageWork4 = create_image(size))
   return false;


   imageWork4.Fill(255, 0, 0, 0);

   imageWork4.from(point(max(0, m_pointAlphaBlend.x - xDest), max(0, m_pointAlphaBlend.y - yDest)),
   m_pimageAlphaBlend->get_graphics(), point(max(0, xDest - m_pointAlphaBlend.x), max(0, yDest - m_pointAlphaBlend.y)), size);

   imageWork.channel_multiply(::color::channel_alpha, imageWork4);


   keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


   return Application.m_visual.imaging().true_blend(this, pointDest, size, imageWork.get_graphics(), pointSrc);


   }

   return ::AlphaBlend(get_handle1(), xDest, yDest,
   nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
   nSrcHeight, blend) != FALSE;
   }*/


   bool graphics::TransparentBlt(int xDest, int yDest, int nDestWidth, int nDestHeight, ::draw2d::graphics * pgraphicsSrc, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, UINT crTransparent)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != FALSE;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, u32 dwMode)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //
      //return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != FALSE;

   }

   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //

   // Always Inline. Functions only in Win98/Win2K or later

   //inline COLORREF graphics::GetDCBrushColor()
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetDCBrushColor(get_handle1());

   //}
   //inline COLORREF graphics::SetDCBrushColor(const ::color & color)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::SetDCBrushColor(get_handle1(), crColor);

   //}

   //inline COLORREF graphics::GetDCPenColor()
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetDCPenColor(get_handle1());

   //}
   //inline COLORREF graphics::SetDCPenColor(const ::color & color)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::SetDCPenColor(get_handle1(), crColor);

   //}

#ifdef WINDOWS_DESKTOP
   /*
      inline bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc)
      {

         __throw(todo());

         //ASSERT(get_handle1() != nullptr);

         //return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != FALSE;

      }
      */
#endif

   //inline bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != FALSE;

   //}

   //inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int cgi, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize)
   //{

   //   __throw(todo());

   //   //ENSURE(lpSize != nullptr);
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, lpSize) != FALSE;

   //}


   //inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE lpSize)
   //{

   //   __throw(todo());

   //   //ENSURE(lpSize != nullptr);
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, lpSize) != FALSE;

   //}








#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE lpSize)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      int nMapMode;
      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained ::map mode, ::map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         DPtoLP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // ::map against logical inch for non-constrained mapping modes
         int cxPerInch, cyPerInch;
         if (this != nullptr)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);
         }
         else
         {
            //            cxPerInch = afxData.cxPixelsPerInch;
            //          cyPerInch = afxData.cyPixelsPerInch;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         lpSize->cx = MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
         lpSize->cy = MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
      }
#endif
   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      int nMapMode;
      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained ::map mode, ::map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         LPtoDP(lpSize);
         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // ::map against logical inch for non-constrained mapping modes
         int cxPerInch, cyPerInch;
         if (this != nullptr)
         {
            ASSERT_VALID(this);
            ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);
         }
         else
         {
            //            cxPerInch = afxData.cxPixelsPerInch;
            //          cyPerInch = afxData.cyPixelsPerInch;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         lpSize->cx = MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
         lpSize->cy = MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
      }
#endif
   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize)
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      LPtoDP(lpSize);
      DPtoHIMETRIC(lpSize);
   }

   void graphics::HIMETRICtoLP(LPSIZE lpSize)
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      HIMETRICtoDP(lpSize);
      DPtoLP(lpSize);
   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* graphics::GetHalftoneBrush(::layered * pobjectContext)
   {
      /*
      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
      if (gen_HalftoneBrush == nullptr)
      {
      WORD grayPattern[8];
      for (int i = 0; i < 8; i++)
      grayPattern[i] = (WORD)(0x5555 << (i & 1));
      HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
      if (grayBitmap != nullptr)
      {
      gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
      ::DeleteObject(grayBitmap);
      }
      }
      if (!gen_WingdixTerm)
      gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
      ::aura::UnlockGlobals(CRIT_HALFTONEBRUSH);
      */

      return nullptr;
   }


   //void graphics::DrawDragRect(const ::rect & rect, const ::size & size, const ::rect & rectLast, const ::size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   ::exception::throw_not_implemented();

   //   /*
   //   ASSERT(__is_valid_address(rect, sizeof(RECT), FALSE));
   //   ASSERT(lpRectLast == nullptr ||
   //   __is_valid_address(lpRectLast, sizeof(RECT), FALSE));

   //   // first, determine the update region and select it
   //   ::draw2d::region rgnNew;
   //   ::draw2d::region rgnOutside, rgnInside;
   //   rgnOutside.CreateRectRgnIndirect(rect);
   //   const ::rect & rect = *rect;
   //   rect.inflate(-size.cx, -size.cy);
   //   rect.intersect(rect, rect);
   //   rgnInside.CreateRectRgnIndirect(rect);
   //   rgnNew.CreateRectRgn(0, 0, 0, 0);
   //   rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

   //   ::draw2d::brush* pBrushOld = nullptr;
   //   if (pBrush == nullptr)
   //   {
   //   pBrush = graphics::GetHalftoneBrush(get_object());
   //   }

   //   ENSURE(pBrush);

   //   if (pBrushLast == nullptr)
   //   {
   //   pBrushLast = pBrush;
   //   }

   //   ::draw2d::region rgnLast, rgnUpdate;
   //   if (lpRectLast != nullptr)
   //   {
   //   // find difference between new region and old region
   //   rgnLast.CreateRectRgn(0, 0, 0, 0);
   //   rgnOutside.SetRectRgn(lpRectLast);
   //   rect = *lpRectLast;
   //   rect.inflate(-sizeLast.cx, -sizeLast.cy);
   //   rect.intersect(rect, lpRectLast);
   //   rgnInside.SetRectRgn(rect);
   //   rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

   //   // only diff them if brushes are the same
   //   if (pBrush->get_os_data() == pBrushLast->get_os_data())
   //   {
   //   rgnUpdate.CreateRectRgn(0, 0, 0, 0);
   //   rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
   //   }
   //   }
   //   if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != nullptr)
   //   {
   //   // brushes are different -- erase old region first
   //   SelectClipRgn(&rgnLast);
   //   GetClipBox(&rect);
   //   pBrushOld = SelectObject(pBrushLast);
   //   PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
   //   SelectObject(pBrushOld);
   //   pBrushOld = nullptr;
   //   }

   //   // draw into the update/new region
   //   SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
   //   GetClipBox(&rect);
   //   pBrushOld = SelectObject(pBrush);
   //   PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);

   //   // cleanup DC
   //   if (pBrushOld != nullptr)
   //   SelectObject(pBrushOld);
   //   SelectClipRgn(nullptr);

   //   */

   //}


   void graphics::fill_rect(const ::rect & rect, const ::color & color)
   {

      fill_rect(rectd(rect), color);

   }


   void graphics::draw_3drect(const ::rect & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, eborder eborder)
   {

      draw_3drect(rectd(rect), colorTopLeft, colorBottomRight, eborder);

   }


   void graphics::draw_3drect(const ::rectd & rect,  const ::color & colorTopLeft, const ::color & colorBottomRight, eborder eborder)
   {

      double x = rect.left;
      double y = rect.top;
      double cx = ::width(rect);
      double cy = ::height(rect);

      if (eborder & border_top)
      {

         fill_solid_rect_dim(x, y, cx - 1.0, 1.0, colorTopLeft);

      }

      if (eborder & border_left)
      {

         fill_solid_rect_dim(x, y, 1.0, cy - 1.0, colorTopLeft);

      }

      if (eborder & border_right)
      {

         fill_solid_rect_dim(x + cx, y, -1.0, cy, colorBottomRight);

      }

      if (eborder & border_bottom)
      {

         fill_solid_rect_dim(x, y + cy, cx, -1.0, colorBottomRight);

      }

   }


   bool graphics::DeleteDC()
   {

      return destroy();

      /* if(get_handle() == nullptr)
          return FALSE;

       return ::DeleteDC(Detach()) != FALSE;*/
   }


   int graphics::StartDoc(const char * lpszDocName)
   {

      __throw(todo());

      //DOCINFO di;
      //__memset(&di, 0, sizeof(DOCINFO));
      //di.cbSize = sizeof(DOCINFO);
      //di.lpszDocName = lpszDocName;
      //return StartDoc(&di);
   }


   int graphics::SaveDC()
   {

      m_prendertarget->GetTransform(&m_pstate->m_m);

      ::count iSaveDC = m_statea.get_size();

      m_statea.add(m_pstate);

      m_pstate = __new(state);

      //m_pstate->m_layerparameters = D2D1::LayerParameters();

      //m_prendertarget->PushLayer(m_pstate->m_layerparameters, nullptr);

      return (int) iSaveDC;

   }

   bool graphics::RestoreDC(int nSavedDC)
   {

      if (nSavedDC < 0)
      {

         return false;

      }

      if (nSavedDC >= m_statea.get_count())
      {

         return false;

      }

      m_statea.add(m_pstate);

      for (index iState = m_statea.get_upper_bound(); iState > nSavedDC; iState--)
      {

         auto state = m_statea[iState];

         for (index iItem = state->m_maRegion.get_upper_bound(); iItem >= 0; iItem--)
         {

            m_prendertarget->PopLayer();

         }

         state->m_maRegion.remove_all();

         state->m_sparegionClip.remove_all();

         m_statea.remove_at(iState);

      }

      m_prendertarget->SetTransform(&m_statea[nSavedDC]->m_m);

      m_pstate = m_statea[nSavedDC];

      m_statea.set_size(nSavedDC);

      return true;

   }


   int graphics::SetPolyFillMode(int nPolyFillMode)
   {

      __throw(todo());

   }


   int graphics::SetROP2(int nDrawMode)
   {

      __throw(todo());

      //int nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   nRetVal = ::SetROP2(get_handle1(), nDrawMode);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetROP2(get_handle2(), nDrawMode);
      //return nRetVal;
   }

   int graphics::SetStretchBltMode(int nStretchMode)
   {
      if(nStretchMode == 0)
      {
         m_bitmapinterpolationmode     = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
         m_interpolationmode           = D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR;;
      }
      else if(nStretchMode == HALFTONE)
      {
         m_bitmapinterpolationmode     = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
         m_interpolationmode           = D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC;
      }
      else
      {
         m_bitmapinterpolationmode     = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
         m_interpolationmode           = D2D1_INTERPOLATION_MODE_LINEAR;
      }
      return 1;
      /*int nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
      nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
      nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
      return nRetVal;*/
   }


   // COLORREF graphics::SetTextColor(const ::color & color)
//   {
   //  return set_color(crColor);
   //const ::color & colorRetVal = m_crColor;
   //m_crColor = crColor;
   /*      const ::color & colorRetVal = CLR_INVALID;
   if(get_handle1() != nullptr && get_handle1() != get_handle2())
   crRetVal = ::SetTextColor(get_handle1(), crColor);
   if(get_handle2() != nullptr)
   crRetVal = ::SetTextColor(get_handle2(), crColor);*/
   //return crRetVal;
   //}

   int graphics::SetGraphicsMode(int iMode)
   {

      __throw(todo());

      //int nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //{
      //   nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
      //}
      //if(get_handle2() != nullptr)
      //{
      //   nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
      //}
      //return nRetVal;
   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      __throw(todo());

      //bool nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //{
      //   nRetVal = ::SetWorldTransform(get_handle1(), pXform) != FALSE;
      //}
      //if(get_handle2() != nullptr)
      //{
      //   nRetVal = ::SetWorldTransform(get_handle2(), pXform) != FALSE;
      //}
      //return nRetVal;
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,u32 iMode)
   {

      __throw(todo());

      //bool nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //{
      //   nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != FALSE;
      //}
      //if(get_handle2() != nullptr)
      //{
      //   nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != FALSE;
      //}
      //return nRetVal;
   }


   int graphics::SetMapMode(int nMapMode)
   {

      return 0;

   }


   point graphics::SetViewportOrg(int x, int y)
   {

      return ::draw2d::graphics::SetViewportOrg(x, y);

   }


   point graphics::OffsetViewportOrg(int nWidth, int nHeight)
   {

      return ::draw2d::graphics::OffsetViewportOrg(nWidth, nHeight);

   }


   size graphics::SetViewportExt(int x, int y)
   {

      __throw(todo());

   }


   size graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
   {

      return ::draw2d::graphics::ScaleViewportExt(xNum, xDenom, yNum, yDenom);

   }


   point graphics::SetWindowOrg(int x, int y)
   {

      __throw(todo());

   }


   point graphics::OffsetWindowOrg(int nWidth, int nHeight)
   {

      __throw(todo());

   }


   size graphics::SetWindowExt(int x, int y)
   {

      __throw(todo());

   }


   size graphics::ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom)
   {

      __throw(todo());

   }


   int graphics::GetClipBox(RECT * prect)
   {
      return 0;
      //__throw(todo());

      //return ::GetClipBox(get_handle1(), rect);
   }

   
   ::estatus graphics::reset_clip()
   {

      ::draw2d::lock draw2dlock;

      for (index iState = m_statea.get_upper_bound(); iState >= 0; iState--)
      {

         auto state = m_statea[iState];

         for (index iItem = state->m_maRegion.get_upper_bound(); iItem >= 0; iItem--)
         {

            m_prendertarget->PopLayer();

         }

         state->m_maRegion.remove_all();

         state->m_sparegionClip.remove_all();

      }

      auto& state = m_pstate;

      for (index iItem = state->m_maRegion.get_upper_bound(); iItem >= 0; iItem--)
      {

         m_prendertarget->PopLayer();

      }

      state->m_maRegion.remove_all();

      state->m_sparegionClip.remove_all();

      return ::success;

   }


   ::estatus graphics::add_shapes(const shape_array& shapea)
   {

      for (int i = 0; i < shapea.get_count(); i++)
      {

         if (i + 1 < shapea.get_count())
         {

            if (shapea[i + 1]->eshape() == e_shape_intersect_clip)
            {

               switch (shapea[i]->eshape())
               {
               case e_shape_rect:
                  intersect_clip(shapea[i]->shape < ::rect>());
                  break;
               case e_shape_rectd:
                  intersect_clip(shapea[i]->shape < ::rectd>());
                  break;
               case e_shape_oval:
                  intersect_clip(shapea[i]->shape < ::oval>());
                  break;
               case e_shape_ovald:
                  intersect_clip(shapea[i]->shape < ::ovald>());
                  break;
               case e_shape_polygon:
                  intersect_clip(shapea[i]->shape < ::polygon>());
                  break;
               case e_shape_polygond:
                  intersect_clip(shapea[i]->shape < ::polygond>());
                  break;

               }

               i++;

            }

         }

      }

      return ::success;

   }


   ::estatus graphics::intersect_clip(const ::rect& rect)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_rect(rect);

         D2D1::Matrix3x2F m = {};

         m_prendertarget->GetTransform(&m);

         m_pstate->m_sparegionClip.add(pregion);

         m_pstate->m_maRegion.add(m);

         ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

         m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

      }

      return 0;

   }


   ::estatus graphics::intersect_clip(const ::rectd& rect)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_rect(rect);

         D2D1::Matrix3x2F m = {};

         m_prendertarget->GetTransform(&m);

         m_pstate->m_sparegionClip.add(pregion);

         m_pstate->m_maRegion.add(m);

         ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

         m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

      }

      return 0;


   }




   ::estatus graphics::intersect_clip(const ::oval& oval)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_oval(oval);

         D2D1::Matrix3x2F m = {};

         m_prendertarget->GetTransform(&m);

         m_pstate->m_sparegionClip.add(pregion);

         m_pstate->m_maRegion.add(m);

         ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

         m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

      }

      return 0;


   }


   ::estatus graphics::intersect_clip(const ::ovald& oval)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_oval(oval);

         D2D1::Matrix3x2F m = {};

         m_prendertarget->GetTransform(&m);

         m_pstate->m_sparegionClip.add(pregion);

         m_pstate->m_maRegion.add(m);

         ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

         m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

      }

      return 0;


   }


   ::estatus graphics::intersect_clip(const ::polygon& polygon)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_polygon(polygon.get_data(), polygon.get_count(), ::draw2d::fill_mode_winding);

         D2D1::Matrix3x2F m = {};

         m_prendertarget->GetTransform(&m);

         m_pstate->m_sparegionClip.add(pregion);

         m_pstate->m_maRegion.add(m);

         ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

         m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

      }

      return 0;


   }


   ::estatus graphics::intersect_clip(const ::polygond& polygon)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_polygon(polygon.get_data(), polygon.get_count(), ::draw2d::fill_mode_winding);

         D2D1::Matrix3x2F m = {};

         m_prendertarget->GetTransform(&m);

         m_pstate->m_sparegionClip.add(pregion);

         m_pstate->m_maRegion.add(m);

         ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

         m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

      }

      return 0;


   }


   //void graphics::

   //   }
   //   else
   //   {

   //      D2D1::Matrix3x2F m;

   //      m_prendertarget->GetTransform(&m);

   //      m_pstate->m_sparegionClip.add(pregion);

   //      m_pstate->m_maRegion.add(m);

   //      auto pgeometry = pregion->get_os_data < ID2D1Geometry * >(this);

   //      m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(),pgeometry),nullptr);

   //   }

   //   return 0;

   //   //__throw(todo());


   //   //if(pregion == nullptr)
   //   //{
   //   //   m_prendertarget->ResetClip();
   //   //}
   //   //else
   //   //{
   //   //   m_prendertarget->SetClip((Gdiplus::Region *) pregion->get_os_data());
   //   //}

   //   //return 0;

   //   ///*      int nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //nRetVal = ::SelectClipRgn(get_handle1(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
   //   //if(get_handle2() != nullptr)
   //   //nRetVal = ::SelectClipRgn(get_handle2(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
   //   //return nRetVal;*/
   //}

   //int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   //{

   //   ::draw2d::lock draw2dlock;

   //   {

   //      UINT uiMax = m_pdevicecontext->GetMaximumBitmapSize();

   //      ::draw2d::region_pointer regionBig(e_create);

   //      regionBig->create_rect_dim(-(int) uiMax/2, -(int)uiMax / 2, uiMax / 2, uiMax / 2);

   //      ::draw2d::region_pointer regionSmall(e_create);

   //      regionSmall->create_rect_dim(x1, y1, x2, y2);

   //      ::draw2d::region_pointer regionExclude(e_create);

   //      regionExclude->combine(regionBig, regionSmall, ::draw2d::e_combine_exclude);

   //      D2D1::Matrix3x2F m;

   //      m_prendertarget->GetTransform(&m);

   //      m_pstate->m_sparegionClip.add(regionExclude);

   //      m_pstate->m_maRegion.add(m);

   //      auto pgeometry = regionExclude->get_os_data < ID2D1Geometry * >(this);

   //      m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

   //   }

   //   return 0;

   //}

   //int graphics::ExcludeClipRect(const ::rect & rect)
   //{

   //   return ExcludeClipRect(rect.left, rect.top, rect.right, rect.bottom);

   //}



   //int graphics::OffsetClipRgn(int x, int y)
   //{

   //   __throw(todo());

   //}


   //int graphics::OffsetClipRgn(const ::size & size)
   //{

   //   __throw(todo());

   //}


   UINT graphics::SetTextAlign(UINT nFlags)
   {

      __throw(todo());

   }


   //int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   //{

   //   __throw(todo());

   //}


   //int graphics::SetTextCharacterExtra(int nCharExtra)
   //{

   //   __throw(todo());

   //}


   //u32 graphics::SetMapperFlags(u32 dwFlag)
   //{

   //   __throw(todo());

   //}


   typedef u32 (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   typedef u32 (CALLBACK* __GDISETLAYOUTPROC)(HDC, u32);


   void graphics::apply_primitive_blend()
   {

      if (m_ealphamodeDevice != m_ealphamode)
      {

         m_ealphamodeDevice = m_ealphamode;

         if (m_ealphamodeDevice == ::draw2d::alpha_mode_blend)
         {

            m_pdevicecontext->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_SOURCE_OVER);

         }
         else if (m_ealphamodeDevice == ::draw2d::alpha_mode_set)
         {

            m_pdevicecontext->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_COPY);

         }

      }

   }


   void graphics::apply_text_rendering_hint()
   {

      try
      {

         if (m_prendertarget == nullptr)
         {

            return;

         }

         m_etextrenderinghintDevice = m_etextrenderinghint;

         switch (m_etextrenderinghintDevice)
         {
         case ::draw2d::text_rendering_hint_anti_alias:

            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

            break;

         case ::draw2d::text_rendering_hint_anti_alias_grid_fit:
            
            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

            break;

         case ::draw2d::text_rendering_hint_single_bit_per_pixel:
            
            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

            break;

         case ::draw2d::text_rendering_hint_clear_type_grid_fit:

            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

            break;

         }

      }
      catch (...)
      {

      }

   }


   void graphics::defer_text_primitive_blend()
   {

      if (m_ealphamodeDevice != ::draw2d::alpha_mode_blend)
      {

         m_ealphamodeDevice = m_ealphamode;

         m_pdevicecontext->SetPrimitiveBlend(D2D1_PRIMITIVE_BLEND_SOURCE_OVER);

      }

   }


   oswindow graphics::get_window_handle()
   {

      if (::is_null(m_puserinteraction))
      {

         return nullptr;

      }

      return m_puserinteraction->get_handle();

   }


   u32 graphics::GetLayout()
   {

      __throw(todo());

   }


   u32 graphics::SetLayout(u32 dwSetLayout)
   {

      __throw(todo());

   }


   bool graphics::ArcTo(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {

      __throw(todo());

   }


   int graphics::SetArcDirection(int nArcDirection)
   {

      __throw(todo());

   }


   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, count nCount)
   {

      __throw(todo());

   }


   bool graphics::PolylineTo(const POINT* lpPoints, count nCount)
   {

      __throw(todo());

   }


   bool graphics::PolyBezierTo(const POINT* lpPoints, count nCount)
   {

      __throw(todo());

   }


   bool graphics::SelectClipPath(int nMode)
   {

      __throw(todo());

   }


   //int graphics::SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine)
   //{

   //   return 0;

   //}

   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback
#ifdef WINDOWS_DESKTOP
   int CALLBACK __enum_meta_file_procedure(HDC hDC,
                                           HANDLETABLE* pHandleTable, METARECORD* pMetaRec, int nHandles, LPARAM lParam)
   {
      
      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;

      ASSERT_VALID(pgraphics);

      switch (pMetaRec->rdFunction)
      {
      // these records have effects different for each graphics derived class
      case META_SETMAPMODE:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SetMapMode((int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWEXT:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SetWindowExt(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETWINDOWORG:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SetWindowOrg(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTEXT:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SetViewportExt(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETVIEWPORTORG:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SetViewportOrg(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SCALEWINDOWEXT:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->ScaleWindowExt(
         (int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SCALEVIEWPORTEXT:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->ScaleViewportExt(
         (int)(short)pMetaRec->rdParm[3], (int)(short)pMetaRec->rdParm[2],
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_OFFSETVIEWPORTORG:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->OffsetViewportOrg(
         (int)(short)pMetaRec->rdParm[1], (int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SAVEDC:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SaveDC();
         break;
      case META_RESTOREDC:
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->RestoreDC((int)(short)pMetaRec->rdParm[0]);
         break;
      case META_SETBKCOLOR:
      {
         
         ::draw2d::brush_pointer brush(e_create);
         
         brush->create_solid(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
         
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->set(brush);

      }
      break;
      case META_SETTEXTCOLOR:
      {
         ::draw2d::brush_pointer brush(e_create);
         brush->create_solid(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->set(brush);
      }
      break;

      // need to watch out for SelectObject(HFONT), for custom font mapping
      case META_SELECTOBJECT:
      {
         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
         UINT nObjType = GetObjectType(hObject);
         if (nObjType == 0)
         {
            // object type is unknown, determine if it is a font
            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
            HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1(), hStockFont);
            HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1(), hObject);
            if (hObjOld == hStockFont)
            {
               // got the stock object back, so must be selecting a font
               __throw(not_implemented());
               //                  (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SelectObject(::draw2d_direct2d::font::from_handle_dup(pgraphics->get_context_application(), (HFONT)hObject));
               break;  // don't play the default record
            }
            else
            {
               // didn't get the stock object back, so restore everything
               ::SelectObject((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1(), hFontOld);
               ::SelectObject((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1(), hObjOld);
            }
            // and fall through to PlayMetaFileRecord...
         }
         else if (nObjType == OBJ_FONT)
         {
            // play back as graphics::SelectObject(::draw2d::font*)
            //               (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SelectObject(::draw2d_direct2d::font::from_handle_dup(pgraphics->get_context_application(), (HFONT)hObject));
            __throw(not_implemented());
            break;  // don't play the default record
         }
      }
      // fall through...

      default:
         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
         break;
      }

      return 1;
   }
#endif


   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {

      __throw(todo());

   }


   void graphics::LPtoDP(LPSIZE lpSize)
   {

      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      size sizeWinExt = GetWindowExt();
      size sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));

   }


   void graphics::DPtoLP(LPSIZE lpSize)
   {
   
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      size sizeWinExt = GetWindowExt();
      size sizeVpExt = GetViewportExt();
      lpSize->cx = MulDiv(lpSize->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
      lpSize->cy = MulDiv(lpSize->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));

   }


   bool graphics::draw_text(const char * lpszString, strsize nCount, const ::rect & rect, UINT nFormat)
   {

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      return draw_text(string(lpszString, nCount), rect, nFormat);

   }


   bool graphics::draw_text(const string & str,const ::rect & rect,UINT nFormat)
   {

      if (str.is_empty())
      {

         return true;

      }

      if (str.is_empty())
      {

         return false;

      }

      if (m_pfont.is_null())
      {

         return false;

      }

      if (m_pbrush.is_null())
      {

         return false;

      }

      ID2D1Brush* pbrush = m_pbrush->get_os_data < ID2D1Brush * >(this);

      if (::is_null(pbrush))
      {

         return false;

      }

      IDWriteTextFormat* pfont = m_pfont->get_os_data < IDWriteTextFormat * >(this);

      if (::is_null(pfont))
      {

         return false;

      }

      if (nFormat & DT_RIGHT)
      {

         pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

      }
      else if (nFormat & DT_CENTER)
      {

         pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

      }
      else
      {

         pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

      }

      if (nFormat & DT_BOTTOM)
      {

         pfont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

      }
      else if (nFormat & DT_VCENTER)
      {

         pfont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

      }
      else
      {

         pfont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

      }

      auto& text = m_pfont->m_mapText[str];

      if (text.m_wstr.is_empty())
      {

         text.m_wstr = str;

      }

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      if (m_pfont->m_dFontWidth == 1.0)
      {

         D2D1_RECT_F rectf = D2D1::RectF((FLOAT)rect.left, (FLOAT)rect.top, (FLOAT)rect.right, (FLOAT)rect.bottom);

         m_prendertarget->DrawText(text.m_wstr, (UINT32)text.m_wstr.get_length(), pfont, &rectf, pbrush);

      }
      else
      {
         D2D1::Matrix3x2F m;

         m_prendertarget->GetTransform(&m);

         D2D1::Matrix3x2F mOriginal(m);

         D2D1_RECT_F rectf = D2D1::RectF((FLOAT)0, (FLOAT)0, (FLOAT)width(rect), (FLOAT)height(rect));

         m = m * D2D1::Matrix3x2F::Translation((FLOAT)rect.left, (FLOAT)rect.top);

         m = m * D2D1::Matrix3x2F::Scale((FLOAT)m_pfont->m_dFontWidth, 1.f);

         m_prendertarget->SetTransform(&m);

         m_prendertarget->DrawText(text.m_wstr, (UINT32)text.m_wstr.get_length(), pfont, &rectf, pbrush);

         m_prendertarget->SetTransform(&mOriginal);

      }

      return 1;

   }


   sized graphics::GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex)
   {

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      sized sz;

      bool bOk = GetTextExtent(sz, lpszString, nCount, iIndex);

      if (!bOk)
      {

         return ::size(0, 0);

      }
      else
      {

         return ::size((i32) sz.cx, (i32) sz.cy);

      }

   }


   sized graphics::GetTextExtent(const string & str)
   {
      sized s;

      if (!GetTextExtent(s, str))
      {

         return ::sized(0, 0);

      }

      return s;

   }


   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
   {

      __throw(todo());

   }


   size graphics::GetOutputTextExtent(const string & str)
   {

      __throw(todo());

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex)
   {

      if (iIndex <= 0)
      {

         size.cx = 0;

         size.cy = 0;

         return true;

      }

      string str;

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      if (iIndex < 0)
      {

         iIndex = nCount;

      }

      if (iIndex > nCount && nCount >= 0)
      {

         iIndex = nCount;

      }

      str = string(lpszString, iIndex);

      if (m_pfont.is_null())
      {

         return false;

      }

      auto pfont = m_pfont->get_os_data < IDWriteTextFormat * >(this);

      if (pfont == nullptr)
      {

         return false;

      }

      auto& text = m_pfont->m_mapText[str];

      if (text.m_bSize)
      {

         size = text.m_size;

         return true;

      }


      if (text.m_wstr.is_empty())
      {

         text.m_wstr = str;

      }

      Microsoft::WRL::ComPtr<IDWriteTextLayout> playout1;

      HRESULT hr;

      Microsoft::WRL::ComPtr<IDWriteTextLayout> playout;

      UINT32 uLength = (UINT32)text.m_wstr.get_length();

      hr = global_draw_get_write_factory()->CreateTextLayout(
           text.m_wstr,                // The string to be laid out and formatted.
           uLength,   // The length of the string.
           pfont,    // The text format to apply to the string (contains font information, etc).
           1024.f * 1024.f,               // The width of the on_layout box.
           1024.f * 1024.f,        // The height of the on_layout box.
           &playout  // The IDWriteTextLayout interface pointer.
           );

      if(playout == nullptr || FAILED(hr))
      {

         size.cx = 0;

         size.cy = 0;

         return false;

      }

      DWRITE_TEXT_METRICS m;

      playout->GetMetrics(&m);

      size.cx = (LONG) (m.width  * m_pfont->m_dFontWidth);

      size.cy = (LONG) m.height;

      text.m_size = size;

      text.m_bSize = true;

      return true;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount)
   {

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      return GetTextExtent(size, lpszString, nCount, nCount);

   }


   bool graphics::GetTextExtent(sized & size, const string & str)
   {

      return GetTextExtent(size, str, str.get_length());

   }


   void graphics::fill_rect(const ::rectd & rectParam, const ::color & color)
   {

      if (!m_pdevicecontext)
      {

         return;

      }

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(color);

      auto pbrush = br->get_os_data < ID2D1Brush * >(this);

      D2D1_RECT_F rect;

      __copy(rect, rectParam);

      defer_primitive_blend();

      m_pdevicecontext->FillRectangle(&rect, pbrush);

   }


   bool graphics::text_out(int x, int y, const char * lpszString, strsize nCount)
   {

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      return ::draw2d::graphics::text_out((double)x, (double)y, string(lpszString, nCount));

   }


   bool graphics::TextOutRaw(double x, double y, const string & str)
   {

      if (str.is_empty())
      {

         return false;

      }

      if (m_pfont.is_null())
      {

         return false;

      }

      IDWriteTextFormat* pfont = m_pfont->get_os_data < IDWriteTextFormat * >(this);

      if (pfont == nullptr)
      {

         return false;

      }

      if (m_pbrush.is_null())
      {

         return false;

      }

      ID2D1Brush* pbrush = m_pbrush->get_os_data < ID2D1Brush * >(this);

      if (::is_null(pbrush))
      {

         return false;

      }

      D2D1::Matrix3x2F m;

      D2D1::Matrix3x2F mOriginal;

      auto & text = m_pfont->m_mapText[str];

      size sizeText;
         
      if (text.m_bSize)
      {

         sizeText = text.m_size;

      }
      else
      {

         sizeText = GetTextExtent(str);

      }

      D2D1_RECT_F rectf = D2D1::RectF((FLOAT) 0, (FLOAT)0, (FLOAT)(0 + sizeText.cx * 2), (FLOAT)(0 + sizeText.cy * 2));

      HRESULT  hr = pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

      if(FAILED(hr))
      {

         trace_hr("text_out, SetTextAlignment",hr);

      }

      hr = pfont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

      if(FAILED(hr))
      {

         trace_hr("text_out, SetTextAlignment",hr);

      }

      DWRITE_TRIMMING trim;

      xxf_zero(trim);

      trim.granularity = DWRITE_TRIMMING_GRANULARITY_NONE;

      hr = pfont->SetTrimming(&trim, nullptr);

      if (FAILED(hr))
      {

         trace_hr("text_out, SetTextAlignment", hr);

      }

      hr = pfont->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

      if (m_pfont->m_dFontWidth != 1.0)
      {

         m_prendertarget->GetTransform(&mOriginal);

         m = mOriginal;

         m._11 *= (FLOAT)m_pfont->m_dFontWidth;
         m._31 += (FLOAT)x;
         m._32 += (FLOAT)y;

      }
      else
      {

         rectf.left += (FLOAT)x;
         rectf.top += (FLOAT)y;
         rectf.right += (FLOAT)x;
         rectf.bottom += (FLOAT)y;

      }

      if (m_pfont->m_dFontWidth != 1.0)
      {

         m_prendertarget->SetTransform(&m);

      }

      LPCWSTR lpcwsz = text.m_wstr;

      strsize uiLen = text.m_wstr.get_length();

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      if(lpcwsz != nullptr && uiLen > 0)
      {

         m_prendertarget->DrawText(lpcwsz,(int) uiLen,pfont,&rectf,pbrush);

      }

      if (m_pfont->m_dFontWidth != 1.0)
      {

         m_prendertarget->SetTransform(mOriginal);

      }

      return true;

   }


   bool graphics::draw_line(const ::pointd & point1, const ::pointd & point2, ::draw2d::pen * ppen)
   {

      D2D1_POINT_2F p1;

      __copy(p1, point1);

      D2D1_POINT_2F p2;

      __copy(p2, point2);

      ID2D1Brush * pbrush = m_ppen->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      defer_primitive_blend();

      m_prendertarget->DrawLine(p1, p2, pbrush, (FLOAT)(dynamic_cast < ::draw2d_direct2d::pen * > (m_ppen.m_p))->m_dWidth);

      m_point = point2;

      return true;

   }


   bool graphics::line_to(const ::pointd & point)
   {

      D2D1_POINT_2F p1;

      __copy(p1, m_point);

      D2D1_POINT_2F p2;

      __copy(p2, point);

      ID2D1Brush * pbrush =  m_ppen->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      defer_primitive_blend();

      m_prendertarget->DrawLine(p1, p2, pbrush, (FLOAT) (dynamic_cast < ::draw2d_direct2d::pen * > (m_ppen.m_p))->m_dWidth);

      m_point = point;

      return true;

   }


   bool graphics::set_alpha_mode(::draw2d::e_alpha_mode ealphamode)
   {

      if (m_ealphamode != ealphamode)
      {

        ::draw2d::graphics::set_alpha_mode(ealphamode);

      }

      return true;

   }


   HDC graphics::get_handle() const
   {

      __throw(todo());

   }


   HDC graphics::get_handle1() const
   {

      return get_handle();

   }


   HDC graphics::get_handle2() const
   {

      return get_handle();

   }


   bool graphics::attach(void * pdata)
   {

      if(m_pdevicecontext != nullptr)
      {

         m_pdevicecontext = nullptr;

      }

      if(m_prendertarget != nullptr)
      {

         m_prendertarget = nullptr;

      }

      if(m_pbitmaprendertarget != nullptr)
      {

         m_pbitmaprendertarget = nullptr;

      }

      m_pdevicecontext = (ID2D1DeviceContext *) pdata;

      HRESULT hr = m_pdevicecontext.As(&m_prendertarget);

      if(FAILED(hr))
      {

         m_pdevicecontext = nullptr;

         m_prendertarget = nullptr;

         return false;

      }

      hr = m_prendertarget.As(&m_pbitmaprendertarget);

      if(FAILED(hr))
      {
         m_pbitmaprendertarget = nullptr;
      }

      m_osdata[data_device_context] = m_pdevicecontext.Get();

      m_osdata[data_render_target] = m_prendertarget.Get();

      return true;

   }


   void * graphics::detach()
   {

      m_prendertarget = nullptr;

      m_pbitmaprendertarget = nullptr;

      m_osdata[data_device_context] = nullptr;

      m_osdata[data_render_target] = nullptr;

      return m_pdevicecontext.Detach();

   }


#ifdef WINDOWS_DESKTOP


   bool graphics::attach_hdc(HDC hdc)
   {

      HWND hwnd = ::WindowFromDC(hdc);

      if (hwnd == nullptr)
      {

         return false;

      }

      ::rect rectClient;

      ::GetClientRect(hwnd, rectClient);

      // Create a DC render target.
      D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                                            D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                            D2D1::PixelFormat(
                                            DXGI_FORMAT_B8G8R8A8_UNORM,
                                            D2D1_ALPHA_MODE_IGNORE),
                                            0,
                                            0,
                                            D2D1_RENDER_TARGET_USAGE_NONE,
                                            D2D1_FEATURE_LEVEL_DEFAULT
                                            );

      HRESULT hr = get_d2d1_factory1()->CreateDCRenderTarget(&props,&m_pdcrendertarget);

      if (FAILED(hr))
      {

         return false;

      }

      hr = m_pdcrendertarget->BindDC(hdc, rectClient);

      m_pdcrendertarget.As(&m_prendertarget);

      m_hdcAttach = hdc;

      return true;

   }


   HDC graphics::detach_hdc()
   {

      if (m_hdcAttach == nullptr)
      {

         return nullptr;

      }

      HDC hdc = m_hdcAttach;

      m_hdcAttach = nullptr;

      return hdc;
   }

#endif


   bool graphics::blur(bool bExpand, double dRadius, const ::rect & rect)
   {

      __throw(todo());

   }


   double graphics::get_dpix()
   {
      
      return 72.0;

   }


   bool graphics::destroy()
   {

      ::draw2d::lock draw2dlock;

      if(m_player != nullptr)
      {

         m_prendertarget->PopLayer();

         m_player = nullptr;

      }

      m_ppathgeometryClip = nullptr;

      m_prendertarget = nullptr;

      m_pdevicecontext = nullptr;

      m_pbitmaprendertarget = nullptr;

      clear_os_data();

      return true;

   }


   ::estatus graphics::clear_current_point()
   {

      return ::success;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      return draw_path(ppath, m_ppen);

   }



   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      ::ID2D1Brush * pbrush = ppen->get_os_data < ID2D1Brush * > (this);

      if (pbrush == nullptr)
      {

         return false;

      }

      ID2D1PathGeometry * pgeometry = ppath->get_os_data < ID2D1PathGeometry * >(this);

      defer_primitive_blend();

      if(pgeometry != nullptr)
      {

         m_prendertarget->DrawGeometry(pgeometry,pbrush,(FLOAT)ppen->m_dWidth);

      }

      for(index i = 0; i < ppath->m_elementa.get_size(); i++)
      {

         if(ppath->m_elementa[i]->m_etype == ::draw2d::path::type_text_out)
         {

            draw(ppath->m_elementa[i].cast < ::draw2d::path::text_out>(), ppen);

         }
         else if (ppath->m_elementa[i]->m_etype == ::draw2d::path::type_draw_text)
         {

            draw(ppath->m_elementa[i].cast < ::draw2d::path::draw_text>(), ppen);

         }

      }

      return true;

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      if (ppath == nullptr)
      {

         return false;

      }

      ID2D1Brush * pbrush = m_pbrush->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      __stack(m_bOutline, false);

      ppath->set_modified();

      ID2D1PathGeometry * pgeometry = ppath->get_os_data < ID2D1PathGeometry * >(this);

      defer_primitive_blend();

      if (pgeometry != nullptr)
      {

         m_prendertarget->FillGeometry(pgeometry, pbrush);

      }

      for (index i = 0; i < ppath->m_elementa.get_size(); i++)
      {

         if (ppath->m_elementa[i]->m_etype == ::draw2d::path::type_text_out)
         {

            fill(ppath->m_elementa[i].cast < ::draw2d::path::text_out >(), m_pbrush);

         }
         else if (ppath->m_elementa[i]->m_etype == ::draw2d::path::type_draw_text)
         {

            fill(ppath->m_elementa[i].cast < ::draw2d::path::draw_text >(), m_pbrush);

         }

      }

      return true;

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrushParam)
   {

      if (ppath == nullptr)
      {

         return false;

      }

      ID2D1Brush * pbrush = pbrushParam->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      __stack(m_bOutline, false);

      ppath->set_modified();

      ID2D1PathGeometry * pgeometry = ppath->get_os_data < ID2D1PathGeometry * >(this);

      defer_primitive_blend();

      if (pgeometry != nullptr)
      {

         m_prendertarget->FillGeometry(pgeometry, pbrush);

      }

      for (index i = 0; i < ppath->m_elementa.get_size(); i++)
      {

         if (ppath->m_elementa[i]->m_etype == ::draw2d::path::type_text_out)
         {

            fill(ppath->m_elementa[i].cast < ::draw2d::path::text_out >(), pbrushParam);

         }
         else if (ppath->m_elementa[i]->m_etype == ::draw2d::path::type_draw_text)
         {

            fill(ppath->m_elementa[i].cast < ::draw2d::path::draw_text >(), pbrushParam);

         }

      }

      return true;

   }


   bool graphics::path(::draw2d::path * ppath)
   {

      if (ppath == nullptr)
      {

         return false;

      }

      bool bOk1 = fill_path(ppath);

      bool bOk2 = draw_path(ppath);

      return bOk1 && bOk2;

   }


   bool graphics::draw(::draw2d::path::text_out * ptextout, ::draw2d::pen * ppen)
   {

      wstring szOutline(ptextout->m_strText);

      IDWriteTextFormat * pformat = ptextout->m_pfont->get_os_data < IDWriteTextFormat * > (this);

      IDWriteFactory * pfactory = global_draw_get_write_factory();

      IDWriteTextLayout * playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
                   szOutline,      // The string to be laid out and formatted.
                   (UINT32) szOutline.length(),  // The length of the string.
                   pformat,  // The text format to apply to the string (contains font information, etc).
                   4096,         // The width of the on_layout box.
                   4096,        // The height of the on_layout box.
                   &playout  // The IDWriteTextLayout interface pointer.
                   );

      if(playout == nullptr)
      {

         return false;

      }

      CustomTextRenderer renderer(get_d2d1_factory1(),m_prendertarget.Get(),ppen->get_os_data < ID2D1Brush * >(this));

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      playout->Draw(nullptr, &renderer, (FLOAT) ptextout->m_point.x, (FLOAT) ptextout->m_point.y);

      return true;

   }


   bool graphics::fill(::draw2d::path::text_out * ptextout, ::draw2d::brush * pbrush)
   {

      wstring szOutline(ptextout->m_strText);

      IDWriteTextFormat * pformat = ptextout->m_pfont->get_os_data < IDWriteTextFormat * >(this);

      IDWriteFactory * pfactory = global_draw_get_write_factory();

      IDWriteTextLayout * playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
                   szOutline,      // The string to be laid out and formatted.
                   (UINT32) szOutline.length(),  // The length of the string.
                   pformat,  // The text format to apply to the string (contains font information, etc).
                   4096,         // The width of the on_layout box.
                   4096,        // The height of the on_layout box.
                   &playout  // The IDWriteTextLayout interface pointer.
                   );

      if (playout == nullptr)
      {
         
         return false;

      }

      auto posbrush = pbrush->get_os_data < ID2D1Brush * >(this);

      if (posbrush)
      {

         CustomTextRenderer renderer(get_d2d1_factory1(), m_prendertarget.Get(), nullptr, posbrush);

         defer_text_primitive_blend();

         defer_text_rendering_hint();

         playout->Draw(nullptr, &renderer, (FLOAT)ptextout->m_point.x, (FLOAT)ptextout->m_point.y);

      }

      return true;

   }


   bool graphics::draw(::draw2d::path::draw_text* pdrawtext, ::draw2d::pen* ppen)
   {

      wstring szOutline(pdrawtext->m_strText);

      IDWriteTextFormat* pformat = pdrawtext->m_pfont->get_os_data < IDWriteTextFormat* >(this);

      IDWriteFactory* pfactory = global_draw_get_write_factory();

      IDWriteTextLayout* playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
         szOutline,      // The string to be laid out and formatted.
         (UINT32)szOutline.length(),  // The length of the string.
         pformat,  // The text format to apply to the string (contains font information, etc).
         4096,         // The width of the on_layout box.
         4096,        // The height of the on_layout box.
         &playout  // The IDWriteTextLayout interface pointer.
      );

      if (playout == nullptr)
      {

         return false;

      }

      CustomTextRenderer renderer(get_d2d1_factory1(), m_prendertarget.Get(), ppen->get_os_data < ID2D1Brush* >(this));

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      playout->Draw(nullptr, &renderer, (FLOAT)pdrawtext->m_rect.left, (FLOAT)pdrawtext->m_rect.top);

      return true;

   }


   bool graphics::fill(::draw2d::path::draw_text * pdrawtext, ::draw2d::brush* pbrush)
   {

      wstring szOutline(pdrawtext->m_strText);

      IDWriteTextFormat* pformat = pdrawtext->m_pfont->get_os_data < IDWriteTextFormat* >(this);

      IDWriteFactory* pfactory = global_draw_get_write_factory();

      IDWriteTextLayout* playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
         szOutline,      // The string to be laid out and formatted.
         (UINT32)szOutline.length(),  // The length of the string.
         pformat,  // The text format to apply to the string (contains font information, etc).
         4096,         // The width of the on_layout box.
         4096,        // The height of the on_layout box.
         &playout  // The IDWriteTextLayout interface pointer.
      );

      if (playout == nullptr)
      {

         return false;

      }

      auto posbrush = pbrush->get_os_data < ID2D1Brush* >(this);

      if (posbrush)
      {

         CustomTextRenderer renderer(get_d2d1_factory1(), m_prendertarget.Get(), nullptr, posbrush);

         defer_text_primitive_blend();

         defer_text_rendering_hint();

         playout->Draw(nullptr, &renderer, (FLOAT)pdrawtext->m_rect.left, (FLOAT)pdrawtext->m_rect.top);

      }

      return true;

   }


   bool graphics::flush()
   {

      HRESULT hr = m_prendertarget->Flush();

      return SUCCEEDED(hr);

   }


   void graphics::debug()
   {

#ifdef WINDOWS_DESKTOP
      directx_debug();
#endif

   }


   void graphics::enum_fonts(::draw2d::font_enum_item_array & itema)
   {

      ::comptr<IDWriteFontCollection> pFontCollection;

      HRESULT hr = global_draw_get_write_factory()->GetSystemFontCollection(&pFontCollection);

      UINT32 familyCount = 0;

      if(SUCCEEDED(hr))
      {

         familyCount = pFontCollection->GetFontFamilyCount();

      }

      u32 index = 0;

      BOOL exists = false;

      wchar_t localeName[LOCALE_NAME_MAX_LENGTH];

      int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName,LOCALE_NAME_MAX_LENGTH);

      for(UINT32 i = 0; i < familyCount; ++i)
      {

         ::comptr<IDWriteFontFamily> pFontFamily;

         if(SUCCEEDED(hr))
         {

            hr = pFontCollection->GetFontFamily(i,&pFontFamily);

         }

         ::comptr<IDWriteLocalizedStrings> pFamilyNames;

         if(SUCCEEDED(hr))
         {

            hr = pFontFamily->GetFamilyNames(&pFamilyNames);

         }

         if(SUCCEEDED(hr))
         {

            if(defaultLocaleSuccess)
            {

               hr = pFamilyNames->FindLocaleName(localeName,&index,&exists);

            }

            if(SUCCEEDED(hr) && !exists) // if the above find did not find a match, retry with US English
            {

               hr = pFamilyNames->FindLocaleName(L"en-us",&index,&exists);

            }

         }

         // If the specified locale doesn't exist, select the first on the list.
         if(!exists)
         {
            index = 0;
         }

         UINT32 length = 0;

         // Get the string length.
         if(SUCCEEDED(hr))
         {

            hr = pFamilyNames->GetStringLength(index,&length);

         }

         // Allocate a string big enough to hold the name.
         wstring wstr;

         auto name = wstr.get_string_buffer(length + 1);

         if(name == nullptr)
         {

            hr = E_OUTOFMEMORY;

         }

         // Get the family name.
         if(SUCCEEDED(hr))
         {

            hr = pFamilyNames->GetString(index,name,length + 1);

         }

         wstr.release_string_buffer();

         // Add the family name to the String Array.
         if(SUCCEEDED(hr))
         {

            string strName = string((LPCWSTR)(name));

            itema.add(__new(::draw2d::font_enum_item(strName, strName)));

         }

      }

      itema.pred_sort([](auto & item1, auto & item2)
      {

         return item1->m_strName < item2->m_strName;

      });

   }


} // namespace draw2d_direct2d



