#include "framework.h"
#include "list_impact.h"
#include "document.h"
#include "operation.h"
#include "thread.h"
#include "acme/constant/user_message.h"
#include "acme/handler/topic.h"
#include "acme/platform/timer.h"
#include "core/filesystem/filemanager/file_properties_form.h"
#include "core/user/user/list_column.h"
#include "core/user/user/list_cache.h"
#include "core/user/user/mesh_item.h"


namespace filemanager
{


   operation_list_impact::operation_list_impact()
   {

      m_timeLastUpdate.Now();

   }

   void operation_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);
      ::user::list::install_message_routing(pchannel);
//      //USER_MESSAGE_LINK(::user::e_message_timer,pchannel,this,&operation_list_impact::on_timer);
      USER_MESSAGE_LINK(::user::e_message_create,pchannel,this,&operation_list_impact::on_message_create);
   }


   void operation_list_impact::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }


   ::collection::count operation_list_impact::_001GetItemCount()
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

         psubitem->m_strText = get_document()->m_poperationthread->get_item_message((int)psubitem->m_pitem->m_iItem);
         
         psubitem->m_bOk = true;

      }
      else
      {
         
         double d;
         
         d = get_document()->m_poperationthread->get_item_progress((int)psubitem->m_pitem->m_iItem);

         psubitem->m_strText.formatf("%0.1f%%",d * 100.0);

         psubitem->m_bOk = true;

      }

   }


   void operation_list_impact::on_insert_columns()
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
      
      ødefer_construct_new(m_puserlistcache);

      m_pmeshcache = m_puserlistcache;

      set_timer(123,500_ms,nullptr);

   }


   void operation_list_impact::on_timer(::timer * ptimer)
   {
      BASE::on_timer(ptimer);
      if(ptimer->m_uTimer == 123)
      {
         /*if(m_timeLastUpdate.elapsed() > 500)
         {
         m_timeLastUpdate= ::time::now();
         _001OnUpdateItemCount();
         m_cache._001Invalidate();
         }*/
      }

   }


   void operation_list_impact::OnFileOperationStep(int iOperation,bool bFinal)
   {

      __UNREFERENCED_PARAMETER(iOperation);

      if(bFinal || m_timeLastUpdate.elapsed() > 200_ms)
      {

         m_timeLastUpdate= ::time::now();

         update_impact();

         m_puserlistcache->_001Invalidate(this);

         ::collection::count iItem = 0;

         for(int i = 0; i < get_document()->m_poperationthread->m_iOperation; i++)
         {

            iItem += get_document()->m_poperationthread->m_fileoperationa.get_size();

         }

         if(get_document()->m_poperationthread->m_iOperation < get_document()->m_poperationthread->m_fileoperationa.get_size())
         {

            iItem += get_document()->m_poperationthread->m_fileoperationa[get_document()->m_poperationthread->m_iOperation]->m_iFile;

         }

         scroll_to_item(iItem);

      }

   }


   void operation_list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      BASE::handle(ptopic, phandlercontext);

      if (ptopic->id() == id_initial_update)
      {

         set_pending_column_update();

         update_impact();

      }

   }


} // namespace filemanager



