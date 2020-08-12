#pragma once


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D path :
      virtual public ::draw2d::path,
      virtual public object
   {
   public:
      
      
      CGMutablePathRef        m_path;
      bool                    m_bBegin;
      
      
      path();
      virtual ~path();
      
      
      virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);
      virtual bool internal_add_arc(const ::rect & rect, double dStart, double dAngle, bool bClockwise);
      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x, int y);
      virtual bool internal_add_string_path(int x, int y, const string & strText, ::draw2d::font_pointer spfont, ::draw2d_quartz2d::graphics * p);
      
      //virtual void * get_os_data() const;
      
      virtual bool create(::draw2d::graphics * pgraphics) override;

      virtual void destroy() override;

      virtual void * detach() override;
      
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool set(const ::draw2d::path::string_path & stringpath);
   
      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const ::pointd & point) override;
      
      
   };
   
   
} // namespace draw2d_quartz2d





