#pragma once


class delay_thread :
   virtual public thread
{

public:

   ::u32       m_dwSleep;

   delay_thread(::object * pobject, ::u32 dwSleep = 1000) :
      ::object(pobject)
   {

      m_dwSleep = dwSleep;

   }


   ::estatus     run()
   {

      while (true)
      {

         ::u32 dwSleep = m_dwSleep;

         if (dwSleep == 0)
         {

            break;

         }

         m_dwSleep = 0;

         if (!task_sleep(dwSleep))
         {

            return success_exit_thread;

         }

      }

      do_delayed();

      return ::success;

   }

   virtual void do_delayed()
   {

   }

};

template < typename PRED >
class pred_delay_thread :
   virtual public delay_thread
{
public:

   
   PRED &      m_pred;
   
   
   pred_delay_thread(::object * pobject, PRED pred, ::u32 dwSleep = 1000) :
      m_pred(pred),
      ::object(pobject),
      delay_thread(pobject, dwSleep)
   {
      
   }


   virtual void do_delayed() override
   {

      m_pred();

   }
   

};


template < typename PRED >
delay_thread * pred_delay(::object * pobject, millis tickDelay, PRED pred)
{

   auto point  = __new(pred_delay_thread < PRED >(pobject, pred, tickDelay));

   point->begin();

   return point;

}
