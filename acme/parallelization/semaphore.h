#pragma once


// #include "acme/primitive/string/string.h"
#include "acme/operating_system/security_attributes.h"


class CLASS_DECL_ACME semaphore :
   virtual public particle
{
public:


   string            m_strName;

#ifdef WINDOWS

   ::hsynchronization      m_handleSemaphore;

#elif defined(ANDROID)

   ::i32              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(__APPLE__) || defined(FREEBSD)

   ::i32         m_lMaxCount;
   i32           m_hsync;

#endif

   semaphore(::i32 lInitialCount = 1, ::i32 lMaxCount = 1, const char * pstrName=nullptr, security_attributes * psecurityattributes = nullptr);
   ~semaphore() override;


#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS) || defined(FREEBSD)
//   using matter::lock;
   bool _wait(const class time & timeWait) override;
#endif

   void unlock() override;
   void unlock(::i32 lCount, ::i32 * prevCount = nullptr) override;


};



