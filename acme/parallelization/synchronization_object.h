#pragma once


#ifdef WINDOWS
using hsync = void *;
#endif


class CLASS_DECL_ACME synchronization_object :
   virtual public matter
{
public:


#ifdef WINDOWS
   hsync                   m_hsync;
#endif
   bool                    m_bOwner;

#ifdef WINDOWS
   synchronization_object() { m_hsync = nullptr; m_bOwner = true; }
   synchronization_object(hsync hsync) : m_hsync(hsync) { m_bOwner = true; }
#else
   synchronization_object() { m_bOwner = true; }
#endif
   ~synchronization_object() override;


   virtual void lock();
   virtual bool lock(const class ::wait & wait);

   virtual void _lock();
   virtual bool _lock(const class ::wait & wait);

   virtual void _wait();
   virtual bool _wait(const class ::wait & wait);

   
   void wait() override;
   virtual bool wait(const class ::wait & wait);


   virtual bool is_locked() const;

   virtual void unlock();
   virtual void unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */);


   virtual void init_wait();
   virtual void exit_wait();


   virtual void acquire_ownership();
   virtual void release_ownership();

#ifdef WINDOWS
   inline ::hsync hsync() const { return m_hsync; }
#endif


};



