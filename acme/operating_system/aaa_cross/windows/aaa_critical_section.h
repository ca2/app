#pragma once


class CLASS_DECL_ACME critical_section :
   virtual public ::matter
{
public:


   critical_section();
   virtual ~critical_section();


   virtual void lock() = 0;

   virtual void unlock() = 0;


   virtual bool initialize() = 0;

};



class CLASS_DECL_ACME critical_section_lock
{
public:


   critical_section * m_criticalsection;


   inline critical_section_lock(critical_section * pcriticalsection): m_criticalsection(pcriticalsection) { if(m_criticalsection != nullptr) m_criticalsection->lock(); }
   inline ~critical_section_lock() { if(m_criticalsection != nullptr) m_criticalsection->unlock(); }


};




