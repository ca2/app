#include "framework.h"
#include "_vulkan.h"
#include "draw2d.h"
#include "pen.h"
#include "font.h"
#include "brush.h"
#include "image.h"
#include "color.h"
#include <glm/glm.hpp>
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "acme/platform/application.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/gpu/cpu_buffer.h"
#include "aura/graphics/gpu/render.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "aura/user/user/interaction.h"
#include "windowing_win32/window.h"


#include <math.h>
#include <dwmapi.h>
////#include <vk/freeglut.h>
//#define VKAD_GLAPI_EXPORT

//#include "vkad_wgl.h"
////#define WGL_CONTEXT_FLAGS_ARB 0X2094
//#define WGL_CONTEXT_COREPROFILE_BIT_ARB 0x00000001
//#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

//int  vulkan_init();


//HGLRC initialize_vulkan_version(HDC hdc, int iMajor, int iMinor);



namespace vulkan
{

#include "line1.h"

}


BOOL CALLBACK draw2d_vulkan_EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,unsigned int FontType,LPVOID p);


class draw2d_vulkan_enum_fonts
{
public:


   ::write_text::font_enumeration_item_array& m_itema;


   draw2d_vulkan_enum_fonts(::write_text::font_enumeration_item_array& itema):
      m_itema(itema)
   {

   }


};


namespace draw2d_vulkan
{

   //ATOM class_atom = NULL;

   graphics * thread_graphics()
   {

      return ::get_task()->payload("draw2d_vulkan::graphics").cast < graphics >();

   }

   void thread_graphics(graphics * pgraphics)
   {

      ::get_task()->payload("draw2d_vulkan::graphics") = pgraphics;

   }


   graphics::graphics()
   {

      //m_hrc = nullptr;
      //m_hwnd = nullptr;
      //m_hglrc = nullptr;
      m_pointTranslate = ::int_point();
      m_bPrinting = false;
      m_pimageAlphaBlend = nullptr;
      m_size.set(0, 0);
      //m_hdc = nullptr;
      //m_hdcGraphics = nullptr;
      m_ewritetextrendering = ::write_text::e_rendering_anti_alias_grid_fit;
      m_dFontFactor = 1.0;

   }


   //void graphics::assert_ok() const
   //{

   //   object::assert_ok();

   //}


   //void graphics::dump(dump_context& dumpcontext) const
   //{
   //   
   //   object::dump(dumpcontext);

   //   dumpcontext << "m_hdc = " << (iptr) m_hdc;
   //   dumpcontext << "\nm_hAttribDC = " << (iptr) m_hdc;
   //   dumpcontext << "\nm_bPrinting = " << m_bPrinting;

   //   dumpcontext << "\n";

   //}


   graphics::~graphics()
   {

      //vulkan_delete_offscreen_buffer();

      DeleteDC();

   }

#ifdef _DEBUG

   long long graphics::increment_reference_count()
   {

      return ::particle::increment_reference_count();

   }


   long long graphics::decrement_reference_count()
   {

      return ::particle::decrement_reference_count();

   }


#endif

   //bool graphics::IsPrinting() const
   //{

   //   return m_bPrinting;

   //}


   bool graphics::CreateDC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName, const char * lpszOutput, const void* lpInitData)
   {
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
      return false;
   }


   bool graphics::CreateIC(const ::scoped_string & lpszDriverName, const ::scoped_string & lpszDeviceName, const char * lpszOutput, const void* lpInitData)
   {
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
      return false;
   }


   void graphics::create_memory_graphics(const ::int_size & sizeParam)
   {

      ::int_size size(sizeParam);

      if (sizeParam.is_empty())
      {

         size = { 1920, 1080 };

      }

      vulkan_create_offscreen_buffer(size);

   }


   void graphics::create_window_graphics(::windowing::window * pwindow)
   {
      
      m_pwindow = pwindow;

      vulkan_defer_create_window_context(pwindow);

      set_ok_flag();

   }


   void graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      vulkan_create_offscreen_buffer({ 1920, 1080 });
      //vulkan_create_offscreen_buffer(pgraphics->m_pimage->size());

   }


   bool graphics::vulkan_create_offscreen_buffer(const ::int_size & size)
   {

      //if (!draw2d_vulkan()->m_pvulkancontext) {
      //   informationf("MS GDI - RegisterClass failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}


       if (!m_pgpucontext)
       {

           auto psystem = system();

           auto pgpu = psystem->get_gpu();

           m_pgpucontext = pgpu->create_context(this);

       }



      if (!m_pgpucontext)
      {
         return false;
         //auto psystem = system();

         //auto pgpu = psystem->get_gpu();

         //m_pgpucontextVulkan = pgpu->create_context(this);

         //if (m_pgpucontextVulkan)
         //{

         //   m_pgpucontextVulkan->initialize(this);

         //}

      }

      //if (__defer_construct(m_pgpucontextVulkan))
      //{

         m_pgpucontext->create_offscreen_buffer(size);

      //}

      //LPCTSTR lpClassName = L"draw2d_vulkan_offscreen_buffer_window";
      //LPCTSTR lpWindowName = L"draw2d_vulkan_offscreen_buffer_window";
      ////unsigned int dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
      //unsigned int dwExStyle = 0;
      //unsigned int dwStyle = WS_OVERLAPPEDWINDOW;
      //dwStyle |= WS_POPUP;
      ////dwStyle |= WS_VISIBLE;
      ////dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
      //dwStyle &= ~WS_CAPTION;
      ////dwStyle = 0;
      //dwStyle &= ~WS_THICKFRAME;
      //dwStyle &= ~WS_BORDER;
      //int x = 0;
      //int y = 0;
      //int nWidth = size.cx();
      //int nHeight = size.cy();
      //HWND hWndParent = nullptr;
      //HMENU hMenu = nullptr;
      /////HINSTANCE hInstance = psystem->m_hinstance;
      //LPVOID lpParam = nullptr;

      ////HWND window = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y,  nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
      //HWND window = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, nullptr, lpParam);

      //if (window == nullptr) 
      //{
      //   informationf("MS GDI - CreateWindow failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //// create WGL context, make current

      //PIXELFORMATDESCRIPTOR pixformat;
      //int chosenformat;
      //HDC hdc = GetDC(window);
      //if (hdc == nullptr)
      //{
      //   informationf("MS GDI - GetDC failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //ZeroMemory(&pixformat, sizeof(pixformat));
      //pixformat.nSize = sizeof(pixformat);
      //pixformat.nVersion = 1;
      //pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_VULKAN | PFD_DOUBLEBUFFER;
      //pixformat.iPixelType = PFD_TYPE_RGBA;
      //pixformat.cColorBits = 24;
      //pixformat.cAlphaBits = 8;
      //pixformat.cDepthBits = 24;
      //pixformat.cStencilBits = 8;

      //chosenformat = ChoosePixelFormat(hdc, &pixformat);
      //if (chosenformat == 0) 
      //{
      //   informationf("MS GDI - ChoosePixelFormat failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);
      //if (!spfok) 
      //{
      //   informationf("MS GDI - SetPixelFormat failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}

      //HGLRC hglrcTime = wglCreateContext(hdc);
      //if (hglrcTime == nullptr)
      //{
      //   informationf("MS WGL - wglCreateContext failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   ReleaseDC(m_hwnd, m_hdc);
      //   return false;
      //}

      //bool okMakeCurrent = wglMakeCurrent(hdc, hglrcTime);
      //if (!okMakeCurrent)
      //{
      //   informationf("MS WGL - wglMakeCurrent failed");
      //   informationf("last-error code: %d\n", GetLastError());
      //   return false;
      //}
      ////vkfwInit();
      //// ... <snip> ... setup a window and a context
      //
      //auto wglCurrentContext = wglGetCurrentContext();

      //// Load all Vulkan functions using the vkfw loader function
      //// If you use SDL you can use: https://wiki.libsdl.org/SDL_GL_GetProcAddress
      ////if (!vkadLoadGLLoader((VKADloadproc)vkfwGetProcAddress)) {
      ////   std::cout << "Failed to initialize Vulkan context" << std::endl;
      ////   return -1;
      ////}
      //if (!vkadLoadWGL(hdc))
      //{
      //   // Problem: vkewInit failed, something is seriously wrong.
      //   informationf("vkadLoadWGL failed");
      //   //return false;
      //   //throw resource_exception();

      //   return false;

      //}
      //int attribs[] =
      //{
      //   WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      //   WGL_CONTEXT_MINOR_VERSION_ARB, 1,
      //   WGL_CONTEXT_FLAGS_ARB, 0,
      //   WGL_CONTEXT_PROFILE_MASK_ARB,
      //   WGL_CONTEXT_COREPROFILE_BIT_ARB, 0
      //};

      ////PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
      ////wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

      //auto hglrc =  wglCreateContextAttribsARB(hdc, 0, attribs);
      //wglMakeCurrent(nullptr, nullptr);
      //wglDeleteContext(hglrcTime);
      //   wglMakeCurrent(hdc, m_hglrc);
      ////draw2d_vulkan()->defer_initialize_glew();
      //
      ////draw2d_vulkan()->defer_initialize_glew();


      //m_hwnd = window;
      //m_hdc = hdc;
      //m_hglrc = hglrc;
      //m_size = size;

      bool bYSwap = m_papplication->m_bUseDraw2dProtoWindow;

      ::vulkan::resize(size, bYSwap);

      return true;

   }


   bool graphics::vulkan_delete_offscreen_buffer()
   {

      //if (m_hglrc == NULL && m_hdc == NULL && m_hwnd == NULL)
      //{

      //   return true;

      //}

      //wglMakeCurrent(nullptr, nullptr);
      //wglDeleteContext(m_hglrc);
      //::ReleaseDC(m_hwnd, m_hdc);
      //::DestroyWindow(m_hwnd);
      m_size.set(0, 0);
      //m_hglrc = NULL;
      //m_hwnd = NULL;
      //m_hdc = NULL;
      return true;

   }


   bool graphics::vulkan_defer_create_window_context(::windowing::window * pwindow)
   {

      //if (!m_pgpucontext)
      //{

      //   return false;

      //}


       if (!m_pgpucontext)
       {

           auto psystem = system();

           auto pgpu = psystem->get_gpu();

           m_pgpucontext = pgpu->create_context(this);

       }




      m_pgpucontext->defer_create_window_context(pwindow);

//      ::vulkan::resize(size);

      return true;

   }



   int graphics::ExcludeUpdateRgn(::user::interaction_base * pwindow)
   {
      // ASSERT(m_hdc != nullptr);
      //throw ::interface_only();
      ////return ::ExcludeUpdateRgn(m_hdc, WIN_WINDOW(pwindow)->get_handle());
      return 0;
   }

   //double graphics::GetDeviceCaps(double nIndex) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetDeviceCaps(m_hdc, nIndex);
   //   return 0;
   //}

   int_point graphics::GetBrushOrg() const
   {
      // ASSERT(m_hdc != nullptr);
      ::int_point point;
      //VERIFY(::GetBrushOrgEx(m_hdc, &point));
      return point;
   }

   int_point graphics::SetBrushOrg(int x, int y)
   {
      // ASSERT(m_hdc != nullptr);
      ::int_point point;
      //VERIFY(::SetBrushOrgEx(m_hdc, x, y, &point));
      return point;
   }

   int_point graphics::SetBrushOrg(const ::int_point & point)
   {
      // ASSERT(m_hdc != nullptr);
      //VERIFY(::SetBrushOrgEx(m_hdc, point.x(), point.y(), &point));
      return point;
   }


   int graphics::EnumObjects(int nObjectType, int (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::EnumObjects(m_hdc, nObjectType, (GOBJENUMPROC)lpfn, lpData);
      return 0;
   }

   ::draw2d::bitmap * graphics::SelectObject(::draw2d::bitmap * pbitmap)
   {

      if (m_pbitmap == pbitmap)
      {

         return m_pbitmap;

      }

      vulkan_delete_offscreen_buffer();

      if (!vulkan_create_offscreen_buffer(pbitmap->get_size()))
      {

         return NULL;

      }

      bool bYSwap = m_papplication->m_bUseDraw2dProtoWindow;

      ::vulkan::resize(pbitmap->get_size(), bYSwap);

      //vkClear(VK_COLOR_BUFFER_BIT | VK_DEPTH_BUFFER_BIT);

      m_pbitmap = pbitmap;

      return m_pbitmap;

   }


   ::draw2d::object* graphics::SelectObject(::draw2d::object* pObject)
   {
      /*      // ASSERT(m_hdc != nullptr);
         if(pObject == nullptr)
            return nullptr;
         return SelectGdiObject(get_app(), m_hdc, pObject->get_os_data()); */
      return nullptr;
   }

   //HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for nullptr handles
   //{

   //   unsigned int uType = GetObjectType(hObject);

   //   if(uiType == OBJ_BITMAP)
   //   {

   //      HBITMAP hbitmap = (HBITMAP) hObject;

   //      if(m_pbitmap.is_null())
   //         m_pbitmap.create();

   //      if(m_pbitmap.is_null())
   //         return nullptr;

   //      //(dynamic_cast < ::draw2d_vulkan::bitmap * > (m_pbitmap.m_p))->m_pbitmap = ___new plusplus::Bitmap (hbitmap, nullptr);

   //      //if(m_pgraphics != nullptr)
   //      //{

   //      //   try
   //      //   {

   //      //      delete m_pgraphics;

   //      //   }
   //      //   catch(...)
   //      //   {

   //      //      informationf("graphics::SelectObject(HGDIOBJ) OBJ_BITMAP : Failed to delete plusplus::Graphics");

   //      //   }

   //      //   m_pgraphics = nullptr;

   //      //}

   //      //m_pgraphics = __allocate< plusplus::Graphics((plusplus::Bitmap *) m_pbitmap->get_os_data >());

   //      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

   //      //set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

   //      return hbitmap;

   //   }

   //   //*ASSERT(m_hdc == m_hdc); // ASSERT a simple graphics object
   //   //return (hObject != nullptr) ? ::SelectObject(m_hdc, hObject) : nullptr; */
   //   return nullptr;
   //}

   
   color32_t graphics::GetNearestColor(color32_t crColor) const
   {
      
      //return ::GetNearestColor(m_hdc, crColor);
      return color::transparent;

   }


   unsigned int graphics::RealizePalette()
   {
      //return ::RealizePalette(m_hdc);
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(m_hdc);
   }

   
   int graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(m_hdc);
      return 0;
   }

   
   int graphics::GetROP2() const
   {
      //return ::GetROP2(m_hdc);
      return 0;
   }

   
   int graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(m_hdc);
      return 0;
   }

   
   int graphics::GetMapMode() const
   {
      //return ::GetMapMode(m_hdc);
      return 0;
   }

   
   int graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(m_hdc);
      return 0;
   }


   bool graphics::GetWorldTransform(XFORM* pXform) const
   {



      //m_pgraphics->GetTransform(((graphics *)this)->m_pm);

      //plusplus::REAL ::double_rectangle[6];

      //m_pm->GetElements(rectangle);

      //pXform->eM11 = ::double_rectangle[0];
      //pXform->eM12 = ::double_rectangle[1];
      //pXform->eM21 = ::double_rectangle[2];
      //pXform->eM22 = ::double_rectangle[3];

      //pXform->eDx = ::double_rectangle[4];
      //pXform->eDy = ::double_rectangle[5];


      return true;

   }

   int_size graphics::get_context_extents() const
   {
      ::int_size size;
      //::Get_wiewportExtEx(m_hdc, &size);
      return size;
   }

   int_point graphics::GetWindowOrg() const
   {
      ::int_point point;
      //::GetWindowOrgEx(m_hdc, &point);
      return point;
   }

   int_size graphics::GetWindowExt() const
   {
      ::int_size size;
      //::GetWindowExtEx(m_hdc, &size);
      return size;
   }

   // non-virtual helpers calling virtual mapping functions
   int_point graphics::set_origin(const ::int_point & point)
   {

      return set_origin(point.x(), point.y());

   }

   //int_size graphics::set_context_extents(const ::int_size & size)
   //{
   //   return set_context_extents(size.cx(), size.cy());
   //}

   int_point graphics::SetWindowOrg(const ::int_point & point)
   {
      return SetWindowOrg(point.x(), point.y());
   }

   int_size graphics::set_window_ext(const ::int_size & size)
   {
      return set_window_ext(size.cx(), size.cy());
   }

   void graphics::DPtoLP(::double_point * lpPoints, ::collection::count nCount)
   {
      //::DPtoLP(m_hdc, lpPoints, (int) nCount);
   }

   void graphics::DPtoLP(::double_rectangle * prectangle)
   {
      //::DPtoLP(m_hdc, (::double_point *)rectangle, 2);
   }

   void graphics::LPtoDP(::double_point * lpPoints,::collection::count nCount)
   {
      //::LPtoDP(m_hdc, lpPoints, (int)  nCount);
   }

   void graphics::LPtoDP(::double_rectangle * prectangle)
   {
      //::LPtoDP(m_hdc, (::double_point *)rectangle, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      //return ::FillRgn(m_hdc, (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;
      return false;

   }

   
   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int nWidth, int nHeight)
   {

      //return ::FrameRgn(m_hdc, (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::InvertRgn(m_hdc, (HRGN)pRgn->get_os_data()) != false;
      return false;

   }

   //bool graphics::PaintRgn(::draw2d::region* pRgn)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::PaintRgn(m_hdc, (HRGN)pRgn->get_os_data())  != false;

   //   return ::draw2d::graphics::PaintRgn(pRgn);

   //}


   bool graphics::PtVisible(int x, int y) const
   {

      // ASSERT(m_hdc != nullptr);

      //return ::PtVisible(m_hdc, x, y) != false;
      //return ::draw2d::graphics::PtVisible(x, y);

      return true;

   }


   bool graphics::PtVisible(const ::int_point & point) const
   {
   
      // ASSERT(m_hdc != nullptr);   // call virtual
      return PtVisible(point.x(), point.y());

   }


   //bool graphics::rectVisible(const ::double_rectangle & ::double_rectangle) const
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::rectVisible(m_hdc, &rectangle) != false;
   //   return false;

   //}


   //int_point graphics::GetCurrentPosition() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //::int_point point(m_po;
   //   //VERIFY(::GetCurrentPositionEx(m_hdc, &point));
   //   //return point;
   //   return ::draw2d::graphics::G;
   //}

   void graphics::polyline(const ::double_point* lpPoints,::collection::count nCount)
   {

      if (nCount <= 0)
      {

         //return true;

         return;

      }

      bool bOk1 = false;

      //plusplus::Point * ppoints = ___new plusplus::Point[nCount];

      //try
      //{

      //   for(double i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x();
      //      ppoints[i].Y = lpPoints[i].y();
      //   }

      //   bOk1 = m_pgraphics->DrawLines(vk2d_pen(),ppoints,(::double) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1;
   }


   void graphics::arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   {

      auto pmathematics = mathematics();

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / π;
      double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / π;
      double sweep      = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return arc(x1,y1,x2-x1,y2-y1,start,sweep);

   }


   //void graphics::arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   //{

   //   double centerx    = (x2 + x1) / 2.0;
   //   double centery    = (y2 + y1) / 2.0;

   //   double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / π;
   //   double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / π;
   //   double sweep      = fabs(end - start);

   //   /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
   //   {
   //      sweep = -sweep;
   //   }
   //   */

   //   return Arc(x1,y1, x2-x1, y2-y1, start, sweep);

   //}


   void graphics::arc(double x1,double y1,double w,double h,double start, double extends)
   {

      //::plusplus::double_rectangle ::double_rectangle(x1,y1,w,h);

      //return m_pgraphics->DrawArc(vk2d_pen(),rectangle,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

      //return true;

   }


   //void graphics::arc(double x1,double y1,double w,double h,double start,double extends)
   //{

   //   //::plusplus::rectF float_rectangle((plusplus::REAL) x1,(plusplus::REAL) y1,(plusplus::REAL) w,(plusplus::REAL) h);

   //   //return m_pgraphics->DrawArc(vk2d_pen(),float_rectangle,(plusplus::REAL) start,(plusplus::REAL) extends) == plusplus::Status::Ok;

   //   return true;

   //}


   void graphics::fill_rectangle(const ::double_rectangle & rectangle, ::draw2d::brush* pbrush)
   {

      //vkBegin(VK_QUADS);

      //set(pbrush);

      //::vulkan::vertex2f(rectangle);

      //vkEnd();

      ////return false;

   }


   void graphics::frame_rectangle(const ::double_rectangle & rectangleParam,::draw2d::brush* pBrush)
   {

      //// ASSERT(m_hdc != nullptr);

      //::FrameRect(m_hdc,&rectangleParam,(HBRUSH)pBrush->get_os_data());

   }


   void graphics::invert_rectangle(const ::double_rectangle & rectangleParam)
   {

      // ASSERT(m_hdc != nullptr);

      //::InvertRect(m_hdc,&rectangleParam);

   }


   //bool graphics::DrawIcon(double x, double y, ::image::icon * picon)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   if(picon == nullptr)
   //      return false;

   //   //return ::DrawIcon(m_hdc, x, y, (HICON) picon->m_picon) != false;

   //   return false;

   //}

   //bool graphics::DrawIcon(const ::int_point & point, ::image::icon * picon)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   if(picon == nullptr)
   //      return false;

   //   //return ::DrawIcon(m_hdc, point.x(), point.y(), (HICON) picon->m_picon) != false;

   //   return false;

   //}

   //bool graphics::DrawIcon(double x, double y, ::image::icon * picon, double cx, double cy, unsigned int istepIfAniCur, HBRUSH hbrFlickerFreeDraw, unsigned int diFlags)
   //{

   //   //try
   //   //{

   //   //   if(picon == nullptr)
   //   //      return false;

   //   //   if(m_pgraphics == nullptr)
   //   //      return false;

   //   //   bool bOk = false;

   //   //   BITMAPINFO info;
   //   //   color32_t * pimage32;

   //   //   ZeroMemory(&info, sizeof (BITMAPINFO));

   //   //   info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
   //   //   info.bmiHeader.biWidth         = cx;
   //   //   info.bmiHeader.biHeight        = - cy;
   //   //   info.bmiHeader.biPlanes        = 1;
   //   //   info.bmiHeader.biBitCount      = 32;
   //   //   info.bmiHeader.biCompression   = BI_RGB;
   //   //   info.bmiHeader.biSizeImage     = cx * cy * 4;

   //   //   HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pimage32, nullptr, 0);

   //   //   HDC hdc = ::CreateCompatibleDC(nullptr);

   //   //   HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

   //   //   ICONINFO ii;
   //   //   BITMAPINFO biC;
   //   //   BITMAPINFO biM;

   //   //   zero(biC);
   //   //   zero(biM);



   //   //   if(::GetIconInfo((HICON)picon->m_picon,&ii))
   //   //   {

   //   //      ::GetObject(ii.hbmColor,sizeof(biC),(LPVOID)&biC);

   //   //      ::GetObject(ii.hbmMask,sizeof(biM),(LPVOID)&biM);

   //   //   }



   //   //   if(!::DrawIconEx(hdc,0,0,(HICON)picon->m_picon,cx,cy,istepIfAniCur,nullptr,DI_IMAGE | DI_MASK))
   //   //   {

   //   //      informationf("nok");
   //   //   }
   //   //   else
   //   //   {

   //   //      bool bAllZeroAlpha = true;
   //   //      bool bTheresunsigned int = false;

   //   //      int area = cx * cy;

   //   //      color32_t * pc = pimage32;
   //   //      unsigned char * pA = &((unsigned char *) pimage32)[3];

   //   //      for(int i = 0; i < area; i++)
   //   //      {
   //   //         if(*pc != 0)
   //   //         {
   //   //            bTheresunsigned int = true;
   //   //         }
   //   //         if(*pA != 0)
   //   //         {
   //   //            bAllZeroAlpha = false;
   //   //            break;
   //   //         }
   //   //         pc++;
   //   //         pA +=4;
   //   //      }

   //   //      if(bAllZeroAlpha && bTheresunsigned int)
   //   //      {

   //   //         pc = pimage32;
   //   //         pA = &((unsigned char *)pimage32)[3];

   //   //         for(int i = 0; i < area; i++)
   //   //         {
   //   //            if(*pc != 0)
   //   //            {
   //   //               *pA = 255;
   //   //            }
   //   //            pc++;
   //   //            pA +=4;
   //   //         }
   //   //      }

   //   //      ::SelectObject(hdc, hbitmapOld);

   //   //      try
   //   //      {

   //   //         plusplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (unsigned char *) pimage32);

   //   //         bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, plusplus::UnitPixel) == plusplus::Ok;

   //   //      }
   //   //      catch(...)
   //   //      {
   //   //      }

   //   //   }

   //   //   ::DeleteDC(hdc);

   //   //   ::DeleteObject(hbitmap);

   //   //   return bOk;

   //   //}
   //   //catch(...)
   //   //{
   //   //   return false;
   //   //}

   //   //return ::DrawIconEx(m_hdc, x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

   //   return true;

   //}

