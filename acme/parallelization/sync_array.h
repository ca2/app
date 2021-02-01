#pragma once


#ifdef WINDOWS
using hsync_array = ::address_array < hsync >;
#endif

#define MAXIMUM_SYNC_OBJECTS 64

class CLASS_DECL_ACME sync_array :
   public matter
{
public:


#ifdef WINDOWS
   hsync_array          m_hsyncaCache;
#endif
   byte                 m_byteaSyncIndex[MAXIMUM_SYNC_OBJECTS];


   DECLARE_ARRAY_OF(sync_array, sync, sync);


   sync_array();
   sync_array(const ::sync_array & array);
   virtual ~sync_array();


   void	clear();

   ::count size() const;

   bool is_empty() const;

   bool add_item(class sync * psync);

   inline bool add(class sync* psync) { return add_item(psync); }

   bool add(const sync_array & waitablea);

   void remove(class sync * psync);

   void remove(index index);

   virtual void wait();

   virtual sync_result wait(const duration & duration);

   sync_result wait(bool waitForAll, const duration & duration, bool bWaitMessageQueue = false);

   sync_result contains(const sync_result & result) const;

   sync_array & operator = (const sync_array & synca);


};



