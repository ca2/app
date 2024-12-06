// Created by camilo on 2024-12-06 18:44 <3ThomasBorregaardSorensen!!
#pragma once


   windows_path::windows_path() {}
   windows_path::windows_path(const ::file::path& path)
   {

   }

   wstring windows_path::extended_path() const
   {

      ::wstring wstr("L\\\\?\\");

      wstr.append(*this);

      return wstr;

   }

   wstring windows_path::path() const
   {

      return *this;

   }

   windows_path& windows_path::operator = (const ::file::path& path);

};



