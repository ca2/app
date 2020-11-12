#pragma once


CLASS_DECL_APEX bool vfxFullPath(unichar * pszPathOut, const unichar * pszFileIn);

CLASS_DECL_APEX bool vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);
CLASS_DECL_APEX ::u32 vfxGetFileName(const unichar * pszPathName, unichar * pszTitle, ::u32 nMax);

CLASS_DECL_APEX void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);
CLASS_DECL_APEX void vfxGetModuleShortFileName(HINSTANCE hInst, string & strShortName);


namespace windows
{


   class CLASS_DECL_APEX file_context :
      virtual public ::file_context
   {
   public:


      __reference(file_system)      m_pfilesystem;
      __reference(dir_system)       m_pdirsystem;


      file_context();
      virtual ~file_context();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual ::estatus init_system() override;


      virtual bool get_status(const ::file::path & path, ::file::file_status & status);
      virtual ::status::result set_status(const ::file::path & path, const ::file::file_status & status);



      virtual bool FullPath(string & str, const char * pszFileIn);

      virtual bool FullPath(wstring & wstrFullPath, const wstring & wstrPath);
      virtual ::u32 GetFileName(const char * pszPathName, string & str);

      virtual void GetModuleShortFileName(HINSTANCE hInst, string & strShortName);
      virtual var length(const ::file::path & path) override;

      virtual bool get_last_write_time(FILETIME * pfiletime, const string & strFilename);

      virtual ::estatus update_module_path() override;

      virtual file_result get_file(const var & varFile, const efileopen & nOpenFlags) override;



      virtual ::file::path dropbox_info_json() override;

      //virtual ::file::path onedrive_global_ini(::layered * pobjectContext) override;
      //virtual ::file::path onedrive_cid_ini(::layered * pobjectContext) override;


   };


} // namespace windows



