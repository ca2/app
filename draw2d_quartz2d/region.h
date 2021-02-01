#pragma once


namespace draw2d_quartz2d
{


   class region :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::region
   {
   public:


      CGMutablePathRef        m_path;

      // xxx     Gdiplus::Region *       m_pregion;

      //static region * PASCAL from_handle(::base::application * papp, HRGN hRgn);
      //operator HRGN() const;

      region();
      virtual ~region();


      //virtual void * get_os_data() const;


      /*bool CreateRectRgn(i32 x1, i32 y1, i32 x2, i32 y2);
       bool CreateRectRgnIndirect(const ::rectangle_i32 & rectangle);
       bool CreateEllipticRgn(i32 x1, i32 y1, i32 x2, i32 y2);
       bool CreateEllipticRgnIndirect(const ::rectangle_i32 & rectangle);
       bool CreatePolygonRgn(POINT_I32 * lpPoints, i32 nCount, i32 nMode);
       bool CreatePolyPolygonRgn(POINT_I32 * lpPoints, LPINT lpPolyCounts,
       i32 nCount, i32 nPolyFillMode);
       bool CreateRoundRectRgn(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
       bool CreateFromPath(::image::image * pimage);
       bool CreateFromData(const XFORM* lpXForm, i32 nCount,
       const RGNDATA* pRgnData);*/

      // Operations
      //void SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2);
      //void SetRectRgn(const ::rectangle_i32 & rectangle);
      //i32 CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, i32 nCombineMode);
      //i32 CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      //i32 OffsetRgn(i32 x, i32 y);
      //i32 OffsetRgn(const ::point_i32 & point);
      //i32 GetRgnBox(RECTANGLE_I32 * prectangle) const;
      //bool PtInRegion(i32 x, i32 y) const;
      //bool PtInRegion(const ::point_i32 & point) const;
      //bool RectInRegion(const ::rectangle_i32 & rectangle) const;
      // xxx      i32 GetRegionData(LPRGNDATA lpRgnData, i32 nCount) const;

//      bool get(cairo_t * pdc);
      //    bool get_rect(cairo_t * pdc);
      //  bool get_oval(cairo_t * pdc);
      //bool get_polygon(cairo_t * pdc);
      //  bool get_poly_polygon(cairo_t * pdc);
      //bool get_combine(cairo_t * pdc);

      virtual void destroy() override;

      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      virtual void * detach();
      

   };


} // namespace draw2d_quartz2d



