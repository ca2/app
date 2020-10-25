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

      __defer_construct(m_peventCompletion);

   }
public:


   var                                    m_var;
   __pointer(manual_reset_event)          m_peventCompletion;


   virtual ~sync_future() {}


   inline virtual void operator()(const var & var) override
   {

      m_var = var;

      m_peventCompletion->SetEvent();

   }

   inline sync_result wait(const ::duration& duration = duration::infinite())
   {

      return m_peventCompletion->wait(duration);

   }


};


inline __pointer(sync_future) __sync_future()
{

   return __new(sync_future);

}



