#pragma once


CLASS_DECL_AQUA int create_process(const char * _cmd_line, int * pprocessId);
CLASS_DECL_AQUA int get_process_pid(const char * csProcessName);
CLASS_DECL_AQUA bool launch_macos_app(const char * pszAppFolder);
CLASS_DECL_AQUA bool launch_macos_app_args(const char * pszAppFolder, const char * pszArgs);
