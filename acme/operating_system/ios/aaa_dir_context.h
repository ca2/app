#pragma once


namespace ios
{
   
   
   class CLASS_DECL_ACME directory_context :
   virtual public ::directory_context
   {
   public:
      
      
      ::pointer<directory_system>     m_pdirectorysystem;
      ::pointer<file_system>    m_pfilesystem;

      
      directory_context();
      virtual ~directory_context();
      
      
      virtual void initialize(::particle * pparticle) override;
      //virtual void update_module_path();
      virtual void init_context() override;

      
      // rls fetchs should set a meaningful m_iRelative value at each returned path
      virtual ::file::listing & ls(::file::listing & path) override;
      
      
      virtual bool  is(const ::file::path & path) override;
      virtual bool  is_inside(const ::file::path & pathFolder,const ::file::path & path) override;
      virtual bool  is_inside_time(const ::file::path & path) override;
      //virtual bool  name_is(const ::file::path & path) override;
      virtual bool  has_subdir(const ::file::path & path) override;
      
      virtual ::file::listing & root_ones(::file::listing & listing) override;
      virtual bool mk(const ::file::path & path) override;
      virtual bool rm(const ::file::path & path, bool bRecursive = true) override;
      
      
      //virtual ::file::path name(const ::file::path & path);
      
      virtual ::file::path time() override;
      virtual ::file::path stage() override;
      virtual ::file::path stageapp() override;
      //virtual ::file::path netseed() override;

      
      virtual ::file::path module() override;
      virtual ::file::path ca2module() override;
      virtual ::file::path time_square(const ::scoped_string & scopedstrPrefix = nullptr, const ::scoped_string & scopedstrSuffix = nullptr);
      virtual ::file::path time_log();
      
      
      //virtual ::file::path trash_that_is_not_trash(const ::file::path & path) override;
      
      
      
      virtual ::file::path appdata() override;
      virtual ::file::path commonappdata_root() override;
      
//      virtual ::file::path usersystemappdata(::particle * pparticle, const char * lpcszPrefix);
//      virtual ::file::path userappdata(::particle * pparticle);
//      virtual ::file::path userdata(::particle * pparticle);
//      //virtual ::file::path userfolder(::particle * pparticle);
//      virtual ::file::path default_os_user_path_prefix(::particle * pparticle);
//      virtual ::file::path default_userappdata(::particle * pparticle,const string & lpcszPrefix,const string & lpcszLogin );
//      virtual ::file::path default_userdata(::particle * pparticle,const string & lpcszPrefix,const string & lpcszLogin);
//      virtual ::file::path default_userfolder(::particle * pparticle,const string & lpcszPrefix,const string & lpcszLogin);
      virtual ::file::path userquicklaunch() override;
      virtual ::file::path userprograms() override;
      
      virtual ::file::path commonprograms() override;
      
      //virtual bool initialize();
      
      
   };
   
   
} // namespace ios



