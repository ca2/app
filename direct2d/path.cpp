#include "framework.h"
#include <math.h>


namespace draw2d_direct2d
{


   path::path()
   {

      m_pthis = this;
      m_bFigureOpened = false;

   }


   path::~path()
   {

      destroy();

   }


   bool path::internal_end_figure(bool bClose)
   {

      if (m_psink == nullptr)
      {

         return false;

      }

      if(bClose)
      {

         m_psink->EndFigure(D2D1_FIGURE_END_CLOSED);

      }
      else
      {

         m_psink->EndFigure(D2D1_FIGURE_END_OPEN);

      }

      m_bFigureOpened = false;

      return true;

   }


   bool path::internal_add_arc(::draw2d::graphics* pgraphics, const ::arc & arc)
   {

      ::point_f64 point;

      D2D1_ARC_SEGMENT arcseg;

      internal_get_arc(point, arcseg, arc);

      if (!internal_start_figure(pgraphics, point.x, point.y))
      {

         return false;

      }

      m_psink->AddArc(arcseg);

      return true;

   }


   bool path::internal_add_rect(::draw2d::graphics* pgraphics, double x, double y, double cx, double cy)
   {

      internal_start_figure(pgraphics, x, y);

      internal_add_line(pgraphics, x + cx,y);
      internal_add_line(pgraphics, x + cx,y + cy);
      internal_add_line(pgraphics, x,y + cy);
      
      internal_end_figure(true);

      return true;

   }


   bool path::internal_add_lines(::draw2d::graphics* pgraphics, const ::point_i32_array& pointa, bool bClose)
   {

      if (pointa.get_count() < 1)
      {

         return false;

      }

      internal_start_figure(pgraphics, pointa[0].x, pointa[0].y);

      for (index i = 1; i < pointa.get_count(); i++)
      {

         internal_add_line(pgraphics, pointa[i].x, pointa[i].y);

      }

      internal_end_figure(bClose);

      return true;

   }


   bool path::internal_add_lines(::draw2d::graphics* pgraphics, const ::point_f64_array& pointa, bool bClose)
   {

      if (pointa.get_count() < 1)
      {

         return false;

      }

      internal_start_figure(pgraphics, pointa[0].x, pointa[0].y);

      for (index i = 1; i < pointa.get_count(); i++)
      {

         internal_add_line(pgraphics, pointa[i].x, pointa[i].y);

      }

      internal_end_figure(bClose);

      return true;

   }


   bool path::internal_add_string(::draw2d_direct2d::graphics * pgraphics, double x, double y, const string & strText, ::write_text::font * pfont)
   {

      HRESULT hr;

      if(m_psink == nullptr)
      {

         hr = m_ppath->Open(&m_psink);

      }

      wstring szOutline(strText);

      IDWriteFactory * pfactory = psystem->draw2d()->direct2d()->dwrite_factory();

      Microsoft::WRL::ComPtr < IDWriteTextLayout> textLayout;

      pfactory->CreateTextLayout(szOutline, (::u32) szOutline.length(),(IDWriteTextFormat *)pfont->get_os_data(pgraphics),1024 * 1024,1024 * 1024,&textLayout);

      Microsoft::WRL::ComPtr < IDWriteTextRenderer > textRenderer;

      CreatePathTextRenderer(psystem->m_dpi, &textRenderer);

      textLayout->Draw(this, textRenderer.Get(), 0, 0);

      return true;

   }


   bool path::internal_add_line(::draw2d::graphics* pgraphics, double x, double y)
   {

      if (::is_null(m_psink.Get()))
      {

         return false;

      }

      m_psink->AddLine({ (FLOAT) x, (FLOAT)y });

      m_pointEnd.x = x;

      m_pointEnd.y = y;

      return true;

   }


