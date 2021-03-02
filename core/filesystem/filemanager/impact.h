#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE impact :
      virtual public ::user::impact
   {
   public:


      bool                          m_bEditConnectInit;


      impact();
      virtual ~impact();


      virtual void install_message_routing(::channel * pchannel);


      ::file::item * filemanager_item();
      ::file::path filemanager_path();

      virtual ::filemanager::document *               filemanager_document();
      virtual ::filemanager::data *                   filemanager_data();
      virtual ::user::impact *                        this_view();
      virtual __pointer(::fs::data)                          fs_data();

      void on_subject(::subject::subject * psubject, ::subject::context * pcontext);

      virtual void browse_sync(const ::action_context & action_context);
      virtual void knowledge(const string & pathUser, const ::action_context & action_context);

      //string calc_parent_data_key();

      virtual void _001Refresh();

      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnOperationDocMessage);


   };


} // namespace filemanager



