#include "framework.h"
#include "_windows.h"
#include "aura/os/windows_common/_file_c.h"
#include "aura/os/windows_common/file.h"


bool CLASS_DECL_AURA vfxFullPath(wstring & wstrFullPath,const wstring & wstrPath);

namespace windows
{


   file::file()
   {

      m_handleFile = INVALID_HANDLE_VALUE;
      m_dwAccessMode = 0;

   }


   file::file(HANDLE handleFile)
   {

      m_handleFile = handleFile;
      m_dwAccessMode = 0;

   }


   file::file(const char* pszFileName, efileopen eopen) 
   {

      ASSERT(__is_valid_string(pszFileName));


      if (!open(pszFileName, eopen))

      {

         ::file::throw_status(error_file, -1, pszFileName);


      }

   }

   file::~file()
   {

      if (m_handleFile != INVALID_HANDLE_VALUE)
      {
         close();
      }

   }


   ::status::result file::open(const ::file::path& pszFileName, const efileopen & eopenParam)
   {

      auto eopen = eopenParam;

      if (pszFileName.is_empty())
      {

         TRACE("windows::file::open file with empty name!!");

         return ::error_failed;

      }

      if (m_handleFile != INVALID_HANDLE_VALUE)
      {

         close();

      }

      ASSERT_VALID(this);
      ASSERT(__is_valid_string(pszFileName));

      eopen -= ::file::type_binary;

      if ((eopen & ::file::defer_create_directory) && (eopen & ::file::mode_write))
      {

         Context.dir().mk(pszFileName.folder());

      }

      m_handleFile = INVALID_HANDLE_VALUE;
      m_path.Empty();

      m_path = pszFileName;


      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::share_compat == 0);

      // map read/write mode
      ASSERT((::file::mode_read | ::file::mode_write | ::file::mode_read_write) == 3);
      DWORD dwAccess = 0;
      switch (eopen & 3)
      {
      case ::file::mode_read:
         dwAccess = GENERIC_READ;
         break;
      case ::file::mode_write:
         dwAccess = GENERIC_WRITE;
         break;
      case ::file::mode_read_write:
         dwAccess = GENERIC_READ | GENERIC_WRITE;
         break;
      default:
         dwAccess = GENERIC_READ;
         break;
      }

      // map share mode
      DWORD dwShareMode = 0;
      switch (eopen & 0x70)    // map compatibility mode to exclusive
      {
      default:
         ASSERT(FALSE);  // invalid share mode?
      case ::file::share_compat:
      case ::file::share_exclusive:
         dwShareMode = 0;
         break;
      case ::file::share_deny_write:
         dwShareMode = FILE_SHARE_READ;
         break;
      case ::file::share_deny_read:
         dwShareMode = FILE_SHARE_WRITE;
         break;
      case ::file::share_deny_none:
         dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
         break;
      }

      // Note: type_text and type_binary are used in derived classes only.

      // map modeNoInherit flag
      SECURITY_ATTRIBUTES sa;
      SECURITY_ATTRIBUTES* psa = nullptr;
      if ((eopen & ::file::mode_no_inherit) != FALSE)
      {
         psa = &sa;
         xxf_zero(sa);
         sa.nLength = sizeof(sa);
         sa.lpSecurityDescriptor = nullptr;

         sa.bInheritHandle = FALSE;
      }

      // map creation flags
      DWORD dwCreateFlag;
      if (eopen & ::file::mode_create)
      {
         if (eopen & ::file::mode_no_truncate)
            dwCreateFlag = OPEN_ALWAYS;
         else
            dwCreateFlag = CREATE_ALWAYS;
      }
      else
         dwCreateFlag = OPEN_EXISTING;

      HANDLE handleFile = INVALID_HANDLE_VALUE;

      DWORD dwWaitSharingViolation = 84;
      auto tickStart = ::tick::now();

      //DWORD dwFileSharingViolationRetryTimeout = ::get_thread() != nullptr ? ::get_thread()->get_file_sharing_violation_timeout_total_milliseconds() : 0;

   retry:

      wstring wstrFileName(m_path);

      // attempt file creation
      //HANDLE handleFile = shell::CreateFile(::str::international::utf8_to_unicode(m_path), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);

