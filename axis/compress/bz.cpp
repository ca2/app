#include "framework.h"
#include "bz.h"
#include <bzlib.h>


#define MAKEU64(hi, lo) ((((u64)hi) << 32) | ((u64) lo))

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

//static const i32 gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

#define BZ_SETERR(err) m_z_err = err
extern "C"
{
   typedef  void *(* bzalloc)(void *,i32,i32);
   typedef  void(* bzfree)(void *,void *);

}

//u8 *                   m_outbuf; /* output buffer */
//uptr                   m_crc;     /* crc32 of uncompressed data */





compress_bz::compress_bz(::object * pobject, int iBlockSize, int iVerbosity, int iWorkFactor)
{

   m_iBlockSize = iBlockSize;
   m_iVerbosity = iVerbosity;
   m_iWorkFactor = iWorkFactor;

}

compress_bz::~compress_bz()
{


}


bool compress_bz::transfer(::file::file * pfileBzFileCompressed, ::file::file * pfileUncompressed)
{

   memory                     memory;
   i32                    m_CurrentBufferSize;
   bz_stream                  zstream;
   i32                    m_z_err;   /* error code for last stream operation */
   iptr                    ret;

   __zero(zstream);

   int iBlockSize             = m_iBlockSize;
   int iVerbosity             = m_iVerbosity;
   int iWorkFactor            = m_iWorkFactor;

   class memory memIn;
   memIn.set_size(1024 * 64);

   i64 uRead             = pfileUncompressed->read(memIn.get_data(), memIn.get_size());

   iBlockSize                 = max(1, min(9, iBlockSize));
   iVerbosity                 = max(0, min(4, iVerbosity));
   iWorkFactor                = max(0, min(250, iWorkFactor));

   m_CurrentBufferSize        = 1024 * 1024 * 8;
   i32 blockSize100k      = iBlockSize; // 900k
   i32 workFactor         = iWorkFactor;
   i32 verbosity          = iVerbosity;
   memory.set_size(m_CurrentBufferSize);

   zstream.bzalloc = (bzalloc)0;
   zstream.bzfree = (bzfree)0;
   zstream.opaque = (void *)0;
   zstream.next_in = (char *)memIn.get_data();
   zstream.avail_in = (u32)uRead;
   zstream.next_out = nullptr;
   zstream.avail_out = 0;
   m_z_err = BZ_OK;

   //   m_crc = crc32(0L,nullptr,0);

   i32 err = BZ2_bzCompressInit(&zstream, blockSize100k, verbosity, workFactor);

   if (err != BZ_OK || memory.get_data() == nullptr)
   {

      return false;

   }

   m_z_err = BZ_OK;

   int iState = BZ_RUN;

   while (true)
   {

      do
      {

         zstream.next_out = (char *)memory.get_data();
         zstream.avail_out = (u32)memory.get_size();

         ret = BZ2_bzCompress(&zstream, iState);

         pfileBzFileCompressed->write(memory.get_data(), memory.get_size() - zstream.avail_out);

         if (ret == BZ_STREAM_END)
         {

            goto stop1;

         }
         else if (ret == BZ_RUN_OK)
         {

            break;

         }
         else if (ret != BZ_OK)
         {

            goto stop1;

         }

      }
      while (zstream.avail_out == 0);

      uRead = pfileUncompressed->read(memIn.get_data(), memIn.get_size());

      if (uRead == 0)
      {

         iState = BZ_FINISH;

         zstream.next_in = (char *)nullptr;

         zstream.avail_in = (u32)0;

      }
      else
      {

         zstream.next_in = (char *)memIn.get_data();

         zstream.avail_in = (u32)uRead;

      }

   }

stop1:

   BZ_SETERR(BZ_OK);
   BZ2_bzCompressEnd(&(zstream));


   return ret >= 0;

}



uncompress_bz::uncompress_bz(::layered * pobjectContext) :
   ::object(pobjectContext)
{

}

uncompress_bz::~uncompress_bz()
{
}


bool uncompress_bz::transfer(::file::file * pfileOut, ::file::file * pfileIn)
{

   bool done = false;

   i32 status;

   class memory memIn;
   memIn.set_size(1024 * 8);

   i64 uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

   bz_stream zstream;
   __zero(zstream);
   zstream.next_in = (char *)memIn.get_data();
   zstream.avail_in = (u32)uRead;

   class memory memory;
   memory.set_size(1024 * 256);
   ASSERT(memory.get_size() <= UINT_MAX);

   // inflateInit2 knows how to deal with gzip format
   if (BZ2_bzDecompressInit(&zstream, 0, 0) != BZ_OK)
   {
      return false;
   }

   while (!done)
   {

      do
      {

         zstream.next_out = (char *)memory.get_data();
         zstream.avail_out = (u32)memory.get_size();

         // Inflate another chunk.
         status = BZ2_bzDecompress(&zstream);

         pfileOut->write(memory.get_data(), memory.get_size() - zstream.avail_out);

         if (status == BZ_STREAM_END)
         {

            done = true;

            goto stop1;

         }
         else if (status != BZ_OK)
         {

            goto stop1;

         }

      }
      while (zstream.avail_out == 0);

      if (uRead == 0)
      {

         break;

      }

      uRead = pfileIn->read(memIn.get_data(), memIn.get_size());

      zstream.next_in = (char *)memIn.get_data();

      zstream.avail_in = (u32)uRead;

   }

stop1:

   if(BZ2_bzDecompressEnd(&zstream) != BZ_OK)
   {



   }

   return done;

}





//const i32 g_iGzUncompressLen = 1024 * 1024;
//char * g_pchGzUncompressBuffer = nullptr;
//
//
//
//i32 bzuncompress(const char * pcszUncompressed, const char * lpcszGzFileCompressed)

//{
//   if (g_pchGzUncompressBuffer == nullptr)
//   {
//      g_pchGzUncompressBuffer = new char[g_iGzUncompressLen];
//   }
//   BZFILE * file = BZ2_bzopen(pcszGzFileCompressed, "rb");

//   if (file == nullptr)
//   {
//      //fprintf_dup(stderr_dup, "bzopen error\n");
//      return -2;
//   }
//   string strUn(pcszUncompressed);

//   //   strUn += ".tmp";
//   FILE * fileUn = fopen_dup(strUn, "wb+");
//   if (fileUn == nullptr)
//   {
//      BZ2_bzclose(file);
//      return -1;
//   }
//   i32 uncomprLen;
//   while ((uncomprLen = BZ2_bzread(file, g_pchGzUncompressBuffer, g_iGzUncompressLen)) > 0)
//   {
//      fwrite_dup(g_pchGzUncompressBuffer, 1, uncomprLen, fileUn);
//   }
//   fclose_dup(fileUn);
//   BZ2_bzclose(file);
//   //   ::CopyFile(strUn, pcszUncompressed, false);

//   //   ::DeleteFile(strUn);
//   return 0;
//}
