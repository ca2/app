#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_selection_list_impact:
      virtual public ::filemanager_show < ::user::split_impact >
   {
   public:


      

      ::user::tree *             m_pusertree;
      tree *                     m_ptree;
      folder_list_impact *         m_plistview;
      data *                     m_pdata;


      folder_selection_list_impact();
      virtual ~folder_selection_list_impact();


      virtual data * filemanager_data() override;

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      DECLARE_MESSAGE_HANDLER(_001OnAdd);
      DECLARE_MESSAGE_HANDLER(_001OnRemove);

      virtual void on_create_split_impact() override;


      virtual void browse_sync(const ::action_context & action_context) override;


      virtual void FolderAdd();
      virtual void FolderRemove();


   };


} // namespace filemanager





