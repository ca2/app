#include "framework.h"
#include "_simpledb.h"


namespace simpledb
{


   item::item()
   {

   }


   item::item(const item & item)
   {

      operator = (item);

   }


   item::item(item && item)
   {

      operator = (::move(item));

   }


   item & item::operator = (const item & item)
   {

      if (&item != this)
      {

         m_tick = item.m_tick;

         m_memory = item.m_memory;

      }

      return *this;

   }


   item & item::operator = (item && item)
   {

      if (&item != this)
      {

         m_tick = item.m_tick;

         m_memory = ::move(item.m_memory);

      }

      return *this;

   }


} // namespace simpledb



