#include "framework.h"


namespace process
{


   bidirectional_pipe::bidirectional_pipe() :
      m_sppipeIn(e_create),
      m_sppipeOut(e_create)
   {

   }


   bidirectional_pipe::~bidirectional_pipe()
   {

   }


   bool bidirectional_pipe::create(bool bBlock,bool bInherit)
   {

      if(!m_sppipeIn->create(bBlock,bInherit))
      {

         return false;

      }

#ifdef LINUX

      if(!m_sppipeIn->not_inherit_write())
      {

         return false;

      }

#endif

      if(!m_sppipeOut->create(bBlock,bInherit))
      {

         return false;

      }

#ifdef LINUX

      if(!m_sppipeOut->not_inherit_read())
      {

         return false;

      }

#endif

      return true;

   }


} // namespace os