//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, HBITMAP hBitmap, unsigned int nFlags, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush, nullptr, (LPARAM)hBitmap, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_BITMAP) != false;
//      return false;
//
//   }

//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, ::draw2d::bitmap* pBitmap, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_BITMAP) != false;
//
//      return false;
//
//   }
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush, nullptr, (LPARAM)hIcon, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_ICON) != false;
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, HICON hIcon, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_ICON) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, const ::string & lpszText, unsigned int nFlags, bool bPrefixText, double nTextLen, HBRUSH hBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x(), point.y(), size.cx(), size.cy(), nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, const ::string & lpszText, unsigned int nFlags, bool bPrefixText, double nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x(), point.y(), size.cx(), size.cy(), nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, unsigned int nFlags, HBRUSH hBrush)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, hBrush,
//          //               lpDrawProc, lData, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_COMPLEX) != false;
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::int_point & point, const ::int_size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, unsigned int nFlags, ::draw2d::brush* pBrush)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawState(m_hdc, (HBRUSH)pBrush->get_os_data(),
//        //                 lpDrawProc, lData, 0, point.x(), point.y(), size.cx(), size.cy(), nFlags|DST_COMPLEX) != false;
//      return false;
//
//   }
//

//   bool graphics::DrawEdge(const ::double_rectangle & rectangleParam,unsigned int nEdge,unsigned int nFlags)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawEdge(m_hdc,(::double_rectangle *)&rectangleParam,nEdge,nFlags) != false;
//      return false;
//
//   }
//

//   bool graphics::DrawFrameControl(const ::double_rectangle & rectangleParam,unsigned int nType,unsigned int nState)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::DrawFrameControl(m_hdc,(::double_rectangle *) &rectangleParam,nType,nState) != false;
//      return false;
//
//   }


   bool graphics::Chord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::Chord(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
      return false;

   }


   bool graphics::Chord(const ::int_rectangle & rectangleParam,const ::int_point & pointStart,const ::int_point & pointEnd)
   {

      // ASSERT(m_hdc != nullptr);
      //return ::Chord(m_hdc,rectangleParam.left(),rectangleParam.top(),
      //               rectangleParam.right(),rectangleParam.bottom(),ptStart.x(),ptStart.y(),
      //               ptEnd.x(), ptEnd.y()) != false;

      return false;

   }

   
   void graphics::DrawFocusRect(const ::int_rectangle & rectangleParam)
   {
      // ASSERT(m_hdc != nullptr);
      //::DrawFocusRect(m_hdc,&rectangleParam);

   }


   //bool graphics::DrawEllipse(double x1, double y1, double x2, double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(vk2d_pen(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

   //   return true;
   //}


   void graphics::draw_ellipse(const ::double_rectangle &  rectangleParam)
   {

      //set_smooth_mode(::draw2d::e_smooth_mode_high);

      //return (m_pgraphics->DrawEllipse(vk2d_pen(),rectangleParam.left(),rectangleParam.top(),rectangleParam.right() - rectangleParam.left(),rectangleParam.bottom() - rectangleParam.top())) == plusplus::Status::Ok;

      //return true;

   }


   //bool graphics::FillEllipse(double x1, double y1, double x2, double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(vk2d_brush(), x1, y1, x2 - x1, y2 - y1)) == plusplus::Status::Ok;

   //   return true;

   //}


   void graphics::fill_ellipse(const ::double_rectangle &  rectangleParam)
   {

      //set_smooth_mode(::draw2d::e_smooth_mode_high);

//      return (m_pgraphics->FillEllipse(vk2d_brush(), rectangleParam.left(), rectangleParam.top(), rectangleParam.right() - rectangleParam.left(), rectangleParam.bottom() - rectangleParam.top())) == plusplus::Status::Ok;

      //return true;

   }


   //bool graphics::draw_ellipse(double x1,double y1,double x2,double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(vk2d_pen(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::draw_ellipse(const ::double_rectangle & rectectParam)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->DrawEllipse(vk2d_pen(),(plusplus::REAL)rectangleParam.left(),(plusplus::REAL)rectangleParam.top(),
   //   //                                 (plusplus::REAL)(rectangleParam.right() - rectangleParam.left()),
   //   //                                 (plusplus::REAL)(rectangleParam.bottom() - rectangleParam.top()))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::FillEllipse(double x1,double y1,double x2,double y2)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(vk2d_brush(),(plusplus::REAL)x1,(plusplus::REAL)y1,(plusplus::REAL)(x2 - x1),(plusplus::REAL)(y2 - y1))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::FillEllipse(const ::double_rectangle & rectectParam)
   //{

   //   //set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //return (m_pgraphics->FillEllipse(vk2d_brush(),(plusplus::REAL)rectangleParam.left(),(plusplus::REAL)rectangleParam.top(),
   //   //                                 (plusplus::REAL)(rectangleParam.right() - rectangleParam.left()),
   //   //                                 (plusplus::REAL)(rectangleParam.bottom() - rectangleParam.top()))) == plusplus::Status::Ok;

   //   return true;

   //}


   //bool graphics::Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   //{
   //
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::Pie(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   return false;

   //}


   //bool graphics::Pie(const ::double_rectangle & rectangleParam,const ::int_point & pointStart,const ::int_point & pointEnd)
   //{

   //   // ASSERT(m_hdc != nullptr);
   //   //return ::Pie(m_hdc, rectangleParam.left(), rectangleParam.top(),
   //   //             rectangleParam.right(), rectangleParam.bottom(), ptStart.x(), ptStart.y(),
   //   //             ptEnd.x(), ptEnd.y()) != false;

   //   return false;

   //}


   void graphics::fill_polygon(const ::double_point * lpPoints,::collection::count nCount)
   {

      //   if(nCount <= 0)
      //      return true;

      //   bool bOk1 = false;

      //   plusplus::PointF * ppoints = ___new plusplus::PointF[nCount];

      //   try
      //   {

      //      for(double i = 0; i < nCount; i++)
      //      {
      //         ppoints[i].X = (plusplus::REAL) lpPoints[i].x();
      //         ppoints[i].Y = (plusplus::REAL) lpPoints[i].y();
      //      }

      //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //      set_smooth_mode(::draw2d::e_smooth_mode_high);


      //      bOk1 = m_pgraphics->FillPolygon(vk2d_brush(), ppoints, (::double) nCount, vk2d_get_fill_mode()) == plusplus::Status::Ok;

      //   }
      //   catch(...)
      //   {
      //   }

      //   try
      //   {
      //      delete ppoints;
      //   }
      //   catch(...)
      //   {
      //   }


      //   return bOk1;

      //return true;

   }


   //void graphics::fill_polygon(const ::double_point* lpPoints,::collection::count nCount)
   //{

   //   //   if(nCount <= 0)
   //   //      return true;

   //   //   bool bOk1 = false;

   //   //   plusplus::Point * ppoints = ___new plusplus::Point[nCount];

   //   //   try
   //   //   {

   //   //      for(double i = 0; i < nCount; i++)
   //   //      {
   //   //         ppoints[i].X = lpPoints[i].x();
   //   //         ppoints[i].Y = lpPoints[i].y();
   //   //      }

   //   //      m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //   //      bOk1 = m_pgraphics->FillPolygon(vk2d_brush(), ppoints, (::double)  nCount, vk2d_get_fill_mode()) == plusplus::Status::Ok;

   //   //   }
   //   //   catch(...)
   //   //   {
   //   //   }

   //   //   try
   //   //   {
   //   //      delete ppoints;
   //   //   }
   //   //   catch(...)
   //   //   {
   //   //   }


   //   //   return bOk1;

   //   return true;

   //}


   void graphics::draw_polygon(const ::double_point* lpPoints,::collection::count nCount)
   {

      //if (nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //plusplus::Point * ppoints = ___new plusplus::Point[nCount];

      //try
      //{

      //   for (double i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x();
      //      ppoints[i].Y = lpPoints[i].y();
      //   }

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

      //   set_smooth_mode(::draw2d::e_smooth_mode_high);

      //   bOk1 = m_pgraphics->DrawPolygon(vk2d_pen(), ppoints, (::double) nCount) == plusplus::Status::Ok;

      //}
      //catch (...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch (...)
      //{
      //}


      //return bOk1;
      //return true;

   }


   //void graphics::draw_polygon(const ::double_point* lpPoints,::collection::count nCount)
   //{

   //   //if(nCount <= 0)
   //   //   return true;

   //   //bool bOk1 = false;

   //   //plusplus::PointF * ppoints = ___new plusplus::PointF[nCount];

   //   //try
   //   //{

   //   //   for(double i = 0; i < nCount; i++)
   //   //   {
   //   //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x();
   //   //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y();
   //   //   }

   //   //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //   //   bOk1 = m_pgraphics->DrawPolygon(vk2d_pen(),ppoints,(::double) nCount) == plusplus::Status::Ok;

   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //   //try
   //   //{
   //   //   delete ppoints;
   //   //}
   //   //catch(...)
   //   //{
   //   //}


   //   //return bOk1;

   //   return true;

   //}


   void graphics::polygon(const ::double_point* lpPoints,::collection::count nCount)
   {

      //if(nCount <= 0)
      //   return true;

      //bool bOk1 = false;

      //bool bOk2 = false;

      //plusplus::Point * ppoints = ___new plusplus::Point[nCount];

      //try
      //{

      //   for(double i = 0; i < nCount; i++)
      //   {
      //      ppoints[i].X = lpPoints[i].x();
      //      ppoints[i].Y = lpPoints[i].y();
      //   }


      //   set_smooth_mode(::draw2d::e_smooth_mode_high);

      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //   bOk1 = m_pgraphics->FillPolygon(vk2d_brush(), ppoints, (::double) nCount, vk2d_get_fill_mode()) == plusplus::Status::Ok;

      //   bOk2 = m_pgraphics->DrawPolygon(vk2d_pen(), ppoints, (::double) nCount) == plusplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //try
      //{
      //   delete ppoints;
      //}
      //catch(...)
      //{
      //}


      //return bOk1 && bOk2;

      //return true;

   }


   void graphics::poly_polygon(const ::double_point* lpPoints, const int * lpPolyCounts,::collection::count nCount)
   {

      // ASSERT(m_hdc != nullptr);


      //return ::PolyPolygon(m_hdc, lpPoints, (const ::double *) lpPolyCounts, (int) nCount) != false;
      //return false;

   }


   //bool graphics::double_rectangle(double x1, double y1, double x2, double y2)
   //{

   //   //plusplus::rectF float_rectangle((plusplus::REAL) x1, (plusplus::REAL) y1, (plusplus::REAL) (x2 - x1), (plusplus::REAL) (y2 - y1));

   //   //bool bOk1 = m_pgraphics->FillRectangle(vk2d_brush(), float_rectangle) == plusplus::Status::Ok;

   //   //bool bOk2 = m_pgraphics->DrawRectangle(vk2d_pen(), float_rectangle) == plusplus::Status::Ok;

   //   //return bOk1 && bOk2;

   //   return true;

   //}


   //void graphics::polygon(const ::double_point* lpPoints,::collection::count nCount)
   //{

   //   //if(nCount <= 0)
   //   //   return true;

   //   //bool bOk1 = false;

   //   //bool bOk2 = false;

   //   //plusplus::PointF * ppoints = ___new plusplus::PointF[nCount];

   //   //try
   //   //{

   //   //   for(double i = 0; i < nCount; i++)
   //   //   {
   //   //      ppoints[i].X = (plusplus::REAL) lpPoints[i].x();
   //   //      ppoints[i].Y = (plusplus::REAL) lpPoints[i].y();
   //   //   }

   //   //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);

   //   //   if(m_ealphamode == ::draw2d::e_alpha_mode_set)
   //   //   {

   //   //      set_smooth_mode(::draw2d::e_smooth_mode_none);

   //   //   }
   //   //   else
   //   //   {

   //   //      set_smooth_mode(::draw2d::e_smooth_mode_high);

   //   //   }


   //   //   bOk1 = m_pgraphics->FillPolygon(vk2d_brush(),ppoints,(::double) nCount,vk2d_get_fill_mode()) == plusplus::Status::Ok;

   //   //   bOk2 = m_pgraphics->DrawPolygon(vk2d_pen(),ppoints,(::double) nCount) == plusplus::Status::Ok;

   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //   //try
   //   //{
   //   //   delete ppoints;
   //   //}
   //   //catch(...)
   //   //{
   //   //}


   //   //return bOk1 && bOk2;

   //   return true;

   //}

   
   void graphics::rectangle(const ::double_rectangle &  rectangleParam)
   {

      fill_rectangle(rectangleParam);

      draw_rectangle(rectangleParam);

      //return ::double_rectangle(rectangleParam.left(), rectangleParam.top(), rectangleParam.right(), rectangleParam.bottom());

      //return bOk1 && bOk2;

   }


   void graphics::draw_rectangle(const ::double_rectangle& rectangle, ::draw2d::pen* ppen)
   {

      //if (::is_set(ppen))
      //{

      //   vkLineWidth((float)(ppen->m_dWidth));

      //}

      //vkBegin(VK_LINE_LOOP);

      //if (::is_set(ppen))
      //{

      //   ::vulkan::color(ppen->m_color);

      //}
      //
      //::vulkan::vertex2f(rectangle);
      //
      //vkEnd();

      //return true;

   }


   void graphics::draw_rectangle(const ::double_rectangle & rectangle)
   {

      draw_rectangle(rectangle, m_ppen);

      //return true;

   }


   void graphics::fill_rectangle(const ::double_rectangle & rectangle)
   {

      fill_rectangle(rectangle, m_pbrush);

   }

   
   //void graphics::round_rectangle(double x1, double y1, double x2, double y2, double x3, double y3)
   //{
   //
   //   //// ASSERT(m_hdc != nullptr);
   //   //return ::RoundRect(m_hdc, x1, y1, x2, y2, x3, y3) != false;

   //   //return false;

   //}


   void graphics::round_rectangle(const ::double_rectangle & rectangleParam,const ::int_point & point)
   {
      //// ASSERT(m_hdc != nullptr);
      //return ::RoundRect(m_hdc, rectangleParam.left(), rectangleParam.top(),
        //                 rectangleParam.right(), rectangleParam.bottom(), point.x(), point.y()) != false;

      //return false;

   }


//   bool graphics::PatBlt(double x, double y, double nWidth, double nHeight)
//   {
//      //// ASSERT(m_hdc != nullptr);
//      //return ::PatBlt(m_hdc, x, y, nWidth, nHeight, dwRop) != false;
//
//      return false;
//
//   }
//
//
//   bool graphics::BitBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc)
//   {
////      if (m_pgraphics == nullptr)
////         return false;
////
////      if (::draw2d::graphics::BitBlt(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop))
////         return true;
////
//      try
//      {
//
//         if(pgraphicsSrc == nullptr)
//            return false;
//
//         if (pgraphicsSrc->get_current_bitmap() == nullptr)
//            return false;
//
//         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
//            return false;
//
//         ::pointer<bitmap>pbitmap = pgraphicsSrc->get_current_bitmap();
//
//         //pbitmap->create_texture(0);
//
//         //vkBegin(VK_QUADS);
//         //// Front Face
//         //vkTexCoord2f(0.0f, 0.0f); vkVertex3f(-1.0f, -1.0f, 1.0f);
//         //vkTexCoord2f(1.0f, 0.0f); vkVertex3f(1.0f, -1.0f, 1.0f);
//         //vkTexCoord2f(1.0f, 1.0f); vkVertex3f(1.0f, 1.0f, 1.0f);
//         //vkTexCoord2f(0.0f, 1.0f); vkVertex3f(-1.0f, 1.0f, 1.0f);
//
//
////
////
////         return m_pgraphics->DrawImage(
////                   (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),
////                   x, y, xSrc + pgraphicsSrc->get_origin().x(), ySrc + pgraphicsSrc->get_origin().y(), nWidth, nHeight, plusplus::UnitPixel) == plusplus::Status::Ok;
////
//      }
//      catch(...)
//      {
//         return false;
//      }
////
////      //return ::BitBlt(m_hdc, x, y, nWidth, nHeight, VK2D_HDC(pgraphicsSrc), xSrc, ySrc);
////
////gdi_fallback:
////
////      HDC hdcDst = get_hdc();
////
////      if(hdcDst == nullptr)
////         return false;
////
////      HDC hdcSrc = VK2D_GRAPHICS(pgraphicsSrc)->get_hdc();
////
////      if(hdcSrc == nullptr)
////      {
////
////         release_hdc(hdcDst);
////
////         return false;
////
////      }
////
////      bool bOk = ::BitBlt(hdcDst, x, y, nWidth, nHeight, hdcSrc, x, y, dwRop) != false;
////
////      VK2D_GRAPHICS(pgraphicsSrc)->release_hdc(hdcSrc);
////
////      release_hdc(hdcDst);
////
////      return bOk;
//
//      return true;
//
//   }
//
//
//   bool graphics::StretchBltRaw(double xDst, double yDst, double nDstWidth, double nDstHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight)
//   {
//
//      //if(pgraphicsSrc == nullptr)
//      //   return false;
//
//      //plusplus::rectF dstRect((plusplus::REAL) xDst, (plusplus::REAL) yDst, (plusplus::REAL) nDstWidth, (plusplus::REAL) nDstHeight);
//
//      //plusplus::rectF srcRect((plusplus::REAL) xSrc, (plusplus::REAL) ySrc, (plusplus::REAL) nSrcWidth, (plusplus::REAL) nSrcHeight);
//
//      //if(pgraphicsSrc == nullptr || pgraphicsSrc->get_current_bitmap() == nullptr)
//      //   return false;
//
//      //try
//      //{
//      //   return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(),  dstRect, srcRect, plusplus::UnitPixel) == plusplus::Status::Ok;
//      //}
//      //catch(...)
//      //{
//
//      //}
//
//      //return false;
//
//      ////return ::StretchBlt(m_hdc, x, y, nWidth, nHeight, VK2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight);
//
//      return true;
//
//   }


   ::color::color graphics::GetPixel(int x, int y) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetPixel(m_hdc, x, y);
      return color::transparent;

   }


   ::color::color graphics::GetPixel(const ::int_point & point) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetPixel(m_hdc, point.x(), point.y());
      return color::transparent;

   }


   ::color::color graphics::SetPixel(double x, double y, ::color::color crColor)
   {
      
      return color::transparent;

   }


   ::color::color graphics::SetPixel(const ::int_point & point, ::color::color crColor)
   {

      //fill_solid_rect_coord(point.x(),point.y(),1,1,crColor);

      return crColor;

   }

   
