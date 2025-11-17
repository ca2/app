#pragma once


#include "core/user/rich_text/_.h"
//#include "acme/prototype/collection/pointer_array.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE line :
         virtual public pointer_array < box >
      {
      public:


         double   m_dLeft;
         double   m_dLeftDevice;

         double   m_xOffset;


         line();
         ~line() override;


      };



   } // namespace rich_text


} // namespace user



