#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE primary_view :
      public ::user::show < ::user::plain_edit >
   {
   public:


      

      typedef ::user::show <  ::user::plain_edit > BASE;


      strsize m_iCompromised;


      primary_view(::layered * pobjectContext);


      virtual void install_message_routing(::channel * pchannel);


      virtual void _001OnAfterChangeText(const ::action_context & action_context);
      void on_subject(::subject::subject * psubject, ::subject::context * pcontext);


      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnContextMenu);


   };


} // namespace prompt



