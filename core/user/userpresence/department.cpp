#include "framework.h"
#include "_.h"


void debug_pointer_defer_new()
{

   __pointer(::user::interaction) p;

   p.create_new();


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


   ::e_status department::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      if(!System->is_true("do_not_initialize_user_presence"))
      {
         // xxx
         // defer_initialize_user_presence();
         //
      }

      return estatus;

   }


   void department::finalize()
   {

      defer_finalize_user_presence();

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

      if(Application.is_true("install") || Application.is_true("uninstall"))
      {

         return true;

      }

      if(Application.payload("app") == "simpledbcfg" || Application.payload("app") == "app-core/netnodelite")
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

      auto psession = Session;

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

      UNREFERENCED_PARAMETER(pmessage);

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



