#pragma once






class CLASS_DECL_ACME sync :
   virtual public matter
{
public:


   sync();
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




};



