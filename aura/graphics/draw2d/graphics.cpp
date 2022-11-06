#include "framework.h"
#include "graphics.h"
#include "brush.h"
#include "pen.h"
#include "path.h"
#include "draw2d.h"
#include "aura/platform/aura.h"
#include "aura/graphics/image/array.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/write_text/fonts.h"
#include "acme/parallelization/single_lock.h"
#include "acme/primitive/geometry2d/_enhanced.h"
#include "acme/primitive/geometry2d/_collection_enhanced.h"
#include "acme/primitive/geometry2d/_defer_shape.h"
#include "acme/primitive/string/str.h"
#include "aura/user/user/interaction.h"
#include "nanosvg/nanosvg.h"


#define IMAGE_OK(pimpl) (::is_set(pimpl) && pimpl->area() > 0)


namespace draw2d
{


   bool word_break(::draw2d::graphics * pgraphics, const ::string & strSource, const rectangle_i32 & rectangleParam, string &str1, string & str2, int iEll);


   strsize _EncodeV033(string & str);


   graphics::graphics()
   {

      m_puserinteraction = nullptr;
      m_bUseImageMipMapsOrResizedImages = false;

      m_pointOrigin.x = 0;
      m_pointOrigin.y = 0;
      m_sizeScaling.cx = 1.0;
      m_sizeScaling.cy = 1.0;
      //m_estatus = success;
      //m_estatusLast = success;

      //m_bAlphaBlend = false;
      m_bBeginDraw = false;
      //m_puserstyle = nullptr;

      //m_bLayoutModified = false;

      m_bOutline = false;

      defer_create_synchronization();

      m_bPat                     = false;
      m_bStoreThumbnails         = true;
      m_pdrawcontext             = nullptr;
      m_dFontFactor              = 1.0;
      m_efillmode                = e_fill_mode_winding;
      m_ealphamode               = e_alpha_mode_none;
      m_ewritetextrendering      = ::write_text::e_rendering_undefined;
      m_einterpolationmode       = e_interpolation_mode_none;

   }


   graphics::~graphics()
   {

   }


   void graphics::prefer_mapped_image_on_mix()
   {

      //return false;

   }


   ::text::context * graphics::textcontext()
   {
      
      return m_ptextcontext;

   }


   ::aura::draw_context * graphics::draw_context()
   {
      return m_pdrawcontext;
   }


   bool graphics::is_set()
   {

      return get_os_data() != 0;

   }


   //void graphics::set_direct2d_plugin(::draw2d_direct2d::plugin * pplugin)
   //{


   //}


   ::image_pointer graphics::image_source_image(const concrete < ::size_i32 > & sizeDst)
   {
      
      return m_pimage->get_image(sizeDst); 
   
   }

   
   concrete < ::size_i32 > graphics::image_source_size(const ::size_f64 & sizeDst, enum_image_selection eimageselection) const
   {
      
      return m_pimage->image_source_size(sizeDst, eimageselection); 
   
   }


   concrete < ::size_i32 > graphics::image_source_size() const 
   { 
      
      return m_pimage->size(); 
   
   }


   void graphics::on_begin_draw()
   {

      set_alpha_mode(::draw2d::e_alpha_mode_set);

      set_text_rendering_hint(::write_text::e_rendering_system_default);

      ::color::color color(0, 0, 0, 0);

      fill_rectangle(get_size(), color);

      //return true;

   }

   //void *  graphics::get_os_data(int i) const
   //{

   //   return 0;

   //}


   //void graphics::release_os_data_ex(int i, void * p)
   //{

   //}


   void graphics::attach(void * pdata)
   {



      //return false;

   }


   void * graphics::detach()
   {



      return nullptr;

   }


#ifdef WINDOWS_DESKTOP


   void graphics::attach_hdc(hdc hdc)
   {

      throw ::interface_only();

      //return false;

   }


   hdc graphics::detach_hdc()
   {

      throw ::interface_only();

      return nullptr;

   }


   void graphics::AttachPrinter(hdc hdc)
   {

      throw ::interface_only();

      //return false;

   }


   hdc graphics::DetachPrinter()
   {

      throw ::interface_only();

      return nullptr;

   }

#endif


   //oswindow graphics::get_window_handle() const
   //{

   //   if (!m_puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   oswindow oswindow = m_puserinteraction->get_safe_oswindow();

   //   if (!oswindow)
   //   {

   //      return nullptr;

   //   }

   //   return oswindow;

   //}


   //::size_f64 graphics::size_i32(const ::size_f64 & sizeHint) const
   //{

   //   return m_pimage->size_i32(sizeHint);

   //}


   //void graphics::IsPrinting()
   //{



   //   return false;

   //}


   void graphics::thread_select()
   {


   }


   void graphics::create_device_context(const ::string & pszDriverName,  const ::string & pszDeviceName, const ::string & pszOutput, const void * pInitData)
   {

      __UNREFERENCED_PARAMETER(pszDriverName);

      __UNREFERENCED_PARAMETER(pszDeviceName);

      __UNREFERENCED_PARAMETER(pszOutput);

      __UNREFERENCED_PARAMETER(pInitData);

      //return false;

   }


   void graphics::create_information_context(const ::string & pszDriverName,  const ::string & pszDeviceName, const ::string & pszOutput, const void * pInitData)
   {

      __UNREFERENCED_PARAMETER(pszDriverName);

      __UNREFERENCED_PARAMETER(pszDeviceName);

      __UNREFERENCED_PARAMETER(pszOutput);

      __UNREFERENCED_PARAMETER(pInitData);

      //return false;

   }


   void graphics::create_memory_graphics()
   {

      CreateCompatibleDC(nullptr);
      //if (!CreateCompatibleDC(nullptr))
      //{

      //   return false;

      //}

      //return true;

   }


   void graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);



      //return false;

   }


   void graphics::CreateWindowDC(oswindow wnd)
   {

      __UNREFERENCED_PARAMETER(wnd);



      //return false;

   }


   /*   i32 graphics::ExcludeUpdateRgn(::user::interaction_impl * pwindow)
      {
         __UNREFERENCED_PARAMETER(pwindow);

      }
      */

   i32 graphics::GetDeviceCaps(i32 nIndex)
   {
      __UNREFERENCED_PARAMETER(nIndex);


      return -1;

   }


   point_f64 graphics::GetBrushOrg()
   {

      return nullptr;

   }


   void graphics::set_font(::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate)
   {

      auto pstyle = pinteraction->get_style(m_puserstyle);

      auto pfont = pinteraction->get_font(pstyle, eelement, estate);

      return set(pfont);

   }


   void graphics::set_text_color(::color::color color)
   {

      auto pbrush = __create < ::draw2d::brush >();

      //if (!pbrush)
      //{

      //   //return false;



      //}

      pbrush->create_solid(color);

      return set(pbrush);

   }


   point_f64 graphics::SetBrushOrg(double x, double y)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);

      return nullptr;

   }

   
   point_f64 graphics::SetBrushOrg(const ::point_f64 & point)
   {

      __UNREFERENCED_PARAMETER(point);

      return nullptr;

   }