      handleFile = ::CreateFileW(wstrFileName, dwAccess, dwShareMode, psa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, nullptr);

      if (handleFile == INVALID_HANDLE_VALUE)
      {

         DWORD dwLastError = ::get_last_error();

         if (!(eopen & ::file::no_share_violation_wait))
         {

            if (dwLastError == ERROR_SHARING_VIOLATION && ::thread_get_run() && (tickStart.elapsed()) < m_dwErrorBlockTimeout)
            {

               Sleep(max(m_dwErrorBlockTimeout / 10, 50));

               goto retry;

            }

         }

         ::estatus     estatus = ::file::os_error_to_status(dwLastError);

         if (::file::should_ignore_file_exception_callstack(estatus))
         {

            return ::error_failed;

         }

         return estatus;


      }

      m_handleFile = handleFile;

      m_dwAccessMode = dwAccess;

      m_eopen = eopen;

      return ::success;

   }


   memsize file::read(void* pdata, memsize nCount)

   {
      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      if (nCount == 0)
         return 0;   // avoid Win32 "null-read"

      ASSERT(pdata != nullptr);

      ASSERT(__is_valid_address(pdata, nCount));


      DWORD dwRead;
      if (!::ReadFile((HANDLE)m_handleFile, pdata, (DWORD)nCount, &dwRead, nullptr))

         ::file::throw_os_error((LONG)::get_last_error());

      return (UINT)dwRead;
   }

   void file::write(const void* pdata, memsize nCount)

   {
      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      if (nCount == 0)
         return;     // avoid Win32 "null-write" option

      ASSERT(pdata != nullptr);

      ASSERT(__is_valid_address(pdata, nCount, FALSE));


      DWORD nWritten;
      if (!::WriteFile((HANDLE)m_handleFile, pdata, (DWORD)nCount, &nWritten, nullptr))

         ::file::throw_os_error((LONG)::get_last_error(), m_path);

      // Win32s will not return an error all the time (usually DISK_FULL)
      if (nWritten != nCount)
         ::file::throw_status(error_disk_full, -1, m_path);
   }

   filesize file::seek(filesize lOff, ::file::e_seek nFrom)
   {

      if (m_handleFile == INVALID_HANDLE_VALUE)
         ::file::throw_os_error((LONG)0);

      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      LONG lLoOffset = lOff & 0xffffffff;
      LONG lHiOffset = (lOff >> 32) & 0xffffffff;

      filesize posNew = ::SetFilePointer((HANDLE)m_handleFile, lLoOffset, &lHiOffset, (DWORD)nFrom);
      posNew |= ((filesize)lHiOffset) << 32;
      if (posNew == (filesize)-1)
         ::file::throw_os_error((LONG)::get_last_error());

      return posNew;
   }

   filesize file::get_position() const
   {
      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      LONG lLoOffset = 0;
      LONG lHiOffset = 0;

      filesize pos = ::SetFilePointer((HANDLE)m_handleFile, lLoOffset, &lHiOffset, FILE_CURRENT);
      pos |= ((filesize)lHiOffset) << 32;
      if (pos == (filesize)-1)
         ::file::throw_os_error((LONG)::get_last_error());

      return pos;
   }

   void file::flush()
   {
      ASSERT_VALID(this);

      if (m_handleFile == INVALID_HANDLE_VALUE || !(m_dwAccessMode & GENERIC_WRITE))
         return;

      if (!::FlushFileBuffers((HANDLE)m_handleFile))
      {
         DWORD dwLastError = ::get_last_error();
         if (dwLastError == ERROR_INVALID_HANDLE
            || dwLastError == ERROR_ACCESS_DENIED)
         {
         }
         else
         {
            ::file::throw_os_error((LONG)dwLastError);
         }
      }
   }

   void file::close()
   {

      flush();

      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      bool bError = FALSE;
      DWORD dwLastError = 0;
      if (m_handleFile != INVALID_HANDLE_VALUE)
      {
         bError = !::CloseHandle((HANDLE)m_handleFile);
         if (bError)
         {
            dwLastError = ::get_last_error();
         }
      }

      m_handleFile = INVALID_HANDLE_VALUE;

      m_dwAccessMode = 0;

      if (bError)
         ::file::throw_os_error(dwLastError, m_path);

   }


   void file::lock(filesize dwPos, filesize dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      if (!::LockFile((HANDLE)m_handleFile, LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
         ::file::throw_os_error((LONG)::get_last_error());
   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {
      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      if (!::UnlockFile((HANDLE)m_handleFile, LODWORD(dwPos), HIDWORD(dwPos), LODWORD(dwCount), HIDWORD(dwCount)))
         ::file::throw_os_error((LONG)::get_last_error());
   }


   void file::set_size(filesize dwNewLen)
   {

      ASSERT_VALID(this);
      ASSERT(m_handleFile != INVALID_HANDLE_VALUE);

      seek((LONG)dwNewLen, (::file::e_seek)::file::seek_begin);

      if (!::SetEndOfFile((HANDLE)m_handleFile))
         ::file::throw_os_error((LONG)::get_last_error());

   }


   filesize file::get_size() const
   {

      ASSERT_VALID(this);

      filesize dwLen, dwCur;

      // seek is a non const operation
      __pointer(::windows::file) pFile = (::windows::file*)this;
      dwCur = pFile->seek(0L, ::file::seek_current);
      dwLen = pFile->seek_to_end();
      if (dwCur != (u64)pFile->seek((filesize)dwCur, ::file::seek_begin))
         __throw(::exception::exception("file cursor not in same place after getting length"));

      return (filesize)dwLen;

   }


   void file::assert_valid() const
   {

      ::context_object::assert_valid();
      
   }


   void file::dump(dump_context& dumpcontext) const
   {

      ::context_object::dump(dumpcontext);

      dumpcontext << "with handle " << m_handleFile;
      dumpcontext << " and name \"" << m_path << "\"";
      dumpcontext << "\n";

   }


#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41
#define EILSEQ          42

   /*
   * Support EDEADLOCK for compatibiity with older MS-C versions.
   */
#define EDEADLOCK       EDEADLK


   /////////////////////////////////////////////////////////////////////////////
   // file name handlers

   //string file::GetFileName() const
   //{
   //   ASSERT_VALID(this);

   //   ::file::file_status status;
   //   GetStatus(status);
   //   return file_name_dup(status.m_strFullName);
   //}

   //string file::GetFileTitle() const
   //{
   //   ASSERT_VALID(this);

   //   ::file::file_status status;
   //   GetStatus(status);
   //   return file_title_dup(status.m_strFullName);
   //}

   ::file::path file::get_file_path() const
   {

      return m_path;

   }



   bool file::get_status(::file::file_status& rStatus) const
   {

      ASSERT_VALID(this);

      rStatus.m_strFullName = m_path;

      if (m_handleFile != INVALID_HANDLE_VALUE)
      {

         BY_HANDLE_FILE_INFORMATION information;

         if (!::GetFileInformationByHandle((HANDLE)m_handleFile, &information))
         {

            return false;

         }

         ULARGE_INTEGER integer;

         integer.HighPart = information.nFileSizeHigh;
         integer.LowPart = information.nFileSizeLow;

         rStatus.m_size = integer.QuadPart;

         // don't return an error for this because previous versions of aura API didn't
         if (information.dwFileAttributes == 0xFFFFFFFF)
         {

            rStatus.m_attribute = 0;

         }
         else
         {
            rStatus.m_attribute = (BYTE)information.dwFileAttributes & 0xff;

         }

         // convert times as appropriate
         rStatus.m_ctime = ::datetime::time(information.ftCreationTime);
         rStatus.m_atime = ::datetime::time(information.ftLastAccessTime);
         rStatus.m_mtime = ::datetime::time(information.ftLastWriteTime);

         if (rStatus.m_ctime.get_time() == 0)
         {

            rStatus.m_ctime = rStatus.m_mtime;

         }

         if (rStatus.m_atime.get_time() == 0)
         {

            rStatus.m_atime = rStatus.m_mtime;

         }

      }

      return true;

   }


   bool file::is_opened() const
   {

      return m_handleFile != INVALID_HANDLE_VALUE;

   }


   void file::set_file_path(const ::file::path & path)
   {

      ASSERT_VALID(this);

      m_path = path;

   }



   file::operator HANDLE() const
   {

      return m_handleFile;

   }

   //u64 file::ReadHuge(void * pBuffer, u64 dwCount)

   //{

   //   return (u64) read(pBuffer, (UINT)dwCount);


   //}

   //void file::WriteHuge(const void * pBuffer, u64 dwCount)

   //{

   //   write(pBuffer, (UINT)dwCount);


   //}



} // namespace windows




#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)




// turn a file, relative path or other into an absolute path
bool CLASS_DECL_AURA vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath)
// pszPathOut = buffer of _MAX_PATH

// pszFileIn = file, relative path or absolute path

// (both in ANSI character set)
{

   strsize dwAllocLen = wstrPath.get_length() + _MAX_PATH;

   auto pwszFullPath = wstrFullPath.get_string_buffer(dwAllocLen);

   // first, fully qualify the path name
   unichar * pszFilePart;


   strsize dwLen = GetFullPathNameW(wstrPath, (DWORD) dwAllocLen, pwszFullPath, &pszFilePart);

   wstrFullPath.release_string_buffer();


   if(dwLen == 0)
   {
      wstrFullPath.release_string_buffer();


      wstrFullPath = wstrPath; // take it literally

      return FALSE;

   }

   else if(dwLen > dwAllocLen)
   {

      dwAllocLen = dwLen + _MAX_PATH;

      dwLen = GetFullPathNameW(wstrPath, (DWORD) dwAllocLen, pwszFullPath, &pszFilePart);

      wstrFullPath.release_string_buffer();


      if(dwLen == 0 || dwLen > dwAllocLen)
      {

         wstrFullPath = wstrPath; // take it literally

         return FALSE;

      }

   }

   wstring wstrRoot;
   // determine the root name of the volume
   vfxGetRoot(wstrRoot, wstrFullPath);

   // get file system information for the volume
   DWORD dwFlags, dwDummy;
   if (!GetVolumeInformationW(wstrRoot, nullptr, 0, nullptr, &dwDummy, &dwFlags, nullptr, 0))
   {
      //      TRACE1("Warning: could not get volume information '%s'.\n", strRoot);
      return FALSE;   // preserving case may not be correct
   }

   // not all characters have complete uppercase/lowercase
   if (!(dwFlags & FS_CASE_IS_PRESERVED))
      wstrFullPath.make_upper();

   // assume non-UNICODE file systems, use OEM character set
   if (!(dwFlags & FS_UNICODE_STORED_ON_DISK))
   {
      WIN32_FIND_DATAW data;
      HANDLE h = FindFirstFileW(wstrPath, &data);
      if (h != INVALID_HANDLE_VALUE)
      {
         FindClose(h);
         i32 iLenFileName = lstrlenW(data.cFileName);
         if(iLenFileName >=  MAX_PATH)
         {
            wstring wstrBackup = wstrFullPath;
            strsize iFilePart = pszFilePart - wstrFullPath;

            auto pwsz = wstrFullPath.get_string_buffer(iFilePart + iLenFileName + 32); // arrange more space with more 32 extra wchars
            lstrcpynW(pwsz, wstrBackup, (i32) iFilePart);
            wstrFullPath.release_string_buffer();
            pszFilePart = pwsz + iFilePart;

         }
         lstrcpyW(pszFilePart, data.cFileName);

         wstrFullPath.release_string_buffer();
      }
   }
   return TRUE;
}


void CLASS_DECL_AURA vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
{
   WCHAR szLongPathName[_MAX_PATH];
   wstring wstrShortName;
   ::GetModuleFileNameW(hInst, szLongPathName, _MAX_PATH);
   if(::GetShortPathNameW(szLongPathName, wstrShortName.get_string_buffer(_MAX_PATH * 4), _MAX_PATH * 4) == 0)
   {
      // rare failure case (especially on not-so-modern file systems)
      ::str::international::unicode_to_utf8(strShortName, szLongPathName);
   }
   else
   {
      wstrShortName.release_string_buffer();
      ::str::international::unicode_to_utf8(strShortName, wstrShortName);
   }
}




string CLASS_DECL_AURA vfxStringFromCLSID(REFCLSID rclsid)
{
   WCHAR szCLSID[256];
   wsprintfW(szCLSID, L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
             rclsid.Data1, rclsid.Data2, rclsid.Data3,
             rclsid.Data4[0], rclsid.Data4[1], rclsid.Data4[2], rclsid.Data4[3],
             rclsid.Data4[4], rclsid.Data4[5], rclsid.Data4[6], rclsid.Data4[7]);
   return szCLSID;
}

bool CLASS_DECL_AURA vfxGetInProcServer(const char * pszCLSID, string & str)

{
   HKEY hKey = nullptr;
   bool b = FALSE;
   if (RegOpenKeyW(HKEY_CLASSES_ROOT, L"CLSID", &hKey) == ERROR_SUCCESS)
   {
      HKEY hKeyCLSID = nullptr;
      if (RegOpenKeyW(hKey, wstring(pszCLSID), &hKeyCLSID) == ERROR_SUCCESS)

      {
         HKEY hKeyInProc = nullptr;
         if (RegOpenKeyW(hKeyCLSID, L"InProcServer32", &hKeyInProc) ==
               ERROR_SUCCESS)
         {
            wstring wstr;
            LPWSTR psz = wstr.get_string_buffer(_MAX_PATH);

            DWORD dwSize = _MAX_PATH * sizeof(WCHAR);
            DWORD dwType;
            LONG lRes = ::RegQueryValueExW(hKeyInProc,L"",
                                          nullptr, &dwType, (BYTE*)psz, &dwSize);

            str.release_string_buffer();
            str = wstr;
            b = (lRes == ERROR_SUCCESS);
            RegCloseKey(hKeyInProc);
         }
         RegCloseKey(hKeyCLSID);
      }
      RegCloseKey(hKey);
   }
   return b;
}
//#endif  //!___NO_OLE_SUPPORT



// turn a file, relative path or other into an absolute path
bool CLASS_DECL_AURA vfxFullPath(unichar * pszPathOut, const unichar * pszFileIn)

// pszPathOut = buffer of _MAX_PATH

// pszFileIn = file, relative path or absolute path

// (both in ANSI character set)
{
   ASSERT(__is_valid_address(pszPathOut, _MAX_PATH));


   // first, fully qualify the path name
   unichar * pszFilePart;

   if (!GetFullPathNameW(pszFileIn, _MAX_PATH, pszPathOut, &pszFilePart))
   {

      lstrcpynW(pszPathOut, pszFileIn, _MAX_PATH); // take it literally

      return FALSE;

   }

   string strRoot;
   // determine the root name of the volume
   vfxGetRoot(pszPathOut, strRoot);


   // get file system information for the volume
   DWORD dwFlags, dwDummy;
   if (!GetVolumeInformationW(::str::international::utf8_to_unicode(strRoot), nullptr, 0, nullptr, &dwDummy, &dwFlags, nullptr, 0))
   {
      //      TRACE1("Warning: could not get volume information '%s'.\n", strRoot);
      return FALSE;   // preserving case may not be correct
   }

   // not all characters have complete uppercase/lowercase
   if (!(dwFlags & FS_CASE_IS_PRESERVED))
      CharUpperW(pszPathOut);


   // assume non-UNICODE file systems, use OEM character set
   if (!(dwFlags & FS_UNICODE_STORED_ON_DISK))
   {
      WIN32_FIND_DATAW data;
      HANDLE h = FindFirstFileW(pszFileIn, &data);

      if (h != INVALID_HANDLE_VALUE)
      {
         FindClose(h);
         lstrcpyW(pszFilePart, data.cFileName);

      }
   }
   return TRUE;
}




void CLASS_DECL_AURA vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath)
{
   //   ASSERT(pszPath != nullptr);

   // determine the root name of the volume
   wstrRoot = wstrPath;
   unichar * pszRoot = wstrRoot.get_string_buffer((wstrPath.get_length() + MAX_PATH ) *2);

   unichar * psz;

   for (psz = pszRoot; *psz != L'\0'; psz = _wcsinc(psz))

   {
      // find first double slash and stop
      if (IsDirSep(psz[0]) && IsDirSep(psz[1]))

         break;
   }
   if (*psz != '\0')

   {
      // it is a UNC name, find second slash past '\\'
      ASSERT(IsDirSep(psz[0]));

      ASSERT(IsDirSep(psz[1]));

      psz += 2;

      while (*psz != '\0' && (!IsDirSep(*psz)))

         psz = _wcsinc(psz);

      if (*psz != '\0')

         psz = _wcsinc(psz);

      while (*psz != '\0' && (!IsDirSep(*psz)))

         psz = _wcsinc(psz);

      // terminate it just after the UNC root (ie. '\\server\share\')
      if (*psz != '\0')

         psz[1] = '\0';

   }
   else
   {
      // not a UNC, look for just the first slash
      psz = pszRoot;

      while (*psz != '\0' && (!IsDirSep(*psz)))

         psz = _wcsinc(psz);

      // terminate it just after root (ie. 'x:\')
      if (*psz != '\0')

         psz[1] = '\0';

   }
   wstrRoot.release_string_buffer();
}


