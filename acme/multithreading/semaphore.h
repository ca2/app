#pragma once


class CLASS_DECL_ACME semaphore :
   virtual public sync
{
public:

   string            m_strName;

#if defined(ANDROID)

   LONG              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(APPLEOS)

   LONG              m_lMaxCount;
   i32           m_hsync;

#endif

   semaphore(LONG lInitialCount = 1, LONG lMaxCount = 1, const char * pstrName=nullptr, LPSECURITY_ATTRIBUTES psaAttributes = nullptr);

   virtual ~semaphore();


#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
//   using elemental::lock;
   virtual sync_result wait(const duration & durationTimeout) override;
#endif

   virtual bool unlock() override;
   virtual bool unlock(LONG lCount, LPLONG prevCount = nullptr) override;


};


