#pragma once


#ifdef WINDOWS
using hsync_array = ::address_array < hsync >;
#endif

#define MAXIMUM_SYNCHRONIZING_OBJECTS 64

class CLASS_DECL_ACME synchronization_array :
   public matter
{
public:


#ifdef WINDOWS


   hsync_array          m_hsyncaCache;
   byte                 m_byteaSyncIndex[MAXIMUM_SYNCHRONIZING_OBJECTS];


#endif


   DECLARE_ARRAY_CONTAINER_OF(synchronization_array, synchronization_object, m_synchronizationa, synchronization_object);


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

   virtual synchronization_result wait();

   virtual synchronization_result wait(const duration & duration, bool waitForAll = true, ::u32 uWaitMask = 0);

   virtual synchronization_result contains(const synchronization_result & result) const;

   synchronization_array & operator = (const synchronization_array & synca);


};



