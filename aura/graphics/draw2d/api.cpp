#include "framework.h"
#include "api.h"
#include "graphics.h"
#include "acme/prototype/string/international.h"


namespace draw2d
{


   api::api()
   {

   }


   api::~api()
   {

   }


   void api::draw_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::f64_point *                    ppoints,
      ::i32                           iCount,
      ::f64                        dRateX,
      ::f64_point *                    ppointOffset)
   {

      ::i32_rectangle clipRect;

      auto offsetcontext = pgraphics->offset_context();

      offsetcontext += *ppointOffset;

      pgraphics->scale_extents((::i32)dRateX, 1, 1, 1);

      pgraphics->begin_path();
      pgraphics->poly_bezier(ppoints, iCount);

      pgraphics->end_path();
      pgraphics->stroke_path();

      //pgraphics->place_impact_area(origin, extents);
      //pgraphics->set_origin(viewportOrg);

   }


   void api::draw_and_fill_beziers(
   ::draw2d::graphics_pointer & pgraphics,
   ::f64_point *             ppoints,
   ::i32                  iCount,
   ::f64               dRateX,
   ::f64_point *               ppointOffset)
   {

      ::i32_rectangle clipRect;

      //i32_size viewportExt = pgraphics->get_extents();
      auto offsetcontext = pgraphics->offset_context();

      offsetcontext += *ppointOffset;

      //pgraphics->shift_impact_area(*ppointOffset, viewportExt);

      pgraphics->scale_extents((::i32)dRateX, 1, 1, 1);

      pgraphics->begin_path();
      pgraphics->poly_bezier(ppoints, iCount);

      pgraphics->end_path();
      pgraphics->stroke_and_fill_path();

      //pgraphics->place_impact_area(viewportOrg, viewportExt);
      //pgraphics->set_origin();

   }


   void api::draw_and_fill_beziers(
   ::draw2d::graphics_pointer & pgraphics,
   array<f64_point_array, f64_point_array &> *
   pglyph,

   ::f64               dRateX,
   ::f64_point *               ppointOffset)

   {

      ::i32_rectangle clipRect;

      auto offsetcontext = pgraphics->offset_context();

      offsetcontext += *ppointOffset;

      pgraphics->scale_extents((::i32)(dRateX * 1000.0), 1, 1, 1);

      for (::i32 i = 0; i < pglyph->get_size(); i++)

      {
         pgraphics->poly_bezier(pglyph->element_at(i).data(), (::i32)pglyph->element_at(i).get_size());

      }

      //pgraphics->place_impact_area(viewportOrg, viewportExt);

   }


   void api::embossed_text_out(
   ::draw2d::graphics_pointer &     pgraphics,
   const ::f64_rectangle &                    rectangle,
   ::f64                           dRateX,
   ::f64                           dHeight,
   const_char_pointer psz,
   ::i32 *                            piCharsPositions,
   ::i32                              iCharsPositions,
   ::i32                              iOffset)
   {

      ::i32_rectangle clipRect;



      //      ::i32 iOldMapMode = ::GetMapMode(pgraphics->m_hDC);
      //      i32_point viewportOrg;
      //      ::write_text::font * pfont = pgraphics->get_current_font();
      //      ASSERT(pfont != nullptr);
      //      VERIFY(::GetContextOrgEx(pgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetContextOrgEx(
      //         pgraphics->m_hDC,
      //         rectangle.left,
      //         rectangle.top,
      //         nullptr));
      //      VERIFY(::SetMapMode(pgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(floatRateX == 0.0)
      //         floatRateX = 1.0;
      //      VERIFY(::scale_context_extentsEx(pgraphics->m_hDC, floatRateX * 30000.0, 10000, 1, 1, nullptr));

      //      VERIFY(::SelectObject(pgraphics->m_hDC, pfont->m_hObject));

      pgraphics->text_out(rectangle.left, rectangle.top, psz);
      pgraphics->begin_path();
      pgraphics->text_out(rectangle.left, rectangle.top, psz);
      pgraphics->end_path();
      pgraphics->stroke_path();


      //      VERIFY(::SetMapMode(pgraphics->m_hDC, iOldMapMode));
      //      VERIFY(::SetContextOrgEx(
      //         pgraphics->m_hDC,
      //         viewportOrg.x,
      //         viewportOrg.y,
      //         nullptr));
   }


   void api::embossed_text_out(
   ::draw2d::graphics_pointer & pgraphics,
   const_char_pointer psz,
   ::i32            iLeft,
   ::i32            iTop,
   ::i32            iWidth,
   ::color::color       crText,
   ::color::color       crOutline,
   ::i32            iLen)
   {
      ::i32_rectangle clipRect;

      //      ::i32 iOldMapMode = ::GetMapMode(pgraphics->m_hDC);
      //      i32_point viewportOrg;
      //      ::write_text::font * pfont = pgraphics->get_current_font();
      //      ASSERT(pfont != nullptr);
      //      VERIFY(::GetContextOrgEx(pgraphics->m_hDC, &viewportOrg));

      //      VERIFY(::OffsetContextOrgEx(
      //         pgraphics->m_hDC,
      //         rectangle.left,
      //         rectangle.top,
      //         nullptr));
      //      VERIFY(::SetMapMode(pgraphics->m_hDC, MM_ANISOTROPIC));
      //      if(floatRateX == 0.0)
      //         floatRateX = 1.0;
      //      VERIFY(::scale_context_extentsEx(pgraphics->m_hDC, floatRateX * 30000.0, 10000, 1, 1, nullptr));

      //      VERIFY(::SelectObject(pgraphics->m_hDC, pfont->m_hObject));

      string str;
      str = utf8_to_unicode(psz);

//#ifdef WINDOWS_DESKTOP
//      ::SetTextColor((HDC)pgraphics->get_os_data(), crOutline);
//      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft - iWidth, iTop, str, iLen);
//      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop - iWidth, str, iLen);
//      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft + iWidth, iTop, str, iLen);
//      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop + iWidth, str, iLen);
//
//      ::SetTextColor((HDC)pgraphics->get_os_data(), crText);
//      ::TextOutU((HDC)pgraphics->get_os_data(), iLeft, iTop, str, iLen);
//#endif

      //pgraphics->text_out(rectangle.left, rectangle.top, str);
//      pgraphics->BeginPath();
//      ::TextOutW((HDC)pgraphics->get_os_data(), rectangle.left, rectangle.top, pcsz, iLen);

      //pgraphics->text_out(rectangle.left, rectangle.top, str);
//      pgraphics->EndPath();
//      pgraphics->StrokePath();


//      VERIFY(::SetMapMode(pgraphics->m_hDC, iOldMapMode));
//      VERIFY(::SetContextOrgEx(
//         pgraphics->m_hDC,
//         viewportOrg.x,
//         viewportOrg.y,
//         nullptr));
   }

   void api::simple_text_out(
   ::draw2d::graphics_pointer &  pgraphics,
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


      pgraphics->text_out(pcrect.left, pcrect.top, psz);

      return;

//      string str;
//      str = utf8_to_unicode(scopedstr);
//      ::TextOutU((HDC)pgraphics->get_os_data(), pcrect.left, pcrect.top, str, (::i32)str.length());

   }


   void api::embossed_text_out(::draw2d::graphics_pointer & pgraphics, const ::f64_rectangle & rectangle, ::f64 dHeight, ::f64 dRateX, const ::scoped_string & scopedstr)
   {

      pgraphics->text_out(rectangle.left, rectangle.top, scopedstr);
      pgraphics->begin_path();
      pgraphics->text_out(rectangle.left, rectangle.top, scopedstr);
      pgraphics->end_path();
      pgraphics->stroke_path();

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