//   bool graphics::FloodFill(double x, double y, color32_t crColor)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::FloodFill(m_hdc, x, y, crColor) != false;
//      return 0;
//
//   }
//
//
//   bool graphics::ExtFloodFill(double x, double y, color32_t crColor, unsigned int nFillType)
//   {
//
//      // ASSERT(m_hdc != nullptr);
//      //return ::ExtFloodFill(m_hdc, x, y, crColor, nFillType) != false;
//
//      return 0;
//
//   }


   //int_size graphics::GetTabbedTextExtent(const ::string & lpszString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   return nullptr;

   //}


   //int_size graphics::GetTabbedTextExtent(const ::string & str, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   return nullptr;

   //}


   //int_size graphics::GetOutputTabbedTextExtent(const ::string & lpszString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetTabbedTextExtent(m_hdc, lpszString, (double) nCount, (int) nTabPositions, lpnTabStopPositions);
   //   return nullptr;

   //}


   //int_size graphics::GetOutputTabbedTextExtent(const ::string & str, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetTabbedTextExtent(m_hdc, str, (double) str.length(), (int) nTabPositions, lpnTabStopPositions);
   //   return nullptr;

   //}


   //bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, double), LPARAM lpData, double nCount,double x, double y, double nWidth, double nHeight)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GrayString(m_hdc, (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;
   //   return false;

   //}


   unsigned int graphics::GetTextAlign()
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextAlign(m_hdc);
      return 0;

   }


   //double graphics::GetTextFace(::collection::count nCount, char * lpszFacename)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetTextFace(m_hdc, (int) nCount, lpszFacename);
   //   return -1;

   //}


   //double graphics::GetTextFace(string & rString)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //double nResult = ::GetTextFace(m_hdc, 256, rString.GetBuffer(256));
   //   //rString.ReleaseBuffer();

   //   //return nResult;
   //   return -1;

   //}


   void graphics::get_text_metrics(::write_text::text_metric * lpMetrics)
   {

      set(m_pfont);
      //if (!set(m_pfont))
      //{

      //   return false;

      //}

      ::pointer<font>pfont = m_pfont;

      TEXTMETRIC tm;

      GetTextMetrics(pfont->m_hdcFont, &tm);

      lpMetrics->m_dAscent = tm.tmAscent;
      lpMetrics->m_dHeight = tm.tmHeight;
      lpMetrics->m_dDescent = tm.tmDescent;
      //lpMetrics->tmAveCharWidth = tm.tmAveCharWidth;

      //if (m_pgraphics == nullptr)
      //   return false;

      //graphics * pgraphics = ((graphics *)this);

      //if(pgraphics->vk2d_font() == nullptr)
      //   return false;

      //plusplus::Font * pfont = pgraphics->vk2d_font();

      //plusplus::FontFamily family;

      //pfont->GetFamily(&family);

      //::double iStyle = pfont->GetStyle();

      //double dHeight = family.GetEmHeight(iStyle);

      //double dSize = pfont->GetSize();

      //double dFontHeight = pfont->GetHeight((plusplus::REAL) pgraphics->get_dpiy());

      //lpMetrics->tmAscent              = (::double) (dSize * family.GetCellAscent(iStyle) / dHeight);
      //lpMetrics->tmDescent             = (::double) (dSize * family.GetCellDescent(iStyle) / dHeight);
      //lpMetrics->tmHeight              = (::double)dFontHeight;

      //double dLineSpacing = maximum(dFontHeight, dSize * family.GetLineSpacing(iStyle) / dHeight);

      //lpMetrics->tmInternalLeading     = (::double) (lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight);
      //lpMetrics->tmExternalLeading     = (::double) (dLineSpacing - (lpMetrics->tmAscent + lpMetrics->tmDescent));

      //const plusplus::FontFamily * pfamilyMono = family.GenericMonospace();

      //::plusplus::Font font2(pfamilyMono, pfamilyMono->GetEmHeight(((graphics * )this)->vk2d_font()->GetStyle()));

      //wstring wstr(L"123AWZwmc123AWZwmcpQg");
      //plusplus::rectF ::double_rectangle(0.f, 0.f, 1024.f * 1024.f, 1024.f * 1024.f);
      //plusplus::rectF rect2;
      //plusplus::PointF origin(0, 0);

      //m_pgraphics->MeasureString(wstr, (::double) wstr.get_length(), ((graphics * )this)->vk2d_font(), origin, &rectangle);


      ///*wstr = L"";
      //m_pgraphics->MeasureString(wstr.m_pwsz, -1, (plusplus::Font *) m_pfont->get_os_data(), origin, &rect2);*/

      //lpMetrics->tmAveCharWidth = (::double) (rectangle.Width * get_current_font()->m_dFontWidth / (double) wstr.get_length());

      //return true;

   }


   void graphics::get_output_text_metrics(::write_text::text_metric * lpMetrics)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::GetTextMetricsW(m_hdc, lpMetrics) != false;

      //throw ::interface_only();

      //return false;

   }


   //double graphics::GetTextCharacterExtra()
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextCharacterExtra(m_hdc);
   //   return 0;

   //}


   //bool graphics::GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharWidth(m_hdc, nFirstChar, nLastChar, lpBuffer) != false;

   //   return false;

   //}


   //bool graphics::GetOutputCharWidth(unsigned int nFirstChar, unsigned int nLastChar, LPINT lpBuffer) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharWidth(m_hdc, nFirstChar, nLastChar, lpBuffer) != false;
   //   return false;

   //}


   unsigned int graphics::GetFontLanguageInfo() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetFontLanguageInfo(m_hdc);

      return 0;

   }


   //unsigned int graphics::GetCharacterPlacement(const ::string & lpString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   // return ::GetCharacterPlacement(m_hdc, lpString, (int)nCount, (int)nMaxExtent, lpResults, dwFlags);
   //   return false;

   //}


   //unsigned int graphics::GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS lpResults, unsigned int dwFlags) const
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetCharacterPlacement(m_hdc, (const ::string &)str, (double) str.length(), (int) nMaxExtent, lpResults, dwFlags);
   //   return false;

   //}


   //int_size graphics::GetAspectRatioFilter() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   ::int_size size;
   //   // VERIFY(::GetAspectRatioFilterEx(m_hdc, &size));
   //   return size;

   //}


   //bool graphics::ScrollDC(double Δx, double Δy,
   //                        const ::double_rectangle & lpRectScroll,const ::double_rectangle & rectangleClip,
   //                        ::draw2d::region* pRgnUpdate, ::double_rectangle * lpRectUpdate)
   //{
   //   
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::ScrollDC(m_hdc,Δx,Δy,&rectangleClip,
   //     //                &rectangleClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != false;
   //   return 0;

   //}


   // Printer Escape Functions
   int graphics::Escape(int nEscape, int nCount, const ::scoped_string & lpszInData, LPVOID lpOutData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::Escape(m_hdc, nEscape, nCount, lpszInData, lpOutData);
      return 0;

   }


   // graphics 3.1 Specific functions
   unsigned int graphics::SetBoundsRect(const ::double_rectangle & rectangleBounds, unsigned int flags)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetBoundsRect(m_hdc, &rectangleBounds, flags);
      return 0;

   }


   unsigned int graphics::GetBoundsRect(::double_rectangle * rectangleBounds, unsigned int flags)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetBoundsRect(m_hdc, rectangleBounds, flags);
      return 0;

   }


   void graphics::resize(const ::int_size & sizeWindow)
   {

      m_sizeWindow = sizeWindow;

      bool bYSwap = m_papplication->m_bUseDraw2dProtoWindow;

      ::vulkan::resize(sizeWindow, bYSwap);

   }



   //bool graphics::ResetDC(const DEVMODE* lpDevMode)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::ResetDC(m_hdc, lpDevMode) != nullptr;
   //   return false;

   //}


   //unsigned int graphics::GetOutlineTextMetrics(unsigned int cbData, LPOUTLINETEXTMETRICW lpotm) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetOutlineTextMetricsW(m_hdc, cbData, lpotm);
   //   return 0;
   //}


   //bool graphics::GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar, LPABC lpabc) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharABCWidths(m_hdc, nFirstChar, nLastChar, lpabc) != false;
   //   return false;

   //}


   //unsigned int graphics::GetFontData(unsigned int dwTable, unsigned int dwOffset, LPVOID lpData,
   //                               unsigned int cbData) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetFontData(m_hdc, dwTable, dwOffset, lpData, cbData);
   //   return 0;

   //}


   //double graphics::GetKerningPairs(double nPairs, LPKERNINGPAIR lpkrnpair) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetKerningPairs(m_hdc, nPairs, lpkrnpair);
   //   return 0;

   //}


   //unsigned int graphics::GetGlyphOutline(unsigned int nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm,
   //                                   unsigned int cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetGlyphOutline(m_hdc, nChar, nFormat,
   //     //                       lpgm, cbBuffer, lpBuffer, lpmat2);
   //   return 0;

   //}


   // ::user::document handling functions
   int graphics::StartDoc(LPDOCINFO lpDocInfo)
   {

      //ASSERT(m_hdc != nullptr);

      //return ::StartDoc(m_hdc, lpDocInfo);
      return 0;

   }


   int graphics::StartPage()
   {

      //ASSERT(m_hdc != nullptr);

      //::StartPage(m_hdc);

      //m_pgraphics = ___new plusplus::Graphics (m_hdc);

      //m_pgraphics->SetPageUnit(plusplus::UnitPixel);

      return 1;

   }


   int graphics::EndPage()
   {

      /* ASSERT(m_hdc != nullptr);

       delete m_pgraphics;

      */
      //return ::EndPage(m_hdc);
      return 0;

   }


   int graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int))
   {

      //ASSERT(m_hdc != nullptr);

      //return ::SetAbortProc(m_hdc, (ABORTPROC)lpfn);
      return 0;

   }


   int graphics::AbortDoc()
   {

      //ASSERT(m_hdc != nullptr);

      //return ::AbortDoc(m_hdc);
      return 0;

   }


   int graphics::EndDoc()
   {

      //ASSERT(m_hdc != nullptr);

      //return ::EndDoc(m_hdc);
      return 0;

   }


