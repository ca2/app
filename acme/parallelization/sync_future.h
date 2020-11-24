#pragma once


class sync_future;


inline ＿＿pointer(sync_future) ＿＿sync_future();



class CLASS_DECL_ACME sync_future : 
   virtual public matter
{
protected:

   friend ＿＿pointer(sync_future) ＿＿sync_future();

   sync_future()
   {

      ＿＿defer_construct(m_peventCompletion);

   }
public:


   payload                                    m_var;
   ＿＿pointer(manual_reset_event)          m_peventCompletion;


   virtual ~sync_future() {}


   inline virtual void operator()(const payload & payload) override
   {

      m_var = payload;

      m_peventCompletion->SetEvent();

   }

   inline sync_result wait(const ::duration& duration = duration::infinite())
   {

      return m_peventCompletion->wait(duration);

   }


};


inline ＿＿pointer(sync_future) ＿＿sync_future()
{

   return ＿＿new(sync_future);

}