void CLASS_DECL_AURA vfxGetRoot(const unichar * pszPath, string& strRoot)

{
   ASSERT(pszPath != nullptr);

   wstring wstrRoot;
   // determine the root name of the volume
   unichar * pszRoot = wstrRoot.get_string_buffer(_MAX_PATH * 4);

   __memset(pszRoot, 0, _MAX_PATH * 4);

   lstrcpynW(pszRoot, pszPath, _MAX_PATH * 4);

   unichar * psz;

   for (psz = pszRoot; *psz != '\0'; psz = _wcsinc(psz))

   {
      // find first double slash and stop
      if (IsDirSep(psz[0]) && IsDirSep(psz[1]))

         break;
   }
   if (*psz != '\0')

   {
      // it is a UNC name, find second slash past '\\'
      ASSERT(IsDirSep(psz[0]));

      ASSERT(IsDirSep(psz[1]));

      psz += 2;

      while (*psz != '\0' && (!IsDirSep(*psz)))

         psz = _wcsinc(psz);

      if (*psz != '\0')

         psz = _wcsinc(psz);

      while (*psz != '\0' && (!IsDirSep(*psz)))

         psz = _wcsinc(psz);

      // terminate it just after the UNC root (ie. '\\server\share\')
      if (*psz != '\0')

         psz[1] = '\0';

   }
   else
   {
      // not a UNC, look for just the first slash
      psz = pszRoot;

      while (*psz != '\0' && (!IsDirSep(*psz)))

         psz = _wcsinc(psz);

      // terminate it just after root (ie. 'x:\')
      if (*psz != '\0')

         psz[1] = '\0';

   }
   ::str::international::unicode_to_utf8(strRoot, wstrRoot);
}




