#pragma once


#ifdef WINDOWS

using HSYNC = HANDLE;

#define INVALID_HSYNC_VALUE INVALID_HANDLE_VALUE

#else

class sync;

using HSYNC = sync *;

#endif


class CLASS_DECL_ACME sync :
   virtual public generic
{
public:


   HSYNC                   m_hsync;
   bool                    m_bOwner;

#ifdef WINDOWS
   sync() { m_hsync = nullptr; m_bOwner = true; }
   sync(HSYNC hsync) : m_hsync(hsync) { m_bOwner = true; }
#else
   sync() { m_hsync = this; m_bOwner = true; }
   sync(HSYNC hsync) : m_hsync(this) { m_bOwner = true; }
#endif
   virtual ~sync();


   virtual bool lock();
   virtual bool lock(const duration & durationTimeout);

   virtual sync_result wait();
   virtual sync_result wait(const duration & durationTimeout);

   virtual bool is_locked() const;

   virtual bool unlock();
   virtual bool unlock(LONG /* lCount */, LPLONG /* pPrevCount=nullptr */);


   virtual void init_wait();
   virtual void exit_wait();


   virtual void acquire_ownership();
   virtual void release_ownership();


   inline HSYNC hsync() const { return m_hsync; }


};



