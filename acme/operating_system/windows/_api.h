// Created by camilo on 2022-09-26 21:01 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system.h"


namespace windows
{

   
   CLASS_DECL_ACME string get_last_error_string();
   CLASS_DECL_ACME string get_error_string(DWORD dwError);


} // namespace windows



