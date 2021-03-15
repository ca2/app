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


   ::e_status department::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::department::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      if(!psystem->is_true("do_not_initialize_user_presence"))
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

      if(papplication->is_true("install") || papplication->is_true("uninstall"))
      {

         return true;

      }

      if(papplication->payload("app") == "simpledbcfg" || papplication->payload("app") == "app-core/netnodelite")
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

      auto psession = get_session();

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



