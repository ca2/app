#pragma once



namespace simple_ui
{


   class top :
      virtual public ::user::interaction,
      virtual public ::simple_ui::style
   {
   public:


      bool                       m_bLButtonDown;
      ::point_i32                    m_pointLButtonDown;
      ::size_i32                     m_sizeLButtonDownOffset;

      bool                       m_bDrag;



      top();
      virtual ~top();


      void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnSysCommand);

   };


} // namespace simple_ui




