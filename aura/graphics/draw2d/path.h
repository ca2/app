#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA path :
      virtual public ::draw2d::object
   {
   public:


      //enum enum_type
      //{

      //   type_none,
      //   type_begin,
      //   type_arc,
      //   type_rect,
      //   type_line,
      //   type_lines,
      //   type_polygon,
      //   type_text_out,
      //   type_draw_text,
      //   type_close,

      //};


      //class CLASS_DECL_AURA matter :
      //   virtual public ::matter
      //{
      //public:

      //   enum_type m_etype;


      //   matter();
      //   virtual ~matter();


      //   virtual bool expand_bounding_rect(RECTANGLE_F64* prectd) const;

      //   virtual bool expand_bounding_rect(RECTANGLE_I32* prectd) const;

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const;

      //   virtual bool get_bounding_rectangle(RECTANGLE_I32* prectd) const;

      //   virtual bool contains(const ::point_f64& point) const;


      //};


      //class CLASS_DECL_AURA begin :
      //   virtual public matter
      //{
      //public:

      //   begin() { m_etype = type_begin; }

      //};


      //class CLASS_DECL_AURA arc :
      //   virtual public matter
      //{
      //public:

      //   point_f64      m_pointCenter;
      //   ::size_f64     m_sizeRadius;
      //   point_f64      m_pointBeg;
      //   point_f64      m_pointEnd;
      //   angle       m_angleBeg;
      //   angle       m_angleEnd;
      //   angle       m_angleRotation;

      //   arc() { m_etype = type_arc; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;

      //   virtual bool contains(const ::point_f64& point) const override;

      //};


      //class CLASS_DECL_AURA rectangle_i32 :
      //   virtual public matter
      //{
      //public:


      //   ::rectangle_f64 m_rectangle;

      //   rectangle_i32() { m_etype = type_rect; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;

      //   virtual bool contains(const ::point_f64& point) const override;


      //};


      //class CLASS_DECL_AURA line :
      //   virtual public matter
      //{
      //public:


      //   point_f64   m_pointBeg;
      //   point_f64   m_pointEnd;


      //   line() { m_etype = type_line; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;


      //};


      //class CLASS_DECL_AURA lines :
      //   virtual public matter
      //{
      //public:

      //   point_f64_array                  m_pointa;


      //   lines() { m_etype = type_lines; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;

      //   virtual bool contains(const ::point_f64& point) const override;


      //};


      //class CLASS_DECL_AURA polygon_i32 :
      //   virtual public matter
      //{
      //public:

      //   ::draw2d::enum_fill_mode         m_efillmode;
      //   point_f64_array                  m_pointa;


      //   polygon_i32() { m_etype = type_polygon; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;

      //   virtual bool contains(const ::point_f64 & point) const override;


      //};


      //class CLASS_DECL_AURA text :
      //   virtual public matter
      //{
      //public:

      //   string                        m_strText;
      //   ::write_text::font_pointer        m_pfont;

      //};


      //class CLASS_DECL_AURA text_out :
      //   virtual public text
      //{
      //public:

      //   point_i32                         m_point;

      //   text_out() { m_etype = type_text_out; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;

      //   virtual bool contains(const ::point_f64& point) const override;

      //};


      //class CLASS_DECL_AURA draw_text :
      //   virtual public text
      //{
      //public:

      //   ::rectangle_f64                        m_rectangle;
      //   int                           m_iDrawTextFlags;

      //   draw_text() { m_etype = type_draw_text; }

      //   virtual bool get_bounding_rectangle(RECTANGLE_F64* prectd) const override;

      //   virtual bool contains(const ::point_f64& point) const override;

      //};


      //class CLASS_DECL_AURA close :
      //   virtual public matter
      //{
      //public:

      //   close() { m_etype = type_close; }

      //};


      shape_array                      m_shapea;
      bool                             m_bHasPoint;
      point_f64                           m_pointBeg;
      point_f64                           m_pointEnd;
      ::draw2d::enum_fill_mode         m_efillmode;
      point_f64                           m_pointOffset;
      

      path();
      virtual ~path();


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


      virtual bool add_rect(const ::rectangle_f64& rectangle, const ::point_f64& point, const ::angle& angleRotation);

      virtual bool add_rect(const ::rectangle_f64& rectangle, const ::angle& angleCenterRotation);

      virtual bool add_rect(const ::rectangle_f64& rectangle);

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

      //bool do_round_rect_corner(const ::rectangle_f64& rectCorner, const ::rectangle_f64& rectRect, i32 iDiameter, const ::e_border & eborder, int iCorner, bool & bOn);
      bool do_round_rect_corner(const ::rectangle_f64& rectCorner, const ::rectangle_f64& rectRect, double dDiameter, const ::e_border & eborder, int iCorner, bool& bOn);

      bool add_round_top_left(const ::rectangle_f64 & rectangle, double iDiameter, const ::e_border & eborder = e_border_all);
      bool add_round_bottom_right(const ::rectangle_f64 & rectangle, double iDiameter, const ::e_border & eborder = e_border_all);


      //bool add_round_rect(const ::rectangle_f64 & rectangle, double iRadius, const ::e_border & eborder = e_border_all);
      //bool counter_corner(const ::rectangle_f64 & rectCorner, double iRadius, const ::e_border & eborder);
      //bool clock_corner(const ::rectangle_f64 & rectCorner, double iRadius, const ::e_border & eborder);

      bool add_round_rect(const ::rectangle_f64 & rectangle, double dRadius, const ::e_border & eborder = e_border_all);
      bool counter_corner(const ::rectangle_f64 & rectCorner, double dRadius, const ::e_border & eborder);
      bool clock_corner(const ::rectangle_f64 & rectCorner, double dRadius, const ::e_border & eborder);


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

      //virtual bool _set(::draw2d::graphics * pgraphics, const ::polygon_i32 & ppolygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::polygon & polygon);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext);


   };


   using path_pointer = __pointer(path);


} // namespace draw2d



