#pragma once


CLASS_DECL_ACME void throw_memory_exception();
CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const char * pszMessage = nullptr, i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr);