//   bool graphics::MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
//                          double xSrc, double ySrc, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
//   {
//      // ASSERT(m_hdc != nullptr);
//      //return ::MaskBlt(m_hdc, x, y, nWidth, nHeight, VK2D_HDC(pgraphicsSrc),
//        //               xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;
//      return 0;
//
//   }
//
//
//   bool graphics::PlgBlt(::double_point * lpPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc,
//                         double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, double yMask)
//   {
//
//      /*try
//      {
//
//         if(pgraphicsSrc == nullptr)
//            return false;
//
//         if(pgraphicsSrc->get_current_bitmap() == nullptr)
//            return false;
//
//         if(pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
//            return false;
//
//         plusplus::Point p[3];
//
//         p[0].X = lpPoint[0].x();
//         p[0].Y = lpPoint[0].y();
//         p[1].X = lpPoint[1].x();
//         p[1].Y = lpPoint[1].y();
//         p[2].X = lpPoint[2].x();
//         p[2].Y = lpPoint[2].y();
//
//         return m_pgraphics->DrawImage((plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), p, 3) == plusplus::Status::Ok;
//
//      }
//      catch(...)
//      {
//         return false;
//      }
//      */
//      return true;
//
//   }



   void graphics::SetPixelV(int x, int y, ::color::color crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetPixelV(m_hdc, x, y, crColor) != false;
      //return 0;

   }


   void graphics::SetPixelV(const ::int_point & point, ::color::color crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetPixelV(m_hdc, point.x(), point.y(), crColor) != false;
      //return 0;

   }


   void graphics::angle_arc(double x, double y, double nRadius, ::double_angle fStartAngle, ::double_angle fSweepAngle)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::AngleArc(m_hdc, x, y, nRadius, fStartAngle, fSweepAngle) != false;
      //return 0;

   }



   void graphics::arc_to(const ::int_rectangle & rectangleParam,const ::int_point & pointStart,const ::int_point & pointEnd)
   {
      // ASSERT(m_hdc != nullptr);
      //return ArcTo(rectangleParam.left(), rectangleParam.top(), rectangleParam.right(),
        //           rectangleParam.bottom(), ptStart.x(), ptStart.y(), ptEnd.x(), ptEnd.y());

      //return false;

   }


   //int graphics::GetArcDirection() const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   // return ::GetArcDirection(m_hdc);
   //   return 0;

   //}


   void graphics::poly_polyline(const ::double_point* lpPoints, const int * lpPolyPoints, ::collection::count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::poly_polyline(m_hdc, lpPoints, (LPDWORD) lpPolyPoints, (unsigned int) nCount) != false;
      //return false;

   }


   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetColorAdjustment(m_hdc, lpColorAdjust) != false;
      return false;

   }


   ::draw2d::pen * graphics::get_current_pen()
   {

      return m_ppen;

   }

   ::draw2d::brush * graphics::get_current_brush()
   {

      return m_pbrush;

   }

   //::draw2d::palette_pointer graphics::get_current_palette()
   //{

   //   return (::draw2d::palette *)nullptr;

   //}

   ::write_text::font * graphics::get_current_font()
   {

      return m_pfont;

   }

   ::draw2d::bitmap * graphics::get_current_bitmap()
   {

      return m_pbitmap;

   }


   void graphics::poly_bezier(const ::double_point* lpPoints, ::collection::count nCount)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::poly_bezier(m_hdc, lpPoints, (unsigned int) nCount) != false;
      //return false;

   }


   int graphics::DrawEscape(int nEscape, int nInputSize, const ::scoped_string & lpszInputData)
   {

      // ASSERT(m_hdc != nullptr);

      //return ::DrawEscape(m_hdc, nEscape, nInputSize, lpszInputData);
      return 0;


   }


   int graphics::Escape(int nEscape, int nInputSize, __in_bcount(nInputSize) const char * lpszInputData,  int nOutputSize, __out_bcount(nOutputSize) char * lpszOutputData)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::ExtEscape(m_hdc, nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
      return 0;

   }


   //bool graphics::GetCharABCWidths(unsigned int nFirstChar, unsigned int nLastChar,
   //                                LPABCFLOAT lpABCF) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharABCWidthsFloat(m_hdc, nFirstChar, nLastChar, lpABCF) != false;
   //   return false;
   //}


   //bool graphics::GetCharWidth(unsigned int nFirstChar, unsigned int nLastChar, float* lpFloatBuffer) const
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetCharWidthFloat(m_hdc, nFirstChar, nLastChar, lpFloatBuffer) != false;
   //   return false;

   //}


   void graphics::abort_path()
   {
      //if(m_ppath != nullptr)
      //{
      //   delete m_ppath;
      //   m_ppath = nullptr;
      //}
      //return true;

   }


   void graphics::begin_path()
   {

      /*     if(m_ppath != nullptr)
              delete m_ppath;

           m_ppath = ___new plusplus::GraphicsPath ();
      */
//      return m_ppath != nullptr;

      //return true;

   }


   void graphics::close_figure()
   {
      //ASSERT(m_ppath != nullptr);
      //return m_ppath->CloseFigure() == plusplus::Status::Ok;
      //return true;

   }


   void graphics::end_path()
   {

      //if(m_ppath == nullptr)
      //   return false;

      //m_ppathPaint   = m_ppath;
      //m_ppath        = nullptr;

      //return true;

   }


   void graphics::fill_path()
   {

      //return m_pgraphics->FillPath(vk2d_brush(), m_ppath) == plusplus::Status::Ok;
      //return true;

   }


   void graphics::flatten_path()
   {
//      return m_ppath->Flatten() == plusplus::Status::Ok;
      //return true;

   }

   
   void graphics::stroke_and_fill_path()
   {


   }


   void graphics::stroke_path()
   {


   }


   void graphics::widen_path()
   {

      
   }


   float graphics::GetMiterLimit()
   {
      // ASSERT(m_hdc != nullptr);
      //float fMiterLimit;
      //VERIFY(::GetMiterLimit(m_hdc, &fMiterLimit));
      //::GetMiterLimit(m_hdc, &fMiterLimit);
      //;;; return fMiterLimit;
      return 0.f;
   }


   //void graphics::GetPath(::double_point * lpPoints, unsigned char * lpTypes, ::collection::count nCount)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GetPath(m_hdc, lpPoints, lpTypes, (int) nCount);

   //   ::GetPath(m_hdc, lpPoints, lpTypes, (int)nCount);

   //}


   void graphics::SetMiterLimit(float fMiterLimit)
   {
      // ASSERT(m_hdc != nullptr);
      ///return ::SetMiterLimit(m_hdc, fMiterLimit, nullptr) != false;
      //::SetMiterLimit(m_hdc, fMiterLimit, nullptr);

   }


   //void graphics::StrokeAndFillPath()
   //{

   //   //bool bOk1 = m_pgraphics->FillPath(vk2d_brush(), m_ppathPaint) == plusplus::Status::Ok;

   //   //bool bOk2 = m_pgraphics->DrawPath(vk2d_pen(), m_ppathPaint) == plusplus::Status::Ok;

   //   //return bOk1 && bOk2;

   //   //return true;

   //}


