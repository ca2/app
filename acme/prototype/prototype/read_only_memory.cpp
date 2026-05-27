#include "framework.h"
#include "read_only_memory.h"


read_only_memory::read_only_memory(const ::block & block) :
   read_only_memory(block.data(), block.size()) 
{


}


read_only_memory::read_only_memory(const void * p, memsize size)
{

   this->m_bOwner = false;
   this->m_bReadOnly = true;
   this->m_preadonlymemory = this;
   this->m_beginStorage = (::u8 *)p;
   this->m_begin = (::u8 *)p;
   this->m_sizeStorage = size;
   this->m_end = ((::u8 *)p)+ size;

}



