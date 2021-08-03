#pragma once

typedef struct tagMSG MSG;
inline void copy(MESSAGE * pmessage, const MSG * pmsg);


//#ifdef WINDOWS
//#include <Winsvc.h>
//#endif

#ifdef WINDOWS_DESKTOP
CLASS_DECL_ACME string ca2_command_line(hinstance hinstance);
#else
CLASS_DECL_ACME string ca2_command_line();
#endif





typedef ::u32 thread_data_index;


CLASS_DECL_ACME void TRACELASTERROR();

CLASS_DECL_ACME string get_error_string(DWORD dwError);


//CLASS_DECL_ACME::e_status init_gdi_plus();
//CLASS_DECL_ACME void term_gdi_plus();

CLASS_DECL_ACME string get_display_error(u32 NTStatusMessage);
CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach = true);


class memory;











//inline payload::operator long() const
//{
//
//   return i32();
//
//}
//
//inline payload & payload::operator = (LPDWORD pinteraction)
//{
//
//   
//
//}



using hfile = void *;


#ifdef WINDOWS
CLASS_DECL_ACME filesize hfile_get_size(hfile h);
#endif


CLASS_DECL_ACME string key_to_char(wparam wparam, lparam lparam);






//static DWORD WINAPI task::s_os_task(void * p);




