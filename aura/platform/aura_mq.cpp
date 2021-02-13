#include "framework.h"
#include "aura/user/_user.h"


CLASS_DECL_AURA int_bool message_queue_post(::windowing::window * pwindow, const ::id & id, wparam wparam, lparam lparam)
{

   //auto psession = Session;

   //auto puser = psession->m_puser;

   //auto pwindowing = puser->m_pwindowing;

   //auto pwindow = pwindowing->window(oswindow);

   auto pinteraction = __interaction(pwindow);

   if (pinteraction == nullptr)
   {

      return false;

   }

   auto pmq = pinteraction->m_pthreadUserInteraction->get_message_queue();

   if (!pmq)
   {

      return false;

   }

   if (!pmq->post_message(pwindow->get_oswindow(), id, wparam, lparam))
   {

      return false;

   }

   return true;

}



CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(::windowing::window * pwindow)
{

   //auto psession = Session;

   //auto puser = psession->m_puser;

   //auto pwindowing = puser->m_pwindowing;

   //auto pwindow = pwindowing->window(oswindow);

   ::user::interaction * pinteraction = __interaction(pwindow);

   if(pinteraction == nullptr)
   {

      return false;

   }

   if(pinteraction->get_context_application() == nullptr)
   {

      return false;

   }

   ithread_t idthread = pinteraction->get_context_application()->get_ithread();

   message_queue * pmq = get_message_queue(idthread, false);

   if(pmq == nullptr)
   {

      return false;

   }

   synchronization_lock ml(pmq->mutex());

   pmq->m_messagea.predicate_remove([=](MESSAGE & message)
   {

      return message.oswindow == pwindow->get_oswindow();

   });

   return true;

}



