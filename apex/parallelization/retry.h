#pragma once


template < typename PREDICATE >
bool predicate_retry(const class time & timeStep, const class time & timeTotal, PREDICATE predicate)
{

   auto start = time::now();

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
      
      ::preempt(timeStep);

      if (start.elapsed() > timeTotal)
      {

         return false;

      }

   }

}


class CLASS_DECL_APEX retry
{
public:


   class ::time m_timeRetry;

   class ::time m_timeTimeout;


   retry(const class ::time & timeRetry, const class ::time& timeTimeout) :
      m_timeRetry(timeRetry),
      m_timeTimeout(timeTimeout)
   {

   };

   ~retry()
   {


   }

   template < typename PRED >
   bool operator()(PRED pred)
   {

      return ::predicate_retry(m_timeRetry, m_timeTimeout, pred);

   }

};




