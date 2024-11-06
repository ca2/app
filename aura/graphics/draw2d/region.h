#pragma once


#include "object.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/_collection.h"
#include "acme/prototype/geometry2d/region.h"


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


//      virtual bool create_rectangle(const ::int_rectangle & rectangle) override;
//
//      virtual bool create_ellipse(const ::int_rectangle & rectangle) override;
//      
//      virtual bool create_polygon(const ::int_point * pPoints, int nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding) override;
//
//      virtual bool create_polygon(const ::double_point * pPoints, int nCount, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding) override;
//
//      virtual bool create_polygon(const polygon & polygon, ::draw2d::enum_fill_mode efillmode = ::draw2d::e_fill_mode_winding) override;
//
//      virtual bool create_poly_polygon(const ::double_point * pPoints, const int * lpPolyCounts, int nCount, ::draw2d::enum_fill_mode efillmode) override;
//
//      virtual bool create_poly_polygon(const ::int_point * pPoints, const int * lpPolyCounts, int nCount,::draw2d::enum_fill_mode efillmode) override;

      
      //virtual bool combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, enum_combine ecombine, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool translate(const ::int_point & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool get_bounding_box(::int_rectangle & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      virtual bool contains(const ::int_point & point, ::draw2d::graphics * pgraphics = nullptr);
      virtual bool contains(const ::double_point & point, ::draw2d::graphics * pgraphics = nullptr);

      
      bool internal_contains(const ::int_point & point);

      bool internal_rectangle_contains(const ::int_point & point);

      bool internal_oval_contains(const ::int_point & point);

      bool internal_polygon_contains(const ::int_point & point);

      bool internal_poly_polygon_contains(const ::int_point & point);

      bool internal_combine_contains(const ::int_point & point);



      bool internal_contains(const ::double_point & point);

      //bool internal_rectangle_contains(const ::double_point & point);

      //bool internal_oval_contains(const ::double_point & point);

      //bool internal_polygon_contains(const ::double_point & point);

      //bool internal_poly_polygon_contains(const ::double_point & point);

      //bool internal_combine_contains(const ::double_point & point);


      virtual void expand_bounding_box(::int_rectangle & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_rect(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_oval(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_polygon(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_poly_polygon(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_combine(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);


      
      virtual void expand_bounding_box(::double_rectangle & rectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_rect(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_oval(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_polygon(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_poly_polygon(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      //virtual void max_bounding_box_combine(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics = nullptr);

      
      virtual void destroy() override;


      region & operator = (const ::draw2d::region & regionSrc);


   };


   
   //using arc_shape_region = _shape < ::arc, e_shape_arc, region>;
   ////using line_shape_with_region = _shape < ::line, e_shape_line, region >;
   //using rectangle_shape_region = _shape < ::double_rectangle, e_shape_rectangle, region >;
   //using ellipse_shape_region = _shape < ::double_ellipse, e_shape_ellipse, region >;
   //using polygon_shape_region = _shape < ::polygon, e_shape_polygon, region >;

   /*template < >
   inline ::pointer<___shape>__create_shape(const ::line & line)
   {

      return __allocate line_shape_with_region(line);

   }*/




} // namespace draw2d


//template < >
//CLASS_DECL_AURA ::pointer<___shape< ::draw2d::region>> __create_shape(const ::write_text::text_out & textout, holdee < ::draw2d::region>);
//
//template < >
//CLASS_DECL_AURA ::pointer<___shape< ::draw2d::region>> __create_shape(const ::write_text::draw_text & drawtext, holdee < ::draw2d::region>);
//
//

