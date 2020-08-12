#pragma once


namespace uwp
{


   namespace axis
   {


      class file_system:
         virtual public ::_UWP::file_system,
         virtual public ::file::axis::system
      {
      public:


         file_system(::object * pobject);
         virtual ~file_system();


         //virtual bool FullPath(string & str,const char * pszFileIn);

         //virtual bool FullPath(wstring & wstrFullPath,const wstring & wstrPath);
         //virtual UINT GetFileName(const char * pszPathName,string & str);

         //virtual void GetModuleShortFileName(HINSTANCE hInst,string & strShortName);


         virtual var length(const ::file::path & path, ::aura::application * papp) override;


         virtual file_result get_file(::object * pobject, var varFile, UINT nOpenFlags) override;


      };


   } // namespace axis


} // namespace uwp




















































