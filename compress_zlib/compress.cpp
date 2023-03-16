// Refactor by camilo from gz on 2021-11-10 11:09 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "compress.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/primitive/primitive/memory.h"
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


//static const i32 gz_magic[2] = {0x1f, 0x8b}; /* gzip_stream magic header */


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


   void compress::transfer(::file::file* pfileOut, ::file::file* pfileIn)
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

      i32 status;

      class memory memIn;

      memIn.set_size((memsize)maximum(1024, minimum(pfileIn->get_left(), 1024 * 64)));

      i64 uRead = pfileIn->read(memIn);

      z_stream zstream;

      zero(zstream);

      zstream.next_in = (u8*)memIn.data();
      zstream.avail_in = (u32)uRead;
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

            zstream.avail_out = (u32)memory.size();

            // Inflate another chunk.
            status = deflate(&zstream, iFlush);

            pfileOut->write(memory(0, (u32)memory.size() - zstream.avail_out));

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

            zstream.next_in = (u8*) nullptr;

            zstream.avail_in = (u32)0;

         }
         else
         {

            zstream.next_in = (u8*)memIn.data();

            zstream.avail_in = (u32)uRead;

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


   ::u32 compress::crc32(::u32 uCrc, const ::block& block)
   {

      return (::u32)::crc32(uCrc, (const Bytef *) block.data(), (uInt) block.size());

   }


} // namespace compress_zlib



