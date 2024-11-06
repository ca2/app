#pragma once

#define WH_SHSTDAPI(type) type


namespace ios
{
   
   class CLASS_DECL_APEX shell
   {
   public:
      shell();
      virtual ~shell();
      
      
      static shell theLinuxShell;
      
      static bool Initialize();
      // xxx   static int_bool WINAPI _SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
      // xxx   static HANDLE WINAPI _FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
      // xxx   static int_bool WINAPI _FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
      /*   static int_bool WINAPI _MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
       static unsigned int WINAPI _GetFullPathName(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
       static WCHAR * __cdecl __fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
       static int_bool WINAPI _GetVolumeInformation(
       const unichar * lpRootPathName,           // root directory
       unichar * lpVolumeNameBuffer,        // volume name buffer
       unsigned int nVolumeNameSize,            // length of name buffer
       LPDWORD lpVolumeSerialNumber,     // volume serial number
       LPDWORD lpMaximumComponentLength, // maximum file name length
       LPDWORD lpFileSystemFlags,        // file system options
       unichar * lpFileSystemNameBuffer,    // file system name buffer
       unsigned int nFileSystemNameSize);         // length of file system name buffer
       // xxx   static DWORD_PTR __stdcall _SHGetFileInfo(
       // xxx const unichar * pszPath,
       // xxx unsigned int dwFileAttributes,
       // xxx SHFILEINFOW *psfi,
       // xxx unsigned int cbFileInfo,
       // xxx unsigned int uFlags);
       static int_bool __stdcall _GetStringTypeEx(
       LCID Locale,
       unsigned int dwInfoType,
       const unichar * lpSrcStr,
       int cchSrc,
       LPWORD lpCharType);
       static unsigned int WINAPI  _GetTempPath(
       unsigned int nBufferLength,
       unichar * lpBuffer);
       static unsigned int WINAPI _GetTempFileName(
       const unichar * lpPathName,
       const unichar * lpPrefixString,
       unsigned int uUnique,
       unichar * lpTempFileName);
       static HANDLE WINAPI _CreateFile(
       const unichar * lpFileName,
       unsigned int dwDesiredAccess,
       unsigned int dwShareMode,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
       unsigned int dwCreationDisposition,
       unsigned int dwFlagsAndAttributes,
       HANDLE hTemplateFile
       );
       static unsigned int WINAPI _GetModuleFileName(
       HMODULE hModule,
       unichar * lpFilename,
       unsigned int nSize
       );
       // xxx    static int_bool WINAPI _GetClassInfo(
       // xxx        HINSTANCE hInstance ,
       // xxx        const unichar * lpClassName,
       // xxx        LPWNDCLASSW lpWndClass);
       // xxx    static ATOM WINAPI _RegisterClass(
       // xxx const WNDCLASSW *lpWndClass);
       
       static oswindow WINAPI _CreateWindowEx(
       unsigned int dwExStyle,
       const unichar * lpClassName,
       const unichar * lpWindowName,
       unsigned int uStyle,
       int x,
       int y,
       int nWidth,
       int nHeight,
       oswindow hWndParent,
       HMENU hMenu,
       HINSTANCE hInstance,
       LPVOID lpParam);
       
       
       
       
       
       // xxx    int_bool (WINAPI * m_pfnSHGetPathFromIDList)(LPCITEMIDLIST pidl, unichar * pszPath);
       // xxx    HANDLE (WINAPI * m_pfnFindFirstFile)(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
       // xxx    int_bool (WINAPI * m_pfnFindNextFile)(HANDLE handle, WIN32_FIND_DATAW * lpdata);
       int_bool (WINAPI * m_pfnMoveFile)(const unichar * lpExistingFileName, const unichar * lpNewFileName);
       WCHAR * (__cdecl * m_pfn_fullpath)(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
       unsigned int (WINAPI * m_pfnGetFullPathName)(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
       int_bool (WINAPI * m_pfnGetVolumeInformation)(
       const unichar * lpRootPathName,           // root directory
       unichar * lpVolumeNameBuffer,        // volume name buffer
       unsigned int nVolumeNameSize,            // length of name buffer
       LPDWORD lpVolumeSerialNumber,     // volume serial number
       LPDWORD lpMaximumComponentLength, // maximum file name length
       LPDWORD lpFileSystemFlags,        // file system options
       unichar * lpFileSystemNameBuffer,    // file system name buffer
       unsigned int nFileSystemNameSize);         // length of file system name buffer
       
       // xxx    DWORD_PTR (__stdcall * m_pfnSHGetFileInfo)(
       // xxx       const unichar * pszPath,
       // xxx       unsigned int dwFileAttributes,
       // xxx       SHFILEINFOW *psfi,
       // xxx       unsigned int cbFileInfo,
       // xxx       unsigned int uFlags);
       int_bool (__stdcall * m_pfnGetStringTypeEx)(
       LCID Locale,
       unsigned int dwInfoType,
       const unichar * lpSrcStr,
       int cchSrc,
       LPWORD lpCharType);
       unsigned int (WINAPI * m_pfnGetTempPath)(
       unsigned int nBufferLength,
       unichar * lpBuffer);
       unsigned int (WINAPI * m_pfnGetTempFileName)(
       const unichar * lpPathName,
       const unichar * lpPrefixString,
       unsigned int uUnique,
       unichar * lpTempFileName);
       HANDLE (WINAPI * m_pfnCreateFile)(
       const unichar * lpFileName,
       unsigned int dwDesiredAccess,
       unsigned int dwShareMode,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
       unsigned int dwCreationDisposition,
       unsigned int dwFlagsAndAttributes,
       HANDLE hTemplateFile
       );
       
       unsigned int (WINAPI * m_pfnGetModuleFileName)(
       HMODULE hModule,
       unichar * lpFilename,
       unsigned int nSize
       );
       
       // xxx    int_bool (WINAPI * m_pfnGetClassInfo)(
       // xxx HINSTANCE hInstance ,
       // xxx        const unichar * lpClassName,
       // xxx        LPWNDCLASSW lpWndClass);
       
       // xxx ATOM (WINAPI * m_pfnRegisterClass)(
       // xxx const WNDCLASSW *lpWndClass);
       
       oswindow (WINAPI * m_pfnCreateWindowEx)(
       unsigned int dwExStyle,
       const unichar * lpClassName,
       const unichar * lpWindowName,
       unsigned int uStyle,
       int x,
       int y,
       int nWidth,
       int nHeight,
       oswindow hWndParent,
       HMENU hMenu,
       HINSTANCE hInstance,
       LPVOID lpParam);
       
       
       
       
       
       
       
       
       // xxx    static int_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str);
       // xxx    static int_bool SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath);
       // xxx    static HANDLE FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata);
       // xxx    static int_bool WINAPI FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata);
       static int_bool MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName);
       static WCHAR * __cdecl _fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen);
       static unsigned int GetFullPathName(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart);
       static int_bool GetVolumeInformation(
       const unichar * lpRootPathName,           // root directory
       unichar * lpVolumeNameBuffer,        // volume name buffer
       unsigned int nVolumeNameSize,            // length of name buffer
       LPDWORD lpVolumeSerialNumber,     // volume serial number
       LPDWORD lpMaximumComponentLength, // maximum file name length
       LPDWORD lpFileSystemFlags,        // file system options
       unichar * lpFileSystemNameBuffer,    // file system name buffer
       unsigned int nFileSystemNameSize);         // length of file system name buffer
       
       // xxx    static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
       // xxx       const unichar * pszPath,
       // xxx       unsigned int dwFileAttributes,
       // xxx       SHFILEINFOW *psfi,
       // xxx       unsigned int cbFileInfo,
       // xxx       unsigned int uFlags);
       
       static int_bool  GetStringTypeEx(
       LCID Locale,
       unsigned int dwInfoType,
       const char * lpSrcStr,
       int cchSrc,
       LPWORD lpCharType);
       
       static unsigned int GetTempPathW(
       unsigned int nBufferLength,
       unichar * lpBuffer);
       
       static unsigned int GetTempFileNameW(
       const unichar * lpPathName,
       const unichar * lpPrefixString,
       unsigned int uUnique,
       unichar * lpTempFileName);
       
       static HANDLE CreateFile(
       const unichar * lpFileName,
       unsigned int dwDesiredAccess,
       unsigned int dwShareMode,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
       unsigned int dwCreationDisposition,
       unsigned int dwFlagsAndAttributes,
       HANDLE hTemplateFile);
       
       static unsigned int WINAPI GetModuleFileName(
       HMODULE hModule,
       unichar * lpFilename,
       unsigned int nSize
       );
       
       // xxx    static int_bool WINAPI GetClassInfo(
       // xxx        HINSTANCE hInstance ,
       // xxx        const unichar * lpClassName,
       // xxx        LPWNDCLASSW lpWndClass);
       
       // xxx    static ATOM WINAPI RegisterClass(
       // xxx          const WNDCLASSW *lpWndClass);
       
       static oswindow WINAPI CreateWindowEx(
       unsigned int dwExStyle,
       const unichar * lpClassName,
       const unichar * lpWindowName,
       unsigned int uStyle,
       int x,
       int y,
       int nWidth,
       int nHeight,
       oswindow hWndParent,
       HMENU hMenu,
       HINSTANCE hInstance,
       LPVOID lpParam);
       
       
       // xxx    static WH_SHSTDAPI(unsigned int) SHGetFileInfo(
       // xxx       const ::file::path & path,
       // xxx       unsigned int dwFileAttributes,
       // xxx       SHFILEINFO *psfi,
       // xxx       unsigned int cbFileInfo,
       // xxx       unsigned int uFlags);
       
       static unsigned int GetTempPath(string & str);
       
       static unsigned int GetTempFileName(
       const char * lpPathName,
       const char * lpPrefixString,
       unsigned int uUnique,
       string & str);
       
       static int_bool MoveFile(const char * lpExistingFileName, const char * lpNewFileName);
       */
   };
   
   
   
