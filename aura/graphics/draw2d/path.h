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

struct NSVGimage;



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
      ::f64_point                              m_pointBegin;
      ::f64_point                              m_pointEnd;
      ::draw2d::enum_fill_mode               m_efillmode;
      ::f64_point                              m_pointOffset;
      ::pointer < ::draw2d::path_optimization > m_ppathoptimization;
      bool                                      m_bUseGeometryRealization;


      path();
      ~path() override;


      void destroy() override;


      virtual bool has_current_point();
      virtual ::f64_point get_current_point();


      virtual bool is_empty();


      inline bool set_current_point(::f64 x, ::f64 y) { return set_current_point({ x, y }); }
      virtual bool set_current_point(const ::f64_point & point);


      virtual void set_fill_mode(::draw2d::enum_fill_mode efillmode);
      virtual ::draw2d::enum_fill_mode get_fill_mode();


      virtual bool begin_figure();
      virtual bool close_figure();
      virtual bool end_figure();


      virtual bool add_arc_label(const ::f64_rectangle & rectangle);


      //virtual bool contains(::draw2d::graphics_pointer & pgraphics, const ::f64_point & point);

      virtual bool path_contains_point(const ::f64_point &point);


      virtual bool add_rectangle(const ::f64_rectangle & rectangle, const ::f64_point & point, const ::f64_angle & angleRotation);

      virtual bool add_rectangle(const ::f64_rectangle & rectangle, const ::f64_angle & angleCenterRotation);

      virtual bool add_rectangle(const ::f64_rectangle & rectangle);

      virtual bool add_ellipse(const ::f64_ellipse & ellipse);

      virtual bool add_arc(const ::f64_rectangle & rectangle, const ::f64_angle & angleBeg, const ::f64_angle & angleSweep);
//      virtual bool varc(const ::f64_point & point, ::f64 h, const ::f64_angle & angle);
//      virtual bool harc(const ::f64_point & point, ::f64 w, const ::f64_angle & angle);


      //virtual bool add_lines(const ::i32_point * ppoint, ::collection::count nCount);
      virtual bool add_lines(const ::f64_point * ppoint, ::collection::count nCount);


      //virtual bool add_polygon(const ::i32_point* ppoint, ::collection::count nCount);
      virtual bool add_polygon(const ::f64_point * ppoint, ::collection::count nCount);


      inline bool add_line(::f64 x, ::f64 y) { return add_line({ x, y }); }
      virtual bool add_line(const ::f64_point & point);


      inline bool add_line(::f64 m, ::f64 n, ::f64 p, ::f64 q) { return add_line({ m, n }, { p, q }); }
      virtual bool add_line(const ::f64_point & point1, const ::f64_point & point2);


      virtual bool add_text_out(const ::f64_point & point, const ::scoped_string & scopedstrText, ::write_text::font_pointer spfont);
      virtual bool add_draw_text(const ::scoped_string & scopedstrText, const ::f64_rectangle & rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font_pointer pfont);


      virtual void * detach();


      virtual bool get_bounding_box(::f64_rectangle & rectangle) const;
      //virtual bool get_bounding_box(::i32_rectangle * prectangle) const;




      //=============================================================================
      //
      // get_round_rect()
      //
      // Purpose:     Defines a Rounded i32_rectangle and places it in the GraphicsPath
      //
      // Parameters:  pPath		- [out] pointer to GraphicsPath that will recieve the
      //									path data
      //				i32_rectangle			- [in]	Rect that defines the round i32_rectangle boundaries
      //				dia			- [in]	diameter of the rounded corners (2*radius)
      //
      // Returns:     None
      //

      //bool do_round_rect_corner(const ::f64_rectangle& rectangleCorner, const ::f64_rectangle& rectangleRect, ::i32 iDiameter, const ::e_border & eborder, ::i32 iCorner, bool & bOn);
      bool do_round_rectangle_corner(const ::f64_rectangle & rectangleCorner, const ::f64_rectangle & rectangleRect, ::f64 dDiameter, const ::e_border & eborder, ::i32 iCorner, bool & bOn);

      bool add_round_top_left(const ::f64_rectangle & rectangle, ::f64 iDiameter, const ::e_border & eborder = e_border_all);
      bool add_round_bottom_right(const ::f64_rectangle & rectangle, ::f64 iDiameter, const ::e_border & eborder = e_border_all);


      //bool add_round_rect(const ::f64_rectangle & rectangle, ::f64 iRadius, const ::e_border & eborder = e_border_all);
      //bool counter_corner(const ::f64_rectangle & rectangleCorner, ::f64 iRadius, const ::e_border & eborder);
      //bool clock_corner(const ::f64_rectangle & rectangleCorner, ::f64 iRadius, const ::e_border & eborder);

      void add_round_rectangle(const ::f64_rectangle & rectangle, ::f64 dRadius, const ::e_border & eborder = e_border_all);
      bool counter_corner(const ::f64_rectangle & rectangleCorner, ::f64 dRadius, const ::e_border & eborder);
      bool clock_corner(const ::f64_rectangle & rectangleCorner, ::f64 dRadius, const ::e_border & eborder);


      virtual bool _set_create(::draw2d::graphics * pgraphics);

      //virtual bool _set(::draw2d::graphics * pgraphics, ::___shape<path> * pshape);

      virtual bool _set(::draw2d::graphics * pgraphics, ::geometry2d::item * pitem);

      virtual bool _set(::draw2d::graphics * pgraphics, const enum_item & eitem);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_arc & arc);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::line & pline);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_line & line);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::lines & pline);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_lines & lines);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_rectangle & prectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_rectangle & rectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_ellipse & ellipse);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::i32_polygon & ppolygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_polygon & polygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_poly_polygon & polygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext);

      path & operator = (const path & path);

      virtual ::f32 nanosvg_distPtSeg(::f32 x, ::f32 y, ::f32 px, ::f32 py, ::f32 qx, ::f32 qy);
      virtual void nanosvg_cubicBez(::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2, ::f32 x3, ::f32 y3, ::f32 x4, ::f32 y4, ::f32 tol, ::i32 level);
      virtual void nanosvg_drawPath(::f32* pts, ::i32 npts, ::i8 closed, ::f32 tol, const ::color::color& color);
      virtual void nanosvg_drawControlPts(::f32* pts, ::i32 npts);
      virtual void nanosvg_drawframe(NSVGimage* pimage, ::i32 x, ::i32 y, ::i32 w, ::i32 h);
      // virtual void nanosvg_resizecb(::i32 width, ::i32 height, ::i32 x, ::i32 y, ::i32 w, ::i32 h);

      virtual void nanosvg(const ::scoped_string & scopedstr, ::i32 x, ::i32 y, ::i32 w, ::i32 h);



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
