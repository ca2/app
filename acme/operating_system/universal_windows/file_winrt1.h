#pragma once


CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ get_os_folder(const_char_pointer lpcszDirName);
CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFile ^ get_os_file(const_char_pointer lpcszFileName, unsigned int dwDesiredAcces, unsigned int dwShareMode, LPSECURITY_ATTRIBUTES lpSA, unsigned int dwCreationDisposition, unsigned int dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_ACME bool get_file_time(::winrt::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);
CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::scoped_string & scopedstrFolder);
CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::scoped_string & scopedstrFolder, string & strPrefix);
CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ winrt_get_folder(const ::scoped_string & scopedstrFolder, string & strPrefix, string & strRelative);

CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ winrt_folder1(string & strPath, string & strPrefix);
CLASS_DECL_ACME ::winrt::Windows::Storage::StorageFolder ^ winrt_folder(string & strPath, string & strPrefix);

CLASS_DECL_ACME memsize read_buffer(void* p, ::winrt::Windows::Storage::Streams::IBuffer^ ibuf, memsize size = -1, memsize pos = 0);


CLASS_DECL_ACME memory_file_pointer create_memory_file(::winrt::Windows::Storage::Streams::IInputStream^ stream);
