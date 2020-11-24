#pragma once


namespace uwp
{


   class CLASS_DECL_AXIS file_context :
      virtual public ::file_context
   {
   public:


      file_context();
      virtual ~file_context();


      virtual bool FullPath(string & str, const char * pszFileIn);

      virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      virtual ::u32 GetFileName(const char * pszPathName, string & str);

      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);

      virtual payload length(const ::file::path & path) override;

      virtual file_result get_file(const payload & varFile, const ::efileopen & efileopen) override;



   };


} // namespace uwp