//   void graphics::StrokePath()
//   {
//
////      return m_pgraphics->DrawPath(vk2d_pen(), m_ppathPaint) == plusplus::Status::Ok;
//
//      //return true;
//
//   }


   //void graphics::WidenPath()
   //{

   //   //return m_ppath->Widen(vk2d_pen()) == plusplus::Status::Ok;

   //   //return true;

   //}


   void graphics::draw(::draw2d::path * ppath)
   {

      //m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeAntiAlias);
      //m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);


      //return m_pgraphics->DrawPath(vk2d_pen(),(dynamic_cast < ::draw2d_vulkan::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;
      //return true;

   }


   void graphics::draw(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      //return m_pgraphics->DrawPath((::plusplus::Pen *) ppen->get_os_data(),(dynamic_cast < ::draw2d_vulkan::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      //return true;

   }


   void graphics::fill(::draw2d::path * ppath)
   {

      //return m_pgraphics->FillPath(vk2d_brush(),(dynamic_cast < ::draw2d_vulkan::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      //return true;

   }


   void graphics::fill(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      //return m_pgraphics->FillPath((::plusplus::Brush *) pbrush->get_os_data(),(dynamic_cast < ::draw2d_vulkan::path * > (ppath))->get_os_path(m_pgraphics)) == plusplus::Status::Ok;

      //return true;

   }


   //void graphics::AddMetaFileComment(unsigned int nDataSize, const unsigned char* pCommentData)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GdiComment(m_hdc, nDataSize, pCommentData) != false;
   //   //return false;

   //}


   /*bool CALLBACK metaCallback(
      EmfPlusRecordType recordType,
      unsigned int flags,
      unsigned int dataSize,
      const uchar* pStr,
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
      Metafile* pMeta = ___new Metafile(L"SampleMetafile.emf", hdc);
      {
         // Fill a ::double_rectangle and an ellipse in pMeta.
         Graphics metaGraphics(pMeta);
         metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
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
   
   
   //bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::double_rectangle & rectangleBounds)
   //{

   //   //plusplus::rectF ::double_rectangle((plusplus::REAL) rectangleBounds.left(),(plusplus::REAL) rectangleBounds.top(),(plusplus::REAL) width(rectangleBounds),(plusplus::REAL) height(rectangleBounds));

   //   //plusplus::Metafile* pMeta = ___new plusplus::Metafile (hEnhMF, false);

   //   ////m_pgraphcis->EnumerateMetafile(pMeta, rectangle, metaCallback, PMETAHEADER);

   //   //bool bOk = m_pgraphics->DrawImage(pMeta, rectangle) == plusplus::Status::Ok;

   //   //delete pMeta;

   //   //return bOk ? true : false;
   //   //return ::PlayEnhMetaFile(m_hdc, hEnhMF, lpBounds);

   //   return true;

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


//   void graphics::alpha_blend(double xDest, double yDest, double nDestWidth, double nDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight, double dRate)
//   {
//
////      if (m_pgraphics == nullptr)
////         return false;
////
////      if(m_pimageAlphaBlend->is_set())
////      {
////
////
////         ::double_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
////
////
////         ::image::image_pointer pimageWork = nullptr;
////         ::image::image_pointer pimageWork2 = nullptr;
//////         ::image::image_pointer pimageWork3 = nullptr;
////         ::image::image_pointer pimageWork4 = nullptr;
////
////
////         ::int_point pointSrc(xSrc, ySrc);
////         ::int_point ptDest(xDest, yDest);
////         ::int_size size(nDestWidth, nDestHeight);
////
////
////
////         ::image::image_pointer pimage;
////         if(imageWork == nullptr)
////         {
////            pimage->create(this);
////            imageWork = pimage;
////         }
////         if(imageWork == nullptr)
////            return false;
////         if(!imageWork = create_image(size))
////            return false;
////         if(!imageWork.from(::int_point(), pgraphicsSrc, pointSrc, size))
////            return false;
////
////
////
////
////         ::image::image_pointer pimage2;
////         if(imageWork2 == nullptr)
////         {
////            pimage2->create(this);
////            imageWork2 = pimage2;
////         }
////
////
////         ::image::image_pointer pimage4;
////         if(imageWork4 == nullptr)
////         {
////            image4.create(this);
////            imageWork4 = image4;
////         }
////         if(imageWork4 == nullptr)
////            return false;
////         if(!imageWork4 = create_image(size))
////            return false;
////
////
////         imageWork4.Fill(255, 0, 0, 0);
////
////         imageWork4.from(int_point(maximum(0, m_pointAlphaBlend.x() - xDest), maximum(0, m_pointAlphaBlend.y() - yDest)),
////                         m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, xDest - m_pointAlphaBlend.x()), maximum(0, yDest - m_pointAlphaBlend.y())), size);
////
////         imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);
////
////
////         keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);
////
////
////         return BitBlt(ptDest.x(), ptDest.y(), size.cx(), size.cy(), imageWork.get_graphics(), pointSrc.x(), pointSrc.y());
////
////
////      }
////
////
////      float fA = (float) dRate;
////
////      plusplus::ColorMatrix matrix = {
////         1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
////         0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
////         0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
////         0.0f, 0.0f, 0.0f, fA  , 0.0f,
////         0.0f, 0.0f, 0.0f, 0.0f, 1.0f
////      };
////
////      plusplus::ImageAttributes attributes;
////
////      attributes.SetColorMatrix(&matrix, plusplus::ColorMatrixFlagsDefault, plusplus::ColorAdjustTypeBitmap);
////
////      plusplus::rectF dstRect((plusplus::REAL) xDest, (plusplus::REAL) yDest, (plusplus::REAL) nDestWidth, (plusplus::REAL) nDestHeight);
////
////      if(pgraphicsSrc == nullptr)
////         return false;
////
////      if(pgraphicsSrc->get_current_bitmap() == nullptr)
////         return false;
////
////      plusplus::Bitmap * pbitmap = nullptr;
////
////      try
////      {
////
////         pbitmap = (plusplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();
////
////      }
////      catch(...)
////      {
////      }
////
////      if(pbitmap != nullptr)
////      {
////
////         m_pgraphics->DrawImage(pbitmap,dstRect,(plusplus::REAL) xSrc,(plusplus::REAL) ySrc,(plusplus::REAL) nSrcWidth,(plusplus::REAL) nSrcHeight,plusplus::UnitPixel,&attributes);
////
////      }
////
//      //return true;
//
//   }


   /*bool graphics::alpha_blend(double xDest, double yDest, double nDestWidth, double nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight, BLENDFUNCTION blend)
   {

      throw ::interface_only();
      //if(m_hdc == nullptr)
        // return false;


      if(m_pimageAlphaBlend->is_set())
      {


         ::double_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image::image_pointer pimageWork = nullptr;
         ::image::image_pointer pimageWork2 = nullptr;
   //         ::image::image_pointer pimageWork3 = nullptr;
         ::image::image_pointer pimageWork4 = nullptr;


         ::int_point pointSrc(xSrc, ySrc);
         ::int_point ptDest(xDest, yDest);
         ::int_size size(nDestWidth, nDestHeight);



         ::image::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage->create(this);
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;
         if(!imageWork.from(::int_point(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2->create(this);
            imageWork2 = pimage2;
         }


         ::image::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4.create(this);
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.from(int_point(maximum(0, m_pointAlphaBlend.x() - xDest), maximum(0, m_pointAlphaBlend.y() - yDest)),
            m_pimageAlphaBlend->get_graphics(), int_point(maximum(0, xDest - m_pointAlphaBlend.x()), maximum(0, yDest - m_pointAlphaBlend.y())), size);

         imageWork.channel_multiply(::color::e_channel_opacity, imageWork4);


         keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


         return psystem->imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);


      }

      return ::AlphaBlend(m_hdc, xDest, yDest,
         nDestWidth, nDestHeight, VK2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != false;
   }*/


   //bool graphics::TransparentBlt(double xDest, double yDest, double nDestWidth, double nDestHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, double ySrc, double nSrcWidth, double nSrcHeight, unsigned int crTransparent)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::TransparentBlt(m_hdc, xDest, yDest,  nDestWidth, nDestHeight, VK2D_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,  nSrcHeight, crTransparent) != false;

   //   return true;

   //}


   //bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, unsigned int dwMode)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   //return ::GradientFill(m_hdc, pVertices, nVertices, pMesh, nMeshElements, dwMode) != false;

   //   return true;

   //}

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

   inline color32_t graphics::GetDCBrushColor() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetDCBrushColor(m_hdc);
      return color::transparent;
   }


   inline color32_t graphics::SetDCBrushColor(color32_t crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetDCBrushColor(m_hdc, crColor);
      return color::transparent;

   }


   inline color32_t graphics::GetDCPenColor() const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetDCPenColor(m_hdc);
      return color::transparent;


   }


   inline color32_t graphics::SetDCPenColor(color32_t crColor)
   {
      // ASSERT(m_hdc != nullptr);
      //return ::SetDCPenColor(m_hdc, crColor);
      return color::transparent;

   }


   inline bool graphics::GetCharABCWidthsI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPABC lpabc) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharABCWidthsI(m_hdc, giFirst, cgi, pgi, lpabc) != false;
      return false;

   }


   inline bool graphics::GetCharWidthI(unsigned int giFirst, unsigned int cgi, LPWORD pgi, LPINT lpBuffer) const
   {
      // ASSERT(m_hdc != nullptr);
      //return ::GetCharWidthI(m_hdc, giFirst, cgi, pgi, lpBuffer) != false;
      return false;

   }


   //inline bool graphics::GetTextExtentExPointI(LPWORD pgiIn, double cgi, double nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32) const
   //{
   //   ENSURE(LPSIZE32 != nullptr);
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextExtentExPointI(m_hdc, pgiIn, cgi, nMaxExtent, lpnFit, alpDx, LPSIZE32) != false;
   //   return false;

   //}


   //inline bool graphics::GetTextExtentPointI(LPWORD pgiIn, double cgi, LPSIZE32 LPSIZE32) const
   //{
   //   ENSURE(LPSIZE32 != nullptr);
   //   // ASSERT(m_hdc != nullptr);
   //   //return ::GetTextExtentPointI(m_hdc, pgiIn, cgi, LPSIZE32) != false;
   //   return false;

   //}


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(::double_size * psize)
   {
//      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));
//
//      double nMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained map mode, map against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         DPtoLP(LPSIZE32);
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         
//         double cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_VALID(this);
//            // ASSERT(m_hdc != nullptr);  // no HDC attached or created?
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {

//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         LPSIZE32->cx() = MulDiv(LPSIZE32->cx(), HIMETRIC_INCH, cxPerInch);
//         LPSIZE32->cy() = MulDiv(LPSIZE32->cy(), HIMETRIC_INCH, cyPerInch);
//      }
   }


   void graphics::HIMETRICtoDP(::double_size * psize)
   {
//      ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));
//
//      double nMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained map mode, map against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         LPtoDP(LPSIZE32);
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         
//         double cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_VALID(this);
//            // ASSERT(m_hdc != nullptr);  // no HDC attached or created?
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {

//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         LPSIZE32->cx() = MulDiv(LPSIZE32->cx(), cxPerInch, HIMETRIC_INCH);
//         LPSIZE32->cy() = MulDiv(LPSIZE32->cy(), cyPerInch, HIMETRIC_INCH);
//      }
   }


   void graphics::LPtoHIMETRIC(::double_size * psize)
   {
      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

      //LPtoDP(LPSIZE32);
      //DPtoHIMETRIC(LPSIZE32);
   }


   void graphics::HIMETRICtoLP(::double_size * psize)
   {
      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

      //HIMETRICtoDP(LPSIZE32);
      //DPtoLP(LPSIZE32);

   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* graphics::GetHalftoneBrush()
   {
      /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
            if (gen_HalftoneBrush == nullptr)
            {
               unsigned short grayPattern[8];
               for (double i = 0; i < 8; i++)
                  grayPattern[i] = (unsigned short)(0x5555 << (i & 1));
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

      //      return ::draw2d_vulkan::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }

   
   //void graphics::DrawDragRect(const ::double_rectangle & rectangle, const ::int_size & size, const ::double_rectangle & lpRectLast, const ::int_size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   //throw ::interface_only();

   //   /*

   //         ASSERT(is_memory_segment_ok(rectangle, sizeof(::double_rectangle), false));
   //         ASSERT(lpRectLast == nullptr ||
   //            is_memory_segment_ok(lpRectLast, sizeof(::double_rectangle), false));

   //         // first, determine the update region and select it
   //         ::draw2d::region rgnNew;
   //         ::draw2d::region rgnOutside, rgnInside;
   //         rgnOutside.create_rect(rectangle);
   //         const ::double_rectangle & rectangle = *rectangle;
   //         rectangle.inflate(-size.cx(), -size.cy());
   //         rectangle.intersect(rectangle, rectangle);
   //         rgnInside.create_rect(rectangle);
   //         rgnNew.create_rect(0, 0, 0, 0);
   //         rgnNew.combine(&rgnOutside, &rgnInside, RGN_XOR);

   //         ::draw2d::brush* pBrushOld = nullptr;
   //         if (pBrush == nullptr)
   //         {
   //            pBrush = graphics::GetHalftoneBrush(this);
   //         }

   //         ENSURE(pBrush);

   //         if (pBrushLast == nullptr)
   //         {
   //            pBrushLast = pBrush;
   //         }

   //         ::draw2d::region rgnLast, rgnUpdate;
   //         if (lpRectLast != nullptr)
   //         {
   //            // find difference between ___new region and old region
   //            rgnLast.create_rect(0, 0, 0, 0);
   //            rgnOutside.SetRectRgn(lpRectLast);
   //            rectangle = *lpRectLast;
   //            rectangle.inflate(-sizeLast.cx(), -sizeLast.cy());
   //            rectangle.intersect(rectangle, lpRectLast);
   //            rgnInside.SetRectRgn(rectangle);
   //            rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

   //            // only diff them if brushes are the same
   //            if (pBrush->get_os_data() == pBrushLast->get_os_data())
   //            {
   //               rgnUpdate.create_rect(0, 0, 0, 0);
   //               rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
   //            }
   //         }
   //         if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != nullptr)
   //         {
   //            // brushes are different -- erase old region first
   //            SelectClipRgn(&rgnLast);
   //            get_clip_box(&rectangle);
   //            pBrushOld = SelectObject(pBrushLast);
   //            PatBlt(rectangle.left(), rectangle.top(), rectangle.width(), rectangle.height(), PATINVERT);
   //            SelectObject(pBrushOld);
   //            pBrushOld = nullptr;
   //         }

   //         // draw into the update/___new region
   //         SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
   //         get_clip_box(&rectangle);
   //         pBrushOld = SelectObject(pBrush);
   //         PatBlt(rectangle.left(), rectangle.top(), rectangle.width(), rectangle.height(), PATINVERT);

   //         // cleanup DC
   //         if (pBrushOld != nullptr)
   //            SelectObject(pBrushOld);
   //         SelectClipRgn(nullptr);

   //   */
   //}

   /*void graphics::FillSolidRect(const ::double_rectangle & rectangle, color32_t clr)
   {
      ::SetBkColor(m_hdc, clr);
      ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, rectangle, nullptr, 0, nullptr);
   }*/

   /*void graphics::fill_rectangle(const double_rectangle & rectangle, color32_t clr)
   {
      ::double_rectangle rect32;
      copy(rect32, rectangle);
      FillSolidRect(rect32, clr);
   }
*/

   /*

   void graphics::FillSolidRect(double x, double y, double cx, double cy, color32_t clr)
   {
      ::SetBkColor(m_hdc, clr);
      ::double_rectangle rectangle(x, y, x + cx, y + cy);
      ::ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, &rectangle, nullptr, 0, nullptr);
   }

   */

   
   //void graphics::draw_inset_3d_rectangle(const ::double_rectangle & rectangleParam,
   //                          const ::color::color & clrTopLeft, const ::color::color & clrBottomRight,
   //   const ::e_border & eborder)
   //{

   //   //draw3d_rectangle(rectangleParam.left(), rectangleParam.top(), rectangleParam.right() - rectangleParam.left(),
   //     //         rectangleParam.bottom() - rectangleParam.top(), clrTopLeft, clrBottomRight);

   //}

   //
   //void graphics::draw_inset_rectangle(const ::double_rectangle & rectangle, const ::color::color & color, const ::e_border & eborder)
   //{


   //}


   //void graphics::Draw3dRect(double x, double y, double cx, double cy,
   //                          color32_t clrTopLeft, color32_t clrBottomRight)
   //{
   //   fill_solid_rect_coord(x, y, cx - 1, 1, clrTopLeft);
   //   fill_solid_rect_coord(x, y, 1, cy - 1, clrTopLeft);
   //   fill_solid_rect_coord(x + cx - 1, y, 1, cy, clrBottomRight);
   //   fill_solid_rect_coord(x, y + cy - 1, cx, 1, clrBottomRight);
   //}





   //::draw2d::graphics * ::draw2d_vulkan::graphics::from_handle(HDC hDC)
   //{
   //hdc_map* pMap = ::windows_definition::MapHDC(true); //create map if not exist
   //ASSERT(pMap != nullptr);
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pgraphics == nullptr || (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->m_hdc == hDC);
   //  return pgraphics;
   // return nullptr;
   //}

   //bool graphics::Attach(HDC hdc)
   //{

   //   //if(hdc == nullptr)
   //   //   return false;

   //   //if(m_hdc == hdc)
   //   //{

   //   //   if(m_pgraphics != nullptr)
   //   //      return true;

   //   //}

   //   //if(hdc != nullptr)
   //   //{

   //   //   m_pgraphics = __allocate< ::plusplus::Graphics( >(HDC) hdc);

   //   //   m_pgraphics->SetPageUnit(plusplus::UnitPixel);

   //   //   set_text_rendering_hint(::write_text::e_rendering_anti_alias_grid_fit);

   //   //   m_hdc = (HDC) hdc;

   //   //}

   //   //return m_pgraphics != nullptr;

   //   return true;

   //   /*ASSERT(m_hdc == nullptr);      // only attach once, detach on destroy
   //   ASSERT(m_hdc == nullptr);    // only attach to an is_empty DC

   //   if (hDC == nullptr)
   //   {
   //      return false;
   //   }
   //   // remember early to avoid leak
   //   set_handle1(hDC);
   //   hdc_map* pMap = ::windows_definition::MapHDC(true); // create map if not exist
   //   ASSERT(pMap != nullptr);
   //   pMap->set_permanent(m_hdc, this);

   //   SetAttribDC(m_hdc);     // Default to same as output
   //   return true;*/
   //}


   //HDC graphics::Detach()
   //{

   //   //if(m_hdc == nullptr)
   //   //   return nullptr;

   //   //if(m_pgraphics == nullptr)
   //   //   return nullptr;

   //   //try
   //   //{

   //   //   delete m_pgraphics;

   //   //}
   //   //catch(...)
   //   //{

   //   //   informationf("graphics::Detach : Failed to delete plusplus::Graphics");

   //   //}

   //   //m_pgraphics = nullptr;

   //   //HDC hdc = m_hdc;
   //   //m_hdc = nullptr;

   //   //return hdc;

   //   return nullptr;

   //}


   //bool graphics::AttachPrinter(HDC hdc)
   //{

   //   //if (hdc == nullptr)
   //   //   return false;

   //   //if (m_hdc == hdc)
   //   //{

   //   //   return true;

   //   //}

   //   //if (hdc != nullptr)
   //   //{

   //   //   m_hdc = (HDC)hdc;

   //   //}

   //   //return m_hdc != nullptr;

   //   return true;

   //}


   //HDC graphics::DetachPrinter()
   //{

   //   //if (m_hdc == nullptr)
   //   //   return nullptr;

   //   //HDC hdc = m_hdc;

   //   //m_hdc = nullptr;

   //   //return hdc;

   //   return nullptr;

   //}


   void graphics::DeleteDC()
   {



      //HDC hdc = Detach();

      //if(hdc != nullptr)
      //{

      //   bool bDeleted = ::DeleteDC(hdc) != false;

      //   if(!bDeleted)
      //   {

      //      informationf("graphics::DeleteDC : Failed to delete GDI device context");

      //   }

      //}

      //if(m_pgraphics != nullptr)
      //{

      //   try
      //   {

      //      delete m_pgraphics;

      //   }
      //   catch(...)
      //   {

      //      informationf("graphics::DeleteDC : Failed to delete plusplus::Graphics");

      //   }

      //   m_pgraphics = nullptr;

      //}

      //if(m_ppath != nullptr)
      //{

      //   try
      //   {

      //      delete m_ppath;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppath = nullptr;

      //}

      //if(m_ppathPaint != nullptr)
      //{

      //   try
      //   {

      //      delete m_ppathPaint;

      //   }
      //   catch(...)
      //   {

      //   }

      //   m_ppathPaint = nullptr;

      //}

      //if (m_hdc != nullptr)
      //{

      //   //::ReleaseDC(m_hwnd, m_hdc);

      //}

      //return true;

   }


//   void graphics::SetAttribDC(HDC hDC)  // set the Attribute DC
//   {
////      set_handle2(hDC);
//   }
//
//
//   void graphics::SetOutputDC(HDC hDC)  // set the Output DC
//   {
//#ifdef _DEBUG
//      /*      hdc_map* pMap = ::windows_definition::MapHDC();
//            if (pMap != nullptr && pMap->lookup_permanent(m_hdc) == this)
//            {
//               information(trace_category_appmsg, 0, "Cannot set Output hDC on Attached graphics.\n");
//               ASSERT(false);
//            }*/
//#endif
//      //    set_handle1(hDC);
//   }
//
//
//   void graphics::ReleaseAttribDC()     // Release the Attribute DC
//   {
////      set_handle2(nullptr);
//   }
//
//
//   void graphics::ReleaseOutputDC()     // Release the Output DC
//   {
//#ifdef _DEBUG
//      /*      hdc_map* pMap = ::windows_definition::MapHDC();
//            if (pMap != nullptr && pMap->lookup_permanent(m_hdc) == this)
//            {
//               information(trace_category_appmsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
//               ASSERT(false);
//            }*/
//#endif
//      //set_handle1(nullptr);
//   }

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int graphics::StartDoc(const ::scoped_string & lpszDocName)
   {
      //DOCINFO di;
      //memory_set(&di, 0, sizeof(DOCINFO));
      //di.cbSize = sizeof(DOCINFO);
      //di.lpszDocName = lpszDocName;
      //return StartDoc(&di);
      return -1;
   }

   
   int graphics::save_graphics_context()
   {
//      return m_pgraphics->Save();
      return 0;

   }

   
   void graphics::restore_graphics_context(int iSavedContext)
   {

      //return m_pgraphics->Restore(nSavedDC) != false;
      //return true;

   }

//   ::draw2d::object* graphics::SelectGdiObject(::particle * pparticle, HDC hDC, HGDIOBJ h)
   // {
//      return ::draw2d_vulkan::object::from_handle(papp, ::SelectObject(hDC, h));
   //}
   ::draw2d_vulkan::draw2d * graphics::draw2d_vulkan()
   {

      return dynamic_cast < ::draw2d_vulkan::draw2d * >(system()->draw2d());

   }

   ::draw2d::object* graphics::SelectStockObject(int nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
            HGDIOBJ hOldObj = nullptr;
            ASSERT(hObject != nullptr);
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, hObject);
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, hObject);
            return ::draw2d_vulkan::object::from_handle(get_app(), hOldObj);*/

      return nullptr;

   }


   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* pPen)
   {
      /*HGDIOBJ hOldObj = nullptr;
      if(pPen == nullptr)
         return nullptr;
      if(m_hdc != nullptr && m_hdc != m_hdc)
         hOldObj = ::SelectObject(m_hdc, pPen->get_os_data());
      if(m_hdc != nullptr)
         hOldObj = ::SelectObject(m_hdc, pPen->get_os_data());
      return dynamic_cast < pen * > (::draw2d_vulkan::object::from_handle(get_app(), hOldObj));*/
      m_ppen = pPen;
      return m_ppen;

   }


   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pBrush)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pBrush == nullptr)
               return nullptr;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, pBrush->get_os_data());
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, pBrush->get_os_data());
            return dynamic_cast < ::draw2d::brush * > (::draw2d_vulkan::object::from_handle(get_app(), hOldObj));*/
      m_pbrush = pBrush;

      return m_pbrush;

   }


   ::write_text::font* graphics::SelectObject(::write_text::font* pfont)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pFont == nullptr)
               return nullptr;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               hOldObj = ::SelectObject(m_hdc, pFont->get_os_data());
            if(m_hdc != nullptr)
               hOldObj = ::SelectObject(m_hdc, pFont->get_os_data());
            return dynamic_cast < ::write_text::font * > (::draw2d_vulkan::object::from_handle(get_app(), hOldObj));*/

      /*ASSERT(pFont != nullptr);

      if(pFont == nullptr)
         return nullptr;

      m_fontxyz = *pFont;
      return &m_fontxyz;*/

      //if(!set(pfont))
        // return nullptr;

      set(pfont);

      return m_pfont;

   }


   int graphics::SelectObject(::draw2d::region* pRgn)
   {
      int nRetVal = GDI_ERROR;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = (double)(iptr)::SelectObject(m_hdc, (HGDIOBJ) pRgn->get_os_data());
      //if(m_hdc != nullptr)
      //   nRetVal = (double)(iptr)::SelectObject(m_hdc, (HGDIOBJ) pRgn->get_os_data());
      return nRetVal;

   }


   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return nullptr;
