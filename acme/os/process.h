//
// Created by camilo on 03/12/2020. <3tbs!!
//
#pragma once


CLASS_DECL_ACME bool os_init_application();
CLASS_DECL_ACME void os_term_application();


#ifdef WINDOWS_DESKTOP
CLASS_DECL_ACME string ca2_command_line(HINSTANCE hinstance);
#else
CLASS_DECL_ACME string ca2_command_line();
#endif
