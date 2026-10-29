#pragma once

//#include "acme/prototype/prototype/particle.h"
#include "acme/parallelization/synchronization_object.h"

namespace parallelization
{

   class mutex_implementation;

   class CLASS_DECL_ACME mutex :
      virtual public ::synchronization_object
   {
   public:

#if defined(PARALLELIZATION_PTHREAD)
      void * m_pPthreadMutexT = nullptr;
      int m_iFd = -1;
      ::u32 m_uCount = 0;
#endif

      mutex();
      mutex(enum_create_new, bool bInitiallyOwn = false);
      mutex(::particle * pparticle, bool bInitiallyOwn, const_char_pointer pszName, security_attributes * psecurityattributes);
#ifdef PARALLELIZATION_PTHREAD
      mutex(enum_create_new, const_char_pointer pszName, int iFd, bool bOwner = true);
#elif defined(WINDOWS)
      mutex(enum_create_new, const_char_pointer pszName, void * handle, bool bOwner = true);
#endif
      ~mutex() override;

      mutex(const mutex &) = delete;
      mutex & operator=(const mutex &) = delete;

      hsynchronization get_synchronization_handle() override;
      void _wait() override;
      bool _wait(const class ::time & timeWait) override;

      using ::particle::unlock;
      void unlock() override;
   };

} // namespace parallelization

CLASS_DECL_ACME void wait_until_mutex_does_not_exist(const_char_pointer pszName);
CLASS_DECL_ACME ::pointer< ::parallelization::mutex > get_ui_destroyed_mutex();