   bool path::internal_start_figure(::draw2d::graphics* pgraphics, double x, double y)
   {

      if (m_psink == nullptr)
      {

         m_ppath->Open(&m_psink);

      }

      if (m_bFigureOpened)
      {

         internal_end_figure(false);

      }

      if (m_efillmode == ::draw2d::fill_mode_winding)
      {

         m_psink->SetFillMode(D2D1_FILL_MODE_WINDING);

      }
      else if (m_efillmode == ::draw2d::fill_mode_alternate)
      {

         m_psink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);

      }

      m_psink->BeginFigure({(FLOAT) x, (FLOAT) y}, pgraphics->m_bOutline ? D2D1_FIGURE_BEGIN_HOLLOW : D2D1_FIGURE_BEGIN_FILLED);

      m_bFigureOpened = true;

      return true;

   }


   bool path::internal_get_arc(::point_f64 & pointStart,D2D1_ARC_SEGMENT & arcseg, const ::arc & arc)
   {

      D2D1_POINT_2F pointCenter;

      pointCenter.x = (FLOAT)arc.m_pointCenter.x;
      pointCenter.y = (FLOAT)arc.m_pointCenter.y;

      double rx = arc.m_sizeRadius.cx;
      double ry = arc.m_sizeRadius.cy;

      pointStart.x = arc.m_pointBeg.x;
      pointStart.y = arc.m_pointBeg.y;

      arcseg.point.x = (FLOAT)arc.m_pointEnd.x;
      arcseg.point.y = (FLOAT)arc.m_pointEnd.y;

      if(arc.m_angleEnd2 > arc.m_angleBeg)
      {

         arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;

      }
      else
      {

         arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;

      }

      if(fabs(arc.m_angleEnd2 - arc.m_angleBeg) < MATH_PI)
      {

         arcseg.arcSize = D2D1_ARC_SIZE_SMALL;

      }
      else
      {

         arcseg.arcSize = D2D1_ARC_SIZE_LARGE;

      }

      arcseg.rotationAngle = (FLOAT) arc.m_angleRotation;

      arcseg.size.width    = (FLOAT) rx;

      arcseg.size.height   = (FLOAT) ry;

      return true;

   }


   bool path::create(::draw2d::graphics* pgraphicsParam, ::i8 iCreate)
   {

      auto pgraphics = __graphics(pgraphicsParam);

      HRESULT hr = S_OK;

      if (pgraphics->m_bOutline)
      {

         if (iCreate == path_hollow)
         {

            if (m_ppathHollow.Get())
            {

               m_osdata[path_hollow] = m_ppathHollow.Get();

               return m_osdata[path_hollow] != nullptr;

            }

         }

         hr = ::draw2d_direct2d::plugin::d2d1_factory1()->CreatePathGeometry(&m_ppathHollow);

         m_ppath = m_ppathHollow;

      }
      else
      {

         if (m_ppathFilled.Get())
         {

            m_osdata[path_filled] = m_ppathFilled.Get();

            return m_osdata[path_filled] != nullptr;

         }

         hr = ::draw2d_direct2d::plugin::d2d1_factory1()->CreatePathGeometry(&m_ppathFilled);
         
         m_ppath = m_ppathFilled;

      }

      ::draw2d_direct2d::throw_if_failed(hr);

      m_psink  = nullptr;

      _set_create(pgraphics);

      /*for(i32 i = 0; i < m_elementa.get_count(); i++)
      {

         if (m_elementa.ptr_at(i))
         {

            set(pgraphics, m_elementa(i));

         }

      }*/

      if (m_bFigureOpened)
      {

         internal_end_figure(false);

      }

      if(m_psink != nullptr)
      {
         
         HRESULT hr = m_psink->Close();

         m_osdata[iCreate] = m_ppath.Get();

      }
      else
      {

         m_ppath = nullptr;

      }

      m_psink = nullptr;

      return m_ppath.Get() != nullptr;

   }


   void * path::detach(::draw2d::graphics* pgraphicsParam)
   {

      defer_update(pgraphicsParam, 0);

      return m_ppath.Detach();

   }


   void path::destroy()
   {

      m_psink = nullptr;

      m_ppath = nullptr;

      m_ppathHollow = nullptr;

      m_ppathFilled = nullptr;

   }


   bool path::create()
   {

      return true;

   }


   //bool path::set(::draw2d_direct2d::graphics * pgraphics, const ::draw2d::path::matter & e)
   //{

   //   switch(e.m_etype)
   //   {
   //   case ::draw2d::path::matter::type_move:
   //      set(e.u.m_move);
   //      break;
   //   case ::draw2d::path::matter::type_arc:
   //      set(e.u.m_arc);
   //      break;
   //   case ::draw2d::path::matter::type_line:
   //      set(e.u.m_line);
   //      break;
   //   case ::draw2d::path::matter::type_rect:
   //      set(e.u.m_rectangle);
   //      break;
   //   case ::draw2d::path::matter::e_type_string:
   //      set(pgraphics,e.m_stringpath);
   //      break;
   //   case ::draw2d::path::matter::type_end:
   //      internal_end_figure(e.u.m_end.m_bClose);
   //      break;
   //   default:
   //      __throw(::exception::exception("unexpected simple os graphics matter type"));
   //   }

   //   return false;

   //}


   bool path::_set(::draw2d::graphics * pgraphics, const ::arc & arc)
   {

      //::rectangle_f64 rectangle;

      //rectangle.left      = (::i32) (arc.m_pointCenter.x - arc.m_sizeRadius.cx);
      //rectangle.right     = (::i32) (arc.m_pointCenter.x + arc.m_sizeRadius.cx);
      //rectangle.top       = (::i32) (arc.m_pointCenter.y - arc.m_sizeRadius.cy);
      //rectangle.bottom    = (::i32) (arc.m_pointCenter.y + arc.m_sizeRadius.cy);

      //bool bOk = internal_add_arc(pgraphics, parc);

      //return bOk;

      return internal_add_arc(pgraphics, arc);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const enum_shape& eshape)
   {

      if (eshape == e_shape_begin_figure)
      {

         if (m_bFigureOpened)
         {

            internal_end_figure(false);

         }

         return true;

      }
      else if (eshape == e_shape_close_figure)
      {

         if (m_bFigureOpened)
         {

            internal_end_figure(true);

         }


         return true;

      }
      else if (eshape == e_shape_end_figure)
      {

         if (m_bFigureOpened)
         {

            internal_end_figure(false);

         }

         return true;

      }
      else
      {

         return ::draw2d::path::_set(pgraphics, eshape);

      }


      return true;

   }


   //bool path::_set(const ::draw2d::path::move & move)
   //{

   //   return internal_add_move((int) move.m_x, (int) move.m_y);

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   {

      if (line.m_p1 != m_pointEnd)
      {

         if (!internal_start_figure(pgraphics, line.m_p1.x, line.m_p1.y))
         {

            return false;

         }

      }

      return internal_add_line(pgraphics, line.m_p2.x, line.m_p2.y);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::lined& line)
   {

      if (line.m_p1 != m_pointEnd || !m_bFigureOpened)
      {

         if (!internal_start_figure(pgraphics, line.m_p1.x, line.m_p1.y))
         {

            return false;

         }

         m_pointEnd = line.m_p1;

      }

      return internal_add_line(pgraphics, line.m_p2.x, line.m_p2.y);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle)
   {

      return internal_add_rect(pgraphics, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_f64& rectangle)
   {

      return internal_add_rect(pgraphics, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::lines & lines)
   {

      return internal_add_lines(pgraphics, (const ::point_i32_array &) lines, false);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::linesd& lines)
   {

      return internal_add_lines(pgraphics, (const ::point_f64_array&) lines, false);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_i32 & polygon_i32)
   {

      return internal_add_lines(pgraphics, (const ::point_i32_array&)polygon_i32, true);

   }

   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_f64& polygon_i32)
   {

      return internal_add_lines(pgraphics, (const ::point_f64_array&)polygon_i32, true);

   }

   bool path::_set(::draw2d::graphics * pgraphics, const ::text_out & textout)
   {

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::draw_text & drawtext)
   {

      return true;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::close* pclose)
   //{

   //   //::rectangle_f64 rectangle;

   //   //rectangle.left      = (::i32) (arc.m_pointCenter.x - arc.m_sizeRadius.cx);
   //   //rectangle.right     = (::i32) (arc.m_pointCenter.x + arc.m_sizeRadius.cx);
   //   //rectangle.top       = (::i32) (arc.m_pointCenter.y - arc.m_sizeRadius.cy);
   //   //rectangle.bottom    = (::i32) (arc.m_pointCenter.y + arc.m_sizeRadius.cy);

   //   //bool bOk = internal_add_arc(pgraphics, parc);

   //   //return bOk;

   //   if (m_bFigureOpened)
   //   {

   //      internal_end_figure(true);

   //   }

   //   return true;

   //}


} // namespace draw2d_direct2d



