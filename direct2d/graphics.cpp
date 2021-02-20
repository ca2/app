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


   //bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   //{
   //   __throw(todo());
   //   //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   //}


   //bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   //{

   //   __throw(todo());

   //}


   bool graphics::CreateCompatibleDC(::draw2d::graphics *)
   {

      ::draw2d::lock draw2dlock;

      if (m_iType != 0)
      {

         destroy();

      }

      /*System.draw2d()->direct2d() = __new(::draw2d_direct2d::plugin);

      System.draw2d()->direct2d()->initialize();*/

      HRESULT hr;

      Microsoft::WRL::ComPtr<ID2D1DeviceContext> pdevicecontextTemplate;

      if (FAILED(hr = System.draw2d()->direct2d()->m_pd2device->CreateDeviceContext(
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

         ASSERT(false);

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
         D2D1_COMPATIBLE_RENDER_TARGET_OPTIONS_GDI_COMPATIBLE,
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


   //int graphics::GetDeviceCaps(double dIndex)
   //{

   //   __throw(todo());

   //}


   point_f64 graphics::GetBrushOrg()
   {
      //__throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //::point_f64 point;
      //VERIFY(::GetBrushOrgEx(get_handle1(), &point));
      //return point;

      return ::point_f64();

   }

   
   point_f64 graphics::SetBrushOrg(double x, double y)
   {
      //__throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //::point_f64 point;
      //VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
      //return point;

      return ::point_f64();

   }

   
   point_f64 graphics::SetBrushOrg(const ::point_f64 & point)
   {

      //__throw(todo());
      //ASSERT(get_handle1() != nullptr);
      //VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
      //return point;

      return ::point_f64();

   }


   //int graphics::EnumObjects(double dObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   //{
   //   __throw(todo());
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);
   //}

   
   bool graphics::_draw_blend(const ::image_drawing & imagedrawing)
   {

      //return ::draw2d::graphics::BitBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc);

      //if (m_pimageAlphaBlend->is_set())
      //{
      //   //return true;

      //   // Reference implementation

      //   ::rectangle_i32 rectAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

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

      //   point_i32 ::point_f64(x, y);

      //   ::size_f64 size(nWidth, nHeight);

      //   ::rectangle_i32 rectBlend(point, ::size_f64);

      //   ::rectangle_i32 rectIntersect;

      //   if (rectIntersect.intersect(rectAlphaBlend, rectBlend))
      //   {

      //      ::image_pointer pimage1;

      //      pimage1 = create_image(::size_f64);

      //      ::rectangle_i32 rectDib1(::point_f64(), pimage1->m_size);

      //      pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //      pimage1->get_graphics()->fill_rectangle(rectDib1, argb(0, 0, 0, 0));

      //      if (!pimage1->from(::point_f64(), pgraphicsSrc, ::point_f64(xSrc, ySrc), ::size_f64))
      //      {

      //         return false;

      //      }

      //      ::image_pointer pimage2;

      //      pimage2 = create_image(::size_f64);

      //      pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //      pimage2->get_graphics()->fill_rectangle(rectDib1, argb(255, 0, 0, 0));

      //      if (!pimage2->from(::point_f64(), m_pimageAlphaBlend, point_i32 - m_pointAlphaBlend, rectIntersect.size()))
      //      {

      //         return false;

      //      }

      //      __pointer(::draw2d_direct2d::graphics) pgraphicsDib1 = pimage1->get_graphics();

      //      __pointer(::draw2d_direct2d::graphics) pgraphicsDib2 = pimage2->get_graphics();

      //      HRESULT hr = ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->EndDraw();

      //      pgraphicsDib2->m_pdevicecontext->DrawImage(
      //      (ID2D1Bitmap *)pgraphicsDib1->get_current_bitmap()->get_os_data(),
      //      D2D1::Point2F(0.f, 0.f),
      //      d2d1::rectangle_f32(rectDib1),
      //      D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
      //      D2D1_COMPOSITE_MODE_SOURCE_OVER);

      //      if (SUCCEEDED(hr))
      //      {

      //         ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->BeginDraw();

      //      }

      //      set_alpha_mode(::draw2d::alpha_mode_blend);

      //      BitBltRaw(x, y, nWidth, nHeight, pimage2->get_graphics(), 0, 0);

      //      return true;

      //   }

      //}

      //return false;

      if (m_pimageAlphaBlend->is_set())
      {

         auto rectDst = imagedrawing.m_rectDst;
         auto rectSrc = imagedrawing.m_rectSrc;


         auto x = rectDst.left;
         auto y = rectDst.top;
         auto xSrc = rectSrc.left;
         auto ySrc = rectSrc.top;
         auto nWidth = rectDst.width();
         auto nHeight = rectDst.height();

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


         ::rectangle_f64 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         ::rectangle_f64 rectBlt(::point_f64(x, y), ::size_f64(nWidth, nHeight));

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
            //if (m_pimage->is_set() && pgraphicsSrc->m_pimage->is_set())
            //{

            //   ::point_f64 pointOff = GetViewportOrg();

            //   x += pointOff.x;

            //   y += pointOff.y;

            //   return m_pimage->blend(::point_f64(x, y), pgraphicsSrc->m_pimage, ::point_f64(xSrc, ySrc), m_pimageAlphaBlend, point_i32(m_pointAlphaBlend.x - x, m_pointAlphaBlend.y - y), rectBlt.size());

            //}
            //else
            //{

               auto pimage1 = create_image(rectBlt.size());

               pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               if (!pimage1->draw(::rectangle_f64(rectBlt.size()), imagedrawing.m_pimage, ::point_f64(xSrc, ySrc)))
               {

                  return false;

               }

               pimage1->blend2(::point_f64(), m_pimageAlphaBlend, point_f64(x - m_pointAlphaBlend.x, y - m_pointAlphaBlend.y), rectBlt.size(), 255);

               image_drawing_options imagedrawingoptions;

               _draw_raw(rectDst, pimage1, imagedrawingoptions, ::point_f64());

            //}

            return true;

         }

      }

      return false;
   }


   bool graphics::TextOutAlphaBlend(double x, double y, const block & block)
   {

      if (block.is_empty())
      {

         return false;

      }

      ASSERT(m_pimageAlphaBlend->is_ok());
      
      // "Reference" implementation for TextOutAlphaBlend

      auto size = GetTextExtent(block);

      ::rectangle_f64 rectAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

      ::point_f64 point(x, y);

      ::rectangle_f64 rectText(point, size);

      ::rectangle_f64 rectIntersect;

      if (rectIntersect.intersect(rectAlphaBlend, rectText))
      {

         ::draw2d::lock draw2dlock;

         auto pimage1 = create_image(size);

         ::rectangle_f64 rectDib1(::point_f64(), size);

         pimage1->get_graphics()->set(get_current_font());

         pimage1->get_graphics()->set(get_current_brush());

         pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         pimage1->get_graphics()->fill_rectangle(rectDib1, argb(0, 0, 0, 0));

         pimage1->get_graphics()->text_out(0, 0, block);

         ::image_pointer pimage2;

         pimage2->create(size);

         pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         pimage2->get_graphics()->fill_rectangle(rectDib1, argb(255, 0, 0, 0));

         if (!pimage2->draw(rectIntersect.size(), m_pimageAlphaBlend, __pointd(point - m_pointAlphaBlend)))
         {

            return false;

         }

         __pointer(::draw2d_direct2d::graphics) pgraphicsDib1 = pimage1->get_graphics();

         __pointer(::draw2d_direct2d::graphics) pgraphicsDib2 = pimage2->get_graphics();

         HRESULT hr = ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->EndDraw();

         pgraphicsDib1->m_pdevicecontext->DrawImage(
         (ID2D1Bitmap *)pgraphicsDib2->get_current_bitmap()->m_osdata[0],
         D2D1::Point2F(0.f, 0.f),
         d2d1::rectangle_f32(rectDib1),
         D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
         D2D1_COMPOSITE_MODE_DESTINATION_IN);

         if (SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pgraphicsDib2->get_os_data())->BeginDraw();

         }

         set_alpha_mode(::draw2d::alpha_mode_blend);

         draw(::point_f64(x, y), pimage1->get_graphics());

         return true;

      }

      return false;

   }


   ::e_status graphics::set(::draw2d::bitmap* pbitmap)
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


   //color32_t graphics::GetNearestColor(const ::color::color & color)
   //{

   //   __throw(todo());

   //}


   //::u32 graphics::RealizePalette()
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


   //bool graphics::GetWorldTransform(XFORM* pXform)
   //{

   //   __throw(todo());

   //}


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


   point_f64 graphics::GetViewportOrg()
   {

      return ::draw2d::graphics::GetViewportOrg();

   }


   size_f64 graphics::GetViewportExt()
   {

      __throw(todo());

   }

   
   point_f64 graphics::GetWindowOrg()
   {

      __throw(todo());

   }


   size_f64 graphics::GetWindowExt()
   {
      __throw(todo());
      //::size_f64::size_f64;
      //::GetWindowExtEx(get_handle2(), &::size_f64);
      //return ::size_f64;
   }


   point_f64 graphics::SetViewportOrg(const ::point_f64 & point)
   {

      return ::draw2d::graphics::SetViewportOrg(point.x, point.y);

   }


   ::size_f64 graphics::SetViewportExt(const ::size_f64 & size)
   {

      return ::draw2d::graphics::SetViewportExt(size.cx, size.cy);

   }


   point_f64 graphics::SetWindowOrg(const ::point_f64 & point)
   {

      return SetWindowOrg(point.x, point.y);

   }


   ::size_f64 graphics::set_window_ext(const ::size_f64 & size)
   {
      
      return set_window_ext(size.cx, size.cy);

   }


   void graphics::DPtoLP(::point_f64 * ppoints, count nCount)
   {

      __throw(todo());
      //::DPtoLP(get_handle2(), ppoints, nCount);

   }


   void graphics::DPtoLP(::rectangle_f64 * prectangle)
   {

      __throw(todo());
      //::DPtoLP(get_handle2(), (::point_f64 *)rectangle, 2);

   }


   void graphics::LPtoDP(::point_f64 * ppoints, count nCount)
   {

      __throw(todo());
      //::LPtoDP(get_handle2(), ppoints, nCount);

   }


   void graphics::LPtoDP(::rectangle_f64 * prectangle)
   {

      __throw(todo());
      //::LPtoDP(get_handle2(), (::point_f64 *)rectangle, 2);

   }


   bool graphics::fill_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      __throw(todo());
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;

   }


   bool graphics::frame_region(::draw2d::region* pRgn, ::draw2d::brush* pBrush, double nWidth, double nHeight)
   {

      __throw(todo());
      //return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;

   }


   bool graphics::invert_region(::draw2d::region* pregion)
   {
      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != false;

   }


   bool graphics::paint_region(::draw2d::region* pregion)
   {

      __throw(todo());
      //ASSERT(get_handle1() != nullptr);

      //return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != false;

   }

   //bool graphics::PtVisible(double x, double y)
   //{

   //   __throw(todo());
   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::PtVisible(get_handle1(), x, y) != false;

   //}

   //bool graphics::PtVisible(const ::point_f64 & point)
   //{

   //   ASSERT(get_handle1() != nullptr);

   //   return PtVisible(point.x, point.y);

   //} // call virtual


   //bool graphics::RectVisible(const ::rectangle_i32 & rectangle)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::RectVisible(get_handle1(), rectangle) != false;

   //}


   point_f64 graphics::current_position()
   {

      __throw(todo());
      //ASSERT(get_handle2() != nullptr);
      //::point_f64 point;
      //VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
      //return point;

   }


   //bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   //{

   //   ::draw2d::path_pointer path(e_create);

   //   double pi = 3.1415927f;

   //   ::rectangle_f64 rectangle(x1, y1, x2, y2);

   //   double centerx    = (x2 + x1) / 2.0;
   //   double centery    = (y2 + y1) / 2.0;

   //   double start      = atan2(y3 - centery, x3 - centerx) * 180.0 / pi;
   //   double end        = atan2(y4 - centery, x4 - centerx) * 180.0 / pi;

   //   //path->begin_figure(false, ::draw2d::fill_mode_winding);
   //   path->begin_figure();
   //   path->add_arc(rectangle, (int) start, (int) fmod(end + 360.0 - start, 360.0));
   //   //path->end_figure(false);
   //   //path->close_figure();

   //   return this->path(path);

   //}

   bool graphics::Arc(double x1, double y1, double w, double h, angle start, angle extends)
   {

      ::draw2d::path_pointer path(e_create);

      ::rectangle_i32 rectangle((::i32) x1, (::i32)y1, (::i32)(x1 + w), (::i32)(y1 + h));

      //path->begin_figure(false, ::draw2d::fill_mode_winding);
      path->begin_figure();
      path->add_arc(rectangle, start, extends);
      //path->end_figure(false);
      //path->close(false);

      return this->path(path);

   }


   bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      ::draw2d::path_pointer path(e_create);

      double pi = 3.1415927f;

      ::rectangle_i32 rectangle((::i32)x1, (::i32)y1, (::i32)x2, (::i32)y2);

      double centerx = (x2 + x1) / 2.0;
      double centery = (y2 + y1) / 2.0;

      double start = atan2(y3 - centery, x3 - centerx) * 180.0 / pi;
      double end = atan2(y4 - centery, x4 - centerx) * 180.0 / pi;

      //path->begin_figure(false, ::draw2d::fill_mode_winding);
      path->begin_figure();
      path->add_arc(rectangle, start, end - start);
      //path->end_figure(false);

      return this->path(path);

   }


   bool graphics::Arc(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      ASSERT(get_handle1() != nullptr);

      return Arc(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y)  != false;

   }


   bool graphics::polyline(const ::point_f64* ppoints, count nCount)
   {

      ::draw2d::path_pointer path(e_create);

      //path->begin_figure(false, ::draw2d::fill_mode_winding);

      path->begin_figure();

      path->add_lines(ppoints, nCount);

      //path->end_figure(false);

      //path->end_figure();

      return this->draw_path(path);

   }


   bool graphics::frame_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::brush* pbrush)
   {

      if (m_prendertarget == nullptr)
      {

         return false;

      }

      D2D1_RECT_F rectangle;

      __copy(rectangle, rectParam);

      m_prendertarget->DrawRectangle(rectangle, pbrush->get_os_data < ID2D1Brush * > (this));

      return true;

   }


   bool graphics::invert_rectangle(const ::rectangle_f64 & rectangle)
   {

      __throw(todo());

      return false;

   }


   //bool graphics::DrawIcon(double x, double y, ::draw2d::icon * picon)
   //{
   //   __throw(todo());
   //   //ASSERT(get_handle1() != nullptr);

   //   //if(picon == nullptr)
   //   //   return false;

   //   //return ::DrawIcon(get_handle1(), x, y, picon->m_hicon) != false;

   //}

   //bool graphics::DrawIcon(const ::point_f64 & point, ::draw2d::icon * picon)
   //{
   //   __throw(todo());
   //   //ASSERT(get_handle1() != nullptr);

   //   //if(picon == nullptr)
   //   //   return false;

   //   //return ::DrawIcon(get_handle1(), point.x, point.y, picon->m_hicon) != false;

   //}

