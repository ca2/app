#pragma once


#include "core/filesystem/filemanager/impact_base.h"


namespace filemanager
{


   class CLASS_DECL_CORE folder_selection_list_impact:
      virtual public ::filemanager_show < ::user::split_impact >
   {
   public:


      ::pointer < ::user::tree >          m_pusertree;
      ::pointer < tree_data >             m_ptreedata;
      ::pointer < folder::list_impact >    m_plistview;
      ::pointer < data >                  m_pdata;


      folder_selection_list_impact();
      ~folder_selection_list_impact() override;


      virtual data * filemanager_data() override;

      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      DECLARE_MESSAGE_HANDLER(_001OnAdd);
      DECLARE_MESSAGE_HANDLER(_001OnRemove);

      virtual void on_create_split_impact() override;


      virtual void browse_sync(const ::action_context & action_context) override;


      virtual void FolderAdd();
      virtual void FolderRemove();


   };


} // namespace filemanager





