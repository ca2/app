#include "framework.h"
#include "acme/operating_system.h"


int __node_is_debugger_attached()
{

   return ::IsDebuggerPresent();

}



#ifdef WINDOWS

extern LARGE_INTEGER g_largeintegerFrequency;

#endif


CLASS_DECL_ACME::i64 _get_nanos()
{

   LARGE_INTEGER largeinteger = {};

   QueryPerformanceCounter(&largeinteger);

   return muldiv64(largeinteger.QuadPart, 1'000'000'000, ::g_largeintegerFrequency.QuadPart);

}


//CLASS_DECL_ACME void output_error_message(const ansichar * pszMessage, const ansichar * pszTitle, int iMessageBox)
//{
//
//   string strMessage(pszMessage);
//
//   string strTitle(pszTitle);
//
//   if (strTitle.is_empty())
//   {
//
//      output_debug_string("ERRORMSG: " + strMessage + "\n");
//
//   }
//   else
//   {
//
//      strTitle.make_upper();
//
//      output_debug_string("\nERROR: \"" + strTitle + "\"\nMSG: " + strMessage + "\n\n");
//
//   }
//
//}


void output_debug_string(const ansichar * psz)
{

#ifdef WINDOWS

   auto len = utf8_to_unichar_len(psz);

   memory memory;

   memory.set_size((len + 1) * sizeof(wchar_t));

   auto pwsz = (wchar_t *)memory.get_data();

   utf8_to_unichar(pwsz, psz, len);

   ::OutputDebugStringW(pwsz);

#else

   printf("%s", psz);

#endif

}


void output_debug_string(const unichar * pwsz)
{

#ifdef WINDOWS

   ::OutputDebugStringW(pwsz);

#else

   string str(pwsz);

   printf("%s", str.c_str());

#endif

}


CLASS_DECL_ACME htask_t get_current_hthread()
{

   return ::GetCurrentThread();

}


CLASS_DECL_ACME itask_t get_current_ithread()
{

   return ::GetCurrentThreadId();

}




CLASS_DECL_ACME string last_error_message(DWORD dwError)
{

   wstring wstrMessage;

   LPWSTR lpBuffer = nullptr;

   auto dwSize = FormatMessageW(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
      nullptr,
      dwError,
      0,
      (LPWSTR)&lpBuffer,
      256,
      nullptr);

   if (::is_set(lpBuffer))
   {

      lpBuffer[dwSize] = L'\0';

      wstrMessage = lpBuffer;

      ::LocalFree(lpBuffer);

   }

   string strMessage;

   strMessage = wstrMessage;

   return strMessage;

}


//
//
//string get_last_error_message(u32 dwError)
//{
//   wstring wstr;
//   WCHAR * p = wstr.get_string_buffer(16 * 1024 / sizeof(unichar));
//   ::u32 dw = FormatMessageW(
//      FORMAT_MESSAGE_FROM_SYSTEM,
//      nullptr,
//      dwError,
//      0,
//      p,
//      (::u32)(wstr.get_length() / sizeof(unichar)),
//      nullptr);
//   p[dw] = L'\0';
//   wstr.release_string_buffer();
//   string str(wstr);
//   return str;
//}


//int __node_is_debugger_attached()
//{
//
//   return ::IsDebuggerPresent();
//
//}


CLASS_DECL_ACME::u32 get_last_error()
{

   return GetLastError();

}


CLASS_DECL_ACME void set_last_error(::u32 dw)
{

   SetLastError(dw);

}



::e_status last_error_to_status(DWORD dwError)
{

   // NT Error codes
   switch (dwError)
   {
   case NO_ERROR:
      return ::success;
   case ERROR_FILE_NOT_FOUND:
      return ::error_file_not_found;
   case ERROR_PATH_NOT_FOUND:
      return ::error_bad_path;
   case ERROR_TOO_MANY_OPEN_FILES:
      return ::error_too_many_open_files;
   case ERROR_ACCESS_DENIED:
      return ::error_file_access_denied;
   case ERROR_INVALID_HANDLE:
      return ::error_file_not_found;
   case ERROR_BAD_FORMAT:
      return ::error_invalid_file;
   case ERROR_INVALID_ACCESS:
      return ::error_file_access_denied;
   case ERROR_INVALID_DRIVE:
      return ::error_bad_path;
   case ERROR_CURRENT_DIRECTORY:
      return ::error_erase_current_dir;
   case ERROR_NOT_SAME_DEVICE:
      return ::error_bad_path;
   case ERROR_NO_MORE_FILES:
      return ::error_file_not_found;
   case ERROR_WRITE_PROTECT:
      return ::error_file_access_denied;
   case ERROR_BAD_UNIT:
      return ::error_hard_io;
   case ERROR_NOT_READY:
      return ::error_hard_io;
   case ERROR_BAD_COMMAND:
      return ::error_hard_io;
   case ERROR_CRC:
      return ::error_hard_io;
   case ERROR_BAD_LENGTH:
      return ::error_bad_seek;
   case ERROR_SEEK:
      return ::error_bad_seek;
   case ERROR_NOT_DOS_DISK:
      return ::error_invalid_file;
   case ERROR_SECTOR_NOT_FOUND:
      return ::error_bad_seek;
   case ERROR_WRITE_FAULT:
      return ::error_file_access_denied;
   case ERROR_READ_FAULT:
      return ::error_bad_seek;
   case ERROR_SHARING_VIOLATION:
      return ::error_file_sharing_violation;
   case ERROR_LOCK_VIOLATION:
      return ::error_file_lock_violation;
   case ERROR_WRONG_DISK:
      return ::error_bad_path;
   case ERROR_SHARING_BUFFER_EXCEEDED:
      return ::error_too_many_open_files;
   case ERROR_HANDLE_EOF:
      return ::error_end_of_file;
   case ERROR_HANDLE_DISK_FULL:
      return ::error_disk_full;
   case ERROR_DUP_NAME:
      return ::error_bad_path;
   case ERROR_BAD_NETPATH:
      return ::error_bad_path;
   case ERROR_NETWORK_BUSY:
      return ::error_file_access_denied;
   case ERROR_DEV_NOT_EXIST:
      return ::error_bad_path;
   case ERROR_ADAP_HDW_ERR:
      return ::error_hard_io;
   case ERROR_BAD_NET_RESP:
      return ::error_file_access_denied;
   case ERROR_UNEXP_NET_ERR:
      return ::error_hard_io;
   case ERROR_BAD_REM_ADAP:
      return ::error_invalid_file;
   case ERROR_NO_SPOOL_SPACE:
      return ::error_directory_full;
   case ERROR_NETNAME_DELETED:
      return ::error_file_access_denied;
   case ERROR_NETWORK_ACCESS_DENIED:
      return ::error_file_access_denied;
   case ERROR_BAD_DEV_TYPE:
      return ::error_invalid_file;
   case ERROR_BAD_NET_NAME:
      return ::error_bad_path;
   case ERROR_TOO_MANY_NAMES:
      return ::error_too_many_open_files;
   case ERROR_SHARING_PAUSED:
      return ::error_bad_path;
   case ERROR_REQ_NOT_ACCEP:
      return ::error_file_access_denied;
   case ERROR_FILE_EXISTS:
      return ::error_file_access_denied;
   case ERROR_CANNOT_MAKE:
      return ::error_file_access_denied;
   case ERROR_ALREADY_ASSIGNED:
      return ::error_bad_path;
   case ERROR_INVALID_PASSWORD:
      return ::error_file_access_denied;
   case ERROR_NET_WRITE_FAULT:
      return ::error_hard_io;
   case ERROR_DISK_CHANGE:
      return ::error_file_not_found;
   case ERROR_DRIVE_LOCKED:
      return ::error_file_lock_violation;
   case ERROR_BUFFER_OVERFLOW:
      return ::error_bad_path;
   case ERROR_DISK_FULL:
      return ::error_disk_full;
   case ERROR_NO_MORE_SEARCH_HANDLES:
      return ::error_too_many_open_files;
   case ERROR_INVALID_TARGET_HANDLE:
      return ::error_invalid_file;
   case ERROR_INVALID_CATEGORY:
      return ::error_hard_io;
   case ERROR_INVALID_NAME:
      return ::error_bad_path;
   case ERROR_INVALID_LEVEL:
      return ::error_bad_path;
   case ERROR_NO_VOLUME_LABEL:
      return ::error_bad_path;
   case ERROR_NEGATIVE_SEEK:
      return ::error_bad_seek;
   case ERROR_SEEK_ON_DEVICE:
      return ::error_bad_seek;
   case ERROR_DIR_NOT_ROOT:
      return ::error_bad_path;
   case ERROR_DIR_NOT_EMPTY:
      return ::error_erase_current_dir;
   case ERROR_LABEL_TOO_LONG:
      return ::error_bad_path;
   case ERROR_BAD_PATHNAME:
      return ::error_bad_path;
   case ERROR_LOCK_FAILED:
      return ::error_file_lock_violation;
   case ERROR_BUSY:
      return ::error_file_access_denied;
   case ERROR_INVALID_ORDINAL:
      return ::error_invalid_file;
   case ERROR_ALREADY_EXISTS:
      return ::error_file_access_denied;
   case ERROR_INVALID_EXE_SIGNATURE:
      return ::error_invalid_file;
   case ERROR_BAD_EXE_FORMAT:
      return ::error_invalid_file;
   case ERROR_FILENAME_EXCED_RANGE:
      return ::error_bad_path;
   case ERROR_META_EXPANSION_TOO_LONG:
      return ::error_bad_path;
   case ERROR_DIRECTORY:
      return ::error_bad_path;
   case ERROR_OPERATION_ABORTED:
      return ::error_hard_io;
   case ERROR_IO_INCOMPLETE:
      return ::error_hard_io;
   case ERROR_IO_PENDING:
      return ::error_hard_io;
   case ERROR_SWAPERROR:
      return ::error_file_access_denied;
   default:
      return ::error_file;
   }
}




CLASS_DECL_ACME void TRACELASTERROR()
{

   auto error = ::GetLastError();

   if (!error)
   {

      return;

   }

   string strErrorMessage = ::last_error_message(error);

   string strError;

   strError.Format("\nError Message:\n%s\n\n", strErrorMessage.c_str());

   ::output_debug_string(strError);

}



void CLASS_DECL_ACME __cdecl _ca2_purecall()
{

   __throw(error_pure_call);

}





