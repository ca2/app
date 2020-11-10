#pragma once


CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
CLASS_DECL_CORE ::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, ::u32 dwDesiredAcces, ::u32 dwShareMode, LPSECURITY_ATTRIBUTES lpSA, ::u32 dwCreationDisposition, ::u32 dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_CORE bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);
CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ winrt_get_folder(const string & strFolder);
CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ winrt_get_folder(const string & strFolder, string & strPrefix);
CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ winrt_get_folder(const string & strFolder, string & strPrefix, string & strRelative);

CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ winrt_folder1(string & strPath, string & strPrefix);
CLASS_DECL_CORE ::Windows::Storage::StorageFolder ^ winrt_folder(string & strPath, string & strPrefix);

CLASS_DECL_CORE memsize read_buffer(void* p, ::Windows::Storage::Streams::IBuffer^ ibuf, memsize size = -1, memsize pos = 0);


CLASS_DECL_CORE memory_file_pointer create_memory_file(::Windows::Storage::Streams::IInputStream^ stream);
