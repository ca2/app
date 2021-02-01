#pragma once


namespace draw2d_direct2d
{


   enum e_path
   {

      path_hollow,
      path_filled

   };


   class CLASS_DECL_DRAW2D_DIRECT2D path :
      virtual public ::draw2d::path,
      virtual public ::draw2d::object
   {
   public:


      Microsoft::WRL::ComPtr<ID2D1PathGeometry>          m_ppathHollow;
      Microsoft::WRL::ComPtr<ID2D1PathGeometry>          m_ppathFilled;
      Microsoft::WRL::ComPtr<ID2D1PathGeometry>          m_ppath;
      Microsoft::WRL::ComPtr<ID2D1GeometrySink>          m_psink;
      bool                                               m_bFigureOpened;
      ::point_i32                                            m_point;
      D2D1_FIGURE_BEGIN                                  m_d2d2figurebegin;


      path();
      virtual ~path();


      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;
      virtual void destroy() override;


      //virtual bool internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point_i32 current_point();

      virtual bool internal_add_arc(::draw2d::graphics * pgraphics, const ::arc & arc);

      virtual bool internal_add_line(::draw2d::graphics* pgraphics, double x, double y);

      virtual bool internal_add_rect(::draw2d::graphics* pgraphics, double x, double y, double cx, double cy);

      virtual bool internal_add_lines(::draw2d::graphics* pgraphics, const ::point_i32_array & pointa, bool bClose);

      virtual bool internal_add_lines(::draw2d::graphics* pgraphics, const ::point_f64_array& pointa, bool bClose);

      virtual bool internal_add_string(::draw2d_direct2d::graphics * pgraphics, double x, double y, const string & strText, ::draw2d::font * pfont);

      virtual bool internal_start_figure(::draw2d::graphics* pgraphics, double x, double y);

      virtual bool internal_get_arc(::point_f64 & pointStart, D2D1_ARC_SEGMENT & arcseg, const ::arc & arc);

      virtual void * detach(::draw2d::graphics * pgraphics);

      virtual bool create();

      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::begin * pbegin) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::arc * parc) override;
      ////virtual bool _set(::draw2d::graphics* pgraphics, const ::draw2d::path::move & move);
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::rectangle_i32* prectangle) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::line * pline) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::lines* plines) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon_i32* pline) override;
      //virtual bool _set(::draw2d::graphics * pgraphics, ::draw2d::path::text_out * ptextout) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text * pdrawtext) override;
      //virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::close* pclose) override;


      virtual bool _set(::draw2d::graphics* pgraphics, const enum_shape& eshape);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::arc& parc);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::line& pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::lined& pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::lines& pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::linesd& pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::rectangle_i32& prectangle);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::rectangle_f64& prectangle);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::polygon_i32& ppolygon);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::polygon_f64& ppolygond);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::text_out& ptextout);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::draw_text& pdrawtext);


      static void CreatePathTextRenderer(FLOAT pixelsPerDip,IDWriteTextRenderer **textRenderer);


   };


} // namespace draw2d_direct2d



