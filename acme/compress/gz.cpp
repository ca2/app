#include "framework.h"
#include "zlib.h"
#include "gz.h"


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


compress_gz::compress_gz(int iLevel) 
{

   m_iLevel = iLevel;

}

compress_gz::~compress_gz()
{
}


bool compress_gz::transfer(::file::file* pfileOut, ::file::file* pfileIn)
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
   memIn.set_size((memsize)max(1024, min(pfileIn->get_left(), 1024 * 64)));

   i64 uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

   z_stream zstream;
   __zero(zstream);
   zstream.next_in = (u8 *)memIn.get_data();
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
      return false;
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

      }
      while (zstream.avail_out == 0 || zstream.avail_in > 0);

      uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

      if (uRead == 0)
      {

         iFlush = Z_FINISH;

         zstream.next_in = (u8 *) nullptr;

         zstream.avail_in = (u32)0;

      }
      else
      {

         zstream.next_in = (u8 *)memIn.get_data();

         zstream.avail_in = (u32)uRead;

      }

   }

stop1:

   status = deflateEnd(&zstream);

   return status >= 0;

}







uncompress_gz::uncompress_gz()
{

}

uncompress_gz::~uncompress_gz()
{
}



bool uncompress_gz::transfer(::file::file * pfileUncompressed, ::file::file * pfileGzFileCompressed)
{

   i32 status;

   class memory memIn;

   memIn.set_size((memsize) min(1024 * 4, pfileGzFileCompressed->get_left()));

   u32 uRead;

   uRead = (u32) (pfileGzFileCompressed->read(memIn.get_data(), memIn.get_size()));

   z_stream zstream;

   __zero(zstream);
   zstream.next_in = (u8 *)memIn.get_data();
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

      return false;

   }

   while (true)
   {

      do
      {

         zstream.next_out = memory.get_data();
         zstream.avail_out = (u32)memory.get_size();

         // Inflate another chunk.
         status = inflate(&zstream, Z_NO_FLUSH);

         pfileUncompressed->write(memory.get_data(), memory.get_size()- zstream.avail_out);

         if (status == Z_STREAM_END)
         {

            goto stop1;

         }
         else if (status != Z_OK)
         {

            goto stop1;

         }

      }
      while (zstream.avail_out == 0 || zstream.avail_in > 0);

      uRead = (u32) (pfileGzFileCompressed->read(memIn.get_data(), memIn.get_size()));

      zstream.next_in = (u8 *)memIn.get_data();

      zstream.avail_in = (u32)uRead;

   }

stop1:

   if (inflateEnd(&zstream) != Z_OK)
   {

      return true;

   }

   return true;

}


//namespace crypto
//{
//
//
//   u32 crypto::crc32(u32 dwPrevious, const char * psz)
//   {
//
//      return (u32) ::crc32(dwPrevious, (const u8 *)psz, (::u32)strlen(psz));
//
//   }
//
//
//} // namespace axis






