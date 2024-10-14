#pragma once


class CLASS_DECL_ACME single_lock
{
public:


   ::subparticle_pointer      m_psubparticleSynchronization;
   bool                       m_bLocked;


   explicit single_lock(subparticle * psubparticleSynchronization, bool bInitialLock = false);
   ~single_lock();


   void _wait();
   bool _wait(const class ::time& wait);
   ::e_status wait();
   ::e_status wait(const class ::time& wait = ::time::infinity());
   void _lock();
   bool lock(const class ::time & wait = ::time::infinity());
   void unlock();
   void unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool is_locked() const;


};



class CLASS_DECL_ACME _single_lock
{
public:


   ::subparticle_pointer            m_psubparticleSynchronization;
   bool                             m_bLocked;


   explicit _single_lock(::subparticle * psubparticle, bool bInitialLock = false);
   ~_single_lock();


   void _wait();
   bool _wait(const class time & timeWait);
   void _lock();
//   bool lock();
   void unlock();
   void unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool is_locked() const;


};



