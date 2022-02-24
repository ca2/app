//
// Created by camilo on 03/12/2020. <3tbs!!
//
#pragma once


//CLASS_DECL_ACME bool os_init_application();
//CLASS_DECL_ACME void os_term_application();


enum enum_command_system
{

   e_command_system_none = 0,
   e_command_system_inline_log = 1,

};


//#include "acme/primitive/duration/_.h"


CLASS_DECL_ACME void command_system(string & strOutput, string & strError, int & iExitCode, const char* psz, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite());

