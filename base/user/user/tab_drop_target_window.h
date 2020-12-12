#pragma once


namespace user
{


   class tab_drop_target_window :
      virtual public ::user::interaction
   {
   public:


      array < e_position >                   m_positiona;
      ::user::tab* m_ptab;
      index                                  m_iTab;


      tab_drop_target_window(::user::tab* ptab, index iTab);
      virtual ~tab_drop_target_window();


      //virtual bool get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, style_context * pcontext) override;

      virtual void install_message_routing(::channel* pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;

      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual bool has_pending_graphical_update() override;

   };


} // namespace user



