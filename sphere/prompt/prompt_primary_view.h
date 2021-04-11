#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE primary_view :
      public ::user::show < ::user::plain_edit >
   {
   public:


      

      typedef ::user::show <  ::user::plain_edit > BASE;


      strsize m_iCompromised;


      primary_view(::object * pobject);


      virtual void install_message_routing(::channel * pchannel);


      virtual void _001OnAfterChangeText(const ::action_context & action_context);
      void on_subject(::subject::subject * psubject, ::subject::context * pcontext);


      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditPaste);
      DECLARE_MESSAGE_HANDLER(_001OnEditPaste);
      DECLARE_MESSAGE_HANDLER(_001OnContextMenu);


   };


} // namespace prompt