//   bool graphics::draw(const ::rectangle_f64 & rectDst, ::draw2d::icon * picon)
//   {
//
//#ifdef _UWP
//
//      //::exception::throw_not_implemented();
//      return false;
//
//#else
//
//      try
//      {
//
//         if(picon == nullptr)
//            return false;
//
//         if(m_prendertarget == nullptr)
//            return false;
//
//         bool bOk = false;
//
//         BITMAPINFO info;
//         color32_t * pcolorref;
//
//         ZeroMemory(&info, sizeof (BITMAPINFO));
//
//         info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
//         info.bmiHeader.biWidth         = rectDst.width();
//         info.bmiHeader.biHeight        = - rectDst.height();
//         info.bmiHeader.biPlanes        = 1;
//         info.bmiHeader.biBitCount      = 32;
//         info.bmiHeader.biCompression   = BI_RGB;
//         info.bmiHeader.biSizeImage     = rectDst.area() * 4;
//
//         HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pcolorref, nullptr, 0);
//
//         HDC hdc = ::CreateCompatibleDC(nullptr);
//
//         HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);
//
//         int istepIfAniCur = 0;
//         if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, rectDst.width(), rectDst.height(), istepIfAniCur, nullptr, DI_IMAGE | DI_MASK))
//         {
//
//            ::SelectObject(hdc, hbitmapOld);
//
//            try
//            {
//
//               //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (byte *) pcolorref);
//
//               ::draw2d::bitmap_pointer b(e_create);
//
//               b->CreateBitmap(this, rectDst.size(), 1, 32, pcolorref, rectDst.width() * sizeof(color32_t));
//
//               D2D1_RECT_F rectangle_i32;
//
//               __copy(rectangle, rectDst);
//               //rectangle.left   = (FLOAT) rectangle_i32;
//               //rectangle.top    = (FLOAT) y;
//               //rectangle.right  = rectangle.left    + cx;
//               //rectangle.bottom = rectangle.top     + cy;
//
//               m_prendertarget->DrawBitmap((ID2D1Bitmap *) b->get_os_data(), rectangle);
//
//            }
//            catch(...)
//            {
//            }
//
//         }
//
//         ::DeleteDC(hdc);
//
//         ::DeleteObject(hbitmap);
//
//         return bOk;
//
//      }
//      catch(...)
//      {
//      }
//
//      return false;
//
//#endif
//
//   }
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      __throw(todo());
//      //ASSERT(get_handle1() != nullptr);
//      //return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != false;
//
//   }
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, ::draw2d::bitmap* pBitmap, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//      //return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != false;
//
//   }
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, HICON hIcon, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//      //return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//      //return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != false;
//
//   }
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, const char * lpszText, ::u32 nFlags, bool bPrefixText, double dTextLen, HBRUSH hBrush)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//      //return ::DrawState(get_handle1(), hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//
//   }
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, const char * lpszText, ::u32 nFlags, bool bPrefixText, double dTextLen, ::draw2d::brush* pBrush)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//      //return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//
//   }
//
//#ifdef WINDOWS_DESKTOP
//
//   /*
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr); return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != false;
//
//   }
//
//   bool graphics::DrawState(const ::point_f64 & point, const ::size_f64& ::size_f64, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr); return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != false;
//
//   }
//   */
//
//#endif
//
//
   //bool graphics::DrawEdge(::rectangle_f64 * prectangle, ::u32 nEdge, ::u32 nFlags)
   //{

   //   __throw(todo());

   //   ASSERT(get_handle1() != nullptr);

   //   //return ::DrawEdge(get_handle1(), rectangle, nEdge, nFlags) != false;

   //}


   //bool graphics::DrawFrameControl(::rectangle_f64 * prectangle, ::u32 nType, ::u32 nState)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr); return ::DrawFrameControl(get_handle1(), rectangle, nType, nState) != false;

   //}

   bool graphics::Chord(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      __throw(todo());

      ASSERT(get_handle1() != nullptr);

      //return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;

   }

   bool graphics::Chord(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      __throw(todo());

      ASSERT(get_handle1() != nullptr);

      //return ::Chord(get_handle1(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y) != false;

   }


   void graphics::DrawFocusRect(const ::rectangle_f64 & rectangle)
   {

      __throw(todo());

      ASSERT(get_handle1() != nullptr);

   }


   bool graphics::fill_ellipse(const ::rectangle_f64 & rectangle)
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

      ellipse.point.x = (float)(rectangle.right + rectangle.left) / 2.f;
      ellipse.point.y = (float)(rectangle.bottom + rectangle.top) / 2.f;
      ellipse.radiusX = (float)(rectangle.right - rectangle.left) / 2.f;
      ellipse.radiusY = (float)(rectangle.bottom - rectangle.top) / 2.f;

      defer_primitive_blend();

      m_pdevicecontext->FillEllipse(&ellipse, pbrush);

      return true;

   }


   bool graphics::draw_ellipse(const ::rectangle_f64 & rectangle)
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

      ellipse.point.x = (float)(rectangle.right + rectangle.left) / 2.f;
      ellipse.point.y = (float)(rectangle.bottom + rectangle.top) / 2.f;
      ellipse.radiusX = (float)(rectangle.right - rectangle.left) / 2.f;
      ellipse.radiusY = (float)(rectangle.bottom - rectangle.top) / 2.f;

      defer_primitive_blend();

      m_pdevicecontext->DrawEllipse(&ellipse, pbrush,(FLOAT) m_ppen->m_dWidth);

      return true;

   }


   bool graphics::Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      __throw(todo());

   }


   bool graphics::Pie(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      __throw(todo());

      return false;

   }


   bool graphics::polygon_i32(const POINT_F64 * ppoints, count count)
   {

      if (count < 3)
      {

         return false;

      }

      Microsoft::WRL::ComPtr<ID2D1PathGeometry> pgeometry;

      HRESULT hr = ::draw2d_direct2d::plugin::d2d1_factory1()->CreatePathGeometry(&pgeometry);

      {

         Microsoft::WRL::ComPtr<ID2D1GeometrySink> psink;

         pgeometry->Open(&psink);

         psink->SetFillMode(D2D1_FILL_MODE_WINDING);

         psink->BeginFigure(D2D1::Point2F((FLOAT) ppoints->x, (FLOAT)ppoints->y), D2D1_FIGURE_BEGIN_FILLED);

         for (index i = 1; i < count; i++)
         {

            psink->AddLine({ (FLOAT)ppoints[i].x, (FLOAT)ppoints[i].y });

         }

         psink->EndFigure(D2D1_FIGURE_END_CLOSED);

         psink->Close();

      }

      bool bOk = fill_path(pgeometry.Get(), m_pbrush);

      bOk = bOk && draw_path(pgeometry.Get(), m_ppen);

      return bOk;

   }


   bool graphics::draw_polygon(const POINT_F64 * ppoints, count count)
   {

      if (count < 3)
      {

         return false;

      }

      Microsoft::WRL::ComPtr<ID2D1PathGeometry> pgeometry;

      HRESULT hr = ::draw2d_direct2d::plugin::d2d1_factory1()->CreatePathGeometry(&pgeometry);

      {

         Microsoft::WRL::ComPtr<ID2D1GeometrySink> psink;

         pgeometry->Open(&psink);

         psink->SetFillMode(D2D1_FILL_MODE_WINDING);

         psink->BeginFigure(D2D1::Point2F((FLOAT)ppoints->x, (FLOAT)ppoints->y), D2D1_FIGURE_BEGIN_FILLED);

         for (index i = 1; i < count; i++)
         {

            psink->AddLine({ (FLOAT)ppoints[i].x, (FLOAT)ppoints[i].y });

         }

         psink->EndFigure(D2D1_FIGURE_END_CLOSED);

         psink->Close();

      }

      bool bOk = draw_path(pgeometry.Get(), m_ppen);

      return bOk;


   }


   bool graphics::fill_polygon(const POINT_F64 * ppoints, count count)
   {

      if (count < 3)
      {

         return false;

      }

      Microsoft::WRL::ComPtr<ID2D1PathGeometry> pgeometry;

      HRESULT hr = ::draw2d_direct2d::plugin::d2d1_factory1()->CreatePathGeometry(&pgeometry);

      {

         Microsoft::WRL::ComPtr<ID2D1GeometrySink> psink;

         pgeometry->Open(&psink);

         psink->SetFillMode(D2D1_FILL_MODE_WINDING);

         psink->BeginFigure(D2D1::Point2F((FLOAT)ppoints->x, (FLOAT)ppoints->y), D2D1_FIGURE_BEGIN_FILLED);

         for (index i = 1; i < count; i++)
         {

            psink->AddLine({ (FLOAT)ppoints[i].x, (FLOAT)ppoints[i].y });

         }

         psink->EndFigure(D2D1_FIGURE_END_CLOSED);

         psink->Close();

      }

      bool bOk = fill_path(pgeometry.Get(), m_pbrush);

      return bOk;

   }


   bool graphics::rectangle(const ::rectangle_f64 & rectangle)
   {

      bool bOk1;

      bOk1 = fill_rectangle(rectangle);

      bool bOk2;

      bOk2 = draw_rectangle(rectangle);

      return bOk1 && bOk2;

   }


   bool graphics::draw_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::pen * ppen)
   {

      if (ppen == nullptr)
      {

         return false;

      }

      if (ppen->m_epen == ::draw2d::e_pen_null)
      {

         return true;

      }

      D2D1_RECT_F rectangle;

      __copy(rectangle, rectParam);

      ::draw2d_direct2d::pen * ppen2 = dynamic_cast <::draw2d_direct2d::pen *> (ppen);

      defer_primitive_blend();

      m_prendertarget->DrawRectangle(&rectangle, ppen2->get_os_data < ID2D1Brush * >(this), (FLOAT)m_ppen->m_dWidth);

      return true;

   }


   bool graphics::fill_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::brush * pbrush)
   {

      if (pbrush == nullptr)
      {

         return false;

      }

      if (pbrush->m_etype == ::draw2d::brush::e_type_null)
      {

         return true;

      }

      D2D1_RECT_F rectangle;

      __copy(rectangle, rectParam);

      ::draw2d_direct2d::brush * pbrush2 = dynamic_cast <::draw2d_direct2d::brush *> (pbrush);

      defer_primitive_blend();

      m_prendertarget->FillRectangle(rectangle, pbrush2->get_os_data < ID2D1Brush * >(this));

      return true;

   }


   bool graphics::round_rectangle(const ::rectangle_f64 & rectParam, double dRadius)
   {

      D2D1_ROUNDED_RECT rectangle;

      __copy(rectangle, rectParam);

      rectangle.radiusX = (FLOAT) dRadius;

      if (m_pbrush.is_set() && m_pbrush->m_etype != ::draw2d::brush::e_type_null)
      {

         auto pbrush = m_pbrush.cast <::draw2d_direct2d::brush > ();

         defer_primitive_blend();

         m_prendertarget->FillRoundedRectangle(rectangle, pbrush->get_os_data < ID2D1Brush * > (this));

      }

      if (m_pbrush.is_set() && m_pbrush->m_etype != ::draw2d::brush::e_type_null)
      {

         auto ppen = m_ppen.cast <::draw2d_direct2d::pen >();
         
         defer_primitive_blend();

         m_prendertarget->DrawRoundedRectangle(rectangle, ppen->get_os_data < ID2D1Brush * > (this), (FLOAT) ppen->m_dWidth);

      }

      return true;

   }


   //bool graphics::PatBlt(double x, double y, double dWidth, double dHeight)
   //{

   //   __throw(todo());

   //}


   bool graphics::_draw_raw(const ::rectangle_f64 & rectDst, ::image * pimage, const image_drawing_options & imagedrawingoptions, const ::point_f64 & pointSrc)
   {

      ::draw2d::lock draw2dlock;

      try
      {

         if (pimage == nullptr)
         {

            return false;

         }

         //if (pgraphicsSrc->get_current_bitmap() == nullptr)
         //{

         //   return false;

         //}

         //if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
         //{

         //   return false;

         //}

         double x = rectDst.left;
         double y = rectDst.top;
         double nWidth = rectDst.width();
         double nHeight = rectDst.height();
         double xSrc = pointSrc.x;
         double ySrc = pointSrc.y;

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

            if (nWidth + x + GetViewportOrg().x > sz.width)
            {

               nWidth = sz.width - x - GetViewportOrg().x;

            }

            if (nHeight + y + GetViewportOrg().y > sz.height)
            {

               nHeight = sz.height - y - GetViewportOrg().y;

            }

         }

         {

            D2D1_SIZE_U sz = ((ID2D1Bitmap *)pimage->get_bitmap()->get_os_data())->GetPixelSize();

            if (nWidth + xSrc > sz.width)
            {

               nWidth = sz.width - xSrc;

            }

            if (nHeight + ySrc > sz.height)
            {

               nHeight = sz.height - ySrc;

            }

         }

         D2D1_RECT_F rectDst = D2D1::RectF((float)x, (float)y, (float)(x + nWidth), (float)(y + nHeight));

         D2D1_RECT_F rectSrc = D2D1::RectF((float)xSrc, (float)ySrc, (float)(xSrc + nWidth), (float)(ySrc + nHeight));

         HRESULT hr = ((ID2D1DeviceContext *)pimage->g()->get_os_data())->EndDraw();

         defer_primitive_blend();

         m_pdevicecontext->DrawBitmap((ID2D1Bitmap *)pimage->g()->get_current_bitmap()->get_os_data(), rectDst, 1.0, D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR, rectSrc);

         if (SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pimage->g()->get_os_data())->BeginDraw();

         }

         return true;

      }
      catch (...)
      {

         return false;

      }

   }


   bool graphics::_stretch_raw(const ::rectangle_f64 & rectDst, ::image * pimage, const image_drawing_options & imagedrawingoptions, const ::rectangle_f64 & rectSrc)
   {

      try
      {

         double xDst = rectDst.left;
         double yDst = rectDst.top;
         double nDstWidth = rectDst.width();
         double nDstHeight = rectDst.height();
         double xSrc = rectSrc.left;
         double ySrc = rectSrc.top;
         double nSrcWidth = rectSrc.width();
         double nSrcHeight = rectSrc.height();

         //if (pgraphicsSrc == nullptr)
         //{

         //   return false;

         //}

         //if (pgraphicsSrc->get_current_bitmap() == nullptr)
         //{

         //   return false;

         //}

         //if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
         //{

         //   return false;

         //}

         D2D1_RECT_F rectDst = D2D1::RectF((float)xDst, (float)yDst, (float)(xDst + nDstWidth), (float)(yDst + nDstHeight));

         D2D1_RECT_F rectSrc = D2D1::RectF((float)xSrc, (float)ySrc, (float)(xSrc + nSrcWidth), (float)(ySrc + nSrcHeight));

         HRESULT hr = ((ID2D1DeviceContext *)pimage->g()->get_os_data())->EndDraw();

         defer_primitive_blend();

         if (m_prendertarget != nullptr)
         {

            m_prendertarget->DrawBitmap((ID2D1Bitmap *)pimage->g()->get_current_bitmap()->get_os_data(), &rectDst, 1.0, m_bitmapinterpolationmode, &rectSrc);

         }
         else
         {

            m_pdevicecontext->DrawBitmap((ID2D1Bitmap *)pimage->g()->get_current_bitmap()->get_os_data(), rectDst, 1.0, m_interpolationmode, rectSrc);

         }

         if (SUCCEEDED(hr))
         {

            ((ID2D1DeviceContext *)pimage->g()->get_os_data())->BeginDraw();

         }
         else
         {

            output_debug_string("direct2d graphics::StretchBltRaw hr failed");

         }

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   //bool graphics::_draw_raw(const ::rectangle_f64 & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point_f64 & pointSrc)
   //{


   //}


   //bool graphics::_stretch_raw(const ::rectangle_f64 & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectSrc)
   //{


   //}


   ::color::color graphics::GetPixel(double x, double y)
   {

      __throw(todo());

   }


   ::color::color graphics::GetPixel(const ::point_f64 & point)
   {

      __throw(todo());

   }


   ::color::color graphics::SetPixel(double x, double y, const ::color::color & color)
   {

      __throw(todo());

   }


   ::color::color graphics::SetPixel(const ::point_f64 & point, const ::color::color & color)
   {

      __throw(todo());

   }


//   bool graphics::FloodFill(double x, double y, const ::color::color & color)
//   {
//
//      __throw(todo());
//
//   }
//
//
//   bool graphics::ExtFloodFill(double x, double y, const ::color::color & color, ::u32 nFillType)
//   {
//
//      __throw(todo());
//
//   }


   //bool graphics::text_out(double x, double y, const block & block)
   //{

   //   return text_out(x, y, (const char *) block.get_data(), block.get_size());

   //}


   //bool graphics::text_out(double x, double y, const string & str)
   //{

   //   return text_out((int) x, (int) y, str, (int) str.get_length());

   //}


   //bool graphics::ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const char * lpszString, strsize nCount, LPINT lpDxWidths)
   //{

   //   __throw(todo());

   //}


   //bool graphics::ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const string & str, LPINT lpDxWidths)
   //{

   //   __throw(todo());

   //}


   //::size_f64 graphics::TabbedTextOut(double x, double y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   //{

   //   __throw(todo());

   //}


   //::size_f64 graphics::TabbedTextOut(double x, double y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   //{

   //   __throw(todo());

   //}


   //::size_f64 graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   __throw(todo());

   //}


   //::size_f64 graphics::GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   __throw(todo());

   //}


   ::size_f64 graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(todo());

   }


   ::size_f64 graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(todo());

   }


   //bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int), LPARAM lpData, double dCount,double x, double y, double dWidth, double dHeight)
   //{

   //   __throw(todo());

   //}


   ::u32 graphics::GetTextAlign()
   {

      __throw(todo());

   }


   //int graphics::GetTextFace(count nCount, char * lpszFacename)
   //{

   //   __throw(todo());

   //}


   //int graphics::GetTextFace(string & rString)
   //{

   //   __throw(todo());

   //}


   bool graphics::get_text_metrics(::write_text::text_metric * lpMetrics)
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
      ::u32 findex;
      BOOL exists;

      auto pwritetextformat = m_pfont->get_os_data < IDWriteTextFormat * >(this);

      if (::is_null(pwritetextformat))
      {

         lpMetrics->m_dAscent = 0;
         lpMetrics->m_dDescent = 0;
         lpMetrics->m_dHeight = 24;
         lpMetrics->m_dInternalLeading = 0;
         lpMetrics->m_dExternalLeading = 0;


         return true;

      }

      pwritetextformat->GetFontFamilyName(name, 256);

      pwritetextformat->GetFontCollection(&pcollection);

      if (pcollection == nullptr)
      {

         lpMetrics->m_dAscent = 0;
         lpMetrics->m_dDescent = 0;
         lpMetrics->m_dHeight = 24;
         lpMetrics->m_dInternalLeading = 0;
         lpMetrics->m_dExternalLeading = 0;

         return true;

      }

      pcollection->FindFamilyName(name, &findex, &exists);

      if (!exists)
      {

         pcollection->FindFamilyName(L"Arial", &findex, &exists);

         if (!exists)
         {

            lpMetrics->m_dAscent = 0;
            lpMetrics->m_dDescent = 0;
            lpMetrics->m_dHeight = 24;
            lpMetrics->m_dInternalLeading = 0;
            lpMetrics->m_dExternalLeading = 0;

            return true;

         }

      }

      Microsoft::WRL::ComPtr<IDWriteFontFamily> ffamily;

      pcollection->GetFontFamily(findex, &ffamily);

      if (ffamily == nullptr)
      {

         lpMetrics->m_dAscent = 0;
         lpMetrics->m_dDescent = 0;
         lpMetrics->m_dHeight = 24;
         lpMetrics->m_dInternalLeading = 0;
         lpMetrics->m_dExternalLeading = 0;

         return true;

      }

      Microsoft::WRL::ComPtr<IDWriteFont> pfont;

      ffamily->GetFirstMatchingFont(pwritetextformat->GetFontWeight(), pwritetextformat->GetFontStretch(), pwritetextformat->GetFontStyle(), &pfont);

      if (pfont == nullptr)
      {

         lpMetrics->m_dAscent = 0;
         lpMetrics->m_dDescent = 0;
         lpMetrics->m_dHeight = 24;
         lpMetrics->m_dInternalLeading = 0;
         lpMetrics->m_dExternalLeading = 0;

         return true;

      }

      DWRITE_FONT_METRICS metrics;

      pfont->GetMetrics(&metrics);

      double ratio = pwritetextformat->GetFontSize() / (float)metrics.designUnitsPerEm;

      lpMetrics->m_dAscent = (::i32) (metrics.ascent * ratio);
      lpMetrics->m_dDescent = (::i32) (metrics.descent * ratio);
      lpMetrics->m_dInternalLeading = (::i32) 0;
      lpMetrics->m_dExternalLeading = (::i32) (metrics.lineGap * ratio);
      lpMetrics->m_dHeight = (::i32) ((metrics.ascent + metrics.descent + metrics.lineGap) * ratio);

      return true;

   }


   bool graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::GetTextMetrics(get_handle1(), lpMetrics) != false;

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
//   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != false;
//
//   }
//
//   bool graphics::GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != false;
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
//   /*   u32 graphics::GetCharacterPlacement(const char * lpString, double dCount, double dMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
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
//      u32 graphics::GetCharacterPlacement(string & str, double dMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
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
//   ::size_f64 graphics::GetAspectRatioFilter()
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//      //::size_f64::size_f64;
//      //VERIFY(::GetAspectRatioFilterEx(get_handle2(), &::size_f64));
//      //return ::size_f64;
//
//   }
//
//   bool graphics::ScrollDC(int dx, int dy, const ::rectangle_i32 & rectScroll, const ::rectangle_i32 & rectClip, ::draw2d::region* pRgnUpdate, RECTANGLE_I32 * lpRectUpdate)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::ScrollDC(get_handle1(), dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != false;
//
//   }
//
//   // Printer Escape Functions
//   int graphics::Escape(double dEscape, double dCount, const char * lpszInData, LPVOID lpOutData)
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
   ::u32 graphics::SetBoundsRect(const ::rectangle_f64 & rectBounds, ::u32 flags)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetBoundsRect(get_handle1(), rectBounds, flags);

   }


   ::u32 graphics::GetBoundsRect(::rectangle_f64 * prectBounds, ::u32 flags)
   {

      __throw(todo());

      //ASSERT(get_handle2() != nullptr);

      //return ::GetBoundsRect(get_handle2(), rectBounds, flags);

   }


   //bool graphics::ResetDC(const DEVMODE* lpDevMode)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle2() != nullptr);

   //   //return ::ResetDC(get_handle2(), lpDevMode) != nullptr;

   //}

