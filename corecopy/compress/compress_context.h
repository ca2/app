#pragma once


namespace core
{


   class CLASS_DECL_CORE compress_context :
      virtual public ::compress_context
   {
   public:


      compress_context(::object* pobject);
      virtual ~compress_context();


      //bool get_patha(::file::path& path, string_array& straPath, const ::file::path& pathSource);


      //bool compress(memory& memoryOut, const memory& memoryIn);
      //bool uncompress(memory& memoryOut, const memory& memoryIn);


      //bool gz(::file::file* pfileCompressed, ::file::file* pfileUncompressed, int iLevel = 6);

      //bool ungz(::file::file* pfileUncompressed, ::file::file* pfileCompressed);

      virtual bool bz(::file::file* pfileCompressed, ::file::file* pfileUncompressed, int iBlockSize = 9, int iVerbosity = 0, int iWorkFactor = 0) override;

      virtual bool unbz(::file::file* pfileUncompressed, ::file::file* pfileCompressed) override;

      //::count extract_all(const ::file::path & pszDir, const ::file::path & pszFile, ::aura::application * papp);

      //::count extract_all(const ::file::path & pszFile, ::aura::application * papp);

      //bool zip(const ::file::path & pszZip,const ::file::path & psz,::aura::application * papp);

      //bool zip(const ::file::path & psz,::aura::application * papp);

      //bool unzip(const var & varFile, const ::file::path & pathZipFileCompressed);

      //bool unzip(memory & m, const ::file::path & pathZipFileCompressed);


   };



   //#ifdef WINDOWS
   //CLASS_DECL_CORE i32 my_open(const char * psz, i32 i);
   //CLASS_DECL_CORE FILE * my_fopen(const char * psz, const char * pszMode);
   //#else
   //CLASS_DECL_CORE void _get_errno(i32 * perrno);
   //CLASS_DECL_CORE i32 my_open(const char * psz, i32 i);
   //CLASS_DECL_CORE FILE * my_fopen(const char * psz, const char * pszMode);
   //#endif


} // namespace core



