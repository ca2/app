#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS queue_item :
      virtual public context_object
   {
   public:

      string            m_strKey;
      millis              m_tick;
      fork_block        m_block;

   };


} // namespace simpledb



