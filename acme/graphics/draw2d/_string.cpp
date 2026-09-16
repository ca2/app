//
// Created by camilo on 2026-09-15 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#include "platform.h"
#include "_constant.h"


CLASS_DECL_ACME ::string as_string(::draw2d::enum_disposal edisposal)
{

   switch(edisposal)
   {
      case ::draw2d::enum_disposal::e_disposal_undefined:
         return "::draw2d::e_disposal_undefined"_ansi;
      case ::draw2d::enum_disposal::e_disposal_none:
         return "::draw2d::e_disposal_none"_ansi;
      case ::draw2d::enum_disposal::e_disposal_previous:
         return "::draw2d::e_disposal_previous"_ansi;
      case ::draw2d::enum_disposal::e_disposal_background:
         return "::draw2d::e_disposal_background"_ansi;
      default:
         return "::draw2d::e_disposal_(unknown)"_ansi;
   }

}



