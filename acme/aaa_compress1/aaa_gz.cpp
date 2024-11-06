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

//static const int gz_magic[2] = {0x1f, 0x8b}; /* gzip_stream magic header */


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

   int status;

   class memory memIn;
   memIn.set_size((memsize)maximum(1024, minimum(pfileIn->get_left(), 1024 * 64)));

   huge_integer uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

   z_stream zstream;
   zero(zstream);
   zstream.next_in = (unsigned char *)memIn.get_data();
   zstream.avail_in = (unsigned int)uRead;
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

         zstream.avail_out = (unsigned int)memory.get_size();

         // Inflate another chunk.
         status = deflate(&zstream, iFlush);

         pfileOut->write(memory.get_data(), (unsigned int)memory.get_size() - zstream.avail_out);

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

         zstream.next_in = (unsigned char *) nullptr;

         zstream.avail_in = (unsigned int)0;

      }
      else
      {

         zstream.next_in = (unsigned char *)memIn.get_data();

         zstream.avail_in = (unsigned int)uRead;

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

   int status;

   class memory memIn;

   memIn.set_size((memsize) minimum(1024 * 4, pfileGzFileCompressed->get_left()));

   unsigned int uRead;

   uRead = (unsigned int) (pfileGzFileCompressed->read(memIn.get_data(), memIn.get_size()));

   z_stream zstream;

   zero(zstream);
   zstream.next_in = (unsigned char *)memIn.get_data();
   zstream.avail_in = (unsigned int)uRead;
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
         zstream.avail_out = (unsigned int)memory.get_size();

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

      uRead = (unsigned int) (pfileGzFileCompressed->read(memIn.get_data(), memIn.get_size()));

      zstream.next_in = (unsigned char *)memIn.get_data();

      zstream.avail_in = (unsigned int)uRead;

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
//   unsigned int crypto::crc32(unsigned int dwPrevious, const ::scoped_string & scopedstr)
//   {
//
//      return (unsigned int) ::crc32(dwPrevious, (const unsigned char *)psz, (unsigned int)strlen(psz));
//
//   }
//
//
//} // namespace axis






