#pragma once


#ifdef WINDOWS 
#define ARG_SEC_ATTRS_DEF , void * psaAttributes = nullptr
#define ARG_SEC_ATTRS , void * psaAttributes
#define PARAM_SEC_ATTRS (LPSECURITY_ATTRIBUTES) psaAttributes
#define ADD_PARAM_SEC_ATTRS , PARAM_SEC_ATTRS
#else
#define ARG_SEC_ATTRS_DEF 
#define ARG_SEC_ATTRS
#define PARAM_SEC_ATTRS
#define ADD_PARAM_SEC_ATTRS 
#endif


class CLASS_DECL_ACME semaphore :
   virtual public sync
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

   semaphore(::i32 lInitialCount = 1, ::i32 lMaxCount = 1, const char * pstrName=nullptr ARG_SEC_ATTRS_DEF);
   virtual ~semaphore();


#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS)
//   using matter::lock;
   virtual sync_result wait(const duration & durationTimeout) override;
#endif

   virtual bool unlock() override;
   virtual bool unlock(::i32 lCount, ::i32 * prevCount = nullptr) override;


};


