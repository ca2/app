#pragma once


#include "core/user/user/list_base.h"
#include "berg/user/user/show.h"


namespace filemanager
{


   class CLASS_DECL_CORE operation_list_impact:
      virtual public ::user::show < ::user::list_base >
   {
   public:


      typedef ::user::show < ::user::list_base > BASE;


      ::pointer<::user::list_cache>      m_puserlistcache;
      class ::time                              m_timeLastUpdate;


      operation_list_impact();

      void install_message_routing(::channel * pchannel) override;

      void on_insert_columns() override;

      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_timer(::timer * ptimer) override;

      virtual ::collection::count _001GetItemCount() override;
      virtual void _001GetSubItemText(::user::mesh_subitem * psubitem) override;

      void OnFileOperationStep(int iOperation,bool bFinal);


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      ::pointer<operation_document>get_document();


   };


} // namespace filemanager














