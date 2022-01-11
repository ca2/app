#pragma once


class CLASS_DECL_ACME single_lock :
   virtual public synchronization_object
{
public:


   synchronization_object *                  m_psync;
   bool                                      m_bAcquired;


   explicit single_lock(synchronization_object * pobject, bool bInitialLock = false);
   ~single_lock() override;


   void _wait() override;
   void _wait(const class ::wait& wait) override;
   void wait() override;
   void wait(const class ::wait& wait) override;
   bool unlock() override;
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr) override;
   bool is_locked() const override;


};



class CLASS_DECL_ACME _single_lock :
   virtual public synchronization_object
{
public:


   synchronization_object *      m_psync;
   bool                          m_bAcquired;


   explicit _single_lock(synchronization_object * pobject, bool bInitialLock = false);
   ~_single_lock();


   void _wait();
   void _wait(const duration & duration);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked();


};



