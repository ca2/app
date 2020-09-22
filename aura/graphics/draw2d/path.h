#pragma once


namespace draw2d
{



   class CLASS_DECL_AURA path :
      virtual public ::draw2d::object
   {
   public:


      enum enum_type
      {

         type_none,
         type_begin,
         type_arc,
         type_rect,
         type_line,
         type_lines,
         type_polygon,
         type_text_out,
         type_draw_text,
         type_close,

      };


      class CLASS_DECL_AURA element :
         virtual public ::generic
      {
      public:

         enum_type m_etype;


         element();
         virtual ~element();


         virtual bool expand_bounding_rect(RECTD* prectd) const;

         virtual bool expand_bounding_rect(RECT* prectd) const;

         virtual bool get_bounding_rect(RECTD* prectd) const;

         virtual bool get_bounding_rect(RECT* prectd) const;

         virtual bool contains(const ::pointd& point) const;


      };


      class CLASS_DECL_AURA begin :
         virtual public element
      {
      public:

         begin() { m_etype = type_begin; }

      };


      class CLASS_DECL_AURA arc :
         virtual public element
      {
      public:

         pointd      m_pointCenter;
         ::sized     m_sizeRadius;
         pointd      m_pointBeg;
         pointd      m_pointEnd;
         angle       m_angleBeg;
         angle       m_angleEnd;
         angle       m_angleRotation;

         arc() { m_etype = type_arc; }

         virtual bool get_bounding_rect(RECTD* prectd) const override;

         virtual bool contains(const ::pointd& point) const override;

      };


      class CLASS_DECL_AURA rect :
         virtual public element
      {
      public:


         ::rectd m_rect;

         rect() { m_etype = type_rect; }

         virtual bool get_bounding_rect(RECTD* prectd) const override;

         virtual bool contains(const ::pointd& point) const override;


      };


      class CLASS_DECL_AURA line :
         virtual public element
      {
      public:


         pointd   m_pointBeg;
         pointd   m_pointEnd;


         line() { m_etype = type_line; }

         virtual bool get_bounding_rect(RECTD* prectd) const override;


      };


      class CLASS_DECL_AURA lines :
         virtual public element
      {
      public:

         pointd_array                  m_pointa;


         lines() { m_etype = type_lines; }

         virtual bool get_bounding_rect(RECTD* prectd) const override;

         virtual bool contains(const ::pointd& point) const override;


      };


      class CLASS_DECL_AURA polygon :
         virtual public element
      {
      public:

         ::draw2d::e_fill_mode         m_efillmode;
         pointd_array                  m_pointa;


         polygon() { m_etype = type_polygon; }

         virtual bool get_bounding_rect(RECTD* prectd) const override;

         virtual bool contains(const ::pointd & point) const override;


      };


      class CLASS_DECL_AURA text :
         virtual public element
      {
      public:

         string                        m_strText;
         ::draw2d::font_pointer        m_pfont;

         //text();
         //text(const text& stringpath);
         //virtual ~text();

         //text& operator = (const text& stringpath);

         //virtual bool get_bounding_rect(RECTD* prectd) const override;

      };


      class CLASS_DECL_AURA text_out :
         virtual public text
      {
      public:

         point                         m_point;
         //::rect                        m_rect;
         //int                           m_iDrawTextFlags;
         //COLORREF                      m_crForeground;

         text_out() { m_etype = type_text_out; }

         //text& operator = (const text& stringpath);

         virtual bool get_bounding_rect(RECTD* prectd) const override;

         virtual bool contains(const ::pointd& point) const override;

      };


      class CLASS_DECL_AURA draw_text :
         virtual public text
      {
      public:

         ::rect                        m_rect;
         int                           m_iDrawTextFlags;
         //COLORREF                      m_crForeground;

         draw_text() { m_etype = type_draw_text; }

         virtual bool get_bounding_rect(RECTD* prectd) const override;

         virtual bool contains(const ::pointd& point) const override;

      };


      class CLASS_DECL_AURA close :
         virtual public element
      {
      public:

         close() { m_etype = type_close; }

      };


      __pointer_array(element)         m_elementa;
      bool                             m_bHasPoint;
      pointd                           m_pointBeg;
      pointd                           m_pointEnd;
      ::draw2d::e_fill_mode            m_efillmode;
      pointd                           m_pointOffset;
      

      path();
      virtual ~path();


      virtual bool has_current_point();
      virtual pointd get_current_point();

      inline bool set_current_point(double x, double y) { return set_current_point({ x, y }); }
      virtual bool set_current_point(const ::pointd & point);

      //virtual bool begin_figure(bool bFill);
      //virtual bool end_figure(bool bClose);

      virtual void set_fill_mode(::draw2d::e_fill_mode efillmode);
      virtual ::draw2d::e_fill_mode get_fill_mode();

      //virtual bool begin_figure();
      virtual bool begin_figure();
      virtual bool close_figure();
      //virtual bool end_figure();

      virtual bool add_arc_label(const ::rectd & rect);


      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const pointd& point);