//      return dynamic_cast < ::draw2d::palette * > (::draw2d_vulkan::object::from_handle(get_app(), ::SelectPalette(m_hdc, (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }


   int graphics::SetPolyFillMode(int nPolyFillMode)
   {
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetPolyFillMode(m_hdc, nPolyFillMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetPolyFillMode(m_hdc, nPolyFillMode);
      return nRetVal;

   }


   int graphics::SetROP2(int nDrawMode)
   {
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetROP2(m_hdc, nDrawMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetROP2(m_hdc, nDrawMode);
      return nRetVal;

   }


   int graphics::set_interpolation_mode(int nStretchMode)
   {

      //if(m_pgraphics == nullptr)
      //{

      //   return -1;

      //}

      //if(nStretchMode == 0)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeNearestNeighbor);
      //}
      //else if(nStretchMode == e_interpolation_mode_high_quality_bicubic)
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeHighQualityBicubic);
      //}
      //else
      //{
      //   m_pgraphics->SetInterpolationMode(plusplus::InterpolationModeLowQuality);
      //}
      //return 1;

      return true;

      /*double nRetVal = 0;
      if(m_hdc != nullptr && m_hdc != m_hdc)
         nRetVal = ::set_interpolation_mode(m_hdc, nStretchMode);
      if(m_hdc != nullptr)
         nRetVal = ::set_interpolation_mode(m_hdc, nStretchMode);
      return nRetVal;*/
   }


   int graphics::SetGraphicsMode(int iMode)
   {
   
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //{
      //   nRetVal = ::SetGraphicsMode(m_hdc, iMode);
      //}
      //if(m_hdc != nullptr)
      //{
      //   nRetVal = ::SetGraphicsMode(m_hdc, iMode);
      //}
      return nRetVal;

   }


   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      //plusplus::REAL ::double_rectangle[6];

      //::double_rectangle[0] = pXform->eDx;
      //::double_rectangle[1] = pXform->eDy;

      //::double_rectangle[2] = pXform->eM11;
      //::double_rectangle[3] = pXform->eM12;
      //::double_rectangle[4] = pXform->eM21;
      //::double_rectangle[5] = pXform->eM22;

      //plusplus::Matrix m;

      //m.SetElements(::double_rectangle[2],::double_rectangle[3],::double_rectangle[4],::double_rectangle[5],::double_rectangle[0],::double_rectangle[1]);

      //m_pgraphics->SetTransform(&m);

      return true;

   }


   bool graphics::ModifyWorldTransform(const XFORM* pXform,unsigned int iMode)
   {
      bool nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //{
      //   nRetVal = ::ModifyWorldTransform(m_hdc, pXform, iMode) != false;
      //}
      //if(m_hdc != nullptr)
      //{
      //   nRetVal = ::ModifyWorldTransform(m_hdc, pXform, iMode) != false;
      //}
      return nRetVal;

   }


   int graphics::SetMapMode(int nMapMode)
   {
      int nRetVal = 0;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::SetMapMode(m_hdc, nMapMode);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetMapMode(m_hdc, nMapMode);
      return nRetVal;

   }


   //int_point graphics::get_origin() const
   //{

   //   return ::draw2d::graphics::get_origin();

   //   //::int_point point;
   //   //::GetContextOrgEx(m_hdc, &point);

   //   //if (m_pgraphics == nullptr)
   //   //{

   //   //   return ::int_point();

   //   //}

   //   //plusplus::Point origin(0, 0);

   //   //m_pgraphics->TransformPoints(
   //   //   plusplus::CoordinateSpacePage,
   //   //   plusplus::CoordinateSpaceWorld,
   //   //   &origin,
   //   //   1);

   //   //return point((long long) origin.X, (long long) origin.Y);

   //   //return m_pointTranslate;

   //}


   void graphics::_set(const ::geometry2d::matrix & matrix)
   {

      thread_select();

      //vkMatrixMode(VK_MODELVIEW);
      //vkLoadIdentity();

///      VKdouble m[16];
      
      //vkGetDoublev(VK_MODELVIEW_MATRIX, m);

      //vkTranslatef(matrix.c1, matrix.c2, 0.f);

      //vkGetDoublev(VK_MODELVIEW_MATRIX, m);


      double m[16];

      m[0] = matrix.a1;
      m[1] = matrix.b1;
      //m[2] = matrix.c1;
      m[2] = 0.0;
      m[3] = 0.0;
      
      m[4] = matrix.a2;
      m[5] = matrix.b2;
      //m[6] = matrix.c2;
      m[6] = 0.0;
      m[7] = 0.0;
      
      m[8] = 0.0;
      m[9] = 0.0;
      m[10] = 1.0;
      m[11] = 0.0;
      
      m[12] = matrix.c1;
      m[13] = matrix.c2;
      m[14] = 0.0;
      m[15] = 1.0;

      //vkLoadMatrixd((const VKdouble *) m);

      //return false;

   }


   int_point graphics::set_origin(int x, int y)
   {

      return ::draw2d::graphics::set_origin(x, y);

   }


   int_point graphics::offset_origin(int nWidth, int nHeight)
   {

      return ::draw2d::graphics::offset_origin(nWidth, nHeight);


   }


   //int_size graphics::set_context_extents(int x, int y)
   //{

   //   return ::draw2d::graphics::set_context_extents(x, y);

   //   //int_size size(0, 0);
   //   ////if(m_hdc != nullptr && m_hdc != m_hdc)
   //   ////   ::Set_wiewportExtEx(m_hdc, x, y, &size);
   //   ////if(m_hdc != nullptr)
   //   ////   ::Set_wiewportExtEx(m_hdc, x, y, &size);
   //   //return size;

   //}


   //int_size graphics::scale_context_extents(int xNum, int xDenom, int yNum, int yDenom)
   //{

   //   return ::draw2d::graphics::scale_context_extents(xNum, xDenom, yNum, yDenom);

   //   //int_size size(0, 0);
   //   ////if(m_hdc != nullptr && m_hdc != m_hdc)
   //   ////   ::scale_context_extentsEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
   //   ////if(m_hdc != nullptr)
   //   ////   ::scale_context_extentsEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
   //   //return size;
   //}

   
   int_point graphics::SetWindowOrg(int x, int y)
   {
      
      ::int_point point;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetWindowOrgEx(m_hdc, x, y, &point);
      //if(m_hdc != nullptr)
      //   ::SetWindowOrgEx(m_hdc, x, y, &point);
      return point;

   }

   
   int_point graphics::offset_window_org(int nWidth, int nHeight)
   {
      
      ::int_point point;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::OffsetWindowOrgEx(m_hdc, nWidth, nHeight, &point);
      //if(m_hdc != nullptr)
      //   ::OffsetWindowOrgEx(m_hdc, nWidth, nHeight, &point);
      return point;

   }

   
   int_size graphics::set_window_ext(int x, int y)
   {
   
      int_size size(0, 0);
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetWindowExtEx(m_hdc, x, y, &size);
      //if(m_hdc != nullptr)
      //   ::SetWindowExtEx(m_hdc, x, y, &size);
      return size;

   }


   int_size graphics::scale_window_ext(int xNum, int xDenom, int yNum, int yDenom)
   {
   
      int_size size(0, 0);
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::ScaleWindowExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      //if(m_hdc != nullptr)
      //   ::ScaleWindowExtEx(m_hdc, xNum, xDenom, yNum, yDenom, &size);
      return size;

   }


   int graphics::get_clip_box(::double_rectangle * prectangle) const
   {

      //plusplus::double_rectangle ::double_rectangle;

      //m_pgraphics->GetClipBounds(rectangle);

      //rectangle.left() = rectangle.X;
      //rectangle.top() = rectangle.Y;
      //rectangle.right() = rectangle.X + rectangle.Width;
      //rectangle.bottom() = rectangle.Y + rectangle.Height;

      return 1;

   }


   int graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      //if(pregion == nullptr)
      //{
      //   m_pgraphics->ResetClip();
      //}
      //else
      //{
      //   m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data());
      //}

      return 0;

      /*      double nRetVal = ERROR;
            if(m_hdc != nullptr && m_hdc != m_hdc)
               nRetVal = ::SelectClipRgn(m_hdc, pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            if(m_hdc != nullptr)
               nRetVal = ::SelectClipRgn(m_hdc, pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            return nRetVal;*/
   }


   int graphics::ExcludeClipRect(int x1, int y1, int x2, int y2)
   {

      //double nRetVal = ERROR;
      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::ExcludeClipRect(m_hdc, x1, y1, x2, y2);
      //if(m_hdc != nullptr)
      //   nRetVal = ::ExcludeClipRect(m_hdc, x1, y1, x2, y2);

      //return nRetVal;

      return 0;

   }


   int graphics::ExcludeClipRect(const ::int_rectangle & rectangleParam)
   {
      
      //double nRetVal = ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::ExcludeClipRect(m_hdc, rectangleParam.left(), rectangleParam.top(),
      //                               rectangleParam.right(), rectangleParam.bottom());
      //if(m_hdc != nullptr)
      //   nRetVal = ::ExcludeClipRect(m_hdc, rectangleParam.left(), rectangleParam.top(),
      //                               rectangleParam.right(), rectangleParam.bottom());

      //return nRetVal;

      return 0;

   }


   int graphics::IntersectClipRect(int x1, int y1, int x2, int y2)
   {
      
      //double nRetVal = ERROR;

      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::IntersectClipRect(m_hdc, x1, y1, x2, y2);
      //if(m_hdc != nullptr)
      //   nRetVal = ::IntersectClipRect(m_hdc, x1, y1, x2, y2);

      return nRetVal;

   }


   int graphics::IntersectClipRect(const ::int_rectangle & rectangleBounds)
   {
      
      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::IntersectClipRect(m_hdc,rectangleBounds.left(),rectangleBounds.top(),rectangleBounds.right(),rectangleBounds.bottom());
      //if(m_hdc != nullptr)
      //   nRetVal = ::IntersectClipRect(m_hdc,rectangleBounds.left(),rectangleBounds.top(),rectangleBounds.right(),rectangleBounds.bottom());

      return nRetVal;

   }


   int graphics::OffsetClipRgn(int x, int y)
   {
      
      int nRetVal = 0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::OffsetClipRgn(m_hdc, x, y);
      //if(m_hdc != nullptr)
      //   nRetVal = ::OffsetClipRgn(m_hdc, x, y);

      return nRetVal;

   }


   int graphics::OffsetClipRgn(const ::int_size & size)
   {
      
      int nRetVal =0;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   nRetVal = ::OffsetClipRgn(m_hdc, size.cx(), size.cy());
      //if(m_hdc != nullptr)
      //   nRetVal = ::OffsetClipRgn(m_hdc, size.cx(), size.cy());

      return nRetVal;

   }


   unsigned int graphics::SetTextAlign(unsigned int nFlags)
   {
      
      unsigned int nRetVal = GDI_ERROR;

      //if(m_hdc != nullptr && m_hdc != m_hdc)
      //   ::SetTextAlign(m_hdc, nFlags);
      //if(m_hdc != nullptr)
      //   nRetVal = ::SetTextAlign(m_hdc, nFlags);

      return nRetVal;

   }


   //int graphics::SetTextJustification(int nBreakExtra, int nBreakCount)
   //{
   // 
   //   double nRetVal = 0;

   //   //if(m_hdc != nullptr && m_hdc != m_hdc)
   //   //   nRetVal = ::SetTextJustification(m_hdc, nBreakExtra, nBreakCount);
   //   //if(m_hdc != nullptr)
   //   //   nRetVal = ::SetTextJustification(m_hdc, nBreakExtra, nBreakCount);

   //   return nRetVal;

   //}


   //double graphics::SetTextCharacterExtra(double nCharExtra)
   //{
   //   
   //   // ASSERT(m_hdc != nullptr);

   //   double nRetVal = 0x8000000;
   //   
   //   //if(m_hdc != nullptr && m_hdc != m_hdc)
   //   //   nRetVal = ::SetTextCharacterExtra(m_hdc, nCharExtra);
   //   //if(m_hdc != nullptr)
   //   //   nRetVal = ::SetTextCharacterExtra(m_hdc, nCharExtra);

   //   return nRetVal;

   //}


   //unsigned int graphics::SetMapperFlags(unsigned int dwFlag)
   //{
   //   
   //   // ASSERT(m_hdc != nullptr);

   //   unsigned int dwRetVal = GDI_ERROR;

   //   //if(m_hdc != nullptr && m_hdc != m_hdc)
   //   //   dwRetVal = ::SetMapperFlags(m_hdc, dwFlag);
   //   //if(m_hdc != nullptr)
   //   //   dwRetVal = ::SetMapperFlags(m_hdc, dwFlag);

   //   return dwRetVal;

   //}


   typedef unsigned int (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   typedef unsigned int (CALLBACK* __GDISETLAYOUTPROC)(HDC, unsigned int);

   unsigned int graphics::GetLayout() const
   {
      
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");

      ASSERT(hInst != nullptr);

      /*      unsigned int dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(m_hdc);
            else
            {
               dwGetLayout = GDI_ERROR;
               set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
            }*/

      //return dwGetLayout;

      return 0;

   }


   unsigned int graphics::SetLayout(unsigned int dwSetLayout)
   {
      /*HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      unsigned int dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != nullptr)
         dwGetLayout = (*pfn)(m_hdc, dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;*/

      return 0;

   }
   /*
   void window::screen_to_client(::double_rectangle * prectangle)
   {
   ASSERT(::IsWindow(m_hdc));
   ::screen_to_client(m_hdc, (::double_point *)::double_rectangle);
   ::screen_to_client(m_hdc, ((::double_point *)::double_rectangle)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   ::double_rectangle::swap_left_right(rectangle);
   }

   void window::client_to_screen(::double_rectangle * prectangle)
   {
   ASSERT(::IsWindow(m_hdc));
   ::client_to_screen(m_hdc, (::double_point *)::double_rectangle);
   ::client_to_screen(m_hdc, ((::double_point *)::double_rectangle)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   ::double_rectangle::swap_left_right(rectangle);
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   void graphics::arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {
      // ASSERT(m_hdc != nullptr);
      bool bResult = false;
      //bool bResult = ::ArcTo(m_hdc, x1, y1, x2, y2, x3, y3, x4, y4) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::int_point point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x(), point.y(), nullptr));
      //}
      //return bResult;
   }


   //double graphics::SetArcDirection(double nArcDirection)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   double nResult = 0;
   //   //if (m_hdc != m_hdc)
   //   //   nResult = ::SetArcDirection(m_hdc, nArcDirection);
   //   //if (m_hdc != nullptr)
   //   //   nResult = ::SetArcDirection(m_hdc, nArcDirection);
   //   return nResult;
   //}

   //bool graphics::PolyDraw(const ::double_point* lpPoints, const unsigned char* lpTypes, ::collection::count nCount)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   bool bResult = false;
   //   //bool bResult = ::PolyDraw(m_hdc, lpPoints, lpTypes, (int) nCount) != false;

   //   //if (m_hdc != m_hdc)
   //   //{
   //   //   ::int_point point;
   //   //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
   //   //   VERIFY(::MoveToEx(m_hdc, point.x(), point.y(), nullptr));
   //   //}
   //   return bResult;
   //}

   void graphics::polyline_to(const ::double_point* lpPoints, ::collection::count nCount)
   {
      // ASSERT(m_hdc != nullptr);
      //bool bResult = false;
      //bool bResult = ::polyline_to(m_hdc, lpPoints, (unsigned int) nCount) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::int_point point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x(), point.y(), nullptr));
      //}
      //return bResult;
   }


   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {
      // ASSERT(m_hdc != nullptr);
      bool bResult = false;
      //if (m_hdc != m_hdc)
      //   bResult = ::SetColorAdjustment(m_hdc, lpColorAdjust) != false;
      //if (m_hdc != nullptr)
      //   bResult = ::SetColorAdjustment(m_hdc, lpColorAdjust) != false;
      return bResult;
   }

   
   void graphics::poly_bezier_to(const ::double_point* lpPoints, ::collection::count nCount)
   {
      // ASSERT(m_hdc != nullptr);
      //bool bResult = false;      //bool bResult = ::poly_bezier_to(m_hdc, lpPoints, (unsigned int) nCount) != false;
      //if (m_hdc != m_hdc)
      //{
      //   ::int_point point;
      //   VERIFY(::GetCurrentPositionEx(m_hdc, &point));
      //   VERIFY(::MoveToEx(m_hdc, point.x(), point.y(), nullptr));
      //}
      //return bResult;
   }


   void graphics::SelectClipPath(int nMode)
   {
      // ASSERT(m_hdc != nullptr);

      //bool bResult = false;

      //// output DC always holds the current path
      //if (!::SelectClipPath(m_hdc, nMode))
      //   return false;

      //// transfer clipping region into the attribute DC
      //bool bResult = true;
      //if (m_hdc != m_hdc)
      //{
      //   HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
      //   if (::GetClipRgn(m_hdc, hRgn) < 0 || !::SelectClipRgn(m_hdc, hRgn))
      //   {
      //      INFO(trace_category_appmsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
      //      bResult = false;
      //   }
      //   ::DeleteObject(hRgn);
      //}
      //return bResult;
   }


   int graphics::SelectClipRgn(::draw2d::region* pregion, int nMode)
   {

      //if(pregion == nullptr)
      //{

      //   m_pgraphics->ResetClip();

      //}
      //else
      //{

      //   if(nMode == RGN_AND)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(), plusplus::CombineModeIntersect);

      //   }
      //   else if(nMode == RGN_OR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeUnion);

      //   }
      //   else if(nMode == RGN_XOR)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeXor);

      //   }
      //   else if(nMode == RGN_COPY)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeReplace);

      //   }
      //   else if(nMode == RGN_DIFF)
      //   {

      //      m_pgraphics->SetClip((plusplus::Region *) pregion->get_os_data(),plusplus::CombineModeExclude);

      //   }

      //}

      return 0;

   }


   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback

   double CALLBACK __enum_meta_file_procedure(HDC hDC,
         HANDLETABLE* pHandleTable, METARECORD* pMetaRec, double nHandles, LPARAM lParam)
   {
      return 1;
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;
//      ASSERT_VALID(pgraphics);
//
//      switch (pMetaRec->rdFunction)
//      {
//      // these records have effects different for each graphics derived class
//      case META_SETMAPMODE:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SetMapMode((double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SETWINDOWEXT:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->set_window_ext(
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SETWINDOWORG:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SetWindowOrg(
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SETVIEWPORTEXT:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->set_context_extents(
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SETVIEWPORTORG:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->set_origin(
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SCALEWINDOWEXT:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->scale_window_ext(
//         (double)(short)pMetaRec->rdParm[3], (double)(short)pMetaRec->rdParm[2],
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SCALEVIEWPORTEXT:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->scale_context_extents(
//         (double)(short)pMetaRec->rdParm[3], (double)(short)pMetaRec->rdParm[2],
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_OFFSETVIEWPORTORG:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->offset_origin(
//         (double)(short)pMetaRec->rdParm[1], (double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SAVEDC:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SaveDC();
//         break;
//      case META_RESTOREDC:
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->RestoreDC((double)(short)pMetaRec->rdParm[0]);
//         break;
//      case META_SETBKCOLOR:
//      {
//         auto pbrush = __øcreate < ::draw2d::brush >();
//         
//         pbrush->create_solid(*(UNALIGNED color32_t*)& pMetaRec->rdParm[0]);
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SelectObject(brush);
//      }
//      break;
//      case META_SETTEXTCOLOR:
//      {
//         ::draw2d::brush_pointer brush((dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->create_new, this, *(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
//         (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SelectObject(brush);
//      }
//      break;
//
//      // need to watch out for SelectObject(HFONT), for custom font mapping
//      case META_SELECTOBJECT:
//      {
//         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
//         unsigned int nObjType = GetObjectType(hObject);
//         if (nObjType == 0)
//         {
//            // object type is unknown, determine if it is a font
//            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
//            HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->m_hdc, hStockFont);
//            HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->m_hdc, hObject);
//            if (hObjOld == hStockFont)
//            {
//               // got the stock object back, so must be selecting a font
//               throw ::not_implemented();
////                  (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SelectObject(::draw2d_vulkan::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
//               break;  // don't play the default record
//            }
//            else
//            {
//               // didn't get the stock object back, so restore everything
//               ::SelectObject((dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->m_hdc, hFontOld);
//               ::SelectObject((dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->m_hdc, hObjOld);
//            }
//            // and fall through to PlayMetaFileRecord...
//         }
//         else if (nObjType == OBJ_FONT)
//         {
//            // play back as graphics::SelectObject(::write_text::font*)
////               (dynamic_cast<::draw2d_vulkan::graphics * >(pgraphics))->SelectObject(::draw2d_vulkan::font::from_handle(pgraphics->get_app(), (HFONT)hObject));
//            throw ::not_implemented();
//            break;  // don't play the default record
//         }
//      }
//      // fall through...
//
//      default:
//         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
//         break;
//      }
//
//      return 1;
   }


   //bool graphics::PlayMetaFile(HMETAFILE hMF)
   //{
   //   //if (::GetDeviceCaps(m_hdc, TECHNOLOGY) == DT_METAFILE)
   //   //{
   //   //   // playing metafile in metafile, just use aura windows API
   //   //   return ::PlayMetaFile(m_hdc, hMF) != false;
   //   //}

   //   //// for special playback, lParam == pgraphics
   //   //return ::EnumMetaFile(m_hdc, hMF, __enum_meta_file_procedure, (LPARAM)this) != false;
   //   return false;

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   
   void graphics::LPtoDP(::double_size *LPSIZE32) 
   {

      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

      //int_size sizeWinExt = GetWindowExt();
      //int_size sizeVpExt = get_context_extents();
      //LPSIZE32->cx() = MulDiv(LPSIZE32->cx(), abs(sizeVpExt.cx()), abs(sizeWinExt.cx()));
      //LPSIZE32->cy() = MulDiv(LPSIZE32->cy(), abs(sizeVpExt.cy()), abs(sizeWinExt.cy()));

   }


   void graphics::DPtoLP(::double_size  * psize)
   {

      //ASSERT(is_memory_segment_ok(LPSIZE32, sizeof(::int_size)));

      //int_size sizeWinExt = GetWindowExt();
      //int_size sizeVpExt = get_context_extents();
      //LPSIZE32->cx() = MulDiv(LPSIZE32->cx(), abs(sizeWinExt.cx()), abs(sizeVpExt.cx()));
      //LPSIZE32->cy() = MulDiv(LPSIZE32->cy(), abs(sizeWinExt.cy()), abs(sizeVpExt.cy()));

   }


   void graphics::draw_text(const ::scoped_string & str,const ::double_rectangle & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      //::double_rectangle rectangle;

      //copy(rectangle,&rectangleParam);

      //return draw_text(str, rectangle, ealign, edrawtext);


   }


   void graphics::draw_text(const ::scoped_string & str, const ::int_rectangle & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      //try
      //{

      //   if(m_pgraphics == nullptr)
      //      return false;

      //   /*

      //   switch(m_ewritetextrendering)
      //   {
      //   case ::write_text::e_rendering_anti_alias:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);
      //      break;
      //   case ::write_text::e_rendering_anti_alias_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAliasGridFit);
      //      break;
      //   case ::write_text::e_rendering_single_bit_per_pixel:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintSingleBitPerPixel);
      //      break;
      //   case ::write_text::e_rendering_clear_type_grid_fit:
      //      m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //      m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintClearTypeGridFit);
      //      break;
      //   }

      //   */
      //   m_pgraphics->SetCompositingMode(plusplus::CompositingModeSourceOver);
      //   m_pgraphics->SetTextRenderingHint(plusplus::TextRenderingHintAntiAlias);


      //}
      //catch(...)
      //{
      //}



      //plusplus::StringFormat format(plusplus::StringFormat::GenericTypographic());


      //format.SetFormatFlags(format.GetFormatFlags()
      //                      | plusplus::StringFormatFlagsNoClip | plusplus::StringFormatFlagsMeasureTrailingSpaces
      //                      | plusplus::StringFormatFlagsLineLimit);

      //if(nFormat & e_align_left)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & e_align_right)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & e_align_horizontal_center)
      //{
      //   format.SetAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetAlignment(plusplus::StringAlignmentNear);
      //}

      //if(nFormat & e_align_bottom)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentFar);
      //}
      //else if(nFormat & e_align_top)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}
      //else if(nFormat & e_align_vertical_center)
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentCenter);
      //}
      //else
      //{
      //   format.SetLineAlignment(plusplus::StringAlignmentNear);
      //}

      //plusplus::REAL stops[] = {16,32,48, 64,80,96,112,128};

      //format.SetTabStops(0,8,stops);

      ////m_dFontSize             = pfontSrc.m_dFontSize;

      //plusplus::Matrix m;
      //m_pgraphics->GetTransform(&m);
      //plusplus::Matrix * pmNew = m.Clone();
      //try
      //{


      //   pmNew->Translate((plusplus::REAL) rectangleParam.left(),(plusplus::REAL) rectangleParam.top());
      //   pmNew->Scale((plusplus::REAL) m_pfont->m_dFontWidth,(plusplus::REAL) 1.0,plusplus::MatrixOrderAppend);

      //   plusplus::rectF float_rectangle(0,0,(plusplus::REAL) ((rectangleParam.right() - rectangleParam.left()) * m_pfont->m_dFontWidth),(plusplus::REAL) (rectangleParam.bottom() - rectangleParam.top()));

      //   m_pgraphics->SetTransform(pmNew);

      //   m_pgraphics->DrawString(utf8_to_unicode(str),-1,vk2d_font(),float_rectangle,&format,vk2d_brush());
      //}
      //catch(...)
      //{
      //}

      //m_pgraphics->SetTransform(&m);

      //delete pmNew;

      //return 1;

   }


   //void graphics::draw_text_ex(const ::scoped_string & str, const ::int_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   // these flags would modify the string
   //   //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
   //   //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
   //   //wstring wstr = utf8_to_unicode(str);
   //   //return ::DrawTextExW(m_hdc,const_cast<wchar_t *>((const wchar_t *)wstr),(double)wcslen(wstr),(::double_rectangle *) &rectangleParam,nFormat,lpDTParams);
   //   
   //   //return false;

   //}


   //void graphics::draw_text_ex(const ::scoped_string & str,const ::int_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   ::draw2d::graphics::draw_text_ex(str,rectangleParam,ealign, edrawtext,lpDTParams);

   //}


   //double_size graphics::get_text_extent(const ::scoped_string & lpszString, character_count nCount, character_count iIndex)
   double_size graphics::get_text_extent(const ::scoped_string & lpszString)
   {

      //if(lpszString.is_empty())
      //   return int_size(0, 0);

      return int_size(0, 0);

      //wstring wstr = lpszString;

      //character_count iRange = 0;
      //character_count i = 0;
      //character_count iLen;
      //const ::scoped_string & scopedstr = lpszString;
      //while(i < iIndex)
      //{
      //   iLen = ::str::get_utf8_char(psz).length();
      //   iRange++;
      //   i += iLen;
      //   unicode_increment(psz);
      //   if(psz == nullptr)
      //      break;
      //   if(*psz == '\0')
      //      break;
      //}

      //set(m_pfont);

      //::pointer<font>pfont = m_pfont;

      //::int_size s = { 0 };

      //::GetTextExtentPointW(pfont->m_hdcFont, wstr, wstr.get_length(), &s);

      //return s;

   }


   //double_size graphics::get_text_extent(const ::string & lpszString, character_count nCount)
   //{

   //   ::double_size size;

   //   if (!get_text_extent(size, lpszString, nCount, 0))
   //      return ::int_size(0, 0);

   //   return ::int_size(size.cx(), size.cy());

   //}


  /* double_size graphics::get_text_extent(const ::scoped_string & str)
   {

      ::double_size size;

      if(!get_text_extent(size, str, (double) str.length(), 0))
         return ::int_size(0, 0);

      return ::int_size((long) size.cx(), (long) size.cy());

   }*/


   //int_size graphics::GetOutputTextExtent(const ::string & lpszString, character_count nCount)
   //{
   //   // ASSERT(m_hdc != nullptr);
   //   ::int_size size;
   //   //string str(lpszString, nCount);
   //   //wstring wstr = utf8_to_unicode(str);
   //   //VERIFY(::GetTextExtentPoint32W(m_hdc, wstr, (double)wstr.get_length(), &size));
   //   return size;

   //}


   //int_size graphics::GetOutputTextExtent(const ::string & str)
   //{

   //   // ASSERT(m_hdc != nullptr);

   //   ::int_size size;

   //   wstring wstr = utf8_to_unicode(str);

   //   //::GetTextExtentPoint32W(m_hdc, wstr, (double)wstr.get_length(), &size);

   //   return size;

   //}

