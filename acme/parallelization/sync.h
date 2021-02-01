#pragma once


#ifdef WINDOWS
using hsync = void *;
#endif


class CLASS_DECL_ACME sync :
   virtual public matter
{
public:


#ifdef WINDOWS
   hsync                   m_hsync;
#endif
   bool                    m_bOwner;

#ifdef WINDOWS
   sync() { m_hsync = nullptr; m_bOwner = true; }
   sync(hsync hsync) : m_hsync(hsync) { m_bOwner = true; }
#else
   sync() { m_bOwner = true; }
#endif
   virtual ~sync();


   virtual bool lock();
   virtual bool lock(const duration & durationTimeout);

   virtual sync_result wait();
   virtual sync_result wait(const duration & durationTimeout);

   virtual bool is_locked() const;

   virtual bool unlock();
   virtual bool unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */);


   virtual void init_wait();
   virtual void exit_wait();


   virtual void acquire_ownership();
   virtual void release_ownership();

#ifdef WINDOWS
   inline ::hsync hsync() const { return m_hsync; }
#endif


};



