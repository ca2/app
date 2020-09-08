#pragma once



template < typename PRED >
bool pred_retry(duration durationRetry, ::duration durationTimeout, PRED pred)
{

   ::tick tickStart = tick::now();

   tick tickRetry = durationRetry.get_total_milliseconds();

   tick tickTimeout = durationTimeout.get_total_milliseconds();

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

      if (!thread_sleep(tickRetry))
      {

         return false;

      }

      if (tickStart.elapsed() > tickTimeout)
      {

         return false;

      }

   }

}


class CLASS_DECL_ACME retry
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

      return ::pred_retry(m_durationRetry, m_durationTimeout, pred);

   }

};




