#pragma once


namespace promise
{


   class CLASS_DECL_ACME context :
      virtual public matter
   {
   public:


      ::i64       m_iUpdateSerial;
      bool        m_bFork;


      context();

      virtual ~context();


      virtual ::e_status start_task();


      virtual bool is_up_to_date(const ::promise::subject * phandler) const;

      virtual void set_up_to_date(const ::promise::subject * phandler);


   };


   using context_pointer = __pointer(context);


} // namespace promise



