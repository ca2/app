#pragma once


namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB region :
      virtual public ::draw2d::region
   {
   public:

//      xlib_surface_t *       m_psurface;
      ::rectangle_i32                  m_rectBoundingBoxInternal;


// xxx     Gdiplus::Region *       m_pregion;

      //static region * PASCAL from_handle(::object * pobject, HRGN hRgn);
      //operator HRGN() const;

      region(::object * pobject);
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

      /*      bool get(xlib_t * pdc);
            bool get_rect(xlib_t * pdc);
            bool get_oval(xlib_t * pdc);
            bool get_polygon(xlib_t * pdc);
            bool get_poly_polygon(xlib_t * pdc);
            bool get_combine(xlib_t * pdc);


            virtual void * get_os_data() const;*/



   };


} // namespace draw2d_xlib


