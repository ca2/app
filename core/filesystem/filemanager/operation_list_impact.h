#pragma once


#include "core/user/user/list.h"
#include "base/user/user/show.h"


namespace filemanager
{


   class CLASS_DECL_CORE operation_list_impact:
      virtual public ::user::show < ::user::list >
   {
   public:


      typedef ::user::show < ::user::list > BASE;


      ::pointer<::user::list_cache>      m_puserlistcache;
      class ::time                              m_timeLastUpdate;


      operation_list_impact();

      void install_message_routing(::channel * pchannel) override;

      void _001InsertColumns() override;

      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;

      virtual count _001GetItemCount() override;
      virtual void _001GetSubItemText(::user::mesh_subitem * psubitem) override;

      void OnFileOperationStep(i32 iOperation,bool bFinal);


      void handle(::topic * ptopic, ::context * pcontext) override;


      ::pointer<operation_document>get_document();


   };


} // namespace filemanager














