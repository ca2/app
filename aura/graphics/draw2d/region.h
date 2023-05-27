#pragma once


#include "object.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/_collection.h"
#include "acme/primitive/geometry2d/region.h"


namespace draw2d
{


   class CLASS_DECL_AURA region :
      virtual public object,
      virtual public geometry2d::region
   {
   public:


      region();
      region(const region & region);
      ~region() override;


      virtual bool create_rectangle(const ::rectangle_i32 & rectangle);

      virtual bool create_ellipse(const ::rectangle_i32 & rectangle);
      
      virtual bool create_polygon(const ::point_i32 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const ::point_f64 * pPoints, i32 nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_polygon(const polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding);

      virtual bool create_poly_polygon(const ::point_f64 * pPoints, const i32 * lpPolyCounts, i32 nCount, ::draw2d::enum_fill_mode efillmode);

      virtual bool create_poly_polygon(const ::point_i32 * pPoints, const i32 * lpPolyCounts, i32 nCount,::draw2d::enum_fill_mode efillmode);

      
      virtual bool combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, enum_combine ecombine, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool translate(const ::point_i32 & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool get_bounding_box(::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual bool contains(const ::point_i32 & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool contains(const ::point_f64 & point, ::draw2d::graphics * pgraphics = nullptr);

      
      bool internal_contains(const ::point_i32 & point);

      bool internal_rectangle_contains(const ::point_i32 & point);

      bool internal_oval_contains(const ::point_i32 & point);

      bool internal_polygon_contains(const ::point_i32 & point);

      bool internal_poly_polygon_contains(const ::point_i32 & point);

      bool internal_combine_contains(const ::point_i32 & point);



      bool internal_contains(const ::point_f64 & point);

      //bool internal_rectangle_contains(const ::point_f64 & point);

      //bool internal_oval_contains(const ::point_f64 & point);

      //bool internal_polygon_contains(const ::point_f64 & point);

      //bool internal_poly_polygon_contains(const ::point_f64 & point);

      //bool internal_combine_contains(const ::point_f64 & point);


      virtual void max_bounding_box(::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_rect(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_oval(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_polygon(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_poly_polygon(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_combine(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics = nullptr);


      
      virtual void max_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_rect(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_oval(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_polygon(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_poly_polygon(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_combine(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      
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

