#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE primary_impact :
      public ::user::show < ::user::plain_edit >
   {
   public:


      

      typedef ::user::show <  ::user::plain_edit > BASE;


      character_count m_iCompromised;


      primary_impact(::particle * pparticle);


      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnAfterChangeText(const ::action_context & action_context);
      void handle(::topic * ptopic, ::context * pcontext);


      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditPaste);
      DECLARE_MESSAGE_HANDLER(_001OnEditPaste);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);


   };


} // namespace prompt



