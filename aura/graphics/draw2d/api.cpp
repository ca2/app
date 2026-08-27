#include "platform.h"
#include "api.h"
#include "graphics.h"
#include "acme/prototype/string/international.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


namespace draw2d
{


   api::api()
   {

   }


   api::~api()
   {

   }


   void api::draw_beziers(
      ::draw2d::graphics_pointer &  pdraw2dgraphics,
      ::f64_point *                    ppoints,
      ::i32                           iCount,
      ::f64                        dRateX,
      ::f64_point *                    ppointOffset)
   {

      ::i32_rectangle clipRect;

      auto targetscope = pdraw2dgraphics->target_scope();

      targetscope += *ppointOffset;

      pdraw2dgraphics->scale_extents((::i32)dRateX, 1, 1, 1);

      pdraw2dgraphics->begin_path();
      pdraw2dgraphics->poly_bezier(ppoints, iCount);

      pdraw2dgraphics->end_path();
      pdraw2dgraphics->stroke_path();

      //pdraw2dgraphics->place_impact_area(origin, extents);
      //pdraw2dgraphics->set_origin(viewportOrg);

   }


   void api::draw_and_fill_beziers(
   ::draw2d::graphics_pointer & pdraw2dgraphics,
   ::f64_point *             ppoints,
   ::i32                  iCount,
   ::f64               dRateX,
   ::f64_point *               ppointOffset)
   {

      ::i32_rectangle clipRect;

      //i32_size viewportExt = pdraw2dgraphics->get_extents();
      auto targetscope = pdraw2dgraphics->target_scope();

      targetscope += *ppointOffset;

      //pdraw2dgraphics->shift_impact_area(*ppointOffset, viewportExt);

      pdraw2dgraphics->scale_extents((::i32)dRateX, 1, 1, 1);

      pdraw2dgraphics->begin_path();
      pdraw2dgraphics->poly_bezier(ppoints, iCount);

      pdraw2dgraphics->end_path();
      pdraw2dgraphics->stroke_and_fill_path();

      //pdraw2dgraphics->place_impact_area(viewportOrg, viewportExt);
      //pdraw2dgraphics->set_origin();

   }


   void api::draw_and_fill_beziers(
   ::draw2d::graphics_pointer & pdraw2dgraphics,
   array<f64_point_array, f64_point_array &> *
   pglyph,

   ::f64               dRateX,
   ::f64_point *               ppointOffset)

   {

      ::i32_rectangle clipRect;

      auto targetscope = pdraw2dgraphics->target_scope();

      targetscope += *ppointOffset;

      pdraw2dgraphics->scale_extents((::i32)(dRateX * 1000.0), 1, 1, 1);

      for (::i32 i = 0; i < pglyph->get_size(); i++)

      {
         pdraw2dgraphics->poly_bezier(pglyph->element_at(i).data(), (::i32)pglyph->element_at(i).get_size());

      }

      //pdraw2dgraphics->place_impact_area(viewportOrg, viewportExt);

   }


   void api::embossed_text_out(
   ::draw2d::graphics_pointer &     pdraw2dgraphics,
   const ::f64_rectangle &                    rectangle,
   ::f64                           dRateX,
   ::f64                           dHeight,
   const_char_pointer psz,
   ::i32 *                            piCharsPositions,
   ::i32                              iCharsPositions,
   ::i32                              iOffset)
   {

      ::i32_rectangle clipRect;



      //      ::i32 iOldMapMode = ::GetMapMode(pdraw2dgraphics->m_hDC);
      //      i32_point viewportOrg;
      //      ::write_text::font * pwritetextfont = pdraw2dgraphics->get_current_font();
      //      ASSERT(pwritetextfont != nullptr);
      //      VERIFY(::GetContextOrgEx(pdraw2dgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetContextOrgEx(
      //         pdraw2dgraphics->m_hDC,
      //         rectangle.left,
      //         rectangle.top,
      //         nullptr));
      //      VERIFY(::SetMapMode(pdraw2dgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(f32RateX == 0.0)
      //         f32RateX = 1.0;
      //      VERIFY(::scale_context_extentsEx(pdraw2dgraphics->m_hDC, f32RateX * 30000.0, 10000, 1, 1, nullptr));

      //      VERIFY(::SelectObject(pdraw2dgraphics->m_hDC, pwritetextfont->m_hObject));

      pdraw2dgraphics->text_out(rectangle.left, rectangle.top, psz);
      pdraw2dgraphics->begin_path();
      pdraw2dgraphics->text_out(rectangle.left, rectangle.top, psz);
      pdraw2dgraphics->end_path();
      pdraw2dgraphics->stroke_path();


      //      VERIFY(::SetMapMode(pdraw2dgraphics->m_hDC, iOldMapMode));
      //      VERIFY(::SetContextOrgEx(
      //         pdraw2dgraphics->m_hDC,
      //         viewportOrg.x,
      //         viewportOrg.y,
      //         nullptr));
   }


