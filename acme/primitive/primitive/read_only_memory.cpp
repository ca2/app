#include "framework.h"
#include "read_only_memory.h"


read_only_memory::read_only_memory(const ::block & block) :
   read_only_memory(block.data(), block.size()) 
{


}


read_only_memory::read_only_memory(const void * p, memsize size)
{

   m_memory.m_bOwner = false;
   m_memory.m_bReadOnly = true;
   m_memory.m_preadonlymemory = this;
   m_memory.m_beginStorage = (byte *)p;
   m_memory.m_begin = (byte *)p;
   m_memory.m_sizeStorage = size;
   m_memory.m_end = ((::byte *)p)+ size;

}



