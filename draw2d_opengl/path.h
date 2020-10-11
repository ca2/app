#pragma once


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL path :
      virtual public ::draw2d::path
   {
   public:


      bool                       m_bHasPointInternal;
      ::pointd                   m_pointLast;


      path();
      virtual ~path();


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

      virtual void destroy() override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::arc& parc) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::line& pline) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::lined& pline) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::lines& pline) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::linesd& pline) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::rect& prect) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::rectd& prect) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::polygon& ppolygon) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::polygond& ppolygond) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::text_out& ptextout) override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::draw_text& pdrawtext) override;


   };


} // namespace draw2d_opengl




