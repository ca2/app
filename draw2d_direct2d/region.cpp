#include "framework.h"


namespace draw2d_direct2d
{


   region::region()
   {

      //m_bUpdated = false;

   }


   region::~region()
   {

      destroy();

   }


   int region::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
   {

      __throw(todo());

      //   ASSERT(get_os_data() != nullptr); return (int)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData);

   }
   void region::SetRectRgn(int x1, int y1, int x2, int y2)
   {

      __throw(todo());

      //ASSERT(get_os_data() != nullptr); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2);
   }

   void region::SetRectRgn(const ::rect & rect)
   {

      __throw(todo());

      //   ::SetRectRgn((HRGN)get_os_data(), rect.left, rect.top, rect.right, rect.bottom);
   }

   int region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode)
   {

      __throw(todo());

      //ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
      //(HRGN)pRgn2->get_os_data(), nCombineMode);
   }
   int region::CopyRgn(const ::draw2d::region* pRgnSrc)
   {

      __throw(todo());

      //ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), nullptr, RGN_COPY);
   }

   bool region::EqualRgn(const ::draw2d::region* pRgn) const
   {

      __throw(todo());


      //   ASSERT(get_os_data() != nullptr);

      // return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()) != FALSE;

   }

   int region::OffsetRgn(int x, int y)
   {

      __throw(todo());


      //ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), x, y);
   }
   int region::OffsetRgn(const ::point & point)
   {

      __throw(todo());


      //ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y);
   }
   int region::GetRgnBox(RECT * prect) const
   {

      __throw(todo());


      //ASSERT(get_os_data() != nullptr); return ::GetRgnBox((HRGN)get_os_data(), rect);
   }


   bool region::contains(::draw2d::graphics* pgraphics, int x, int y) const
   {

      ((region *) this)->defer_update(pgraphics, 0);

      BOOL b = FALSE;

      HRESULT hr = m_pgeometry->FillContainsPoint(D2D1::Point2F((FLOAT) x, (FLOAT) y), nullptr, &b);

      if(FAILED(hr))
         return false;

      return b != FALSE;

      //Gdiplus::PointF pointf((Gdiplus::REAL) x, (Gdiplus::REAL) y);
      //
      //ASSERT(get_os_data() != nullptr); //return ::PtInRegion((HRGN)get_os_data(), x, y);

      //return m_pgeometry->IsVisible(pointf)  != FALSE;

   }


   bool region::contains(::draw2d::graphics* pgraphics, const ::point & point) const
   {

      return contains(pgraphics, point.x, point.y);

      //__throw(todo());


      //return ::PtInRegion((HRGN)get_os_data(), point.x, point.y);
      //Gdiplus::PointF pointf((Gdiplus::REAL) point.x, (Gdiplus::REAL) point.y);
      //
      //ASSERT(get_os_data() != nullptr); //return ::PtInRegion((HRGN)get_os_data(), x, y);

      //return m_pgeometry->IsVisible(pointf)  != FALSE;

   }


   bool region::RectInRegion(const ::rect & rect) const
   {

      __throw(todo());


      //ASSERT(get_os_data() != nullptr); return ::RectInRegion((HRGN)get_os_data(), rect);

      //Gdiplus::RectF rectf((Gdiplus::REAL) rect.left, (Gdiplus::REAL) rect.top, (Gdiplus::REAL) (rect.right - rect.left), (Gdiplus::REAL) (rect.bottom - rect.top));
      //
      //ASSERT(get_os_data() != nullptr); //return ::PtInRegion((HRGN)get_os_data(), x, y);

      //return m_pgeometry->IsVisible(rectf)  != FALSE;

   }


   bool region::create(::draw2d::graphics* pgraphics, ::index iCreate)
   {

      m_osdata[0] = get(pgraphics);

      return m_pgeometry.Get() != nullptr;

   }


   ID2D1Geometry * region::get(::draw2d::graphics* pgraphics)
   {

      switch(m_etype)
      {
      case type_none:
      {

         ID2D1PathGeometry * ppathgeometry = nullptr;

         HRESULT hr = get_d2d1_factory1()->CreatePathGeometry(&ppathgeometry);

         if(FAILED(hr))
            return nullptr;

         return ppathgeometry;

      }
      case type_rect:
         return get_rect(pgraphics);
      case type_oval:
         return get_oval(pgraphics);
      case type_polygon:
         return get_polygon(pgraphics);
      case type_poly_polygon:
         return get_polygon(pgraphics);
      case type_combine:
         return get_combine(pgraphics);
      default:
         ::exception::throw_not_implemented();
      }

      return nullptr;

   }


   ID2D1Geometry * region::get_rect(::draw2d::graphics* pgraphics)
   {

      ID2D1RectangleGeometry * pgeometry = nullptr;

      get_d2d1_factory1()->CreateRectangleGeometry(D2D1::RectF((FLOAT)m_x1, (FLOAT)m_y1, (FLOAT)m_x2, (FLOAT)m_y2), &pgeometry);

      return pgeometry;

   }


   ID2D1Geometry * region::get_oval(::draw2d::graphics* pgraphics)
   {

      D2D1_ELLIPSE ellipse;

      ellipse.point.x = (float)(m_x2 + m_x1) / 2.f;
      ellipse.point.y = (float)(m_y2 + m_y1) / 2.f;
      ellipse.radiusX = (float)(m_x2 - m_x1) / 2.f;
      ellipse.radiusY = (float)(m_y2 - m_y1) / 2.f;

      ID2D1EllipseGeometry * pgeometry = nullptr;

      get_d2d1_factory1()->CreateEllipseGeometry(ellipse, &pgeometry);

      return pgeometry;

   }


   ID2D1Geometry * region::get_polygon(::draw2d::graphics* pgraphics)
   {

      ::draw2d::path_pointer path(this);

      /*point_array pa;

      for(int i = 0; i < m_nCount; i++)
      {
         pa.add(Gdiplus::PointF((Gdiplus::REAL) m_lppoints[i].x, (Gdiplus::REAL) m_lppoints[i].y));
      }*/

      /*
      if(m_efillmode == ::draw2d::fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }
      */

      path->begin_figure();
      path->add_lines(m_lppoints, m_nCount);
      path->close_figure();

      return (ID2D1PathGeometry *) path->detach();

   }


   ID2D1Geometry * region::get_poly_polygon(::draw2d::graphics* pgraphics)
   {

      ::draw2d::path_pointer path(this);

      pointd_array pa;

      /*if(m_efillmode == ::draw2d::fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }*/

      int n = 0;

      for(int i = 0; i < m_nCount; i++)
      {
         int jCount = m_lppolycounts[i];
         pa.remove_all();
         for(int j = 0; j < jCount; j++)
         {
            pa.add(pointd(m_lppoints[n].x, m_lppoints[n].y));
            n++;
         }
         //path->begin_figure(true, m_efillmode);
         path->begin_figure();
         path->add_lines(pa.get_data(), (int) pa.get_count());
         //path->end_figure(true);
         path->close_figure();
      }

      return (ID2D1PathGeometry *) path->detach();

   }


   ID2D1Geometry * region::get_combine(::draw2d::graphics* pgraphics)
   {

      Microsoft::WRL::ComPtr <ID2D1PathGeometry> ppathgeometry ;

      HRESULT hr = get_d2d1_factory1()->CreatePathGeometry(&ppathgeometry);

      Microsoft::WRL::ComPtr < ID2D1GeometrySink > psink ;

      if (FAILED(hr))
      {

         return nullptr;

      }

      hr = ppathgeometry->Open(&psink);

      if(FAILED(hr))
      {

         return nullptr;

      }

      auto pgeometry1 = m_pregion1->get_os_data < ID2D1Geometry * >(pgraphics);

      auto pgeometry2 = m_pregion2->get_os_data < ID2D1Geometry * >(pgraphics);

      if(m_ecombine == combine_add)
      {

         hr = pgeometry1->CombineWithGeometry(pgeometry2, D2D1_COMBINE_MODE_UNION, nullptr, 0.f, psink.Get());

      }
      else if(m_ecombine == combine_exclude)
      {

         hr = pgeometry1->CombineWithGeometry(pgeometry2, D2D1_COMBINE_MODE_EXCLUDE, nullptr, 0.f, psink.Get());

      }
      else if(m_ecombine == combine_intersect)
      {

         hr = pgeometry1->CombineWithGeometry(pgeometry2, D2D1_COMBINE_MODE_INTERSECT, nullptr, 0.f, psink.Get());

      }
      else
      {

         hr = pgeometry1->CombineWithGeometry(pgeometry2, D2D1_COMBINE_MODE_UNION, nullptr, 0.f, psink.Get());

      }

      if(FAILED(hr))
      {

         return nullptr;

      }


      hr = psink->Close();

      if(FAILED(hr))
      {

         return nullptr;

      }

      return ppathgeometry.Detach();

   }


   void region::destroy()
   {

      m_pgeometry = nullptr;

   }


} // namespace draw2d_direct2d



