#pragma once


#include "impact_base.h"
#include "aura/user/user/plain_edit.h"


namespace filemanager
{


   class CLASS_DECL_CORE path_impact :
      virtual public ::user::show < ::user::plain_edit >,
      virtual public ::filemanager_impact_base
   {
   public:


      bool m_bVoidSync;


      path_impact();


      void install_message_routing(::channel * pchannel) override;

      //virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::topic * ptopic, ::context * pcontext) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void browse_sync(const ::action_context & action_context) override;


   };


} // namespace filemanager




