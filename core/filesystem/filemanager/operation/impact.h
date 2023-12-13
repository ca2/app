#pragma once


#include "base/user/user/split_impact.h"


namespace filemanager
{


   class CLASS_DECL_CORE operation_impact:
      public ::user::split_impact
   {
   public:


      enum enum_main_post
      {

         e_main_post_file_operation,
         e_main_post_file_operation_final,

      };



      operation_list_impact *    m_plistview;
      operation_info_impact *    m_pinfoview;

      ::user::impact_creator *     m_pviewcreator;


      operation_impact();
      ~operation_impact() override;


      ::pointer<operation_document>get_document();

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnMainPostMessage);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


   };


} // namespace filemanager













