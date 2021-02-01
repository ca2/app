#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


CLASS_DECL_AURA int_bool mq_post_message(oswindow oswindow, const ::id & id, wparam wparam, lparam lparam)
{

   ::user::interaction* pinteraction = oswindow_interaction(oswindow);

   if (pinteraction == nullptr)
   {

      return FALSE;

   }

   auto pmq = pinteraction->m_pthreadUserInteraction->get_mq();

   if (!pmq)
   {

      return FALSE;

   }

   if (!pmq->post_message(oswindow, id, wparam, lparam))
   {

      return FALSE;

   }

   return true;

}



CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow)
{

   ::user::interaction * pinteraction = oswindow_interaction(oswindow);

   if(pinteraction == nullptr)
   {

      return FALSE;

   }

   if(pinteraction->get_context_application() == nullptr)
   {

      return false;

   }

   ithread_t idthread = pinteraction->get_context_application()->get_ithread();

   mq * pmq = get_mq(idthread, false);

   if(pmq == nullptr)
   {

      return FALSE;

   }

   sync_lock ml(pmq->mutex());

   pmq->m_messagea.pred_remove([=](mq_message & item)
   {

      return item.m_message.hwnd == oswindow;

   });

   return true;

}