UINT CLASS_DECL_AURA vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, UINT nMax)

{
   ASSERT(pszTitle == nullptr ||

          __is_valid_address(pszTitle, _MAX_FNAME));

   ASSERT(__is_valid_string(pszPathName));


   // always capture the complete file name including extension (if present)
   unichar * pszTemp = (unichar *)pszPathName;

   for (const unichar * psz = pszPathName; *psz != '\0'; psz = _wcsinc(psz))

   {
      // remember last directory/drive separator
      if (*psz == '\\' || *psz == '/' || *psz == ':')

         pszTemp = (unichar *)_wcsinc(psz);

   }

   // pszTitle can be nullptr which just returns the number of bytes

   if (pszTitle == nullptr)

      return lstrlenW(pszTemp)+1;


   // otherwise copy it into the buffer provided
   lstrcpynW(pszTitle, pszTemp, nMax);

   return 0;
}







//namespace windows
//{
//
//   //::estatus ::file::errno_to_status(i32 nErrno)
//   //{
//   //   switch(nErrno)
//   //   {
//   //   case EPERM:
//   //   case EACCES:
//   //      return error_file_access_denied;
//   //   case EBADF:
//   //      return error_invalid_file;
//   //   case EDEADLOCK:
//   //      return ::file::exception::sharingViolation;
//   //   case EMFILE:
//   //      return error_too_many_open_files;
//   //   case ENOENT:
//   //   case ENFILE:
//   //      return error_file_not_found;
//   //   case ENOSPC:
//   //      return error_disk_full;
//   //   case EINVAL:
//   //   case EIO:
//   //      return error_hard_io;
//   //   default:
//   //      return ::file::exception::type_generic;
//   //   }
//
//   //}
//
//
//} // namespace windows






