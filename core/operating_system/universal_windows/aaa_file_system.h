#pragma once


//CLASS_DECL_CORE bool windows_full_path(unichar * pszPathOut, const unichar * pszFileIn);

//CLASS_DECL_CORE bool windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);
//CLASS_DECL_CORE ::u32 vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, ::u32 nMax);

//CLASS_DECL_CORE void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
//CLASS_DECL_CORE void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);


namespace universal_windows
{


   class CLASS_DECL_CORE file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();



   };


} // namespace universal_windows



