#pragma once

//
//#ifdef WINDOWS
//using hsynchronization = void *;
//#endif


//class CLASS_DECL_ACME synchronization_object :
//   virtual public particle
//{
//public:
//
//
//#ifdef WINDOWS
//   hsynchronization                   m_hsync;
//#endif
//   bool                    m_bOwner;
//
//#ifdef WINDOWS
//   synchronization_object() { m_hsync = nullptr; m_bOwner = true; }
//   synchronization_object(hsynchronization hsynchronization) : m_hsync(hsynchronization) { m_bOwner = true; }
//#else
//   synchronization_object() { m_bOwner = true; }
//#endif
//   ~synchronization_object() override;
//
//
//   // currently expected returned statuses:
//   // ::error_failed
//   // ::error_wait_timeout
//   // ::success
//   virtual ::e_status lock();
//   virtual ::e_status lock(const class ::wait & wait);
//
//   virtual ::e_status wait();
//   virtual ::e_status wait(const class ::wait & wait);
//
//   virtual void _lock();
//   virtual bool _lock(const class ::wait & wait);
//
//   virtual void _wait();
//   virtual bool _wait(const class ::wait & wait);
//
//   virtual bool is_locked() const;
//
//   virtual void unlock();
//   virtual void unlock(int /* lCount */, int * /* pPrevCount=nullptr */);
//
//
//   virtual void init_wait();
//   virtual void exit_wait();
//
//
//   virtual void acquire_ownership();
//   virtual void release_ownership();
//
//#ifdef WINDOWS
//   inline ::hsynchronization hsynchronization() const { return m_hsync; }
//#endif
//
//
//};

//
//class CLASS_DECL_ACME synchronization_lock :
//   virtual public synchronization_object
//{
//public:
//
//
//   ~synchronization_lock() override;
//
//
//};


