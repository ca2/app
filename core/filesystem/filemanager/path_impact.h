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

      ::file::path resolve_folder(const ::scoped_string & scopedstrText, bool bFindParent);
      bool browse_typed_path(bool bFindParent);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      void browse_sync(const ::action_context & action_context) override;


   };


} // namespace filemanager




