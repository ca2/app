#include "framework.h"


namespace os
{


   pipe::pipe()
   {

      m_bBlock = false;

      m_bInherit = false;

      m_pchBuf = nullptr;

   }


   pipe::~pipe()
   {

      if(m_pchBuf != nullptr)
      {

         free(m_pchBuf);

      }

   }


   bool pipe::create(bool bBlock, bool bInherit)
   {

      m_bBlock = bBlock;

      m_bInherit = bInherit;

      return true;

   }


   bool pipe::not_inherit_read()
   {

      return true;

   }

   bool pipe::not_inherit_write()
   {

      return true;

   }


   bool pipe::write(const char * psz)
   {

      return true;

   }


   string pipe::read()
   {

      return "";

   }


   string pipe::one_pass_read()
   {

      return "";

   }


#ifdef WINDOWS

   void pipe::readex()
   {
      
   }

#endif


} // namespace os



