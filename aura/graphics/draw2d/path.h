#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA path :
      virtual public ::draw2d::object
   {
   public:


      
      class CLASS_DECL_AURA arc
      {
      public:


         POINTD   m_pointCenter;
         SIZED    m_sizeRadius;
         double   m_dAngle1;
         double   m_dAngle2;
         double   m_dAngle;
         POINTD   m_pointStart;
         POINTD   m_pointEnd;


      };
      class CLASS_DECL_AURA rect
      {
      public:


         double   m_x;
         double   m_y;
         double   m_cx;
         double   m_cy;


      };

      class CLASS_DECL_AURA move
      {
      public:

         double   m_x;
         double   m_y;

      };


      class CLASS_DECL_AURA line
      {
      public:

         double   m_x;
         double   m_y;

      };

      class CLASS_DECL_AURA end
      {
      public:

         bool     m_bClose;

      };

      class CLASS_DECL_AURA string_path
      {
      public:

         double               m_x;
         double               m_y;
         string               m_strText;
         ::draw2d::font_pointer    m_pfont;
         ::rect             m_rect;
         int                  m_iDrawTextFlags;
         COLORREF             m_crForeground;

         string_path();
         string_path(const string_path & stringpath);
         ~string_path();

         string_path & operator = (const string_path & stringpath);

      };

      class CLASS_DECL_AURA element :
         virtual public ::context_object
      {
      public:


         enum e_type
         {
            type_none,
            type_begin,
            type_arc,
            type_line,
            type_move,
            type_string,
            type_draw_text,
            type_rect,
            type_end

         };


         union
         {


            arc      m_arc;
            move     m_move;
            line     m_line;
            end      m_end;
            rect     m_rect;

         } u;

         string_path m_stringpath;

         e_type m_etype;

         element();
         element(const element & e);
         ~element();

         element & operator = (const element & e);

      };


      __pointer_array(element)                     m_elementa;
      bool                             m_bFill;
      ::draw2d::e_fill_mode            m_efillmode;
      bool                             m_bHasPoint;
      pointd                           m_point;
      pointd                           m_pointStart;


      path();
      virtual ~path();


      virtual bool has_current_point();
      virtual pointd last_point();



      virtual bool begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool end_figure(bool bClose);

      virtual bool add_arc_label(const ::rect & rect);


      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const pointd& point);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool add_arc(const ::rect & rect,double dStart,double dAngle);
      virtual bool add_arc(const ::rectd & rect,double dStart,double dAngle);
      virtual bool varc(const ::point & point, double h, double dAngle);
      virtual bool harc(const ::point & point, double w, double dAngle);

      virtual bool add_line(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool add_line(double x1,double y1,double x2,double y2);
      virtual bool add_line(const point & point1, const point & point2);

      virtual bool add_lines(const POINT * ppoint, ::count nCount);

      virtual bool add_lines(const POINTD * ppoint, ::count nCount);


      virtual bool add_line(i32 x, i32 y);
      virtual bool add_line(double x,double y);
      virtual bool add_line(pointd point);

      virtual bool add_move(double x,double y);
      virtual bool add_move(pointd point);
      virtual bool add_move(i32 x, i32 y);

      virtual bool add_rect(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool add_rect(const ::rect & rect);



      virtual bool add_string(i32 x,i32 y,const string & strText,::draw2d::font_pointer spfont);
      inline bool add_string(const ::point& point, const string& strText, ::draw2d::font_pointer spfont) { return add_string(point.x, point.y, strText, spfont); }
      virtual bool add_string(const string & strText, const ::rect & rect, int iDrawTextFlags, ::draw2d::font_pointer spfont, COLORREF crForeground);


      virtual void * detach();


      virtual void get_bounding_rect(RECT * prect);

      virtual void get_bounding_rect(RECT * prect,element & e);

      virtual void get_bounding_rect(RECT * prect,rect & e);

      virtual void get_bounding_rect(RECT * prect,arc & a);

      virtual void get_bounding_rect(RECT * prect,move & m);

      virtual void get_bounding_rect(RECT * prect,line & l);

      virtual void get_bounding_rect(RECT * prect,string_path & point);



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






