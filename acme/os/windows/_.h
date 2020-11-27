#pragma once


typedef ::u32 thread_data_index;


CLASS_DECL_ACME void TRACELASTERROR();

CLASS_DECL_ACME string get_error_string(DWORD dwError);


CLASS_DECL_ACME::estatus init_gdi_plus();
CLASS_DECL_ACME void term_gdi_plus();

CLASS_DECL_ACME string get_command_line(HANDLE handleProcess);
CLASS_DECL_ACME string get_display_error(u32 NTStatusMessage);
CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach = true);


class memory;


CLASS_DECL_ACME string key_to_char(WPARAM wparam, LPARAM lparam);
CLASS_DECL_ACME string read_resource_as_string(HINSTANCE hinst, ::u32 nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME bool read_resource_as_memory(memory & m, HINSTANCE hinst, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount = -1);


CLASS_DECL_ACME HANDLE dup_handle(HANDLE h);


#include "registry.h"
#include "process.h"
#include "simple_hold_handle.h"
#include "file.h"


namespace windows
{


   CLASS_DECL_ACME string langid_to_iso(LANGID langid);


} // namespace windows


#include "acme/os/windows_common/comptr.h"


#include "api.h"





