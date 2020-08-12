#pragma once


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL path :
      virtual public ::draw2d::path
   {
   public:


      //plusplus::GraphicsPath *    m_ppath;
      //plusplus::PointF            m_pointInternal;
      bool                       m_bHasPointInternal;



      path();
      virtual ~path();


      //virtual plusplus::GraphicsPath * get_os_path(plusplus::Graphics * graphics);

      virtual bool internal_add_arc(const ::rect & rect, double iStart, double iAngle);

      virtual pointd internal_last_point();

      virtual pointd internal_current_point();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);

      virtual bool internal_add_line(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool internal_add_rect(i32 x,i32 y,i32 cx,i32 cy);
      virtual bool internal_add_line(i32 x, i32 y);
      virtual bool internal_add_move(i32 x,i32 y);

      virtual bool internal_add_rect(double x,double y,double cx,double cy);
      virtual bool internal_add_move(double x,double y);

      //virtual bool internal_add_string(plusplus::Graphics * pgraphics, i32 x,i32 y,const string & strText,::draw2d::font_pointer spfont);

//      virtual bool create(plusplus::Graphics * graphics);
      virtual void destroy() override;

//      virtual bool set(plusplus::Graphics * pgraphics, const ::draw2d::path::element & e);

      virtual bool set(const ::draw2d::path::arc & a);

      virtual bool set(const ::draw2d::path::rect & rect);

      virtual bool set(const ::draw2d::path::line & l);

      virtual bool set(const ::draw2d::path::move & p);

//      virtual bool set(plusplus::Graphics * pgraphics, const ::draw2d::path::string_path & p);


   };


} // namespace draw2d_opengl




