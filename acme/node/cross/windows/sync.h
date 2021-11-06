#pragma once






class CLASS_DECL_ACME synchronization_object :
   virtual public matter
{
public:


   synchronization_object();
   virtual ~synchronization_object();


   virtual bool lock();
   virtual bool lock(const duration & durationTimeout);

   virtual synchronization_result wait();
   virtual synchronization_result wait(const duration & durationTimeout);

   virtual bool is_locked() const;

   virtual bool unlock();
   virtual bool unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */);


   virtual void init_wait();
   virtual void exit_wait();


   virtual void acquire_ownership();
   virtual void release_ownership();




};



