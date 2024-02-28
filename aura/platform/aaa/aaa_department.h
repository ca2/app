#pragma once


namespace aura
{


   class CLASS_DECL_AURA department :
      virtual public ::object
   {
   public:


      department();
      virtual ~department();


      virtual void initialize(::particle * pparticle);


      virtual void connect_to_application_signal();

      virtual void process_init();

      virtual void init();
      virtual void init1();
      virtual void init2();
      virtual void init3();
      virtual void init_instance();

      virtual void term_instance();
      virtual void term3();
      virtual void term2();
      virtual void term1();
      virtual void term();

      void on_application_message(::message::message * pmessage);


   };


} // namespace aura



