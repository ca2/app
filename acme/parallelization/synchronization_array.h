#pragma once


#ifdef WINDOWS
using hsync_array = ::address_array < hsync >;
#endif


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
   ~synchronization_array() override;


   void	clear();

   ::count size() const;

   bool is_empty() const;

   bool add_item(class synchronization_object * psync);

   inline bool add(class synchronization_object* psync) { return add_item(psync); }

   bool add(const synchronization_array & waitablea);

   void erase(class synchronization_object * psync);

   void erase(index index);

   void wait() override;

   virtual ::index wait(const class ::wait & wait, bool waitForAll = true, ::u32 uWaitMask = 0);

   virtual void contains(const ::e_status & result) const;

   synchronization_array & operator = (const synchronization_array & synca);


};



