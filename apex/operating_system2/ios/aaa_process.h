#pragma once


//CLASS_DECL_APEX int create_process(const char * _cmd_line, int * pprocessId);
//CLASS_DECL_APEX int get_process_pid(const char * csProcessName);


int process_get_os_priority(int nCa2Priority);
int process_get_scheduling_priority(int iOsPriority);
