#pragma once


////#include "acme/primitive/primitive/matter.h"
#include "pipe.h"


namespace operating_system
{


   class CLASS_DECL_ACME bidirectional_pipe :
      virtual public ::matter
   {
   public:


      ::pointer<pipe>    m_ppipeIn;
      ::pointer<pipe>    m_ppipeOut;


      bidirectional_pipe();
      virtual ~bidirectional_pipe();


      virtual bool create(bool bBlock = true,bool bInherit = false);


   };


} // namespace operating_system



