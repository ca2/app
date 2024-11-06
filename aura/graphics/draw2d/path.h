#pragma once


#include "object.h"
#include "path_optimization.h"
#include "acme/prototype/geometry2d/angle.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme/prototype/geometry2d/lines.h"
//#include "acme/prototype/geometry2d/ellipse.h"
//#include "acme/prototype/geometry2d/rectangle.h"



//
//template < typename HOLDEE >
//class shape_array;
//template < typename HOLDEE >
//class ___shape;


namespace draw2d
{


   class path_optimization;


   class CLASS_DECL_AURA path :
      virtual public ::draw2d::object
   {
   public:


      bool                                   m_bPersistent;
      //pointer< shape_array < path > >      m_pshapea;
      ::pointer_array < ::geometry2d::item > m_itema;
      bool                                   m_bHasPoint;
      double_point                              m_pointBegin;
      double_point                              m_pointEnd;
      ::draw2d::enum_fill_mode               m_efillmode;
      double_point                              m_pointOffset;
      ::pointer < ::draw2d::path_optimization > m_ppathoptimization;
      bool                                      m_bUseGeometryRealization;


      path();
      ~path() override;


      void destroy() override;


      virtual bool has_current_point();
      virtual double_point get_current_point();


      virtual bool is_empty();


      inline bool set_current_point(double x, double y) { return set_current_point({ x, y }); }
      virtual bool set_current_point(const ::double_point & point);


      virtual void set_fill_mode(::draw2d::enum_fill_mode efillmode);
      virtual ::draw2d::enum_fill_mode get_fill_mode();


      virtual bool begin_figure();
      virtual bool close_figure();
      virtual bool end_figure();


      virtual bool add_arc_label(const ::double_rectangle & rectangle);


      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const double_point & point);


      virtual bool add_rectangle(const ::double_rectangle & rectangle, const ::double_point & point, const ::angle_double & angleRotation);

      virtual bool add_rectangle(const ::double_rectangle & rectangle, const ::angle_double & angleCenterRotation);

      virtual bool add_rectangle(const ::double_rectangle & rectangle);

      virtual bool add_ellipse(const ::double_ellipse & ellipse);

      virtual bool add_arc(const ::double_rectangle & rectangle, const ::angle_double & angleBeg, const ::angle_double & angleSweep);
//      virtual bool varc(const ::double_point & point, double h, const ::angle_double & angle);
//      virtual bool harc(const ::double_point & point, double w, const ::angle_double & angle);


      //virtual bool add_lines(const ::int_point * ppoint, ::collection::count nCount);
      virtual bool add_lines(const ::double_point * ppoint, ::collection::count nCount);


      //virtual bool add_polygon(const ::int_point* ppoint, ::collection::count nCount);
      virtual bool add_polygon(const ::double_point * ppoint, ::collection::count nCount);


      inline bool add_line(double x, double y) { return add_line({ x, y }); }
      virtual bool add_line(const double_point & point);


      inline bool add_line(double m, double n, double p, double q) { return add_line({ m, n }, { p, q }); }
      virtual bool add_line(const double_point & point1, const double_point & point2);


      virtual bool add_text_out(const ::double_point & point, const string & strText, ::write_text::font_pointer spfont);
      virtual bool add_draw_text(const string & strText, const ::double_rectangle & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font_pointer pfont);


      virtual void * detach();


      virtual bool get_bounding_box(::double_rectangle & rectangle) const;
      //virtual bool get_bounding_box(::int_rectangle * prectangle) const;




      //=============================================================================
      //
      // get_round_rect()
      //
      // Purpose:     Defines a Rounded int_rectangle and places it in the GraphicsPath
      //
      // Parameters:  pPath		- [out] pointer to GraphicsPath that will recieve the
      //									path data
      //				int_rectangle			- [in]	Rect that defines the round int_rectangle boundaries
      //				dia			- [in]	diameter of the rounded corners (2*radius)
      //
      // Returns:     None
      //

      //bool do_round_rect_corner(const ::double_rectangle& rectangleCorner, const ::double_rectangle& rectangleRect, int iDiameter, const ::e_border & eborder, int iCorner, bool & bOn);
      bool do_round_rectangle_corner(const ::double_rectangle & rectangleCorner, const ::double_rectangle & rectangleRect, double dDiameter, const ::e_border & eborder, int iCorner, bool & bOn);

      bool add_round_top_left(const ::double_rectangle & rectangle, double iDiameter, const ::e_border & eborder = e_border_all);
      bool add_round_bottom_right(const ::double_rectangle & rectangle, double iDiameter, const ::e_border & eborder = e_border_all);


      //bool add_round_rect(const ::double_rectangle & rectangle, double iRadius, const ::e_border & eborder = e_border_all);
      //bool counter_corner(const ::double_rectangle & rectangleCorner, double iRadius, const ::e_border & eborder);
      //bool clock_corner(const ::double_rectangle & rectangleCorner, double iRadius, const ::e_border & eborder);

      void add_round_rectangle(const ::double_rectangle & rectangle, double dRadius, const ::e_border & eborder = e_border_all);
      bool counter_corner(const ::double_rectangle & rectangleCorner, double dRadius, const ::e_border & eborder);
      bool clock_corner(const ::double_rectangle & rectangleCorner, double dRadius, const ::e_border & eborder);


      virtual bool _set_create(::draw2d::graphics * pgraphics);

      //virtual bool _set(::draw2d::graphics * pgraphics, ::___shape<path> * pshape);

      virtual bool _set(::draw2d::graphics * pgraphics, ::geometry2d::item * pitem);

      virtual bool _set(::draw2d::graphics * pgraphics, const enum_item & eitem);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::arc_double & arc);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::line & pline);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::double_line & line);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::lines & pline);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::lines_double & lines);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::double_rectangle & prectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::double_rectangle & rectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::double_ellipse & ellipse);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::int_polygon & ppolygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::double_polygon & polygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::double_poly_polygon & polygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext);

      path & operator = (const path & path);

   };


   ::pointer<::draw2d::path_optimization>create_path_simple_optimization(::draw2d::path * ppath);


} // namespace draw2d

//
//template < >
//CLASS_DECL_AURA ::pointer<___shape< ::draw2d::path>> __create_shape(const ::write_text::text_out & textout, holdee < ::draw2d::path>);
//
//template < >
//CLASS_DECL_AURA ::pointer<___shape< ::draw2d::path>> __create_shape(const ::write_text::draw_text & drawtext, holdee < ::draw2d::path>);
//
//
//
