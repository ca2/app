#pragma once


//namespace topic
//{
//

   class CLASS_DECL_APEX context :
      virtual public matter
   {
   public:


      ::i64       m_iUpdateSerial;
      bool        m_bFork;


      context();

      virtual ~context();


      virtual void start_task();


      virtual bool is_up_to_date(const ::topic * phandler) const;

      virtual void set_up_to_date(const ::topic * phandler);


   };


   using context_pointer = __pointer(context);

//
//} // namespace topic
//
//
//
