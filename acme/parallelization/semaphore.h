#pragma once



#include "acme/operating_system/security_attributes.h"


class CLASS_DECL_ACME semaphore :
   virtual public particle
{
public:


   string            m_strName;

#ifdef WINDOWS

   ::hsynchronization      m_handleSemaphore;

#elif defined(ANDROID)

   int              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(__APPLE__) || defined(__BSD__)

   int         m_lMaxCount;
   i32           m_hsync;

#endif

   semaphore(int lInitialCount = 1, int lMaxCount = 1, const char * pstrName=nullptr, security_attributes * psecurityattributes = nullptr);
   ~semaphore() override;


//#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS) || defined(FREEBSD) || defined(OPENBSD)
//   using matter::lock;
   bool _wait(const class time & timeWait) override;
//#endif

   void unlock() override;
   void unlock(int lCount, int * prevCount = nullptr) override;


};



