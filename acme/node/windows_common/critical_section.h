#pragma once


namespace windows
{


   class CLASS_DECL_ACME critical_section :
      virtual public critical_section
   {
   public:


      CRITICAL_SECTION        m_criticalsection;

      critical_section();
      virtual ~critical_section();


      virtual void lock();

      virtual void unlock();


   };







} // namespace windows






class CLASS_DECL_ACME critical_section_lock
{
public:


   CRITICAL_SECTION * m_criticalsection;


   inline critical_section_lock(CRITICAL_SECTION * pcriticalsection) : m_criticalsection(pcriticalsection) { if (m_criticalsection != nullptr) ::EnterCriticalSection(m_criticalsection); }
   inline ~critical_section_lock() { if (m_criticalsection != nullptr) ::LeaveCriticalSection(m_criticalsection); }


};


