#pragma once


namespace user
{


   class CLASS_DECL_CORE tooltip:
      virtual public ::user::interaction
   {
   public:


      string               m_str;
      ::draw2d::font_pointer    m_font;
      ::size               m_size;
      bool                 m_bError;


      tooltip(::layered * pobjectContext);
      virtual ~tooltip();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;

      ::size CalcSize();

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


//      virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, style_context * pcontext) override;


      virtual ::user::interaction::e_type get_window_type() override;


   };


} // namespace veritile







