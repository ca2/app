#include "framework.h"
#include <math.h>


namespace draw2d_direct2d
{


   graphics_path::graphics_path()
   {

      m_pthis = this;
      m_bFigureEnded = true;

   }


   graphics_path::~graphics_path()
   {

      destroy();

   }


   bool graphics_path::internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {

      if(m_psink != nullptr)
      {

         internal_end_figure(false);


      }


      return true;


   }


   bool graphics_path::internal_end_figure(bool bClose)
   {

      if(m_psink == nullptr || m_bFigureEnded)
         return true;

      if(bClose)
      {

         m_psink->EndFigure(D2D1_FIGURE_END_CLOSED);

      }
      else
      {

         m_psink->EndFigure(D2D1_FIGURE_END_OPEN);

      }

      m_bFigureEnded = true;

      return true;

   }

   bool graphics_path::internal_add_arc(const ::draw2d::path::arc & arc)
   {

      D2D1_POINT_2F point;

      D2D1_ARC_SEGMENT arcseg;

      internal_get_arc(point, arcseg, arc);

      if(!internal_prepare(point))
         return false;

      m_psink->AddArc(arcseg);



      return true;

   }
   bool graphics_path::internal_add_rect(int x,int y, int cx, int cy)
   {



      internal_add_line(x,y);
      internal_add_line(x + cx,y);
      internal_add_line(x + cx,y + cy);
      internal_add_line(x,y + cy);
      internal_add_line(x,y);


      return true;

   }


   bool graphics_path::internal_add_string(::draw2d_direct2d::graphics * pgraphics, i32 x, i32 y, const string & strText, ::draw2d::font * pfont)
   {

      HRESULT hr;

      if(m_psink == nullptr)
      {

         hr = m_ppath->Open(&m_psink);

      }

      wstring szOutline(strText);

      IDWriteFactory * pfactory = global_draw_get_write_factory();

      Microsoft::WRL::ComPtr < IDWriteTextLayout> textLayout;

      pfactory->CreateTextLayout(szOutline, (UINT32) szOutline.length(),(IDWriteTextFormat *)pfont->get_os_data(pgraphics),1024 * 1024,1024 * 1024,&textLayout);

      Microsoft::WRL::ComPtr < IDWriteTextRenderer > textRenderer;

      CreatePathTextRenderer(System.m_dpi, &textRenderer);

      textLayout->Draw(this, textRenderer.Get(), 0, 0);


      return true;

   }

   bool graphics_path::internal_add_line(int x1, int y1, int x2, int y2)
   {

      bool bOk1 = add_line(x1, y1);

      bool bOk2 = add_line(x2, y2);

      return bOk1 && bOk2;

   }


   bool graphics_path::internal_add_line(int x, int y)
   {

      D2D1_POINT_2F point;

      point.x = (FLOAT) x;
      point.y = (FLOAT) y;

      return internal_prepare(point);
   }


   bool graphics_path::internal_add_move(int x, int y)
   {

      internal_end_figure(false);

      D2D1_POINT_2F point;

      point.x = (FLOAT) x;
      point.y = (FLOAT) y;

      return internal_prepare(point);

   }

   bool graphics_path::internal_prepare(D2D1_POINT_2F point)
   {

      if(m_psink == nullptr)
      {

         m_ppath->Open(&m_psink);

      }

      if(m_bFigureEnded)
      {

         m_psink->BeginFigure(point, m_bFill ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);

         if(m_efillmode == ::draw2d::fill_mode_winding)
         {

            m_psink->SetFillMode(D2D1_FILL_MODE_WINDING);

         }
         else if(m_efillmode == ::draw2d::fill_mode_alternate)
         {

            m_psink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);

         }

         m_bFigureEnded = false;

      }
      else
      {

         m_psink->AddLine(point);

      }

