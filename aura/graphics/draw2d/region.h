#pragma once


#include "object.h"
//#include "acme/primitive/geometry2d/_collection.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/collection/pointer_array.h"
#include "acme/primitive/collection/string_array.h"


template < primitive_rectangle RECTANGLE >
inline void max_bounding_box(RECTANGLE & rectangle, POINT_F64 * p)
{

   rectangle.left = (decltype(rectangle.left))minimum(rectangle.left, p->x);
   rectangle.right = (decltype(rectangle.right))maximum(rectangle.right, p->x);
   rectangle.top = (decltype(rectangle.top))minimum(rectangle.top, p->y);
   rectangle.bottom = (decltype(rectangle.bottom))maximum(rectangle.bottom, p->y);

}

template < primitive_rectangle RECTANGLE >
inline void max_bounding_box(RECTANGLE & rectangle, POINT_F64 * p, ::count c)
{

   for (::index i = 0; i < c; i++)
   {
    
      max_bounding_box(rectangle, p);
      
      p++;

   }

}


namespace draw2d
{


   class CLASS_DECL_AURA region :
      virtual public object
   {
   public:


      class CLASS_DECL_AURA item :
         virtual public ::particle
      {
      public:

         virtual void translate(const POINT_I32 & point);
         virtual void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics);
         virtual bool internal_contains(const POINT_F64 & p);

      };


      class CLASS_DECL_AURA rectangle_item :
         virtual public item
      {
      public:

         ::rectangle_f64 m_rectangle;

         void translate(const POINT_I32 & point) override;
         void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;
         bool internal_contains(const POINT_F64 & p) override;

      };

      class CLASS_DECL_AURA ellipse_item :
         virtual public item
      {
      public:


         ::rectangle_f64 m_rectangle;

         void translate(const POINT_I32 & point) override;
         void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;
         bool internal_contains(const POINT_F64 & p) override;



      };

      class CLASS_DECL_AURA polygon_item :
         virtual public item
      {
      public:

         ::polygon m_polygon;
         ::draw2d::enum_fill_mode            m_efillmode;
         
         
         void translate(const POINT_I32 & point) override;
         void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;
         bool internal_contains(const POINT_F64 & p) override;


      };


      class CLASS_DECL_AURA poly_polygon_item :
         virtual public item
      {
      public:

         pointer_array < ::polygon > m_polygona;
         ::draw2d::enum_fill_mode            m_efillmode;

         void translate(const POINT_I32 & point) override;
         void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;
         bool internal_contains(const POINT_F64 & p) override;


      };

      class CLASS_DECL_AURA combine_item :
         virtual public item
      {
      public:

         pointer_array < ::polygon > m_polygon;

         ::pointer<::draw2d::region>  m_pregion1;
         ::pointer<::draw2d::region>  m_pregion2;
         enum_combine                        m_ecombine;

         void translate(const POINT_I32 & point) override;
         void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;
         bool internal_contains(const POINT_F64 & p) override;



      };


      class CLASS_DECL_AURA round_rectangle_item :
         virtual public item
      {
      public:

         
         ::rectangle_f64   m_rectangle;
         ::size_f64        m_sizeRadius;


         void translate(const POINT_I32 & point) override;
         void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;
         bool internal_contains(const POINT_F64 & p) override;

      };


      enum_region                         m_eregion;
      ::pointer<item>                    m_pitem;
      //union
      //{

      //   ::rectangle_f64      m_rectangle; // rectangle/ellipse
      //   struct
      //   {

      //      ::point_f64 * m_lppoints;
      //      int * m_lppolycounts;
      //      i32                                 m_nCount;

      //   } m_polygon;
      //   struct
      //   {

      //      ::point_f64 * m_lppoints;
      //      int * m_lppolycounts;
      //      i32                                 m_nCount;

      //   } m_polypolygon;
      //   struct
      //   {



      //   } m_combine;

      //};

      //double                              m_x1;
      //double                              m_y1;
      //double                              m_x2;
      //double                              m_y2;
      //double                              m_x3;
      //double                              m_y3;
      ::point_i32                             m_pointOffset;


      region();
      region(const region & region);
      ~region() override;


      virtual bool create_rectangle(const ::rectangle_i32 & rectangle);

      virtual bool create_ellipse(const ::rectangle_i32 & rectangle);
      
      virtual bool create_polygon(const POINT_I32 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const POINT_F64 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_poly_polygon(const POINT_F64 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const POINT_I32 * pPoints, const i32 * lpPolyCounts, i32 nCount,::draw2d::enum_fill_mode efillmode);

      
      virtual bool combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, enum_combine ecombine, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool translate(const POINT_I32 & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool get_bounding_box(RECTANGLE_I32 & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual bool contains(const POINT_I32 & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool contains(const POINT_F64 & point, ::draw2d::graphics * pgraphics = nullptr);

      
      bool internal_contains(const POINT_I32 & point);

      bool internal_rectangle_contains(const POINT_I32 & point);

      bool internal_oval_contains(const POINT_I32 & point);

      bool internal_polygon_contains(const POINT_I32 & point);

      bool internal_poly_polygon_contains(const POINT_I32 & point);

      bool internal_combine_contains(const POINT_I32 & point);



      bool internal_contains(const POINT_F64 & point);

      //bool internal_rectangle_contains(const POINT_F64 & point);

      //bool internal_oval_contains(const POINT_F64 & point);

      //bool internal_polygon_contains(const POINT_F64 & point);

      //bool internal_poly_polygon_contains(const POINT_F64 & point);

      //bool internal_combine_contains(const POINT_F64 & point);


      virtual void max_bounding_box(RECTANGLE_I32 & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_rect(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_oval(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_polygon(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_poly_polygon(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_combine(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);


      
      virtual void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_rect(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_oval(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_polygon(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_poly_polygon(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_combine(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      
      virtual void destroy() override;


      region & operator = (const ::draw2d::region & regionSrc);


   };


   
   //using arc_shape_region = _shape < ::arc, e_shape_arc, region>;
   ////using line_shape_with_region = _shape < ::line, e_shape_line, region >;
   //using rectangle_shape_region = _shape < ::rectangle, e_shape_rectangle, region >;
   //using ellipse_shape_region = _shape < ::ellipse, e_shape_ellipse, region >;
   //using polygon_shape_region = _shape < ::polygon, e_shape_polygon, region >;

   /*template < >
   inline ::pointer<___shape>__create_shape(const ::line & line)
   {

      return __new(line_shape_with_region(line));

   }*/




} // namespace draw2d


//template < >
//CLASS_DECL_AURA ::pointer<___shape< ::draw2d::region>> __create_shape(const ::write_text::text_out & textout, holdee < ::draw2d::region>);
//
//template < >
//CLASS_DECL_AURA ::pointer<___shape< ::draw2d::region>> __create_shape(const ::write_text::draw_text & drawtext, holdee < ::draw2d::region>);
//
//