#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define multi_threaded D2D1_FACTORY_TYPE_MULTI_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?


class PathTextRenderer: public IDWriteTextRenderer
{
public:

   PathTextRenderer(
   FLOAT pixelsPerDip
   );

   STDMETHOD(DrawGlyphRun)(
   _In_opt_ void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   DWRITE_MEASURING_MODE measuringMode,
   _In_ DWRITE_GLYPH_RUN const* glyphRun,
   _In_ DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
   _In_opt_ IUnknown* clientDrawingEffect
   ) override;

   STDMETHOD(DrawUnderline)(
   _In_opt_ void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   _In_ DWRITE_UNDERLINE const* underline,
   _In_opt_ IUnknown* clientDrawingEffect
   ) override;

   STDMETHOD(DrawStrikethrough)(
   _In_opt_ void* clientDrawingContext,
   FLOAT baselineOriginX,
   FLOAT baselineOriginY,
   _In_ DWRITE_STRIKETHROUGH const* strikethrough,
   _In_opt_ IUnknown* clientDrawingEffect
   ) override;

   STDMETHOD(DrawInlineObject)(
   _In_opt_ void* clientDrawingContext,
   FLOAT originX,
   FLOAT originY,
   IDWriteInlineObject* inlineObject,
   BOOL isSideways,
   BOOL isRightToLeft,
   _In_opt_ IUnknown* clientDrawingEffect
   ) override;

