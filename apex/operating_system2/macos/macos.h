#pragma once


//#include "macos_ns_exception.h"

#include "parallelization.h"



#include "main.h"


bool ns_open_file(const scoped_string & str);
void ns_set_this_default_browser();

i32 raw_main_command_line(const scoped_string & strCommandLine, int argc, char *argv[]);

i32 apex_main_command_line(const scoped_string & strParams, int argc, char *argv[]);

#ifdef cplusplus
string macos_error_string(OSStatus status);
string macos_error_description(OSStatus status);
#endif


