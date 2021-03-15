#include "framework.h"
#include "zip/_.h"
#include "acme/compress/zip/_internal.h"
#include "acme/compress/gz.h"
//#include "compress_bz.h"


compress_context::compress_context(::context_object * pcontextobject)
{

   initialize(pcontextobject);

}


compress_context::~compress_context()
{


}


bool compress_context::get_patha(::file::path & path, string_array & straPath, const ::file::path & pathSource)
{

   bool bFinalIsZip = false;

   straPath.remove_all();

   path.Empty();

   {

      index iFind = -1;

      index iStart = 0;

      const char * pszFileName = pathSource;

      while ((iFind = ::str::find_ci(".zip:", pszFileName, iStart)) >= 0)
      {

         string strPath = string(&pszFileName[iStart], iFind + strlen(".zip"));

         if (path.is_empty())
         {

            path = strPath;

         }
         else
         {

            straPath.add(strPath);

         }

         iStart = iFind + strlen(".zip:");

      }

      straPath.add(&pszFileName[iStart]);

   }

   return path.has_char();

}


bool compress_context::ungz(::file::file * pfileOut, ::file::file * pfileIn)
{

   //uncompress_gz ungz(this);
   uncompress_gz ungz;

   return get_context()->file().output(pfileOut, &ungz, &::uncompress_gz::transfer, pfileIn);

}





bool compress_context::gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel)
{

   //compress_gz gz(this, iLevel);
   compress_gz gz( iLevel);

   return get_context()->file().output(pfileOut, &gz, &compress_gz::transfer, pfileIn);

}


bool compress_context::unbz(::file::file* pfileOut, ::file::file* pfileIn)
{

   __throw(error_interface_only);

   return false;

}


//
//   uncompress_bz unbz(this);
//
//   return get_context()->file().output(pfileOut, &unbz, &::uncompress_bz::transfer, pfileIn);
//
//}
//
//


bool compress_context::bz(::file::file* pfileOut, ::file::file* pfileIn, int iBlockSize, int iVerbosity, int iWorkFactor)
{

   __throw(error_interface_only);

   return false;

}



//
//   compress_bz bz(this, iBlockSize, iVerbosity, iWorkFactor);
//
//   return get_context()->file().output(pfileOut, &bz, &::compress_bz::transfer, pfileIn);
//
//
//}


bool compress_context::compress(memory & memoryOut, const ::memory & memoryIn)
{

   memoryOut.set_size(compressBound((uLong)memoryIn.get_size()) * 2);

   uLongf ulDestSize = (uLongf)memoryOut.get_size();

   i32 i = ::compress(memoryOut.get_data(), &ulDestSize, (byte *)memoryIn.get_data(), (uLongf)memoryIn.get_size());

   if (i != Z_OK)
   {

      ulDestSize = 0;

   }

   memoryOut.set_size(ulDestSize);

   return i == Z_OK;

}


bool compress_context::uncompress(memory& memoryOut, const ::memory& memoryIn)
{

   uLongf ulDestSize = (uLongf)memoryOut.get_size();

   i32 i = ::uncompress(memoryOut.get_data(), &ulDestSize, (byte*)memoryIn.get_data(), (uLongf)memoryIn.get_size());

   if (i != Z_OK)
   {

      ulDestSize = 0;

   }

   memoryOut.set_size(ulDestSize);

   return i == Z_OK;

}

//bool compress_context::uncompress(memory & dest, memory & memory)
//{
//
//   int iRate = 1;
//   while (true)
//   {
//
//      dest.allocate(memory.get_size() * 10);
//
//      uLong l;
//
//      l = uLong (dest.get_size());
//
//      int i = ::uncompress(dest.get_data(), &l, memory.get_data(), uLong (memory.get_size()));
//
//      if (i == Z_OK)
//      {
//
//         dest.allocate(l);
//
//         return true;
//
//      }
//
//      if (i == Z_BUF_ERROR)
//      {
//         iRate++;
//         if (iRate > 4)
//            return false;
//         dest.allocate(dest.get_size() * 2);
//         continue;
//      }
//
//      return false;
//
//   }
//
//}


::count compress_context::extract_all(const ::file::path & pszFile, ::apex::application * pobject)
{

   string strDir = pszFile;

   ::str::ends_eat_ci(strDir, ".zip");

   return extract_all(strDir, pszFile, pobject);

}


::count compress_context::extract_all(const ::file::path & pszDir, const ::file::path & pszFile, ::apex::application * pobject)
{
   
   ::file::patha patha;

   //zip_context zip(this);
   zip_context zip(this);
   
   zip.extract_all(pszDir, pszFile, &patha);
   
   return patha.get_count();
   
}


bool compress_context::zip(const ::file::path & pszZip, const ::file::path & psz, ::apex::application * pobject)
{

   INFO("compress_context::zip");

   zip::in_file infile;

   if (!infile.zip_open(pszZip, 0))
   {

      ERR("Could not open zip file");

      return false;

   }

   if (get_context()->dir().is(psz))
   {

      ::file::listing patha;

      ::file::path strPath;

      file_pointer file;

      get_context()->dir().rls_file(patha, psz);

      for (auto & path : patha)
      {

         auto pfile = get_context()->file().get_reader(path);

         infile.add_file(path.relative(), pfile);

      }

   }

   return true;

}


bool compress_context::zip(const ::file::path & psz, ::apex::application * pobject)
{

   __throw(todo);

   return false;

}


bool compress_context::unzip(const ::payload & varFile, const ::file::path & pathZipFileCompressed)
{

   auto pfileTarget = get_context()->file().get_writer(varFile);

   if (!pfileTarget)
   {

      return false;

   }

   memory m;

   if (!unzip(m, pathZipFileCompressed))
   {

      return false;

   }

   pfileTarget->write(m.get_data(), m.get_size());

   return true;

}


bool compress_context::unzip(memory & m, const ::file::path & pathZipFileCompressed)
{

   zip_context zip(this);

   ::file::path pathZip;

   string_array straPath;

   if(!get_patha(pathZip, straPath, pathZipFileCompressed))
   { 

      return false;

   }

   auto pfile = get_context()->file().get_reader(pathZip);

   if (!pfile)
   {

      return false;

   }

   if (!zip.extract(m, pfile, straPath))
   {

      return false;

   }

   return true;

}





