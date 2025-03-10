#pragma once


//#include "macos_ns_exception.h"

#include "parallelization.h"



#include "main.h"


bool ns_open_file(const ::scoped_string & scopedstr);
void ns_set_this_default_browser();

int raw_main_command_line(const ::scoped_string & scopedstrCommandLine, int argc, char *argv[]);

int aura_main_command_line(const ::scoped_string & scopedstrParams, int argc, char *argv[]);

#ifdef cplusplus
string macos_error_string(OSStatus status);
string macos_error_description(OSStatus status);
#endif


