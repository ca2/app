#include "framework.h"
#include "aura/user/_user.h"


CLASS_DECL_AURA void message_queue_post(::windowing::window * pwindow, const ::atom & atom, wparam wparam, lparam lparam)
{

   //auto psession = get_session();

   //auto puser = psession->m_puser;

   //auto pwindowing = puser->m_pwindowing;

   //auto pwindow = pwindowing->window(oswindow);

   auto pinteraction = __interaction(pwindow);

   if (pinteraction == nullptr)
   {

      throw ::exception(error_wrong_state);

   }

   auto pmq = pinteraction->m_pthreadUserInteraction->get_message_queue();

   if (!pmq)
   {

      throw ::exception(error_wrong_state);

   }

   //if (!
   
   pmq->post_message(pwindow->get_oswindow(), atom, wparam, lparam);
   //{

   //   return false;

   //}

   //return true;

}



CLASS_DECL_AURA void mq_erase_window_from_all_queues(::windowing::window * pwindow)
{

   //auto psession = get_session();

   //auto puser = psession->m_puser;

   //auto pwindowing = puser->m_pwindowing;

   //auto pwindow = pwindowing->window(oswindow);

   ::user::interaction * pinteraction = __interaction(pwindow);

   if(pinteraction == nullptr)
   {

      throw ::exception(error_wrong_state);

   }

   if(pinteraction->get_app() == nullptr)
   {

      throw ::exception(error_wrong_state);

   }

   itask_t idthread = pinteraction->get_app()->get_itask();

   message_queue * pmq = get_message_queue(idthread, false);

   if(pmq == nullptr)
   {

      throw ::exception(error_wrong_state);

   }

   synchronous_lock ml(pmq->mutex());

   pmq->m_messagea.predicate_erase([=](MESSAGE & message)
   {

      return message.oswindow == pwindow->get_oswindow();

   });

   //return true;

}



