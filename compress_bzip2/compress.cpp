// Refactor by camilo from bz on 2021-11-10 10:22 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "compress.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/prototype/prototype/memory.h"


#include "acme/_operating_system.h"
#include <bzlib.h>


#define MAKEU64(hi, lo) ((((unsigned long long)hi) << 32) | ((unsigned long long) lo))

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

//static const int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

#define BZ_SETERR(err) m_z_err = err
extern "C"
{
   typedef  void *(* bzalloc)(void *,int,int);
   typedef  void(* bzfree)(void *,void *);

}

//unsigned char *                   m_outbuf; /* output buffer */
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
      
      ::compress::initialize(pparticle);

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


   void compress::transfer(::file::file* pfileBzFileCompressed, ::file::file* pfileUncompressed, transfer_progress_function transferprogressfunction)
   {

      memory                     memory;
      int                    m_CurrentBufferSize;
      bz_stream                  zstream;
      int                    m_z_err;   /* error code for last stream operation */
      iptr                    ret;

      zero(zstream);

      int iBlockSize = m_iBlockSize;
      int iVerbosity = m_iVerbosity;
      int iWorkFactor = m_iWorkFactor;

      class memory memIn;
      memIn.set_size(1024 * 64);

      long long uRead = pfileUncompressed->read(memIn.data(), memIn.size());

      iBlockSize = maximum(1, minimum(9, iBlockSize));
      iVerbosity = maximum(0, minimum(4, iVerbosity));
      iWorkFactor = maximum(0, minimum(250, iWorkFactor));

      m_CurrentBufferSize = 1024 * 1024 * 8;
      int blockSize100k = iBlockSize; // 900k
      int workFactor = iWorkFactor;
      int verbosity = iVerbosity;
      memory.set_size(m_CurrentBufferSize);

      zstream.bzalloc = (bzalloc)0;
      zstream.bzfree = (bzfree)0;
      zstream.opaque = (void*)0;
      zstream.next_in = (char*)memIn.data();
      zstream.avail_in = (unsigned int)uRead;
      zstream.next_out = nullptr;
      zstream.avail_out = 0;
      m_z_err = BZ_OK;

      //   m_crc = crc32(0L,nullptr,0);

      int err = BZ2_bzCompressInit(&zstream, blockSize100k, verbosity, workFactor);

      if (err != BZ_OK || memory.data() == nullptr)
      {

         throw ::exception(error_failed);

      }

      m_z_err = BZ_OK;

      int iState = BZ_RUN;

      while (true)
      {

         do
         {

            zstream.next_out = (char*)memory.data();
            zstream.avail_out = (unsigned int)memory.size();

            ret = BZ2_bzCompress(&zstream, iState);

            pfileBzFileCompressed->write(memory.data(), memory.size() - zstream.avail_out);

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

         uRead = pfileUncompressed->read(memIn.data(), memIn.size());

         if (uRead == 0)
         {

            iState = BZ_FINISH;

            zstream.next_in = (char*)nullptr;

            zstream.avail_in = (unsigned int)0;

         }
         else
         {

            zstream.next_in = (char*)memIn.data();

            zstream.avail_in = (unsigned int)uRead;

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



