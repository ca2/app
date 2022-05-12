#pragma once


class CLASS_DECL_ACME critical_section
{
public:


#ifdef WINDOWS
   char sz[128 + 32]; // I hope it is enough to hold a union of CRITICAL_SECTION
   // It should be enough to hold union of a CRITICAL_SECTION
#else
   char sz[80 + 32]; // I hope it is enough to hold a union of pthread_mutex_t
   // It should be enough to hold union of a pthread_mutex_t
#endif


   critical_section();
   ~critical_section();


   void * aligned_this() { return (void *) ((((::uptr)(byte *)this) + 31) & (~(::uptr)31)); }


   void lock();
   void unlock();


};


class CLASS_DECL_ACME critical_section_lock
{
public:


   bool                    m_bLocked;
   critical_section *      m_pcriticalsection;


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



