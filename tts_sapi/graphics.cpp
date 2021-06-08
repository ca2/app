#include "framework.h"


#undef new


count g_cForkBlend = 0;



/**
*
* Trilinear scale two images, pixels and pixels2, to get a new
* interpolated image with ::size_f64 width * height.
* pixels is the larger image with ::size_f64 w * h.
* pixels2 is the smaller image with ::size_f64 w2 * h2.
* width must be w >= width >= w2, width != 0
* height must be h >= height >= h2, height != 0
* Note: in Mip Mapping pixels2 should be half of pixels in dimension.
*
* @lparam pixels Larger image pixels.
* @lparam w Larger image width.
* @lparam h Larger image height.
* @lparam pixels2 Smaller image pixels.
* @lparam w2 Smaller image width.
* @lparam h2 Smaller image height.
* @lparam width New width.
* @lparam height New height.
* @return New array with ::size_f64 width * height
*/
void trilinearImageScaling(
COLORREF * ret, int width, int height, int scan,
COLORREF * pixels, int w, int h, // larger image
COLORREF * pixels2, int w2, int h2, // smaller image
int scan2)
{

   int index, index2;
   COLORREF A, B, C, D, E, F, G, H;
   float x, y, x2, y2, w_diff, h_diff, w2_diff, h2_diff, red, green, blue, alpha;
   // find ratio for larger image
   float w_ratio = ((float)(w - 1)) / width;
   float h_ratio = ((float)(h - 1)) / height;
   // find ratio for smaller image
   float w2_ratio = ((float)(w2 - 1)) / width;
   float h2_ratio = ((float)(h2 - 1)) / height;
   // estimate h3 distance
   float h3_diff = (w - width) / (float)(w - w2);
   int offset = 0;
   COLORREF * line;
   COLORREF * line2;
   COLORREF * lineRet;
   int wscan = scan / sizeof(COLORREF);
   int wscan2 = scan2 / sizeof(COLORREF);
   for (int i = 0; i<height; i++)
   {
      lineRet = ret + wscan * i;
      line = pixels + wscan2 * i;
      line2 = pixels2 + wscan2 * i;
      for (int j = 0; j<width; j++)
      {
         // find w1 and h1 for larger image
         x = w_ratio * j;
         y = h_ratio * i;
         w_diff = x - (int)x;
         h_diff = y - (int)y;
         index = (int) ((y)*wscan2 + (x));
         A = line[index];
         B = line[index + 1];
         C = line[index + wscan2];
         D = line[index + wscan2 + 1];
         // find w2 and h2 for smaller image
         x2 = w2_ratio * j;
         y2 = h2_ratio * i;
         w2_diff = x2 - (int)x2;
         h2_diff = y2 - (int)y2;
         index2 = (int) ((y2)*wscan2 + (x2));
         E = line2[index2];
         F = line2[index2 + 1];
         G = line2[index2 + wscan2];
         H = line2[index2 + wscan2 + 1];


         // trilinear interpolate blue matter
         blue = (A & 0xff)*(1 - w_diff)*(1 - h_diff)*(1 - h3_diff) +
                (B & 0xff)*(w_diff)*(1 - h_diff)*(1 - h3_diff) +
                (C & 0xff)*(h_diff)*(1 - w_diff)*(1 - h3_diff) +
                (D & 0xff)*(w_diff)*(h_diff)*(1 - h3_diff) +
                (E & 0xff)*(1 - w2_diff)*(1 - h2_diff)*(h3_diff)+
                (F & 0xff)*(w2_diff)*(1 - h2_diff)*(h3_diff)+
                (G & 0xff)*(h2_diff)*(1 - w2_diff)*(h3_diff)+
                (H & 0xff)*(w2_diff)*(h2_diff)*(h3_diff);

         // trilinear interpolate green matter
         green = ((A >> 8) & 0xff)*(1 - w_diff)*(1 - h_diff)*(1 - h3_diff) +
                 ((B >> 8) & 0xff)*(w_diff)*(1 - h_diff)*(1 - h3_diff) +
                 ((C >> 8) & 0xff)*(h_diff)*(1 - w_diff)*(1 - h3_diff) +
                 ((D >> 8) & 0xff)*(w_diff)*(h_diff)*(1 - h3_diff) +
                 ((E >> 8) & 0xff)*(1 - w2_diff)*(1 - h2_diff)*(h3_diff)+
                 ((F >> 8) & 0xff)*(w2_diff)*(1 - h2_diff)*(h3_diff)+
                 ((G >> 8) & 0xff)*(h2_diff)*(1 - w2_diff)*(h3_diff)+
                 ((H >> 8) & 0xff)*(w2_diff)*(h2_diff)*(h3_diff);

         // trilinear interpolate red matter
         red = ((A >> 16) & 0xff)*(1 - w_diff)*(1 - h_diff)*(1 - h3_diff) +
               ((B >> 16) & 0xff)*(w_diff)*(1 - h_diff)*(1 - h3_diff) +
               ((C >> 16) & 0xff)*(h_diff)*(1 - w_diff)*(1 - h3_diff) +
               ((D >> 16) & 0xff)*(w_diff)*(h_diff)*(1 - h3_diff) +
               ((E >> 16) & 0xff)*(1 - w2_diff)*(1 - h2_diff)*(h3_diff)+
               ((F >> 16) & 0xff)*(w2_diff)*(1 - h2_diff)*(h3_diff)+
               ((G >> 16) & 0xff)*(h2_diff)*(1 - w2_diff)*(h3_diff)+
               ((H >> 16) & 0xff)*(w2_diff)*(h2_diff)*(h3_diff);

         // trilinear interpolate alpha matter
         alpha = ((A >> 24) & 0xff)*(1 - w_diff)*(1 - h_diff)*(1 - h3_diff) +
                 ((B >> 24) & 0xff)*(w_diff)*(1 - h_diff)*(1 - h3_diff) +
                 ((C >> 24) & 0xff)*(h_diff)*(1 - w_diff)*(1 - h3_diff) +
                 ((D >> 24) & 0xff)*(w_diff)*(h_diff)*(1 - h3_diff) +
                 ((E >> 24) & 0xff)*(1 - w2_diff)*(1 - h2_diff)*(h3_diff)+
                 ((F >> 24) & 0xff)*(w2_diff)*(1 - h2_diff)*(h3_diff)+
                 ((G >> 24) & 0xff)*(h2_diff)*(1 - w2_diff)*(h3_diff)+
                 ((H >> 24) & 0xff)*(w2_diff)*(h2_diff)*(h3_diff);


         *lineRet =
         (int)(blue) |
         ((int)(green)) << 8 |
         ((int)(red)) << 16 |
         ((int)(alpha)) << 24;
         lineRet++;
      }
   }

}


namespace draw2d_gdiplus
{


   graphics::graphics()
   {

      m_pthis = this;
      m_bPrinting       = false;
      m_pgraphics       = nullptr;
      m_hdc             = nullptr;
      m_hdcAttach       = nullptr;
      m_hdcGraphics     = nullptr;
      m_ppath           = nullptr;
      m_ppathPaint      = nullptr;
      m_ewritetextrendering  = ::write_text::e_rendering_none;
      m_dFontFactor     = 1.0;

      m_pm = new Gdiplus::Matrix();

   }


#ifdef DEBUG


   void graphics::assert_valid() const
   {

      object::assert_valid();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {
      
      object::dump(dumpcontext);

      dumpcontext << "m_pgraphics = " << (iptr) m_pgraphics;
      dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";
   }


#endif


   graphics::~graphics()
   {

      ::acme::del(m_pm);

      close_graphics();

   }


   bool graphics::IsPrinting()
   {

      return m_bPrinting;

   }


   bool graphics::CreateDC(const char * pszDriverName, const char * pszDeviceName, const char * pszOutput, const void * lpInitData)
   {

      return attach_hdc(::CreateDCW(wstring(pszDriverName), wstring(pszDeviceName), wstring(pszOutput), (const DEVMODEW*)lpInitData));

   }


   bool graphics::CreateIC(const char * pszDriverName, const char * pszDeviceName, const char * pszOutput, const void * lpInitData)
   {

      return attach_hdc(::CreateICW(wstring(pszDriverName), wstring(pszDeviceName), wstring(pszOutput), (const DEVMODEW*) lpInitData));

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      close_graphics();

      HDC hdc = nullptr;

      if(pgraphics == nullptr)
      {

         hdc = ::CreateCompatibleDC(nullptr);

      }
      else if(__graphics(pgraphics)->m_hdc != nullptr)
      {

         hdc = ::CreateCompatibleDC(__graphics(pgraphics)->m_hdc);

      }
      else if(__graphics(pgraphics)->m_hdcGraphics != nullptr)
      {

         hdc = ::CreateCompatibleDC(__graphics(pgraphics)->m_hdcGraphics);

      }
      else
      {

         HDC hdcTemplate = __graphics(pgraphics)->get_hdc();

         hdc = ::CreateCompatibleDC(hdcTemplate);

         __graphics(pgraphics)->release_hdc(hdcTemplate);

      }

      if (hdc == nullptr)
      {

         return false;

      }

      m_hdcGraphics = hdc;

      m_pgraphics = new Gdiplus::Graphics(m_hdcGraphics);

      m_pgraphics->SetPageUnit(Gdiplus::UnitPixel);

      set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      set_smooth_mode(::draw2d::smooth_mode_anti_alias_8x8);

      m_osdata[0] = m_pgraphics;

      return true;

   }


   i32 graphics::GetDeviceCaps(i32 nIndex)
   {

      __throw(error_not_implemented);

      return -1;

   }

   
   point_f64 graphics::GetBrushOrg()
   {
      
      __throw(error_not_implemented);

      return nullptr;

   }


   point_f64 graphics::SetBrushOrg(double x, double y)
   {
      
      //ASSERT(get_handle1() != nullptr);
   
      //::point_i32 point;

      //VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));

      //return point;

      __throw(error_not_implemented);

      return nullptr;
   }


   point_f64 graphics::SetBrushOrg(const ::point_f64 & point)
   {
      //ASSERT(get_handle1() != nullptr);
      //::point_i32
      //VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
      //return point;

      __throw(error_interface_only);

      return nullptr;

   }

   //i32 graphics::EnumObjects(i32 nObjectType, i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)pfn, lpData);

   //   __throw(error_interface_only);

   //   return -1;

   //}


   ::e_status graphics::set(::draw2d::bitmap * pbitmap)
   {

      if (::is_null(pbitmap))
      {
       
         return ::error_failed;

      }

      if(::is_set(m_pgraphics))
      {

         try
         {

            delete m_pgraphics;

         }
         catch(...)
         {

            TRACE("graphics::set(::draw2d::bitmap *) : Failed to delete Gdiplus::Graphics");

         }

         m_pgraphics = nullptr;

      }

      auto posbitmap = pbitmap->get_os_data < Gdiplus::Bitmap * >();

      m_pgraphics = Gdiplus::Graphics::FromImage(posbitmap);

      m_pgraphics->SetPageUnit(Gdiplus::UnitPixel);

      set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      set_smooth_mode(::draw2d::smooth_mode_anti_alias_8x8);

      m_pbitmap = pbitmap;

      m_osdata[0] = m_pgraphics;

      return ::success;

   }


   //COLORREF graphics::GetNearestColor(const ::color::color & color)
   //{

   //   //return ::GetNearestColor(get_handle2(), color);
   //   __throw(error_not_implemented);

   //   return -1;

   //}


   //UINT graphics::RealizePalette()
   //{

   //   return 0;

   //   //__throw(error_interface_only);

   //   //return ::RealizePalette(get_handle1());
   //}

   //void graphics::UpdateColors()
   //{
   //   //::UpdateColors(get_handle1());

   //}

   i32 graphics::GetPolyFillMode()
   {
      //return ::GetPolyFillMode(get_handle2());
      __throw(error_not_implemented);

      return -1;

   }

   i32 graphics::GetROP2()
   {
      //return ::GetROP2(get_handle2());
      __throw(error_not_implemented);

      return -1;

   }

   i32 graphics::GetStretchBltMode()
   {
      //return ::GetStretchBltMode(get_handle2());
      __throw(error_not_implemented);

      return -1;

   }

   i32 graphics::GetMapMode()
   {
      //return ::GetMapMode(get_handle2());
      __throw(error_not_implemented);

      return -1;

   }


   i32 graphics::GetGraphicsMode()
   {

      //return ::GetGraphicsMode(get_handle2());
      __throw(error_not_implemented);

      return -1;


   }


   bool graphics::GetWorldTransform(XFORM* pXform)
   {



      m_pgraphics->GetTransform(((graphics *)this)->m_pm);

      Gdiplus::REAL rectangle_i32[6];

      m_pm->GetElements(rectangle);

      pXform->eM11 = rectangle_i32[0];
      pXform->eM12 = rectangle_i32[1];
      pXform->eM21 = rectangle_i32[2];
      pXform->eM22 = rectangle_i32[3];

      pXform->eDx = rectangle_i32[4];
      pXform->eDy = rectangle_i32[5];


      return true;

   }

   
   size_f64 graphics::GetViewportExt()
   {

      //::size_f64 ::size_f64;

      //::GetViewportExtEx(get_handle2(), &::size_f64);

      //return ::size_f64;
      __throw(error_not_implemented);

      return nullptr;


   }


   point_f64 graphics::GetWindowOrg()
   {
      
      //::point_i32 point;

      //::GetWindowOrgEx(get_handle2(), &point);

      //return point;
      __throw(error_interface_only);

      return nullptr;

   }


   size_f64 graphics::GetWindowExt()
   {
      //::size_f64 ::size_f64;
      //::GetWindowExtEx(get_handle2(), &::size_f64);
      //return ::size_f64;

      __throw(error_interface_only);

      return nullptr;

   }


   size_f64 graphics::SetViewportExt(const ::size_f64 & size)
   {

      return SetViewportExt(size.cx, size.cy);

   }


   point_f64 graphics::SetWindowOrg(const ::point_f64 & point)
   {

      return SetWindowOrg(point.x, point.y);

   }


   size_f64 graphics::set_window_ext(const ::size_f64 & size)
   {

      return set_window_ext(size.cx, size.cy);

   }


  void graphics::DPtoLP(::point_f64 * pPoints, count nCount)
  {

     //::DPtoLP(get_handle2(), pPoints, (int) nCount);

  }


   void graphics::DPtoLP(::rectangle_f64 * prectangle)
   {

   //   //::DPtoLP(get_handle2(), (LPPOINT)prectangle, 2);

   }

   void graphics::LPtoDP(::point_f64 * pPoints,count nCount)
   {
   
      //::LPtoDP(get_handle2(), pPoints, (int)  nCount);

   }

   void graphics::LPtoDP(::rectangle_f64 * prectangle)

   {
   //   //::LPtoDP(get_handle2(), (LPPOINT)prectangle, 2);

   }


   bool graphics::fill_region(::draw2d::region * pregion, ::draw2d::brush * pbrush)
   {

      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;
      __throw(error_interface_only);

      return false;

   }


   bool graphics::frame_region(::draw2d::region * pregion, ::draw2d::brush * pbrush, double nWidth, double nHeight)
   {

      //return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;
      __throw(error_interface_only);

      return false;

   }


   bool graphics::invert_region(::draw2d::region * pregion)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != false;

      __throw(error_interface_only);

      return false;

   }


   bool graphics::paint_region(::draw2d::region * pregion)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != false;

      __throw(error_interface_only);

