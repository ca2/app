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

      //void SetRectRgn(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2);
      //void SetRectRgn(const ::i32_rectangle & rectangle);
      //::i32 CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, ::i32 nCombineMode);
      //::i32 CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      ::i32 OffsetRgn(::i32 x, ::i32 y);
      //::i32 OffsetRgn(const ::i32_point & point);
      bool get_bounding_box(::i32_rectangle * prectangle) const;
      //bool PtInRegion(::i32 x, ::i32 y) const;
      bool contains(const ::i32_point & point) const;
      //bool RectInRegion(const ::i32_rectangle & rectangle) const;
      //::i32 GetRegionData(LPRGNDATA lpRgnData, ::i32 nCount) const;

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



