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
      virtual bool internal_close(bool bClose);
      virtual bool internal_add_arc(const ::rectd & rect, double dStart, double dAngle, bool bClockwise);
      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x, int y);
      virtual bool internal_add_text_out(int x, int y, const string & strText, ::draw2d::font_pointer pfont, ::draw2d_quartz2d::graphics * p);
      
      //virtual void * get_os_data() const;
      
      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      virtual void destroy() override;

      virtual void * detach() override;
      
      //bool set(const ::draw2d::path::element & e);
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::begin * pbegin) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::arc * parc) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::rect * prect) override;
      //bool set(::draw2d::path::move * pmove);
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::line * pline) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::lines * plines) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon * ppolygon) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::text_out * ptextout) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text * pdrawtext) override;
      bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::close * pclose) override;
   
      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const ::pointd & point) override;
      
      
   };
   
   
} // namespace draw2d_quartz2d