#ifdef WINDOWS_DESKTOP

   /*   ::u32 graphics::GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm)
      {

         __throw(todo());

         //ASSERT(get_handle2() != nullptr);

         //return ::GetOutlineTextMetrics(get_handle2(), cbData, lpotm);

      }

      bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc)
      {

         __throw(todo());

         //ASSERT(get_handle2() != nullptr);

         //return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != false;

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
//   int graphics::GetKerningPairs(double dPairs, LPKERNINGPAIR lpkrnpair)
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
//   u32 graphics::GetGlyphOutline(::u32 nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm,  u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2)
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


   //int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   //}


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


//   bool graphics::MaskBlt(double x, double y, double dWidth, double dHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;
//
//   }
//
//
//   bool graphics::PlgBlt(::point_f64 * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double dWidth, double dHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != false;
//
//   }


   bool graphics::SetPixelV(double x, double y, const ::color::color & color)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetPixelV(get_handle1(), x, y, crColor) != false;

   }

   bool graphics::SetPixelV(const ::point_f64 & point, const ::color::color & color)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != false;

   }

   bool graphics::AngleArc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != false;

   }


   bool graphics::ArcTo(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ArcTo(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);

   }

   //int graphics::GetArcDirection()
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle2() != nullptr);

   //   //return ::GetArcDirection(get_handle2());

   //}

   bool graphics::poly_polyline(const ::point_f64* ppoints, const ::i32 * lpPolyPoints, count nCount)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::poly_polyline(get_handle1(), ppoints, lpPolyPoints, nCount) != false;

   }

#ifdef WINDOWS_DESKTOP
   /*
      bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust)
      {

         __throw(todo());

         //ASSERT(get_handle2() != nullptr);

         //return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != false;

      }
      */
