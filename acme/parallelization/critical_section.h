#pragma once


class CLASS_DECL_ACME critical_section
{
public:


   typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API construct(void *);
   typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API destruct(void *);
   typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API enter(void *);
   typedef CRITICAL_SECTION_FUNCTION_RETURN WINDOWS_API exit(void *);


   static construct * s_pconstruct;
   static destruct * s_pdestruct;
   static enter * s_penter;
   static exit * s_pexit;


#ifdef WINDOWS
   char sz[128]; // I hope it is enough to hold a union of CRITICAL_SECTION
   // It should be enough to hold union of a CRITICAL_SECTION
#else
   char sz[16]; // I hope it is enough to hold a union of pthread_mutex_t
   // It should be enough to hold union of a pthread_mutex_t
#endif


   critical_section() { s_pconstruct(this); }
   ~critical_section() { s_pdestruct(this); }


   inline void lock() { s_penter(this); }
   inline void unlock() { s_pexit(this); }





};



class CLASS_DECL_ACME critical_section_lock
{
public:


   critical_section * m_criticalsection;


   inline critical_section_lock(critical_section * pcs) : m_criticalsection(pcs) { if (m_criticalsection != nullptr) m_criticalsection->lock(); }
   inline ~critical_section_lock() { if (m_criticalsection != nullptr) m_criticalsection->unlock(); }


};



