// Created by camilo on 2021-04-02 01:58 BRT <3TBS_!!
#pragma once


int main(int argc, platform_char** argv, platform_char** envp)
{

   auto estatus = implement(argc, argv, envp);

   auto iErrorStatus = estatus.error_status();

   return iErrorStatus;

}


