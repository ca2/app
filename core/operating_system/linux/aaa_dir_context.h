#pragma once


namespace linux
{


   class CLASS_DECL_CORE dir_context :
      virtual public ::dir_context
   {
   public:


      ::pointer<file_system>     m_pfilesystem;
      ::pointer<dir_system>      m_pdirsystem;


      dir_context();
      virtual ~dir_context();


      virtual void initialize(::particle * pparticle) override;

      virtual void init_system() override;
      virtual void init_context() override;


      virtual ::file::listing & ls(::file::listing & ls) override;


      virtual bool  is(const ::file::path & path) override;
      virtual bool  is_inside(const ::file::path & pcszDir, const ::file::path & lpcszPath) override;

      virtual bool  is_inside_time(const ::file::path & pcsz) override;

      virtual bool  name_is(const ::file::path & path) override;
      virtual bool  has_subdir(const ::file::path & pcsz) override;


      virtual ::file::listing & root_ones(::file::listing & listing) override;
      virtual bool mk(const ::file::path & pcsz) override;

      virtual bool rm(const ::file::path & psz, bool bRecursive = true) override;


      //virtual ::file::path name(const ::file::path & pcsz);


      virtual ::file::path time() override;
      virtual ::file::path stage() override;
      virtual ::file::path stageapp() override;
      virtual ::file::path netseed() override;

      // stage in ca2os spalib
      //  virtual string matter(const ::string & pcsz, const ::string & lpcsz2 = nullptr);

      //virtual ::file::path install();
//      virtual string matter(const ::string & str);
//      virtual string matter(const ::string & str, const ::string & str2);
//      virtual string matter(const ::string & pcsz, const ::string & str2);

//      virtual string matter(const ::string & str, const ::string & pcsz2);


//      virtual ::file::path module();
//      virtual ::file::path ca2module();
      virtual ::file::path time_square() override;
      virtual ::file::path time_log(const string & pszId) override;


      virtual ::file::path trash_that_is_not_trash(const ::file::path & psz) override;

      virtual ::file::path appdata() override;
      virtual ::file::path commonappdata() override;
      virtual ::file::path element_commonappdata(const ::string & strElement) override;

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



