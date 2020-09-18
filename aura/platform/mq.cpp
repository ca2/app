#include "framework.h"
#include "acme/multithreading/mq.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif

// apex commented
CLASS_DECL_AURA int_bool mq_post_message(oswindow oswindow, UINT message, WPARAM wparam, LPARAM lparam)
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

   if (!pmq->post_message(oswindow, message, wparam, lparam))
   {

      return FALSE;

   }

   return TRUE;

}



