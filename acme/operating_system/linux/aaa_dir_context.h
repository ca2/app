#pragma once


namespace linux
{


   class CLASS_DECL_ACME directory_context :
      virtual public ::directory_context
   {
   public:


      ::pointer<file_system>     m_pfilesystem;
      ::pointer<directory_system>      m_pdirectorysystem;


      directory_context();
      virtual ~directory_context();


      virtual void initialize(::particle * pparticle) override;

      virtual void init_system() override;
      virtual void init_context() override;


      virtual ::file::listing & ls(::file::listing & ls) override;


      virtual bool  is(const ::file::path & path) override;
      virtual bool  is_inside(const ::file::path & pathDir, const ::file::path & lpcszPath) override;

      virtual bool  is_inside_time(const ::file::path & path) override;

      virtual bool  name_is(const ::file::path & path) override;
      virtual bool  has_subdir(const ::file::path & path) override;


      virtual ::file::listing & root_ones(::file::listing & listing) override;
      virtual bool mk(const ::file::path & path) override;

      virtual bool rm(const ::file::path & psz, bool bRecursive = true) override;


      //virtual ::file::path name(const ::file::path & path);


      virtual ::file::path time() override;
      virtual ::file::path stage() override;
      virtual ::file::path stageapp() override;
      virtual ::file::path netseed() override;

      // stage in ca2os spalib
      //  virtual string matter(const ::scoped_string & scopedstr, const char * lpcsz2 = nullptr);

      //virtual ::file::path install();
//      virtual string matter(const ::scoped_string & scopedstr);
//      virtual string matter(const ::scoped_string & scopedstr, const ::scoped_string & scopedstr2);
//      virtual string matter(const ::scoped_string & scopedstr, const ::scoped_string & scopedstr2);

//      virtual string matter(const ::scoped_string & scopedstr, const ::scoped_string & scopedstr2);


//      virtual ::file::path module();
//      virtual ::file::path ca2module();
      virtual ::file::path time_square() override;
      virtual ::file::path time_log(const ::scoped_string & scopedstrId) override;


      virtual ::file::path trash_that_is_not_trash(const ::file::path & psz) override;

      virtual ::file::path appdata() override;
      virtual ::file::path commonappdata() override;
      virtual ::file::path element_commonappdata(const ::scoped_string & scopedstrElement) override;

//      virtual ::file::path usersystemappdata(const string & pcszPrefix);

//      virtual ::file::path userappdata(::particle * pparticle);
//      virtual ::file::path userdata(::particle * pparticle);
//      //virtual ::file::path userfolder(::particle * pparticle);
//      virtual ::file::path default_os_user_path_prefix(::particle * pparticle);
//      virtual ::file::path default_userappdata(const string & pcszPrefix, const string & lpcszLogin);

//      virtual ::file::path default_userdata(const string & pcszPrefix, const string & lpcszLogin);

//      virtual ::file::path default_userfolder(const string & pcszPrefix, const string & lpcszLogin);

      virtual ::file::path userquicklaunch(::particle * pparticle);
      virtual ::file::path userprograms(::particle * pparticle);

      virtual ::file::path commonprograms() override;

      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;
      virtual ::file::path download() override;
      virtual ::file::path document() override;


   };


} // namespace linux



