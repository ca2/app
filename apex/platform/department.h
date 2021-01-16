#pragma once


namespace apex
{


   class CLASS_DECL_APEX department :
      virtual public ::object
   {
   public:


      department();
      virtual ~department();


      virtual ::e_status initialize(::layered * pobjectContext);


      virtual void connect_to_application_signal();

      virtual ::e_status process_init();

      virtual ::e_status init();
      virtual ::e_status init1();
      virtual ::e_status init2();
      virtual ::e_status init3();
      virtual ::e_status init_instance();

      virtual void term_instance();
      virtual void term3();
      virtual void term2();
      virtual void term1();
      virtual void term();

      void on_application_message(::message::message * pmessage);


   };


} // namespace apex