   STDMETHOD(IsPixelSnappingDisabled)(
   _In_opt_ void* clientDrawingContext,
   _Out_ BOOL* isDisabled
   ) override;

   STDMETHOD(GetCurrentTransform)(
   _In_opt_ void* clientDrawingContext,
   _Out_ DWRITE_MATRIX* transform
   ) override;

   STDMETHOD(GetPixelsPerDip)(
   _In_opt_ void* clientDrawingContext,
   _Out_ FLOAT* pixelsPerDip
   ) override;

   STDMETHOD(QueryInterface)(
   REFIID riid,
   _Outptr_ void** object
   ) override;

   STDMETHOD_(ULONG,AddRef)() override;

   STDMETHOD_(ULONG,Release)() override;

private:
   DWORD cRefCount_;
   FLOAT m_pixelsPerDip;   // Number of pixels per DIP.
   ::u32 m_ref;
};



//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

using namespace Microsoft::WRL;

// An identity matrix for use by IDWritePixelSnapping::GetCurrentTransform.
const DWRITE_MATRIX identityTransform =
{
   1,0,
   0,1,
   0,0
};


PathTextRenderer::PathTextRenderer(FLOAT pixelsPerDip):
   m_pixelsPerDip(pixelsPerDip),
   m_ref(0)
{
}

