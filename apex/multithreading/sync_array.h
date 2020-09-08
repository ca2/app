#pragma once


using hsync_array = ::address_array < HSYNC >;


class CLASS_DECL_APEX sync_array :
   public object
{
public:


   hsync_array          m_hsyncaCache;
   byte                 m_byteaSyncIndex[MAXIMUM_WAIT_OBJECTS];


   DEFAULT_ARRAY_OF(sync_array, sync, m_synca, sync);


   sync_array();
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


};



