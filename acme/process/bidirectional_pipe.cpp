#include "framework.h"


namespace operating_system
{


   bidirectional_pipe::bidirectional_pipe() :
      m_ppipeIn(e_create),
      m_ppipeOut(e_create)
   {

   }


   bidirectional_pipe::~bidirectional_pipe()
   {

   }


   bool bidirectional_pipe::create(bool bBlock,bool bInherit)
   {

      if(!m_ppipeIn->create(bBlock,bInherit))
      {

         return false;

      }

#ifdef LINUX

      if(!m_ppipeIn->not_inherit_write())
      {

         return false;

      }

#endif

      if(!m_ppipeOut->create(bBlock,bInherit))
      {

         return false;

      }

#ifdef LINUX

      if(!m_ppipeOut->not_inherit_read())
      {

         return false;

      }

#endif

      return true;

   }


} // namespace operating_system



