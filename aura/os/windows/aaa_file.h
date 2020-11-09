#pragma once


typedef u32 (WINAPI* GetFinalPathNameByHandleDef)(
	HANDLE hFile,
	LPWSTR lpszFilePath,
	u32 cchFilePath,
	u32 dwFlags	);



#ifdef __cplusplus


bool GetDrive(const char * lpDeviceFileName, string & fsFileName, bool bDriveLetterOnly );


#endif


int_bool StopAndUninstallDrv( HANDLE hDrvHandle );

HANDLE ExtractAndInstallDrv();

int ftruncate(int file, filesize len);




CLASS_DECL_AURA int_bool ensure_file_size_handle(HANDLE h, u64 iSize);
CLASS_DECL_AURA int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