      return false;

   }


   //bool graphics::PtVisible(double x, double y)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::PtVisible(get_handle1(), x, y) != false;

   //   __throw(error_interface_only);

   //   return false;


   //}

   //bool graphics::PtVisible(const ::point_i32 & point)
   //{
   //   //ASSERT(get_handle1() != nullptr);   // call virtual
   //   return PtVisible(point.x, point.y);
   //}


   //bool graphics::RectVisible(const rectangle_i32 &  prectangle)
   //{

   //   //return ::RectVisible(get_handle1(), &prectangle) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   point_f64 graphics::current_position()
   {
      //ASSERT(get_handle2() != nullptr);
      //::point_i32 point;
      //VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
      //return point;

      __throw(error_interface_only);

      return nullptr;


   }


   bool graphics::polyline(const ::point_f64 * ppointsParam,count nCount)
   {

      if (nCount <= 0)
      {

         return true;

      }

      bool bOk1 = false;

      ap(Gdiplus::PointF) ppoints(new_array, nCount);

      try
      {

         for(i32 i = 0; i < nCount; i++)
         {

            ppoints[i].X = (Gdiplus::REAL) ppointsParam[i].x;
            ppoints[i].Y = (Gdiplus::REAL) ppointsParam[i].y;

         }

         bOk1 = m_pgraphics->DrawLines(m_ppen->get_os_data < Gdiplus::Pen * >(this),ppoints,(INT) nCount) == Gdiplus::Status::Ok;

      }
      catch(...)
      {
      }


      return bOk1;

   }


   //bool graphics::Arc(double x1,i32 y1,double x2,i32 y2,double x3,i32 y3,double x4,i32 y4)
   //{

   //   double centerx    = (x2 + x1) / 2.0;
   //   double centery    = (y2 + y1) / 2.0;

   //   double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / pmathematics->get_pi();
   //   double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / pmathematics->get_pi();
   //   double sweep      = fabs(end - start);

   //   /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
   //   {
   //      sweep = -sweep;
   //   }
   //   */

   //   return Arc(x1,y1,x2-x1,y2-y1,start,sweep);

   //}


   bool graphics::Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double start      = atan2(y3 - centery,x3 - centerx) * 180.0 / pmathematics->get_pi();
      double end        = atan2(y4 - centery,x4 - centerx) * 180.0 / pmathematics->get_pi();
      double sweep      = fabs(end - start);

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return Arc(x1,y1, x2-x1, y2-y1, start, sweep);

   }


   //bool graphics::Arc(double x1,i32 y1,i32 w,i32 h, angle start, angle extends)
   //{

   //   ::Gdiplus::Rect rectangle_i32(x1,y1,w,h);

   //   return m_pgraphics->DrawArc(m_ppen->get_os_data < Pen * >(this),rectangle,(Gdiplus::REAL) start.degree(),(Gdiplus::REAL) extends.degree()) == Gdiplus::Status::Ok;

   //}


   bool graphics::Arc(double x1,double y1,double w,double h, angle start, angle extends)
   {

      ::Gdiplus::RectF rectangle_f32((Gdiplus::REAL) x1,(Gdiplus::REAL) y1,(Gdiplus::REAL) w,(Gdiplus::REAL) h);

      return m_pgraphics->DrawArc(m_ppen->get_os_data < Gdiplus::Pen * >(this),rectangle_f32,(Gdiplus::REAL) start.degree(),(Gdiplus::REAL) extends.degree()) == Gdiplus::Status::Ok;

   }


   bool graphics::frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush)
   {

      return draw_rectangle(rectangle, pbrush->m_color);

   }


   bool graphics::rectangle_i32(const ::rectangle_f64 & rectangle)
   {

      bool bOk1 = fill_rectangle(rectangle);

      bool bOk2 = draw_rectangle(rectangle);

      return bOk1 && bOk2;

   }


   bool graphics::draw_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::pen * ppen)
   {

      Gdiplus::Rect rectangle_i32;

      __copy(rectangle, rectParam);

      return m_pgraphics->DrawRectangle(ppen->get_os_data < ::Gdiplus::Pen *> (this), rectangle) == ::Gdiplus::Ok;

   }


   bool graphics::invert_rectangle(const ::rectangle_f64 & rectangle)
   {

      //::draw2d::savedc save(this);

      //Gdiplus::REAL colorMatrixElements[][] = {
      //   {-1,  0,  0,  0, 0},
      //   {0,  -1,  0,  0, 0},
      //   {0,   0,  -1, 0, 0},
      //   {0,   0,  0,  1, 0},
      //   {1,   1,  1,  0, 1}};

      //ColorMatrix * colorMatrix = new ColorMatrix(colorMatrixElements);

      //imageAttributes.SetColorMatrix(
      //   colorMatrix,
      //   ColorMatrixFlag.Default,
      //   ColorAdjustType.Bitmap);

      //e.Graphics.DrawImage(pimage, 10, 10, width, height);

      //e.Graphics.DrawImage(
      //   image,
      //   new Rectangle(150, 10, width, height),  // destination rectangle_i32
      //   0, 0,        // upper-left corner of source rectangle_i32
      //   width,       // width of source rectangle_i32
      //   height,      // height of source rectangle_i32
      //   GraphicsUnit.Pixel,
      //   imageAttributes);
      //auto e = m_pgraphics->GetCompositingMode();

      //m_pgraphics->SetCompositingMode(Gdiplus::CombineModeXor);

      //Gdiplus::SolidBrush b(Color(255, 255, 255, 255));

      //Gdiplus::Rect rectangle_i32;

      //__copy(rectangle, pcrect);


      //m_pgraphics->FillRectangle(&b, rectangle);

      //m_pgraphics->SetCompositingMode(e);

      return false;

   }


   bool graphics::Chord(const rectangle_f64 & rectParam,const point_f64 & pointStart, const point_f64 & pointEnd)
   {

      //ASSERT(get_handle1() != nullptr);
      //return ::Chord(get_handle1(),rectParam.left,rectParam.top,
      //               rectParam.right,rectParam.bottom,pointStart.x,pointStart.y,
      //               pointEnd.x, pointEnd.y) != false;
      __throw(error_not_implemented);

      return false;

   }


   void graphics::DrawFocusRect(const rectangle_f64 & rectParam)
   {

      //ASSERT(get_handle1() != nullptr);
      //::DrawFocusRect(get_handle1(),&rectParam);
      __throw(error_not_implemented);


   }


   ::e_status graphics::clear_current_point()
   {

      return ::success;

   }


   //bool graphics::DrawEllipse(double x1, i32 y1, double x2, i32 y2)
   //{

   //   if (m_pgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen * ppen = m_ppen->get_os_data < Pen >(this);

   //   if (ppen == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgraphics->DrawEllipse(ppen, x1, y1, x2 - x1, y2 - y1)) == Gdiplus::Status::Ok;

   //}


   //bool graphics::DrawEllipse(const rectangle_i32 &  rectParam)
   //{

   //   if (m_pgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen * ppen = m_ppen->get_os_data < Pen >(this);

   //   if (ppen == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgraphics->DrawEllipse(ppen,rectParam.left,rectParam.top,rectParam.right - rectParam.left,rectParam.bottom - rectParam.top)) == Gdiplus::Status::Ok;

   //}



   //bool graphics::draw_ellipse(double x1,double y1,double x2,double y2)
   //{

   //   if (m_pgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen * ppen = m_ppen->get_os_data < Pen * >(this);

   //   if (ppen == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgraphics->DrawEllipse(ppen,(Gdiplus::REAL)x1,(Gdiplus::REAL)y1,(Gdiplus::REAL)(x2 - x1),(Gdiplus::REAL)(y2 - y1))) == Gdiplus::Status::Ok;

   //}


   bool graphics::draw_ellipse(const ::rectangle_f64 & rectParam)
   {

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Pen * ppen = m_ppen->get_os_data < Gdiplus::Pen * >(this);

      if (ppen == nullptr)
      {

         return false;

      }

      return (m_pgraphics->DrawEllipse(ppen,(Gdiplus::REAL)rectParam.left,(Gdiplus::REAL)rectParam.top,
                                       (Gdiplus::REAL)(rectParam.right - rectParam.left),
                                       (Gdiplus::REAL)(rectParam.bottom - rectParam.top))) == Gdiplus::Status::Ok;

   }


   /*bool graphics::fill_ellipse(double x1, i32 y1, double x2, i32 y2)
   {

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Brush * pbrush = m_pbrush->get_os_data < Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      return (m_pgraphics->FillEllipse(pbrush, x1, y1, x2 - x1, y2 - y1)) == Gdiplus::Status::Ok;

   }


   bool graphics::FillEllipse(const rectangle_i32 &  rectParam)
   {

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Brush * pbrush = m_pbrush->get_os_data < Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      return (m_pgraphics->FillEllipse(pbrush, rectParam.left, rectParam.top, rectParam.right - rectParam.left, rectParam.bottom - rectParam.top)) == Gdiplus::Status::Ok;

   }*/


   //bool graphics::fill_ellipse(double x1,double y1,double x2,double y2)
   //{

   //   if (m_pgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Brush * pbrush = m_pbrush->get_os_data < Brush * >(this);

   //   if (pbrush == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgraphics->FillEllipse(pbrush,(Gdiplus::REAL)x1,(Gdiplus::REAL)y1,(Gdiplus::REAL)(x2 - x1),(Gdiplus::REAL)(y2 - y1))) == Gdiplus::Status::Ok;

   //}


   bool graphics::fill_ellipse(const ::rectangle_f64 & rectParam)
   {

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Brush * pbrush = m_pbrush->get_os_data < Gdiplus::Brush * >(this);

      if (pbrush == nullptr)
      {

         return false;

      }

      return (m_pgraphics->FillEllipse(pbrush,(Gdiplus::REAL)rectParam.left,(Gdiplus::REAL)rectParam.top,
                                       (Gdiplus::REAL)(rectParam.right - rectParam.left),
                                       (Gdiplus::REAL)(rectParam.bottom - rectParam.top))) == Gdiplus::Status::Ok;

   }


   //bool graphics::Pie(double x1, i32 y1, double x2, i32 y2, double x3, i32 y3, double x4, i32 y4)
   //{

   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   bool graphics::Pie(const rectangle_f64 &  rectParam, const point_f64 & pointStart, const point_f64 & pointEnd)
   {

      //ASSERT(get_handle1() != nullptr);
      //return ::Pie(get_handle1(), rectParam.left, rectParam.top,
      //             rectParam.right, rectParam.bottom, pointStart.x, pointStart.y,
      //             pointEnd.x, pointEnd.y) != false;
      __throw(error_not_implemented);

      return false;

   }


   bool graphics::fill_polygon(const POINT_F64 * ppointParam,count nCount)
   {

      if (nCount <= 0)
      {

         return true;

      }

      bool bOk1 = false;

      //ap(Gdiplus::PointF) ppoint(ppointParam, nCount);

      array < Gdiplus::PointF > pa;

      pa.set_size(nCount);

      for (::index i = 0; i < nCount; i++)
      {

         pa[i].X = (FLOAT) ppointParam[i].x;

         pa[i].Y = (FLOAT) ppointParam[i].y;

      }

      try
      {

         bOk1 = m_pgraphics->FillPolygon(m_pbrush->get_os_data < Gdiplus::Brush * >(this), pa.get_data(), (INT) nCount, gdiplus_get_fill_mode()) == Gdiplus::Status::Ok;

      }
      catch(...)
      {
      }

      return bOk1;

   }


   //bool graphics::fill_polygon(const POINT_F64 * ppointParam,count nCount)
   //{

   //   if (nCount <= 0)
   //   {

   //      return true;

   //   }

   //   bool bOk1 = false;

   //   ap(Gdiplus::Point) ppoint(ppointParam, nCount);

   //   try
   //   {

   //      //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

   //      bOk1 = m_pgraphics->FillPolygon(m_pbrush->get_os_data < Gdiplus::Brush * >(this), ppoint, (INT)  nCount, gdiplus_get_fill_mode()) == Gdiplus::Status::Ok;

   //   }
   //   catch(...)
   //   {
   //   }

   //   //try
   //   //{
   //   //   delete ppoints;
   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //   return bOk1;

   //}


   bool graphics::draw_polygon(const POINT_F64 * ppointParam, count nCount)
   {

      if (nCount <= 0)
      {

         return true;

      }

      bool bOk1 = false;

      array < Gdiplus::PointF > pointa;
      
      pointa.set_size(nCount);

      for (int i = 0; i < nCount; i++)
      {

         pointa[i].X = (Gdiplus::REAL) ppointParam[i].x;
         pointa[i].Y = (Gdiplus::REAL) ppointParam[i].y;

      }

      try
      {

         //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

         bOk1 = m_pgraphics->DrawPolygon(m_ppen->get_os_data < Gdiplus::Pen * >(this), pointa.get_data(), (INT) nCount) == Gdiplus::Status::Ok;

      }
      catch (...)
      {
      }



      return bOk1;
   }


   //bool graphics::draw_polygon(const POINT_F64 * ppointParam, count nCount)
   //{

   //   if (nCount <= 0)
   //   {

   //      return true;

   //   }

   //   bool bOk1 = false;

   //   ap(Gdiplus::PointF) ppoint(ppointParam, nCount);

   //   try
   //   {

   //      //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

   //      bOk1 = m_pgraphics->DrawPolygon(m_ppen->get_os_data < Pen * >(this), ppoint, (INT) nCount) == Gdiplus::Status::Ok;

   //   }
   //   catch(...)
   //   {
   //   }

   //   return bOk1;

   //}


   bool graphics::fill_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::brush * pbrush)
   {

      if (::is_null(pbrush))
      {

         return false;

      }

      Gdiplus::Rect rectangle_i32;

      __copy(rectangle, rectParam);

      Gdiplus::Brush* posbrush = pbrush->get_os_data < Gdiplus::Brush * >(this);

      bool bOk = m_pgraphics->FillRectangle(posbrush, rectangle) == Gdiplus::Status::Ok;

      return bOk;

   }


   //bool graphics::fill_rectangle(const ::rectangle_f64 & rectParam, ::draw2d::brush * pbrush)
   //{

   //   Gdiplus::RectF rectangle_i32;

   //   __copy(rectangle, rectParam);

   //   return m_pgraphics->FillRectangle(pbrush->get_os_data<Brush *>(this), rectangle) == Gdiplus::Status::Ok;

   //}


   bool graphics::round_rectangle(const ::rectangle_f64 & rectangle, double dRadius)
   {

      __throw(todo);

   }


   //bool graphics::round_rectangle(const ::rectangle_f64 & rectangle, const ::point_f64 & point)
   //{

   //   __throw(todo);

   //}


   //bool graphics::PatBlt(double x, double y, double nWidth, double nHeight, u32 dwRop)
   //{

   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != false;
   //   __throw(error_not_implemented);

   //   return false;


   //}

