﻿#pragma once


CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, ::u32 dwDesiredAcces, ::u32 dwShareMode, LPSECURITY_ATTRIBUTES lpSA, ::u32 dwCreationDisposition, ::u32 dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_APEX bool get_filetime(::winrt::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);
CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::string & strFolder);
CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::string & strFolder, string & strPrefix);
CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::string & strFolder, string & strPrefix, string & strRelative);

CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_folder1(string & strPath, string & strPrefix);
CLASS_DECL_APEX ::winrt::Windows::Storage::StorageFolder ^ winrt_folder(string & strPath, string & strPrefix);

CLASS_DECL_APEX memsize read_buffer(void* p, ::winrt::Windows::Storage::Streams::IBuffer^ ibuf, memsize size = -1, memsize pos = 0);


CLASS_DECL_APEX memory_file_pointer create_memory_file(::winrt::Windows::Storage::Streams::IInputStream^ stream);
