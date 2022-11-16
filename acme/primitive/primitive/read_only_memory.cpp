#include "framework.h"
#include "read_only_memory.h"


read_only_memory::read_only_memory(const block & block) :
   read_only_memory(block.get_data(), block.get_size()) 
{


}


read_only_memory::read_only_memory(const void * p, memsize size)
{

   m_memory.m_bOwner = false;
   m_memory.m_bReadOnly = true;
   m_memory.m_preadonlymemory = this;
   m_memory.m_pbStorage = (byte *)p;
   m_memory.m_pdata = (byte *)p;
   m_memory.m_cbStorage = size;
   m_memory.m_iSize = size;

}



