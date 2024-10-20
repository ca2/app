// Refactor by camilo from bz on 2021-11-10 10:26 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "uncompress.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/prototype/prototype/memory.h"


#include "acme/_operating_system.h"
#include <bzlib.h>


namespace compress_bzip2
{


   uncompress::uncompress()
   {

   }


   uncompress::~uncompress()
   {


   }


   void uncompress::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::uncompress::initialize(pparticle);

    /*  if (!estatus)
      {

         return estatus;

      }

      return estatus;*/

   }



   void uncompress::transfer(::file::file* pfileOut, ::file::file* pfileIn, transfer_progress_function transferprogressfunction)
   {

      bool done = false;

      i32 status;

      class memory memIn;
      memIn.set_size(1024 * 8);

      i64 uRead = pfileIn->read(memIn.data(), memIn.size());

      bz_stream zstream;
      zero(zstream);
      zstream.next_in = (char*)memIn.data();
      zstream.avail_in = (u32)uRead;

      class memory memory;
      memory.set_size(1024 * 256);
      ASSERT(memory.size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (BZ2_bzDecompressInit(&zstream, 0, 0) != BZ_OK)
      {
         
         throw ::exception(error_failed);

      }

      while (!done)
      {

         do
         {

            zstream.next_out = (char*)memory.data();
            zstream.avail_out = (u32)memory.size();

            // Inflate another chunk.
            status = BZ2_bzDecompress(&zstream);

            pfileOut->write(memory.data(), memory.size() - zstream.avail_out);

            if (status == BZ_STREAM_END)
            {

               done = true;

               goto stop1;

            }
            else if (status != BZ_OK)
            {

               goto stop1;

            }

         } while (zstream.avail_out == 0);

         if (uRead == 0)
         {

            break;

         }

         uRead = pfileIn->read(memIn.data(), memIn.size());

         zstream.next_in = (char*)memIn.data();

         zstream.avail_in = (u32)uRead;

      }

   stop1:

      if (BZ2_bzDecompressEnd(&zstream) != BZ_OK)
      {



      }

      if (!done)
      {

         throw ::exception(error_failed);

      }

   }


   //const i32 g_iGzUncompressLen = 1024 * 1024;
   //char * g_pchGzUncompressBuffer = nullptr;
   //
   //
   //
   //i32 bzuncompress(const ::string & pcszUncompressed, const ::string & lpcszGzFileCompressed)

   //{
   //   if (g_pchGzUncompressBuffer == nullptr)
   //   {
   //      g_pchGzUncompressBuffer = ___new char[g_iGzUncompressLen];
   //   }
   //   BZFILE * file = BZ2_bzopen(pcszGzFileCompressed, "rb");

   //   if (file == nullptr)
   //   {
   //      //fprintf_dup(stderr_dup, "bzopen error\n");
   //      return -2;
   //   }
   //   string strUn(pcszUncompressed);

   //   //   strUn += ".tmp";
   //   FILE * fileUn = FILE_open(strUn, "wb+");
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


} // namespace compress_bzip2