//
//   bool graphics::_draw_raw(const ::rectangle_f64 & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectSrc)
//   {
//
//      if (m_pgraphics == nullptr)
//      {
//
//         return false;
//
//      }
//
//      Gdiplus::Status ret = Gdiplus::Status::GenericError;
//
//      try
//      {
//
//         if (pgraphicsSrc == nullptr)
//         {
//
//            return false;
//
//         }
//
//         if (pgraphicsSrc->get_current_bitmap() == nullptr)
//         {
//
//            goto gdi_fallback;
//
//         }
//
//         if (pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
//         {
//
//            goto gdi_fallback;
//
//         }
//
//         if (::is_ok(pgraphicsSrc->m_pimage))
//         {
//
//            pgraphicsSrc->m_pimage->defer_update_image();
//
//         }
//
//
//         //bool bThreadToolsForIncreasedFps = ::get_task()== nullptr ? false : ::get_task()->m_bThreadToolsForIncreasedFps;
//
//         //bool bAvoidProcFork = ::get_task() == nullptr ? true : ::get_task()->m_bAvoidProcFork;
//
//         //if (!bAvoidProcFork
//         //      &&
//         //      bThreadToolsForIncreasedFps &&
//         //      pgraphicsSrc->m_pimage->is_ok()
//         //      && m_pimage->is_ok()
//         //      && pgraphicsSrc->m_pimage->m_bMapped
//         //      && m_pimage->m_bMapped)
//         //{
//
//         //   if (m_ealphamode == ::draw2d::alpha_mode_blend)
//         //   {
//
//         //      //single_lock synchronouslock(::get_thread_toolset(::thread::tool_draw2d)->mutex());
//
//         //      if (nHeight >= get_processor_count() * 4 && (nWidth * nHeight) >= (get_processor_count() * 64)
//         //            &&   m_pimage->fork_blend(point_i32(x + GetViewportOrg().x, y + GetViewportOrg().y), pgraphicsSrc->m_pimage,
//         //                  point_i32(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
//         //                  ::size_f64(nWidth, nHeight)))
//         //      {
//
//         //         g_cForkBlend++;
//
//         //         if (g_cForkBlend % 100 == 0)
//         //         {
//         //            output_debug_string("\nfork_blend(" + __str(g_cForkBlend) + ") sample=" + __str(nWidth) + "," + __str(nHeight));
//         //         }
//
//         //         return true;
//
//         //      }
//         //      //else
//         //      //{
//         //      //   m_pimage->blend(point_i32(x + GetViewportOrg().x, y + GetViewportOrg().y), pgraphicsSrc->m_pimage,
//         //      //                                     point_i32(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
//         //      //                                     ::size_f64(nWidth, nHeight));
//
//         //      //}
//         //   }
//         //   //else
//         //   //{
//
//         //   //   m_pimage->from(point_i32(x + GetViewportOrg().x, y + GetViewportOrg().y), pgraphicsSrc->m_pimage,
//         //   //                                    point_i32(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
//         //   //                                    ::size_f64(nWidth, nHeight));
//
//
//         //   //}
//
//         //}
//
//         Gdiplus::Bitmap * pbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();
//
//         if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
//         {
//
//            Gdiplus::ImageAttributes imageattributes;
//
//            Gdiplus::ColorMatrix colormatrix;
//
//            copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);
//
//            imageattributes.SetColorMatrix(
//            &colormatrix,
//            Gdiplus::ColorMatrixFlagsDefault,
//               Gdiplus::ColorAdjustTypeBitmap);
//
//            Gdiplus::Rect rectangle_i32((INT) rectDst.left, (INT) rectDst.top, (INT) rectDst.width(), (INT) rectDst.height());
//
//            ret = m_pgraphics->DrawImage(
//                  pbitmap,
//                  rectangle, 
//               (INT) (rectSrc.left + pgraphicsSrc->GetViewportOrg().x), 
//               (INT) (rectSrc.top + pgraphicsSrc->GetViewportOrg().y), 
//               (INT) (rectSrc.width()),
//               (INT) (rectSrc.height()), 
//               Gdiplus::UnitPixel, &imageattributes);
//
//         }
//         else
//         {
//
//            int xSrcViewport = (int) pgraphicsSrc->GetViewportOrg().x;
//
//            int ySrcViewport = (int) pgraphicsSrc->GetViewportOrg().y;
//
//            ret = m_pgraphics->DrawImage(
//               pbitmap,
//               (INT) rectDst.left, 
//               (INT) rectDst.top,
//               (INT) (rectSrc.left + xSrcViewport), 
//               (INT) (rectSrc.top + ySrcViewport), 
//               (INT) (rectSrc.width()), 
//               (INT) (rectSrc.height()),
//               Gdiplus::UnitPixel);
//
//         }
//
//         if(ret != Gdiplus::Status::Ok)
//         {
//
//            return false;
//
//         }
//
//      }
//      catch(...)
//      {
//
//         return false;
//
//      }
//
//      return true;
//
////gdi_fallback:
////
////      HDC hdcDst = get_hdc();
////
////      if (hdcDst == nullptr)
////      {
////
////         return false;
////
////      }
////
////      HDC hdcSrc = __graphics(pgraphicsSrc)->get_hdc();
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
////      bool bOk = ::BitBlt(hdcDst, 
////         rectDst.left, rectDst.top,
////         rectDst.width(), rectDst.height(),
////         hdcSrc,
////         pointSrc.x, pointSrc.y, SRCCOPY) != false;
////
////      __graphics(pgraphicsSrc)->release_hdc(hdcSrc);
////
////      release_hdc(hdcDst);
////
////      return bOk;
//
//   }


   bool graphics::_draw_raw(const ::rectangle_f64 & rectDstParam, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectSrcParam)
   {

      if (pgraphicsSrc == nullptr)
      {

         return false;

      }

      double nDstWidth = rectDstParam.width();

      double nDstHeight = rectDstParam.height();

      double xSrc = rectSrcParam.left;

      double ySrc = rectSrcParam.top;

      double nSrcWidth = rectSrcParam.width();

      double nSrcHeight = rectSrcParam.height();

      Gdiplus::RectF rectDst((Gdiplus::REAL) rectDstParam.left, (Gdiplus::REAL)rectDstParam.top, (Gdiplus::REAL)rectDstParam.width(), (Gdiplus::REAL)rectDstParam.height());

      if (pgraphicsSrc == nullptr || pgraphicsSrc->get_current_bitmap() == nullptr)
      {

         return false;

      }

      Gdiplus::Status ret = Gdiplus::Status::GenericError;

      if (pgraphicsSrc->m_pimage->is_ok())
      {

         if (pgraphicsSrc->m_pimage->m_emipmap == ::draw2d::mipmap_anisotropic
               && (pgraphicsSrc->m_pimage->width() == rectSrcParam.width()
                   && pgraphicsSrc->m_pimage->height() == rectSrcParam.height()
                   && rectSrcParam.left == 0 && rectSrcParam.top == 0
                  && rectDstParam.width() > 0 && rectDstParam.height() > 0))
         {

            try
            {

               index iFind = -1;

               double dRateFound = 1024.0;

               int xFound;
               int yFound;
               int cxFound;
               int cyFound;

               for (index i = 0; i < pgraphicsSrc->m_pimage->get_image_count(); i++)
               {

                  int x1 = 0;
                  int y1 = 0;
                  int x2 = 0;
                  int y2 = 0;
                  int dx = (int) nSrcWidth;
                  int dy = (int)nSrcHeight;
                  int cx1 = (int)nSrcWidth;
                  int cy1 = (int)nSrcHeight;
                  int cx2 = (int)nSrcWidth;
                  int cy2 = (int)nSrcHeight;

                  while (dx >= nDstWidth)
                  {
                     x1 = x2;
                     x2 += dx;
                     cx1 = dx;
                     dx /= 2;
                     cx2 = dx;
                  }

                  while (dy >= nSrcHeight)
                  {
                     y1 = y2;
                     y2 += dy;
                     cy1 = dy;
                     dy /= 2;
                     cy2 = dy;
                  }

                  if (y1 == nSrcHeight)
                  {
                     y1 = 0;
                  }
                  if (y2 == nSrcHeight)
                  {
                     y2 = 0;
                  }

                  double dRateX = (double)nDstWidth / (double)cx1;

                  double dRateY = (double)nDstHeight / (double)cy1;

                  double dRateArea = dRateX * dRateY;

                  if (dRateArea < dRateFound)
                  {

                     iFind = i;

                     dRateFound = dRateArea;

                     xFound = x1;

                     yFound = y1;

                     cxFound = cx1;

                     cyFound = cy1;

                  }

               }

               if (iFind >= 0)
               {

                  ::image_pointer pimage = pgraphicsSrc->m_pimage->get_image(iFind);

                  auto emode = m_pgraphics->GetInterpolationMode();

                  m_pgraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);

                  //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

                  //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeBilinear);

                  ret = m_pgraphics->DrawImage(
                        (Gdiplus::Bitmap *) pimage->get_bitmap()->get_os_data(),
                        rectDst, 
                     (Gdiplus::REAL) xFound, (Gdiplus::REAL) yFound, 
                     (Gdiplus::REAL) cxFound, (Gdiplus::REAL) cyFound,
                        Gdiplus::UnitPixel);

                  //m_pgraphics->SetInterpolationMode(emode);

                  if (ret == Gdiplus::Status::Ok)
                  {

                     return true;

                  }

               }

            }
            catch (...)
            {


            }



         }

      }

      try
      {

         Gdiplus::Bitmap * pbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();

         if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
         {

            Gdiplus::ImageAttributes imageattributes;

            Gdiplus::ColorMatrix colormatrix;

            copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);

            imageattributes.SetColorMatrix(
            &colormatrix,
            Gdiplus::ColorMatrixFlagsDefault,
               Gdiplus::ColorAdjustTypeBitmap);

            ret = m_pgraphics->DrawImage(pbitmap, rectDst, 
               (Gdiplus::REAL) xSrc, (Gdiplus::REAL)ySrc, 
               (Gdiplus::REAL)nSrcWidth, (Gdiplus::REAL)nSrcHeight, Gdiplus::UnitPixel, &imageattributes);

         }
         else
         {

            ret = m_pgraphics->DrawImage(pbitmap, rectDst, 
               (Gdiplus::REAL)xSrc, (Gdiplus::REAL)ySrc, 
               (Gdiplus::REAL)nSrcWidth, (Gdiplus::REAL)nSrcHeight, Gdiplus::UnitPixel);

         }

         if(ret != Gdiplus::Status::Ok)
         {

            return false;

         }

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   //bool graphics::draw_raw(const  xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, double xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop)
   //{

   //   if (pgraphicsSrc == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Rect rectDst(xDst, yDst, nDstWidth, nDstHeight);

   //   if (pgraphicsSrc == nullptr || pgraphicsSrc->get_current_bitmap() == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Status ret = Gdiplus::Status::GenericError;

   //   if (pgraphicsSrc->m_pimage->is_ok())
   //   {

   //      if (pgraphicsSrc->m_pimage->m_emipmap == ::draw2d::mipmap_anisotropic
   //            && (pgraphicsSrc->m_pimage->width() == nSrcWidth
   //                && pgraphicsSrc->m_pimage->height() == nSrcHeight
   //                && xSrc == 0 && ySrc == 0 && nDstWidth > 0 && nDstHeight > 0))
   //      {

   //         try
   //         {

   //            /*int x1 = 0;
   //            int y1 = 0;
   //            int x2 = 0;
   //            int y2 = 0;
   //            int dx = nSrcWidth;
   //            int dy = nSrcHeight;
   //            int cx1 = nSrcWidth;
   //            int cy1 = nSrcHeight;
   //            int cx2 = nSrcWidth;
   //            int cy2 = nSrcHeight;

   //            while (dx >= nDstWidth)
   //            {
   //               x1 = x2;
   //               x2 += dx;
   //               cx1 = dx;
   //               dx /= 2;
   //               cx2 = dx;
   //            }

   //            while (dy >= nSrcHeight)
   //            {
   //               y1 = y2;
   //               y2 += dy;
   //               cy1 = dy;
   //               dy /= 2;
   //               cy2 = dy;
   //            }

   //            if (y1 == nSrcHeight)
   //            {
   //               y1 = 0;
   //            }
   //            if (y2 == nSrcHeight)
   //            {
   //               y2 = 0;
   //            }*/

   //            //::image_pointer pimage = m_pimage;
   //            //int iScan = pimage->m_iScan;
   //            //::image_pointer pimageMipmap = pgraphicsSrc->m_pimage;
   //            //COLORREF * pcrMipmap = imageMipmap.m_pcolorref;
   //            //int iMimapScan = imageMipmap.m_iScan;
   //            //::size_f64 sizeMipmap = imageMipmap.m_size;

   //            //trilinearImageScaling(
   //            //&pimage->m_pcolorref[xDst + iScan * yDst / sizeof(COLORREF)],
   //            //nDstWidth, nDstHeight,
   //            //iScan,
   //            //&pcrMipmap[x1 + y1 * iMimapScan / sizeof(COLORREF)],
   //            //cx1, cy1,
   //            //&pcrMipmap[x2 + y2 * iMimapScan / sizeof(COLORREF)],
   //            //cx2, cy2,
   //            //iMimapScan);

   //            index iFind = -1;

   //            double dRateFound = 1024.0;

   //            int xFound;
   //            int yFound;
   //            int cxFound;
   //            int cyFound;

   //            for (index i = 0; i < pgraphicsSrc->m_pimage->get_image_count(); i++)
   //            {

   //               int x1 = 0;
   //               int y1 = 0;
   //               int x2 = 0;
   //               int y2 = 0;
   //               int dx = nSrcWidth;
   //               int dy = nSrcHeight;
   //               int cx1 = nSrcWidth;
   //               int cy1 = nSrcHeight;
   //               int cx2 = nSrcWidth;
   //               int cy2 = nSrcHeight;

   //               while (dx >= nDstWidth)
   //               {
   //                  x1 = x2;
   //                  x2 += dx;
   //                  cx1 = dx;
   //                  dx /= 2;
   //                  cx2 = dx;
   //               }

   //               while (dy >= nSrcHeight)
   //               {
   //                  y1 = y2;
   //                  y2 += dy;
   //                  cy1 = dy;
   //                  dy /= 2;
   //                  cy2 = dy;
   //               }

   //               if (y1 == nSrcHeight)
   //               {
   //                  y1 = 0;
   //               }
   //               if (y2 == nSrcHeight)
   //               {
   //                  y2 = 0;
   //               }

   //               double dRateX = (double)nDstWidth / (double)cx1;

   //               double dRateY = (double)nDstHeight / (double)cy1;

   //               double dRateArea = dRateX * dRateY;

   //               if (dRateArea < dRateFound)
   //               {

   //                  iFind = i;

   //                  dRateFound = dRateArea;

   //                  xFound = x1;

   //                  yFound = y1;

   //                  cxFound = cx1;

   //                  cyFound = cy1;

   //               }

   //            }

   //            if (iFind >= 0)
   //            {

   //               ::image_pointer pimage = pgraphicsSrc->m_pimage->get_image(iFind);

   //               auto emode = m_pgraphics->GetInterpolationMode();

   //               m_pgraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);

   //               //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

   //               //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeBilinear);

   //               ret = m_pgraphics->DrawImage(
   //                     (Gdiplus::Bitmap *) pimage->get_bitmap()->get_os_data(),
   //                     rectDst, xFound, yFound, cxFound, cyFound, Gdiplus::UnitPixel);

   //               //m_pgraphics->SetInterpolationMode(emode);

   //               if (ret == Gdiplus::Status::Ok)
   //               {

   //                  return true;

   //               }

   //            }

   //         }
   //         catch (...)
   //         {


   //         }



   //      }

   //   }

   //   try
   //   {

   //      Gdiplus::Bitmap * pbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();

   //      //if(m_pgraphics->GetInterpolationMode() == Gdiplus::InterpolationModeLowQuality
   //      //      && m_pgraphics->GetCompositingMode() == Gdiplus::CompositingModeSourceCopy)
   //      //{

   //      //   m_pgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
   //      //   m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
   //      //   m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);
   //      //   m_pgraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);

   //      //}

   //      if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
   //      {

   //         Gdiplus::ImageAttributes imageattributes;

   //         Gdiplus::ColorMatrix colormatrix;

   //         copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);

   //         imageattributes.SetColorMatrix(
   //         &colormatrix,
   //         ColorMatrixFlagsDefault,
   //         ColorAdjustTypeBitmap);

   //         ret = m_pgraphics->DrawImage(pbitmap, rectDst, xSrc, ySrc, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel, &imageattributes);

   //      }
   //      else
   //      {

   //         if (rectDst.Width == nSrcWidth && rectDst.Height == nSrcHeight)
   //         {

   //            ret = m_pgraphics->DrawImage(pbitmap, rectDst.X, rectDst.Y, xSrc, ySrc, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel);

   //         }
   //         else
   //         {

   //            ret = m_pgraphics->DrawImage(pbitmap, rectDst, xSrc, ySrc, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel);

   //         }

   //      }

   //      if (ret != Gdiplus::Status::Ok)
   //      {

   //         return false;

   //      }

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //   return true;

   //}




   ::color::color graphics::GetPixel(double x, double y)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::GetPixel(get_handle1(), x, y);
      __throw(error_not_implemented);

      return false;

   }
   
   
   ::color::color graphics::GetPixel(const ::point_f64 & point)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::GetPixel(get_handle1(), point.x, point.y);
      __throw(error_not_implemented);

      return false;

   }


   ::color::color graphics::SetPixel(double x, double y, const ::color::color & color)
   {

      return 0;

   }


   ::color::color graphics::SetPixel(const ::point_f64 & point, const ::color::color & color)
   {

      if (m_pimage->is_ok())
      {

         m_pimage->map();

         m_pimage->colorref()[(int) point.x + (int) point.y * m_pimage->scan_size()] = color;

      }
      else
      {

         fill_rectangle(::rectd_dim(point.x, point.y, 1, 1), color);

      }

      return color;

   }


   ::color::color graphics::blend_pixel(const ::point_f64 & point, const ::color::color& colorChange)
   {

      if (m_pimage->is_ok())
      {

         m_pimage->map();

         ::color::color color = m_pimage->colorref()[(int) point.x + (int) point.y * m_pimage->scan_size()];

         color.m_iR = (int) (color.m_iR * (1.0 - colorChange.da()) + colorChange.m_iR * colorChange.da());
         color.m_iG = (int) (color.m_iG * (1.0 - colorChange.da()) + colorChange.m_iG * colorChange.da());
         color.m_iB = (int) (color.m_iB * (1.0 - colorChange.da()) + colorChange.m_iB * colorChange.da());

         m_pimage->colorref()[(int) point.x + (int) point.y * m_pimage->scan_size()] = color;
         //colorCurrent.m_iA = colorCurrent.m_iA * (1.0 - color.da()) + color.m_iR * color.da();

      }
      else
      {

         fill_rectangle(::rectd_dim(point.x, point.y, 1, 1), colorChange);

      }

      return colorChange;

   }


   //bool graphics::FloodFill(double x, double y, const ::color::color & color)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::FloodFill(get_handle1(), x, y, color) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   //bool graphics::ExtFloodFill(double x, double y, const ::color::color & color, UINT nFillType)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::ExtFloodFill(get_handle1(), x, y, color, nFillType) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST


   bool graphics::ExtTextOut(double x, double y,UINT nOptions,const rectangle_f64 &  rectParam,const char * pszString,strsize nCount,LPINT lpDxWidths)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::ExtTextOut(get_handle1(),x,y,nOptions,&rectParam,pszString,(UINT) nCount,lpDxWidths) != false;
      __throw(error_not_implemented);

      return false;


   }


   bool graphics::ExtTextOut(double x, double y,UINT nOptions,const rectangle_f64 &  rectParam, const string & str, LPINT pDxWidths)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::ExtTextOut(get_handle1(),x,y,nOptions,&rectParam, str, (UINT)str.get_length(), pDxWidths) != false;
      __throw(error_not_implemented);

      return false;


   }


   size_f64 graphics::TabbedTextOut(double x, double y, const char * pszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::TabbedTextOut(get_handle1(), x, y, pszString, (int) nCount, (int) nTabPositions, lpnTabStopPositions, nTabOrigin);

      __throw(error_not_implemented);

      return nullptr;

   }


   size_f64 graphics::TabbedTextOut(double x, double y, const string & str, count nTabPositions, LPINT pnTabStopPositions, i32 nTabOrigin)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::TabbedTextOut(get_handle1(), x, y, str, (i32)str.get_length(), (int) nTabPositions, pnTabStopPositions, nTabOrigin);

      __throw(error_not_implemented);

      return nullptr;

   }


   size_f64 graphics::GetTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      //ASSERT(get_handle2() != nullptr);

      //return ::GetTabbedTextExtent(get_handle2(), pszString, (i32) nCount, (int) nTabPositions, lpnTabStopPositions);
      __throw(error_not_implemented);

      return nullptr;


   }


   size_f64 graphics::GetTabbedTextExtent(const string & str, count nTabPositions, LPINT pnTabStopPositions)
   {

      //ASSERT(get_handle2() != nullptr);

      //return ::GetTabbedTextExtent(get_handle2(), str, (i32) str.get_length(), (int) nTabPositions, pnTabStopPositions);

      __throw(error_not_implemented);

      return nullptr;

   }


   size_f64 graphics::GetOutputTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GetTabbedTextExtent(get_handle1(), pszString, (i32) nCount, (int) nTabPositions, lpnTabStopPositions);

      __throw(error_not_implemented);

      return nullptr;

   }


   size_f64 graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT pnTabStopPositions)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GetTabbedTextExtent(get_handle1(), str, (i32) str.get_length(), (int) nTabPositions, pnTabStopPositions);

      __throw(error_not_implemented);

      return nullptr;
   }


   //bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount,double x, double y, double nWidth, double nHeight)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)pfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   UINT graphics::GetTextAlign()
   {

      //ASSERT(get_handle2() != nullptr);

      //return ::GetTextAlign(get_handle2());
      __throw(error_not_implemented);

      return -1;
   }


   //i32 graphics::GetTextFace(count nCount, LPTSTR pszFacename)

   //{

   //   //ASSERT(get_handle2() != nullptr);

   //   //return ::GetTextFace(get_handle2(), (int) nCount, pszFacename);
   //   __throw(error_not_implemented);

   //   return -1;

   //}


   i32 graphics::GetTextFace(string & rString)
   {

      //ASSERT(get_handle2() != nullptr);

      //i32 nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256));
      //rString.ReleaseBuffer();

      //return nResult;
      __throw(error_not_implemented);

      return -1;
   }


   bool graphics::get_text_metrics(::write_text::text_metric * pmetric)
   {

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      if (m_pfont == nullptr)
      {

         return false;

      }

      graphics * pgraphics = ((graphics *)this);

      Gdiplus::Font * pfont = m_pfont->get_os_data < Gdiplus::Font * >(this);

      if (pfont == nullptr)
      {

         return false;

      }

      Gdiplus::FontFamily family;

      pfont->GetFamily(&family);

      INT iStyle = pfont->GetStyle();

      double dHeight = family.GetEmHeight(iStyle);

      double dSize = pfont->GetSize();

      double dFontHeight = pfont->GetHeight((Gdiplus::REAL) pgraphics->get_dpiy());

      pmetric->m_dAscent              = dSize * family.GetCellAscent(iStyle) / dHeight;

      pmetric->m_dDescent             = dSize * family.GetCellDescent(iStyle) / dHeight;

      pmetric->m_dHeight              = dFontHeight;

      double dLineSpacing = maximum(dFontHeight, dSize * family.GetLineSpacing(iStyle) / dHeight);

      pmetric->m_dInternalLeading     = 0;

      pmetric->m_dExternalLeading     = dLineSpacing - (pmetric->m_dAscent + pmetric->m_dDescent);

      return true;

   }


   bool graphics::get_output_text_metrics(::write_text::text_metric * pmetric)

   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GetTextMetricsW(get_handle1(), pmetric) != false;


      ::exception::throw_not_implemented();

      return false;

   }


   //i32 graphics::GetTextCharacterExtra()
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetTextCharacterExtra(get_handle2());
   //   __throw(error_not_implemented);

   //   return -1;
   //}
   //bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, pBuffer) != false;
   //   __throw(error_not_implemented);

   //   return false;
   //}
   //bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer)

   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, pBuffer) != false;
   //   __throw(error_not_implemented);

   //   return false;
   //}
   //u32 graphics::GetFontLanguageInfo()
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetFontLanguageInfo(get_handle1());
   //   __throw(error_not_implemented);

   //   return -1;
   //}


   //u32 graphics::GetCharacterPlacement(const char * pString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetCharacterPlacement(get_handle1(), pString, (int) nCount, (int) nMaxExtent, lpResults, dwFlags);
   //   __throw(error_not_implemented);

   //   return -1;

   //}


   //u32 graphics::GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS pResults, u32 dwFlags)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetCharacterPlacement(get_handle1(), (const char *)str, (i32) str.get_length(), (int) nMaxExtent, pResults, dwFlags);
   //   __throw(error_not_implemented);

   //   return -1;

   //}


   //::size_f64 graphics::GetAspectRatioFilter()
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //::size_f64 ::size_f64;
   //   //VERIFY(::GetAspectRatioFilterEx(get_handle2(), &::size_f64));
   //   //return ::size_f64;
   //   __throw(error_not_implemented);

   //   return nullptr;
   //}
   //bool graphics::ScrollDC(i32 dx, i32 dy,
   //                        const rectangle_i32 &  pRectScroll,const rectangle_i32 &  rectClip,

   //                        ::draw2d::region* pRgnUpdate, RECT * pRectUpdate)

   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::ScrollDC(get_handle1(),dx,dy,&rectClip,
   //   //                  &rectClip, (HRGN)pRgnUpdate->get_os_data(), pRectUpdate) != false;

   //   __throw(error_not_implemented);

   //   return false;
   //}

   //// Printer Escape Functions
   //i32 graphics::Escape(i32 nEscape, i32 nCount, const char * pszInData, LPVOID lpOutData)

   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::Escape(get_handle1(), nEscape, nCount, pszInData, lpOutData);
   //   __throw(error_not_implemented);

   //   return -1;
   //}

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const rectangle_f64 &  rectBounds, UINT flags)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::SetBoundsRect(get_handle1(), &rectBounds, flags);
      __throw(error_not_implemented);

      return -1;
   }


   UINT graphics::GetBoundsRect(::rectangle_f64 * pRectBounds, UINT flags)
   {

      //ASSERT(get_handle2() != nullptr);
      //return ::GetBoundsRect(get_handle2(), pRectBounds, flags);
      __throw(error_not_implemented);

      return -1;
   }


   bool graphics::ResetDC(const DEVMODE* pDevMode)
   {

      //ASSERT(get_handle2() != nullptr);
      //return ::ResetDC(get_handle2(), pDevMode) != nullptr;
      __throw(error_not_implemented);

      return false;
   }


   //UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW potm)
   //{

   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetOutlineTextMetricsW(get_handle2(), cbData, potm);
   //   __throw(error_not_implemented);

   //   return -1;
   //}


   //bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC pabc)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, pabc) != false;
   //   __throw(error_not_implemented);

   //   return false;
   //}
   //u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID pData,

   //                          u32 cbData)
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetFontData(get_handle2(), dwTable, dwOffset, pData, cbData);
   //   __throw(error_not_implemented);

   //   return -1;
   //}
   //i32 graphics::GetKerningPairs(i32 nPairs, LPKERNINGPAIR pkrnpair)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetKerningPairs(get_handle2(), nPairs, pkrnpair);
   //   __throw(error_not_implemented);

   //   return -1;
   //}
   //u32 graphics::GetGlyphOutline(UINT nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS pgm,

   //                              u32 cbBuffer, LPVOID pBuffer, const MAT2* lpmat2)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetGlyphOutline(get_handle2(), nChar, nFormat,
   //   //                         pgm, cbBuffer, lpBuffer, lpmat2);
   //   __throw(error_not_implemented);

   //   return -1;
   //}

   // ::user::document handling functions
   i32 graphics::StartDoc(LPDOCINFO pDocInfo)

   {

      //ASSERT(m_hdc != nullptr);

      //return ::StartDoc(m_hdc, pDocInfo);

      __throw(error_not_implemented);

      return -1;
   }


   i32 graphics::StartPage()
   {

      ASSERT(m_hdc != nullptr);

      ::StartPage(m_hdc);

      m_pgraphics = new Gdiplus::Graphics(m_hdc);

      m_pgraphics->SetPageUnit(Gdiplus::UnitPixel);

      set_text_rendering_hint(::write_text::e_rendering_anti_alias);

      set_smooth_mode(::draw2d::smooth_mode_anti_alias_8x8);

      return 1;

   }


   i32 graphics::EndPage()
   {

      ASSERT(m_hdc != nullptr);

      delete m_pgraphics;


      return ::EndPage(m_hdc);

   }


   //i32 graphics::SetAbortProc(bool (CALLBACK* pfn)(HDC, i32))

   //{

   //   ASSERT(m_hdc != nullptr);

   //   return ::SetAbortProc(m_hdc, (ABORTPROC)pfn);


   //}


   i32 graphics::AbortDoc()
   {

      ASSERT(m_hdc != nullptr);

      return ::AbortDoc(m_hdc);

   }


   i32 graphics::EndDoc()
   {

      ASSERT(m_hdc != nullptr);

      return ::EndDoc(m_hdc);

   }

   
   //bool graphics::MaskBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
   //                       double xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, double xMask, i32 yMask, u32 dwRop)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, GDIPLUS_HDC(pgraphicsSrc),
   //   //                 xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   //bool graphics::PlgBlt(LPPOINT pPoint, ::draw2d::graphics * pgraphicsSrc, double xSrc, i32 ySrc,

   //                      double nWidth, double nHeight, ::draw2d::bitmap& maskBitmap, double xMask, i32 yMask)
   //{

   //   Gdiplus::Status ret = Gdiplus::Status::GenericError;

   //   try
   //   {

   //      if(pgraphicsSrc == nullptr)
   //         return false;

   //      if(pgraphicsSrc->get_current_bitmap() == nullptr)
   //         return false;

   //      if(pgraphicsSrc->get_current_bitmap()->get_os_data() == nullptr)
   //         return false;

   //      Gdiplus::Point point_i32[3];

   //      point_i32[0].X = pPoint[0].x;

   //      point_i32[0].Y = pPoint[0].y;

   //      point_i32[1].X = pPoint[1].x;

   //      point_i32[1].Y = pPoint[1].y;

   //      point_i32[2].X = pPoint[2].x;

   //      point_i32[2].Y = pPoint[2].y;


   //      ret = m_pgraphics->DrawImage((Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), point, 3);

   //      if (ret != Gdiplus::Status::Ok)
   //      {

   //         return false;

   //      }

   //   }
   //   catch(...)
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   bool graphics::SetPixelV(double x, double y, const ::color::color & color)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::SetPixelV(get_handle1(), x, y, color) != false;
      __throw(error_not_implemented);

      return false;

   }
   
   
   bool graphics::SetPixelV(const ::point_f64 & point, const ::color::color & color)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::SetPixelV(get_handle1(), point.x, point.y, color) != false;
      __throw(error_not_implemented);

      return false;

   }

   bool graphics::AngleArc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle)
   {
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != false;
   //   __throw(error_not_implemented);

      return false;

   }


   bool graphics::ArcTo(const rectangle_f64 & rectParam,const point_f64 & pointStart,const point_f64 & pointEnd)
   {
////      ASSERT(get_handle1() != nullptr);
      //return ArcTo(rectParam.left, rectParam.top, rectParam.right,
        //           rectParam.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);
         //   if (::is_null(m_pgraphics))
   //   {

   //      return false;

   //   }

   //   //ASSERT(get_handle1() != nullptr);
   //   //bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   //if (get_handle1() != get_handle2())
   //   //{
   //   //   ::point_i32 point;
   //   //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
   //   //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
   //   //}
   //   //return bResult;
   //   __throw(error_not_implemented);

      return false;
   }
   //i32 graphics::GetArcDirection()
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetArcDirection(get_handle2());
   //   __throw(error_not_implemented);

   //   return -1;

   //}


   bool graphics::poly_polyline(const ::point_f64 * pPoints, const INT * lpPolyPoints, count nCount)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::poly_polyline(get_handle1(), pPoints, (LPDWORD) lpPolyPoints, (DWORD) nCount) != false;

      __throw(error_not_implemented);

      return false;

   }


   //bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetColorAdjustment(get_handle2(), pColorAdjust) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   bool graphics::poly_bezier(const ::point_f64 * pPoints, count nCount)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::poly_bezier(get_handle1(), pPoints, (DWORD) nCount) != false;
      __throw(error_not_implemented);

      return false;


   }


   //i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const char * pszInputData)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::DrawEscape(get_handle1(), nEscape, nInputSize, pszInputData);
   //   __throw(error_not_implemented);

   //   return false;


   //}


   //i32 graphics::Escape(i32 nEscape, i32 nInputSize, const char * pszInputData,  i32 nOutputSize, char * pszOutputData)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::ExtEscape(get_handle1(), nEscape, nInputSize, pszInputData, nOutputSize, pszOutputData);
   //   __throw(error_not_implemented);

   //   return false;


   //}


   //bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
   //                                LPABCFLOAT pABCF)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, pABCF) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}
   //bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* pFloatBuffer)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, pFloatBuffer) != false;
   //   __throw(error_not_implemented);

   //   return false;

   //}


   bool graphics::abort_path()
   {

      if(m_ppath != nullptr)
      {

         delete m_ppath;

         m_ppath = nullptr;

      }

      return true;

   }


   bool graphics::begin_path()
   {

      if (m_ppath != nullptr)
      {

         delete m_ppath;

      }

      m_ppath = new Gdiplus::GraphicsPath;

      return m_ppath != nullptr;

   }


   bool graphics::close_figure()
   {

      ASSERT(m_ppath != nullptr);

      return m_ppath->CloseFigure() == Gdiplus::Status::Ok;

   }


   bool graphics::end_path()
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      m_ppathPaint   = m_ppath;

      m_ppath        = nullptr;

      return true;

   }


   bool graphics::fill_path()
   {

      return m_pgraphics->FillPath(m_pbrush->get_os_data < Gdiplus::Brush * >(this), m_ppath) == Gdiplus::Status::Ok;

   }


   bool graphics::flatten_path()
   {

      return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }


   float graphics::GetMiterLimit()
   {
      //ASSERT(get_handle1() != nullptr);
      //float fMiterLimit;
      //VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      //return fMiterLimit;
      __throw(error_not_implemented);

      return 0.f;

   }


   i32 graphics::GetPath(::point_f64 * pPoints, byte * lpTypes, count nCount)

   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GetPath(get_handle1(), pPoints, lpTypes, (int) nCount);

      __throw(error_not_implemented);

      return false;

   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != false;
      __throw(error_not_implemented);

      return false;

   }


   bool graphics::stroke_and_fill_path()
   {

      bool bOk1 = m_pgraphics->FillPath(m_pbrush->get_os_data < Gdiplus::Brush * >(this), m_ppathPaint) == Gdiplus::Status::Ok;

      bool bOk2 = m_pgraphics->DrawPath(m_ppen->get_os_data < Gdiplus::Pen * >(this), m_ppathPaint) == Gdiplus::Status::Ok;

      return bOk1 && bOk2;

   }


   bool graphics::stroke_path()
   {

      return m_pgraphics->DrawPath(m_ppen->get_os_data < Gdiplus::Pen * >(this), m_ppathPaint) == Gdiplus::Status::Ok;

   }


   bool graphics::widen_path()
   {

      return m_ppath->Widen(m_ppen->get_os_data < Gdiplus::Pen * >(this)) == Gdiplus::Status::Ok;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      //m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
      //m_pgraphics->SetCompositingQuality(Gdiplus::CompositingQualityGammaCorrected);
      //m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

      return m_pgraphics->DrawPath(m_ppen->get_os_data < Gdiplus::Pen * >(this),ppath->get_os_data<Gdiplus::GraphicsPath *>(this)) == Gdiplus::Status::Ok;

   }

   
   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      return m_pgraphics->DrawPath(ppen->get_os_data<Gdiplus::Pen *>(this), ppath->get_os_data <Gdiplus::GraphicsPath *>(this)) == Gdiplus::Status::Ok;

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      Gdiplus::Brush* pbrush = m_pbrush->get_os_data < Gdiplus::Brush* >(this);

      Gdiplus::GraphicsPath * pgraphicspath = ppath->get_os_data < Gdiplus::GraphicsPath* >(this);

      return m_pgraphics->FillPath(pbrush, pgraphicspath) == Gdiplus::Status::Ok;

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      if (ppath == nullptr)
      {

         return false;

      }

      if (pbrush == nullptr)
      {

         return false;

      }

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      ::Gdiplus::Brush * pbr = pbrush->get_os_data < Gdiplus::Brush * >(this);

      if (pbr == nullptr)
      {

         return false;

      }

      auto ppathOs = ppath->get_os_data < Gdiplus::GraphicsPath * >(this);

      if (ppathOs == nullptr)
      {

         return false;

      }

      return m_pgraphics->FillPath(pbr, ppathOs) == Gdiplus::Status::Ok;

   }


   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GdiComment(get_handle1(), nDataSize, pCommentData) != false;
      __throw(error_not_implemented);

      return false;
   }


   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const rectangle_f64 &  rectBounds)
   {

      Gdiplus::RectF rectangle_i32((Gdiplus::REAL) rectBounds.left,(Gdiplus::REAL) rectBounds.top,(Gdiplus::REAL) width(rectBounds),(Gdiplus::REAL) height(rectBounds));

      ap(Gdiplus::Metafile) pMeta = new Gdiplus::Metafile(hEnhMF, false);

      Gdiplus::Status ret = m_pgraphics->DrawImage(pMeta, rectangle);

      if (ret != Gdiplus::Status::Ok)
      {

         return false;

      }

      return true;
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, pBounds);


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



   bool graphics::_alpha_blend_raw(const ::rectangle_f64 & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectSrc , double dRate)
   {

      if (m_pgraphics == nullptr || pgraphicsSrc == nullptr)
      {

         return false;

      }

      synchronous_lock slSource(pgraphicsSrc->mutex());

      //bool bThreadToolsForIncreasedFps = ::get_task()->m_bThreadToolsForIncreasedFps;

      //bool bAvoidProcFork = ::get_task()->m_bAvoidProcFork;

      ////bAvoidProcFork = true;

      //if (!bAvoidProcFork && bThreadToolsForIncreasedFps && nDestWidth == nSrcWidth && nDestHeight == nSrcHeight)
      //{

      //   if (m_ealphamode == ::draw2d::alpha_mode_blend)
      //   {

      //      auto cProcessor = get_processor_count();

      //      if (nDestHeight >= cProcessor * 4 && (nDestWidth * nDestHeight) >= (cProcessor * 64))
      //      {

      //         m_pimage->fork_blend(point_i32(xDest + GetViewportOrg().x, yDest + GetViewportOrg().y), pgraphicsSrc->m_pimage,
      //                                                point_i32(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
      //                                                ::size_f64(nSrcWidth, nDestHeight), (byte)(dRate * 255.0f));

      //         g_cForkBlend++;

      //         if (g_cForkBlend % 100 == 0)
      //         {
      //            output_debug_string("\nfork_blend(" + __str(g_cForkBlend) + ") sample=" + __str(nSrcWidth) + "," + __str(nDestHeight));
      //         }

      //      }
      //      else
      //      {

      //         m_pimage->blend(point_i32(xDest + GetViewportOrg().x, yDest + GetViewportOrg().y), pgraphicsSrc->m_pimage,
      //                                           point_i32(xSrc+pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
      //                                           ::size_f64(nSrcWidth, nDestHeight), (byte)(dRate * 255.0f));

      //      }

      //   }
      //   else
      //   {

      //      m_pimage->from(point_i32(xDest + GetViewportOrg().x, yDest + GetViewportOrg().y), pgraphicsSrc->m_pimage,
      //                                       point_i32(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
      //                                       ::size_f64(nSrcWidth, nDestHeight), (byte) (dRate * 255.0f));


      //   }

      //   return true;

      //}


      float fA = (float) (dRate);


      Gdiplus::ColorMatrix colormatrix;

      if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
      {

         copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);

      }
      else
      {

         ::draw2d::color_matrix m;

         copy_color_matrix(colormatrix.m, m.a);

      }

      colormatrix.m[3][3] = fA;

      Gdiplus::ImageAttributes imageattributes;

      imageattributes.SetColorMatrix(
      &colormatrix,
         Gdiplus::ColorMatrixFlagsDefault,
         Gdiplus::ColorAdjustTypeBitmap);

      Gdiplus::RectF rectfDst((Gdiplus::REAL) rectDst.left, (Gdiplus::REAL) rectDst.top, (Gdiplus::REAL) rectDst.width(), (Gdiplus::REAL) rectDst.height());

      if (pgraphicsSrc == nullptr)
      {

         return false;

      }

      if (pgraphicsSrc->get_current_bitmap() == nullptr)
      {

         return false;

      }

      Gdiplus::Bitmap * pbitmap = nullptr;

      try
      {

         pbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();

      }
      catch(...)
      {

      }

      Gdiplus::Status ret = Gdiplus::Status::GenericError;

      if(pbitmap != nullptr)
      {

         ret =  m_pgraphics->DrawImage(pbitmap,rectfDst,
            (Gdiplus::REAL) rectSrc.left,
            (Gdiplus::REAL) rectSrc.top,
            (Gdiplus::REAL) rectSrc.width(),
            (Gdiplus::REAL) rectSrc.height(),
            Gdiplus::UnitPixel,&imageattributes);

         if (ret != Gdiplus::Status::Ok)
         {

            return false;

         }

      }

      return true;

   }




