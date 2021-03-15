#pragma once


class CLASS_DECL_APEX compress_context :
   virtual public ::object
{
public:


   compress_context(::context_object * pcontextobject);
   virtual ~compress_context();


   bool get_patha(::file::path & path, string_array & straPath, const ::file::path & pathSource);


   bool compress(memory& memoryOut, const memory& memoryIn);
   bool uncompress(memory& memoryOut, const memory& memoryIn);


   bool gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6);

   bool ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);

   virtual bool bz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iBlockSize = 9, int iVerbosity = 0, int iWorkFactor = 0);

   virtual bool unbz(::file::file * pfileUncompressed, ::file::file * pfileCompressed);

   ::count extract_all(const ::file::path & pszDir, const ::file::path & pszFile, ::apex::application * papp);

   ::count extract_all(const ::file::path & pszFile, ::apex::application * papp);

   bool zip(const ::file::path & pszZip,const ::file::path & psz,::apex::application * papp);

   bool zip(const ::file::path & psz,::apex::application * papp);

   bool unzip(const ::payload & varFile, const ::file::path & pathZipFileCompressed);

   bool unzip(memory & m, const ::file::path & pathZipFileCompressed);


};



//#ifdef WINDOWS
//CLASS_DECL_APEX i32 my_open(const char * psz, i32 i);
//CLASS_DECL_APEX FILE * my_fopen(const char * psz, const char * pszMode);
//#else
//CLASS_DECL_APEX void _get_errno(i32 * perrno);
//CLASS_DECL_APEX i32 my_open(const char * psz, i32 i);
//CLASS_DECL_APEX FILE * my_fopen(const char * psz, const char * pszMode);
//#endif



