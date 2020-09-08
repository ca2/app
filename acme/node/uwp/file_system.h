#pragma once


//CLASS_DECL_ACME bool vfxFullPath(unichar * pszPathOut, const unichar * pszFileIn);

//CLASS_DECL_ACME bool vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);
//CLASS_DECL_ACME UINT vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, UINT nMax);

//CLASS_DECL_ACME void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
//CLASS_DECL_ACME void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);


namespace uwp
{


   class CLASS_DECL_ACME file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();



   };


} // namespace uwp