#endif


   bool graphics::poly_bezier(const ::point_f64* ppoints, count nCount)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);

      //return ::poly_bezier(get_handle1(), ppoints, nCount) != false;

   }


//   int graphics::DrawEscape(double dEscape, double dInputSize, const char * lpszInputData)
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
//   int graphics::Escape(double dEscape, double dInputSize, const char * lpszInputData, double dOutputSize, char * lpszOutputData)
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
//      bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT lpABCF)
//      {
//
//         __throw(todo());
//
//         //ASSERT(get_handle2() != nullptr);
//         //
//         //return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != false;
//
//      }
//      */
//#endif
//
//   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float* lpFloatBuffer)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle2() != nullptr);
//
//      //return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != false;
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
      //   return false;

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


   i32 graphics::GetPath(::point_f64 * ppoints, byte * lpTypes, ::count nCount)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::GetPath(get_handle1(), ppoints, lpTypes, nCount);

   }


   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      __throw(todo());

      //ASSERT(get_handle1() != nullptr);
      //return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != false;

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


   bool graphics::AddMetaFileComment(::u32 nDataSize, const byte* pCommentData)
   {

      __throw(todo());


      //ASSERT(get_handle1() != nullptr);
      //return ::GdiComment(get_handle1(), nDataSize, pCommentData) != false;
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
   return true;
   }

   VOID Example_EnumerateMetafile9(HDC hdc)
   {
   Graphics graphics(hdc);
   // Create a Metafile object from an existing disk metafile.
   Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
   {
   // Fill a rectangle_i32 and an ellipse in pMeta.
   Graphics metaGraphics(pMeta);
   metaGraphics.fill_rectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
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
   //bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::rectangle_f64 & rectBounds)
   //{

   //   __throw(todo());

   //   //Gdiplus::RectF rectangle_i32((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

   //   //Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);

   //   ////m_pgraphcis->EnumerateMetafile(pMeta, rectangle, metaCallback, PMETAHEADER);

   //   //bool bOk = m_prendertarget->DrawImage(pMeta, rectangle) == Gdiplus::Status::Ok;

   //   //delete pMeta;

   //   //return bOk ? true : false;
   //   ////return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

   //}

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   // Thank you
   // Jiju George T
   // Web Developer
   // India India
   // Member


   //bool graphics::_alpha_blend_raw(const ::rectangle_f64 & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectSrc, double dRate)
   //{

   //   ::draw2d::lock draw2dlock;

   //   /*      float fA = (float) dRate;

   //         Gdiplus::ColorMatrix matrix = {
   //            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
   //            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
   //            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
   //            0.0f, 0.0f, 0.0f, fA  , 0.0f,
   //            0.0f, 0.0f, 0.0f, 0.0f, 1.0f
   //         };

   //         Gdiplus::ImageAttributes attributes;

   //         attributes.SetColorMatrix(&matrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

   //         Gdiplus::RectF dstRect((Gdiplus::REAL) xDest, (Gdiplus::REAL) yDest, (Gdiplus::REAL) nDestWidth, (Gdiplus::REAL) nDestHeight);

   //         m_prendertarget->DrawImage((Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), dstRect,
   //            (Gdiplus::REAL) xSrc, (Gdiplus::REAL) ySrc, (Gdiplus::REAL) nSrcWidth, (Gdiplus::REAL) nSrcHeight, Gdiplus::UnitPixel, &attributes);*/

   //   try
   //   {

   //      if(pgraphicsSrc == nullptr)
   //         return false;

   //      if(pgraphicsSrc->get_current_bitmap() == nullptr)
   //         return false;

   //      if(pgraphicsSrc->get_current_bitmap()->m_osdata[0] == nullptr)
   //         return false;

   //      //D2D1_RECT_F rectDst = D2D1::RectF((float) xDst, (float) yDst, (float) (xDst + nDstWidth), (float) (yDst + nDstHeight));
   //      //D2D1_RECT_F rectSrc = D2D1::RectF((float) xSrc, (float) ySrc, (float) (xSrc + nSrcWidth), (float) (ySrc + nSrcHeight));
   //      /*
   //               if (get_current_bitmap() != nullptr && get_current_bitmap()->get_os_data() != nullptr)
   //               {

   //                  D2D1_SIZE_U sz = ((ID2D1Bitmap *)get_current_bitmap()->get_os_data())->GetPixelSize();

   //                  if (natural(nDstWidth + xDst) > sz.width)
   //                     nDstWidth = sz.width - xDst;

   //                  if (natural(nDstHeight + yDst) > sz.height)
   //                     nDstHeight = sz.height - yDst;

   //               }

   //               {

   //                  D2D1_SIZE_U sz = ((ID2D1Bitmap *)pgraphicsSrc->get_current_bitmap()->get_os_data())->GetPixelSize();

   //                  if (natural(nSrcWidth + xSrc) > sz.width)
   //                     nSrcWidth = sz.width - xSrc;

   //                  if (natural(nSrcHeight + ySrc) > sz.height)
   //                     nSrcHeight = sz.height - ySrc;

   //               }*/

   //      D2D1_RECT_F rDst = D2D1::RectF((float)rectDst.left, (float)rectDst.top, (float) rectDst.right, (float) rectDst.bottom);
   //      D2D1_RECT_F rSrc = D2D1::RectF((float)rectSrc.left, (float)rectSrc.top, (float) rectSrc.right, (float) rectSrc.bottom);


   //      //dynamic_cast <::draw2d_direct2d::graphics *> (pgraphicsSrc)->SaveClip();

   //      HRESULT hr = ((ID2D1DeviceContext *) pgraphicsSrc->get_os_data())->EndDraw();

   //      defer_primitive_blend();

   //      if(m_pdevicecontext != nullptr)
   //      {

   //         m_pdevicecontext->DrawBitmap((ID2D1Bitmap*)pgraphicsSrc->get_current_bitmap()->get_os_data(), rDst, (float)dRate, m_interpolationmode, rSrc);

   //      }
   //      else
   //      {

   //         m_prendertarget->DrawBitmap((ID2D1Bitmap*)pgraphicsSrc->get_current_bitmap()->get_os_data(), rDst, (float)dRate, m_bitmapinterpolationmode, rSrc);

   //      }


   //      //auto pimage = (ID2D1Bitmap*)pgraphicsSrc->get_current_bitmap()->get_os_data();
   //      //auto ecomposite = m_ealphamode == ::draw2d::alpha_mode_blend ? D2D1_COMPOSITE_MODE_SOURCE_OVER : D2D1_COMPOSITE_MODE_SOURCE_IN;

   //      //m_pdevicecontext->DrawImage(pimage, pointDst, rectSrc, m_interpolationmode, ecomposite);


   //      //hr = m_prendertarget->Flush();
   //      //flush();

   //      if(SUCCEEDED(hr))
   //      {

   //         ((ID2D1DeviceContext *)pgraphicsSrc->get_os_data())->BeginDraw();

   //         //dynamic_cast <::draw2d_direct2d::graphics *> (pgraphicsSrc)->RestoreClip();

   //      }

   //      return true;

   //   }
   //   catch(...)
   //   {
   //      return false;
   //   }



   //   return true;

   //}


   /*bool graphics::alpha_blend(double xDest, double yDest, double dDestWidth, double dDestHeight,
   ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double dSrcWidth, double dSrcHeight, BLENDFUNCTION blend)
   {

   __throw(not_implemented_exception());
   //if(get_handle1() == nullptr)
   // return false;


   if(m_pimageAlphaBlend->is_set())
   {


   ::rectangle_i32 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


   ::image_pointer pimageWork = nullptr;
   ::image_pointer pimageWork2 = nullptr;
   //         ::image_pointer pimageWork3 = nullptr;
   ::image_pointer pimageWork4 = nullptr;


   ::point_f64 pointSrc(xSrc, ySrc);
   ::point_f64 pointDest(xDest, yDest);
   ::size_f64::size_f64(nDestWidth, nDestHeight);



   ::image_pointer pimage;
   if(imageWork == nullptr)
   {
   pimage = create_image(get_object());
   imageWork = pimage;
   }
   if(imageWork == nullptr)
   return false;
   if(!imageWork = create_image(::size_f64))
   return false;
   if(!imageWork.from(::point_f64(), pgraphicsSrc, pointSrc, ::size_f64))
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
   if(!imageWork4 = create_image(::size_f64))
   return false;


   imageWork4.Fill(255, 0, 0, 0);

   imageWork4.from(point_i32(maximum(0, m_pointAlphaBlend.x - xDest), maximum(0, m_pointAlphaBlend.y - yDest)),
   m_pimageAlphaBlend->get_graphics(), point_i32(maximum(0, xDest - m_pointAlphaBlend.x), maximum(0, yDest - m_pointAlphaBlend.y)), ::size_f64);

   imageWork.channel_multiply(::color::e_channel_alpha, imageWork4);


   keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


   return Application.m_visual.imaging().true_blend(this, pointDest, ::size_f64, imageWork.get_graphics(), pointSrc);


   }

   return ::AlphaBlend(get_handle1(), xDest, yDest,
   nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
   nSrcHeight, blend) != false;
   }*/


//   bool graphics::TransparentBlt(double xDest, double yDest, double dDestWidth, double dDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double dSrcWidth, double dSrcHeight, ::u32 crTransparent)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//
//      //return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != false;
//
//   }
//
//   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, u32 dwMode)
//   {
//
//      __throw(todo());
//
//      //ASSERT(get_handle1() != nullptr);
//      //
//      //return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != false;
//
//   }

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

   //inline color32_t graphics::GetDCBrushColor()
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetDCBrushColor(get_handle1());

   //}
   //inline color32_t graphics::SetDCBrushColor(const ::color::color & color)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::SetDCBrushColor(get_handle1(), crColor);

   //}

   //inline color32_t graphics::GetDCPenColor()
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetDCPenColor(get_handle1());

   //}
   //inline color32_t graphics::SetDCPenColor(const ::color::color & color)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::SetDCPenColor(get_handle1(), crColor);

   //}

#ifdef WINDOWS_DESKTOP
   /*
      inline bool graphics::GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc)
      {

         __throw(todo());

         //ASSERT(get_handle1() != nullptr);

         //return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != false;

      }
      */
#endif

   //inline bool graphics::GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer)
   //{

   //   __throw(todo());

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != false;

   //}

   //inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int cgi, double dMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32)
   //{

   //   __throw(todo());

   //   //ENSURE(LPSIZE32 != nullptr);
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, LPSIZE32) != false;

   //}


   //inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, int cgi, LPSIZE32 LPSIZE32)
   //{

   //   __throw(todo());

   //   //ENSURE(LPSIZE32 != nullptr);
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, LPSIZE32) != false;

   //}








