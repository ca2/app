// Refactor by camilo from gz on 2021-11-10 11:09 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "uncompress.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/prototype/prototype/memory.h"
#include <zlib.h>


namespace compress_zlib
{


   uncompress::uncompress()
   {


   }


   uncompress::~uncompress()
   {


   }


   void uncompress::transfer(::file::file* pfileUncompressed, ::file::file* pfileGzFileCompressed, transfer_progress_function transferprogressfunction)
   {

      int status;

      class memory memIn;

      unsigned int size = 0;

      if (pfileGzFileCompressed->is_seekable())
      {
         auto pos = pfileGzFileCompressed->get_position();
         pfileGzFileCompressed->seek_from_end(-4);

         auto iRead = pfileGzFileCompressed->read(&size, 4);

         if (iRead != 4)
         {

            size = 0;

         }
         pfileGzFileCompressed->set_position(pos);

      }

      memIn.set_size((memsize)minimum(1_MiB, pfileGzFileCompressed->right_size()));

      unsigned int uRead;

      uRead = (unsigned int)(pfileGzFileCompressed->read(memIn));

      z_stream zstream;

      zero(zstream);
      //zstream.next_in = (unsigned char*)memIn.data();
      //zstream.avail_in = (unsigned int)uRead;
      zstream.next_in = (unsigned char*)memIn.data();
      zstream.avail_in = (unsigned int)uRead;
      zstream.total_out = 0;
      zstream.zalloc = Z_NULL;
      zstream.zfree = Z_NULL;

      class memory memory;

      memory.set_size(1024 * 1024);

      ASSERT(memory.size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (inflateInit2(&zstream, 16 + MAX_WBITS) != Z_OK)
      {

         throw ::exception(error_failed);

      }

      while (true)
      {

         do
         {

            zstream.next_out = memory.data();
            zstream.avail_out = (unsigned int)memory.size();

            // Inflate another chunk.
            status = inflate(&zstream, Z_NO_FLUSH);

            pfileUncompressed->write(memory.data(), memory.size() - zstream.avail_out);

            if (transferprogressfunction)
            {

               if (pfileUncompressed->size() <=  size)
               {
                  transferprogressfunction((double)pfileUncompressed->size()
                     / (double)size, pfileUncompressed->size(), size);

               }
               else
               {

                  transferprogressfunction(0, pfileUncompressed->size(), 0);

               }

            }

            if (status == Z_STREAM_END)
            {

               goto stop1;

            }
            else if (status != Z_OK)
            {

               goto stop1;

            }

         //} while (zstream.avail_out == 0 || zstream.avail_in > 0);
         } while (zstream.avail_out == 0);

         uRead = (unsigned int)(pfileGzFileCompressed->read(memIn));

         zstream.next_in = (unsigned char*)memIn.data();

         zstream.avail_in = (unsigned int)uRead;

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



