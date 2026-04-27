//
// Created by camilo on 2026-04-27 16:22 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#include "framework.h"
#include "last_error.h"
#include "acme/_operating_system.h"


namespace windows
{


   CLASS_DECL_ACME last_error get_last_error()
   {

      ::windows::last_error lasterror(::GetLastError());

      return lasterror;

   }


}