   void api::embossed_text_out(
   ::draw2d::graphics_pointer & pdraw2dgraphics,
   const_char_pointer psz,
   ::i32            iLeft,
   ::i32            iTop,
   ::i32            iWidth,
   ::color::color       crText,
   ::color::color       crOutline,
   ::i32            iLen)
   {
      ::i32_rectangle clipRect;

      //      ::i32 iOldMapMode = ::GetMapMode(pdraw2dgraphics->m_hDC);
      //      i32_point viewportOrg;
      //      ::write_text::font * pwritetextfont = pdraw2dgraphics->get_current_font();
      //      ASSERT(pwritetextfont != nullptr);
      //      VERIFY(::GetContextOrgEx(pdraw2dgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetContextOrgEx(
      //         pdraw2dgraphics->m_hDC,
      //         rectangle.left,
      //         rectangle.top,
      //         nullptr));
      //      VERIFY(::SetMapMode(pdraw2dgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(f32RateX == 0.0)
      //         f32RateX = 1.0;
      //      VERIFY(::scale_context_extentsEx(pdraw2dgraphics->m_hDC, f32RateX * 30000.0, 10000, 1, 1, nullptr));

      //      VERIFY(::SelectObject(pdraw2dgraphics->m_hDC, pwritetextfont->m_hObject));

      string str;
      str = utf8_to_unicode(psz);

//#ifdef WINDOWS_DESKTOP
//      ::SetTextColor((HDC)pdraw2dgraphics->get_os_data(), crOutline);
//      ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), iLeft - iWidth, iTop, str, iLen);
//      ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), iLeft, iTop - iWidth, str, iLen);
//      ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), iLeft + iWidth, iTop, str, iLen);
//      ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), iLeft, iTop + iWidth, str, iLen);
//
//      ::SetTextColor((HDC)pdraw2dgraphics->get_os_data(), crText);
//      ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), iLeft, iTop, str, iLen);
//#endif

      //pdraw2dgraphics->text_out(rectangle.left, rectangle.top, str);
//      pdraw2dgraphics->BeginPath();
//      ::TextOutW((HDC)pdraw2dgraphics->get_os_data(), rectangle.left, rectangle.top, pcsz, iLen);

      //pdraw2dgraphics->text_out(rectangle.left, rectangle.top, str);
//      pdraw2dgraphics->EndPath();
//      pdraw2dgraphics->StrokePath();


//      VERIFY(::SetMapMode(pdraw2dgraphics->m_hDC, iOldMapMode));
//      VERIFY(::SetContextOrgEx(
//         pdraw2dgraphics->m_hDC,
//         viewportOrg.x,
//         viewportOrg.y,
//         nullptr));
   }

   void api::simple_text_out(
   ::draw2d::graphics_pointer &  pdraw2dgraphics,
   const ::f64_rectangle &                 pcrect,
   ::f64                        dRateX,
   ::f64                        dHeight,
   const_char_pointer psz,
   ::i32 *                         piCharsPositions,
   ::i32                           iCharsPositions,
   ::i32                           iOffset)
   {
      __UNREFERENCED_PARAMETER(dRateX);
      __UNREFERENCED_PARAMETER(dHeight);
      __UNREFERENCED_PARAMETER(iOffset);
      __UNREFERENCED_PARAMETER(iCharsPositions);
      __UNREFERENCED_PARAMETER(piCharsPositions);


      pdraw2dgraphics->text_out(pcrect.left, pcrect.top, psz);

      return;

//      string str;
//      str = utf8_to_unicode(scopedstr);
//      ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), pcrect.left, pcrect.top, str, (::i32)str.length());

   }


   void api::embossed_text_out(::draw2d::graphics_pointer & pdraw2dgraphics, const ::f64_rectangle & rectangle, ::f64 dHeight, ::f64 dRateX, const ::scoped_string & scopedstr)
   {

      pdraw2dgraphics->text_out(rectangle.left, rectangle.top, scopedstr);
      pdraw2dgraphics->begin_path();
      pdraw2dgraphics->text_out(rectangle.left, rectangle.top, scopedstr);
      pdraw2dgraphics->end_path();
      pdraw2dgraphics->stroke_path();

   }


   void api::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void api::destroy()
   {

      //auto estatus = 
      
      ::object::destroy();

      //if (!estatus)
      //{

      //   informationf("::object::destroy returned error at ::draw2d::api::destroy");

      //}

      //return estatus;

   }


} // namespace draw2d




