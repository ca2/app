#pragma once


//CLASS_DECL_ACME bool windows_full_path(unichar * pszPathOut, const unichar * pszFileIn);

//CLASS_DECL_ACME bool windows_full_path(wstring & wstrFullPath, const wstring & wstrPath);
//CLASS_DECL_ACME unsigned int vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, unsigned int nMax);

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



