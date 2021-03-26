#pragma once


namespace macos
{


   class CLASS_DECL_APEX dir_context :
      virtual public ::dir_context
   {
   public:

      __reference(dir_system)      m_pdirsystem;
      __reference(file_system)      m_pfilesystem;

      dir_context();
      virtual ~dir_context();

      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status init_system() override;

      // rls fetchs should set a meaningful m_iRelative value at each returned path
      virtual ::file::listing & ls(::file::listing & path) override;


      virtual bool  is(const ::file::path & path) override;
      virtual bool  is_inside(const ::file::path & pathFolder,const ::file::path & path) override;
      virtual bool  is_inside_time(const ::file::path & path) override;
      virtual bool  name_is(const ::file::path & path) override;
      virtual bool  has_subdir(const ::file::path & path) override;

      virtual ::file::listing & root_ones(::file::listing & listing) override;
      virtual bool mk(const ::file::path & path) override;
      virtual bool rm(const ::file::path & path, bool bRecursive = true) override;


      virtual ::file::path name(const ::file::path & path);

      virtual ::file::path time() override;
      virtual ::file::path stage() override;
      virtual ::file::path stageapp() override;
      virtual ::file::path netseed() override;
      virtual ::file::path install() override;
//       virtual ::file::path profile();

      virtual ::file::path module() override;
      virtual ::file::path ca2module() override;
      virtual ::file::path time_square(const string & strPrefix = nullptr, const string & strSuffix = nullptr);
      virtual ::file::path time_log();


      virtual ::file::path trash_that_is_not_trash(const ::file::path & path) override;



      virtual ::file::path appdata() override;
      virtual ::file::path commonappdata_root() override;
      virtual ::file::path commonappdata() override;

//       virtual ::file::path usersystemappdata(const char * lpcszPrefix);
//       virtual ::file::path userappdata();
//       virtual ::file::path userdata();
//       //virtual ::file::path userfolder();
//       virtual ::file::path default_os_user_path_prefix();
//       virtual ::file::path default_userappdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin );
//       virtual ::file::path default_userdata(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin);
//       virtual ::file::path default_userfolder(::object * pobject,const string & lpcszPrefix,const string & lpcszLogin);
      virtual ::file::path userquicklaunch() override;
      virtual ::file::path userprograms() override;

      virtual ::file::path commonprograms() override;

      virtual ::file::path home() override;
      virtual ::file::path desktop() override;
      virtual ::file::path document() override;
      virtual ::file::path download() override;

      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;


   };


} // namespace macos