#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(::size_f64 * psize)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(__is_valid_address(psize, sizeof(::size_f64)));
//
//      double dMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained ::map mode, ::map against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         DPtoLP(psize);
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         // ::map against logical inch for non-constrained mapping modes
//         int cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_VALID(this);
//            ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {
//            //            cxPerInch = afxData.cxPixelsPerInch;
//            //          cyPerInch = afxData.cyPixelsPerInch;
//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         psize->cx = psize->cx * HIMETRIC_INCH / cxPerInch;
//         psize->cy = psize->cy * HIMETRIC_INCH / cyPerInch;
//      }
//#endif
   }

   void graphics::HIMETRICtoDP(::size_f64 * psize)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(__is_valid_address(psize, sizeof(::size_f64)));
//
//      double dMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained ::map mode, ::map against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         LPtoDP(psize);
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         // ::map against logical inch for non-constrained mapping modes
//         int cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_VALID(this);
//            ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {
//            //            cxPerInch = afxData.cxPixelsPerInch;
//            //          cyPerInch = afxData.cyPixelsPerInch;
//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         psize->cx = psize->cx * cxPerInch / HIMETRIC_INCH;
//         psize->cy = psize->cy * cyPerInch / HIMETRIC_INCH;
//      }
//#endif
   }

   /*void graphics::LPtoHIMETRIC(LPSIZE32 LPSIZE32)
   {
      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));

      LPtoDP(LPSIZE32);
      DPtoHIMETRIC(LPSIZE32);
   }

   void graphics::HIMETRICtoLP(LPSIZE32 LPSIZE32)
   {
      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE_I32)));

      HIMETRICtoDP(LPSIZE32);
      DPtoLP(LPSIZE32);
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* graphics::GetHalftoneBrush(::layered * pobjectContext)
   {
      /*
      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
      if (gen_HalftoneBrush == nullptr)
      {
      ::u16 grayPattern[8];
      for (int i = 0; i < 8; i++)
      grayPattern[i] = (::u16)(0x5555 << (i & 1));
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


   //void graphics::DrawDragRect(const ::rectangle_i32 & rectangle, const ::size_f64& ::size_f64, const ::rectangle_i32 & rectLast, const ::size_f64& sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   ::exception::throw_not_implemented();

   //   /*
   //   ASSERT(__is_valid_address(rectangle, sizeof(::rectangle_f64), false));
   //   ASSERT(lpRectLast == nullptr ||
   //   __is_valid_address(lpRectLast, sizeof(::rectangle_f64), false));

   //   // first, determine the update region and select it
   //   ::draw2d::region rgnNew;
   //   ::draw2d::region rgnOutside, rgnInside;
   //   rgnOutside.CreateRectRgnIndirect(rectangle);
   //   const ::rectangle_i32 & rectangle = *rectangle;
   //   rectangle.inflate(-size.cx, -size.cy);
   //   rectangle.intersect(rectangle, rectangle);
   //   rgnInside.CreateRectRgnIndirect(rectangle);
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
   //   rectangle = *lpRectLast;
   //   rectangle.inflate(-sizeLast.cx, -sizeLast.cy);
   //   rectangle.intersect(rectangle, lpRectLast);
   //   rgnInside.SetRectRgn(rectangle);
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
   //   get_clip_box(&rectangle);
   //   pBrushOld = SelectObject(pBrushLast);
   //   PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);
   //   SelectObject(pBrushOld);
   //   pBrushOld = nullptr;
   //   }

   //   // draw into the update/new region
   //   SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
   //   get_clip_box(&rectangle);
   //   pBrushOld = SelectObject(pBrush);
   //   PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);

   //   // cleanup DC
   //   if (pBrushOld != nullptr)
   //   SelectObject(pBrushOld);
   //   SelectClipRgn(nullptr);

   //   */

   //}


   //bool graphics::fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
   //{

   //   return fill_rectangle(rectangle_f64(rectangle), color);

   //}


   //bool graphics::draw_3drect(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder)
   //{

   //   draw_3drect(rectangle_f64(rectangle), colorTopLeft, colorBottomRight, eborder);

   //}


   //void graphics::draw_3drect(const ::rectangle_f64 & rectangle,  const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder)
   //{

   //   double x = rectangle.left;
   //   double y = rectangle.top;
   //   double cx = ::width(rectangle);
   //   double cy = ::height(rectangle);

   //   if (eborder & e_border_top)
   //   {

   //      fill_solid_rect_dim(x, y, cx - 1.0, 1.0, colorTopLeft);

   //   }

   //   if (eborder & e_border_left)
   //   {

   //      fill_solid_rect_dim(x, y, 1.0, cy - 1.0, colorTopLeft);

   //   }

   //   if (eborder & e_border_right)
   //   {

   //      fill_solid_rect_dim(x + cx, y, -1.0, cy, colorBottomRight);

   //   }

   //   if (eborder & e_border_bottom)
   //   {

   //      fill_solid_rect_dim(x, y + cy, cx, -1.0, colorBottomRight);

   //   }

   //}


   bool graphics::DeleteDC()
   {

      return destroy();

      /* if(get_handle() == nullptr)
          return false;

       return ::DeleteDC(Detach()) != false;*/
   }


   //int graphics::StartDoc(const char * lpszDocName)
   //{

   //   __throw(todo());

   //   //DOCINFO di;
   //   //__memset(&di, 0, sizeof(DOCINFO));
   //   //di.cbSize = sizeof(DOCINFO);
   //   //di.lpszDocName = lpszDocName;
   //   //return StartDoc(&di);
   //}


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

      //double dRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   nRetVal = ::SetROP2(get_handle1(), nDrawMode);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetROP2(get_handle2(), nDrawMode);
      //return nRetVal;
   }

   bool graphics::set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode)
   {
      if(einterpolationmode == ::draw2d::e_interpolation_mode_nearest_neighbor)
      {
         m_bitmapinterpolationmode     = D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
         m_interpolationmode           = D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR;;
      }
      else if(einterpolationmode == ::draw2d::e_interpolation_mode_high_quality_bicubic)
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
      /*double dRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
      nRetVal = ::set_interpolation_mode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
      nRetVal = ::set_interpolation_mode(get_handle2(), nStretchMode);
      return nRetVal;*/
   }


   // color32_t graphics::SetTextColor(const ::color::color & color)
