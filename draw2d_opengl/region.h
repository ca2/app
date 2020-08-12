#pragma once


namespace draw2d_opengl
{


   class region :
      virtual public ::draw2d::region
   {
   public:


      //plusplus::Region *       m_pregion;

      region(const region & rect);
      region();
      virtual ~region();


      virtual void * get_os_data() const;


      void defer_update();

      //void SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2);
      //void SetRectRgn(const ::rect & rect);
      //i32 CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, i32 nCombineMode);
      //i32 CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      i32 OffsetRgn(i32 x, i32 y);
      //i32 OffsetRgn(const ::point & point);
      bool get_bounding_box(RECT * prect) const;
      //bool PtInRegion(i32 x, i32 y) const;
      bool contains(const ::point & point) const;
      //bool RectInRegion(const ::rect & rect) const;
      //i32 GetRegionData(LPRGNDATA lpRgnData, i32 nCount) const;

      virtual void destroy() override;

      // platform-specific or platform-internals
      // "get" set of funcionts translate ::draw2d::region data into platform specific data
      //plusplus::Region * get();
      //plusplus::Region * get_rect();
      //plusplus::Region * get_oval();
      //plusplus::Region * get_polygon();
      //plusplus::Region * get_poly_polygon();
      //plusplus::Region * get_combine();

   };


} // namespace draw2d_opengl



