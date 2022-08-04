#pragma once


namespace userex
{


   class CLASS_DECL_CORE top_toggle_impact :
      virtual public ::user::show < ::user::button >
   {
   public:


      top_impact *           m_ptopview;


      top_toggle_impact();
      virtual ~top_toggle_impact();


      void install_message_routing(::channel * pchannel) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


      virtual bool keyboard_focus_is_focusable() const override;


   };


} // namespace userex




