#include "framework.h"


block & block::from_base64(const char * psz, strsize iSize) const
{

   __throw(todo("base64"));
   //::get_context_system()->m_pbase64->decode(*this, psz, iSize);

   //return (block &)*this;
      return *(block*)nullptr;


}


string block::to_base64() const
{

   //return ::get_context_system()->m_pbase64->encode(*this);
   //__throw(todo("base64"));
   return "";

}




fork_block & fork_block::from_base64(const char * psz, strsize iSize)
{

   m_iSize = (iSize + 1) * 3 / 4;

   m_pdata = memory_alloc((::memsize_cast) m_iSize);

   // acme commented
   //m_iSize = ::get_context_system()->m_pbase64->decode(*this, psz, iSize);



   return (fork_block &)*this;

}



#ifdef __DEBUG

#include "block.inl"

#endif //__DEBUG