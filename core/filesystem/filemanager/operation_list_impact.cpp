#include "framework.h"
#include "operation_list_impact.h"
#include "operation_document.h"
#include "operation.h"
#include "operation_thread.h"
#include "file_properties_form.h"
#include "acme/constant/message.h"
#include "acme/platform/timer.h"
#include "core/user/user/list_column.h"
#include "core/user/user/list_cache.h"
#include "core/user/user/mesh_item.h"


namespace filemanager
{


   operation_list_impact::operation_list_impact()
   {

      m_durationLastUpdate.Now();

   }

   void operation_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::list::install_message_routing(pchannel);
//      //MESSAGE_LINK(e_message_timer,pchannel,this,&operation_list_impact::_001OnTimer);
      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&operation_list_impact::on_message_create);
   }


   void operation_list_impact::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   ::count operation_list_impact::_001GetItemCount()
   {
      if(get_document() == nullptr)
         return 0;
      return get_document()->m_poperationthread->get_item_count();
   }

   ::pointer<operation_document>operation_list_impact::get_document()
   {
      return  (::user::impact::get_document());
   }

   
   void operation_list_impact::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      if(psubitem->m_iSubItem == 0)
      {

         psubitem->m_strText = get_document()->m_poperationthread->get_item_message((i32)psubitem->m_pitem->m_iItem);
         
         psubitem->m_bOk = true;

      }
      else
      {
         
         double d;
         
         d = get_document()->m_poperationthread->get_item_progress((i32)psubitem->m_pitem->m_iItem);

         psubitem->m_strText.format("%0.1f%%",d * 100.0);

         psubitem->m_bOk = true;

      }

   }


   void operation_list_impact::_001InsertColumns()
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


   void operation_list_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      //auto estatus = 
      
      __defer_construct_new(m_puserlistcache);

      m_pmeshcache = m_puserlistcache;

      SetTimer(123,500_ms,nullptr);

   }


   void operation_list_impact::_001OnTimer(::timer * ptimer)
   {
      BASE::_001OnTimer(ptimer);
      if(ptimer->m_uEvent == 123)
      {
         /*if(m_durationLastUpdate.elapsed() > 500)
         {
         m_durationLastUpdate= ::duration::now();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
         }*/
      }

   }


   void operation_list_impact::OnFileOperationStep(i32 iOperation,bool bFinal)
   {

      __UNREFERENCED_PARAMETER(iOperation);

      if(bFinal || m_durationLastUpdate.elapsed() > 200_ms)
      {

         m_durationLastUpdate= ::duration::now();

         _001OnUpdateItemCount();

         m_puserlistcache->_001Invalidate(this);

         ::count iItem = 0;

         for(i32 i = 0; i < get_document()->m_poperationthread->m_iOperation; i++)
         {

            iItem += get_document()->m_poperationthread->m_fileoperationa.get_size();

         }

         if(get_document()->m_poperationthread->m_iOperation < get_document()->m_poperationthread->m_fileoperationa.get_size())
         {

            iItem += get_document()->m_poperationthread->m_fileoperationa[get_document()->m_poperationthread->m_iOperation]->m_iFile;

         }

         _001ItemScroll(iItem);

      }

   }


   void operation_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      BASE::handle(ptopic, pcontext);

      if (ptopic->m_atom == ID_INITIAL_UPDATE)
      {

         _001UpdateColumns();

      }

   }


} // namespace filemanager



