#pragma once


class CLASS_DECL_ACME synchronization_array :
   public matter
{
public:


   DECLARE_ARRAY_OF(synchronization_array, synchronization_object, synchronization_object);


   synchronization_array();
   synchronization_array(const ::synchronization_array & array);
   virtual ~synchronization_array();


   void	clear();

   ::count size() const;

   bool is_empty() const;

   bool add_item(class synchronization_object * psync);

   inline bool add(class synchronization_object* psync) { return add_item(psync); }

   bool add(const synchronization_array & waitablea);

   void erase(class synchronization_object * psync);

   void erase(index index);

   virtual void wait();

   virtual synchronization_result wait(const duration & duration);

   synchronization_result wait(bool waitForAll, const duration & duration, bool bWaitMessageQueue = false);

   synchronization_result contains(const synchronization_result & result) const;

   synchronization_array & operator = (const synchronization_array & synca);


};