      return true;

   }


   bool graphics_path::internal_get_arc(D2D1_POINT_2F & point,D2D1_ARC_SEGMENT & arcseg,const ::draw2d::path::arc & arc)
   {

      D2D1_POINT_2F pointCenter;

      pointCenter.x = (float) arc.m_pointCenter.x;
      pointCenter.y = (float) arc.m_pointCenter.y;

      double rx = arc.m_sizeRadius.cx;
      double ry = arc.m_sizeRadius.cy;

      point.x = (float) arc.m_pointStart.x;
      point.y = (float) arc.m_pointStart.y;

      arcseg.point.x = (float) arc.m_pointEnd.x;
      arcseg.point.y = (float) arc.m_pointEnd.y;

      if(arc.m_dAngle > 0.0)
      {

         arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_CLOCKWISE;

      }
      else
      {

         arcseg.sweepDirection = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;

      }

      if(fabs(arc.m_dAngle) < MATH_PI)
      {

         arcseg.arcSize = D2D1_ARC_SIZE_SMALL;

      }
      else
      {

         arcseg.arcSize = D2D1_ARC_SIZE_LARGE;

      }

      arcseg.rotationAngle = 0.0;

      arcseg.size.width    = (float) rx;

      arcseg.size.height   = (float) ry;

      return true;

   }


   bool graphics_path::create(::draw2d::graphics* pgraphicsParam)
   {

      auto pgraphics = __graphics(pgraphicsParam);

      m_ppath = nullptr;

      HRESULT hr = ::get_d2d1_factory1()->CreatePathGeometry(&m_ppath);

      ::draw2d_direct2d::throw_if_failed(hr);

      m_psink  = nullptr;

      for(i32 i = 0; i < m_elementa.get_count(); i++)
      {

         if (m_elementa.ptr_at(i))
         {

            set(pgraphics, m_elementa(i));

         }

      }

      if(m_psink != nullptr)
      {
         
         m_psink->Close();

         m_osdata[0] = m_ppath.Get();

      }
      else
      {

         m_ppath = nullptr;

      }

      m_psink = nullptr;

      return m_osdata[0] != nullptr;

   }


   void * graphics_path::detach(::draw2d::graphics* pgraphicsParam)
   {

      defer_update(pgraphicsParam);

      return m_ppath.Detach();

   }


   void graphics_path::destroy()
   {

      m_psink = nullptr;

      m_ppath = nullptr;

   }


   bool graphics_path::create()
   {

      return true;

   }


   bool graphics_path::set(::draw2d_direct2d::graphics * pgraphics, const ::draw2d::path::element & e)
   {

      switch(e.m_etype)
      {
      case ::draw2d::path::element::type_move:
         set(e.u.m_move);
         break;
      case ::draw2d::path::element::type_arc:
         set(e.u.m_arc);
         break;
      case ::draw2d::path::element::type_line:
         set(e.u.m_line);
         break;
      case ::draw2d::path::element::type_rect:
         set(e.u.m_rect);
         break;
      case ::draw2d::path::element::type_string:
         set(pgraphics,e.m_stringpath);
         break;
      case ::draw2d::path::element::type_end:
         internal_end_figure(e.u.m_end.m_bClose);
         break;
      default:
         __throw(::exception::exception("unexpected simple os graphics element type"));
      }

      return false;

   }


   bool graphics_path::set(const ::draw2d::path::arc & arc)
   {

      ::rect rect;

      rect.left      = (LONG) (arc.m_pointCenter.x - arc.m_sizeRadius.cx);
      rect.right     = (LONG) (arc.m_pointCenter.x + arc.m_sizeRadius.cx);
      rect.top       = (LONG) (arc.m_pointCenter.y - arc.m_sizeRadius.cy);
      rect.bottom    = (LONG) (arc.m_pointCenter.y + arc.m_sizeRadius.cy);

      bool bOk = internal_add_arc(arc);

      return bOk;

   }


   bool graphics_path::set(const ::draw2d::path::move & move)
   {

      return internal_add_move((int) move.m_x, (int) move.m_y);

   }


   bool graphics_path::set(const ::draw2d::path::line & line)
   {

      return internal_add_line((int) line.m_x, (int) line.m_y);

   }


   bool graphics_path::set(const ::draw2d::path::rect & rect)
   {

      return internal_add_rect((int)rect.m_x,(int)rect.m_y,(int)rect.m_cx,(int)rect.m_cy);

   }


   bool graphics_path::set(::draw2d_direct2d::graphics * pgraphics,const ::draw2d::path::string_path & path)
   {

      return true;

   }


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
   LONG cRefCount_;
   FLOAT m_pixelsPerDip;   // Number of pixels per DIP.
   UINT m_ref;
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

   ::draw2d_direct2d::graphics_path * dc = static_cast<::draw2d_direct2d::graphics_path*>(clientDrawingContext);

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
   *isDisabled = FALSE;
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
   void graphics_path::CreatePathTextRenderer(FLOAT pixelsPerDip, IDWriteTextRenderer **textRenderer)
   {
      *textRenderer = nullptr;

      PathTextRenderer *newRenderer = new PathTextRenderer(pixelsPerDip);
      newRenderer->AddRef();
      *textRenderer = newRenderer;
      newRenderer = nullptr;
   }

} // namespace draw2d_direct2d
