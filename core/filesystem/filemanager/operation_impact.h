#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_impact:
      public ::user::split_impact
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


      operation_list_impact *    m_plistview;
      operation_info_impact *    m_pinfoview;

      ::user::impact_creator *     m_pviewcreator;


      operation_impact();
      virtual ~operation_impact();

      __pointer(operation_document) get_document();

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnMainPostMessage);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


   };


} // namespace filemanager













