#include "framework.h"
#include "acme/id.h"
//#include "apex/message/application.h"


namespace acme
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

      ::object::initialize(pobject);

   }


   void department::call_member(::i64 iId)
   {

      switch (iId)
      {
      case id_process_init:
         return process_init();
      case id_init:
         return init();
      case id_init1:
         return init1();
      case id_init2:
         return init2();
      case id_init3:
         return init3();
      case id_init_instance:
         return init_instance();
      case id_term3:
         return term3();
      case id_term1:
         return term1();
      case id_term2:
         return term2();
      case id_term:
         return term();
      case id_term_instance:
         return term_instance();


      }

      throw_status(error_not_found);

   }

   //void department::connect_to_context_signal()
   //{

   //   m_pcontext->add_handler(id_none, this, &department::on_application_message);

   //}


   void department::process_init()
   {

      //return ::success;

   }


   void department::init()
   {

      //return ::success;

   }


   void department::init1()
   {

      //return ::success;

   }


   void department::init2()
   {

      //return ::success;

   }


   void department::init3()
   {

      //return ::success;

   }

   void department::init_instance()
   {

      //return ::success;

   }


   void department::term_instance()
   {

      //return ::success;

   }


   void department::term()
   {

      //return ::success;

   }


   void department::term3()
   {

      //return ::success;

   }


   void department::term2()
   {

      //return ::success;

   }


   void department::term1()
   {

      //return ::success;

   }


} // namespace acme




