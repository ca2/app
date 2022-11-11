#include "framework.h"
#include "_.h"
//#include "aura/graphics/draw2d/_component.h"
#include "acme/platform/timer.h"
#include "base/platform/session.h"
#include "axis/account/department.h"


void debug_pointer_defer_new()
{

//   ::pointer<::user::interaction>p;
//
//   p.create_new(this);


}


namespace userpresence
{


   department::department()
   {

      m_bUserPresenceFeatureRequired = false;

      m_bInit = false;

   }


   department::~department()
   {

   }


   void department::initialize(::particle * pparticle)
   {

      //auto estatus =

         ::acme::department::initialize(pparticle);

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }

      if(!acmesystem()->is_true("do_not_initialize_user_presence"))
      {
         // xxx
         // defer_initialize_user_presence();
         //
      }

      //return estatus;

   }


   void department::destroy()
   {

      defer_finalize_user_presence();

      //return ::success;

   }


   bool department::defer_initialize_user_presence()
   {

      delete_all_timers();

      return true;

   }


   bool department::defer_finalize_user_presence()
   {

      if(!is_initialized())
      {

         return true;

      }

      auto papp = get_app();

      if(papp->is_true("install") || papp->is_true("uninstall"))
      {

         return true;

      }

      if(papp->payload("app") == "simpledbcfg" || papp->payload("app") == "app-core/netnodelite")
      {

         return true;

      }

      if(!is_initialized())
      {

         return true;

      }

      delete_timer(2000);

      delete_timer(8888);

      m_ppresence.release();

      m_bInit = false;

      return true;

   }


   bool department::is_initialized()
   {

      return m_bInit;

   }


   void department::_001OnTimer(::timer * ptimer)
   {

      auto psession = get_session()->m_pbasesession;

      if(psession->account()->get_user() != nullptr)
      {

         if(m_ppresence.is_set())
         {

            if(ptimer->m_uEvent == 8888)
            {

               m_ppresence->defer_pulse_user_presence();

            }

         }

      }

   }


   void department::message_queue_message_handler(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   bool department::on_ui_mouse_message(::user::mouse * pmouse)
   {

      if(m_ppresence.is_set())
      {

         m_ppresence->on_ui_mouse_message(pmouse);

      }

      return true;

   }


} //namespace userpresence