//   {
   //  return set_color(crColor);
   //const ::color::color & colorRetVal = m_colorColor;
   //m_colorColor = crColor;
   /*      const ::color::color & colorRetVal = CLR_INVALID;
   if(get_handle1() != nullptr && get_handle1() != get_handle2())
   crRetVal = ::SetTextColor(get_handle1(), crColor);
   if(get_handle2() != nullptr)
   crRetVal = ::SetTextColor(get_handle2(), crColor);*/
   //return crRetVal;
   //}

   int graphics::SetGraphicsMode(int iMode)
   {

      __throw(todo());

      //double dRetVal = 0;
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

   //bool graphics::SetWorldTransform(const XFORM* pXform)
   //{

   //   __throw(todo());

   //   //bool nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //{
   //   //   nRetVal = ::SetWorldTransform(get_handle1(), pXform) != false;
   //   //}
   //   //if(get_handle2() != nullptr)
   //   //{
   //   //   nRetVal = ::SetWorldTransform(get_handle2(), pXform) != false;
   //   //}
   //   //return nRetVal;
   //}

   //bool graphics::ModifyWorldTransform(const XFORM* pXform,u32 iMode)
   //{

   //   __throw(todo());

   //   //bool nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //{
   //   //   nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != false;
   //   //}
   //   //if(get_handle2() != nullptr)
   //   //{
   //   //   nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != false;
   //   //}
   //   //return nRetVal;
   //}


   int graphics::SetMapMode(int nMapMode)
   {

      return 0;

   }


   point_f64 graphics::SetViewportOrg(double x, double y)
   {

      return ::draw2d::graphics::SetViewportOrg(x, y);

   }


   point_f64 graphics::OffsetViewportOrg(double dWidth, double dHeight)
   {

      return ::draw2d::graphics::OffsetViewportOrg(dWidth, dHeight);

   }


   ::size_f64 graphics::SetViewportExt(double x, double y)
   {

      __throw(todo());

   }


   ::size_f64 graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
   {

      return ::draw2d::graphics::ScaleViewportExt(xNum, xDenom, yNum, yDenom);

   }


   point_f64 graphics::SetWindowOrg(double x, double y)
   {

      __throw(todo());

   }


   point_f64 graphics::offset_window_org(double dWidth, double dHeight)
   {

      __throw(todo());

   }


   ::size_f64 graphics::set_window_ext(double x, double y)
   {

      __throw(todo());

   }


   ::size_f64 graphics::scale_window_ext(double xNum, double xDenom, double yNum, double yDenom)
   {

      __throw(todo());

   }


   int graphics::get_clip_box(::rectangle_f64 * prectangle)
   {
      return 0;
      //__throw(todo());

      //return ::get_clip_box(get_handle1(), rectangle);
   }

   
   ::e_status graphics::reset_clip()
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


   ::e_status graphics::add_shapes(const shape_array& shapea)
   {

      for (int i = 0; i < shapea.get_count(); i++)
      {

         if (i + 1 < shapea.get_count())
         {

            if (shapea[i + 1]->eshape() == e_shape_intersect_clip)
            {

               switch (shapea[i]->eshape())
               {
               //case e_shape_rect:
               //   intersect_clip(shapea[i]->shape < ::rectangle_i32>());
               //   break;
               case e_shape_rectd:
                  intersect_clip(shapea[i]->shape < ::rectangle_f64>());
                  break;
               //case e_shape_oval:
               //   intersect_clip(shapea[i]->shape < ::oval>());
               //   break;
               case e_shape_ovald:
                  intersect_clip(shapea[i]->shape < ::ovald>());
                  break;
               //case e_shape_polygon:
               //   intersect_clip(shapea[i]->shape < ::polygon_i32>());
               //   break;
               case e_shape_polygond:
                  intersect_clip(shapea[i]->shape < ::polygon_f64>());
                  break;

               }

               i++;

            }

         }

      }

      return ::success;

   }


   //::e_status graphics::intersect_clip(const ::rectangle_f64 & rectangle)
   //{

   //   ::draw2d::lock draw2dlock;

   //   {

   //      ::draw2d::region_pointer pregion(e_create);

   //      auto rectClip = rectangle_i32 + m_pointAddShapeTranslate;

   //      pregion->create_rect(rectClip);

   //      D2D1::Matrix3x2F m = {};

   //      m_prendertarget->GetTransform(&m);

   //      m_pstate->m_sparegionClip.add(pregion);

   //      m_pstate->m_maRegion.add(m);

   //      ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

   //      auto layerparameters = D2D1::LayerParameters(
   //         D2D1::InfiniteRect(),
   //         pgeometry);

   //      m_prendertarget->PushLayer(layerparameters, nullptr);

   //   }

   //   return 0;

   //}


   ::e_status graphics::intersect_clip(const ::rectangle_f64 & rectangle)
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::region_pointer pregion(e_create);

      auto rectClip = rectangle + m_pointAddShapeTranslate;

      pregion->create_rect(rectClip);

      D2D1::Matrix3x2F m = {};

      m_prendertarget->GetTransform(&m);

      m_pstate->m_sparegionClip.add(pregion);

      m_pstate->m_maRegion.add(m);

      ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

      auto layerparameters = D2D1::LayerParameters(
         D2D1::InfiniteRect(),
         pgeometry);

      m_prendertarget->PushLayer(layerparameters, nullptr);

      return 0;


   }




   //::e_status graphics::intersect_clip(const ::oval& oval)
   //{

   //   ::draw2d::lock draw2dlock;

   //   {

   //      ::draw2d::region_pointer pregion(e_create);

   //      pregion->create_oval(oval);

   //      D2D1::Matrix3x2F m = {};

   //      m_prendertarget->GetTransform(&m);

   //      m_pstate->m_sparegionClip.add(pregion);

   //      m_pstate->m_maRegion.add(m);

   //      ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

   //      m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

   //   }

   //   return 0;


   //}


   ::e_status graphics::intersect_clip(const ::ovald& oval)
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


   //::e_status graphics::intersect_clip(const ::polygon_i32& polygon_i32)
   //{

   //   ::draw2d::lock draw2dlock;

   //   {

   //      ::draw2d::region_pointer pregion(e_create);

   //      pregion->create_polygon(polygon_i32.get_data(), (::i32) polygon_i32.get_count(), ::draw2d::fill_mode_winding);

   //      D2D1::Matrix3x2F m = {};

   //      m_prendertarget->GetTransform(&m);

   //      m_pstate->m_sparegionClip.add(pregion);

   //      m_pstate->m_maRegion.add(m);

   //      ID2D1Geometry* pgeometry = (ID2D1Geometry*)pregion->get_os_data(this);

   //      m_prendertarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pgeometry), nullptr);

   //   }

   //   return 0;


   //}


   ::e_status graphics::intersect_clip(const ::polygon_f64& polygon_i32)
   {

      ::draw2d::lock draw2dlock;

      {

         ::draw2d::region_pointer pregion(e_create);

         pregion->create_polygon(polygon_i32.get_data(), (::i32) polygon_i32.get_count(), ::draw2d::fill_mode_winding);

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

   //   ///*      double dRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //nRetVal = ::SelectClipRgn(get_handle1(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
   //   //if(get_handle2() != nullptr)
   //   //nRetVal = ::SelectClipRgn(get_handle2(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
   //   //return nRetVal;*/
   //}

   //int graphics::ExcludeClipRect(double x1, double y1, double x2, double y2)
   //{

   //   ::draw2d::lock draw2dlock;

   //   {

   //      ::u32 uMax = m_pdevicecontext->GetMaximumBitmapSize();

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

   //int graphics::ExcludeClipRect(const ::rectangle_i32 & rectangle)
   //{

   //   return ExcludeClipRect(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

   //}



   //int graphics::OffsetClipRgn(double x, double y)
   //{

   //   __throw(todo());

   //}


   //int graphics::OffsetClipRgn(const ::size_f64& ::size_f64)
   //{

   //   __throw(todo());

   //}


   ::u32 graphics::SetTextAlign(::u32 nFlags)
   {

      __throw(todo());

   }


   //int graphics::SetTextJustification(double dBreakExtra, double dBreakCount)
   //{

   //   __throw(todo());

   //}


   //int graphics::SetTextCharacterExtra(double dCharExtra)
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

         m_etextrenderinghintDevice = m_ewritetextrendering;

         switch (m_etextrenderinghintDevice)
         {
         case ::write_text::e_rendering_anti_alias:

            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

            break;

         case ::write_text::e_rendering_anti_alias_grid_fit:
            
            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

            break;

         case ::write_text::e_rendering_single_bit_per_pixel:
            
            m_prendertarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

            break;

         case ::write_text::e_rendering_clear_type_grid_fit:

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

      return m_puserinteraction->get_oswindow();

   }


   u32 graphics::GetLayout()
   {

      __throw(todo());

   }


   u32 graphics::SetLayout(u32 dwSetLayout)
   {

      __throw(todo());

   }


   bool graphics::ArcTo(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      __throw(todo());

   }


   //int graphics::SetArcDirection(double dArcDirection)
   //{

   //   __throw(todo());

   //}


   bool graphics::polydraw(const ::point_f64* ppoints, const byte* lpTypes, count nCount)
   {

      __throw(todo());

   }


   bool graphics::polyline_to(const ::point_f64* ppoints, count nCount)
   {

      __throw(todo());

   }


   bool graphics::poly_bezier_to(const ::point_f64* ppoints, count nCount)
   {

      __throw(todo());

   }


   bool graphics::SelectClipPath(int nMode)
   {

      //__throw(todo());

      return false;

   }


   //int graphics::SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine)
   //{

   //   return 0;

   //}

   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback
#ifdef WINDOWS_DESKTOP
   int CALLBACK __enum_meta_file_procedure(HDC hDC,
                                           HANDLETABLE* pHandleTable, METARECORD* pMetaRec, double dHandles, LPARAM lParam)
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
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->set_window_ext(
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
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->scale_window_ext(
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
         
         brush->create_solid(*(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
         
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->set(brush);

      }
      break;
      case META_SETTEXTCOLOR:
      {
         ::draw2d::brush_pointer brush(e_create);
         brush->create_solid(*(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
         (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->set(brush);
      }
      break;

      // need to watch out for SelectObject(HFONT), for custom font mapping
      case META_SELECTOBJECT:
      {
         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
         ::u32 nObjType = GetObjectType(hObject);
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
            // play back as graphics::SelectObject(::write_text::font*)
            //               (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->SelectObject(::draw2d_direct2d::font::from_handle_dup(pgraphics->get_context_application(), (HFONT)hObject));
            __throw(not_implemented());
            break;  // don't play the default record
         }
      }
      // fall through...

      default:
         //::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
         break;
      }

      return 1;
   }
#endif


   //bool graphics::PlayMetaFile(HMETAFILE hMF)
   //{

   //   __throw(todo());

   //}


   void graphics::LPtoDP(::size_f64 * psize)
   {

      ASSERT(__is_valid_address(psize, sizeof(::size_f64)));

      ::size_f64 sizeWinExt = GetWindowExt();
      ::size_f64 sizeVpExt = GetViewportExt();
      psize->cx = psize->cx * abs(sizeVpExt.cx) / abs(sizeWinExt.cx);
      psize->cy = psize->cy * abs(sizeVpExt.cy) / abs(sizeWinExt.cy);

   }


   void graphics::DPtoLP(::size_f64 * psize)
   {
   
      ASSERT(__is_valid_address(psize, sizeof(::size_f64)));

      ::size_f64 sizeWinExt = GetWindowExt();
      ::size_f64 sizeVpExt = GetViewportExt();
      psize->cx = psize->cx * abs(sizeWinExt.cx) / abs(sizeVpExt.cx);
      psize->cy = psize->cy * abs(sizeWinExt.cy) / abs(sizeVpExt.cy);

   }


   //bool graphics::draw_text(const char * lpszString, strsize nCount, const ::rectangle_i32 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   //{

   //   if (nCount < 0)
   //   {

   //      nCount = strlen(lpszString) + nCount + 1;

   //   }

   //   return draw_text(string(lpszString, nCount), rectangle, nFormat);

   //}


   bool graphics::draw_text(const string & str,const ::rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
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

      if (ealign & e_align_right)
      {

         pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

      }
      else if (ealign & e_align_horizontal_center)
      {

         pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

      }
      else
      {

         pfont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

      }

      if (ealign & e_align_bottom)
      {

         pfont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

      }
      else if (ealign & e_align_vertical_center)
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

         D2D1_RECT_F rectangle_f32 = D2D1::RectF((FLOAT)rectangle.left, (FLOAT)rectangle.top, (FLOAT)rectangle.right, (FLOAT)rectangle.bottom);

         m_prendertarget->DrawText(text.m_wstr, (::u32)text.m_wstr.get_length(), pfont, &rectangle_f32, pbrush);

      }
      else
      {
         D2D1::Matrix3x2F m;

         m_prendertarget->GetTransform(&m);

         D2D1::Matrix3x2F mOriginal(m);

         D2D1_RECT_F rectangle_f32 = D2D1::RectF((FLOAT)0, (FLOAT)0, (FLOAT)width(rectangle), (FLOAT)height(rectangle));

         m = m * D2D1::Matrix3x2F::Translation((FLOAT)rectangle.left, (FLOAT)rectangle.top);

         m = m * D2D1::Matrix3x2F::Scale((FLOAT)m_pfont->m_dFontWidth, 1.f);

         m_prendertarget->SetTransform(&m);

         m_prendertarget->DrawText(text.m_wstr, (::u32)text.m_wstr.get_length(), pfont, &rectangle_f32, pbrush);

         m_prendertarget->SetTransform(&mOriginal);

      }

      return 1;

   }


   size_f64 graphics::GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex)
   {

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      size_f64 sz;

      bool bOk = GetTextExtent(sz, lpszString, nCount, iIndex);

      if (!bOk)
      {

         return ::size_f64(0, 0);

      }
      else
      {

         return ::size_f64(sz.cx, sz.cy);

      }

   }


   size_f64 graphics::GetTextExtent(const string & str)
   {
      size_f64 s;

      if (!GetTextExtent(s, str))
      {

         return ::size_f64(0, 0);

      }

      return s;

   }


   ::size_f64 graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
   {

      __throw(todo());

   }


   ::size_f64 graphics::GetOutputTextExtent(const string & str)
   {

      __throw(todo());

   }


   bool graphics::GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount, strsize iIndex)
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

      ::u32 uLength = (::u32)text.m_wstr.get_length();

      hr = System.draw2d()->direct2d()->dwrite_factory()->CreateTextLayout(
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

      size.cx = (::i32) (m.widthIncludingTrailingWhitespace  * m_pfont->m_dFontWidth);

      size.cy = (::i32) m.height;

      text.m_size = size;

      text.m_bSize = true;

      return true;

   }


   bool graphics::GetTextExtent(size_f64 & size, const char * lpszString, strsize nCount)
   {

      if (nCount < 0)
      {

         nCount = strlen(lpszString) + nCount + 1;

      }

      return GetTextExtent(size, lpszString, nCount, nCount);

   }


   bool graphics::GetTextExtent(size_f64 & size, const string & str)
   {

      return GetTextExtent(size, str, str.get_length());

   }


   bool graphics::fill_rectangle(const ::rectangle_f64 & rectParam, const ::color::color & color)
   {

      if (!m_pdevicecontext)
      {

         return false;

      }

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(color);

      auto pbrush = br->get_os_data < ID2D1Brush * >(this);

      D2D1_RECT_F rectangle;

      __copy(rectangle, rectParam);

      defer_primitive_blend();

      m_pdevicecontext->FillRectangle(&rectangle, pbrush);

      return true;

   }


   //bool graphics::text_out(double x, double y, const block & block)
   //{

   //   if (block.is_empty())
   //   {

   //      return false;

   //   }

   //   return ::draw2d::graphics::text_out((double)x, (double)y, string(lpszString, nCount));

   //}


   bool graphics::TextOutRaw(double x, double y, const block & block)
   {

      if (block.is_empty())
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

      auto & text = m_pfont->m_mapText[block];

      ::size_f64 sizeText;
         
      if (text.m_bSize)
      {

         sizeText = text.m_size;

      }
      else
      {

         sizeText = GetTextExtent(block);

      }

      D2D1_RECT_F rectangle_f32 = D2D1::RectF((FLOAT) 0, (FLOAT)0, (FLOAT)(0 + sizeText.cx * 2), (FLOAT)(0 + sizeText.cy * 2));

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

      __zero(trim);

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

         rectangle_f32.left += (FLOAT)x;
         rectangle_f32.top += (FLOAT)y;
         rectangle_f32.right += (FLOAT)x;
         rectangle_f32.bottom += (FLOAT)y;

      }

      if (m_pfont->m_dFontWidth != 1.0)
      {

         m_prendertarget->SetTransform(&m);

      }

      const widechar * lpcwsz = text.m_wstr;

      strsize uiLen = text.m_wstr.get_length();

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      if(lpcwsz != nullptr && uiLen > 0)
      {

         m_prendertarget->DrawText(lpcwsz,(int) uiLen,pfont,&rectangle_f32,pbrush);

      }

      if (m_pfont->m_dFontWidth != 1.0)
      {

         m_prendertarget->SetTransform(mOriginal);

      }

      return true;

   }


   bool graphics::draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen)
   {

      D2D1_POINT_2F p1;

      p1.x = (FLOAT) x1;

      p1.y = (FLOAT) y1;

      D2D1_POINT_2F p2;

      p2.x = (FLOAT) x2;

      p2.y = (FLOAT) y2;

      ID2D1Brush * pbrush = m_ppen->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      defer_primitive_blend();

      m_prendertarget->DrawLine(p1, p2, pbrush, (FLOAT)(dynamic_cast < ::draw2d_direct2d::pen * > (m_ppen.m_p))->m_dWidth);

      m_point.x = x2;

      m_point.y = y2;

      return true;

   }


   bool graphics::line_to(double x, double y)
   {

      D2D1_POINT_2F p1;

      __copy(p1, m_point);

      D2D1_POINT_2F p2;

      p2.x = (FLOAT) x;

      p2.y = (FLOAT) y;

      ID2D1Brush * pbrush =  m_ppen->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      defer_primitive_blend();

      FLOAT fWidth = (FLOAT)(dynamic_cast <::draw2d_direct2d::pen *> (m_ppen.m_p))->m_dWidth;

      m_prendertarget->DrawLine(p1, p2, pbrush, fWidth);

      m_point.x = x;

      m_point.y = y;

      return true;

   }


   bool graphics::on_begin_draw()
   {

      reset_clip();

      ::draw2d::graphics::on_begin_draw();

      m_ealphamodeDevice = ::draw2d::alpha_mode_none;

      set_alpha_mode(::draw2d::alpha_mode_blend);

      return true;

   }


   bool graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
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


