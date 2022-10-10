#pragma once


namespace android
{


   class CLASS_DECL_AURA dir_context :
      virtual public ::dir_context
   {
   public:

      
      ::pointer<dir_system>      m_pdirsystem;
      ::pointer<file_system>     m_pfilesystem;


      dir_context();
      virtual ~dir_context();

      virtual void initialize(::object * pobject) override;

      virtual void init_system() override;
      virtual void init_context() override;

      virtual ::file::listing & ls(::file::listing & listing) override;
      virtual ::file::listing & root_ones(::file::listing & listing) override;


      //virtual bool  is(const ::file::path & path, bool bRequired = false, bool bBypassCache = false);
      virtual bool  is(const ::file::path & path) override;
      virtual bool  is_inside(const ::file::path & lpcszDir, const ::file::path & lpcszPath) override;
      virtual bool  is_inside_time(const ::file::path & lpcsz) override;
      virtual bool  name_is(const ::file::path & str) override;
      virtual bool  has_subdir(const ::file::path & lpcsz) override;

      virtual bool mk(const ::file::path & lpcsz) override;
      virtual bool rm(const ::file::path & psz, bool bRecursive = true) override;



      //virtual string warehouse();
      virtual ::file::path time() override;
      virtual ::file::path stage() override;
      virtual ::file::path stageapp() override;
      virtual ::file::path netseed() override;

      // stage in ccwarehouse spalib
      virtual ::file::path install() override;

      //virtual ::file::path module();
      //virtual ::file::path ca2module();
      virtual ::file::path time_square() override;
      virtual ::file::path time_log(const ::string & strId) override;


      virtual ::file::path trash_that_is_not_trash(const ::file::path & psz) override;

      virtual ::file::path appdata() override;
      virtual ::file::path commonappdata() override;


      //virtual ::file::path usersystemappdata(const string & lpcszPrefix);
      //virtual ::file::path userappdata();
      //virtual ::file::path userdata();
      ////virtual ::file::path userfolder();
      //virtual ::file::path default_os_user_path_prefix();
      //virtual ::file::path default_userappdata(const string & lpcszPrefix, const string & lpcszLogin);
      //virtual ::file::path default_userdata(const string & lpcszPrefix, const string & lpcszLogin);
      //virtual ::file::path default_userfolder(const string & lpcszPrefix, const string & lpcszLogin);
      virtual ::file::path userquicklaunch() override;
      virtual ::file::path userprograms() override;
      virtual ::file::path bookmark() override;

      virtual ::file::path commonprograms() override;

      virtual ::file::path commonappdata_root() override;

//      virtual bool initialize();

   };

} // namespace android



