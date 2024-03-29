#include "framework.h"
#include "_simpledb.h"
#include "item.h"


namespace simpledb
{


   item::item()
   {

      m_bData = false;

   }


   item::item(const item & item)
   {

      operator = (item);

   }


   item::item(item && item)
   {

      operator = (::transfer(item));

   }


   item & item::operator = (const item & item)
   {

      if (&item != this)
      {

         m_tick = item.m_tick;

         m_memory = item.m_memory;

         m_bData = item.m_bData;

      }

      return *this;

   }


   item & item::operator = (item && item)
   {

      if (&item != this)
      {

         m_tick = item.m_tick;

         m_memory = ::transfer(item.m_memory);

         m_bData = item.m_bData;

      }

      return *this;

   }


} // namespace simpledb



