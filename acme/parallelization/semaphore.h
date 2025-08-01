#pragma once



#include "acme/operating_system/security_attributes.h"


class CLASS_DECL_ACME semaphore :
   virtual public particle
{
public:


   string            m_strName;

#ifdef WINDOWS

   ::hsynchronization      m_handleSemaphore;

#elif defined(__ANDROID__)

   int              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(__APPLE__) || defined(__BSD__)

   int         m_lMaxCount;
   int           m_hsync;

#endif

   semaphore(int lInitialCount = 1, int lMaxCount = 1, const_char_pointer pstrName=nullptr, security_attributes * psecurityattributes = nullptr);
   ~semaphore() override;


//#if defined(__APPLE__) || defined(LINUX) || defined(__ANDROID__) || defined(SOLARIS) || defined(FREEBSD) || defined(OPENBSD)
//   using matter::lock;
   bool _wait(const class time & timeWait) override;
//#endif

   void unlock() override;
   void unlock(int lCount, int * prevCount = nullptr) override;


};