/*
   i32 graphics::EnumObjects(i32 nObjectType, i32 (CALLBACK* pfn)(LPVOID, lparam), lparam pData)

   {
      __UNREFERENCED_PARAMETER(nObjectType);
      __UNREFERENCED_PARAMETER(pfn);

      __UNREFERENCED_PARAMETER(pData);



      return -1;

   }
   */


   void graphics::set(::draw2d::bitmap* pbitmap)
   {

      if (::is_null(pbitmap))
      {

         throw ::exception(error_bad_argument);

      }

      m_pbitmap = pbitmap;

      //return ::error_failed;

   }



   void graphics::set(::draw2d::pen * ppen)
   {

      if (::is_null(ppen))
      {

         throw ::exception(error_bad_argument);

      }

      m_ppen = ppen;

   }


   void graphics::set(::draw2d::brush* pbrush)
   {

      if (::is_null(pbrush))
      {

         throw ::exception(error_bad_argument);

      }

      m_pbrush = pbrush;

   }


   void graphics::set(::draw2d::region* pregion)
   {

      if (::is_null(pregion))
      {

         throw ::exception(error_bad_argument);

      }

      m_pregion = pregion;

   }


   //::color::color graphics::GetNearestColor(const ::color::color & colorColor)
   //{

   //   __UNREFERENCED_PARAMETER(crColor);

   //   return 0;

   //}


   //::u32 graphics::RealizePalette()
   //{


   //   return -1;

   //}

   //void graphics::UpdateColors()
   //{




   //}


   //i32 graphics::GetPolyFillMode()
   //{



   //   return -1;

   //}


   //i32 graphics::GetROP2()
   //{



   //   return -1;

   //}


   //i32 graphics::GetStretchBltMode()
   //{



   //   return -1;

   //}


   point_f64 graphics::get_origin()
   {

      return ::point_i32((::i32)m_pointOrigin.x, (::i32) m_pointOrigin.y);

   }


   size_f64 graphics::get_extents()
   {

      return ::size_f64(0, 0);

   }


   point_f64 graphics::GetWindowOrg()
   {

      return nullptr;

   }


   size_f64 graphics::GetWindowExt()
   {

      return ::size_f64(0, 0);

   }


   point_f64 graphics::set_origin(const ::point_f64 & point)
   {

      return set_origin(point.x, point.y);

   }


   size_f64 graphics::set_extents(const ::size_f64 & size)
   {

      __UNREFERENCED_PARAMETER(size);

      return ::size_f64(0, 0);

   }


   point_f64 graphics::SetWindowOrg(const ::point_f64 & point)
   {

      __UNREFERENCED_PARAMETER(point);

      return nullptr;

   }


   size_f64 graphics::set_window_ext(const ::size_f64 & size)
   {

      __UNREFERENCED_PARAMETER(size);

      return ::size_f64(0, 0);

   }


   void graphics::DPtoLP(point_f64 * ppoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);
      __UNREFERENCED_PARAMETER(nCount);

   }


   void graphics::DPtoLP(::rectangle_f64 * prectangle)
   {

      __UNREFERENCED_PARAMETER(prectangle);

   }


   void graphics::LPtoDP(::point_f64 * ppoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);
      __UNREFERENCED_PARAMETER(nCount);

   }


   void graphics::LPtoDP(::rectangle_f64 * prectangle)
   {

      __UNREFERENCED_PARAMETER(prectangle);

   }


   void graphics::fill_region(::draw2d::region* pregion, ::draw2d::brush* pbrush)
   {

      __UNREFERENCED_PARAMETER(pregion);
      __UNREFERENCED_PARAMETER(pbrush);

      //return false;

   }


   void graphics::frame_region(::draw2d::region * pregion, ::draw2d::brush * pbrush, double nWidth, double nHeight)
   {

      __UNREFERENCED_PARAMETER(pregion);
      __UNREFERENCED_PARAMETER(pbrush);
      __UNREFERENCED_PARAMETER(nWidth);
      __UNREFERENCED_PARAMETER(nHeight);

      //return false;

   }


   void graphics::invert_region(::draw2d::region * pregion)
   {

      __UNREFERENCED_PARAMETER(pregion);

      //return false;

   }


   void graphics::paint_region(::draw2d::region * pregion)
   {

      __UNREFERENCED_PARAMETER(pregion);

      //return false;

   }


   point_f64 graphics::current_position()
   {

      return m_point;

   }


   void graphics::set_current_point(double x, double y)
   {

      m_point.x = x;

      m_point.y = y;

      //return true;

   }


   void graphics::line_to(double x, double y)
   {

      return draw_line(m_point.x, m_point.y, x, y);

   }


   void graphics::draw_line(double x1, double y1, double x2, double y2)
   {

      return draw_line(x1, y1, x2, y2, m_ppen);

   }


   void graphics::draw_line(double x1, double y1, double x2, double y2, ::draw2d::pen * ppen)
   {

      // return draw_line(point_f64(point1), point_f64(point2), ppen);
      //return false;

   }


   void graphics::rectangle(const ::rectangle_f64 & rectangle)
   {

      //if (fill_rectangle(rectangle))

      fill_rectangle(rectangle);
      //{
      draw_rectangle(rectangle);
         //if (draw_rectangle(rectangle))
      //   {

      //      return true;

      //   }

      //}

      //return false;

   }


   void graphics::draw_rectangle(const ::rectangle_f64 & rectangle)
   {

      //return draw_rectangle(::rectangle_f64(rectangle), m_ppen);
      draw_rectangle(::rectangle_f64(rectangle), m_ppen);

   }


   void graphics::draw_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen)
   {
      
      throw ::interface_only();

      //return false;

   }


   void graphics::fill_rectangle(const ::rectangle_f64 & rectangle)
   {

      fill_rectangle(rectangle, m_pbrush);

   }


   void graphics::fill_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush)
   {

      //return false;

   }


   void graphics::arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      double x = (x1 + x2) / 2.0;

      double y = (y1 + y2) / 2.0;

      arc(x1, y1, x2 - x1, y2 - y1, atan2(x3 - x, y3 - y), atan2(x4 - x, y4 - y));

   }


   void graphics::arc(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      arc(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);

   }


   void graphics::arc(double x, double y, double w, double h, angle start, angle extends)
   {

      arc(rectangle_f64_dimension(x, y, w, h), start, extends);

   }


   void graphics::arc(const ::rectangle_f64 & rectangle, angle start, angle extends)
   {

      arc(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), start, extends);

   }


   void graphics::polyline(const ::point_f64 * ppoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);

      __UNREFERENCED_PARAMETER(nCount);

      //return false;

   }


   void graphics::frame_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush)
   {

      __UNREFERENCED_PARAMETER(rectangle);
      __UNREFERENCED_PARAMETER(pbrush);

      //return false;

   }


   void graphics::invert_rectangle(const ::rectangle_f64 & rectangle)
   {

      __UNREFERENCED_PARAMETER(rectangle);

      //return false;

   }


   void graphics::Chord(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      __UNREFERENCED_PARAMETER(x1);
      __UNREFERENCED_PARAMETER(y1);
      __UNREFERENCED_PARAMETER(x2);
      __UNREFERENCED_PARAMETER(y2);
      __UNREFERENCED_PARAMETER(x3);
      __UNREFERENCED_PARAMETER(y3);
      __UNREFERENCED_PARAMETER(x4);
      __UNREFERENCED_PARAMETER(y4);

      //return false;

   }


   void graphics::Chord(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      __UNREFERENCED_PARAMETER(rectangle);
      __UNREFERENCED_PARAMETER(pointStart);
      __UNREFERENCED_PARAMETER(pointEnd);

      //return false;

   }


   void graphics::DrawFocusRect(const ::rectangle_f64 & rectangle)
   {

      __UNREFERENCED_PARAMETER(rectangle);

   }


   void graphics::ellipse(const ::rectangle_f64 & rectangle)
   {

      //auto ealphamode = m_ealphamode;

      //set_alpha_mode(e_alpha_mode_blend);

      fill_ellipse(rectangle);

      draw_ellipse(rectangle);

      //set_alpha_mode(ealphamode);

      //return bFill && bDraw;

   }


   void graphics::ellipse(double x1, double y1, double x2, double y2)
   {

      fill_ellipse(x1, y1, x2, y2);

      draw_ellipse(x1, y1, x2, y2);

      //return bFill && bDraw;

   }


   void graphics::draw_ellipse(double x1, double y1, double x2, double y2)
   {

      ::rectangle_f64 rectangle(x1, y1, x2, y2);

      draw_ellipse(rectangle);

   }


   void graphics::draw_ellipse(const ::rectangle_f64 & rectangle)
   {

      return draw_ellipse(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

   }


   void graphics::fill_ellipse(double x1, double y1, double x2, double y2)
   {

      ::rectangle_f64 rectangle(x1, y1, x2, y2);

      fill_ellipse(rectangle);

   }


   void graphics::fill_ellipse(const ::rectangle_f64 & rectangle)
   {

      __UNREFERENCED_PARAMETER(rectangle);

      //return false;

   }


   void graphics::Pie(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      __UNREFERENCED_PARAMETER(x1);
      __UNREFERENCED_PARAMETER(y1);
      __UNREFERENCED_PARAMETER(x2);
      __UNREFERENCED_PARAMETER(y2);
      __UNREFERENCED_PARAMETER(x3);
      __UNREFERENCED_PARAMETER(y3);
      __UNREFERENCED_PARAMETER(x4);
      __UNREFERENCED_PARAMETER(y4);

      //return false;

   }


   void graphics::Pie(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      __UNREFERENCED_PARAMETER(rectangle);
      __UNREFERENCED_PARAMETER(pointStart);
      __UNREFERENCED_PARAMETER(pointEnd);

      //return false;

   }


   void graphics::fill_polygon(const POINT_F64 * ppoints, count nCount)
   {
      
      throw ::interface_only();

      //return false;

   }


   void graphics::draw_polygon(const POINT_F64 * ppoints, count nCount)
   {
      
      throw ::interface_only();

      //return false;

   }


   void graphics::polygon(const POINT_F64 * ppoints, count nCount)
   {

      fill_polygon(ppoints, nCount);

      draw_polygon(ppoints, nCount);

      //return bOk1 && bOk2;

   }


   void graphics::poly_polygon(const POINT_F64 * ppoints, const i32 * pPolyCounts, count nCount)
   {

      fill_poly_polygon(ppoints, pPolyCounts, nCount);

      draw_poly_polygon(ppoints, pPolyCounts, nCount);

      //return bOk1 && bOk2;

   }


   void graphics::draw_poly_polygon(const POINT_F64 * ppoints, const i32 * pPolyCounts, count nCount)
   {

      //bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         //if (!draw_polygon(ppoints, *pPolyCounts))
         draw_polygon(ppoints, *pPolyCounts);
         //{

         //   bOk = false;

         //}

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      // return bOk;

   }


   void graphics::fill_poly_polygon(const POINT_F64 * ppoints, const i32 * pPolyCounts, count nCount)
   {

      //bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         //if (!fill_polygon(ppoints, *pPolyCounts))
         fill_polygon(ppoints, *pPolyCounts);
         //{

         //   bOk = false;

         //}

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      //return bOk;

   }


   bool graphics::has_blender() const
   {

      return m_pimageAlphaBlend.is_set();

   }


   bool graphics::_draw_blend(const ::image_drawing & imagedrawing)
   {

      if (!has_blender())
      {

         throw ::exception(error_bad_argument);

      }

      if (m_pimageAlphaBlend->is_ok())
      {

         ::rectangle_f64 rectangleAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         ::rectangle_f64 rectangleIntersect;

         if (rectangleIntersect.intersect(rectangleAlphaBlend, imagedrawing.m_rectangleTarget))
         {

            auto rectangleSource = imagedrawing.source_rectangle();

            auto & rectangleTarget = imagedrawing.m_rectangleTarget;

            ::size_i32 size(imagedrawing.m_rectangleTarget.size());

            ::image_pointer pimage1 = m_pcontext->m_pauracontext->create_image(size);

            image_source imagesource(imagedrawing.m_pimagesource, rectangleSource);

            rectangle_f64 rectangle(size);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pimage1->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

            pimage1->draw(imagedrawing);

            auto x = rectangleTarget.left;

            auto y = rectangleTarget.top;

            point_i32 pointDst;

            pointDst.y = (::i32) maximum(0., rectangleIntersect.top - y);

            pointDst.x = (::i32) maximum(0., rectangleIntersect.left - x);

            point_i32 pointSrc;

            pointSrc.y = (::i32) maximum(0, y - rectangleAlphaBlend.top);

            pointSrc.x = (::i32) maximum(0, x - rectangleAlphaBlend.left);

            pimage1->blend2(pointDst, m_pimageAlphaBlend, pointSrc, rectangleIntersect.size(), 255);

            image_drawing_options imagedrawingoptionsDrawRaw;

            set_alpha_mode(::draw2d::e_alpha_mode_blend);

            _draw_raw(rectangleTarget, pimage1, imagedrawingoptionsDrawRaw, ::point_f64());

            return true;

         }

      }

      return false;

   }


   //void graphics::draw(const ::point_f64 & point, cursor * pcursor)
   //{
   //
   //   set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //   ::point_i32 pointDst(point_i32 - pcursor->m_szHotspotOffset);

   //   auto pimage = pcursor->m_pimage;

   //   return draw(::rectangle_f64(pointDst, pimage->size()), pimage->g());

   //}


   //void graphics::draw_at(const ::point_f64 & pointDst, ::image * pimage)
   //{

   //   return draw(::rectangle_f64(pointDst, pimage->get_size()), pimage->g());

   //}


   //void graphics::draw_at(const ::point_f64 & pointDst, ::image_frame * pframe)
   //{

   //   return draw_at(pointDst, pframe->m_pimage);

   //}


   //void graphics::draw_at(const ::point_f64 & pointDst, ::draw2d::graphics * pgraphics)
   //{

   //   return draw_at(pointDst, pgraphics->m_pimage);

   //}


   //void graphics::draw(::image * pimage, const ::point_f64 & pointSrc)
   //{

   //   return draw(pimage->get_size() - pointSrc, pimage, pointSrc);

   //}


   //void graphics::draw(::image_frame * pframe, const ::point_f64 & pointSrc)
   //{

   //   return draw(pframe->m_pimage, pointSrc);

   //}


   //void graphics::draw(::draw2d::graphics * pgraphicsSrc, const ::point_f64 & pointSrc)
   //{

   //   return draw(pgraphicsSrc->m_pimage, pointSrc);

   //}

   
   //void graphics::draw(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::point_f64 & pointSrc)
   //{

   //   return draw(rectangleTarget, pimage->g(), pointSrc);

   //}


   //void graphics::draw(const ::rectangle_f64 & rectangleTarget, ::image_frame * pframe, const ::point_f64 & pointSrc)
   //{

   //   return draw(rectangleTarget, pframe->m_pimage, pointSrc);

   //}




   //void graphics::stretch_raw(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource)
   //{

   //   return false;

   //}


   //void graphics::stretch_blend(const ::rectangle_f64 & rectangleDstParam, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSrcParam)
   //{

   //   //::rectangle_f64 rectangleTarget(rectangleDstParam);

   //   //::rectangle_f64 rectangleSource(rectangleSrcParam);

   //   //if (m_pimageAlphaBlend)
   //   //{

   //   //   if (rectangleTarget.left < 0)
   //   //   {

   //   //      rectangleSource.left -= rectangleTarget.left;

   //   //      rectangle.right += rectangle.left;

   //   //      rectangle.left = 0;

   //   //   }

   //   //   if (rectangle.top < 0)
   //   //   {

   //   //      point.y -= rectangle.top;

   //   //      rectangle.bottom += rectangle.top;

   //   //      rectangle.top = 0;

   //   //   }

   //   //   ::rectangle_f64 rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->get_size());

   //   //   if (rectangleIntersect.intersect(rectangleIntersect, rectangle))
   //   //   {

   //   //      // The following commented out code does not work well when there is clipping
   //   //      // and some calculations are not precise
   //   //      //if (m_pimage != nullptr && pgraphicsSrc->m_pimage != nullptr)
   //   //      //{

   //   //      //   const ::point_f64 & pointOff = get_origin();

   //   //      //   x += pointOff.x;

   //   //      //   y += pointOff.y;

   //   //      //   return m_ppimage->blend(::point_i32(x, y), pgraphicsSrc->m_pimage, ::point_i32(xSrc, ySrc), m_pimageAlphaBlend, point_i32(m_pointAlphaBlend.x - x, m_pointAlphaBlend.y - y), rectangleBlt.size());

   //   //      //}
   //   //      //else
   //   //      {

   //   //         ::image_pointer pimage1;
   //   //         //#ifdef _UWP
   //   //         //               g_pimagea.add(pimage1);
   //   //         //#endif

   //   //         pimage1 = create_image(rectangle.size());

   //   //         pimage1->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //   //         if (!pimage1->from(nullptr, pgraphicsSrc, point, rectangle.size()))
   //   //            return false;

   //   //         pimage1->blend(::point_i32(), m_pimageAlphaBlend,
   //   //            {
   //   //               (int)maximum(0, rectangle.left - m_pointAlphaBlend.x),
   //   //               (int)maximum(0, rectangle.top - m_pointAlphaBlend.y)
   //   //            }, rectangle.size());

   //   //         draw_image(rectangle, pimage1->get_graphics());

   //   //      }

   //   //      return true;

   //   //   }



   //   //}

   //   return false;

   //}


   //void graphics::draw_image(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc)
   //{

   //   if(pgraphicsSrc == nullptr)
   //   {

   //      return false;

   //   }

   //   ::image_pointer pimage = pgraphicsSrc->m_pimage;

   //   if(pimage->is_null())
   //   {

   //      return false;

   //   }

   //   ::rectangle_f64 rectangleSource(nullptr, pimage->get_size());

   //   return draw_image(rectangleTarget, pgraphicsSrc, rectangleSource);

   //}


   //void graphics::stretch(const ::rectangle_f64 & rectangleTarget, ::image * pimage, const ::rectangle_f64 & rectangleSource)
   //{

   //   return stretch(rectangleTarget, pimage->g(), rectangleSource.is_null() ? ::rectangle_f64(pimage->rectangle()) : rectangleSource);

   //}


   //void graphics::stretch(const ::rectangle_f64 & rectangleTarget, ::image_frame * pframe, const ::rectangle_f64 & rectangleSource)
   //{

   //   return stretch(rectangleTarget, pframe->m_pimage, rectangleSource);

   //}


   //void graphics::stretch(const ::rectangle_f64 & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::rectangle_f64 & rectangleSource)
   //{

   //   if (stretch_blend(rectangleTarget, pgraphicsSrc, rectangleSource))
   //   {

   //      return true;

   //   }

   //   if (stretch_raw(rectangleTarget, pgraphicsSrc, rectangleSource))
   //   {

   //      return true;

   //   }

   //   return false;

   //}


   ::color::color graphics::GetPixel(double x, double y)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);

      return 0;

   }


   ::color::color graphics::GetPixel(const ::point_f64 & point)
   {

      __UNREFERENCED_PARAMETER(point);

      return 0;

   }


   ::color::color graphics::SetPixel(double x, double y, const ::color::color & color)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);
      __UNREFERENCED_PARAMETER(color);

      return 0;

   }


   ::color::color graphics::SetPixel(const ::point_f64 & point, const ::color::color& color)
   {

      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(color);

      return 0;

   }


   ::color::color graphics::blend_pixel(const ::point_f64 & point, const ::color::color & color)
   {

      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(color);

      return 0;

   }


   //void graphics::text_out(double x, double y, const ::string & pszString, strsize nCount)
   //{

   //   return text_out(x, y, string(pszString, nCount));


   //}


   //void graphics::text_out(double x, double y, const ::string & str)
   //{

   //   return text_out((double) x, (double) y, str);

   //}


   //void graphics::text_out(double x, double y, const ::string & pszString, strsize nCount)
   //{

   //   return text_out(x, y, string(pszString, nCount));

   //}


   void graphics::text_out(double x, double y, const block & block)
   {

      if(block.get_size() <= 0)
      {

         return;

      }

      if (m_pimageAlphaBlend)
      {

         //if (TextOutAlphaBlend(x, y, block))
         if(TextOutAlphaBlend(x, y, block))
         {

            return;

         }

      }

      TextOutRaw(x, y, block);

   }


   void graphics::TextOutRaw(double x, double y, const block & str)
   {

      //return false;

   }


