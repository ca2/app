// Created by camilo on 2021-04-02 01:58 BRT <3TBS_!!
#pragma once
#include "acme/primitive/collection/strdup_array.h"


int main(int argc, platform_char** argv)
{

   ::e_status estatus = ::success;

   {

      wcsdup_array wcsdupa;

      auto envp = wcsdupa.windows_get_envp();

      estatus = implement(argc, argv, envp);

   }

   auto iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


