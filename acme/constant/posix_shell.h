// Created by camilo on 2024-05-06 11:06 <3ThomasBorregaardSørensen!!
#pragma once


enum enum_posix_shell : int
{

   e_posix_shell_system_default,
#ifdef WINDOWS_DESKTOP
   e_posix_shell_git_bash,
   e_posix_shell_msys2,
#endif

};



