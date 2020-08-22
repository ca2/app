#pragma once


CLASS_DECL_AXIS int create_process(const char * _cmd_line, int * pprocessId);
CLASS_DECL_AXIS int get_process_pid(const char * csProcessName);


i32 process_get_os_priority(i32 nCa2Priority);
i32 process_get_scheduling_priority(i32 iOsPriority);
