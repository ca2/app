#pragma once


class critical_section_impl;


class CLASS_DECL_ACME critical_section
{
public:


#ifdef PARALLELIZATION_PTHREAD

   pthread_mutex_t m_mutex;

   critical_section()
{
   
   ::pthread_recursive_mutex_init(&m_mutex);
   
}


~critical_section()
{
   
   ::pthread_mutex_destroy(&m_mutex);
   
}


void lock()
{
   
   ::pthread_mutex_lock(&m_mutex);
   
}


void unlock()
{
   
   ::pthread_mutex_unlock(&m_mutex);
   
}


#else

   CRITICAL_SECTION m_criticalsection;
   
   
critical_section()
{
   
   ::InitializeCriticalSection(&m_criticalsection);

}


~critical_section()
{
   
   ::DeleteCriticalSection(&m_criticalsection);

}


void lock()
{
   
   ::EnterCriticalSection(&m_criticalsection);

}


void unlock()
{
   
   ::LeaveCriticalSection(&m_criticalsection);

}


#endif



};



class CLASS_DECL_ACME critical_section_lock
{
public:


   bool                    m_bLocked;
   critical_section *      m_pcriticalsection;


   inline critical_section_lock(critical_section * pcriticalsection, bool bInitialLock = true) : 
      m_pcriticalsection(pcriticalsection),
      m_bLocked(false) 
   { 
      
      if (bInitialLock)
      {

         lock();

      }

   }


   inline ~critical_section_lock()
   { 
      
      unlock(); 
   
   }


   void lock()
   {

      if (m_pcriticalsection != nullptr)
      {

         if (!m_bLocked)
         {

            m_pcriticalsection->lock();

            m_bLocked = true;

         }

      }

   }


   void unlock()
   {

      if (m_bLocked)
      {


         if (m_pcriticalsection != nullptr)
         {

            m_pcriticalsection->unlock();

            m_bLocked = false;

         }

      }

   }


};



