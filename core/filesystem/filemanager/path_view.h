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


      virtual void install_message_routing(::channel * pchannel);

      //virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::subject * psubject, ::context * pcontext);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void browse_sync(const ::action_context & action_context);


   };


} // namespace filemanager




