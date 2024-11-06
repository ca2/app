#pragma once


//#include "synchronization_object.h"
////#include "acme/prototype/collection/pointer_array.h"
#include "acme/prototype/collection/address_array.h"


//#ifdef WINDOWS
using hsynchronization_array = ::address_array < hsynchronization >;
//#endif


template < typename T, ::collection::count t_iCount >
class fixed_raw_array
{
public:


   T     m_ta[t_iCount];

   fixed_raw_array()
   {
      ::memory_set(m_ta, 0, sizeof(T) * t_iCount);

   }
   fixed_raw_array(const fixed_raw_array & a)
   {

      ::memory_copy(m_ta, a.m_ta, sizeof(T) * t_iCount);

   }
   ::collection::count size() const { return t_iCount; }
   T & operator[](::collection::index i) { return m_ta[i]; }
   const T & operator[](::collection::index i) const { return m_ta[i]; }
   void erase_at(::collection::index i, ::collection::count s)
   {
      ::memory_transfer(&m_ta[i], &m_ta[i + 1], s - i - 1);
   }
   fixed_raw_array & operator = (const fixed_raw_array & a)
   {
      if (this != &a)
      {

         ::memory_copy(m_ta, a.m_ta, sizeof(T) * t_iCount);
      }
      return *this;
   }
};

class CLASS_DECL_ACME synchronization_array :
   virtual public ::particle
{
protected:
   
   
   ::pointer_array < subparticle >                             m_subparticlea;

   hsynchronization_array                                                 m_hsynchronizationa;
   fixed_raw_array < unsigned char, MAXIMUM_SYNCHRONIZING_OBJECTS >     m_uaIndexes;

public:



   synchronization_array();
   synchronization_array(const ::synchronization_array & array);
   ~synchronization_array() override;


   void	clear();

   

   bool add_item(::subparticle * pparticle);

   inline bool add(::subparticle* pparticle) { return add_item(pparticle); }

   bool add(const synchronization_array & waitablea);

   void erase(::subparticle* pparticle);

   void erase(::collection::index index);

   ::e_status wait() override;

   virtual ::e_status wait(const class time & timeWait, bool waitForAll = true, unsigned int uWaitMask = 0);

   virtual void unlock_item(::collection::index index);

   virtual void unlock_item(::collection::index index, int lCount, int * pPrevCount = nullptr);

   virtual void contains(const ::e_status & result) const;

   synchronization_array & operator = (const synchronization_array & synca);

   hsynchronization * data() {return m_hsynchronizationa.data(); }
   ::collection::count size() const { return m_hsynchronizationa.size(); }
   bool is_empty() const { return this->size() <= 0; }
   ::subparticle * at(::collection::index i) const { return m_subparticlea.ptr_at(i); }
};



