#pragma once


namespace userex
{


   class CLASS_DECL_CORE font_view :
      virtual public ::user::split_view
   {
   public:


      top_view *                    m_ptopview;
      ::user::font_list_view *      m_pview;
      bool                          m_bSourceFontSel;


      font_view();
      virtual ~font_view();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;

      virtual void on_create_split_impact() override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual bool set_sel_by_name(string str);


   };


} // namespace userex





