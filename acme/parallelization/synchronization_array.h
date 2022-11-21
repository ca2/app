#pragma once


//#include "synchronization_object.h"
////#include "acme/primitive/collection/pointer_array.h"
#include "acme/primitive/collection/address_array.h"


#ifdef WINDOWS
using hsync_array = ::address_array < hsync >;
#endif


class CLASS_DECL_ACME synchronization_array :
   virtual public ::particle
{
public:


#ifdef WINDOWS


   hsync_array          m_hsyncaCache;
   byte                 m_byteaSyncIndex[MAXIMUM_SYNCHRONIZING_OBJECTS];


#endif


   DECLARE_ARRAY_CONTAINER_OF(synchronization_array, synchronization, m_synchronizationa, particle);


   synchronization_array();
   synchronization_array(const ::synchronization_array & array);
   ~synchronization_array() override;


   void	clear();

   ::count size() const;

   bool is_empty() const;

   bool add_item(::particle * pparticle);

   inline bool add(::particle * pparticle) { return add_item(pparticle); }

   bool add(const synchronization_array & waitablea);

   void erase(::particle * pparticle);

   void erase(index index);

   ::e_status wait() override;

   virtual ::index wait(const class ::wait & wait, bool waitForAll = true, ::u32 uWaitMask = 0);

   virtual void contains(const ::e_status & result) const;

   synchronization_array & operator = (const synchronization_array & synca);


};



