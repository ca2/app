#pragma once


namespace file
{
  

   inline path::path(const path & path) :
      string((const string &) path),
      path_meta(path)
   {

   }


   inline path::path(const path_object& path) :
      ::file::path((const ::file::path &) path)
   {

   }


} // namespace file


inline void __exchange(::payload_stream & stream, ::file::path_array & array)
{

   __exchange_array(stream, array);

}



