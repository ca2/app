// From save_as_name_impact by camilo on 2023-05-05 19:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "impact_base.h"
#include "aura/user/user/button.h"


namespace filemanager
{


   class CLASS_DECL_CORE save_as_edit_impact :
      virtual public ::filemanager_show < ::user::show < ::user::plain_edit > >
   {
   public:


      bool m_bVoidSync;


      save_as_edit_impact();


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::topic * ptopic, ::context * pcontext) override;

      void browse_sync(const ::action_context & action_context) override;


   };



} // namespace filemanager





