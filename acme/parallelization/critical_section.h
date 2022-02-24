#pragma once

//#ifdef WINDOWS
//

class CLASS_DECL_ACME critical_section
{
public:


   //typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API construct(void *);
   //typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API destruct(void *);
   //typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API enter(void *);
   //typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API exit(void *);


   //static construct * s_pconstruct;
   //static destruct * s_pdestruct;
   //static enter * s_penter;
   //static exit * s_pexit;


#ifdef WINDOWS
   char sz[128]; // I hope it is enough to hold a union of CRITICAL_SECTION
   // It should be enough to hold union of a CRITICAL_SECTION
#else
   char sz[80]; // I hope it is enough to hold a union of pthread_mutex_t
   // It should be enough to hold union of a pthread_mutex_t
#endif


   critical_section();
   ~critical_section();


   void lock();
   void unlock();





};



class CLASS_DECL_ACME critical_section_lock
{
public:



   bool m_bLocked;
   critical_section * m_pcriticalsection;


   inline critical_section_lock(critical_section* pcs, bool bInitialLock = true) : 
      m_pcriticalsection(pcs), 
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

            m_bLocked = true;

            m_pcriticalsection->lock();

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

         }
      }

   }

};



