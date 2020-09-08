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


   void operation_view::_001OnCreate(::message::message * pmessage)
   {
      pmessage->previous();

      get_document()->m_thread.m_pview = this;

      m_pviewcreator = __new(::user::impact_creator());

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position_rate(0,0.3);

      initialize_split_layout();

      m_plistview = create_view < operation_list_view >();

      if(m_plistview == nullptr)
      {

         message_box("Could not create transfer list ::user::impact");

      }

      SetPane(0,m_plistview,false);


      m_pinfoview = create_view < operation_info_view >();
      if(m_pinfoview == nullptr)
      {
         System.message_box("Could not create transfer information ::user::impact");
      }
      SetPane(1,m_pinfoview,false);

   }

   void operation_view::install_message_routing(::channel * pchannel)
   {
      ::user::split_view::install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_CREATE,pchannel,this,&operation_view::_001OnCreate);
      IGUI_MSG_LINK(MessageMainPost,pchannel,this,&operation_view::_001OnMainPostMessage);
      IGUI_MSG_LINK(WM_DESTROY,pchannel,this,&operation_view::_001OnDestroy);
   }

   __pointer(operation_document) operation_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_view::_001OnMainPostMessage(::message::message * pmessage)
   {
      SCAST_PTR(::message::base,pbase,pmessage);
      if(pbase->m_wparam == MessageMainPostFileOperation)
      {
         m_pinfoview->OnFileOperationStep((i32)pbase->m_lparam,false);
         m_plistview->OnFileOperationStep((i32)pbase->m_lparam,false);
      }
      else if(pbase->m_wparam == MessageMainPostFileOperationFinal)
      {
         m_pinfoview->OnFileOperationStep((i32)pbase->m_lparam,true);
         m_plistview->OnFileOperationStep((i32)pbase->m_lparam,true);
      }
   }

   void operation_view::_001OnDestroy(::message::message *pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


} // namespace filemanager
