//   bool graphics::TextOutAlphaBlend(double x, double y, const block & block)
//   {
//
//      if (block.get_size() <= 0)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      ASSERT(m_pimageAlphaBlend->is_ok());
//
//      single_lock synchronouslock(this->synchronization());
//
//      // "Reference" implementation for TextOutAlphaBlend
//
//      ::rectangle_f64 rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->get_size());
//
//      const ::size_i32 & size = ::size_i32(get_text_extent((const char *) block.get_data(), block.get_size()));
//
//      ::rectangle_f64 rectangleText(point_i32((::i32)x, (::i32)y), size);
//
//      if (rectangleIntersect.intersect(rectangleIntersect, rectangleText))
//      {
//
//         ::image_pointer pimage1;
////#ifdef _UWP
////            g_pimagea.add(pimage1);
////#endif
//
//         pimage1 = m_pcontext->m_pauracontext->create_image(rectangleText.size());
//
//         pimage1->get_graphics()->set(get_current_font());
//
//         pimage1->get_graphics()->set(get_current_brush());
//
//         pimage1->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//         pimage1->get_graphics()->text_out(0, 0, block);
//
//         {
//
//            image_source imagesource(m_pimageAlphaBlend, ::rectangle_f64(point_i32((int)maximum(0, x - m_pointAlphaBlend.x), (int)maximum(0, y - m_pointAlphaBlend.y)), rectangleText.size()));
//
//            rectangle_f64 rectangle(pimage1->rectangle());
//
//            image_drawing_options imagedrawingoptions(rectangle);
//
//            image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//            pimage1->g()->draw(imagedrawing);
//
//         }
//
//         {
//
//            set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//            image_source imagesource(pimage1);
//
//            rectangle_f64 rectangle(::rectangle_f64(::point_f64(x, y), rectangleText.size()));
//
//            image_drawing_options imagedrawingoptions(rectangle);
//
//            image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//            draw(imagedrawing);
//
//         }
//
//         return true;
//
//      }
//
//      return false;
//
//   }

   bool graphics::TextOutAlphaBlend(double x, double y, const block & block)
   {

      if (m_pimageAlphaBlend->is_set())
      {

         single_lock synchronouslock(this->synchronization());

         if (block.is_empty())
         {

            //return false;

            throw ::exception(error_null_pointer);


         }

         // "Reference" implementation for TextOutAlphaBlend

         ::rectangle_i32 rectangleAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         ::rectangle_i32 rectangleIntersect;

         const ::size_f64 & size = ::size_f64(get_text_extent(block));

         //size.cx = size.cx * 110 / 100;

         //size.cy = size.cy * 110 / 100;

         ::rectangle_i32 rectangleText(point_i32((::i32)x, (::i32)y), size);

         if (rectangleIntersect.intersect(rectangleAlphaBlend, rectangleText))
         {

            ::image_pointer pimage1;

            pimage1 = m_pcontext->m_pauracontext->create_image(rectangleText.size());

            pimage1->fill(0);

            pimage1->get_graphics()->set(get_current_font());

            pimage1->get_graphics()->set(get_current_brush());

            pimage1->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            pimage1->get_graphics()->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

            pimage1->get_graphics()->text_out(0, 0, block);

            point_i32 pointDst;

            pointDst.y = (::i32)maximum(0, rectangleIntersect.top - y);

            pointDst.x = (::i32)maximum(0, rectangleIntersect.left - x);

            point_i32 pointSrc;

            pointSrc.y = (::i32)maximum(0, y - rectangleAlphaBlend.top);

            pointSrc.x = (::i32)maximum(0, x - rectangleAlphaBlend.left);

            pimage1->blend2(pointDst, m_pimageAlphaBlend, pointSrc, rectangleIntersect.size(), 255);

            image_drawing_options imagedrawingoptions;

            set_alpha_mode(::draw2d::e_alpha_mode_blend);

            _draw_raw(rectangleText, pimage1, imagedrawingoptions, ::point_f64());

            return true;

         }

      }

      return false;

   }


   //void graphics::ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const ::string & pszString, strsize nCount, i32 * pDxWidths)
   //{

   //   __UNREFERENCED_PARAMETER(x);
   //   __UNREFERENCED_PARAMETER(y);
   //   __UNREFERENCED_PARAMETER(nOptions);
   //   __UNREFERENCED_PARAMETER(rectangle);
   //   __UNREFERENCED_PARAMETER(pszString);
   //   __UNREFERENCED_PARAMETER(nCount);
   //   __UNREFERENCED_PARAMETER(pDxWidths);

   //   return false;

   //}


   //void graphics::ExtTextOut(double x, double y, ::u32 nOptions, const ::rectangle_f64 & rectangle, const ::string & str, i32 * pDxWidths)
   //{

   //   __UNREFERENCED_PARAMETER(x);
   //   __UNREFERENCED_PARAMETER(y);
   //   __UNREFERENCED_PARAMETER(nOptions);
   //   __UNREFERENCED_PARAMETER(rectangle);
   //   __UNREFERENCED_PARAMETER(str);
   //   __UNREFERENCED_PARAMETER(pDxWidths);

   //   return false;

   //}


   //size_f64 graphics::TabbedTextOut(double x, double y, const ::string & pszString, strsize nCount, count nTabPositions, i32 * pnTabStopPositions, int nTabOrigin)
   //{

   //   __UNREFERENCED_PARAMETER(x);
   //   __UNREFERENCED_PARAMETER(y);
   //   __UNREFERENCED_PARAMETER(pszString);
   //   __UNREFERENCED_PARAMETER(nCount);
   //   __UNREFERENCED_PARAMETER(nTabPositions);
   //   __UNREFERENCED_PARAMETER(pnTabStopPositions);
   //   __UNREFERENCED_PARAMETER(nTabOrigin);

   //   return size_f64(0, 0);

   //}


   //size_f64 graphics::TabbedTextOut(double x, double y, const ::string & str, count nTabPositions, i32 * pnTabStopPositions, int nTabOrigin)
   //{

   //   __UNREFERENCED_PARAMETER(x);
   //   __UNREFERENCED_PARAMETER(y);
   //   __UNREFERENCED_PARAMETER(str);
   //   __UNREFERENCED_PARAMETER(nTabPositions);
   //   __UNREFERENCED_PARAMETER(pnTabStopPositions);
   //   __UNREFERENCED_PARAMETER(nTabOrigin);

   //   return size_f64(0, 0);

   //}


   //size_f64 graphics::GetTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * pnTabStopPositions)
   //{

   //   __UNREFERENCED_PARAMETER(pszString);
   //   __UNREFERENCED_PARAMETER(nCount);
   //   __UNREFERENCED_PARAMETER(nTabPositions);
   //   __UNREFERENCED_PARAMETER(pnTabStopPositions);

   //   return size_f64(0, 0);

   //}


   //size_f64 graphics::GetTabbedTextExtent(const ::string & str, count nTabPositions, i32 * pnTabStopPositions)
   //{

   //   __UNREFERENCED_PARAMETER(str);
   //   __UNREFERENCED_PARAMETER(nTabPositions);
   //   __UNREFERENCED_PARAMETER(pnTabStopPositions);

   //   return size_f64(0, 0);

   //}


   //size_f64 graphics::GetOutputTabbedTextExtent(const ::string & pszString, strsize nCount, count nTabPositions, i32 * pnTabStopPositions)
   //{

   //   __UNREFERENCED_PARAMETER(pszString);
   //   __UNREFERENCED_PARAMETER(nCount);
   //   __UNREFERENCED_PARAMETER(nTabPositions);
   //   __UNREFERENCED_PARAMETER(pnTabStopPositions);

   //   return size_f64(0, 0);

   //}


   //size_f64 graphics::GetOutputTabbedTextExtent(const ::string & str, count nTabPositions, i32 * pnTabStopPositions)
   //{

   //   __UNREFERENCED_PARAMETER(str);
   //   __UNREFERENCED_PARAMETER(nTabPositions);
   //   __UNREFERENCED_PARAMETER(pnTabStopPositions);

   //   return size_f64(0, 0);

   //}


   ::u32 graphics::GetTextAlign()
   {

      return -1;

   }


   //i32 graphics::GetTextFace(count nCount, char * pszFacename)
   //{

   //   __UNREFERENCED_PARAMETER(nCount);
   //   __UNREFERENCED_PARAMETER(pszFacename);

   //   return -1;

   //}


   //i32 graphics::GetTextFace(string & rString)
   //{
   //
   //   __UNREFERENCED_PARAMETER(rString);

   //   return -1;

   //}


   void graphics::get_text_metrics(::write_text::text_metric * pMetrics)
   {

      if (!m_pfont)
      {

         return;

      }

      m_pfont->get_os_data(this);

      memcpy(pMetrics, &m_pfont->m_textmetric2, sizeof(*pMetrics));

   }


   void graphics::get_output_text_metrics(::write_text::text_metric * pMetrics)
   {

      __UNREFERENCED_PARAMETER(pMetrics);

      //return false;

   }


   // ::draw2d::graphics_pointer 3.1 Specific functions
   ::u32 graphics::SetBoundsRect(const ::rectangle_f64 & rectangleBounds, ::u32 flags)
   {

      __UNREFERENCED_PARAMETER(rectangleBounds);
      __UNREFERENCED_PARAMETER(flags);

      return -1;

   }


   ::u32 graphics::GetBoundsRect(::rectangle_f64 * pRectBounds, ::u32 flags)
   {

      __UNREFERENCED_PARAMETER(pRectBounds);
      __UNREFERENCED_PARAMETER(flags);

      return -1;

   }


//#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(SOLARIS)
//
//
//   void graphics::ResetDC(const DEVMODE* pDevMode)
//   {
//
//      __UNREFERENCED_PARAMETER(pDevMode);
//
//      return false;
//
//   }
//
//
//#endif


//#ifdef WINDOWS_DESKTOP
//
//
//   // ::user::document handling functions
//   i32 graphics::StartDoc(LPDOCINFO pDocInfo)
//   {
//
//      __UNREFERENCED_PARAMETER(pDocInfo);
//
//      return -1;
//
//   }
//
//
//#endif


   i32 graphics::StartPage()
   {

      return -1;

   }

   
   i32 graphics::EndPage()
   {

      return -1;

   }


   i32 graphics::AbortDoc()
   {

      return -1;

   }


   i32 graphics::EndDoc()
   {

      return -1;

   }


   void graphics::SetPixelV(double x, double y, const ::color::color& color)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);
      __UNREFERENCED_PARAMETER(color);

      //return false;

   }


   void graphics::SetPixelV(const ::point_f64 & point, const ::color::color& color)
   {

      __UNREFERENCED_PARAMETER(point);
      __UNREFERENCED_PARAMETER(color);

      //return false;

   }


   void graphics::angle_arc(double x, double y, double nRadius, angle fStartAngle, angle fSweepAngle)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);
      __UNREFERENCED_PARAMETER(nRadius);
      __UNREFERENCED_PARAMETER(fStartAngle);
      __UNREFERENCED_PARAMETER(fSweepAngle);

      //return false;

   }


   void graphics::arc_to(const ::rectangle_f64 & rectangle, const ::point_f64 & pointStart, const ::point_f64 & pointEnd)
   {

      __UNREFERENCED_PARAMETER(rectangle);
      __UNREFERENCED_PARAMETER(pointStart);
      __UNREFERENCED_PARAMETER(pointEnd);

      //return false;

   }


   //i32 graphics::GetArcDirection()
   //{

   //   return -1;

   //}


   void graphics::poly_polyline(const ::point_f64 * ppoints, const ::i32 * pPolyPoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);

      __UNREFERENCED_PARAMETER(pPolyPoints);

      __UNREFERENCED_PARAMETER(nCount);


      //return false;

   }


//#ifdef WINDOWS_DESKTOP
//
//   void graphics::GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust)
//
//   {
//      __UNREFERENCED_PARAMETER(pColorAdjust);
//
//
//      return false;
//   }
//
//#endif
//

   ::draw2d::pen * graphics::get_current_pen()
   {

      return m_ppen;

   }


   ::draw2d::brush * graphics::get_current_brush()
   {

      return m_pbrush;

   }


   ::draw2d::palette * graphics::get_current_palette()
   {

      return nullptr;

   }


   ::draw2d::bitmap * graphics::get_current_bitmap()
   {

      return m_pbitmap;

   }


   void graphics::poly_bezier(const ::point_f64 * ppoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);
      __UNREFERENCED_PARAMETER(nCount);

      //return false;

   }


   void graphics::abort_path()
   {

      //return false;

   }


   void graphics::begin_path()
   {

      //return false;

   }


   void graphics::close_figure()
   {

      //return false;

   }


   void graphics::end_path()
   {

      //return false;

   }


   void graphics::fill_path()
   {

      //return false;

   }


   void graphics::flatten_path()
   {

      //return false;

   }


   float graphics::GetMiterLimit()
   {

      return false;

   }


//   i32 graphics::GetPath(::point_f64 * ppoints, byte * pTypes, count nCount)
//   {
//
//      __UNREFERENCED_PARAMETER(ppoints);
//      __UNREFERENCED_PARAMETER(pTypes);
//      __UNREFERENCED_PARAMETER(nCount);
//
//      return false;
//
//   }


   void graphics::SetMiterLimit(float fMiterLimit)
   {

      __UNREFERENCED_PARAMETER(fMiterLimit);

      //return false;

   }


   void graphics::stroke_and_fill_path()
   {

      //return false;

   }


   void graphics::stroke_path()
   {

      //return false;

   }


   void graphics::widen_path()
   {

      //return false;

   }


   void graphics::draw(::draw2d::path * ppath)
   {

      //return false;

   }


   void graphics::draw(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      //return false;

   }


   void graphics::fill(::draw2d::path * ppath)
   {

      //return false;

   }


   void graphics::fill(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      //return false;

   }


   void graphics::path(::draw2d::path * ppath)
   {

      //bool bOk1 = 
      fill(ppath);

      //bool bOk2 = 
      draw(ppath);

      //return bOk1 && bOk2;

   }


   void graphics::intersect_clip(::draw2d::path * ppath)
   {

   }


   void graphics::set_clip(::draw2d::path * ppath)
   {

      reset_clip();

      intersect_clip(ppath);

   }


   void graphics::AddMetaFileComment(::u32 nDataSize, const byte* pCommentData)
   {

      __UNREFERENCED_PARAMETER(nDataSize);
      __UNREFERENCED_PARAMETER(pCommentData);

      //return false;

   }


