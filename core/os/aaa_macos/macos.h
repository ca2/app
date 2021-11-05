#pragma once


//#include "macos_ns_exception.h"

#include "parallelization.h"



#include "main.h"


bool ns_open_file(const ::string & psz);
void ns_set_this_default_browser();

i32 raw_main_command_line(const ::string & pszCommandLine, int argc, char *argv[]);

i32 aura_main_command_line(const ::string & pszParams, int argc, char *argv[]);

#ifdef cplusplus
string macos_error_string(OSStatus status);
string macos_error_description(OSStatus status);
#endif


