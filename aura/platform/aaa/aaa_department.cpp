#include "framework.h"


namespace aura
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
   void department::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void department::connect_to_application_signal()
   {

      get_app()->add_route(this,&department::on_application_message);

   }


   void department::process_init()
   {

      return ::success;

   }


   void department::init()
   {

      return ::success;

   }


   void department::init1()
   {

      return ::success;

   }


   void department::init2()
   {

      return ::success;

   }


   void department::init3()
   {

      return ::success;

   }

   void department::init_instance()
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

      __pointer(::aura::application_message) pappsignal(pmessage);

      try
      {
         if(pappsignal->m_esignal == ::aura::application_message_process_init)
         {

            pappsignal->m_bOk = process_init();

         }
         else if(pappsignal->m_esignal == ::aura::application_message_init)
         {

            pappsignal->m_bOk = init();

         }
         else if(pappsignal->m_esignal == ::aura::application_message_init1)
         {

            pappsignal->m_bOk = init1();

         }
         else if(pappsignal->m_esignal == ::aura::application_message_init2)
         {

            pappsignal->m_bOk = init2();

         }
         else if(pappsignal->m_esignal == ::aura::application_message_init3)
         {

            pappsignal->m_bOk = init3();

         }
         else if(pappsignal->m_esignal == ::aura::application_message_init_instance)
         {

            pappsignal->m_bOk = init_instance();

         }
         else if(pappsignal->m_esignal == ::aura::application_message_term_instance)
         {

            term_instance();

            pappsignal->m_bOk = true;

         }
         else if(pappsignal->m_esignal == ::aura::application_message_term3)
         {

            term3();

            pappsignal->m_bOk = true;

         }
         else if(pappsignal->m_esignal == ::aura::application_message_term2)
         {

            term2();

            pappsignal->m_bOk = true;

         }
         else if(pappsignal->m_esignal == ::aura::application_message_term1)
         {

            term1();

            pappsignal->m_bOk = true;

         }
         else if(pappsignal->m_esignal == ::aura::application_message_process_term)
         {

            term();

            pappsignal->m_bOk = true;

         }

      }
      catch(...)
      {

         pappsignal->m_bOk = false;

      }

   }







} // namespace aura


