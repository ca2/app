#ifndef OPERATIONAL_SYSTEM_CROSS_WIN_WINDOWS_INTERNALS_H
#define OPERATIONAL_SYSTEM_CROSS_WIN_WINDOWS_INTERNALS_H


/*
 * Internal NT APIs and data structures
 *
 * Copyright (C) the Wine project
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */


/**********************************************************************
 * Fundamental types and data structures
 */

#ifndef WINE_NTSTATUS_DECLARED
#define WINE_NTSTATUS_DECLARED
typedef LONG NTSTATUS;
#endif

typedef CONST char *PCSZ;

typedef short CSHORT;
typedef CSHORT *PCSHORT;

#ifndef __STRING_DEFINED__
#define __STRING_DEFINED__

typedef struct _STRING
{
   WINUSHORT Length;
   WINUSHORT MaximumLength;
   PCHAR Buffer;
} STRING, *PSTRING;
#endif

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;
typedef const STRING *PCANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef const STRING *PCOEM_STRING;

#ifndef __UNICODE_STRING_DEFINED__
#define __UNICODE_STRING_DEFINED__

typedef struct _UNICODE_STRING
{
   WINUSHORT Length; /* bytes */
   WINUSHORT MaximumLength; /* bytes */
   PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
#endif

typedef const UNICODE_STRING *PCUNICODE_STRING;

#ifndef _FILETIME_
#define _FILETIME_

/* 64 bit number of 100 nanoseconds intervals since January 1, 1601 */
typedef struct _FILETIME
{
#ifdef WORDS_BIGENDIAN
   DWORD dwHighDateTime;
   DWORD dwLowDateTime;
#else
   DWORD dwLowDateTime;
   DWORD dwHighDateTime;
#endif
} FILETIME, *PFILETIME, *LPFILETIME;
#endif /* _FILETIME_ */

/*
 * RTL_SYSTEM_TIME and RTL_TIME_ZONE_INFORMATION are the same as
 * the SYSTEMTIME and TIME_ZONE_INFORMATION structures defined
 * in winbase.h, however we need to define them separately so
 * winternl.h doesn't depend on winbase.h.  They are used by
 * RtlQueryTimeZoneInformation and RtlSetTimeZoneInformation.
 * The names are guessed; if anybody knows the real names, let me know.
 */
typedef struct _RTL_SYSTEM_TIME
{
   WORD wYear;
   WORD wMonth;
   WORD wDayOfWeek;
   WORD wDay;
   WORD wHour;
   WORD wMinute;
   WORD wSecond;
   WORD wMilliseconds;
} RTL_SYSTEM_TIME, *PRTL_SYSTEM_TIME;

typedef struct _RTL_TIME_ZONE_INFORMATION
{
   LONG Bias;
   WCHAR StandardName[32];
   RTL_SYSTEM_TIME StandardDate;
   LONG StandardBias;
   WCHAR DaylightName[32];
   RTL_SYSTEM_TIME DaylightDate;
   LONG DaylightBias;
} RTL_TIME_ZONE_INFORMATION, *PRTL_TIME_ZONE_INFORMATION;

typedef struct _CLIENT_ID
{
   HANDLE UniqueProcess;
   HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _CURDIR
{
   UNICODE_STRING DosPath;
   PVOID Handle;
} CURDIR, *PCURDIR;

typedef struct RTL_DRIVE_LETTER_CURDIR
{
   WINUSHORT Flags;
   WINUSHORT Length;
   WINULONG TimeStamp;
   UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct tagRTL_BITMAP
{
   WINULONG SizeOfBitMap; /* Number of bits in the bitmap */
   PWINULONG Buffer; /* Bitmap data, assumed sized to a DWORD boundary */
} RTL_BITMAP, *PRTL_BITMAP;

typedef const RTL_BITMAP *PCRTL_BITMAP;

typedef struct tagRTL_BITMAP_RUN
{
   WINULONG StartingIndex; /* Bit position at which run starts */
   WINULONG NumberOfBits; /* Size of the run in bits */
} RTL_BITMAP_RUN, *PRTL_BITMAP_RUN;

typedef const RTL_BITMAP_RUN *PCRTL_BITMAP_RUN;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
   WINULONG AllocationSize;
   WINULONG Size;
   WINULONG Flags;
   WINULONG DebugFlags;
   HANDLE ConsoleHandle;
   WINULONG ConsoleFlags;
   HANDLE hStdInput;
   HANDLE hStdOutput;
   HANDLE hStdError;
   CURDIR CurrentDirectory;
   UNICODE_STRING DllPath;
   UNICODE_STRING ImagePathName;
   UNICODE_STRING CommandLine;
   PWSTR Environment;
   WINULONG dwX;
   WINULONG dwY;
   WINULONG dwXSize;
   WINULONG dwYSize;
   WINULONG dwXCountChars;
   WINULONG dwYCountChars;
   WINULONG dwFillAttribute;
   WINULONG dwFlags;
   WINULONG wShowWindow;
   UNICODE_STRING WindowTitle;
   UNICODE_STRING Desktop;
   UNICODE_STRING ShellInfo;
   UNICODE_STRING RuntimeInfo;
   RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

/* value for Flags field (FIXME: not the correct name) */
#define PROCESS_PARAMS_FLAG_NORMALIZED 1

typedef struct _PEB_LDR_DATA
{
   WINULONG Length;
   int_bool Initialized;
   PVOID SsHandle;
   LIST_ENTRY InLoadOrderModuleList;
   LIST_ENTRY InMemoryOrderModuleList;
   LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _GDI_TEB_BATCH
{
   WINULONG Offset;
   HANDLE HDC;
   WINULONG Buffer[0x136];
} GDI_TEB_BATCH;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
   struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *Previous;
   struct _ACTIVATION_CONTEXT *ActivationContext;
   WINULONG Flags;
} RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

typedef struct _ACTIVATION_CONTEXT_STACK
{
   WINULONG Flags;
   WINULONG NextCookieSequenceNumber;
   RTL_ACTIVATION_CONTEXT_STACK_FRAME *ActiveFrame;
   LIST_ENTRY FrameListCache;
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

/***********************************************************************
 * PEB data structure
 */
typedef struct _PEB   /* win32/win64 */
{
   int_bool InheritedAddressSpace; /* 000/000 */
   int_bool ReadImageFileExecOptions; /* 001/001 */
   int_bool BeingDebugged; /* 002/002 */
   int_bool SpareBool; /* 003/003 */
   HANDLE Mutant; /* 004/008 */
   HMODULE ImageBaseAddress; /* 008/010 */
   PPEB_LDR_DATA LdrData; /* 00c/018 */
   RTL_USER_PROCESS_PARAMETERS *ProcessParameters; /* 010/020 */
   PVOID SubSystemData; /* 014/028 */
   HANDLE ProcessHeap; /* 018/030 */
   PRTL_CRITICAL_SECTION FastPebLock; /* 01c/038 */
   PVOID /*PPEBLOCKROUTINE*/ FastPebLockRoutine; /* 020/040 */
   PVOID /*PPEBLOCKROUTINE*/ FastPebUnlockRoutine; /* 024/048 */
   WINULONG EnvironmentUpdateCount; /* 028/050 */
   PVOID KernelCallbackTable; /* 02c/058 */
   WINULONG Reserved[2]; /* 030/060 */
   PVOID /*PPEB_FREE_BLOCK*/ FreeList; /* 038/068 */
   WINULONG TlsExpansionCounter; /* 03c/070 */
   PRTL_BITMAP TlsBitmap; /* 040/078 */
   WINULONG TlsBitmapBits[2]; /* 044/080 */
   PVOID ReadOnlySharedMemoryBase; /* 04c/088 */
   PVOID ReadOnlySharedMemoryHeap; /* 050/090 */
   PVOID *ReadOnlyStaticServerData; /* 054/098 */
   PVOID AnsiCodePageData; /* 058/0a0 */
   PVOID OemCodePageData; /* 05c/0a8 */
   PVOID UnicodeCaseTableData; /* 060/0b0 */
   WINULONG NumberOfProcessors; /* 064/0b8 */
   WINULONG NtGlobalFlag; /* 068/0bc */
   LARGE_INTEGER CriticalSectionTimeout; /* 070/0c0 */
   SIZE_T HeapSegmentReserve; /* 078/0c8 */
   SIZE_T HeapSegmentCommit; /* 07c/0d0 */
   SIZE_T HeapDeCommitTotalFreeThreshold; /* 080/0d8 */
   SIZE_T HeapDeCommitFreeBlockThreshold; /* 084/0e0 */
   WINULONG NumberOfHeaps; /* 088/0e8 */
   WINULONG MaximumNumberOfHeaps; /* 08c/0ec */
   PVOID *ProcessHeaps; /* 090/0f0 */
   PVOID GdiSharedHandleTable; /* 094/0f8 */
   PVOID ProcessStarterHelper; /* 098/100 */
   PVOID GdiDCAttributeList; /* 09c/108 */
   PVOID LoaderLock; /* 0a0/110 */
   WINULONG OSMajorVersion; /* 0a4/118 */
   WINULONG OSMinorVersion; /* 0a8/11c */
   WINULONG OSBuildNumber; /* 0ac/120 */
   WINULONG OSPlatformId; /* 0b0/124 */
   WINULONG ImageSubSystem; /* 0b4/128 */
   WINULONG ImageSubSystemMajorVersion; /* 0b8/12c */
   WINULONG ImageSubSystemMinorVersion; /* 0bc/130 */
   WINULONG ImageProcessAffinityMask; /* 0c0/134 */
   HANDLE GdiHandleBuffer[28]; /* 0c4/138 */
   WINULONG unknown[6]; /* 134/218 */
   PVOID PostProcessInitRoutine; /* 14c/230 */
   PRTL_BITMAP TlsExpansionBitmap; /* 150/238 */
   WINULONG TlsExpansionBitmapBits[32]; /* 154/240 */
   WINULONG SessionId; /* 1d4/2c0 */
   ULARGE_INTEGER AppCompatFlags; /* 1d8/2c8 */
   ULARGE_INTEGER AppCompatFlagsUser; /* 1e0/2d0 */
   PVOID ShimData; /* 1e8/2d8 */
   PVOID AppCompatInfo; /* 1ec/2e0 */
   UNICODE_STRING CSDVersion; /* 1f0/2e8 */
   PVOID ActivationContextData; /* 1f8/2f8 */
   PVOID ProcessAssemblyStorageMap; /* 1fc/300 */
   PVOID SystemDefaultActivationData; /* 200/308 */
   PVOID SystemAssemblyStorageMap; /* 204/310 */
   SIZE_T MinimumStackCommit; /* 208/318 */
   PVOID *FlsCallback; /* 20c/320 */
   LIST_ENTRY FlsListHead; /* 210/328 */
   PRTL_BITMAP FlsBitmap; /* 218/338 */
   WINULONG FlsBitmapBits[4]; /* 21c/340 */
} PEB, *PPEB;

/***********************************************************************
 * TEB data structure
 */
typedef struct _TEB   /* win32/win64 */
{
   NT_TIB Tib; /* 000/0000 */
   PVOID EnvironmentPointer; /* 01c/0038 */
   CLIENT_ID ClientId; /* 020/0040 */
   PVOID ActiveRpcHandle; /* 028/0050 */
   PVOID ThreadLocalStoragePointer; /* 02c/0058 */
   PPEB Peb; /* 030/0060 */
   WINULONG LastErrorValue; /* 034/0068 */
   WINULONG CountOfOwnedCriticalSections; /* 038/006c */
   PVOID CsrClientThread; /* 03c/0070 */
   PVOID Win32ThreadInfo; /* 040/0078 */
   WINULONG Win32ClientInfo[31]; /* 044/0080 used for user32 private data in Wine */
   PVOID WOW32Reserved; /* 0c0/0100 */
   WINULONG CurrentLocale; /* 0c4/0108 */
   WINULONG FpSoftwareStatusRegister; /* 0c8/010c */
   PVOID SystemReserved1[54]; /* 0cc/0110 used for kernel32 private data in Wine */
   LONG ExceptionCode; /* 1a4/02c0 */
   ACTIVATION_CONTEXT_STACK ActivationContextStack; /* 1a8/02c8 */
   BYTE SpareBytes1[24]; /* 1bc/02e8 used for ntdll private data in Wine */
   PVOID SystemReserved2[10]; /* 1d4/0300 used for ntdll private data in Wine */
   GDI_TEB_BATCH GdiTebBatch; /* 1fc/0350 used for vm86 private data in Wine */
   HANDLE gdiRgn; /* 6dc/0838 */
   HANDLE gdiPen; /* 6e0/0840 */
   HANDLE gdiBrush; /* 6e4/0848 */
   CLIENT_ID RealClientId; /* 6e8/0850 */
   HANDLE GdiCachedProcessHandle; /* 6f0/0860 */
   WINULONG GdiClientPID; /* 6f4/0868 */
   WINULONG GdiClientTID; /* 6f8/086c */
   PVOID GdiThreadLocaleInfo; /* 6fc/0870 */
   WINULONG UserReserved[5]; /* 700/0878 */
   PVOID glDispachTable[280]; /* 714/0890 */
   PVOID glReserved1[26]; /* b74/1150 */
   PVOID glReserved2; /* bdc/1220 */
   PVOID glSectionInfo; /* be0/1228 */
   PVOID glSection; /* be4/1230 */
   PVOID glTable; /* be8/1238 */
   PVOID glCurrentRC; /* bec/1240 */
   PVOID glContext; /* bf0/1248 */
   WINULONG LastStatusValue; /* bf4/1250 */
   UNICODE_STRING StaticUnicodeString; /* bf8/1258 used by advapi32 */
   WCHAR StaticUnicodeBuffer[261]; /* c00/1268 used by advapi32 */
   PVOID DeallocationStack; /* e0c/1478 */
   PVOID TlsSlots[64]; /* e10/1480 */
   LIST_ENTRY TlsLinks; /* f10/1680 */
   PVOID Vdm; /* f18/1690 */
   PVOID ReservedForNtRpc; /* f1c/1698 */
   PVOID DbgSsReserved[2]; /* f20/16a0 */
   WINULONG HardErrorDisabled; /* f28/16b0 */
   PVOID Instrumentation[16]; /* f2c/16b8 */
   PVOID WinSockData; /* f6c/1738 */
   WINULONG GdiBatchCount; /* f70/1740 */
   WINULONG Spare2; /* f74/1744 */
   PVOID Spare3; /* f78/1748 */
   PVOID Spare4; /* f7c/1750 */
   PVOID ReservedForOle; /* f80/1758 */
   WINULONG WaitingOnLoaderLock; /* f84/1760 */
   PVOID Reserved5[3]; /* f88/1768 */
   PVOID *TlsExpansionSlots; /* f94/1780 */
   WINULONG ImpersonationLocale; /* f98/1788 */
   WINULONG IsImpersonating; /* f9c/178c */
   PVOID NlsCache; /* fa0/1790 */
   PVOID ShimData; /* fa4/1798 */
   WINULONG HeapVirtualAffinity; /* fa8/17a0 */
   PVOID CurrentTransactionHandle; /* fac/17a8 */
   PVOID ActiveFrame; /* fb0/17b0 */
#ifdef _WIN64
   PVOID unknown[2]; /*     17b8 */
#endif
   PVOID *FlsSlots; /* fb4/17c8 */
} TEB, *PTEB;

/***********************************************************************
 * Enums
 */

typedef enum _FILE_INFORMATION_CLASS
{
   FileDirectoryInformation = 1,
   FileFullDirectoryInformation,
   FileBothDirectoryInformation,
   FileBasicInformation,
   FileStandardInformation,
   FileInternalInformation,
   FileEaInformation,
   FileAccessInformation,
   FileNameInformation,
   FileRenameInformation,
   FileLinkInformation,
   FileNamesInformation,
   FileDispositionInformation,
   FilePositionInformation,
   FileFullEaInformation,
   FileModeInformation,
   FileAlignmentInformation,
   FileAllInformation,
   FileAllocationInformation,
   FileEndOfFileInformation,
   FileAlternateNameInformation,
   FileStreamInformation,
   FilePipeInformation,
   FilePipeLocalInformation,
   FilePipeRemoteInformation,
   FileMailslotQueryInformation,
   FileMailslotSetInformation,
   FileCompressionInformation,
   FileObjectIdInformation,
   FileCompletionInformation,
   FileMoveClusterInformation,
   FileQuotaInformation,
   FileReparsePointInformation,
   FileNetworkOpenInformation,
   FileAttributeTagInformation,
   FileTrackingInformation,
   FileIdBothDirectoryInformation,
   FileIdFullDirectoryInformation,
   FileValidDataLengthInformation,
   FileShortNameInformation = 40,
   /* 41, 42, 43 undocumented */
   FileSfioReserveInformation = 44,
   FileSfioVolumeInformation = 45,
   FileHardLinkInformation = 46,
   /* 47 undocumented */
   FileNormalizedNameInformation = 48,
   /* 49 undocumented */
   FileIdGlobalTxDirectoryInformation = 50,
   /* 51, 52, 53 undocumented */
   FileStandardLinkInformation = 54,
   FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef struct _FILE_DIRECTORY_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG FileIndex;
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   LARGE_INTEGER EndOfFile;
   LARGE_INTEGER AllocationSize;
   WINULONG FileAttributes;
   WINULONG FileNameLength;
   WCHAR FileName[ANYSIZE_ARRAY];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

typedef struct _FILE_FULL_DIRECTORY_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG FileIndex;
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   LARGE_INTEGER EndOfFile;
   LARGE_INTEGER AllocationSize;
   WINULONG FileAttributes;
   WINULONG FileNameLength;
   WINULONG EaSize;
   WCHAR FileName[ANYSIZE_ARRAY];
} FILE_FULL_DIRECTORY_INFORMATION, *PFILE_FULL_DIRECTORY_INFORMATION,
FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_FULL_DIRECTORY_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG FileIndex;
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   LARGE_INTEGER EndOfFile;
   LARGE_INTEGER AllocationSize;
   WINULONG FileAttributes;
   WINULONG FileNameLength;
   WINULONG EaSize;
   LARGE_INTEGER FileId;
   WCHAR FileName[ANYSIZE_ARRAY];
} FILE_ID_FULL_DIRECTORY_INFORMATION, *PFILE_ID_FULL_DIRECTORY_INFORMATION;

typedef struct _FILE_BOTH_DIRECTORY_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG FileIndex;
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   LARGE_INTEGER EndOfFile;
   LARGE_INTEGER AllocationSize;
   WINULONG FileAttributes;
   WINULONG FileNameLength;
   WINULONG EaSize;
   CHAR ShortNameLength;
   WCHAR ShortName[12];
   WCHAR FileName[ANYSIZE_ARRAY];
} FILE_BOTH_DIRECTORY_INFORMATION, *PFILE_BOTH_DIRECTORY_INFORMATION,
FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;

typedef struct _FILE_ID_BOTH_DIRECTORY_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG FileIndex;
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   LARGE_INTEGER EndOfFile;
   LARGE_INTEGER AllocationSize;
   WINULONG FileAttributes;
   WINULONG FileNameLength;
   WINULONG EaSize;
   CHAR ShortNameLength;
   WCHAR ShortName[12];
   LARGE_INTEGER FileId;
   WCHAR FileName[ANYSIZE_ARRAY];
} FILE_ID_BOTH_DIRECTORY_INFORMATION, *PFILE_ID_BOTH_DIRECTORY_INFORMATION;

typedef struct _FILE_BASIC_INFORMATION
{
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   WINULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

typedef struct _FILE_STANDARD_INFORMATION
{
   LARGE_INTEGER AllocationSize;
   LARGE_INTEGER EndOfFile;
   WINULONG NumberOfLinks;
   int_bool DeletePending;
   int_bool Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

typedef struct _FILE_INTERNAL_INFORMATION
{
   LARGE_INTEGER IndexNumber;
} FILE_INTERNAL_INFORMATION, *PFILE_INTERNAL_INFORMATION;

typedef struct _FILE_EA_INFORMATION
{
   WINULONG EaSize;
} FILE_EA_INFORMATION, *PFILE_EA_INFORMATION;

typedef struct _FILE_ACCESS_INFORMATION
{
   ACCESS_MASK AccessFlags;
} FILE_ACCESS_INFORMATION, *PFILE_ACCESS_INFORMATION;

typedef struct _FILE_NAME_INFORMATION
{
   WINULONG FileNameLength;
   WCHAR FileName[1];
} FILE_NAME_INFORMATION, *PFILE_NAME_INFORMATION;

typedef struct _FILE_RENAME_INFORMATION
{
   int_bool Replace;
   HANDLE RootDir;
   WINULONG FileNameLength;
   WCHAR FileName[1];
} FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

typedef struct _FILE_NAMES_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG FileIndex;
   WINULONG FileNameLength;
   WCHAR FileName[1];
} FILE_NAMES_INFORMATION, *PFILE_NAMES_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION
{
   int_bool DoDeleteFile;
} FILE_DISPOSITION_INFORMATION, *PFILE_DISPOSITION_INFORMATION;

typedef struct _FILE_POSITION_INFORMATION
{
   LARGE_INTEGER CurrentByteOffset;
} FILE_POSITION_INFORMATION, *PFILE_POSITION_INFORMATION;

typedef struct _FILE_ALIGNMENT_INFORMATION
{
   WINULONG AlignmentRequirement;
} FILE_ALIGNMENT_INFORMATION, *PFILE_ALIGNMENT_INFORMATION;

typedef struct _FILE_ALLOCATION_INFORMATION
{
   LARGE_INTEGER AllocationSize;
} FILE_ALLOCATION_INFORMATION, *PFILE_ALLOCATION_INFORMATION;

typedef struct _FILE_END_OF_FILE_INFORMATION
{
   LARGE_INTEGER EndOfFile;
} FILE_END_OF_FILE_INFORMATION, *PFILE_END_OF_FILE_INFORMATION;

typedef struct _FILE_NETWORK_OPEN_INFORMATION
{
   LARGE_INTEGER CreationTime;
   LARGE_INTEGER LastAccessTime;
   LARGE_INTEGER LastWriteTime;
   LARGE_INTEGER ChangeTime;
   LARGE_INTEGER AllocationSize;
   LARGE_INTEGER EndOfFile;
   WINULONG FileAttributes;
} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION;

typedef struct _FILE_FULL_EA_INFORMATION
{
   WINULONG NextEntryOffset;
   WINUCHAR Flags;
   WINUCHAR EaNameLength;
   WINUSHORT EaValueLength;
   CHAR EaName[1];
} FILE_FULL_EA_INFORMATION, *PFILE_FULL_EA_INFORMATION;

typedef struct _FILE_MODE_INFORMATION
{
   WINULONG Mode;
} FILE_MODE_INFORMATION, *PFILE_MODE_INFORMATION;

typedef struct _FILE_STREAM_INFORMATION
{
   WINULONG NextEntryOffset;
   WINULONG StreamNameLength;
   LARGE_INTEGER StreamSize;
   LARGE_INTEGER StreamAllocationSize;
   WCHAR StreamName[1];
} FILE_STREAM_INFORMATION, *PFILE_STREAM_INFORMATION;

typedef struct _FILE_ATTRIBUTE_TAG_INFORMATION
{
   WINULONG FileAttributes;
   WINULONG ReparseTag;
} FILE_ATTRIBUTE_TAG_INFORMATION, *PFILE_ATTRIBUTE_TAG_INFORMATION;

typedef struct _FILE_MAILSLOT_QUERY_INFORMATION
{
   WINULONG MaximumMessageSize;
   WINULONG MailslotQuota;
   WINULONG NextMessageSize;
   WINULONG MessagesAvailable;
   LARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_QUERY_INFORMATION, *PFILE_MAILSLOT_QUERY_INFORMATION;

typedef struct _FILE_MAILSLOT_SET_INFORMATION
{
   LARGE_INTEGER ReadTimeout;
} FILE_MAILSLOT_SET_INFORMATION, *PFILE_MAILSLOT_SET_INFORMATION;

typedef struct _FILE_PIPE_LOCAL_INFORMATION
{
   WINULONG NamedPipeType;
   WINULONG NamedPipeConfiguration;
   WINULONG MaximumInstances;
   WINULONG CurrentInstances;
   WINULONG InboundQuota;
   WINULONG ReadDataAvailable;
   WINULONG OutboundQuota;
   WINULONG WriteQuotaAvailable;
   WINULONG NamedPipeState;
   WINULONG NamedPipeEnd;
} FILE_PIPE_LOCAL_INFORMATION, *PFILE_PIPE_LOCAL_INFORMATION;

typedef struct _FILE_ALL_INFORMATION
{
   FILE_BASIC_INFORMATION BasicInformation;
   FILE_STANDARD_INFORMATION StandardInformation;
   FILE_INTERNAL_INFORMATION InternalInformation;
   FILE_EA_INFORMATION EaInformation;
   FILE_ACCESS_INFORMATION AccessInformation;
   FILE_POSITION_INFORMATION PositionInformation;
   FILE_MODE_INFORMATION ModeInformation;
   FILE_ALIGNMENT_INFORMATION AlignmentInformation;
   FILE_NAME_INFORMATION NameInformation;
} FILE_ALL_INFORMATION, *PFILE_ALL_INFORMATION;

typedef enum _FSINFOCLASS
{
   FileFsVolumeInformation = 1,
   FileFsLabelInformation,
   FileFsSizeInformation,
   FileFsDeviceInformation,
   FileFsAttributeInformation,
   FileFsControlInformation,
   FileFsFullSizeInformation,
   FileFsObjectIdInformation,
   FileFsMaximumInformation
} FS_INFORMATION_CLASS, *PFS_INFORMATION_CLASS;

typedef enum _KEY_INFORMATION_CLASS
{
   KeyBasicInformation,
   KeyNodeInformation,
   KeyFullInformation,
   KeyNameInformation
} KEY_INFORMATION_CLASS;

typedef enum _KEY_VALUE_INFORMATION_CLASS
{
   KeyValueBasicInformation,
   KeyValueFullInformation,
   KeyValuePartialInformation,
   KeyValueFullInformationAlign64,
   KeyValuePartialInformationAlign64
} KEY_VALUE_INFORMATION_CLASS;

typedef enum _OBJECT_INFORMATION_CLASS
{
   ObjectBasicInformation,
   ObjectNameInformation,
   ObjectTypeInformation,
   ObjectAllInformation,
   ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;

#ifndef _UWP
typedef enum _PROCESSINFOCLASS
{
   ProcessBasicInformation = 0,
   ProcessQuotaLimits = 1,
   ProcessIoCounters = 2,
   ProcessVmCounters = 3,
   ProcessTimes = 4,
   ProcessBasePriority = 5,
   ProcessRaisePriority = 6,
   ProcessDebugPort = 7,
   ProcessExceptionPort = 8,
   ProcessAccessToken = 9,
   ProcessLdtInformation = 10,
   ProcessLdtSize = 11,
   ProcessDefaultHardErrorMode = 12,
   ProcessIoPortHandlers = 13,
   ProcessPooledUsageAndLimits = 14,
   ProcessWorkingSetWatch = 15,
   ProcessUserModeIOPL = 16,
   ProcessEnableAlignmentFaultFixup = 17,
   ProcessPriorityClass = 18,
   ProcessWx86Information = 19,
   ProcessHandleCount = 20,
   ProcessAffinityMask = 21,
   ProcessPriorityBoost = 22,
   ProcessDeviceMap = 23,
   ProcessSessionInformation = 24,
   ProcessForegroundInformation = 25,
   ProcessWow64Information = 26,
   ProcessImageFileName = 27,
   ProcessLUIDDeviceMapsEnabled = 28,
   ProcessBreakOnTermination = 29,
   ProcessDebugObjectHandle = 30,
   ProcessDebugFlags = 31,
   ProcessHandleTracing = 32,
   ProcessExecuteFlags = 34,
   MaxProcessInfoClass
} PROCESSINFOCLASS, PROCESS_INFORMATION_CLASS;

#else

typedef PROCESS_INFORMATION_CLASS PROCESSINFOCLASS;

#endif

#define MEM_EXECUTE_OPTION_DISABLE   0x01
#define MEM_EXECUTE_OPTION_ENABLE    0x02
#define MEM_EXECUTE_OPTION_PERMANENT 0x08

typedef enum _SECTION_INHERIT
{
   ViewShare = 1,
   ViewUnmap = 2
} SECTION_INHERIT;

typedef enum _SYSTEM_INFORMATION_CLASS
{
   SystemBasicInformation = 0,
   SystemCpuInformation = 1,
   SystemPerformanceInformation = 2,
   SystemTimeOfDayInformation = 3, /* was SystemTimeInformation */
   Unknown4,
   SystemProcessInformation = 5,
   Unknown6,
   Unknown7,
   SystemProcessorPerformanceInformation = 8,
   Unknown9,
   Unknown10,
   SystemModuleInformation = 11,
   Unknown12,
   Unknown13,
   Unknown14,
   Unknown15,
   SystemHandleInformation = 16,
   Unknown17,
   SystemPageFileInformation = 18,
   Unknown19,
   Unknown20,
   SystemCacheInformation = 21,
   Unknown22,
   SystemInterruptInformation = 23,
   SystemDpcBehaviourInformation = 24,
   SystemFullMemoryInformation = 25,
   SystemNotImplemented6 = 25,
   SystemLoadImage = 26,
   SystemUnloadImage = 27,
   SystemTimeAdjustmentInformation = 28,
   SystemTimeAdjustment = 28,
   SystemSummaryMemoryInformation = 29,
   SystemNotImplemented7 = 29,
   SystemNextEventIdInformation = 30,
   SystemNotImplemented8 = 30,
   SystemEventIdsInformation = 31,
   SystemCrashDumpInformation = 32,
   SystemExceptionInformation = 33,
   SystemCrashDumpStateInformation = 34,
   SystemKernelDebuggerInformation = 35,
   SystemContextSwitchInformation = 36,
   SystemRegistryQuotaInformation = 37,
   SystemCurrentTimeZoneInformation = 44,
   SystemTimeZoneInformation = 44,
   SystemLookasideInformation = 45,
   SystemSetTimeSlipEvent = 46,
   SystemCreateSession = 47,
   SystemDeleteSession = 48,
   SystemInvalidInfoClass4 = 49,
   SystemRangeStartInformation = 50,
   SystemVerifierInformation = 51,
   SystemAddVerifier = 52,
   SystemSessionProcessesInformation = 53,
   Unknown54,
   Unknown55,
   Unknown56,
   Unknown57,
   Unknown58,
   Unknown59,
   Unknown60,
   Unknown61,
   Unknown62,
   Unknown63,
   Unknown64,
   Unknown65,
   Unknown66,
   Unknown67,
   Unknown68,
   Unknown69,
   Unknown70,
   Unknown71,
   Unknown72,
   SystemLogicalProcessorInformation = 73,
   SystemInformationClassMax
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef enum _TIMER_TYPE
{
   NotificationTimer,
   SynchronizationTimer
} TIMER_TYPE;

typedef enum _THREADINFOCLASS
{
   ThreadBasicInformation,
   ThreadTimes,
   ThreadPriority,
   ThreadBasePriority,
   ThreadAffinityMask,
   ThreadImpersonationToken,
   ThreadDescriptorTableEntry,
   ThreadEnableAlignmentFaultFixup,
   ThreadEventPair_Reusable,
   ThreadQuerySetWin32StartAddress,
   ThreadZeroTlsCell,
   ThreadPerformanceCount,
   ThreadAmILastThread,
   ThreadIdealProcessor,
   ThreadPriorityBoost,
   ThreadSetTlsArrayAddress,
   ThreadIsIoPending,
   ThreadHideFromDebugger,
   MaxThreadInfoClass
} THREADINFOCLASS;

typedef struct _THREAD_BASIC_INFORMATION
{
   NTSTATUS ExitStatus;
   PVOID TebBaseAddress;
   CLIENT_ID ClientId;
   ULONG_PTR AffinityMask;
   LONG Priority;
   LONG BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _THREAD_DESCRIPTOR_INFORMATION
{
   DWORD Selector;
   LDT_ENTRY Entry;
} THREAD_DESCRIPTOR_INFORMATION, *PTHREAD_DESCRIPTOR_INFORMATION;

typedef struct _KERNEL_USER_TIMES
{
   LARGE_INTEGER CreateTime;
   LARGE_INTEGER ExitTime;
   LARGE_INTEGER KernelTime;
   LARGE_INTEGER UserTime;
} KERNEL_USER_TIMES, *PKERNEL_USER_TIMES;

typedef enum _WINSTATIONINFOCLASS
{
   WinStationInformation = 8
} WINSTATIONINFOCLASS;

typedef enum _MEMORY_INFORMATION_CLASS
{
   MemoryBasicInformation,
   MemoryWorkingSetList,
   MemorySectionName,
   MemoryBasicVlmInformation
} MEMORY_INFORMATION_CLASS;

typedef enum _MUTANT_INFORMATION_CLASS
{
   MutantBasicInformation
} MUTANT_INFORMATION_CLASS, *PMUTANT_INFORMATION_CLASS;

typedef struct _MUTANT_BASIC_INFORMATION
{
   LONG CurrentCount;
   int_bool OwnedByCaller;
   int_bool AbandonedState;
} MUTANT_BASIC_INFORMATION, *PMUTANT_BASIC_INFORMATION;

typedef enum _TIMER_INFORMATION_CLASS
{
   TimerBasicInformation = 0
} TIMER_INFORMATION_CLASS;

typedef struct _TIMER_BASIC_INFORMATION
{
   LARGE_INTEGER RemainingTime;
   int_bool TimerState;
} TIMER_BASIC_INFORMATION, *PTIMER_BASIC_INFORMATION;

/* return type of RtlDetermineDosPathNameType_U (FIXME: not the correct names) */
typedef enum
{
   INVALID_PATH = 0,
   UNC_PATH, /* "//foo" */
   ABSOLUTE_DRIVE_PATH, /* "ca:/foo" */
   RELATIVE_DRIVE_PATH, /* "ca:foo" */
   ABSOLUTE_PATH, /* "/foo" */
   RELATIVE_PATH, /* "foo" */
   DEVICE_PATH, /* "//./foo" */
   UNC_DOT_PATH /* "//." */
} DOS_PATHNAME_TYPE;


/***********************************************************************
 * Types and data structures
 */

/* This is used by NtQuerySystemInformation */
typedef struct _SYSTEM_THREAD_INFORMATION   /* win32/win64 */
{
   LARGE_INTEGER KernelTime; /* 00/00 */
   LARGE_INTEGER UserTime; /* 08/08 */
   LARGE_INTEGER CreateTime; /* 10/10 */
   DWORD dwTickCount; /* 18/18 */
   LPVOID StartAddress; /* 1c/20 */
   CLIENT_ID ClientId; /* 20/28 */
   DWORD dwCurrentPriority; /* 28/38 */
   DWORD dwBasePriority; /* 2c/3c */
   DWORD dwContextSwitches; /* 30/40 */
   DWORD dwThreadState; /* 34/44 */
   DWORD dwWaitReason; /* 38/48 */
   DWORD dwUnknown; /* 3c/4c */
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _IO_STATUS_BLOCK
{

   union
   {
      NTSTATUS _Status;
      PVOID Pointer;
   } DUMMYUNIONNAME;

   ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef void (WINAPI * PIO_APC_ROUTINE)(PVOID, PIO_STATUS_BLOCK, WINULONG);

typedef struct _KEY_BASIC_INFORMATION
{
   LARGE_INTEGER LastWriteTime;
   WINULONG TitleIndex;
   WINULONG NameLength;
   WCHAR Name[1];
} KEY_BASIC_INFORMATION, *PKEY_BASIC_INFORMATION;

typedef struct _KEY_NODE_INFORMATION
{
   LARGE_INTEGER LastWriteTime;
   WINULONG TitleIndex;
   WINULONG ClassOffset;
   WINULONG ClassLength;
   WINULONG NameLength;
   WCHAR Name[1];
   /* Class[1]; */
} KEY_NODE_INFORMATION, *PKEY_NODE_INFORMATION;

typedef struct _KEY_FULL_INFORMATION
{
   LARGE_INTEGER LastWriteTime;
   WINULONG TitleIndex;
   WINULONG ClassOffset;
   WINULONG ClassLength;
   WINULONG SubKeys;
   WINULONG MaxNameLen;
   WINULONG MaxClassLen;
   WINULONG Values;
   WINULONG MaxValueNameLen;
   WINULONG MaxValueDataLen;
   WCHAR Class[1];
} KEY_FULL_INFORMATION, *PKEY_FULL_INFORMATION;

typedef struct _KEY_NAME_INFORMATION
{
   WINULONG NameLength;
   WCHAR Name[1];
} KEY_NAME_INFORMATION, *PKEY_NAME_INFORMATION;

typedef struct _KEY_VALUE_ENTRY
{
   PUNICODE_STRING ValueName;
   WINULONG DataLength;
   WINULONG DataOffset;
   WINULONG Type;
} KEY_VALUE_ENTRY, *PKEY_VALUE_ENTRY;

typedef struct _KEY_VALUE_BASIC_INFORMATION
{
   WINULONG TitleIndex;
   WINULONG Type;
   WINULONG NameLength;
   WCHAR Name[1];
} KEY_VALUE_BASIC_INFORMATION, *PKEY_VALUE_BASIC_INFORMATION;

typedef struct _KEY_VALUE_FULL_INFORMATION
{
   WINULONG TitleIndex;
   WINULONG Type;
   WINULONG DataOffset;
   WINULONG DataLength;
   WINULONG NameLength;
   WCHAR Name[1];
} KEY_VALUE_FULL_INFORMATION, *PKEY_VALUE_FULL_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION
{
   WINULONG TitleIndex;
   WINULONG Type;
   WINULONG DataLength;
   WINUCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION, *PKEY_VALUE_PARTIAL_INFORMATION;

#ifndef __OBJECT_ATTRIBUTES_DEFINED__
#define __OBJECT_ATTRIBUTES_DEFINED__

typedef struct _OBJECT_ATTRIBUTES
{
   WINULONG Length;
   HANDLE RootDirectory;
   PUNICODE_STRING ObjectName;
   WINULONG Attributes;
   PVOID SecurityDescriptor; /* type SECURITY_DESCRIPTOR */
   PVOID SecurityQualityOfService; /* type SECURITY_QUALITY_OF_SERVICE */
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
#endif

typedef struct _OBJECT_DATA_INFORMATION
{
   int_bool InheritHandle;
   int_bool ProtectFromClose;
} OBJECT_DATA_INFORMATION, *POBJECT_DATA_INFORMATION;

typedef struct _OBJECT_BASIC_INFORMATION
{
   WINULONG Attributes;
   ACCESS_MASK GrantedAccess;
   WINULONG HandleCount;
   WINULONG PointerCount;
   WINULONG PagedPoolUsage;
   WINULONG NonPagedPoolUsage;
   WINULONG Reserved[3];
   WINULONG NameInformationLength;
   WINULONG TypeInformationLength;
   WINULONG SecurityDescriptorLength;
   LARGE_INTEGER CreateTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

typedef struct _OBJECT_NAME_INFORMATION
{
   UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _PROCESS_BASIC_INFORMATION
{
#ifdef __WINESRC__
   DWORD_PTR ExitStatus;
   PPEB PebBaseAddress;
   DWORD_PTR AffinityMask;
   DWORD_PTR BasePriority;
   ULONG_PTR UniqueProcessId;
   ULONG_PTR InheritedFromUniqueProcessId;
#else
   PVOID Reserved1;
   PPEB PebBaseAddress;
   PVOID Reserved2[2];
   ULONG_PTR UniqueProcessId;
   PVOID Reserved3;
#endif
} PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;

#define PROCESS_PRIOCLASS_IDLE          1
#define PROCESS_PRIOCLASS_NORMAL        2
#define PROCESS_PRIOCLASS_HIGH          3
#define PROCESS_PRIOCLASS_REALTIME      4
#define PROCESS_PRIOCLASS_BELOW_NORMAL  5
#define PROCESS_PRIOCLASS_ABOVE_NORMAL  6

typedef struct _PROCESS_PRIORITY_CLASS
{
   int_bool Foreground;
   WINUCHAR PriorityClass;
} PROCESS_PRIORITY_CLASS, *PPROCESS_PRIORITY_CLASS;

typedef struct _RTL_HEAP_DEFINITION
{
   WINULONG Length; /* = sizeof(RTL_HEAP_DEFINITION) */

   WINULONG Unknown[11];
} RTL_HEAP_DEFINITION, *PRTL_HEAP_DEFINITION;

typedef struct _RTL_RWLOCK
{
   RTL_CRITICAL_SECTION rtlCS;

   HANDLE hSharedReleaseSemaphore;
   UINT uSharedWaiters;

   HANDLE hExclusiveReleaseSemaphore;
   UINT uExclusiveWaiters;

   INT iNumberActive;
   HANDLE hOwningThreadId;
   DWORD tickTimeoutBoost;
   PVOID pDebugInfo;
} RTL_RWLOCK, *LPRTL_RWLOCK;

/* System Information Class 0x00 */

typedef struct _SYSTEM_BASIC_INFORMATION
{
#ifdef __WINESRC__
   DWORD unknown;
   WINULONG KeMaximumIncrement;
   WINULONG PageSize;
   WINULONG MmNumberOfPhysicalPages;
   WINULONG MmLowestPhysicalPage;
   WINULONG MmHighestPhysicalPage;
   ULONG_PTR AllocationGranularity;
   PVOID LowestUserAddress;
   PVOID HighestUserAddress;
   ULONG_PTR ActiveProcessorsAffinityMask;
   BYTE NumberOfProcessors;
#else
   BYTE Reserved1[24];
   PVOID Reserved2[4];
   CCHAR NumberOfProcessors;
#endif
} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

/* System Information Class 0x01 */

typedef struct _SYSTEM_CPU_INFORMATION
{
   WORD Architecture;
   WORD Level;
   WORD Revision; /* combination of CPU model and stepping */
   WORD Reserved; /* always zero */
   DWORD FeatureSet; /* see bit flags below */
} SYSTEM_CPU_INFORMATION, *PSYSTEM_CPU_INFORMATION;

/* definitions of bits in the Feature set for the x86 processors */
#define CPU_FEATURE_VME    0x00000005   /* Virtual 86 Mode Extensions */
#define CPU_FEATURE_TSC    0x00000002   /* Time Stamp Counter available */
#define CPU_FEATURE_CMOV   0x00000008   /* Conditional Move instruction*/
#define CPU_FEATURE_PGE    0x00000014   /* Page table Entry Global bit */
#define CPU_FEATURE_PSE    0x00000024   /* Page Size Extension */
#define CPU_FEATURE_MTRR   0x00000040   /* Memory Type Range Registers */
#define CPU_FEATURE_CX8    0x00000080   /* Compare and eXchange 8 byte instr. */
#define CPU_FEATURE_MMX    0x00000100   /* Multi Media eXtensions */
#define CPU_FEATURE_X86    0x00000200   /* seems to be always ON, on the '86 */
#define CPU_FEATURE_PAT    0x00000400   /* Page Attribute Table */
#define CPU_FEATURE_FXSR   0x00000800   /* FXSAVE and FXSTORE instructions */
#define CPU_FEATURE_SEP    0x00001000   /* SYSENTER and SYSEXIT instructions */
#define CPU_FEATURE_SSE    0x00002000   /* SSE extensions (ext. MMX) */
#define CPU_FEATURE_3DNOW  0x00008000   /* 3DNOW instructions available
                                           (FIXME: needs to be confirmed) */
#define CPU_FEATURE_SSE2   0x00010000   /* SSE2 extensions (XMMI64) */
#define CPU_FEATURE_DS     0x00020000   /* Debug Store */
#define CPU_FEATURE_HTT    0x00040000   /* Hyper Threading Technology */

/* System Information Class 0x02 */

/* Documented in "Windows NT/2000 Native API Reference" by Gary Nebbett. */
typedef struct _SYSTEM_PERFORMANCE_INFORMATION
{
   LARGE_INTEGER IdleTime;
   LARGE_INTEGER ReadTransferCount;
   LARGE_INTEGER WriteTransferCount;
   LARGE_INTEGER OtherTransferCount;
   WINULONG ReadOperationCount;
   WINULONG WriteOperationCount;
   WINULONG OtherOperationCount;
   WINULONG AvailablePages;
   WINULONG TotalCommittedPages;
   WINULONG TotalCommitLimit;
   WINULONG PeakCommitment;
   WINULONG PageFaults;
   WINULONG WriteCopyFaults;
   WINULONG TransitionFaults;
   WINULONG Reserved1;
   WINULONG DemandZeroFaults;
   WINULONG PagesRead;
   WINULONG PageReadIos;
   WINULONG Reserved2[2];
   WINULONG PagefilePagesWritten;
   WINULONG PagefilePageWriteIos;
   WINULONG MappedFilePagesWritten;
   WINULONG MappedFilePageWriteIos;
   WINULONG PagedPoolUsage;
   WINULONG NonPagedPoolUsage;
   WINULONG PagedPoolAllocs;
   WINULONG PagedPoolFrees;
   WINULONG NonPagedPoolAllocs;
   WINULONG NonPagedPoolFrees;
   WINULONG TotalFreeSystemPtes;
   WINULONG SystemCodePage;
   WINULONG TotalSystemDriverPages;
   WINULONG TotalSystemCodePages;
   WINULONG SmallNonPagedLookasideListAllocateHits;
   WINULONG SmallPagedLookasideListAllocateHits;
   WINULONG Reserved3;
   WINULONG MmSystemCachePage;
   WINULONG PagedPoolPage;
   WINULONG SystemDriverPage;
   WINULONG FastReadNoWait;
   WINULONG FastReadWait;
   WINULONG FastReadResourceMiss;
   WINULONG FastReadNotPossible;
   WINULONG FastMdlReadNoWait;
   WINULONG FastMdlReadWait;
   WINULONG FastMdlReadResourceMiss;
   WINULONG FastMdlReadNotPossible;
   WINULONG MapDataNoWait;
   WINULONG MapDataWait;
   WINULONG MapDataNoWaitMiss;
   WINULONG MapDataWaitMiss;
   WINULONG PinMappedDataCount;
   WINULONG PinReadNoWait;
   WINULONG PinReadWait;
   WINULONG PinReadNoWaitMiss;
   WINULONG PinReadWaitMiss;
   WINULONG CopyReadNoWait;
   WINULONG CopyReadWait;
   WINULONG CopyReadNoWaitMiss;
   WINULONG CopyReadWaitMiss;
   WINULONG MdlReadNoWait;
   WINULONG MdlReadWait;
   WINULONG MdlReadNoWaitMiss;
   WINULONG MdlReadWaitMiss;
   WINULONG ReadAheadIos;
   WINULONG LazyWriteIos;
   WINULONG LazyWritePages;
   WINULONG DataFlushes;
   WINULONG DataPages;
   WINULONG ContextSwitches;
   WINULONG FirstLevelTbFills;
   WINULONG SecondLevelTbFills;
   WINULONG SystemCalls;
} SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

/* System Information Class 0x03 */

typedef struct _SYSTEM_TIMEOFDAY_INFORMATION
{
#ifdef __WINESRC__
   LARGE_INTEGER liKeBootTime;
   LARGE_INTEGER liKeSystemTime;
   LARGE_INTEGER liExpTimeZoneBias;
   WINULONG uCurrentTimeZoneId;
   DWORD dwUnknown1[5];
#else
   BYTE Reserved1[48];
#endif
} SYSTEM_TIMEOFDAY_INFORMATION, *PSYSTEM_TIMEOFDAY_INFORMATION; /* was SYSTEM_TIME_INFORMATION */

/* System Information Class 0x08 */

typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
{
   LARGE_INTEGER IdleTime;
   LARGE_INTEGER KernelTime;
   LARGE_INTEGER UserTime;
   LARGE_INTEGER Reserved1[2];
   WINULONG Reserved2;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

/* System Information Class 0x0b */

typedef struct _SYSTEM_DRIVER_INFORMATION
{
   PVOID pvAddress;
   DWORD dwUnknown1;
   DWORD dwUnknown2;
   DWORD dwEntryIndex;
   DWORD dwUnknown3;
   char szName[MAX_PATH + 1];
} SYSTEM_DRIVER_INFORMATION, *PSYSTEM_DRIVER_INFORMATION;

/* System Information Class 0x10 */

typedef struct _SYSTEM_HANDLE_ENTRY
{
   WINULONG OwnerPid;
   BYTE ObjectType;
   BYTE HandleFlags;
   WINUSHORT HandleValue;
   PVOID ObjectPointer;
   WINULONG AccessMask;
} SYSTEM_HANDLE_ENTRY, *PSYSTEM_HANDLE_ENTRY;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
   WINULONG Count;
   SYSTEM_HANDLE_ENTRY Handle[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

/* System Information Class 0x15 */

typedef struct _SYSTEM_CACHE_INFORMATION
{
   WINULONG CurrentSize;
   WINULONG PeakSize;
   WINULONG PageFaultCount;
#ifndef _WIN64
   WINULONG MinimumWorkingSet;
   WINULONG MaximumWorkingSet;
   WINULONG unused[4];
#endif
} SYSTEM_CACHE_INFORMATION, *PSYSTEM_CACHE_INFORMATION;

/* System Information Class 0x17 */

typedef struct _SYSTEM_INTERRUPT_INFORMATION
{
   BYTE Reserved1[24];
} SYSTEM_INTERRUPT_INFORMATION, *PSYSTEM_INTERRUPT_INFORMATION;

typedef struct _SYSTEM_CONFIGURATION_INFO
{

   union
   {
      WINULONG OemId;

      struct
      {
         WORD ProcessorArchitecture;
         WORD Reserved;
      } tag1;
   } tag2;
   WINULONG PageSize;
   PVOID MinimumApplicationAddress;
   PVOID MaximumApplicationAddress;
   WINULONG ActiveProcessorMask;
   WINULONG NumberOfProcessors;
   WINULONG ProcessorType;
   WINULONG AllocationGranularity;
   WORD ProcessorLevel;
   WORD ProcessorRevision;
} SYSTEM_CONFIGURATION_INFO, *PSYSTEM_CONFIGURATION_INFO;

typedef struct _SYSTEM_EXCEPTION_INFORMATION
{
   BYTE Reserved1[16];
} SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

typedef struct _SYSTEM_LOOKASIDE_INFORMATION
{
   BYTE Reserved1[32];
} SYSTEM_LOOKASIDE_INFORMATION, *PSYSTEM_LOOKASIDE_INFORMATION;

typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
{
   int_bool DebuggerEnabled;
   int_bool DebuggerNotPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

/* System Information Class 0x05 */

typedef struct _VM_COUNTERS_
{
   SIZE_T PeakVirtualSize;
   SIZE_T VirtualSize;
   WINULONG PageFaultCount;
   SIZE_T PeakWorkingSetSize;
   SIZE_T WorkingSetSize;
   SIZE_T QuotaPeakPagedPoolUsage;
   SIZE_T QuotaPagedPoolUsage;
   SIZE_T QuotaPeakNonPagedPoolUsage;
   SIZE_T QuotaNonPagedPoolUsage;
   SIZE_T PagefileUsage;
   SIZE_T PeakPagefileUsage;
   SIZE_T PrivatePageCount;
} VM_COUNTERS, *PVM_COUNTERS;

typedef struct _SYSTEM_PROCESS_INFORMATION
{
#ifdef __WINESRC__                  /* win32/win64 */
   WINULONG NextEntryOffset; /* 00/00 */
   DWORD dwThreadCount; /* 04/04 */
   DWORD dwUnknown1[6]; /* 08/08 */
   LARGE_INTEGER CreationTime; /* 20/20 */
   LARGE_INTEGER UserTime; /* 28/28 */
   LARGE_INTEGER KernelTime; /* 30/30 */
   UNICODE_STRING ProcessName; /* 38/38 */
   DWORD dwBasePriority; /* 40/48 */
   HANDLE UniqueProcessId; /* 44/50 */
   HANDLE ParentProcessId; /* 48/58 */
   WINULONG HandleCount; /* 4c/60 */
   DWORD dwUnknown3; /* 50/64 */
   DWORD dwUnknown4; /* 54/68 */
   VM_COUNTERS vmCounters; /* 58/70 */
   IO_COUNTERS ioCounters; /* 88/d0 */
   SYSTEM_THREAD_INFORMATION ti[1]; /* b8/100 */
#else
   WINULONG NextEntryOffset; /* 00/00 */
   BYTE Reserved1[52]; /* 04/04 */
   PVOID Reserved2[3]; /* 38/38 */
   HANDLE UniqueProcessId; /* 44/50 */
   PVOID Reserved3; /* 48/58 */
   WINULONG HandleCount; /* 4c/60 */
   BYTE Reserved4[4]; /* 50/64 */
   PVOID Reserved5[11]; /* 54/68 */
   SIZE_T PeakPagefileUsage; /* 80/c0 */
   SIZE_T PrivatePageCount; /* 84/c8 */
   LARGE_INTEGER Reserved6[6]; /* 88/d0 */
#endif
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION
{
   WINULONG RegistryQuotaAllowed;
   WINULONG RegistryQuotaUsed;
   PVOID Reserved1;
} SYSTEM_REGISTRY_QUOTA_INFORMATION, *PSYSTEM_REGISTRY_QUOTA_INFORMATION;

typedef struct _SYSTEM_TIME_ADJUSTMENT
{
   WINULONG TimeAdjustment;
   int_bool TimeAdjustmentDisabled;
} SYSTEM_TIME_ADJUSTMENT, *PSYSTEM_TIME_ADJUSTMENT;

typedef struct _TIME_FIELDS
{
   CSHORT Year;
   CSHORT Month;
   CSHORT Day;
   CSHORT Hour;
   CSHORT Minute;
   CSHORT Second;
   CSHORT Milliseconds;
   CSHORT Weekday;
} TIME_FIELDS, *PTIME_FIELDS;

typedef struct _WINSTATIONINFORMATIONW
{
   BYTE Reserved2[70];
   WINULONG LogonId;
   BYTE Reserved3[1140];
} WINSTATIONINFORMATIONW, *PWINSTATIONINFORMATIONW;

typedef int_bool(WINAPI * PWINSTATIONQUERYINFORMATIONW)(HANDLE, WINULONG, WINSTATIONINFOCLASS, PVOID, WINULONG, PWINULONG);

typedef struct _LDR_RESOURCE_INFO
{
   ULONG_PTR Type;
   ULONG_PTR Name;
   WINULONG Language;
} LDR_RESOURCE_INFO, *PLDR_RESOURCE_INFO;

/* debug buffer definitions */

typedef struct _DEBUG_BUFFER
{
   HANDLE SectionHandle;
   PVOID SectionBase;
   PVOID RemoteSectionBase;
   WINULONG SectionBaseDelta;
   HANDLE EventPairHandle;
   WINULONG Unknown[2];
   HANDLE RemoteThreadHandle;
   WINULONG InfoClassMask;
   WINULONG SizeOfInfo;
   WINULONG AllocatedSize;
   WINULONG SectionSize;
   PVOID ModuleInformation;
   PVOID BackTraceInformation;
   PVOID HeapInformation;
   PVOID LockInformation;
   PVOID Reserved[8];
} DEBUG_BUFFER, *PDEBUG_BUFFER;

#define PDI_MODULES                       0x01
#define PDI_BACKTRACE                     0x02
#define PDI_HEAPS                         0x04
#define PDI_HEAP_TAGS                     0x08
#define PDI_HEAP_BLOCKS                   0x10
#define PDI_LOCKS                         0x20

typedef struct _DEBUG_MODULE_INFORMATION
{
   WINULONG Reserved[2];
   WINULONG Base;
   WINULONG Size;
   WINULONG Flags;
   WINUSHORT Index;
   WINUSHORT Unknown;
   WINUSHORT LoadCount;
   WINUSHORT ModuleNameOffset;
   CHAR ImageName[256];
} DEBUG_MODULE_INFORMATION, *PDEBUG_MODULE_INFORMATION;

typedef struct _DEBUG_HEAP_INFORMATION
{
   WINULONG Base;
   WINULONG Flags;
   WINUSHORT Granularity;
   WINUSHORT Unknown;
   WINULONG Allocated;
   WINULONG Committed;
   WINULONG TagCount;
   WINULONG BlockCount;
   WINULONG Reserved[7];
   PVOID Tags;
   PVOID Blocks;
} DEBUG_HEAP_INFORMATION, *PDEBUG_HEAP_INFORMATION;

typedef struct _DEBUG_LOCK_INFORMATION
{
   PVOID Address;
   WINUSHORT Type;
   WINUSHORT CreatorBackTraceIndex;
   WINULONG OwnerThreadId;
   WINULONG ActiveCount;
   WINULONG ContentionCount;
   WINULONG EntryCount;
   WINULONG RecursionCount;
   WINULONG NumberOfSharedWaiters;
   WINULONG NumberOfExclusiveWaiters;
} DEBUG_LOCK_INFORMATION, *PDEBUG_LOCK_INFORMATION;

typedef struct _PORT_MESSAGE_HEADER
{
   WINUSHORT DataSize;
   WINUSHORT MessageSize;
   WINUSHORT MessageType;
   WINUSHORT VirtualRangesOffset;
   CLIENT_ID ClientId;
   WINULONG MessageId;
   WINULONG SectionSize;
} PORT_MESSAGE_HEADER, *PPORT_MESSAGE_HEADER, PORT_MESSAGE, *PPORT_MESSAGE;

typedef unsigned short RTL_ATOM, *PRTL_ATOM;

/* Wine doesn't implement atom table as NT does:
 * - in NT, atom tables are user space tables, which ntdll directly accesses
 * - on Wine, (even local) atom tables are wineserver objects, hence a HANDLE
 */
typedef struct atom_table *RTL_ATOM_TABLE, **PRTL_ATOM_TABLE;

typedef enum _ATOM_INFORMATION_CLASS
{
   AtomBasicInformation = 0,
   AtomTableInformation = 1
} ATOM_INFORMATION_CLASS;

typedef struct _ATOM_BASIC_INFORMATION
{
   WINUSHORT ReferenceCount;
   WINUSHORT Pinned;
   WINUSHORT NameLength;
   WCHAR Name[1];
} ATOM_BASIC_INFORMATION, *PATOM_BASIC_INFORMATION;

/* FIXME: names probably not correct */
typedef struct _RTL_HANDLE
{
   struct _RTL_HANDLE * Next;
} RTL_HANDLE;

/* FIXME: names probably not correct */
typedef struct _RTL_HANDLE_TABLE
{
   WINULONG MaxHandleCount; /* 0x00 */
   WINULONG HandleSize; /* 0x04 */
   WINULONG Unused[2]; /* 0x08-0x0c */
   PVOID NextFree; /* 0x10 */
   PVOID FirstHandle; /* 0x14 */
   PVOID ReservedMemory; /* 0x18 */
   PVOID MaxHandle; /* 0x1c */
} RTL_HANDLE_TABLE;

/***********************************************************************
 * Defines
 */

/* flags for NtCreateFile and NtOpenFile */
#define FILE_DIRECTORY_FILE             0x00000001
#define FILE_WRITE_THROUGH              0x00000002
#define FILE_SEQUENTIAL_ONLY            0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING  0x00000008
#define FILE_SYNCHRONOUS_IO_ALERT       0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT    0x00000020
#define FILE_NON_DIRECTORY_FILE         0x00000040
#define FILE_CREATE_TREE_CONNECTION     0x00000080
#define FILE_COMPLETE_IF_OPLOCKED       0x00000100
#define FILE_NO_EA_KNOWLEDGE            0x00000200
#define FILE_OPEN_FOR_RECOVERY          0x00000400
#define FILE_RANDOM_ACCESS              0x00000800
#define FILE_DELETE_ON_CLOSE            0x00001000
#define FILE_OPEN_BY_FILE_ID            0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT     0x00004000
#define FILE_NO_COMPRESSION             0x00008000
#define FILE_RESERVE_OPFILTER           0x00100000
#define FILE_TRANSACTED_MODE            0x00200000
#define FILE_OPEN_OFFLINE_FILE          0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY  0x00800000

#define FILE_ATTRIBUTE_VALID_FLAGS      0x00007fb7
#define FILE_ATTRIBUTE_VALID_SET_FLAGS  0x000031a7

/* status for NtCreateFile or NtOpenFile */
#define FILE_SUPERSEDED                 0
#define FILE_OPENED                     1
#define FILE_CREATED                    2
#define FILE_OVERWRITTEN                3
#define FILE_EXISTS                     4
#define FILE_DOES_NOT_EXIST             5

/* disposition for NtCreateFile */
#define FILE_SUPERSEDE                  0
#define FILE_OPEN                       1
#define FILE_CREATE                     2
#define FILE_OPEN_IF                    3
#define FILE_OVERWRITE                  4
#define FILE_OVERWRITE_IF               5
#define FILE_MAXIMUM_DISPOSITION        5

/* Characteristics of a File System */
#define FILE_REMOVABLE_MEDIA            0x00000001
#define FILE_READ_ONLY_DEVICE           0x00000002
#define FILE_FLOPPY_DISKETTE            0x00000004
#define FILE_WRITE_ONE_MEDIA            0x00000008
#define FILE_REMOTE_DEVICE              0x00000010
#define FILE_DEVICE_IS_MOUNTED          0x00000020
#define FILE_VIRTUAL_VOLUME             0x00000040
#define FILE_AUTOGENERATED_DEVICE_NAME  0x00000080
#define FILE_DEVICE_SECURE_OPEN         0x00000100

/* options for NtCreateNamedPipeFile */
#define FILE_PIPE_INBOUND               0x00000000
#define FILE_PIPE_OUTBOUND              0x00000001
#define FILE_PIPE_FULL_DUPLEX           0x00000002

/* options for pipe's type */
#define FILE_PIPE_TYPE_MESSAGE          0x00000001
#define FILE_PIPE_TYPE_BYTE             0x00000000
/* and client / server end */
#define FILE_PIPE_SERVER_END            0x00000001
#define FILE_PIPE_CLIENT_END            0x00000000

#define INTERNAL_TS_ACTIVE_CONSOLE_ID ( *((volatile WINULONG*)(0x7ffe02d8)) )

#define LOGONID_CURRENT    ((WINULONG)-1)

#define OBJ_INHERIT          0x00000002L
#define OBJ_PERMANENT        0x00000010L
#define OBJ_EXCLUSIVE        0x00000020L
#define OBJ_CASE_INSENSITIVE 0x00000040L
#define OBJ_OPENIF           0x00000080L
#define OBJ_OPENLINK         0x00000100L
#define OBJ_KERNEL_HANDLE    0x00000200L
#define OBJ_VALID_ATTRIBUTES 0x000003F2L

#define SERVERNAME_CURRENT ((HANDLE)nullptr)

typedef void (CALLBACK *PNTAPCFUNC)(ULONG_PTR, ULONG_PTR, ULONG_PTR); /* FIXME: not the right name */
typedef void (CALLBACK *PRTL_THREAD_START_ROUTINE)(LPVOID); /* FIXME: not the right name */
typedef DWORD(CALLBACK *PRTL_WORK_ITEM_ROUTINE)(LPVOID); /* FIXME: not the right name */
typedef void (NTAPI *RTL_WAITORTIMERCALLBACKFUNC)(PVOID, int_bool); /* FIXME: not the right name */


/* DbgPrintEx default levels */
#define DPFLTR_ERROR_LEVEL     0
#define DPFLTR_WARNING_LEVEL   1
#define DPFLTR_TRACE_LEVEL     2
#define DPFLTR_INFO_LEVEL      3
#define DPFLTR_MASK    0x8000000

/* Well-known LUID values */
#define SE_MIN_WELL_KNOWN_PRIVILEGE       2L
#define SE_CREATE_TOKEN_PRIVILEGE         2L
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE   3L
#define SE_LOCK_MEMORY_PRIVILEGE          4L
#define SE_INCREASE_QUOTA_PRIVILEGE       5L
#define SE_UNSOLICITED_INPUT_PRIVILEGE    6L /* obsolete */
#define SE_MACHINE_ACCOUNT_PRIVILEGE      6L
#define SE_TCB_PRIVILEGE                  7L
#define SE_SECURITY_PRIVILEGE             8L
#define SE_TAKE_OWNERSHIP_PRIVILEGE       9L
#define SE_LOAD_DRIVER_PRIVILEGE         10L
#define SE_SYSTEM_PROFILE_PRIVILEGE      11L
#define SE_SYSTEMTIME_PRIVILEGE          12L
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE 13L
#define SE_INC_AXIS_PRIORITY_PRIVILEGE   14L
#define SE_CREATE_PAGEFILE_PRIVILEGE     15L
#define SE_CREATE_PERMANENT_PRIVILEGE    16L
#define SE_BACKUP_PRIVILEGE              17L
#define SE_RESTORE_PRIVILEGE             18L
#define SE_SHUTDOWN_PRIVILEGE            19L
#define SE_DEBUG_PRIVILEGE               20L
#define SE_AUDIT_PRIVILEGE               21L
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE  22L
#define SE_CHANGE_NOTIFY_PRIVILEGE       23L
#define SE_REMOTE_SHUTDOWN_PRIVILEGE     24L
#define SE_UNDOCK_PRIVILEGE              25L
#define SE_SYNC_AGENT_PRIVILEGE          26L
#define SE_ENABLE_DELEGATION_PRIVILEGE   27L
#define SE_MANAGE_VOLUME_PRIVILEGE       28L
#define SE_IMPERSONATE_PRIVILEGE         29L
#define SE_CREATE_GLOBAL_PRIVILEGE       30L
#define SE_MAX_WELL_KNOWN_PRIVILEGE      SE_CREATE_GLOBAL_PRIVILEGE

/* NtGlobalFlag bits */
#define FLG_STOP_ON_EXCEPTION            0x00000001
#define FLG_SHOW_LDR_SNAPS               0x00000002
#define FLG_DEBUG_INITIAL_COMMAND        0x00000004
#define FLG_STOP_ON_HUNG_GUI             0x00000008
#define FLG_HEAP_ENABLE_TAIL_CHECK       0x00000010
#define FLG_HEAP_ENABLE_FREE_CHECK       0x00000020
#define FLG_HEAP_VALIDATE_PARAMETERS     0x00000040
#define FLG_HEAP_VALIDATE_ALL            0x00000080
#define FLG_APPLICATION_VERIFIER         0x00000100
#define FLG_POOL_ENABLE_TAGGING          0x00000400
#define FLG_HEAP_ENABLE_TAGGING          0x00000800
#define FLG_USER_STACK_TRACE_DB          0x00001000
#define FLG_KERNEL_STACK_TRACE_DB        0x00002000
#define FLG_MAINTAIN_OBJECT_TYPELIST     0x00004000
#define FLG_HEAP_ENABLE_TAG_BY_DLL       0x00008000
#define FLG_DISABLE_STACK_EXTENSION      0x00010000
#define FLG_ENABLE_CSRDEBUG              0x00020000
#define FLG_ENABLE_KDEBUG_SYMBOL_LOAD    0x00040000
#define FLG_DISABLE_PAGE_KERNEL_STACKS   0x00080000
#define FLG_ENABLE_SYSTEM_CRIT_BREAKS    0x00100000
#define FLG_HEAP_DISABLE_COALESCING      0x00200000
#define FLG_ENABLE_CLOSE_EXCEPTIONS      0x00400000
#define FLG_ENABLE_EXCEPTION_LOGGING     0x00800000
#define FLG_ENABLE_HANDLE_TYPE_TAGGING   0x01000000
#define FLG_HEAP_PAGE_ALLOCS             0x02000000
#define FLG_DEBUG_INITIAL_COMMAND_EX     0x04000000
#define FLG_DISABLE_DBGPRINT             0x08000000
#define FLG_CRITSEC_EVENT_CREATION       0x10000000
#define FLG_LDR_TOP_DOWN                 0x20000000
#define FLG_ENABLE_HANDLE_EXCEPTIONS     0x40000000
#define FLG_DISABLE_PROTDLLS             0x80000000

/* Rtl*Registry* functions structs and defines */
#define RTL_REGISTRY_ABSOLUTE             0
#define RTL_REGISTRY_SERVICES             1
#define RTL_REGISTRY_CONTROL              2
#define RTL_REGISTRY_WINDOWS_NT           3
#define RTL_REGISTRY_DEVICEMAP            4
#define RTL_REGISTRY_USER                 5

#define RTL_REGISTRY_HANDLE       0x40000000
#define RTL_REGISTRY_OPTIONAL     0x80000000

#define RTL_QUERY_REGISTRY_SUBKEY         0x00000001
#define RTL_QUERY_REGISTRY_TOPKEY         0x00000002
#define RTL_QUERY_REGISTRY_REQUIRED       0x00000004
#define RTL_QUERY_REGISTRY_NOVALUE        0x00000008
#define RTL_QUERY_REGISTRY_NOEXPAND       0x00000010
#define RTL_QUERY_REGISTRY_DIRECT         0x00000020
#define RTL_QUERY_REGISTRY_DELETE         0x00000040

typedef NTSTATUS(WINAPI *PRTL_QUERY_REGISTRY_ROUTINE)(PCWSTR ValueName,
      WINULONG ValueType,
      PVOID ValueData,
      WINULONG ValueLength,
      PVOID Context,
      PVOID EntryContext);

typedef struct _RTL_QUERY_REGISTRY_TABLE
{
   PRTL_QUERY_REGISTRY_ROUTINE QueryRoutine;
   WINULONG Flags;
   PWSTR Name;
   PVOID EntryContext;
   WINULONG DefaultType;
   PVOID DefaultData;
   WINULONG DefaultLength;
} RTL_QUERY_REGISTRY_TABLE, *PRTL_QUERY_REGISTRY_TABLE;

typedef struct _KEY_MULTIPLE_VALUE_INFORMATION
{
   PUNICODE_STRING ValueName;
   WINULONG DataLength;
   WINULONG DataOffset;
   WINULONG Type;
} KEY_MULTIPLE_VALUE_INFORMATION, *PKEY_MULTIPLE_VALUE_INFORMATION;

typedef VOID(CALLBACK *PRTL_OVERLAPPED_COMPLETION_ROUTINE)(DWORD, DWORD, LPVOID);

typedef VOID(CALLBACK *PTIMER_APC_ROUTINE) (PVOID, WINULONG, LONG);

typedef enum _EVENT_TYPE
{
   NotificationEvent,
   SynchronizationEvent
} EVENT_TYPE, *PEVENT_TYPE;

typedef enum _EVENT_INFORMATION_CLASS
{
   EventBasicInformation
} EVENT_INFORMATION_CLASS, *PEVENT_INFORMATION_CLASS;

typedef struct _EVENT_BASIC_INFORMATION
{
   EVENT_TYPE EventType;
   LONG EventState;
} EVENT_BASIC_INFORMATION, *PEVENT_BASIC_INFORMATION;

typedef enum _SEMAPHORE_INFORMATION_CLASS
{
   SemaphoreBasicInformation
} SEMAPHORE_INFORMATION_CLASS, *PSEMAPHORE_INFORMATION_CLASS;

typedef struct _SEMAPHORE_BASIC_INFORMATION
{
   WINULONG CurrentCount;
   WINULONG MaximumCount;
} SEMAPHORE_BASIC_INFORMATION, *PSEMAPHORE_BASIC_INFORMATION;

typedef enum _SECTION_INFORMATION_CLASS
{
   SectionBasicInformation,
   SectionImageInformation
} SECTION_INFORMATION_CLASS;

typedef struct _SECTION_BASIC_INFORMATION
{
   WINULONG BaseAddress;
   WINULONG Attributes;
   LARGE_INTEGER Size;
} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

typedef struct _SECTION_IMAGE_INFORMATION
{
   PVOID EntryPoint;
   WINULONG StackZeroBits;
   WINULONG StackReserved;
   WINULONG StackCommit;
   WINULONG ImageSubsystem;
   WORD SubsystemVersionLow;
   WORD SubsystemVersionHigh;
   WINULONG Unknown1;
   WINULONG ImageCharacteristics;
   WINULONG ImageMachineType;
   WINULONG Unknown2[3];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _LPC_SECTION_WRITE
{
   WINULONG Length;
   HANDLE SectionHandle;
   WINULONG SectionOffset;
   WINULONG ViewSize;
   PVOID ViewBase;
   PVOID TargetViewBase;
} LPC_SECTION_WRITE, *PLPC_SECTION_WRITE;

typedef struct _LPC_SECTION_READ
{
   WINULONG Length;
   WINULONG ViewSize;
   PVOID ViewBase;
} LPC_SECTION_READ, *PLPC_SECTION_READ;

typedef struct _LPC_MESSAGE
{
   WINUSHORT DataSize;
   WINUSHORT MessageSize;
   WINUSHORT MessageType;
   WINUSHORT VirtualRangesOffset;
   CLIENT_ID ClientId;
   ULONG_PTR MessageId;
   ULONG_PTR SectionSize;
   WINUCHAR Data[ANYSIZE_ARRAY];
} LPC_MESSAGE, *PLPC_MESSAGE;

typedef enum _SHUTDOWN_ACTION
{
   ShutdownNoReboot,
   ShutdownReboot,
   ShutdownPowerOff
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;

typedef enum _KPROFILE_SOURCE
{
   ProfileTime,
   ProfileAlignmentFixup,
   ProfileTotalIssues,
   ProfilePipelineDry,
   ProfileLoadInstructions,
   ProfilePipelineFrozen,
   ProfileBranchInstructions,
   ProfileTotalNonissues,
   ProfileDcacheMisses,
   ProfileIcacheMisses,
   ProfileCacheMisses,
   ProfileBranchMispredictions,
   ProfileStoreInstructions,
   ProfileFpInstructions,
   ProfileIntegerInstructions,
   Profile2Issue,
   Profile3Issue,
   Profile4Issue,
   ProfileSpecialInstructions,
   ProfileTotalCycles,
   ProfileIcacheIssues,
   ProfileDcacheAccesses,
   ProfileMemoryBarrierCycles,
   ProfileLoadLinkedIssues,
   ProfileMaximum
} KPROFILE_SOURCE, *PKPROFILE_SOURCE;

typedef struct _DIRECTORY_BASIC_INFORMATION
{
   UNICODE_STRING ObjectName;
   UNICODE_STRING ObjectTypeName;
} DIRECTORY_BASIC_INFORMATION, *PDIRECTORY_BASIC_INFORMATION;

typedef struct _INITIAL_TEB
{
   PVOID StackBase;
   PVOID StackLimit;
   PVOID StackCommit;
   PVOID StackCommitMax;
   PVOID StackReserved;
} INITIAL_TEB, *PINITIAL_TEB;

typedef enum _PORT_INFORMATION_CLASS
{
   PortNoInformation
} PORT_INFORMATION_CLASS, *PPORT_INFORMATION_CLASS;

typedef enum _IO_COMPLETION_INFORMATION_CLASS
{
   IoCompletionBasicInformation
} IO_COMPLETION_INFORMATION_CLASS, *PIO_COMPLETION_INFORMATION_CLASS;

typedef struct _FILE_COMPLETION_INFORMATION
{
   HANDLE CompletionPort;
   ULONG_PTR CompletionKey;
} FILE_COMPLETION_INFORMATION, *PFILE_COMPLETION_INFORMATION;

#define IO_COMPLETION_QUERY_STATE  0x0001
#define IO_COMPLETION_MODIFY_STATE 0x0002
#define IO_COMPLETION_ALL_ACCESS   (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

typedef enum _HARDERROR_RESPONSE_OPTION
{
   OptionAbortRetryIgnore,
   OptionOk,
   OptionOkCancel,
   OptionRetryCancel,
   OptionYesNo,
   OptionYesNoCancel,
   OptionShutdownSystem
} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;

typedef enum _HARDERROR_RESPONSE
{
   ResponseReturnToCaller,
   ResponseNotHandled,
   ResponseAbort,
   ResponseCancel,
   ResponseIgnore,
   ResponseNo,
   ResponseOk,
   ResponseRetry,
   ResponseYes
} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;

typedef enum _SYSDBG_COMMAND
{
   SysDbgQueryModuleInformation,
   SysDbgQueryTraceInformation,
   SysDbgSetTracepoint,
   SysDbgSetSpecialCall,
   SysDbgClearSpecialCalls,
   SysDbgQuerySpecialCalls,
   SysDbgBreakPoint,
   SysDbgQueryVersion,
   SysDbgReadVirtual,
   SysDbgWriteVirtual,
   SysDbgReadPhysical,
   SysDbgWritePhysical,
   SysDbgReadControlSpace,
   SysDbgWriteControlSpace,
   SysDbgReadIoSpace,
   SysDbgWriteIoSpace,
   SysDbgReadMsr,
   SysDbgWriteMsr,
   SysDbgReadBusData,
   SysDbgWriteBusData
} SYSDBG_COMMAND, *PSYSDBG_COMMAND;

/*************************************************************************
 * Loader structures
 *
 * Those are not part of standard Winternl.h
 */
typedef struct _LDR_MODULE
{
   LIST_ENTRY InLoadOrderModuleList;
   LIST_ENTRY InMemoryOrderModuleList;
   LIST_ENTRY InInitializationOrderModuleList;
   void* BaseAddress;
   void* EntryPoint;
   WINULONG SizeOfImage;
   UNICODE_STRING FullDllName;
   UNICODE_STRING BaseDllName;
   WINULONG Flags;
   SHORT LoadCount;
   SHORT TlsIndex;
   HANDLE SectionHandle;
   WINULONG CheckSum;
   WINULONG TimeDateStamp;
   HANDLE ActivationContext;
} LDR_MODULE, *PLDR_MODULE;

/* those defines are (some of the) regular LDR_MODULE.Flags values */
#define LDR_IMAGE_IS_DLL                0x00000004
#define LDR_LOAD_IN_PROGRESS            0x00001000
#define LDR_UNLOAD_IN_PROGRESS          0x00002000
#define LDR_NO_DLL_CALLS                0x00040000
#define LDR_PROCESS_ATTACHED            0x00080000
#define LDR_MODULE_REAXISD              0x00200000

/* these ones is Wine specific */
#define LDR_DONT_RESOLVE_REFS           0x40000000
#define LDR_WINE_INTERNAL               0x80000000

/* FIXME: to be checked */
#define MAXIMUM_FILENAME_LENGTH 256

typedef struct _SYSTEM_MODULE
{
   PVOID Reserved1; /* 00/00 */
   PVOID Reserved2; /* 04/08 */
   PVOID ImageBaseAddress; /* 08/10 */
   WINULONG ImageSize; /* 0c/18 */
   WINULONG Flags; /* 10/1c */
   WORD Id; /* 14/20 */
   WORD Rank; /* 16/22 */
   WORD Unknown; /* 18/24 */
   WORD NameOffset; /* 1a/26 */
   BYTE Name[MAXIMUM_FILENAME_LENGTH]; /* 1c/28 */
} SYSTEM_MODULE, *PSYSTEM_MODULE;

typedef struct _SYSTEM_MODULE_INFORMATION
{
   WINULONG ModulesCount;
   SYSTEM_MODULE Modules[1]; /* FIXME: should be Modules[0] */
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

/***********************************************************************
 * Function declarations
 */

#if defined(__i386__) && defined(__GNUC__)

static inline void WINAPI DbgBreakPoint(void)
{
   __asm__ __volatile__("int3");
}

static inline void WINAPI DbgUserBreakPoint(void)
{
   __asm__ __volatile__("int3");
}
#else  /* __i386__ && __GNUC__ */
CLASS_DECL_AQUA void WINAPI DbgBreakPoint(void);
CLASS_DECL_AQUA void WINAPI DbgUserBreakPoint(void);
#endif  /* __i386__ && __GNUC__ */
CLASS_DECL_AQUA NTSTATUS WINAPIV DbgPrint(LPCSTR fmt, ...);
CLASS_DECL_AQUA NTSTATUS WINAPIV DbgPrintEx(WINULONG iComponentId, WINULONG Level, LPCSTR fmt, ...);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrAccessResource(HMODULE, const IMAGE_RESOURCE_DATA_ENTRY*, void**, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrAddRefDll(WINULONG, HMODULE);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrFindResourceDirectory_U(HMODULE, const LDR_RESOURCE_INFO*, WINULONG, const IMAGE_RESOURCE_DIRECTORY**);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrFindResource_U(HMODULE, const LDR_RESOURCE_INFO*, WINULONG, const IMAGE_RESOURCE_DATA_ENTRY**);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrDisableThreadCalloutsForDll(HMODULE);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrFindEntryForAddress(const void*, PLDR_MODULE*);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrGetDllHandle(LPCWSTR, WINULONG, const UNICODE_STRING*, HMODULE*);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrGetProcedureAddress(HMODULE, const ANSI_STRING*, WINULONG, void**);
CLASS_DECL_AQUA void WINAPI LdrInitializeThunk(void*, ULONG_PTR, ULONG_PTR, ULONG_PTR);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrLoadDll(LPCWSTR, DWORD, const UNICODE_STRING*, HMODULE*);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrLockLoaderLock(WINULONG, WINULONG*, WINULONG*);
IMAGE_BASE_RELOCATION * WINAPI LdrProcessRelocationBlock(void*, UINT, WINUSHORT*, INT_PTR);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrQueryImageFileExecutionOptions(const UNICODE_STRING*, LPCWSTR, WINULONG, void*, WINULONG, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrQueryProcessModuleInformation(SYSTEM_MODULE_INFORMATION*, WINULONG, WINULONG*);
CLASS_DECL_AQUA void WINAPI LdrShutdownProcess(void);
CLASS_DECL_AQUA void WINAPI LdrShutdownThread(void);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrUnloadDll(HMODULE);
CLASS_DECL_AQUA NTSTATUS WINAPI LdrUnlockLoaderLock(WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAcceptConnectPort(PHANDLE, WINULONG, PLPC_MESSAGE, int_bool, PLPC_SECTION_WRITE, PLPC_SECTION_READ);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtAccessCheck(PSECURITY_DESCRIPTOR, HANDLE, ACCESS_MASK, PGENERIC_MAPPING, PPRIVILEGE_SET, PWINULONG, PWINULONG, NTSTATUS*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAccessCheckAndAuditAlarm(PUNICODE_STRING, HANDLE, PUNICODE_STRING, PUNICODE_STRING, PSECURITY_DESCRIPTOR, ACCESS_MASK, PGENERIC_MAPPING, int_bool, PACCESS_MASK, PBOOLEAN, PBOOLEAN);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAddAtom(const WCHAR*, WINULONG, RTL_ATOM*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAdjustGroupsToken(HANDLE, int_bool, PTOKEN_GROUPS, WINULONG, PTOKEN_GROUPS, PWINULONG);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtAdjustPrivilegesToken(HANDLE, int_bool, PTOKEN_PRIVILEGES, DWORD, PTOKEN_PRIVILEGES, PDWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAlertResumeThread(HANDLE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAlertThread(HANDLE ThreadHandle);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAllocateLocallyUniqueId(PLUID lpLuid);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAllocateUuids(PULARGE_INTEGER, PWINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAllocateVirtualMemory(HANDLE, PVOID*, WINULONG, SIZE_T*, WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAreMappedFilesTheSame(PVOID, PVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtAssignProcessToJobObject(HANDLE, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCallbackReturn(PVOID, WINULONG, NTSTATUS);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCancelIoFile(HANDLE, PIO_STATUS_BLOCK);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCancelIoFileEx(HANDLE, PIO_STATUS_BLOCK, PIO_STATUS_BLOCK);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCancelTimer(HANDLE, int_bool*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtClearEvent(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtClose(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCloseObjectAuditAlarm(PUNICODE_STRING, HANDLE, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCompleteConnectPort(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtConnectPort(PHANDLE, PUNICODE_STRING, PSECURITY_QUALITY_OF_SERVICE, PLPC_SECTION_WRITE, PLPC_SECTION_READ, PWINULONG, PVOID, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtContinue(PCONTEXT, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateDirectoryObject(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateEvent(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES *, EVENT_TYPE, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateEventPair(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateFile(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, PLARGE_INTEGER, WINULONG, WINULONG, WINULONG, WINULONG, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateIoCompletion(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateJobObject(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateKey(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*, WINULONG, const UNICODE_STRING*, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateMailslotFile(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, WINULONG, WINULONG, WINULONG, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateMutant(HANDLE*, ACCESS_MASK, const OBJECT_ATTRIBUTES*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateNamedPipeFile(PHANDLE, WINULONG, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, WINULONG, WINULONG, WINULONG, WINULONG, WINULONG, WINULONG, WINULONG, WINULONG, WINULONG, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreatePagingFile(PUNICODE_STRING, PLARGE_INTEGER, PLARGE_INTEGER, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreatePort(PHANDLE, POBJECT_ATTRIBUTES, WINULONG, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateProcess(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, int_bool, HANDLE, HANDLE, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateProfile(PHANDLE, HANDLE, PVOID, WINULONG, WINULONG, PVOID, WINULONG, KPROFILE_SOURCE, KAFFINITY);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateSection(HANDLE*, ACCESS_MASK, const OBJECT_ATTRIBUTES*, const LARGE_INTEGER*, WINULONG, WINULONG, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateSemaphore(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*, LONG, LONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateSymbolicLinkObject(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PUNICODE_STRING);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateThread(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, PCLIENT_ID, PCONTEXT, PINITIAL_TEB, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateTimer(HANDLE*, ACCESS_MASK, const OBJECT_ATTRIBUTES*, TIMER_TYPE);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtCreateToken(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, TOKEN_TYPE, PLUID, PLARGE_INTEGER, PTOKEN_USER, PTOKEN_GROUPS, PTOKEN_PRIVILEGES, PTOKEN_OWNER, PTOKEN_PRIMARY_GROUP, PTOKEN_DEFAULT_DACL, PTOKEN_SOURCE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDelayExecution(int_bool, const LARGE_INTEGER*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDeleteAtom(RTL_ATOM);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDeleteFile(POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDeleteKey(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDeleteValueKey(HANDLE, const UNICODE_STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDeviceIoControlFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, WINULONG, PVOID, WINULONG, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDisplayString(PUNICODE_STRING);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDuplicateObject(HANDLE, HANDLE, HANDLE, PHANDLE, ACCESS_MASK, WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtDuplicateToken(HANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, SECURITY_IMPERSONATION_LEVEL, TOKEN_TYPE, PHANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtEnumerateKey(HANDLE, WINULONG, KEY_INFORMATION_CLASS, void *, DWORD, DWORD *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtEnumerateValueKey(HANDLE, WINULONG, KEY_VALUE_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtExtendSection(HANDLE, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFindAtom(const WCHAR*, WINULONG, RTL_ATOM*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFlushBuffersFile(HANDLE, IO_STATUS_BLOCK*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFlushInstructionCache(HANDLE, LPCVOID, SIZE_T);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFlushKey(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFlushVirtualMemory(HANDLE, LPCVOID*, SIZE_T*, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFlushWriteBuffer(VOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFreeVirtualMemory(HANDLE, PVOID*, SIZE_T*, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtFsControlFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, WINULONG, PVOID, WINULONG, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtGetContextThread(HANDLE, CONTEXT*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtGetPlugPlayEvent(WINULONG, WINULONG, PVOID, WINULONG);
CLASS_DECL_AQUA WINULONG WINAPI NtGetTickCount(VOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtGetWriteWatch(HANDLE, WINULONG, PVOID, SIZE_T, PVOID*, ULONG_PTR*, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtImpersonateAnonymousToken(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtImpersonateClientOfPort(HANDLE, PPORT_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtImpersonateThread(HANDLE, HANDLE, PSECURITY_QUALITY_OF_SERVICE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtInitializeRegistry(int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtInitiatePowerAction(POWER_ACTION, SYSTEM_POWER_STATE, WINULONG, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtIsProcessInJob(HANDLE, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtListenPort(HANDLE, PLPC_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtLoadDriver(const UNICODE_STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtLoadKey(const OBJECT_ATTRIBUTES *, OBJECT_ATTRIBUTES *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtLockFile(HANDLE, HANDLE, PIO_APC_ROUTINE, void*, PIO_STATUS_BLOCK, PLARGE_INTEGER, PLARGE_INTEGER, WINULONG*, int_bool, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtLockVirtualMemory(HANDLE, PVOID*, SIZE_T*, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtMakeTemporaryObject(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtMapViewOfSection(HANDLE, HANDLE, PVOID*, WINULONG, SIZE_T, const LARGE_INTEGER*, SIZE_T*, SECTION_INHERIT, WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtNotifyChangeDirectoryFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, PVOID, WINULONG, WINULONG, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtNotifyChangeKey(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, WINULONG, int_bool, PVOID, WINULONG, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenDirectoryObject(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenEvent(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenEventPair(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenFile(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenIoCompletion(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenJobObject(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenKey(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenMutant(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenObjectAuditAlarm(PUNICODE_STRING, PHANDLE, PUNICODE_STRING, PUNICODE_STRING, PSECURITY_DESCRIPTOR, HANDLE, ACCESS_MASK, ACCESS_MASK, PPRIVILEGE_SET, int_bool, int_bool, PBOOLEAN);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenProcess(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*, const CLIENT_ID*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenProcessToken(HANDLE, DWORD, HANDLE *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenProcessTokenEx(HANDLE, DWORD, DWORD, HANDLE *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenSection(HANDLE*, ACCESS_MASK, const OBJECT_ATTRIBUTES*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenSemaphore(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenSymbolicLinkObject(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenThread(HANDLE*, ACCESS_MASK, const OBJECT_ATTRIBUTES*, const CLIENT_ID*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenThreadToken(HANDLE, DWORD, int_bool, HANDLE *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenThreadTokenEx(HANDLE, DWORD, int_bool, DWORD, HANDLE *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtOpenTimer(HANDLE*, ACCESS_MASK, const OBJECT_ATTRIBUTES*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtPowerInformation(POWER_INFORMATION_LEVEL, PVOID, WINULONG, PVOID, WINULONG);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtPrivilegeCheck(HANDLE, PPRIVILEGE_SET, PBOOLEAN);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtPrivilegeObjectAuditAlarm(PUNICODE_STRING, HANDLE, HANDLE, WINULONG, PPRIVILEGE_SET, int_bool);
//    CLASS_DECL_AQUA NTSTATUS WINAPI NtPrivilegedServiceAuditAlarm(PUNICODE_STRING, PUNICODE_STRING, HANDLE, PPRIVILEGE_SET, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtProtectVirtualMemory(HANDLE, PVOID*, SIZE_T*, WINULONG, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtPulseEvent(HANDLE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueueApcThread(HANDLE, PNTAPCFUNC, ULONG_PTR, ULONG_PTR, ULONG_PTR);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryAttributesFile(const OBJECT_ATTRIBUTES*, FILE_BASIC_INFORMATION*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryDefaultLocale(int_bool, LCID*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryDefaultUILanguage(LANGID*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryDirectoryFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, PVOID, WINULONG, FILE_INFORMATION_CLASS, int_bool, PUNICODE_STRING, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryDirectoryObject(HANDLE, PDIRECTORY_BASIC_INFORMATION, WINULONG, int_bool, int_bool, PWINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryEaFile(HANDLE, PIO_STATUS_BLOCK, PVOID, WINULONG, int_bool, PVOID, WINULONG, PWINULONG, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryEvent(HANDLE, EVENT_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryFullAttributesFile(const OBJECT_ATTRIBUTES*, FILE_NETWORK_OPEN_INFORMATION*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationAtom(RTL_ATOM, ATOM_INFORMATION_CLASS, PVOID, WINULONG, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationFile(HANDLE, PIO_STATUS_BLOCK, PVOID, LONG, FILE_INFORMATION_CLASS);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationJobObject(HANDLE, JOBOBJECTINFOCLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationPort(HANDLE, PORT_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationProcess(HANDLE, PROCESSINFOCLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationThread(HANDLE, THREADINFOCLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInformationToken(HANDLE, TOKEN_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryInstallUILanguage(LANGID*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryIntervalProfile(KPROFILE_SOURCE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryIoCompletion(HANDLE, IO_COMPLETION_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryKey(HANDLE, KEY_INFORMATION_CLASS, void *, DWORD, DWORD *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryMultipleValueKey(HANDLE, PKEY_MULTIPLE_VALUE_INFORMATION, WINULONG, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryMutant(HANDLE, MUTANT_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryObject(HANDLE, OBJECT_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryOpenSubKeys(POBJECT_ATTRIBUTES, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryPerformanceCounter(PLARGE_INTEGER, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySecurityObject(HANDLE, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySection(HANDLE, SECTION_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySemaphore(HANDLE, SEMAPHORE_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySymbolicLinkObject(HANDLE, PUNICODE_STRING, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySystemEnvironmentValue(PUNICODE_STRING, PWCHAR, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQuerySystemTime(PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryTimer(HANDLE, TIMER_INFORMATION_CLASS, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryTimerResolution(PWINULONG, PWINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryValueKey(HANDLE, const UNICODE_STRING *, KEY_VALUE_INFORMATION_CLASS, void *, DWORD, DWORD *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryVirtualMemory(HANDLE, LPCVOID, MEMORY_INFORMATION_CLASS, PVOID, SIZE_T, SIZE_T*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtQueryVolumeInformationFile(HANDLE, PIO_STATUS_BLOCK, PVOID, WINULONG, FS_INFORMATION_CLASS);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRaiseException(PEXCEPTION_RECORD, PCONTEXT, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRaiseHardError(NTSTATUS, WINULONG, PUNICODE_STRING, PVOID*, HARDERROR_RESPONSE_OPTION, PHARDERROR_RESPONSE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReadFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, PVOID, WINULONG, PLARGE_INTEGER, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReadFileScatter(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, FILE_SEGMENT_ELEMENT*, WINULONG, PLARGE_INTEGER, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReadRequestData(HANDLE, PLPC_MESSAGE, WINULONG, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReadVirtualMemory(HANDLE, const void*, void*, SIZE_T, SIZE_T*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRegisterThreadTerminatePort(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReleaseMutant(HANDLE, PLONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReleaseSemaphore(HANDLE, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRemoveIoCompletion(HANDLE, PULONG_PTR, PULONG_PTR, PIO_STATUS_BLOCK, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReplaceKey(POBJECT_ATTRIBUTES, HANDLE, POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReplyPort(HANDLE, PLPC_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReplyWaitReceivePort(HANDLE, PWINULONG, PLPC_MESSAGE, PLPC_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReplyWaitReceivePortEx(HANDLE, PVOID*, PPORT_MESSAGE, PPORT_MESSAGE, PLARGE_INTEGER);
CLASS_DECL_AQUA NTSTATUS WINAPI NtReplyWaitReplyPort(HANDLE, PLPC_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRequestPort(HANDLE, PLPC_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRequestWaitReplyPort(HANDLE, PLPC_MESSAGE, PLPC_MESSAGE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtResetEvent(HANDLE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtResetWriteWatch(HANDLE, PVOID, SIZE_T);
CLASS_DECL_AQUA NTSTATUS WINAPI NtRestoreKey(HANDLE, HANDLE, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtResumeThread(HANDLE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSaveKey(HANDLE, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSecureConnectPort(PHANDLE, PUNICODE_STRING, PSECURITY_QUALITY_OF_SERVICE, PLPC_SECTION_WRITE, PSID, PLPC_SECTION_READ, PWINULONG, PVOID, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetContextThread(HANDLE, const CONTEXT*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetDefaultHardErrorPort(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetDefaultLocale(int_bool, LCID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetDefaultUILanguage(LANGID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetEaFile(HANDLE, PIO_STATUS_BLOCK, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetEvent(HANDLE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetHighEventPair(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetHighWaitLowEventPair(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetHighWaitLowThread(VOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationFile(HANDLE, PIO_STATUS_BLOCK, PVOID, WINULONG, FILE_INFORMATION_CLASS);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationJobObject(HANDLE, JOBOBJECTINFOCLASS, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationKey(HANDLE, const i32, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationObject(HANDLE, OBJECT_INFORMATION_CLASS, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationProcess(HANDLE, PROCESS_INFORMATION_CLASS, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationThread(HANDLE, THREADINFOCLASS, LPCVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetInformationToken(HANDLE, TOKEN_INFORMATION_CLASS, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetIntervalProfile(WINULONG, KPROFILE_SOURCE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetIoCompletion(HANDLE, ULONG_PTR, ULONG_PTR, NTSTATUS, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetLdtEntries(WINULONG, LDT_ENTRY, WINULONG, LDT_ENTRY);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetLowEventPair(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetLowWaitHighEventPair(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetLowWaitHighThread(VOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetSecurityObject(HANDLE, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetSystemEnvironmentValue(PUNICODE_STRING, PUNICODE_STRING);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetSystemInformation(SYSTEM_INFORMATION_CLASS, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetSystemPowerState(POWER_ACTION, SYSTEM_POWER_STATE, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetSystemTime(const LARGE_INTEGER*, LARGE_INTEGER*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetTimer(HANDLE, const LARGE_INTEGER*, PTIMER_APC_ROUTINE, PVOID, int_bool, WINULONG, int_bool*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetTimerResolution(WINULONG, int_bool, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetValueKey(HANDLE, const UNICODE_STRING *, WINULONG, WINULONG, const void *, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSetVolumeInformationFile(HANDLE, PIO_STATUS_BLOCK, PVOID, WINULONG, FS_INFORMATION_CLASS);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSignalAndWaitForSingleObject(HANDLE, HANDLE, int_bool, const LARGE_INTEGER*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtShutdownSystem(SHUTDOWN_ACTION);
CLASS_DECL_AQUA NTSTATUS WINAPI NtStartProfile(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtStopProfile(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSuspendThread(HANDLE, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtSystemDebugControl(SYSDBG_COMMAND, PVOID, WINULONG, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtTerminateJobObject(HANDLE, NTSTATUS);
CLASS_DECL_AQUA NTSTATUS WINAPI NtTerminateProcess(HANDLE, LONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtTerminateThread(HANDLE, LONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtTestAlert(VOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtUnloadDriver(const UNICODE_STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI NtUnloadKey(POBJECT_ATTRIBUTES);
CLASS_DECL_AQUA NTSTATUS WINAPI NtUnloadKeyEx(POBJECT_ATTRIBUTES, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtUnlockFile(HANDLE, PIO_STATUS_BLOCK, PLARGE_INTEGER, PLARGE_INTEGER, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtUnlockVirtualMemory(HANDLE, PVOID*, SIZE_T*, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtUnmapViewOfSection(HANDLE, PVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtVdmControl(WINULONG, PVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWaitForSingleObject(HANDLE, int_bool, const LARGE_INTEGER*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWaitForMultipleObjects(WINULONG, const HANDLE*, int_bool, int_bool, const LARGE_INTEGER*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWaitHighEventPair(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWaitLowEventPair(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWriteFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, const void*, WINULONG, PLARGE_INTEGER, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWriteFileGather(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, FILE_SEGMENT_ELEMENT*, WINULONG, PLARGE_INTEGER, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWriteRequestData(HANDLE, PLPC_MESSAGE, WINULONG, PVOID, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI NtWriteVirtualMemory(HANDLE, void*, const void*, SIZE_T, SIZE_T*);
CLASS_DECL_AQUA NTSTATUS WINAPI NtYieldExecution(void);

CLASS_DECL_AQUA void WINAPI RtlAcquirePebLock(void);
CLASS_DECL_AQUA BYTE WINAPI RtlAcquireResourceExclusive(LPRTL_RWLOCK, BYTE);
CLASS_DECL_AQUA BYTE WINAPI RtlAcquireResourceShared(LPRTL_RWLOCK, BYTE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlActivateActivationContext(DWORD, HANDLE, ULONG_PTR*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAce(PACL, DWORD, DWORD, PACE_HEADER, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAccessAllowedAce(PACL, DWORD, DWORD, PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAccessAllowedAceEx(PACL, DWORD, DWORD, DWORD, PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAccessDeniedAce(PACL, DWORD, DWORD, PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAccessDeniedAceEx(PACL, DWORD, DWORD, DWORD, PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAtomToAtomTable(RTL_ATOM_TABLE, const WCHAR*, RTL_ATOM*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAuditAccessAce(PACL, DWORD, DWORD, PSID, int_bool, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAddAuditAccessAceEx(PACL, DWORD, DWORD, DWORD, PSID, int_bool, int_bool);
CLASS_DECL_AQUA void WINAPI RtlAddRefActivationContext(HANDLE);
CLASS_DECL_AQUA PVOID WINAPI RtlAddVectoredExceptionHandler(WINULONG, PVECTORED_EXCEPTION_HANDLER);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAdjustPrivilege(WINULONG, int_bool, int_bool, PBOOLEAN);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAllocateAndInitializeSid(PSID_IDENTIFIER_AUTHORITY, BYTE, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, PSID *);
CLASS_DECL_AQUA RTL_HANDLE * WINAPI RtlAllocateHandle(RTL_HANDLE_TABLE *, WINULONG *);
#ifndef _UWP
CLASS_DECL_AQUA PVOID WINAPI RtlAllocateHeap(HANDLE, WINULONG, SIZE_T) __WINE_ALLOC_SIZE(3);
#endif
CLASS_DECL_AQUA WCHAR WINAPI RtlAnsiCharToUnicodeChar(LPSTR *);
CLASS_DECL_AQUA DWORD WINAPI RtlAnsiStringToUnicodeSize(const STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAnsiStringToUnicodeString(PUNICODE_STRING, PCANSI_STRING, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAppendAsciizToString(STRING *, LPCSTR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAppendStringToString(STRING *, const STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAppendUnicodeStringToString(UNICODE_STRING *, const UNICODE_STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlAppendUnicodeToString(UNICODE_STRING *, LPCWSTR);
CLASS_DECL_AQUA int_bool WINAPI RtlAreAllAccessesGranted(ACCESS_MASK, ACCESS_MASK);
CLASS_DECL_AQUA int_bool WINAPI RtlAreAnyAccessesGranted(ACCESS_MASK, ACCESS_MASK);
CLASS_DECL_AQUA int_bool WINAPI RtlAreBitsSet(PCRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA int_bool WINAPI RtlAreBitsClear(PCRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCharToInteger(PCSZ, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCheckRegistryKey(WINULONG, PWSTR);
CLASS_DECL_AQUA void WINAPI RtlClearAllBits(PRTL_BITMAP);
CLASS_DECL_AQUA void WINAPI RtlClearBits(PRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateActivationContext(HANDLE*, const void*);
CLASS_DECL_AQUA PDEBUG_BUFFER WINAPI RtlCreateQueryDebugBuffer(WINULONG, int_bool);
CLASS_DECL_AQUA WINULONG WINAPI RtlCompactHeap(HANDLE, WINULONG);
CLASS_DECL_AQUA LONG WINAPI RtlCompareString(const STRING*, const STRING*, int_bool);
CLASS_DECL_AQUA LONG WINAPI RtlCompareUnicodeString(const UNICODE_STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCompressBuffer(WINUSHORT, PWINUCHAR, WINULONG, PWINUCHAR, WINULONG, WINULONG, PWINULONG, PVOID);
CLASS_DECL_AQUA DWORD WINAPI RtlComputeCrc32(DWORD, const BYTE*, INT);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlConvertSidToUnicodeString(PUNICODE_STRING, PSID, int_bool);
CLASS_DECL_AQUA void WINAPI RtlCopyLuid(PLUID, const LUID*);
//    CLASS_DECL_AQUA void WINAPI RtlCopyLuidAndAttributesArray(WINULONG, const LUID_AND_ATTRIBUTES*, PLUID_AND_ATTRIBUTES);
CLASS_DECL_AQUA int_bool WINAPI RtlCopySid(DWORD, PSID, PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCopySecurityDescriptor(PSECURITY_DESCRIPTOR, PSECURITY_DESCRIPTOR);
CLASS_DECL_AQUA void WINAPI RtlCopyString(STRING*, const STRING*);
CLASS_DECL_AQUA void WINAPI RtlCopyUnicodeString(UNICODE_STRING*, const UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateAcl(PACL, DWORD, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateAtomTable(WINULONG, RTL_ATOM_TABLE*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateEnvironment(int_bool, PWSTR*);
CLASS_DECL_AQUA HANDLE WINAPI RtlCreateHeap(WINULONG, PVOID, SIZE_T, SIZE_T, PVOID, PRTL_HEAP_DEFINITION);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateProcessParameters(RTL_USER_PROCESS_PARAMETERS**, const UNICODE_STRING*, const UNICODE_STRING*, const UNICODE_STRING*, const UNICODE_STRING*, PWSTR, const UNICODE_STRING*, const UNICODE_STRING*, const UNICODE_STRING*, const UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateSecurityDescriptor(PSECURITY_DESCRIPTOR, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateTimerQueue(PHANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateTimer(PHANDLE, HANDLE, RTL_WAITORTIMERCALLBACKFUNC, PVOID, DWORD, DWORD, WINULONG);
CLASS_DECL_AQUA int_bool WINAPI RtlCreateUnicodeString(PUNICODE_STRING, LPCWSTR);
CLASS_DECL_AQUA int_bool WINAPI RtlCreateUnicodeStringFromAsciiz(PUNICODE_STRING, LPCSTR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlCreateUserThread(HANDLE, const SECURITY_DESCRIPTOR*, int_bool, PVOID, SIZE_T, SIZE_T, PRTL_THREAD_START_ROUTINE, void*, HANDLE*, CLIENT_ID*);
CLASS_DECL_AQUA void WINAPI RtlDeactivateActivationContext(DWORD, ULONG_PTR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDecompressBuffer(WINUSHORT, PWINUCHAR, WINULONG, PWINUCHAR, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteAce(PACL, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteAtomFromAtomTable(RTL_ATOM_TABLE, RTL_ATOM);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteCriticalSection(RTL_CRITICAL_SECTION *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteRegistryValue(WINULONG, PCWSTR, PCWSTR);
CLASS_DECL_AQUA void WINAPI RtlDeleteResource(LPRTL_RWLOCK);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteSecurityObject(PSECURITY_DESCRIPTOR*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteTimer(HANDLE, HANDLE, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeleteTimerQueueEx(HANDLE, HANDLE);
CLASS_DECL_AQUA PRTL_USER_PROCESS_PARAMETERS WINAPI RtlDeNormalizeProcessParams(RTL_USER_PROCESS_PARAMETERS*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeregisterWait(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDeregisterWaitEx(HANDLE, HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDestroyAtomTable(RTL_ATOM_TABLE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDestroyEnvironment(PWSTR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDestroyHandleTable(RTL_HANDLE_TABLE *);
CLASS_DECL_AQUA HANDLE WINAPI RtlDestroyHeap(HANDLE);
CLASS_DECL_AQUA void WINAPI RtlDestroyProcessParameters(RTL_USER_PROCESS_PARAMETERS*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDestroyQueryDebugBuffer(PDEBUG_BUFFER);
CLASS_DECL_AQUA DOS_PATHNAME_TYPE WINAPI RtlDetermineDosPathNameType_U(PCWSTR);
CLASS_DECL_AQUA int_bool WINAPI RtlDllShutdownInProgress(void);
CLASS_DECL_AQUA int_bool WINAPI RtlDoesFileExists_U(LPCWSTR);
CLASS_DECL_AQUA int_bool WINAPI RtlDosPathNameToNtPathName_U(PCWSTR, PUNICODE_STRING, PWSTR*, CURDIR*);
CLASS_DECL_AQUA WINULONG WINAPI RtlDosSearchPath_U(LPCWSTR, LPCWSTR, LPCWSTR, WINULONG, LPWSTR, LPWSTR*);
CLASS_DECL_AQUA WCHAR WINAPI RtlDowncaseUnicodeChar(WCHAR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDowncaseUnicodeString(UNICODE_STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA void WINAPI RtlDumpResource(LPRTL_RWLOCK);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlDuplicateUnicodeString(i32, const UNICODE_STRING*, UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlEmptyAtomTable(RTL_ATOM_TABLE, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlEnterCriticalSection(RTL_CRITICAL_SECTION *);
CLASS_DECL_AQUA void WINAPI RtlEraseUnicodeString(UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlEqualComputerName(const UNICODE_STRING*, const UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlEqualDomainName(const UNICODE_STRING*, const UNICODE_STRING*);
CLASS_DECL_AQUA int_bool WINAPI RtlEqualLuid(const LUID*, const LUID*);
CLASS_DECL_AQUA int_bool WINAPI RtlEqualPrefixSid(PSID, PSID);
CLASS_DECL_AQUA int_bool WINAPI RtlEqualSid(PSID, PSID);
CLASS_DECL_AQUA int_bool WINAPI RtlEqualString(const STRING*, const STRING*, int_bool);
CLASS_DECL_AQUA int_bool WINAPI RtlEqualUnicodeString(const UNICODE_STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA void DECLSPEC_NORETURN WINAPI RtlExitUserThread(WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlExpandEnvironmentStrings_U(PCWSTR, const UNICODE_STRING*, UNICODE_STRING*, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlFindActivationContextSectionString(WINULONG, const GUID*, WINULONG, const UNICODE_STRING*, PVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlFindCharInUnicodeString(i32, const UNICODE_STRING*, const UNICODE_STRING*, WINUSHORT*);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindClearBits(PCRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindClearBitsAndSet(PRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindClearRuns(PCRTL_BITMAP, PRTL_BITMAP_RUN, WINULONG, int_bool);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindLastBackwardRunSet(PCRTL_BITMAP, WINULONG, PWINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindLastBackwardRunClear(PCRTL_BITMAP, WINULONG, PWINULONG);
CLASS_DECL_AQUA CCHAR WINAPI RtlFindLeastSignificantBit(ULONGLONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindLongestRunSet(PCRTL_BITMAP, PWINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindLongestRunClear(PCRTL_BITMAP, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlFindMessage(HMODULE, WINULONG, WINULONG, WINULONG, const MESSAGE_RESOURCE_ENTRY**);
CLASS_DECL_AQUA CCHAR WINAPI RtlFindMostSignificantBit(ULONGLONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindNextForwardRunSet(PCRTL_BITMAP, WINULONG, PWINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindNextForwardRunClear(PCRTL_BITMAP, WINULONG, PWINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindSetBits(PCRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindSetBitsAndClear(PRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlFindSetRuns(PCRTL_BITMAP, PRTL_BITMAP_RUN, WINULONG, int_bool);
CLASS_DECL_AQUA int_bool WINAPI RtlFirstFreeAce(PACL, PACE_HEADER *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlFormatCurrentUserKeyPath(PUNICODE_STRING);
//CLASS_DECL_AQUA  NTSTATUS  WINAPI RtlFormatMessage(LPWSTR,WINUCHAR,int_bool,int_bool,int_bool,__ms_va_list *,LPWSTR,WINULONG);
CLASS_DECL_AQUA void WINAPI RtlFreeAnsiString(PANSI_STRING);
CLASS_DECL_AQUA int_bool WINAPI RtlFreeHandle(RTL_HANDLE_TABLE *, RTL_HANDLE *);
CLASS_DECL_AQUA int_bool WINAPI RtlFreeHeap(HANDLE, WINULONG, PVOID);
CLASS_DECL_AQUA void WINAPI RtlFreeOemString(POEM_STRING);
CLASS_DECL_AQUA DWORD WINAPI RtlFreeSid(PSID);
CLASS_DECL_AQUA void WINAPI RtlFreeThreadActivationContextStack(void);
CLASS_DECL_AQUA void WINAPI RtlFreeUnicodeString(PUNICODE_STRING);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetAce(PACL, DWORD, LPVOID *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetActiveActivationContext(HANDLE*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetCompressionWorkSpaceSize(WINUSHORT, PWINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetControlSecurityDescriptor(PSECURITY_DESCRIPTOR, PSECURITY_DESCRIPTOR_CONTROL, LPDWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetCurrentDirectory_U(WINULONG, LPWSTR);
CLASS_DECL_AQUA PEB * WINAPI RtlGetCurrentPeb(void);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetDaclSecurityDescriptor(PSECURITY_DESCRIPTOR, PBOOLEAN, PACL *, PBOOLEAN);
CLASS_DECL_AQUA WINULONG WINAPI RtlGetFullPathName_U(PCWSTR, WINULONG, PWSTR, PWSTR*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetGroupSecurityDescriptor(PSECURITY_DESCRIPTOR, PSID *, PBOOLEAN);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetLastNtStatus(void);
CLASS_DECL_AQUA DWORD WINAPI RtlGetLastWin32Error(void);
CLASS_DECL_AQUA DWORD WINAPI RtlGetLongestNtPathLength(void);
CLASS_DECL_AQUA WINULONG WINAPI RtlGetNtGlobalFlags(void);
CLASS_DECL_AQUA int_bool WINAPI RtlGetNtProductType(LPDWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetOwnerSecurityDescriptor(PSECURITY_DESCRIPTOR, PSID *, PBOOLEAN);
CLASS_DECL_AQUA WINULONG WINAPI RtlGetProcessHeaps(WINULONG, HANDLE*);
CLASS_DECL_AQUA DWORD WINAPI RtlGetThreadErrorMode(void);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetSaclSecurityDescriptor(PSECURITY_DESCRIPTOR, PBOOLEAN, PACL *, PBOOLEAN);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGetVersion(RTL_OSVERSIONINFOEXW*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlGUIDFromString(PUNICODE_STRING, GUID*);
CLASS_DECL_AQUA PSID_IDENTIFIER_AUTHORITY WINAPI RtlIdentifierAuthoritySid(PSID);
CLASS_DECL_AQUA PVOID WINAPI RtlImageDirectoryEntryToData(HMODULE, int_bool, WORD, WINULONG *);
CLASS_DECL_AQUA PIMAGE_NT_HEADERS WINAPI RtlImageNtHeader(HMODULE);
CLASS_DECL_AQUA PIMAGE_SECTION_HEADER WINAPI RtlImageRvaToSection(const IMAGE_NT_HEADERS *, HMODULE, DWORD);
CLASS_DECL_AQUA PVOID WINAPI RtlImageRvaToVa(const IMAGE_NT_HEADERS *, HMODULE, DWORD, IMAGE_SECTION_HEADER **);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlImpersonateSelf(SECURITY_IMPERSONATION_LEVEL);
CLASS_DECL_AQUA void WINAPI RtlInitString(PSTRING, PCSZ);
CLASS_DECL_AQUA void WINAPI RtlInitAnsiString(PANSI_STRING, PCSZ);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlInitAnsiStringEx(PANSI_STRING, PCSZ);
CLASS_DECL_AQUA void WINAPI RtlInitUnicodeString(PUNICODE_STRING, PCWSTR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlInitUnicodeStringEx(PUNICODE_STRING, PCWSTR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlInitializeCriticalSection(RTL_CRITICAL_SECTION *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlInitializeCriticalSectionAndSpinCount(RTL_CRITICAL_SECTION *, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlInitializeCriticalSectionEx(RTL_CRITICAL_SECTION *, WINULONG, WINULONG);
CLASS_DECL_AQUA void WINAPI RtlInitializeBitMap(PRTL_BITMAP, PWINULONG, WINULONG);
CLASS_DECL_AQUA void WINAPI RtlInitializeHandleTable(WINULONG, WINULONG, RTL_HANDLE_TABLE *);
CLASS_DECL_AQUA void WINAPI RtlInitializeResource(LPRTL_RWLOCK);
CLASS_DECL_AQUA int_bool WINAPI RtlInitializeSid(PSID, PSID_IDENTIFIER_AUTHORITY, BYTE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlInt64ToUnicodeString(ULONGLONG, WINULONG, UNICODE_STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlIntegerToChar(WINULONG, WINULONG, WINULONG, PCHAR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlIntegerToUnicodeString(WINULONG, WINULONG, UNICODE_STRING *);
CLASS_DECL_AQUA int_bool WINAPI RtlIsActivationContextActive(HANDLE);
CLASS_DECL_AQUA WINULONG WINAPI RtlIsDosDeviceName_U(PCWSTR);
CLASS_DECL_AQUA int_bool WINAPI RtlIsNameLegalDOS8Dot3(const UNICODE_STRING*, POEM_STRING, PBOOLEAN);
CLASS_DECL_AQUA int_bool WINAPI RtlIsTextUnicode(LPCVOID, INT, INT *);
CLASS_DECL_AQUA int_bool WINAPI RtlIsValidHandle(const RTL_HANDLE_TABLE *, const RTL_HANDLE *);
CLASS_DECL_AQUA int_bool WINAPI RtlIsValidIndexHandle(const RTL_HANDLE_TABLE *, WINULONG Index, RTL_HANDLE **);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlLeaveCriticalSection(RTL_CRITICAL_SECTION *);
CLASS_DECL_AQUA DWORD WINAPI RtlLengthRequiredSid(DWORD);
CLASS_DECL_AQUA WINULONG WINAPI RtlLengthSecurityDescriptor(PSECURITY_DESCRIPTOR);
CLASS_DECL_AQUA DWORD WINAPI RtlLengthSid(PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlLocalTimeToSystemTime(const LARGE_INTEGER*, PLARGE_INTEGER);
CLASS_DECL_AQUA int_bool WINAPI RtlLockHeap(HANDLE);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlLookupAtomInAtomTable(RTL_ATOM_TABLE, const WCHAR*, RTL_ATOM*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlMakeSelfRelativeSD(PSECURITY_DESCRIPTOR, PSECURITY_DESCRIPTOR, LPDWORD);
CLASS_DECL_AQUA void WINAPI RtlMapGenericMask(PACCESS_MASK, const GENERIC_MAPPING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlMultiByteToUnicodeN(LPWSTR, DWORD, LPDWORD, LPCSTR, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlMultiByteToUnicodeSize(DWORD*, LPCSTR, UINT);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlNewSecurityObject(PSECURITY_DESCRIPTOR, PSECURITY_DESCRIPTOR, PSECURITY_DESCRIPTOR*, int_bool, HANDLE, PGENERIC_MAPPING);
CLASS_DECL_AQUA PRTL_USER_PROCESS_PARAMETERS WINAPI RtlNormalizeProcessParams(RTL_USER_PROCESS_PARAMETERS*);
CLASS_DECL_AQUA WINULONG WINAPI RtlNtStatusToDosError(NTSTATUS);
CLASS_DECL_AQUA WINULONG WINAPI RtlNtStatusToDosErrorNoTeb(NTSTATUS);
CLASS_DECL_AQUA WINULONG WINAPI RtlNumberOfSetBits(PCRTL_BITMAP);
CLASS_DECL_AQUA WINULONG WINAPI RtlNumberOfClearBits(PCRTL_BITMAP);
CLASS_DECL_AQUA UINT WINAPI RtlOemStringToUnicodeSize(const STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlOemStringToUnicodeString(UNICODE_STRING*, const STRING*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlOemToUnicodeN(LPWSTR, DWORD, LPDWORD, LPCSTR, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlOpenCurrentUser(ACCESS_MASK, PHANDLE);
#ifndef _UWP
CLASS_DECL_AQUA PVOID WINAPI RtlPcToFileHeader(PVOID, PVOID*);
#endif
CLASS_DECL_AQUA NTSTATUS WINAPI RtlPinAtomInAtomTable(RTL_ATOM_TABLE, RTL_ATOM);
CLASS_DECL_AQUA int_bool WINAPI RtlPrefixString(const STRING*, const STRING*, int_bool);
CLASS_DECL_AQUA int_bool WINAPI RtlPrefixUnicodeString(const UNICODE_STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryAtomInAtomTable(RTL_ATOM_TABLE, RTL_ATOM, WINULONG*, WINULONG*, WCHAR*, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryEnvironmentVariable_U(PWSTR, PUNICODE_STRING, PUNICODE_STRING);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryHeapInformation(HANDLE, HEAP_INFORMATION_CLASS, PVOID, SIZE_T, PSIZE_T);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryInformationAcl(PACL, LPVOID, DWORD, ACL_INFORMATION_CLASS);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryInformationActivationContext(WINULONG, HANDLE, PVOID, WINULONG, PVOID, SIZE_T, SIZE_T*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryProcessDebugInformation(WINULONG, WINULONG, PDEBUG_BUFFER);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryRegistryValues(WINULONG, PCWSTR, PRTL_QUERY_REGISTRY_TABLE, PVOID, PVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueryTimeZoneInformation(RTL_TIME_ZONE_INFORMATION*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlQueueWorkItem(PRTL_WORK_ITEM_ROUTINE, PVOID, WINULONG);
CLASS_DECL_AQUA void WINAPI RtlRaiseException(PEXCEPTION_RECORD);
CLASS_DECL_AQUA void WINAPI RtlRaiseStatus(NTSTATUS);
CLASS_DECL_AQUA WINULONG WINAPI RtlRandom(PWINULONG);
CLASS_DECL_AQUA PVOID WINAPI RtlReAllocateHeap(HANDLE, WINULONG, PVOID, SIZE_T);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlRegisterWait(PHANDLE, HANDLE, RTL_WAITORTIMERCALLBACKFUNC, PVOID, WINULONG, WINULONG);
CLASS_DECL_AQUA void WINAPI RtlReleaseActivationContext(HANDLE);
CLASS_DECL_AQUA void WINAPI RtlReleasePebLock(void);
CLASS_DECL_AQUA void WINAPI RtlReleaseResource(LPRTL_RWLOCK);
CLASS_DECL_AQUA WINULONG WINAPI RtlRemoveVectoredExceptionHandler(PVOID);
CLASS_DECL_AQUA void WINAPI RtlRestoreLastWin32Error(DWORD);
CLASS_DECL_AQUA void WINAPI RtlSecondsSince1970ToTime(DWORD, LARGE_INTEGER *);
CLASS_DECL_AQUA void WINAPI RtlSecondsSince1980ToTime(DWORD, LARGE_INTEGER *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSelfRelativeToAbsoluteSD(PSECURITY_DESCRIPTOR, PSECURITY_DESCRIPTOR, PDWORD, PACL, PDWORD, PACL, PDWORD, PSID, PDWORD, PSID, PDWORD);
CLASS_DECL_AQUA void WINAPI RtlSetAllBits(PRTL_BITMAP);
CLASS_DECL_AQUA void WINAPI RtlSetBits(PRTL_BITMAP, WINULONG, WINULONG);
CLASS_DECL_AQUA WINULONG WINAPI RtlSetCriticalSectionSpinCount(RTL_CRITICAL_SECTION*, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetControlSecurityDescriptor(PSECURITY_DESCRIPTOR, SECURITY_DESCRIPTOR_CONTROL, SECURITY_DESCRIPTOR_CONTROL);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetCurrentDirectory_U(const UNICODE_STRING*);
CLASS_DECL_AQUA void WINAPI RtlSetCurrentEnvironment(PWSTR, PWSTR*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetDaclSecurityDescriptor(PSECURITY_DESCRIPTOR, int_bool, PACL, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetEnvironmentVariable(PWSTR*, PUNICODE_STRING, PUNICODE_STRING);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetOwnerSecurityDescriptor(PSECURITY_DESCRIPTOR, PSID, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetGroupSecurityDescriptor(PSECURITY_DESCRIPTOR, PSID, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetIoCompletionCallback(HANDLE, PRTL_OVERLAPPED_COMPLETION_ROUTINE, WINULONG);
CLASS_DECL_AQUA void WINAPI RtlSetLastWin32Error(DWORD);
CLASS_DECL_AQUA void WINAPI RtlSetLastWin32ErrorAndNtStatusFromNtStatus(NTSTATUS);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetSaclSecurityDescriptor(PSECURITY_DESCRIPTOR, int_bool, PACL, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetThreadErrorMode(DWORD, LPDWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSetTimeZoneInformation(const RTL_TIME_ZONE_INFORMATION*);
CLASS_DECL_AQUA SIZE_T WINAPI RtlSizeHeap(HANDLE, WINULONG, const void*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlStringFromGUID(REFGUID, PUNICODE_STRING);
CLASS_DECL_AQUA LPDWORD WINAPI RtlSubAuthoritySid(PSID, DWORD);
CLASS_DECL_AQUA byte * WINAPI RtlSubAuthorityCountSid(PSID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlSystemTimeToLocalTime(const LARGE_INTEGER*, PLARGE_INTEGER);
CLASS_DECL_AQUA void WINAPI RtlTimeToTimeFields(const LARGE_INTEGER*, PTIME_FIELDS);
CLASS_DECL_AQUA int_bool WINAPI RtlTimeFieldsToTime(PTIME_FIELDS, PLARGE_INTEGER);
CLASS_DECL_AQUA void WINAPI RtlTimeToElapsedTimeFields(const LARGE_INTEGER *, PTIME_FIELDS);
CLASS_DECL_AQUA int_bool WINAPI RtlTimeToSecondsSince1970(const LARGE_INTEGER *, LPDWORD);
CLASS_DECL_AQUA int_bool WINAPI RtlTimeToSecondsSince1980(const LARGE_INTEGER *, LPDWORD);
CLASS_DECL_AQUA int_bool WINAPI RtlTryEnterCriticalSection(RTL_CRITICAL_SECTION *);
CLASS_DECL_AQUA ULONGLONG __cdecl RtlUlonglongByteSwap(ULONGLONG);
CLASS_DECL_AQUA DWORD WINAPI RtlUnicodeStringToAnsiSize(const UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUnicodeStringToAnsiString(PANSI_STRING, PCUNICODE_STRING, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUnicodeStringToInteger(const UNICODE_STRING *, WINULONG, WINULONG *);
CLASS_DECL_AQUA DWORD WINAPI RtlUnicodeStringToOemSize(const UNICODE_STRING*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUnicodeStringToOemString(POEM_STRING, PCUNICODE_STRING, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUnicodeToMultiByteN(LPSTR, DWORD, LPDWORD, LPCWSTR, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUnicodeToMultiByteSize(PWINULONG, PCWSTR, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUnicodeToOemN(LPSTR, DWORD, LPDWORD, LPCWSTR, DWORD);
CLASS_DECL_AQUA WINULONG WINAPI RtlUniform(PWINULONG);
CLASS_DECL_AQUA int_bool WINAPI RtlUnlockHeap(HANDLE);
NTSYSAPI void WINAPI RtlUnwind(PVOID, PVOID, PEXCEPTION_RECORD, PVOID);
#ifdef __x86_64__
CLASS_DECL_AQUA void WINAPI RtlUnwindEx(PVOID, PVOID, PEXCEPTION_RECORD, PVOID, PCONTEXT, PUNWIND_HISTORY_TABLE);
#elif defined(__ia64__)
CLASS_DECL_AQUA void WINAPI RtlUnwind2(FRAME_POINTERS, PVOID, PEXCEPTION_RECORD, PVOID, PCONTEXT);
CLASS_DECL_AQUA void WINAPI RtlUnwindEx(FRAME_POINTERS, PVOID, PEXCEPTION_RECORD, PVOID, PCONTEXT, PUNWIND_HISTORY_TABLE);
#endif
CLASS_DECL_AQUA WCHAR WINAPI RtlUpcaseUnicodeChar(WCHAR);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpcaseUnicodeString(UNICODE_STRING*, const UNICODE_STRING *, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpcaseUnicodeStringToAnsiString(STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpcaseUnicodeStringToCountedOemString(STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpcaseUnicodeStringToOemString(STRING*, const UNICODE_STRING*, int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpcaseUnicodeToMultiByteN(LPSTR, DWORD, LPDWORD, LPCWSTR, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpcaseUnicodeToOemN(LPSTR, DWORD, LPDWORD, LPCWSTR, DWORD);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlUpdateTimer(HANDLE, HANDLE, DWORD, DWORD);
CLASS_DECL_AQUA CHAR WINAPI RtlUpperChar(CHAR);
CLASS_DECL_AQUA void WINAPI RtlUpperString(STRING *, const STRING *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlValidSecurityDescriptor(PSECURITY_DESCRIPTOR);
CLASS_DECL_AQUA int_bool WINAPI RtlValidAcl(PACL);
CLASS_DECL_AQUA int_bool WINAPI RtlValidSid(PSID);
CLASS_DECL_AQUA int_bool WINAPI RtlValidateHeap(HANDLE, WINULONG, LPCVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlVerifyVersionInfo(const RTL_OSVERSIONINFOEXW*, DWORD, DWORDLONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlWalkHeap(HANDLE, PVOID);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlWow64EnableFsRedirection(int_bool);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlWow64EnableFsRedirectionEx(WINULONG, WINULONG*);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlWriteRegistryValue(WINULONG, PCWSTR, PCWSTR, WINULONG, PVOID, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlpNtCreateKey(PHANDLE, ACCESS_MASK, const OBJECT_ATTRIBUTES*, WINULONG, const UNICODE_STRING*, WINULONG, PWINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlpNtEnumerateSubKey(HANDLE, UNICODE_STRING *, WINULONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlpWaitForCriticalSection(RTL_CRITICAL_SECTION *);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlpUnWaitCriticalSection(RTL_CRITICAL_SECTION *);
//CLASS_DECL_AQUA  NTSTATUS  WINAPI vDbgPrintEx(WINULONG,WINULONG,LPCSTR,__ms_va_list);
//CLASS_DECL_AQUA  NTSTATUS  WINAPI vDbgPrintExWithPrefix(LPCSTR,WINULONG,WINULONG,LPCSTR,__ms_va_list);

/* 32-bit only functions */

#ifndef _WIN64
CLASS_DECL_AQUA LONGLONG WINAPI RtlConvertLongToLargeInteger(LONG);
CLASS_DECL_AQUA ULONGLONG WINAPI RtlConvertUlongToLargeInteger(WINULONG);
CLASS_DECL_AQUA LONGLONG WINAPI RtlEnlargedIntegerMultiply(INT, INT);
CLASS_DECL_AQUA ULONGLONG WINAPI RtlEnlargedUnsignedMultiply(UINT, UINT);
CLASS_DECL_AQUA UINT WINAPI RtlEnlargedUnsignedDivide(ULONGLONG, UINT, UINT *);
CLASS_DECL_AQUA LONGLONG WINAPI RtlExtendedMagicDivide(LONGLONG, LONGLONG, INT);
CLASS_DECL_AQUA LONGLONG WINAPI RtlExtendedIntegerMultiply(LONGLONG, INT);
CLASS_DECL_AQUA LONGLONG WINAPI RtlExtendedLargeIntegerDivide(LONGLONG, INT, INT *);
CLASS_DECL_AQUA LONGLONG WINAPI RtlLargeIntegerAdd(LONGLONG, LONGLONG);
CLASS_DECL_AQUA LONGLONG WINAPI RtlLargeIntegerArithmeticShift(LONGLONG, INT);
CLASS_DECL_AQUA ULONGLONG WINAPI RtlLargeIntegerDivide(ULONGLONG, ULONGLONG, ULONGLONG *);
CLASS_DECL_AQUA LONGLONG WINAPI RtlLargeIntegerNegate(LONGLONG);
CLASS_DECL_AQUA LONGLONG WINAPI RtlLargeIntegerShiftLeft(LONGLONG, INT);
CLASS_DECL_AQUA LONGLONG WINAPI RtlLargeIntegerShiftRight(LONGLONG, INT);
CLASS_DECL_AQUA LONGLONG WINAPI RtlLargeIntegerSubtract(LONGLONG, LONGLONG);
CLASS_DECL_AQUA NTSTATUS WINAPI RtlLargeIntegerToChar(const ULONGLONG *, WINULONG, WINULONG, PCHAR);
#endif

/* Wine internal functions */

CLASS_DECL_AQUA NTSTATUS CDECL wine_nt_to_unix_file_name(const UNICODE_STRING *nameW, ANSI_STRING *unix_name_ret,
      UINT disposition, int_bool check_case);
CLASS_DECL_AQUA NTSTATUS CDECL wine_unix_to_nt_file_name(const ANSI_STRING *name, UNICODE_STRING *nt);


/***********************************************************************
 * Inline functions
 */

#define InitializeObjectAttributes(p,n,a,r,s) \
    do { \
        (p)->Length = sizeof(OBJECT_ATTRIBUTES); \
        (p)->RootDirectory = r; \
        (p)->Attributes = a; \
        (p)->ObjectName = n; \
        (p)->SecurityDescriptor = s; \
        (p)->SecurityQualityOfService = nullptr; \
    } while (0)

#define NtCurrentProcess() ((HANDLE)-1)

#ifndef _UWP
#define RtlFillMemory(Destination,Length,Fill) __memset((Destination),(Fill),(Length))
#define RtlMoveMemory(Destination,Source,Length) __memmov((Destination),(Source),(Length))
#define RtlZeroMemory(Destination,Length) __memset((Destination),0,(Length))
#endif
#define RtlStoreUlong(p,v)  do { WINULONG _v = (v); ::memcpy_dup((p), &_v, sizeof(_v)); } while (0)
#define RtlStoreUlonglong(p,v) do { ULONGLONG _v = (v); ::memcpy_dup((p), &_v, sizeof(_v)); } while (0)
#define RtlRetrieveUlong(p,s) ::memcpy_dup((p), (s), sizeof(WINULONG))
#define RtlRetrieveUlonglong(p,s) ::memcpy_dup((p), (s), sizeof(ULONGLONG))


#ifndef _UWP

static inline int_bool RtlCheckBit(PCRTL_BITMAP lpBits, WINULONG ulBit)
{
   if (lpBits && ulBit < lpBits->SizeOfBitMap &&
         lpBits->Buffer[ulBit >> 5] & (1 << (ulBit & 31)))
      return TRUE;
   return FALSE;
}

/* These are implemented as __fastcall, so we can't let Winelib apps link with them */
static inline WINUSHORT RtlUshortByteSwap(WINUSHORT s)
{
   return (s >> 8) | (s << 8);
}

static inline WINULONG RtlUlongByteSwap(WINULONG i)
{
#if defined(__i386__) && defined(__GNUC__)
   WINULONG ret;
   __asm__("bswap %0" : "=r" (ret) : "0" (i));
   return ret;
#else
   return ((WINULONG) RtlUshortByteSwap((WINUSHORT) i) << 16) | RtlUshortByteSwap((WINUSHORT) (i >> 16));
#endif
}

#endif

/* list manipulation macros */
#define InitializeListHead(le)  (void)((le)->Flink = (le)->Blink = (le))
#define InsertHeadList(le,e)    do { PLIST_ENTRY f = (le)->Flink; (e)->Flink = f; (e)->Blink = (le); f->Blink = (e); (le)->Flink = (e); } while (0)
#define InsertTailList(le,e)    do { PLIST_ENTRY b = (le)->Blink; (e)->Flink = (le); (e)->Blink = b; b->Flink = (e); (le)->Blink = (e); } while (0)
#define IsListEmpty(le)         ((le)->Flink == (le))
#define RemoveEntryList(e)      do { PLIST_ENTRY f = (e)->Flink, b = (e)->Blink; f->Blink = b; b->Flink = f; (e)->Flink = (e)->Blink = nullptr; } while (0)

#ifndef _UWP

static inline PLIST_ENTRY RemoveHeadList(PLIST_ENTRY le)
{
   PLIST_ENTRY f, b, e;

   e = le->Flink;
   f = le->Flink->Flink;
   b = le->Flink->Blink;
   f->Blink = b;
   b->Flink = f;

   if (e != le) e->Flink = e->Blink = NULL;
   return e;
}

static inline PLIST_ENTRY RemoveTailList(PLIST_ENTRY le)
{
   PLIST_ENTRY f, b, e;

   e = le->Blink;
   f = le->Blink->Flink;
   b = le->Blink->Blink;
   f->Blink = b;
   b->Flink = f;

   if (e != le) e->Flink = e->Blink = NULL;
   return e;
}

#endif

#ifdef __WINESRC__

/* FIXME: private structure for vm86 mode, stored in teb->GdiTebBatch */
typedef struct
{
   DWORD dpmi_vif;
   DWORD vm86_pending;
} WINE_VM86_TEB_INFO;

static inline WINE_VM86_TEB_INFO *get_vm86_teb_info(void)
{
   return (WINE_VM86_TEB_INFO *)&NtCurrentTeb()->GdiTebBatch;
}

/* The thread information for 16-bit threads */

/* NtCurrentTeb()->SubSystemTib points to this */
typedef struct
{
   void *unknown; /* 00 unknown */
   UNICODE_STRING *exe_name; /* 04 exe module name */

   /* the following fields do not exist under Windows */
   UNICODE_STRING exe_str; /* exe name string pointed to by exe_name */
   CURDIR curdir; /* current directory */
   WCHAR curdir_buffer[MAX_PATH];
} WIN16_SUBSYSTEM_TIB;

#endif /* __WINESRC__ */

#ifdef __cplusplus
} /* extern "C" */
#endif /* defined(__cplusplus) */


#endif // OPERATIONAL_SYSTEM_CROSS_WIN_WINDOWS_INTERNALS_H




