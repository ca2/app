#pragma once


CLASS_DECL_ACME ::mutex open_mutex(const char * lpszName);


class CLASS_DECL_ACME mutex :
   virtual public sync
{
public:


#if !defined(WINDOWS)

   pthread_mutex_t         m_mutex;
   string                  m_strName;

#ifdef MUTEX_COND_TIMED

   pthread_cond_t          m_cond;

#endif

#if defined(MUTEX_COND_TIMED) || defined(MUTEX_NAMED_FD)

   pthread_t               m_thread;
   int                     m_count;

#endif

#if defined(MUTEX_NAMED_POSIX)

   sem_t *                 m_psem; // as of 2016-11-26
   // not implemented (err=38) on android-19
#elif defined(MUTEX_NAMED_FD)

   int                     m_iFd;

#elif defined(MUTEX_NAMED_VSEM)

   key_t                   m_key;
   i32                     m_semid;

#endif

#endif

   bool                    m_bAlreadyExists;


#ifdef WINDOWS
   ::mutex(enum_create_new ecreatenew, const char * pstrName, void * posdata, bool bOwner = true);
#elif defined(MUTEX_NAMED_POSIX)
   ::mutex(enum_create_new ecreatenew = create_new, const char * psz = nullptr, const char * pstrName,sem_t * psem,bool bOwner = true);
#elif defined(MUTEX_NAMED_FD)
   ::mutex(enum_create_new ecreatenew, const char * pstrName, int iFd, bool bOwner = true);
#elif defined(MUTEX_NAMED_VSEM)
   ::mutex(enum_create_new ecreatenew, const char * pstrName,key_t key, i32 semid, bool bOwner = true);
#endif
   ::mutex(enum_create_new ecreatenew, bool bInitiallyOwn, const char * lpszName, sync_options * psyncoptions = nullptr);
   ::mutex(enum_create_new ecreatenew = e_create_new, bool bInitiallyOwn = false);
   virtual ~mutex();


#ifndef WINDOWS

   virtual bool lock();

   virtual bool lock(const duration & durationTimeout);

   virtual sync_result wait();

   virtual sync_result wait(const duration & durationTimeout);

#endif

   using sync::unlock;
   virtual bool unlock();


   bool already_exists();


   static ::mutex open_mutex(const char * lpszName) {return ::open_mutex(lpszName);}


};


CLASS_DECL_ACME void wait_until_mutex_does_not_exist(const char * lpszName);



CLASS_DECL_ACME ::mutex * get_ui_destroyed_mutex();







namespace install
{


   class CLASS_DECL_ACME ::mutex :
      public ::mutex
   {
   public:

      // null_dacl_sync_options
      ::mutex(string strPlatform, string strSuffix = "");

   };


   class CLASS_DECL_ACME admin_mutex :
      public ::mutex
   {
   public:

      // null_dacl_sync_options
      admin_mutex(string strPlatform, string strSuffix = "");

   };




} // namespace install




