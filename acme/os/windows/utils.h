#pragma once

#include <Winsvc.h>
#include <Tlhelp32.h>
#include <Psapi.h>
#include <WinIoCtl.h>



CLASS_DECL_ACME int_bool IsWow64();


int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege);


#define IOCTL_LISTDRV_BUFFERED_IO		\
        CTL_CODE(FILE_DEVICE_UNKNOWN,	\
        0x802,							\
        METHOD_BUFFERED,	            \
        FILE_READ_DATA | FILE_WRITE_DATA)

#define VISTA_FILETYPE  25
#define XP_FILETYPE 28

typedef struct _HANDLE_INFO
{	
	
   USHORT tcDeviceName[260];
	USHORT tcFileName[260];
   ULONG uType;

} HANDLE_INFO;

typedef struct _ADDRESS_INFO
{
   PVOID pAddress;
} ADDRESS_INFO;

typedef ::i32 NTSTATUS;



typedef struct _SYSTEM_HANDLE
{
   
   u32       dwProcessId;
   byte		      bObjectType;
   byte		      bFlags;
   ::u16		      wValue;
   PVOID          pAddress;
   u32       GrantedAccess;

}SYSTEM_HANDLE;




// 
// typedef enum OF_FILE_INFO_BY_HANDLE_CLASS
// {
// 	OF_FileNameInfo  = 2,
// 	OF_FileStreamInfo = 7
// };
// 
// struct OF_FILE_NAME_INFO
// {
// 	u32  FileNameLength;
// 	WCHAR FileName[MAX_PATH];
// };
// 
// struct OF_FILE_STREAM_INFO
// {  
// 	u32 NextEntryOffset;
// 	u32 StreamNameLength;
// 	LARGE_INTEGER StreamSize;
// 	LARGE_INTEGER StreamAllocationSize; 
// 	WCHAR StreamName[MAX_PATH];
// };
// 
// 
// typedef bool (WINAPI *PGetFileInformationByHandleEx)(
// 	HANDLE hFile,
// 	OF_FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
// 	LPVOID pFileInformation,

// 	u32 dwBufferSize);




