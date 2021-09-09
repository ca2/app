#pragma once


namespace universal_windows
{


   class CLASS_DECL_CORE file_context :
      virtual public ::file_context
   {
   public:


      file_context();
      virtual ~file_context();


      virtual bool FullPath(string & str, const ::string & pszFileIn);

      virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      virtual ::u32 GetFileName(const ::string & pszPathName, string & str);

      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);

      virtual ::payload length(const ::file::path & path) override;

      virtual file_transport get_file(const ::payload & varFile, const ::file::e_open & eopen) override;



   };


} // namespace universal_windows



