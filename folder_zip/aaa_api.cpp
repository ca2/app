#include "framework.h"


namespace zip
{


   api::api()
   {

   }


   api::~api()
   {

   }


   void * api::unzip_open(memory_file * pfile)
   {

      void * pf = unzOpen2("pad", (zlib_filefunc_def*)pfile->m_pvoidFileFuncDef);

      if(pf == nullptr)
         return nullptr;

      // m_mapUnzip.set_at(pf, pfile);

      return pf;

   }


   unzFile api::unzip_open (file * pfile)
   {
      unzFile pf = unzOpen2("pad", (zlib_filefunc_def*)pfile->m_pvoidFileFuncDef);
      if(pf == nullptr)
         return nullptr;

      //   m_mapUnzip.set_at(pf, pfile);

      return pf;

   }


   //zipFile api::zip_open(file * pfile)
   //{
   //   zipFile pf = zipOpen2("pad", APPEND_STATUS_CREATE, nullptr, (zlib_filefunc_def *) pfile->m_pvoidFileFuncDef);
   //   if(pf == nullptr)
   //      return nullptr;

   //   // m_mapUnzip.set_at(pf, pfile);

   //   return pf;

   //}


} // namespace zip



