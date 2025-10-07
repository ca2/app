#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_message_queue.h"
#include "aura/platform/message_queue.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/user/user/interaction_thread.h"
#include "aura/windowing/window.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/application.h"


//CLASS_DECL_AURA void message_queue_post(::windowing::window * pwindow, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)
//{
//
//   //
//
//   //auto puser = psession->m_puser;
//
//   //auto pwindowing = system()->windowing();
//
//   //auto pwindow = pwindowing->window(oswindow);
//
//   auto pinteraction = pwindow->m_puserinteraction;
//
//   if (pinteraction == nullptr)
//   {
//
//      throw ::exception(error_wrong_state);
//
//   }
//
//   auto pmq = pinteraction->m_pthreadUserInteraction->get_message_queue();
//
//   if (!pmq)
//   {
//
//      throw ::exception(error_wrong_state);
//
//   }
//
//   //if (!
//   
//   pmq->post_message(pwindow->oswindow(), eusermessage, wparam, lparam);
//   //{
//
//   //   return false;
//
//   //}
//
//   //return true;
//
//}



CLASS_DECL_AURA void mq_erase_window_from_all_queues(::windowing::window * pwindow)
{

   //

   //auto puser = psession->m_puser;

   //auto pwindowing = system()->windowing();

   //auto pwindow = pwindowing->window(oswindow);

   auto puserinteraction = pwindow->user_interaction();

   auto puserframe = puserinteraction;

   if(!puserframe)
   {

      throw ::exception(error_wrong_state);

   }

   if(puserframe->get_app() == nullptr)
   {

      throw ::exception(error_wrong_state);

   }

   ::cast < ::thread > pthread = puserframe->application();

   auto taskindex = pthread->m_taskindex;

   message_queue * pmessagequeue = ::system()->m_ptaskmessagequeue->get_message_queue(taskindex, false);

   if(pmessagequeue == nullptr)
   {

      throw ::exception(error_wrong_state);

   }

   synchronous_lock ml(pmessagequeue->synchronization(), pmessagequeue, SYNCHRONOUS_LOCK_SUFFIX);

   pmessagequeue->m_messagea.predicate_erase([=](MESSAGE & message)
   {

      return message.m_oswindow == pwindow->oswindow();

   });

   //return true;

}



