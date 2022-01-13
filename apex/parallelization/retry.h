#pragma once


template < typename PREDICATE >
bool predicate_retry(const ::duration & durationStep, const ::duration & durationTotal, PREDICATE predicate)
{

   auto start = duration::now();

   while (true)
   {

      try
      {

         //if (predicate())

         predicate();
         //{

         //   return true;

         //}

      }
      catch (...)
      {

         return false;

      }
      
      ::preempt(durationStep);

      if (start.elapsed() > durationTotal)
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




