#pragma once


class sync_future;


inline __pointer(sync_future) __sync_future();



class CLASS_DECL_ACME sync_future : 
   virtual public matter
{
protected:

   friend __pointer(sync_future) __sync_future();

   sync_future()
   {

      m_peventCompletion = __new(manual_reset_event);

   }
public:


   ::payload                                    m_var;
   __pointer(manual_reset_event)          m_peventCompletion;


   virtual ~sync_future() {}


   void operator()(const ::payload & payload) override
   {

      m_var = payload;

      m_peventCompletion->SetEvent();

   }

   
   void wait(const ::duration& duration = duration::infinite()) override
   {

      return m_peventCompletion->wait(duration);

   }


};


inline __pointer(sync_future) __sync_future()
{

   return __new(sync_future);

}



