#pragma once


class CLASS_DECL_ACME single_lock
{
public:


   const ::subparticle *      m_psubparticleContext;
   ::subparticle *            m_psubparticleSynchronization;
   bool                       m_bLocked;
   ::task *                   m_ptask = nullptr;
   const_char_pointer         m_pszFile;
   int                        m_iLine;


   explicit single_lock(subparticle * psubparticleSynchronization, bool bInitialLock = false, const ::subparticle * psubparticleContext = nullptr, const_char_pointer pszFile = nullptr, int iLine = -1);
   ~single_lock();


   void _wait();
   bool _wait(const class ::time& wait);
   ::e_status wait();
   ::e_status wait(const class ::time& wait);
   void _lock();
   bool lock(const class ::time & wait = ::time::infinity());
   void unlock();
   void unlock(int lCount, int * lPrevCount = nullptr);
   bool is_locked() const;
   class ::time remaining_from_timeout() const;


   void debug_on_lock();
   void debug_on_unlock();


};




class CLASS_DECL_ACME _single_lock
{
public:


   const ::subparticle *            m_psubparticleContext;
   ::subparticle *                  m_psubparticleSynchronization;
   bool                             m_bLocked;
   ::task *                         m_ptask = nullptr;
   const_char_pointer               m_pszFile;
   int                              m_iLine;


   explicit _single_lock(::subparticle * psubparticle, bool bInitialLock = false, const ::subparticle * psubparticleContext = nullptr, const_char_pointer pszFile = nullptr, int iLine = -1);
   ~_single_lock();


   void _wait();
   bool _wait(const class time & timeWait);
   void _lock();
//   bool lock();
   void unlock();
   void unlock(int lCount, int * lPrevCount = nullptr);
   bool is_locked() const;


   void debug_on_lock();
   void debug_on_unlock();


};
//
//
//namespace parallelization
//{
//
//
//   CLASS_DECL_ACME void on_single_lock_lock(::subparticle *psubparticleSynchronization,
//                                            const ::subparticle *psubparticleContext, const_char_pointer pszFile,
//                                            int iLine);
//   CLASS_DECL_ACME void on_single_lock_unlock(::subparticle *psubparticleSynchronization);
//
//
//} // namespace parallelization
//


