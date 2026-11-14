#pragma once

namespace file
{
   // Optional capability for destinations that import files rather than expose writable streams.
   // Kept separate from enumerator/fs::data to preserve existing provider vtables.
   class folder_importer : virtual public ::particle
   {
   public:
      virtual ::file::path import_file(const ::file::path & destination, const ::file::path & source,
         const ::function<bool(::f64)> & progress) = 0;
   };
}
