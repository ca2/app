#pragma once


class critical_section_impl;


class CLASS_DECL_ACME critical_section
{
public:


   critical_section_impl* m_pimpl;


   critical_section();
   ~critical_section();


   void lock();
   void unlock();


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



