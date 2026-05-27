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


         ::f64   m_dLeft;
         ::f64   m_dLeftDevice;

         ::f64   m_xOffset;


         line();
         ~line() override;


      };



   } // namespace rich_text


} // namespace user



