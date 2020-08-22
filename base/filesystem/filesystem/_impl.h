#pragma once


namespace file
{
  

   inline path::path(const path & path) :
      string(path),
      path_meta(path),
      path_os(path)
   {

   }


   inline path::path(const path_object& path) :
      ::file::path((const ::file::path &) path)
   {

   }


} // namespace file



