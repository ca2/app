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

         m_block = item.m_block;

      }

      return *this;

   }


   item & item::operator = (item && item)
   {

      if (&item != this)
      {

         m_tick = item.m_tick;

         m_block = ::move(item.m_block);

      }

      return *this;

   }


} // namespace simpledb



