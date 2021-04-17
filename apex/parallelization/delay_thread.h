#pragma once


class delay_thread :
   virtual public thread
{

public:

   ::u32       m_dwSleep;

   //delay_thread(::object * pobject, ::u32 dwSleep = 1000) //:
   delay_thread(::u32 dwSleep = 1000) //:
      //::object(pobject)
   {

      m_dwSleep = dwSleep;
      //initialize(pobject);


   }


   ::e_status     run()
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
class predicate_delay_thread :
   virtual public delay_thread
{
public:

   
   PRED &      m_predicate;
   
   
   predicate_delay_thread(::object * pobject, PRED pred, ::u32 dwSleep = 1000) :
      m_predicate(pred),
      delay_thread(dwSleep)
   {
      
   }


   virtual void do_delayed() override
   {

      m_predicate();

   }
   

};


template < typename PRED >
delay_thread * predicate_delay(::object * pobject, millis tickDelay, PRED pred)
{

   auto pthread  = __new(predicate_delay_thread < PRED >(pobject, pred, tickDelay));

   pthread->begin();

   return pthread;

}



