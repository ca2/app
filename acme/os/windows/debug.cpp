#include "framework.h"
#include "acme/operating_system.h"

//#include <stdio.h>
//#include <stdarg.h>



//
//int __node_is_debugger_attached()
//{
//
//   return ::IsDebuggerPresent();
//
//}


// Twitter Automator and Denis Lakic and UpWork contribution
// enzymes: Liveedu.tv, Twitch.tv and Mixer.com streamers and viewers
// Mummi and bilbo!!
// create call to :
CLASS_DECL_ACME void windows_install_crash_dump_reporting(const string & strModuleNameWithTheExeExtension)
{

   ::windows::registry::key k;

   string strKey = "SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting\\LocalDumps\\" + strModuleNameWithTheExeExtension;

   if (k._open(HKEY_LOCAL_MACHINE, strKey, true))
   {
      ::file::path str = dir::system() / "CrashDumps" / strModuleNameWithTheExeExtension;
      wstring wstr = str;
      RegSetValueExW(k.m_hkey, L"DumpFolder", 0, REG_EXPAND_SZ, (byte *)wstr.c_str(),  ::u32 ((wcslen(wstr) + 1) * sizeof(wchar_t)));
      ::u32 dw = 10;
      RegSetValueExW(k.m_hkey, L"DumpCount", 0, REG_DWORD, (byte *)&dw, sizeof(dw));
      dw = 2;
      RegSetValueExW(k.m_hkey, L"DumpType", 0, REG_DWORD, (byte *)&dw, sizeof(dw));

   }

   output_debug_string("test01");

}




