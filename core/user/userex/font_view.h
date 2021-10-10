#pragma once


namespace userex
{


   class CLASS_DECL_CORE font_view :
      virtual public ::user::split_view
   {
   public:


      top_view *                    m_ptopview;
      ::user::font_list_view *      m_pimpact;
      bool                          m_bSourceFontSel;


      font_view();
      virtual ~font_view();


      void install_message_routing(::channel * pchannel) override;

      void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

      virtual void on_create_split_impact() override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      //virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      virtual bool set_sel_by_name(string str);


   };


} // namespace userex





