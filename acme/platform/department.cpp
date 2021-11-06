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
   ::e_status department::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status department::call_member(::i64 iId)
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

      return error_not_found;

   }

   //void department::connect_to_context_signal()
   //{

   //   m_pcontext->add_handler(id_none, this, &department::on_application_message);

   //}


   ::e_status department::process_init()
   {

      return ::success;

   }


   ::e_status department::init()
   {

      return ::success;

   }


   ::e_status department::init1()
   {

      return ::success;

   }


   ::e_status department::init2()
   {

      return ::success;

   }


   ::e_status department::init3()
   {

      return ::success;

   }

   ::e_status department::init_instance()
   {

      return ::success;

   }


   ::e_status department::term_instance()
   {

      return ::success;

   }


   ::e_status department::term()
   {

      return ::success;

   }


   ::e_status department::term3()
   {

      return ::success;

   }


   ::e_status department::term2()
   {

      return ::success;

   }


   ::e_status department::term1()
   {

      return ::success;

   }


} // namespace acme




