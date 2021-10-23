#pragma once


//INLINE void fork_block::destroy()
//{
//
//   if (::is_set(m_pdata))
//   {
//
//      memory_free(m_pdata);
//
//   }
//
//}
//
//INLINE fork_block & fork_block::operator = (const block & block)
//{
//   if (this != &block)
//   {
//      if (get_data() != block.get_data())
//      {
//         assign(block.get_data(), block.m_iSize);
//      }
//      m_iSize = block.m_iSize;
//   }
//   return *this;
//}
//
//
//
//
//INLINE void fork_block::assign(const void * p, i64 iSize)
//{
//
//   destroy();
//
//   m_pdata = (byte *) memory_allocate(iSize);
//
//   memcpy_dup(m_pdata, p, iSize);
//
//   m_iSize = iSize;
//
//}
//
//
//INLINE fork_block & fork_block::operator = (const fork_block & block)
//{
//
//   return operator = ((const ::block &) block);
//
//}
//
//
//INLINE fork_block & fork_block::operator = (block && block)
//{
//
//   if (this != &block)
//   {
//      if (get_data() != block.get_data())
//      {
//         destroy();
//         m_pdata = block.m_pdata;
//         block.m_pdata = NULL;
//      }
//      m_iSize = block.m_iSize;
//      block.m_iSize = 0;
//   }
//
//   return *this;
//}
