#pragma once


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


      virtual bool create_rect(const ::rectangle_i32 & rectangle);

      virtual bool create_oval(const ::rectangle_i32 & rectangle);
      

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


      
      virtual ::e_status finalize() override;

      

      region & operator = (const ::draw2d::region & regionSrc);

      
      inline bool create_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2) { return create_rect(::rectangle_i32(x1, y1, x2, y2)); }
      inline bool create_rect_dim(i32 x, i32 y, i32 cx, i32 cy) { return create_rect(rect_dim(x, y, cx, cy)); }
      inline bool create_oval_coord(i32 x1, i32 y1, i32 x2, i32 y2) { return create_oval(::rectangle_i32(x1, y1, x2, y2)); }
      inline bool create_oval_dim(i32 x, i32 y, i32 cx, i32 cy) { return create_oval(rect_dim(x, y, cx, cy)); }


   };


   typedef __pointer(region) region_pointer;


} // namespace draw2d



