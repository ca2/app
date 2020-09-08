#pragma once


typedef DWORD thread_data_index;


CLASS_DECL_APEX string get_command_line(HANDLE handleProcess);
CLASS_DECL_APEX string get_display_error(u32 NTStatusMessage);
CLASS_DECL_APEX void attach_thread_input_to_main_thread(bool bAttach = true);


class memory;


CLASS_DECL_APEX string key_to_char(WPARAM wparam, LPARAM lparam);
CLASS_DECL_APEX string read_resource_as_string(HINSTANCE hinst, UINT nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
CLASS_DECL_APEX bool read_resource_as_memory(memory & m, HINSTANCE hinst, UINT nID, const char * pcszType, strsize iReadAtMostByteCount = -1);


CLASS_DECL_APEX HANDLE dup_handle(HANDLE h);


#include "registry.h"
#include "process.h"
#include "simple_hold_handle.h"
#include "file.h"


namespace windows
{


   CLASS_DECL_APEX string langid_to_iso(LANGID langid);


} // namespace windows


#include "apex/os/windows_common/comptr.h"


#include "api.h"