//
//   bool graphics::get_text_extent(double_size & size, const ::string & lpszString, character_count nCount, character_count iIndex)
//   {
//
//      //// ASSERT(m_hdc != nullptr);
//
//      set(m_pfont);
//
//      ::pointer<font>pfont = m_pfont;
//
//      ::int_size s;
//
//      wstring wstr = utf8_to_unicode(string(&lpszString[iIndex], nCount));
//
//      //if (!::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (double)wstr.get_length(), &s))
////         return false;
//
//      //// FreeType
//      //FT_Library ft;
//      //// All functions return a value different than 0 whenever an error occurred
//      //if (FT_Init_FreeType(&ft))
//      //   std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//
//      //// Load font as face
//      //FT_Face face;
//      //if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
//      //   std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//
//      //// Set int_size to load vkyphs as
//      //FT_Set_Pixel_Sizes(face, 0, 48);
//
//      //// Disable unsigned char-alignment restriction
//      //vkPixelStorei(VK_UNPACK_ALIGNMENT, 1);
//
//      //// Load first 128 characters of ASCII set
//      //for (VKubyte c = 0; c < 128; c++)
//      //{
//      //   // Load character vkyph 
//      //   if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//      //   {
//      //      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//      //      continue;
//      //   }
//      //   // Generate texture
//      //   VKuint texture;
//      //   vkGenTextures(1, &texture);
//      //   vkBindTexture(VK_TEXTURE_2D, texture);
//      //   vkTexImage2D(
//      //      VK_TEXTURE_2D,
//      //      0,
//      //      VK_RED,
//      //      face->vkyph->bitmap.width,
//      //      face->vkyph->bitmap.rows,
//      //      0,
//      //      VK_RED,
//      //      VK_UNSIGNED_BYTE,
//      //      face->vkyph->bitmap.buffer
//      //   );
//      //   // Set texture options
//      //   vkTexParameteri(VK_TEXTURE_2D, VK_TEXTURE_WRAP_S, VK_CLAMP_TO_EDGE);
//      //   vkTexParameteri(VK_TEXTURE_2D, VK_TEXTURE_WRAP_T, VK_CLAMP_TO_EDGE);
//      //   vkTexParameteri(VK_TEXTURE_2D, VK_TEXTURE_MIN_FILTER, VK_LINEAR);
//      //   vkTexParameteri(VK_TEXTURE_2D, VK_TEXTURE_MAG_FILTER, VK_LINEAR);
//      //   // Now store character for later use
//      //   Character character = {
//      //       texture,
//      //       vkm::ivec2(face->vkyph->bitmap.width, face->vkyph->bitmap.rows),
//      //       vkm::ivec2(face->vkyph->bitmap_left, face->vkyph->bitmap_top),
//      //       face->vkyph->advance.x()
//      //   };
//      //   Characters.insert(std::pair<VKchar, Character>(c, character));
//      //}
//      //vkBindTexture(VK_TEXTURE_2D, 0);
//      //// Destroy FreeType once we're finished
//      //FT_Done_Face(face);
//      //FT_Done_FreeType(ft);
//
//      size.cx() = s.cx();
//
//      size.cy() = s.cy();
//
//      return true;
//
//   }
//
//
//   bool graphics::get_text_extent(double_size & size, const ::string & lpszString, character_count nCount)
//   {
//
//      //// ASSERT(m_hdc != nullptr);
//
//      set(m_pfont);
//
//      ::pointer<font>pfont = m_pfont;
//
//      ::int_size s;
//
//      wstring wstr = utf8_to_unicode(lpszString, nCount);
//
//      //if (!::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (double)wstr.get_length(), &s))
//        // return false;
//
//      size.cx() = s.cx();
//
//      size.cy() = s.cy();
//
//      return true;
//
//   }
//
//
//   bool graphics::get_text_extent(double_size & size, const ::string & str)
//   {
//
//      //// ASSERT(m_hdc != nullptr);
//
//      set(m_pfont);
//
//      ::pointer<font>pfont = m_pfont;
//
//      ::int_size s;
//
//      wstring wstr = utf8_to_unicode(str);
//
//      //if (::GetTextExtentPoint32W(pfont->m_hdcFont, wstr, (double)wstr.get_length(), &s))
//        // return false;
//
//      size.cx() = s.cx();
//
//      size.cy() = s.cy();
//
//      return true;
//
//   }


   //void graphics::fill_rectangle(const double_rectangle& rectangle, color32_t color32)
   //{

   //   try
   //   {

   //      if (m_pbitmap.is_set())
   //      {


   //         ::int_size s = m_pbitmap.cast < bitmap>()->m_sizeOut;

   //         if (s.area() <= 0)
   //         {

   //            return;

   //         }

   //      }

   //      vkBegin(VK_QUADS);

   //      ::vulkan::color(color32);

   //      ::vulkan::vertex2f(rectangle);

   //      vkEnd();

   //   }
   //   catch(...)
   //   {
   //      
   //   }

   //}


   void graphics::draw_line(const int_point& point1, const int_point& point2, ::draw2d::pen * ppen)
   {

      ::vulkan::line(point1.x(), point1.y(), point2.x(), point2.y(), (float)(ppen->m_dWidth),
         ppen->m_color.f32_red(), ppen->m_color.f32_green(),
         ppen->m_color.f32_blue(),
         ppen->m_color.f32_opacity(), 0.f, 0.f, true);

      /*vkLineWidth(ppen->m_dWidth);

      vkBegin(VK_LINES);

      ::vulkan::color(ppen->m_color);

      vkVertex2f(point1.x(), point1.y());
      vkVertex2f(point2.x(), point2.y());

      vkEnd();*/

      m_point.x() = point2.x();
      m_point.y() = point2.y();

      //return true;

   }

   
   void graphics::line_to(double x, double y)
   {

      //if (::is_set(m_ppen))
      //{

      //   vkLineWidth((float)(m_ppen->m_dWidth));

      //}

      //vkBegin(VK_LINES);

      //if (::is_set(m_ppen))
      //{

      //   ::vulkan::color(m_ppen->m_color);

      //}

      //vkVertex2f((float)(m_point.x()), (float)(m_point.y()));
      //vkVertex2f((float)(x), (float)(y));

      //vkEnd();

      m_point.x() = x;
      m_point.y() = y;

      //return true;

   }


   void graphics::text_out(double x, double y, const ::scoped_string & scopedstr)
   {

      if (m_pfont.is_null())
      {

         return;

      }

      //::draw2d::graphics::text_out(x, y, lpszString);
      //if (::draw2d::graphics::text_out(x, y, lpszString, nCount))
      //{

      //   return true;

      //}

      //return true;

      set(m_pfont);

      //::pointer<font>pfont = m_pfont;

      //float length = 0.f;

      //for (unsigned int loop = 0; loop < scopedstr.size(); loop++)	// Loop To Find Text Length
      //{

      //   length += pfont->m_gmf[scopedstr[loop]].gmfCellIncX;			// Increase Length By Each Characters Width

      //}

      //vkTranslatef((float)(x), (float)(y), 0.0f);					// Center Our Text On The Screen

      //vkPushAttrib(VK_LIST_BIT);							// Pushes The Display List Bits
      //vkListBase(pfont->m_baseFont);									// Sets The Base Character to 0
      //vkCallLists((VKsizei)scopedstr.size(), VK_UNSIGNED_BYTE, scopedstr.begin());	// Draws The Display List Text
      //vkPopAttrib();										// Pops The Display List Bits      }

      //vkTranslatef((float)(-x), (float)(-y), 0.0f);					// Center Our Text On The Screen

      ////return true;

   }


   void graphics::set(::draw2d::region* pregion)
   {

      //return ::success;

   }


   void graphics::set(::draw2d::pen * ppen)
   {

      //vkLineWidth(ppen->m_dWidth);

      ::vulkan::color(ppen->m_color);

      //return ::success;

   }



   void graphics::set(::draw2d::brush * pbrush)
   {

      ::vulkan::color(pbrush->m_color);
      
      //return ::success;

   }



   void graphics::set(::write_text::font * pfont)
   {

      if (::is_null(pfont))
      {

         //return ::error_failed;
         return;

      }

      pfont->get_os_data(this);

      //return ::success;

   }


   void graphics::set(::draw2d::bitmap* pbitmap)
   {

      //return ::success;

   }


   ::draw2d::object* graphics::set_stock_object(int nIndex)
   {

      return nullptr;

   }


   void graphics::set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode)
   {

      //if(m_esmoothmode == esmoothmode)
      //   return;

      //::draw2d::graphics::set_smooth_mode(esmoothmode);

      //try
      //{

      //   if(m_pgraphics == nullptr)
      //      return;

      //   if(m_esmoothmode == ::draw2d::e_smooth_mode_none)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeNone);

      //   }
      //   else if(m_esmoothmode == ::draw2d::e_smooth_mode_antialias)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighSpeed);

      //   }
      //   else if(m_esmoothmode == ::draw2d::e_smooth_mode_high)
      //   {

      //      m_pgraphics->SetSmoothingMode(plusplus::SmoothingModeHighQuality);

      //   }

      //}
      //catch(...)
      //{
      //return true;
      //}

   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      try
      {

         //if(m_pgraphics == nullptr)
         //   return;

         ::draw2d::graphics::set_alpha_mode(ealphamode);
         if(m_ealphamode == ::draw2d::e_alpha_mode_blend)
         {
            //vkColorMask(false, false, false, true);
            //vkColorMask(true, true, true, false);
            //vkBlendFunc(VK_SRC_ALPHA, VK_ONE_MINUS_SRC_ALPHA);
            //vkBlendFunc(VK_SRC_ALPHA, VK_SRC_ALPHA);
            //vkBlendFunc(VK_ONE, VK_ONE_MINUS_SRC_ALPHA);
            //vkBlendFunc(VK_ZERO, VK_SRC_ALPHA);
            //vkBlendEquationSeparate(VK_FUNC_ADD, VK_FUNC_ADD);
            // vkBlendFuncSeparate(VK_SRC_ALPHA, VK_ONE_MINUS_SRC_ALPHA, VK_ONE, VK_ZERO);
            //vkEnable(VK_BLEND);
            //vkDisable(VK_DEPTH_TEST);
            //vkDepthFunc(VK_NEVER);
         }
         else if(m_ealphamode == ::draw2d::e_alpha_mode_set)
         {
            //vkEnable(VK_BLEND);
            //vkBlendFunc(VK_ONE, VK_ZERO);
         }

      }
      catch(...)
      {
         //return false;

      }

      //return true;

   }


   void graphics::_draw_raw(const ::double_rectangle & rectangleTarget, ::image::image *pimage, const ::image::image_drawing_options & imagedrawingoptionsParam, const ::double_point & pointSrc)
   {


   }


   void graphics::set_text_rendering_hint(::write_text::enum_rendering etextrendering)
   {
      
      m_ewritetextrendering = etextrendering;

      //return true;

   }


//   void * graphics::get_os_data() const
//   {
//
////      return (void *) m_pgraphics;
//
//      if (!m_hglrc)
//      {
//         return (void *) (iptr)1;
//      }
//
//      return m_hglrc;
//
//   }


   //void graphics::fill_rectangle(const double_rectangle& rectangle, color32_t color32)
   //{



   //}

//   void * graphics::get_os_data_ex(int i) const
//   {
//
//      if(i == 1)
//      {
////         return m_pgraphics->GetHDC();
//      }
//      else
//      {
//         return ::draw2d::graphics::get_os_data(i);
//      }
//
//      return nullptr;
//
//   }


