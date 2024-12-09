// Created by camilo on 2024-12-06 18:43 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME windows_path :
   protected ::wstring
{
public:

   
   windows_path();
   windows_path(const ::file::path& path);


   wstring extended_path() const;

   wstring path() const;

   windows_path& operator = (const ::file::path& path);


   using ::wstring::clear;
   using ::wstring::is_empty;

protected:
   void normalize_path();
};



