#pragma once



template < typename PRED >
bool predicate_retry(duration durationRetry, ::duration durationTimeout, PRED pred)
{

   auto tickStart = millis::now();

   auto tickRetry = durationRetry.u32_millis();

   auto tickTimeout = durationTimeout.u32_millis();

   while (true)
   {

      try
      {

         if (pred())
         {

            return true;

         }

      }
      catch (...)
      {

         return false;

      }

      if (!task_sleep(tickRetry))
      {

         return false;

      }

      if (tickStart.elapsed() > tickTimeout)
      {

         return false;

      }

   }

}


class CLASS_DECL_APEX retry
{
public:


   ::duration m_durationRetry;

   ::duration m_durationTimeout;


   retry(duration durationRetry, ::duration durationTimeout) :
      m_durationRetry(durationRetry),
      m_durationTimeout(durationTimeout)
   {

   };

   ~retry()
   {


   }

   template < typename PRED >
   bool operator()(PRED pred)
   {

      return ::predicate_retry(m_durationRetry, m_durationTimeout, pred);

   }

};




