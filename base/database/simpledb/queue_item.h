#pragma once


namespace simpledb
{


   class CLASS_DECL_AURA queue_item :
      virtual public context_object
   {
   public:

      string            m_strKey;
      tick              m_tick;
      fork_block        m_block;

   };


} // namespace simpledb



