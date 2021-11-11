// Refactor by camilo from gz on 2021-11-10 11:09 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
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


   ::e_status compress::set_level(int iLevel)
   {

      m_iLevel = iLevel;

      return ::success;

   }


   ::e_status compress::transfer(::file::file* pfileOut, ::file::file* pfileIn)
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

      i64 uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

      z_stream zstream;

      __zero(zstream);

      zstream.next_in = (u8*)memIn.get_data();
      zstream.avail_in = (u32)uRead;
      zstream.total_out = 0;
      zstream.zalloc = Z_NULL;
      zstream.zfree = Z_NULL;

      class memory memory;
      memory.set_size(1024 * 256);
      ASSERT(memory.get_size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (deflateInit2(&zstream, iLevel, Z_DEFLATED, 16 + MAX_WBITS, 9, Z_DEFAULT_STRATEGY) != Z_OK)
      {

         return error_failed;

      }

      // use deflateSetHeader to set original file params

      int iFlush = Z_NO_FLUSH;

      while (true)
      {

         do
         {

            zstream.next_out = memory.get_data();

            zstream.avail_out = (u32)memory.get_size();

            // Inflate another chunk.
            status = deflate(&zstream, iFlush);

            pfileOut->write(memory.get_data(), (u32)memory.get_size() - zstream.avail_out);

            if (status == Z_STREAM_END)
            {

               goto stop1;

            }
            else if (status != Z_OK)
            {

               goto stop1;

            }

         } while (zstream.avail_out == 0 || zstream.avail_in > 0);

         uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

         if (uRead == 0)
         {

            iFlush = Z_FINISH;

            zstream.next_in = (u8*) nullptr;

            zstream.avail_in = (u32)0;

         }
         else
         {

            zstream.next_in = (u8*)memIn.get_data();

            zstream.avail_in = (u32)uRead;

         }

      }

   stop1:

      status = deflateEnd(&zstream);

      return status >= 0 ? ::success : error_failed;

   }


} // namespace compress_zlib



