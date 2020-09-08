#pragma once


//CLASS_DECL_APEX bool vfxFullPath(unichar * pszPathOut, const unichar * pszFileIn);

//CLASS_DECL_APEX bool vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);
//CLASS_DECL_APEX UINT vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, UINT nMax);

//CLASS_DECL_APEX void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
//CLASS_DECL_APEX void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);


namespace uwp
{


   class CLASS_DECL_APEX file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();



   };


} // namespace uwp



