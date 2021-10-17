#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE path_view :
      virtual public ::user::show < ::user::plain_edit >,
      virtual public ::filemanager_impact_base
   {
   public:


      bool m_bVoidSync;


      path_view();


      void install_message_routing(::channel * pchannel) override;

      //virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::subject * psubject, ::context * pcontext) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void browse_sync(const ::action_context & action_context) override;


   };


} // namespace filemanager




