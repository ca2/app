// Refactor by camilo from gz on 2021-11-10 11:09 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "compress.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/prototype/prototype/memory.h"
#include <zlib.h>


//#define ALLOC(size) malloc(size)
//#define TRYFREE(point) {if (point) free(point);}
//#define Z_BUFSIZE 4096
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */


typedef  uchar GZIP;
typedef  GZIP* LPGZIP;


//static const int gz_magic[2] = {0x1f, 0x8b}; /* gzip_stream magic header */


namespace compress_zlib
{


   compress::compress()
   {

      m_iLevel = 1;

   }


   compress::~compress()
   {


   }


   void compress::set_level(int iLevel)
   {

      m_iLevel = iLevel;

      //return ::success;

   }


   void compress::transfer(::file::file* pfileOut, ::file::file* pfileIn, transfer_progress_function transferprogressfunction)
   {

      int iLevel = m_iLevel;

      if (iLevel < 0)
      {

         iLevel = 0;

      }
      else if (iLevel > 9)
      {

         iLevel = 9;

      }

      filesize size = 0;

      if (pfileIn->is_seekable())
      {

         size = pfileIn->size();

      }

      int status;

      class memory memIn;

      memIn.set_size((memsize)maximum(1024, minimum(pfileIn->right_size(), 1024 * 64)));

      i64 uRead = pfileIn->read(memIn);

      z_stream zstream;

      zero(zstream);

      zstream.next_in = (unsigned char*)memIn.data();
      zstream.avail_in = (unsigned int)uRead;
      zstream.total_out = 0;
      zstream.zalloc = Z_NULL;
      zstream.zfree = Z_NULL;

      class memory memory;

      memory.set_size(1024 * 256);

      ASSERT(memory.size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (deflateInit2(&zstream, iLevel, Z_DEFLATED, 16 + MAX_WBITS, 9, Z_DEFAULT_STRATEGY) != Z_OK)
      {

         throw ::exception(error_failed);

      }

      // use deflateSetHeader to set original file params

      int iFlush = Z_NO_FLUSH;

      while (true)
      {

         do
         {

            zstream.next_out = memory.data();

            zstream.avail_out = (unsigned int)memory.size();

            // Inflate another chunk.
            status = deflate(&zstream, iFlush);

            auto amountToWrite = (unsigned int)memory.size() - zstream.avail_out;

            pfileOut->write(memory.data(), amountToWrite);

            if (transferprogressfunction)
            {

               if (pfileOut->size() < size)
               {

                  transferprogressfunction((double)pfileOut->size()
                     / (double)size, pfileOut->size(), size);

               }
               else
               {

                  transferprogressfunction(0, pfileOut->size(), 0);

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

         } while (zstream.avail_out == 0 || zstream.avail_in > 0);

         uRead = pfileIn->read(memIn);

         if (uRead == 0)
         {

            iFlush = Z_FINISH;

            zstream.next_in = (unsigned char*) nullptr;

            zstream.avail_in = (unsigned int)0;

         }
         else
         {

            zstream.next_in = (unsigned char*)memIn.data();

            zstream.avail_in = (unsigned int)uRead;

         }

      }

   stop1:

      status = deflateEnd(&zstream);

      //return status >= 0 ? ::success : error_failed;

      if (status < 0)
      {

         throw ::exception(error_failed);

      }

   }


   unsigned int compress::crc32(unsigned int uCrc, const ::block& block)
   {

      return (unsigned int)::crc32(uCrc, (const Bytef *) block.data(), (uInt) block.size());

   }


} // namespace compress_zlib



