//
// Created by camilo on 03/12/2020. <3tbs!!
//
#pragma once


enum enum_command_system
{

   e_command_system_none = 0,
   e_command_system_inline_log = 1,

};


CLASS_DECL_ACME void command_system(string_array & straOutput, int & iExitCode, const char* psz, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite(), ::particle * pparticleSynchronization = nullptr, ::file::file * pfileLog = nullptr);



