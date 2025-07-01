#pragma once


#include "aura/graphics/draw2d/region.h"


namespace typeface_freetype
{


   class region :
      virtual public ::draw2d::region
   {
   public:


      //plusplus::Region *       m_pregion;

      region(const region & rectangle);
      region();
      virtual ~region();


      virtual void * get_os_data() const;


      void defer_update();

      //void SetRectRgn(int x1, int y1, int x2, int y2);
      //void SetRectRgn(const ::int_rectangle & rectangle);
      //int CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int nCombineMode);
      //int CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      int OffsetRgn(int x, int y);
      //int OffsetRgn(const ::int_point & point);
      bool get_bounding_box(::int_rectangle * prectangle) const;
      //bool PtInRegion(int x, int y) const;
      bool contains(const ::int_point & point) const;
      //bool RectInRegion(const ::int_rectangle & rectangle) const;
      //int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;

      virtual void destroy() override;

      // operating_system-specific or operating_system-internals
      // "get" set of funcionts translate ::draw2d::region data into platform specific data
      //plusplus::Region * get();
      //plusplus::Region * get_rect();
      //plusplus::Region * get_oval();
      //plusplus::Region * get_polygon();
      //plusplus::Region * get_poly_polygon();
      //plusplus::Region * get_combine();

   };


} // namespace typeface_freetype



