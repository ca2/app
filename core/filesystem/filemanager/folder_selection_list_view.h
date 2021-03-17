#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_selection_list_view:
      virtual public ::filemanager_show < ::user::split_view >
   {
   public:


      

      ::user::tree *             m_pusertree;
      tree *                     m_ptree;
      folder_list_view *         m_plistview;
      data *                     m_pdata;


      folder_selection_list_view();
      virtual ~folder_selection_list_view();


      virtual data * filemanager_data() override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      DECL_GEN_SIGNAL(_001OnAdd);
      DECL_GEN_SIGNAL(_001OnRemove);

      virtual void on_create_split_impact() override;


      virtual void browse_sync(const ::action_context & action_context) override;


      virtual void FolderAdd();
      virtual void FolderRemove();


   };


} // namespace filemanager





