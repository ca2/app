#pragma once


class CLASS_DECL_ACME single_lock :
   virtual public synchronization_object
{
public:


   synchronization_object *                  m_psync;
   bool                                      m_bAcquired;


   explicit single_lock(synchronization_object * pobject, bool bInitialLock = false);
   ~single_lock();

   synchronization_result wait();
   synchronization_result wait(const duration & duration);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked();


};



class CLASS_DECL_ACME _single_lock :
   virtual public synchronization_object
{
public:


   synchronization_object *      m_psync;
   bool                          m_bAcquired;


   explicit _single_lock(synchronization_object * pobject, bool bInitialLock = false);
   ~_single_lock();


   synchronization_result _wait();
   synchronization_result _wait(const duration & duration);
   bool unlock();
   bool unlock(::i32 lCount, ::i32 * lPrevCount = nullptr);
   bool IsLocked();


};



