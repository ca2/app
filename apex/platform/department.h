#pragma once


namespace apex
{


   class CLASS_DECL_APEX department :
      virtual public ::object
   {
   public:


      department();
      virtual ~department();


      virtual ::estatus initialize(::layered * pobjectContext);


      virtual void connect_to_application_signal();

      virtual ::estatus process_init();

      virtual ::estatus init();
      virtual ::estatus init1();
      virtual ::estatus init2();
      virtual ::estatus init3();
      virtual ::estatus init_instance();

      virtual void term_instance();
      virtual void term3();
      virtual void term2();
      virtual void term1();
      virtual void term();

      void on_application_message(::message::message * pmessage);


   };


} // namespace apex