//#ifdef WINDOWS
//
//
//   void graphics::PlayMetaFile(HENHMETAFILE henhmetafile, const rectangle_f64 & rectangleBounds)
//   {
//
//      __UNREFERENCED_PARAMETER(henhmetafile);
//      __UNREFERENCED_PARAMETER(rectangleBounds);
//
//      return false;
//
//   }
//
//
//#endif


   void graphics::DPtoHIMETRIC(::size_f64 * psize)
   {

      __UNREFERENCED_PARAMETER(psize);

   }


   void graphics::HIMETRICtoDP(::size_f64 * psize)
   {

      __UNREFERENCED_PARAMETER(psize);

   }


   void graphics::LPtoHIMETRIC(::size_f64 * psize)
   {

      ASSERT(__is_valid_address(psize, sizeof(::size_f64)));

      LPtoDP(psize);

      DPtoHIMETRIC(psize);

   }


   void graphics::HIMETRICtoLP(::size_f64 * psize)
   {

      ASSERT(__is_valid_address(psize, sizeof(size_f64)));

      HIMETRICtoDP(psize);

      DPtoLP(psize);

   }


   ::draw2d::brush * graphics::GetHalftoneBrush()
   {

      return nullptr;

   }


   void graphics::fill_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
   {

      auto pbrushSolidColor = __create < ::draw2d::brush > ();

      pbrushSolidColor->create_solid(color);

      fill_rectangle(rectangle, pbrushSolidColor);

   }


   void graphics::fill_inset_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
   {

      auto pbrushSolidColor = __create < ::draw2d::brush > ();

      pbrushSolidColor->create_solid(color);

      //if (!
      fill_rectangle(
         {
            rectangle.left + 1,
            rectangle.top + 1,
            rectangle.right - 1,
            rectangle.bottom - 1
         },
         pbrushSolidColor);/*)
      {

         return false;

      }

      return true;*/

   }


   
   void graphics::fill_solid_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color)
   {

      auto pbrushSolidColor = __create < ::draw2d::brush > ();

      pbrushSolidColor->create_solid(color);

      auto smooth_mode = get_smooth_mode();

      if (smooth_mode != e_smooth_mode_none)
      {

         set_smooth_mode(e_smooth_mode_none);

      }

      //if (!fill_rectangle(rectangle, pbrushSolidColor))
      fill_rectangle(rectangle, pbrushSolidColor);
      //{

      //   return false;

      //}

      if (smooth_mode != e_smooth_mode_none)
      {

         set_smooth_mode(smooth_mode);

      }

      //return true;

   }


   void graphics::color_blend_3dRect(const rectangle_i32& rectangleParam, const ::color::color& colorTopLeft, const ::opacity& opacityTopLeft, const ::color::color & colorBottomRight, const ::opacity& opacityBottomRight)
   {

      ::rectangle_i32 rectangle(rectangleParam);

      i32 x = rectangle.left;
      i32 y = rectangle.top;
      i32 cx = rectangle.width();
      i32 cy = rectangle.height();

      //auto estatus1 = 
      fill_rectangle({ point_i32(x, y), size_i32(cx - 1, 1) }, colorTopLeft & opacityTopLeft);

      //auto estatus2 = 
      fill_rectangle({ point_i32(x, y), size_i32(1, cy - 1) }, colorTopLeft & opacityTopLeft);

      //auto estatus3 = 
      fill_rectangle({ point_i32(x + cx - 1, y + 1), size_i32(1, cy - 1) }, colorBottomRight & opacityBottomRight);

      //auto estatus4 =
      fill_rectangle({ point_i32(x + 1, y + cy - 1), size_i32(cx - 1, 1) }, colorBottomRight & opacityBottomRight);

      //return estatus1 && estatus2 && estatus3 && estatus4 ;

   }



   void graphics::draw_inset_3d_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & colorTopLeft, const ::color::color & colorBottomRight, const ::e_border & eborder)
   {

      auto smooth_mode = get_smooth_mode();

      if (smooth_mode != e_smooth_mode_none)
      {

         set_smooth_mode(e_smooth_mode_none);

      }

      if (eborder & e_border_top)
      {

         fill_rectangle(rectangle_f64_dimension(rectangle.left, rectangle.top, rectangle.width(), 1.0), colorTopLeft);

      }

      if (eborder & e_border_left)
      {

         fill_rectangle(rectangle_f64_dimension(
            rectangle.left,
            rectangle.top + (eborder & e_border_top ? 1.0 : 0),
            1.0,
            rectangle.height() - (eborder & e_border_top ? 1.0 : 0)), colorTopLeft);
         //{

         //   return false;

         //}

      }

      if (eborder & e_border_bottom)
      {

         fill_rectangle(rectangle_f64_dimension(
            rectangle.left + (eborder & e_border_left ? 1.0 : 0),
            rectangle.bottom - 1.0,
            rectangle.width() - (eborder & e_border_left ? 1.0 : 0),
            1.0), colorBottomRight);
         //{

         //   return false;

         //}

      }

      if (eborder & e_border_right)
      {

         //if (!
         fill_rectangle(
            ::rectangle_f64_dimension(
               rectangle.right - 1.0,
               rectangle.top + (eborder & e_border_top ? 1.0 : 0),
               1.0,
               rectangle.height() - (eborder & e_border_top ? 1.0 : 0) - (eborder & e_border_bottom ? 1.0 : 0)),
            colorBottomRight);
         //{

         //   return false;

         //}

      }

      if (smooth_mode != e_smooth_mode_none)
      {

         set_smooth_mode(smooth_mode);

      }

      ///return true;

   }


   void graphics::draw_inset_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, const ::e_border & eborder)
   {

      //if (!
      draw_inset_3d_rectangle(rectangle, color, color, eborder);
      //{

      //   return false;

      //}

      //return true;

   }

   void graphics::frame_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, const ::e_border & eborder)
   {

      auto rectangleFrame(rectangle);

      rectangleFrame.inflate(1.0);

      //if (!
      draw_inset_rectangle(rectangleFrame, color, eborder);
      //{

      //   return false;

      //}

      //return true;
   }


//      void graphics::assert_ok() const
//   {
//
//
//
//   }
//
//
//   void graphics::dump(dump_context & dumpcontext) const
//   {
//
//      __UNREFERENCED_PARAMETER(dumpcontext);
//
//
//
//   }


   void graphics::destroy()
   {
      
      //auto estatusOsData =
         
         
         destroy_os_data();
      
      //auto estatusDestroy =
         ::aura::simple_chain < ::aura::draw_context >::destroy();
      
      //return estatusOsData && estatusDestroy;
      
   }

   
   void graphics::destroy_os_data()
   {
      
      clear_os_data();
      
   }


   void graphics::DeleteDC()
   {



      //return false;

   }


   //i32 graphics::StartDoc(const ::string & pszDocName)

   //{

   //   __UNREFERENCED_PARAMETER(pszDocName);




   //   return -1;

   //}


   i32 graphics::SaveDC()
   {

      return -1;
   }


   void graphics::RestoreDC(i32)
   {

      //return false;

   }


   ::draw2d::object* graphics::set_stock_object(i32)
   {

      return nullptr;

   }





   //::draw2d::palette* graphics::SelectPalette(::draw2d::palette *, bool)
   //{

   //   return nullptr;

   //}


   //i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
   //{

   //   __UNREFERENCED_PARAMETER(nPolyFillMode);

   //   return -1;

   //}


   //i32 graphics::SetROP2(i32 nDrawMode)
   //{

   //   __UNREFERENCED_PARAMETER(nDrawMode);

   //   return -1;

   //}


//   i32 graphics::set_interpolation_mode(i32 nStretchMode)
//   {
//
//      __UNREFERENCED_PARAMETER(nStretchMode);
//
//      return -1;
//
//   }


   //i32 graphics::SetGraphicsMode(i32 iMode)
   //{

   //   __UNREFERENCED_PARAMETER(iMode);

   //   return -1;

   //}


//#ifdef WINDOWS
//
//   void graphics::SetWorldTransform(const XFORM* pXform)
//   {
//
//      __UNREFERENCED_PARAMETER(pXform);
//
//      return false;
//
//   }
//
//   void graphics::ModifyWorldTransform(const XFORM* pXform, u32 iMode)
//   {
//
//      __UNREFERENCED_PARAMETER(pXform);
//      __UNREFERENCED_PARAMETER(iMode);
//
//      return false;
//
//   }
//
//#endif

   //i32 graphics::SetMapMode(i32 nMapMode)
   //{

   //   __UNREFERENCED_PARAMETER(nMapMode);

   //   return -1;

   //}


   point_f64 graphics::set_origin(double x, double y)
   {

      m_pointOrigin = {x, y};

      update_matrix();

      return m_pointOrigin;

   }


   ::size_f64 graphics::get_scaling()
   {

      return m_sizeScaling;

   }


   point_f64 graphics::offset_origin(double nWidth, double nHeight)
   {

      ::shift_i32(nWidth, nHeight)(m_pointOrigin);

      update_matrix();

      return m_pointOrigin;

   }


   size_f64 graphics::set_extents(double x, double y)
   {

      __UNREFERENCED_PARAMETER(x);

      __UNREFERENCED_PARAMETER(y);

      return size_f64(0, 0);

   }


   size_f64 graphics::scale_extents(double xNum, double xDenom, double yNum, double yDenom)
   {

      m_sizeScaling *= xNum / xDenom;

      update_matrix();

      return m_sizeScaling;

   }


   point_f64 graphics::SetWindowOrg(double x, double y)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);

      return nullptr;

   }


   point_f64 graphics::offset_window_org(double nWidth, double nHeight)
   {

      __UNREFERENCED_PARAMETER(nWidth);

      __UNREFERENCED_PARAMETER(nHeight);

      return nullptr;

   }


   size_f64 graphics::set_window_ext(double x, double y)
   {

      __UNREFERENCED_PARAMETER(x);
      __UNREFERENCED_PARAMETER(y);

      return size_f64(0, 0);

   }


   size_f64 graphics::scale_window_ext(double xNum, double xDenom, double yNum, double yDenom)
   {

      __UNREFERENCED_PARAMETER(xNum);
      __UNREFERENCED_PARAMETER(xDenom);
      __UNREFERENCED_PARAMETER(yNum);
      __UNREFERENCED_PARAMETER(yDenom);

      return size_f64(0, 0);

   }


   //i32 graphics::get_clip_box(::rectangle_f64 * rectangle_i32)
   //{

   //   __UNREFERENCED_PARAMETER(rectangle);

   //   return -1;

   //}


   i32 graphics::get_clip_box(::rectangle_f64 & rectangle)
   {

      //::rectangle_f64 rectangle;

      //i32 iClip = get_clip_box(rectangle);

      //::copy_rect(prectangle, &rectangle);

      //return iClip;

      return 0;

   }


//   i32 graphics::ExcludeClipRect(double x1, double y1, double x2, double y2)
//   {
//
//      __UNREFERENCED_PARAMETER(x1);
//      __UNREFERENCED_PARAMETER(y1);
//      __UNREFERENCED_PARAMETER(x2);
//      __UNREFERENCED_PARAMETER(y2);
//
//      return -1;
//
//   }
//
//
//   i32 graphics::ExcludeClipRect(const ::rectangle_f64 & rectangle)
//   {
//
//      __UNREFERENCED_PARAMETER(rectangle);
//
//
//
//      return -1;
//
//   }
//
//
//   i32 graphics::IntersectClipRect(double x1, double y1, double x2, double y2)
//   {
//
//      ::rectangle_f64 rectangle;
//
//      rectangle.left = x1;
//      rectangle.top = y1;
//      rectangle.right = x2;
//      rectangle.bottom = y2;
//
//      return IntersectClipRect(rectangle);
//
//   }
//
//
//   i32 graphics::IntersectClipRect(const ::rectangle_f64 & rectangleParam)
//   {
//
//      auto pregion = __create < ::draw2d::region > ();
//
//      pregion->create_rect(rectangleParam);
//
//      if(m_pregion)
//      {
//
//         auto pregionOld = m_pregion;
//
//         __construct(m_pregion);
//
//         m_pregion->combine(pregionOld, pregion, ::draw2d::e_combine_intersect, this);
//
//      }
//      else
//      {
//
//         m_pregion = pregion;
//
//      }
//
//      //m_pregion->defer_update(this, 0);
//
//      on_apply_clip_region();
//
//      return 0;
//
//   }
//
//
//   i32 graphics::OffsetClipRgn(double x, double y)
//   {
//
//      if(m_pregion)
//      {
//
//         m_pregion->m_pointOffset += ::size_i32(x, y);
//
//         m_pregion->set_modified();
//
//         on_apply_clip_region();
//
//      }
//
//      return 0;
//
//   }
//
//
//   i32 graphics::OffsetClipRgn(const ::size_i32 & size)
//   {
//
//      return OffsetClipRgn(size.cx, size.cy);
//
//   }


   void graphics::on_apply_clip_region()
   {

   }


//   i32 graphics::OffsetClipRgn(const ::size_i32 & size)
//   {
//
//      throw ::not_implemented();
//      return 0;
//
//      /*
//       i32 nRetVal = ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
//       if(get_handle2() != nullptr)
//       nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
//       return nRetVal;
//       */
//   }
//   i32 graphics::OffsetClipRgn(double x, double y)
//   {
//
//      __UNREFERENCED_PARAMETER(x);
//      __UNREFERENCED_PARAMETER(y);
//
//
//
//      return -1;
//
//   }


