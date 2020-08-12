#pragma once


CLASS_DECL_AURA void call_sync(const char * path, const char * param);
i32 create_process(const char * _cmd_line, i32 * pprocessId);
i32 get_process_pid(const char * procNameParam);
