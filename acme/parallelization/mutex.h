#pragma once


//

#undef ACME_MUTEX_DEBUG

class CLASS_DECL_ACME mutex :
   virtual public particle
{
public:

#ifdef ACME_MUTEX_DEBUG
   string                  m_strThread;
   itask                 m_itask;
#endif

//#if !defined(WINDOWS)
//
//   pthread_mutex_t         m_pmutex;
//   string                  m_strName;
//
//#ifdef MUTEX_COND_TIMED
//
//   pthread_cond_t          m_cond;
//
//#endif
//
//#if defined(MUTEX_COND_TIMED) || defined(MUTEX_NAMED_FD)
//
//   pthread_t               m_thread;
//   int                     m_count;
//
//#endif
//
//#if defined(MUTEX_NAMED_POSIX)
//
//   sem_t *                 m_psem; // as of 2016-11-26
//   // not implemented (err=38) on android-19
//#elif defined(MUTEX_NAMED_FD)
//
//   int                     m_iFd;
//
//#elif defined(MUTEX_NAMED_VSEM)
//
//   key_t                   m_key;
//   int                     m_semid;
//
//#endif
//
//#endif

   //bool                    m_bAlreadyExists;


//#ifdef WINDOWS
   //mutex(enum_create_new ecreatenew, const_char_pointer pstrName, void * posdata, bool bOwner = true);
//#elif defined(MUTEX_NAMED_POSIX)
//   mutex(enum_create_new ecreatenew = create_new, const ::scoped_string & scopedstr = nullptr, const_char_pointer pstrName,sem_t * psem,bool bOwner = true);
//#elif defined(MUTEX_NAMED_FD)
//   mutex(enum_create_new ecreatenew, const_char_pointer pstrName, int iFd, bool bOwner = true);
//#elif defined(MUTEX_NAMED_VSEM)
//   mutex(enum_create_new ecreatenew, const_char_pointer pstrName,key_t key, int semid, bool bOwner = true);
//#endif
   //mutex(::particle * pparticle, bool bInitiallyOwn, const_char_pointer lpszName ARG_SEC_ATTRS_DEF);
   //mutex(enum_create_new ecreatenew = e_create_new, bool bInitiallyOwn = false);
   mutex();
   ~mutex() override;


//#ifndef WINDOWS
//
//   //virtual ::e_status lock() override;
//
//   //virtual ::e_status lock(const class time & timeWait) override;
//
//   virtual void _wait() override;
//
//   virtual bool _wait(const class time & timeWait) override;
//
//#endif

   using particle::unlock;
   void unlock() override  = 0;

   //virtual bool already_exists();


   ///static ::pointer < ::mutex >open_mutex(::matter * pmatter, const_char_pointer lpszName) {return ::open_mutex(pmatter, lpszName);}


};


CLASS_DECL_ACME void wait_until_mutex_does_not_exist(const_char_pointer lpszName);



CLASS_DECL_ACME ::pointer< ::mutex > get_ui_destroyed_mutex();


