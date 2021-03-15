#include "framework.h"
#include "number.h"

namespace mathematics
{


   number::number()
   {
      m_pimpl = new value_impl;
   }

   number::~number()
   {
      delete m_pimpl;
   }


} // namespace mathematics