#pragma once


//CLASS_DECL_ACME bool windows_full_path(wide_character * pszPathOut, const wide_character * pszFileIn);

//CLASS_DECL_ACME bool windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);
//CLASS_DECL_ACME ::u32 vfxGetFileName(const wide_character * pszPathName, wide_character * pszTitle, ::u32 nMax);

//CLASS_DECL_ACME void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
//CLASS_DECL_ACME void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);


namespace universal_windows
{


   class CLASS_DECL_ACME file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();



   };


} // namespace universal_windows



