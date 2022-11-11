#pragma once


#include "acme/primitive/primitive/particle.h"


class CLASS_DECL_ACME single_lock :
   virtual public particle
{
public:


   //synchronization_object *                  m_psync;
   //bool                                      m_bAcquired;


   explicit single_lock(particle * pparticleSynchronization, bool bInitialLock = false);
   ~single_lock() override;


   void _wait() override;
   bool _wait(const class ::wait& wait) override;
   ::e_status wait() override;
   ::e_status wait(const class ::wait& wait) override;
   void unlock() override;
   void unlock(::i32 lCount, ::i32 * lPrevCount = nullptr) override;
   bool is_locked() const override;


};



class CLASS_DECL_ACME _single_lock :
   virtual public particle
{
public:


   //synchronization *      m_psync;
   //bool                          m_bAcquired;


   explicit _single_lock(particle * pparticle, bool bInitialLock = false);
   ~_single_lock();


   void _wait() override;
   bool _wait(const class ::wait & wait) override;
   void unlock() override;
   void unlock(::i32 lCount, ::i32 * lPrevCount = nullptr) override;
   bool is_locked() const override;


};