   /*inline int_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, string & str)
    {
    unichar * pwszPath = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
    if(!(*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pwszPath))
    {
    free(pwszPath);
    return false;
    }
    gen::international::unicode_to_utf8(str, pwszPath);
    free(pwszPath);
    return true;
    }
    */
   /*
    
    inline int_bool shell::SHGetPathFromIDList(LPCITEMIDLIST pidl, unichar * pszPath)
    {
    return (*theLinuxShell.m_pfnSHGetPathFromIDList)(pidl, pszPath);
    }
    */
   /*
    inline HANDLE shell::FindFirstFile(const unichar * pcsz, WIN32_FIND_DATAW * lpdata)
    {
    return (*theLinuxShell.m_pfnFindFirstFile)(pcsz, lpdata);
    }
    
    inline int_bool shell::FindNextFile(HANDLE handle, WIN32_FIND_DATAW * lpdata)
    {
    return (*theLinuxShell.m_pfnFindNextFile)(handle, lpdata);
    }
    
    */
   
   /*
    inline WCHAR * shell::_fullpath(WCHAR *UserBuf, const WCHAR *path, size_t maxlen)
    {
    return (*theLinuxShell.m_pfn_fullpath)(UserBuf, path, maxlen);
    }
    
    inline unsigned int shell::GetFullPathName(const unichar * lpFileName, unsigned int nBufferLength, unichar * lpBuffer, unichar ** lpFilePart)
    {
    return (*theLinuxShell.m_pfnGetFullPathName)(lpFileName, nBufferLength, lpBuffer, lpFilePart);
    }
    
    
    inline int_bool shell::MoveFile(const unichar * lpExistingFileName, const unichar * lpNewFileName)
    {
    return (*theLinuxShell.m_pfnMoveFile)(lpExistingFileName, lpNewFileName);
    }
    
    inline int_bool shell::GetVolumeInformation(
    const unichar * lpRootPathName,           // root directory
    unichar * lpVolumeNameBuffer,        // volume name buffer
    unsigned int nVolumeNameSize,            // length of name buffer
    LPDWORD lpVolumeSerialNumber,     // volume serial number
    LPDWORD lpMaximumComponentLength, // maximum file name length
    LPDWORD lpFileSystemFlags,        // file system options
    unichar * lpFileSystemNameBuffer,    // file system name buffer
    unsigned int nFileSystemNameSize)         // length of file system name buffer
    {
    return (*theLinuxShell.m_pfnGetVolumeInformation)(
    lpRootPathName,           // root directory
    lpVolumeNameBuffer,        // volume name buffer
    nVolumeNameSize,            // length of name buffer
    lpVolumeSerialNumber,     // volume serial number
    lpMaximumComponentLength, // maximum file name length
    lpFileSystemFlags,        // file system options
    lpFileSystemNameBuffer,    // file system name buffer
    nFileSystemNameSize);         // length of file system name buffer
    }
    
    
    inline unsigned int shell::SHGetFileInfo(
    const unichar * pszPath,
    unsigned int dwFileAttributes,
    SHFILEINFOW *psfi,
    unsigned int cbFileInfo,
    unsigned int uFlags)
    {
    return (*theLinuxShell.m_pfnSHGetFileInfo)(
    pszPath,
    dwFileAttributes,
    psfi,
    cbFileInfo,
    uFlags);
    }
    */
   /*
    inline unsigned int shell::GetTempPathW(
    unsigned int nBufferLength,
    unichar * lpBuffer)
    {
    return (*theLinuxShell.m_pfnGetTempPath)(
    nBufferLength,
    lpBuffer);
    }
    
    inline unsigned int shell::GetTempFileNameW(
    const unichar * lpPathName,
    const unichar * lpPrefixString,
    unsigned int uUnique,
    unichar * lpTempFileName)
    {
    return (*theLinuxShell.m_pfnGetTempFileName)(
    lpPathName,
    lpPrefixString,
    uUnique,
    lpTempFileName);
    }
    
    inline HANDLE shell::CreateFile(
    const unichar * lpFileName,
    unsigned int dwDesiredAccess,
    unsigned int dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    unsigned int dwCreationDisposition,
    unsigned int dwFlagsAndAttributes,
    HANDLE hTemplateFile)
    {
    return (*theLinuxShell.m_pfnCreateFile)(
    lpFileName,
    dwDesiredAccess,
    dwShareMode,
    lpSecurityAttributes,
    dwCreationDisposition,
    dwFlagsAndAttributes,
    hTemplateFile);
    }
    
    inline unsigned int shell::GetModuleFileName(
    HMODULE hModule,
    unichar * lpFilename,
    unsigned int nSize
    )
    {
    return (*theLinuxShell.m_pfnGetModuleFileName)(
    hModule,
    lpFilename,
    nSize);
    }
    
    inline int_bool shell::GetClassInfo(
    HINSTANCE hInstance ,
    const unichar * lpClassName,
    LPWNDCLASSW lpWndClass)
    {
    return (*theLinuxShell.m_pfnGetClassInfo)(
    hInstance ,
    lpClassName,
    lpWndClass);
    }
    
    inline ATOM shell::RegisterClass(
    const WNDCLASSW *lpWndClass)
    {
    return (*theLinuxShell.m_pfnRegisterClass)(
    lpWndClass);
    }*/
   /*
    inline oswindow shell::CreateWindowEx(
    unsigned int dwExStyle,
    const unichar * lpClassName,
    const unichar * lpWindowName,
    unsigned int uStyle,
    int x,
    int y,
    int nWidth,
    int nHeight,
    oswindow hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam)
    {
    return (*theLinuxShell.m_pfnCreateWindowEx)(
    dwExStyle,
    lpClassName,
    lpWindowName,
    uStyle,
    x,
    y,
    nWidth,
    nHeight,
    hWndParent,
    hMenu,
    hInstance,
    lpParam);
    
    }
    
    inline unsigned int shell::GetTempPath(string & str)
    {
    unichar * pwsz = (unichar *) malloc(sizeof(unichar) * MAX_PATH * 4);
    unsigned int dwResult = (*theLinuxShell.m_pfnGetTempPath)(sizeof(unichar) * MAX_PATH * 4, pwsz);
    gen::international::unicode_to_utf8(str, pwsz);
    free(pwsz);
    return dwResult;
    }
    
    inline unsigned int shell::GetTempFileName(const char * lpPathName, const char * lpPrefixString, unsigned int uUnique, string & str)
    {
    wstring wstrPathName = gen::international::utf8_to_unicode(lpPathName);
    wstring wstrPrefixString = gen::international::utf8_to_unicode(lpPrefixString);
    wstring wstr;
    wstr.get_buffer(MAX_PATH * 4);
    unsigned int uResult = (*theLinuxShell.m_pfnGetTempFileName)(
    wstrPathName,
    wstrPrefixString,
    uUnique,
    wstr);
    gen::international::unicode_to_utf8(str, wstr);
    return uiResult;
    }
    
    inline int_bool shell::MoveFile(const char * lpExistingFileName, const char * lpNewFileName)
    {
    return MoveFile(gen::international::utf8_to_unicode(lpExistingFileName), gen::international::utf8_to_unicode(lpNewFileName));
    }
    
    */
   
   
} // namespace ios

