#pragma once


namespace draw2d_direct2d
{


   class region :
      virtual public ::draw2d::region
   {
   public:


      Microsoft::WRL::ComPtr<ID2D1Geometry>            m_pgeometry;


      region();
      virtual ~region();

      //void defer_update();

      virtual void destroy() override;
      virtual bool create(::draw2d::graphics * pgraphics, ::index iCreate) override;


      void SetRectRgn(int x1, int y1, int x2, int y2);
      void SetRectRgn(const ::rect & rect);
      int CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode);
      int CopyRgn(const ::draw2d::region* pRgnSrc);
      bool EqualRgn(const ::draw2d::region* pRgn) const;
      int OffsetRgn(int x, int y);
      int OffsetRgn(const ::point & point);
      int GetRgnBox(RECT * prect) const;
      bool contains(::draw2d::graphics * pgraphics, int x, int y) const;
      bool contains(::draw2d::graphics * pgraphics, const ::point & point) const;
      bool RectInRegion(const ::rect & rect) const;
      int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;


      ID2D1Geometry * get(::draw2d::graphics * pgraphics);
      ID2D1Geometry * get_rect(::draw2d::graphics * pgraphics);
      ID2D1Geometry * get_oval(::draw2d::graphics * pgraphics);
      ID2D1Geometry * get_polygon(::draw2d::graphics * pgraphics);
      ID2D1Geometry * get_poly_polygon(::draw2d::graphics * pgraphics);
      ID2D1Geometry * get_combine(::draw2d::graphics * pgraphics);

   };


} // namespace draw2d_direct2d



