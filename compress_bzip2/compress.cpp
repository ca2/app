// Refactor by camilo from bz on 2021-11-10 10:22 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"
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

namespace compress_bzip2
{


   compress::compress()
   {

   }


   compress::~compress()
   {


   }


   void compress::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void compress::set_bzip2_parameters(int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      m_iBlockSize = iBlockSize;
      m_iVerbosity = iVerbosity;
      m_iWorkFactor = iWorkFactor;

      //return ::success;

   }


   void compress::transfer(::file::file* pfileBzFileCompressed, ::file::file* pfileUncompressed)
   {

      memory                     memory;
      i32                    m_CurrentBufferSize;
      bz_stream                  zstream;
      i32                    m_z_err;   /* error code for last stream operation */
      iptr                    ret;

      zero(zstream);

      int iBlockSize = m_iBlockSize;
      int iVerbosity = m_iVerbosity;
      int iWorkFactor = m_iWorkFactor;

      class memory memIn;
      memIn.set_size(1024 * 64);

      i64 uRead = pfileUncompressed->read(memIn.get_data(), memIn.get_size());

      iBlockSize = maximum(1, minimum(9, iBlockSize));
      iVerbosity = maximum(0, minimum(4, iVerbosity));
      iWorkFactor = maximum(0, minimum(250, iWorkFactor));

      m_CurrentBufferSize = 1024 * 1024 * 8;
      i32 blockSize100k = iBlockSize; // 900k
      i32 workFactor = iWorkFactor;
      i32 verbosity = iVerbosity;
      memory.set_size(m_CurrentBufferSize);

      zstream.bzalloc = (bzalloc)0;
      zstream.bzfree = (bzfree)0;
      zstream.opaque = (void*)0;
      zstream.next_in = (char*)memIn.get_data();
      zstream.avail_in = (u32)uRead;
      zstream.next_out = nullptr;
      zstream.avail_out = 0;
      m_z_err = BZ_OK;

      //   m_crc = crc32(0L,nullptr,0);

      i32 err = BZ2_bzCompressInit(&zstream, blockSize100k, verbosity, workFactor);

      if (err != BZ_OK || memory.get_data() == nullptr)
      {

         throw ::exception(error_failed);

      }

      m_z_err = BZ_OK;

      int iState = BZ_RUN;

      while (true)
      {

         do
         {

            zstream.next_out = (char*)memory.get_data();
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

         } while (zstream.avail_out == 0);

         uRead = pfileUncompressed->read(memIn.get_data(), memIn.get_size());

         if (uRead == 0)
         {

            iState = BZ_FINISH;

            zstream.next_in = (char*)nullptr;

            zstream.avail_in = (u32)0;

         }
         else
         {

            zstream.next_in = (char*)memIn.get_data();

            zstream.avail_in = (u32)uRead;

         }

      }

   stop1:

      BZ_SETERR(BZ_OK);
      BZ2_bzCompressEnd(&(zstream));


      if (ret < 0)
      {

         throw ::exception(error_failed);

      }// ? ::success : ::error_failed;

   }


} // namespace compress_bzip2



