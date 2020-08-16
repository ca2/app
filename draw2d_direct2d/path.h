#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D graphics_path :
      virtual public ::draw2d::path,
      virtual public ::draw2d::object
   {
   public:


      Microsoft::WRL::ComPtr<ID2D1PathGeometry>          m_ppath;
      Microsoft::WRL::ComPtr<ID2D1GeometrySink>          m_psink;
      bool                                               m_bFigureOpened;
      ::point                                            m_point;


      graphics_path();
      virtual ~graphics_path();


      virtual bool create(::draw2d::graphics * pgraphics) override;
      virtual void destroy() override;


      //virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool internal_add_arc(::draw2d::graphics * pgraphics, ::draw2d::path::arc * parc);

      virtual bool internal_add_line(::draw2d::graphics* pgraphics, double x, double y);

      virtual bool internal_add_rect(::draw2d::graphics* pgraphics, double x, double y, double cx, double cy);

      virtual bool internal_add_lines(::draw2d::graphics* pgraphics, const ::pointd_array & pointa, bool bClose);

      //virtual bool internal_add_line(::draw2d::graphics* pgraphics, int x, int y);

      //virtual bool internal_add_move(::draw2d::graphics* pgraphics, int x, int y);


      virtual bool internal_add_string(::draw2d_direct2d::graphics * pgraphics, double x, double y, const string & strText, ::draw2d::font * pfont);


      virtual bool internal_start_figure(::draw2d::graphics* pgraphics, double x, double y);

      //virtual bool internal_prepare(::draw2d::graphics * pgraphics, D2D1_POINT_2F point);
      virtual bool internal_get_arc(::pointd & pointStart, D2D1_ARC_SEGMENT & arcseg, ::draw2d::path::arc * parc);

      //virtual bool internal_add_rect(int x1, int y1, int x2, int y2);

      //virtual void * get_os_data() const;
      virtual void * detach(::draw2d::graphics * pgraphics);

      //ID2D1PathGeometry * get_os_path(::draw2d_direct2d::graphics * pdc);

      virtual bool create();
      //bool destroy();
      //bool set(::draw2d::graphics * pdc,const ::draw2d::path::element & e);
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::begin * pbegin) override;
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::arc * parc) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, const ::draw2d::path::move & move);
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::rect* prect) override;
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::line * pline) override;
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::lines* plines) override;
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon* pline) override;
      virtual bool _set(::draw2d::graphics * pgraphics, ::draw2d::path::text_out * ptextout) override;
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text * pdrawtext) override;
      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::close* pclose) override;

      static void CreatePathTextRenderer(FLOAT pixelsPerDip,IDWriteTextRenderer **textRenderer);


   };


} // namespace draw2d_direct2d



