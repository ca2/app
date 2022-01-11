#pragma once


#include "object.h"


namespace draw2d
{


   class CLASS_DECL_AURA region :
      virtual public object
   {
   public:


      enum_region                         m_eregion;
      double                              m_x1;
      double                              m_y1;
      double                              m_x2;
      double                              m_y2;
      double                              m_x3;
      double                              m_y3;
      ::point_f64 *                          m_lppoints;
      int *                               m_lppolycounts;
      i32                                 m_nCount;
      ::draw2d::enum_fill_mode            m_efillmode;
      __pointer(::draw2d::region)   m_pregion1;
      __pointer(::draw2d::region)   m_pregion2;
      enum_combine                        m_ecombine;
      ::point_i32                             m_pointOffset;


      region();
      region(const region & region);
      virtual ~region();


      virtual bool create_rectangle(const ::rectangle_i32 & rectangle);

      virtual bool create_ellipse(const ::rectangle_i32 & rectangle);
      
      virtual bool create_polygon(const POINT_I32 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_polygon(const POINT_F64 * pPoints, i32 nCount,::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const POINT_F64 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const POINT_I32 * pPoints, const i32 * lpPolyCounts, i32 nCount,::draw2d::enum_fill_mode efillmode);

      
      virtual bool combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, enum_combine ecombine, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool translate(const POINT_I32 & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool get_bounding_box(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual bool contains(const POINT_I32 & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool contains(const POINT_F64 & point, ::draw2d::graphics * pgraphics = nullptr);

      
      bool internal_contains(const POINT_I32 & point);

      bool internal_rectangle_contains(const POINT_I32 & point);

      bool internal_oval_contains(const POINT_I32 & point);

      bool internal_polygon_contains(const POINT_I32 & point);

      bool internal_poly_polygon_contains(const POINT_I32 & point);

      bool internal_combine_contains(const POINT_I32 & point);



      bool internal_contains(const POINT_F64 & point);

      bool internal_rectangle_contains(const POINT_F64 & point);

      bool internal_oval_contains(const POINT_F64 & point);

      bool internal_polygon_contains(const POINT_F64 & point);

      bool internal_poly_polygon_contains(const POINT_F64 & point);

      bool internal_combine_contains(const POINT_F64 & point);


      virtual void max_bounding_box(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_rect(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_oval(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_polygon(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_poly_polygon(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_combine(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);


      
      virtual void max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_rect(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_oval(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_polygon(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_poly_polygon(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual void max_bounding_box_combine(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      
      virtual ::e_status destroy() override;


      region & operator = (const ::draw2d::region & regionSrc);


   };


   typedef __pointer(region) region_pointer;


} // namespace draw2d



