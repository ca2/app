#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/shape_array.h"
#include "acme/primitive/geometry2d/lines.h"
#include "object.h"


#include "acme/primitive/geometry2d/shape_array.h"


namespace draw2d
{


   class CLASS_DECL_AURA path :
      virtual public ::draw2d::object
   {
   public:



      shape_array                         m_shapea;
      bool                                m_bHasPoint;
      point_f64                           m_pointBegin;
      point_f64                           m_pointEnd;
      ::draw2d::enum_fill_mode            m_efillmode;
      point_f64                           m_pointOffset;
      

      path();
      ~path() override;


      virtual bool has_current_point();
      virtual point_f64 get_current_point();


      inline bool set_current_point(double x, double y) { return set_current_point({ x, y }); }
      virtual bool set_current_point(const ::point_f64 & point);


      virtual void set_fill_mode(::draw2d::enum_fill_mode efillmode);
      virtual ::draw2d::enum_fill_mode get_fill_mode();


      virtual bool begin_figure();
      virtual bool close_figure();


      virtual bool add_arc_label(const ::rectangle_f64 & rectangle);


      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const point_f64& point);


      virtual bool add_rectangle(const ::rectangle_f64& rectangle, const ::point_f64& point, const ::angle& angleRotation);

      virtual bool add_rectangle(const ::rectangle_f64& rectangle, const ::angle& angleCenterRotation);

      virtual bool add_rectangle(const ::rectangle_f64& rectangle);

      virtual bool add_ellipse(const ::ellipse_f64 & ellipse);

      virtual bool add_arc(const ::rectangle_f64 & rectangle, const ::angle& angleBeg, const ::angle& angleSweep);
      virtual bool varc(const ::point_f64 & point, double h, const ::angle & angle);
      virtual bool harc(const ::point_f64 & point, double w, const ::angle & angle);

      
      //virtual bool add_lines(const POINT_I32 * ppoint, ::count nCount);
      virtual bool add_lines(const ::point_f64 * ppoint, ::count nCount);


      //virtual bool add_polygon(const POINT_I32* ppoint, ::count nCount);
      virtual bool add_polygon(const ::point_f64 * ppoint, ::count nCount);

      
      inline bool add_line(double x, double y) { return add_line({ x, y }); }
      virtual bool add_line(const point_f64& point);


      inline bool add_line(double m, double n, double p, double q) { return add_line({ m, n }, { p, q }); }
      virtual bool add_line(const point_f64 & point1, const point_f64 & point2);


      virtual bool add_text_out(const ::point_f64& point, const string& strText, ::write_text::font_pointer spfont);
      virtual bool add_draw_text(const string& strText, const ::rectangle_f64& rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font_pointer pfont);


      virtual void * detach();


      virtual bool get_bounding_rectangle(::rectangle_f64 * prectangle) const;
      //virtual bool get_bounding_rectangle(RECTANGLE_I32 * prectangle) const;




      //=============================================================================
      //
      // get_round_rect()
      //
      // Purpose:     Defines a Rounded rectangle_i32 and places it in the GraphicsPath
      //
      // Parameters:  pPath		- [out] pointer to GraphicsPath that will recieve the
      //									path data
      //				rectangle_i32			- [in]	Rect that defines the round rectangle_i32 boundaries
      //				dia			- [in]	diameter of the rounded corners (2*radius)
      //
      // Returns:     None
      //

      //bool do_round_rect_corner(const ::rectangle_f64& rectangleCorner, const ::rectangle_f64& rectangleRect, i32 iDiameter, const ::e_border & eborder, int iCorner, bool & bOn);
      bool do_round_rectangle_corner(const ::rectangle_f64& rectangleCorner, const ::rectangle_f64& rectangleRect, double dDiameter, const ::e_border & eborder, int iCorner, bool& bOn);

      bool add_round_top_left(const ::rectangle_f64 & rectangle, double iDiameter, const ::e_border & eborder = e_border_all);
      bool add_round_bottom_right(const ::rectangle_f64 & rectangle, double iDiameter, const ::e_border & eborder = e_border_all);


      //bool add_round_rect(const ::rectangle_f64 & rectangle, double iRadius, const ::e_border & eborder = e_border_all);
      //bool counter_corner(const ::rectangle_f64 & rectangleCorner, double iRadius, const ::e_border & eborder);
      //bool clock_corner(const ::rectangle_f64 & rectangleCorner, double iRadius, const ::e_border & eborder);

      void add_round_rectangle(const ::rectangle_f64 & rectangle, double dRadius, const ::e_border & eborder = e_border_all);
      bool counter_corner(const ::rectangle_f64 & rectangleCorner, double dRadius, const ::e_border & eborder);
      bool clock_corner(const ::rectangle_f64 & rectangleCorner, double dRadius, const ::e_border & eborder);


      virtual bool _set_create(::draw2d::graphics* pgraphics);

      virtual bool _set(::draw2d::graphics * pgraphics, ::___shape * pshape);

      virtual bool _set(::draw2d::graphics * pgraphics, const enum_shape & eshape);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::arc & arc);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::line & pline);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::line & line);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::lines & pline);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::lines & lines);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::rectangle_f64 & prectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::rectangle & rectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::ellipse & ellipse);

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::polygon_i32 & ppolygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::polygon & polygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext);

      path & operator = (const path & path);

   };


   using path_pointer = __pointer(path);


} // namespace draw2d