//
// Draws a given glyph run along the geometry specified
// in the given clientDrawingEffect.
//
// This method calculates the horizontal displacement
// of each glyph cluster in the run, then calculates the
// tangent vector of the geometry at each of those distances.
// It then renders the glyph cluster using the offset and angle
// defined by that tangent, thereby placing each cluster on
// the path and also rotated to the path.
//
HRESULT PathTextRenderer::DrawGlyphRun(
_In_opt_ void* clientDrawingContext,
FLOAT baselineOriginX,
FLOAT baselineOriginY,
DWRITE_MEASURING_MODE measuringMode,
_In_ DWRITE_GLYPH_RUN const* glyphRun,
_In_ DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
_In_opt_ IUnknown* clientDrawingEffect
)
{
   if(clientDrawingContext == nullptr)
   {
      return S_OK;
   }

   ::draw2d_direct2d::path * dc = static_cast<::draw2d_direct2d::path*>(clientDrawingContext);

   HRESULT hr = glyphRun->fontFace->GetGlyphRunOutline(
                glyphRun->fontEmSize,
                glyphRun->glyphIndices,
                glyphRun->glyphAdvances,
                glyphRun->glyphOffsets,
                glyphRun->glyphCount,
                glyphRun->isSideways,
                glyphRun->bidiLevel % 2,
                dc->m_psink.Get()
                );

   return hr;
}

HRESULT PathTextRenderer::DrawUnderline(
_In_opt_ void* clientDrawingContext,
FLOAT baselineOriginX,
FLOAT baselineOriginY,
_In_ DWRITE_UNDERLINE const* underline,
_In_opt_ IUnknown* clientDrawingEffect
)
{
   // We don't use underline in this application.
   return E_NOTIMPL;
}

HRESULT PathTextRenderer::DrawStrikethrough(
_In_opt_ void* clientDrawingContext,
FLOAT baselineOriginX,
FLOAT baselineOriginY,
_In_ DWRITE_STRIKETHROUGH const* strikethrough,
_In_opt_ IUnknown* clientDrawingEffect
)
{
   // We don't use strikethrough in this application.
   return E_NOTIMPL;
}

HRESULT PathTextRenderer::DrawInlineObject(
_In_opt_ void* clientDrawingContext,
FLOAT originX,
FLOAT originY,
IDWriteInlineObject* inlineObject,
BOOL isSideways,
BOOL isRightToLeft,
_In_opt_ IUnknown* clientDrawingEffect
)
{
   // We don't use inline objects in this application.
   return E_NOTIMPL;
}

//
// IDWritePixelSnapping methods
//
HRESULT PathTextRenderer::IsPixelSnappingDisabled(
_In_opt_ void* clientDrawingContext,
_Out_ BOOL* isDisabled
)
{
   *isDisabled = false;
   return S_OK;
}

HRESULT PathTextRenderer::GetCurrentTransform(
_In_opt_ void* clientDrawingContext,
_Out_ DWRITE_MATRIX* transform
)
{
   *transform = identityTransform;
   return S_OK;
}

HRESULT PathTextRenderer::GetPixelsPerDip(
_In_opt_ void* clientDrawingContext,
_Out_ FLOAT* pixelsPerDip
)
{
   *pixelsPerDip = m_pixelsPerDip;
   return S_OK;
}

//
// IUnknown methods
//
// These use a basic, non-thread-safe implementation of the
// standard context_object-counting logic.
//
HRESULT PathTextRenderer::QueryInterface(
REFIID riid,
_Outptr_ void** object
)
{
   *object = nullptr;
   return E_NOTIMPL;
}

ULONG PathTextRenderer::AddRef()
{
   return InterlockedIncrement(&cRefCount_);
}

ULONG PathTextRenderer::Release()
{
   unsigned long newCount = InterlockedDecrement(&cRefCount_);
   if(newCount == 0)
   {
      delete this;
      return 0;
   }

   return newCount;
}






namespace draw2d_direct2d
{
   void path::CreatePathTextRenderer(FLOAT pixelsPerDip, IDWriteTextRenderer **textRenderer)
   {
      *textRenderer = nullptr;

      PathTextRenderer *newRenderer = new PathTextRenderer(pixelsPerDip);
      newRenderer->AddRef();
      *textRenderer = newRenderer;
      newRenderer = nullptr;
   }

} // namespace draw2d_direct2d
