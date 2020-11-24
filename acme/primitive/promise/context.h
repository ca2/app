#pragma once


namespace promise
{


   class CLASS_DECL_ACME machine :
           virtual public matter
   {
   public:


      ::i64    m_iUpdateSerial;
      bool     m_bFork;


      machine();

      virtual ~machine();


      virtual ::estatus start_task();


      inline bool is_up_to_date(::promise::handler * pmanager) const;

      virtual void set_up_to_date(::promise::handler * pmanager);


   };


   using machine_pointer = ＿＿pointer(machine);


} // namespace promise



