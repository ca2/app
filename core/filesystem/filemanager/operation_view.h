#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_view:
      public ::user::split_view
   {
   public:


      


      enum e_message
      {

         MessageMainPost = WM_USER + 23,

      };


      enum EMessageMainPost
      {

         MessageMainPostFileOperation,
         MessageMainPostFileOperationFinal,

      };


      operation_list_view *    m_plistview;
      operation_info_view *    m_pinfoview;

      ::user::impact_creator *     m_pviewcreator;


      operation_view();
      virtual ~operation_view();

      __pointer(operation_document) get_document();

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnMainPostMessage);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


   };


} // namespace filemanager