//   i32 graphics::OffsetClipRgn(const ::size_i32 & size)
//   {
//
//      __UNREFERENCED_PARAMETER(size);
//
//
//
//      return -1;
//
//   }


   ::u32 graphics::SetTextAlign(::u32 nFlags)
   {
      __UNREFERENCED_PARAMETER(nFlags);

      return -1;
   }

   //i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
   //{
   //   __UNREFERENCED_PARAMETER(nBreakExtra);
   //   __UNREFERENCED_PARAMETER(nBreakCount);

   //   return -1;
   //}

   //i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
   //{
   //   __UNREFERENCED_PARAMETER(nCharExtra);

   //   return -1;
   //}

   //u32 graphics::SetMapperFlags(u32 dwFlag)
   //{
   //   __UNREFERENCED_PARAMETER(dwFlag);

   //   return -1;
   //}

   u32 graphics::GetLayout()
   {

      return -1;
   }

   u32 graphics::SetLayout(u32 dwSetLayout)
   {
      __UNREFERENCED_PARAMETER(dwSetLayout);

      return -1;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   void graphics::arc_to(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {
      __UNREFERENCED_PARAMETER(x1);
      __UNREFERENCED_PARAMETER(y1);
      __UNREFERENCED_PARAMETER(x2);
      __UNREFERENCED_PARAMETER(y2);
      __UNREFERENCED_PARAMETER(x3);
      __UNREFERENCED_PARAMETER(y3);
      __UNREFERENCED_PARAMETER(x4);
      __UNREFERENCED_PARAMETER(y4);

      //return false;
   }

   //i32 graphics::SetArcDirection(i32 nArcDirection)
   //{
   //   __UNREFERENCED_PARAMETER(nArcDirection);

   //   return -1;
   //}


   void graphics::polydraw(const ::point_f64 * ppoints, const byte* pTypes, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);
      __UNREFERENCED_PARAMETER(pTypes);
      __UNREFERENCED_PARAMETER(nCount);

      //return false;
   
   }


   void graphics::polyline_to(const ::point_f64 * ppoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);
      __UNREFERENCED_PARAMETER(nCount);

      //return false;

   }


   void graphics::poly_bezier_to(const ::point_f64 * ppoints, count nCount)
   {

      __UNREFERENCED_PARAMETER(ppoints);
      __UNREFERENCED_PARAMETER(nCount);

      //return false;

   }


   void graphics::SelectClipPath(i32 nMode)
   {

      __UNREFERENCED_PARAMETER(nMode);

      //return false;

   }


   void graphics::reset_clip()
   {
   
      //return ::success;
   
   }


   void graphics::add_clipping_shapes(const shape_array < ::draw2d::region > & shapea)
   {
      
      for(auto & pshape : shapea)
      {
         
         _add_clipping_shape(*pshape);
         
      }

      //return ::success;

   }


   void graphics::_add_clipping_shape(___shape < ::draw2d::region > & shape)
   {
   
      switch(shape.eshape())
      {
      case e_shape_none:
         return;
      case e_shape_intersect_clip:
         _intersect_clip();
         break;
      case e_shape_rectangle:
         _add_clipping_shape(shape.shape < ::rectangle >(), shape);
         break;
      case e_shape_ellipse:
         _add_clipping_shape(shape.shape < ::ellipse >(), shape);
         break;
//      case e_shape_lines:
//         return _add_shape(shape.shape < ::lines >());
      case e_shape_polygon:
         _add_clipping_shape(shape.shape < ::polygon >(), shape);
         break;
      default:
         throw ::exception(error_not_implemented);
         break;
      }

   }


   void graphics::_intersect_clip()
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void graphics::_add_clipping_shape(const ::rectangle_f64 & rectangle, ___shape < ::draw2d::region > & shape)
   {
   
      throw ::interface_only();
   
      //throw ::interface_only();
   
   }


   //void graphics::_add_shape(const ::rectangle_f64 & rectangle)
   //{
   //
   //   throw ::interface_only();
   //
   //   throw ::interface_only();
   //
   //}


   //void graphics::_add_shape(const ::ellipse & ellipse)
   //{
   //
   //   throw ::interface_only();
   //
   //   throw ::interface_only();
   //
   //}


   void graphics::_add_clipping_shape(const ::ellipse & ellipse, ___shape < ::draw2d::region > & shape)
   {
   
      throw ::interface_only();
   
      //throw ::interface_only();
   
   }


   //void graphics::_add_shape(const ::polygon_i32 & polygon_i32)
   //{
   //
   //   throw ::interface_only();
   //
   //   throw ::interface_only();
   //
   //}


   void graphics::_add_clipping_shape(const ::polygon_f64 & polygon, ___shape < ::draw2d::region > & shape)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void graphics::intersect_clip(const ::rectangle & rectangle)
   {
      
      _shape < ::rectangle, e_shape_rectangle, ::draw2d::region > regionshape;

      _add_clipping_shape(rectangle, regionshape);

   }


   void graphics::intersect_clip(const ::ellipse & ellipse)
   {
   
      _shape < ::ellipse, e_shape_ellipse, ::draw2d::region > regionshape;

      _add_clipping_shape(ellipse, regionshape);
   
   }


   void graphics::intersect_clip(const ::polygon & polygon)
   {

      _shape < ::polygon, e_shape_polygon, ::draw2d::region > regionshape;

      _add_clipping_shape(polygon, regionshape);

   }


//   void graphics::intersect_clip(const ::ellipse & ellipse)
//   {
//
//      throw interface_only();
////      //auto estatus =
////
////      ::pointer<::draw2d::region>pregion;
////
////      _add_clipping_shape(ellipse, pregion);
////
////      //if(!estatus)
////      //{
////      //
////      //   return estatus;
////      //
////      //}
////
////      //estatus =
////
////      _intersect_clip();
////
////      //if(!estatus)
////      //{
////      //
////      //   return estatus;
////      //
////      //}
////      //
////      //return estatus;
//
//   }


   //void graphics::intersect_clip(const ::polygon_i32 & polygon_i32)
   //{
   //
   //   auto estatus = _add_shape(polygon_i32);
   //   
   //   if(!estatus)
   //   {
   //    
   //      return estatus;
   //      
   //   }
   //   
   //   estatus = _intersect_clip();
   //   
   //   if(!estatus)
   //   {
   //    
   //      return estatus;
   //      
   //   }
   //   
   //   return estatus;
   //
   //}


//   void graphics::intersect_clip(const ::polygon_f64 & polygon)
//   {
//
//      ::pointer<::draw2d::region>pregion;
//
//      //auto estatus = 
//      _add_clipping_shape(polygon, pregion);
//      //
//      //if(!estatus)
//      //{
//      // 
//      //   return estatus;
//      //   
//      //}
//      //
//      //estatus =
//      _intersect_clip();
//      
//      //if(!estatus)
//      //{
//      // 
//      //   return estatus;
//      //   
//      //}
//      //
//      //return estatus;
//
//   }




//   i32 graphics::SelectClipRgn(::draw2d::region * pregion, enum_combine ecombine)
//   {
//
//      if(pregion != nullptr)
//      {
//
//         auto pregionOld = m_pregion;
//
//         __construct(m_pregion);
//
//         m_pregion->combine(pregionOld, pregion, ecombine);
//
//         m_pregion = pregion;
//
//      }
//
//      on_apply_clip_region();
//
//      return 0;
//
//   }


//#ifdef WINDOWS
//
//   void graphics::PlayMetaFile(HMETAFILE hMF)
//   {
//      __UNREFERENCED_PARAMETER(hMF);
//
//      return false;
//   }
//
//#endif

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(::size_f64 * psize)
   {

      __UNREFERENCED_PARAMETER(psize);

   }


   void graphics::DPtoLP(::size_f64 * psize)
   {

      __UNREFERENCED_PARAMETER(psize);

   }


   ::count graphics::get_character_extent(double_array & daLeft, double_array & daRight, const ::string & str, strsize iStart, strsize iCount)
   {

      daLeft.erase_all();

      daRight.erase_all();

      if (str.length() <= 0)
      {

         return 0;

      }

      if (iCount == 0)
      {

         return 0;

      }

      if (iStart < 0)
      {

         iStart = 0;

      }

      if (iStart > str.get_length())
      {

         return 0;

      }

      if (iCount < 0)
      {

         iCount = str.get_length() - iStart;

      }

      if (iStart + iCount > str.get_length())
      {

         iCount = str.get_length() - iStart;

         if (iCount <= 0)
         {

            return 0;

         }

      }

      iCount++;

      strsize iRange = 0;

      strsize iAsciiCharCount = 0;

      strsize iLen;

      const char * pszStart = str;

      const char * psz = pszStart;

      double dLeft = 0.0;

      while (*psz && iRange < iStart + iCount)
      {

         const char * pszNext = unicode_next(psz);

         if (pszNext == nullptr)
         {

            break;

         }

         iLen = pszNext - psz;

         iAsciiCharCount += iLen;

         daLeft.add(dLeft);

         dLeft = get_text_extent(str, iAsciiCharCount).cx;

         daRight.add(dLeft);

         iRange++;

         if (*pszNext == '\0')
         {

            break;

         }

         psz = pszNext;

      }

      return daLeft.get_size();

   }


   size_f64 graphics::GetTextBegin(const char * pszString, strsize nCount, strsize iIndex)
   {

      return get_text_extent(pszString, nCount, iIndex);

   }


   size_f64 graphics::get_text_extent(const char * pszString, strsize nCount, strsize iIndex)
   {

      return get_text_extent(pszString, iIndex);

   }


   size_f64 graphics::get_text_extent(const char * pszString, strsize nCount)
   {

      return get_text_extent(string(pszString, nCount));

   }


   size_f64 graphics::get_text_extent(const block & block)
   {
      
      ::size_f64 size;

      get_text_extent(size, (const char*)block.get_data(), block.get_size());

      return size;

   }


   void graphics::get_text_extent(size_f64 & size, const char * pszString, strsize nCount, strsize iIndex)
   {

      ::size_f64 sz = get_text_extent(string(pszString), nCount, iIndex);

      size.cx = sz.cx;
      size.cy = sz.cy;

      //return true;

   }


   void graphics::get_text_extent(size_f64 & size, const char * pszString, strsize nCount)
   {

      ::size_f64 sz = get_text_extent(string(pszString), nCount);

      size.cx = sz.cx;
      size.cy = sz.cy;

      //return true;

   }


   void graphics::get_text_extent(size_f64 & size, const ::string & str)
   {

      ::size_f64 sz = get_text_extent(str);

      size.cx = sz.cx;
      size.cy = sz.cy;

      //return true;

   }


   //size_f64 graphics::GetOutputTextExtent(const char * pszString, strsize nCount)
   //{

   //   __UNREFERENCED_PARAMETER(pszString);
   //   __UNREFERENCED_PARAMETER(nCount);

   //   return size_f64(0, 0);

   //}


   //size_f64 graphics::GetOutputTextExtent(const ::string & str)
   //{

   //   __UNREFERENCED_PARAMETER(str);

   //   return size_f64(0, 0);

   //}


   void graphics::draw_text(const ::string & str, const rectangle_f64 & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      ::rectangle_f64 rectangle(rectangleParam);

      _001DrawText(str, rectangle, ealign, edrawtext, false);

   }


   //void graphics::draw_text(const ::string & strParam, const ::rectangle_f64 & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   //{

   //   ::rectangle_f64 rectangle(rectangleParam);

   //   return _001DrawText(strParam, rectangle, ealign, edrawtext, false);

   //}


   void graphics::_001DrawText(const ::string & strParam, ::rectangle_f64 & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, bool bMeasure)
   {

      string str(strParam);

      size_f64 size = get_text_extent(str);

      double Δx;

      double Δy;

      if(ealign & e_align_right)
      {

         Δx = rectangleParam.right - rectangleParam.left - size.cx;

      }
      else if(ealign & e_align_horizontal_center)
      {

         Δx = ((rectangleParam.right - rectangleParam.left) - (size.cx)) / 2.0;

      }
      else
      {

         Δx = 0.;

      }

      if(ealign & e_align_bottom)
      {

         Δy = rectangleParam.bottom - rectangleParam.top - size.cy;

      }
      else if(ealign & e_align_vertical_center)
      {

         Δy = ((rectangleParam.bottom - rectangleParam.top) - (size.cy)) / 2.0;

      }
      else
      {

         Δy = 0.;

      }

      if(edrawtext & e_draw_text_expand_tabs)
      {

         str.replace_with("        ", "\t");

      }
      else
      {

         str.replace_with(" ", "\t");

      }

      if(edrawtext & e_draw_text_single_line)
      {

         str.replace_with("", "\r");

         str.replace_with("", "\n");

         text_out(rectangleParam.left + Δx, rectangleParam.top + Δy, str);

      }
      else
      {

         auto size = get_text_extent(str);

         string_array stra;

         stra.add_lines(str);

         int offsety = 0;

         for(auto & str : stra)
         {

            auto size1 = get_text_extent(str);

            text_out(rectangleParam.left + Δx, rectangleParam.top + Δy + offsety, str);

            offsety += (i32) size1.cy;

         }

      }

      //return 1;

   }


#ifndef _UWP


   void graphics::draw_text_ex(const ::string & str, const rectangle_f64 & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      __UNREFERENCED_PARAMETER(str);
      __UNREFERENCED_PARAMETER(rectangle);
      __UNREFERENCED_PARAMETER(ealign);
      __UNREFERENCED_PARAMETER(edrawtext);

      //return false;

   }


