#pragma once


//CLASS_DECL_ACME ::i32 create_process(const_char_pointer _cmd_line, ::i32 * pprocessId);
//CLASS_DECL_ACME ::i32 get_process_pid(const_char_pointer csProcessName);


::i32 process_get_os_priority(::i32 nCa2Priority);
::i32 process_get_scheduling_priority(::i32 iOsPriority);
