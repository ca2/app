#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS item
   {
   public:


      ::duration           m_tick;
      memory               m_memory;
      bool                 m_bData;

      item();
      item(const item & item);
      item(item && item);

      item & operator=(const item & item);

      item & operator=(item && item);

   };


} // namespace simpledb



