#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   operation_view::operation_view()
   {

   }


   operation_view::~operation_view()
   {

   }


   void operation_view::on_message_create(::message::message * pmessage)
   {
      pmessage->previous();

      get_document()->m_thread.m_pimpact = this;

      m_pviewcreator = __new(::user::impact_creator());

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position_rate(0,0.3);

      initialize_split_layout();

      m_plistview = create_view < operation_list_view >();

      if(m_plistview == nullptr)
      {

         output_error_message("Could not create transfer list ::user::impact");

      }

      SetPane(0,m_plistview,false);


      m_pinfoview = create_view < operation_info_view >();
      if(m_pinfoview == nullptr)
      {
         output_error_message("Could not create transfer information ::user::impact");
      }
      SetPane(1,m_pinfoview,false);

   }

   void operation_view::install_message_routing(::channel * pchannel)
   {
      ::user::split_view::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create,pchannel,this,&operation_view::on_message_create);
      MESSAGE_LINK(MessageMainPost,pchannel,this,&operation_view::_001OnMainPostMessage);
      MESSAGE_LINK(e_message_destroy,pchannel,this,&operation_view::on_message_destroy);
   }

   __pointer(operation_document) operation_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_view::_001OnMainPostMessage(::message::message * pmessage)
   {
      __pointer(::user::message) pusermessage(pmessage);
      if(pusermessage->m_wparam == MessageMainPostFileOperation)
      {
         m_pinfoview->OnFileOperationStep((i32)pusermessage->m_lparam,false);
         m_plistview->OnFileOperationStep((i32)pusermessage->m_lparam,false);
      }
      else if(pusermessage->m_wparam == MessageMainPostFileOperationFinal)
      {
         m_pinfoview->OnFileOperationStep((i32)pusermessage->m_lparam,true);
         m_plistview->OnFileOperationStep((i32)pusermessage->m_lparam,true);
      }
   }

   void operation_view::on_message_destroy(::message::message *pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace filemanager
























