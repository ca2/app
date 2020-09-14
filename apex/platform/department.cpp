#include "framework.h"
#include "apex/message/application.h"


namespace apex
{


   department::department()
   {

   }


   department::~department()
   {

   }


   // designed to be in constructors, so should
   // not contain advanced initialization as the
   // papp application pointer may be incompletely
   // initialized specially its virtual functions.
   ::estatus department::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void department::connect_to_application_signal()
   {

      get_context_application()->add_route(this,&department::on_application_message);

   }


   ::estatus department::process_init()
   {

      return ::success;

   }


   ::estatus department::init()
   {

      return ::success;

   }


   ::estatus department::init1()
   {

      return ::success;

   }


   ::estatus department::init2()
   {

      return ::success;

   }


   ::estatus department::init3()
   {

      return ::success;

   }

   ::estatus department::init_instance()
   {

      return ::success;

   }


   void department::term_instance()
   {
   }


   void department::term()
   {

   }

   void department::term3()
   {

   }

   void department::term2()
   {

   }

   void department::term1()
   {

   }

   void department::on_application_message(::message::message * pmessage)
   {

      SCAST_PTR(::message::application,papplicationsignal,pmessage);

      try
      {
         if(papplicationsignal->m_eapplication == ::message::application_process_init)
         {

            papplicationsignal->m_bOk = process_init();

         }
         else if(papplicationsignal->m_eapplication == ::message::application_init)
         {

            papplicationsignal->m_bOk = init();

         }
         else if(papplicationsignal->m_eapplication == ::message::application_init1)
         {

            papplicationsignal->m_bOk = init1();

         }
         else if(papplicationsignal->m_eapplication == ::message::application_init2)
         {

            papplicationsignal->m_bOk = init2();

         }
         else if(papplicationsignal->m_eapplication == ::message::application_init3)
         {

            papplicationsignal->m_bOk = init3();

         }
         else if(papplicationsignal->m_eapplication == ::message::application_init_instance)
         {

            papplicationsignal->m_bOk = init_instance();

         }
         else if(papplicationsignal->m_eapplication == ::message::application_term_instance)
         {

            term_instance();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_eapplication == ::message::application_term3)
         {

            term3();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_eapplication == ::message::application_term2)
         {

            term2();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_eapplication == ::message::application_term1)
         {

            term1();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_eapplication == ::message::application_process_term)
         {

            term();

            papplicationsignal->m_bOk = true;

         }

      }
      catch(...)
      {

         papplicationsignal->m_bOk = false;

      }

   }


} // namespace apex




