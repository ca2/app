#pragma once


namespace universal_windows
{


   class CLASS_DECL_ACME file_context :
      virtual public ::file_context
   {
   public:


      file_context();
      virtual ~file_context();


      virtual bool FullPath(string & str, const ::scoped_string & scopedstrFileIn);

      virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      virtual ::u32 GetFileName(const ::file::path & pathName, string & str);

      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);

      virtual ::payload length(const ::file::path & path) override;

      virtual file_pointer get_file(const ::payload & payloadFile, const ::file::e_open & eopen) override;



   };


} // namespace universal_windows



