// Refactor by camilo from gz on 2021-11-10 11:09 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "uncompress.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/primitive/primitive/memory.h"
#include <zlib.h>


namespace compress_zlib
{


   uncompress::uncompress()
   {


   }


   uncompress::~uncompress()
   {


   }


   void uncompress::transfer(::file::file* pfileUncompressed, ::file::file* pfileGzFileCompressed)
   {

      i32 status;

      class memory memIn;

      memIn.set_size((memsize)minimum(1024 * 4, pfileGzFileCompressed->get_left()));

      u32 uRead;

      uRead = (u32)(pfileGzFileCompressed->read(memIn.get_data(), memIn.get_size()));

      z_stream zstream;

      memset(&zstream, 0, sizeof(zstream));
      zstream.next_in = (u8*)memIn.get_data();
      zstream.avail_in = (u32)uRead;
      zstream.total_out = 0;
      zstream.zalloc = Z_NULL;
      zstream.zfree = Z_NULL;

      class memory memory;

      memory.set_size(1024 * 1024);

      ASSERT(memory.get_size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (inflateInit2(&zstream, 16 + MAX_WBITS) != Z_OK)
      {

         throw ::exception(error_failed);

      }

      while (true)
      {

         do
         {

            zstream.next_out = memory.get_data();
            zstream.avail_out = (u32)memory.get_size();

            // Inflate another chunk.
            status = inflate(&zstream, Z_NO_FLUSH);

            pfileUncompressed->write(memory.get_data(), memory.get_size() - zstream.avail_out);

            if (status == Z_STREAM_END)
            {

               goto stop1;

            }
            else if (status != Z_OK)
            {

               goto stop1;

            }

         } while (zstream.avail_out == 0 || zstream.avail_in > 0);

         uRead = (u32)(pfileGzFileCompressed->read(memIn.get_data(), memIn.get_size()));

         zstream.next_in = (u8*)memIn.get_data();

         zstream.avail_in = (u32)uRead;

      }

   stop1:

      if (inflateEnd(&zstream) != Z_OK)
      {

         //return true;

         return;

      }

      //return true;

      return;

   }


} // namespace compress_zlib