#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(::size_f64 * psize)

   {
      ASSERT(__is_valid_address(psize, sizeof(const size_f64 &)));


      i32 nMapMode;
      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained map mode, map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         DPtoLP(psize);

         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // map against logical inch for non-constrained mapping modes
         i32 cxPerInch, cyPerInch;
         if (this != nullptr)
         {
            ASSERT_VALID(this);
            //ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);
         }
         else
         {
//            cxPerInch = afxData.cxPixelsPerInch;
            //          cyPerInch = afxData.cyPixelsPerInch;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         psize->cx = psize->cx * HIMETRIC_INCH / cxPerInch;

         psize->cy = psize->cy * HIMETRIC_INCH / cyPerInch;

      }
   }

   void graphics::HIMETRICtoDP(::size_f64 * psize)

   {
      ASSERT(__is_valid_address(psize, sizeof(const size_f64&)));


      i32 nMapMode;
      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
            nMapMode != MM_TEXT)
      {
         // when using a constrained map mode, map against physical inch
         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
         LPtoDP(psize);

         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
      }
      else
      {
         // map against logical inch for non-constrained mapping modes
         i32 cxPerInch, cyPerInch;
         if (this != nullptr)
         {
            ASSERT_VALID(this);
            //ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
            cxPerInch = GetDeviceCaps(LOGPIXELSX);
            cyPerInch = GetDeviceCaps(LOGPIXELSY);
         }
         else
         {
//            cxPerInch = afxData.cxPixelsPerInch;
            //          cyPerInch = afxData.cyPixelsPerInch;
         }
         ASSERT(cxPerInch != 0 && cyPerInch != 0);
         psize->cx = psize->cx* cxPerInch/ HIMETRIC_INCH;

         psize->cy = psize->cy * cyPerInch/ HIMETRIC_INCH;

      }
   }

   void graphics::LPtoHIMETRIC(::size_f64 * psize)

   {
      ASSERT(__is_valid_address(psize, sizeof(const size_f64 &)));


      LPtoDP(psize);

      DPtoHIMETRIC(psize);

   }


   void graphics::HIMETRICtoLP(::size_f64 * psize)
   {

      ASSERT(__is_valid_address(psize, sizeof(const size_f64 &)));

      HIMETRICtoDP(psize);

      DPtoLP(psize);

   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* graphics::GetHalftoneBrush(::object * pobject)
   {
      /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
            if (gen_HalftoneBrush == nullptr)
            {
               WORD grayPattern[8];
               for (i32 i = 0; i < 8; i++)
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

      //      return ::draw2d_gdiplus::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }


   //void graphics::DrawDragRect(const rectangle_i32 &  prectangle, const ::size_f64 & size, const rectangle_i32 &  lpRectLast, const ::size_f64 & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   ::exception::throw_not_implemented();

   //   /*

   //         ASSERT(__is_valid_address(prectangle, sizeof(const rectangle_i32 &), false));

   //         ASSERT(pRectLast == nullptr ||

   //            __is_valid_address(pRectLast, sizeof(const rectangle_i32 &), false));


   //         // first, determine the update region and select it
   //         ::draw2d::region rgnNew;
   //         ::draw2d::region rgnOutside, rgnInside;
   //         rgnOutside.create_rect(prectangle);

   //         const ::rectangle_i32 & rectangle = *prectangle;

   //         rectangle.inflate(-size.cx, -size.cy);
   //         rectangle.intersect(rectangle, prectangle);

   //         rgnInside.create_rect(rectangle);
   //         rgnNew.create_rect(0, 0, 0, 0);
   //         rgnNew.combine(&rgnOutside, &rgnInside, RGN_XOR);

   //         ::draw2d::brush* pBrushOld = nullptr;
   //         if (pBrush == nullptr)
   //         {
   //            pBrush = graphics::GetHalftoneBrush(get_application());
   //         }

   //         ENSURE(pBrush);

   //         if (pBrushLast == nullptr)
   //         {
   //            pBrushLast = pBrush;
   //         }

   //         ::draw2d::region rgnLast, rgnUpdate;
   //         if (pRectLast != nullptr)

   //         {
   //            // find difference between new region and old region
   //            rgnLast.create_rect(0, 0, 0, 0);
   //            rgnOutside.SetRectRgn(pRectLast);

   //            rectangle = *pRectLast;

   //            rectangle.inflate(-sizeLast.cx, -sizeLast.cy);
   //            rectangle.intersect(rectangle, pRectLast);

   //            rgnInside.SetRectRgn(rectangle);
   //            rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

   //            // only diff them if brushes are the same
   //            if (pBrush->get_os_data() == pBrushLast->get_os_data())
   //            {
   //               rgnUpdate.create_rect(0, 0, 0, 0);
   //               rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
   //            }
   //         }
   //         if (pBrush->get_os_data() != pBrushLast->get_os_data() && pRectLast != nullptr)

   //         {
   //            // brushes are different -- erase old region first
   //            SelectClipRgn(&rgnLast);
   //            get_clip_box(&rectangle);
   //            pBrushOld = set(pBrushLast);
   //            PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);
   //            set(pBrushOld);
   //            pBrushOld = nullptr;
   //         }

   //         // draw into the update/new region
   //         SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
   //         get_clip_box(&rectangle);
   //         pBrushOld = set(pBrush);
   //         PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);

   //         // cleanup DC
   //         if (pBrushOld != nullptr)
   //            set(pBrushOld);
   //         SelectClipRgn(nullptr);

   //   */
   //}

   /*void graphics::fill_rectangle(const rectangle_i32 &  prectangle, COLORREF clr)

   {
      ::SetBkColor(get_handle1(), clr);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, prectangle, nullptr, 0, nullptr);

   }*/


   bool graphics::fill_rectangle(const ::rectangle_f64 & rectParam, const ::color::color & color)
   {

      try
      {

         if (m_pgraphics == nullptr)
         {

            return false;

         }

         Gdiplus::RectF rectangle_i32;

         __copy(rectangle, rectParam);

         Gdiplus::SolidBrush b(Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB));

         m_pgraphics->FillRectangle(&b, rectangle);

      }
      catch (...)
      {

      }

      return true;

   }


   bool graphics::draw_rectangle(const ::rectangle_f64 & rectangle, const ::color::color& color, const ::e_border & eborder)
   {

      if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
      {

         return false;

      }

      Gdiplus::Pen pen(Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB), 1.0);

      //if ((eborder & e_border_left) && (eborder & e_border_top)
      //   && (eborder & e_border_right) && (eborder & e_border_bottom)
      //   && crTopLeft == crBottomRight)
      //{

      //   m_pgraphics->DrawRectangle(&pen, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

      //} else
      if ((eborder & e_border_left) && (eborder & e_border_top))
      {

         Gdiplus::GraphicsPath path;

         Gdiplus::PointF pa[3];

         pa[0].X = (Gdiplus::REAL) rectangle.left;
         pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
         pa[1].X = (Gdiplus::REAL) rectangle.left;
         pa[1].Y = (Gdiplus::REAL) rectangle.top;
         pa[2].X = (Gdiplus::REAL) rectangle.right;
         pa[2].Y = (Gdiplus::REAL)rectangle.top;

         path.AddLines(pa, 3);

         m_pgraphics->DrawPath(&pen, &path);

      }
      else
      {

         if (eborder & e_border_left)
         {

            m_pgraphics->DrawLine(&pen, 
               (Gdiplus::REAL) rectangle.left, 
               (Gdiplus::REAL)rectangle.bottom - 1, 
               (Gdiplus::REAL)rectangle.left, 
               (Gdiplus::REAL)rectangle.top);

         }
         else if (eborder & e_border_top)
         {

            m_pgraphics->DrawLine(&pen, 
               (Gdiplus::REAL)rectangle.left,
               (Gdiplus::REAL)rectangle.top, 
               (Gdiplus::REAL)rectangle.right, 
               (Gdiplus::REAL)rectangle.top);

         }

      }

      if ((eborder & e_border_right) && (eborder & e_border_bottom))
      {

         Gdiplus::GraphicsPath path;

         Gdiplus::PointF pa[3];

         pa[0].X = (Gdiplus::REAL) rectangle.left;
         pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
         pa[1].X = (Gdiplus::REAL) rectangle.right;
         pa[1].Y = (Gdiplus::REAL) rectangle.bottom;
         pa[2].X = (Gdiplus::REAL) rectangle.right;
         pa[2].Y = (Gdiplus::REAL) rectangle.top;

         path.AddLines(pa, 3);

         m_pgraphics->DrawPath(&pen, &path);

      }
      else
      {

         if (eborder & e_border_bottom)
         {

            m_pgraphics->DrawLine(&pen,
               (Gdiplus::REAL)rectangle.left, 
               (Gdiplus::REAL)rectangle.bottom,
               (Gdiplus::REAL)rectangle.right,
               (Gdiplus::REAL)rectangle.bottom);

         }
         else if (eborder & e_border_right)
         {

            m_pgraphics->DrawLine(&pen, 
               (Gdiplus::REAL)rectangle.right, 
               (Gdiplus::REAL)rectangle.bottom, 
               (Gdiplus::REAL)rectangle.right, 
               (Gdiplus::REAL)rectangle.top + 1);

         }

      }

      return true;

   }


   //bool graphics::draw_rectangle(const ::rectangle_f64& rectangle, const ::color::color& color, const ::e_border & eborder)
   //{

   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen pen(Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB), 1.0);

   //   //if ((eborder & e_border_left) && (eborder & e_border_top)
   //   //   && (eborder & e_border_right) && (eborder & e_border_bottom)
   //   //   && crTopLeft == crBottomRight)
   //   //{

   //   //   m_pgraphics->DrawRectangle(&pen, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   //   //} else
   //   if ((eborder & e_border_left) && (eborder & e_border_top))
   //   {

   //      Gdiplus::GraphicsPath path;

   //      Gdiplus::PointF pa[3];

   //      pa[0].X = (Gdiplus::REAL) rectangle.left;
   //      pa[0].Y = (Gdiplus::REAL) rectangle.bottom - 1;
   //      pa[1].X = (Gdiplus::REAL) rectangle.left;
   //      pa[1].Y = (Gdiplus::REAL) rectangle.top;
   //      pa[2].X = (Gdiplus::REAL) rectangle.right;
   //      pa[2].Y = (Gdiplus::REAL) rectangle.top;

   //      path.AddLines(pa, 3);

   //      m_pgraphics->DrawPath(&pen, &path);

   //   }
   //   else
   //   {

   //      if (eborder & e_border_left)
   //      {

   //         m_pgraphics->DrawLine(&pen, (Gdiplus::REAL) rectangle.left, (Gdiplus::REAL)rectangle.bottom-1, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top);

   //      }
   //      else if (eborder & e_border_top)
   //      {

   //         m_pgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top);

   //      }

   //   }


   //   if ((eborder & e_border_right) && (eborder & e_border_bottom))
   //   {

   //      Gdiplus::GraphicsPath path;

   //      Gdiplus::PointF pa[3];

   //      pa[0].X = (Gdiplus::REAL) rectangle.left;
   //      pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
   //      pa[1].X = (Gdiplus::REAL) rectangle.right;
   //      pa[1].Y = (Gdiplus::REAL) rectangle.top;
   //      pa[2].X = (Gdiplus::REAL) rectangle.right;
   //      pa[2].Y = (Gdiplus::REAL) rectangle.top + 1;

   //      path.AddLines(pa, 3);

   //   }
   //   else
   //   {

   //      if (eborder & e_border_bottom)
   //      {

   //         m_pgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom);

   //      }
   //      else if (eborder & e_border_right)
   //      {

   //         m_pgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top + 1);

   //      }

   //   }

   //}


   bool graphics::draw_3drect(const ::rectangle_f64 & rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder)
   {

      if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
      {

         return false;

      }


      if (colorTopLeft == colorBottomRight)
      {

         return draw_rectangle(rectangle, colorTopLeft, eborder);

      }


      if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
      {

         return false;

      }

      {

         Gdiplus::Pen pen(Gdiplus::Color(colorTopLeft.m_iA, colorTopLeft.m_iR, colorTopLeft.m_iG, colorTopLeft.m_iB), 1.0);

         if ((eborder & e_border_left) && (eborder & e_border_top))
         {

            Gdiplus::GraphicsPath path;

            Gdiplus::PointF pa[3];

            pa[0].X = (Gdiplus::REAL) rectangle.left;
            pa[0].Y = (Gdiplus::REAL) rectangle.bottom - 1;
            pa[1].X = (Gdiplus::REAL) rectangle.left;
            pa[1].Y = (Gdiplus::REAL) rectangle.top;
            pa[2].X = (Gdiplus::REAL) rectangle.right;
            pa[2].Y = (Gdiplus::REAL) rectangle.top;

            path.AddLines(pa, 3);

            m_pgraphics->DrawPath(&pen, &path);

         }
         else
         {

            if (eborder & e_border_left)
            {

               m_pgraphics->DrawLine(&pen, (Gdiplus::REAL) rectangle.left, (Gdiplus::REAL)rectangle.bottom - 1, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top);

            }
            else if (eborder & e_border_top)
            {

               m_pgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top);

            }

         }

      }

      {

         Gdiplus::Pen pen(Gdiplus::Color(colorBottomRight.m_iA, colorBottomRight.m_iR, colorBottomRight.m_iG, colorBottomRight.m_iB), 1.0);

         if ((eborder & e_border_right) && (eborder & e_border_bottom))
         {

            Gdiplus::GraphicsPath path;

            Gdiplus::PointF pa[3];

            pa[0].X = (Gdiplus::REAL) rectangle.left;
            pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
            pa[1].X = (Gdiplus::REAL) rectangle.right;
            pa[1].Y = (Gdiplus::REAL) rectangle.top;
            pa[2].X = (Gdiplus::REAL) rectangle.right;
            pa[2].Y = (Gdiplus::REAL) rectangle.top + 1;

            path.AddLines(pa, 3);

         }
         else
         {

            if (eborder & e_border_bottom)
            {

               m_pgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom);

            }
            else if (eborder & e_border_right)
            {

               m_pgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top + 1);

            }

         }

      }

      return true;

   }


   //void graphics::draw_3drect(const ::rectangle_i32& rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder)
   //{

   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return;

   //   }


   //   if (colorTopLeft == colorBottomRight)
   //   {

   //      draw_rectangle(rectangle, colorTopLeft, eborder);

   //      return;

   //   }


   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return;

   //   }

   //   {

   //      Gdiplus::Pen pen(Gdiplus::Color(colorTopLeft.m_iA, colorTopLeft.m_iR, colorTopLeft.m_iG, colorTopLeft.m_iB), 1.0);

   //      if ((eborder & e_border_left) && (eborder & e_border_top))
   //      {

   //         Gdiplus::GraphicsPath path;

   //         Gdiplus::Point pa[3];

   //         pa[0].X = rectangle.left;
   //         pa[0].Y = rectangle.bottom - 1;
   //         pa[1].X = rectangle.left;
   //         pa[1].Y = rectangle.top;
   //         pa[2].X = rectangle.right;
   //         pa[2].Y = rectangle.top;

   //         path.AddLines(pa, 3);

   //         m_pgraphics->DrawPath(&pen, &path);

   //      }
   //      else
   //      {

   //         if (eborder & e_border_left)
   //         {

   //            m_pgraphics->DrawLine(&pen, rectangle.left, rectangle.bottom - 1, rectangle.left, rectangle.top);

   //         }
   //         else if (eborder & e_border_top)
   //         {

   //            m_pgraphics->DrawLine(&pen, rectangle.left, rectangle.top, rectangle.right, rectangle.top);

   //         }

   //      }

   //   }

   //   {

   //      Gdiplus::Pen pen(Gdiplus::Color(colorBottomRight.m_iA, colorBottomRight.m_iR, colorBottomRight.m_iG, colorBottomRight.m_iB), 1.0);

   //      if ((eborder & e_border_right) && (eborder & e_border_bottom))
   //      {

   //         Gdiplus::GraphicsPath path;

   //         Gdiplus::Point pa[3];

   //         pa[0].X = rectangle.left;
   //         pa[0].Y = rectangle.bottom;
   //         pa[1].X = rectangle.right;
   //         pa[1].Y = rectangle.top;
   //         pa[2].X = rectangle.right;
   //         pa[2].Y = rectangle.top + 1;

   //         path.AddLines(pa, 3);

   //      }
   //      else
   //      {

   //         if (eborder & e_border_bottom)
   //         {

   //            m_pgraphics->DrawLine(&pen, rectangle.left, rectangle.bottom, rectangle.right, rectangle.bottom);

   //         }
   //         else if (eborder & e_border_right)
   //         {

   //            m_pgraphics->DrawLine(&pen, rectangle.right, rectangle.bottom, rectangle.right, rectangle.top + 1);

   //         }

   //      }

   //   }

   //}


   void graphics::close_graphics()
   {

      if (m_hdcAttach != nullptr)
      {

         detach_hdc();

      }

      if (m_pgraphics != nullptr)
      {

         try
         {

            delete m_pgraphics;

         }
         catch (...)
         {

            TRACE("graphics::DeleteDC : Failed to delete Gdiplus::Graphics");

         }

         m_pgraphics = nullptr;

      }

      if (m_hdcGraphics != nullptr)
      {

         bool bDeleted = ::DeleteDC(m_hdcGraphics) != false;

         if (!bDeleted)
         {

            TRACE("graphics::DeleteDC : Failed to delete GDI device context");

         }

         m_hdcGraphics = NULL;

      }

      if (m_ppath != nullptr)
      {

         try
         {

            delete m_ppath;

         }
         catch (...)
         {

         }

         m_ppath = nullptr;

      }

      if (m_ppathPaint != nullptr)
      {

         try
         {

            delete m_ppathPaint;

         }
         catch (...)
         {

         }

         m_ppathPaint = nullptr;

      }

   }


   bool graphics::attach_hdc(HDC hdc)
   {

      if (hdc == nullptr)
      {

         return false;

      }

      if(m_hdcAttach == hdc)
      {

         if (m_pgraphics != nullptr)
         {

            return true;

         }

      }

      close_graphics();

      if(hdc != nullptr)
      {

         m_pgraphics = new ::Gdiplus::Graphics((HDC) hdc);

         m_pgraphics->SetPageUnit(Gdiplus::UnitPixel);

         set_text_rendering_hint(::write_text::e_rendering_anti_alias);

         set_smooth_mode(::draw2d::smooth_mode_anti_alias_8x8);

         m_hdcAttach = hdc;

      }

      return m_pgraphics != nullptr;

      /*ASSERT(get_handle1() == nullptr);      // only attach once, detach on destroy
      ASSERT(get_handle2() == nullptr);    // only attach to an is_empty DC

      if (hDC == nullptr)
      {
         return false;
      }
      // remember early to avoid leak
      set_handle1(hDC);
      hdc_map* pMap = afxMapHDC(true); // create map if not exist
      ASSERT(pMap != nullptr);
      pMap->set_permanent(get_handle1(), this);

      SetAttribDC(get_handle1());     // Default to same as output
      return true;*/
   }


   HDC graphics::detach_hdc()
   {

      if (m_hdcAttach == nullptr)
      {

         return nullptr;

      }

      if (m_pgraphics == nullptr)
      {

         return nullptr;

      }

      try
      {

         delete m_pgraphics;

      }
      catch(...)
      {

         TRACE("graphics::Detach : Failed to delete Gdiplus::Graphics");

      }

      m_pgraphics = nullptr;

      HDC hdc = m_hdcAttach;

      m_hdcAttach = nullptr;

      return hdc;

   }


   bool graphics::AttachPrinter(HDC hdc)
   {

      if (hdc == nullptr)
         return false;

      if (m_hdc == hdc)
      {

         return true;

      }

      if (hdc != nullptr)
      {

         m_hdc = (HDC)hdc;

      }

      return m_hdc != nullptr;

   }


   HDC graphics::DetachPrinter()
   {

      if (m_hdc == nullptr)
         return nullptr;

      HDC hdc = m_hdc;

      m_hdc = nullptr;

      return hdc;

   }


   bool graphics::DeleteDC()
   {

      close_graphics();

      return true;

   }


   i32 graphics::StartDoc(const char * pszDocName)

   {

      DOCINFOW di;

      __memset(&di, 0, sizeof(DOCINFOW));

      di.cbSize = sizeof(DOCINFOW);

      di.lpszDocName = wstring(pszDocName);


      return StartDoc(&di);

   }


   i32 graphics::SaveDC()
   {

      Gdiplus::GraphicsState state = m_pgraphics->Save();

      return (int) state;

   }


   bool graphics::RestoreDC(i32 nSavedDC)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      Gdiplus::Status status = m_pgraphics->Restore((Gdiplus::GraphicsState) nSavedDC);

      return status == Gdiplus::Ok;

   }


   //::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   //{

   //   return nullptr;

   //}


   i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
   {
      //i32 nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
      //return nRetVal;
      __throw(error_not_implemented);

      return -1;

   }

   i32 graphics::SetROP2(i32 nDrawMode)
   {
      //i32 nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   nRetVal = ::SetROP2(get_handle1(), nDrawMode);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetROP2(get_handle2(), nDrawMode);
      //return nRetVal;
      __throw(error_not_implemented);

      return -1;

   }


   bool graphics::set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode)
   {

      if(m_pgraphics == nullptr)
      {

         return false;

      }

      if(einterpolationmode == ::draw2d::e_interpolation_mode_nearest_neighbor)
      {

         m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

      }
      else if(einterpolationmode == ::draw2d::e_interpolation_mode_high_quality_bicubic)
      {

         m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

      }
      else
      {

         m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);

      }

      return true;

      /*i32 nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
      return nRetVal;*/

   }


   i32 graphics::SetGraphicsMode(i32 iMode)
   {
      //i32 nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //{
      //   nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
      //}
      //if(get_handle2() != nullptr)
      //{
      //   nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
      //}
      //return nRetVal;
      __throw(error_not_implemented);

      return -1;
   }


   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      Gdiplus::REAL rectangle_i32[6];

      rectangle_i32[0] = pXform->eDx;
      rectangle_i32[1] = pXform->eDy;

      rectangle_i32[2] = pXform->eM11;
      rectangle_i32[3] = pXform->eM12;
      rectangle_i32[4] = pXform->eM21;
      rectangle_i32[5] = pXform->eM22;

      Gdiplus::Matrix m;

      m.SetElements(rectangle_i32[2],rectangle_i32[3],rectangle_i32[4],rectangle_i32[5],rectangle_i32[0],rectangle_i32[1]);

      m_pgraphics->SetTransform(&m);

      return true;
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,u32 iMode)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //bool nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //{
      //   nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != false;
      //}
      //if(get_handle2() != nullptr)
      //{
      //   nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != false;
      //}
      //return nRetVal;
      __throw(error_not_implemented);

      return false;
   }

   i32 graphics::SetMapMode(i32 nMapMode)
   {
      //i32 nRetVal = 0;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   nRetVal = ::SetMapMode(get_handle1(), nMapMode);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetMapMode(get_handle2(), nMapMode);
      //return nRetVal;
      ///__throw(error_not_implemented);

      return -1;
   }


   size_f64 graphics::SetViewportExt(double x, double y)
   {

      ::size_f64 size(0, 0);
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetViewportExtEx(get_handle1(), x, y, &::size_f64);
      //if(get_handle2() != nullptr)
      //   ::SetViewportExtEx(get_handle2(), x, y, &::size_f64);
      return size;

   }


   point_f64 graphics::SetWindowOrg(double x, double y)
   {
      //::point_i32 point;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetWindowOrgEx(get_handle1(), x, y, &point);
      //if(get_handle2() != nullptr)
      //   ::SetWindowOrgEx(get_handle2(), x, y, &point);
      return nullptr;
   }


   point_f64 graphics::offset_window_org(double nWidth, double nHeight)
   {
//      ::point_i32 point;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
      //if(get_handle2() != nullptr)
      //   ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
      return nullptr;
   }


   size_f64 graphics::set_window_ext(double x, double y)
   {
      ::size_f64 size(0, 0);
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetWindowExtEx(get_handle1(), x, y, &::size_f64);
      //if(get_handle2() != nullptr)
      //   ::SetWindowExtEx(get_handle2(), x, y, &::size_f64);
      return size;
   }


   size_f64 graphics::scale_window_ext(double xNum, double xDenom, double yNum, double yDenom)
   {
      ::size_f64 size(0, 0);
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &::size_f64);
      //if(get_handle2() != nullptr)
      //   ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &::size_f64);
      return size;
   }


   i32 graphics::get_clip_box(::rectangle_f64 * prectangle)
   {

      Gdiplus::Rect rectangle_i32;

      m_pgraphics->GetClipBounds(&rectangle);

      __copy(prectangle, rectangle);

      return 1;

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
               //case e_shape_ellipse:
               //   intersect_clip(shapea[i]->shape < ::ellipse>());
               //   break;
               case e_shape_ovald:
                  intersect_clip(shapea[i]->shape < ::ellipse>());
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


   ::e_status graphics::reset_clip()
   {

      m_pgraphics->ResetClip();

      return ::success;

   }


   ::e_status graphics::intersect_clip(const ::rectangle_i32& rectangle)
   {

      Gdiplus::RectF r;

      __copy(r, rectangle);

      r.X += (Gdiplus::REAL)m_pointAddShapeTranslate.x;

      r.Y += (Gdiplus::REAL)m_pointAddShapeTranslate.y;

      m_pgraphics->IntersectClip(r);

      return ::success;

   }


   ::e_status graphics::intersect_clip(const ::rectangle_f64& rectangle)
   {

      Gdiplus::RectF r;

      __copy(r, rectangle);

      r.X += (Gdiplus::REAL)m_pointAddShapeTranslate.x;

      r.Y += (Gdiplus::REAL)m_pointAddShapeTranslate.y;

      m_pgraphics->IntersectClip(r);

      return ::success;

   }


   ::e_status graphics::intersect_clip(const ::ellipse& ellipse)
   {

      auto ppath = __auto(new Gdiplus::GraphicsPath());

      Gdiplus::RectF r;

      __copy(r, ellipse);

      r.X += (Gdiplus::REAL)m_pointAddShapeTranslate.x;

      r.Y += (Gdiplus::REAL)m_pointAddShapeTranslate.y;

      ppath->AddArc(r, 0.f, 360.0f);

      m_pgraphics->SetClip(ppath, Gdiplus::CombineModeIntersect);

      return ::success;

   }


   ::e_status graphics::intersect_clip(const ::ellipse& ellipse)
   {

      auto ppath = __auto(new Gdiplus::GraphicsPath());

      Gdiplus::RectF r;

      __copy(r, ellipse);

      r.X += (Gdiplus::REAL)m_pointAddShapeTranslate.x;

      r.Y += (Gdiplus::REAL)m_pointAddShapeTranslate.y;

      ppath->AddArc(r, 0.f, 360.0f);

      m_pgraphics->SetClip(ppath, Gdiplus::CombineModeIntersect);

      return ::success;

   }


   ::e_status graphics::intersect_clip(const ::polygon_i32& polygon_i32)
   {

      auto ppath = __auto(new Gdiplus::GraphicsPath());

      auto copy = [this](Gdiplus::PointF* p2, const POINT* p1)
      {

         p2->X = (Gdiplus::REAL)(p1->x + m_pointAddShapeTranslate.x);

         p2->Y = (Gdiplus::REAL)(p1->y + m_pointAddShapeTranslate.y);

      };

      ap(Gdiplus::PointF) ppoint(polygon_i32.get_data(), polygon_i32.get_count(), copy);

      ppath->AddPolygon(ppoint, (INT) polygon_i32.get_count());

      m_pgraphics->SetClip(ppath, Gdiplus::CombineModeIntersect);

      return ::success;

   }


   ::e_status graphics::intersect_clip(const ::polygon_f64& polygon_i32)
   {

      auto ppath = __auto(new Gdiplus::GraphicsPath());

      auto copy = [this](Gdiplus::PointF* p2, const POINT_F64* p1)
      {

         p2->X = (Gdiplus::REAL) (p1->x + m_pointAddShapeTranslate.x);

         p2->Y = (Gdiplus::REAL) (p1->y + m_pointAddShapeTranslate.y);

      };

      ap(Gdiplus::PointF) ppoint(polygon_i32.get_data(), polygon_i32.get_count(), copy);

      ppath->AddPolygon(ppoint, (INT) polygon_i32.get_count());

      m_pgraphics->SetClip(ppath, Gdiplus::CombineModeIntersect);

      return ::success;

   }





   //i32 graphics::SelectClipRgn(::draw2d::region * pregion)
   //{

   //   if(pregion == nullptr)
   //   {

   //      m_pgraphics->ResetClip();

   //   }
   //   else
   //   {

   //      m_pgraphics->SetClip(pregion->get_os_data<Region * >(this));

   //   }

   //   return 0;

   //}


   //i32 graphics::ExcludeClipRect(double x1, i32 y1, double x2, i32 y2)
   //{
   //   i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
   //   return nRetVal;
   //}

   //i32 graphics::ExcludeClipRect(const rectangle_i32 &  rectParam)
   //{
   //   i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::ExcludeClipRect(get_handle1(), rectParam.left, rectParam.top,
   //   //                               rectParam.right, rectParam.bottom);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::ExcludeClipRect(get_handle2(), rectParam.left, rectParam.top,
   //   //                               rectParam.right, rectParam.bottom);
   //   return nRetVal;
   //}

   //i32 graphics::IntersectClipRect(double x1, i32 y1, double x2, i32 y2)
   //{
   //   i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
   //   return nRetVal;
   //}

   //i32 graphics::IntersectClipRect(const rectangle_i32 &  rectBounds)
   //{
   //   i32 nRetVal = ERROR;

   //   Gdiplus::Rect rectangle_i32(rectBounds.left, rectBounds.top, width(rectBounds),  height(rectBounds));

   //   m_pgraphics->IntersectClip(rectangle);

   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::IntersectClipRect(get_handle1(),rectBounds.left,rectBounds.top,rectBounds.right,rectBounds.bottom);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::IntersectClipRect(get_handle2(),rectBounds.left,rectBounds.top,rectBounds.right,rectBounds.bottom);
   //   return SIMPLEREGION;
   //}

   //i32 graphics::OffsetClipRgn(double x, double y)
   //{
   //   i32 nRetVal = ERROR;
   //   return OffsetClipRgn({ x, y });
   //   return nRetVal;
   //}

   //i32 graphics::OffsetClipRgn(const ::size_f64 & size)
   //{
   //   i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
   //   m_pgraphics->TranslateClip(size.cx, size.cy);
   //   return nRetVal;
   //}


   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UINT nRetVal = GDI_ERROR;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetTextAlign(get_handle1(), nFlags);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetTextAlign(get_handle2(), nFlags);
      return nRetVal;
   }

   //i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
   //{
   //   i32 nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
   //   return nRetVal;
   //}

   //i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   i32 nRetVal = 0x8000000;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
   //   return nRetVal;
   //}

   //u32 graphics::SetMapperFlags(u32 dwFlag)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   u32 dwRetVal = GDI_ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
   //   //if(get_handle2() != nullptr)
   //   //   dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
   //   return dwRetVal;
   //}

   typedef u32 (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   typedef u32 (CALLBACK* __GDISETLAYOUTPROC)(HDC, u32);

   u32 graphics::GetLayout()
   {
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      /*      u32 dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(get_handle1());
            else
            {
               dwGetLayout = GDI_ERROR;
               SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
            }*/
      //return dwGetLayout;
      return 0;
   }

   u32 graphics::SetLayout(u32 dwSetLayout)
   {
      /*HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      u32 dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != nullptr)
         dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;*/

      return 0;

   }
   /*
   void window::ScreenToClient(RECT * prectangle)

   {
   ASSERT(::IsWindow(get_handle1()));
   ::ScreenToClient(get_handle1(), (LPPOINT)prectangle);

   ::ScreenToClient(get_handle1(), ((LPPOINT)prectangle)+1);

   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rectangle_i32::swap_left_right(prectangle);

   }

   void window::ClientToScreen(RECT * prectangle)

   {
   ASSERT(::IsWindow(get_handle1()));
   ::ClientToScreen(get_handle1(), (LPPOINT)prectangle);

   ::ClientToScreen(get_handle1(), ((LPPOINT)prectangle)+1);

   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rectangle_i32::swap_left_right(prectangle);

   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   //bool graphics::ArcTo(double x1, i32 y1, double x2, i32 y2, double x3, double y3, double x4, double y4)
   //{

   //   if (::is_null(m_pgraphics))
   //   {

   //      return false;

   //   }

   //   //ASSERT(get_handle1() != nullptr);
   //   //bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   //if (get_handle1() != get_handle2())
   //   //{
   //   //   ::point_i32 point;
   //   //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
   //   //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
   //   //}
   //   //return bResult;
   //   __throw(error_not_implemented);

   //   return false;
   //}

   //i32 graphics::SetArcDirection(i32 nArcDirection)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //i32 nResult = 0;
   //   //if (get_handle1() != get_handle2())
   //   //   nResult = ::SetArcDirection(get_handle1(), nArcDirection);
   //   //if (get_handle2() != nullptr)
   //   //   nResult = ::SetArcDirection(get_handle2(), nArcDirection);
   //   //return nResult;
   //   __throw(error_not_implemented);

   //   return -1;
   //}


   bool graphics::polydraw(const ::point_f64 * pPoints, const BYTE* lpTypes, count nCount)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //ASSERT(get_handle1() != nullptr);

      //bool bResult = ::poly_draw(get_handle1(), pPoints, lpTypes, (int) nCount) != false;


      //if (get_handle1() != get_handle2())
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
      //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
      //}
      //return bResult;
      __throw(error_not_implemented);

      return false;
   }


   bool graphics::polyline_to(const ::point_f64 * pPoints, count nCount)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //ASSERT(get_handle1() != nullptr);
      //bool bResult = ::polyline_to(get_handle1(), pPoints, (DWORD) nCount) != false;

      //if (get_handle1() != get_handle2())
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
      //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
      //}
      //return bResult;
      __throw(error_not_implemented);

      return false;
   }


   //bool graphics::SetColorAdjustment(const COLORADJUSTMENT* pColorAdjust)
   //{

   //   if (::is_null(m_pgraphics))
   //   {

   //      return false;

   //   }

   //   //ASSERT(get_handle1() != nullptr);
   //   //bool bResult = false;
   //   //if (get_handle1() != get_handle2())
   //   //   bResult = ::SetColorAdjustment(get_handle1(), pColorAdjust) != false;

   //   //if (get_handle2() != nullptr)
   //   //   bResult = ::SetColorAdjustment(get_handle2(), pColorAdjust) != false;

   //   //return bResult;
   //   __throw(error_not_implemented);

   //   return false;

   //}

   
   bool graphics::poly_bezier_to(const ::point_f64 * ppoints, count nCount)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //ASSERT(get_handle1() != nullptr);
      //bool bResult = ::poly_bezier_to(get_handle1(), pPoints, (DWORD) nCount) != false;

      //if (get_handle1() != get_handle2())
      //{
      //   ::point_i32 point;
      //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
      //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
      //}
      //return bResult;
      __throw(error_not_implemented);

      return false;

   }

   
   bool graphics::SelectClipPath(i32 nMode)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //ASSERT(get_handle1() != nullptr);

      //// output DC always holds the current path
      //if (!::SelectClipPath(get_handle1(), nMode))
      //   return false;

      //// transfer clipping region into the attribute DC
      bool bResult = true;
      //if (get_handle1() != get_handle2())
      //{
      //   HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
      //   if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
      //   {
      //      __trace(trace_category_appmsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
      //      bResult = false;
      //   }
      //   ::DeleteObject(hRgn);
      //}
      return bResult;
   }


   //i32 graphics::SelectClipRgn(::draw2d::region* pregion, ::draw2d::enum_combine ecombine)
   //{

   //   if(pregion == nullptr)
   //   {

   //      m_pgraphics->ResetClip();

   //   }
   //   else
   //   {

   //      if(ecombine == ::draw2d::e_combine_intersect)
   //      {

   //         m_pgraphics->SetClip(pregion->get_os_data<Region *>(this), Gdiplus::CombineModeIntersect);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_add)
   //      {

   //         m_pgraphics->SetClip(pregion-> get_os_data<Region * >(this),Gdiplus::CombineModeUnion);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_xor)
   //      {

   //         m_pgraphics->SetClip(pregion->get_os_data<Region * >(this),Gdiplus::CombineModeXor);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_copy)
   //      {

   //         m_pgraphics->SetClip(pregion->get_os_data<Region * >(this),Gdiplus::CombineModeReplace);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_exclude)
   //      {

   //         m_pgraphics->SetClip(pregion->get_os_data<Region * >(this),Gdiplus::CombineModeExclude);

   //      }

   //   }

   //   return 0;

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback

   i32 CALLBACK __enum_meta_file_procedure(HDC hDC,
                                           HANDLETABLE* pHandleTable, METARECORD* pMetaRec, i32 nHandles, LPARAM lParam)
   {
      graphics * pgraphics = (graphics *)lParam;

      ASSERT_VALID(pgraphics);

      return pgraphics->meta_file_procedure(hDC, pHandleTable, pMetaRec, nHandles);

   }


   i32 graphics::meta_file_procedure(HDC hDC, HANDLETABLE* pHandleTable, METARECORD* pMetaRec, i32 nHandles)
   {

//      switch (pMetaRec->rdFunction)
//      {
//      // these records have effects different for each graphics derived class
//      case META_SETMAPMODE:
//         SetMapMode((i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETWINDOWEXT:
//         set_window_ext(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETWINDOWORG:
//         SetWindowOrg(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETVIEWPORTEXT:
//         SetViewportExt(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETVIEWPORTORG:
//         SetViewportOrg(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SCALEWINDOWEXT:
//         scale_window_ext(
//         (i32)(i16)pMetaRec->rdParm[3], (i32)(i16)pMetaRec->rdParm[2],
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SCALEVIEWPORTEXT:
//         ScaleViewportExt(
//         (i32)(i16)pMetaRec->rdParm[3], (i32)(i16)pMetaRec->rdParm[2],
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_OFFSETVIEWPORTORG:
//         OffsetViewportOrg(
//         (i32)(i16)pMetaRec->rdParm[1], (i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SAVEDC:
//         SaveDC();
//         break;
//      case META_RESTOREDC:
//         RestoreDC((i32)(i16)pMetaRec->rdParm[0]);
//         break;
//      case META_SETBKCOLOR:
//      {
//         ::draw2d::brush_pointer brush(e_create);
//         brush->create_solid(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
//         set(brush);
//      }
//      break;
//      case META_SETTEXTCOLOR:
//      {
//         ::draw2d::brush_pointer brush(e_create);
//
//         brush->create_solid(*(UNALIGNED COLORREF*)&pMetaRec->rdParm[0]);
//         set(brush);
//      }
//      break;
//
//      // need to watch out for set(HFONT), for custom font mapping
//      case META_SELECTOBJECT:
//      {
//         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
//         UINT nObjType = GetObjectType(hObject);
//         if (nObjType == 0)
//         {
//            // object type is unknown, determine if it is a font
//            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
//            HFONT hFontOld = (HFONT)::set(get_handle1(), hStockFont);
//            HGDIOBJ hObjOld = ::set(get_handle1(), hObject);
//            if (hObjOld == hStockFont)
//            {
//               // got the stock object back, so must be selecting a font
//               __throw(error_not_implemented);
////                  set(::draw2d_gdiplus::font::from_handle(pgraphics->get_application(), (HFONT)hObject));
//               break;  // don't play the default record
//            }
//            else
//            {
//               // didn't get the stock object back, so restore everything
//               ::set(get_handle1(), hFontOld);
//               ::set(get_handle1(), hObjOld);
//            }
//            // and fall through to PlayMetaFileRecord...
//         }
//         else if (nObjType == OBJ_FONT)
//         {
//            // play back as graphics::set(::write_text::font*)
////               set(::draw2d_gdiplus::font::from_handle(pgraphics->get_application(), (HFONT)hObject));
//            __throw(error_not_implemented);
//            break;  // don't play the default record
//         }
//      }
//      // fall through...
//
//      default:
//         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
//         break;
//      }

      return 1;

   }


   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //if (::GetDeviceCaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
      //{
      //   // playing metafile in metafile, just use aura windows API
      //   return ::PlayMetaFile(get_handle1(), hMF) != false;
      //}

      //// for special playback, lParam == pgraphics
      //return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != false;

      return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(::size_f64 * psize)

   {
      ASSERT(__is_valid_address(psize, sizeof(const size_f64 &)));


      size_f64 sizeWinExt = GetWindowExt();
      size_f64 sizeVpExt = GetViewportExt();
      psize->cx = psize->cx * abs(sizeVpExt.cx) / abs(sizeWinExt.cx);

      psize->cy = psize->cy * abs(sizeVpExt.cy) / abs(sizeWinExt.cy);

   }


   void graphics::DPtoLP(::size_f64 * psize)
   {

      ASSERT(__is_valid_address(psize, sizeof(const size_f64 &)));

      size_f64 sizeWinExt = GetWindowExt();

      size_f64 sizeVpExt = GetViewportExt();

      psize->cx = psize->cx * abs(sizeWinExt.cx) / abs(sizeVpExt.cx);

      psize->cy = psize->cy * abs(sizeWinExt.cy) / abs(sizeVpExt.cy);

   }


   bool graphics::_001DrawText(const string & str, rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, bool bMeasure)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      synchronous_lock synchronouslock(mutex());

      if (m_pfont.is_null())
      {

         return false;

      }

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Status status = Gdiplus::Status::GenericError;

      if (m_pfont.is_set() && m_ewritetextrendering != m_pfont->m_ewritetextrendering)
      {

         set_text_rendering_hint(m_pfont->m_ewritetextrendering);

      }

      return gdiplus_draw_text(this, nullptr, str, rectParam, ealign, edrawtext, m_pfont, m_pfont->m_dFontWidth, m_pbrush, bMeasure);

   }


   //bool graphics::draw_text_ex(const char * pszString,strsize nCount,const rectangle_i32 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   if (::is_null(m_pgraphics))
   //   {

   //      return false;

   //   }

   //   //if(get_handle1() == nullptr)
   //   //   return -1;

   //   // these flags would modify the string
   //   //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
   //   //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
   //   //wstring text.m_wstr = ::str::international::utf8_to_unicode(string(pszString, nCount));

   //   //return ::DrawTextExW(get_handle1(),const_cast<wchar_t *>((const wchar_t *)text.m_wstr),(i32)wcslen(text.m_wstr),(RECT *) &rectParam,nFormat,pDTParams);

   //   __throw(error_not_implemented);

   //   return false;

   //}


   bool graphics::draw_text_ex(const string & str,const rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      //ASSERT(get_handle1() != nullptr);
      //// these flags would modify the string
      //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      //wstring text.m_wstr = ::str::international::utf8_to_unicode(str);
      //return ::DrawTextExW(get_handle1(),const_cast<wchar_t *>((const wchar_t *)text.m_wstr),(i32)wcslen(text.m_wstr),(RECT *) &rectParam,nFormat,pDTParams);
      __throw(error_not_implemented);

      return false;
   }


   //bool graphics::draw_text_ex(const char * pszString,strsize nCount,const ::rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   if (::is_null(m_pgraphics))
   //   {

   //      return false;

   //   }

   //   return ::draw2d::graphics::draw_text_ex(pszString,nCount,rectParam,nFormat,lpDTParams);

   //}


   //bool graphics::draw_text_ex(const string& str, const ::rectangle_f64 &rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   //{

   //   if (::is_null(m_pgraphics))
   //   {

   //      return false;

   //   }

   //   return ::draw2d::graphics::draw_text_ex(str,rectParam,ealign, edrawtext);

   //}


   //::count graphics::GetEachCharTextExtent(array < ::size_f64 > & sizea, const string & str)
   //{
   //   sizea.erase_all();
   //   strsize_array iaLen;
   //   strsize iRange = 0;
   //   strsize i = 0;
   //   strsize iLen;
   //   const char * pszStart = str;
   //   const char * psz = pszStart;
   //   while (*psz)
   //   {
   //      const char * pszNext = ::str::utf8_inc(psz);
   //      if (pszNext == nullptr)
   //         break;
   //      iLen = pszNext - psz;
   //      iRange++;
   //      i += iLen;
   //      iaLen.add(i);
   //      if (*pszNext == '\0')
   //         break;
   //      psz = pszNext;
   //   }
   //

   //   for (int iLen : iaLen)
   //   {

   //      sizea.add(get_text_extent(str, iLen));

   //   }



   //   return sizea.get_size();

   //}

   // return Extents per UTF8 Char Boundaries, so there can be lesser
   // "extents" than bytes
   ::count graphics::get_character_extent(double_array & daLeft, double_array& daRight, const string & str, strsize iStartParam, strsize iCountParam)
   {

      if (str.is_empty())
      {

         return 0;

      }

      if (iCountParam < 0)
      {

         iCountParam += str.get_length() - iStartParam + 1;

      }
      
      daLeft.erase_all();

      daRight.erase_all();

      wstring wstrBefore(str.Left(iStartParam));

      wstring wstrMiddle(str.Mid(iStartParam, iCountParam));

      m_pfont->defer_update(this, 0);

      auto & text = m_pfont->m_mapText[str];

      if (text.m_wstr.is_empty())
      {

         text.m_wstr = str;

      }

      ::count cLength = text.m_wstr.get_length();

      ::count cBeg = wstrBefore.get_length();

      ::index cEnd = cBeg + wstrMiddle.get_length();

      int iCount = 0;

      int iStart = (i32_cast) cBeg;

      int cMaxMeasureCharacterRanges = 32;

      ap(Gdiplus::CharacterRange) charRanges(new_array, 32);

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
         | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
         | Gdiplus::StringFormatFlagsNoClip
         | Gdiplus::StringFormatFlagsNoWrap
         | Gdiplus::StringFormatFlagsNoFitBlackBox
      );

      bool bFirst = true;

      while(true)
      {

         iStart += iCount;

         if (iStart >= cEnd)
         {

            break;

         }

         iCount = minimum((int) cMaxMeasureCharacterRanges, (int) (cEnd - iStart));


         for (index j = 0; j < iCount; j++)
         {

            charRanges[j].First = (int) (iStart + j);

            charRanges[j].Length = 1;

         }

         Gdiplus::Status status = strFormat.SetMeasurableCharacterRanges(iCount, charRanges);

         i32 count = strFormat.GetMeasurableCharacterRangeCount();

#undef new

         ap(Gdiplus::Region) regiona(new_array, new Gdiplus::Region[count]);

#define new ACME_NEW

         Gdiplus::RectF box(0.0f, 0.0f, 0.0f, 0.0f);

         Gdiplus::PointF origin(0.f, 0.f);

         m_pgraphics->MeasureCharacterRanges(text.m_wstr, (INT) cLength, m_pfont->get_os_data < Gdiplus::Font * >(this), box, &strFormat, count, regiona);

         Gdiplus::RectF rectBound;

         for (int i = 0; i < count; i++)
         {

            regiona[i].GetBounds(&rectBound, m_pgraphics);

            wchar_t wch = text.m_wstr.c_str()[i + iStart];

            int iUtf8Length = ::str::ch::ansichar_uni_len(wch);

            for (index iAnsiChar = 0; iAnsiChar < iUtf8Length; iAnsiChar++)
            {

               daLeft.add(rectBound.GetLeft());

               daRight.add(rectBound.GetRight());

            }

         }

      }

      return daLeft.get_size();

   }



   size_f64 graphics::get_text_extent(const char * pszString, strsize nCount, strsize iIndex)
   {

       if (::is_null(m_pgraphics))
       {

           __throw(::exception::exception("invalid state"));

       }

      if(pszString == nullptr || *pszString == '\0')

         return size_f64(0, 0);



      if(nCount < 0)
         nCount = strlen(pszString);


      if(iIndex > nCount)
         return size_f64(0, 0);

      if(iIndex < 0)
         return size_f64(0, 0);

      string str(pszString, nCount);

      wstring wstr(str);

      wstring wstrRange = ::str::international::utf8_to_unicode(pszString, iIndex);

      Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(0, (INT)wstrRange.get_length()) };

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetMeasurableCharacterRanges(1, charRanges);

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                              );

      i32 count = strFormat.GetMeasurableCharacterRangeCount();

      Gdiplus::PointF origin(0, 0);

      if (count <= 0)
      {

         Gdiplus::RectF box(0.0f, 0.0f, 0.0f, 0.0f);

         wstring wstrRange = ::str::international::utf8_to_unicode(pszString, iIndex);

         m_pgraphics->MeasureString(wstrRange, (i32)wstrRange.get_length(), m_pfont->get_os_data < Gdiplus::Font * >(this), origin, Gdiplus::StringFormat::GenericTypographic(), &box);

         return ::size_f64((LONG)(box.Width  * m_pfont->m_dFontWidth), (LONG)(box.Height));

      }

      Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);

#undef new

      Gdiplus::Region * pCharRangeRegions = new Gdiplus::Region[count];

#define new ACME_NEW

      m_pgraphics->MeasureCharacterRanges(wstr, (INT) wstr.get_length(), m_pfont->get_os_data < Gdiplus::Font * >(this), box, &strFormat, (INT) count, pCharRangeRegions);

      for(index i = 1; i < count; i++)
      {

         pCharRangeRegions[0].Union(&pCharRangeRegions[i]);

      }

      Gdiplus::RectF rectBound;

      pCharRangeRegions[0].GetBounds(&rectBound, m_pgraphics);

      delete[] pCharRangeRegions;

      Gdiplus::SizeF size;

      rectBound.GetSize(&size);

      return class ::size_f64((double)(size.Width  * m_pfont->m_dFontWidth), (double)(size.Height));

   }

   size_f64 graphics::GetTextBegin(const char * pszString, strsize nCount, strsize iIndex)

   {

      if (pszString == nullptr || *pszString == '\0')

         return ::size_f64(0, 0);

      if (nCount < 0)
         nCount = strlen(pszString);


      if (iIndex > nCount)
         return ::size_f64(0, 0);

      if (iIndex < 0)
         return ::size_f64(0, 0);

      wstring wstr = ::str::international::utf8_to_unicode(pszString, nCount);

      wstring wstrRange = ::str::international::utf8_to_unicode(pszString, iIndex);

      Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(INT(wstrRange.get_length()), INT(wstr.get_length() - wstrRange.get_length())) };

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetMeasurableCharacterRanges(1, charRanges);

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                              );

      i32 count = strFormat.GetMeasurableCharacterRangeCount();

      Gdiplus::PointF origin(0, 0);

      if (count <= 0)
      {

         Gdiplus::RectF box(0.0f, 0.0f, 0.0f, 0.0f);

         wstrRange = ::str::international::utf8_to_unicode(pszString, iIndex);

         m_pgraphics->MeasureString(wstrRange, (i32)wstrRange.get_length(), m_pfont->get_os_data < Gdiplus::Font *  >(this), origin, Gdiplus::StringFormat::GenericTypographic(), &box);

         return ::size_f64((LONG)(box.Width  * m_pfont->m_dFontWidth), (LONG) (box.Height));

      }

      Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);

#undef new

      Gdiplus::Region * pCharRangeRegions = new Gdiplus::Region[count];

#define new ACME_NEW

      m_pgraphics->MeasureCharacterRanges(wstr, (INT)wstr.get_length(), m_pfont->get_os_data < Gdiplus::Font * >(this), box, &strFormat, (INT)count, pCharRangeRegions);

      for (index i = 1; i < count; i++)
      {

         pCharRangeRegions[0].Union(&pCharRangeRegions[i]);

      }

      Gdiplus::RectF rectBound;

      pCharRangeRegions[0].GetBounds(&rectBound, m_pgraphics);

      delete[] pCharRangeRegions;

      return class ::size_f64((double)(rectBound.X  * m_pfont->m_dFontWidth), (double)(rectBound.Height));

   }

   size_f64 graphics::get_text_extent(const string & str)
   {

      if (!m_pfont || str.is_empty())
      {

         return ::size_f64(0, 0);

      }

      m_pfont->defer_update(this, 0);

      auto& text = m_pfont->m_mapText[str];

      if (text.m_bSize)
      {

         return text.m_size;

      }

      if (text.m_wstr.is_empty())
      {

         text.m_wstr = str;

      }
      

      Gdiplus::RectF box;

      Gdiplus::PointF origin(0, 0);

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                              );

      auto pfont = m_pfont->get_os_data < Gdiplus::Font * >(this);

      if (::is_null(pfont))
      {

         return size_f64(0.0, 0.0);

      }

      m_pgraphics->MeasureString(text.m_wstr, (i32) text.m_wstr.get_length(), pfont, origin, &strFormat,  &box);

      text.m_size = size_f64((double)(box.Width * m_pfont->m_dFontWidth), (double)(box.Height));

      text.m_bSize = true;

      return text.m_size;

      /*if(get_handle2() == nullptr)
         return ::size_f64(0, 0);
      ::size_f64 ::size_f64;
      string str(pszString, nCount);

      wstring text.m_wstr = ::str::international::utf8_to_unicode(str);
      if(!::GetTextExtentPoint32W(get_handle2(), text.m_wstr, (i32)text.m_wstr.get_length(), &::size_f64))
      {
         return const ::size_f64 & size(0, 0);
      }
      return ::size_f64;*/
   }

   //size_f64 graphics::get_text_extent(const string & str)
   //{
   //   /*      if(get_handle2() == nullptr)
   //            return ::size_f64(0, 0);
   //         ::size_f64 ::size_f64;
   //         wstring text.m_wstr = ::str::international::utf8_to_unicode(str);
   //         if(!::GetTextExtentPoint32W(get_handle2(), text.m_wstr, (i32)text.m_wstr.get_length(), &::size_f64))
   //         {
   //            return const ::size_f64 & size(0, 0);
   //         }
   //         return ::size_f64;*/

   //   //class size_f64 ::size_f64;

   //   //if(!get_text_extent(::size_f64, str, (i32) str.get_length(), (i32) str.get_length()))
   //   //   return const ::size_f64 & size(0, 0);

   //   return get_text_extent(str);

   //   //return const ::size_f64 & size(0, 0);

   //   //return const ::size_f64 & size((long) size.cx, (long) size.cy);

   //   /*if(m_pgraphics == nullptr)
   //      return ::size_f64(0, 0);

   //   wstring text.m_wstr = ::str::international::utf8_to_unicode(str);

   //   Gdiplus::RectF box;

   //   Gdiplus::PointF origin(0, 0);


   //   if(m_pgraphics == nullptr)
   //      return ::size_f64(0, 0);

   //   try
   //   {
   //      m_pgraphics->MeasureString(text.m_wstr, (i32) text.m_wstr.get_length(), m_pfont->get_os_data < Font * >(this), origin, &box);
   //   }
   //   catch(...)
   //   {
   //      return ::size_f64(0, 0);
   //   }

   //   return ::size_f64((i64) (box.Width * m_fontxyz.m_dFontWidth), (i64) box.Height);*/

   //}


   ::size_f64 graphics::GetOutputTextExtent(const char * pszString, strsize nCount)
   {

      //ASSERT(get_handle1() != nullptr);
      //::size_f64 ::size_f64;
      //string str(pszString, nCount);

      //wstring text.m_wstr = ::str::international::utf8_to_unicode(str);
      //VERIFY(::GetTextExtentPoint32W(get_handle1(), text.m_wstr, (i32)text.m_wstr.get_length(), &::size_f64));
      //return ::size_f64;

      return nullptr;
      
   //}


   }


   ::size_f64 graphics::GetOutputTextExtent(const string & str)
   {

      //ASSERT(get_handle1() != nullptr);

      //::size_f64 ::size_f64;

      //wstring text.m_wstr = ::str::international::utf8_to_unicode(str);

      //VERIFY(::GetTextExtentPoint32W(get_handle1(), text.m_wstr, (i32)text.m_wstr.get_length(), &::size_f64));

      //return ::size_f64;

      return nullptr;

   }


   bool graphics::get_text_extent(::size_f64 & size, const char * pszString, strsize nCount, strsize iIndex)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      if (m_pfont.is_null())
         return false;

      if(pszString == nullptr || *pszString == '\0')

         return false;

      if(nCount < 0)
         nCount = strlen(pszString);


      if(iIndex > nCount)
         return false;

      if(iIndex < 0)
         return false;

      m_pfont->defer_update(this, 0);

      wstring wstr = ::str::international::utf8_to_unicode(pszString, nCount);

      strsize iRange = 0;
      strsize i = 0;
      strsize iLen;
      const char * psz = pszString;

      while(i < iIndex)
      {
         try
         {
            iLen = ::str::get_utf8_char_length(psz);
         }
         catch(...)
         {
            break;
         }
         if (iLen < 0)
            break;
         iRange++;
         i += iLen;
         if(i >= iIndex)
            break;
         try
         {
            psz += iLen;
         }
         catch(...)
         {
            break;
         }
         if(psz == nullptr)
            break;
         if(*psz == '\0')
            break;
      }

      Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(0, (INT) iRange) };

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());
      //Gdiplus::StringFormat strFormat;

      strFormat.SetMeasurableCharacterRanges(1, charRanges);

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                              );

      i32 count = strFormat.GetMeasurableCharacterRangeCount();

