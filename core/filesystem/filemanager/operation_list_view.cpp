#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   operation_list_view::operation_list_view()
   {
      m_millisLast123Update= ::millis::now();
      m_pcache = &m_listcache;
   }

   void operation_list_view::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
      ::user::list::install_message_routing(pchannel);
//      //MESSAGE_LINK(e_message_timer,pchannel,this,&operation_list_view::_001OnTimer);
      MESSAGE_LINK(e_message_create,pchannel,this,&operation_list_view::_001OnCreate);
   }


   void operation_list_view::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   ::count operation_list_view::_001GetItemCount()
   {
      if(get_document() == nullptr)
         return 0;
      return get_document()->m_thread.get_item_count();
   }

   __pointer(operation_document) operation_list_view::get_document()
   {
      return  (::user::impact::get_document());
   }

   void operation_list_view::_001GetItemText(::user::mesh_item * pitem)
   {
      if(pitem->m_iSubItem == 0)
      {
         pitem->m_strText = get_document()->m_thread.get_item_message((i32)pitem->m_iItem);
         pitem->m_bOk = true;
      }
      else
      {
         double d;
         d = get_document()->m_thread.get_item_progress((i32)pitem->m_iItem);
         pitem->m_strText.Format("%0.1f%%",d * 100.0);
         pitem->m_bOk = true;
      }
   }

   void operation_list_view::_001InsertColumns()
   {
      {
         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 500;
         pcolumn->m_iSubItem = 0;
         pcolumn->m_sizeIcon.cx = 16;
         pcolumn->m_sizeIcon.cy = 16;

      }

      {

         auto pcolumn = new_list_column();
         pcolumn->m_iWidth = 500;
         pcolumn->m_iSubItem = 1;
         pcolumn->m_sizeIcon.cx = 16;
         pcolumn->m_sizeIcon.cy = 16;


      }

   }




   void operation_list_view::_001OnCreate(::message::message * pmessage)
   {
      pmessage->previous();
      SetTimer(123,500,nullptr);
   }
   void operation_list_view::_001OnTimer(::timer * ptimer)
   {
      BASE::_001OnTimer(ptimer);
      if(ptimer->m_uEvent == 123)
      {
         /*if(m_millisLast123Update.elapsed() > 500)
         {
         m_millisLast123Update= ::millis::now();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
         }*/
      }
   }

   void operation_list_view::OnFileOperationStep(i32 iOperation,bool bFinal)
   {
      UNREFERENCED_PARAMETER(iOperation);
      if(bFinal || m_millisLast123Update.elapsed() > 184)
      {
         m_millisLast123Update= ::millis::now();
         _001OnUpdateItemCount();
         m_listcache._001Invalidate(this);
         ::count iItem = 0;
         for(i32 i = 0; i < get_document()->m_thread.m_iOperation; i++)
         {
            iItem += get_document()->m_thread.m_fileoperationa.get_size();
         }
         if(get_document()->m_thread.m_iOperation < get_document()->m_thread.m_fileoperationa.get_size())
         {
            iItem += get_document()->m_thread.m_fileoperationa[get_document()->m_thread.m_iOperation]->m_iFile;
         }

         _001ItemScroll(iItem);

      }

   }


   void operation_list_view::on_apply(::action * paction)
   {

      BASE::on_apply(paction);

      if (paction->id() == INITIAL_UPDATE)
      {

         _001UpdateColumns();

      }

   }


} // namespace filemanager