      virtual bool add_rect(const ::rectd& rect, const ::pointd& point, const ::angle& angleRotation);

      virtual bool add_rect(const ::rectd& rect, const ::angle& angleCenterRotation);

      virtual bool add_rect(const ::rectd& rect);

      virtual bool add_arc(const ::rectd & rect, const ::angle& angleBeg, const ::angle& angleSweep);
      virtual bool varc(const ::pointd & point, double h, const ::angle & angle);
      virtual bool harc(const ::pointd & point, double w, const ::angle & angle);

      
      virtual bool add_lines(const POINT * ppoint, ::count nCount);
      virtual bool add_lines(const POINTD * ppoint, ::count nCount);


      virtual bool add_polygon(const POINT* ppoint, ::count nCount);
      virtual bool add_polygon(const POINTD* ppoint, ::count nCount);

      
      inline bool add_line(double x, double y) { return add_line({ x, y }); }
      virtual bool add_line(const pointd& point);

      inline bool add_line(double m, double n, double p, double q) { return add_line({ m, n }, { p, q }); }
      virtual bool add_line(const pointd & point1, const pointd & point2);

      //virtual bool add_move(double x,double y);
      //virtual bool add_move(pointd point);
      //virtual bool add_move(i32 x, i32 y);




      virtual bool add_text_out(const ::pointd& point, const string& strText, ::draw2d::font_pointer spfont);
      //virtual bool add_draw_text(const string & strText, const ::rectd & rect, int iDrawTextFlags, ::draw2d::font_pointer spfont, COLORREF crForeground);
      virtual bool add_draw_text(const string& strText, const ::rectd& rect, int iDrawTextFlags, ::draw2d::font_pointer pfont);


      virtual void * detach();


      virtual bool get_bounding_rect(RECTD* prectd) const;
      virtual bool get_bounding_rect(RECT * prect) const;




      //=============================================================================
      //
      // get_round_rect()
      //
      // Purpose:     Defines a Rounded rectangle and places it in the GraphicsPath
      //
      // Parameters:  pPath		- [out] pointer to GraphicsPath that will recieve the
      //									path data
      //				rect			- [in]	Rect that defines the round rectangle boundaries
      //				dia			- [in]	diameter of the rounded corners (2*radius)
      //
      // Returns:     None
      //

      bool do_round_rect_corner(const ::rect& rectCorner, const ::rect& rectRect, i32 iDiameter, eborder eborder, int iCorner, bool & bOn);
      bool do_round_rect_corner(const ::rectd& rectCorner, const ::rectd& rectRect, double dDiameter, eborder eborder, int iCorner, bool& bOn);

      bool add_round_top_left(const ::rect& rect, i32 iDiameter, eborder eborder = border_all);
      bool add_round_bottom_right(const ::rect& rect, i32 iDiameter, eborder eborder = border_all);


      bool add_round_rect(const ::rect & rect, i32 iRadius, eborder eborder = border_all);
      bool counter_corner(const ::rect& rectCorner, i32 iRadius, eborder eborder);
      bool clock_corner(const ::rect& rectCorner, i32 iRadius, eborder eborder);

      bool add_round_rect(const ::rectd& rect, double dRadius, eborder eborder = border_all);
      bool counter_corner(const ::rectd& rectCorner, double dRadius, eborder eborder);
      bool clock_corner(const ::rectd& rectCorner, double dRadius, eborder eborder);


      virtual bool _set_create(::draw2d::graphics* pgraphics);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::element * pelement);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::begin* pbegin);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::arc * parc);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::rect * prect);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::line * pline);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::lines * plines);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon * pline);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::text_out* ptextout);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text* pdrawtext);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::close* pclose);



   };


   using path_pointer = __pointer(path);


   //class CLASS_DECL_AURA path_pointer :
   //   public pointer < path >
   //{
   //public:

   //   path_pointer()
   //   {
   //   }

   //   path_pointer(const pointer < path > & point) :
   //      pointer < path > (point)
   //   {
   //   }

   //   path_pointer(const ::allocer & allocer) :
   //      pointer < path > (allocer)
   //   {
   //   }

   //   path_pointer & operator = (::draw2d::path * ppath)
   //   {

   //      pointer < path >::operator = (ppath);

   //      return *this;

   //   }


   //};


} // namespace draw2d