//   void graphics::release_os_data_ex(int i,void * p)
//   {
//      if(i == 1)
//      {
////         m_pgraphics->ReleaseHDC((HDC)p);
//      }
//      else
//      {
//
//         //::draw2d::graphics::release_os_data(i, p);
//
//      }
//
//   }


   /*HDC graphics::get_handle() const
   {

      return m_hdc;

   }


   HDC graphics::m_hdc const
   {

      return get_handle();

   }


   HDC graphics::m_hdc const
   {
      return get_handle();
   }
*/

   //bool graphics::attach(void * pdata)
   //{

   //   //if(m_pgraphics != nullptr)
   //   //{

   //   //   try
   //   //   {

   //   //      delete m_pgraphics;

   //   //   }
   //   //   catch(...)
   //   //   {

   //   //      informationf("graphics::attach : Failed to delete plusplus::Graphics");

   //   //   }

   //   //   m_pgraphics = nullptr;

   //   //}

   //   //m_pgraphics = (plusplus::Graphics *) pdata;

   //   return false;

   //}


   void * graphics::detach()
   {

      //plusplus::Graphics * pgraphics = m_pgraphics;

      //m_pgraphics = nullptr;

      //m_hdc = nullptr;

      //return pgraphics;

      return nullptr;

   }

   //plusplus::Font * graphics::vk2d_font()
   //{
   //   if(m_pfont.is_null())
   //   {
   //      m_pfont.create(this);
   //      if(m_pfont.is_set())
   //      {
   //         m_pfont->m_powner = this;
   //      }
   //   }
   //   if(m_pfont.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Font *) m_pfont->get_os_data();
   //}

   //plusplus::Brush * graphics::vk2d_brush()
   //{
   //   if(m_pbrush.is_null())
   //   {
   //      m_pbrush.create(this);
   //      if(m_pbrush.is_set())
   //      {
   //         m_pbrush->m_powner = this;
   //      }
   //   }
   //   if(m_pbrush.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Brush *) m_pbrush->get_os_data();
   //}

   //plusplus::Pen * graphics::vk2d_pen()
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   if(m_ppen.is_null())
   //   {
   //      m_ppen.create(this);
   //      if(m_ppen.is_set())
   //      {
   //         m_ppen->m_powner = this;
   //      }
   //   }
   //   if(m_ppen.is_null())
   //   {
   //      return nullptr;
   //   }
   //   return (plusplus::Pen *) m_ppen->get_os_data();
   //}

   //plusplus::FillMode graphics::vk2d_get_fill_mode()
   //{
   //   return plusplus::FillModeWinding;
   //}

   
   bool graphics::blur(bool bExpand, double dRadius,const ::int_rectangle & rectangleParam)
   {

      //   // Commented Out for Running in cosan machine running Windows 2008

      //   //if(m_pbitmap.is_null() || m_pbitmap->get_os_data() == nullptr)
      //   //   return false;

      //   //plusplus::BlurParams myBlurParams;

      //   //myBlurParams.expandEdge    = bExpand ? 1 : 0;
      //   //myBlurParams.radius        = (float) dRadius;

      //   //plusplus::Blur myBlur;
      //   //myBlur.SetParameters(&myBlurParams);

      //   //

      //   //plusplus::Matrix m;
      //   //m_pgraphics->GetTransform(&m);

      //   //plusplus::PointF points[2];

      //   //points[0].X    = (plusplus::REAL) rectangleParam.left();
      //   //points[0].Y    = (plusplus::REAL) rectangleParam.top();
      //   //points[1].X    = (plusplus::REAL) rectangleParam.right();
      //   //points[1].Y    = (plusplus::REAL) rectangleParam.bottom();

      //   //m.TransformPoints(points, 2);

      //   ////plusplus::rectF float_rectangle(points[0].X, points[0].Y, points[1].X - points[0].X, points[1].Y - points[0].Y);

      //   //::double_rectangle ::double_rectangle;

      //   //rectangle.left()      = (::double) points[0].X;
      //   //rectangle.top()       = (::double) points[0].Y;
      //   //rectangle.right()     = (::double) points[1].X;
      //   //rectangle.bottom()    = (::double) points[1].Y;

      //   //plusplus::Bitmap * pbitmap = ((plusplus::Bitmap *) m_pbitmap->get_os_data());

      //   //pbitmap->ApplyEffect(&myBlur, &rectangle);

      //   return true;

      return true;
   }


   double graphics::get_dpix() const
   {

      //if (m_pgraphics == nullptr)
      //   return 96.0;

      //return m_pgraphics->GetDpiX();

      return 96.0;

   }


   double graphics::get_dpiy() const
   {

      //if (m_pgraphics == nullptr)
      //   return 96.0;

      //return m_pgraphics->GetDpiY();

      return 96.0;

   }


   void graphics::flush()
   {

      synchronous_lock synchronouslock(this->synchronization());

//      m_pgraphics->Flush();

      //return true;

   }


   void graphics::sync_flush()
   {

      synchronous_lock synchronouslock(this->synchronization());

      //m_pgraphics->Flush(plusplus::FlushIntentionSync);

      //return true;

   }


   //HDC graphics::get_hdc()
   //{

   //   if(m_hdc != nullptr)
   //      return m_hdc;

   //   ////if(m_pgraphics == nullptr)
   //   //   return nullptr;

   //   //return m_pgraphics->GetHDC();

   //   return nullptr;

   //}

   //void graphics::release_hdc(HDC hdc)
   //{

   //   if(m_hdc != nullptr)
   //      return;

   //   //m_pgraphics->ReleaseHDC(hdc);

   //}


   //void graphics::enum_fonts(::write_text::font_enumeration_item_array& itema)
   //{

   //   return;

   //   synchronous_lock synchronouslock(this->synchronization());

   //   draw2d_vulkan_enum_fonts fonts(itema);

   //   //HDC hdc = ::CreateCompatibleDC(nullptr);

   //   //::EnumFontFamilies(hdc,(LPCTSTR)nullptr,(FONTENUMPROC)draw2d_vulkan_EnumFamCallBack,(LPARAM)&fonts);

   //   //::DeleteDC(hdc);

   //   // straPath = stra;

   //}


   //bool graphics::prefer_mapped_image_on_mix()
   //{

   //   return true;

   //}



   void graphics::CreateWindowDC(oswindow wnd)
   {

      // http://stackoverflow.com/questions/4052940/how-to-make-an-vulkan-rendering-context-with-transparent-background
      //

      //PIXELFORMATDESCRIPTOR pfd =
      //{
      //   sizeof(PIXELFORMATDESCRIPTOR),
      //   1,                                // Version Number
      //   PFD_DRAW_TO_WINDOW |         // Format Must Support Window
      //   PFD_SUPPORT_VULKAN |         // Format Must Support Vulkan
      //   PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
      //   PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
      //   PFD_TYPE_RGBA,                    // Request An RGBA Format
      //   32,                               // Select Our Color Depth
      //   0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
      //   8,                                // An Alpha Buffer
      //   0,                                // Shift Bit Ignored
      //   0,                                // No Accumulation Buffer
      //   0, 0, 0, 0,                       // Accumulation Bits Ignored
      //   24,                               // 16Bit Z-Buffer (Depth Buffer)
      //   8,                                // Some Stencil Buffer
      //   0,                                // No Auxiliary Buffer
      //   PFD_MAIN_PLANE,                   // Main Drawing Layer
      //   0,                                // Reserved
      //   0, 0, 0                           // Layer Masks Ignored
      //};


      //DWM_BLURBEHIND bb = { 0 };
      ////HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
      ////bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
      //bb.dwFlags = DWM_BB_ENABLE;
      ////bb.hRgnBlur = hRgn;
      //bb.fEnable = true;
      //DwmEnableBlurBehindWindow(wnd, &bb);


      //m_hdc = GetDC(wnd);
      //int PixelFormat = ChoosePixelFormat(m_hdc, &pfd);
      //if (PixelFormat == 0)
      //{
      //   ASSERT(0);
      //   return false;
      //}

      //BOOL bResult = SetPixelFormat(m_hdc, PixelFormat, &pfd);
      //if (bResult == false)
      //{
      //   ASSERT(0);
      //   return false;
      //}

      //m_hglrc = wglCreateContext(m_hdc);
      //if (!m_hglrc)
      //{
      //   ASSERT(0);
      //   return false;
      //}

//      return true;
      //return false;

   }


   //oswindow graphics::get_window_handle() const
   //{

   //   if (::is_null(m_puserinteraction))
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteraction->get_handle();

   //}


   void graphics::is_valid_update_window_thread()
   {

      //return ::GetCurrentThreadId() == psystem->get_twf()->m_uiThread;
      //return ::GetCurrentThreadId() == ::GetWindowThreadProcessId(m_hwnd, NULL);

   }


   //void graphics::_add_clipping_shape(const ::double_rectangle & rectangle, ::draw2d::region * pregion)
   //{


   //}

   void graphics::do_on_context(const ::procedure & procedure)
   {

      m_pgpucontext->send(procedure);

   }


   //void graphics::on_begin_draw(oswindow wnd, const ::int_size & sz)
   void graphics::on_begin_draw()
   {

      thread_select();

      ::int_size size;

      if (!m_puserinteraction && m_papplication->m_bUseDraw2dProtoWindow)
      {

         m_puserinteraction = dynamic_cast <::user::interaction*>(m_pwindow->m_pacmeuserinteraction.m_p);

      }

      if (m_puserinteraction && !m_puserinteraction->size().is_empty())
      {

         size = m_puserinteraction->size();

      }
      else
      {

         size = { 1920, 1080 };

      }

      bool bYSwap = m_papplication->m_bUseDraw2dProtoWindow;

      ::vulkan::resize(size, bYSwap);

      m_z = 0.f;

      if (!m_pgpucontext->m_prenderer)
      {

         __øconstruct(m_pgpucontext->m_prenderer);

         m_pgpucontext->m_prenderer->initialize_renderer(m_pgpucontext);

      }

      if (m_callbackOffscreen)
      {

         m_pgpucontext->m_callbackOffscreen = m_callbackOffscreen;

      }

      if (m_egraphics & e_graphics_draw)
      {

         m_pgpucontext->m_prenderer->on_begin_draw(size);

      }

      //vkClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      //vkClear(VK_COLOR_BUFFER_BIT | VK_DEPTH_BUFFER_BIT);
      ////vkLoadIdentity();
      ////vkClear(VK_COLOR_BUFFER_BIT | VK_DEPTH_BUFFER_BIT);
      ////vkClear(VK_COLOR_BUFFER_BIT);
      ////vkEnable(VK_BLEND);
      ////vkBlendFunc(VK_SRC_ALPHA, VK_ONE_MINUS_SRC_ALPHA);
      ////::memory_copy(&m_pgpucontext->m_pbuffer->m_pixmap, (::pixmap *)m_pimage, sizeof(::pixmap));

      ////vkClear(VK_COLOR_BUFFER_BIT | VK_DEPTH_BUFFER_BIT);

      ////m_pgpucontext->start_drawing();

      /////vkEnable(VK_DEPTH_TEST);

   }


   void graphics::defer_add_gpu_render(::gpu::render * pgpurender)
   {

      m_pgpucontext->m_rendera.add_unique(pgpurender);

   }


   void graphics::initialize(::particle * pparticle)
   {

      ::draw2d::graphics::initialize(pparticle);

      ::gpu::renderer::initialize(pparticle);

   }

   void graphics::on_end_draw()
   {

      if (m_egraphics & e_graphics_draw)
      {

         m_pgpucontext->m_prenderer->on_end_draw();

      }

      ////vkPushMatrix();

      ////vkColor3f(0, 1, 1);
      //vkBegin(VK_TRIANGLES);                              // Drawing Using Triangles
      //

      //vkColor4f(1.0f, 0.0f, 0.0f, 0.5f);                      // Set The Color To Red
      //vkVertex3f(100.0f, -2000.0f, 0.0f);                  // Top
      //

      //vkColor3f(0.0f, 1.0f, 0.0f);                      // Set The Color To Green
      //vkVertex3f(0.0f, 200.0f, 0.0f);                  // Bottom Left


      //vkColor3f(0.0f, 0.0f, 1.0f);                      // Set The Color To Blue
      //vkVertex3f(2000.0f, 2000.0f, 0.0f);                  // Bottom Right

      //vkEnd();

      //vkPopMatrix();


      //vkFlush();
      //vkFinish();
      //vkDisable(VK_BLEND);


      

      //SwapBuffers(m_hdc);

      //m_pgpucontextVulkan->render

      //dr();

      if (m_papplication->m_bUseDraw2dProtoWindow)
      {
         
         //m_pgpucontext->swap_buffers();

         //m_pwindow->m_timeLastDrawGuard1.Now();

      }
      else
      {

         //m_pgpucontext->swap_buffers();

      //}
      //else
      //{

         read_to_cpu_buffer();

         m_pimage->map();

         m_pimage->copy(&m_pgpucontext->m_pcpubuffer->m_pixmap);

      }

   }


   void graphics::on_present()
   {

      if (m_papplication->m_bUseDraw2dProtoWindow)
      {

         m_pgpucontext->swap_buffers();

      }

   }


   void graphics::thread_select()
   {

      if (thread_graphics() == this)
      {

         return;
      }

      //wglMakeCurrent(m_hdc, m_hglrc);

      m_pgpucontext->make_current();

      thread_graphics(this);

   }


   bool graphics::_is_ok() const
   {

      //return ::is_set(this) & ::is_set(m_hglrc);

      return ::is_set(this) && m_pgpucontext;

   }




   void graphics::intersect_clip(const ::double_rectangle & rectangle)
   {


   }


   void graphics::intersect_clip(const ::draw2d::clip_group & clipgroup)
   {



   }



   void graphics::_vk_rectangle(const ::double_rectangle & rectangle)
   {

      //vkVertex2f((VKfloat)rectangle.left(), (VKfloat)rectangle.top());
      //vkVertex2f((VKfloat)rectangle.right(), (VKfloat)rectangle.top());
      //vkVertex2f((VKfloat)rectangle.right(), (VKfloat)rectangle.bottom());
      //vkVertex2f((VKfloat)rectangle.left(), (VKfloat)rectangle.bottom());

      struct Vertex {
         glm::vec2 pos;
         glm::vec3 color;
      };

      std::vector<Vertex> vertices = {
          {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
          {{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}, // Bottom-right
          {{ 0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // Top-right
          {{-0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}}, // Top-left
      };

      std::vector<uint16_t> indices = {
          0, 1, 2, 2, 3, 0 // Two triangles
      };

   }




} // namespace draw2d_vulkan





BOOL CALLBACK draw2d_vulkan_EnumFamCallBack(LPLOGFONT lplf,LPNEWTEXTMETRIC lpntm,unsigned int FontType,LPVOID p)
{

   draw2d_vulkan_enum_fonts * pfonts = (draw2d_vulkan_enum_fonts *) p;

   if(FontType & RASTER_FONTTYPE)
   {

   }
   else if(FontType & TRUETYPE_FONTTYPE)
   {

      pfonts->m_itema.add(__allocate ::write_text::font_enumeration_item(lplf->lfFaceName));

   }
   else
   {

   }

   return true;

}





namespace vulkan
{


   void resize(const ::int_size& size, bool bYSwap)
   {

      //double d = 200.0 / 72.0;

      //double d = 1.0;

      ////vkViewport(0, 0, size.cx() * d, size.cy() * d);
      //vkViewport(0, 0, size.cx(), size.cy());

      //vkMatrixMode(VK_PROJECTION);
      //vkLoadIdentity();
      ////vkOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
      ////vkOrtho(0, size.cx() * d, size.cy() * d, 0.0f, 000.0f, 1000.0f);
      //////vkOrtho(0, size.cx() * d, 0.0f, size.cy() * d, 000.0f, 1000.0f);
      ////vkOrtho(0, size.cx(), size.cy(), 0.0f, -1000.0f, 1000.0f);
      //vkOrtho(0.f, size.cx(), 0.f, -size.cy(), -1.0f, 1.0f);


      //vkMatrixMode(VK_PROJECTION);
      //vkLoadIdentity();
      //if (bYSwap)
      //{
      //   vkOrtho(0.0f, size.cx(), size.cy(), 0, -1.0f, 1.0f);  // Flip Y
      //}
      //else
      //{
      //   vkOrtho(0.0f, size.cx(), 0, size.cy(), -1.0f, 1.0f);  // Flip Y
      //}
      ////auto left = 0.;
      ////auto right = (double) size.cx();
      ////auto bottom = 0.;
      ////auto top = (double)size.cy();
      ////double dFar = 1.0;
      ////double dNear = -1.0;
      ////double tx = -(right + left) / (right - left);
      ////double ty = -(top + bottom) / (top - bottom);
      ////double tz = -(dFar + dNear) / (dFar - dNear);
      ////double a[] =
      ////{
      ////   2.0/(right - left),0.0,0.0,tx,
      ////   0.0,2.0/(top - bottom),0.0,ty,
      ////   0.0,0.0,-2.0/(dFar-dNear),tz,
      ////   0.0,0.0,0.0,1.0
      ////};
      ////vkMultMatrixd(a);

      ////vkMatrixMode(VK_MODELVIEW);
      ////vkLoadIdentity();


      ////vkuOrtho2D(0.f, size.cx(), 0.f, size.cy());
      ////vkMatrixMode(VK_MODELVIEW);
      ////vkLoadIdentity();

      //// Clear
      ////vkClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      ////vkClear(VK_COLOR_BUFFER_BIT | VK_DEPTH_BUFFER_BIT);

      //// Translate to inside of pixel (otherwise inaccuracies can occur on certain vk implementations)
      ////if (Vulkan::accuracyTweak())
      //vkTranslatef(0.5f, 0.5f, 0);

   }

   //https://community.khronos.org/t/draw-an-arc-in-vulkan/57994/2
   inline void draw_arc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
   {
      float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

      float tangetial_factor = tanf(theta);

      float radial_factor = cosf(theta);


      float x = r * cosf(start_angle);//we now start at the start angle
      float y = r * sinf(start_angle);

      //vkBegin(VK_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
      //for (int ii = 0; ii < num_segments; ii++)
      //{
      //   vkVertex2f(x + cx, y + cy);

      //   float tx = -y;
      //   float ty = x;

      //   x += tx * tangetial_factor;
      //   y += ty * tangetial_factor;

      //   x *= radial_factor;
      //   y *= radial_factor;
      //}
      //vkEnd();
   }

   

} // namespace vulkan



