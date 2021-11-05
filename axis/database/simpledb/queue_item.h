#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS queue_item :
      virtual public ::matter
   {
   public:


      string               m_strKey;
      ::duration               m_tick;
      memory               m_memory;


   };


} // namespace simpledb