#endif



   void graphics::set_alpha_mode(enum_alpha_mode ealphamode)
   {

      m_ealphamode = ealphamode;

      //return true;

   }


   void graphics::set_smooth_mode(enum_smooth_mode esmoothmode)
   {

      m_esmoothmode = esmoothmode;

      //return true;

   }


   void graphics::set_interpolation_mode(enum_interpolation_mode einterpolationmode)
   {

      m_einterpolationmode = einterpolationmode;

      //return true;

   }


   void graphics::set_compositing_quality(enum_compositing_quality ecompositingquality)
   {

      m_ecompositingquality = ecompositingquality;

      //return true;

   }



   void graphics::set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint)
   {

      m_ewritetextrendering = etextrenderinghint;

      //return true;

   }


   enum_smooth_mode graphics::get_smooth_mode()
   {

      return m_esmoothmode;

   }


   void graphics::blur(bool bExpand, double dRadius, const ::rectangle_f64 & rectangle)
   {



      //return false;

   }


   void graphics::set_solid_pen(double dWidth, const ::color::color & color)
   {

      __defer_construct(m_ppen);

      m_ppen->create_solid(dWidth, color);

      //return true;

   }


   //memory_graphics::memory_graphics(enum_create) :
   //   graphics_pointer(e_create)
   //{

   //   m_p->CreateCompatibleDC(nullptr);

   //}


   //memory_graphics::~memory_graphics()
   //{

   //}


   double graphics::get_dpix()
   {

      return 96.0;

   }


   double graphics::get_dpiy()
   {

      return 96.0;

   }


   void graphics::set_fill_mode(::draw2d::enum_fill_mode efillmode)
   {

      m_efillmode = efillmode;

   }


   ::draw2d::enum_fill_mode graphics::get_fill_mode()
   {

      return m_efillmode;

   }


   void graphics::flush()
   {

      //return true;

   }


   void graphics::sync_flush()
   {

      return flush();

   }


   ::size_f64 graphics::get_size() const
   {

      if (::is_null(m_pimage))
      {

         return ::size_f64();

      }

      return m_pimage->get_size();

   }


   ::size_i32 graphics::get_image_drawer_size() const
   {

      return get_size();

   }


   //=============================================================================
   //
   // draw_round_rect()
   //
   // Purpose:     Draws a rounded rectangle_i32 with a solid pen
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          rectangle_i32        - [in]   Rect that defines the round rectangle_i32 boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //          width    - [in]  width of the border
   //
   // Returns:     None
   //


   void graphics::draw_round_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, double dRadius)
   {

      auto radius2 = dRadius * 2.0;

      if (radius2 > rectangle.width() || radius2 > rectangle.height())
      {

         return;

      }

      auto ppath = __create < ::draw2d::path >();

      ppath->add_round_rectangle(rectangle, dRadius, e_border_all);

      draw(ppath, ppen);

   }


   void graphics::draw_round_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::pen * ppen, double dRadius, const ::e_border & eborder)
   {

      if (eborder == e_border_all)
      {

         draw_round_rectangle(rectangle, ppen, dRadius);

         return;

      }
      else if (eborder & e_border_all)
      {

         auto radius2 = dRadius * 2.0;

         if (radius2 > rectangle.width() || radius2 > rectangle.height())
         {

            return;

         }

         auto ppath = __create < ::draw2d::path > ();

         ppath->add_round_rectangle(rectangle, dRadius, eborder);

         draw(ppath, ppen);

      }

      //return true;

   }


   //=============================================================================
   //
   // draw_round_rect()
   //
   // Purpose:     Draws a rounded rectangle_i32 with a solid pen
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          rectangle_i32        - [in]   Rect that defines the round rectangle_i32 boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //          width    - [in]  width of the border
   //
   // Returns:     None
   //
   //void graphics::draw_round_rect(const ::rectangle_f64 & rectangleParam, const ::color::color & color, double radius, const ::e_border & eborder)
   //{

   //   ::rectangle_f64 rectangle(rectangleParam);

   //   auto ppen = __create < ::draw2d::pen > ();

   //   ppen->create_solid(1.0, color);

   //   draw_round_rect(rectangle, pen, radius);

   //      rectangle.inflate(1, 0);

   //      draw_round_rect(rectangle, pen, radius);

   //      //rectangle.inflate(0, 1);

   //      //draw_round_rect(rectangle, pen, dia / 2);

   //   }

   //   return true;

   //}


   //void graphics::draw_round_top_left(const ::rectangle_f64 & rectangle, ::draw2d::pen  * ppen, i32 radius, const ::e_border & eborder)
   //{

   //   auto ppath = __create < ::draw2d::path > ();

   //   //ppath->begin_figure(false, ::draw2d::e_fill_mode_winding);

   //   ppath->begin_figure();

   //   ppath->add_round_top_left(rectangle, 2 * radius);

   //   ppath->close_figure();

   //   draw(ppath, ppen);

   //   return true;

   //}


   //void graphics::draw_round_top_left(const ::rectangle_f64 & rectangleParam, const ::color::color & color, i32 radius, double width, const ::e_border & eborder)
   //{

   //   ::rectangle_f64 rectangle(rectangleParam);

   //   i32 dia = 2 * radius;

   //   auto ppen = __create < ::draw2d::pen > ();

   //   ppen->create_solid(1.0, color);

   //   draw_round_top_left(rectangle, pen, radius);


   //   for (i32 i = 1; i<width; i++)
   //   {
   //      dia++;

   //      // left stroke
   //      rectangle.deflate(1, 0);

   //      draw_round_top_left(rectangle, pen, dia / 2);

   //      // up stroke
   //      rectangle.deflate(0, 1);

   //      draw_round_top_left(rectangle, pen, dia / 2);

   //   }

   //   return true;

   //}


   //void graphics::draw_round_bottom_right(const ::rectangle_f64 & rectangle, ::draw2d::pen  * ppen, i32 radius, const ::e_border & eborder)
   //{

   //   auto ppath = __create < ::draw2d::path > ();

   //   //ppath->begin_figure(false, ::draw2d::e_fill_mode_winding);

   //   ppath->begin_figure();

   //   ppath->add_round_bottom_right(rectangle, 2 * radius);

   //   //ppath->end_figure(false);

   //   ppath->close_figure();

   //   draw(ppath, ppen);

   //   return true;

   //}


   //void graphics::draw_round_bottom_right(const ::rectangle_f64 & rectangleParam, const ::color::color & color, i32 radius, double width, const ::e_border & eborder)
   //{

   //   ::rectangle_f64 rectangle(rectangleParam);

   //   i32 dia = 2 * radius;

   //   auto ppen = __create < ::draw2d::pen > ();

   //   ppen->create_solid(1.0, color);

   //   draw_round_bottom_right(rectangle, pen, radius);

   //   for (i32 i = 1; i<width; i++)
   //   {

   //      dia++;

   //      // left stroke
   //      rectangle.deflate(1, 0);

   //      draw_round_bottom_right(rectangle, pen, dia / 2);

   //      // up stroke
   //      rectangle.deflate(0, 1);

   //      draw_round_bottom_right(rectangle, pen, dia / 2);

   //   }

   //   return true;

   //}

   //=============================================================================
   //
   // fill_round_rect()
   //
   // Purpose:     Fills a rounded rectangle_i32 with a solid brush.  Draws the border
   //          first then fills in the rectangle.
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          rectangle_i32        - [in]   Rect that defines the round rectangle_i32 boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //
   // Returns:     None
   //
   void graphics::fill_round_rectangle(const ::rectangle_f64 & rectangle, const ::color::color & color, double radius)
   {

      auto pbrush = __create < ::draw2d::brush > ();

      pbrush->create_solid(color);

      return fill_round_rectangle(rectangle, pbrush, radius);

   }


   //=============================================================================
   //
   // fill_round_rect()
   //
   // Purpose:     Fills a rounded rectangle_i32 with a solid brush.  Draws the border
   //          first then fills in the rectangle.
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          pBrush      - [in]  pointer to a Brush
   //          rectangle_i32        - [in]   Rect that defines the round rectangle_i32 boundaries
   //          color    - [in]   Color value for the border (needed in case the
   //                         brush is a type other than solid)
   //          radius      - [in]  radius of the rounded corner
   //
   // Returns:     None
   //
   void graphics::fill_round_rectangle(const ::rectangle_f64 & rectangle, ::draw2d::brush * pbrush, double radius)
   {

      auto ppath = __create < ::draw2d::path > ();

      ppath->begin_figure();

      ppath->add_round_rectangle(rectangle, radius);

      ppath->close_figure();

      fill(ppath, pbrush);

   }


   void graphics::round_rectangle(const ::rectangle_f64 & rectangle, double radius)
   {

      fill_round_rectangle(rectangle, m_pbrush.m_p, radius);

      draw_round_rectangle(rectangle, m_ppen, radius);

   }


   i32 graphics::_DrawText(const string& strArg, const rectangle_f64 & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfontUnderlineParam)
   {

      string strParam(strArg);

      strParam = ::str().q_valid(strParam);

      if (strParam.is_empty())
      {

         return -1;

      }

      if (!m_pfont)
      {

         return -1;

      }

      m_pfont->get_os_data(this);

      string str(strParam);

      string str2;

      ::rectangle_f64 rectangleClip(rectangleParam);

      if (rectangleClip.area() <= 0)
      {

         return 0;

      }

      size_f64 sz;

      sz.cx = 0;

      sz.cy = 0;

      strsize iUnderline = -1;

      if(!(edrawtext & e_draw_text_no_prefix))
      {

         iUnderline = _EncodeV033(str);

      }

      strsize iLen = str.get_length();

      bool bLastLine = false;

      if((edrawtext & e_draw_text_word_break) != 0)
      {

         bLastLine = !word_break(this, str, rectangleClip, str, str2, (edrawtext & e_draw_text_end_ellipsis));

         auto & text = m_pfont->m_mapText[str];

         if (text.m_bSize)
         {

            sz = text.m_size;

         }
         else
         {

            sz = get_text_extent(str);

         }

      }
      else if ((edrawtext & e_draw_text_end_ellipsis) != 0)
      {

         auto & text = m_pfont->m_mapText[::string(str, iLen)];

         if (text.m_bSize)
         {

            sz = text.m_size;

         }
         else
         {

            sz = get_text_extent(::string(str, iLen));

         }

         if (sz.cx > rectangleClip.width())
         {

            const char * pszStart = str;

            const char * psz = pszStart;

            string strLastSample = "...";

            string strSample;

            while (true)
            {

               unicode_increment(psz);

               strSample = string(pszStart, psz - pszStart) + "...";

               sz = get_text_extent(strSample);

               if (sz.cx > rectangleClip.width())
               {

                  str = strLastSample;

                  break;

               }

               strLastSample = strSample;

            }

         }

      }
      else
      {

         auto & text = m_pfont->m_mapText[str];

         if (text.m_bSize)
         {

            sz = text.m_size;

         }
         else
         {

            sz = get_text_extent(str);

         }

         if (sz.cx > rectangleClip.width())
         {

            strsize i = iLen;

            if (i < 0)
            {

               i = 0;

            }

            char * psz = str.get_string_buffer(maximum(0, i));

            while (i > 0)
            {

               sz = get_text_extent(str, (i32)i);

               if ((int) sz.cx > rectangleClip.width())
               {

                  i = unicode_prior_index(i, str);

                  if (i <= 0)
                  {

                     break;

                  }

               }
               else
               {

                  break;

               }

            }

            psz[i] = L'\0';

            str.release_string_buffer();

         }

      }

      if (str.is_empty())
      {

         return 0;

      }

      ::write_text::font_pointer pfontUnderline(pfontUnderlineParam);

      if (iUnderline >= 0)
      {

         if (!pfontUnderline)
         {

            pfontUnderline.create(this);

            pfontUnderline->operator=(*get_current_font());

            pfontUnderline->set_bold();

         }

      }

      //double dLineSpacing = m_pfont->m_textmetric2.get_line_spacing();

      //::draw2d::graphics * pgraphics = this;

      //wstring wstr = utf8_to_unicode(strParam);

      ::rectangle_f64 rectangle;

      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.right =  sz.cx;
      rectangle.bottom = sz.cy;
      //rectangle.bottom = (::i32) (dLineSpacing);

      //::e_align ealign;

      //if (ealig & e_align_bottom)
      //{
      //   
      //   ealign |= ::e_align_bottom;

      //}
      //else if (uiFormat & e_align_vertical_center)
      //{
      //   
      //   ealign |= ::e_align_vertical_center;

      //}
      //else
      //{
      //   
      //   ealign |= ::e_align_top;

      //}

      //if (uiFormat & e_align_right)
      //{
      //   
      //   ealign |= ::e_align_right;

      //}
      //else if (uiFormat & e_align_horizontal_center)
      //{

      //   ealign |= ::e_align_horizontal_center;

      //}
      //else
      //{

      //   ealign |= ::e_align_left;

      //}

      rectangle.Align(ealign, rectangleParam);

      if (iUnderline >= 0 && iUnderline < str.get_length())
      {

         text_out(rectangle.left, rectangle.top, { str.c_str(), (i32)minimum(iUnderline, str.get_length()) });
         /*::TextOutU(
         (HDC)pgraphics->get_os_data(),
         rectangle.left,
         rectangle.top,
         str,
         minimum(iUnderline, str.get_length()));*/
         if (iUnderline <= str.get_length())
         {
            set(pfontUnderline);
            /*::GetTextExtentPoint32U(
            (HDC)pgraphics->get_os_data(),
            str,
            iUnderline,
            &sz);*/
            
            sz = get_text_extent(str, (i32)iUnderline);

            char wch = str[iUnderline];
            /*::TextOutU(
            (HDC)pgraphics->get_os_data(),
            rectangle.left + sz.cx,
            rectangle.top,
            &wch,
            1);*/
            
            text_out(rectangle.left + sz.cx, (double)rectangle.top, { &wch, 1 });

            if (iUnderline + 1 <= str.get_length())
            {

               sz = get_text_extent(str, (i32)(iUnderline + 1));
               /*::GetTextExtentPoint32U(
               (HDC)pgraphics->get_os_data(),
               str,
               iUnderline + 1,
               &sz);*/
               
               strsize iCount = str.get_length() - iUnderline - 1;

               text_out(rectangle.left + sz.cx, (double)rectangle.top, { str.Right(iCount).c_str(), (i32)iCount });

               /*::TextOutU(
               (HDC)pgraphics->get_os_data(),
               rectangle.left + sz.cx,
               rectangle.top,
               str.Right(iCount),
               iCount);*/

            }

         }

      }
      else
      {

         text_out(rectangle.left, rectangle.top, str);

      }

      if (!bLastLine && str2.get_length() > 0)
      {

         rectangleClip.top = rectangleClip.top+sz.cy;

         _DrawText(str2, rectangleClip, ealign, edrawtext);

      }

      return 1;

   }


   bool word_break(::draw2d::graphics * pgraphics, const ::string & strSource, const rectangle_i32 & rectangleParam, string &str1, string & str2, int iEll)
   {

      ::rectangle_f64 rectangle(rectangleParam);

      string str;

      ::rectangle_f64 rectangleClip(rectangle);

      const char * pszSource = strSource;

      strsize len = strSource.get_length();

      const char * pszEnd = pszSource + len;

      const char * pszStart = unicode_next(pszSource);

      size_i32 sz;

      const char * pszSpaceStart = nullptr;

      const char * pszSpaceEnd = nullptr;

      const char * psz = pszStart;

      const char * pszPrevious = pszSource;

      string strChar;

      double dNewY;

      bool bLastLine = false;

      bool bEnd = false;

      auto y = rectangle.top;

      while(psz <= pszEnd)
      {

         sz = pgraphics->get_text_extent(pszSource, psz - pszSource);

         dNewY = y + sz.cy;

         if(dNewY + sz.cy > rectangle.bottom)
         {

            bLastLine = true;


            str = strSource;

            strsize iLen = str.length();

            sz = pgraphics->get_text_extent(str,(i32)iLen);


            if(sz.cx > rectangleClip.width())
            {

               strsize iSampleLen = strSource.get_length();

               while(iSampleLen > 0)
               {

                  iSampleLen--;

                  str = strSource.Left(iSampleLen) + "...";

                  sz = pgraphics->get_text_extent(str);

                  if(sz.cx < rectangleClip.width())
                  {

                     break;

                  }

               }

            }

            str1 = str;

            rectangle.top = y;

            return false;


         }

         if(unicode_is_space_char(pszPrevious))
         {

            pszSpaceStart       = pszPrevious;

            do
            {

               pszSpaceEnd      = psz;

               if(!unicode_is_space_char(psz))
               {

                  break;

               }

               pszPrevious      = psz;

               unicode_increment(psz);

            }
            while(psz != nullptr);

         }

         if (sz.cx > rectangleClip.width())
         {

            if(psz == pszStart)

            {
               pszEnd = pszStart;

               break;
            }

            if(pszSpaceStart != nullptr)
            {

               // "legit" word break, i.meaning., found mid space in text and split there, instead of slicing a full word in a single-character (above) or the maximum-unclipped (below).
               psz = pszSpaceStart;

               pszEnd = pszSpaceEnd;

               break;
            }

            unicode_decrement(psz, pszSource);

            pszEnd = psz;

            break;

         }

         pszPrevious = psz;

         unicode_increment(psz);

         if(bEnd)
         {
            
            break;

         }
         else
         {

            bEnd = psz >= pszEnd;

         }

      }

      str1 = string(pszSource, psz - pszSource);


      str2 = string(pszEnd);


      rectangle.top = y;

      return true;

   }


   strsize _EncodeV033(string & str)
   {
      strsize iStart = 0;
      strsize iIndex;
      strsize iLen = str.get_length();
      while (true)
      {
         iIndex = str.find(L'&', iStart);
         if (iIndex < 0)
            break;
         if (iIndex + 1 >= iLen)
            break;
         if (str[iIndex + 1] == L'&')
         {
            iIndex++;
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
         }
         else
         {
            // Found !
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
            return iIndex;
         }

         if (iIndex >= str.get_length())
            break;
      }
      // Not Found
      return -1;
   }




   void graphics::draw_stock_icon(const ::rectangle_f64 & rectangleParam, enum_stock_icon estockicon)
   {

      ::rectangle_f64 rectangle(rectangleParam);

      if(estockicon == e_stock_icon_close)
      {

         rectangle.deflate(rectangle.width() / 7.0, rectangle.height() / 7.0);

//         m_ppen->m_dWidth *= 2.0;
//         m_ppen->set_modified();

         ::pointer<::draw2d::path>ppath;

         __construct(ppath);

         ppath->begin_figure();
         ppath->add_line(rectangle.top_left(), rectangle.bottom_right());
         ppath->end_figure();
         ppath->begin_figure();
         ppath->add_line(rectangle.bottom_left(), rectangle.top_right());
         ppath->end_figure();

         draw(ppath);

      }
      else if(estockicon == e_stock_icon_zoom)
      {

         rectangle.deflate(0, rectangle.height() / 7.0);

         draw_rectangle(rectangle);

         //m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_flat;
         //m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_flat;
         //set_current_point(rectangle.top_left() + ::size_i32(0,(::i32) (ppen->m_dWidth/2.0)));
         //line_to(rectangle.top_right() + ::size_i32(0,(::i32)(ppen->m_dWidth / 2.0)));
         //set_current_point(rectangle.top_left() + ::size_i32(0,(::i32)(ppen->m_dWidth)));
         //line_to(rectangle.top_right() + ::size_i32(0,(::i32)(ppen->m_dWidth)));
         //set_current_point(rectangle.top_left() + ::size_i32(0,(::i32)(ppen->m_dWidth *3.0 / 2.0)));
         //line_to(rectangle.top_right() + ::size_i32(0,(::i32)(ppen->m_dWidth *3.0 / 2.0)));
         //set_current_point(rectangle.top_left() + ::size_i32(0,(::i32)(ppen->m_dWidth*2.0)));
         //line_to(rectangle.top_right() + ::size_i32(0,(::i32)(ppen->m_dWidth*2.0)));

      }
      else if(estockicon == e_stock_icon_restore)
      {

         rectangle.deflate(0, rectangle.height() / 7.0);

         ::rectangle_f64 rect1(rectangle);

         rect1.deflate(0, 0, rectangle.width() / 3.0, rectangle.height() / 3.0);

         ::rectangle_f64 rect2(rect1);

         rect2.Align(e_align_bottom_right, rectangle);

         draw_rectangle(rect2);

         m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_flat;
         m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_flat;
         set_current_point(rect2.top_left() + ::size_f64(0.,(m_ppen->m_dWidth / 2.0)));
         line_to(rect2.top_right() + ::size_f64(0.,(m_ppen->m_dWidth / 2.0)));
         set_current_point(rect2.top_left() + ::size_f64(0.,(m_ppen->m_dWidth)));
         line_to(rect2.top_right() + ::size_f64(0.,(m_ppen->m_dWidth)));


         set_current_point(rect1.top_left());
         line_to(rect1.top_right());
         set_current_point(rect1.top_left() + ::size_f64(0.,(m_ppen->m_dWidth / 2.0)));
         line_to(rect1.top_right() + ::size_f64(0.,(m_ppen->m_dWidth / 2.0)));
         set_current_point(rect1.top_left() + ::size_f64(0.,(m_ppen->m_dWidth)));
         line_to(rect1.top_right() + ::size_f64(0.,(m_ppen->m_dWidth)));



         m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_square;
         m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_square;
         m_ppen->set_modified();

         set_current_point(rect1.top_left() + ::size_f64(0,(m_ppen->m_dWidth)));
         line_to(rect1.bottom_left());
         line_to(rect2.bottom_left());

         set_current_point(rect1.top_right() + ::size_f64(0,(m_ppen->m_dWidth)));
         line_to(point_f64(rect1.right,(int)(rect2.top - (m_ppen->m_dWidth))));

      }
      else if(estockicon == e_stock_icon_iconify)
      {


         rectangle.deflate(0, rectangle.height() / 7.0);

         set_current_point(rectangle.bottom_left());
         line_to(rectangle.bottom_right());
         //set_current_point(rectangle.bottom_left() - ::size_i32(0,(::i32)(m_ppen->m_dWidth*2.0)));
         //line_to(rectangle.bottom_right() - ::size_i32(0,(::i32)(m_ppen->m_dWidth*2.0)));
         //set_current_point(rectangle.bottom_left() - ::size_i32(0,(::i32)(m_ppen->m_dWidth*3.0 / 2.0)));
         //line_to(rectangle.bottom_right() - ::size_i32(0,(::i32)(m_ppen->m_dWidth*3.0 / 2.0)));
         //set_current_point(rectangle.bottom_left() - ::size_i32(0,(::i32)(m_ppen->m_dWidth)));
         //line_to(rectangle.bottom_right() - ::size_i32(0,(::i32)(m_ppen->m_dWidth)));
         //set_current_point(rectangle.bottom_left() - ::size_i32(0,(::i32)(m_ppen->m_dWidth / 2.0)));
         //line_to(rectangle.bottom_right() - ::size_i32(0,(::i32)(m_ppen->m_dWidth / 2.0)));
         //set_current_point(rectangle.bottom_left());
         //line_to(rectangle.bottom_right());

      }
      else if(estockicon == e_stock_icon_transparent_frame)
      {

      }
      else if(estockicon == e_stock_icon_dock)
      {

         rectangle.deflate(rectangle.height() / 8.0, rectangle.height() / 8.0);

         draw_ellipse(rectangle);

         ::rectangle_f64 rect1(rectangle);

         rect1.deflate((i32)(m_ppen->m_dWidth / 2.0),(i32)(m_ppen->m_dWidth / 2.0));

         draw_ellipse(rect1);

         ::rectangle_f64 rect2(rectangle);

         rect2.deflate((i32)(m_ppen->m_dWidth),(i32)(m_ppen->m_dWidth));

         draw_ellipse(rect2);

      }
      else if (estockicon == e_stock_icon_notify)
      {

         rectangle.deflate(rectangle.height() / 2.0, rectangle.height() / 2.0);

         draw_ellipse(rectangle);

         ::rectangle_f64 rect1(rectangle);

         rect1.deflate((i32)(m_ppen->m_dWidth / 2.0), (i32)(m_ppen->m_dWidth / 2.0));

         draw_ellipse(rect1);

         ::rectangle_f64 rect2(rectangle);

         rect2.deflate((i32)(m_ppen->m_dWidth), (i32)(m_ppen->m_dWidth));

         draw_ellipse(rect2);

      }
      else if (estockicon == e_stock_icon_level_up)
      {

         rectangle.deflate(rectangle.height() / 3.0, rectangle.height() / 3.0);

         point_f64_array pointa;

         pointa.add(rectangle.bottom_left());

         pointa.add(rectangle.bottom_right());

         pointa.add((rectangle.right + rectangle.left) / 2.0, rectangle.top);

         polygon(pointa);

      }
      else if (estockicon == e_stock_icon_level_down)
      {

         rectangle.deflate(rectangle.height() / 3.0, rectangle.height() / 3.0);

         point_f64_array pointa;

         pointa.add(rectangle.top_left());

         pointa.add(rectangle.top_right());

         pointa.add((rectangle.right + rectangle.left) / 2.0, rectangle.bottom);

         polygon(pointa);

      }
      else
      {

         throw ::interface_only();

      }

      //return true;

   }


   void graphics::debug()
   {
   }


   void graphics::draw_error_line(double x1, double h, double x2, i32 iStyle)
   {

      int iR = m_ppen->m_color.red;
      int iG = m_ppen->m_color.green;
      int iB = m_ppen->m_color.blue;
      int iA = m_ppen->m_color.alpha;

      if(iStyle == 0)
      {

         draw_line({ x1, h }, { x2, h });

      }
      else
      {

         ::image_pointer pimage;

         double w = x2 - x1 + 1;

         //auto estatus = 
         
         __construct(pimage);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 
         
         pimage->create({ (i32)w, 6 });

         //if (!estatus || pimage->area() <= 0)
         if(pimage->area() <= 0)
         {

            throw ::exception(error_failed);

         }

         pimage->fill(0, 0, 0, 0);

         double dStep = 0.125;
         double dPeriod = 7.0;
         double dTint;
         double dHalfH = 1.33;
         double dHSpan = 0.7;
         double dH = 2.5;
         double dCurl = 2.3;
         double dBaseTint = 2.0;
         double dCircleX;
         double dCircleY;

         pimage->map();

         auto colorref = pimage->colorref();

         auto scan = pimage->scan_size();

         auto wscan = scan / sizeof(::color32_t);

         for (double Δx = 0; Δx < w; Δx += dStep)
         {
            dCircleX = fmod(Δx, (double)(dPeriod));
            double dSign = dCircleX < (dPeriod / 2.0) ? 1.0 : -1.0;
            dCircleX -= dPeriod / 2.0;
            dTint = dBaseTint * 0.51;
            dCircleY = dSign * sqrt(dPeriod * dPeriod / 4.0 - dCircleX * dCircleX) * 0.05;
            {
               double Δy = (sin((double)Δx * 2.0 * 3.1415 / dPeriod) - fmod(Δx, (double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               ;
               Δy = (Δy * dHalfH + dH - dHSpan);
               int x = (int)round(Δx);
               int y = (int)round(Δy);
               if (x < 0 || y < 0 || x >= pimage->width() || y >= pimage->height())
               {
               }
               else
               {
                  int A = (colorref[x + wscan * y] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(Δy), 1.0);
                  double fx = 1.0 - fmod(fabs(Δx), 1.0);
                  A = (int)(A + ((fx * fy) * 255.0 * dStep * dTint));
                  A = minimum(A, 255);
                  colorref[x + wscan * y] = argb((A * iA) / 255, iB, iG, iR);
               }
            }
            dTint = dBaseTint * 0.51;
            {
               double Δy = (sin((double)Δx * 2.0 * 3.1415 / dPeriod) - fmod(Δx, (double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               Δy = (Δy * dHalfH + dH + dHSpan);
               int x = (int)round(Δx);
               int y = (int)round(Δy);
               if (x < 0 || y < 0 || x >= pimage->width() || y >= pimage->height())
               {
               }
               else
               {
                  int A = (colorref[x + wscan * y] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(Δy), 1.0);
                  double fx = 1.0 - fmod(fabs(Δx), 1.0);
                  A = (int)(A + ((fx * fy) * 255.0 * dStep * dTint));
                  A = minimum(A, 255);
                  colorref[x + wscan * y] = argb((A * iA) / 255, iB, iG, iR);
               }

            }

            dTint = dBaseTint * 2.3;

            {
               double Δy = (sin((double)Δx * 2.0 * 3.1415 / dPeriod) - fmod(Δx, (double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               Δy = (Δy * dHalfH + dH);
               int x = (int)round(Δx);
               int y = (int)round(Δy);
               if (x < 0 || y < 0 || x >= pimage->width() || y >= pimage->height())
               {
               }
               else
               {
                  int A = (colorref[x + wscan] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(Δy), 1.0);
                  double fx = 1.0 - fmod(fabs(Δx), 1.0);
                  A = (int)(A + ((fx * fy) * 255.0 * dStep * dTint));
                  A = minimum(A, 255);
                  colorref[x + wscan * y] = argb((A * iA) / 255, iB, iG, iR);

               }

            }

         }

         set_alpha_mode(::draw2d::e_alpha_mode_blend);

         auto rectangleTarget = ::rectangle_f64(::point_f64(x1, h), pimage->size());

         {

            image_source imagesource(pimage);

            rectangle_f64 rectangle(rectangleTarget);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            draw(imagedrawing);

         }

      }

      //return true;

   }


   void graphics::draw_ca2_with_border2(int x, int y, int z, int bOut, int bIn, const ::color::color & colorBk, const ::color::color & color, const ::color::color & colorOut, const ::color::color & colorIn)
   {

      draw_ca2(x + bIn + bOut, y + bIn + bOut, z, colorBk, color);

      draw_ca2_border2(x, y, z, bOut, bIn, colorBk, color, colorOut, colorIn);

   }


   void graphics::draw_ca2_with_border(int x, int y, int z, int b, const ::color::color & colorBk, const ::color::color & color, const ::color::color & colorBorder)
   {

      draw_ca2(x + b, y + b, z, colorBk, color);

      int w = z / 19;

      if (w < 1)
      {

         w = 1;

      }

      z = w * 19;

      ::rectangle_i32 rectangle(x + b, y + b, x + b + z, y + b + z);

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, colorBorder);

      for(int i = 0; i < b; i++)
      {

         rectangle.inflate(1,1);

         draw_rectangle(rectangle, ppen);

      }

   }


   ::file::path graphics::get_font_path(const ::string & strName, int iWeight, bool bItalic)
   {

      auto penumeration = acmesystem()->m_paurasystem->draw2d()->write_text()->fonts()->enumeration();

      penumeration->m_eventReady.wait(30_s);

      critical_section_lock synchronouslock(&acmesystem()->m_paurasystem->draw2d()->write_text()->m_csFont);

      string strFontName(strName);

      strFontName.make_lower();

      string strPath = acmesystem()->m_paurasystem->draw2d()->write_text()->m_mapFontKeyFaceName[strFontName][iWeight * 10 + (bItalic ? 1 : 0)];

      return strPath;

   }


   bool graphics::fill_contains(const point_f64 & point)
   {

      throw ::not_implemented();

      return false;

   }


   void graphics::draw_ca2(int x, int y, int z, const ::color::color & colorBk, const ::color::color & color)
   {

      ::draw2d::brush_pointer b(e_create, this);

      // black rectangle_i32

      int w = z / 19;

      if(w < 1)
         w = 1;

      z = w * 19;

      b->create_solid(colorBk);

      ::rectangle_i32 rectangle(x, y, x + z, y + z);

      fill_rectangle(rectangle, b);

      // bottom line

      b->create_solid(color);

      rectangle.top += w * 13;
      rectangle.bottom -= w;


      // c

      rectangle.left += w;
      rectangle.right = rectangle.left + w * 5;

      ::rectangle_f64 rect2(rectangle);

      // c vertical

      rect2.right = rect2.left + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.bottom = rect2.top + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.top = rect2.bottom - w;

      fill_rectangle(rect2, b);


      // a

      rectangle.left += w * 6;
      rectangle.right = rectangle.left + w * 5;

      rect2 = rectangle;

      rect2.bottom = rect2.top + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.top = rect2.bottom - w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.right = rect2.left + w * 2;
      rect2.top += w * 2;
      rect2.bottom = rect2.top + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.left += w * 5 / 2;
      rect2.right = rect2.left + w;
      rect2.top += w * 2;
      rect2.bottom = rect2.top + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.left = rect2.right - w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.right = rect2.left + w;
      rect2.top += w * 2;

      fill_rectangle(rect2, b);





      // 2

      rectangle.left += w * 6;
      rectangle.right = rectangle.left + w * 5;

      rect2 = rectangle;

      rect2.bottom = rect2.top + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.top = rect2.bottom - w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.top += w * 2;
      rect2.bottom = rect2.top + w;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.right = rect2.left + w;
      rect2.top += w * 2;

      fill_rectangle(rect2, b);

      rect2 = rectangle;

      rect2.left = rect2.right - w;
      rect2.bottom -= w * 2;

      fill_rectangle(rect2, b);

   }


   void graphics::draw_ca2_border2(int x, int y, int z, int bOut, int bIn, const ::color::color & colorBk, const ::color::color & color, const ::color::color & colorOut, const ::color::color & colorIn)
   {
      int w = z / 19;

      if(w < 1)
         w = 1;

      z = w * 19;

      ::rectangle_i32 rectangle(x + bIn + bOut, y + bIn + bOut, x + bIn + bOut + z - 1, y + bIn + bOut + z - 1);

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, colorIn);

      for(int i = 0; i < bIn; i++)
      {

         rectangle.inflate(1,1);

         draw_rectangle(rectangle, ppen);

      }

      ppen->create_solid(1.0, colorOut);

      for(int i = 0; i < bOut; i++)
      {

         rectangle.inflate(1,1);

         draw_rectangle(rectangle, ppen);

      }

   }


   //void graphics::enum_fonts(::write_text::font_enumeration_item_array & itema)
   //{

   //   __UNREFERENCED_PARAMETER(itema);



   //}


   //void graphics::sorted_fonts(::write_text::font_enumeration_item_array & itema)
   //{

   //   enum_fonts(itema);

   //   ::sort::array::predicate_sort(itema, [&](auto & a, auto & b)
   //   {

   //      return a->m_strName < b->m_strName;

   //   });

   //}


   float graphics::nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy)
   {

      float pqx, pqy, Δx, Δy, d, t;
      pqx = qx - px;
      pqy = qy - py;
      Δx = x - px;
      Δy = y - py;
      d = pqx*pqx + pqy*pqy;
      t = pqx*Δx + pqy*Δy;
      if (d > 0) t /= d;
      if (t < 0) t = 0;
      else if (t > 1) t = 1;
      Δx = px + t*pqx - x;
      Δy = py + t*pqy - y;
      return Δx*Δx + Δy*Δy;

   }


   void graphics::nanosvg_cubicBez(float x1, float y1, float x2, float y2,
                                   float x3, float y3, float x4, float y4,
                                   float tol, int level)
   {
      float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
      float d;

      if (level > 12) return;

      x12 = (x1 + x2)*0.5f;
      y12 = (y1 + y2)*0.5f;
      x23 = (x2 + x3)*0.5f;
      y23 = (y2 + y3)*0.5f;
      x34 = (x3 + x4)*0.5f;
      y34 = (y3 + y4)*0.5f;
      x123 = (x12 + x23)*0.5f;
      y123 = (y12 + y23)*0.5f;
      x234 = (x23 + x34)*0.5f;
      y234 = (y23 + y34)*0.5f;
      x1234 = (x123 + x234)*0.5f;
      y1234 = (y123 + y234)*0.5f;

      d = nanosvg_distPtSeg(x1234, y1234, x1, y1, x4, y4);
      if (d > tol*tol)
      {
         nanosvg_cubicBez(x1, y1, x12, y12, x123, y123, x1234, y1234, tol, level + 1);
         nanosvg_cubicBez(x1234, y1234, x234, y234, x34, y34, x4, y4, tol, level + 1);
      }
      else
      {

         line_to(point_f64(x4, y4));

      }

   }


   void graphics::nanosvg_drawPath(float* pts, int npts, char closed, float tol, const ::color::color & color)
   {

      int i;

      begin_path();

      set_current_point(point_f64(pts[0], pts[1]));

      for (i = 0; i < npts - 1; i += 3)
      {

         float* p = &pts[i * 2];

         nanosvg_cubicBez(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], tol, 0);

      }

      if (closed)
      {

         set_current_point(point_f64(pts[0], pts[1]));

      }

      end_path();

   }


   void graphics::nanosvg_drawControlPts(float* pts, int npts)
   {

      int i;

      // Control lines
      //glColor4ubv(lineColor);
      //glBegin(GL_LINES);
      begin_path();

      for (i = 0; i < npts - 1; i += 3)
      {

         float * p = &pts[i * 2];

         set_current_point(::point_i32((::i32)p[0], (::i32)p[1]));
         line_to(::point_i32((::i32)p[2], (::i32)p[3]));
         line_to(::point_i32((::i32)p[4], (::i32)p[5]));
         line_to(::point_i32((::i32)p[6], (::i32)p[7]));

      }

      end_path();

      // Points
      //glPointSize(6.0f);
      //glColor4ubv(lineColor);

      //glBegin(GL_POINTS);
      //glVertex2f(pts[0], pts[1]);
      //for (i = 0; i < npts - 1; i += 3) {
      // float* point = &pts[i * 2];
      //glVertex2f(point_i32[6], point_i32[7]);
      //}
      //glEnd();

      // Points
      //glPointSize(3.0f);

      //glBegin(GL_POINTS);
      //glColor4ubv(bgColor);
      //glVertex2f(pts[0], pts[1]);
      //for (i = 0; i < npts - 1; i += 3) {
      //   float* point = &pts[i * 2];
      //   glColor4ubv(lineColor);
      //   glVertex2f(point_i32[2], point_i32[3]);
      //   glVertex2f(point_i32[4], point_i32[5]);
      //   glColor4ubv(bgColor);
      //   glVertex2f(point_i32[6], point_i32[7]);
      //}
      //glEnd();

   }


   void graphics::nanosvg_drawframe(NSVGimage* pnsvgimage, int x, int y, int width, int height)
   {

      float impact[4], cx, cy, hw, hh, aspect, px;

      NSVGshape* pnsvgshape;

      NSVGpath* pnsvgpath;

      //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      //glfwGetFramebufferSize(window, &width, &height);

      //glContext(0, 0, width, height);

      int n=SaveDC();

      offset_origin(x, y);

      //glClearColor(220.0f / 255.0f, 220.0f / 255.0f, 220.0f / 255.0f, 1.0f);
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glDisable(GL_TEXTURE_2D);
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();

      // Fit impact to bounds
      cx = pnsvgimage->width * 0.5f;
      cy = pnsvgimage->height * 0.5f;
      hw = pnsvgimage->width * 0.5f;
      hh = pnsvgimage->height * 0.5f;

      if (width / hw < height / hh)
      {
         aspect = (float)height / (float)width;
         impact[0] = cx - hw * 1.2f;
         impact[2] = cx + hw * 1.2f;
         impact[1] = cy - hw * 1.2f * aspect;
         impact[3] = cy + hw * 1.2f * aspect;
      }
      else
      {
         aspect = (float)width / (float)height;
         impact[0] = cx - hh * 1.2f * aspect;
         impact[2] = cx + hh * 1.2f * aspect;
         impact[1] = cy - hh * 1.2f;
         impact[3] = cy + hh * 1.2f;
      }
      // Size of one pixel.
      px = (impact[2] - impact[1]) / (float)width;

      //glOrtho(impact[0], impact[2], impact[3], impact[1], -1, 1);

      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();
      //glDisable(GL_DEPTH_TEST);
      //glColor4ub(255, 255, 255, 255);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      // Draw bounds
      //glColor4ub(0, 0, 0, 64);
      //glBegin(GL_LINE_LOOP);
      //glVertex2f(0, 0);
      //glVertex2f(pnsvgimage->width, 0);
      //glVertex2f(pnsvgimage->width, pnsvgimage->height);
      //glVertex2f(0, pnsvgimage->height);
      //glEnd();

      auto ppen = __create < ::draw2d::pen > ();

      ppen->create_solid(1.0, argb(255, 0, 128, 0));

      set(ppen);

      for (pnsvgshape = pnsvgimage->shapes; pnsvgshape != nullptr; pnsvgshape = pnsvgshape->next)
      {

         for (pnsvgpath = pnsvgshape->paths; pnsvgpath != nullptr; pnsvgpath = pnsvgpath->next)
         {

            nanosvg_drawPath(pnsvgpath->pts, pnsvgpath->npts, pnsvgpath->closed, px / 3.0f, argb(255, 0, 128, 0));

//            nanosvg_drawControlPts(ppath->pts, ppath->npts);

         }

      }

      //glfwSwapBuffers(window);

      RestoreDC(n);

   }

   //void graphics::nanosvg_resizecb(int width, int height)
   //{
   //   // Update and render
   //   NSVG_NOTUSED(width);
   //   NSVG_NOTUSED(height);
   //   //drawframe(window);
   //}


   void graphics::nanosvg(string str, int x, int y, int w, int h)
   {

      struct NSVGimage* pnsvgimage;

      pnsvgimage = nsvgParse((char *) (const char *) str, "px", 96);

      nanosvg_drawframe(pnsvgimage, x, y, w, h);

      nsvgDelete(pnsvgimage);

      //return true;

   }



   void graphics::is_valid_update_window_thread()
   {

      //return true;

   }


   void graphics::on_begin_draw(oswindow wnd, const size_f64 & sz)
   {

   }


   void graphics::on_end_draw(oswindow wnd)
   {


   }

   
   savedc::savedc(graphics * pgraphics)
   {
      
      m_pgraphics = pgraphics;
      
      try
      {
         
         if (m_pgraphics != nullptr)
         {
            
            m_iSavedDC = m_pgraphics->SaveDC();
            m_sizeScaling = pgraphics->m_sizeScaling;
            m_pointOrigin = pgraphics->m_pointOrigin;
            m_matrix = pgraphics->m_matrix;
            
         }
         
      }
      catch (...)
      {

      }
      
   }


   savedc::~savedc()
   {

      try
      {

         if (m_pgraphics != nullptr)
         {

            m_pgraphics->RestoreDC(m_iSavedDC);
            m_pgraphics->m_sizeScaling = m_sizeScaling;
            m_pgraphics->m_matrix = m_matrix;
            m_pgraphics->m_pointOrigin = m_pointOrigin;
            m_pgraphics->update_matrix();

         }

      }
      catch (...)
      {

      }

   }


   void graphics::_get(matrix & matrix)
   {

      //return false;

   }


   void graphics::_set(const matrix & matrix)
   {

      //return false;

   }


   void graphics::get(matrix & matrix)
   {

      matrix = m_matrix;

      //return true;

   }


   void graphics::set(const matrix & matrix)
   {

      m_matrix = matrix;

      update_matrix();

      //return true;

   }


   void graphics::update_matrix()
   {

      matrix matrixScale;

      matrix matrixTranslate;

      matrixScale.a1 = m_sizeScaling.cx;

      matrixScale.b2 = m_sizeScaling.cy;

      matrixTranslate.c1 = m_pointOrigin.x;

      matrixTranslate.c2 = m_pointOrigin.y;

      auto matrix = matrixScale * m_matrix * matrixTranslate;

      _set(matrix);

   }


   void graphics::append(const matrix & matrix)
   {

      m_matrix.append(matrix);

      update_matrix();

   }


   void graphics::prepend(const matrix & matrix)
   {

      m_matrix.prepend(matrix);

      update_matrix();

   }


   void graphics::draw_rect_side(const ::rectangle_f64& rectangle, enum_border eborder)
   {

      if (eborder & e_border_top)
      {

         set_current_point(rectangle.top_left());

         line_to(rectangle.top_right());

      }

      if (eborder & e_border_right)
      {

         set_current_point(rectangle.top_right());

         line_to(rectangle.bottom_right());

      }

      if (eborder & e_border_bottom)
      {

         set_current_point(rectangle.bottom_right());

         line_to(rectangle.bottom_left());

      }

      if (eborder & e_border_left)
      {

         set_current_point(rectangle.bottom_left());

         line_to(rectangle.top_left());

      }

   }


   void graphics::draw_border(const ::rectangle_f64 & rectangleParam, const ::color::color & color, int iWidth)
   {

      ::rectangle_f64 rectangle(rectangleParam);

      rectangle.inflate(iWidth + 1, iWidth + 1);

      ::pointer<pen>point = m_ppen;

      pen_pointer point1(e_create, this);

      point1->create_solid(iWidth, color);

      point1->m_epenalign = e_pen_align_inset;

      set(point1);

      draw_rectangle(rectangle);

      set(point);

   }


   void graphics::clear_current_point()
   {

      throw ::exception(todo);

      //return ::success_none;

   }






} // namespace draw2d