#undef new

      Gdiplus::Region * pCharRangeRegions = new Gdiplus::Region[count];

#define new ACME_NEW

      //Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);

      Gdiplus::PointF origin(0, 0);

      // Generate a on_layout rectangle_i32 for the text

      Gdiplus::RectF layoutRect(0, 0, 10000, 10000);
      
      Gdiplus::Status status = m_pgraphics->MeasureString(wstr, (INT) nCount, m_pfont->get_os_data < Gdiplus::Font * >(this), origin, &layoutRect );

      // Prevent clipping

      //StringFormat strFormat( StringFormat::GenericTypographic() );
      //status = ((graphics *)this)->m_pgraphics->SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsNoClip );

      //m_pgraphics->MeasureString(text.m_wstr, (i32) text.m_wstr.get_length(), m_pfont->get_os_data < Font * >(this), origin, Gdiplus::StringFormat::GenericTypographic(), &box);

      m_pgraphics->MeasureCharacterRanges(wstr, (INT) nCount, m_pfont->get_os_data < Gdiplus::Font * >(this), layoutRect, &strFormat, (INT) count, pCharRangeRegions);

      Gdiplus::Region * pregion = nullptr;


      if(count > 0)
      {

         pregion = pCharRangeRegions[0].Clone();

      }

      for(i = 1; i < count; i++)
      {
         pregion->Union(&pCharRangeRegions[i]);
      }

      delete [] pCharRangeRegions;

      if(pregion == nullptr)
         return false;

      Gdiplus::RectF rectBound;

      pregion->GetBounds(&rectBound, m_pgraphics);

      delete pregion;

      Gdiplus::SizeF size_f32;

      rectBound.GetSize(&size_f32);

      size.cx = size_f32.Width * m_pfont->m_dFontWidth;

      size.cy = size_f32.Height;

      return true;
   }

   
   bool graphics::get_text_extent(::size_f64 & size, const char * pszString, strsize nCount)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      wstring wstr = ::str::international::utf8_to_unicode(pszString, nCount);


      Gdiplus::RectF box;

      Gdiplus::PointF origin(0, 0);

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                              );
      bool bOk = true;

      try
      {

         if (m_pgraphics->MeasureString(wstr, (i32)wstr.get_length(), m_pfont->get_os_data < Gdiplus::Font * >(this), origin, &strFormat, &box) != Gdiplus::Status::Ok)
         {

            bOk = false;

         }

      }
      catch(...)
      {
         bOk = false;
      }

      if(!bOk)
         return false;

      size.cx = box.Width * m_pfont->m_dFontWidth;

      size.cy = box.Height;

      return true;

   }


   bool graphics::get_text_extent(::size_f64 & size, const string & str)
   {

      if (::is_null(m_pgraphics) && is_null(m_pfont))
      {

         return false;

      }

      wstring wstr = ::str::international::utf8_to_unicode(str);

      Gdiplus::RectF box;

      Gdiplus::PointF origin(0, 0);

      m_pfont->defer_update(this, 0);

      bool bOk = true;

      try
      {

         if (m_pgraphics->MeasureString(wstr, (i32)wstr.get_length(), m_pfont->get_os_data < Gdiplus::Font * >(this), origin, &box) != Gdiplus::Status::Ok)
         {

            bOk = false;

         }

      }
      catch(...)
      {

         bOk = false;

      }

      if (!bOk)
      {

         return false;

      }

      size.cx = box.Width * m_pfont->m_dFontWidth;

      size.cy = box.Height;

      return true;

   }


   //bool graphics::fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
   //{

   //   try
   //   {

   //      if(m_pgraphics == nullptr)
   //         return;

   //      auto emodeOld = m_pgraphics->GetSmoothingMode();

   //      //if(emodeOld != Gdiplus::SmoothingModeNone)
   //      //{

   //      //   m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);

   //      //}

   //      Gdiplus::SolidBrush b(Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB));

   //      m_pgraphics->FillRectangle(&b, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   //      //if (emodeOld != Gdiplus::SmoothingModeNone)
   //      //{

   //      //   m_pgraphics->SetSmoothingMode(emodeOld);

   //      //}

   //   }
   //   catch(...)
   //   {

   //   }

   //}


   bool graphics::TextOutRaw(double x, double y, const block & block)
   {

      if (block.is_empty())
      {

         return false;

      }

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      if (!m_pfont)
      {

         return false;

      }

      Gdiplus::Font * pfont = m_pfont->get_os_data < Gdiplus::Font * > (this);

      auto & text = m_pfont->m_mapText[block];

      if (text.m_wstr.is_empty())
      {

         text.m_wstr = block;

      }

      if (m_pgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Brush* pbrush = nullptr;
      
      if (::is_null(m_ppath))
      {

         if (::is_null(m_pbrush))
         {

            return false;

         }

         pbrush = m_pbrush->get_os_data <  Gdiplus::Brush * >(this);

         if (pbrush == nullptr)
         {

            return false;

         }

      }

      ::draw2d::savedc k(this);

      set_alpha_mode(::draw2d::alpha_mode_blend);

      //if (m_ewritetextrendering != m_pfont->m_ewritetextrendering)
      {

         set_text_rendering_hint(m_pfont->m_ewritetextrendering);

      }

      Gdiplus::Status status;

      Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());

      format.SetFormatFlags(format.GetFormatFlags()
                            | Gdiplus::StringFormatFlagsNoClip
                           );

      format.SetLineAlignment(Gdiplus::StringAlignmentNear);

      if (m_pfont->m_dFontWidth == 1.0)
      {

         ::Gdiplus::PointF origin((Gdiplus::REAL)x, (Gdiplus::REAL)y);

         if (m_ppath != nullptr)
         {

            FLOAT fDpiX = m_pgraphics->GetDpiX();

            Gdiplus::GraphicsPath path;

            Gdiplus::FontFamily fontfamily;

            pfont->GetFamily(&fontfamily);

            double d1 = pfont->GetSize() * m_pgraphics->GetDpiX() / 72.0;

            double d2 = fontfamily.GetEmHeight(pfont->GetStyle());

            double d3 = d1 * d2;

            status = path.AddString(text.m_wstr, (INT)text.m_wstr.get_length(), &fontfamily, pfont->GetStyle(), (Gdiplus::REAL) d1, origin, &format);

            m_ppath->AddPath(&path, false);

         }
         else
         {

            auto e = m_pgraphics->GetTextRenderingHint();

            status = m_pgraphics->DrawString(text.m_wstr, (INT)text.m_wstr.get_length(), pfont, origin, &format, pbrush);

         }

      }
      else
      {

         g_keep k(m_pgraphics);

         ::Gdiplus::PointF origin(0, 0);

         FLOAT fDpiX = m_pgraphics->GetDpiX();

         Gdiplus::Matrix m;

         m_pgraphics->GetTransform(&m);

         ap(Gdiplus::Matrix) pmNew;

         if (m_ppath != nullptr)
         {

#undef new

            pmNew = new Gdiplus::Matrix();

#define new ACME_NEW

         }
         else
         {

            pmNew = m.Clone();

         }

         pmNew->Translate((Gdiplus::REAL)  (x / m_pfont->m_dFontWidth), (Gdiplus::REAL) y);

         pmNew->Scale((Gdiplus::REAL) m_pfont->m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);

         if (m_ppath != nullptr)
         {

            Gdiplus::GraphicsPath path;

            Gdiplus::FontFamily fontfamily;

            pfont->GetFamily(&fontfamily);

            double d1 = pfont->GetSize() * m_pgraphics->GetDpiX() / 72.0;

            double d2 = fontfamily.GetEmHeight(pfont->GetStyle());

            double d3 = d1 * d2;

            status = path.AddString(text.m_wstr, (INT)text.m_wstr.get_length(), &fontfamily, pfont->GetStyle(), (Gdiplus::REAL) d1, origin, &format);

            path.Transform(pmNew);

            m_ppath->AddPath(&path, false);

         }
         else
         {

            m_pgraphics->SetTransform(pmNew);

            status = m_pgraphics->DrawString(text.m_wstr, (INT)text.m_wstr.get_length(), pfont, origin, &format, pbrush);

            m_pgraphics->SetTransform(&m);

         }
      }

      return status  == Gdiplus::Status::Ok;

   }


   bool graphics::line_to(double x, double y)
   {

      if (::is_null(m_pgraphics))
      {

         return false;

      }

      synchronous_lock synchronouslock(mutex());

      if(m_ppen.cast < ::draw2d_gdiplus::pen >()->m_egdiplusalign != Gdiplus::PenAlignment::PenAlignmentCenter)
      {

         m_ppen->get_os_data < Gdiplus::Pen * >(this)->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

         m_ppen.cast < ::draw2d_gdiplus::pen >()->m_egdiplusalign = Gdiplus::PenAlignment::PenAlignmentCenter;

      }

      m_pgraphics->DrawLine(m_ppen->get_os_data < Gdiplus::Pen * >(this), Gdiplus::PointF((Gdiplus::REAL) m_point.x, (Gdiplus::REAL)  m_point.y), Gdiplus::PointF((Gdiplus::REAL) x, (Gdiplus::REAL) y));


      m_point.x = x;
      m_point.y = y;


      return true;

   }

   //bool graphics::line_to(double x, double y)

   //{

   //   synchronous_lock synchronouslock(mutex());

   //   if(m_ppen.cast < ::draw2d_gdiplus::pen >()->m_egdiplusalign != Gdiplus::PenAlignment::PenAlignmentCenter)
   //   {

   //      //m_ppen->get_os_data < Pen * >(this)->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

   //      m_ppen->m_epenalign = ::draw2d::e_pen_align_center;

   //      m_ppen->set_modified();

   //      //m_ppen.cast < ::draw2d_gdiplus::pen >()-

   //   }

   //   auto ppen = m_ppen->get_os_data < Pen* >(this);

   //   if (fmod(m_point.x, 1.0) != 0.0 || fmod(m_point.y, 1.0) != 0)
   //   {

   //      m_pgraphics->DrawLine(ppen, Gdiplus::PointF((Gdiplus::REAL)m_point.x, (Gdiplus::REAL)m_point.y), Gdiplus::PointF((Gdiplus::REAL)point.x, (Gdiplus::REAL) point.y));


   //   }
   //   else
   //   {

   //      m_pgraphics->DrawLine(ppen, Gdiplus::Point((INT)m_point.x, (INT)m_point.y), Gdiplus::Point((INT)point.x, (INT)point.y));


   //   }

   //   m_point.x = point.x;

   //   m_point.y = point.y;

   //   return true;

   //}


   bool graphics::draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppenParam)
   {

      if (::is_null(ppenParam))
      {

         return false;

      }

      synchronous_lock synchronouslock(mutex());

      auto ppen = ppenParam->get_os_data < Gdiplus::Pen * >(this);

//      ppen->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

      m_pgraphics->DrawLine(ppen, Gdiplus::PointF((Gdiplus::REAL) x1, (Gdiplus::REAL) y1), Gdiplus::PointF((Gdiplus::REAL) x2, (Gdiplus::REAL) y2));

      m_point.x = x2;

      m_point.y = y2;

      return true;

   }


   //bool graphics::draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppenParam)
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   auto ppen = (Gdiplus::Pen *) ppenParam->get_os_data(this);

   //   if (!ppen)
   //   {

   //      return false;

   //   }

   //   ppen->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

   //   m_pgraphics->DrawLine(ppen, Gdiplus::Point(point1.x, point1.y), Gdiplus::Point(point2.x, point2.y));

   //   m_point.x = point2.x;

   //   m_point.y = point2.y;

   //   return true;

   //}


   bool graphics::set_smooth_mode(::draw2d::e_smooth_mode esmoothmode)
   {

      try
      {

         if (m_pgraphics == nullptr)
         {

            return false;

         }

         if(esmoothmode == ::draw2d::smooth_mode_none)
         {

            m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);

         }
         else if(esmoothmode == ::draw2d::smooth_mode_high)
         {

            m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

         }
         else if (esmoothmode == ::draw2d::smooth_mode_anti_alias_8x4)
         {

            m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x4);

         }
         else if (esmoothmode == ::draw2d::smooth_mode_anti_alias_8x8)
         {

            m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);

         }

         ::draw2d::graphics::set_smooth_mode(esmoothmode);

         return true;

      }
      catch(...)
      {

      }

      return false;

   }


   //bool graphics::set_interpolation_mode(::draw2d::e_interpolation_mode einterpolationmode)
   //{

   //   try
   //   {

   //      if (m_pgraphics == nullptr)
   //      {

   //         return false;

   //      }

   //      if (einterpolationmode == ::draw2d::interpolation_mode_none)
   //      {

   //         m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeDefault);

   //      }
   //      else if (einterpolationmode == ::draw2d::interpolation_mode_low_quality)
   //      {

   //         m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);

   //      }
   //      else if (einterpolationmode == ::draw2d::interpolation_mode_high_quality)
   //      {

   //         m_pgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

   //      }

   //      ::draw2d::graphics::set_interpolation_mode(einterpolationmode);

   //      return true;

   //   }
   //   catch (...)
   //   {

   //   }

   //   return false;

   //}



   bool graphics::set_compositing_quality(::draw2d::e_compositing_quality ecompositingquality)
   {

      try
      {

         if (m_pgraphics == nullptr)
         {

            return false;

         }

         if (ecompositingquality == ::draw2d::compositing_quality_none)
         {

            m_pgraphics->SetCompositingQuality(Gdiplus::CompositingQualityDefault);

         }
         else if (ecompositingquality == ::draw2d::compositing_quality_high_speed)
         {

            m_pgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);

         }
         else if (ecompositingquality == ::draw2d::compositing_quality_high_quality)
         {

            m_pgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

         }

         ::draw2d::graphics::set_compositing_quality(ecompositingquality);

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   bool graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      try
      {

         if (m_pgraphics == nullptr)
         {

            return false;

         }

         if(ealphamode == ::draw2d::alpha_mode_blend)
         {

            m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         }
         else if(ealphamode == ::draw2d::alpha_mode_set)
         {

            m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

         }

         ::draw2d::graphics::set_alpha_mode(ealphamode);

         return true;

      }
      catch(...)
      {

      }

      return false;

   }


   bool graphics::set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint)
   {

      try
      {

         if (m_pgraphics == nullptr)
         {

            return false;

         }

         switch (etextrenderinghint)
         {
         case ::write_text::e_rendering_anti_alias:
            m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
            break;
         case ::write_text::e_rendering_anti_alias_grid_fit:
            m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
            break;
         case ::write_text::e_rendering_single_bit_per_pixel:
            m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel);
            break;
         case ::write_text::e_rendering_single_bit_per_pixel_grid_fit:
            m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
            break;
         case ::write_text::e_rendering_clear_type_grid_fit:
            m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
            break;
         case ::write_text::e_rendering_none:
            m_pgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
            break;
         }

         ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   //void * graphics::get_os_data() const
   //{

   //   return (void *) m_pgraphics;

   //}


   //void * graphics::get_os_data_ex(int i) const
   //{

   //   if(i == 1)
   //   {
   //      return m_pgraphics->GetHDC();
   //   }
   //   else
   //   {
   //      return ::draw2d::graphics::get_os_data_ex(i);
   //   }

   //}


   //void graphics::release_os_data_ex(int i,void * p)
   //{

   //   if(i == 1)
   //   {

   //      m_pgraphics->ReleaseHDC((HDC)p);

   //   }
   //   else
   //   {

   //      ::draw2d::graphics::release_os_data_ex(i, p);

   //   }

   //}


   HDC graphics::get_handle() const
   {

      return m_hdc;

   }


   //HDC graphics::get_handle1() const
   //{

   //   return get_handle();

   //}


   //HDC graphics::get_handle2() const
   //{

   //   return get_handle();

   //}


   bool graphics::attach(void * pdata)
   {

      close_graphics();

      m_pgraphics = (Gdiplus::Graphics *) pdata;

      m_osdata[0] = pdata;

      return false;

   }


   void * graphics::detach()
   {

      Gdiplus::Graphics * pgraphics = m_pgraphics;

      m_pgraphics = nullptr;

      m_hdc = nullptr;

      clear_os_data();

      return pgraphics;

   }


   /*Gdiplus::Font* graphics::m_pfont->get_os_data < Font >(this);
   {

      if(m_pfont.is_null())
      {

         m_pfont.create();

         if(m_pfont.is_set())
         {

            m_pfont->m_powner = this;

         }

      }

      if(m_pfont.is_null())
      {

         return nullptr;

      }

      return m_pfont->get_os_data< Font * >(this);

   }


   Gdiplus::Brush * graphics::m_pbrush->get_os_data < Brush * >(this)
   {

      if(m_pbrush.is_null())
      {

         m_pbrush.create();

         if(m_pbrush.is_set())
         {

            m_pbrush->m_powner = this;

         }

      }

      if(m_pbrush.is_null())
      {

         return nullptr;

      }

      return m_pbrush->get_os_data < Brush * >(this);

   }


   Gdiplus::Pen * graphics::m_ppen->get_os_data < Pen * >(this)
   {

      synchronous_lock synchronouslock(mutex());

      if(m_ppen.is_null())
      {

         m_ppen.create();

         if(m_ppen.is_set())
         {

            m_ppen->m_powner = this;

         }

      }

      if(m_ppen.is_null())
      {

         return nullptr;

      }

      return m_ppen->get_os_data < Pen * >(this);

   }*/


   Gdiplus::FillMode graphics::gdiplus_get_fill_mode()
   {

      return Gdiplus::FillModeWinding;

   }


   bool graphics::blur(bool bExpand,double dRadius,const rectangle_f64 & rectParam)
   {

      // Commented Out for Running in cosan machine running Windows 2008

      //if(m_pbitmap.is_null() || m_pbitmap->get_os_data() == nullptr)
      //   return false;

      //Gdiplus::BlurParams myBlurParams;

      //myBlurParams.expandEdge    = bExpand ? 1 : 0;
      //myBlurParams.radius        = (float) dRadius;

      //Gdiplus::Blur myBlur;
      //myBlur.SetParameters(&myBlurParams);

      //

      //Gdiplus::Matrix m;
      //m_pgraphics->GetTransform(&m);

      //Gdiplus::PointF points[2];

      //points[0].X    = (Gdiplus::REAL) rectParam.left;
      //points[0].Y    = (Gdiplus::REAL) rectParam.top;
      //points[1].X    = (Gdiplus::REAL) rectParam.right;
      //points[1].Y    = (Gdiplus::REAL) rectParam.bottom;

      //m.TransformPoints(points, 2);

      ////Gdiplus::RectF rectangle_f32(points[0].X, points[0].Y, points[1].X - points[0].X, points[1].Y - points[0].Y);

      //::rectangle_i32 rectangle;

      //rectangle.left      = (LONG) points[0].X;
      //rectangle.top       = (LONG) points[0].Y;
      //rectangle.right     = (LONG) points[1].X;
      //rectangle.bottom    = (LONG) points[1].Y;

      //Gdiplus::Bitmap * pbitmap = ((Gdiplus::Bitmap *) m_pbitmap->get_os_data());

      //pbitmap->ApplyEffect(&myBlur, &rectangle);

      return true;

   }


   double graphics::get_dpix()
   {

      if (m_pgraphics == nullptr)
         return 96.0;

      return m_pgraphics->GetDpiX();

   }


   double graphics::get_dpiy()
   {

      if (m_pgraphics == nullptr)
         return 96.0;

      return m_pgraphics->GetDpiY();

   }


   bool graphics::flush()
   {

      synchronous_lock synchronouslock(mutex());

      m_pgraphics->Flush();

      return true;

   }


   bool graphics::sync_flush()
   {

      synchronous_lock synchronouslock(mutex());

      m_pgraphics->Flush(Gdiplus::FlushIntentionSync);

      return true;

   }

   HDC graphics::get_hdc()
   {

      if(m_hdc != nullptr)
         return m_hdc;

      if(m_pgraphics == nullptr)
         return nullptr;

      return m_pgraphics->GetHDC();

   }

   void graphics::release_hdc(HDC hdc)
   {

      if(m_hdc != nullptr)
         return;

      m_pgraphics->ReleaseHDC(hdc);

   }


   void graphics::enum_fonts(::write_text::font_enumeration_item_array & itema)
   {

      ::draw2d::wingdi_enum_fonts(itema, false, true, true);

   }


   bool graphics::prefer_mapped_image_on_mix()
   {

      return true;

   }


   bool graphics::TextOutAlphaBlend(double x, double y, const block & block)
   {

      if (m_pimageAlphaBlend->is_set())
      {

         single_lock synchronouslock(mutex());

         if (block.is_empty())
         {

            return false;

         }

         // "Reference" implementation for TextOutAlphaBlend

         ::rectangle_i32 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         const ::size_f64 & size = ::size_f64(get_text_extent(block));

         //size.cx = size.cx * 110 / 100;

         //size.cy = size.cy * 110 / 100;

         ::rectangle_i32 rectText(point_i32((LONG)x, (LONG)y), size);

         if (rectIntersect.intersect(rectIntersect, rectText))
         {

            ::image_pointer pimage1;
            //#ifdef _UWP
            //            g_pimagea.add(pimage1);
            //#endif

            pimage1 = create_image(rectText.size());

            pimage1->get_graphics()->set(get_current_font());

            pimage1->get_graphics()->set(get_current_brush());

            pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

            pimage1->get_graphics()->text_out(0, 0, block);

            pimage1->blend2(nullptr, m_pimageAlphaBlend, point_i32((int)maximum(0, x - m_pointAlphaBlend.x), (int)maximum(0, y - m_pointAlphaBlend.y)), rectText.size(), 255);

            _draw_raw({ ::point_i32((LONG)x, (LONG) y), rectText.size() }, pimage1->get_graphics());

            return true;

         }



      }

      return false;

   }


   //bool graphics::draw_blend(const ::point_i32 & pointDst, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_i32 & rectSrc)
   //{

   //   //return ::draw2d::graphics::BitBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop);

   //   if (m_pimageAlphaBlend->is_set())
   //   {

   //      if (x < 0)
   //      {

   //         xSrc -= x;

   //         nWidth += x;

   //         x = 0;

   //      }

   //      if (y < 0)
   //      {

   //         ySrc -= y;

   //         nHeight += y;

   //         y = 0;

   //      }


   //      ::rectangle_i32 rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->::size_f64());

   //      ::rectangle_i32 rectBlt(point_i32((i64)x, (i64)y), ::size_f64(nWidth, nHeight));

   //      if (rectIntersect.intersect(rectIntersect, rectBlt))
   //      {

   //         //if (m_pointAlphaBlend.x < 0)
   //         //{

   //         //   xSrc += -m_pointAlphaBlend.x;

   //         //}
   //         //if (m_pointAlphaBlend.y < 0)
   //         //{

   //         //   ySrc += -m_pointAlphaBlend.y;

   //         //}

   //         // The following commented out code does not work well when there is clipping
   //         // and some calculations are not precise
   //         //if (m_pimage != nullptr && pgraphicsSrc->m_pimage != nullptr)
   //         //{

   //         //   const ::point_i32 & pointOff = GetViewportOrg();

   //         //   x += pointOff.x;

   //         //   y += pointOff.y;

   //         //   return m_pimage->blend(::point_i32(x, y), pgraphicsSrc->m_pimage, ::point_i32(xSrc, ySrc), m_pimageAlphaBlend, point_i32(m_pointAlphaBlend.x - x, m_pointAlphaBlend.y - y), rectBlt.::size_f64());

   //         //}
   //         //else
   //         {

   //            ::image_pointer pimage1;
   //            
   //            auto estatus = __construct(pimage1);

   //            if (!estatus)
   //            {

   //               return false;

   //            }
   //            
   //            estatus = pimage1->create(rectBlt.::size_f64());

   //            if (!estatus)
   //            {

   //               return false;

   //            }

   //            pimage1->g()->set_alpha_mode(::draw2d::alpha_mode_set);

   //            if (!pimage1->from(nullptr, pgraphicsSrc, ::point_i32(xSrc, ySrc), rectBlt.::size_f64()))
   //               return false;

   //            pimage1->blend2(::point_i32(), m_pimageAlphaBlend, point_i32(x - m_pointAlphaBlend.x, y - m_pointAlphaBlend.y), rectBlt.::size_f64(), 255);

   //            BitBltRaw(x, y, nWidth, nHeight, pimage1->get_graphics(), 0, 0, dwRop);

   //         }

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   bool graphics::_get(::draw2d::matrix & matrix)
   {

      Gdiplus::Matrix m;

      if (m_pgraphics->GetTransform(&m) != Gdiplus::Ok)
      {

         return false;

      }

      float fa[6];

      m.GetElements(fa);

      matrix = ::draw2d::matrix();

      matrix.SetElements(fa);

      return true;

   }


   bool graphics::_set(const ::draw2d::matrix & matrix)
   {

      Gdiplus::Matrix m;

      m.SetElements((Gdiplus::REAL) matrix.a1, (Gdiplus::REAL)matrix.a2, (Gdiplus::REAL)matrix.b1, (Gdiplus::REAL)matrix.b2, (Gdiplus::REAL)matrix.c1, (Gdiplus::REAL)matrix.c2);

      return m_pgraphics->SetTransform(&m) == Gdiplus::Ok;

   }


   //bool graphics::append(const ::draw2d::matrix & matrix)
   //{

   //   ::draw2d::matrix m;

   //   get(m);

   //   m.append(matrix);

   //   return set(m);

   //}


   //bool graphics::prepend(const ::draw2d::matrix & matrix)
   //{

   //   ::draw2d::matrix m;

   //   get(m);

   //   m.prepend(matrix);

   //   return set(m);

   //}

} // namespace draw2d_gdiplus