//#ifdef WINDOWS_DESKTOP
//
//
//   bool graphics::attach_hdc(HDC hdc)
//   {
//
//      HWND hwnd = ::WindowFromDC(hdc);
//
//      if (hwnd == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::rectangle_i32 rectClient;
//
//      ::GetClientRect(hwnd, rectClient);
//
//      // Create a DC render target.
//      D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
//                                            D2D1_RENDER_TARGET_TYPE_DEFAULT,
//                                            D2D1::PixelFormat(
//                                            DXGI_FORMAT_B8G8R8A8_UNORM,
//                                            D2D1_ALPHA_MODE_IGNORE),
//                                            0,
//                                            0,
//                                            D2D1_RENDER_TARGET_USAGE_NONE,
//                                            D2D1_FEATURE_LEVEL_DEFAULT
//                                            );
//
//      HRESULT hr = ::draw2d_direct2d::plugin::d2d1_factory1()->CreateDCRenderTarget(&props,&m_pdcrendertarget);
//
//      if (FAILED(hr))
//      {
//
//         return false;
//
//      }
//
//      hr = m_pdcrendertarget->BindDC(hdc, rectClient);
//
//      m_pdcrendertarget.As(&m_prendertarget);
//
//      m_hdcAttach = hdc;
//
//      return true;
//
//   }
//
//
//   HDC graphics::detach_hdc()
//   {
//
//      if (m_hdcAttach == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      HDC hdc = m_hdcAttach;
//
//      m_hdcAttach = nullptr;
//
//      return hdc;
//   }
//
//#endif


   bool graphics::blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle)
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


   ::e_status graphics::clear_current_point()
   {

      return ::success;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      return draw_path(ppath, m_ppen);

   }


   bool graphics::draw_path(ID2D1PathGeometry * pgeometry, ::draw2d::pen * ppen)
   {

      ::ID2D1Brush * pbrush = ppen->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      m_prendertarget->DrawGeometry(pgeometry, pbrush, (FLOAT)ppen->m_dWidth);

      return true;

   }


   bool graphics::fill_path(ID2D1PathGeometry * pgeometry, ::draw2d::brush * pbrushParam)
   {

      ::ID2D1Brush * pbrush = pbrushParam->get_os_data < ID2D1Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      m_prendertarget->FillGeometry(pgeometry, pbrush);

      return true;

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      __stack(m_bOutline, true);

      ppath->set_modified();

      ID2D1PathGeometry * pgeometry = ppath->get_os_data < ID2D1PathGeometry * >(this);

      defer_primitive_blend();

      if(pgeometry != nullptr)
      {

         draw_path(pgeometry, ppen);

      }

      for(index i = 0; i < ppath->m_shapea.get_size(); i++)
      {

         if(ppath->m_shapea[i]->eshape() == e_shape_text_out)
         {

            draw(ppath->m_shapea[i]->shape < ::text_out>(), ppen);

         }
         else if (ppath->m_shapea[i]->eshape() == e_shape_draw_text)
         {

            draw(ppath->m_shapea[i]->shape < ::draw_text>(), ppen);

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

      __stack(m_bOutline, false);

      ppath->set_modified();

      ID2D1PathGeometry * pgeometry = ppath->get_os_data < ID2D1PathGeometry * >(this);

      defer_primitive_blend();

      if (pgeometry != nullptr)
      {

         fill_path(pgeometry, m_pbrush);

      }

      for (index i = 0; i < ppath->m_shapea.get_size(); i++)
      {

         if (ppath->m_shapea[i]->eshape() == ::e_shape_text_out)
         {

            fill(ppath->m_shapea[i]->shape < ::text_out >(), m_pbrush);

         }
         else if (ppath->m_shapea[i]->eshape() == ::e_shape_draw_text)
         {

            fill(ppath->m_shapea[i]->shape < ::draw_text >(), m_pbrush);

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

      for (index i = 0; i < ppath->m_shapea.get_size(); i++)
      {

         if (ppath->m_shapea[i]->eshape() == ::e_shape_text_out)
         {

            fill(ppath->m_shapea[i]->shape < ::text_out >(), pbrushParam);

         }
         else if (ppath->m_shapea[i]->eshape() == ::e_shape_draw_text)
         {

            fill(ppath->m_shapea[i]->shape < ::draw_text >(), pbrushParam);

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


   bool graphics::draw(const ::text_out & textout, ::draw2d::pen * ppen)
   {

      wstring szOutline(textout.m_strText);

      IDWriteTextFormat * pformat = textout.m_pfont->get_os_data < IDWriteTextFormat * > (this);

      IDWriteFactory * pfactory = System.draw2d()->direct2d()->dwrite_factory();

      IDWriteTextLayout * playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
                   szOutline,      // The string to be laid out and formatted.
                   (::u32) szOutline.length(),  // The length of the string.
                   pformat,  // The text format to apply to the string (contains font information, etc).
                   4096,         // The width of the on_layout box.
                   4096,        // The height of the on_layout box.
                   &playout  // The IDWriteTextLayout interface pointer.
                   );

      if(playout == nullptr)
      {

         return false;

      }

      CustomTextRenderer renderer(::draw2d_direct2d::plugin::d2d1_factory1(),m_prendertarget.Get(),ppen->get_os_data < ID2D1Brush * >(this));

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      playout->Draw(nullptr, &renderer, (FLOAT) textout.m_point.x, (FLOAT) textout.m_point.y);

      return true;

   }


   bool graphics::fill(const ::text_out & textout, ::draw2d::brush * pbrush)
   {

      wstring szOutline(textout.m_strText);

      IDWriteTextFormat * pformat = textout.m_pfont->get_os_data < IDWriteTextFormat * >(this);

      IDWriteFactory * pfactory = System.draw2d()->direct2d()->dwrite_factory();

      IDWriteTextLayout * playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
                   szOutline,      // The string to be laid out and formatted.
                   (::u32) szOutline.length(),  // The length of the string.
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

         CustomTextRenderer renderer(::draw2d_direct2d::plugin::d2d1_factory1(), m_prendertarget.Get(), nullptr, posbrush);

         defer_text_primitive_blend();

         defer_text_rendering_hint();

         playout->Draw(nullptr, &renderer, (FLOAT)textout.m_point.x, (FLOAT)textout.m_point.y);

      }

      return true;

   }


   bool graphics::draw(const ::draw_text & drawtext, ::draw2d::pen* ppen)
   {

      wstring szOutline(drawtext.m_strText);

      IDWriteTextFormat* pformat = drawtext.m_pfont->get_os_data < IDWriteTextFormat* >(this);

      IDWriteFactory* pfactory = System.draw2d()->direct2d()->dwrite_factory();

      IDWriteTextLayout* playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
         szOutline,      // The string to be laid out and formatted.
         (::u32)szOutline.length(),  // The length of the string.
         pformat,  // The text format to apply to the string (contains font information, etc).
         4096,         // The width of the on_layout box.
         4096,        // The height of the on_layout box.
         &playout  // The IDWriteTextLayout interface pointer.
      );

      if (playout == nullptr)
      {

         return false;

      }

      CustomTextRenderer renderer(::draw2d_direct2d::plugin::d2d1_factory1(), m_prendertarget.Get(), ppen->get_os_data < ID2D1Brush* >(this));

      defer_text_primitive_blend();

      defer_text_rendering_hint();

      playout->Draw(nullptr, &renderer, (FLOAT)drawtext.m_rectangle.left, (FLOAT)drawtext.m_rectangle.top);

      return true;

   }


   bool graphics::fill(const ::draw_text & drawtext, ::draw2d::brush* pbrush)
   {

      wstring szOutline(drawtext.m_strText);

      IDWriteTextFormat* pformat = drawtext.m_pfont->get_os_data < IDWriteTextFormat* >(this);

      IDWriteFactory* pfactory = System.draw2d()->direct2d()->dwrite_factory();

      IDWriteTextLayout* playout = nullptr;

      HRESULT hr = pfactory->CreateTextLayout(
         szOutline,      // The string to be laid out and formatted.
         (::u32)szOutline.length(),  // The length of the string.
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

         CustomTextRenderer renderer(::draw2d_direct2d::plugin::d2d1_factory1(), m_prendertarget.Get(), nullptr, posbrush);

         defer_text_primitive_blend();

         defer_text_rendering_hint();

         playout->Draw(nullptr, &renderer, (FLOAT)drawtext.m_rectangle.left, (FLOAT)drawtext.m_rectangle.top);

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


   //void graphics::enum_fonts(::write_text::font_enum_item_array & itema)
   //{


   //}


   //void graphics::set_direct2d_plugin(::draw2d_direct2d::plugin * pplugin)
   //{

   //   System.draw2d()->direct2d() = pplugin;

   //}


} // namespace draw2d_direct2d





