#include "framework.h"
#include "operation_impact.h"
#include "operation_document.h"
#include "operation_thread.h"
#include "operation_list_impact.h"
#include "operation_info_impact.h"
#include "operation.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "base/user/user/split_layout.h"


namespace filemanager
{


   operation_impact::operation_impact()
   {

   }


   operation_impact::~operation_impact()
   {

   }


   void operation_impact::on_message_create(::message::message * pmessage)
   {
      pmessage->previous();

      get_document()->m_poperationthread->m_pimpact = this;

      m_pviewcreator = __new(::user::impact_creator());

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position_rate(0,0.3);

      initialize_split_layout();

      m_plistview = create_impact < operation_list_impact >();

      if(m_plistview == nullptr)
      {

         output_error_message("Could not create transfer list ::user::impact");

      }

      SetPane(0,m_plistview,false);


      m_pinfoview = create_impact < operation_info_impact >();
      if(m_pinfoview == nullptr)
      {
         output_error_message("Could not create transfer information ::user::impact");
      }

      SetPane(1,m_pinfoview,false);

   }


   void operation_impact::install_message_routing(::channel * pchannel)
   {
      ::user::split_impact::install_message_routing(pchannel);
      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&operation_impact::on_message_create);
      MESSAGE_LINK(e_message_main_post,pchannel,this,&operation_impact::_001OnMainPostMessage);
      MESSAGE_LINK(MESSAGE_DESTROY,pchannel,this,&operation_impact::on_message_destroy);
   }

   ::pointer<operation_document>operation_impact::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_impact::_001OnMainPostMessage(::message::message * pmessage)
   {
      ::pointer<::user::message>pusermessage(pmessage);
      if(pusermessage->m_wparam == e_main_post_file_operation)
      {
         m_pinfoview->OnFileOperationStep((i32)pusermessage->m_lparam,false);
         m_plistview->OnFileOperationStep((i32)pusermessage->m_lparam,false);
      }
      else if(pusermessage->m_wparam == e_main_post_file_operation_final)
      {
         m_pinfoview->OnFileOperationStep((i32)pusermessage->m_lparam,true);
         m_plistview->OnFileOperationStep((i32)pusermessage->m_lparam,true);
      }
   }

   void operation_impact::on_message_destroy(::message::message *pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace filemanager
























