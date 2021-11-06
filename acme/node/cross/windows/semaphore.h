#pragma once


class CLASS_DECL_ACME semaphore :
   virtual public synchronization_object
{
public:

   string            m_strName;

#if defined(ANDROID)

   ::i32              m_lMaxCount;
   sem_t *           m_psem;

#elif defined(LINUX) || defined(APPLEOS)

   ::i32              m_lMaxCount;
   i32           m_hsync;

#endif

   semaphore(::i32 lInitialCount = 1, ::i32 lMaxCount = 1, const char * pstrName=nullptr, sync_options * poptions = nullptr);

   virtual ~semaphore();


#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
//   using matter::lock;
   virtual synchronization_result wait(const duration & durationTimeout) override;
#endif

   virtual bool unlock() override;
   virtual bool unlock(::i32 lCount, ::i32 * prevCount = nullptr) override;


};


