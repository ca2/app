//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#include "framework.h"
#include "_.h"


namespace text
{


   data::data(translator* ptexttranslator) :
      m_ptranslator(ptexttranslator)
   {

      m_bPendingUpdate = true;

   }


   data::~data()
   {

   }



} // namespace text