::enum_status os_error_to_estatus(::i32 lOsErr)
{
    // NT Error codes
    switch ((::u32)lOsErr)
    {
        case NO_ERROR:
            return error_file;
        case ERROR_FILE_NOT_FOUND:
            return error_file_not_found;
        case ERROR_PATH_NOT_FOUND:
            return error_bad_path;
        case ERROR_TOO_MANY_OPEN_FILES:
            return error_too_many_open_files;
        case ERROR_ACCESS_DENIED:
            return error_file_access_denied;
        case ERROR_INVALID_HANDLE:
            return error_file_not_found;
        case ERROR_BAD_FORMAT:
            return error_invalid_file;
        case ERROR_INVALID_ACCESS:
            return error_file_access_denied;
        case ERROR_INVALID_DRIVE:
            return error_bad_path;
        case ERROR_CURRENT_DIRECTORY:
            return error_remove_current_dir;
        case ERROR_NOT_SAME_DEVICE:
            return error_bad_path;
        case ERROR_NO_MORE_FILES:
            return error_file_not_found;
        case ERROR_WRITE_PROTECT:
            return error_file_access_denied;
        case ERROR_BAD_UNIT:
            return error_hard_io;
        case ERROR_NOT_READY:
            return error_hard_io;
        case ERROR_BAD_COMMAND:
            return error_hard_io;
        case ERROR_CRC:
            return error_hard_io;
        case ERROR_BAD_LENGTH:
            return error_bad_seek;
        case ERROR_SEEK:
            return error_bad_seek;
        case ERROR_NOT_DOS_DISK:
            return error_invalid_file;
        case ERROR_SECTOR_NOT_FOUND:
            return error_bad_seek;
        case ERROR_WRITE_FAULT:
            return error_file_access_denied;
        case ERROR_READ_FAULT:
            return error_bad_seek;
        case ERROR_SHARING_VIOLATION:
            return error_file_sharing_violation;
        case ERROR_LOCK_VIOLATION:
            return error_file_lock_violation;
        case ERROR_WRONG_DISK:
            return error_bad_path;
        case ERROR_SHARING_BUFFER_EXCEEDED:
            return error_too_many_open_files;
        case ERROR_HANDLE_EOF:
            return error_end_of_file;
        case ERROR_HANDLE_DISK_FULL:
            return error_disk_full;
        case ERROR_DUP_NAME:
            return error_bad_path;
        case ERROR_BAD_NETPATH:
            return error_bad_path;
        case ERROR_NETWORK_BUSY:
            return error_file_access_denied;
        case ERROR_DEV_NOT_EXIST:
            return error_bad_path;
        case ERROR_ADAP_HDW_ERR:
            return error_hard_io;
        case ERROR_BAD_NET_RESP:
            return error_file_access_denied;
        case ERROR_UNEXP_NET_ERR:
            return error_hard_io;
        case ERROR_BAD_REM_ADAP:
            return error_invalid_file;
        case ERROR_NO_SPOOL_SPACE:
            return error_directory_full;
        case ERROR_NETNAME_DELETED:
            return error_file_access_denied;
        case ERROR_NETWORK_ACCESS_DENIED:
            return error_file_access_denied;
        case ERROR_BAD_DEV_TYPE:
            return error_invalid_file;
        case ERROR_BAD_NET_NAME:
            return error_bad_path;
        case ERROR_TOO_MANY_NAMES:
            return error_too_many_open_files;
        case ERROR_SHARING_PAUSED:
            return error_bad_path;
        case ERROR_REQ_NOT_ACCEP:
            return error_file_access_denied;
        case ERROR_FILE_EXISTS:
            return error_file_access_denied;
        case ERROR_CANNOT_MAKE:
            return error_file_access_denied;
        case ERROR_ALREADY_ASSIGNED:
            return error_bad_path;
        case ERROR_INVALID_PASSWORD:
            return error_file_access_denied;
        case ERROR_NET_WRITE_FAULT:
            return error_hard_io;
        case ERROR_DISK_CHANGE:
            return error_file_not_found;
        case ERROR_DRIVE_LOCKED:
            return error_file_lock_violation;
        case ERROR_BUFFER_OVERFLOW:
            return error_bad_path;
        case ERROR_DISK_FULL:
            return error_disk_full;
        case ERROR_NO_MORE_SEARCH_HANDLES:
            return error_too_many_open_files;
        case ERROR_INVALID_TARGET_HANDLE:
            return error_invalid_file;
        case ERROR_INVALID_CATEGORY:
            return error_hard_io;
        case ERROR_INVALID_NAME:
            return error_bad_path;
        case ERROR_INVALID_LEVEL:
            return error_bad_path;
        case ERROR_NO_VOLUME_LABEL:
            return error_bad_path;
        case ERROR_NEGATIVE_SEEK:
            return error_bad_seek;
        case ERROR_SEEK_ON_DEVICE:
            return error_bad_seek;
        case ERROR_DIR_NOT_ROOT:
            return error_bad_path;
        case ERROR_DIR_NOT_EMPTY:
            return error_remove_current_dir;
        case ERROR_LABEL_TOO_LONG:
            return error_bad_path;
        case ERROR_BAD_PATHNAME:
            return error_bad_path;
        case ERROR_LOCK_FAILED:
            return error_file_lock_violation;
        case ERROR_BUSY:
            return error_file_access_denied;
        case ERROR_INVALID_ORDINAL:
            return error_invalid_file;
        case ERROR_ALREADY_EXISTS:
            return error_file_access_denied;
        case ERROR_INVALID_EXE_SIGNATURE:
            return error_invalid_file;
        case ERROR_BAD_EXE_FORMAT:
            return error_invalid_file;
        case ERROR_FILENAME_EXCED_RANGE:
            return error_bad_path;
        case ERROR_META_EXPANSION_TOO_LONG:
            return error_bad_path;
        case ERROR_DIRECTORY:
            return error_bad_path;
        case ERROR_OPERATION_ABORTED:
            return error_hard_io;
        case ERROR_IO_INCOMPLETE:
            return error_hard_io;
        case ERROR_IO_PENDING:
            return error_hard_io;
        case ERROR_SWAPERROR:
            return error_file_access_denied;
        default:
            return error_file;
    }
}


CLASS_DECL_ACME void TRACELASTERROR()
{

   auto error = ::GetLastError();

   if (!error)
   {

      return;

   }

   string strErrorMessage = ::get_system_error_message(error);

   string strError;

   strError.Format("Error Message :\n%s\n", strErrorMessage.c_str());

   ::output_debug_string(strError);

}



