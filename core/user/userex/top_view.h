#pragma once


namespace userex
{


   class CLASS_DECL_CORE top_view :
      virtual public ::user::split_view
   {
   public:


      top_edit_view *                     m_peditview;
      top_toggle_view *                   m_ptoggleview;


      top_view();
      virtual ~top_view();

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual void on_create_split_impact() override;

      virtual void handle(::topic * psubject, ::context * pcontext) override;

      virtual bool is_this_visible(::user::enum_layout elayout = ::user::e_layout_design) override;


      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace userex







