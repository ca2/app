#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS item
   {
   public:


      tick              m_tick;
      fork_block        m_block;

      item();
      item(const item & item);
      item(item && item);

      item & operator=(const item & item);

      item & operator=(item && item);

   };


} // namespace simpledb



